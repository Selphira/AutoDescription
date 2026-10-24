// Opcode 175 (State: Hold) : paralyse la cible, avec la phrase de l'opcode 109 (ancien
// opcode_self_175) : « Paralyse la cible », ou un type de créature (« Paralyse les morts-vivants »).
// Code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_175_support BEGIN
	SET hold_opcode = 175
	LPM ad_hold_support
END

DEFINE_PATCH_MACRO ad_op_175_lines BEGIN
	SET state_opcode = 175
	SPRINT state_variant_macro ~ad_hold_variant~
	LPM ad_state_lines
END
