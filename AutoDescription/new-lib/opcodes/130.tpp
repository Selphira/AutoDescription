// Opcode 130 (State: Bless) : « Bénédiction (+1) (non cumulatif) » ; le jeu ne lit que le premier
// octet de parameter1 (IESDP), et l'effet ne se cumule pas (ancien opcode_not_cumulative, ajouté au
// texte avant la durée, une seule fois après un 321 sur la ressource elle-même).

DEFINE_PATCH_MACRO ad_op_130_support BEGIN END

DEFINE_PATCH_MACRO ad_op_130_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~130~)
	PHP_EACH fx_ids_130 AS _ => bless_id BEGIN
		PATCH_IF NOT $fx_consumed(~%bless_id%~) BEGIN
			LPF ad_signed_value INT_VAR value = $fx_parameter1(~%bless_id%~) BAND 255 RET value = text END
			SPRINT bless_not_cumulative @4000010 // ~non cumulatif~
			SPRINT line_suffix ~(%bless_not_cumulative%)~
			SET line_fx = bless_id
			SET $fx_not_cumulative(~%bless_id%~) = 0
			SET line_phrase = 21300100 // ~Bénédiction (%value%)~
			LPM ad_effect_line
		END
	END
END
