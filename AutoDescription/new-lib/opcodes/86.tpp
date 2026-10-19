// Opcode 86 (Stat: Slashing Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_86_support BEGIN
	SET stat_opcode = 86
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_86_lines BEGIN
	SET stat_opcode = 86
	LPM ad_resistance_lines
END
