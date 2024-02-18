DEFINE_PATCH_FUNCTION ~load_spell_extended_effects~
	INT_VAR
		baseProbability = 100
		forceTarget = 0
		ignoreDuration = 0
	RET
		countLines
	RET_ARRAY
		lines
BEGIN
	SET countLines = 0
	SET projectile = 0
	SET projectileTarget = 0
	SET projectileTargetNumber = 0

	PATCH_IF isSpellInItem AND VARIABLE_IS_SET $level_projectiles(~%levelIndex%~) BEGIN
		SET projectile = $level_projectiles(~%levelIndex%~)
		SET projectileTarget = $level_targets(~%levelIndex%~)
		SET projectileTargetNumber = $level_target_numbers(~%levelIndex%~)
	END

	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~

				SET oldProbability = probability
				PATCH_IF baseProbability != 100 BEGIN
		            SET probability = probability * baseProbability / 100
		        END
				LPF ~get_effect_description~ INT_VAR ignoreDuration ignoreSavingThrow forceTarget projectile projectileTarget projectileTargetNumber RET effectDescription = description sort END
				PATCH_IF NOT ~%effectDescription%~ STRING_EQUAL ~~ BEGIN
					SET probability = oldProbability
					SET $lines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 1
					SET countLines += 1
				END
		    END
	    END
	END

	LPF ~get_unique_effects~ RET countLines = count RET_ARRAY lines = effects END
	LPF ~group_probability_effects~ RET countLines = count RET_ARRAY lines = effects END
END


DEFINE_PATCH_FUNCTION ~load_leveled_extended_effects~
	INT_VAR
		headerOffset = 0
	RET
		count_leveled_opcodes
	RET_ARRAY
		leveled_opcodes
BEGIN
	READ_SHORT (headerOffset + SPL_HEAD_level_required) requiredLevel

	SET count_leveled_opcodes = 0

	CLEAR_ARRAY leveled_opcodes
	LPM ~clear_opcodes~

    PATCH_DEFINE_ASSOCIATIVE_ARRAY leveled_opcodes BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY opcodes BEGIN END

	LPM ~load_extended_effects~
	LPM ~replace_effects~
	LPM ~filter_effects~
	LPM ~group_effects~

	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~
		        SET count_leveled_opcodes += 1
				SET $leveled_opcodes(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~) = opcode
		    END
	    END
	END
END

DEFINE_PATCH_FUNCTION ~spell_has_same_effects_on_all_levels_except_duration~
	INT_VAR
		match_opcode = 0
		match_isExternal   = 0
		match_target       = 0
		match_power        = 0
		match_parameter1   = 0
		match_parameter2   = 0
		match_timingMode   = 0
		match_resistance   = 0
		match_duration     = 0
		match_probability  = 0
		match_probability1 = 0
		match_probability2 = 0
		match_diceCount    = 0
		match_diceSides    = 0
		match_saveType     = 0
		match_saveBonus    = 0
		match_special      = 0
		match_parameter3   = 0
		match_parameter4   = 0
		match_custom_int   = 0
	STR_VAR
		match_resref     = ~~
		match_resref2    = ~~
		match_resref3    = ~~
		match_custom_str = ~~
		match_macro      = ~opcode_match_except_duration~
		return_parameter = ~~
	RET
		inAllLevels
		total
		total_durations
	RET_ARRAY
		effects_to_disabled
		all_durations
		all_effects
BEGIN
	SET inAllLevels = 1
    SET total = 0
    SET total_durations = 0

    PATCH_DEFINE_ARRAY all_durations BEGIN END
    PATCH_DEFINE_ARRAY all_effects BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY effects_to_disabled BEGIN END

	FOR (levelIndex = 0; levelIndex < countLevels; levelIndex += 1) BEGIN
		SET level = $level_effects(~%levelIndex%~)
		SET found = 0
		SET hasOpcode = 0
		PATCH_PHP_EACH ~leveled_opcodes_%level%~ AS data => opcode BEGIN
			PATCH_IF opcode >= 0 BEGIN
				SET hasOpcode = 1
			END
			PATCH_IF (opcode == match_opcode OR match_opcode == 0 - opcode - 1) AND found == 0 BEGIN
			    LPM ~data_to_vars~

			    PATCH_IF opcode < 0 BEGIN
			        SET opcode = 0 - opcode - 1
			    END

				PATCH_TRY LPM ~opcode_%opcode%_spell_level_match~ WITH DEFAULT END
				LPM ~%match_macro%~

				PATCH_IF match == 1 BEGIN
					SET found = 1
			        PATCH_IF opcode >=0 BEGIN
						SET total += 1

						SPRINT $all_effects(~%level%~) EVAL ~%%return_parameter%%~

						PATCH_IF match_duration != duration BEGIN
							SET $all_durations(~%level%~) = duration
							SET total_durations += 1
						END

						// On ne désactive pas l'opcode du niveau 0
						PATCH_IF level > 0 BEGIN
							SET $effects_to_disabled(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~ ~%level%~) = level
						END
					END
				END
				ELSE BEGIN
				/*
					PATCH_PRINT "NIVEAU : %level% - OPCODE: %opcode% - %match_macro%
					    match_isExternal : %match_isExternal%   == %isExternal%
					AND match_target : %match_target%       == %target%
					AND match_power : %match_power%        == %power%
					AND match_parameter1 : %match_parameter1%   == %parameter1%
					AND match_parameter2 : %match_parameter2%   == %parameter2%
					AND match_timingMode : %match_timingMode%   == %timingMode%
					AND match_resistance : %match_resistance%   == %resistance%
					AND match_duration : %match_duration%     == %duration%
					AND match_probability : %match_probability%  == %probability%
					AND match_probability1 : %match_probability1% == %probability1%
					AND match_probability2 : %match_probability2% == %probability2%
					AND match_diceCount : %match_diceCount%    == %diceCount%
					AND match_diceSides : %match_diceSides%    == %diceSides%
					AND match_saveType : %match_saveType%     == %saveType%
					AND match_saveBonus : %match_saveBonus%    == %saveBonus%
					AND match_special : %match_special%      == %special%
					AND match_parameter3 : %match_parameter3%   == %parameter3%
					AND match_parameter4 : %match_parameter4%   == %parameter4%
					AND match_custom_int : %match_custom_int%   == %custom_int%
					AND match_resref : %match_resref%     STRING_EQUAL %resref%
					AND match_resref2 : %match_resref2%    STRING_EQUAL %resref2%
					AND match_resref3 : %match_resref3%    STRING_EQUAL %resref3%
					AND match_custom_str : %match_custom_str% STRING_EQUAL %custom_str%
					"
				*/
				END
			END
		END

        PATCH_IF found == 0 AND hasOpcode == 1 BEGIN
            SET inAllLevels = 0
            SET levelIndex = countLevels
        END
	END

	SORT_ARRAY_INDICES ~all_durations~ NUMERICALLY

	PATCH_IF total_durations > 0 AND total - 1 != total_durations BEGIN
		SET inAllLevels = 0
	END
END

DEFINE_PATCH_FUNCTION ~get_unique_spell_effects~ INT_VAR requiredLevel = 0 STR_VAR array_name = "" RET count RET_ARRAY newAbilities BEGIN
	CLEAR_ARRAY newAbilities
    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~newAbilities~ BEGIN END
    SET count = 0

	PATCH_PHP_EACH ~%array_name%~ AS data => value BEGIN
		PATCH_IF requiredLevel == data_3 BEGIN
			SET found = 0
			PATCH_PHP_EACH newAbilities AS ability => v BEGIN
				PATCH_IF data_3 == ability_3 BEGIN
					SPRINT tmp1 ~%data_2%~
					SPRINT tmp2 ~%ability_2%~
					TO_LOWER tmp1
					TO_LOWER tmp2
					PATCH_IF ~%tmp1%~ STRING_EQUAL ~%tmp2%~ BEGIN
						SET found = 1
					END
				END
			END
			PATCH_IF found == 0 BEGIN
				SET $newAbilities(~%data_0%~ ~%count%~ ~%data_2%~ ~%data_3%~ ~%data_4%~) = 1
				SET count += 1
			END
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_item_spell_effects_description~
	INT_VAR
		castingLevel = 0
		baseProbability = 100
		ignoreDurationIfSameForAllEffect = 0
	STR_VAR
		file = ~~
	RET
		description
		strDuration
		totalLines
BEGIN
	// 146 :
	// 232 :
	// 272 : [272] Active un effet (boucle)
	// 326 :
	// 341 : Semble que ce soit toujours la cible de l'attaque
	SET forceTarget = (opcode == 146 OR opcode == 232 OR opcode == 326) ? 1 : 0
	SET totalLines = 0
	SPRINT strDuration ~~
	// Nécessité de vider les tableaux pour leur utilisation dans la fonction, afin que les opcodes de l'objet n'interfèrent pas avec ceux du sort.
	LPM ~clear_opcodes~

	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.spl~ BEGIN
        INNER_PATCH_FILE ~%file%.spl~ BEGIN
            SPRINT CURRENT_SOURCE_RES ~%file%~
            SET isSpecialDuration = 0
            SET isSpellInItem = isItem

			PATCH_IF ignoreDurationIfSameForAllEffect BEGIN
				LPM ~load_level_effects~
	            LPF ~spell_duration~ RET ignoreDuration strDuration isSpecialDuration = is_special END
				LPM ~clear_levels~
			END

            PATCH_IF castingLevel > 0 BEGIN
                LPF ~get_spell_effects_description_for_level~ INT_VAR baseProbability castingLevel forceTarget ignoreDuration RET description totalLines END
            END
            ELSE BEGIN
				LPM ~load_level_effects~
                LPF ~get_spell_effects_description~ INT_VAR baseProbability forceTarget ignoreDuration STR_VAR description RET description totalLines END
            END
			PATCH_IF totalLines == 1 BEGIN
				INNER_PATCH_SAVE description ~%description%~ BEGIN
		            REPLACE_TEXTUALLY EVALUATE_REGEXP ~^%crlf%- ~ ~~
		        END
	        END
			ELSE PATCH_IF totalLines > 1 BEGIN
				INNER_PATCH_SAVE description ~%description%~ BEGIN
		            REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~%crlf%  ~
		        END
	        END
        END
    END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Resource %file%.spl doesn't exist.~ END
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_effects_description~
	INT_VAR
		baseProbability = 100
		forceTarget = 0
		ignoreDuration = 0
	STR_VAR
		description = ~~
	RET
		description totalLines
BEGIN
	LPM ~group_identical_spell_effects_between_level~
	LPM ~group_spell_effects_by_duration~
	LPM ~group_spell_effects_by_parameters~
	LPM ~group_spell_effects_by_damage~

	// FIXME: SPPR729
	// TODO: Avant de calculer les descriptions :
	// - Regrouper les effets dont seule la durée diffère (+ déterminer la formule)
	// - Regrouper les effets dont seul les dégâts diffèrent (+ déterminer la formule)
	// - Pour le "à partir du niveau 1", le véritable niveau à prendre en compte pour les calculs est celui où l'on peut apprendre le sort
	//   Ex: sort de niveau 7 = niveau 14
	//   Donc avoir un tableau qui fait la correspondance entre niveau du sort => niveau du lanceur
	//   et ce pour chaque type de sort (mage, prêtre, etc.)

	SORT_ARRAY_INDICES level_effects NUMERICALLY

	LPF ~build_spell_effects_description~ INT_VAR baseProbability forceTarget ignoreDuration RET description totalLines END
END

DEFINE_PATCH_MACRO ~load_level_effects~ BEGIN
	// TODO: Cette variable est utilisée à plusieurs endroits...  Trouver une meilleure solution
	SET abilityType = ~-1~
	SET countLevels = 0
	SET countHeaders = 0

	LPM ~clear_levels~

    PATCH_DEFINE_ARRAY level_effects BEGIN END
    PATCH_DEFINE_ARRAY level_projectiles BEGIN END
    PATCH_DEFINE_ARRAY level_targets BEGIN END
    PATCH_DEFINE_ARRAY level_target_numbers BEGIN END

	GET_OFFSET_ARRAY headerOffsets SPL_V10_HEADERS
	PHP_EACH headerOffsets AS _ => headerOffset BEGIN
		READ_SHORT (headerOffset + SPL_HEAD_level_required) requiredLevel
		READ_SHORT (headerOffset + SPL_HEAD_target) spellTarget
		READ_BYTE  (headerOffset + SPL_HEAD_target_number) spellTargetNumber
		READ_SHORT (headerOffset + SPL_HEAD_projectile) spellProjectile

		SET $level_effects(~%countLevels%~) = requiredLevel
		SET $level_projectiles(~%countLevels%~) = spellProjectile
		SET $level_targets(~%countLevels%~) = spellTarget
		SET $level_target_numbers(~%countLevels%~) = spellTargetNumber
		SET countLevels += 1
		SET countHeaders += 1

		LPF ~load_leveled_extended_effects~
			INT_VAR requiredLevel headerOffset
			RET EVAL
				~leveled_opcodes_count_%requiredLevel%~ = count_leveled_opcodes
			RET_ARRAY
				EVAL ~leveled_opcodes_%requiredLevel%~ = leveled_opcodes
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_effects_description_for_level~
	INT_VAR
		baseProbability = 100
		castingLevel = 0
		forceTarget = 0
	STR_VAR
		description = ~~
	RET
		description totalLines
BEGIN
	SET countLevels = 0
	SET countHeaders = 0

	LPM ~clear_levels~

    PATCH_DEFINE_ARRAY level_effects BEGIN END

	LPF ~get_spell_headeroffset_for_level~ INT_VAR castingLevel RET headerOffset END

	READ_SHORT (headerOffset + SPL_HEAD_level_required) requiredLevel
	READ_SHORT (headerOffset + SPL_HEAD_target) spellTarget
	READ_BYTE  (headerOffset + SPL_HEAD_target_number) spellTargetNumber
	READ_SHORT (headerOffset + SPL_HEAD_projectile) spellProjectile

	SET $level_effects(~%countLevels%~) = requiredLevel
	SET $level_projectiles(~%countLevels%~) = spellProjectile
	SET $level_targets(~%countLevels%~) = spellTarget
	SET $level_target_numbers(~%countLevels%~) = spellTargetNumber
	SET countLevels += 1
	SET countHeaders += 1

	LPF ~load_leveled_extended_effects~
		INT_VAR headerOffset
		RET EVAL
			~leveled_opcodes_count_%requiredLevel%~ = count_leveled_opcodes
		RET_ARRAY
			EVAL ~leveled_opcodes_%requiredLevel%~ = leveled_opcodes
	END

	LPF ~build_spell_effects_description~ INT_VAR baseProbability forceTarget ignoreDuration RET description totalLines END
END

DEFINE_PATCH_FUNCTION ~get_spell_headeroffset_for_level~
	INT_VAR
		castingLevel = 0
	RET
		headerOffset
BEGIN
	SET headerOffset = 0
	SET headerLevel  = 0

	GET_OFFSET_ARRAY headerOffsets SPL_V10_HEADERS
	PHP_EACH headerOffsets AS _ => offset BEGIN
		READ_SHORT (offset + SPL_HEAD_level_required) requiredLevel
		PATCH_IF requiredLevel <= castingLevel AND requiredLevel > headerLevel BEGIN
			SET headerLevel  = requiredLevel
			SET headerOffset = offset
		END
	END
END

DEFINE_PATCH_MACRO ~clear_opcodes~ BEGIN
	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		CLEAR_ARRAY ~opcodes_%opcode%~
	END
	CLEAR_ARRAY opcodes
END

DEFINE_PATCH_MACRO ~clear_levels~ BEGIN
	PATCH_PHP_EACH level_effects AS _ => requiredLevel BEGIN
		CLEAR_ARRAY ~leveled_opcodes_%requiredLevel%~
	END
	CLEAR_ARRAY leveled_opcodes_zero
	CLEAR_ARRAY level_effects
	SET leveled_opcodes_count_zero = 0
END

DEFINE_PATCH_FUNCTION ~build_spell_effects_description~
	INT_VAR
		baseProbability = 100
		forceTarget = 0
		ignoreDuration = 0
	RET
		description
		totalLines
BEGIN
	SET totalLines = 0

	// Traitement des effets qui sont effectifs que pour certains niveaux du sortilège

	CLEAR_ARRAY grouped_level_effects
	CLEAR_ARRAY groups_level_effects

	PATCH_PHP_EACH level_effects AS levelIndex => requiredLevel BEGIN
		PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
			PATCH_IF opcode >= 0 BEGIN
				SET minRequiredLevel = requiredLevel
				SET maxRequiredLevel = 99
				SET loop1 = 1
				LPM ~data_to_vars~
				PATCH_PHP_EACH level_effects AS matchLevelIndex => matchRequiredLevel BEGIN
					SET matched = 0
					SET nextLevelIndex = matchLevelIndex + 1
					SET hasNextLevel = VARIABLE_IS_SET $level_effects(~%nextLevelIndex%~)
					PATCH_IF loop1 == 1 AND requiredLevel < matchRequiredLevel BEGIN
						PATCH_PHP_EACH ~leveled_opcodes_%matchRequiredLevel%~ AS data => matchOpcode BEGIN
							PATCH_IF (matchOpcode == opcode OR opcode == 0 - matchOpcode - 1) AND matched == 0 BEGIN
								LPM ~data_to_match_vars~
								PATCH_TRY LPM ~opcode_%opcode%_spell_level_match~ WITH DEFAULT END
					            PATCH_IF ignoreDuration BEGIN
					                LPM ~opcode_match_except_duration~
					            END
					            ELSE BEGIN
									LPM ~opcode_match~
								END
					            PATCH_IF match == 1 BEGIN
				                    SET matched = 1
					            END
							END
						END

						PATCH_IF matched == 0 BEGIN
							SET maxRequiredLevel = matchRequiredLevel - 1
							SET loop1 = 0
						END
					END
				END
				PATCH_IF minRequiredLevel == 1 AND maxRequiredLevel == 99 BEGIN
					SET $EVAL ~leveled_opcodes_zero~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~) = opcode
				END
				ELSE BEGIN
					SET key = ((minRequiredLevel + 100) * 100) + maxRequiredLevel
					SET $groups_level_effects(~%key%~) = 1
					SET $EVAL ~grouped_level_effects_%key%~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~) = opcode
				END
			END
		END
	END

	LPF ~array_count~ STR_VAR array_name = ~level_effects~ RET countLeveledOpcode = count END

	SORT_ARRAY_INDICES groups_level_effects NUMERICALLY

	CLEAR_ARRAY lines

	LPM ~clear_opcodes~

	// Traitement des effets qui sont effectifs pour tous les niveaux du sortilège

	PATCH_PHP_EACH ~leveled_opcodes_zero~ AS data => opcode BEGIN
		// Si plus petit, c'est qu'on a désactivé l'entrée lors d'une précédente opération
		PATCH_IF opcode >= 0 BEGIN
		    LPM ~data_to_vars~
			LPM ~add_opcode~
		END
	END

	LPF ~load_spell_extended_effects~ INT_VAR baseProbability forceTarget ignoreDuration RET countLines RET_ARRAY lines END
	SET totalLines += countLines

	PATCH_IF countLines > 0 BEGIN
		LPF ~add_items_section_to_description~ STR_VAR arrayName = ~lines~ RET description END
	END

	PATCH_PHP_EACH groups_level_effects AS levelIndex => _ BEGIN
		CLEAR_ARRAY lines

		LPM ~clear_opcodes~

		PATCH_PHP_EACH ~grouped_level_effects_%levelIndex%~ AS data => opcode BEGIN
			// Si plus petit, c'est qu'on a désactivé l'entrée lors d'une précédente opération
			PATCH_IF opcode >= 0 BEGIN
			    LPM ~data_to_vars~
				LPM ~add_opcode~
			END
		END

		LPF ~load_spell_extended_effects~ INT_VAR baseProbability forceTarget ignoreDuration RET countLines RET_ARRAY lines END
		SET totalLines += countLines

		PATCH_IF countLines > 0 AND countLeveledOpcode > 1 BEGIN
			SET maxRequiredLevel = levelIndex MODULO 100
			SET minRequiredLevel = ((levelIndex - maxRequiredLevel) / 100) - 100

            LPF ~appendLine~ RET description END
            PATCH_IF maxRequiredLevel == 99 BEGIN
				SPRINT levelDescription @12320400 // ~À partir du niveau %minRequiredLevel%~
            END
            ELSE PATCH_IF minRequiredLevel = maxRequiredLevel BEGIN
				SPRINT levelDescription @12320402 // ~Au niveau %minRequiredLevel%~
            END
            ELSE BEGIN
				SPRINT levelDescription @12320401 // ~Entre le niveau %minRequiredLevel% et %maxLevel%~
			END
			SPRINT description ~%description%%crlf%%levelDescription%~
		END
		//LPM ~add_common_opcodes_to_description
		LPF ~add_items_section_to_description~ STR_VAR arrayName = ~lines~ RET description END
	END
/*
	INNER_PATCH_SAVE description ~%description%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^%crlf%~ ~~
	END
	*/
END

DEFINE_PATCH_MACRO ~group_identical_spell_effects_between_level~ BEGIN
	LOCAL_SET desactivated = 0
	LOCAL_SET continue = 1
	LOCAL_SET lastFoundLevel = 0 - 1
	LOCAL_SET inAllLevel = 1

	// On commence par traiter tous les effets identiques qui se trouvent dans tous les niveaux du sort
	CLEAR_ARRAY positions
	SET requiredLevel = $level_effects(~0~)
	PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
		LPM ~data_to_vars~
		SET inAllLevel = 1
		CLEAR_ARRAY tmpPositions
		PATCH_PHP_EACH level_effects AS _ => matchRequiredLevel BEGIN
			PATCH_IF inAllLevel == 1 AND requiredLevel < matchRequiredLevel BEGIN
				PATCH_PHP_EACH ~leveled_opcodes_%matchRequiredLevel%~ AS data => matchOpcode BEGIN
					PATCH_IF matchOpcode == opcode AND inAllLevel == 1 BEGIN
						LPM ~data_to_match_vars~
						PATCH_TRY LPM ~opcode_%opcode%_spell_level_match~ WITH DEFAULT END
			            PATCH_IF ignoreDuration BEGIN
			                LPM ~opcode_match_except_duration~
			            END
			            ELSE BEGIN
							LPM ~opcode_match~
						END
			            PATCH_IF match == 1 BEGIN
			                SET $tmpPositions(~%matchRequiredLevel%-%match_position%~) = 1
			            END
			            ELSE BEGIN
							SET inAllLevel = 0
			            END
					END
				END
			END
		END
		PATCH_IF inAllLevel == 1 BEGIN
			SET $tmpPositions(~%requiredLevel%-%position%~) = 1
			// On place l'effet dans les effets globaux du sort
			SET $EVAL ~leveled_opcodes_zero~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~) = opcode

			PATCH_PHP_EACH level_effects AS index => tmpRequiredLevel BEGIN
				PATCH_PHP_EACH ~leveled_opcodes_%tmpRequiredLevel%~ AS data => tmpOpcode BEGIN
			        LPM ~data_to_vars~
			        PATCH_IF VARIABLE_IS_SET $tmpPositions(~%tmpRequiredLevel%-%position%~) AND $tmpPositions(~%tmpRequiredLevel%-%position%~) == 1 BEGIN
			            SET $positions(~%tmpRequiredLevel%-%position%~) = 1
			        END
				END
			END
		END
	END
	PATCH_PHP_EACH level_effects AS index => requiredLevel BEGIN
		PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
	        LPM ~data_to_vars~
	        PATCH_IF VARIABLE_IS_SET $positions(~%requiredLevel%-%position%~) AND $positions(~%requiredLevel%-%position%~) == 1 BEGIN
	            SET $EVAL ~leveled_opcodes_%requiredLevel%~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~) = 0 - opcode - 1
	        END
		END
	END

	CLEAR_ARRAY positions

	// On traite ensuite les effets qui diffèrent selon le niveau
	PATCH_PHP_EACH level_effects AS index => requiredLevel BEGIN
		PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
			SET loop2 = 1
			PATCH_IF opcode >= 0 BEGIN
	            LPM ~data_to_vars~
	            SET desactivated = 0
	            SET continue = 1
				PATCH_PHP_EACH level_effects AS _ => matchRequiredLevel BEGIN
					PATCH_IF loop2 == 1 BEGIN
						PATCH_IF continue == 1 AND requiredLevel < matchRequiredLevel BEGIN
							PATCH_PHP_EACH ~leveled_opcodes_%matchRequiredLevel%~ AS data => matchOpcode BEGIN
								PATCH_IF loop2 == 1 AND matchOpcode >= 0 BEGIN
							        LPM ~data_to_match_vars~
									PATCH_IF matchOpcode == opcode AND NOT VARIABLE_IS_SET $positions(~%matchRequiredLevel%-%match_position%~) BEGIN
										PATCH_TRY LPM ~opcode_%opcode%_spell_level_match~ WITH DEFAULT END
							            PATCH_IF ignoreDuration BEGIN
							                LPM ~opcode_match_except_duration~
							            END
							            ELSE BEGIN
											LPM ~opcode_match~
										END
							            PATCH_IF match == 1 BEGIN
							                SET $positions(~%matchRequiredLevel%-%match_position%~) = 1
						                    SET desactivated = 1
						                    SET loop2 = 0
							            END
							        END
							    END
							END
					        PATCH_IF desactivated == 0 BEGIN
					            SET continue = 0
					        END
						END
					END
				END
			END
		END
	END

	PATCH_PHP_EACH level_effects AS index => requiredLevel BEGIN
		PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
			PATCH_IF opcode >= 0 BEGIN
		        LPM ~data_to_vars~
		        PATCH_IF VARIABLE_IS_SET $positions(~%requiredLevel%-%position%~) AND $positions(~%requiredLevel%-%position%~) == 1 BEGIN
		            SET $EVAL ~leveled_opcodes_%requiredLevel%~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~) = 0 - opcode - 1
		        END
	        END
		END
	END

	CLEAR_ARRAY positions
END

DEFINE_PATCH_MACRO ~group_spell_effects_by_duration~ BEGIN
	SET level = $level_effects(~0~)
	PATCH_PHP_EACH ~leveled_opcodes_%level%~ AS data => opcode BEGIN
		CLEAR_ARRAY effects_to_disabled
		PATCH_IF opcode >= 0 BEGIN
		    LPM ~data_to_vars~
		    LPM ~data_to_match_vars~
		    // TODO: Si un effet exactement pareil est présent dans les niveaux plus haut, le supprimer des niveaux supérieurs !
		    // TODO: Modifier la fonction pour qu'elle retourne dans effects_to_disabled tous les effets qui se trouvent dans un niveau supérieur à l'effet en cours.
		    // Un spécifique pour l'opcode 12 qui va vérifier si dice, side et/ou value changent !!
		    //   Car on peut avoir en même temps les dés qui changent, ainsi que le bonus...
		    //   1d8 par niveau du lanceur/20 + 2 par niveau du lanceur/10
		    //   1d8 par niveau du lanceur/20 + 2
		    //   1d8 tous les 2 niveaux du lanceur/20 + 2
		    //   1d8 + 2 par niveau du lanceur/20


		    LPF spell_has_same_effects_on_all_levels_except_duration
				INT_VAR
					match_opcode
					match_isExternal
					match_target
					match_power
					match_parameter1
					match_parameter2
					match_timingMode
					match_resistance
					match_duration
					match_probability
					match_probability1
					match_probability2
					match_diceCount
					match_diceSides
					match_saveType
					match_saveBonus
					match_special
					match_parameter3
					match_parameter4
					match_custom_int
				STR_VAR
					match_resref
					match_resref2
					match_resref3
					match_custom_str
		        RET
		            inAllLevels
		            total
		            total_durations
		        RET_ARRAY
		            effects_to_disabled
		            all_durations
		    END

		    PATCH_IF inAllLevels AND total > 1 BEGIN
		        PATCH_IF isSpecialDuration AND total_durations > 0 BEGIN
					PATCH_IF level == 1 BEGIN
						LPF get_first_level_for_spell RET level = minLevel END
					END

					LPF ~get_complex_duration~
						STR_VAR
							array_name = ~all_durations~
						RET
							strDuration = complex_duration
					END
		        END
		        PATCH_IF NOT ~%strDuration%~ STRING_EQUAL ~~ BEGIN
		            SPRINT complex_duration @100311 // ~pendant %strDuration%~
		        END

		        LPM ~group_spell_effects_disable~
		    END
		END
	END
END

DEFINE_PATCH_MACRO ~group_spell_effects_by_parameters~ BEGIN
	SET level = $level_effects(~0~)

	PATCH_DEFINE_ASSOCIATIVE_ARRAY opcodes_resistance BEGIN
		27 => 1
		28 => 1
		29 => 1
		30 => 1
		31 => 1
		84 => 1
		85 => 1
		86 => 1
		87 => 1
		88 => 1
		89 => 1
		166 => 1
		173 => 1
		502 => 1
		503 => 1
		504 => 1
	END

	PATCH_PHP_EACH ~leveled_opcodes_%level%~ AS data => opcode BEGIN
		CLEAR_ARRAY effects_to_disabled
		/*
		 * Uniquement si parameter2 == MOD_TYPE_cumulative ET que parameter1 et duration sont différents
		 */
		PATCH_FOR_EACH basicOpcode IN
			6 10 15 19 21 22 23 44 49 54 73 93 94 95 96 97 104 108 126 132 178 179 189 191 250 263 278 284 285 286 288 289 299 305 306 323 325 // Les basiques
			27 28 29 30 31 84 85 86 87 88 89 166 173 502 503 504 // Les résistances
			12 17 18 111 218
			// 25 98
		BEGIN
			PATCH_IF opcode == basicOpcode BEGIN
			    LPM ~data_to_vars~
			    PATCH_IF opcode == 12 BEGIN
					SET parameter2 = parameter2 BAND 65535
				END
			    PATCH_IF parameter2 == MOD_TYPE_cumulative OR ((parameter2 == MOD_TYPE_flat OR parameter2 == MOD_TYPE_percentage) AND VARIABLE_IS_SET $opcodes_resistance(~%opcode%~)) BEGIN
			        LPM ~data_to_match_vars~
				    LPF spell_has_same_effects_on_all_levels_except_duration
						INT_VAR
							match_opcode match_isExternal match_target match_power match_parameter1 match_parameter2
							match_timingMode match_resistance match_duration match_probability match_probability1
							match_probability2 match_diceCount match_diceSides match_saveType match_saveBonus match_special
							match_parameter3 match_parameter4 match_custom_int
						STR_VAR
							match_resref match_resref2 match_resref3 match_custom_str
							match_macro = ~opcode_match_except_parameter1_and_duration~
							return_parameter = ~parameter1~
				        RET
				            inAllLevels total total_durations
				        RET_ARRAY
				            effects_to_disabled all_durations all_effects
				    END

			        PATCH_IF inAllLevels AND total > 1 BEGIN
						LPF ~get_complex_value~
							INT_VAR
								is_percent = VARIABLE_IS_SET $opcodes_resistance(~%opcode%~) ? 1 : 0
							STR_VAR
								array_name = ~all_effects~
							RET
								is_valid
								complex_value
								complex_value_int
						END
						PATCH_IF is_valid BEGIN
					        PATCH_IF isSpecialDuration AND total_durations > 0 BEGIN
								PATCH_IF level == 1 BEGIN
									LPF get_first_level_for_spell RET level = minLevel END
								END

								LPF ~get_complex_duration~
									STR_VAR
										array_name = ~all_durations~
									RET
										strDuration = complex_duration
								END
					        END
					        PATCH_IF NOT ~%strDuration%~ STRING_EQUAL ~~ BEGIN
					            SPRINT complex_duration @100311 // ~pendant %strDuration%~
					        END
				            PATCH_IF opcode == 12 OR opcode == 17 BEGIN
				                LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount = 0 RET value = damage END
								PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
									PATCH_IF complex_value_int > 0 BEGIN
										SPRINT complex_value ~%value% + %complex_value%~
									END
									ELSE BEGIN
	                                    SPRINT complex_value ~%value% %complex_value%~
	                                END
								END
				            END
					        LPM ~group_spell_effects_disable~
						END
					END
			    END
			END
		END
		PATCH_IF opcode == 12 BEGIN
			LPM ~data_to_vars~
			SET mode = parameter2 BAND 65535

			PATCH_IF mode == 0 BEGIN
		        LPM ~data_to_match_vars~

				// Si diceCount et duration sont différents
			    LPF spell_has_same_effects_on_all_levels_except_duration
					INT_VAR
						match_opcode match_isExternal match_target match_power match_parameter1 match_parameter2
						match_timingMode match_resistance match_duration match_probability match_probability1
						match_probability2 match_diceCount match_diceSides match_saveType match_saveBonus match_special
						match_parameter3 match_parameter4 match_custom_int
					STR_VAR
						match_resref match_resref2 match_resref3 match_custom_str
						match_macro = ~opcode_match_except_diceCount_and_duration~
						return_parameter = ~diceCount~
			        RET
			            inAllLevels total total_durations
			        RET_ARRAY
			            effects_to_disabled all_durations all_effects
			    END
		        PATCH_IF inAllLevels AND total > 1 BEGIN
					LPF ~get_complex_value~
						INT_VAR
							is_percent = VARIABLE_IS_SET $opcodes_resistance(~%opcode%~) ? 1 : 0
							dice_sides = diceSides
						STR_VAR
							array_name = ~all_effects~
						RET
							is_valid
							complex_value
							complex_value_int
					END
					PATCH_IF is_valid BEGIN
				        PATCH_IF isSpecialDuration AND total_durations > 0 BEGIN
							PATCH_IF level == 1 BEGIN
								LPF get_first_level_for_spell RET level = minLevel END
							END

							LPF ~get_complex_duration~
								STR_VAR
									array_name = ~all_durations~
								RET
									strDuration = complex_duration
							END
				        END
				        PATCH_IF NOT ~%strDuration%~ STRING_EQUAL ~~ BEGIN
				            SPRINT complex_duration @100311 // ~pendant %strDuration%~
				        END
						LPM ~group_spell_effects_disable~
					END
		        END

				// Si parameter1 et duration sont différents
				// Si diceCount et parameter1 et duration sont différents
			END
		END
	END
END

DEFINE_PATCH_MACRO ~group_spell_effects_disable~ BEGIN
	SET $leveled_opcodes_zero(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~) = opcode
	SET leveled_opcodes_count_zero += 1

	// On désactive les effets qui se trouvent dans les niveaux plus importants
	PATCH_PHP_EACH effects_to_disabled AS data => level2 BEGIN
        LPM ~data_to_vars~
	    SET $EVAL ~leveled_opcodes_%level2%~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~) = ~-1~
	    SET ~leveled_opcodes_count_%level2%~ -= 1
	    PATCH_IF ~leveled_opcodes_count_%level2%~ == 0 BEGIN
	        CLEAR_ARRAY ~leveled_opcodes_%level2%~
	    END
	END
END


DEFINE_PATCH_MACRO ~group_spell_effects_by_damage~ BEGIN
END