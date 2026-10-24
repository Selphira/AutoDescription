// Opcode 346 (Save vs. school bonus, EE) : « Jets de sauvegarde : +3 contre les sorts de l'école de
// l'Enchantement » ; parameter2 0 ajoute la valeur, 1 la fixe (IESDP), special = école (mschool.2da).
// Modificateur simple, code commun dans new-lib/opcodes/stat_modifiers.tpp.

// Refus : école hors de 0-11 (ancien opcode_346_is_valid) ; école sans nom (0, 10, 11).
DEFINE_PATCH_MACRO ad_op_346_support BEGIN
	PHP_EACH fx_ids_346 AS _ => stat_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET save_school = $fx_special(~%stat_id%~)
			PATCH_IF save_school < 0 OR save_school > 11 BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~file_error:opcode346:invalid~ message = ~school %save_school% (expected 0-11)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF save_school < 1 OR save_school > 9 BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode346:school~ message = ~school %save_school% has no name~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET $fx_stat_subject(~%stat_id%~) = save_school
			END
		END
	END
	SET stat_opcode = 346
	SPRINT stat_percentage ~invalid~
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_346_lines BEGIN
	SET stat_opcode = 346
	SPRINT stat_line_macro ~ad_op_346_line~
	LPM ad_stat_modifier_lines
END

// Forme « soi » comme les jets de sauvegarde (ad_saving_throw_lines) ; forme « cible » : « Augmente de
// 3 les jets de sauvegarde contre les sorts de l'école de l'Enchantement de la cible ».
DEFINE_PATCH_MACRO ad_op_346_line BEGIN
	LPF ad_tra INT_VAR tra_id = 23460010 + $fx_special(~%line_fx%~) tra_block_start = 23460011 tra_block_size = 9 RET versus = text END // ~contre les sorts de l'école de l'Enchantement~ (@23460014)
	PATCH_IF line_form == 0 BEGIN
		LPF ad_stat_modifier_value INT_VAR value = stat_value mode = stat_mode RET value = text END
		SPRINT saves_name @23460000 // ~Jets de sauvegarde~
		PATCH_IF stat_mode == MOD_TYPE_flat BEGIN
			SPRINT name ~%saves_name% %versus%~
		END
		ELSE BEGIN
			SPRINT name ~%saves_name%~
			SPRINT value ~%value% %versus%~
		END
		SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
		LPM ad_effect_line
		SET stat_line_done = 1
	END
END
