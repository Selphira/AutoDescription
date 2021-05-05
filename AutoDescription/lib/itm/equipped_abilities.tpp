/* ================================================================= *
 * Gestion de la section "Capacités d'équipement" de la description. *
 * ================================================================= */

DEFINE_PATCH_FUNCTION ~format_cumulative_simple_signed~ INT_VAR strref = 0 STR_VAR value = ~~ RET value BEGIN
	LPF ~signed_value~ INT_VAR value RET value END
END

DEFINE_PATCH_FUNCTION ~format_flatted_attack_per_round~ INT_VAR strref = 0 STR_VAR value = ~~ RET value BEGIN
	INNER_PATCH_SAVE value ~%value%~ BEGIN
		SPRINT oneHalf @10011
		SPRINT andHalf @10012
		REPLACE_TEXTUALLY ~^5$~ ~%oneHalf%~           // 5  => une demi
		REPLACE_TEXTUALLY ~^\([0-9]\)?5$~ ~%andHalf%~ // 25 => 2 et demi
	END
	SPRINT value (AT ~%strref%~)
END

DEFINE_PATCH_FUNCTION ~equipped_abilities~ RET description BEGIN
	CLEAR_ARRAY abilities
	// CLEAR_ARRAY abilities_groups
	CLEAR_ARRAY opcode_values

    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~abilities~ BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~opcode_values~ BEGIN END

	READ_LONG  ITM_feature_blocks_offset blockOffset
    READ_SHORT ITM_feature_blocks_count  blockCount
    READ_SHORT ITM_flags                 flags

    SET count = 0

    GET_OFFSET_ARRAY blockOffsets ITM_V10_GEN_EFFECTS
    PHP_EACH blockOffsets AS int => blockOffset BEGIN
		READ_SHORT (blockOffset)                    opcode
		READ_BYTE  (blockOffset + EFF_timing_mode)  timing
		READ_BYTE  (blockOffset + EFF_probability1) probability1
		READ_BYTE  (blockOffset + EFF_probability2) probability2

		PATCH_IF !VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
			PATCH_IF timing == TIMING_while_equipped OR timing == TIMING_permanent BEGIN // while equiped
				PATCH_IF (probability1 - probability2) == 100 BEGIN
					SET abilityType = AbilityType_Equipped
					PATCH_IF opcode == 219 BEGIN
						SET opcodeBase = opcode
						PATCH_FOR_EACH subOpcode IN 0 1 BEGIN
							SET opcode = opcodeBase * 1000 + subOpcode
							LPF ~get_description_effect~ RET desc = description END
							PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
								SET $abilities($sort_opcodes(~%opcode%~) ~%count%~ ~%desc%~) = 1
								SET count += 1
							END
						END
					END
					ELSE BEGIN
						LPF ~get_description_effect~ RET desc = description END
						PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
							SET $abilities($sort_opcodes(~%opcode%~) ~%count%~ ~%desc%~) = 1
							SET count += 1
						END
					END
				END
				ELSE BEGIN
					PATCH_WARN ~%SOURCE_FILE% : equipped_abilities : Opcode '%opcode%' a une probabilité inferieure a 100 !~
				END
			END
			ELSE BEGIN PATCH_WARN ~%SOURCE_FILE% : equipped_abilities : Opcode '%opcode%' timing different de 2 ! (%timing%)~ END
		END
    END
    /*
	// TODO: ~get_description_effect_group~ va simplement appeler LPM ~opcode_group_%opcode%~
	// TODO: LPM ~opcode_group_%opcode%~ va utiliser data à sa façon ?
	// TODO: Bien penser qu'il pourra grouper un nombre indéterminé d'entrées... entre 1 et 9 par exemple
	// TODO: Penser aussi que pour un opcode déterminé, plusieurs groupes peuvent être créés, que ce qui détermine qu'on groupe ou non peut être différent d'un opcode à l'autre
	//       Ex: - Mémorisation de 2 sorts divins supplémentaires de niveau 5, 6 et 7
    //           - Mémorisation d'1 sort divin supplémentaire de niveau 2
    // Un compteur par groupe
    SET $abilities_groups(166 10) = 2 // compteur indiquant combien d'entrée à (tenter de) grouper (si possible)
    SET $abilities_groups(62) = 1
    // Une entrée par élément
    SET $abilities_groups_166_10(opcodea parameter1a parameter2a etca) = 1
    SET $abilities_groups_166_10(opcodeb parameter1b parameter2b etcb) = 1
    SET $abilities_groups_62_0 (opcodec parameter1c parameter2c etcc) = 1
    PATCH_PHP_EACH abilities_groups AS group => count BEGIN
		SET abilityType = AbilityType_Equipped
        PATCH_PRINT "%group_0% %group_1% => %count%"
        PATCH_IF count == 1 BEGIN
            PATCH_PRINT "1 seul element"
            PATCH_PHP_EACH ~abilities_groups_%group_0%_%group_1%~ AS data => v BEGIN
                LPM ~abilities_groups_to_vars~
                LPF ~get_description_effect_group~ RET desc = description END
            END
        END
        ELSE BEGIN
            // LPF ~get_description_effect_group~ STR_VAR group = EVAL "%group_0%_%group_1%" RET desc = description END // LPM ~opcode_group_%opcode%~
            // Code spécifique à chaque opcode qui décide comment grouper
            PATCH_PHP_EACH ~abilities_groups_%group_0%_%group_1%~ AS data => v BEGIN
                LPM ~abilities_groups_to_vars~
                PATCH_PRINT "+- %data_0% %data_1% => %v%"
            END
        END
    END
    */

    // PATCH_PHP_EACH ~abilities~ AS data => value BEGIN PATCH_PRINT "%data_0% %data_1% %value%" END

    LPF ~get_unique_equipped_abilities~ STR_VAR array_name = "abilities" RET count RET_ARRAY newAbilities END

	PATCH_IF (flags BAND BIT4) != 0 BEGIN
		SET count += 1
		SPRINT desc @102126 // ~Maudit : Ne peut être ôté qu'à l'aide d'un sort de Délivrance de la malédiction~
		SET $newAbilities(~0~ ~0~ ~%desc%~) = 1
	END

    SORT_ARRAY_INDICES newAbilities NUMERICALLY

	PATCH_IF count > 0 BEGIN LPF ~appendSection~ INT_VAR strref = 100010 RET description END END // ~Capacités d'équipement~

    PATCH_PHP_EACH ~newAbilities~ AS data => value BEGIN
		LPF ~appendProperty~ STR_VAR name = EVAL ~%data_2%~ RET description END
    END

	LPF ~group_physical_resistances~ RET description END
	LPF ~group_saves_throws~ RET description END
END

/* -------------------------------------------------------------------- *
 * Supprime les entrées en double, en se basant sur le nom en lowercase *
 * -------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~get_unique_equipped_abilities~ STR_VAR array_name = "" RET count RET_ARRAY newAbilities BEGIN
    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~newAbilities~ BEGIN END
    SET count = 0

	PATCH_PHP_EACH ~%array_name%~ AS data => value BEGIN
		SET found = 0
		PATCH_PHP_EACH newAbilities AS ability => v BEGIN
			SPRINT tmp1 ~%data_2%~
			SPRINT tmp2 ~%ability_2%~
			TO_LOWER tmp1
			TO_LOWER tmp2
			PATCH_IF ~%tmp1%~ STRING_EQUAL ~%tmp2%~ BEGIN
				SET found = 1
			END
		END
		PATCH_IF found == 0 BEGIN
			SET $newAbilities(~%data_0%~ ~%count%~ ~%data_2%~) = 1
			SET count += 1
		END
	END
END

/* --------------------------------------------------------------------------------------------------------- *
 * Groupement des résistances aux dégâts physiques, uniquement si les 4 sont présentes ET ont la même valeur *
 * Les valeurs trouvées sont 5, 10, 15, 20 et 25 %
 * --------------------------------------------------------------------------------------------------------- *
 * - Résistance aux dégâts tranchants : +5 %                                                                 *
 * - Résistance aux dégâts contondants : +5 %                                                                *
 * - Résistance aux dégâts perforants : +5 %                                                                 *
 * - Résistance aux dégâts de projectiles : +5 %                                                             *
 * Devient                                                                                                   *
 * - Résistance aux dégâts physiques : +5 %                                                                  *
 * --------------------------------------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~group_physical_resistances~ RET description BEGIN
    SPRINT regexTemplate ~~
    PATCH_FOR_EACH strref IN 102061 102062 102063 102064 BEGIN
		SPRINT name (AT ~%strref%~)
		SPRINT value ~value~
		SPRINT value ~\%%value%%~
		SPRINT name @100001 // %name% : %value%
        SPRINT regexTemplate ~%regexTemplate%%crlf%- %name%~
    END

    PATCH_FOR_EACH value IN ~+5~ ~+10~ ~+15~ ~+20~ ~+25~ BEGIN
        SPRINT value @10002 // ~%value% %~
        SPRINT name @102225 // ~Résistance aux dégâts physiques~
		SPRINT replace @100001 // %name% : %value%
        SPRINT regex EVAL ~%regexTemplate%~
		INNER_PATCH_SAVE description ~%description%~ BEGIN
			REPLACE_TEXTUALLY CASE_INSENSITIVE ~%regex%~ ~%crlf%- %replace%~
		END
    END
END

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
DEFINE_PATCH_FUNCTION ~group_saves_throws~ RET description BEGIN
    SPRINT regexTemplate ~~
    PATCH_FOR_EACH strref IN 102029 102030 102031 102032 102033 BEGIN
		SPRINT name @102034 // ~Jets de sauvegarde~
		SPRINT versus (AT ~%strref%~)
		SPRINT value ~value~
		SPRINT value ~\%%value%% %versus%~
		SPRINT name @100001 // %name% : %value%
        SPRINT regexTemplate ~%regexTemplate%%crlf%- %name%~
    END

    PATCH_FOR_EACH value IN ~+1~ ~+2~ ~+3~ ~+4~ ~+5~ BEGIN
        SPRINT name @102034 // ~Jets de sauvegarde~
		SPRINT replace @100001 // %name% : %value%
        SPRINT regex EVAL ~%regexTemplate%~
		INNER_PATCH_SAVE description ~%description%~ BEGIN
			REPLACE_TEXTUALLY CASE_INSENSITIVE ~%regex%~ ~%crlf%- %replace%~
		END
    END
END