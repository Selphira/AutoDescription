// Opcode 39 (State: Unconsciousness) : « Endort la cible », ou « Endort profondément la cible »
// quand le sommeil ne cesse pas au premier coup : sur EE avec parameter2 1, et pour l'ancien moteur
// avec un timing permanent ou différé (timings 1, 4, 7) ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_39_support BEGIN END

DEFINE_PATCH_MACRO ad_op_39_lines BEGIN
	SET state_opcode = 39
	SPRINT state_variant_macro ~ad_op_39_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_39_variant BEGIN
	SET state_timing = $fx_timing(~%line_fx%~)
	SET state_variant = (IS_EE AND $fx_parameter2(~%line_fx%~) == 1) OR state_timing == TIMING_permanent
		OR state_timing == TIMING_delayed OR state_timing == 7
END
