// Opcode 216 (Spell Effect: Level Drain) : « Draine 2 niveaux à la cible » ; parameter1 0 inhibe le
// passage de niveau, une valeur négative injecte des niveaux ; code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_216_support BEGIN
END

DEFINE_PATCH_MACRO ad_op_216_lines BEGIN
	SET state_opcode = 216
	SPRINT state_variant_macro ~ad_op_216_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_216_variant BEGIN
	SET amount = $fx_parameter1(~%line_fx%~)
	SET state_variant = amount > 1 ? 1 : (amount == 0 ? 2 : (amount == 0 - 1 ? 3 : (amount < 0 ? 4 : 0)))
	SET amount = ABS amount
END
