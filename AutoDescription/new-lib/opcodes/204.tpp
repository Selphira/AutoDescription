// Opcode 204 (Spell: Protection from Spell (School)) : immunise contre les sorts de l'école de magie
// parameter2 (1-10), nommée par son complément (liste @8150000, ancien get_spell_school) :
// « Immunité contre les sorts de l'école de l'Illusion ».

// Refus : école hors de 1-10 (l'ancien moteur écrit un nom vide).
DEFINE_PATCH_MACRO ad_op_204_support BEGIN
	PHP_EACH fx_ids_204 AS _ => school_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET school_value = $fx_parameter2(~%school_id%~)
			PATCH_IF school_value < 1 OR school_value > 10 BEGIN
				LPF ad_refusal INT_VAR fx_id = school_id STR_VAR reason = ~not_implemented:opcode204:school~ message = ~school %school_value% (parameter2) outside 1-10~ RET render_missing = refusal END
			END
			ELSE BEGIN
				LPF ad_tra INT_VAR tra_id = 8150000 + school_value tra_block_start = 8150000 tra_block_size = 11 RET school_name = text END // ~de l'Illusion~ (@8150005)
				SPRINT $fx_school_name(~%school_id%~) ~%school_name%~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_204_lines BEGIN
	SET state_opcode = 204
	SPRINT state_variant_macro ~ad_op_204_name~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_204_name BEGIN
	SPRINT spellSchoolName $fx_school_name(~%line_fx%~)
END
