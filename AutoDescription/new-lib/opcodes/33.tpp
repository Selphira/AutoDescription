// Opcode 33, jet de sauvegarde contre la mort (Stat: Save vs. Death Modifier) : code commun dans
// new-lib/opcodes/saving_throws.tpp.

DEFINE_PATCH_MACRO ad_op_33_support BEGIN
	SET stat_opcode = 33
	SPRINT stat_mode_3 ~added~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_33_lines BEGIN
	SET stat_opcode = 33
	LPM ad_saving_throw_lines
END
