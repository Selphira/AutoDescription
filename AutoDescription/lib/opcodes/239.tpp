// Opcode 239 (Spell Effect: Farsight) : « Permet d'observer une zone, même inconnue », « … déjà reconnue » pour
// parameter2 0 (IESDP) ; forme « soi » seulement, comme dans l'ancien moteur ; code commun dans lib/opcodes/states.tpp.

// Variante 1 : zone même inconnue.
DEFINE_PATCH_MACRO ad_op_239_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) != 0
END
