// Opcode 210 (Spell Effect: Stun 90HP) : « Étourdit la cible lorsque ses points de vie sont inférieurs à 90,
// la durée varie selon les points de vie restant » ; code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_210_support BEGIN END

DEFINE_PATCH_MACRO ad_op_210_lines BEGIN
	SET state_opcode = 210
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
