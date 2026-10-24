// Opcode 159 (Spell Effect: Mirror Image (Exact Number)) : « Crée 1 image miroir sur le lanceur »,
// parameter1 images (l'ancien moteur lit son mot de poids faible) ; 0 : « Dissipe les images-miroir… » ;
// code commun dans new-lib/opcodes/states.tpp.

// Refus : parameter1 hors de 0-65 535 ; avec AD_ENABLE_SHRINKAGE, plusieurs effets semblables au nombre
// d'images près, que l'ancien opcode_159_group réunit (« entre 1 et 3 images miroir »).
DEFINE_PATCH_MACRO ad_op_159_support BEGIN
	PHP_EACH fx_ids_159 AS _ => image_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET image_amount = $fx_parameter1(~%image_id%~)
			PATCH_IF image_amount < 0 OR image_amount > 65535 BEGIN
				LPF ad_refusal INT_VAR fx_id = image_id STR_VAR reason = ~not_implemented:opcode159:value~ message = ~amount %image_amount% outside 0-65535~ RET render_missing = refusal END
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND image_amount > 0 AND NOT support_header_only BEGIN
				SET same_id = image_id
				SET same_ignored = AD_SAME_PARAMETER1
				PHP_EACH fx_ids_159 AS _ => image_other BEGIN
					PATCH_IF image_other != image_id AND $fx_parameter1(~%image_other%~) > 0 AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
						SET same_other = image_other
						LPM ad_fx_same_fields
						PATCH_IF fx_same BEGIN
							LPF ad_refusal INT_VAR fx_id = image_id STR_VAR reason = ~not_implemented:opcode159:group~ message = ~several mirror image effects differing only by the amount~ RET render_missing = refusal END
						END
					END
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_159_lines BEGIN
	SET state_opcode = 159
	SPRINT state_variant_macro ~ad_op_159_variant~
	LPM ad_state_lines
END

// Variante 0 : une image, 1 : plusieurs, 2 : images dissipées.
DEFINE_PATCH_MACRO ad_op_159_variant BEGIN
	SET amount = $fx_parameter1(~%line_fx%~)
	SET state_variant = amount == 1 ? 0 : (amount > 1 ? 1 : 2)
END
