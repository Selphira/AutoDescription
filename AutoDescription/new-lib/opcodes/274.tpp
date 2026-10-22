// Opcode 274 (Spell Effect: Teleport to Target) : téléporte la cible auprès d'un ennemi au hasard, sans
// paramètre (IESDP) : « Téléporte aléatoirement le porteur auprès d'un ennemi à portée de vue ». Code
// commun dans new-lib/opcodes/states.tpp.
DEFINE_PATCH_MACRO ad_op_274_support BEGIN
END

DEFINE_PATCH_MACRO ad_op_274_lines BEGIN
	SET state_opcode = 274
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
