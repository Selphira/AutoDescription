// Opcode 2 (Cure: Sleep) : « Réveille la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_2_support BEGIN END

DEFINE_PATCH_MACRO ad_op_2_lines BEGIN
	SET state_opcode = 2
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
