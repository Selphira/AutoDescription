// Range la chaîne tra_id de description.tra dans la variable nommée par tra_out. Un identifiant hors
// des plages du fichier (donc éventuellement défini par setup.tra), hors du sous-bloc déclaré pour un
// identifiant calculé (tra_block_start, tra_block_size), ou absent fait échouer la ressource : la
// boucle la classe alors « non couverte » et journalise l'erreur, plutôt que d'afficher un texte faux.
// Macro plutôt que fonction : appelée plusieurs fois par ligne, un LPF y copierait chaque fois toutes
// les variables. Les %variables% du gabarit sont celles de l'appelant ; ses entrées portent le
// préfixe tra_ pour ne pas en masquer une, et le sous-bloc est remis à zéro pour l'appel suivant.
// tra_out est un nom de variable simple, jamais un élément de tableau parcouru (écrit par nom).
DEFINE_PATCH_MACRO ad_tra_to BEGIN
	PATCH_IF NOT ((tra_id >= 1000000 AND tra_id <= 9999999) OR (tra_id >= 20000000 AND tra_id <= 39999999)) BEGIN
		PATCH_FAIL ~New engine: string @%tra_id% outside the ranges of description.tra~
	END
	PATCH_IF tra_block_size > 0 AND (tra_id < tra_block_start OR tra_id >= tra_block_start + tra_block_size) BEGIN
		PATCH_FAIL ~New engine: string @%tra_id% outside its block @%tra_block_start% (size %tra_block_size%)~
	END
	PATCH_IF NOT TRA_ENTRY_EXISTS (~%tra_id%~) BEGIN
		PATCH_FAIL ~New engine: missing string @%tra_id%~
	END
	SPRINT ~%tra_out%~ (AT ~%tra_id%~)
	SET tra_block_start = 0
	SET tra_block_size = 0
END
