// Opcode 125 (Spell Effect: Unlock (Knock)) : « Déverrouille la serrure ciblée » ; formes « cible »
// seulement, comme dans l'ancien moteur ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_125_support BEGIN END

DEFINE_PATCH_MACRO ad_op_125_lines BEGIN
	SET state_opcode = 125
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
