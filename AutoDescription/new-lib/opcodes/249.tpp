// Opcode 249 (Item: Set Ranged Effect) : effet d'un fichier EFF à chaque attaque à distance réussie ;
// code commun dans new-lib/opcodes/hit_effects.tpp.

DEFINE_PATCH_MACRO ad_op_249_support BEGIN
	SET hit_opcode = 249
	LPM ad_hit_effect_support
END

DEFINE_PATCH_MACRO ad_op_249_lines BEGIN
	SET hit_opcode = 249
	SET hit_condition_self = 22490001 // ~À chaque attaque à distance réussie~
	SET hit_condition_target = 22490002 // ~À chaque attaque à distance réussie par %theTarget%~
	LPM ad_hit_effect_lines
END
