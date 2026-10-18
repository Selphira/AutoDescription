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
	LPM ad_fx_load_item
	PATCH_IF AD_EFFECTS_DUMP BEGIN
		LPM ad_fx_dump
	END
	LPM ad_set_coverage
	PATCH_IF ~%uncovered_reason%~ STRING_EQUAL ~not_implemented~ BEGIN
		LPM ad_item_render_support
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			LPM ad_item_render
			SET covered = 1
			SPRINT uncovered_reason ~~
		END
		ELSE BEGIN
			SPRINT uncovered_reason ~%render_missing%~
		END
	END
END
