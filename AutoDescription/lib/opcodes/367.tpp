// Opcode 367 (Minimum base stats, EE) : « Immunité à la mort par absorption de caractéristique » (les
// caractéristiques ne tombent pas à 0, IESDP), « Sensible… » pour parameter2 0 ; code commun dans lib/opcodes/states.tpp.

// Variante 1 : sensible.
DEFINE_PATCH_MACRO ad_op_367_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0
END
