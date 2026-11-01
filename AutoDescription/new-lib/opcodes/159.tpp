// Opcode 159 (Spell Effect: Mirror Image (Exact Number)) : « Crée 1 image miroir sur le lanceur »,
// parameter1 images (l'ancien moteur lit son mot de poids faible) ; 0 : « Dissipe les images-miroir… » ;
// code commun dans new-lib/opcodes/states.tpp.

// Avec AD_ENABLE_SHRINKAGE, des effets semblables au nombre d'images et à la probabilité près, dont les
// plages de tirage sont contiguës et disjointes (un nombre d'images au hasard), n'en font qu'un
// (new-lib/opcodes/value_ranges.tpp) : « Crée entre 1 et 4 images miroir » (ancien opcode_159_group).
// Refus : parameter1 hors de 0-65 535 ; avec AD_ENABLE_SHRINKAGE, d'autres effets semblables au nombre
// d'images près, que l'ancien opcode_159_group réunit aussi alors qu'ils s'appliquent ensemble.
DEFINE_PATCH_MACRO ad_op_159_support BEGIN
	PHP_EACH fx_ids_159 AS _ => image_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%image_id%~) BEGIN
			SET image_amount = $fx_parameter1(~%image_id%~)
			PATCH_IF image_amount < 0 OR image_amount > 65535 BEGIN
				LPF ad_refusal INT_VAR fx_id = image_id STR_VAR reason = ~not_implemented:opcode159:value~ message = ~amount %image_amount% outside 0-65535~ RET render_missing = refusal END
			END
		END
	END
	SET range_opcode = 159
	SPRINT range_eligible_macro ~~
	LPM ad_value_range_support
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
	LPM ad_value_range_text
	PATCH_IF NOT (~%range_text%~ STRING_EQUAL ~~) BEGIN
		SPRINT amount ~%range_text%~
		SET state_variant = 1
	END
END
