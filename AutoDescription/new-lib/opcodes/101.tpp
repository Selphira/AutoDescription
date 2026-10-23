// Opcode 101 (Protection: from Opcode) : immunité à l'opcode parameter2, « Immunité au silence ».
// Libellé « au silence » dans la liste @8030000 (8 030 000 + opcode ; libellé vide : immunité non
// décrite, comme dans l'ancien moteur). La passe des regroupements (ad_group_immunities,
// new-lib/groups.tpp) lui fait absorber les effets qu'elle rend sans objet et peut changer son
// libellé (fx_immunity_label) en le plaçant après les autres (fx_immunity_late, comme un effet
// identique à un autre, fx_late).
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp). Dans un en-tête, l'ancien moteur n'applique pas les absorptions des
// soins (delete_cure_linked_to_specific_immunity, lignes EQUIPPED de 2da/immunity_absorbs.2da) ni
// celle de l'action libre ; la ligne unique qu'il y forme prend les champs (durée, jet de
// sauvegarde…) de la dernière immunité de l'en-tête.

// Refus : opcode sans libellé ; dans un en-tête dont une classe de cible a plusieurs immunités (ligne
// unique), immunités aux champs différents, parameter2 mis à part.

DEFINE_PATCH_MACRO ad_op_101_support BEGIN
	FOR (immunity_id = 0; immunity_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++immunity_id) BEGIN
		PATCH_IF $fx_opcode(~%immunity_id%~) == 101 BEGIN
			SET immunity_opcode = $fx_parameter2(~%immunity_id%~)
			SET immunity_label_tra = 8030000 + immunity_opcode
			// Opcode sans libellé : l'ancien moteur échoue sur la chaîne absente.
			PATCH_IF immunity_opcode < 0 OR immunity_opcode > 999 OR NOT TRA_ENTRY_EXISTS (~%immunity_label_tra%~) BEGIN
				PATCH_IF immunity_opcode < 0 OR immunity_opcode > 999 BEGIN
					LPF ad_refusal INT_VAR fx_id = immunity_id STR_VAR reason = ~file_error:opcode101:unknown_opcode~ message = ~opcode %immunity_opcode% does not exist (expected 0-999)~ RET render_missing = refusal END
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = immunity_id STR_VAR reason = ~not_implemented:opcode101:unknown_opcode~ message = ~no name for opcode %immunity_opcode%~ RET render_missing = refusal END
				END
			END
			ELSE BEGIN
				SET $fx_immunity_label(~%immunity_id%~) = immunity_opcode
				SET $fx_immunity_late(~%immunity_id%~) = 0
				SPRINT immunity_scope $fx_scope(~%immunity_id%~)
				PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_IMMUNITIES_SINGLE_LINE AND NOT (~%immunity_scope%~ STRING_EQUAL ~equipped~) BEGIN
					LPM ad_op_101_ability_support
				END
			END
		END
	END
END

// Immunité immunity_id d'un en-tête : si une autre immunité de l'en-tête est de la même classe de
// cible (ad_immunity_class), toutes les immunités de l'en-tête ont les mêmes champs, parameter2 mis à
// part.
DEFINE_PATCH_MACRO ad_op_101_ability_support BEGIN
	LPM ad_immunity_class
	SET immunity_own_class = immunity_class
	SET same_id = immunity_id
	SET same_ignored = AD_SAME_PARAMETER2
	SET immunity_same_class = 0
	SET immunity_different = 0
	SET immunity_self = immunity_id
	FOR (immunity_id = 0; immunity_id < fx_count; ++immunity_id) BEGIN
		SPRINT immunity_other_scope $fx_scope(~%immunity_id%~)
		PATCH_IF immunity_id != immunity_self AND $fx_opcode(~%immunity_id%~) == 101 AND (~%immunity_other_scope%~ STRING_EQUAL ~%immunity_scope%~) BEGIN
			LPM ad_immunity_class
			SET immunity_same_class = immunity_same_class OR (immunity_own_class > 0 AND immunity_class == immunity_own_class)
			SET same_other = immunity_id
			LPM ad_fx_same_fields
			SET immunity_different = immunity_different OR NOT fx_same
		END
	END
	SET immunity_id = immunity_self
	SPRINT immunity_scope $fx_scope(~%immunity_id%~)
	PATCH_IF immunity_same_class AND immunity_different BEGIN
		LPF ad_refusal INT_VAR fx_id = immunity_id STR_VAR reason = ~not_implemented:opcode101:ability_group_fields~ message = ~immunities of the ability with different fields~ RET render_missing = refusal END
	END
END

// Lignes (ancien opcode_self_101 et opcode_101_post_group) : avec AD_SHRINK_IMMUNITIES_SINGLE_LINE,
// les immunités certaines d'un même bloc et d'une même classe de cible (soi ou lanceur d'origine ;
// cible prédéfinie) sont réunies en une ligne si elles sont plusieurs, libellés identiques fusionnés ;
// les lignes réunies viennent après les autres, comme les effets que l'ancien moteur ajoute en fin de
// liste.
DEFINE_PATCH_MACRO ad_op_101_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~101~)
	CLEAR_ARRAY immunity_key_count
	FOR (immunity_id = 0; immunity_id < fx_count; ++immunity_id) BEGIN
		PATCH_IF $fx_opcode(~%immunity_id%~) == 101 AND NOT $fx_consumed(~%immunity_id%~) BEGIN
			LPM ad_immunity_class
			PATCH_IF immunity_class > 0 BEGIN
				PATCH_IF NOT VARIABLE_IS_SET $immunity_key_count(~%immunity_key%~) BEGIN
					SET $immunity_key_count(~%immunity_key%~) = 0
				END
				SET $immunity_key_count(~%immunity_key%~) += 1
			END
		END
	END
	FOR (immunity_late = 0; immunity_late <= 1; ++immunity_late) BEGIN
		FOR (immunity_id = 0; immunity_id < fx_count; ++immunity_id) BEGIN
			PATCH_IF $fx_opcode(~%immunity_id%~) == 101 AND NOT $fx_consumed(~%immunity_id%~)
					AND ($fx_immunity_late(~%immunity_id%~) OR $fx_late(~%immunity_id%~)) == immunity_late BEGIN
				LPM ad_immunity_class
				LPM ad_immunity_merged
				PATCH_IF NOT immunity_merged BEGIN
					LPM ad_immunity_label
					PATCH_IF NOT ~%immunity_label%~ STRING_EQUAL ~~ BEGIN
						SPRINT opcodeStr ~%immunity_label%~
						SET line_phrase = 21010100 // ~Immunité %opcodeStr%~ (+1 : ~Immunise %theTarget% %opcodeStr%~)
						SET line_fx = immunity_id
						LPM ad_effect_line
					END
				END
			END
		END
	END
	PHP_EACH immunity_key_count AS immunity_merged_key => immunity_merged_count BEGIN
		PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_IMMUNITIES_SINGLE_LINE AND immunity_merged_count > 1 BEGIN
			CLEAR_ARRAY immunity_labels
			SET immunity_label_count = 0
			SET immunity_first = 0 - 1
			FOR (immunity_late = 0; immunity_late <= 1; ++immunity_late) BEGIN
				FOR (immunity_id = 0; immunity_id < fx_count; ++immunity_id) BEGIN
					PATCH_IF $fx_opcode(~%immunity_id%~) == 101 AND NOT $fx_consumed(~%immunity_id%~)
							AND ($fx_immunity_late(~%immunity_id%~) OR $fx_late(~%immunity_id%~)) == immunity_late BEGIN
						LPM ad_immunity_class
						PATCH_IF immunity_class > 0 AND (~%immunity_key%~ STRING_EQUAL ~%immunity_merged_key%~) BEGIN
							LPM ad_immunity_label
							PATCH_IF NOT ~%immunity_label%~ STRING_EQUAL ~~ BEGIN
								SPRINT $immunity_labels(~%immunity_label%~) ~%immunity_label%~
								SET immunity_label_count += 1
								PATCH_IF immunity_first < 0 BEGIN
									SET immunity_first = immunity_id
								END
							END
						END
					END
				END
			END
			PATCH_IF immunity_label_count > 0 BEGIN
				LPF ad_join STR_VAR array_name = ~immunity_labels~ RET opcodeStr = text END
				SET line_phrase = 21010100 // ~Immunité %opcodeStr%~
				SET line_fx = immunity_first
				LPM ad_effect_line
			END
		END
	END
END

// Classe de cible de l'effet immunity_id pour la ligne unique : 1 soi ou lanceur d'origine, 2 cible
// prédéfinie, 0 jamais réunie (immunité probable, autre cible) ; immunity_key : classe dans sa portée
// (une ligne unique par bloc).
DEFINE_PATCH_MACRO ad_immunity_class BEGIN
	SET immunity_target = $fx_effective_target(~%immunity_id%~)
	SET immunity_class = $fx_probability(~%immunity_id%~) < 100 ? 0
		: ((immunity_target == TARGET_FX_self OR immunity_target == TARGET_FX_original_caster) ? 1
		: (immunity_target == TARGET_FX_preset ? 2 : 0))
	SPRINT immunity_key_scope $fx_scope(~%immunity_id%~)
	SPRINT immunity_key ~%immunity_key_scope% %immunity_class%~
END

// L'immunité immunity_id (classe et clé de ad_immunity_class) est-elle dans une ligne unique ?
DEFINE_PATCH_MACRO ad_immunity_merged BEGIN
	SET immunity_merged = AD_ENABLE_SHRINKAGE AND AD_SHRINK_IMMUNITIES_SINGLE_LINE AND immunity_class > 0
		AND VARIABLE_IS_SET $immunity_key_count(~%immunity_key%~)
	PATCH_IF immunity_merged BEGIN
		SET immunity_merged = $immunity_key_count(~%immunity_key%~) > 1
	END
END

DEFINE_PATCH_MACRO ad_immunity_label BEGIN
	SET immunity_label_tra = 8030000 + $fx_immunity_label(~%immunity_id%~)
	LPF ad_tra INT_VAR tra_id = immunity_label_tra RET immunity_label = text END
END
