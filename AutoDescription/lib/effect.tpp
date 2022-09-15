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
END


DEFINE_PATCH_MACRO ~load_feature_effects~
BEGIN
	SET position = 0
	CLEAR_ARRAY opcodes

    GET_OFFSET_ARRAY offsets ITM_V10_GEN_EFFECTS
    PHP_EACH offsets AS _ => offset BEGIN
        LPM ~load_effect~
    END
END

DEFINE_PATCH_MACRO ~load_extended_effects~
BEGIN
	SET position = 0
	CLEAR_ARRAY opcodes

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

		LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END
		LPM ~opcode_is_valid~

        PATCH_IF isValid == 1 BEGIN
            LPM ~add_opcode~
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

/**
 * Permettrait de remplacer certains effets par d'autres.
 * Typiquement, pour le cas de l'opcode 177, afin que l'effet vers lequel il pointe puisse être pris en compte dans la
 * phase de regroupement.
 */
DEFINE_PATCH_MACRO ~replace_effects~ BEGIN
	//TODO: Ecrire le traitement...
	//TODO: Nécessiterait de pouvoir fournir d'une manière ou d'une autre une cible forcée, selon les paramètres de
	//      l'opcode 177...
	//TODO: Avoir les différentes chaînes de cible déjà dans le tableau "opcodes_xx" ??
	//TODO: Si opcode 177 géré ici, ne pas oubier de multiplier les chances d'activation ! On ne doit pas écrire
	//      des choses comme "10 % de chance d'avoir 50% de chance...", mais directement "5 % de chance"
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
 * Si des paramètres spécifiques doivent être passé, il y a toute la place dans les variables présentes
 * Attention, seules les variables resref, resref2 et resref3 peuvent accueillir une chaîne.
 */
DEFINE_PATCH_MACRO ~group_effects~ BEGIN
	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
			PATCH_TRY LPM ~opcode_%opcode%_group~ WITH DEFAULT END
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
	SET $EVAL ~opcodes_%opcode%~(~%position%~ ~%isExternal%~ ~%target%~ ~%power%~ ~%parameter1%~ ~%parameter2%~ ~%timingMode%~ ~%resistance%~ ~%duration%~ ~%probability%~ ~%probability1%~ ~%probability2%~ ~%resref%~ ~%diceCount%~ ~%diceSides%~ ~%saveType%~ ~%saveBonus%~ ~%special%~ ~%parameter3%~ ~%parameter4%~ ~%resref2%~ ~%resref3%~) = 1
END

DEFINE_PATCH_FUNCTION ~delete_opcode~
	INT_VAR
		opcode = 0
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

	SET count = $opcodes(~%opcode%~)

	PATCH_IF VARIABLE_IS_SET $opcodes(~%opcode%~) AND $opcodes(~%opcode%~) > 0 BEGIN
	    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
	        LPM ~data_to_vars~
	        LPF evaluate_expression STR_VAR expression RET value END
	        PATCH_IF value == 1 BEGIN
	            SET $opcodes(~%opcode%~) -= 1
	        END
	        ELSE BEGIN
		        SET $opcodes_xx(~%data_0%~ ~%data_1%~ ~%data_2%~ ~%data_3%~ ~%data_4%~ ~%data_5%~ ~%data_6%~ ~%data_7%~ ~%data_8%~ ~%data_9%~ ~%data_10%~ ~%data_11%~ ~%data_12%~ ~%data_13%~ ~%data_14%~ ~%data_15%~ ~%data_16%~ ~%data_17%~ ~%data_18%~ ~%data_19%~ ~%data_20%~ ~%data_21%~) = 1
	        END
	    END
	END

	SET count = $opcodes(~%opcode%~)
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
	RET
		description
		sort
		saveAdded
		ignoreDuration
BEGIN
	SET ignoreDuration = 0
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
			PATCH_IF NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
				SPRINT theTarget   @102472 // ~le porteur~
				SPRINT ofTheTarget @101086 // ~du porteur~
				SPRINT toTheTarget @101180 // ~au porteur~
			END
		END
		ELSE PATCH_IF target == TARGET_FX_preset OR target == TARGET_FX_everyone_except_self BEGIN
			SPRINT opcode_target ~_target~
			PATCH_IF NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
				SPRINT theTarget   @102471 // ~la cible~
				SPRINT ofTheTarget @101085 // ~de la cible~
				SPRINT toTheTarget @101181 // ~à la cible~
			END
		END
		ELSE PATCH_IF target == TARGET_FX_party BEGIN
			SPRINT opcode_target ~_target~
			PATCH_IF NOT VARIABLE_IS_SET theTarget OR resetTarget == 1 BEGIN
				SPRINT theTarget   @102473 // ~les membres du groupe~
				SPRINT ofTheTarget @101088 // ~des membres du groupe~
				SPRINT toTheTarget @101182 // ~aux membres du groupe~
			END
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
					SPRINT description @101125 // ~%probability% de chance %description%~
				END
			END

			LPM ~add_condition~
			LPM ~add_duration~
			LPM ~add_save~
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
