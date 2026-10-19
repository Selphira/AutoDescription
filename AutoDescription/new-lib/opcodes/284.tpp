// Opcode 284 (Stat: Melee THAC0 Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_284_support BEGIN
	SET stat_opcode = 284
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_284_lines BEGIN
	SET stat_opcode = 284
	LPM ad_stat_modifier_lines
END
