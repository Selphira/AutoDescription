// Opcode 200 (Spell: Bounce (by Power Level, decrementing)) : « Renvoie jusqu'à 6 niveaux de sorts
// parmi ceux de 1er niveau » ; code commun dans new-lib/opcodes/spell_power.tpp.

DEFINE_PATCH_MACRO ad_op_200_support BEGIN
	SET power_opcode = 200
	LPM ad_spell_power_support
END

DEFINE_PATCH_MACRO ad_op_200_lines BEGIN
	SET power_opcode = 200
	SET power_phrase = 22000100 // ~Renvoie jusqu'à %amount% niveaux de sorts parmi ceux de %levelStr% niveau~
	LPM ad_spell_power_lines
END
