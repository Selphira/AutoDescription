// Opcode 144 (Button: Disable Button) : bouton parameter2 désactivé, « Empêche l'utilisation des
// compétences de roublard » (phrases 2144 1000 + parameter2).
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp).

DEFINE_PATCH_MACRO ad_op_144_support BEGIN
	PHP_EACH fx_ids_144 AS _ => button_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET button = $fx_parameter2(~%button_id%~)
			// IESDP : boutons 0 à 15 ; 10 et 15 n'existent que sur EE.
			PATCH_IF button < 0 OR button > 15 OR (NOT IS_EE AND (button == 10 OR button == 15)) BEGIN
				LPF ad_refusal INT_VAR fx_id = button_id STR_VAR reason = ~file_error:opcode144:invalid~ message = ~button %button% (expected 0-15; 10 and 15 only on enhanced editions)~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_144_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~144~)
	PHP_EACH fx_ids_144 AS _ => button_id BEGIN
		PATCH_IF NOT $fx_consumed(~%button_id%~) BEGIN
			SET button = $fx_parameter2(~%button_id%~)
			SET line_fx = button_id
			LPM ad_application_form
			// Action selon la forme (« Empêche », « Empêche la cible », « d'empêcher »…), suivie de
			// « l'utilisation de … » sans cible, de « d'utiliser … » avec la cible (ancien opcode_144_common) ;
			// les chaînes de la cible de l'effet sont lues avant, l'action les contient.
			LPM ad_application_target_strings
			LPF ad_tra INT_VAR tra_id = 21440100 + line_form RET action = text END // ~Empêche~
			SET button_list = (line_form == 1 OR line_form == 3) ? 21441100 : 21441000
			LPF ad_tra INT_VAR tra_id = button_list + button tra_block_start = button_list tra_block_size = 16 RET line_text = text END // ~%action% l'utilisation du camouflage dans l'ombre~
			SET line_any_form = 1
			LPM ad_effect_line
		END
	END
END
