// Opcode 345 (Enchantment bonus, EE) : « Niveau d'enchantement des armes : +3 » ; parameter2 = type
// d'arme concerné (0 : bonus d'enchantement parameter1, IESDP), special = emplacement (0 arme
// équipée, 1 main directrice, 2 main secondaire, 3 les deux). Modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp. Un 345 d'un EFF (type d'objet dans parameter4) n'est pas
// remplacé (AD_OPCODES_EFF_FIELDS).

// Refus : parameter2 non nul (propriété de l'arme : argent, fer froid…), que l'ancien moteur ne
// décrit pas ; emplacement 1 ou 2, qu'il ne nomme que pour un EFF, et inconnu.
DEFINE_PATCH_MACRO ad_op_345_support BEGIN
	PHP_EACH fx_ids_345 AS _ => stat_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET enchantment_type = $fx_parameter2(~%stat_id%~)
			SET enchantment_slot = $fx_special(~%stat_id%~)
			PATCH_IF enchantment_type != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode345:type~ message = ~weapon type %enchantment_type% (only 0, enchantment level, is described)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF enchantment_slot != 0 AND enchantment_slot != 3 BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode345:slot~ message = ~weapon slot %enchantment_slot% (only 0, current weapon, and 3, both hands, are described)~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET $fx_stat_subject(~%stat_id%~) = enchantment_slot
			END
		END
	END
	SET stat_opcode = 345
	SET stat_forced_mode = MOD_TYPE_cumulative
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_345_lines BEGIN
	SET stat_opcode = 345
	SPRINT stat_line_macro ~ad_op_345_line~
	LPM ad_stat_modifier_lines
END

// Formes probables : absentes de l'ancien moteur (pas de macro opcode_*_probability_345), refusées.
DEFINE_PATCH_MACRO ad_op_345_line BEGIN
	PATCH_IF line_form >= 2 BEGIN
		LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:opcode345:form%line_form%~ message = ~probable effect~ RET render_late_missing = refusal END
		SET stat_line_done = 1
	END
	ELSE PATCH_IF $fx_special(~%line_fx%~) == 3 BEGIN
		SPRINT stat_name_suffix @23450013 // ~des armes~
	END
END
