// Opcode 99 (Spell Effect: Duration Modifier) : durée des sorts de la cible portée à parameter1 % de sa
// valeur (IESDP : 0 sans durée, 100 inchangée, 200 doublée) ; parameter2 0 sorts profanes, 1 divins,
// 2 chants du barde (EE) : « Allonge de 50 % la durée des sorts profanes », « Réduit à néant la durée
// des chants de barde ». Avec AD_ENABLE_SHRINKAGE, les effets qui ne diffèrent que par le type de sort
// profane ou divin sont réunis (ad_group_spell_types, new-lib/groups.tpp, fx_spell_types).
// Phrase : 2099 0100 + 10 × variante (0 durée nulle, 1 réduite, 2 allongée ; + 3 chants du barde).

// Écartés et journalisés : type inconnu (ancien opcode_99_is_valid) ; pourcentage négatif ou de 100,
// sans effet (l'ancien moteur écrivait « Réduit à néant la durée » pour 100).
DEFINE_PATCH_MACRO ad_op_99_support BEGIN
	PHP_EACH fx_ids_99 AS _ => duration_id BEGIN
		SET $fx_spell_types(~%duration_id%~) = 0
		SET duration_type = $fx_parameter2(~%duration_id%~)
		SET duration_percent = $fx_parameter1(~%duration_id%~)
		PATCH_IF NOT $fx_dropped(~%duration_id%~) AND (duration_type < 0 OR duration_type > (IS_EE ? 2 : 1)) BEGIN
			SET drop_id = duration_id
			SPRINT ignored_reason ~file_error:opcode99:type~
			SPRINT ignored_message ~spell type %duration_type% (expected 0-1, 2 on enhanced editions)~
			LPM ad_application_drop
		END
		ELSE PATCH_IF NOT $fx_dropped(~%duration_id%~) AND (duration_percent < 0 OR duration_percent == 100) BEGIN
			SET drop_id = duration_id
			SPRINT ignored_reason ~file_error:opcode99:invalid~
			SPRINT ignored_message ~duration percentage %duration_percent% (100 leaves durations unchanged)~
			LPM ad_application_drop
		END
	END
END

DEFINE_PATCH_MACRO ad_op_99_lines BEGIN
	SET state_opcode = 99
	SPRINT state_variant_macro ~ad_op_99_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_99_variant BEGIN
	SET duration_percent = $fx_parameter1(~%line_fx%~)
	SET duration_type = $fx_parameter2(~%line_fx%~)
	SET state_variant = duration_percent == 0 ? 0 : (duration_percent < 100 ? 1 : 2)
	SET value = ABS (duration_percent - 100)
	SPRINT duration @1200003 // ~%value%%PERCENT%~
	PATCH_IF duration_type == 2 BEGIN
		SET state_variant += 3
	END
	ELSE BEGIN
		SET duration_types = $fx_spell_types(~%line_fx%~)
		LPF ad_spell_types_text INT_VAR types = (duration_types == 0 ? 1 << duration_type : duration_types) RET spellType = text END
	END
END
