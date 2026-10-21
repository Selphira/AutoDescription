// Opcode 148 (Spell: Cast Spell (at Point)) : comme l'opcode 146, dont l'ancien moteur reprend les
// phrases ; code commun dans new-lib/opcodes/cast_spell.tpp.

DEFINE_PATCH_MACRO ad_op_148_support BEGIN
	SET cast_opcode = 148
	LPM ad_cast_spell_support
END

DEFINE_PATCH_MACRO ad_op_148_lines BEGIN
	SET cast_opcode = 148
	SET cast_phrase = 21480100 // ~%spellName%~
	LPM ad_cast_spell_lines
END
