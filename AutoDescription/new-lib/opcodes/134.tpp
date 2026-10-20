// Opcode 134 (State: Petrification) : « Pétrifie la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_134_support BEGIN END

DEFINE_PATCH_MACRO ad_op_134_lines BEGIN
	SET state_opcode = 134
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
