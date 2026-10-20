// Opcode 74 (State: Blindness) : « Aveugle la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_74_support BEGIN END

DEFINE_PATCH_MACRO ad_op_74_lines BEGIN
	SET state_opcode = 74
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
