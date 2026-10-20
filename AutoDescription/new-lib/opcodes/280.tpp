// Opcode 280 (Spell Effect: Wild Magic) : parameter2 1 fait du prochain sort lancé un hiatus
// entropique, au-delà de 1 tous les sorts, sinon dissipe ces effets ; code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_280_support BEGIN END

DEFINE_PATCH_MACRO ad_op_280_lines BEGIN
	SET state_opcode = 280
	SPRINT state_variant_macro ~ad_op_280_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_280_variant BEGIN
	SET surge_mode = $fx_parameter2(~%line_fx%~)
	SET state_variant = surge_mode == 1 ? 0 : (surge_mode > 1 ? 1 : 2)
END
