// Opcode 42 (Spell: Wizard Spell Slots Modifier) : emplacements de sorts, code commun dans
// new-lib/opcodes/spell_slots.tpp.

DEFINE_PATCH_MACRO ad_op_42_support BEGIN
	SET slots_opcode = 42
	SET slots_max_level = 9
	SET slots_priest = 0
	LPM ad_spell_slots_support
END

DEFINE_PATCH_MACRO ad_op_42_lines BEGIN
	SET slots_opcode = 42
	SET slots_max_level = 9
	SET slots_priest = 0
	LPM ad_spell_slots_lines
END
