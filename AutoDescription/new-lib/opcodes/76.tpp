// Opcode 76 (State: Feeblemindedness) : « Inflige débilité mentale à la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_76_support BEGIN END

DEFINE_PATCH_MACRO ad_op_76_lines BEGIN
	SET state_opcode = 76
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
