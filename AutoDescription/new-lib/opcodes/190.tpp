// Opcode 190 (Stat: Attack Speed Factor) : « Facteur de vitesse : Bonus de 1 (non cumulatif) » ;
// parameter1 est un bonus (IESDP : le facteur de vitesse va de 0, le meilleur, à 10), parameter2 est
// ignoré et l'effet ne se cumule pas (« (non cumulatif) » après la durée, ancien cumulable à 0).
// Modificateur simple, code commun dans new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_190_support BEGIN
	SET stat_opcode = 190
	SET stat_forced_mode = MOD_TYPE_cumulative
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_190_lines BEGIN
	SET stat_opcode = 190
	SPRINT stat_line_macro ~ad_op_190_line~
	LPM ad_stat_modifier_lines
END

// Forme « soi » : « Bonus de 1 » ou « Malus de 1 » (ancien opcode_self_190) ; aux autres formes, un
// bonus réduit le facteur de vitesse (« Réduit de 1 le facteur de vitesse de la cible »).
DEFINE_PATCH_MACRO ad_op_190_line BEGIN
	SET $fx_not_cumulative(~%line_fx%~) = 1
	PATCH_IF line_form == 0 BEGIN
		SET value = ABS stat_value
		SPRINT stat_level_value $fx_level_value(~%line_fx%~)
		PATCH_IF NOT (~%stat_level_value%~ STRING_EQUAL ~~) BEGIN
			LPF ad_level_unsigned STR_VAR text = ~%stat_level_value%~ RET value = text END
		END
		PATCH_IF stat_value >= 0 BEGIN
			SPRINT value @21900010 // ~Bonus de %value%~
		END
		ELSE BEGIN
			SPRINT value @21900011 // ~Malus de %value%~
		END
		SPRINT name @21900000 // ~Facteur de vitesse~
		SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
		LPM ad_effect_line
		SET stat_line_done = 1
	END
	ELSE BEGIN
		SET stat_value = 0 - stat_value
	END
END
