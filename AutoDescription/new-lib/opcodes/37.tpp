// Opcode 37, jet de sauvegarde contre les sorts (Stat: Save vs. Spells Modifier) : code commun dans
// new-lib/opcodes/saving_throws.tpp.

DEFINE_PATCH_MACRO ad_op_37_support BEGIN
	SET stat_opcode = 37
	SPRINT stat_mode_3 ~added~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_37_lines BEGIN
	SET stat_opcode = 37
	LPM ad_saving_throw_lines
END
