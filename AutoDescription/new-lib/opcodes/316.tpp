// Opcode 316 (Spell: Magical Rest) : rend les sorts et retire la fatigue (IESDP) : « Repose la cible » ;
// code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_316_support BEGIN END

DEFINE_PATCH_MACRO ad_op_316_lines BEGIN
	SET state_opcode = 316
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
