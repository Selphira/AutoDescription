// Opcode 193 (Spell Effect: Invisible Detection by Script) : « Permet à la cible d'attaquer une créature cachée
// ou invisible », « Empêche… » pour parameter2 0 (IESDP) ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_193_support BEGIN END

DEFINE_PATCH_MACRO ad_op_193_lines BEGIN
	SET state_opcode = 193
	SPRINT state_variant_macro ~ad_op_193_variant~
	LPM ad_state_lines
END

// Variante 1 : capacité retirée.
DEFINE_PATCH_MACRO ad_op_193_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0
END
