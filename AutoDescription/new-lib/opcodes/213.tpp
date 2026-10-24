// Opcode 213 (Spell Effect: Maze) : « Enferme la cible dans un labyrinthe » ; sur les jeux classiques
// et, sur EE, avec parameter2 0, la durée dépend de l'Intelligence de la cible (IESDP) : « …, la durée
// varie selon l'Intelligence », sans la durée de l'effet ; son délai reste écrit (ancien
// opcode_target_213 et add_duration). Code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_213_support BEGIN END

DEFINE_PATCH_MACRO ad_op_213_lines BEGIN
	SET state_opcode = 213
	SPRINT state_variant_macro ~ad_op_213_variant~
	LPM ad_state_lines
END

// Variante 0 : durée selon l'Intelligence, 1 : durée de l'effet.
DEFINE_PATCH_MACRO ad_op_213_variant BEGIN
	SET state_variant = IS_EE AND $fx_parameter2(~%line_fx%~) != 0
	PATCH_IF NOT state_variant AND $fx_timing(~%line_fx%~) != TIMING_delayed AND NOT $fx_series_anchor(~%line_fx%~) BEGIN
		SET line_no_duration = 1
	END
END
