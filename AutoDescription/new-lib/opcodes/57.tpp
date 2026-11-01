// Opcode 57 (Alignment: Change) : alignement de la cible fixé à parameter2 (IESDP : 17 loyal bon, 18
// loyal neutre, 19 loyal mauvais, 33 neutre bon, 34 neutre strict, 35 neutre mauvais, 49 chaotique
// bon, 50 chaotique neutre, 51 chaotique mauvais) : « Alignement modifié en neutre mauvais » ; code
// commun dans new-lib/opcodes/states.tpp. Noms des alignements : 2057 0000 + parameter2.

// Alignement inconnu : écarté et journalisé (ancien opcode_57_is_valid).
DEFINE_PATCH_MACRO ad_op_57_support BEGIN
	PHP_EACH fx_ids_57 AS _ => alignment_id BEGIN
		SET alignment_value = $fx_parameter2(~%alignment_id%~)
		SET alignment_order = alignment_value BAND 15
		SET alignment_known = (alignment_value BAND (BNOT 15)) >= 16 AND (alignment_value BAND (BNOT 15)) <= 48
			AND alignment_order >= 1 AND alignment_order <= 3
		PATCH_IF NOT $fx_dropped(~%alignment_id%~) AND NOT alignment_known BEGIN
			SET drop_id = alignment_id
			SPRINT ignored_reason ~file_error:opcode57:alignment~
			SPRINT ignored_message ~unknown alignment %alignment_value% (expected 17-19, 33-35, 49-51)~
			LPM ad_application_drop
		END
	END
END

DEFINE_PATCH_MACRO ad_op_57_lines BEGIN
	SET state_opcode = 57
	SPRINT state_variant_macro ~ad_op_57_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_57_variant BEGIN
	LPF ad_tra INT_VAR tra_id = 20570000 + $fx_parameter2(~%line_fx%~) tra_block_start = 20570017 tra_block_size = 35 RET alignment = text END // ~neutre mauvais~ (@20570035)
END
