// Opcode 236 (Spell Effect: Image Projection) : « Crée une image du lanceur qui ne peut ni attaquer ni lancer
// de sorts » ; parameter2 = type (IESDP : 0 clone, 1 image, 2 projection, 3 simulacre, au-delà comme 0) ; code commun dans new-lib/opcodes/states.tpp.

// Refus : type négatif ; avec AD_ENABLE_SHRINKAGE, plusieurs effets semblables du même type, que
// l'ancien opcode_236_group réunit (« Crée 2 images… »).
DEFINE_PATCH_MACRO ad_op_236_support BEGIN
	PHP_EACH fx_ids_236 AS _ => image_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET image_type = $fx_parameter2(~%image_id%~)
			PATCH_IF image_type < 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = image_id STR_VAR reason = ~not_implemented:opcode236:type~ message = ~type %image_type%~ RET render_missing = refusal END
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND NOT support_header_only BEGIN
				SET image_type = image_type > 3 ? 0 : image_type
				SET same_id = image_id
				SET same_ignored = AD_SAME_PARAMETER2 BOR AD_SAME_PROBABILITY
				PHP_EACH fx_ids_236 AS _ => image_other BEGIN
					SET image_other_type = $fx_parameter2(~%image_other%~)
					SET image_other_type = image_other_type > 3 ? 0 : image_other_type
					PATCH_IF image_other != image_id AND image_other_type == image_type AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
						SET same_other = image_other
						LPM ad_fx_same_fields
						PATCH_IF fx_same BEGIN
							LPF ad_refusal INT_VAR fx_id = image_id STR_VAR reason = ~not_implemented:opcode236:group~ message = ~several image projections of the same type~ RET render_missing = refusal END
						END
					END
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_236_lines BEGIN
	SET state_opcode = 236
	SPRINT state_variant_macro ~ad_op_236_variant~
	LPM ad_state_lines
END

// Variante : type.
DEFINE_PATCH_MACRO ad_op_236_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~)
	SET state_variant = state_variant > 3 ? 0 : state_variant
END
