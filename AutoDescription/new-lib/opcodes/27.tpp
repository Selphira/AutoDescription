// Opcode 27 (Stat: Acid Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_27_support BEGIN
	SET stat_opcode = 27
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_27_lines BEGIN
	SET stat_opcode = 27
	LPM ad_resistance_lines
END
