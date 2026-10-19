// Opcode 88 (Stat: Piercing Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_88_support BEGIN
	SET stat_opcode = 88
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_88_lines BEGIN
	SET stat_opcode = 88
	LPM ad_resistance_lines
END
