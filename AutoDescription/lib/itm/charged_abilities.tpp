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
			SET $abilityHeaderIndex(~%countHeaders%~) = headerIndex
			SET $abilityDepletion(~%countHeaders%~) = depletion
			SET $abilityCharges(~%countHeaders%~) = charges

			SET countHeaders += 1
		END
		SET headerIndex += 1
	END

	PATCH_IF countHeaders > 0 BEGIN
		SET isMultiple = countHeaders > 1

		FOR (index = 0; index < countHeaders; index += 1) BEGIN
			SET headerIndex = $abilityHeaderIndex(~%index%~)
			SET depletion = $abilityDepletion(~%index%~)
			SET charges = $abilityCharges(~%index%~)
			SET sort = (index + 1) * 1000000
			SET lineCount = EVAL ~countLines%index%~

			PATCH_IF itemType == ITM_TYPE_potion OR (isAmmo AND countHeaders == 1) BEGIN
				PATCH_PHP_EACH ~lines%index%~ AS data => _ BEGIN
					SET lineSort = sort + ~%data_0%~
					SET $lines(~%lineSort%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~) = 1
					SET countLines += 1
				END
			END
			ELSE BEGIN
				LPF ~get_tooltip~ INT_VAR index = headerIndex STR_VAR resource = ~%SOURCE_RES%~ RET tooltip END
				SPRINT title ~%tooltip%~

				// Le nom de la capacité est déjà au début de l'unique ligne : on évite de le répéter
				SET isTitleRepeated = 0
				PATCH_IF NOT ~%title%~ STRING_EQUAL ~~ AND lineCount == 1 BEGIN
					SPRINT lowerTitle ~%title%~
					TO_LOWER lowerTitle
					PATCH_PHP_EACH ~lines%index%~ AS data => _ BEGIN
						SPRINT lowerLine ~%data_5%~
						TO_LOWER lowerLine
						PATCH_IF INDEX(~%lowerTitle%~ ~%lowerLine%~) == 0 BEGIN
							SET isTitleRepeated = 1
						END
					END
				END

				// Une ligne unique sert de titre : sans tooltip, ou avec un tooltip déjà présent dans la ligne
				SET isLineTheTitle = 0
				PATCH_IF lineCount == 1 AND (isTitleRepeated OR ~%title%~ STRING_EQUAL ~~) BEGIN
					SET isLineTheTitle = 1
				END

				// Le titre générique n'a de sens que pour regrouper plusieurs lignes
				PATCH_IF ~%title%~ STRING_EQUAL ~~ AND isMultiple AND lineCount > 1 BEGIN
					SET abilityNumber = index + 1
					SPRINT title @101124 // ~Capacité %abilityNumber%~
				END

				SET lineLevel = 1
				PATCH_IF NOT isLineTheTitle AND NOT ~%title%~ STRING_EQUAL ~~ BEGIN
					PATCH_IF isMultiple BEGIN
						LPF ~get_charged_ability_title~ INT_VAR charges depletion STR_VAR title RET title END
					END
					SET $lines(~%sort%~ ~%countLines%~ ~100~ ~0~ ~99~ ~%title%~) = 1
					SET countLines += 1
					SET lineLevel = 2
				END

				// +1 : le titre doit toujours être trié avant les lignes de sa capacité
				PATCH_PHP_EACH ~lines%index%~ AS data => _ BEGIN
					SET lineSort = sort + 1 + ~%data_0%~
					PATCH_IF isLineTheTitle AND isMultiple BEGIN
						LPF ~get_charged_ability_title~ INT_VAR charges depletion STR_VAR title = ~%data_5%~ RET data_5 = title END
					END
					SET $lines(~%lineSort%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~) = lineLevel
					SET countLines += 1
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

	PATCH_TIME ~step:load_effects:item=%isItem%:subspell=%isSubSpell%~ BEGIN LPM ~load_extended_effects~ END
	PATCH_TIME ~step:replace_effects:item=%isItem%:subspell=%isSubSpell%~ BEGIN LPM ~replace_effects~ END
	PATCH_TIME ~step:filter_effects:item=%isItem%:subspell=%isSubSpell%~ BEGIN LPM ~filter_effects~ END
	PATCH_TIME ~step:group_effects:item=%isItem%:subspell=%isSubSpell%~ BEGIN LPM ~group_effects~ END

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

				PATCH_TIME ~step:get_effect_description:item=%isItem%:subspell=%isSubSpell%~ BEGIN
					LPF ~get_effect_description~ INT_VAR ignoreDuration projectile projectileTarget = headTarget projectileTargetNumber = headTargetNumber RET effectDescription = description sort END
				END
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
	PATCH_IF charges == 0 BEGIN
		SPRINT chargeStr @102678 // ~usage illimité~
	END
    ELSE PATCH_IF depletion == 1 BEGIN
        PATCH_IF charges == 1 BEGIN
			SPRINT chargeStr @102677 // ~usage unique~
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
