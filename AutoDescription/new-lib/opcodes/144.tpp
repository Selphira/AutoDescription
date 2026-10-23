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
	SPRINT action @21440100 // ~Empêche~
	PHP_EACH fx_ids_144 AS _ => button_id BEGIN
		PATCH_IF NOT $fx_consumed(~%button_id%~) BEGIN
			SET button = $fx_parameter2(~%button_id%~)
			LPF ad_tra INT_VAR tra_id = 21441000 + button tra_block_start = 21441000 tra_block_size = 16 RET line_text = text END
			SET line_fx = button_id
			LPM ad_effect_line
		END
	END
END
