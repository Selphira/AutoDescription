// Opcode 55 (Death: Kill Creature Type) : tue les créatures de la valeur parameter1 du fichier IDS
// parameter2 (ad_ids_name, new-lib/resources.tpp) : « Tue instantanément les rakshasas ». Valeur 0 :
// la cible de l'effet, sans précision. Le nom remplace la cible, même celle d'une zone, comme dans
// l'ancien moteur. Avec AD_ENABLE_SHRINKAGE, les effets d'un même bloc qui ne diffèrent que par
// parameter1 et parameter2 n'en font qu'un (ancien opcode_group_by_target) : noms réunis sans doublon
// dans l'ordre des effets, ligne écrite après les autres effets 55, comme celle que l'ancien moteur
// ajoute en fin de liste.

// Refus : fichier hors de 2-8 (l'ancien moteur écarte les autres, sauf kit.ids sur EE, et la valeur
// 100 de ea.ids, opcode_modstat_is_valid) ; valeur sans nom ; effet d'un 177 qui vise un type de
// créature (l'ancien moteur remplace alors le nom de l'opcode par celui du 177).
DEFINE_PATCH_MACRO ad_op_55_support BEGIN
	FOR (kill_id = 0; kill_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++kill_id) BEGIN
		PATCH_IF $fx_opcode(~%kill_id%~) == 55 BEGIN
			SET kill_file = $fx_parameter2(~%kill_id%~)
			SET kill_value = $fx_parameter1(~%kill_id%~)
			LPF ad_ids_name INT_VAR ids_file = kill_file entry = kill_value RET kill_name = name END
			SPRINT $fx_kill_name(~%kill_id%~) ~%kill_name%~
			PATCH_IF kill_file < 2 OR kill_file > 8 OR (kill_file == 2 AND kill_value == 100) BEGIN
				SPRINT render_missing ~not_implemented:opcode55:ids_file~
			END
			ELSE PATCH_IF kill_value != 0 AND ~%kill_name%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode55:ids_name~
			END
			ELSE PATCH_IF $fx_versus_file(~%kill_id%~) > 0 BEGIN
				SPRINT render_missing ~not_implemented:opcode55:versus~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_55_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~55~)
	SPRINT the @1000008 // ~les~
	FOR (kill_id = 0; kill_id < fx_count; ++kill_id) BEGIN
		SET $kill_anchor(~%kill_id%~) = kill_id
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		FOR (kill_id = 0; kill_id < fx_count; ++kill_id) BEGIN
			PATCH_IF $fx_opcode(~%kill_id%~) == 55 AND NOT $fx_consumed(~%kill_id%~) AND $kill_anchor(~%kill_id%~) == kill_id BEGIN
				LPF ad_fx_signature INT_VAR fx_id = kill_id with_parameter1 = 0 with_parameter2 = 0 RET kill_signature = signature END
				FOR (kill_other = kill_id + 1; kill_other < fx_count; ++kill_other) BEGIN
					PATCH_IF $fx_opcode(~%kill_other%~) == 55 AND NOT $fx_consumed(~%kill_other%~) BEGIN
						LPF ad_fx_signature INT_VAR fx_id = kill_other with_parameter1 = 0 with_parameter2 = 0 RET kill_other_signature = signature END
						PATCH_IF ~%kill_other_signature%~ STRING_EQUAL ~%kill_signature%~ BEGIN
							SET $kill_anchor(~%kill_other%~) = kill_id
							SET $fx_late(~%kill_id%~) = 1
						END
					END
				END
			END
		END
	END
	FOR (kill_late = 0; kill_late <= 1; ++kill_late) BEGIN
		FOR (kill_id = 0; kill_id < fx_count; ++kill_id) BEGIN
			PATCH_IF $fx_opcode(~%kill_id%~) == 55 AND NOT $fx_consumed(~%kill_id%~) AND $kill_anchor(~%kill_id%~) == kill_id
					AND $fx_late(~%kill_id%~) == kill_late BEGIN
				LPM ad_op_55_target
				SET line_phrase = 20550100 // ~Tue instantanément %theTarget%~
				SET line_fx = kill_id
				LPM ad_effect_line
			END
		END
	END
END

// Cible de la ligne de l'effet kill_id et de ceux qu'il réunit (line_the_target). Refus d'un
// regroupement : valeur 0 ; cible d'une zone (l'ancien moteur y écrit la zone, sans les
// types de créatures, BUG-032) ; classes que l'ancien moteur réunit sous un seul nom (ancien
// opcode_set_target_strings : mages, puis voleurs, monoclassés et multiclassés).
DEFINE_PATCH_MACRO ad_op_55_target BEGIN
	CLEAR_ARRAY kill_names
	SET kill_members = 0
	SET kill_zero = 0
	SET kill_mages = 0
	SET kill_thieves = 0
	FOR (kill_member = kill_id; kill_member < fx_count; ++kill_member) BEGIN
		PATCH_IF $fx_opcode(~%kill_member%~) == 55 AND NOT $fx_consumed(~%kill_member%~) AND $kill_anchor(~%kill_member%~) == kill_id BEGIN
			SET kill_members += 1
			SPRINT kill_name $fx_kill_name(~%kill_member%~)
			PATCH_IF NOT (~%kill_name%~ STRING_EQUAL ~~) BEGIN
				SPRINT $kill_names(~%kill_name%~) ~%kill_name%~
			END
			SET kill_value = $fx_parameter1(~%kill_member%~)
			SET kill_zero = kill_zero OR kill_value == 0
			PATCH_IF $fx_parameter2(~%kill_member%~) == 5 BEGIN
				SET kill_mages = kill_mages BOR ((kill_value == 1) + 2 * (kill_value == 7) + 4 * (kill_value == 10) + 8 * (kill_value == 13)
					+ 16 * (kill_value == 14) + 32 * (kill_value == 17))
				SET kill_thieves = kill_thieves BOR ((kill_value == 4) + 2 * (kill_value == 9) + 4 * (kill_value == 10) + 8 * (kill_value == 13)
					+ 16 * (kill_value == 15))
			END
		END
	END
	PATCH_IF kill_members > 1 AND kill_zero BEGIN
		SPRINT render_late_missing ~not_implemented:opcode55:group_value~
	END
	ELSE PATCH_IF kill_members > 1 AND $fx_area_target(~%kill_id%~) BEGIN
		SPRINT render_late_missing ~not_implemented:opcode55:area_group~
	END
	ELSE PATCH_IF kill_members > 1 AND (kill_mages == 63 OR kill_thieves == 31) BEGIN
		SPRINT render_late_missing ~not_implemented:opcode55:class_group~
	END
	SPRINT line_the_target ~~
	PATCH_IF $fx_parameter1(~%kill_id%~) != 0 BEGIN
		LPF ad_join STR_VAR array_name = ~kill_names~ glue = EVAL ~, %the% ~ final_glue = EVAL ~ %AD_AND% %the% ~ RET kill_target = text END
		SPRINT line_the_target ~%the% %kill_target%~
	END
END
