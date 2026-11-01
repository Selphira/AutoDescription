// Opcode 341 (Spell Effect: Change Critical Hit Effect, EE) : sort lancé à chaque coup critique ; code
// commun dans new-lib/opcodes/event_spells.tpp.

DEFINE_PATCH_MACRO ad_op_341_support BEGIN
	SET event_opcode = 341
	SET event_weapon = 1
	LPM ad_event_spell_support
END

DEFINE_PATCH_MACRO ad_op_341_lines BEGIN
	SET event_opcode = 341
	SET event_weapon = 1
	SET event_condition_tra = 23410001 // ~À chaque coup critique~
	LPM ad_event_spell_lines
END
