// Opcode 221 (Removal: Remove Secondary Type) : dissipe tous les sorts d'un type secondaire ; code commun dans
// new-lib/opcodes/dispel_secondary_type.tpp.

DEFINE_PATCH_MACRO ad_op_221_support BEGIN
	SET dispel_type_opcode = 221
	LPM ad_dispel_type_support
END

DEFINE_PATCH_MACRO ad_op_221_lines BEGIN
	SET dispel_type_opcode = 221
	LPM ad_dispel_type_lines
END
