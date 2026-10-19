// Opcode 85 (Stat: Magical Cold Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_85_support BEGIN
	SET stat_opcode = 85
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_85_lines BEGIN
	SET stat_opcode = 85
	LPM ad_resistance_lines
END
