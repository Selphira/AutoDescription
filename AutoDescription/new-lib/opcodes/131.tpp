// Opcode 131 (State: Positive Chant) : chance, comme l'opcode 22, mais non cumulative (IESDP) : « Chance : +1
// (non cumulatif) » ; code commun dans new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_131_support BEGIN
	SET stat_opcode = 131
	LPM ad_stat_modifier_byte_support
END

DEFINE_PATCH_MACRO ad_op_131_lines BEGIN
	SET stat_opcode = 131
	SPRINT stat_line_macro ~ad_stat_modifier_not_cumulative_line~
	LPM ad_stat_modifier_lines
END
