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
	SET isValid = 1
	SET saveAdded = 0
	SET sort = 0
	SET forceSort = 0

	LPM ~block_to_vars~
	LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END

	SPRINT condition ~~
	SPRINT method ~~
	SPRINT description ~~
	SPRINT opcode_target ~~

	PATCH_IF forceProbability == 1 BEGIN
		SET probability = forcedProbability
	END

	// ITM global (equipped) effects: Target is always the wearer, this field isn’t relevant.
	PATCH_IF target == TARGET_FX_none AND ~%SOURCE_EXT%~ STRING_EQUAL_CASE ~ITM~ BEGIN
		SET target = TARGET_FX_self
	END

	LPM ~opcode_is_valid~

	PATCH_IF isValid == 1 BEGIN
		PATCH_TRY
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
				PATCH_IF probability >= 100 BEGIN
					SPRINT method ~opcode%opcode_target%_%opcode_n%~
					LPM ~%method%~
					LPM ~set_opcode_sort~
				END
				ELSE BEGIN
					SPRINT method ~opcode%opcode_target%_probability_%opcode_n%~
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
END

DEFINE_PATCH_MACRO ~opcode_is_valid~ BEGIN
	// Si la macro n'existe pas, on considère comme valide
	PATCH_TRY LPM ~opcode_%opcode%_is_valid~ WITH DEFAULT SET isValid = 1 END

	PATCH_IF probability <= 0 BEGIN
		SET isValid = 0
        LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Probability error : <= 0~ END
    END

	PATCH_IF target > 9 BEGIN
		SET isValid = 0
		LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid target : %target%~ END
	END

	// OR abilityType == AbilityType_Equipped ?
	// TODO: Cas particulier de l'opcode 177...
	PATCH_IF target == TARGET_FX_none BEGIN // On ignore les effets dont la cible est none (Ex: BARBEAXE.ITM qui ne passe pas la force du porteur à 20)
		SET isValid = 0
		LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Target est none~ END
	END

	PATCH_IF VARIABLE_IS_SET $opcodes_parameters_should_be_zero(~%opcode%~) AND (parameter1 != 0 OR parameter2 != 0) BEGIN
		SET isValid = 0
		LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Les 2 parametres doivent avoir la valeur 0~ END
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
	PATCH_IF resetTarget == 1 BEGIN
		// resetTarget == 0 dans le cas où on demande la description depuis l'opcode 177
		// TODO: Améliorer la gestion de ce comportement d'une façon moins tirée par les cheveux
		READ_BYTE  EFF2_target target
	END
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

	SET isValid = 1
	SET parentProbability = probability
	SPRINT condition ~~
	SPRINT description ~~

	LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END
	LPM ~opcode_is_valid~

	PATCH_IF isValid == 1 BEGIN
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
		ELSE PATCH_IF $ignored_opcodes(~%opcode%~) == 1 BEGIN
			LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode% à gérer.~ END
		END

		LPM ~add_condition~
		LPM ~add_duration~
		LPM ~add_save~
	END
END

DEFINE_PATCH_MACRO ~add_condition~ BEGIN
	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND NOT ~%condition%~ STRING_EQUAL ~~ BEGIN
		SPRINT description ~%condition%%semicolon%%description%~
	END
END

DEFINE_PATCH_MACRO ~add_duration~ BEGIN
	// durée ou pas, un effet peut avoir un délai avant fonctionnement
	PATCH_IF (timingMode == TIMING_delayed OR NOT VARIABLE_IS_SET $opcodes_ignore_duration(~%opcode%~)) AND opcode != 177 AND opcode != 183 AND opcode != 283 AND ignoreDuration == 0 AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
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

		// FIXME
		SET saveForHalf = 0
		SET failForHalf = 0
		PATCH_IF opcode == 12 AND mode == 0 BEGIN
			SET saveForHalf = (special BAND BIT8)
			SET failForHalf = (special BAND BIT9)
		END
		//

        PATCH_IF saveBonus != 0 BEGIN
			LPF ~signed_value~ INT_VAR value = EVAL ~%saveBonus%~ RET saveBonus = value END
			PATCH_IF saveForHalf OR failForHalf BEGIN
				PATCH_IF saveForHalf AND NOT failForHalf BEGIN
					SPRINT saveStr @101184 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour réduire de moitié~
				END
				ELSE PATCH_IF NOT failForHalf AND failForHalf BEGIN
					// FIXME
					LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode% failForHalf non gere.~ END
					SPRINT saveStr @102122 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour éviter~
				ELSE BEGIN
					SPRINT saveStr @102122 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour éviter~
				END
			ELSE BEGIN
				SPRINT saveStr @102122 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour éviter~
			END
        END
        ELSE BEGIN
			PATCH_IF saveForHalf BEGIN
				SPRINT saveStr @101183 // ~jet de sauvegarde %saveTypeStr% pour réduire de moitié~
			END
			ELSE PATCH_IF failForHalf BEGIN
				// FIXME
				LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode% failForHalf non gere.~ END
				SPRINT saveStr @102121 // ~jet de sauvegarde %saveTypeStr% pour éviter~
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
	PATCH_IF (levelMax > 0 OR levelMin > 0) AND (opcode != 12 AND opcode != 17 AND opcode != 18 AND opcode != 331 AND opcode != 333 AND (opcode != 218 OR is_ee == 0 OR parameter2 == 0) AND (opcode != 127 OR is_ee == 0)) BEGIN
		PATCH_IF levelMin == diceCount BEGIN
			SET strref = 101186 // ~%target% (de niveau %levelMin%)~
		END
		ELSE PATCH_IF levelMin == 0 AND levelMax > 0 BEGIN
			SET strref = 101187 // ~%target% (de niveau %levelMax% ou inférieur)~
		END
		ELSE PATCH_IF levelMin > 0 AND levelMax == 0 BEGIN
			SET strref = 101188 // ~%target% (de niveau %levelMin% ou supérieur)~
		END
		ELSE BEGIN
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


DEFINE_PATCH_FUNCTION ~get_probability~ INT_VAR probability1 = 0 probability2 = 0 RET probability BEGIN
	PATCH_IF probability1 > 99 OR probability1 < 0 BEGIN
	    probability1 = 99
	END

	SET probability = probability1 - probability2 + 1

	PATCH_IF probability2 > probability1 OR probability2 < 0 BEGIN
        SET probability = 0
    END
END


DEFINE_PATCH_FUNCTION ~get_damage_value~ INT_VAR diceCount = 0 diceSides = 0 damageAmount = 0 RET damage BEGIN
	SPRINT ~damage~ ~~

	PATCH_IF diceCount > 0 BEGIN
		PATCH_IF diceSides <= 1 BEGIN
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
	// FIXME, il peut avoir certaines subtilités entre un vrai timing 1 et un timing X
	// Il faudrait considérer un nouveau timing dont l'effet à mi-chemin entre le 1 et le 9
	PATCH_IF timingMode > TIMING_duration_ticks AND timingMode != TIMING_absolute_duration BEGIN
		SET timingMode = TIMING_permanent
	END
	ELSE PATCH_IF timingMode == 6 BEGIN
		SET timingMode = TIMING_duration
		SET duration = duration * 16 / 15
	END
	ELSE PATCH_IF timingMode == 7 BEGIN
		SET timingMode = TIMING_delayed
		SET duration = duration / 15
	END
	// TODO ~ TIMING_while_equipped + delay
	ELSE PATCH_IF timingMode == 8 BEGIN
		SET timingMode = 5
		SET duration = duration / 15
	END

	PATCH_IF timingMode == TIMING_permanent OR timingMode == TIMING_permanent_after_death BEGIN
		PATCH_IF NOT VARIABLE_IS_SET $opcodes_cant_be_permanent(~%opcode%~) BEGIN
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
			SPRINT value @100311 // ~pendant %strDuration%~
		END
		ELSE PATCH_IF timingMode == TIMING_delayed BEGIN
			SPRINT value @100310 // ~après %strDuration%~
		END
		ELSE PATCH_IF timingMode == TIMING_delayed_duration BEGIN
			// TODO, meilleure tournure
			SPRINT value @100314 // ~après %strDuration% et pendant %strDuration%~
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
	   1 => 100300 // seconde
END

DEFINE_PATCH_FUNCTION ~get_str_duration~ INT_VAR duration = 0 RET strDuration BEGIN
	SPRINT strDuration ~~

	PATCH_PHP_EACH durations AS divisor => strref BEGIN
		PATCH_IF duration MODULO divisor == 0 AND ~%strDuration%~ STRING_EQUAL ~~ BEGIN
			SET amount = duration / divisor
			PATCH_IF amount > 1 BEGIN
				SET strref += 1
			END

            SPRINT strDuration (AT strref)
		END
	END
END
