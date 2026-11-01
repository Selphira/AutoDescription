// Opcode 362 (Critical miss bonus, EE) ; code commun dans new-lib/opcodes/critical_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_362_support BEGIN
	SET critical_opcode = 362
	LPM ad_critical_support
END

DEFINE_PATCH_MACRO ad_op_362_lines BEGIN
	SET critical_opcode = 362
	SET critical_name_base = 23620001 // ~Chance d'échec critique~
	LPM ad_critical_lines
END
