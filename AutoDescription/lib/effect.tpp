DEFINE_PATCH_MACRO ~read_effect_vars~ BEGIN
	READ_SHORT (offset) opcode
	READ_BYTE  (offset + EFF_target) target
	READ_BYTE  (offset + EFF_power) power
	READ_LONG  (offset + EFF_parameter1) parameter1
	READ_LONG  (offset + EFF_parameter2) parameter2
	READ_BYTE  (offset + EFF_timing_mode) timingMode
	READ_BYTE  (offset + EFF_resistance) resistance
	READ_LONG  (offset + EFF_duration) duration
	READ_BYTE  (offset + EFF_probability1) probability1
	READ_BYTE  (offset + EFF_probability2) probability2
	READ_ASCII (offset + EFF_resref_key) resref
	READ_LONG  (offset + EFF_dice_count) diceCount
	READ_LONG  (offset + EFF_dice_sides) diceSides
	READ_LONG  (offset + EFF_save_type) saveType
	READ_LONG  (offset + EFF_save_bonus) saveBonus
	READ_LONG  (offset + 0x2c) special

	SET parameter3 = 0
	SET parameter4 = 0
	SET resref2 = 0
	SET resref3 = 0

	SET custom_int = 0
	SPRINT custom_str ~~
	SPRINT target_type ~~
	SPRINT complex_value ~~
	SPRINT complex_duration ~~
	SPRINT complex_save ~~
END

DEFINE_PATCH_MACRO ~read_external_effect_vars~ BEGIN
	READ_SHORT EFF2_opcode opcode
	READ_BYTE  EFF2_target target
	READ_BYTE  EFF2_power power
	READ_LONG  EFF2_parameter1 parameter1
	READ_LONG  EFF2_parameter2 parameter2
	READ_BYTE  EFF2_timing timingMode
	READ_LONG  EFF2_duration duration
	READ_BYTE  EFF2_probability1 probability1
	READ_BYTE  EFF2_probability2 probability2
	READ_ASCII EFF2_resource resref
	READ_LONG  EFF2_dice_thrown diceCount
	READ_LONG  EFF2_dice_sides diceSides
	READ_LONG  EFF2_save_type saveType
	READ_LONG  EFF2_save_bonus saveBonus
	READ_LONG  EFF2_stacking_id_tobex special
	READ_LONG  EFF2_resistance resistance
	READ_LONG  EFF2_parameter3 parameter3
	READ_LONG  EFF2_parameter4 parameter4
	READ_ASCII EFF2_resource2 resref2
	READ_ASCII EFF2_resource3 resref3

	READ_LONG  0x54 minLevel
	READ_LONG  0x58 maxLevel

	SET custom_int = 0
	SPRINT custom_str ~~
	SPRINT target_type ~~
	SPRINT complex_value ~~
	SPRINT complex_duration ~~
	SPRINT complex_save ~~
END

DEFINE_PATCH_MACRO ~data_to_vars~ BEGIN
	SET position     = ~%data_0%~
	SET isExternal   = ~%data_1%~
	SET target       = ~%data_2%~
	SET power        = ~%data_3%~
	SET parameter1   = ~%data_4%~
	SET parameter2   = ~%data_5%~
	SET timingMode   = ~%data_6%~
	SET resistance   = ~%data_7%~
	SET duration     = ~%data_8%~
	SET probability  = ~%data_9%~
	SET probability1 = ~%data_10%~
	SET probability2 = ~%data_11%~
	SPRINT resref      ~%data_12%~
	SET diceCount    = ~%data_13%~
	SET diceSides    = ~%data_14%~
	SET saveType     = ~%data_15%~
	SET saveBonus    = ~%data_16%~
	SET special      = ~%data_17%~
	SET parameter3   = ~%data_18%~
	SET parameter4   = ~%data_19%~
	SPRINT resref2     ~%data_20%~
	SPRINT resref3     ~%data_21%~
	SET custom_int   = ~%data_22%~
	SPRINT custom_str  ~%data_23%~
	SET cumulable    = ~%data_24%~
	SPRINT target_exceptions ~%data_25%~
	SPRINT target_type ~%data_26%~
	SPRINT complex_value ~%data_27%~
	SPRINT complex_duration ~%data_28%~
	SPRINT complex_save ~%data_29%~
END

DEFINE_PATCH_MACRO ~data_to_match_vars~ BEGIN
	SET match_opcode       = opcode
	SET match_position     = ~%data_0%~
	SET match_isExternal   = ~%data_1%~
	SET match_target       = ~%data_2%~
	SET match_power        = ~%data_3%~
	SET match_parameter1   = ~%data_4%~
	SET match_parameter2   = ~%data_5%~
	SET match_timingMode   = ~%data_6%~
	SET match_resistance   = ~%data_7%~
	SET match_duration     = ~%data_8%~
	SET match_probability  = ~%data_9%~
	SET match_probability1 = ~%data_10%~
	SET match_probability2 = ~%data_11%~
	SPRINT match_resref      ~%data_12%~
	SET match_diceCount    = ~%data_13%~
	SET match_diceSides    = ~%data_14%~
	SET match_saveType     = ~%data_15%~
	SET match_saveBonus    = ~%data_16%~
	SET match_special      = ~%data_17%~
	SET match_parameter3   = ~%data_18%~
	SET match_parameter4   = ~%data_19%~
	SPRINT match_resref2     ~%data_20%~
	SPRINT match_resref3     ~%data_21%~
	SET match_custom_int   = ~%data_22%~
	SPRINT match_custom_str  ~%data_23%~
	SET match_cumulable    = ~%data_24%~
	SPRINT match_target_exceptions ~%data_25%~
	SPRINT match_target_type ~%data_26%~
	SPRINT match_complex_value ~%data_27%~
	SPRINT match_complex_save ~%data_29%~
END


DEFINE_PATCH_MACRO ~load_feature_effects~
BEGIN
	SET cumulable = 1
	SET position = 0
	SPRINT target_exceptions ~~
	LPM ~clear_opcodes~

    GET_OFFSET_ARRAY offsets ITM_V10_GEN_EFFECTS
    PHP_EACH offsets AS _ => offset BEGIN
        LPM ~load_effect~
    END
END

DEFINE_PATCH_MACRO ~load_extended_effects~
BEGIN
	SET cumulable = 1
	SET position = 0
	SPRINT target_exceptions ~~

	LPM ~clear_opcodes~

	GET_OFFSET_ARRAY2 offsets headerOffset ITM_V10_HEAD_EFFECTS
	PHP_EACH offsets AS _ => offset BEGIN
		LPM ~load_effect~
	END
END

DEFINE_PATCH_MACRO ~load_effect~
BEGIN
	SET isExternal = 0
    LPM ~load_opcode~
END

DEFINE_PATCH_MACRO ~load_opcode~ BEGIN
	READ_SHORT (offset) opcode
	PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
    	LPM ~read_effect_vars~
		SET position += 1
		SET isValid = 1

		// ITM global (equipped) effects: Target is always the wearer, this field isn’t relevant.
		PATCH_IF isItem == 1 AND isSubSpell == 0 AND abilityType == AbilityType_Equipped BEGIN
			SET target = TARGET_FX_self
		END

		LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END
		// Sort lancé par un opcode 333 sans niveau de lancement : ses dégâts sans dés prennent ceux de
		// l'effet (opcode_333_common).
		PATCH_IF opcode == 12 AND diceCount == 0 AND VARIABLE_IS_SET inheritDiceCount AND inheritDiceCount > 0 BEGIN
			SET diceCount = inheritDiceCount
			SET diceSides = inheritDiceSides
		END
		LPM ~opcode_is_valid~

		SPRINT exceptionSplstateName ~~
		PATCH_IF opcode == 318 AND (parameter2 == 76 OR parameter2 == 110 OR parameter2 == 111) BEGIN
			LPF ~get_splstate_name~ INT_VAR strref = 420000 + parameter1 opcode splstate = parameter1 RET exceptionSplstateName = splstateName END
		END
		PATCH_IF isValid == 1 AND opcode == 321 BEGIN
			PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ AND
                    (timingMode != TIMING_duration OR duration != 0) BEGIN // N'empêche rien sans durée
                SET cumulable = 0
                SET isValid = 0
            END
        END
        // Protection probable contre la ressource elle-même sous un état de sort sans nom (pnp_potion : « sous l'effet
        // d'une potion ») : l'exception ne peut pas être nommée ; écrite comme une ligne sous la condition du 326
        // (opcode virtuel 526).
        ELSE PATCH_IF isValid == 1 AND opcode == 318 AND ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ AND probability < 100
                AND (parameter2 == 76 OR parameter2 == 110 OR parameter2 == 111) AND parameter1 != 121 AND ~%exceptionSplstateName%~ STRING_EQUAL ~~ BEGIN
            SET opcode = 526
            SET custom_int = probability
            SET probability1 = 99
            SET probability2 = 0
            SET probability = 100
        END
        ELSE PATCH_IF isValid == 1 AND (opcode == 318 OR opcode == 324) AND ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ AND (parameter1 != 0 OR parameter2 != 0) BEGIN
			SPRINT target_exceptions ~%target_exceptions% %probability1%=>%probability2%;%parameter1%=>%parameter2%~
            SET isValid = 0
		END
        ELSE PATCH_IF isValid == 1 AND opcode == 318 AND NOT ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ BEGIN
            PATCH_IF NOT VARIABLE_IS_SET EVAL ~target_exceptions_%resref%~ BEGIN
                SPRINT EVAL ~target_exceptions_%resref%~ ~~
            END
			SPRINT EVAL ~target_exceptions_%resref%~ EVAL ~%target_exceptions_%resref%% %probability1%=>%probability2%;%parameter1%=>%parameter2%~
            //SET isValid = 0
        END
		// EFF d'un 183 qui protège seulement contre la ressource elle-même (D2WKZM9) : les effets lus après lui sont
		// inefficaces si la cible équipe ce type d'objet ; écrit comme une exception de cible (type 100183).
		ELSE PATCH_IF isValid == 1 AND opcode == 183 BEGIN
			SET effProtectsSource = 0
			PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.eff~ BEGIN
				INNER_PATCH_FILE ~%resref%.eff~ BEGIN
					PATCH_IF BUFFER_LENGTH >= 0x38 BEGIN
						READ_LONG 0x10 effOpcode
						READ_LONG 0x1c effParameter1
						READ_LONG 0x20 effParameter2
						READ_ASCII 0x30 effResref (8) NULL
						PATCH_IF effOpcode == 318 AND effParameter1 == 0 AND effParameter2 == 0 AND ~%effResref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ BEGIN
							SET effProtectsSource = 1
						END
					END
				END
			END
			PATCH_IF effProtectsSource BEGIN
				SPRINT target_exceptions ~%target_exceptions% %probability1%=>%probability2%;%parameter2%=>100183~
				SET isValid = 0
			END
		END
		// TODO: 206 depuis un 177 qui rend innefficace certains effets => RR#WEAR

        PATCH_IF isValid == 1 BEGIN
            PATCH_IF VARIABLE_IS_SET EVAL ~target_exceptions_%resref%~ BEGIN
                SPRINT old_target_exceptions ~%target_exceptions%~
                SPRINT target_exceptions EVAL ~%target_exceptions% %target_exceptions_%resref%%~
                LPM ~add_opcode~
                SPRINT target_exceptions ~%old_target_exceptions%~
            END
            ELSE BEGIN
                LPM ~add_opcode~
            END
        END
    END
END

/* ------------------------------------------------------------------------------------------------------------------ *
 * Supprime les entrées en double.                                                                                    *
 * ATTENTION ! Un effet est unique si la chaîne est la même ET que sa probabilité l'est aussi.                        *
 * TODO: Certains effets peuvent être en doublon ! 2 effets qui ajoutent un bonus de caractéristique peuvent se       *
 * cumuler...                                                                                                         *
 * SET $lines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 1    *
 * ------------------------------------------------------------------------------------------------------------------ */
DEFINE_PATCH_FUNCTION ~get_unique_effects~ RET count RET_ARRAY effects BEGIN
    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~effects~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~seen_effects~ BEGIN END

    SET count = 0

	PATCH_PHP_EACH ~lines~ AS line => value BEGIN
		SPRINT normalizedDescription ~%line_5%~
		TO_LOWER normalizedDescription

		// Clé composée des critères de déduplication actuels.
		SPRINT effectKey ~%line_3%|%line_4%|%normalizedDescription%~

		PATCH_IF NOT VARIABLE_IS_SET $seen_effects(~%effectKey%~) BEGIN
			SET $seen_effects(~%effectKey%~) = 1
			SET $effects(~%line_0%~ ~%line_1%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~) = value
			SET count += 1
		END
	END
END

DEFINE_PATCH_FUNCTION ~group_probability_effects~ RET count RET_ARRAY effects BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~effects~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~probability_effects~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~bounds~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~signatures~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~totals~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~duplicates~ BEGIN END
	PATCH_DEFINE_ARRAY ~ranges~ BEGIN END

	SET mode = use_complex_grouping_of_probability_ranges ? 2 : 1
	SET count = 0
	SET range_count = 0
	// set_opcode_sort ne recalcule `sort` que si forceSort vaut 0
	SET forceSort = 0
	SET range = 0
	SET range_low = ~-1~
	SET range_high = ~-1~

	PATCH_PHP_EACH ~lines~ AS line => value BEGIN
		PATCH_IF line_2 == 100 BEGIN
			SET $effects(~%line_0%~ ~%count%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~) = value
			SET count += 1
		END
		ELSE BEGIN
			LPF ~get_range_key~ INT_VAR probability1 = line_4 probability2 = line_3 RET range_key = rangeKey END
			SET $probability_effects(~%range_key%~ ~%line_0%~ ~%line_1%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~) = value
		END
	END

	SORT_ARRAY_INDICES probability_effects NUMERICALLY

	PATCH_IF mode == 1 BEGIN
		PATCH_PHP_EACH ~probability_effects~ AS line => value BEGIN
			// Les plages du jeu s'arrêtent à 99 : sans plafonnement, 0-100 et 0-99 donneraient deux groupes de même clé
			SET effect_high = line_5
			PATCH_IF effect_high > 99 BEGIN SET effect_high = 99 END

			PATCH_IF line_4 != range_low OR effect_high != range_high BEGIN
				SPRINT range ~%line_0%~
				SET range_count += 1
				SPRINT $ranges(~%range_count%~) ~%range%~
				SET EVAL ~size_%range%~ = 0
				SET range_low = line_4
				SET range_high = effect_high
			END
			SET EVAL ~size_%range%~ += 1
			SET $EVAL ~range_effects_%range%~(~%line_0%~ ~%line_1%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~ ~%line_6%~) = value
		END
	END
	ELSE BEGIN
		// Une plage vide (bas > haut) ou à borne basse négative ne s'active jamais : l'effet est ignoré
		PATCH_PHP_EACH ~probability_effects~ AS line => value BEGIN
			SET effect_low = line_4
			SET effect_high = line_5
			PATCH_IF effect_high > 99 BEGIN SET effect_high = 99 END

			PATCH_IF effect_low >= 0 AND effect_low <= effect_high BEGIN
				SET $bounds(~%effect_low%~) = effect_low
				SET effect_high += 1
				SET $bounds(~%effect_high%~) = effect_high
			END
		END
		SORT_ARRAY_INDICES bounds NUMERICALLY

		// Entre deux bornes consécutives l'ensemble des effets actifs est constant : chaque intervalle forme un groupe
		SET previous_bound = ~-1~
		PATCH_PHP_EACH ~bounds~ AS _ => bound BEGIN
			PATCH_IF previous_bound >= 0 BEGIN
				SET range_low = previous_bound
				SET range_high = bound - 1

				LPF ~get_range_key~ INT_VAR probability1 = range_high probability2 = range_low RET range = rangeKey END
				LPF ~get_probability~ INT_VAR probability1 = range_high probability2 = range_low RET probability END
				SET EVAL ~size_%range%~ = 0

				PATCH_PHP_EACH ~probability_effects~ AS line => value BEGIN
					SET effect_low = line_4
					SET effect_high = line_5
					PATCH_IF effect_high > 99 BEGIN SET effect_high = 99 END

					PATCH_IF effect_low >= 0 AND effect_low <= range_low AND effect_high >= range_high BEGIN
						INNER_PATCH_SAVE line_6 ~%line_6%~ BEGIN
							REPLACE_TEXTUALLY EVALUATE_REGEXP ~^%line_3%%outer_percent%~ ~%probability%%outer_percent%~
						END

						SET EVAL ~size_%range%~ += 1
						SET $EVAL ~range_effects_%range%~(~%range%~ ~%line_1%~ ~%line_2%~ ~%probability%~ ~%range_low%~ ~%range_high%~ ~%line_6%~) = value
					END
				END

				SET range_size = EVAL ~size_%range%~
				PATCH_IF range_size > 0 BEGIN
					SET range_count += 1
					SPRINT $ranges(~%range_count%~) ~%range%~
				END
			END
			SET previous_bound = bound
		END
	END

	// Les segments du mode complexe sont disjoints : les probabilités de groupes identiques s'additionnent sans erreur
	PATCH_IF mode == 2 BEGIN
		PATCH_PHP_EACH ~ranges~ AS _ => range BEGIN
			SPRINT signature ~~
			SET range_probability = 0
			PATCH_PHP_EACH ~range_effects_%range%~ AS line => value BEGIN
				SET range_probability = line_3
				INNER_PATCH_SAVE tail ~%line_6%~ BEGIN
					SPRINT regex @10009 // ~^[0-9]+ % de chance ~
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
				END
				SPRINT signature ~%signature%|%tail%~
			END

			PATCH_IF VARIABLE_IS_SET $signatures(~%signature%~) BEGIN
				SPRINT owner $signatures(~%signature%~)
				SET $totals(~%owner%~) = $totals(~%owner%~) + range_probability
				SET $duplicates(~%range%~) = 1
			END
			ELSE BEGIN
				SPRINT $signatures(~%signature%~) ~%range%~
				SET $totals(~%range%~) = range_probability
			END
		END
	END

	SET group_index = 0
	PATCH_PHP_EACH ~ranges~ AS _ => range BEGIN
		PATCH_IF NOT VARIABLE_IS_SET $duplicates(~%range%~) BEGIN
			SET range_size = EVAL ~size_%range%~

			PATCH_IF range_size == 1 BEGIN
				PATCH_PHP_EACH ~range_effects_%range%~ AS line => value BEGIN
					PATCH_IF VARIABLE_IS_SET $totals(~%range%~) BEGIN
						SET old_probability = line_3
						SET new_probability = $totals(~%range%~)
						PATCH_IF new_probability != old_probability BEGIN
							INNER_PATCH_SAVE line_6 ~%line_6%~ BEGIN
								REPLACE_TEXTUALLY EVALUATE_REGEXP ~^%old_probability%%outer_percent%~ ~%new_probability%%outer_percent%~
							END
							SET line_3 = new_probability
						END
					END
					SET $effects(~%line_1%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~ ~%line_6%~) = value
					SET count += 1
				END
			END
			ELSE BEGIN
				INNER_PATCH_SAVE group_low ~%range%~ BEGIN
					SPRINT regex ~\([0-9][0-9]\)$~
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
				END
				INNER_PATCH_SAVE group_high ~%range%~ BEGIN
					SPRINT regex ~^\([0-9][0-9]\)~
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
				END

				LPF ~get_probability~ INT_VAR probability1 = group_high probability2 = group_low RET probability END
				PATCH_IF VARIABLE_IS_SET $totals(~%range%~) BEGIN
					SET probability = $totals(~%range%~)
				END
				LPM ~set_opcode_sort~
				LPF ~percent_value~ INT_VAR value = EVAL ~%probability%~ RET probability = value END
				SPRINT header_description @101126 // ~%probability% de chance~
				SET sort += group_index * 20 // Laisse une marge de 20 effets par groupe de range...
				SET $effects(~%sort%~ ~%count%~ ~%probability%~ ~%group_low%~ ~%group_high%~ ~%header_description%~) = 1
				SET count += 1

				PATCH_PHP_EACH ~range_effects_%range%~ AS line => value BEGIN
					INNER_PATCH_SAVE line_6 ~%line_6%~ BEGIN
						SPRINT regex @10009 // ~^[0-9]+ % de chance ~
						REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
						SPRINT regex @10019 // ~[0-9]+ % de chance ~
						SPRINT regex ~; %regex%~
						REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~; ~
					END
					SET sort += 1
					SET $effects(~%sort%~ ~%count%~ ~%line_3%~ ~%line_4%~ ~%line_5%~ ~%line_6%~) = value + 2
					SET count += 1
				END
			END
			SET group_index += 1
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_range_key~
	INT_VAR
		probability1 = 0
		probability2 = 0
	RET
		rangeKey
BEGIN
	PATCH_IF STRING_LENGTH ~%probability2%~ == 1 BEGIN
		SPRINT probability2 ~0%probability2%~
	END
	PATCH_IF STRING_LENGTH ~%probability1%~ == 1 BEGIN
		SPRINT probability1 ~0%probability1%~
	END
	PATCH_IF probability1 == 100 BEGIN
		SET probability1 = 99
	END
	SPRINT rangeKey ~%probability2%%probability1%~
END

/**
 * Permettrait de remplacer certains effets par d'autres.
 * Typiquement, pour le cas de l'opcode 177, afin que l'effet vers lequel il pointe puisse être pris en compte dans la
 * phase de regroupement.
 */
DEFINE_PATCH_MACRO ~replace_effects~ BEGIN
	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
			SPRINT dispatch_replace ~opcode_%opcode%_replace~
			PATCH_TRY LPM ~%dispatch_replace%~ WITH DEFAULT
				PATCH_IF show_swallowed_errors BEGIN LPF ~log_swallowed_error~ STR_VAR name = ~%dispatch_replace%~ error = ~%ERROR_MESSAGE%~ END END
			END
		END
	END
END

/**
 * L'éventuelle macro de filtre va servir à désactiver certains effets pour diverses raisons :
 * - Ils s'annulent entre eux
 * - Ils ne peuvent pas se stack
 */
DEFINE_PATCH_MACRO ~filter_effects~ BEGIN
	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
			SPRINT dispatch_filter ~opcode_%opcode%_filter~
			PATCH_TRY LPM ~%dispatch_filter%~ WITH DEFAULT
				PATCH_IF show_swallowed_errors BEGIN LPF ~log_swallowed_error~ STR_VAR name = ~%dispatch_filter%~ error = ~%ERROR_MESSAGE%~ END END
			END
		END
	END
END

/**
 * L'éventuelle macro qui va servir à regrouper certains effets.
 * Techniquement, lorsque des effets sont regroupés, ils doivent être désactivés dans le tableau principal, et une
 * nouvelle entrée doit être créée, contenant les données qui seront traitées par les macros habituelles.
 * Si la chaîne générée est trop différente, il est tout à fait possible de faire en sorte d'appeler une macro d'un
 * opcode imaginaire, qui va se charger de générer la chaîne spécifiquement pour le regroupement.
 * Si des paramètres spécifiques doivent être passés, il y a toute la place dans les variables présentes
 * Attention, seules les variables resref, resref2 et resref3 peuvent accueillir une chaîne.
 */
DEFINE_PATCH_MACRO ~group_effects~ BEGIN
	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 1 AND VARIABLE_IS_SET $merge_duplicate_kinds(~%opcode%~) BEGIN
			LPM ~merge_duplicate_effects~
		END
	END
	PATCH_IF enable_shrinkage == 1 BEGIN
		PATCH_PHP_EACH opcodes AS opcode => count BEGIN
			PATCH_IF count > 1 BEGIN
				LPM ~group_duration_range~
			END
			PATCH_IF $opcodes(~%opcode%~) > 0 BEGIN
				LPM ~opcode_group_by_target~
				LPM ~opcode_group_by_duration~
				SPRINT dispatch_group ~opcode_%opcode%_group~
				PATCH_TRY LPM ~%dispatch_group%~ WITH DEFAULT
					PATCH_IF show_swallowed_errors BEGIN LPF ~log_swallowed_error~ STR_VAR name = ~%dispatch_group%~ error = ~%ERROR_MESSAGE%~ END END
				END
			END
		END
		// Second passe, pour les regroupements qui peuvent être affectés par le précécent regroupement.
		// Notamment par la suppression d'opcodes.
		PATCH_PHP_EACH opcodes AS opcode => count BEGIN
			PATCH_IF count > 0 BEGIN
				SPRINT dispatch_post_group ~opcode_%opcode%_post_group~
				PATCH_TRY LPM ~%dispatch_post_group%~ WITH DEFAULT
					PATCH_IF show_swallowed_errors BEGIN LPF ~log_swallowed_error~ STR_VAR name = ~%dispatch_post_group%~ error = ~%ERROR_MESSAGE%~ END END
				END
			END
		END
	END
END

/**
 * Deux effets identiques de l'opcode courant (puissance et résistance mises à part) écrivent la même ligne,
 * que get_unique_effects ne garde qu'une fois, alors que le jeu applique les deux : le second est réuni au
 * premier, selon la règle de merge_duplicate_kinds : ajouts additionnés, pourcentages multipliés, valeur fixée
 * gardée une fois. Les attaques par round s'additionnent en demi-attaques (6 à 10 valent 0,5 à 4,5) ; un total
 * que parameter1 ne sait pas écrire, ou un retrait d'attaques, laisse les deux effets. Le tableau de l'opcode
 * est réécrit dans son ordre.
 */
DEFINE_PATCH_MACRO ~merge_duplicate_effects~ BEGIN
	LOCAL_SPRINT mergeKind $merge_duplicate_kinds(~%opcode%~)
	// Marque propre à cet appel : vider un tableau ne défait pas les éléments que VARIABLE_IS_SET teste.
	SET mergePass = VARIABLE_IS_SET mergePass ? mergePass + 1 : 1
	CLEAR_ARRAY ~mergeEffects~
	SET mergeCount = 0
	SET mergeAny = 0
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		SPRINT mergeMode ~%data_5%~
		PATCH_IF ~%mergeKind%~ STRING_EQUAL ~ADD_ANY~ OR ~%mergeKind%~ STRING_EQUAL ~ADD_EE~ BEGIN
			SPRINT mergeMode ~*~
		END
		SPRINT mergeKey ~%data_1%|%data_2%|%data_4%|%mergeMode%|%data_6%|%data_8%|%data_9%|%data_10%|%data_11%|%data_12%|%data_13%|%data_14%|%data_15%|%data_16%|%data_17%~
		SPRINT mergeKey ~%mergeKey%|%data_18%|%data_19%|%data_20%|%data_21%|%data_22%|%data_23%|%data_24%|%data_25%|%data_26%|%data_27%|%data_28%|%data_29%~
		PATCH_IF NOT VARIABLE_IS_SET $mergeFirst(~%mergePass% %mergeKey%~) BEGIN
			SET $mergeFirst(~%mergePass% %mergeKey%~) = data_0
			SET $mergeValue(~%mergePass% %data_0%~) = data_4
		END
		ELSE BEGIN
			SET mergeFirstPosition = $mergeFirst(~%mergePass% %mergeKey%~)
			SET mergeTotal = $mergeValue(~%mergePass% %mergeFirstPosition%~)
			SET mergeMode = data_5
			SET mergeAction = 0 // 0 : effet gardé une fois ; 1 : ajout ; 2 : pourcentage ; 3 : les deux gardés
			PATCH_IF ~%mergeKind%~ STRING_EQUAL ~ADD~ OR ~%mergeKind%~ STRING_EQUAL ~ADD_ANY~ OR (~%mergeKind%~ STRING_EQUAL ~ADD_EE~ AND is_ee) BEGIN
				SET mergeAction = 1
			END
			ELSE PATCH_IF ~%mergeKind%~ STRING_EQUAL ~AC~ BEGIN
				SET mergeAction = (mergeMode == 16) ? 3 : 1
			END
			ELSE PATCH_IF ~%mergeKind%~ STRING_EQUAL ~HP~ BEGIN
				SET mergeAction = (mergeMode == 0 OR mergeMode == 3) ? 1 : ((mergeMode == 2 OR mergeMode == 5) ? 2 : 0)
			END
			ELSE PATCH_IF ~%mergeKind%~ STRING_EQUAL ~MODE~ OR ~%mergeKind%~ STRING_EQUAL ~PARTY~ OR ~%mergeKind%~ STRING_EQUAL ~APR~ BEGIN
				PATCH_IF ~%mergeKind%~ STRING_EQUAL ~PARTY~ AND is_ee AND mergeMode >= 3 AND mergeMode <= 5 BEGIN
					SET mergeMode -= 3
				END
				SET mergeAction = (mergeMode == 0) ? 1 : ((mergeMode == 2) ? 2 : 0)
				PATCH_IF mergeMode == 3 AND is_ee AND (opcode == 325 OR (opcode >= 33 AND opcode <= 37)) BEGIN
					SET mergeAction = 1
				END
			END
			PATCH_IF mergeAction == 1 AND ~%mergeKind%~ STRING_EQUAL ~APR~ BEGIN
				SET mergeHalves = ((mergeTotal <= 5) ? 2 * mergeTotal : 2 * (mergeTotal - 5) - 1) + ((data_4 <= 5) ? 2 * data_4 : 2 * (data_4 - 5) - 1)
				SET mergeTotal = ((mergeHalves MODULO 2) == 0) ? mergeHalves / 2 : (mergeHalves + 1) / 2 + 5
				PATCH_IF data_4 < 0 OR ((mergeHalves MODULO 2) == 0 AND mergeTotal > 5) OR ((mergeHalves MODULO 2) == 1 AND mergeTotal > 10) BEGIN
					SET mergeAction = 3
				END
			END
			ELSE PATCH_IF mergeAction == 1 BEGIN
				SET mergeTotal += data_4
			END
			ELSE PATCH_IF mergeAction == 2 BEGIN
				SET mergeTotal = mergeTotal * data_4 / 100
			END
			PATCH_IF mergeAction != 3 BEGIN
				SET $mergeValue(~%mergePass% %mergeFirstPosition%~) = mergeTotal
				SET $mergeDropped(~%mergePass% %data_0%~) = 1
				SET mergeAny = 1
			END
		END
	END
	PATCH_IF mergeAny BEGIN
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			PATCH_IF NOT VARIABLE_IS_SET $mergeDropped(~%mergePass% %data_0%~) BEGIN
				PATCH_IF VARIABLE_IS_SET $mergeValue(~%mergePass% %data_0%~) BEGIN
					SPRINT data_4 $mergeValue(~%mergePass% %data_0%~)
				END
				SET $mergeEffects(~%data_0%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~ ~%data_6%~ ~%data_7%~ ~%data_8%~ ~%data_9%~ ~%data_10%~ ~%data_11%~ ~%data_12%~ ~%data_13%~ ~%data_14%~ ~%data_15%~ ~%data_16%~ ~%data_17%~ ~%data_18%~ ~%data_19%~ ~%data_20%~ ~%data_21%~ ~%data_22%~ ~%data_23%~ ~%data_24%~ ~%data_25%~ ~%data_26%~ ~%data_27%~ ~%data_28%~ ~%data_29%~) = 1
				SET mergeCount += 1
			END
		END
		CLEAR_ARRAY ~opcodes_%opcode%~
		PATCH_PHP_EACH ~mergeEffects~ AS data => _ BEGIN
			SET $EVAL ~opcodes_%opcode%~(~%data_0%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~ ~%data_6%~ ~%data_7%~ ~%data_8%~ ~%data_9%~ ~%data_10%~ ~%data_11%~ ~%data_12%~ ~%data_13%~ ~%data_14%~ ~%data_15%~ ~%data_16%~ ~%data_17%~ ~%data_18%~ ~%data_19%~ ~%data_20%~ ~%data_21%~ ~%data_22%~ ~%data_23%~ ~%data_24%~ ~%data_25%~ ~%data_26%~ ~%data_27%~ ~%data_28%~ ~%data_29%~) = 1
		END
		SET $opcodes(~%opcode%~) = mergeCount
	END
END

DEFINE_PATCH_MACRO ~opcode_group_generic~ BEGIN
    // Besoin d'un tableau contenant les valeurs qui DOIVENT rester identiques
    // Besoin d'un tableau contenant les valeurs qui PEUVENT être différentes
    // Générer une clé pour les valeurs identiques
    // La position des lignes aux valeurs identiques est enregistrée dans un tableau
    // Si ce tableau a une valeur de plus de 1, un regroupement est possible !
END

/**
 * Valeurs tirées au sort : le jeu tire un seul nombre de 0 à 99 pour les effets d'une capacité ; des effets de
 * l'opcode courant semblables à leur valeur (parameter1) et à leur probabilité près, dont les plages sont
 * contiguës et disjointes, donnent donc une seule de ces valeurs. Ils n'en font qu'un, sur l'union de leurs
 * plages, sa valeur « entre X et Y » (texte rangeStrref) dans custom_str. Les valeurs sont écrites comme
 * équiprobables : les écarts d'arrondi des plages (11 %, 10 %… 9 %) sont acceptés, enable_shrinkage à 0 les
 * détaille. rangeEligibleMacro (facultative) écarte un effet en mettant rangeEligible à 0 ; rangeTextMacro
 * (facultative) écrit custom_str d'après amountMin et amountMax à la place du texte rangeStrref.
 */
DEFINE_PATCH_MACRO ~group_value_range~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~rangePositions~ BEGIN END
	// CLEAR_ARRAY ne supprime pas les variables rangeChecked_<position> : chaque appel marque les effets vus de
	// son propre numéro.
	SET rangePass = VARIABLE_IS_SET rangePass ? rangePass + 1 : 1
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET rangeEligible = parameter1 > 0 AND ~%custom_str%~ STRING_EQUAL ~~
			AND NOT (VARIABLE_IS_SET $rangeChecked(~%position%~) AND $rangeChecked(~%position%~) == rangePass)
		PATCH_IF rangeEligible AND NOT ~%rangeEligibleMacro%~ STRING_EQUAL ~~ BEGIN
			LPM ~%rangeEligibleMacro%~
		END
		PATCH_IF rangeEligible BEGIN
			SET $rangeChecked(~%position%~) = rangePass
			CLEAR_ARRAY rangePositions
			SET $rangePositions(~%position%~) = 1
			SET rangePosition = position
			SET amountMin = parameter1
			SET amountMax = parameter1
			SET rangeLow = probability2
			SET rangeHigh = probability1 > 99 ? 99 : probability1
			LPF ~get_probability~ INT_VAR probability1 probability2 RET rangeTotal = probability END
			SET rangeCount = 1
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_match_vars~
				PATCH_IF match_parameter1 > 0 AND NOT (VARIABLE_IS_SET $rangeChecked(~%match_position%~) AND $rangeChecked(~%match_position%~) == rangePass) BEGIN
					LPM ~opcode_match_value_range~
					PATCH_IF match == 1 BEGIN
						SET $rangeChecked(~%match_position%~) = rangePass
						SET $rangePositions(~%match_position%~) = 1
						SET rangeCount += 1
						SET amountMin = match_parameter1 < amountMin ? match_parameter1 : amountMin
						SET amountMax = match_parameter1 > amountMax ? match_parameter1 : amountMax
						SET rangeLow = match_probability2 < rangeLow ? match_probability2 : rangeLow
						SET rangeHigh = match_probability1 > rangeHigh ? (match_probability1 > 99 ? 99 : match_probability1) : rangeHigh
						LPF ~get_probability~ INT_VAR probability1 = match_probability1 probability2 = match_probability2 RET matchProbability = probability END
						SET rangeTotal += matchProbability
					END
				END
			END
			// Plages disjointes et sans trou : leur somme est la largeur de leur union.
			PATCH_IF rangeCount > 1 AND rangeTotal == rangeHigh - rangeLow + 1 BEGIN
				PATCH_PHP_EACH rangePositions AS rangeDeleted => _ BEGIN
					LPF ~delete_opcode~
						INT_VAR opcode match_position = rangeDeleted
						RET $opcodes(~%opcode%~) = count
						RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
					END
				END
				// Bug où il reste toujours un item dans le tableau si c'était le dernier
				PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
					CLEAR_ARRAY ~opcodes_%opcode%~
				END
				PATCH_IF ~%rangeTextMacro%~ STRING_EQUAL ~~ BEGIN
					LPF ~getTranslation~ INT_VAR strref = rangeStrref opcode RET custom_str = string END
				END
				ELSE BEGIN
					LPM ~%rangeTextMacro%~
				END
				SET position = rangePosition
				SET probability1 = rangeHigh
				SET probability2 = rangeLow
				SET probability = rangeTotal
				LPM ~add_opcode~
			END
		END
	END
END

DEFINE_PATCH_MACRO ~group_duration_range~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~durationRangePositions~ BEGIN END
	SET durationRangePass = VARIABLE_IS_SET durationRangePass ? durationRangePass + 1 : 1
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF timingMode == TIMING_duration AND duration > 0 AND probability < 100 AND ~%complex_duration%~ STRING_EQUAL ~~
				AND NOT (VARIABLE_IS_SET $durationRangeChecked(~%position%~) AND $durationRangeChecked(~%position%~) == durationRangePass) BEGIN
			SET $durationRangeChecked(~%position%~) = durationRangePass
			CLEAR_ARRAY durationRangePositions
			SET $durationRangePositions(~%position%~) = probability
			SET rangePosition = position
			SET unitDuration = duration
			SET maxDuration = duration
			SET sumDuration = duration
			SET rangeLow = probability2
			SET rangeHigh = probability1 > 99 ? 99 : probability1
			SET rangeTotal = probability
			SET rangeCount = 1
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_match_vars~
				PATCH_IF match_duration > 0 AND NOT (VARIABLE_IS_SET $durationRangeChecked(~%match_position%~) AND $durationRangeChecked(~%match_position%~) == durationRangePass) BEGIN
					LPM ~opcode_match_duration_range~
					PATCH_IF match == 1 BEGIN
						SET $durationRangeChecked(~%match_position%~) = durationRangePass
						SET $durationRangePositions(~%match_position%~) = match_probability
						SET rangeCount += 1
						SET unitDuration = match_duration < unitDuration ? match_duration : unitDuration
						SET maxDuration = match_duration > maxDuration ? match_duration : maxDuration
						SET sumDuration += match_duration
						SET rangeLow = match_probability2 < rangeLow ? match_probability2 : rangeLow
						SET rangeHigh = match_probability1 > rangeHigh ? (match_probability1 > 99 ? 99 : match_probability1) : rangeHigh
						SET rangeTotal += match_probability
					END
				END
			END
			SET isDiceDuration = rangeCount > 1 AND rangeTotal == rangeHigh - rangeLow + 1
				AND maxDuration == unitDuration * rangeCount
				AND sumDuration == unitDuration * rangeCount * (rangeCount + 1) / 2
			PATCH_IF isDiceDuration BEGIN
				PATCH_PHP_EACH durationRangePositions AS _ => slice BEGIN
					PATCH_IF ABS (slice * rangeCount - rangeTotal) > rangeCount BEGIN
						SET isDiceDuration = 0
					END
				END
			END
			PATCH_IF isDiceDuration BEGIN
				SPRINT durationRangeText ~~
				PATCH_PHP_EACH durations AS divisor => unitStrref BEGIN
					PATCH_IF unitDuration MODULO divisor == 0 AND ~%durationRangeText%~ STRING_EQUAL ~~ BEGIN
						PATCH_IF unitDuration == divisor BEGIN
							SPRINT amount ~1d%rangeCount%~
							SET unitStrref += 1
							SPRINT strDuration (AT unitStrref)
							SPRINT durationRangeText @100311 // ~pendant %strDuration%~
						END
						ELSE BEGIN
							SPRINT durationRangeText ~-~
						END
					END
				END
				PATCH_IF NOT ~%durationRangeText%~ STRING_EQUAL ~~ AND NOT ~%durationRangeText%~ STRING_EQUAL ~-~ BEGIN
					PATCH_PHP_EACH durationRangePositions AS rangeDeleted => _ BEGIN
						LPF ~delete_opcode~
							INT_VAR opcode match_position = rangeDeleted
							RET $opcodes(~%opcode%~) = count
							RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
						END
					END
					// Bug où il reste toujours un item dans le tableau si c'était le dernier
					PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
						CLEAR_ARRAY ~opcodes_%opcode%~
					END
					SET position = rangePosition
					SET duration = unitDuration
					SET probability1 = rangeHigh
					SET probability2 = rangeLow
					SET probability = rangeTotal
					SPRINT complex_duration ~%durationRangeText%~
					LPM ~add_opcode~
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_match_duration_range~ BEGIN
	SET match = (
		    match_isExternal   == isExternal
		AND match_target       == target
		AND match_power        == power
		AND match_parameter1   == parameter1
		AND match_parameter2   == parameter2
		AND match_timingMode   == timingMode
		AND match_resistance   == resistance
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
		// Durée complexe de l'effet comparé, que data_to_match_vars ne lit pas.
		AND ~%data_28%~ STRING_EQUAL ~~
	)
END

DEFINE_PATCH_MACRO ~opcode_match_value_range~ BEGIN
	SET match = (
		    match_isExternal   == isExternal
		AND match_target       == target
		AND match_power        == power
		AND match_parameter2   == parameter2
		AND match_duration     == duration
		AND match_timingMode   == timingMode
		AND match_resistance   == resistance
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

DEFINE_PATCH_FUNCTION ~has_opcode~
	INT_VAR
		opcode = 0

		match_opcode       = 0
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
		match_macro      = ~~
	RET
		hasOpcode
BEGIN
	SET hasOpcode = 0
	PATCH_IF VARIABLE_IS_SET $opcodes(~%opcode%~) AND $opcodes(~%opcode%~) > 0 BEGIN
	    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
	    	PATCH_IF hasOpcode == 0 BEGIN
				LPM ~data_to_vars~
				LPM ~%match_macro%~
				PATCH_IF match == 1 BEGIN
					SET hasOpcode = 1
				END
			END
	    END
	END
END

DEFINE_PATCH_MACRO ~add_opcode~ BEGIN
	PATCH_IF NOT VARIABLE_IS_SET $opcodes(~%opcode%~) BEGIN
		SET $opcodes(~%opcode%~) = 1
	END
	ELSE BEGIN
		SET $opcodes(~%opcode%~) += 1
	END
	SET $EVAL ~opcodes_%opcode%~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~ ~%complex_duration%~ ~%complex_save%~) = 1
END

DEFINE_PATCH_FUNCTION ~delete_opcode~
	INT_VAR
		opcode = 0
		match_position = ~-1~

		match_opcode       = 0
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
		match_macro      = ~opcode_match_position~
	RET
		count
	RET_ARRAY
		opcodes_xx
BEGIN
	// Tableau qui sera retourné, doit être une copie de l'ensemble du tableau qu'on désire modifier
	// Sauf que je ne sais pas coment copier facilement un tableau dans une autre variable donc je doit itérer sur
	// l'ensemble du taleau sur lequel on doit travailler...
	PATCH_DEFINE_ARRAY opcodes_xx BEGIN END

	SET count = 0

	PATCH_IF VARIABLE_IS_SET $opcodes(~%opcode%~) AND $opcodes(~%opcode%~) > 0 BEGIN
	    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
	        LPM ~data_to_vars~
			LPM ~%match_macro%~
			PATCH_IF NOT match BEGIN
				SET count += 1
		        SET $opcodes_xx(~%data_0%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~ ~%data_6%~ ~%data_7%~ ~%data_8%~ ~%data_9%~ ~%data_10%~ ~%data_11%~ ~%data_12%~ ~%data_13%~ ~%data_14%~ ~%data_15%~ ~%data_16%~ ~%data_17%~ ~%data_18%~ ~%data_19%~ ~%data_20%~ ~%data_21%~ ~%data_22%~ ~%data_23%~ ~%data_24%~ ~%data_25%~ ~%data_26%~ ~%data_27%~ ~%data_28%~ ~%data_29%~) = 1
	        END
	    END
	END
	SET $opcodes(~%opcode%~) = count
END

DEFINE_PATCH_MACRO ~delete_opcode~ BEGIN
    LPF ~delete_opcode~
        INT_VAR opcode = opcode_to_delete match_position = position_to_delete
        RET $opcodes(~%opcode_to_delete%~) = count
        RET_ARRAY EVAL ~opcodes_%opcode_to_delete%~ = opcodes_xx
    END
    // Bug où il reste toujours un item dans le tableau si c'était le dernier
    // N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
    PATCH_IF $opcodes(~%opcode_to_delete%~) == 0 BEGIN
        CLEAR_ARRAY ~opcodes_%opcode_to_delete%~
    END
END

DEFINE_PATCH_FUNCTION ~get_opcode_by_position~
	INT_VAR
		opcode = 0
		match_position = 0
	RET
		found
		position
		isExternal
		target
		power
		parameter1
		parameter2
		timingMode
		resistance
		duration
		probability
		probability1
		probability2
		resref
		diceCount
		diceSides
		saveType
		saveBonus
		special
		parameter3
		parameter4
		resref2
		resref3
		custom_int
		custom_str
BEGIN
	SET found        = 0
	SET position     = 0
	SET isExternal   = 0
	SET target       = 0
	SET power        = 0
	SET parameter1   = 0
	SET parameter2   = 0
	SET timingMode   = 0
	SET resistance   = 0
	SET duration     = 0
	SET probability  = 0
	SET probability1 = 0
	SET probability2 = 0
	SPRINT resref      ~~
	SET diceCount    = 0
	SET diceSides    = 0
	SET saveType     = 0
	SET saveBonus    = 0
	SET special      = 0
	SET parameter3   = 0
	SET parameter4   = 0
	SPRINT resref2     ~~
	SPRINT resref3     ~~
	SET custom_int   = 0
	SPRINT custom_str  ~~
	PATCH_IF VARIABLE_IS_SET $opcodes(~%opcode%~) AND $opcodes(~%opcode%~) > 0 BEGIN
	    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
	        PATCH_IF found == 0 BEGIN
		        LPM ~data_to_vars~
				PATCH_IF position == match_position BEGIN
					SET found = 1
		        END
	        END
	    END
	END
END

DEFINE_PATCH_FUNCTION ~get_opcode_position~
	INT_VAR
		opcode = 0
		match_position     = 0
		match_opcode       = 0
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
		match_macro      = ~~
		// Type de créature (177) de l'effet cherché, comparé par les macros qui le lisent.
		match_target_type = ~~
	RET
		position
BEGIN
	SET found = 0
	SET return = ~-1~
	PATCH_IF VARIABLE_IS_SET $opcodes(~%opcode%~) AND $opcodes(~%opcode%~) > 0 BEGIN
	    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
	        PATCH_IF found == 0 BEGIN
		        LPM ~data_to_vars~
				LPM ~%match_macro%~
				PATCH_IF match BEGIN
		            SET return = position
		            SET found = 1
		        END
	        END
	    END
	END
	SET position = return
END

DEFINE_PATCH_FUNCTION ~get_effect_description~
	INT_VAR
		resetTarget = 0
		forceTarget = 0
		ignoreDuration = 0
		ignoreSavingThrow = 0
		projectile = 0
		projectileTarget = 0
		projectileTargetNumber = 0
		omitDefaultTarget = 0
	RET
		description
		sort
		saveAdded
		ignoreDuration
BEGIN
	SET isValid = 1
	SET saveAdded = 0
	SET saveForHalf = 0
	SET sort = 0
	SET forceSort = 0

	SPRINT condition ~~
	SPRINT method ~~
	SPRINT description ~~
	SPRINT opcode_target ~~

	PATCH_TRY
		PATCH_IF target == TARGET_FX_self OR target == TARGET_FX_original_caster BEGIN
			SPRINT opcode_target ~_self~
			PATCH_IF forceTarget != 1 OR NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
				PATCH_IF isSpell BEGIN
					SPRINT theTarget   @102475 // ~le lanceur~
					SPRINT ofTheTarget @102476 // ~du lanceur~
					SPRINT toTheTarget @102477 // ~au lanceur~
				END
				ELSE PATCH_IF VARIABLE_IS_SET itemType AND itemType == ITM_TYPE_potion BEGIN
					SPRINT theTarget   @102451 // ~le buveur~
					SPRINT ofTheTarget @102452 // ~du buveur~
					SPRINT toTheTarget @102453 // ~au buveur~
				END
				ELSE BEGIN
					SPRINT theTarget   @102472 // ~le porteur~
					SPRINT ofTheTarget @101086 // ~du porteur~
					SPRINT toTheTarget @101180 // ~au porteur~
				END
			END
		END
		ELSE PATCH_IF target == TARGET_FX_preset BEGIN
			SPRINT opcode_target ~_target~
			PATCH_IF forceTarget == 0 OR NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
				SPRINT theTarget   @102471 // ~la cible~
				SPRINT ofTheTarget @101085 // ~de la cible~
				SPRINT toTheTarget @101181 // ~à la cible~
			END
		END
		// TARGET_FX_party : membre de groupe de CHARNAME
		// TARGET_FX_everyone_match_specific_caster: membre du groupe du lanceur de sort
		ELSE PATCH_IF target == TARGET_FX_party OR target == TARGET_FX_everyone_match_specific_caster BEGIN
			SPRINT opcode_target ~_target~
			PATCH_IF forceTarget == 0 OR NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
				SPRINT theTarget   @102473 // ~les membres du groupe~
				SPRINT ofTheTarget @101088 // ~des membres du groupe~
				SPRINT toTheTarget @101182 // ~aux membres du groupe~
			END
		END
		ELSE PATCH_IF target == TARGET_FX_everyone BEGIN
			SPRINT opcode_target ~_target~
			PATCH_IF forceTarget == 0 OR NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
				SPRINT theTarget   @102474 // ~les créatures dans la zone d'effet~
				SPRINT ofTheTarget @101089 // ~des créatures dans la zone d'effet~
				SPRINT toTheTarget @101190 // ~aux créatures dans la zone d'effet~
			END
		END
		ELSE PATCH_IF target == TARGET_FX_everyone_except_party BEGIN
			SPRINT opcode_target ~_target~
			PATCH_IF forceTarget == 0 OR NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
				SPRINT theTarget   @101191 // ~les créatures non membres du groupe~
				SPRINT ofTheTarget @101192 // ~des créatures non membres du groupe~
				SPRINT toTheTarget @101193 // ~aux créatures non membres du groupe~
			END
		END
		ELSE PATCH_IF target == TARGET_FX_everyone_except_self BEGIN
			SPRINT opcode_target ~_target~
			PATCH_IF forceTarget == 0 OR NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
				SPRINT theTarget   @101194 // ~les autres créatures dans la zone d'effet~
				SPRINT ofTheTarget @101195 // ~des autres créatures dans la zone d'effet~
				SPRINT toTheTarget @101196 // ~aux autres créatures dans la zone d'effet~
			END
		END

		LPM ~opcode_set_target_strings~

		PATCH_IF NOT ~%opcode_target%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF projectile > 1 BEGIN
				// Exception du lanceur : l'effet ne le touche pas.
				SET sourceExcluded = INDEX (CASE_SENSITIVE EVALUATE_REGEXP ~;-?[0-9]+=>43 ~ ~%target_exceptions% ~) >= 0
				LPF ~get_target_by_projectile~ INT_VAR projectile target = projectileTarget targetNumber = projectileTargetNumber sourceExcluded STR_VAR theTarget ofTheTarget toTheTarget RET theTarget ofTheTarget toTheTarget END
			END
			// Après la zone du projectile, qui remplace les chaînes de la cible : sinon la restriction de
			// niveau disparaît (WAND13 : « Tue instantanément les créatures dans un rayon de 4,5 mètres »).
			LPM ~set_self_level_text~
			LPM ~add_target_level~
			SET thisOpcode = opcode
			PATCH_IF probability >= 100 BEGIN
				SPRINT method ~opcode%opcode_target%_%opcode%~
				LPM ~%method%~
				LPM ~set_opcode_sort~
			END
			ELSE BEGIN
				SPRINT method ~opcode%opcode_target%_probability_%opcode%~
				LPM ~%method%~
				LPM ~set_opcode_sort~
				PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
                    INNER_PATCH_SAVE description ~%description%~ BEGIN
                        REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~%crlf%  ~
                    END
					LPF ~percent_value~ INT_VAR value = EVAL ~%probability%~ RET probability = value END
					// Description de plusieurs lignes (sort lancé par un 146 probable) : titre sans espace final.
					PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~%crlf%~ ~%description%~) == 0 BEGIN
						SPRINT probabilityTitle @101126 // ~%probability% de chances~
						SPRINT description ~%probabilityTitle%%description%~
					END
					ELSE BEGIN
						SPRINT description @101125 // ~%probability% de chances %description%~
					END
					// Effet d'un EFF maudit : « Malédiction : 20 % de chances d'aveugler la cible ».
					PATCH_IF thisOpcode == 283 BEGIN
						SPRINT curseName @12830001 // ~Malédiction~
						SPRINT description ~%curseName%%colon%%description%~
					END
				END
			END
			PATCH_IF omitDefaultTarget AND enable_shrinkage AND target == TARGET_FX_preset BEGIN
				LPM ~omit_default_target~
			END
			SET opcode = thisOpcode

			LPM ~add_condition~
			LPM ~add_duration~
			LPM ~add_save~
			LPM ~add_cumulable~
			LPM ~add_only_for~
			LPM ~add_self_level~
			LPM ~add_target_exceptions~
			LPF ~collapse_spaces~ STR_VAR text = EVAL ~%description%~ RET description = text END
		END
		ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Unknow target : %target% ~ END
		END
	WITH
		~Failure("Unknown macro: \%method%")~
		BEGIN
			LPF ~add_log_warning~ STR_VAR message = ~FAILURE: Unknown macro: %method%~ END
			SET $opcodes_to_code(~%opcode%~) = 1
		END
		DEFAULT
			LPF ~add_log_warning~ STR_VAR message = ~FAILURE: opcode %opcode%: %ERROR_MESSAGE%~ END
			PATCH_FAIL ~Opcode %opcode%: %ERROR_MESSAGE%~
	END
END

// Retire la cible par défaut « à la cible » de la description d'une ligne de capacités de combat.
DEFINE_PATCH_MACRO ~omit_default_target~ BEGIN
	SPRINT defaultToTheTarget @101181 // ~à la cible~
	SPRINT wearerName @102472 // ~le porteur~
	SPRINT ofTheWearer @101086 // ~du porteur~
	SPRINT toTheWearer @101180 // ~au porteur~
	SPRINT omittedTarget ~ %toTheTarget%~
	SET omittedStart = STRING_LENGTH ~%description%~ - STRING_LENGTH ~%omittedTarget%~
	PATCH_IF ~%toTheTarget%~ STRING_EQUAL ~%defaultToTheTarget%~ AND omittedStart > 0 BEGIN
		PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~%omittedTarget%~ ~%description%~ omittedStart) == omittedStart
				AND INDEX (CASE_SENSITIVE EXACT_MATCH ~%crlf%~ ~%description%~) < 0
				AND INDEX (CASE_SENSITIVE EXACT_MATCH ~%wearerName%~ ~%description%~) < 0
				AND INDEX (CASE_SENSITIVE EXACT_MATCH ~%ofTheWearer%~ ~%description%~) < 0
				AND INDEX (CASE_SENSITIVE EXACT_MATCH ~%toTheWearer%~ ~%description%~) < 0 BEGIN
			INNER_PATCH_SAVE description ~%description%~ BEGIN
				DELETE_BYTES omittedStart (STRING_LENGTH ~%omittedTarget%~)
			END
		END
	END
END
