// Opcode 29 (Stat: Electricity Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_29_support BEGIN
	SET stat_opcode = 29
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_29_lines BEGIN
	SET stat_opcode = 29
	LPM ad_resistance_lines
END
