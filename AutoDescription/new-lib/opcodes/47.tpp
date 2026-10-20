// Opcode 47 (Cure: Invisibility) : « Dissipe l'invisibilité de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_47_support BEGIN END

DEFINE_PATCH_MACRO ad_op_47_lines BEGIN
	SET state_opcode = 47
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
