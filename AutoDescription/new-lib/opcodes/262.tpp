// Opcode 262 (Stat: Visual Range) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp, dont la valeur est une distance : une unité vaut 2 pieds (IESDP),
// écrite en mètres (« Porte à 3,5 mètres le champ de vision de la cible »). Seuls les modes 0 et 1
// existent (IESDP). Comme l'ancien opcode_262_common : une valeur fixée négative vaut 0, et la valeur
// est bornée à 15, l'IESDP la situant entre 0 et 15.

DEFINE_PATCH_MACRO ad_op_262_support BEGIN
	PHP_EACH fx_ids_262 AS _ => stat_id BEGIN
		PATCH_IF $fx_parameter2(~%stat_id%~) == MOD_TYPE_flat AND $fx_parameter1(~%stat_id%~) < 0 BEGIN
			SET $fx_parameter1(~%stat_id%~) = 0
		END
	END
	SET stat_opcode = 262
	SPRINT stat_mode_3 ~invalid~
	SPRINT stat_percentage ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_262_lines BEGIN
	SET stat_opcode = 262
	SPRINT stat_line_macro ~ad_op_262_line~
	LPM ad_stat_modifier_lines
END

DEFINE_PATCH_MACRO ad_op_262_line BEGIN
	SET vision_units = ABS stat_value
	SET vision_units = vision_units > 15 ? 15 : vision_units
	LPF ad_distance_text INT_VAR feet = vision_units * 2 RET vision_text = text END
	// Sans distance (champ de vision fixé à 0) : « 0 mètre », comme l'ancien feets_to_meters.
	PATCH_IF ~%vision_text%~ STRING_EQUAL ~~ BEGIN
		SET distance_units = 0
		LPF ad_tra INT_VAR tra_id = 1100000 RET vision_text = text END // ~%distance_units% mètre~
	END
	PATCH_IF line_form == 0 BEGIN
		SPRINT value ~%vision_text%~
		PATCH_IF stat_mode == MOD_TYPE_flat BEGIN
			SPRINT value @1200002 // ~Passe à %value%~
		END
		ELSE PATCH_IF stat_value >= 0 BEGIN
			SPRINT value @1200001 // ~+%value%~
		END
		ELSE BEGIN
			SPRINT value ~-%value%~
		END
		LPF ad_tra INT_VAR tra_id = stat_name_tra RET name = text END
		SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
		LPM ad_effect_line
	END
	ELSE BEGIN
		LPF ad_tra INT_VAR tra_id = stat_name_tra + 60000 RET theStatistic = text END
		LPM ad_stat_modifier_phrase
		SPRINT value ~%vision_text%~
		LPM ad_effect_line
	END
	SET stat_line_done = 1
END
