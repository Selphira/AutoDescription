// États, soins et autres effets à phrase fixe : états (opcodes 3, 13, 16, 20, 24, 38, 39, 40, 45,
// 63, 74, 76, 80, 109, 128, 134, 317), soins et dissipations (2, 4, 11, 43, 46, 47, 48, 58, 75, 77,
// 79, 81, 116, 161-164), drain de niveaux (216), point de rupture de moral (106), charme (5),
// inversion de l'alignement (56) et du sexe (71), protection contre un type de créature (100),
// métamorphose (135), peau de pierre (218) ; une phrase par variante de l'opcode, « Réduit la cible
// au silence ».
// Chaque fichier d'opcode fixe state_opcode et state_variant_macro (vide si l'opcode n'a qu'une
// variante) ; cette macro choisit state_variant pour l'effet line_fx et peut fixer line_condition.
// Phrase : 20 000 000 + opcode × 10 000 + 100 + 10 × variante, plus la forme (ad_effect_line,
// new-lib/application.tpp).

// Une ligne par effet non consommé, dans l'ordre du fichier (ancien opcode_<self|target>[_probability]_N).
DEFINE_PATCH_MACRO ad_state_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%state_opcode%~)
	FOR (state_id = 0; state_id < fx_count; ++state_id) BEGIN
		PATCH_IF $fx_opcode(~%state_id%~) == state_opcode AND NOT $fx_consumed(~%state_id%~) BEGIN
			SET line_fx = state_id
			SET state_variant = 0
			PATCH_IF NOT (~%state_variant_macro%~ STRING_EQUAL ~~) BEGIN
				LPM ~%state_variant_macro%~
			END
			SET line_phrase = 20000000 + state_opcode * 10000 + 100 + 10 * state_variant
			LPM ad_effect_line
		END
	END
END
