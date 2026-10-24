// Opcode 303 (Spell Effect: Backstab Every Hit) : « Transforme toute attaque portée en attaque sournoise (si l'arme
// équipée l'autorise) », « Bloque la capacité… » pour parameter2 0 ; code commun dans new-lib/opcodes/states.tpp.

// Refus : parameter2 qui n'ignore que l'invisibilité (2) ou que la position (4) sur EE ou avec ToBEx
// (IESDP), que l'ancien moteur décrit comme toute attaque sournoise.
DEFINE_PATCH_MACRO ad_op_303_support BEGIN
	PHP_EACH fx_ids_303 AS _ => backstab_id BEGIN
		SET backstab_mode = $fx_parameter2(~%backstab_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND backstab_mode != 0 AND (backstab_mode BAND BIT0) == 0 AND (backstab_mode BAND (BIT1 BOR BIT2)) != (BIT1 BOR BIT2) BEGIN
			LPF ad_refusal INT_VAR fx_id = backstab_id STR_VAR reason = ~not_implemented:opcode303:mode~ message = ~mode %backstab_mode% ignores only invisibility or only position~ RET render_missing = refusal END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_303_lines BEGIN
	SET state_opcode = 303
	SPRINT state_variant_macro ~ad_op_303_variant~
	LPM ad_state_lines
END

// Variante 1 : capacité bloquée.
DEFINE_PATCH_MACRO ad_op_303_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0
END
