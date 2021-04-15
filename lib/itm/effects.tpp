DEFINE_PATCH_FUNCTION ~get_description_effect~ RET description BEGIN
	LPM ~block_to_vars~

	SPRINT description ~~

	// Cas à gérer par chaque opcode
	PATCH_IF probability == 100 BEGIN
		//TODO: Propriété : [xxx]
		//TODO: Immunité contre [xxx]
	END
	ELSE BEGIN
		//TODO: xx% de chance de [xxx]
	END

	PATCH_TRY
		// Chaque fonction va simplement retourner la description de l'effet
		LPM ~opcode_%opcode%~
	WITH
		DEFAULT
			SPRINT description ~Opcode "%opcode%" pas encore gere~
			PATCH_WARN "%SOURCE_FILE% : Opcode '%opcode%' non gere : %target% %power% %parameter1% %parameter2% %timingMode% %resistance% %duration% %probability1% %probability2% '%resref%' %diceCount% %diceSides% %saveType% %saveBonus% %special%"
	END
END

DEFINE_PATCH_MACRO ~block_to_vars~ BEGIN
	READ_SHORT (blockOffset) opcode
	READ_BYTE  (blockOffset + EFF_target) target
	READ_BYTE  (blockOffset + EFF_power) power
	READ_LONG  (blockOffset + EFF_parameter1) parameter1
	READ_LONG  (blockOffset + EFF_parameter2) parameter2
	READ_BYTE  (blockOffset + EFF_timing_mode) timingMode
	READ_BYTE  (blockOffset + EFF_resistance) resistance
	READ_LONG  (blockOffset + EFF_duration) duration
	READ_BYTE  (blockOffset + EFF_probability1) probability1
	READ_BYTE  (blockOffset + EFF_probability2) probability2
	READ_ASCII (blockOffset + EFF_resref_key) resref
	READ_LONG  (blockOffset + EFF_dice_count) diceCount
	READ_LONG  (blockOffset + EFF_dice_sides) diceSides
	READ_LONG  (blockOffset + EFF_save_type) saveType
	READ_LONG  (blockOffset + EFF_save_bonus) saveBonus
	READ_LONG  (blockOffset + 0x2c) special

	SET probability = probability1 - probability2
END

DEFINE_PATCH_MACRO ~abilities_groups_to_vars~ BEGIN
	SPRINT opcode "%data_0%"
	SPRINT target "%data_1%"
	SPRINT power "%data_2%"
	SPRINT parameter1 "%data_3%"
	SPRINT parameter2 "%data_4%"
	SPRINT timingMode "%data_5%"
	SPRINT resistance "%data_6%"
	SPRINT duration "%data_7%"
	SPRINT probability1 "%data_8%"
	SPRINT probability2 "%data_9%"
	SPRINT resref "%data_10%"
	SPRINT diceCount "%data_11%"
	SPRINT diceSides "%data_12%"
	SPRINT saveType "%data_13%"
	SPRINT saveBonus "%data_14%"
	SPRINT special "%data_15%"
END


DEFINE_PATCH_FUNCTION ~get_damage_value~ INT_VAR diceCount = 0 diceSides = 0 damageAmount = 0 RET damage BEGIN
	SPRINT ~damage~ ~~

	PATCH_IF diceCount > 0 AND diceSides > 0 BEGIN
		SPRINT ~damage~ @10014 // ~%diceCount%d%diceSides%~
	END
	PATCH_IF damageAmount > 0 BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%damageAmount%~ RET damageAmount = value END
		PATCH_IF ~damage~ STRING_EQUAL ~~ BEGIN
			SPRINT ~damage~ ~%damageAmount%~
		END
		ELSE BEGIN
			SPRINT ~damage~ ~%damage% %damageAmount%~
		END
	END
END