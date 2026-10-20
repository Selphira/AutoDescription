// Opcode 63 (State: Infravision) : « Octroie la capacité d'infravision à la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_63_support BEGIN END

DEFINE_PATCH_MACRO ad_op_63_lines BEGIN
	SET state_opcode = 63
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
