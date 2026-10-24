// Opcode 211 (Spell Effect: Imprisonment) : « Emprisonne la cible » ; le changement de sexe qui
// l'accompagne est retiré (ad_group_imprisonment, new-lib/groups.tpp). Code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_211_support BEGIN END

DEFINE_PATCH_MACRO ad_op_211_lines BEGIN
	SET state_opcode = 211
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
