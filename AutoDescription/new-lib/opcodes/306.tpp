// Opcode 306 (Stat: THAC0 Modifier (On-Hand)) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_306_support BEGIN
	SET stat_opcode = 306
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_306_lines BEGIN
	SET stat_opcode = 306
	LPM ad_stat_modifier_lines
END
