// Opcode 250 (Spell Effect: Damage Modifier) : dégâts minimums des coups portés (IESDP), « Dégâts
// minimums : +20 » ; parameter2 ignoré. Modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_250_support BEGIN
	SET stat_opcode = 250
	SET stat_forced_mode = MOD_TYPE_cumulative
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_250_lines BEGIN
	SET stat_opcode = 250
	LPM ad_stat_modifier_lines
END
