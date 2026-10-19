// Opcode 144 (Button: Disable Button) : bouton parameter2 désactivé, « Empêche l'utilisation des
// compétences de roublard » (phrases 2144 1000 + parameter2).
//
// Pris en charge : effets d'équipement certains, actifs tant que l'objet est équipé.

DEFINE_PATCH_MACRO ad_op_144_support BEGIN
	FOR (button_id = 0; button_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++button_id) BEGIN
		PATCH_IF $fx_opcode(~%button_id%~) == 144 BEGIN
			SPRINT button_block $fx_block(~%button_id%~)
			SPRINT button_timing_kind $fx_timing_kind(~%button_id%~)
			SET button = $fx_parameter2(~%button_id%~)
			PATCH_IF NOT (~%button_block%~ STRING_EQUAL ~equipped~) OR NOT (~%button_timing_kind%~ STRING_EQUAL ~while_equipped~)
					OR $fx_probability(~%button_id%~) != 100 BEGIN
				SPRINT render_missing ~not_implemented:opcode144:effect_kind~
			END
			// IESDP : boutons 0 à 15 ; 10 et 15 n'existent que sur EE.
			ELSE PATCH_IF button < 0 OR button > 15 OR (NOT IS_EE AND (button == 10 OR button == 15)) BEGIN
				SPRINT render_missing ~not_implemented:opcode144:invalid~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_144_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~144~)
	SPRINT action @21440100 // ~Empêche~
	FOR (button_id = 0; button_id < fx_count; ++button_id) BEGIN
		PATCH_IF $fx_opcode(~%button_id%~) == 144 AND NOT $fx_consumed(~%button_id%~) BEGIN
			SET button = $fx_parameter2(~%button_id%~)
			LPF ad_tra INT_VAR tra_id = 21441000 + button tra_block_start = 21441000 tra_block_size = 16 RET line_text = text END
			LPM ad_line_add
		END
	END
END
