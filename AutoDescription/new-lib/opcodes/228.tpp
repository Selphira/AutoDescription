// Opcode 228 (Spell: Bounce (by Secondary Type, decrementing)) : « Renvoie jusqu'à 2 niveaux de
// sorts de type Attaque magique » ; code commun dans new-lib/opcodes/spell_decrement.tpp.

DEFINE_PATCH_MACRO ad_op_228_support BEGIN
	SET decrement_opcode = 228
	SET decrement_by_school = 0
	LPM ad_decrement_support
END

DEFINE_PATCH_MACRO ad_op_228_lines BEGIN
	SET decrement_opcode = 228
	SPRINT decrement_variant_macro ~~
	LPM ad_decrement_lines
END
