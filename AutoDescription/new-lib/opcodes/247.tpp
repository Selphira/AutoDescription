// Opcode 247 (Spell Effect: Attack Nearest Creature) : « Provoque la folie du berserker chez la
// cible », « En combat » avec parameter2 0 (ancien opcode_247_condition) ; code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_247_support BEGIN END

DEFINE_PATCH_MACRO ad_op_247_lines BEGIN
	SET state_opcode = 247
	SPRINT state_variant_macro ~ad_op_247_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_247_variant BEGIN
	PATCH_IF $fx_parameter2(~%line_fx%~) == 0 BEGIN
		SPRINT line_condition @22470001 // ~En combat~
	END
END
