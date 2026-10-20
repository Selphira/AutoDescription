// Opcode 81 (Cure: Deafness) : « Guérit la surdité de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_81_support BEGIN END

DEFINE_PATCH_MACRO ad_op_81_lines BEGIN
	SET state_opcode = 81
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
