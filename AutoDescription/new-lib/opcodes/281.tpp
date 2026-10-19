// Opcode 281 (Stat: Wild Magic) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_281_support BEGIN
	SET stat_opcode = 281
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_281_lines BEGIN
	SET stat_opcode = 281
	LPM ad_stat_modifier_lines
END
