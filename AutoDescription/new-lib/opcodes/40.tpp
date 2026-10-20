// Opcode 40 (State: Slow) : « Inflige lenteur à la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_40_support BEGIN END

DEFINE_PATCH_MACRO ad_op_40_lines BEGIN
	SET state_opcode = 40
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
