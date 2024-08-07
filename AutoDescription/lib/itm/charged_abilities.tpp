DEFINE_PATCH_FUNCTION ~add_charged_abilities~
	STR_VAR
		description = ~~
	RET
		description
BEGIN
	SET abilityType  = AbilityType_Charge
	SET countHeaders = 0
	SET headerIndex = 0
	SET countLines = 0
	SET isGlobalDuration = 0

	GET_OFFSET_ARRAY headerOffsets ITM_V10_HEADERS
	PHP_EACH headerOffsets AS _ => headerOffset BEGIN
		READ_BYTE  (headerOffset + ITM_HEAD_attack_type) attackType
		READ_BYTE  (headerOffset + ITM_HEAD_location) location
		READ_SHORT (headerOffset + ITM_HEAD_target) headTarget
		READ_BYTE  (headerOffset + ITM_HEAD_target_count) headTargetNumber
		READ_SHORT (headerOffset + ITM_HEAD_charges) charges
		READ_SHORT (headerOffset + ITM_HEAD_depletion) depletion

		SET projectile = 0

		PATCH_IF headTarget == TARGET_HEAD_area BEGIN
			READ_SHORT (headerOffset + ITM_HEAD_projectile_animation) projectile
		END

		PATCH_IF charges > 0 OR location == 3 BEGIN
			LPF ~load_charged_abilities~ INT_VAR headerOffset index = headerIndex RET EVAL ~countLines%countHeaders%~ = countLines isGlobalDuration globalDuration globalTimingMode RET_ARRAY EVAL ~lines%countHeaders%~ = lines END
			SET $EVAL ~headers%countHeaders%~(~%attackType%~ ~%location%~ ~%headerIndex%~ ~%depletion%~ ~%charges%~) = 1

			SET countHeaders += 1
		END
		SET headerIndex += 1
	END

	PATCH_IF countHeaders > 0 BEGIN
		FOR (index = 0; index < countHeaders; index += 1) BEGIN
			PATCH_PHP_EACH ~headers%index%~ AS data => _ BEGIN
				SPRINT headerIndex ~%data_2%~
				SPRINT title ~~
				SET depletion = ~%data_3%~
				SET charges = ~%data_4%~
				SET hasTitle = 0

				SET sort = ( index + 1 ) * 1000000

				PATCH_IF itemType == ITM_TYPE_potion BEGIN
	                PATCH_PHP_EACH ~lines%index%~ AS data => _ BEGIN
	                    SET lineSort = sort + ~%data_0%~
						SET $lines(~%lineSort%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~) = 1
						SET countLines += 1
					END
				END
				ELSE PATCH_IF isAmmo AND countHeaders == 1 BEGIN
	                PATCH_PHP_EACH ~lines%index%~ AS data => _ BEGIN
	                    SET lineSort = sort + ~%data_0%~
						SET $lines(~%lineSort%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~) = 1
						SET countLines += 1
					END
				END
				ELSE BEGIN
					LPF ~get_tooltip~ INT_VAR index = headerIndex STR_VAR resource = ~%SOURCE_RES%~ RET tooltip END
					SPRINT tooltipTitle ~~
					// Ajout du nom de la capacité
	                PATCH_IF NOT ~%tooltip%~ STRING_EQUAL ~~ BEGIN
	                    SPRINT title ~%tooltip%~
	                    PATCH_IF EVAL ~countLines%index%~ == 0 BEGIN
							PATCH_IF countHeaders != 1 BEGIN
		                        LPF ~get_charged_ability_title~ INT_VAR charges depletion STR_VAR title RET title END
		                    END
							SET $lines(~%sort%~ ~%countLines%~ ~100~ ~0~ ~99~ ~%title%~) = 1
							SET countLines += 1
						END
						SET hasTitle = 2
	                END

					PATCH_IF EVAL ~countLines%index%~ > 1 BEGIN
						// On ajoute le titre générique que si on n'a pas trouvé le titre par tooltip
						PATCH_IF ~%title%~ STRING_EQUAL ~~ AND countHeaders > 1 BEGIN
							SET abilityNumber = index + 1
							SPRINT title @101124 // ~Capacité %abilityNumber%~

		                    LPF ~get_charged_ability_title~ INT_VAR charges depletion STR_VAR title RET title END
							SET $lines(~%sort%~ ~%countLines%~ ~100~ ~0~ ~99~ ~%title%~) = 1
							SET countLines += 1
							SET hasTitle = 2
						END
						ELSE PATCH_IF ~%title%~ STRING_EQUAL ~~ AND countHeaders == 1 BEGIN
							SET hasTitle = 1
						END
					END

	                PATCH_PHP_EACH ~lines%index%~ AS data => _ BEGIN
	                    SET lineSort = sort + ~%data_0%~
	                    PATCH_IF hasTitle == 0 BEGIN
							PATCH_IF countHeaders != 1 BEGIN
		                        LPF ~get_charged_ability_title~ INT_VAR charges depletion STR_VAR title = ~%data_5%~ RET data_5 = title END
							END
							SET hasTitle = 1
		                    SET $lines(~%lineSort%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~) = hasTitle
	                    END
	                    ELSE PATCH_IF hasTitle == 2 BEGIN
	                        PATCH_IF "%data_5%" STRING_MATCHES_REGEXP "%title%" BEGIN
								PATCH_IF countHeaders != 1 BEGIN
	                                LPF ~get_charged_ability_title~ INT_VAR charges depletion STR_VAR title RET title END
								END
								SET $lines(~%sort%~ ~%countLines%~ ~100~ ~0~ ~99~ ~%title%~) = 1
		                        SET $lines(~%lineSort%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~) = hasTitle
								SPRINT title ~~
	                        END
	                        ELSE BEGIN
								PATCH_IF countHeaders != 1 AND EVAL ~countLines%index%~ == 1 BEGIN
			                        LPF ~get_charged_ability_title~ INT_VAR charges depletion STR_VAR title = ~%data_5%~ RET data_5 = title END
			                        SET $lines(~%lineSort%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~) = 1
								END
								ELSE BEGIN
			                        SET $lines(~%lineSort%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~) = EVAL ~countLines%index%~ == 1 ? 1 : 2
			                    END
	                        END
	                    END
	                    ELSE BEGIN
		                    SET $lines(~%lineSort%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~) = hasTitle
						END
						SET countLines += 1
	                END
	            END
			END
		END

		PATCH_IF itemType == ITM_TYPE_potion BEGIN
			LPF ~add_items_section_to_description~ STR_VAR arrayName = ~lines~ RET description END
            INNER_PATCH_SAVE description ~%description%~ BEGIN
                REPLACE_TEXTUALLY EVALUATE_REGEXP ~- %crlf%~ ~~
            END
            PATCH_IF countHeaders == 1 AND isGlobalDuration AND globalDuration > 0 AND (globalTimingMode == TIMING_duration OR globalTimingMode == TIMING_duration_ticks) BEGIN
                PATCH_IF globalTimingMode == TIMING_duration_ticks BEGIN
                    SET globalDuration = globalDuration / 15
                END
                LPF ~get_str_duration~ INT_VAR duration = globalDuration RET value = strDuration END
                PATCH_IF NOT ~%duration%~ STRING_EQUAL ~~ BEGIN
					LPF ~appendLine~ RET description END
					LPF ~appendValue~ INT_VAR strref = 100031 STR_VAR value RET description END // Durée
                END
            END
		END
		ELSE PATCH_IF isAmmo AND countHeaders == 1 BEGIN
			SPRINT title @100011 // ~Capacités de combat~
			LPF ~add_section_to_description~ INT_VAR count = countLines STR_VAR title arrayName = ~lines~ RET description END
		END
		ELSE PATCH_IF (itemType != ITM_TYPE_dart OR (itemType == ITM_TYPE_dart AND countHeaders > 1)) BEGIN
			SPRINT title @100012  // ~Capacités de charge~
			PATCH_IF itemType != ITM_TYPE_dart AND countHeaders <= 1 BEGIN
				SPRINT title @100015  // ~Capacité de charge~
				LPF ~get_charged_ability_title~ INT_VAR charges depletion STR_VAR title RET title END
			END
			LPF ~add_section_to_description~ INT_VAR count = countLines STR_VAR title arrayName = ~lines~ RET description END
		END
	END
END


DEFINE_PATCH_FUNCTION ~load_charged_abilities~
	INT_VAR
		index = 0
		headerOffset = 0
	RET
		countLines
		isGlobalDuration
		globalDuration
		globalTimingMode
	RET_ARRAY
		lines
BEGIN
	SET countLines = 0
	SET isGlobalDuration = 0
	SET globalDuration = ~-1~
	SET globalTimingMode = 0
	SET ignoreDuration = 0

	CLEAR_ARRAY lines
	LPM ~clear_opcodes~

    PATCH_DEFINE_ASSOCIATIVE_ARRAY lines BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY opcodes BEGIN END

	LPM ~load_extended_effects~
	LPM ~replace_effects~
	LPM ~filter_effects~
	LPM ~group_effects~

	PATCH_IF itemType == ITM_TYPE_potion BEGIN
		SET isGlobalDuration = 1
		PATCH_PHP_EACH opcodes AS opcode => count BEGIN
			//FIXME: Si opcode 146 (et autres opcode lançant un sortilège), vérifier les opcodes à l'intérieur du sort... (voir "spell_duration")
			PATCH_IF count > 0 AND opcode != 146 AND NOT VARIABLE_IS_SET $opcodes_ignore_duration(~%opcode%~) BEGIN
			    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
			        PATCH_IF isGlobalDuration BEGIN
				        LPM ~data_to_vars~
				        PATCH_IF timingMode == TIMING_duration OR timingMode == TIMING_duration_ticks BEGIN
					        PATCH_IF globalDuration < 0 BEGIN
					            SET globalDuration = duration
					            SET globalTimingMode = timingMode
					        END
					        PATCH_IF globalDuration != duration BEGIN
					            SET isGlobalDuration = 0
					        END
				        END
			        END
			    END
			END
	    END
	END
	PATCH_IF isGlobalDuration AND globalDuration > 0 BEGIN
		SET ignoreDuration = 1
	END

	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~

		        PATCH_IF itemType == ITM_TYPE_potion AND headTarget == TARGET_HEAD_self BEGIN
		            SET target = TARGET_FX_self
		        END

				LPF ~get_effect_description~ INT_VAR ignoreDuration projectile projectileTarget = headTarget projectileTargetNumber = headTargetNumber RET effectDescription = description sort END
				PATCH_IF NOT ~%effectDescription%~ STRING_EQUAL ~~ BEGIN
					SET $lines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 1
					SET countLines += 1
				END
		    END
	    END
	END

	LPF ~get_unique_effects~ RET countLines = count RET_ARRAY lines = effects END
END

DEFINE_PATCH_FUNCTION ~get_charged_string~
	INT_VAR
		charges = 0
		depletion = 0
	RET
		chargeStr
BEGIN
    PATCH_IF depletion == 1 BEGIN
        PATCH_IF charges == 1 BEGIN
			SPRINT chargeStr @102677 // ~usage unique~
        END
        ELSE PATCH_IF charges == 0 BEGIN
			SPRINT chargeStr @102678 // ~usage illimité~
        END
        ELSE BEGIN
			SPRINT chargeStr @102159 // ~%charges% charges, l'objet est détruit quand toutes les charges sont utilisées~
        END
    END
    ELSE BEGIN
		SPRINT chargeStr @102094 // ~%charges% fois par jour~
    END
END

DEFINE_PATCH_FUNCTION ~get_charged_ability_title~
	INT_VAR
		charges = 0
		depletion = 0
	STR_VAR
		title = ~~
	RET
		title
BEGIN
	LPF ~get_charged_string~ INT_VAR charges depletion RET chargeStr END

	SPRINT title ~%title% (%chargeStr%)~
END
