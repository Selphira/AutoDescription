// Opcode 270 (Cure: Unpause Target) : retire l'effet de l'opcode 165 (IESDP) : « Défige la cible » ; code
// commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_270_support BEGIN END

DEFINE_PATCH_MACRO ad_op_270_lines BEGIN
	SET state_opcode = 270
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
