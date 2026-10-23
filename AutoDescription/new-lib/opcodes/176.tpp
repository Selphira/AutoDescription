// Opcode 176 (Stat: Movement Modifier II) : décrit comme l'opcode 126 (ancien opcode_self_176), code
// commun dans new-lib/opcodes/stat_modifiers.tpp et cas particuliers de new-lib/opcodes/126.tpp.

// Refus : vitesse rétablie (100 %), que l'ancien opcode_176_group réunit à l'action libre comme pour
// l'opcode 126, regroupement que ad_group_movement_restored ne fait que pour le 126.
DEFINE_PATCH_MACRO ad_op_176_support BEGIN
	PHP_EACH fx_ids_176 AS _ => stat_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF IS_EE AND $fx_parameter2(~%stat_id%~) == 5 BEGIN
				SET $fx_parameter2(~%stat_id%~) = MOD_TYPE_percentage
			END
			PATCH_IF $fx_parameter2(~%stat_id%~) == MOD_TYPE_percentage AND $fx_parameter1(~%stat_id%~) == 100 BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode176:restored~ message = ~movement rate restored to its normal value (100 percent)~ RET render_missing = refusal END
			END
		END
	END
	SET stat_opcode = 176
	SPRINT stat_mode_3 ~invalid~
	SPRINT stat_percent_100 ~valid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_176_lines BEGIN
	SET stat_opcode = 176
	SPRINT stat_line_macro ~ad_op_126_line~
	LPM ad_stat_modifier_lines
END
