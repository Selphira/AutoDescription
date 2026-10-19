// Opcode 73 (Stat: Extra Damage Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_73_support BEGIN
	SET stat_opcode = 73
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_73_lines BEGIN
	SET stat_opcode = 73
	LPM ad_stat_modifier_lines
END
