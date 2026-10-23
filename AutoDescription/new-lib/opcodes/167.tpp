// Opcode 167 (Stat: THAC0 Modifier with Missile Weapons) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp, « TAC0 : +2 avec les armes de trait et les armes de jet » ;
// l'ancien moteur ne lit que le mot de poids faible de parameter2.

DEFINE_PATCH_MACRO ad_op_167_support BEGIN
	PHP_EACH fx_ids_167 AS _ => stat_id BEGIN
		SET $fx_parameter2(~%stat_id%~) = $fx_parameter2(~%stat_id%~) BAND 65535
	END
	SET stat_opcode = 167
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_167_lines BEGIN
	SET stat_opcode = 167
	SPRINT stat_line_macro ~ad_op_167_line~
	LPM ad_stat_modifier_lines
END

// Forme « soi » : la valeur est suivie de « avec les armes de trait et les armes de jet ».
DEFINE_PATCH_MACRO ad_op_167_line BEGIN
	PATCH_IF line_form == 0 BEGIN
		LPF ad_stat_modifier_value INT_VAR value = stat_value mode = stat_mode RET value = text END
		SPRINT value @21670001 // ~%value% avec les armes de trait et les armes de jet~
		SPRINT name @21670000 // ~TAC0~
		SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
		LPM ad_effect_line
		SET stat_line_done = 1
	END
END
