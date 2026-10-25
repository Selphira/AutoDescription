// Opcode 124 (Spell Effect: Teleport (Dimension Door)) : « Téléporte le lanceur » ; parameter2 = destination
// (IESDP : 0 défaut, 1 de la source vers la cible, 2 lieu enregistré, 3 échange de la source et de la
// cible) ; code commun dans new-lib/opcodes/states.tpp.

// Refus : destination hors de 0-3, que l'ancien moteur décrit comme la destination par défaut.
DEFINE_PATCH_MACRO ad_op_124_support BEGIN
	PHP_EACH fx_ids_124 AS _ => teleport_id BEGIN
		SET teleport_type = $fx_parameter2(~%teleport_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND (teleport_type < 0 OR teleport_type > 3) BEGIN
			LPF ad_refusal INT_VAR fx_id = teleport_id STR_VAR reason = ~not_implemented:opcode124:type~ message = ~type %teleport_type% (expected 0-3)~ RET render_missing = refusal END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_124_lines BEGIN
	SET state_opcode = 124
	SPRINT state_variant_macro ~ad_op_124_variant~
	LPM ad_state_lines
END

// Variante : destination parameter2.
DEFINE_PATCH_MACRO ad_op_124_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~)
END
