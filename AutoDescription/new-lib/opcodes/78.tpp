// Opcode 78 (State: Disease) : maladie de type parameter2 (ancien opcode_78_common) : 0-3 dégâts au
// fil du temps, comptés comme ceux du poison (ad_hp_over_time_value, new-lib/opcodes/hp_over_time.tpp),
// « de poison » sur EE ; 4-9 force, dextérité, constitution, intelligence, sagesse ou charisme réduits
// de parameter1 (augmentés pour une valeur négative) ; 10 lenteur ; 13 contagion, lenteur et force,
// dextérité et charisme réduits (augmentés pour une valeur positive, comme dans l'ancien moteur).
// Phrase : 2078 0100 + 10 × décalage de la chaîne de l'ancien moteur (+ forme) ; 40 (réduites) et 50
// (augmentées) pour des caractéristiques réunies (ad_op_78_group).

// Refus : type hors de 0-13, ou au-delà de 10 sur un jeu classique ; dégâts sans durée sous un timing
// permanent ou sans effet (opcode_78_is_valid, comme le poison) ; contact de la moisissure (11, 12),
// que l'ancien moteur n'écrit pas ; caractéristique inchangée ; refus de ad_op_78_group.
DEFINE_PATCH_MACRO ad_op_78_support BEGIN
	PHP_EACH fx_ids_78 AS _ => disease_id BEGIN
		SET $fx_disease_group(~%disease_id%~) = 0
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%disease_id%~) BEGIN
			SET disease_type = $fx_parameter2(~%disease_id%~)
			SET disease_amount = $fx_parameter1(~%disease_id%~)
			SET disease_timing = $fx_timing(~%disease_id%~)
			SET hp_id = disease_id
			LPM ad_hp_over_time_value
			PATCH_IF disease_type < 0 OR disease_type > 13 OR (disease_type > 10 AND NOT IS_EE) BEGIN
				LPF ad_refusal INT_VAR fx_id = disease_id STR_VAR reason = ~file_error:opcode78:invalid~ message = ~disease type %disease_type% (expected 0-13, 0-10 on classic games)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF disease_type <= 3 AND (disease_timing == TIMING_permanent OR disease_timing == TIMING_delayed OR disease_timing == 7
					OR disease_timing == TIMING_permanent_after_death) AND $fx_duration(~%disease_id%~) == 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = disease_id STR_VAR reason = ~file_error:opcode78:timing~ message = ~damage over time with a permanent or delayed timing and no duration~ RET render_missing = refusal END
			END
			ELSE PATCH_IF disease_type <= 3 AND hp_amount <= 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = disease_id STR_VAR reason = ~file_error:opcode78:no_effect~ message = ~damage amount of 0 or less~ RET render_missing = refusal END
			END
			ELSE PATCH_IF disease_type == 11 OR disease_type == 12 BEGIN
				LPF ad_refusal INT_VAR fx_id = disease_id STR_VAR reason = ~not_implemented:opcode78:mold_touch~ message = ~mold touch~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ((disease_type >= 4 AND disease_type <= 9) OR disease_type == 13) AND disease_amount == 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = disease_id STR_VAR reason = ~file_error:opcode78:no_effect~ message = ~amount of 0~ RET render_missing = refusal END
			END
		END
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_op_78_group
	END
END

// Avec AD_ENABLE_SHRINKAGE, les maladies d'une caractéristique (types 4 à 9) d'un même bloc aux mêmes
// champs, type mis à part (ancien opcode_78_group), n'en font qu'une, écrite après les autres
// (fx_late) : « Inocule une maladie qui diminue de 2 la force, la dextérité et le charisme de la
// cible ». Caractéristiques (fx_disease_attributes) : celle de l'effet, puis, pour chacune des
// autres dans l'ordre des types, le premier effet qui lui correspond. Refus : deux effets de la
// caractéristique de l'effet (l'ancien moteur n'en écarte qu'un).
DEFINE_PATCH_MACRO ad_op_78_group BEGIN
	PHP_EACH fx_ids_78 AS _ => disease_id BEGIN
		SET disease_type = $fx_parameter2(~%disease_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%disease_id%~) AND disease_type >= 4 AND disease_type <= 9 BEGIN
			CLEAR_ARRAY disease_names
			LPF ad_tra INT_VAR tra_id = 20780060 + disease_type RET disease_name = text END // ~la force~ (@20780064)
			SPRINT $disease_names(~0~) ~%disease_name%~
			SET disease_count = 1
			SET same_id = disease_id
			SET same_ignored = AD_SAME_PARAMETER2
			FOR (disease_attribute = 4; disease_attribute <= 9; ++disease_attribute) BEGIN
				SET disease_found = 0 - 1
				PHP_EACH fx_ids_78 AS _ => disease_other BEGIN
					PATCH_IF disease_found < 0 AND disease_other != disease_id AND NOT $fx_consumed(~%disease_other%~)
							AND $fx_parameter2(~%disease_other%~) == disease_attribute BEGIN
						SET same_other = disease_other
						LPM ad_fx_same_fields
						PATCH_IF fx_same BEGIN
							SET disease_found = disease_other
						END
					END
				END
				PATCH_IF disease_found >= 0 BEGIN
					PATCH_IF disease_attribute == disease_type BEGIN
						LPF ad_refusal INT_VAR fx_id = disease_found STR_VAR reason = ~not_implemented:opcode78:group_same_attribute~ message = ~identical diseases of the same ability~ RET render_missing = refusal END
					END
					SET $fx_consumed(~%disease_found%~) = 1
					SET $fx_group_anchor(~%disease_found%~) = disease_id
					LPF ad_tra INT_VAR tra_id = 20780060 + disease_attribute RET disease_name = text END
					SPRINT $disease_names(~%disease_count%~) ~%disease_name%~
					SET disease_count += 1
				END
			END
			SET same_ignored = 0
			PATCH_IF disease_count > 1 BEGIN
				SPRINT disease_and @20780001 // ~et~
				LPF ad_join STR_VAR array_name = ~disease_names~ glue = ~, ~ final_glue = EVAL ~ %disease_and% ~ RET disease_attributes = text END
				SPRINT $fx_disease_attributes(~%disease_id%~) ~%disease_attributes%~
				SET $fx_disease_group(~%disease_id%~) = 1
				SET $fx_late(~%disease_id%~) = 1
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_78_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~78~)
	FOR (disease_late = 0; disease_late <= 1; ++disease_late) BEGIN
		PHP_EACH fx_ids_78 AS _ => disease_id BEGIN
			PATCH_IF NOT $fx_consumed(~%disease_id%~) AND $fx_late(~%disease_id%~) == disease_late BEGIN
				SET disease_type = $fx_parameter2(~%disease_id%~)
				SET amount = $fx_parameter1(~%disease_id%~)
				PATCH_IF $fx_disease_group(~%disease_id%~) BEGIN
					SPRINT theAttributes $fx_disease_attributes(~%disease_id%~)
					SET disease_offset = amount < 0 ? 50 : 40
					SET amount = ABS amount
				END
				ELSE PATCH_IF disease_type <= 3 BEGIN
					SET hp_id = disease_id
					LPM ad_hp_over_time_value
					SET amount = hp_amount
					LPF ad_duration_text INT_VAR seconds = hp_frequency tra_base = 3030000 RET strDuration = text END // ~par round~
					SET disease_offset = (IS_EE ? 30 : 0) + (hp_amount > 1 ? 1 : 0)
				END
				ELSE PATCH_IF disease_type <= 9 BEGIN
					SET disease_offset = disease_type + (amount < 0 ? 10 : 0)
					SET amount = ABS amount
				END
				ELSE PATCH_IF disease_type == 10 BEGIN
					SET disease_offset = 10
				END
				ELSE BEGIN
					SET disease_offset = amount < 0 ? 13 : 23
					SET amount = ABS amount
				END
				SET line_fx = disease_id
				SET line_phrase = 20780100 + 10 * disease_offset // ~Inocule une maladie qui inflige 1 point de dégâts %strDuration% %toTheTarget%~
				LPM ad_effect_line
			END
		END
	END
END
