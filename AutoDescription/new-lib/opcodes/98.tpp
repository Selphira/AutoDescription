// Opcode 98 (HP: Regeneration) : « Régénère 1 point de vie par round » ; code commun dans new-lib/opcodes/hp_over_time.tpp.

DEFINE_PATCH_MACRO ad_op_98_support BEGIN
	SET hp_opcode = 98
	LPM ad_hp_over_time_support
END

DEFINE_PATCH_MACRO ad_op_98_lines BEGIN
	SET hp_opcode = 98
	LPM ad_hp_over_time_lines
END
