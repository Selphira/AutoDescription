// Opcode 95 (Stat: Tracking Skill Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_95_support BEGIN
	SET stat_opcode = 95
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_95_lines BEGIN
	SET stat_opcode = 95
	LPM ad_stat_modifier_lines
END
