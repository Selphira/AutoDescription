// Opcode 248 (Item: Set Melee Effect) : effet d'un fichier EFF à chaque attaque de mêlée réussie ; code
// commun dans new-lib/opcodes/hit_effects.tpp.

DEFINE_PATCH_MACRO ad_op_248_support BEGIN
	SET hit_opcode = 248
	LPM ad_hit_effect_support
END

DEFINE_PATCH_MACRO ad_op_248_lines BEGIN
	SET hit_opcode = 248
	SET hit_condition_self = 22480001 // ~À chaque attaque de mêlée réussie~
	SET hit_condition_target = 22480003 // ~À chaque attaque de mêlée réussie par %theTarget%~
	LPM ad_hit_effect_lines
END
