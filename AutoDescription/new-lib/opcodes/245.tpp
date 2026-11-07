// Opcode 245 (Check For Berserk) : 1 % de chances, à chaque attaque de la créature, de la rendre
// berserk (IESDP : « on each attack it makes », sans condition de réussite ; il attache l'opcode 246) :
// « Chaque attaque a 1 % de chances de provoquer la folie du berserker chez le porteur » ; code commun
// dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_245_support BEGIN END

DEFINE_PATCH_MACRO ad_op_245_lines BEGIN
	SET state_opcode = 245
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
