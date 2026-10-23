// Opcode 189 (Stat: Casting Time Modifier) : modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp. Comme l'ancien opcode_189_is_valid : un ajout réduit le temps
// d'incantation (valeur écrite en négatif), un mode inconnu vaut un ajout, une valeur fixée négative
// vaut 0 ; sur EE, parameter2 2 fixe le temps d'incantation maximal.

DEFINE_PATCH_MACRO ad_op_189_support BEGIN
	FOR (stat_id = 0; stat_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == 189 BEGIN
			SET cast_value = $fx_parameter1(~%stat_id%~)
			SET cast_mode = $fx_parameter2(~%stat_id%~)
			SET $fx_cast_maximum(~%stat_id%~) = 0
			// Sans changement : écarté par l'ancien moteur.
			PATCH_IF (cast_value BAND 255) == 0 AND cast_mode == 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~file_error:opcode189:invalid~ message = ~no change (casting time modifier of 0)~ RET render_missing = refusal END
			END
			ELSE BEGIN
				PATCH_IF cast_mode > 2 OR cast_mode < 0 OR (cast_mode == 2 AND NOT IS_EE) BEGIN
					SET cast_mode = MOD_TYPE_cumulative
				END
				PATCH_IF cast_mode == MOD_TYPE_cumulative BEGIN
					SET cast_value = 0 - cast_value
				END
				ELSE PATCH_IF cast_value < 0 BEGIN
					SET cast_value = 0
				END
				PATCH_IF cast_mode == 2 BEGIN
					SET cast_mode = MOD_TYPE_flat
					SET $fx_cast_maximum(~%stat_id%~) = 1
				END
				SET $fx_parameter1(~%stat_id%~) = cast_value
				SET $fx_parameter2(~%stat_id%~) = cast_mode
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		SET stat_opcode = 189
		SPRINT stat_mode_3 ~invalid~
		LPM ad_stat_modifier_support
	END
END

DEFINE_PATCH_MACRO ad_op_189_lines BEGIN
	SET stat_opcode = 189
	SPRINT stat_line_macro ~ad_op_189_line~
	LPM ad_stat_modifier_lines
END

DEFINE_PATCH_MACRO ad_op_189_line BEGIN
	PATCH_IF $fx_cast_maximum(~%line_fx%~) BEGIN
		SET stat_name_tra = 21890003 // ~Temps d'incantation maximal~
	END
END
