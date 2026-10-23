// Opcode 20 (State: Invisibility) : parameter2 0 invisibilité, 1 invisibilité majeure,
// « Lance « Invisibilité » sur la cible » ; une invisibilité majeure remplace l'invisibilité de mêmes
// champs (ad_group_improved_invisibility, new-lib/groups.tpp) ; code commun dans
// new-lib/opcodes/states.tpp.

// Les autres valeurs de parameter2 (EE) : l'ancien moteur les décrit comme une invisibilité majeure.
DEFINE_PATCH_MACRO ad_op_20_support BEGIN
	PHP_EACH fx_ids_20 AS _ => state_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND $fx_parameter2(~%state_id%~) != 0 AND $fx_parameter2(~%state_id%~) != 1 BEGIN
			LPF ad_refusal INT_VAR fx_id = state_id STR_VAR reason = ~not_implemented:opcode20:type~ message = ~invisibility type (parameter2) not supported~ RET render_missing = refusal END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_20_lines BEGIN
	SET state_opcode = 20
	SPRINT state_variant_macro ~ad_op_20_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_20_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~)
END
