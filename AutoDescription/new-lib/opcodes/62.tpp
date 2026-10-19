// Opcode 62 (Spell: Priest Spell Slots Modifier) : emplacements de sorts, code commun dans
// new-lib/opcodes/spell_slots.tpp.

DEFINE_PATCH_MACRO ad_op_62_support BEGIN
	SET slots_opcode = 62
	SET slots_max_level = 7
	SET slots_priest = 1
	LPM ad_spell_slots_support
END

DEFINE_PATCH_MACRO ad_op_62_lines BEGIN
	SET slots_opcode = 62
	SET slots_max_level = 7
	SET slots_priest = 1
	LPM ad_spell_slots_lines
END
