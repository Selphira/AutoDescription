// Code commun des boutons de l'interface (opcodes 144 et 279) : bouton parameter2, 0 à 15 (IESDP), dont
// 10 et 15 n'existent que sur EE. L'opcode fixe button_opcode et button_action_tra, première des
// quatre actions selon la forme (« Empêche », « Permet »…), suivie de « l'utilisation de … » sans
// cible, de « d'utiliser … » avec la cible (listes 2144 1000 et 2144 1100 + parameter2, ancien
// opcode_144_common).
//
// Comme l'ancien opcode_144_is_valid, un bouton inconnu est écarté.

DEFINE_PATCH_MACRO ad_button_support BEGIN
	PHP_EACH ~fx_ids_%button_opcode%~ AS _ => button_id BEGIN
		SET button = $fx_parameter2(~%button_id%~)
		PATCH_IF NOT $fx_dropped(~%button_id%~) AND (button < 0 OR button > 15 OR (NOT IS_EE AND (button == 10 OR button == 15))) BEGIN
			SET drop_id = button_id
			SPRINT ignored_reason ~file_error:opcode%button_opcode%:invalid~
			SPRINT ignored_message ~button %button% (expected 0-15; 10 and 15 only on enhanced editions)~
			LPM ad_application_drop
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
			SET button_list = (line_form == 1 OR line_form == 3) ? 21441100 : 21441000
			LPF ad_tra INT_VAR tra_id = button_list + button tra_block_start = button_list tra_block_size = 16 RET line_text = text END // ~%action% l'utilisation du camouflage dans l'ombre~
			SET line_any_form = 1
			LPM ad_effect_line
		END
	END
END
