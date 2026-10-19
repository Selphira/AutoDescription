// Opcode 84 (Stat: Magical Fire Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_84_support BEGIN
	SET stat_opcode = 84
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_84_lines BEGIN
	SET stat_opcode = 84
	LPM ad_resistance_lines
END
