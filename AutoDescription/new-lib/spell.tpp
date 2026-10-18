// Appelée sur le fichier .spl en cours de traitement ; même contrat que ad_describe_item.
DEFINE_PATCH_FUNCTION ad_describe_spell
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
	LPM ad_fx_load_spell
	PATCH_IF AD_EFFECTS_DUMP BEGIN
		LPM ad_fx_dump
	END
	LPM ad_set_uncovered_reason
END
