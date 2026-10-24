// Opcode 137 (State: Negative Chant) : chance non cumulative, réduite de la valeur de parameter1
// (IESDP : l'inverse du chant, opcode 131) : « Chance : -1 (non cumulatif) » ; code commun dans
// new-lib/opcodes/stat_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_137_support BEGIN
	SET stat_opcode = 137
	LPM ad_stat_modifier_byte_support
END

DEFINE_PATCH_MACRO ad_op_137_lines BEGIN
	SET stat_opcode = 137
	SPRINT stat_line_macro ~ad_op_137_line~
	LPM ad_stat_modifier_lines
END

DEFINE_PATCH_MACRO ad_op_137_line BEGIN
	SET stat_value = 0 - stat_value
	LPM ad_stat_modifier_not_cumulative_line
END
