// Opcode 91 (Stat: Find Traps Modifier) : compétence de voleur, modificateur simple en pourcentage, code
// commun dans lib/opcodes/stat_modifiers.tpp ; regroupée avec les six autres par
// ad_group_same_fields (lib/groups.tpp, ligne THIEF_SKILLS de 2da/field_groups.2da).

DEFINE_PATCH_MACRO ad_op_91_support BEGIN
	SET stat_opcode = 91
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_91_lines BEGIN
	SET stat_opcode = 91
	LPM ad_stat_modifier_lines
END
