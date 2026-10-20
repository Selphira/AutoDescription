// Opcode 4 (Cure: Berserking) : « Apaise la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_4_support BEGIN END

DEFINE_PATCH_MACRO ad_op_4_lines BEGIN
	SET state_opcode = 4
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
