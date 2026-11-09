// Opcode 100 (Protection: from Creature Type) : immunise contre les attaques et les sorts des
// créatures de la valeur parameter1 du fichier IDS parameter2 (ad_ids_name, new-lib/resources.tpp) :
// « Immunité aux attaques et aux sorts des morts-vivants » ; valeur 0 : de toutes les créatures.
// Code commun dans new-lib/opcodes/states.tpp.

// Fichier qui n'est pas un type de créature : écarté et journalisé. Refus : kit.ids et valeur 100 de
// ea.ids (écartés par l'ancien opcode_idscheck8_is_valid) ; valeur sans nom.
DEFINE_PATCH_MACRO ad_op_100_support BEGIN
	PHP_EACH fx_ids_100 AS _ => versus_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET versus_file = $fx_parameter2(~%versus_id%~)
			SET versus_value = $fx_parameter1(~%versus_id%~)
			LPF ad_ids_name INT_VAR ids_file = versus_file entry = versus_value RET versus_name = name END
			SPRINT $fx_versus_name(~%versus_id%~) ~%versus_name%~
			PATCH_IF versus_file < 2 OR versus_file > 8 OR (versus_file == 2 AND versus_value == 100) BEGIN
				PATCH_IF versus_file < 2 OR versus_file > (IS_EE ? 9 : 8) BEGIN
					SET drop_id = versus_id
					SPRINT ignored_reason ~file_error:opcode100:ids_file~
					SPRINT ignored_message ~IDS file %versus_file% is not a creature type (expected 2-8: EA, GENERAL, RACE, CLASS, SPECIFIC, GENDER, ALIGN; 9: KIT on enhanced editions)~
					LPM ad_application_drop
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = versus_id STR_VAR reason = ~not_implemented:opcode100:ids_file~ message = ~kit restriction or value 100 of EA.IDS not supported (IDS file %versus_file%, value %versus_value%)~ RET render_missing = refusal END
				END
			END
			ELSE PATCH_IF versus_value != 0 AND ~%versus_name%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = versus_id STR_VAR reason = ~not_implemented:opcode100:ids_name~ message = ~value %versus_value% of IDS file %versus_file% has no name~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_100_lines BEGIN
	SET state_opcode = 100
	SPRINT state_variant_macro ~ad_op_100_variant~
	LPM ad_state_lines
END

// Variante 0 : créatures nommées, 1 : toutes les créatures.
DEFINE_PATCH_MACRO ad_op_100_variant BEGIN
	SET state_variant = $fx_parameter1(~%line_fx%~) == 0 ? 1 : 0
	SPRINT creatureType $fx_versus_name(~%line_fx%~)
END

// Protections contre des types de créatures nommés réunies (anciennes lignes séparées) : chaque effet
// réunit les autres effets de l'opcode contre un type nommé qui ont les mêmes champs, parameter1 et
// parameter2 mis à part, et le même type de créature (177) ; ses noms, sans doublon et dans l'ordre
// des effets, deviennent « morts-vivants, des goules et des ombres » (fx_versus_name).
DEFINE_PATCH_MACRO ad_group_creature_types BEGIN
	SPRINT creature_glue @21000000 // ~, des ~
	SPRINT creature_final_glue @21000001 // ~ et des ~
	PHP_EACH fx_ids_100 AS _ => group_id BEGIN
		PATCH_IF NOT $fx_consumed(~%group_id%~) AND $fx_parameter1(~%group_id%~) != 0 BEGIN
			SET group_merged = 0
			SET same_id = group_id
			SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2
			CLEAR_ARRAY creature_type_names
			SPRINT creature_type_name $fx_versus_name(~%group_id%~)
			SPRINT $creature_type_names(~%creature_type_name%~) ~%creature_type_name%~
			PHP_EACH fx_ids_100 AS _ => group_candidate BEGIN
				PATCH_IF group_candidate != group_id AND NOT $fx_consumed(~%group_candidate%~) AND $fx_parameter1(~%group_candidate%~) != 0 BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					PATCH_IF fx_same AND $fx_versus_file(~%group_id%~) == $fx_versus_file(~%group_candidate%~)
							AND $fx_versus_value(~%group_id%~) == $fx_versus_value(~%group_candidate%~)
							AND $fx_versus_inner_file(~%group_id%~) == $fx_versus_inner_file(~%group_candidate%~)
							AND $fx_versus_inner_value(~%group_id%~) == $fx_versus_inner_value(~%group_candidate%~) BEGIN
						SET $fx_consumed(~%group_candidate%~) = 1
						SET $fx_group_anchor(~%group_candidate%~) = group_id
						SPRINT creature_type_name $fx_versus_name(~%group_candidate%~)
						SPRINT $creature_type_names(~%creature_type_name%~) ~%creature_type_name%~
						SET group_merged = 1
					END
				END
			END
			PATCH_IF group_merged BEGIN
				LPF ad_join STR_VAR array_name = ~creature_type_names~ glue = EVAL ~%creature_glue%~ final_glue = EVAL ~%creature_final_glue%~ RET creature_types = text END
				SPRINT $fx_versus_name(~%group_id%~) ~%creature_types%~
			END
		END
	END
END
