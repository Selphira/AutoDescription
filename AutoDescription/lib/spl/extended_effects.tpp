DEFINE_PATCH_FUNCTION ~add_extended_effects~
	STR_VAR
		description = ~~
	RET
		description
BEGIN
	READ_SHORT SPL_type  spellType
	READ_LONG  SPL_level spellLevel
	// Variable utilisée à plusieurs endroits...
	// TODO: Trouver une meilleure solution
	SET abilityType = ~-1~
	SET countHeaders = 0
	SET count_levels = 0

	CLEAR_ARRAY levels

    PATCH_DEFINE_ARRAY levels BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY common_opcodes BEGIN END

	GET_OFFSET_ARRAY headerOffsets SPL_V10_HEADERS
	PHP_EACH headerOffsets AS _ => headerOffset BEGIN
		READ_SHORT (headerOffset + SPL_HEAD_level_required) requiredLevel
		READ_SHORT (headerOffset + SPL_HEAD_target) spellTarget

		SET $levels(~%count_levels%~) = requiredLevel
		SET count_levels += 1

		LPF ~load_leveled_extended_effects~
			INT_VAR requiredLevel headerOffset
			RET EVAL ~count_leveled_opcodes_%requiredLevel%~ = count_leveled_opcodes
			RET_ARRAY
				EVAL ~leveled_opcodes_%requiredLevel%~ = leveled_opcodes
		END

		SET countHeaders += 1
	END

	// FIXME: SPPR729
	// TODO: Avant de calculer les descriptions :
	// - Regrouper les effets dont seule la durée diffère (+ déterminer la formule)
	// - Regrouper les effets dont seul les dégâts diffèrent (+ déterminer la formule)
	// - Pour le "à partir du niveau 1", le véritable niveau à prendre en compte pour les calculs est celui où l'on peut apprendre le sort
	//   Ex: sort de niveau 7 = niveau 14
	//   Donc avoir un tableau qui fait la correspondance entre niveau du sort => niveau du lanceur
	//   et ce pour chaque type de sort (mage, prêtre, etc.)

	SET level = $levels(~0~)
	PATCH_PHP_EACH ~leveled_opcodes_%level%~ AS data => opcode BEGIN
		CLEAR_ARRAY effects_to_disabled
		PATCH_IF opcode >= 0 BEGIN
		    LPM ~data_to_vars~
		    // TODO: Si un effet exactement pareil est présent dans les niveaux plus haut, le supprimer des niveaux supérieurs !
		    // TODO: Modifier la fonction pour qu'elle retourne dans effects_to_disabled tous les effets qui se trouvent dans un niveau supérieur à l'effet en cours.
		    LPF has_same_effect_in_all_levels
				INT_VAR
					match_opcode = opcode
					match_level = level
					match_isExternal   = isExternal
					match_target       = target
					match_power        = power
					match_parameter1   = parameter1
					match_parameter2   = parameter2
					match_timingMode   = timingMode
					match_resistance   = resistance
					match_duration     = duration
					match_probability  = probability
					match_probability1 = probability1
					match_probability2 = probability2
					match_diceCount    = diceCount
					match_diceSides    = diceSides
					match_saveType     = saveType
					match_saveBonus    = saveBonus
					match_special      = special
					match_parameter3   = parameter3
					match_parameter4   = parameter4
					match_custom_int   = custom_int
				STR_VAR
					match_resref     = ~%resref%~
					match_resref2    = ~%resref2%~
					match_resref3    = ~%resref3%~
					match_custom_str = ~%custom_str%~
		        RET
		            inAllLevels
		            total_durations
		        RET_ARRAY
		            effects_to_disabled
		            all_durations
		    END
		    PATCH_IF inAllLevels BEGIN
		        // TODO: Et si la durée du sort est égale à spéciale, dans les autres cas, pas besoin de recalculer la durée, vu qu'elle ne sera pas affichée
		        PATCH_IF total_durations > 0 BEGIN
					PATCH_IF level == 1 BEGIN
						LPF get_first_level_for_spell RET level = minLevel END
					END

					LPF ~get_complex_duration~
						INT_VAR
							base_level = level
							base_duration = duration
						STR_VAR
							array_name = ~all_durations~
						RET
							complex_duration
					END
					PATCH_PRINT "Durée complexe: %complex_duration%"

					//TODO: Si complex_duration est vide, ne pas l'utiliser ?

		        END
				SET $common_opcodes(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~) = opcode

				// On désactive les effets qui se trouvent dans les niveaux plus importants
				PATCH_PHP_EACH effects_to_disabled AS data => level2 BEGIN
					// Dépend du type du sort !
		            LPM ~data_to_vars~
				    SET $EVAL ~leveled_opcodes_%level2%~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~) = ~-1~
				END
		    END
		END
	END

	LPF ~add_common_opcodes_to_description~ RET description END
	LPF ~add_leveled_opcodes_to_description~ RET description END
END

DEFINE_PATCH_FUNCTION ~add_common_opcodes_to_description~
	RET description
BEGIN
	PATCH_PHP_EACH ~common_opcodes~ AS data => opcode BEGIN
		LPM ~data_to_vars~
		LPM ~add_opcode~
	END
	LPM ~add_common_opcodes_to_description~
	LPF ~add_items_section_to_description~ STR_VAR arrayName = ~lines~ RET description END
END

DEFINE_PATCH_MACRO ~add_common_opcodes_to_description~ BEGIN
	SET countLines = 0
	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~
		        //TODO: La cible est implicitement envoyée, il faudrait le faire explicitement
				//TODO: Ignorer la durée pour tous les opcodes si on a une durée du sort autre que "Spécial" !!
				LPF ~get_effect_description~ INT_VAR ignoreDuration RET effectDescription = description sort END
				//LPF ~get_effect_description~ RET effectDescription = description sort END
				PATCH_IF NOT ~%effectDescription%~ STRING_EQUAL ~~ BEGIN
					SET $lines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 1
					SET countLines += 1
				END
		    END
	    END
	END

	LPF ~get_unique_effects~ RET countLines = count RET_ARRAY lines = effects END
	LPF ~group_probability_effects~ RET countLines = count RET_ARRAY lines = effects END
END

DEFINE_PATCH_FUNCTION ~add_leveled_opcodes_to_description~
	RET description
BEGIN
	PATCH_PHP_EACH levels AS _ => level BEGIN
		SET requiredLevel = level
		LPF ~load_leveled_opcodes~ INT_VAR requiredLevel RET description END
	END
END

DEFINE_PATCH_FUNCTION ~load_leveled_opcodes~
	INT_VAR requiredLevel = 0
	RET description
BEGIN
	PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
		PATCH_IF opcode >= 0 BEGIN
		    LPM ~data_to_vars~
			LPM ~add_opcode~
		END
	END

	PATCH_IF requiredLevel == 1 BEGIN
		LPF get_first_level_for_spell RET requiredLevel = minLevel END
	END

	LPM ~add_common_opcodes_to_description~
	SPRINT title @12320400 // ~À partir du niveau %requiredLevel%~
	LPF ~add_section_to_description~ INT_VAR count = ~countLines~ STR_VAR title arrayName = ~lines~ RET description END
END

DEFINE_PATCH_FUNCTION ~load_leveled_extended_effects~
	INT_VAR
		headerOffset = 0
		requiredLevel = 0
	RET
		count_leveled_opcodes
	RET_ARRAY
		leveled_opcodes
BEGIN
	SET count_leveled_opcodes = 0

	CLEAR_ARRAY leveled_opcodes
	CLEAR_ARRAY opcodes

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
				SET $leveled_opcodes(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~) = opcode
		    END
	    END
	END
END

DEFINE_PATCH_FUNCTION ~has_same_effect_in_all_levels~
	INT_VAR
		match_opcode = 0
		match_level = 0
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
	RET
		inAllLevels
		total_durations
	RET_ARRAY
		effects_to_disabled
		all_durations
BEGIN
	SET inAllLevels = 1
    SET total = 0
    SET total_durations = 0

    PATCH_DEFINE_ARRAY all_durations BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY effects_to_disabled BEGIN END

	FOR (levelIndex = 0; levelIndex < count_levels; levelIndex += 1) BEGIN
		SET level = $levels(~%levelIndex%~)
		SET found = 0
		PATCH_PHP_EACH ~leveled_opcodes_%level%~ AS data => opcode BEGIN
			PATCH_IF opcode >= 0 AND opcode == match_opcode AND found == 0 BEGIN
			    LPM ~data_to_vars~
			    // TODO: Vérifier si une méthode du genre opcode_%opcode_match existe
			    //       Si oui, l'utiliser, cela permettra de faire des vérifications, qui peuvent éviter de tenir
			    //       compte de variables qui ne sont pas relevant...
			    //Exempla vec opcode 119 : Parameter #1: Irrelevant
				//                         Parameter #2: Irrelevant

				PATCH_TRY
					LPM ~opcode_%opcode%_match~
				WITH DEFAULT
					SET match = (
						match_isExternal   == isExternal
	                    AND match_target       == target
	                    AND match_power        == power
	                    AND match_parameter1   == parameter1
	                    AND match_parameter2   == parameter2
	                    AND match_timingMode   == timingMode
	                    AND match_resistance   == resistance
	                    AND match_probability  == probability
	                    AND match_probability1 == probability1
	                    AND match_probability2 == probability2
	                    AND match_diceCount    == diceCount
	                    AND match_diceSides    == diceSides
	                    AND match_saveType     == saveType
	                    AND match_saveBonus    == saveBonus
	                    AND match_special      == special
	                    AND match_parameter3   == parameter3
	                    AND match_parameter4   == parameter4
	                    AND match_custom_int   == custom_int
	                    AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
	                    AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
	                    AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
	                    AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
	                )
				END
				PATCH_IF match == 1 BEGIN
					SET found = 1
					SET total += 1

					PATCH_IF match_duration != duration BEGIN
						SET $all_durations(~%level%~) = duration
						SET total_durations += 1
					END

					SET $effects_to_disabled(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%level%~) = level
				END
				ELSE BEGIN
					PATCH_PRINT "NIVEAU : %level% - OPCODE: %opcode%
					    %match_isExternal%   == %isExternal%
					AND %match_target%       == %target%
					AND %match_power%        == %power%
					AND %match_parameter1%   == %parameter1%
					AND %match_parameter2%   == %parameter2%
					AND %match_timingMode%   == %timingMode%
					AND %match_resistance%   == %resistance%
					//AND match_duration     == duration
					AND %match_probability%  == %probability%
					AND %match_probability1% == %probability1%
					AND %match_probability2% == %probability2%
					AND %match_diceCount%    == %diceCount%
					AND %match_diceSides%    == %diceSides%
					AND %match_saveType%     == %saveType%
					AND %match_saveBonus%    == %saveBonus%
					AND %match_special%      == %special%
					AND %match_parameter3%   == %parameter3%
					AND %match_parameter4%   == %parameter4%
					AND %match_custom_int%   == %custom_int%
					AND %match_resref%     STRING_EQUAL %resref%
					AND %match_resref2%    STRING_EQUAL %resref2%
					AND %match_resref3%    STRING_EQUAL %resref3%
					AND %match_custom_str% STRING_EQUAL %custom_str%
					"
				END
			END
		END

		PATCH_IF found == 0 BEGIN
			SET inAllLevels = 0
			SET levelIndex = count_levels
		END
	END

	PATCH_IF total_durations > 0 AND total - 1 != total_durations BEGIN
		SET inAllLevels = 0
	END
END

DEFINE_PATCH_FUNCTION ~load_extended_effects~
	INT_VAR
		headerOffset = 0
	RET
		countLines
	RET_ARRAY
		lines
BEGIN
	SET countLines = 0

	CLEAR_ARRAY lines
	CLEAR_ARRAY opcodes

    PATCH_DEFINE_ASSOCIATIVE_ARRAY lines BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY opcodes BEGIN END

	LPM ~load_extended_effects~
	LPM ~replace_effects~
	LPM ~filter_effects~
	LPM ~group_effects~

	PATCH_IF spellTarget == TARGET_HEAD_self OR spellTarget == TARGET_HEAD_self_ignore_pause BEGIN
		SPRINT theTarget   @102475 // ~le lanceur~
		SPRINT ofTheTarget @102476 // ~du lanceur~
		SPRINT toTheTarget @102477 // ~au lanceur~
	END

	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~
		        //TODO: La cible est implicitement envoyée, il faudrait le faire explicitement
				LPF ~get_effect_description~ RET effectDescription = description sort END
				PATCH_IF NOT ~%effectDescription%~ STRING_EQUAL ~~ BEGIN
					SET $lines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 1
					SET countLines += 1
				END
		    END
	    END
	END

	LPF ~get_unique_effects~ RET countLines = count RET_ARRAY lines = effects END
	LPF ~group_probability_effects~ RET countLines = count RET_ARRAY lines = effects END
END

DEFINE_PATCH_FUNCTION ~get_spell_effects~
	INT_VAR
		forceTarget = 0
		forcedProbability = 100
		ignoreDuration = 0
	STR_VAR
		file = ~~
		theTarget = ~~
		ofTheTarget = ~~
		toTheTarget = ~~
	RET
		count
	RET_ARRAY
		effects
		levels
BEGIN
	SET count = 0
	SET requiredLevel = 0

	CLEAR_ARRAY tmpEffects
	CLEAR_ARRAY effects
	CLEAR_ARRAY levels
    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~tmpEffects~ BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~effects~ BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~levels~ BEGIN END

	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.spl~ BEGIN
        INNER_PATCH_FILE ~%file%.spl~ BEGIN
			READ_BYTE  SPL_HEAD_target                   spellTarget
			READ_LONG  SPL_extended_headers_offset       headerOffset
			READ_SHORT SPL_extended_headers_count        headerCount
			READ_SHORT SPL_casting_feature_blocks_count  featureCount

			SPRINT OLD_SOURCE_RES ~%SOURCE_RES%~
			SPRINT SOURCE_RES ~%file%~

			PATCH_IF spellTarget == 5 OR spellTarget == 7 BEGIN
				forceTarget = TARGET_FX_self
			END

			PATCH_IF featureCount > 0 BEGIN
				CLEAR_ARRAY features
                PATCH_DEFINE_ASSOCIATIVE_ARRAY ~features~ BEGIN END
				GET_OFFSET_ARRAY blockOffsets SPL_V10_GEN_EFFECTS

				LPF ~get_spell_level_effects~ RET_ARRAY effects levels END
		    END

			PATCH_IF headerCount > 0 BEGIN
			    FOR (headerIndex = 0; headerIndex < headerCount; headerIndex += 1) BEGIN
					SET count += 1
	                SET offset = headerOffset + 0x28 * headerIndex
					READ_SHORT (offset + SPL_HEAD_level_required) requiredLevel

					CLEAR_ARRAY features
                    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~features~ BEGIN END

					GET_OFFSET_ARRAY2 blockOffsets offset SPL_V10_HEAD_EFFECTS

					LPF ~get_spell_level_effects~ RET_ARRAY effects levels END
			    END
			END
			SPRINT SOURCE_RES ~%OLD_SOURCE_RES%~
		END
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Resource %file%.spl doesn't exist.~ END
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_level_effects~
	RET_ARRAY
		effects
		levels
BEGIN
	SET cumulable = 1
	SET featureCount = 0
    PHP_EACH blockOffsets AS _ => blockOffset BEGIN
		READ_SHORT blockOffset opcode
		PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
			//TODO: Meilleur test pour vérifier si provient d'un effet d'une capacité d'équipement
			PATCH_IF abilityType != AbilityType_Equipped BEGIN
				SET abilityType = AbilityType_Charge
			END
			PATCH_IF opcode == 219 BEGIN
				SET opcodeBase = opcode
				PATCH_FOR_EACH subOpcode IN 0 1 BEGIN
					SET opcode = opcodeBase * 1000 + subOpcode
					LPF ~get_description_effect~ INT_VAR ignoreDuration forceTarget STR_VAR theTarget ofTheTarget toTheTarget RET desc = description sort END
					PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
						PATCH_IF cumulable == 0 BEGIN
							SPRINT stringNotCumulable @102682
							SPRINT desc ~%desc% (%stringNotCumulable%)~
						END
						SET $tmpEffects(~%sort%~ ~%featureCount%~ ~%desc%~ ~%requiredLevel%~ ~%opcode%~) = 1
						SET featureCount += 1
					END
				END
			END
			PATCH_IF opcode == 321 BEGIN
				PATCH_IF ~%resref%~ STRING_EQUAL ~%SOURCE_RES%~ AND
            			(timingMode != TIMING_duration OR duration != 0) BEGIN // N'empêche rien sans durée
            		SET cumulable = 0
            	END
            END
			ELSE BEGIN
				LPF ~get_description_effect~ INT_VAR ignoreDuration forceTarget STR_VAR theTarget ofTheTarget toTheTarget RET desc = description sort END
				PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
					PATCH_IF cumulable == 0 AND NOT VARIABLE_IS_SET $opcodes_ignore_not_cumulable(~%opcode%~) BEGIN
						SPRINT stringNotCumulable @102682
						SPRINT desc ~%desc% (%stringNotCumulable%)~
					END
					SET $tmpEffects(~%sort%~ ~%featureCount%~ ~%desc%~ ~%requiredLevel%~ ~%opcode%~) = 1
					SET featureCount += 1
				END
			END
		END
		ELSE PATCH_IF $ignored_opcodes(~%opcode%~) == 1 BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% à gérer.~ END
		END
	END

	PATCH_IF featureCount > 0 BEGIN
		LPF ~get_unique_spell_effects~ INT_VAR requiredLevel STR_VAR array_name = "tmpEffects" RET featureCount = count RET_ARRAY features = newAbilities END

		SORT_ARRAY_INDICES features NUMERICALLY

		PATCH_PHP_EACH features AS data => value BEGIN
			SET $effects(~%data_0%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~) = value
		END

		SET $levels(~%requiredLevel%~) = featureCount
	END
END

DEFINE_PATCH_FUNCTION ~get_single_spell_effect~
	INT_VAR
		forceTarget = 0
		forcedProbability = 100
		cumulable = 1
	STR_VAR
		file = ~~
		theTarget = ~~
		ofTheTarget = ~~
		toTheTarget = ~~
	RET
		effectDescription
BEGIN
	SPRINT effectDescription ~~
	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.spl~ BEGIN
        INNER_PATCH_FILE ~%file%.spl~ BEGIN
			READ_BYTE  SPL_HEAD_target             spellTarget
			READ_LONG  SPL_extended_headers_offset headerOffset
			READ_SHORT SPL_extended_headers_count  headerCount

			PATCH_IF spellTarget == 5 OR spellTarget == 7 BEGIN
				forceTarget = TARGET_FX_self
			END

			PATCH_IF headerCount == 1 BEGIN
                SET offset = headerOffset
				GET_OFFSET_ARRAY2 blockOffsets offset SPL_V10_HEAD_EFFECTS
				PATCH_PHP_EACH blockOffsets AS _ => blockOffset BEGIN
					READ_SHORT blockOffset opcode
					PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
						LPF ~get_description_effect~ INT_VAR ignoreDuration forceTarget forceProbability = 1 forcedProbability STR_VAR theTarget ofTheTarget toTheTarget RET effectDescription = description descSort = sort END

						PATCH_IF cumulable == 0 BEGIN
							SPRINT stringNotCumulable @102682
							SPRINT effectDescription ~%effectDescription% (%stringNotCumulable%)~
						END
					END
				END
			END
		END
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Resource %file%.spl doesn't exist.~ END
	END
END

DEFINE_PATCH_FUNCTION ~get_item_spell_description~
	INT_VAR
		forceTarget = 0
		probability = 100
		ignoreDuration = 0
	STR_VAR
		file = ~~
		theTarget = ~~
		ofTheTarget = ~~
		toTheTarget = ~~
	RET
		spellDescription
		count
		featureCount
		lineCount
BEGIN
	LPF ~get_spell_effects~ INT_VAR ignoreDuration forceTarget = 1 STR_VAR file theTarget ofTheTarget toTheTarget RET count RET_ARRAY effects levels END

	SET featureCount = 0
	SPRINT spellDescription ~~
	SPRINT indentation ~~

	PATCH_IF count > 1 BEGIN
		SPRINT indentation ~  ~
	END

	PATCH_PHP_EACH levels AS requiredLevel => levelCount BEGIN
		PATCH_PHP_EACH effects AS data => feature BEGIN
			SET featureCount += 1
		END
	END

	PATCH_PHP_EACH levels AS requiredLevel => levelCount BEGIN
		SPRINT levelSpellDescription ~~
		PATCH_IF requiredLevel != 0 AND (count > 1 OR requiredLevel > 1) BEGIN
			SPRINT levelDescription @12320400 // ~À partir du niveau %requiredLevel%~
			SPRINT levelSpellDescription ~%levelSpellDescription%%crlf%%levelDescription%~
		END
		PATCH_PHP_EACH effects AS data => feature BEGIN
			PATCH_IF requiredLevel == data_3 BEGIN
				SPRINT levelSpellDescription ~%levelSpellDescription%%crlf%%indentation%- %data_2%~
				// Indique que les effets ne sont (in)valides que sous certaines conditions, mais il n'y a pas d'autres effets listés.
				PATCH_IF featureCount == 1 AND data_4 == 318 BEGIN
					SPRINT levelSpellDescription ~~
				END
			END
		END

		PATCH_IF enable_shrinkage BEGIN
			//LPF ~shrink_resistances~ RET spellDescription END
			LPF ~shrink_spell_effects_saves_throws~ STR_VAR spellDescription = EVAL ~%levelSpellDescription%~ RET levelSpellDescription = spellDescription END
			//LPF ~shrink_abilities~ RET spellDescription END
			//LPF ~shrink_thief_skills~ RET spellDescription END
		END
		SPRINT spellDescription ~%spellDescription%%levelSpellDescription%~
	END

	INNER_PATCH ~%spellDescription%~ BEGIN
		COUNT_2DA_ROWS ~1~ ~lineCount~
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


//TODO: Ca fonctionnerait aussi pour le jet de sauvegarde des equipped abilities ?? A TESTER !!!

/* --------------------------------------------------------------------------------------------------------- *
 * Groupement des jets de sauvegarde, uniquement si les 5 sont présentes ET ont la même valeur               *
 * Les valeurs trouvées sont 1, 2, 3, 4 et 5                                                                 *
 * --------------------------------------------------------------------------------------------------------- *
 * - Jets de sauvegarde : +2 contre la paralysie, la mort et les poisons                                     *
 * - Jets de sauvegarde : +2 contre les baguettes, les sceptres et les bâtons                                *
 * - Jets de sauvegarde : +2 contre la pétrification et la métamorphose                                      *
 * - Jets de sauvegarde : +2 contre les souffles                                                             *
 * - Jets de sauvegarde : +2 contre les sorts                                                                *
 * Devient                                                                                                   *
 * - Jets de sauvegarde : +2                                                                                 *
 * --------------------------------------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~shrink_spell_effects_saves_throws~
	STR_VAR
		spellDescription = ~~
	RET
		spellDescription
BEGIN
	PATCH_IF shrink_saves_throws BEGIN
		INNER_PATCH_SAVE spellDescription ~%spellDescription%~ BEGIN
			SPRINT indentation ~~
			SPRINT target ~~
			SPRINT value ~~
			SPRINT options ~~
			SET canShrink = 1

		    PATCH_FOR_EACH strref IN 10330001 10340001 10350001 10360001 10370001 BEGIN
				SPRINT name @102034 // ~Jets de sauvegarde~
				SPRINT versus (AT ~%strref%~)
	            SPRINT regex ~\([ ]*\)- %name%\(.*\)%colon%\([-\+]+[0-9]*\) %versus%\(.*\)\(%crlf%\)*~

			    found = INDEX_BUFFER (CASE_INSENSITIVE EVALUATE_REGEXP ~%regex%~)
				PATCH_IF found != "-1" BEGIN
		            REPLACE_EVALUATE CASE_INSENSITIVE ~%regex%~ BEGIN
		                PATCH_IF ~%value%~ STRING_EQUAL ~~ BEGIN
							SPRINT indentation ~%MATCH1%~
							SPRINT target ~%MATCH2%~
							SPRINT value ~%MATCH3%~
							SPRINT options ~%MATCH4%~
		                END

		                PATCH_IF NOT ~%target%~ STRING_EQUAL ~%MATCH2%~
		                    OR NOT ~%value%~ STRING_EQUAL ~%MATCH3%~
		                    OR NOT ~%options%~ STRING_EQUAL ~%MATCH4%~
		                BEGIN
			                SET canShrink = 0
		                END
		            END ~%MATCH0%~
			    END
			    ELSE BEGIN
			        SET canShrink = 0
			    END
	        END

	        PATCH_IF canShrink == 1 BEGIN
				SPRINT name @102034 // ~Jets de sauvegarde~
				SPRINT regex ~~
				SPRINT replace ~%indentation%- %name%%target%%colon%%value%%options%~
				INNER_PATCH_SAVE value ~%value%~ BEGIN
					REPLACE_TEXTUALLY ~+~ ~\+~
				END
			    PATCH_FOR_EACH strref IN 10330001 10340001 10350001 10360001 10370001 BEGIN
					SPRINT versus (AT ~%strref%~)
			        SPRINT regex ~%regex%%crlf%[ ]*- %name%%target%%colon%%value% %versus%%options%~
			    END

				REPLACE_TEXTUALLY CASE_INSENSITIVE ~%regex%~ ~%replace%~
	        END
		END
    END
END