// Opcode 3 (State: Berserking) : « Provoque la folie du berserker chez la cible » ; code commun dans
// new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_3_support BEGIN END

DEFINE_PATCH_MACRO ad_op_3_lines BEGIN
	SET state_opcode = 3
	SPRINT state_variant_macro ~ad_op_3_variant~
	LPM ad_state_lines
END

// « En combat » sauf pour un effet permanent ou, sur EE, de parameter2 1 (ancien opcode_3_condition) :
// l'ancien moteur lit ainsi la rage qui ne dure que le temps du combat.
DEFINE_PATCH_MACRO ad_op_3_variant BEGIN
	PATCH_IF $fx_timing(~%line_fx%~) != TIMING_permanent AND ($fx_parameter2(~%line_fx%~) != 1 OR NOT IS_EE) BEGIN
		SPRINT line_condition @20030001 // ~En combat~
	END
END
