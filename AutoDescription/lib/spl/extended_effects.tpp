DEFINE_PATCH_FUNCTION ~load_spell_extended_effects~
	INT_VAR
		baseProbability = 100
		forceTarget = 0
	RET
		countLines
	RET_ARRAY
		lines
BEGIN
	SET countLines = 0
	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~

				SET oldProbability = probability
				PATCH_IF baseProbability != 100 BEGIN
		            SET probability = probability * baseProbability / 100
		        END
		        //TODO: La cible est implicitement envoyée, il faudrait le faire explicitement
				//TODO: Ignorer la durée pour tous les opcodes si on a une durée du sort autre que "Spécial" !!
				LPF ~get_effect_description~ INT_VAR ignoreDuration forceTarget RET effectDescription = description sort END
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
				SET $leveled_opcodes(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~) = opcode
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
	RET
		inAllLevels
		total
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

	FOR (levelIndex = 0; levelIndex < countLevels; levelIndex += 1) BEGIN
		SET level = $level_effects(~%levelIndex%~)
		SET found = 0
		PATCH_PHP_EACH ~leveled_opcodes_%level%~ AS data => opcode BEGIN
			PATCH_IF opcode >= 0 AND opcode == match_opcode AND found == 0 BEGIN
			    LPM ~data_to_vars~

				PATCH_TRY LPM ~opcode_%opcode%_spell_level_match~ WITH DEFAULT END
				LPM ~opcode_match_except_duration~

				PATCH_IF match == 1 BEGIN
					SET found = 1
					SET total += 1

					PATCH_IF match_duration != duration BEGIN
						SET $all_durations(~%level%~) = duration
						SET total_durations += 1
					END

					// On ne désactive pas l'opcode du niveau 0
					PATCH_IF level > 0 BEGIN
						SET $effects_to_disabled(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%level%~) = level
					END
				END
				ELSE BEGIN
				/*
					PATCH_PRINT "NIVEAU : %level% - OPCODE: %opcode%
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

        PATCH_IF found == 0 BEGIN
            SET inAllLevels = 0
            SET levelIndex = countLevels
        END
	END

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
	STR_VAR
		file = ~~
	RET
		description
		totalLines
BEGIN
	// 146 :
	// 232 :
	// 272 : [272] Active un effet (boucle)
	// 326 :
	// 341 : Semble que ce soit toujours la cible de l'attaque
	SET forceTarget = (opcode == 146 OR opcode == 232 OR opcode == 326) ? 1 : 0
	SET totalLines = 0
	// Nécessité de vider les tableaux pour leur utilisation dans la fonction, afin que les opcodes de l'objet n'interfèrent pas avec ceux du sort.
	LPM ~clear_opcodes~

	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.spl~ BEGIN
        INNER_PATCH_FILE ~%file%.spl~ BEGIN
            SPRINT CURRENT_SOURCE_RES ~%file%~

			//TODO: LPF ~spell_duration~ RET duration = description ignoreDuration END // Uniquement si plusieurs lignes seront générées... Comment savoir AVANT ???

            PATCH_IF castingLevel > 0 BEGIN
                LPF ~get_spell_effects_description_for_level~ INT_VAR baseProbability castingLevel forceTarget RET description totalLines END
            END
            ELSE BEGIN
                LPF ~get_spell_effects_description~ INT_VAR baseProbability forceTarget STR_VAR description RET description totalLines END
            END
			PATCH_IF totalLines == 1 BEGIN
				INNER_PATCH_SAVE description ~%description%~ BEGIN
		            REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%- ~ ~~
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
	STR_VAR
		description = ~~
	RET
		description totalLines
BEGIN
	SET countLevels = 0
	SET countHeaders = 0

	LPM ~clear_levels~

    PATCH_DEFINE_ARRAY level_effects BEGIN END

	GET_OFFSET_ARRAY headerOffsets SPL_V10_HEADERS
	PHP_EACH headerOffsets AS _ => headerOffset BEGIN
		READ_SHORT (headerOffset + SPL_HEAD_level_required) requiredLevel
		READ_SHORT (headerOffset + SPL_HEAD_target) spellTarget

		SET $level_effects(~%countLevels%~) = requiredLevel
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

	LPM ~group_spell_effects_by_duration~
	LPM ~group_spell_effects_by_damage~
	//TODO: Regroupement des effets identiques entre chacun des niveaux ( a mettre dans leveled_opcodes_0 pour être géré de manière générique ?? Ca permettrait d'avoir la même chose entre ici et la version pour un niveau particulier)
	// FIXME: SPPR729
	// TODO: Avant de calculer les descriptions :
	// - Regrouper les effets dont seule la durée diffère (+ déterminer la formule)
	// - Regrouper les effets dont seul les dégâts diffèrent (+ déterminer la formule)
	// - Pour le "à partir du niveau 1", le véritable niveau à prendre en compte pour les calculs est celui où l'on peut apprendre le sort
	//   Ex: sort de niveau 7 = niveau 14
	//   Donc avoir un tableau qui fait la correspondance entre niveau du sort => niveau du lanceur
	//   et ce pour chaque type de sort (mage, prêtre, etc.)

	SORT_ARRAY_INDICES level_effects NUMERICALLY

	LPF ~build_spell_effects_description~ INT_VAR baseProbability forceTarget RET description totalLines END
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

	LPM ~clear_levels~

    PATCH_DEFINE_ARRAY level_effects BEGIN END

	LPF ~get_spell_headeroffset_for_level~ INT_VAR castingLevel RET headerOffset END

	READ_SHORT (headerOffset + SPL_HEAD_level_required) requiredLevel

	SET $level_effects(~%countLevels%~) = requiredLevel
	SET countLevels += 1
	SET countHeaders += 1

	LPF ~load_leveled_extended_effects~
		INT_VAR headerOffset
		RET EVAL
			~leveled_opcodes_count_%requiredLevel%~ = count_leveled_opcodes
		RET_ARRAY
			EVAL ~leveled_opcodes_%requiredLevel%~ = leveled_opcodes
	END

	LPF ~build_spell_effects_description~ INT_VAR baseProbability forceTarget RET description totalLines END
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
	CLEAR_ARRAY level_effects
	SET leveled_opcodes_count_0 = 0
END

DEFINE_PATCH_FUNCTION ~build_spell_effects_description~
	INT_VAR
		baseProbability = 100
		forceTarget = 0
	RET
		description
		totalLines
BEGIN
	SET totalLines = 0
	PATCH_PHP_EACH level_effects AS _ => requiredLevel BEGIN
		CLEAR_ARRAY lines

		LPM ~clear_opcodes~

		PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
			// Si plus petit, c'est qu'on a désactivé l'entrée lors d'une précédente opération
			PATCH_IF opcode >= 0 BEGIN
			    LPM ~data_to_vars~
				LPM ~add_opcode~
			END
		END

		LPF ~load_spell_extended_effects~ INT_VAR baseProbability forceTarget RET countLines RET_ARRAY lines END
		SET totalLines += countLines

		PATCH_IF countLines > 0 AND /*~leveled_opcodes_count_%requiredLevel%~ > 0 AND*/ requiredLevel > 1 BEGIN
            LPF ~appendLine~ RET description END
			SPRINT levelDescription @12320400 // ~À partir du niveau %requiredLevel%~
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

DEFINE_PATCH_MACRO ~group_spell_effects_by_duration~ BEGIN
	SET level = $level_effects(~0~)
	PATCH_PHP_EACH ~leveled_opcodes_%level%~ AS data => opcode BEGIN
		CLEAR_ARRAY effects_to_disabled
		PATCH_IF opcode >= 0 BEGIN
		    LPM ~data_to_vars~
		    LPM ~data_to_match_vars~
		    // TODO: Si un effet exactement pareil est présent dans les niveaux plus haut, le supprimer des niveaux supérieurs !
		    // TODO: Modifier la fonction pour qu'elle retourne dans effects_to_disabled tous les effets qui se trouvent dans un niveau supérieur à l'effet en cours.
		    // TODO: Selon l'opcode, pouvoir faire certains regroupement par niveau et pas d'autres, la durée est pour TOUS
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
		        END
		        SET $level_effects(~-1~) = 0
				SET $leveled_opcodes_0(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~) = opcode
				SET leveled_opcodes_count_0 += 1

				// On désactive les effets qui se trouvent dans les niveaux plus importants
				PATCH_PHP_EACH effects_to_disabled AS data => level2 BEGIN
					// Dépend du type du sort !
		            LPM ~data_to_vars~
				    SET $EVAL ~leveled_opcodes_%level2%~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~) = ~-1~
				    SET ~leveled_opcodes_count_%level2%~ -= 1
				    PATCH_IF ~leveled_opcodes_count_%level2%~ == 0 BEGIN
				        CLEAR_ARRAY ~leveled_opcodes_%level2%~
				    END
				END
		    END
		END
	END

END


DEFINE_PATCH_MACRO ~group_spell_effects_by_damage~ BEGIN
END