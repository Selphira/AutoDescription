// Opcode 292 (Protection: Backstab) : parameter2 non nul immunise contre les attaques sournoises,
// 0 y rend sensible ; code commun dans lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_292_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0 ? 1 : 0
END
