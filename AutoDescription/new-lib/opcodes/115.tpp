// Opcode 115 (Detect: Alignment) : « Détection du mal par la cible » ; parameter2 = alignement détecté
// (IESDP : 0 mauvais, 1 neutre, 2 bon) ; code commun dans new-lib/opcodes/states.tpp.

// Alignement hors de 0-2 : écarté et journalisé (ancien opcode_115_is_valid).
DEFINE_PATCH_MACRO ad_op_115_support BEGIN
	PHP_EACH fx_ids_115 AS _ => detect_id BEGIN
		SET detect_alignment = $fx_parameter2(~%detect_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND (detect_alignment < 0 OR detect_alignment > 2) BEGIN
			SET drop_id = detect_id
			SPRINT ignored_reason ~file_error:opcode115:invalid~
			SPRINT ignored_message ~alignment %detect_alignment% (expected 0-2)~
			LPM ad_application_drop
		END
	END
END

DEFINE_PATCH_MACRO ad_op_115_lines BEGIN
	SET state_opcode = 115
	SPRINT state_variant_macro ~ad_op_115_variant~
	LPM ad_state_lines
END

// Nom de l'alignement détecté (alignment).
DEFINE_PATCH_MACRO ad_op_115_variant BEGIN
	LPF ad_tra INT_VAR tra_id = 21150010 + $fx_parameter2(~%line_fx%~) tra_block_start = 21150010 tra_block_size = 3 RET alignment = text END // ~neutre~ (@21150011)
END
