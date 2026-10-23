// Opcode 143 (Item: Create Item in Slot) : crée l'objet resource à l'emplacement parameter1
// (slots.ids, liste @8080000) : « Crée 1 « Armure de plates » à l'emplacement de l'armure du
// porteur ». Le jeu rend permanent tout timing à durée limitée (l'effet 123 qu'il prévoit pour
// retirer l'objet n'a pas de ressource, IESDP) : le timing de l'effet devient permanent, comme dans
// l'ancien opcode_143_common.

// Refus : objet absent ou sans nom, emplacement inconnu (écartés par l'ancien opcode_143_is_valid) ;
// avec AD_ENABLE_SHRINKAGE, objet qui remplace une arme brisée (MISC57, MISC58, CDDELHLM : opcode
// virtuel 519 de l'ancien opcode_143_group_mod).
DEFINE_PATCH_MACRO ad_op_143_support BEGIN
	PHP_EACH fx_ids_143 AS _ => slot_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SPRINT slot_resref $fx_resource(~%slot_id%~)
			SET slot_index = $fx_parameter1(~%slot_id%~)
			LPF ad_item_info STR_VAR resref = ~%slot_resref%~ RET slot_item_name = name END
			PATCH_IF ~%slot_item_name%~ STRING_EQUAL ~~ OR slot_index < 0 OR slot_index > 38 BEGIN
				PATCH_IF slot_index < 0 OR slot_index > 38 BEGIN
					LPF ad_refusal INT_VAR fx_id = slot_id STR_VAR reason = ~file_error:opcode143:invalid~ message = ~slot %slot_index% (expected 0-38)~ RET render_missing = refusal END
				END
				ELSE PATCH_IF ~%slot_resref%~ STRING_EQUAL ~~ OR NOT FILE_EXISTS_IN_GAME ~%slot_resref%.itm~ BEGIN
					LPF ad_refusal INT_VAR fx_id = slot_id STR_VAR reason = ~file_error:opcode143:missing_item~ message = ~item %slot_resref%.ITM does not exist~ RET render_missing = refusal END
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = slot_id STR_VAR reason = ~not_implemented:opcode143:no_name~ message = ~item %slot_resref%.ITM has no name~ RET render_missing = refusal END
				END
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND (~%slot_resref%~ STRING_EQUAL_CASE ~MISC57~ OR ~%slot_resref%~ STRING_EQUAL_CASE ~MISC58~
					OR ~%slot_resref%~ STRING_EQUAL_CASE ~CDDELHLM~) BEGIN
				LPF ad_refusal INT_VAR fx_id = slot_id STR_VAR reason = ~not_implemented:opcode143:broken_weapon~ message = ~item replacing a broken weapon~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SPRINT $fx_item_name(~%slot_id%~) ~%slot_item_name%~
				SET slot_timing = $fx_timing(~%slot_id%~)
				PATCH_IF slot_timing == TIMING_duration OR slot_timing == TIMING_while_equipped OR slot_timing == TIMING_delayed_duration
						OR slot_timing == 5 OR slot_timing == 6 OR slot_timing == 8 OR slot_timing == TIMING_duration_ticks
						OR slot_timing == TIMING_absolute_duration BEGIN
					SET $fx_timing(~%slot_id%~) = TIMING_permanent
					SET ignored_fx = slot_id
					SPRINT ignored_reason ~file_error:opcode143:timing~
					SPRINT ignored_message ~timing %slot_timing% with a limited duration: the game never removes the item, described as permanent~
					SPRINT ignored_consequence ~kept~
					LPM ad_log_ignored
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_143_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~143~)
	PHP_EACH fx_ids_143 AS _ => slot_id BEGIN
		PATCH_IF NOT $fx_consumed(~%slot_id%~) BEGIN
			SPRINT itemName $fx_item_name(~%slot_id%~)
			LPF ad_tra INT_VAR tra_id = 8080000 + $fx_parameter1(~%slot_id%~) tra_block_start = 8080000 tra_block_size = 39 RET slotName = text END // ~de l'armure~
			SET line_phrase = 21430100 // ~Crée 1 « %itemName% » à l'emplacement %slotName% %ofTheTarget%~
			SET line_fx = slot_id
			LPM ad_effect_line
		END
	END
END
