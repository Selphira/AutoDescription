// Opcode 305 (Stat: THAC0 Modifier (Off-Hand)) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_305_support BEGIN
	SET stat_opcode = 305
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_305_lines BEGIN
	SET stat_opcode = 305
	LPM ad_stat_modifier_lines
END
