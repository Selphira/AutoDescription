DEFINE_PATCH_FUNCTION ~get_description_effect~ RET description BEGIN
	LPM ~block_to_vars~

	SPRINT description ~~

	PATCH_IF probability == 100 BEGIN
		PATCH_TRY
			LPM ~opcode_%opcode%~
		WITH
			DEFAULT
				SPRINT description ~Opcode "%opcode%" pas encore gere~
				PATCH_WARN "%SOURCE_FILE% : opcode_%opcode% non gere : %target% %power% %parameter1% %parameter2% %timingMode% %resistance% %duration% %probability1% %probability2% '%resref%' %diceCount% %diceSides% %saveType% %saveBonus% %special%"
		END
	END
	ELSE BEGIN
		PATCH_TRY
			LPM ~opcode_probability_%opcode%~
		WITH
			DEFAULT
				SPRINT description ~Opcode "%opcode%" pas encore gere~
				PATCH_WARN "%SOURCE_FILE% : opcode_probability_%opcode% non gere : %target% %power% %parameter1% %parameter2% %timingMode% %resistance% %duration% %probability1% %probability2% '%resref%' %diceCount% %diceSides% %saveType% %saveBonus% %special%"
		END
	END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND timingMode == TIMING_duration AND duration > 0 BEGIN
		LPF ~get_duration_value~ INT_VAR duration RET duration = value END

		PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
			SPRINT description ~%description% %duration%~
		END
	END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND saveType != 0 BEGIN
        PATCH_IF saveType == FLAG_SAVINGTHROW_spell BEGIN
            SPRINT saveType @102033 // ~contre les sorts~
        END
        ELSE PATCH_IF saveType == FLAG_SAVINGTHROW_breath BEGIN
            SPRINT saveType @102032 // ~contre les souffles~
        END
        ELSE PATCH_IF saveType == FLAG_SAVINGTHROW_death BEGIN
            SPRINT saveType @102029 // ~contre la paralysie, la mort et les poisons~
        END
        ELSE PATCH_IF saveType == FLAG_SAVINGTHROW_wand BEGIN
            SPRINT saveType @102030 // ~contre les baguettes, les sceptres et les bâtons~
        END
        ELSE PATCH_IF saveType == FLAG_SAVINGTHROW_polymorph BEGIN
            SPRINT saveType @102031 // ~contre la pétrification et la métamorphose~
        END

		// TODO: Toujours pour annuler ??

        PATCH_IF saveBonus != 0 BEGIN
			LPF ~signed_value~ INT_VAR value = EVAL ~%saveBonus%~ RET saveBonus = value END
			SPRINT saveStr @102122 // ~jet de sauvegarde à %saveBonus% %saveType% pour annuler~
        END
        ELSE BEGIN
			SPRINT saveStr @102121 // ~jet de sauvegarde %saveType% pour annuler~
        END

		SPRINT description ~%description% (%saveStr%)~
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

DEFINE_PATCH_FUNCTION ~get_duration_value~ INT_VAR duration = 0 RET value BEGIN
	SPRINT value ~~
	PATCH_IF duration > 0 BEGIN
        LPF ~convert_duration~ INT_VAR duration RET turns rounds seconds END

	    PATCH_IF (turns > 0 AND (rounds > 0 OR seconds > 0)) OR (rounds > 0 AND (turns > 0 AND seconds > 0)) BEGIN
	        PATCH_IF duration == 1 BEGIN
	            SPRINT value @100040 // ~pendant 1 seconde~
	        END
	        ELSE BEGIN
	            SPRINT value @100041 // ~pendant %duration% secondes~
	        END
	    END
	    ELSE PATCH_IF turns > 0 BEGIN
	        PATCH_IF turns == 1 BEGIN
	            SPRINT value @100042 // ~pendant 1 tour~
	        END
	        ELSE BEGIN
	            SPRINT value @100043 // ~pendant %turns% tours~
	        END
	    END
	    ELSE PATCH_IF rounds > 0 BEGIN
	        PATCH_IF rounds == 1 BEGIN
	            SPRINT value @100044 // ~pendant 1 round~
	        END
	        ELSE BEGIN
	            SPRINT value @100045 // ~pendant %round% rounds~
	        END
	    END
	    ELSE PATCH_IF seconds > 0 BEGIN
	        PATCH_IF seconds == 1 BEGIN
	            SPRINT value @100040 // ~pendant 1 seconde~
	        END
	        ELSE BEGIN
	            SET duration = seconds
	            SPRINT value @100041 // ~pendant %duration% secondes~
	        END
	    END
    END
END

DEFINE_PATCH_FUNCTION ~convert_duration~ INT_VAR duration = 0 RET turns rounds seconds BEGIN
    SET turns = duration / 60
    SET duration = duration MODULO 60
    SET rounds = duration / 6
    SET duration = duration MODULO 6
    SET seconds = duration
END
