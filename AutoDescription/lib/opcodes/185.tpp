// Opcode 185 (State: Hold II) : comme l'opcode 175, dont l'ancien moteur reprend les macros
// (opcode_self_185) : « Paralyse la cible », ou un type de créature (« Paralyse les morts-vivants »).
// Code commun dans lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_185_support BEGIN
	SET hold_opcode = 185
	LPM ad_hold_support
END
