// Opcode 23 (Stat: Morale Modifier) : sur un jeu classique, ou sur EE avec special 0, le jeu rétablit
// le moral (valeur 10 fixée, paramètres ignorés, IESDP) : « Rétabli le moral du porteur » ; sur EE
// avec special non nul, modificateur simple, code commun dans new-lib/opcodes/stat_modifiers.tpp.
// Avec AD_ENABLE_SHRINKAGE, un rétablissement disparaît devant les immunités à la modification du
// moral et à la panique (ad_group_morale, new-lib/groups.tpp).

DEFINE_PATCH_MACRO ad_op_23_support BEGIN
	FOR (stat_id = 0; stat_id < fx_count; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == 23 AND (NOT IS_EE OR $fx_special(~%stat_id%~) == 0) BEGIN
			SET $fx_parameter1(~%stat_id%~) = 10
			SET $fx_parameter2(~%stat_id%~) = MOD_TYPE_flat
		END
	END
	SET stat_opcode = 23
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_23_lines BEGIN
	SET stat_opcode = 23
	SPRINT stat_line_macro ~ad_op_23_line~
	LPM ad_stat_modifier_lines
END

// Un moral fixé à 10 est un rétablissement, comme dans l'ancien opcode_self_23.
DEFINE_PATCH_MACRO ad_op_23_line BEGIN
	PATCH_IF stat_value == 10 AND stat_mode == MOD_TYPE_flat BEGIN
		SET line_phrase = 20230110 // ~Rétabli le moral %ofTheTarget%~
		LPM ad_effect_line
		SET stat_line_done = 1
	END
END
