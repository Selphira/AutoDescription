// Opcode 188 (Spell Effect: Aura Cleansing) : « Permet de lancer plusieurs sorts par round », ou un
// seul avec parameter2 0 ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_188_support BEGIN END

DEFINE_PATCH_MACRO ad_op_188_lines BEGIN
	SET state_opcode = 188
	SPRINT state_variant_macro ~ad_op_188_variant~
	LPM ad_state_lines
END

// Variante 1 : un seul sort par round.
DEFINE_PATCH_MACRO ad_op_188_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0
END
