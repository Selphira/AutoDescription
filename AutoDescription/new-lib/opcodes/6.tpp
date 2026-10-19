// Opcode 6, charisme (Stat: Charisma Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_6_support BEGIN
	SET stat_opcode = 6
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_6_lines BEGIN
	SET stat_opcode = 6
	LPM ad_stat_modifier_lines
END
