// Code commun des modificateurs contre un type de créature (opcodes 178, 179, 344) : valeur
// contre les créatures de la valeur parameter1 du fichier IDS parameter2 (ad_ids_name,
// new-lib/resources.tpp) : « TAC0 : +2 contre les lycanthropes », à la forme « cible » « Augmente de 5
// le TAC0 de la cible contre les planétaires déchus ». Valeur : parameter3 d'un effet
// d'un EFF (178, 179), sinon special sur EE (ancien opcode_178_common) ; special pour le 344. Avec
// AD_ENABLE_SHRINKAGE, les effets d'un même bloc qui ne diffèrent que par parameter1 et parameter2
// n'en font qu'un (ancien opcode_group_by_target) : noms réunis sans doublon dans l'ordre des effets,
// ligne écrite après les autres effets de l'opcode, comme celle que l'ancien moteur ajoute. Les
// macros ad_op_<N>_* fixent versus_opcode et versus_name_tra puis appellent les macros ci-dessous.

// Un 178 ou un 179 sans valeur : l'ancien moteur l'écarte (opcode_178_is_valid). Refus : fichier
// hors de 2-8 et valeur 100 de ea.ids (opcode_idscheck8_is_valid du 344 ; kit.ids non repris) ;
// valeur sans nom ; effet probable ; forme « cible » du 344 (l'ancien moteur n'en a pas) ;
// effet d'un 177 qui vise lui-même un type de créature (l'ancien moteur remplace alors celui de
// l'opcode).
DEFINE_PATCH_MACRO ad_versus_modifier_support BEGIN
	FOR (versus_id = 0; versus_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++versus_id) BEGIN
		PATCH_IF $fx_opcode(~%versus_id%~) == versus_opcode BEGIN
			SET versus_file = $fx_parameter2(~%versus_id%~)
			SET versus_value = $fx_parameter1(~%versus_id%~)
			SET versus_amount = versus_opcode == 344 ? $fx_special(~%versus_id%~) : $fx_parameter3(~%versus_id%~)
			PATCH_IF versus_opcode != 344 AND versus_amount == 0 AND IS_EE BEGIN
				SET versus_amount = $fx_special(~%versus_id%~)
			END
			SET $fx_versus_amount(~%versus_id%~) = versus_amount
			LPF ad_ids_name INT_VAR ids_file = versus_file entry = versus_value RET versus_name = name END
			SPRINT $fx_versus_name(~%versus_id%~) ~%versus_name%~
			SET versus_target = $fx_effective_target(~%versus_id%~)
			PATCH_IF versus_opcode != 344 AND versus_amount == 0 BEGIN
				SET drop_id = versus_id
				SPRINT ignored_reason ~file_error:opcode%versus_opcode%:no_change~
				SPRINT ignored_message ~modifier of 0~
				LPM ad_application_drop
			END
			ELSE PATCH_IF versus_file < 2 OR versus_file > 8 OR (versus_file == 2 AND versus_value == 100) BEGIN
				PATCH_IF versus_file < 2 OR versus_file > (IS_EE ? 9 : 8) BEGIN
					LPF ad_refusal INT_VAR fx_id = versus_id STR_VAR reason = ~file_error:opcode%versus_opcode%:ids_file~ message = ~IDS file %versus_file% is not a creature type (expected 2-8: EA, GENERAL, RACE, CLASS, SPECIFIC, GENDER, ALIGN; 9: KIT on enhanced editions)~ RET render_missing = refusal END
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = versus_id STR_VAR reason = ~not_implemented:opcode%versus_opcode%:ids_file~ message = ~kit restriction or value 100 of EA.IDS not supported (IDS file %versus_file%, value %versus_value%)~ RET render_missing = refusal END
				END
			END
			ELSE PATCH_IF ~%versus_name%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = versus_id STR_VAR reason = ~not_implemented:opcode%versus_opcode%:ids_name~ message = ~value %versus_value% of IDS file %versus_file% has no name~ RET render_missing = refusal END
			END
			ELSE PATCH_IF (versus_opcode == 344 AND versus_target != TARGET_FX_self AND versus_target != TARGET_FX_original_caster)
					OR $fx_probability(~%versus_id%~) < 100 BEGIN
				LPF ad_refusal INT_VAR fx_id = versus_id STR_VAR reason = ~not_implemented:opcode%versus_opcode%:form~ message = ~effect on another target, or probable~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_versus_file(~%versus_id%~) > 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = versus_id STR_VAR reason = ~not_implemented:opcode%versus_opcode%:double_versus~ message = ~creature type also set by opcode 177~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_versus_modifier_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%versus_opcode%~)
	SPRINT the @2002000 // ~les~
	SPRINT and_the @2002001 // ~et les~
	FOR (versus_id = 0; versus_id < fx_count; ++versus_id) BEGIN
		SET $versus_anchor(~%versus_id%~) = versus_id
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		FOR (versus_id = 0; versus_id < fx_count; ++versus_id) BEGIN
			PATCH_IF $fx_opcode(~%versus_id%~) == versus_opcode AND NOT $fx_consumed(~%versus_id%~) AND $versus_anchor(~%versus_id%~) == versus_id BEGIN
				LPF ad_fx_signature INT_VAR fx_id = versus_id with_parameter1 = 0 with_parameter2 = 0 RET versus_signature = signature END
				FOR (versus_other = versus_id + 1; versus_other < fx_count; ++versus_other) BEGIN
					PATCH_IF $fx_opcode(~%versus_other%~) == versus_opcode AND NOT $fx_consumed(~%versus_other%~)
							AND $fx_parameter3(~%versus_other%~) == $fx_parameter3(~%versus_id%~) BEGIN
						LPF ad_fx_signature INT_VAR fx_id = versus_other with_parameter1 = 0 with_parameter2 = 0 RET versus_other_signature = signature END
						PATCH_IF ~%versus_other_signature%~ STRING_EQUAL ~%versus_signature%~ BEGIN
							SET $versus_anchor(~%versus_other%~) = versus_id
							SET $fx_late(~%versus_id%~) = 1
						END
					END
				END
			END
		END
	END
	FOR (versus_late = 0; versus_late <= 1; ++versus_late) BEGIN
		FOR (versus_id = 0; versus_id < fx_count; ++versus_id) BEGIN
			PATCH_IF $fx_opcode(~%versus_id%~) == versus_opcode AND NOT $fx_consumed(~%versus_id%~) AND $versus_anchor(~%versus_id%~) == versus_id
					AND $fx_late(~%versus_id%~) == versus_late BEGIN
				LPM ad_versus_modifier_line
			END
		END
	END
END

// Ligne de l'effet versus_id et de ceux qu'il réunit. Refus : classes que l'ancien moteur réunit
// sous un seul nom (mages, puis voleurs, monoclassés et multiclassés).
DEFINE_PATCH_MACRO ad_versus_modifier_line BEGIN
	CLEAR_ARRAY versus_names
	SET versus_mages = 0
	SET versus_thieves = 0
	FOR (versus_member = versus_id; versus_member < fx_count; ++versus_member) BEGIN
		PATCH_IF $fx_opcode(~%versus_member%~) == versus_opcode AND NOT $fx_consumed(~%versus_member%~) AND $versus_anchor(~%versus_member%~) == versus_id BEGIN
			SPRINT versus_name $fx_versus_name(~%versus_member%~)
			SPRINT $versus_names(~%versus_name%~) ~%versus_name%~
			SET versus_value = $fx_parameter1(~%versus_member%~)
			PATCH_IF $fx_parameter2(~%versus_member%~) == 5 BEGIN
				SET versus_mages = versus_mages BOR ((versus_value == 1) + 2 * (versus_value == 7) + 4 * (versus_value == 10) + 8 * (versus_value == 13)
					+ 16 * (versus_value == 14) + 32 * (versus_value == 17))
				SET versus_thieves = versus_thieves BOR ((versus_value == 4) + 2 * (versus_value == 9) + 4 * (versus_value == 10) + 8 * (versus_value == 13)
					+ 16 * (versus_value == 15))
			END
		END
	END
	PATCH_IF versus_mages == 63 OR versus_thieves == 31 BEGIN
		LPF ad_refusal INT_VAR fx_id = versus_member STR_VAR reason = ~not_implemented:opcode%versus_opcode%:class_group~ message = ~creature types covering all mage or thief classes~ RET render_late_missing = refusal END
	END
	LPF ad_join STR_VAR array_name = ~versus_names~ glue = EVAL ~, %the% ~ final_glue = EVAL ~ %and_the% ~ RET targetType = text END
	SPRINT line_suffix @2002020 // ~contre les %targetType%~
	SET line_fx = versus_id
	LPM ad_application_form
	SET versus_amount = $fx_versus_amount(~%versus_id%~)
	// Forme « cible » (ancien opcode_target) : « Augmente de 5 le TAC0 de la cible contre les X ».
	PATCH_IF line_form == 1 BEGIN
		LPF ad_tra INT_VAR tra_id = versus_name_tra + 2 RET theStatistic = text END // ~le TAC0~
		SET value = ABS versus_amount
		SET line_phrase = versus_amount >= 0 ? 1210110 : 1210120 // ~Augmente de %value% %theStatistic% %ofTheTarget%~ (+1)
	END
	ELSE BEGIN
		LPF ad_tra INT_VAR tra_id = versus_name_tra RET name = text END // ~TAC0~
		LPF ad_signed_value INT_VAR value = versus_amount RET value = text END
		SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
	END
	LPM ad_effect_line
END
