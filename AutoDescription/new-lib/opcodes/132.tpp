// Opcode 132 (State: Raise Strength, Constitution, & Dexterity Non-Cumulative) : « Force, dextérité
// et constitution : +1 (non cumulatif) » ; parameter2 ignoré, l'effet ne se cumule pas (IESDP).
// Modificateur simple, code commun dans new-lib/opcodes/stat_modifiers.tpp.

// Refus : parameter1 hors de 0-25 ; négatif, il fixe les trois caractéristiques à 25 (IESDP), que
// l'ancien moteur écrit « +25 », comme toute valeur au-delà de 25.
DEFINE_PATCH_MACRO ad_op_132_support BEGIN
	PHP_EACH fx_ids_132 AS _ => stat_id BEGIN
		SET stat_value = $fx_parameter1(~%stat_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND (stat_value < 0 OR stat_value > 25) BEGIN
			LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode132:value~ message = ~value %stat_value% outside 0-25 (a negative value sets the three statistics to 25)~ RET render_missing = refusal END
		END
	END
	SET stat_opcode = 132
	SET stat_forced_mode = MOD_TYPE_cumulative
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_132_lines BEGIN
	SET stat_opcode = 132
	SPRINT stat_line_macro ~ad_stat_modifier_not_cumulative_line~
	LPM ad_stat_modifier_lines
END
