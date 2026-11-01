// Opcode 325 (Stat: Save vs. all, EE) : tous les jets de sauvegarde, modificateur simple, code commun
// dans new-lib/opcodes/stat_modifiers.tpp ; le mode 3 est un ajout (IESDP, ancien opcode_self_325).

DEFINE_PATCH_MACRO ad_op_325_support BEGIN
	SET stat_opcode = 325
	SPRINT stat_mode_3 ~added~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_325_lines BEGIN
	SET stat_opcode = 325
	LPM ad_stat_modifier_lines
END
