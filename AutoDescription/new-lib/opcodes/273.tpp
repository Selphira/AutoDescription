// Opcode 273 (Remove: Specific Area Effect) : « Disperse les nuages dans la zone d'effet » ; code commun dans new-lib/opcodes/states.tpp.

// Refus : sur EE, une table de nuages autre que CLEARAIR, dont l'ancien moteur n'écrit rien
// (opcode_273_common).
DEFINE_PATCH_MACRO ad_op_273_support BEGIN
	PHP_EACH fx_ids_273 AS _ => clear_id BEGIN
		SPRINT clear_table $fx_resource(~%clear_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND IS_EE AND NOT (~%clear_table%~ STRING_EQUAL ~~) AND NOT (~%clear_table%~ STRING_EQUAL_CASE ~CLEARAIR~) BEGIN
			LPF ad_refusal INT_VAR fx_id = clear_id STR_VAR reason = ~not_implemented:opcode273:table~ message = ~clouds listed in %clear_table%.2da~ RET render_missing = refusal END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_273_lines BEGIN
	SET state_opcode = 273
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
