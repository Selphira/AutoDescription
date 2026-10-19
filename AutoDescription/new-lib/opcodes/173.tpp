// Opcode 173 (Stat: Poison Resistance Modifier) : résistance, code commun dans
// new-lib/opcodes/resistances.tpp.

DEFINE_PATCH_MACRO ad_op_173_support BEGIN
	SET stat_opcode = 173
	SPRINT stat_mode_3 ~invalid~
	// IESDP : parameter2 est ignoré ; l'opcode fixe la résistance sur les jeux classiques et EE
	// jusqu'à la v2.3, l'augmente depuis la v2.5 (EE, comme l'ancien moteur).
	SET stat_forced_mode = IS_EE ? MOD_TYPE_cumulative : MOD_TYPE_flat
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_173_lines BEGIN
	SET stat_opcode = 173
	LPM ad_resistance_lines
END
