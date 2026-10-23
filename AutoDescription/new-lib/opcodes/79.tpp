// Opcode 79 (Cure: Disease) : « Guérit les maladies de la cible » ; code commun dans
// new-lib/opcodes/states.tpp.
//
// Avec AD_ENABLE_SHRINKAGE, l'ancien opcode_79_group ajoute au premier 79 d'un bloc sans guérison de
// la débilité mentale (opcode 77) une telle guérison, avec les champs du 79 : sa ligne « Guérison de
// la débilité mentale » est écrite ici, au rang du 77, avec l'application du 79.

// Refus : avec AD_ENABLE_SHRINKAGE, guérison ajoutée dans un bloc qui a une dissipation de la magie
// (58) ou une immunité à la débilité mentale (101 de parameter2 76) : selon l'ordre de ses
// regroupements, l'ancien moteur la retire ou non.
DEFINE_PATCH_MACRO ad_op_79_support BEGIN
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		FOR (disease_id = 0; disease_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++disease_id) BEGIN
			LPM ad_op_79_adds_feeblemind_cure
			PATCH_IF disease_adds_cure BEGIN
				FOR (disease_other = 0; disease_other < fx_count; ++disease_other) BEGIN
					SPRINT disease_other_scope $fx_scope(~%disease_other%~)
					SET disease_other_opcode = $fx_opcode(~%disease_other%~)
					PATCH_IF (~%disease_other_scope%~ STRING_EQUAL ~%disease_scope%~)
							AND (disease_other_opcode == 58 OR (disease_other_opcode == 101 AND $fx_parameter2(~%disease_other%~) == 76)) BEGIN
						LPF ad_refusal INT_VAR fx_id = disease_other STR_VAR reason = ~not_implemented:opcode79:feeblemind_cure_order~ message = ~feeblemind cure in an order the old engine writes differently~ RET render_missing = refusal END
					END
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_79_lines BEGIN
	SET state_opcode = 79
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		SPRINT line_section ~equipped~
		SET line_sort = $AD_OPCODE_SORT(~77~)
		FOR (disease_id = 0; disease_id < fx_count; ++disease_id) BEGIN
			LPM ad_op_79_adds_feeblemind_cure
			PATCH_IF disease_adds_cure BEGIN
				SET line_fx = disease_id
				SET line_phrase = 20770100 // ~Guérison de la débilité mentale~ (+1 : ~Guérit la débilité mentale %ofTheTarget%~)
				LPM ad_effect_line
			END
		END
	END
END

// L'effet disease_id est-il le premier 79 non consommé de son bloc, dans un bloc sans opcode 77 ?
DEFINE_PATCH_MACRO ad_op_79_adds_feeblemind_cure BEGIN
	SET disease_adds_cure = 0
	PATCH_IF $fx_opcode(~%disease_id%~) == 79 AND NOT $fx_consumed(~%disease_id%~) BEGIN
		SPRINT disease_scope $fx_scope(~%disease_id%~)
		SET disease_adds_cure = 1
		FOR (disease_other = 0; disease_other < fx_count; ++disease_other) BEGIN
			SPRINT disease_other_scope $fx_scope(~%disease_other%~)
			SET disease_other_opcode = $fx_opcode(~%disease_other%~)
			PATCH_IF (~%disease_other_scope%~ STRING_EQUAL ~%disease_scope%~) AND (disease_other_opcode == 77
					OR (disease_other_opcode == 79 AND disease_other < disease_id AND NOT $fx_consumed(~%disease_other%~))) BEGIN
				SET disease_adds_cure = 0
			END
		END
	END
END
