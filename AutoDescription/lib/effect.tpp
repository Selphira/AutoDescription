DEFINE_PATCH_FUNCTION ~get_eff_effect_description~
	STR_VAR
		file = ~~
	RET
		description
BEGIN
	INNER_PATCH_FILE ~%file%.eff~ BEGIN
	END
END

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

	SET custom_int = 0
	SPRINT custom_str ~~
	SPRINT target_type ~~
	SPRINT complex_value ~~
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
    LPM ~read_effect_vars~
    LPM ~load_opcode~
END

DEFINE_PATCH_MACRO ~load_external_effect~
BEGIN
	SET isExternal = 1
    LPM ~read_external_effect_vars~
    LPM ~load_opcode~
END

DEFINE_PATCH_MACRO ~load_opcode~ BEGIN
	PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
		SET position += 1
		SET isValid = 1

		// ITM global (equipped) effects: Target is always the wearer, this field isn’t relevant.
		PATCH_IF target == TARGET_FX_none AND ~%SOURCE_EXT%~ STRING_EQUAL_CASE ~ITM~ BEGIN
			SET target = TARGET_FX_self
		END

		LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END
		LPM ~opcode_is_valid~

		PATCH_IF isValid == 1 AND opcode == 321 BEGIN
			PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ AND
                    (timingMode != TIMING_duration OR duration != 0) BEGIN // N'empêche rien sans durée
                SET cumulable = 0
                SET isValid = 0
            END
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
			SPRINT var_target_exceptions EVAL ~%target_exceptions_%resref%%~
            SET isValid = 0
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
    SET count = 0

	PATCH_PHP_EACH ~lines~ AS line => value BEGIN
		SET found = 0
		PATCH_PHP_EACH effects AS effect => _ BEGIN
			SPRINT tmp1 ~%line_5%~
			SPRINT tmp2 ~%effect_5%~
			TO_LOWER tmp1
			TO_LOWER tmp2

			PATCH_IF ~%tmp1%~ STRING_EQUAL ~%tmp2%~ AND ~%line_3%~ == ~%effect_3%~ AND ~%line_4%~ == ~%effect_4%~ BEGIN
				SET found = 1
			END
		END
		PATCH_IF found == 0 BEGIN
			SET $effects(~%line_0%~ ~%line_1%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~) = value
			SET count += 1
		END
	END
END

DEFINE_PATCH_FUNCTION ~group_probability_effects~ RET count RET_ARRAY effects BEGIN
    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~effects~ BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY ~probability_effects~ BEGIN END
    PATCH_DEFINE_ARRAY ~ranges~ BEGIN END
    PATCH_DEFINE_ARRAY ~count_ranges~ BEGIN END

	SET mode = use_complex_grouping_of_probability_ranges ? 2 : 1
    SET count = 0
    SET count_range = 0
	SET forceSort = 0
	SET range = 0
	SET range_low = ~-1~
	SET range_high = ~-1~

	// On place les effets à probabilité dans un tableau de travail.
	PATCH_PHP_EACH ~lines~ AS line => value BEGIN
		PATCH_IF line_2 == 100 BEGIN
			SET $effects(~%line_0%~ ~%count%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~) = value
			SET count += 1
		END
		ELSE BEGIN
			LPF ~get_range_key~ INT_VAR probability1 = line_4 probability2 = line_3 RET rangeKey END
			SET $probability_effects(~%rangeKey%~ ~%line_0%~ ~%line_1%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~) = value
		END
	END

	SORT_ARRAY_INDICES probability_effects NUMERICALLY

	PATCH_IF mode == 1 BEGIN
		// On regroupe uniquement par range identiques
		PATCH_PHP_EACH ~probability_effects~ AS line => value BEGIN
			PATCH_IF line_4 != range_low OR line_5 != range_high BEGIN
				// On commence un nouveau groupe de range
				SET range = line_0
				SET count_range += 1
				SPRINT $ranges(~%count_range%~) ~%range%~
				SET EVAL ~count_ranges_%range%~ = 0
				SET range_low = line_4
				SET range_high = line_5
			END
			SET EVAL ~count_ranges_%range%~ += 1
			SET $EVAL ~range_effects_%range%~(~%line_0%~ ~%line_1%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~ ~%line_6%~) = value
		END
	END
	ELSE BEGIN
		// Regroupement complexe avec gestion des chevauchements de probabilité
		SET prev_range_low = ~-1~
		SET prev_range_high = ~-1~
		PATCH_PHP_EACH ~probability_effects~ AS line => value BEGIN
			// On commence par déterminer quel sera le range de probabilité
			// On boucle une première fois pour éventuellement diminuer le range haut suite au chevauchement de probabilité d'un autre effet.
			SET range_low = line_4
			SET range_high = line_5

			PATCH_IF prev_range_low != range_low OR prev_range_high != range_high BEGIN
				PATCH_IF prev_range_high > range_low BEGIN
					SET range_low = prev_range_high + 1
				END

				PATCH_PHP_EACH ~probability_effects~ AS line2 => value2 BEGIN
					PATCH_IF prev_range_low != line2_4 OR prev_range_high != line2_5 BEGIN
						PATCH_IF range_low < line2_5 AND range_high > line2_4 BEGIN
							PATCH_IF range_low < line2_4 - 1 AND range_high > line2_4 BEGIN
								SET range_high = line2_4 - 1
							END
						END
					END
				END

				// Ensuite on récupère tous les effets qui se trouvent dans le range caclulé
				// En cas de chevauchement, un même effet se retrouvera dans plusieurs groupes de range.
				PATCH_IF range_low <= range_high BEGIN
					LPF ~get_range_key~ INT_VAR probability1 = range_high probability2 = range_low RET range = rangeKey END
					SET count_range += 1
					SPRINT $ranges(~%count_range%~) ~%range%~
					SET EVAL ~count_ranges_%range%~ = 0

					PATCH_PHP_EACH ~probability_effects~ AS line2 => value2 BEGIN
						PATCH_IF range_low >= line2_4 AND range_high <= line2_5 BEGIN
							LPF ~get_probability~ INT_VAR probability1 = range_high probability2 = range_low RET probability END

							INNER_PATCH_SAVE line2_6 ~%line2_6%~ BEGIN
								REPLACE_TEXTUALLY EVALUATE_REGEXP ~^%line2_3% %~ ~%probability% %~
							END

							SET EVAL ~count_ranges_%range%~ += 1
							SET $EVAL ~range_effects_%range%~(~%range%~ ~%line2_1%~ ~%line2_2%~ ~%probability%~ ~%range_low%~ ~%range_high%~ ~%line2_6%~) = value2
						END
					END
				END
			END

			SET prev_range_low = range_low
			SET prev_range_high = range_high
		END
	END

	SET cpt = 0
	PATCH_IF VARIABLE_IS_SET $ranges(~1~) BEGIN
		SET count = 0
	END
	PATCH_PHP_EACH ~ranges~ AS _ => range BEGIN
		SET countRange = EVAL ~count_ranges_%range%~

		PATCH_IF countRange == 1 BEGIN
			PATCH_PHP_EACH ~range_effects_%range%~ AS line => value BEGIN
				SET $effects(~%line_1%~ ~%line_2%~ ~%line_3%~ ~%line_4%~ ~%line_5%~ ~%line_6%~) = value
				SET count += 1
			END
		END
		ELSE BEGIN
			INNER_PATCH_SAVE probability2 ~%range%~ BEGIN
				SPRINT regex ~\([0-9][0-9]\)$~
				REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
			END
			INNER_PATCH_SAVE probability1 ~%range%~ BEGIN
				SPRINT regex ~^\([0-9][0-9]\)~
				REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
			END

			LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END
			LPM ~set_opcode_sort~
			LPF ~percent_value~ INT_VAR value = EVAL ~%probability%~ RET probability = value END
			SPRINT description @101126 // ~%probability% de chance~
			SET sort += cpt * 20 // Laisse une marge de 20 effets par groupe de range...
			SET $effects(~%sort%~ ~%count%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%description%~) = 1
			SET count += 1

			PATCH_PHP_EACH ~range_effects_%range%~ AS line => value BEGIN
				INNER_PATCH_SAVE line_6 ~%line_6%~ BEGIN
					SPRINT regex @10009 // ~^[0-9]+ % de chance ~
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
				END
				SET sort += 1
				SET $effects(~%sort%~ ~%count%~ ~%line_3%~ ~%line_4%~ ~%line_5%~ ~%line_6%~) = value + 2
				SET count += 1
			END
		END
		SET cpt += 1
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
			PATCH_TRY LPM ~opcode_%opcode%_replace~ WITH DEFAULT END
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
			PATCH_TRY LPM ~opcode_%opcode%_filter~ WITH DEFAULT END
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
	PATCH_IF enable_shrinkage == 1 BEGIN
		PATCH_PHP_EACH opcodes AS opcode => count BEGIN
			PATCH_IF count > 0 BEGIN
				LPM ~opcode_group_by_target~
				LPM ~opcode_group_by_duration~
				PATCH_TRY LPM ~opcode_%opcode%_group~ WITH DEFAULT END
			END
		END
		// Second passe, pour les regroupements qui peuvent être affectés par le précécent regroupement.
		// Notamment par la suppression d'opcodes.
		PATCH_PHP_EACH opcodes AS opcode => count BEGIN
			PATCH_IF count > 0 BEGIN
				PATCH_TRY LPM ~opcode_%opcode%_post_group~ WITH DEFAULT END
			END
		END
	END
END

DEFINE_PATCH_FUNCTION ~has_opcode~
	INT_VAR
		opcode = 0
	STR_VAR
		expression = ~~
	RET
		hasOpcode
BEGIN
	SET hasOpcode = 0
	PATCH_IF VARIABLE_IS_SET $opcodes(~%opcode%~) AND $opcodes(~%opcode%~) > 0 BEGIN
	    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
	        LPM ~data_to_vars~
	        LPF evaluate_expression STR_VAR expression RET value END
	        PATCH_IF value == 1 BEGIN
	            SET hasOpcode = 1
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
	SET $EVAL ~opcodes_%opcode%~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~ ~%custom_int%~ ~%custom_str%~ ~%cumulable%~ ~%target_exceptions%~ ~%target_type%~ ~%complex_value%~) = 1
END

DEFINE_PATCH_FUNCTION ~delete_opcode~
	INT_VAR
		opcode = 0
		match_position = ~-1~
	STR_VAR
		expression = ~~
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
		PATCH_IF match_position >= 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~
				PATCH_IF match_position != position BEGIN
					SET count += 1
			        SET $opcodes_xx(~%data_0%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~ ~%data_6%~ ~%data_7%~ ~%data_8%~ ~%data_9%~ ~%data_10%~ ~%data_11%~ ~%data_12%~ ~%data_13%~ ~%data_14%~ ~%data_15%~ ~%data_16%~ ~%data_17%~ ~%data_18%~ ~%data_19%~ ~%data_20%~ ~%data_21%~ ~%data_22%~ ~%data_23%~ ~%data_24%~ ~%data_25%~ ~%data_26%~ ~%data_27%~) = 1
		        END
		    END
		END
		ELSE BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~
		        LPF evaluate_expression STR_VAR expression RET value END
				PATCH_IF NOT value BEGIN
					SET count += 1
			        SET $opcodes_xx(~%data_0%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~ ~%data_6%~ ~%data_7%~ ~%data_8%~ ~%data_9%~ ~%data_10%~ ~%data_11%~ ~%data_12%~ ~%data_13%~ ~%data_14%~ ~%data_15%~ ~%data_16%~ ~%data_17%~ ~%data_18%~ ~%data_19%~ ~%data_20%~ ~%data_21%~ ~%data_22%~ ~%data_23%~ ~%data_24%~ ~%data_25%~ ~%data_26%~ ~%data_27%~) = 1
		        END
		    END
		END
	END
	SET $opcodes(~%opcode%~) = count
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
	STR_VAR
		expression = ~~
	RET
		position
BEGIN
	SET found = 0
	SET return = ~-1~
	PATCH_IF VARIABLE_IS_SET $opcodes(~%opcode%~) AND $opcodes(~%opcode%~) > 0 BEGIN
	    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
	        PATCH_IF found == 0 BEGIN
		        LPM ~data_to_vars~
		        LPF evaluate_expression STR_VAR expression RET value END
		        PATCH_IF value == 1 BEGIN
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
			PATCH_IF forceTarget == 0 OR NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
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

		PATCH_IF NOT ~%target_type~ STRING_EQUAL ~~ BEGIN
			LPM ~opcode_set_target_strings~
		END

		LPM ~add_target_level~

		PATCH_IF NOT ~%opcode_target%~ STRING_EQUAL ~~ BEGIN
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
					LPF ~percent_value~ INT_VAR value = EVAL ~%probability%~ RET probability = value END
					SPRINT description @101125 // ~%probability% de chances %description%~
				END
			END

			LPM ~add_condition~
			LPM ~add_duration~
			LPM ~add_save~
			LPM ~add_cumulable~
			LPM ~add_only_for~
			LPM ~add_target_exceptions~
		END
		ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Unknow target : %target% ~ END
		END
	WITH
		~Failure("Unknown macro: \%method%")~
		BEGIN
			LPF ~add_log_warning~ STR_VAR message = ~FAILURE: Unknown macro: %method%~ END
		END
		DEFAULT
			LPF ~add_log_warning~ STR_VAR message = ~FAILURE: opcode %opcode%: %ERROR_MESSAGE%~ END
			PATCH_FAIL ~Opcode %opcode%: %ERROR_MESSAGE%~
	END
END
