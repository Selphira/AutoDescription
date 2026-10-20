// Opcode 38 (State: Silence) : « Réduit la cible au silence » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_38_support BEGIN END

DEFINE_PATCH_MACRO ad_op_38_lines BEGIN
	SET state_opcode = 38
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
