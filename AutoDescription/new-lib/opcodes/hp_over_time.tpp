// Code commun du poison (opcode 25) et de la régénération (opcode 98), ancien opcode_25_common :
// « Régénère 2 points de vie par round ». Selon parameter2 : 0 un point par seconde (parameter1 non
// nul), 1 un point par seconde (parameter1 supérieur à 1), 2 parameter1 points par seconde, 3 un
// point toutes les parameter1 secondes, 4 (fichier EFF seulement) parameter3 points toutes les
// parameter1 secondes. Sur EE, le multiplicateur parameter4 d'un fichier EFF (ignoré dans un objet
// ou un sort) multiplie l'intervalle des types 2 à 4 et fait agir le type 1 quel que soit
// parameter1 (IESDP). Phrase : 0100 un point, 0110 plusieurs (+ forme), fréquence dans %strDuration%.

// Ancien opcode_25_is_valid, et effets sans dégât ni soin, que l'ancien moteur n'écrit pas.
DEFINE_PATCH_MACRO ad_hp_over_time_support BEGIN
	PHP_EACH ~fx_ids_%hp_opcode%~ AS _ => hp_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET hp_timing = $fx_timing(~%hp_id%~)
			LPM ad_hp_over_time_value
			SET hp_type_max = $fx_external(~%hp_id%~) ? 4 : 3
			PATCH_IF (hp_timing == TIMING_permanent OR hp_timing == TIMING_delayed OR hp_timing == 7
					OR hp_timing == TIMING_permanent_after_death) AND $fx_duration(~%hp_id%~) == 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~file_error:opcode%hp_opcode%:timing~ message = ~effect over time with a permanent or delayed timing and no duration~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_parameter2(~%hp_id%~) < 0 OR $fx_parameter2(~%hp_id%~) > hp_type_max BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~file_error:opcode%hp_opcode%:invalid~ message = ~frequency type (parameter2) outside 0-3 (0-4 in an EFF file)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF hp_amount <= 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~file_error:opcode%hp_opcode%:no_effect~ message = ~amount of 0 or less~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_hp_over_time_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%hp_opcode%~)
	PHP_EACH ~fx_ids_%hp_opcode%~ AS _ => hp_id BEGIN
		PATCH_IF NOT $fx_consumed(~%hp_id%~) BEGIN
			LPM ad_hp_over_time_value
			SET amount = hp_amount
			LPF ad_duration_text INT_VAR seconds = hp_frequency tra_base = 3030000 RET strDuration = text END // ~par round~
			SET line_phrase = 20000000 + hp_opcode * 10000 + (hp_amount > 1 ? 110 : 100)
			SET line_fx = hp_id
			LPM ad_effect_line
		END
	END
END

// Points (hp_amount) et intervalle en secondes (hp_frequency) de l'effet hp_id.
DEFINE_PATCH_MACRO ad_hp_over_time_value BEGIN
	SET hp_value = $fx_parameter1(~%hp_id%~)
	SET hp_type = $fx_parameter2(~%hp_id%~)
	SET hp_multiplier = 0
	PATCH_IF IS_EE AND $fx_external(~%hp_id%~) BEGIN
		SET hp_multiplier = $fx_parameter4(~%hp_id%~)
	END
	SET hp_amount = 0
	SET hp_frequency = 1
	PATCH_IF (hp_type == 0 AND hp_value != 0) OR (hp_type == 1 AND (hp_value > 1 OR hp_multiplier != 0)) BEGIN
		SET hp_amount = 1
	END
	ELSE PATCH_IF hp_type == 2 AND hp_value > 0 BEGIN
		SET hp_amount = hp_value
	END
	ELSE PATCH_IF hp_type == 3 BEGIN
		SET hp_amount = 1
		SET hp_frequency = hp_value
	END
	ELSE PATCH_IF hp_type == 4 AND $fx_external(~%hp_id%~) BEGIN
		SET hp_amount = $fx_parameter3(~%hp_id%~)
		SET hp_frequency = hp_value
	END
	PATCH_IF hp_multiplier != 0 AND hp_type >= 2 BEGIN
		SET hp_frequency = hp_frequency * hp_multiplier
	END
	SET hp_frequency = hp_frequency < 1 ? 1 : hp_frequency
END
