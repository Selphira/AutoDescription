// Opcode 244 (Spell: Drain Wizard Spell) : draine parameter1 sorts profanes de la mémoire de la
// cible : « Draine 1 sort profane de la mémoire de la cible » ; code commun dans
// new-lib/opcodes/states.tpp.

// Refus : aucun sort drainé (écarté par l'ancien opcode_244_is_valid).
DEFINE_PATCH_MACRO ad_op_244_support BEGIN
	FOR (drain_id = 0; drain_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++drain_id) BEGIN
		PATCH_IF $fx_opcode(~%drain_id%~) == 244 AND $fx_parameter1(~%drain_id%~) <= 0 BEGIN
			LPF ad_refusal INT_VAR fx_id = drain_id STR_VAR reason = ~file_error:opcode244:invalid~ message = ~number of spells to drain of 0 or less~ RET render_missing = refusal END
		END
	END
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
END
