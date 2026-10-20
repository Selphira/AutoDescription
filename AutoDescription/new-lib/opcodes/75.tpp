// Opcode 75 (Cure: Blindness) : « Guérit la cécité de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_75_support BEGIN END

DEFINE_PATCH_MACRO ad_op_75_lines BEGIN
	SET state_opcode = 75
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
