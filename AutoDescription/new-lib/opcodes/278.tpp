// Opcode 278 (Stat: To Hit Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_278_support BEGIN
	SET stat_opcode = 278
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_278_lines BEGIN
	SET stat_opcode = 278
	LPM ad_stat_modifier_lines
END
