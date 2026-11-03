// Opcode 180 (Item: Can't Use Item) : empêche d'équiper l'objet resource. Sur l'objet lui-même :
// « Unique : Un seul exemplaire peut être équipé », en tête des capacités d'équipement (rang 0).
// Les autres objets d'une même portée sont réunis en une ligne (ancien opcode_180_group) :
// « Empêche d'utiliser « Anneau des arcanes » et « Anneau Ensorceleur » » ; un objet du même nom que
// l'objet décrit en est un autre exemplaire et n'est pas nommé.

// Ressource vide ou objet absent : effet écarté sans rien écrire, erreur journalisée ; objet sans
// nom : effet écarté et journalisé (l'ancien moteur n'écrit rien). Refus : parameter2 non nul.
DEFINE_PATCH_MACRO ad_op_180_support BEGIN
	LPF ad_item_info STR_VAR resref = ~%ctx_resource%~ RET forbid_own_name = name END
	PHP_EACH fx_ids_180 AS _ => forbid_id BEGIN
		SPRINT $fx_item_name(~%forbid_id%~) ~~
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%forbid_id%~) BEGIN
			SPRINT forbid_resref $fx_resource(~%forbid_id%~)
			SET $fx_forbid_unique(~%forbid_id%~) = ~%forbid_resref%~ STRING_EQUAL_CASE ~%ctx_resource%~
			LPF ad_item_info STR_VAR resref = ~%forbid_resref%~ RET forbid_name = name END
			PATCH_IF ~%forbid_resref%~ STRING_EQUAL ~~ OR NOT FILE_EXISTS_IN_GAME ~%forbid_resref%.itm~ BEGIN
				SET drop_id = forbid_id
				SPRINT ignored_reason ~file_error:opcode180:invalid~
				SPRINT ignored_message ~item %forbid_resref%.ITM does not exist~
				LPM ad_application_drop
			END
			ELSE PATCH_IF $fx_parameter2(~%forbid_id%~) != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = forbid_id STR_VAR reason = ~not_implemented:opcode180:invalid~ message = ~parameter2 other than 0 not supported~ RET render_missing = refusal END
			END
			ELSE PATCH_IF NOT $fx_forbid_unique(~%forbid_id%~) BEGIN
				PATCH_IF ~%forbid_name%~ STRING_EQUAL ~~ BEGIN
					SET drop_id = forbid_id
					SPRINT ignored_reason ~not_implemented:opcode180:no_name~
					SPRINT ignored_message ~item %forbid_resref%.ITM has no name~
					LPM ad_application_drop
				END
				ELSE PATCH_IF NOT (~%forbid_name%~ STRING_EQUAL ~%forbid_own_name%~) BEGIN
					SPRINT $fx_item_name(~%forbid_id%~) ~%forbid_name%~
				END
			END
		END
	END
END

// L'ancien moteur n'a de phrase qu'à la forme « soi ».
DEFINE_PATCH_MACRO ad_op_180_lines BEGIN
	SPRINT line_section ~equipped~
	PHP_EACH fx_ids_180 AS _ => forbid_id BEGIN
		PATCH_IF NOT $fx_consumed(~%forbid_id%~) AND NOT $fx_dropped(~%forbid_id%~) AND $fx_forbid_unique(~%forbid_id%~) BEGIN
			SET line_sort = 0
			SET line_phrase = 21800100 // ~Unique%AD_COLON%Un seul exemplaire peut être équipé~
			SET line_fx = forbid_id
			LPM ad_effect_line
		END
	END
	PHP_EACH fx_ids_180 AS _ => forbid_id BEGIN
		SPRINT forbid_name $fx_item_name(~%forbid_id%~)
		PATCH_IF NOT $fx_consumed(~%forbid_id%~) AND NOT $fx_dropped(~%forbid_id%~) AND NOT (~%forbid_name%~ STRING_EQUAL ~~) BEGIN
			SPRINT forbid_scope $fx_scope(~%forbid_id%~)
			CLEAR_ARRAY forbid_names
			PHP_EACH fx_ids_180 AS _ => forbid_other BEGIN
				SPRINT forbid_other_name $fx_item_name(~%forbid_other%~)
				SPRINT forbid_other_scope $fx_scope(~%forbid_other%~)
				PATCH_IF forbid_other >= forbid_id AND NOT $fx_consumed(~%forbid_other%~) AND NOT $fx_dropped(~%forbid_other%~)
						AND NOT (~%forbid_other_name%~ STRING_EQUAL ~~) AND (~%forbid_other_scope%~ STRING_EQUAL ~%forbid_scope%~) BEGIN
					SPRINT $forbid_names(~%forbid_other_name%~) ~%forbid_other_name%~
					SET $fx_consumed(~%forbid_other%~) = forbid_other != forbid_id
				END
			END
			SPRINT and ~%AD_AND%~
			SPRINT forbid_glue @1000005 // ~ », « ~
			SPRINT forbid_final_glue @1000006 // ~ » %and% « ~
			LPF ad_join STR_VAR array_name = ~forbid_names~ glue = ~%forbid_glue%~ final_glue = ~%forbid_final_glue%~ RET resItemName = text END
			SET line_sort = $AD_OPCODE_SORT(~180~)
			SET line_phrase = 21800110 // ~Empêche d'utiliser « %resItemName% »~
			SET line_fx = forbid_id
			LPM ad_effect_line
		END
	END
END
