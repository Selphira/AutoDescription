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
END
