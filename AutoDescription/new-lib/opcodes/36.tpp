// Opcode 36, jet de sauvegarde contre les souffles (Stat: Save vs. Breath Weapons Modifier) : code commun dans
// new-lib/opcodes/saving_throws.tpp.

DEFINE_PATCH_MACRO ad_op_36_support BEGIN
	SET stat_opcode = 36
	SPRINT stat_mode_3 ~added~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_36_lines BEGIN
	SET stat_opcode = 36
	LPM ad_saving_throw_lines
END
