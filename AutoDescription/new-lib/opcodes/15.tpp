// Opcode 15, dextérité (Stat: Dexterity Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_15_support BEGIN
	SET stat_opcode = 15
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_15_lines BEGIN
	SET stat_opcode = 15
	LPM ad_stat_modifier_lines
END
