// Opcode 288 (Stat: Fist THAC0 Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_288_support BEGIN
	SET stat_opcode = 288
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_288_lines BEGIN
	SET stat_opcode = 288
	LPM ad_stat_modifier_lines
END
