// Opcode 24 (State: Horror) : « Inflige Horreur à la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_24_support BEGIN END

DEFINE_PATCH_MACRO ad_op_24_lines BEGIN
	SET state_opcode = 24
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
