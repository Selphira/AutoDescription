// Opcode 317 (State: Haste 2) : décrit comme l'opcode 16 (ad_op_16_variant, new-lib/opcodes/16.tpp),
// avec ses propres phrases ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_317_support BEGIN END

DEFINE_PATCH_MACRO ad_op_317_lines BEGIN
	SET state_opcode = 317
	SPRINT state_variant_macro ~ad_op_16_variant~
	LPM ad_state_lines
END
