// Opcode 191 (Spell: Casting Level Modifier) : parameter1 = bonus de niveau de lanceur, parameter2
// 0 sorts profanes, 1 sorts divins ; « Niveau de lanceur de sorts profanes : +1 ». Modificateur
// simple (ajout), code commun dans new-lib/opcodes/stat_modifiers.tpp. Comme l'ancien
// get_spell_type_str, le type divin dépend des classes qui peuvent utiliser l'objet : « divins »,
// « druidiques » ou « divins/druidiques » (ad_spell_slots_priest_type,
// new-lib/opcodes/spell_slots.tpp).

// L'ancien moteur lit l'octet de poids faible de parameter1 (un bonus négatif devient 255) et
// écarte un type inconnu.
DEFINE_PATCH_MACRO ad_op_191_support BEGIN
	PHP_EACH fx_ids_191 AS _ => stat_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET caster_type = $fx_parameter2(~%stat_id%~)
			SET caster_bonus = $fx_parameter1(~%stat_id%~)
			PATCH_IF caster_type < 0 OR caster_type > 1 OR caster_bonus < 0 OR caster_bonus > 255 BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~file_error:opcode191:invalid~ message = ~invalid spell type or bonus (type %caster_type% expected 0-1, bonus %caster_bonus% expected 0-255)~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET $fx_stat_subject(~%stat_id%~) = 8020000
				PATCH_IF caster_type == 1 BEGIN
					LPM ad_spell_slots_priest_type
					PATCH_IF slots_priest_type < 0 BEGIN
						LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode191:no_priest~ message = ~no priest class in this game~ RET render_missing = refusal END
					END
					SET $fx_stat_subject(~%stat_id%~) = 8020000 + slots_priest_type
				END
				SET $fx_parameter2(~%stat_id%~) = MOD_TYPE_cumulative
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		SET stat_opcode = 191
		SPRINT stat_mode_3 ~invalid~
		LPM ad_stat_modifier_support
	END
END

DEFINE_PATCH_MACRO ad_op_191_lines BEGIN
	SET stat_opcode = 191
	SPRINT stat_line_macro ~ad_op_191_line~
	LPM ad_stat_modifier_lines
END

// Aux formes probables, l'ancien moteur écrit le nom de la statistique au lieu de « le niveau de
// lanceur de sorts » : refusé.
DEFINE_PATCH_MACRO ad_op_191_line BEGIN
	LPF ad_tra INT_VAR tra_id = $fx_stat_subject(~%line_fx%~) tra_block_start = 8020000 tra_block_size = 10 RET spellType = text END // ~divins/druidiques~
	PATCH_IF line_form >= 2 BEGIN
		LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:opcode191:form%line_form%~ message = ~probable effect~ RET render_late_missing = refusal END
		SET stat_line_done = 1
	END
END
