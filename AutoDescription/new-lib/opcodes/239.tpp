// Opcode 239 (Spell Effect: Farsight) : « Permet d'observer une zone, même inconnue », « … déjà reconnue » pour
// parameter2 0 (IESDP) ; forme « soi » seulement, comme dans l'ancien moteur ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_239_support BEGIN END

DEFINE_PATCH_MACRO ad_op_239_lines BEGIN
	SET state_opcode = 239
	SPRINT state_variant_macro ~ad_op_239_variant~
	LPM ad_state_lines
END

// Variante 1 : zone même inconnue.
DEFINE_PATCH_MACRO ad_op_239_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) != 0
END
