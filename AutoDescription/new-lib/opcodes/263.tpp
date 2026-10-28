// Opcode 263, multiplicateur d'attaque sournoise (Stat: Backstab) : modificateur simple, code commun
// dans new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_263_support BEGIN
	SET stat_opcode = 263
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_263_lines BEGIN
	SET stat_opcode = 263
	LPM ad_stat_modifier_lines
END
