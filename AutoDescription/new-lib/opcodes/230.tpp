// Opcode 230 (Removal: Remove One Secondary Type) : dissipe un sort d'un type secondaire ; code commun dans
// new-lib/opcodes/dispel_secondary_type.tpp.

DEFINE_PATCH_MACRO ad_op_230_support BEGIN
	SET dispel_type_opcode = 230
	LPM ad_dispel_type_support
END

DEFINE_PATCH_MACRO ad_op_230_lines BEGIN
	SET dispel_type_opcode = 230
	LPM ad_dispel_type_lines
END
