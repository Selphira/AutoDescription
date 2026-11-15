// Opcode 302 (Item: Can Use Any Item) : « Permet d'utiliser n'importe quel objet (si les caractéristiques sont
// suffisantes) », « Bloque la capacité… » pour parameter2 0 ; code commun dans lib/opcodes/states.tpp.

// Variante 1 : capacité bloquée.
DEFINE_PATCH_MACRO ad_op_302_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0
END
