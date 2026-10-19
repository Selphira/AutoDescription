// Opcode 34, jet de sauvegarde contre les baguettes (Stat: Save vs. Wands Modifier) : code commun dans
// new-lib/opcodes/saving_throws.tpp.

DEFINE_PATCH_MACRO ad_op_34_support BEGIN
	SET stat_opcode = 34
	SPRINT stat_mode_3 ~added~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_34_lines BEGIN
	SET stat_opcode = 34
	LPM ad_saving_throw_lines
END
