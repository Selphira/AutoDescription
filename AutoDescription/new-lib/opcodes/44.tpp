// Opcode 44, force (Stat: Strength Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_44_support BEGIN
	SET stat_opcode = 44
	// Mode 3 (EE) : l'ancien moteur le traite selon CLSSPLAB.2da, pas encore décrit.
	SPRINT stat_mode_3 ~unsupported~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_44_lines BEGIN
	SET stat_opcode = 44
	LPM ad_stat_modifier_lines
END
