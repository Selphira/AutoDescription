// Opcode 28 (Stat: Cold Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_28_support BEGIN
	SET stat_opcode = 28
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_28_lines BEGIN
	SET stat_opcode = 28
	LPM ad_resistance_lines
END
