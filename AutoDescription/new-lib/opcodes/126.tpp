// Opcode 126 (Stat: Movement Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp ; sur EE, parameter2 5 vaut un pourcentage. Une vitesse fixée à
// 0, ou réduite à 0 %, s'écrit « Immobilisation », une vitesse à 100 % « Rétablissement de la vitesse
// de déplacement », qui absorbe l'action libre de mêmes probabilités avec AD_ENABLE_SHRINKAGE
// (ad_group_movement_restored, new-lib/groups.tpp).

DEFINE_PATCH_MACRO ad_op_126_support BEGIN
	FOR (stat_id = 0; stat_id < fx_count; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == 126 AND IS_EE AND $fx_parameter2(~%stat_id%~) == 5 BEGIN
			SET $fx_parameter2(~%stat_id%~) = MOD_TYPE_percentage
		END
	END
	SET stat_opcode = 126
	SPRINT stat_mode_3 ~invalid~
	SPRINT stat_percent_100 ~valid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_126_lines BEGIN
	SET stat_opcode = 126
	SPRINT stat_line_macro ~ad_op_126_line~
	LPM ad_stat_modifier_lines
END

// Cas particuliers de l'ancien opcode_126_common.
DEFINE_PATCH_MACRO ad_op_126_line BEGIN
	SET line_phrase = 0
	PATCH_IF stat_value == 0 AND stat_mode >= MOD_TYPE_flat BEGIN
		SET line_phrase = 21260110 // ~Immobilisation~
	END
	ELSE PATCH_IF stat_value == 100 AND stat_mode == MOD_TYPE_percentage BEGIN
		SET line_phrase = 21260120 // ~Rétablissement de la vitesse de déplacement~
	END
	PATCH_IF line_phrase > 0 BEGIN
		LPM ad_effect_line
		SET stat_line_done = 1
	END
END
