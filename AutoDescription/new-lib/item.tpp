// Appelée sur le fichier .itm en cours de traitement. Une ressource « non couverte » contient un
// élément que le moteur ne sait pas encore décrire : elle est exclue de la comparaison avec
// l'ancien moteur et n'est pas modifiée.
// Squelette : aucun opcode n'est encore pris en charge.
DEFINE_PATCH_FUNCTION ad_describe_item
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
