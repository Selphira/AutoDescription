// Appelée sur le fichier .spl en cours de traitement ; même contrat que ad_describe_item.
DEFINE_PATCH_FUNCTION ad_describe_spell
	STR_VAR
		original_description = ~~
	RET
		description
		covered
		uncovered_reason
BEGIN
	SPRINT description ~~
	SET covered = 0
	SPRINT uncovered_reason ~not_implemented~
END
