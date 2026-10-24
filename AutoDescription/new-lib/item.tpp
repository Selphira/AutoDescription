// Appelée sur le fichier .itm en cours de traitement. Une ressource « non couverte » contient un
// élément que le moteur ne sait pas encore décrire : elle est exclue de la comparaison avec
// l'ancien moteur et n'est pas modifiée.
DEFINE_PATCH_FUNCTION ad_describe_item
	STR_VAR
		original_description = ~~
		log_name = ~~
	RET
		description
		covered
		uncovered_reason
BEGIN
	SPRINT description ~~
	SET covered = 0
	SET support_header_only = 0
	SET support_spell = 0
	SET source_is_spell = 0
	SET log_muted = 0
	SET group_spell_as_equipped = 0
	LPM ad_recursion_reset
	LPM ad_fx_load_item
	PATCH_IF AD_EFFECTS_DUMP BEGIN
		LPM ad_fx_dump
	END
	LPM ad_set_coverage
	PATCH_IF ~%uncovered_reason%~ STRING_EQUAL ~not_implemented~ BEGIN
		LPM ad_item_render_support
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SPRINT render_late_missing ~~
			LPM ad_item_render
			// Une forme de phrase absente n'apparaît qu'au rendu des lignes (new-lib/application.tpp).
			SET covered = ~%render_late_missing%~ STRING_EQUAL ~~
			SPRINT uncovered_reason ~%render_late_missing%~
		END
		ELSE BEGIN
			SPRINT uncovered_reason ~%render_missing%~
		END
	END
	PATCH_IF NOT covered BEGIN
		LPF ad_log_event STR_VAR event = ~%uncovered_reason%~ RET uncovered_reason = reason END
	END
END
