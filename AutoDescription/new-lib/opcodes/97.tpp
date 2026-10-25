// Opcode 97 (Stat: Exceptional Strength Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp ; une valeur fixée est réunie à une Force fixée par la passe
// des regroupements entre opcodes (ad_group_exceptional_strength, new-lib/groups.tpp).

DEFINE_PATCH_MACRO ad_op_97_support BEGIN
	SET stat_opcode = 97
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
	// Cas où l'ancien moteur réunit une Force exceptionnelle fixée autrement que prévu : la même
	// Force peut aller aux six caractéristiques selon l'ordre des opcodes dans le fichier.
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		PHP_EACH fx_ids_97 AS _ => stat_id BEGIN
			PATCH_IF $fx_parameter2(~%stat_id%~) == MOD_TYPE_flat AND VARIABLE_IS_SET $fx_opcode_count(~6~) BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode97:with_abilities~ message = ~exceptional strength with other abilities~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_97_lines BEGIN
	SET stat_opcode = 97
	LPM ad_stat_modifier_lines
END
