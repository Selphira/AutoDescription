DEFINE_PATCH_MACRO ~opcode_is_valid~ BEGIN
	PATCH_IF NOT is_ee AND opcode >= 319 AND opcode <= 367 BEGIN
		SET isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Opcode doesn't exist in this game~ END
	END
	ELSE BEGIN
		// Si la macro n'existe pas, on considère comme valide
		PATCH_TRY LPM ~opcode_%opcode%_is_valid~ WITH DEFAULT SET isValid = 1 END
		PATCH_TRY LPM ~opcode_%opcode%_is_valid_mod~ WITH DEFAULT END
	END
	
	PATCH_IF probability <= 0 BEGIN
		SET isValid = 0
        LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Probability error : <= 0~ END
    END

	PATCH_IF target > 9 OR target < 0 BEGIN
		SET isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid target : %target%~ END
	END

	// OR abilityType == AbilityType_Equipped ?
	// TODO: Cas particulier de l'opcode 177...
	PATCH_IF target == TARGET_FX_none BEGIN // On ignore les effets dont la cible est none (Ex: BARBEAXE.ITM qui ne passe pas la force du porteur à 20)
		SET isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Target is None~ END
	END

	PATCH_IF timingMode == TIMING_duration AND duration <= 0 AND NOT VARIABLE_IS_SET $opcodes_ignore_duration(~%opcode%~) BEGIN
		SET isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Timing mode == Instant/Limited and duration == 0~ END
	END

	PATCH_IF is_ee == 0 AND VARIABLE_IS_SET $opcodes_parameters_should_be_zero(~%opcode%~) AND (parameter1 != 0 OR parameter2 != 0) BEGIN
		SET isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Les 2 parametres doivent avoir la valeur 0~ END
	END
END

DEFINE_PATCH_MACRO ~set_opcode_sort~ BEGIN
	PATCH_IF forceSort == 0 BEGIN
		PATCH_IF VARIABLE_IS_SET $sort_opcodes(~%opcode%~) BEGIN
			SET sort = $sort_opcodes(~%opcode%~) + ((100 - probability) * 10000)
		END
		ELSE BEGIN
			SET sort = 400 + ((100 - probability) * 10000)
		END
	END
END

DEFINE_PATCH_MACRO ~add_condition~ BEGIN
	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND NOT ~%condition%~ STRING_EQUAL ~~ BEGIN
		SPRINT description ~%condition%%semicolon%%description%~
	END
END

DEFINE_PATCH_MACRO ~add_duration~ BEGIN
	// durée ou pas, un effet peut avoir un délai avant fonctionnement
	PATCH_IF (timingMode == TIMING_delayed OR timingMode == 5000 OR timingMode == 5001 OR NOT VARIABLE_IS_SET $opcodes_ignore_duration(~%opcode%~)) AND
			 opcode != 177 AND opcode != 183 AND opcode != 283 AND (ignoreDuration == 0 OR timingMode == TIMING_delayed OR timingMode == 5000 OR timingMode == 5001) AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF NOT ~%complex_duration%~ STRING_EQUAL ~~ BEGIN
			SPRINT description ~%description% %complex_duration%~
		END
		ELSE BEGIN
			LPF ~get_duration_value~ INT_VAR duration RET duration = value END

			PATCH_IF NOT ~%duration%~ STRING_EQUAL ~~ BEGIN
				SPRINT description ~%description% %duration%~
				SET ignoreDuration = 1
			END
		END
	END
END

DEFINE_PATCH_MACRO ~add_only_for~ BEGIN
	PATCH_IF ~%opcode_target%~ STRING_EQUAL ~_self~ AND VARIABLE_IS_SET onlyForTarget AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		// On ajoute le (uniquement pour les xxx) derrière chaque sous-effets
        INNER_PATCH_SAVE description ~%description%~ BEGIN
            REPLACE_TEXTUALLY EVALUATE_REGEXP ~\(.+\)%crlf%~ ~\1 (%onlyForTarget%)%crlf%~
        END
		SPRINT description ~%description% (%onlyForTarget%)~
	END
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~saveType_to_strref~ BEGIN
	~%FLAG_SAVINGTHROW_spell%~ 		=> 10370001 // ~contre les sorts~
	~%FLAG_SAVINGTHROW_breath%~ 	=> 10360001 // ~contre les souffles~
	~%FLAG_SAVINGTHROW_death%~ 		=> 10330001 // ~contre la paralysie, la mort et les poisons~
	~%FLAG_SAVINGTHROW_wand%~ 		=> 10340001 // ~contre les baguettes, les sceptres et les bâtons~
	~%FLAG_SAVINGTHROW_polymorph%~  => 10350001 // ~contre la pétrification et la métamorphose~
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~short_saveType_to_strref~ BEGIN
	~%FLAG_SAVINGTHROW_spell%~ 		=> 103001 // ~Sorts~
	~%FLAG_SAVINGTHROW_breath%~ 	=> 103002 // ~Souffles~
	~%FLAG_SAVINGTHROW_death%~ 		=> 103004 // ~Paralysie, mort et poisons~
	~%FLAG_SAVINGTHROW_wand%~ 		=> 103008 // ~Baguettes, sceptres et bâtons~
	~%FLAG_SAVINGTHROW_polymorph%~  => 103016 // ~Pétrification et métamorphose~
END

DEFINE_PATCH_MACRO ~add_save~ BEGIN
	PATCH_IF ignoreSavingThrow == 0 BEGIN
		SET saveFlags = saveType
		SET saveType  = (saveType BAND 0b11111)
		// FIXME
		SET saveForHalf = 0
		SET failForHalf = 0
		PATCH_IF is_ee AND opcode == 12 AND (parameter2 BAND 65535) == 0 BEGIN
			SET saveForHalf = (special BAND BIT8) > 0
			SET failForHalf = (special BAND BIT9) > 0
		END
		//

		// les dégâts sont réduits de moitié même si aucun JS n'est permis
		// PATCH_IF saveForHalf AND failForHalf BEGIN
		// 	SPRINT saveStr @102125 // ~réduits de moitié~
		// END

		// dégâts réduits de moitié si :
		// pas de JS autorisés et failForHalf actif
		// JS autorisés mais failForHalf et saveForHalf actifs
		PATCH_IF failForHalf AND NOT ~%description%~ STRING_EQUAL ~~ AND (saveType == 0 OR saveForHalf) BEGIN
			SPRINT saveStr @102125 // ~réduits de moitié~
			SPRINT description ~%description% (%saveStr%)~
		END
		ELSE PATCH_IF saveAdded == 0 AND NOT ~%description%~ STRING_EQUAL ~~ AND saveType != 0 BEGIN
			// FIXME les js ne sont pas cumulés dans la description finale
			SPRINT saveTypeStr ~~

			PHP_EACH saveType_to_strref AS saveBit => strref BEGIN
				PATCH_IF (saveType BAND saveBit) BEGIN
					SPRINT strOr ~~
					SPRINT strref (AT strref)
					PATCH_IF NOT ~%saveTypeStr%~ STRING_EQUAL ~~ BEGIN
						SPRINT strOr @100004 // ~ou~
						// FIXME le faire en une fois ?
						SPRINT strOr ~ %strOr% ~
					END
					SPRINT saveTypeStr ~%saveTypeStr%%strOr%%strref%~
				END
			END

			PATCH_IF saveBonus != 0 OR NOT ~%complex_save%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF NOT ~%complex_save%~ STRING_EQUAL ~~ BEGIN
					SPRINT saveBonus ~%complex_save%~
					PATCH_IF complex_value_int < 0 BEGIN
						SPRINT saveBonus ~-%saveBonus%~
					END
				END
				ELSE BEGIN
					LPF ~signed_value~ INT_VAR value = EVAL ~%saveBonus%~ RET saveBonus = value END
				END
				PATCH_IF saveForHalf BEGIN
					SPRINT saveStr @101184 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour réduire de moitié~
				END
				ELSE PATCH_IF failForHalf BEGIN
					SPRINT saveStr @102124 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour éviter et pour moitié en cas d'échec~
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
					SPRINT saveStr @102123 // ~jet de sauvegarde %saveTypeStr% pour éviter et pour moitié en cas d'échec~
				END
				ELSE BEGIN
					SPRINT saveStr @102121 // ~jet de sauvegarde %saveTypeStr% pour éviter~
				END
	        END

            PATCH_IF is_ee BEGIN
                PATCH_IF saveFlags BAND FLAG_SAVINGTHROW_ignore_primary_target_EE BEGIN
                    SPRINT saveStrExtra @102170 // ~ignore la cible principale~
                    SPRINT saveStr ~%saveStr%, %saveStrExtra%~
                END
                PATCH_IF saveFlags BAND FLAG_SAVINGTHROW_ignore_secondary_target_EE BEGIN
                    SPRINT saveStrExtra @102171 // ~ignore la cible secondaire~
                    SPRINT saveStr ~%saveStr%, %saveStrExtra%~
                END
                PATCH_IF (opcode == 12 OR opcode == 25) AND saveFlags BAND FLAG_SAVINGTHROW_bypass_mirror_image_EE BEGIN
                    SPRINT saveStrExtra @102172 // ~ignore les images miroir~
                    SPRINT saveStr ~%saveStr%, %saveStrExtra%~
                END
                PATCH_IF opcode == 12 AND saveFlags BAND FLAG_SAVINGTHROW_ignore_difficulty_EE BEGIN
                    SPRINT saveStrExtra @102173 // ~ignore la difficulté~
                    SPRINT saveStr ~%saveStr%, %saveStrExtra%~
                END
            END

			SPRINT description ~%description% (%saveStr%)~
			SET saveAdded = 1
		END
	END
END

DEFINE_PATCH_MACRO ~add_target_level~ BEGIN
	LOCAL_SET levelMin = diceSides
	LOCAL_SET levelMax = diceCount
	LOCAL_SET strref   = 0

	//TODO: Limiter aux effets qui ont été appelés par =>  AND (opcode == 177 OR opcode == 183 OR opcode == 248 OR opcode == 249 OR opcode == 282 OR opcode == 283)
	PATCH_IF isExternal == 1 AND VARIABLE_IS_SET minLevel BEGIN
		SET levelMin = minLevel
		SET levelMax = maxLevel
	END
	
	PATCH_IF (levelMax > 0 OR levelMin > 1) AND (NOT VARIABLE_IS_SET $opcode_without_level_restriction(~%opcode%~) AND (opcode != 218 OR is_ee == 0 OR parameter2 == 0) AND (opcode != 127 OR is_ee == 0)) BEGIN
		PATCH_IF levelMin == levelMax BEGIN
			SET strref = 101186 // ~%target% (de niveau %levelMin%)~
		END
		ELSE PATCH_IF levelMin <= 1 AND levelMax > 0 BEGIN
			SET strref = 101187 // ~%target% (de niveau %levelMax% ou inférieur)~
		END
		ELSE PATCH_IF levelMin > 1 AND levelMax == 0 BEGIN
			SET strref = 101188 // ~%target% (de niveau %levelMin% ou supérieur)~
		END
		ELSE PATCH_IF levelMax > levelMin BEGIN
			SET strref = 101189 // ~%target% (de niveau %levelMin% à %levelMax%)~
		END
		ELSE BEGIN
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: has no effect : levelMin (%levelMin%) > levelMax (%levelMax%) ~ END
		END

		PATCH_IF strref != 0 BEGIN
			SET oldTarget = target
		    PATCH_FOR_EACH vTarget IN ~theTarget~ ~ofTheTarget~ ~toTheTarget~ BEGIN
		        SPRINT target EVAL ~%%vTarget%%~
		        SPRINT EVAL ~%vTarget%~ (AT strref)
		    END
		    SET target = oldTarget
		END
	END
END

DEFINE_PATCH_MACRO ~add_cumulable~ BEGIN
	PATCH_IF cumulable == 0 AND NOT ~%description%~ STRING_EQUAL ~~ AND NOT VARIABLE_IS_SET $opcodes_ignore_not_cumulable(~%opcode%~) BEGIN
		SPRINT stringNotCumulable @102682 // ~non cumulatif~
		SPRINT description ~%description% (%stringNotCumulable%)~
	END
END

DEFINE_PATCH_MACRO ~add_target_exceptions~ BEGIN
	PATCH_IF NOT ~%target_exceptions%~ STRING_EQUAL ~~ AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		LPF ~opcode_324_target_exceptions~ STR_VAR list = ~%target_exceptions%~ RET target_exceptions END
		PATCH_IF NOT ~%target_exceptions%~ STRING_EQUAL ~~ BEGIN
			SPRINT description ~%description% (%target_exceptions%)~
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


DEFINE_PATCH_FUNCTION ~get_probability~ INT_VAR probability1 = 0 probability2 = 0 RET probability BEGIN
	PATCH_IF probability1 > 99 OR probability1 < 0 BEGIN
	    SET probability1 = 99
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


DEFINE_PATCH_FUNCTION ~get_duration_value~ INT_VAR duration = 0 RET value strDuration BEGIN
	SPRINT value ~~
	SPRINT strDuration ~~
	// FIXME, il peut avoir certaines subtilités entre un vrai timing 1 et un timing X
	// Il faudrait considérer un nouveau timing dont l'effet à mi-chemin entre le 1 et le 9
	PATCH_IF timingMode > TIMING_duration_ticks AND timingMode != TIMING_absolute_duration AND timingMode != 5000 AND timingMode != 5001 BEGIN
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

	PATCH_IF duration <= 0 BEGIN
		PATCH_IF timingMode == TIMING_delayed BEGIN
			SET timingMode = TIMING_permanent
			SET duration = 0
		END
		ELSE PATCH_IF timingMode == 5 BEGIN
			SET timingMode = TIMING_while_equipped
			SET duration = 0
		END
	END

	PATCH_IF timingMode == TIMING_permanent OR timingMode == TIMING_permanent_after_death BEGIN
		PATCH_IF NOT VARIABLE_IS_SET $opcodes_cant_be_permanent(~%opcode%~) BEGIN
			PATCH_IF timingMode == TIMING_permanent OR
					 VARIABLE_IS_SET $opcodes_cant_be_permanent_after_death(~%opcode%~) BEGIN
				SPRINT value @100312 // ~de manière permanente~
			END
			ELSE BEGIN
				SPRINT value @100313 // ~de manière permanente et persiste après la mort~
			END
		END
	END
	ELSE PATCH_IF timingMode != TIMING_while_equipped AND duration > 0 BEGIN
        LPF ~get_str_duration~ INT_VAR duration RET strDuration END

		PATCH_IF timingMode == TIMING_duration OR timingMode == TIMING_duration_ticks BEGIN
			// 1 tick = 1/15 de seconde
			PATCH_IF timingMode == TIMING_duration_ticks BEGIN
				PATCH_IF duration >= 15 BEGIN
					SET duration = duration / 15
                    LPF ~get_str_duration~ INT_VAR duration RET strDuration END
				END
				ELSE BEGIN
					SPRINT strDuration ~%duration% ticks~
				END
			END
			SPRINT value @100311 // ~pendant %strDuration%~
		END
		ELSE PATCH_IF timingMode == TIMING_delayed BEGIN
			SPRINT value @100310 // ~après %strDuration%~
		END
		ELSE PATCH_IF timingMode == TIMING_delayed_duration BEGIN
			// TODO, meilleure tournure
			SPRINT value @100314 // ~après %strDuration% et pendant %strDuration%~
		END
		ELSE PATCH_IF timingMode == 5000 OR timingMode == 5001 BEGIN
			SET tmpDuration = duration
			SET duration = duration MODULO 10000
			SET frequency = (tmpDuration - duration) / 10000

            PATCH_IF timingMode == 5000 BEGIN
				SET strref = 100316 // ~%frequency% pendant %strDuration% mais après %afterStrDuration%~
			END
			ELSE BEGIN
				// On ajoute la fréquence à la durée, car l'effet si le dernier effet est activé après le 2ème round,
				// cela veut dire qu'il faut 3 rounds pour que l'ensemble des effets agissent.
				// L'effet direct (round 1), le second (après 1 round), et le 3ème (après 2 rounds)
				SET duration += frequency
				SET strref = 100315 // ~%frequency% pendant %strDuration%~
			END

            LPF ~get_str_duration~ INT_VAR duration offset = 1 RET strDuration END
            LPF ~get_str_duration~ INT_VAR duration = frequency RET afterStrDuration = strDuration END
            LPF ~get_frequency_duration~ INT_VAR duration = frequency strref = 100323 RET frequency END

			SPRINT value (AT %strref%)
		END
		ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = ~opcode %opcode% : timing %timingMode%~ END
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

	PATCH_IF duration > 0 BEGIN
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
END
