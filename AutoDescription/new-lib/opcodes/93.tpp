// Opcode 93 (Stat: Fatigue Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_93_support BEGIN
	SET stat_opcode = 93
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_93_lines BEGIN
	SET stat_opcode = 93
	LPM ad_stat_modifier_lines
END
