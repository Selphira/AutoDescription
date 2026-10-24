// Opcode 109 (State: Paralyze) : « Paralyse la cible », ou un type de créature (« Paralyse les
// morts-vivants ») ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_109_support BEGIN
	SET hold_opcode = 109
	LPM ad_hold_support
END

DEFINE_PATCH_MACRO ad_op_109_lines BEGIN
	SET state_opcode = 109
	SPRINT state_variant_macro ~ad_hold_variant~
	LPM ad_state_lines
END
