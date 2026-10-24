// Opcode 367 (Minimum base stats, EE) : « Immunité à la mort par absorption de caractéristique » (les
// caractéristiques ne tombent pas à 0, IESDP), « Sensible… » pour parameter2 0 ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_367_support BEGIN END

DEFINE_PATCH_MACRO ad_op_367_lines BEGIN
	SET state_opcode = 367
	SPRINT state_variant_macro ~ad_op_367_variant~
	LPM ad_state_lines
END

// Variante 1 : sensible.
DEFINE_PATCH_MACRO ad_op_367_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0
END
