// Opcode 78 (State: Disease) : maladie de type parameter2 (ancien opcode_78_common) : 0-3 dégâts au
// fil du temps, comptés comme ceux du poison (ad_hp_over_time_value, new-lib/opcodes/hp_over_time.tpp),
// « de poison » sur EE ; 4-9 force, dextérité, constitution, intelligence, sagesse ou charisme réduits
// de parameter1 (augmentés pour une valeur négative) ; 10 lenteur ; 13 contagion, lenteur et force,
// dextérité et charisme réduits (augmentés pour une valeur positive, comme dans l'ancien moteur).
// Phrase : 2078 0100 + 10 × décalage de la chaîne de l'ancien moteur (+ forme).

// Refus : type hors de 0-13, ou au-delà de 10 sur un jeu classique ; dégâts sans durée sous un timing
// permanent ou sans effet (opcode_78_is_valid, comme le poison) ; contact de la moisissure (11, 12),
// que l'ancien moteur n'écrit pas ; caractéristique inchangée ; avec AD_ENABLE_SHRINKAGE, deux
// caractéristiques réduites aux mêmes champs (ancien opcode_78_group, qui les réunit).
DEFINE_PATCH_MACRO ad_op_78_support BEGIN
	FOR (disease_id = 0; disease_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++disease_id) BEGIN
		PATCH_IF $fx_opcode(~%disease_id%~) == 78 AND NOT $fx_consumed(~%disease_id%~) BEGIN
			SET disease_type = $fx_parameter2(~%disease_id%~)
			SET disease_amount = $fx_parameter1(~%disease_id%~)
			SET disease_timing = $fx_timing(~%disease_id%~)
			SET hp_id = disease_id
			LPM ad_hp_over_time_value
			PATCH_IF disease_type < 0 OR disease_type > 13 OR (disease_type > 10 AND NOT IS_EE) BEGIN
				SPRINT render_missing ~not_implemented:opcode78:invalid~
			END
			ELSE PATCH_IF disease_type <= 3 AND (disease_timing == TIMING_permanent OR disease_timing == TIMING_delayed OR disease_timing == 7
					OR disease_timing == TIMING_permanent_after_death) AND $fx_duration(~%disease_id%~) == 0 BEGIN
				SPRINT render_missing ~not_implemented:opcode78:timing~
			END
			ELSE PATCH_IF disease_type <= 3 AND hp_amount <= 0 BEGIN
				SPRINT render_missing ~not_implemented:opcode78:no_effect~
			END
			ELSE PATCH_IF disease_type == 11 OR disease_type == 12 BEGIN
				SPRINT render_missing ~not_implemented:opcode78:mold_touch~
			END
			ELSE PATCH_IF ((disease_type >= 4 AND disease_type <= 9) OR disease_type == 13) AND disease_amount == 0 BEGIN
				SPRINT render_missing ~not_implemented:opcode78:no_effect~
			END
			ELSE PATCH_IF disease_type >= 4 AND disease_type <= 9 AND AD_ENABLE_SHRINKAGE BEGIN
				LPF ad_fx_signature INT_VAR fx_id = disease_id with_parameter2 = 0 RET disease_signature = signature END
				FOR (disease_other = 0; disease_other < fx_count; ++disease_other) BEGIN
					SET disease_other_type = $fx_parameter2(~%disease_other%~)
					PATCH_IF disease_other != disease_id AND $fx_opcode(~%disease_other%~) == 78 AND disease_other_type >= 4 AND disease_other_type <= 9 BEGIN
						LPF ad_fx_signature INT_VAR fx_id = disease_other with_parameter2 = 0 RET disease_other_signature = signature END
						PATCH_IF ~%disease_other_signature%~ STRING_EQUAL ~%disease_signature%~ BEGIN
							SPRINT render_missing ~not_implemented:opcode78:group~
						END
					END
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_78_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~78~)
	FOR (disease_id = 0; disease_id < fx_count; ++disease_id) BEGIN
		PATCH_IF $fx_opcode(~%disease_id%~) == 78 AND NOT $fx_consumed(~%disease_id%~) BEGIN
			SET disease_type = $fx_parameter2(~%disease_id%~)
			SET amount = $fx_parameter1(~%disease_id%~)
			PATCH_IF disease_type <= 3 BEGIN
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
