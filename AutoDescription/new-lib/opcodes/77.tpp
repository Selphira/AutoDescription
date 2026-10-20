// Opcode 77 (Cure: Feeblemindedness) : « Guérit la débilité mentale de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_77_support BEGIN END

DEFINE_PATCH_MACRO ad_op_77_lines BEGIN
	SET state_opcode = 77
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
