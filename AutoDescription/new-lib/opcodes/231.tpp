// Opcode 231 (Spell Effect: Time Stop) : « Arrêt du temps » sur soi, « Lance Arrêt du temps » ;
// l'arrêt ne dure que la moitié de la durée de l'effet (IESDP), divisée à l'affichage
// (AD_OPCODE_DURATION_DIVISOR, new-lib/catalog.tpa). Code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_231_support BEGIN END

DEFINE_PATCH_MACRO ad_op_231_lines BEGIN
	SET state_opcode = 231
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
