// Opcode 22 (Stat: Cumulative Luck Bonus) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_22_support BEGIN
	SET stat_opcode = 22
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_22_lines BEGIN
	SET stat_opcode = 22
	LPM ad_stat_modifier_lines
END
