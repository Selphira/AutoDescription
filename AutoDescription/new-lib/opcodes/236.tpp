// Opcode 236 (Spell Effect: Image Projection) : « Crée une image du lanceur qui ne peut ni attaquer ni lancer
// de sorts » ; parameter2 = type (IESDP : 0 clone, 1 image, 2 projection, 3 simulacre, au-delà comme 0) ; code commun dans new-lib/opcodes/states.tpp.

// Refus : type négatif. Avec AD_ENABLE_SHRINKAGE, des effets certains semblables du même type n'en
// font qu'un (ancien opcode_236_group : « Crée 3 clones du porteur… », $fx_image_amount) ; refus si
// l'un d'eux est probable (l'ancien moteur en fait « entre N et M »).
DEFINE_PATCH_MACRO ad_op_236_support BEGIN
	PHP_EACH fx_ids_236 AS _ => image_id BEGIN
		SET $fx_image_amount(~%image_id%~) = 1
	END
	PHP_EACH fx_ids_236 AS _ => image_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%image_id%~) BEGIN
			SET image_type = $fx_parameter2(~%image_id%~)
			PATCH_IF image_type < 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = image_id STR_VAR reason = ~not_implemented:opcode236:type~ message = ~type %image_type%~ RET render_missing = refusal END
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND NOT support_header_only BEGIN
				SET image_type = image_type > 3 ? 0 : image_type
				SET same_id = image_id
				SET same_ignored = AD_SAME_PARAMETER2 BOR AD_SAME_PROBABILITY
				SET image_certain = $fx_probability(~%image_id%~) >= 100
				PHP_EACH fx_ids_236 AS _ => image_other BEGIN
					SET image_other_type = $fx_parameter2(~%image_other%~)
					SET image_other_type = image_other_type > 3 ? 0 : image_other_type
					PATCH_IF image_other != image_id AND image_other_type == image_type AND NOT $fx_consumed(~%image_other%~)
							AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
						SET same_other = image_other
						LPM ad_fx_same_fields
						PATCH_IF fx_same AND image_certain AND $fx_probability(~%image_other%~) >= 100 BEGIN
							SET $fx_consumed(~%image_other%~) = 1
							SET $fx_image_amount(~%image_id%~) += 1
							// Ajouté en fin de liste par l'ancien add_opcode.
							SET $fx_late(~%image_id%~) = 1
						END
						ELSE PATCH_IF fx_same BEGIN
							LPF ad_refusal INT_VAR fx_id = image_id STR_VAR reason = ~not_implemented:opcode236:group~ message = ~several image projections of the same type, one of them probable~ RET render_missing = refusal END
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

// Variante : type (0-3), ou type + 4 pour des images réunies, au nombre de amount.
DEFINE_PATCH_MACRO ad_op_236_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~)
	SET state_variant = state_variant > 3 ? 0 : state_variant
	SET amount = $fx_image_amount(~%line_fx%~)
	PATCH_IF amount > 1 BEGIN
		SET state_variant += 4
	END
END
