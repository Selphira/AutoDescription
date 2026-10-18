// Lit la chaîne tra_id de description_new.tra. Un identifiant hors des plages du nouveau fichier
// (donc éventuellement défini par l'ancien), hors du sous-bloc déclaré pour un identifiant
// calculé (tra_block_start, tra_block_size), ou absent fait échouer la ressource : la boucle la
// classe alors « non couverte » et journalise l'erreur, plutôt que d'afficher un texte faux.
// Les %variables% du gabarit sont celles de l'appelant (V7) : les paramètres portent le
// préfixe tra_ pour ne pas en masquer une.
DEFINE_PATCH_FUNCTION ad_tra
	INT_VAR
		tra_id = 0
		tra_block_start = 0
		tra_block_size = 0
	RET
		text
BEGIN
	PATCH_IF NOT ((tra_id >= 1000000 AND tra_id <= 9999999) OR (tra_id >= 20000000 AND tra_id <= 39999999)) BEGIN
		PATCH_FAIL ~New engine: string @%tra_id% outside the ranges of description_new.tra~
	END
	PATCH_IF tra_block_size > 0 AND (tra_id < tra_block_start OR tra_id >= tra_block_start + tra_block_size) BEGIN
		PATCH_FAIL ~New engine: string @%tra_id% outside its block @%tra_block_start% (size %tra_block_size%)~
	END
	PATCH_IF NOT TRA_ENTRY_EXISTS (~%tra_id%~) BEGIN
		PATCH_FAIL ~New engine: missing string @%tra_id%~
	END
	SPRINT text (AT ~%tra_id%~)
END
