// Opcode 301 (Stat: Critical Hit Modifier, EE) ; code commun dans new-lib/opcodes/critical_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_301_support BEGIN
	SET critical_opcode = 301
	LPM ad_critical_support
END

DEFINE_PATCH_MACRO ad_op_301_lines BEGIN
	SET critical_opcode = 301
	SET critical_name_base = 23010001 // ~Chance de coup critique~
	LPM ad_critical_lines
END
