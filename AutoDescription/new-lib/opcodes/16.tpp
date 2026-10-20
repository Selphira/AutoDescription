// Opcode 16 (State: Haste) : parameter2 0 hâte, 1 hâte améliorée, 2 sans attaque supplémentaire ;
// « Double la vitesse de déplacement et accorde une attaque supplémentaire par round », ou le nom du
// sort avec AD_USE_SHORT_EFFECT_DESCRIPTION (« Hâte ») ; code commun dans
// new-lib/opcodes/states.tpp. La hâte améliorée à la forme « cible » n'a pas de phrase : l'ancien
// moteur y écrit celle de la hâte (BUG-023).

DEFINE_PATCH_MACRO ad_op_16_support BEGIN END

DEFINE_PATCH_MACRO ad_op_16_lines BEGIN
	SET state_opcode = 16
	SPRINT state_variant_macro ~ad_op_16_variant~
	LPM ad_state_lines
END

// Variante des opcodes 16 et 317 : 0 hâte, 1 améliorée, 2 sans attaque supplémentaire, + 3 pour la
// version courte.
DEFINE_PATCH_MACRO ad_op_16_variant BEGIN
	SET state_haste = $fx_parameter2(~%line_fx%~)
	SET state_variant = state_haste == 1 ? 1 : (state_haste == 2 ? 2 : 0)
	PATCH_IF AD_USE_SHORT_EFFECT_DESCRIPTION BEGIN
		SET state_variant += 3
	END
END
