// Opcode 109 (State: Paralyze) : « Paralyse la cible » ; code commun dans new-lib/opcodes/states.tpp.

// parameter1 non nul : paralysie d'un type de créature (parameter2, fichier IDS), que l'ancien moteur
// nomme, pas encore repris. Il décrit comme une paralysie simple un type de fichier inhabituel ou,
// sur EE, un special non nul.
DEFINE_PATCH_MACRO ad_op_109_support BEGIN
	FOR (state_id = 0; state_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++state_id) BEGIN
		PATCH_IF $fx_opcode(~%state_id%~) == 109 BEGIN
			SET state_ids = $fx_parameter2(~%state_id%~)
			SET state_plain = state_ids < 2 OR state_ids > 9 OR (state_ids > 8 AND NOT IS_EE) OR (IS_EE AND $fx_special(~%state_id%~) != 0)
			PATCH_IF $fx_parameter1(~%state_id%~) != 0 AND NOT state_plain BEGIN
				SPRINT render_missing ~not_implemented:opcode109:creature_type~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_109_lines BEGIN
	SET state_opcode = 109
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
