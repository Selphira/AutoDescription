DEFINE_PATCH_FUNCTION ~get_spell_effects~
	INT_VAR
		forceTarget = 0
		forcedProbability = 100
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
			READ_LONG  SPL_HEAD_target                   spellTarget
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
		LPF ~log_warning~ STR_VAR message = EVAL ~La ressource %file%.spl n'existe pas.~ END
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_level_effects~
	RET_ARRAY
		effects
		levels
BEGIN
	SET featureCount = 0
    PHP_EACH blockOffsets AS _ => blockOffset BEGIN
		READ_SHORT blockOffset opcode
		PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
			SET abilityType = AbilityType_Charge
			PATCH_IF opcode == 219 BEGIN
				SET opcodeBase = opcode
				PATCH_FOR_EACH subOpcode IN 0 1 BEGIN
					SET opcode = opcodeBase * 1000 + subOpcode
					LPF ~get_description_effect~ INT_VAR forceTarget STR_VAR theTarget ofTheTarget toTheTarget RET desc = description descSort = sort END
					PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
						SET $tmpEffects(~%sort%~ ~%featureCount%~ ~%desc%~ ~%requiredLevel%~) = 1
						SET featureCount += 1
					END
				END
			END
			ELSE BEGIN
				LPF ~get_description_effect~ INT_VAR forceTarget STR_VAR theTarget ofTheTarget toTheTarget RET desc = description descSort = sort END
				PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
					SET $tmpEffects(~%sort%~ ~%featureCount%~ ~%desc%~ ~%requiredLevel%~) = 1
					SET featureCount += 1
				END
			END
		END
		ELSE PATCH_IF $ignored_opcodes(~%opcode%~) == 1 BEGIN
			LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode% à gérer.~ END
		END
	END

	LPF ~get_unique_spell_effects~ INT_VAR requiredLevel STR_VAR array_name = "tmpEffects" RET featureCount = count RET_ARRAY features = newAbilities END

	SORT_ARRAY_INDICES features NUMERICALLY

	PATCH_PHP_EACH features AS data => value BEGIN
		SET $effects(~%data_0%~ ~%data_1%~ ~%data_2%~ ~%data_3%~) = value
	END

	SET $levels(~%requiredLevel%~) = featureCount
END

DEFINE_PATCH_FUNCTION ~get_single_spell_effect~
	INT_VAR
		forceTarget = 0
		forcedProbability = 100
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
			READ_LONG  SPL_HEAD_target             spellTarget
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
						LPF ~get_description_effect~ INT_VAR forceTarget forceProbability = 1 forcedProbability STR_VAR theTarget ofTheTarget toTheTarget RET effectDescription = description descSort = sort END
					END
				END
			END
		END
	END
	ELSE BEGIN
		LPF ~log_warning~ STR_VAR message = EVAL ~La ressource %file%.spl n'existe pas.~ END
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_description~
	INT_VAR
		forceTarget = 0
		probability = 100
	STR_VAR
		file = ~~
		theTarget = ~~
		ofTheTarget = ~~
		toTheTarget = ~~
	RET
		spellDescription
		count
		featureCount
BEGIN
	LPF ~get_spell_effects~ INT_VAR forceTarget = 1 STR_VAR file theTarget ofTheTarget toTheTarget RET count RET_ARRAY effects levels END

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
				SET $newAbilities(~%data_0%~ ~%count%~ ~%data_2%~ ~%data_3%~) = 1
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

		    PATCH_FOR_EACH strref IN 10370001 10360001 10350001 10340001 10330001 BEGIN
				SPRINT name @102034 // ~Jets de sauvegarde~
				SPRINT versus (AT ~%strref%~)
	            SPRINT regex ~\([ ]*\)- %name%\(.*\)%colon%\([^(]*\) %versus%\(.*\)\(%crlf%\)*~

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
				SPRINT replace ~%crlf%%indentation%- %name%%target%%colon%%value%%options%~

			    PATCH_FOR_EACH strref IN 10370001 10360001 10350001 10340001 10330001 BEGIN
					SPRINT versus (AT ~%strref%~)
			        SPRINT regex ~%regex%%crlf%[ ]*- %name%%target%%colon%%value% %versus%%options%~
			    END

				REPLACE_TEXTUALLY CASE_INSENSITIVE ~%regex%~ ~%replace%~
	        END
		END
    END
END