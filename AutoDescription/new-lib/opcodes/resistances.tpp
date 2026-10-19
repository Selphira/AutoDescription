// Code commun des modificateurs de résistance (27-31, 84-89) : modificateurs simples (prise en
// charge par ad_stat_modifier_support, new-lib/opcodes/stat_modifiers.tpp) d'une résistance en
// pourcentage. Libellés du bloc de l'opcode : 2OOO0000 nom (« Résistance à l'acide »), 2OOO0001
// complément d'une immunité (« à l'acide ») ; un effet dérivé suit la même convention (3NNN0000).

// Lignes (ancien opcode_self_<N> et opcode_self_resist) : une par effet non consommé par un
// regroupement.
DEFINE_PATCH_MACRO ad_resistance_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%stat_opcode%~)
	FOR (stat_id = 0; stat_id < fx_count; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == stat_opcode AND NOT $fx_consumed(~%stat_id%~) BEGIN
			SET stat_value = $fx_parameter1(~%stat_id%~)
			SET stat_mode = $fx_parameter2(~%stat_id%~)
			LPF ad_resistance_text INT_VAR value = stat_value mode = stat_mode name_tra = 20000000 + stat_opcode * 10000 RET line_text = text END
			SET line_fx = stat_id
			LPM ad_effect_line
		END
	END
END

// Une résistance fixée à 100 % est une immunité ; sinon « nom : +20 % », « Passe à 50 % »,
// « Multiplié par 50 % ».
DEFINE_PATCH_FUNCTION ad_resistance_text
	INT_VAR
		value = 0
		mode = 0
		name_tra = 0
	RET
		text
BEGIN
	PATCH_IF mode == MOD_TYPE_flat AND value == 100 BEGIN
		LPF ad_tra INT_VAR tra_id = name_tra + 1 RET resistName = text END
		SPRINT text @5000001 // ~Immunité %resistName%~
	END
	ELSE BEGIN
		LPF ad_stat_modifier_value INT_VAR value mode percent = 1 RET value = text END
		LPF ad_tra INT_VAR tra_id = name_tra RET name = text END
		SPRINT text @1200000 // ~%name%%AD_COLON%%value%~
	END
END
