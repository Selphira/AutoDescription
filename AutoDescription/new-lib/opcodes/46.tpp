// Opcode 46 (Cure: Stun) : « Ranime la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_46_support BEGIN END

DEFINE_PATCH_MACRO ad_op_46_lines BEGIN
	SET state_opcode = 46
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
