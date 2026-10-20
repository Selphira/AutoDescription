// Opcode 56 (Alignment: Invert) : « Inverse l'alignement du porteur » ; code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_56_support BEGIN END

DEFINE_PATCH_MACRO ad_op_56_lines BEGIN
	SET state_opcode = 56
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
