// Opcode 112 (Item: Remove Item) : retire l'objet resource de l'inventaire : « Retire « Ras +2 » de
// l'inventaire ». Avec AD_ENABLE_SHRINKAGE, il se combine aux créations d'objet (opcode 122) :
// ad_group_item_return et ad_group_replace_item (new-lib/groups.tpp).

// Comme l'ancien opcode_112_is_valid, le retrait d'une arme nommée « Attaquer » ou « Morgenstern »
// (armes des métamorphoses) est écarté sans rien écrire ; un objet sans nom aussi (ancien
// opcode_self_112, qui n'écrit rien sans nom), journalisé. Refus : ressource vide, objet absent.
DEFINE_PATCH_MACRO ad_op_112_support BEGIN
	PHP_EACH fx_ids_112 AS _ => remove_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SPRINT remove_resref $fx_resource(~%remove_id%~)
			LPF ad_item_info STR_VAR resref = ~%remove_resref%~ RET remove_name = name remove_name_ref = name_ref END
			SET $fx_item_return(~%remove_id%~) = 0
			PATCH_IF ~%remove_resref%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = remove_id STR_VAR reason = ~file_error:opcode112:invalid~ message = ~empty resource field~ RET render_missing = refusal END
			END
			ELSE PATCH_IF remove_name_ref == 25615 OR remove_name_ref == 10966 OR remove_name_ref == 6854 BEGIN
				SET drop_id = remove_id
				LPM ad_application_drop
			END
			// En-tête d'un sort seul : seul compte un objet absent, que l'ancien moteur écarte.
			ELSE PATCH_IF ~%remove_name%~ STRING_EQUAL ~~ AND (NOT support_header_only OR NOT FILE_EXISTS_IN_GAME ~%remove_resref%.itm~) BEGIN
				PATCH_IF FILE_EXISTS_IN_GAME ~%remove_resref%.itm~ BEGIN
					SET drop_id = remove_id
					SPRINT ignored_reason ~not_implemented:opcode112:no_name~
					SPRINT ignored_message ~item %remove_resref%.ITM has no name~
					LPM ad_application_drop
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = remove_id STR_VAR reason = ~file_error:opcode112:missing_item~ message = ~item %remove_resref%.ITM does not exist~ RET render_missing = refusal END
				END
			END
			ELSE BEGIN
				SPRINT $fx_item_name(~%remove_id%~) ~%remove_name%~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_112_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~112~)
	PHP_EACH fx_ids_112 AS _ => remove_id BEGIN
		PATCH_IF NOT $fx_consumed(~%remove_id%~) BEGIN
			SPRINT itemName $fx_item_name(~%remove_id%~)
			SET line_fx = remove_id
			LPM ad_application_form
			// Objet rendu après un délai (ad_group_item_return) : l'ancien opcode_self_112 écrit la durée
			// du retrait, à la forme « soi » seulement.
			PATCH_IF line_form == 0 AND $fx_item_return(~%remove_id%~) > 0 BEGIN
				LPF ad_duration_text INT_VAR seconds = $fx_item_return(~%remove_id%~) RET strDuration = text END
				SPRINT line_suffix @3000000 // ~pendant %strDuration%~
			END
			SET line_phrase = 21120100 // ~Retire « %itemName% » de l'inventaire~ (+1 : ~Retire « %itemName% » de l'inventaire %ofTheTarget%~)
			LPM ad_effect_line
		END
	END
END
