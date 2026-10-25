// Opcode 192 (Spell Effect: Find Familiar) : « Invocation du familier » ; forme « soi » seulement, comme
// dans l'ancien moteur ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_192_support BEGIN END

DEFINE_PATCH_MACRO ad_op_192_lines BEGIN
	SET state_opcode = 192
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
