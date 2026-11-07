// Opcode 332 (Stat: Specific Damage Modifier, EE) : modifie de parameter1 % les dégâts du type
// parameter2 (0 tous, 1 feu, 2 froid, 3 électricité, 4 acide, 5 magie, 6 poison, 7 tranchants,
// 8 perforants, 9 contondants, 10 projectiles) : « Dégâts de feu : +10 % ».

// Valeur nulle ou type inconnu : écartés et journalisés (ancien opcode_332_is_valid). Avec
// AD_ENABLE_SHRINKAGE, les quatre types élémentaires (1 à 4) ou physiques (7 à 10) modifiés de la même
// façon n'en font qu'un, « Dégâts élémentaires » ou « Dégâts physiques » (ancien opcode_332_group,
// types 11 et 12 : $fx_damage_mod_type).
DEFINE_PATCH_MACRO ad_op_332_support BEGIN
	PHP_EACH fx_ids_332 AS _ => damage_mod_id BEGIN
		SET $fx_damage_mod_type(~%damage_mod_id%~) = $fx_parameter2(~%damage_mod_id%~)
	END
	PHP_EACH fx_ids_332 AS _ => damage_mod_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%damage_mod_id%~) BEGIN
			SET damage_mod_type = $fx_parameter2(~%damage_mod_id%~)
			PATCH_IF $fx_parameter1(~%damage_mod_id%~) == 0 OR damage_mod_type < 0 OR damage_mod_type > 10 BEGIN
				SET drop_id = damage_mod_id
				SPRINT ignored_reason ~file_error:opcode332:invalid~
				SPRINT ignored_message ~modifier of 0 or damage type %damage_mod_type% (expected 0-10)~
				LPM ad_application_drop
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND (damage_mod_type == 1 OR damage_mod_type == 7) BEGIN
				LPM ad_op_332_group_support
			END
		END
	END
END

// Les trois types qui suivent damage_mod_type, modifiés comme l'effet damage_mod_id : réunis à lui.
DEFINE_PATCH_MACRO ad_op_332_group_support BEGIN
	SET same_id = damage_mod_id
	SET same_ignored = AD_SAME_PARAMETER2
	SET damage_mod_found = 0
	PHP_EACH fx_ids_332 AS _ => damage_mod_other BEGIN
		SET damage_mod_offset = $fx_parameter2(~%damage_mod_other%~) - damage_mod_type
		PATCH_IF damage_mod_offset >= 1 AND damage_mod_offset <= 3 AND NOT $fx_consumed(~%damage_mod_other%~)
				AND (damage_mod_found BAND (1 << (damage_mod_offset - 1))) == 0 BEGIN
			SET same_other = damage_mod_other
			LPM ad_fx_same_fields
			PATCH_IF fx_same BEGIN
				SET damage_mod_found = damage_mod_found BOR (1 << (damage_mod_offset - 1))
				SET $damage_mod_members(~%damage_mod_offset%~) = damage_mod_other
			END
		END
	END
	PATCH_IF damage_mod_found == 7 BEGIN
		FOR (damage_mod_offset = 1; damage_mod_offset <= 3; ++damage_mod_offset) BEGIN
			SET damage_mod_other = $damage_mod_members(~%damage_mod_offset%~)
			SET $fx_consumed(~%damage_mod_other%~) = 1
		END
		SET $fx_damage_mod_type(~%damage_mod_id%~) = damage_mod_type == 1 ? 11 : 12
		// Ajouté en fin de liste par l'ancien add_opcode.
		SET $fx_late(~%damage_mod_id%~) = 1
	END
END

// Ligne « nom : valeur » à la forme « soi » (ancien opcode_self_332).
DEFINE_PATCH_MACRO ad_op_332_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~332~)
	PHP_EACH fx_ids_332 AS _ => damage_mod_id BEGIN
		PATCH_IF NOT $fx_consumed(~%damage_mod_id%~) BEGIN
			SET damage_mod_type = $fx_damage_mod_type(~%damage_mod_id%~)
			SET damage_mod_value = $fx_parameter1(~%damage_mod_id%~)
			SET line_fx = damage_mod_id
			LPM ad_application_form
			PATCH_IF line_form == 0 BEGIN
				LPF ad_tra INT_VAR tra_id = 23320000 + damage_mod_type tra_block_start = 23320000 tra_block_size = 13 RET name = text END // ~Dégâts de feu~ (@23320001)
				LPF ad_signed_value INT_VAR value = damage_mod_value RET value = text END
				SPRINT value @1200003 // ~%value%%PERCENT%~
				SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
				LPM ad_effect_line
			END
			ELSE BEGIN
				// Ancien opcode_target_332 : « Augmente de 10 % les dégâts de feu de la cible ».
				LPF ad_tra INT_VAR tra_id = 23320100 + damage_mod_type tra_block_start = 23320100 tra_block_size = 13 RET theStatistic = text END // ~les dégâts de feu~ (@23320101)
				SET stat_value = damage_mod_value
				SET stat_mode = MOD_TYPE_cumulative
				SET stat_percent = 1
				LPM ad_stat_modifier_phrase
				LPM ad_effect_line
			END
		END
	END
END
