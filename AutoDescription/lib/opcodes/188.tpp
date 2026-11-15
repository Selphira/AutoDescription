// Opcode 188 (Spell Effect: Aura Cleansing) : « Permet de lancer plusieurs sorts par round », ou un
// seul avec parameter2 0 ; code commun dans lib/opcodes/states.tpp.

// Variante 1 : un seul sort par round.
DEFINE_PATCH_MACRO ad_op_188_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0
END
