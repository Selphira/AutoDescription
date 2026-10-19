// Opcode 166 (Stat: Magic Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_166_support BEGIN
	SET stat_opcode = 166
	SPRINT stat_mode_3 ~invalid~
	// IESDP : sur BG2 et EE, seuls les modes 0 et 1 existent.
	SPRINT stat_percentage ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_166_lines BEGIN
	SET stat_opcode = 166
	LPM ad_resistance_lines
END
