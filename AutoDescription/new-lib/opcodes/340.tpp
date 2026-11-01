// Opcode 340 (Spell Effect: Change Backstab Effect, EE) : sort lancé à chaque attaque sournoise ;
// parameter1, parameter2 et special sans rôle (IESDP) ; code commun dans
// new-lib/opcodes/event_spells.tpp.

DEFINE_PATCH_MACRO ad_op_340_support BEGIN
	SET event_opcode = 340
	SET event_weapon = 0
	LPM ad_event_spell_support
END

DEFINE_PATCH_MACRO ad_op_340_lines BEGIN
	SET event_opcode = 340
	SET event_weapon = 0
	SET event_condition_tra = 23400001 // ~À chaque attaque sournoise~
	LPM ad_event_spell_lines
END
