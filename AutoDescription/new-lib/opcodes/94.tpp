// Opcode 94 (Stat: Drunkenness Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_94_support BEGIN
	SET stat_opcode = 94
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_94_lines BEGIN
	SET stat_opcode = 94
	LPM ad_stat_modifier_lines
END
