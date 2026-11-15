// Opcode 193 (Spell Effect: Invisible Detection by Script) : « Permet à la cible d'attaquer une créature cachée
// ou invisible », « Empêche… » pour parameter2 0 (IESDP) ; code commun dans lib/opcodes/states.tpp.

// Variante 1 : capacité retirée.
DEFINE_PATCH_MACRO ad_op_193_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0
END
