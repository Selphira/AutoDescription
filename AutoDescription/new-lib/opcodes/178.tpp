// Opcode 178 (Spell Effect: THAC0 vs. Creature Type Modifier) : « TAC0 : +2 contre les
// lycanthropes » ; code commun dans new-lib/opcodes/versus_modifiers.tpp.

DEFINE_PATCH_MACRO ad_op_178_support BEGIN
	SET versus_opcode = 178
	LPM ad_versus_modifier_support
END

DEFINE_PATCH_MACRO ad_op_178_lines BEGIN
	SET versus_opcode = 178
	SET versus_name_tra = 21780000 // ~TAC0~
	LPM ad_versus_modifier_lines
END
