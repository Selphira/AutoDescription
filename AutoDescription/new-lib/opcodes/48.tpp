// Opcode 48 (Cure: Silence) : « Rend la parole de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_48_support BEGIN END

DEFINE_PATCH_MACRO ad_op_48_lines BEGIN
	SET state_opcode = 48
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
