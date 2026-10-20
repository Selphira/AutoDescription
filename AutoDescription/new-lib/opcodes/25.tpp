// Opcode 25 (State: Poison) : « Empoisonne la cible, lui infligeant 1 point de dégâts par seconde » ; code commun dans new-lib/opcodes/hp_over_time.tpp.

DEFINE_PATCH_MACRO ad_op_25_support BEGIN
	SET hp_opcode = 25
	LPM ad_hp_over_time_support
END

DEFINE_PATCH_MACRO ad_op_25_lines BEGIN
	SET hp_opcode = 25
	LPM ad_hp_over_time_lines
END
