// Code commun des boutons de l'interface (opcodes 144 et 279) : bouton parameter2, 0 à 15 (IESDP), dont
// 10 et 15 n'existent que sur EE. L'opcode fixe button_opcode et button_action_tra, première des
// quatre actions selon la forme (« Empêche », « Permet »…), suivie de « l'utilisation de … » sans
// cible, de « d'utiliser … » avec la cible (listes 2144 1000 et 2144 1100 + parameter2, ancien
// opcode_144_common).
//
// Comme l'ancien opcode_144_is_valid, un bouton inconnu est écarté ; le bouton des discussions (7),
// qui n'intéresse pas le joueur, l'est aussi, sans journal.
//
// Les boutons de même effet sont réunis (ad_group_buttons, fx_buttons : masque des boutons) en une
// ligne, « Empêche l'utilisation des sorts et des objets » (listes 2144 1300 et 2144 1400 +
// parameter2) ; les sorts rapides y sont compris dans les sorts, les objets rapides dans les objets.

DEFINE_PATCH_MACRO ad_button_support BEGIN
	PHP_EACH ~fx_ids_%button_opcode%~ AS _ => button_id BEGIN
		SET button = $fx_parameter2(~%button_id%~)
		SET $fx_buttons(~%button_id%~) = 0
		PATCH_IF NOT $fx_dropped(~%button_id%~) AND (button < 0 OR button > 15 OR (NOT IS_EE AND (button == 10 OR button == 15))) BEGIN
			SET drop_id = button_id
			SPRINT ignored_reason ~file_error:opcode%button_opcode%:invalid~
			SPRINT ignored_message ~button %button% (expected 0-15; 10 and 15 only on enhanced editions)~
			LPM ad_application_drop
		END
		ELSE PATCH_IF NOT $fx_dropped(~%button_id%~) AND button == 7 BEGIN
			SET drop_id = button_id
			SPRINT ignored_reason ~~
			LPM ad_application_drop
		END
	END
END

// Comme les types de sort (ad_group_spell_types, new-lib/groups.tpp) : chaque effet réunit les autres
// effets de son opcode qui ont les mêmes champs, parameter2 mis à part, et le même type de créature
// (177).
DEFINE_PATCH_MACRO ad_group_buttons BEGIN
	PHP_EACH ~fx_ids_%button_opcode%~ AS _ => group_id BEGIN
		PATCH_IF NOT $fx_consumed(~%group_id%~) BEGIN
			SET group_buttons = 1 << $fx_parameter2(~%group_id%~)
			SET group_merged = 0
			SET same_id = group_id
			SET same_ignored = AD_SAME_PARAMETER2
			PHP_EACH ~fx_ids_%button_opcode%~ AS _ => group_candidate BEGIN
				PATCH_IF group_candidate != group_id AND NOT $fx_consumed(~%group_candidate%~) AND $fx_buttons(~%group_candidate%~) == 0 BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					PATCH_IF fx_same AND $fx_versus_file(~%group_id%~) == $fx_versus_file(~%group_candidate%~)
							AND $fx_versus_value(~%group_id%~) == $fx_versus_value(~%group_candidate%~)
							AND $fx_versus_inner_file(~%group_id%~) == $fx_versus_inner_file(~%group_candidate%~)
							AND $fx_versus_inner_value(~%group_id%~) == $fx_versus_inner_value(~%group_candidate%~) BEGIN
						SET $fx_consumed(~%group_candidate%~) = 1
						SET $fx_group_anchor(~%group_candidate%~) = group_id
						SET group_buttons = group_buttons BOR (1 << $fx_parameter2(~%group_candidate%~))
						SET group_merged = 1
					END
				END
			END
			PATCH_IF group_merged BEGIN
				SET $fx_buttons(~%group_id%~) = group_buttons
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_button_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%button_opcode%~)
	PHP_EACH ~fx_ids_%button_opcode%~ AS _ => button_id BEGIN
		PATCH_IF NOT $fx_consumed(~%button_id%~) BEGIN
			SET button = $fx_parameter2(~%button_id%~)
			SET line_fx = button_id
			LPM ad_application_form
			// Les chaînes de la cible de l'effet sont lues avant l'action, qui les contient.
			LPM ad_application_target_strings
			LPF ad_tra INT_VAR tra_id = button_action_tra + line_form RET action = text END // ~Empêche~
			SET button_target_form = line_form == 1 OR line_form == 3
			SET button_mask = $fx_buttons(~%button_id%~)
			PATCH_IF button_mask == 0 BEGIN
				SET button_list = button_target_form ? 21441100 : 21441000
				LPF ad_tra INT_VAR tra_id = button_list + button tra_block_start = button_list tra_block_size = 16 RET line_text = text END // ~%action% l'utilisation du camouflage dans l'ombre~
			END
			ELSE BEGIN
				// Sorts (2) et sorts rapides (3 à 5), objets (8) et objets rapides (9, 11, 12).
				PATCH_IF (button_mask BAND (1 << 2)) != 0 BEGIN
					SET button_mask = button_mask BAND (BNOT ((1 << 3) BOR (1 << 4) BOR (1 << 5)))
				END
				PATCH_IF (button_mask BAND (1 << 8)) != 0 BEGIN
					SET button_mask = button_mask BAND (BNOT ((1 << 9) BOR (1 << 11) BOR (1 << 12)))
				END
				SET button_list = button_target_form ? 21441400 : 21441300
				CLEAR_ARRAY button_names
				FOR (button_k = 0; button_k < 16; ++button_k) BEGIN
					PATCH_IF (button_mask BAND (1 << button_k)) != 0 BEGIN
						LPF ad_tra INT_VAR tra_id = button_list + button_k tra_block_start = button_list tra_block_size = 16 RET button_name = text END // ~des sorts~
						SPRINT $button_names(~%button_k%~) ~%button_name%~
					END
				END
				LPF ad_join STR_VAR array_name = ~button_names~ RET buttonList = text END
				SET button_phrase = button_target_form ? 21441201 : 21441200
				LPF ad_tra INT_VAR tra_id = button_phrase RET line_text = text END // ~%action% l'utilisation %buttonList%~
			END
			SET line_any_form = 1
			LPM ad_effect_line
		END
	END
END
