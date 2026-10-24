// Opcode 153 (Overlay: Sanctuary) : « Sanctuaire » ; parameter2 ne choisit que l'animation (IESDP) ;
// code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_153_support BEGIN END

DEFINE_PATCH_MACRO ad_op_153_lines BEGIN
	SET state_opcode = 153
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
