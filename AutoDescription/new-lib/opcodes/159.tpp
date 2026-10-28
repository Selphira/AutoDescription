// Opcode 159 (Spell Effect: Mirror Image (Exact Number)) : « Crée 1 image miroir sur le lanceur »,
// parameter1 images (l'ancien moteur lit son mot de poids faible) ; 0 : « Dissipe les images-miroir… » ;
// code commun dans new-lib/opcodes/states.tpp.

// Avec AD_ENABLE_SHRINKAGE, des effets semblables au nombre d'images et à la probabilité près, dont les
// plages de tirage sont contiguës et disjointes (un nombre d'images au hasard), n'en font qu'un, sur
// l'union de leurs plages : « Crée entre 1 et 4 images miroir » (ancien opcode_159_group).
// Refus : parameter1 hors de 0-65 535 ; avec AD_ENABLE_SHRINKAGE, d'autres effets semblables au nombre
// d'images près, que l'ancien opcode_159_group réunit aussi alors qu'ils s'appliquent ensemble.
DEFINE_PATCH_MACRO ad_op_159_support BEGIN
	PHP_EACH fx_ids_159 AS _ => image_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%image_id%~) BEGIN
			SET image_amount = $fx_parameter1(~%image_id%~)
			SET $fx_image_max(~%image_id%~) = 0
			PATCH_IF image_amount < 0 OR image_amount > 65535 BEGIN
				LPF ad_refusal INT_VAR fx_id = image_id STR_VAR reason = ~not_implemented:opcode159:value~ message = ~amount %image_amount% outside 0-65535~ RET render_missing = refusal END
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND image_amount > 0 AND NOT support_header_only BEGIN
				LPM ad_op_159_group
			END
		END
	END
END

// Effets semblables à image_id au nombre d'images et à la probabilité près.
DEFINE_PATCH_MACRO ad_op_159_group BEGIN
	SET same_id = image_id
	SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PROBABILITY
	SET image_min = image_amount
	SET image_max = image_amount
	SET image_low = $fx_probability_low(~%image_id%~)
	SET image_high = $fx_probability_high(~%image_id%~)
	SET image_total = $fx_probability(~%image_id%~)
	SET image_count = 0
	CLEAR_ARRAY image_members
	PHP_EACH fx_ids_159 AS _ => image_other BEGIN
		SET image_other_amount = $fx_parameter1(~%image_other%~)
		PATCH_IF image_other != image_id AND image_other_amount > 0 AND image_other_amount <= 65535 AND NOT $fx_consumed(~%image_other%~) BEGIN
			SET same_other = image_other
			LPM ad_fx_same_fields
			PATCH_IF fx_same BEGIN
				SET $image_members(~%image_other%~) = 1
				SET image_count += 1
				SET image_min = image_other_amount < image_min ? image_other_amount : image_min
				SET image_max = image_other_amount > image_max ? image_other_amount : image_max
				SET image_low = $fx_probability_low(~%image_other%~) < image_low ? $fx_probability_low(~%image_other%~) : image_low
				SET image_high = $fx_probability_high(~%image_other%~) > image_high ? $fx_probability_high(~%image_other%~) : image_high
				SET image_total += $fx_probability(~%image_other%~)
			END
		END
	END
	// Plages disjointes et sans trou : leur somme est la largeur de leur union.
	PATCH_IF image_count > 0 AND image_total != image_high - image_low + 1 BEGIN
		LPF ad_refusal INT_VAR fx_id = image_id STR_VAR reason = ~not_implemented:opcode159:group~ message = ~several mirror image effects differing only by the amount, with overlapping or separate probability ranges~ RET render_missing = refusal END
	END
	ELSE PATCH_IF image_count > 0 BEGIN
		PHP_EACH image_members AS image_other => _ BEGIN
			SET $fx_consumed(~%image_other%~) = 1
		END
		SET $fx_image_min(~%image_id%~) = image_min
		SET $fx_image_max(~%image_id%~) = image_max
		SET $fx_probability_low(~%image_id%~) = image_low
		SET $fx_probability_high(~%image_id%~) = image_high
		SET $fx_probability(~%image_id%~) = image_total
		SET $fx_late(~%image_id%~) = 2
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
	PATCH_IF VARIABLE_IS_SET $fx_image_max(~%line_fx%~) AND $fx_image_max(~%line_fx%~) > 0 BEGIN
		SET amountMin = $fx_image_min(~%line_fx%~)
		SET amountMax = $fx_image_max(~%line_fx%~)
		LPF ad_tra INT_VAR tra_id = 21270000 RET amount = text END // ~entre %amountMin% et %amountMax%~
		SET state_variant = 1
	END
END
