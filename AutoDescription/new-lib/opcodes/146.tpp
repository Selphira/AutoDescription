// Opcode 146 (Spell: Cast Spell (at Creature)) : « Lance « Boule de feu » sur la cible » ; code
// commun dans new-lib/opcodes/cast_spell.tpp.

DEFINE_PATCH_MACRO ad_op_146_support BEGIN
	SET cast_opcode = 146
	LPM ad_cast_spell_support
END

DEFINE_PATCH_MACRO ad_op_146_lines BEGIN
	SET cast_opcode = 146
	SET cast_phrase = 21460100 // ~%spellName%~
	LPM ad_cast_spell_lines
END
