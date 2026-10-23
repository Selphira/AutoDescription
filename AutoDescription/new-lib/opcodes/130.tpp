// Opcode 130 (State: Bless) : « Bénédiction (+1) (non cumulatif) » ; le jeu ne lit que le premier
// octet de parameter1 (IESDP), et l'effet ne se cumule pas (ancien opcode_not_cumulative, ajouté au
// texte avant la durée).

// Refus : effet lu après un 321 sur la ressource elle-même (fx_not_cumulative), que la ligne
// commune dirait aussi non cumulatif, cas non vérifié dans l'ancien moteur.
DEFINE_PATCH_MACRO ad_op_130_support BEGIN
	FOR (bless_id = 0; bless_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++bless_id) BEGIN
		PATCH_IF $fx_opcode(~%bless_id%~) == 130 AND $fx_not_cumulative(~%bless_id%~) BEGIN
			LPF ad_refusal INT_VAR fx_id = bless_id STR_VAR reason = ~not_implemented:opcode130:not_cumulative~ message = ~non-cumulative effect (opcode 321)~ RET render_missing = refusal END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_130_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~130~)
	FOR (bless_id = 0; bless_id < fx_count; ++bless_id) BEGIN
		PATCH_IF $fx_opcode(~%bless_id%~) == 130 AND NOT $fx_consumed(~%bless_id%~) BEGIN
			LPF ad_signed_value INT_VAR value = $fx_parameter1(~%bless_id%~) BAND 255 RET value = text END
			SPRINT bless_not_cumulative @4000010 // ~non cumulatif~
			SPRINT line_suffix ~(%bless_not_cumulative%)~
			SET line_fx = bless_id
			SET line_phrase = 21300100 // ~Bénédiction (%value%)~
			LPM ad_effect_line
		END
	END
END
