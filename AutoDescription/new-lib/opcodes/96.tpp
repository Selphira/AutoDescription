// Opcode 96 (Stat: Level Change) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_96_support BEGIN
	SET stat_opcode = 96
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_96_lines BEGIN
	SET stat_opcode = 96
	LPM ad_stat_modifier_lines
END
