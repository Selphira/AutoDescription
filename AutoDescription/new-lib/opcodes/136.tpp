// Opcode 136 (State: Force Visible) : « Rend la cible partiellement visible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_136_support BEGIN END

DEFINE_PATCH_MACRO ad_op_136_lines BEGIN
	SET state_opcode = 136
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
