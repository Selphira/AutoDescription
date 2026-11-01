// Opcode 244 (Spell: Drain Wizard Spell) : draine parameter1 sorts profanes de la mémoire de la
// cible : « Draine 1 sort profane de la mémoire de la cible » ; code commun dans
// new-lib/opcodes/states.tpp. Nombre tiré au sort réuni : « Draine entre 1 et 10 sorts profanes »
// (new-lib/opcodes/value_ranges.tpp).

// Aucun sort drainé : écarté et journalisé (ancien opcode_244_is_valid).
DEFINE_PATCH_MACRO ad_op_244_support BEGIN
	PHP_EACH fx_ids_244 AS _ => drain_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND $fx_parameter1(~%drain_id%~) <= 0 BEGIN
			SET drop_id = drain_id
			SPRINT ignored_reason ~file_error:opcode244:invalid~
			SPRINT ignored_message ~number of spells to drain of 0 or less~
			LPM ad_application_drop
		END
	END
	SET range_opcode = 244
	SPRINT range_eligible_macro ~~
	LPM ad_value_range_support
END

DEFINE_PATCH_MACRO ad_op_244_lines BEGIN
	SET state_opcode = 244
	SPRINT state_variant_macro ~ad_op_244_variant~
	LPM ad_state_lines
END

// Variante 0 : un sort, 1 : plusieurs.
DEFINE_PATCH_MACRO ad_op_244_variant BEGIN
	SET amount = $fx_parameter1(~%line_fx%~)
	SET state_variant = amount == 1 ? 0 : 1
	LPM ad_value_range_text
	PATCH_IF NOT (~%range_text%~ STRING_EQUAL ~~) BEGIN
		SPRINT amount ~%range_text%~
		SET state_variant = 1
	END
END
