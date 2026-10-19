// Opcode 285 (Stat: Melee Weapon Damage Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_285_support BEGIN
	SET stat_opcode = 285
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_285_lines BEGIN
	SET stat_opcode = 285
	LPM ad_stat_modifier_lines
END
