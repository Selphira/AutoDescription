// Opcode 292 (Protection: Backstab) : parameter2 non nul immunise contre les attaques sournoises,
// 0 y rend sensible ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_292_support BEGIN END

DEFINE_PATCH_MACRO ad_op_292_lines BEGIN
	SET state_opcode = 292
	SPRINT state_variant_macro ~ad_op_292_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_292_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0 ? 1 : 0
END
