// Opcode 45 (State: Stun) : « Étourdit la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_45_support BEGIN END

DEFINE_PATCH_MACRO ad_op_45_lines BEGIN
	SET state_opcode = 45
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
