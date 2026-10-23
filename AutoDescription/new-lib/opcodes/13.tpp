// Opcode 13 (Death: Instant Death) : « Désintègre la cible » ; phrase selon le type de mort
// (parameter2, AD_DEATH_TYPES) ; code commun dans new-lib/opcodes/states.tpp.

// Un type de mort inconnu : l'ancien moteur écarte l'effet (opcode_13_is_valid).
DEFINE_PATCH_MACRO ad_op_13_support BEGIN
	PHP_EACH fx_ids_13 AS _ => state_id BEGIN
		SET state_death_type = $fx_parameter2(~%state_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT VARIABLE_IS_SET $AD_DEATH_TYPES(~%state_death_type%~) BEGIN
			LPF ad_refusal INT_VAR fx_id = state_id STR_VAR reason = ~not_implemented:opcode13:death_type~ message = ~death type %state_death_type% not supported~ RET render_missing = refusal END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_13_lines BEGIN
	SET state_opcode = 13
	SPRINT state_variant_macro ~ad_op_13_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_13_variant BEGIN
	SET state_death_type = $fx_parameter2(~%line_fx%~)
	SET state_variant = $AD_DEATH_TYPES(~%state_death_type%~)
END
