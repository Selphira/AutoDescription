// Opcode 104 (Stat: Experience Points) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_104_support BEGIN
	SET stat_opcode = 104
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_104_lines BEGIN
	SET stat_opcode = 104
	LPM ad_stat_modifier_lines
END
