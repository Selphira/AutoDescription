// Opcode 133 (Spell Effect: Luck Non-Cumulative) : chance, comme l'opcode 22, mais non cumulative (IESDP) : « Chance : +1
// (non cumulatif) » ; code commun dans new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_133_support BEGIN
	SET stat_opcode = 133
	LPM ad_stat_modifier_byte_support
END

DEFINE_PATCH_MACRO ad_op_133_lines BEGIN
	SET stat_opcode = 133
	SPRINT stat_line_macro ~ad_stat_modifier_not_cumulative_line~
	LPM ad_stat_modifier_lines
END
