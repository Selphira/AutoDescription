// Opcode 49, sagesse (Stat: Wisdom Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_49_support BEGIN
	SET stat_opcode = 49
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_49_lines BEGIN
	SET stat_opcode = 49
	LPM ad_stat_modifier_lines
END
