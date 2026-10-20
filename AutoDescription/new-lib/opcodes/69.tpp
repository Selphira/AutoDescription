// Opcode 69 (Protection: From Detection (Non-Detection)) : « Rend le porteur indétectable par des
// moyens magiques tels que la « Détection de l'invisibilité » et autres divinations », ou le nom du
// sort avec AD_USE_SHORT_EFFECT_DESCRIPTION (« Non-détection ») ; code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_69_support BEGIN END

DEFINE_PATCH_MACRO ad_op_69_lines BEGIN
	SET state_opcode = 69
	SPRINT state_variant_macro ~ad_op_69_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_69_variant BEGIN
	SET state_variant = AD_USE_SHORT_EFFECT_DESCRIPTION ? 1 : 0
END
