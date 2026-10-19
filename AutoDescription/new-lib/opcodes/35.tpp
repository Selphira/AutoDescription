// Opcode 35, jet de sauvegarde contre la pétrification (Stat: Save vs. Petrification/Polymorph Modifier) : code commun dans
// new-lib/opcodes/saving_throws.tpp.

DEFINE_PATCH_MACRO ad_op_35_support BEGIN
	SET stat_opcode = 35
	SPRINT stat_mode_3 ~added~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_35_lines BEGIN
	SET stat_opcode = 35
	LPM ad_saving_throw_lines
END
