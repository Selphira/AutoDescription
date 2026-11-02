// Opcode 295 (Graphics: Disable Permanent Death) : parameter2 non nul empêche la mort définitive,
// 0 suspend cette protection pendant la durée de l'effet (IESDP) : « Protection contre la mort
// définitive », « Rend la cible sensible à la mort définitive » ; code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_295_support BEGIN END

DEFINE_PATCH_MACRO ad_op_295_lines BEGIN
	SET state_opcode = 295
	SPRINT state_variant_macro ~ad_op_295_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_295_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0 ? 1 : 0
END
