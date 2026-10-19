// Opcode 87 (Stat: Crushing Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_87_support BEGIN
	SET stat_opcode = 87
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_87_lines BEGIN
	SET stat_opcode = 87
	LPM ad_resistance_lines
END
