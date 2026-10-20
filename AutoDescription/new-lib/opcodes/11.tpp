// Opcode 11 (Cure: Poison) : « Neutralise les poisons infectant la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_11_support BEGIN END

DEFINE_PATCH_MACRO ad_op_11_lines BEGIN
	SET state_opcode = 11
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
