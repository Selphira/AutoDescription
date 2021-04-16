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

    SET count = 0

    GET_OFFSET_ARRAY blockOffsets ITM_V10_GEN_EFFECTS
    PHP_EACH blockOffsets AS int => blockOffset BEGIN
		READ_SHORT (blockOffset)                    opcode
		READ_BYTE  (blockOffset + EFF_timing_mode)  timing
		READ_BYTE  (blockOffset + EFF_probability1) probability1
		READ_BYTE  (blockOffset + EFF_probability2) probability2

		PATCH_IF !VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
			PATCH_IF timing == TIMING_while_equipped BEGIN // while equiped
				PATCH_IF (probability1 - probability2) == 100 BEGIN
					SET abilityType = AbilityType_Equipped
					LPF ~get_description_effect~ RET desc = description END
					PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
						SET $abilities($sort_opcodes(~%opcode%~) ~%count%~ ~%desc%~) = 1
						SET count += 1
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

    SORT_ARRAY_INDICES abilities NUMERICALLY

	PATCH_IF count > 0 BEGIN LPF ~appendSection~ INT_VAR strref = 100010 RET description END END // ~Capacités d'équipement~

    PATCH_PHP_EACH ~abilities~ AS data => value BEGIN
		LPF ~appendProperty~ STR_VAR name = EVAL ~%data_2%~ RET description END
    END
END