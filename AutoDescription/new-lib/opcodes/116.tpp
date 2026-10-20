// Opcode 116 (State: Cure Invisibility) : « Dissipe l'invisibilité de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_116_support BEGIN END

DEFINE_PATCH_MACRO ad_op_116_lines BEGIN
	SET state_opcode = 116
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
