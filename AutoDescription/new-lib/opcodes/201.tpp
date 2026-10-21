// Opcode 201 (Spell: Immunity (by Power Level, decrementing)) : « Immunise jusqu'à 9 niveaux de
// sorts » ; code commun dans new-lib/opcodes/spell_power.tpp.

DEFINE_PATCH_MACRO ad_op_201_support BEGIN
	SET power_opcode = 201
	LPM ad_spell_power_support
END

DEFINE_PATCH_MACRO ad_op_201_lines BEGIN
	SET power_opcode = 201
	SET power_phrase = 22010100 // ~Immunise jusqu'à %amount% niveaux de sorts parmi ceux de %levelStr% niveau~
	LPM ad_spell_power_lines
END
