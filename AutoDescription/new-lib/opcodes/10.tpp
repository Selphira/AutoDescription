// Opcode 10, constitution (Stat: Constitution Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_10_support BEGIN
	SET stat_opcode = 10
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_10_lines BEGIN
	SET stat_opcode = 10
	LPM ad_stat_modifier_lines
END
