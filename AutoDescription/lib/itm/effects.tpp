DEFINE_PATCH_FUNCTION ~get_description_effect~
	INT_VAR
		forceTarget = 0
		forceProbability = 0
		forcedProbability = 100
	STR_VAR
		theTarget = ~~
		ofTheTarget = ~~
		toTheTarget = ~~
	RET
		description
		sort
BEGIN
	SET opcode_n = opcode
	SET ignoreDuration = 0
	SET saveAdded = 0
	SET saveForHalf = 0
	SET sort = 0
	SET forceSort = 0

	LPM ~block_to_vars~

	SPRINT condition ~~
	SPRINT method ~~
	SPRINT description ~~
	SPRINT opcode_target ~~

	PATCH_IF forceProbability == 1 BEGIN
		SET probability = forcedProbability
	END

	PATCH_TRY
		// ITM global (equipped) effects: Target is always the wearer, this field isn’t relevant.
		PATCH_IF target == TARGET_FX_none AND ~%SOURCE_EXT%~ STRING_EQUAL_CASE ~ITM~ BEGIN
			SET target = TARGET_FX_self
		END

		PATCH_IF target > 9 BEGIN
			LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode_n%: Invalid target : %target%~ END
		END
		ELSE PATCH_IF target != TARGET_FX_none BEGIN // On ignore les effets dont la cible est none (Ex: BARBEAXE.ITM qui ne passe pas la force du porteur à 20)
			PATCH_IF VARIABLE_IS_SET $opcodes_parameters_should_be_zero(~%opcode%~) AND (parameter1 != 0 OR parameter2 != 0) BEGIN
				LPF ~log_warning~ STR_VAR type = ~error~ message = EVAL ~Opcode %opcode_n%: Les 2 parametres doivent avoir la valeur 0~ END
			END
			ELSE BEGIN
				PATCH_IF abilityType == AbilityType_Equipped BEGIN
					SPRINT opcode_target ~_self~
					PATCH_IF forceTarget == 0 BEGIN
						SPRINT theTarget   @102472 // ~le porteur~
						SPRINT ofTheTarget @101086 // ~du porteur~
						SPRINT toTheTarget @101180 // ~au porteur~
					END
				END
				ELSE BEGIN
					// TODO: Si abilityType == AbilityType_Combat ou AbilityType_Charge, préciser qu'il faut ajouter "au porteur|du porteur|le porteur ou à la cible|de la cible|la cible"
					// Serait ajouté dans une variable qu'il suffira d'utiliser
					// Pas très i18n friendly par contre, car cela se base sur la construction des phrases en Français... mais bon, pas grave !
					PATCH_IF target == TARGET_FX_self OR target == TARGET_FX_original_caster BEGIN
						SPRINT opcode_target ~_self~
						PATCH_IF forceTarget == 0 BEGIN
							SPRINT theTarget   @102472 // ~le porteur~
							SPRINT ofTheTarget @101086 // ~du porteur~
							SPRINT toTheTarget @101180 // ~au porteur~
						END
					END
					ELSE PATCH_IF target == TARGET_FX_preset OR target == TARGET_FX_everyone_except_self BEGIN
						SPRINT opcode_target ~_target~
						PATCH_IF forceTarget == 0 BEGIN
							SPRINT theTarget   @102471 // ~la cible~
							SPRINT ofTheTarget @101085 // ~de la cible~
							SPRINT toTheTarget @101181 // ~à la cible~
						END
					END
					ELSE PATCH_IF target == TARGET_FX_party BEGIN
						SPRINT opcode_target ~_party~
						PATCH_IF forceTarget == 0 BEGIN
							SPRINT theTarget   @102473 // ~les membres du groupe~
							SPRINT ofTheTarget @101088 // ~des membres du groupe~
							SPRINT toTheTarget @101182 // ~aux membres du groupe~
						END
					END
				END

				LPM ~add_target_level~

				PATCH_IF NOT ~%opcode_target%~ STRING_EQUAL ~~ BEGIN
					PATCH_IF probability == 100 BEGIN
						SPRINT method ~opcode%opcode_target%_%opcode_n%~
						LPM ~%method%~
						LPM ~set_opcode_sort~
					END
					ELSE BEGIN
						SPRINT method ~opcode%opcode_target%_probability_%opcode_n%~
						SET probability += 1
						LPM ~%method%~
						LPM ~set_opcode_sort~
						PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
							LPF ~percent_value~ INT_VAR value = EVAL ~%probability%~ RET probability = value END
							SPRINT description @101125 // ~%probability% de chance %description%~
						END
					END

					LPM ~add_condition~
					LPM ~add_duration~
					LPM ~add_save~
				END
				ELSE BEGIN
					LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode_n%: Unknow target : %target% ~ END
				END
			END
		END
		ELSE BEGIN
			LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode_n%: Target est none~ END
		END
	WITH
		~Failure("Unknown macro: \%method%")~
		BEGIN
			LPF ~log_warning~ STR_VAR message = EVAL ~Unknown macro: %method%~ END
			PATCH_FAIL ~Unknown macro: %method%~
		END
		DEFAULT
			LPF ~log_warning~ STR_VAR message = EVAL ~FAILURE: opcode %opcode_n%: %ERROR_MESSAGE%~ END
			PATCH_FAIL ~Opcode %opcode_n%: %ERROR_MESSAGE%~
	END
END

DEFINE_PATCH_MACRO ~set_opcode_sort~ BEGIN
	PATCH_IF opcode == 219 BEGIN
		SET opcode = opcode_n
	END

	PATCH_IF forceSort == 0 BEGIN
		PATCH_IF VARIABLE_IS_SET $sort_opcodes(~%opcode%~) BEGIN
			SET sort = $sort_opcodes(~%opcode%~) + ((100 - probability) * 10000)
		END
		ELSE BEGIN
			SET sort = 400 + ((100 - probability) * 10000)
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_description_effect2~ INT_VAR resetTarget = 0 RET description saveAdded ignoreDuration BEGIN
	READ_SHORT EFF2_opcode opcode
	READ_BYTE  EFF2_target target
	READ_BYTE  EFF2_power power
	READ_LONG  EFF2_parameter1 parameter1
	READ_LONG  EFF2_parameter2 parameter2
	READ_LONG  EFF2_duration duration
	READ_BYTE  EFF2_probability1 probability1
	READ_BYTE  EFF2_probability2 probability2
	READ_ASCII EFF2_resource resref
	READ_LONG  EFF2_dice_thrown diceCount
	READ_LONG  EFF2_dice_sides diceSides
	READ_LONG  EFF2_save_type saveType
	READ_LONG  EFF2_save_bonus saveBonus
	READ_LONG  EFF2_stacking_id_tobex specialEE
	READ_LONG  EFF2_parameter3 parameter3
	READ_LONG  EFF2_parameter4 parameter4
	READ_ASCII EFF2_resource2 resref2
	READ_ASCII EFF2_resource3 resref3

	PATCH_IF is_ee == 1 BEGIN
		SET special = specialEE
	END

	SET parentProbability = probability
	SET probability = probability1 - probability2
	SPRINT condition ~~
	SPRINT description ~~

	PATCH_IF target == TARGET_FX_self OR abilityType == AbilityType_Equipped BEGIN
        SPRINT macro ~opcode_self_~
        PATCH_IF resetTarget == 1 BEGIN
	        SPRINT theTarget   @102472 // ~le porteur~
	        SPRINT ofTheTarget @101086 // ~du porteur~
	        SPRINT toTheTarget @101180 // ~au porteur~
        END
    END
    ELSE PATCH_IF target == TARGET_FX_preset OR target == TARGET_FX_everyone_except_self BEGIN
        SPRINT macro ~opcode_target_~
        PATCH_IF resetTarget == 1 BEGIN
	        SPRINT theTarget   @102471 // ~la cible~
	        SPRINT ofTheTarget @101085 // ~de la cible~
	        SPRINT toTheTarget @101181 // ~à la cible~
        END
    END
    ELSE PATCH_IF target == TARGET_FX_party BEGIN
        SPRINT macro ~opcode_party_~
        PATCH_IF resetTarget == 1 BEGIN
	        SPRINT theTarget   @102473 // ~les membres du groupe~
	        SPRINT ofTheTarget @101088 // ~des membres du groupe~
	        SPRINT toTheTarget @101182 // ~aux membres du groupe~
        END
    END

	PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
		PATCH_IF probability == 100 AND (~%macro%~ STRING_MATCHES_REGEXP ~_probability$~) == 0 BEGIN
			PATCH_FAIL "%item%: %SOURCE_FILE%: probabilite differentes du 177 et de l'effet pointe."
		END

		PATCH_IF VARIABLE_IS_SET $opcodes_parameters_should_be_zero(~%opcode%~) AND (parameter1 != 0 OR parameter2 != 0) BEGIN
            LPF ~log_warning~ STR_VAR type = ~error~ message = EVAL ~Opcode %opcode_n%: Les 2 parametres doivent avoir la valeur 0~ END
        END
        ELSE BEGIN
			PATCH_TRY
				PATCH_IF probability < 100 OR parentProbability < 100 BEGIN
					SPRINT method ~%macro%probability_%opcode%~
					LPM ~%method%~
					PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND parentProbability == 100 BEGIN
						LPF ~percent_value~ INT_VAR value = EVAL ~%probability%~ RET probability = value END
						SPRINT description @101125 // ~%probability% de chance %description%~
					END
				END
				ELSE BEGIN
					SPRINT method ~%macro%%opcode%~
					LPM ~%method%~
				END
			WITH
				~Failure("Unknown macro: \%method%")~
				BEGIN
					PATCH_FAIL ~Failure("Unknown macro: %method%")~
				END
				DEFAULT
					PATCH_FAIL ~%ERROR_MESSAGE%~
			END
        END
	END
	ELSE PATCH_IF $ignored_opcodes(~%opcode%~) == 1 BEGIN
		LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode% à gérer.~ END
	END

	LPM ~add_condition~
	LPM ~add_duration~
	LPM ~add_save~
END

DEFINE_PATCH_MACRO ~add_condition~ BEGIN
	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND NOT ~%condition%~ STRING_EQUAL ~~ BEGIN
		SPRINT description ~%condition%%semicolon%%description%~
	END
END

DEFINE_PATCH_MACRO ~add_duration~ BEGIN
	PATCH_IF NOT VARIABLE_IS_SET $opcodes_ignore_duration(~%opcode%~) AND opcode != 177 AND opcode != 183 AND opcode != 283 AND ignoreDuration == 0 AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_duration_value~ INT_VAR duration RET duration = value END

		PATCH_IF NOT ~%duration%~ STRING_EQUAL ~~ BEGIN
			SPRINT description ~%description% %duration%~
			SET ignoreDuration = 1
		END
	END
END

DEFINE_PATCH_MACRO ~add_save~ BEGIN
	PATCH_IF saveAdded == 0 AND NOT ~%description%~ STRING_EQUAL ~~ AND saveType != 0 BEGIN
		SPRINT saveTypeStr ~~
        PATCH_IF (saveType BAND FLAG_SAVINGTHROW_spell) == FLAG_SAVINGTHROW_spell BEGIN
            SPRINT saveTypeStr @10370001 // ~contre les sorts~
        END
        PATCH_IF (saveType BAND FLAG_SAVINGTHROW_breath) == FLAG_SAVINGTHROW_breath BEGIN
            PATCH_IF NOT ~%saveTypeStr%~ STRING_EQUAL ~~ BEGIN
				SPRINT strOr @100004 // ~ou~
                SPRINT saveTypeStr ~%saveTypeStr% %strOr% ~
            END
            SPRINT saveTypeStr @10360001 // ~contre les souffles~
        END
        PATCH_IF (saveType BAND FLAG_SAVINGTHROW_death) == FLAG_SAVINGTHROW_death BEGIN
            PATCH_IF NOT ~%saveTypeStr%~ STRING_EQUAL ~~ BEGIN
				SPRINT strOr @100004 // ~ou~
                SPRINT saveTypeStr ~%saveTypeStr% %strOr% ~
            END
            SPRINT saveTypeStr @10330001 // ~contre la paralysie, la mort et les poisons~
        END
        PATCH_IF (saveType BAND FLAG_SAVINGTHROW_wand) == FLAG_SAVINGTHROW_wand BEGIN
            PATCH_IF NOT ~%saveTypeStr%~ STRING_EQUAL ~~ BEGIN
				SPRINT strOr @100004 // ~ou~
                SPRINT saveTypeStr ~%saveTypeStr% %strOr% ~
            END
            SPRINT saveTypeStr @10340001 // ~contre les baguettes, les sceptres et les bâtons~
        END
        PATCH_IF (saveType BAND FLAG_SAVINGTHROW_polymorph) == FLAG_SAVINGTHROW_polymorph BEGIN
            PATCH_IF NOT ~%saveTypeStr%~ STRING_EQUAL ~~ BEGIN
				SPRINT strOr @100004 // ~ou~
                SPRINT saveTypeStr ~%saveTypeStr% %strOr% ~
            END
            SPRINT saveTypeStr @10350001 // ~contre la pétrification et la métamorphose~
        END

        PATCH_IF saveBonus != 0 BEGIN
			LPF ~signed_value~ INT_VAR value = EVAL ~%saveBonus%~ RET saveBonus = value END
			PATCH_IF saveForHalf == 1 BEGIN
				SPRINT saveStr @101184 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour réduire de moitié~
			END
			ELSE BEGIN
				SPRINT saveStr @102122 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour éviter~
			END
        END
        ELSE BEGIN
			PATCH_IF saveForHalf == 1 BEGIN
				SPRINT saveStr @101183 // ~jet de sauvegarde %saveTypeStr% pour réduire de moitié~
			END
			ELSE BEGIN
				SPRINT saveStr @102121 // ~jet de sauvegarde %saveTypeStr% pour éviter~
			END
        END

		SPRINT description ~%description% (%saveStr%)~
		SET saveAdded = 1
	END
END

DEFINE_PATCH_MACRO ~add_target_level~ BEGIN
	LOCAL_SET levelMin = diceSides
	LOCAL_SET levelMax = diceCount
	LOCAL_SET strref   = 0
	PATCH_IF (diceCount > 0 OR diceSides > 0) AND (opcode != 12 AND opcode != 17 AND opcode != 18 AND opcode != 331 AND opcode != 333 AND (opcode != 218 OR is_ee == 0 OR parameter2 == 0)) BEGIN
		PATCH_IF diceSides == diceCount BEGIN
			SET strref = 101186 // ~%target% (de niveau %levelMin%)~
		END
		ELSE PATCH_IF diceSides == 0 AND diceCount > 0 BEGIN
			SET strref = 101187 // ~%target% (de niveau %levelMax% ou inférieur)~
		END
		ELSE PATCH_IF diceSides > 1 AND diceCount == 0 BEGIN
			SET strref = 101188 // ~%target% (de niveau %levelMin% ou supérieur)~
		END
		ELSE PATCH_IF diceSides > 1 AND diceCount > 0 BEGIN
			SET strref = 101189 // ~%target% (de niveau %levelMin% à %levelMax%)~
		END

		PATCH_IF strref != 0 BEGIN
		    PATCH_FOR_EACH vTarget IN ~theTarget~ ~ofTheTarget~ ~toTheTarget~ BEGIN
		        SPRINT target EVAL ~%%vTarget%%~
		        SPRINT EVAL ~%vTarget%~ (AT strref)
		    END
		END
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
		PATCH_IF diceSides == 1 BEGIN
			SET damageAmount += diceCount
		END
		ELSE BEGIN
			SPRINT ~damage~ @10014 // ~%diceCount%d%diceSides%~
		END
	END
	PATCH_IF damageAmount != 0 BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%damageAmount%~ RET damageAmount = value END
		PATCH_IF ~%damage%~ STRING_EQUAL ~~ BEGIN
			SPRINT ~damage~ ~%damageAmount%~
		END
		ELSE BEGIN
			SPRINT ~damage~ ~%damage% %damageAmount%~
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_duration_value~ INT_VAR duration = 0 RET value BEGIN
	SPRINT value ~~
	PATCH_IF timingMode == TIMING_permanent OR timingMode == TIMING_permanent_after_death BEGIN
		SET found = 0
		PATCH_FOR_EACH cOpcode IN 12 13 20 23 24 32 55 58 68 75 77 79 81 116 125 146 148 161 162 177 214 218 230 233 238 244 261 273 280 316 BEGIN
			PATCH_IF opcode == cOpcode BEGIN
				SET found = 1
			END
		END
		PATCH_IF found == 0 BEGIN
			PATCH_IF timingMode == TIMING_permanent BEGIN
				SPRINT value @100312 // ~de manière permanente~
			END
			ELSE BEGIN
				SPRINT value @100313 // ~de manière permanente et persiste après la mort~
			END
		END
	END
	ELSE PATCH_IF timingMode != TIMING_while_equipped AND duration > 0 BEGIN
        LPF ~get_str_duration~ INT_VAR duration RET strDuration END

		PATCH_IF timingMode == TIMING_duration BEGIN
			SPRINT value @100311 // ~pendant %duration%~
		END
		ELSE PATCH_IF timingMode == TIMING_delayed BEGIN
			SPRINT value @100310 // ~après %strDuration%~
		END
		ELSE BEGIN
			PATCH_PRINT "%SOURCE_FILE%: opcode %opcode% : timing %timingMode%"
		END
    END
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~durations~ BEGIN
	7200 => 100308 // jour
	 300 => 100306 // heure
	  60 => 100304 // tour
	   6 => 100302 // round
END

DEFINE_PATCH_FUNCTION ~get_str_duration~ INT_VAR duration = 0 RET strDuration BEGIN
	SET total = duration
	SPRINT strDuration ~~

	PATCH_PHP_EACH durations AS divisor => strref BEGIN
		SET amount = duration / divisor
		SET duration = duration MODULO divisor

		PATCH_IF duration == 0 AND ~%strDuration%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF amount > 1 BEGIN
				SET strref += 1
			END

            SPRINT strDuration (AT strref)
		END
	END

	PATCH_IF duration > 0 AND ~%strDuration%~ STRING_EQUAL ~~ BEGIN
		SET amount = total
		SET strref = 100300 // seconde

		PATCH_IF amount > 1 BEGIN
			SET strref += 1
		END

        SPRINT strDuration (AT strref)
	END
END
