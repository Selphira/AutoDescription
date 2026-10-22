// Opcode 32 (Cure: Death) : « Ressuscite la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_32_support BEGIN END

DEFINE_PATCH_MACRO ad_op_32_lines BEGIN
	SET state_opcode = 32
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
