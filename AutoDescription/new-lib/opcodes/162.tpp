// Opcode 162 (Cure: Hold) : « Guérison de la paralysie de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_162_support BEGIN END

DEFINE_PATCH_MACRO ad_op_162_lines BEGIN
	SET state_opcode = 162
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
