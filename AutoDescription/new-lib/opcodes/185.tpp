// Opcode 185 (State: Hold II) : comme l'opcode 175, dont l'ancien moteur reprend les macros
// (opcode_self_185) : « Paralyse la cible », ou un type de créature (« Paralyse les morts-vivants »).
// Code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_185_support BEGIN
	SET hold_opcode = 185
	LPM ad_hold_support
END

DEFINE_PATCH_MACRO ad_op_185_lines BEGIN
	SET state_opcode = 185
	SPRINT state_variant_macro ~ad_hold_variant~
	LPM ad_state_lines
END
