// Opcode 79 (Cure: Disease) : « Guérit les maladies de la cible » ; code commun dans
// new-lib/opcodes/states.tpp.

// Avec AD_ENABLE_SHRINKAGE, l'ancien moteur ajoute une guérison de la débilité mentale (opcode 77) à
// la guérison des maladies quand le bloc n'en a pas (opcode_79_group), avant ou après la
// dissipation de la magie qui la retire selon l'ordre des opcodes : pas encore repris.
DEFINE_PATCH_MACRO ad_op_79_support BEGIN
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		SPRINT render_missing ~not_implemented:opcode79:feeblemind_cure~
	END
END

DEFINE_PATCH_MACRO ad_op_79_lines BEGIN
	SET state_opcode = 79
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
