// Opcode 276 (Stat: Detect Illusion Modifier) : compétence de voleur, modificateur simple en pourcentage, code
// commun dans new-lib/opcodes/stat_modifiers.tpp ; regroupée avec les six autres par
// ad_group_thief_skills (new-lib/groups.tpp).

DEFINE_PATCH_MACRO ad_op_276_support BEGIN
	SET stat_opcode = 276
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_276_lines BEGIN
	SET stat_opcode = 276
	LPM ad_stat_modifier_lines
END
