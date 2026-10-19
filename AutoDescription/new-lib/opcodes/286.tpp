// Opcode 286 (Stat: Missile Weapon Damage Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_286_support BEGIN
	SET stat_opcode = 286
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_286_lines BEGIN
	SET stat_opcode = 286
	LPM ad_stat_modifier_lines
END
