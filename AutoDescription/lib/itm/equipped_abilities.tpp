/* ================================================================= *
 * Gestion de la section "Capacités d'équipement" de la description. *
 * ================================================================= */

DEFINE_PATCH_FUNCTION ~format_cumulative_simple_signed~ INT_VAR strref = 0 STR_VAR value = ~~ RET value BEGIN
	LPF ~signed_value~ INT_VAR value RET value END
END

DEFINE_PATCH_FUNCTION ~format_flatted_attack_per_round~ INT_VAR strref = 0 STR_VAR value = ~~ RET value BEGIN
	INNER_PATCH_SAVE value ~%value%~ BEGIN
		SPRINT oneHalf @10010005
		SPRINT andHalf @10010006
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
    READ_LONG  ITM_flags                 flags

    SET count = 0

    //TODO: Première boucle pour grouper certains effets (ex: opcode 83 (dévie) et 197 (renvoi) : S#SHLD01)
    //      Pour éviter d'avoir de trop grosses descriptions !

    GET_OFFSET_ARRAY blockOffsets ITM_V10_GEN_EFFECTS
    PHP_EACH blockOffsets AS int => blockOffset BEGIN
		READ_SHORT (blockOffset)                    opcode
		READ_BYTE  (blockOffset + EFF_timing_mode)  timing
		READ_BYTE  (blockOffset + EFF_probability1) probability1
		READ_BYTE  (blockOffset + EFF_probability2) probability2

		PATCH_IF !VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
			PATCH_IF timing == TIMING_while_equipped OR timing == TIMING_permanent OR TIMING_duration == 0 OR opcode == 177 OR opcode == 183 OR opcode == 206 OR opcode == 283 OR opcode == 44 BEGIN // while equiped
				SET abilityType = AbilityType_Equipped
				PATCH_IF opcode == 219 BEGIN
					SET opcodeBase = opcode
					PATCH_FOR_EACH subOpcode IN 0 1 BEGIN
						SET opcode = opcodeBase * 1000 + subOpcode
						LPF ~get_description_effect~ RET desc = description sort END
						PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
							SET $abilities(~%sort%~ ~%count%~ ~%desc%~) = 1
							SET count += 1
						END
					END
				END
				ELSE BEGIN
					LPF ~get_description_effect~ RET desc = description sort END
					PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
						SET $abilities(~%sort%~ ~%count%~ ~%desc%~) = 1
						SET count += 1
					END
				END
			END
			ELSE BEGIN PATCH_WARN ~%SOURCE_FILE% : equipped_abilities : Opcode '%opcode%' timing non gere ! (%timing%)~ END
		END
		ELSE PATCH_IF $ignored_opcodes(~%opcode%~) == 1 BEGIN
			LPF ~log_warning~ STR_VAR message = EVAL ~Opcode %opcode% à gérer.~ END
		END
    END

    LPF ~get_unique_equipped_abilities~ STR_VAR array_name = "abilities" RET count RET_ARRAY newAbilities END

	PATCH_IF (flags BAND BIT4) != 0 BEGIN
		SET count += 1
		SPRINT desc @102126 // ~Maudit : Ne peut être ôté qu'à l'aide d'un sort de Délivrance de la malédiction~
		SET $newAbilities(~0~ ~0~ ~%desc%~) = 1
	END

	PATCH_IF itemType == ITM_TYPE_helm BEGIN
		PATCH_IF ((flags BAND BIT25) == 0 AND itemType == ITM_TYPE_helm) OR ((flags BAND BIT25) == BIT25 AND itemType != ITM_TYPE_helm) BEGIN
			SET count += 1
			SPRINT desc @102679 // ~Protection contre les coups critiques~
			SET $newAbilities(~0~ ~0~ ~%desc%~) = 1
		END
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
    PATCH_FOR_EACH strref IN 10860001 10870001 10880001 10890001 BEGIN
		SPRINT name (AT ~%strref%~)
		SPRINT value ~value~
		SPRINT value ~\%%value%%~
		SPRINT name @100001 // %name% : %value%
        SPRINT regexTemplate ~%regexTemplate%%crlf%- %name%~
    END

    PATCH_FOR_EACH value IN ~+5~ ~+10~ ~+15~ ~+20~ ~+25~ ~+50~ BEGIN
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
    PATCH_FOR_EACH strref IN 10330001 10340001 10350001 10360001 10370001 BEGIN
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