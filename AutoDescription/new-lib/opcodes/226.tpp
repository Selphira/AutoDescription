// Opcode 226 (Spell: Immunity (by Secondary Type, decrementing)) : « Immunise jusqu'à 2 niveaux de sorts
// de type Attaque magique » ; code commun dans new-lib/opcodes/spell_decrement.tpp.

DEFINE_PATCH_MACRO ad_op_226_support BEGIN
	SET decrement_opcode = 226
	SET decrement_by_school = 0
	LPM ad_decrement_support
END

DEFINE_PATCH_MACRO ad_op_226_lines BEGIN
	SET decrement_opcode = 226
	SPRINT decrement_variant_macro ~ad_op_226_variant~
	LPM ad_decrement_lines
END

// Variante 1 : total de 1, épuisé par le premier sort bloqué quel que soit son niveau (« Immunise contre
// le prochain sort de type Attaque magique »).
DEFINE_PATCH_MACRO ad_op_226_variant BEGIN
	SET state_variant = amount == 1
END
