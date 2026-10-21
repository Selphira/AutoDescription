// Opcode 179 (Spell Effect: Damage vs. Creature Type Modifier) : « Dégâts : +2 contre les
// lycanthropes » ; code commun dans new-lib/opcodes/versus_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_179_support BEGIN
	SET versus_opcode = 179
	LPM ad_versus_modifier_support
END

DEFINE_PATCH_MACRO ad_op_179_lines BEGIN
	SET versus_opcode = 179
	SET versus_name_tra = 21790000 // ~Dégâts~
	LPM ad_versus_modifier_lines
END
