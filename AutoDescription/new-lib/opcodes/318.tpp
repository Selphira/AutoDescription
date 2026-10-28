// Opcode 318 (Protection from Resource, EE) : sur la ressource elle-même, exception de cible des
// effets lus après lui (« Inefficace contre les morts-vivants ») ; code commun dans
// new-lib/opcodes/target_exceptions.tpp. Probable et sous une condition de splprot.2da (pnp_potion) :
// une ligne, la condition du 326 puis « 24 % de chances d'être sans effet » (ancien opcode virtuel 526).

DEFINE_PATCH_MACRO ad_op_318_support BEGIN
	SET exception_opcode = 318
	LPM ad_target_exception_support
	PHP_EACH fx_ids_318 AS _ => apply_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND $fx_no_effect_chance(~%apply_id%~) AND NOT $fx_consumed(~%apply_id%~) BEGIN
			LPM ad_op_326_condition
		END
	END
END

DEFINE_PATCH_MACRO ad_op_318_lines BEGIN
	SET exception_opcode = 318
	LPM ad_target_exception_lines
	PHP_EACH fx_ids_318 AS _ => apply_id BEGIN
		PATCH_IF $fx_no_effect_chance(~%apply_id%~) AND NOT $fx_consumed(~%apply_id%~) BEGIN
			SPRINT apply_pending $fx_condition_refusal(~%apply_id%~)
			PATCH_IF NOT (~%apply_pending%~ STRING_EQUAL ~~) BEGIN
				SPRINT apply_pending_message $fx_condition_refusal_message(~%apply_id%~)
				LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~%apply_pending%~ message = ~%apply_pending_message%~ RET render_late_missing = refusal END
			END
			ELSE BEGIN
				SPRINT line_condition $fx_condition_text(~%apply_id%~)
				SET value = $fx_probability(~%apply_id%~)
				SPRINT chanceValue @1200003 // ~%value%%PERCENT%~
				SPRINT line_text @23180100 // ~%chanceValue% de chances d'être sans effet~
				PATCH_IF NOT (~%line_condition%~ STRING_EQUAL ~~) BEGIN
					SPRINT line_text ~%line_condition%%AD_SEMICOLON%%line_text%~
				END
				SPRINT line_section $fx_line_section(~%apply_id%~)
				SET line_sort = $AD_OPCODE_SORT(~326~) - 1
				SET line_probability = 0
				LPM ad_line_add
			END
		END
	END
END
