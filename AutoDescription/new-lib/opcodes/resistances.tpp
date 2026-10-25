// Code commun des modificateurs de résistance (27-31, 84-89) : modificateurs simples (prise en
// charge par ad_stat_modifier_support, new-lib/opcodes/stat_modifiers.tpp) d'une résistance en
// pourcentage. Libellés du bloc de l'opcode : 2OOO0000 nom (« Résistance à l'acide »), 2OOO0001
// complément d'une immunité (« à l'acide »), 2OOO0002 statistique d'une phrase à la forme « cible »
// (« la résistance à l'acide ») ; un effet dérivé suit la même convention (3NNN0000).

// Lignes (ancien opcode_self_<N> et opcode_self_resist) : une par effet non consommé par un
// regroupement. Une progression selon le niveau du sort (fx_level_value, new-lib/spell_levels.tpp)
// remplace la valeur : « Résistance à la magie : 10 % + 1 % par niveau du lanceur/20 ».
DEFINE_PATCH_MACRO ad_resistance_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%stat_opcode%~)
	PHP_EACH ~fx_ids_%stat_opcode%~ AS _ => stat_id BEGIN
		PATCH_IF NOT $fx_consumed(~%stat_id%~) BEGIN
			SET stat_value = $fx_parameter1(~%stat_id%~)
			SET stat_mode = $fx_parameter2(~%stat_id%~)
			SET line_fx = stat_id
			SPRINT stat_level_value $fx_level_value(~%stat_id%~)
			LPM ad_application_form
			PATCH_IF line_form == 0 BEGIN
				LPF ad_resistance_text INT_VAR value = stat_value mode = stat_mode name_tra = 20000000 + stat_opcode * 10000
					STR_VAR level_value = ~%stat_level_value%~ RET line_text = text END
			END
			ELSE BEGIN
				SET resist_name_tra = 20000000 + stat_opcode * 10000
				LPM ad_resistance_target_phrase
			END
			LPM ad_effect_line
		END
	END
END

// Phrase à la forme « cible » de la résistance de libellés resist_name_tra (nom, + 1 complément d'une
// immunité, + 2 statistique), de valeur stat_value, de mode stat_mode et de progression
// stat_level_value (ancien opcode_target_resist et opcode_probability_resist) : line_phrase,
// identifiant de base d'une série de 5 000 1x0 selon le mode (10 augmentation, 20 réduction, 30
// valeur fixée, 40 multiplication, 50 immunité), et ses variables value et theStatistic (resistName
// pour une immunité) ; sans
// statistique dans le .tra, pas de phrase.
DEFINE_PATCH_MACRO ad_resistance_target_phrase BEGIN
	SET stat_statistic_tra = resist_name_tra + 2
	SET line_phrase = 0
	PATCH_IF TRA_ENTRY_EXISTS (~%stat_statistic_tra%~) BEGIN
		LPF ad_tra INT_VAR tra_id = stat_statistic_tra RET theStatistic = text END
		SET value = (stat_mode == MOD_TYPE_flat OR stat_mode == MOD_TYPE_percentage) ? stat_value : ABS stat_value
		SPRINT value @1200003 // ~%value%%PERCENT%~
		PATCH_IF NOT (~%stat_level_value%~ STRING_EQUAL ~~) BEGIN
			SPRINT value ~%stat_level_value%~
			PATCH_IF stat_value < 0 BEGIN
				LPF ad_level_unsigned STR_VAR text = ~%stat_level_value%~ RET value = text END
			END
		END
		PATCH_IF stat_mode == MOD_TYPE_flat AND stat_value == 100 BEGIN
			LPF ad_tra INT_VAR tra_id = stat_statistic_tra - 1 RET resistName = text END
			SET line_phrase = 5000150 // ~Immunise %theTarget% %resistName%~ (+1)
		END
		ELSE PATCH_IF stat_mode == MOD_TYPE_flat BEGIN
			SET line_phrase = 5000130 // ~Porte à %value% %theStatistic% %ofTheTarget%~ (+1)
		END
		ELSE PATCH_IF stat_mode == MOD_TYPE_percentage BEGIN
			SET line_phrase = 5000140 // ~Multiplie par %value% %theStatistic% %ofTheTarget%~ (+1)
		END
		ELSE PATCH_IF stat_value >= 0 BEGIN
			SET line_phrase = 5000110 // ~Augmente de %value% %theStatistic% %ofTheTarget%~ (+1)
		END
		ELSE BEGIN
			SET line_phrase = 5000120 // ~Réduit de %value% %theStatistic% %ofTheTarget%~ (+1)
		END
	END
END

// Une résistance fixée à 100 % est une immunité ; sinon « nom : +20 % », « Passe à 50 % »,
// « Multiplié par 50 % », ou « nom : » suivi de la progression level_value, sans « + ».
DEFINE_PATCH_FUNCTION ad_resistance_text
	INT_VAR
		value = 0
		mode = 0
		name_tra = 0
	STR_VAR
		level_value = ~~
	RET
		text
BEGIN
	PATCH_IF mode == MOD_TYPE_flat AND value == 100 BEGIN
		LPF ad_tra INT_VAR tra_id = name_tra + 1 RET resistName = text END
		SPRINT text @5000001 // ~Immunité %resistName%~
	END
	ELSE BEGIN
		LPF ad_stat_modifier_value INT_VAR value mode percent = 1 RET value = text END
		PATCH_IF NOT (~%level_value%~ STRING_EQUAL ~~) BEGIN
			SPRINT value ~%level_value%~
		END
		LPF ad_tra INT_VAR tra_id = name_tra RET name = text END
		SPRINT text @1200000 // ~%name%%AD_COLON%%value%~
	END
END
