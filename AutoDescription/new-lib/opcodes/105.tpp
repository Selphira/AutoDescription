// Opcode 105 (Stat: Gold) : or de la cible, modificateur simple (code commun dans
// new-lib/opcodes/stat_modifiers.tpp) écrit par la phrase de la forme « cible » à toute forme, comme
// l'ancien opcode_self_105 : « Réduit de 10 la quantité de pièces d'or du porteur ». IESDP : un ajout
// ne fait que retirer de l'or, la valeur étant lue en négatif ; l'or ne descend pas sous 0. Comme
// l'ancien moteur, un ajout négatif s'écrit « Déleste le porteur de tout son or », un ajout positif
// comme une réduction, une valeur fixée négative comme 0.

DEFINE_PATCH_MACRO ad_op_105_support BEGIN
	SET stat_opcode = 105
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_105_lines BEGIN
	SET stat_opcode = 105
	SPRINT stat_line_macro ~ad_op_105_line~
	LPM ad_stat_modifier_lines
END

DEFINE_PATCH_MACRO ad_op_105_line BEGIN
	LPM ad_application_target_strings
	PATCH_IF stat_mode == MOD_TYPE_cumulative AND stat_value < 0 BEGIN
		SET line_phrase = 21050100 // ~Déleste %theTarget% de tout son or~
	END
	ELSE BEGIN
		PATCH_IF stat_mode == MOD_TYPE_cumulative BEGIN
			SET stat_value = 0 - stat_value
		END
		ELSE PATCH_IF stat_mode == MOD_TYPE_flat AND stat_value < 0 BEGIN
			SET stat_value = 0
		END
		LPF ad_tra INT_VAR tra_id = 21050002 RET theStatistic = text END // ~la quantité de pièces d'or~
		LPM ad_stat_modifier_phrase
		// Phrase de la forme « cible » à la forme « soi » : « … du porteur ».
		PATCH_IF line_form == 0 BEGIN
			SET line_phrase += 1
		END
	END
	SET line_any_form = 1
	LPM ad_effect_line
	SET stat_line_done = 1
END
