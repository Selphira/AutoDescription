// Opcode 19, intelligence (Stat: Intelligence Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_19_support BEGIN
	SET stat_opcode = 19
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_19_lines BEGIN
	SET stat_opcode = 19
	LPM ad_stat_modifier_lines
END
