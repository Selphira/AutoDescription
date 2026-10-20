// Opcode 157 (State: Web Effect) : « Empêtre la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_157_support BEGIN END

DEFINE_PATCH_MACRO ad_op_157_lines BEGIN
	SET state_opcode = 157
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
