// Opcode 21 (Stat: Lore Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.
// Les timings 1, 4 et 7 seraient sans effet (ancien opcode_21_is_valid) ; seuls les effets
// d'équipement sont pris en charge.

DEFINE_PATCH_MACRO ad_op_21_support BEGIN
	SET stat_opcode = 21
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_21_lines BEGIN
	SET stat_opcode = 21
	LPM ad_stat_modifier_lines
END
