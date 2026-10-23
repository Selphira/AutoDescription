// Opcode 60 (Stat: Miscast Magic) : parameter1, octet de poids faible = pourcentage d'échec ;
// parameter2 0 sorts profanes, 1 divins, 2 innés (3 à 5 : les mêmes, sans retour visuel) ; « Provoque
// l'échec de 50 % des sorts profanes ». Avec AD_ENABLE_SHRINKAGE, les effets qui ne diffèrent que par
// le type de sort sont réunis (ad_group_spell_types, new-lib/groups.tpp, fx_spell_types). L'ancien
// moteur n'a pas de phrase à la forme « soi » probable : l'effet est alors refusé.

DEFINE_PATCH_MACRO ad_op_60_support BEGIN
	PHP_EACH fx_ids_60 AS _ => failure_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET $fx_spell_types(~%failure_id%~) = 0
			PATCH_IF ($fx_parameter1(~%failure_id%~) BAND 255) == 0 OR $fx_parameter2(~%failure_id%~) < 0 OR $fx_parameter2(~%failure_id%~) > 5 BEGIN
				LPF ad_refusal INT_VAR fx_id = failure_id STR_VAR reason = ~file_error:opcode60:invalid~ message = ~failure chance of 0 or spell type (parameter2) outside 0-5~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_60_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~60~)
	FOR (failure_late = 0; failure_late <= 1; ++failure_late) BEGIN
		PHP_EACH fx_ids_60 AS _ => failure_id BEGIN
			PATCH_IF NOT $fx_consumed(~%failure_id%~) AND $fx_late(~%failure_id%~) == failure_late BEGIN
				SET failure_types = $fx_spell_types(~%failure_id%~)
				PATCH_IF failure_types == 0 BEGIN
					SET failure_type = $fx_parameter2(~%failure_id%~)
					SET failure_types = 1 << (failure_type > 2 ? failure_type - 3 : failure_type)
				END
				SET value = $fx_parameter1(~%failure_id%~) BAND 255
				SPRINT percent @1200003 // ~%value%%PERCENT%~
				SET line_phrase = 20600100 // ~Provoque l'échec de %percent% des sorts~
				PATCH_IF failure_types != 7 BEGIN
					CLEAR_ARRAY failure_names
					SET failure_count = 0
					FOR (failure_bit = 0; failure_bit < 3; ++failure_bit) BEGIN
						PATCH_IF (failure_types BAND (1 << failure_bit)) != 0 BEGIN
							LPF ad_tra INT_VAR tra_id = 8020000 + failure_bit tra_block_start = 8020000 tra_block_size = 10 RET failure_name = text END // ~profanes~
							SPRINT $failure_names(~%failure_count%~) ~%failure_name%~
							SET failure_count += 1
							// Les sorts divins sont ceux des clercs et des druides (ancien get_spell_type_str).
							PATCH_IF failure_bit == 1 BEGIN
								SPRINT $failure_names(~%failure_count%~) @8020004 // ~druidiques~
								SET failure_count += 1
							END
						END
					END
					LPF ad_join STR_VAR array_name = ~failure_names~ RET spellType = text END
					SET line_phrase = 20600110 // ~Provoque l'échec de %percent% des sorts %spellType%~
				END
				SET line_fx = failure_id
				LPM ad_effect_line
			END
		END
	END
END
