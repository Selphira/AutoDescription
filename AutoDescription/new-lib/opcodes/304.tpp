// Opcode 304 (Mass Raise Dead) : ressuscite les membres du groupe morts (IESDP), quelle que soit la
// cible de l'effet : « Ressuscite les membres du groupe » (ancien opcode_target_304, phrases de
// l'opcode 32) ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_304_support BEGIN END

DEFINE_PATCH_MACRO ad_op_304_lines BEGIN
	SET state_opcode = 304
	SPRINT state_variant_macro ~ad_op_304_party~
	LPM ad_state_lines
	SPRINT line_the_target ~~
END

DEFINE_PATCH_MACRO ad_op_304_party BEGIN
	SPRINT line_the_target @2000030 // ~les membres du groupe~
END
