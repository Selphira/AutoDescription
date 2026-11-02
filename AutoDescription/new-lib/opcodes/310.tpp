// Opcode 310 (Protection: from Timestop) : parameter2 non nul immunise contre l'arrêt du temps, 0
// suspend cette immunité pendant la durée de l'effet (IESDP) : « Immunité contre l'arrêt du temps »,
// « Bloque l'immunité contre l'arrêt du temps » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_310_support BEGIN END

DEFINE_PATCH_MACRO ad_op_310_lines BEGIN
	SET state_opcode = 310
	SPRINT state_variant_macro ~ad_op_310_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_310_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0 ? 1 : 0
END
