// Opcode 165 (Spell Effect: Pause Target) : « Fige la cible » ; code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_165_support BEGIN END

DEFINE_PATCH_MACRO ad_op_165_lines BEGIN
	SET state_opcode = 165
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
