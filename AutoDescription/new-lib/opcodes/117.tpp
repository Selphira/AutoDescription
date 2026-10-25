// Opcode 117 (Spell Effect: Reveal Area) : « Révèle l'entièreté de la carte » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_117_support BEGIN END

DEFINE_PATCH_MACRO ad_op_117_lines BEGIN
	SET state_opcode = 117
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
