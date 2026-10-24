// Opcode 208 (HP: Minimum Limit) : « Les points de vie ne peuvent passer en dessous de 1 », « Les points de
// vie ne sont plus protégés » pour 0 ; code commun dans new-lib/opcodes/states.tpp.

// Refus : parameter1 négatif ou au-delà de 32 767, que le jeu lit autrement (IESDP : points de vie
// négatifs, fixés, ou valeur ramenée au-delà de 98 303).
DEFINE_PATCH_MACRO ad_op_208_support BEGIN
	PHP_EACH fx_ids_208 AS _ => minimum_id BEGIN
		SET minimum_value = $fx_parameter1(~%minimum_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND (minimum_value < 0 OR minimum_value > 32767) BEGIN
			LPF ad_refusal INT_VAR fx_id = minimum_id STR_VAR reason = ~not_implemented:opcode208:value~ message = ~minimum %minimum_value% outside 0-32767~ RET render_missing = refusal END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_208_lines BEGIN
	SET state_opcode = 208
	SPRINT state_variant_macro ~ad_op_208_variant~
	LPM ad_state_lines
END

// Variante 1 : points de vie plus protégés.
DEFINE_PATCH_MACRO ad_op_208_variant BEGIN
	SET value = $fx_parameter1(~%line_fx%~)
	SET state_variant = value == 0
END
