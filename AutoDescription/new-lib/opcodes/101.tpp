// Opcode 101 (Protection: from Opcode) : immunité à l'opcode parameter2, « Immunité au silence ».
// Libellé « au silence » dans la liste @8030000 (8 030 000 + opcode ; libellé vide : immunité non
// décrite, comme dans l'ancien moteur). La passe des regroupements (ad_group_immunities,
// new-lib/groups.tpp) lui fait absorber les effets qu'elle rend sans objet et peut changer son
// libellé (fx_immunity_label) en le plaçant après les autres (fx_immunity_late).
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp). Dans un en-tête, l'ancien moteur n'applique pas les absorptions des
// soins (delete_cure_linked_to_specific_immunity) ni celle de l'action libre, et la ligne unique
// qu'il y forme prend la durée du dernier effet réuni : une immunité d'en-tête n'est prise en charge
// que seule dans son en-tête, sans effet qu'elle pourrait absorber.

DEFINE_PATCH_MACRO ad_op_101_support BEGIN
	FOR (immunity_id = 0; immunity_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++immunity_id) BEGIN
		PATCH_IF $fx_opcode(~%immunity_id%~) == 101 BEGIN
			SET immunity_opcode = $fx_parameter2(~%immunity_id%~)
			SET immunity_label_tra = 8030000 + immunity_opcode
			// Opcode sans libellé : l'ancien moteur échoue sur la chaîne absente.
			PATCH_IF immunity_opcode < 0 OR immunity_opcode > 999 OR NOT TRA_ENTRY_EXISTS (~%immunity_label_tra%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode101:unknown_opcode~
			END
			ELSE BEGIN
				SET $fx_immunity_label(~%immunity_id%~) = immunity_opcode
				SET $fx_immunity_late(~%immunity_id%~) = 0
				SPRINT immunity_scope $fx_scope(~%immunity_id%~)
				PATCH_IF NOT (~%immunity_scope%~ STRING_EQUAL ~equipped~) BEGIN
					LPM ad_op_101_ability_support
				END
			END
		END
	END
END

// Immunité immunity_id d'un en-tête : aucun autre effet de son en-tête n'est une immunité ou un effet
// qu'une immunité à immunity_opcode absorbe dans un bloc d'équipement.
DEFINE_PATCH_MACRO ad_op_101_ability_support BEGIN
	FOR (immunity_other = 0; immunity_other < fx_count; ++immunity_other) BEGIN
		SPRINT immunity_other_scope $fx_scope(~%immunity_other%~)
		SET immunity_other_opcode = $fx_opcode(~%immunity_other%~)
		PATCH_IF immunity_other != immunity_id AND (~%immunity_other_scope%~ STRING_EQUAL ~%immunity_scope%~) BEGIN
			PATCH_IF immunity_other_opcode == 101 OR immunity_other_opcode == 206 OR immunity_other_opcode == 321 BEGIN
				SPRINT render_missing ~not_implemented:opcode101:ability_group~
			END
			FOR (absorb_row = 0; absorb_row < AD_IMMUNITY_ABSORB_COUNT; ++absorb_row) BEGIN
				PATCH_IF $AD_IMMUNITY_ABSORB_IMMUNITY(~%absorb_row%~) == immunity_opcode
						AND $AD_IMMUNITY_ABSORB_OPCODE(~%absorb_row%~) == immunity_other_opcode BEGIN
					SPRINT render_missing ~not_implemented:opcode101:ability_group~
				END
			END
		END
	END
END

// Lignes (ancien opcode_self_101 et opcode_101_post_group) : avec AD_SHRINK_IMMUNITIES_SINGLE_LINE,
// les immunités d'équipement d'une même classe de cible (soi ou lanceur d'origine ; cible prédéfinie) sont
// réunies en une ligne si elles sont plusieurs, libellés identiques fusionnés ; les lignes réunies
// viennent après les autres, comme les effets que l'ancien moteur ajoute en fin de liste.
DEFINE_PATCH_MACRO ad_op_101_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~101~)
	SET $immunity_class_count(~1~) = 0
	SET $immunity_class_count(~2~) = 0
	FOR (immunity_id = 0; immunity_id < fx_count; ++immunity_id) BEGIN
		PATCH_IF $fx_opcode(~%immunity_id%~) == 101 AND NOT $fx_consumed(~%immunity_id%~) BEGIN
			LPM ad_immunity_class
			PATCH_IF immunity_class > 0 BEGIN
				SET $immunity_class_count(~%immunity_class%~) = $immunity_class_count(~%immunity_class%~) + 1
			END
		END
	END
	FOR (immunity_class = 1; immunity_class <= 2; ++immunity_class) BEGIN
		SET $immunity_class_merged(~%immunity_class%~) = AD_ENABLE_SHRINKAGE AND AD_SHRINK_IMMUNITIES_SINGLE_LINE
			AND $immunity_class_count(~%immunity_class%~) > 1
	END
	SET $immunity_class_merged(~0~) = 0
	FOR (immunity_late = 0; immunity_late <= 1; ++immunity_late) BEGIN
		FOR (immunity_id = 0; immunity_id < fx_count; ++immunity_id) BEGIN
			PATCH_IF $fx_opcode(~%immunity_id%~) == 101 AND NOT $fx_consumed(~%immunity_id%~)
					AND $fx_immunity_late(~%immunity_id%~) == immunity_late BEGIN
				LPM ad_immunity_class
				PATCH_IF NOT $immunity_class_merged(~%immunity_class%~) BEGIN
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
	FOR (immunity_merged_class = 1; immunity_merged_class <= 2; ++immunity_merged_class) BEGIN
		PATCH_IF $immunity_class_merged(~%immunity_merged_class%~) BEGIN
			CLEAR_ARRAY immunity_labels
			SET immunity_label_count = 0
			SET immunity_first = 0 - 1
			FOR (immunity_late = 0; immunity_late <= 1; ++immunity_late) BEGIN
				FOR (immunity_id = 0; immunity_id < fx_count; ++immunity_id) BEGIN
					PATCH_IF $fx_opcode(~%immunity_id%~) == 101 AND NOT $fx_consumed(~%immunity_id%~)
							AND $fx_immunity_late(~%immunity_id%~) == immunity_late BEGIN
						LPM ad_immunity_class
						PATCH_IF immunity_class == immunity_merged_class BEGIN
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
// prédéfinie, 0 jamais réunie (dont toute immunité d'en-tête).
DEFINE_PATCH_MACRO ad_immunity_class BEGIN
	SET immunity_target = $fx_effective_target(~%immunity_id%~)
	SPRINT immunity_scope $fx_scope(~%immunity_id%~)
	SET immunity_class = (immunity_target == TARGET_FX_self OR immunity_target == TARGET_FX_original_caster) ? 1
		: (immunity_target == TARGET_FX_preset ? 2 : 0)
	PATCH_IF NOT (~%immunity_scope%~ STRING_EQUAL ~equipped~) BEGIN
		SET immunity_class = 0
	END
END

DEFINE_PATCH_MACRO ad_immunity_label BEGIN
	SET immunity_label_tra = 8030000 + $fx_immunity_label(~%immunity_id%~)
	LPF ad_tra INT_VAR tra_id = immunity_label_tra RET immunity_label = text END
END
