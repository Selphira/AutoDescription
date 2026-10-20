// Opcode 128 (State: Confusion) : « Inflige Confusion à la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_128_support BEGIN END

DEFINE_PATCH_MACRO ad_op_128_lines BEGIN
	SET state_opcode = 128
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
