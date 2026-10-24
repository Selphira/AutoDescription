// Opcode 242 (Cure: Confusion) : « Dissipe la confusion de la cible », « Dissipation de la confusion »
// sur soi ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_242_support BEGIN END

DEFINE_PATCH_MACRO ad_op_242_lines BEGIN
	SET state_opcode = 242
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
