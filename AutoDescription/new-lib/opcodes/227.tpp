// Opcode 227 (Spell: Bounce (by School, decrementing)) : « Renvoie jusqu'à 2 niveaux de sorts de
// l'école de l'Illusion » ; code commun dans new-lib/opcodes/spell_decrement.tpp.

DEFINE_PATCH_MACRO ad_op_227_support BEGIN
	SET decrement_opcode = 227
	SET decrement_by_school = 1
	LPM ad_decrement_support
END

DEFINE_PATCH_MACRO ad_op_227_lines BEGIN
	SET decrement_opcode = 227
	SPRINT decrement_variant_macro ~~
	LPM ad_decrement_lines
END
