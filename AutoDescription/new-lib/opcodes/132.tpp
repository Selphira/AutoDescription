// Opcode 132 (State: Raise Strength, Constitution, & Dexterity Non-Cumulative) : « Force, dextérité
// et constitution : +1 (non cumulatif) » ; parameter2 ignoré, l'effet ne se cumule pas (IESDP).
// Modificateur simple, code commun dans new-lib/opcodes/stat_modifiers.tpp.

// Seul le premier octet de parameter1 est lu (IESDP) : négatif (128-255), il fixe les trois
// caractéristiques à 25, « Passe à 25 » ; le mode est sinon un ajout, quel que soit parameter2.
// Refus : premier octet de 26 à 127, que l'ancien moteur écrit « +25 ».
DEFINE_PATCH_MACRO ad_op_132_support BEGIN
	PHP_EACH fx_ids_132 AS _ => stat_id BEGIN
		SET stat_value = $fx_parameter1(~%stat_id%~) BAND 255
		SET $fx_parameter2(~%stat_id%~) = MOD_TYPE_cumulative
		PATCH_IF stat_value >= 128 BEGIN
			SET $fx_parameter1(~%stat_id%~) = 25
			SET $fx_parameter2(~%stat_id%~) = MOD_TYPE_flat
		END
		ELSE BEGIN
			SET $fx_parameter1(~%stat_id%~) = stat_value
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND stat_value > 25 BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode132:value~ message = ~value %stat_value% (first byte of parameter1) over 25~ RET render_missing = refusal END
			END
		END
	END
	SET stat_opcode = 132
	SPRINT stat_forced_mode ~~
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_132_lines BEGIN
	SET stat_opcode = 132
	SPRINT stat_line_macro ~ad_stat_modifier_not_cumulative_line~
	LPM ad_stat_modifier_lines
END
