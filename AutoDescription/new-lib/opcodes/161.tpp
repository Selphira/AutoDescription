// Opcode 161 (Cure: Horror) : « Dissipe la peur de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_161_support BEGIN END

DEFINE_PATCH_MACRO ad_op_161_lines BEGIN
	SET state_opcode = 161
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
