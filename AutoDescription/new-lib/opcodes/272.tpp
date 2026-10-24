// Opcode 272 (Spell: Apply Repeating EFF) : effet du fichier EFF resource appliqué à intervalle
// régulier (ancien opcode_272_common) : « Toutes les 3 secondes ; Téléporte… ». parameter2 0 : chaque
// seconde (une fois si parameter1 est nul), 2 : parameter1 fois par seconde, 3 : toutes les
// parameter1 secondes. L'effet est décrit par les passes du moteur (new-lib/recursion.tpp, avec ses
// propres cibles et durées). Sur un effet d'équipement, chaque round : sans condition, durées de
// l'effet masquées. La condition est suivie de la durée de l'opcode, qui n'est pas répétée en fin de
// ligne ; la ligne prend le rang de l'opcode de l'EFF (ancien get_res_description).

// Refus : effet d'un EFF (l'ancien moteur y lit parameter3 et parameter4) ; parameter2 hors de 0, 2,
// 3 ; aucune application (parameter2 0 ou 2, parameter1 nul) ; effet probable ; plusieurs lignes ;
// refus de ad_recursion_support.
DEFINE_PATCH_MACRO ad_op_272_support BEGIN
	PHP_EACH fx_ids_272 AS _ => repeat_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%repeat_id%~) BEGIN
			SET repeat_type = $fx_parameter2(~%repeat_id%~)
			SET repeat_value = $fx_parameter1(~%repeat_id%~)
			SPRINT repeat_resref $fx_resource_lower(~%repeat_id%~)
			PATCH_IF $fx_external(~%repeat_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = repeat_id STR_VAR reason = ~not_implemented:opcode272:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF (repeat_type != 0 AND repeat_type != 2 AND repeat_type != 3) OR ~%repeat_resref%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = repeat_id STR_VAR reason = ~file_error:opcode272:invalid~ message = ~invalid frequency type %repeat_type% (expected 0, 2 or 3) or empty resource field~ RET render_missing = refusal END
			END
			ELSE PATCH_IF (repeat_type == 0 OR repeat_type == 2) AND repeat_value <= 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = repeat_id STR_VAR reason = ~file_error:opcode272:amount~ message = ~frequency of 0 or less~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_probability(~%repeat_id%~) < 100 BEGIN
				LPF ad_refusal INT_VAR fx_id = repeat_id STR_VAR reason = ~not_implemented:opcode272:probability~ message = ~probable effect~ RET render_missing = refusal END
			END
			ELSE BEGIN
				LPM ad_op_272_condition
				SET recursion_fx = repeat_id
				SPRINT recursion_resref ~%repeat_resref%~
				SPRINT recursion_kind ~eff~
				SET recursion_parent_dice = 0
				SET recursion_casting_level = 0
				SPRINT recursion_targets ~own~
				SET recursion_ignore_duration = repeat_hide
				SET recursion_series = 0
				SET recursion_tracked = 0
				SET recursion_depth_reset = 0
				SET recursion_versus_set = 0
				SPRINT recursion_versus ~~
				SPRINT recursion_single_reason ~not_implemented:opcode272:lines~
				SPRINT recursion_single_message ~several lines in the applied EFF file~
				LPM ad_recursion_support
			END
		END
	END
END

// Condition de l'effet repeat_id (ancien opcode_272_condition) : $fx_condition_text, et repeat_hide
// pour un effet d'équipement répété chaque round. Une fois par intervalle : « À chaque round », sinon
// « Toutes les 3 secondes » ; plusieurs fois : « 2 fois par seconde », « 2 fois tous les 2 rounds » ;
// « toutes » pour les secondes et les heures (accord de l'ancien moteur).
DEFINE_PATCH_MACRO ad_op_272_condition BEGIN
	SET amount = repeat_type == 2 ? repeat_value : 1
	SET repeat_seconds = repeat_type == 3 ? repeat_value : 1
	PATCH_IF repeat_seconds < 1 BEGIN
		SET repeat_seconds = 1
	END
	SPRINT repeat_block $fx_block(~%repeat_id%~)
	SET repeat_hide = 0
	SET repeat_unit = 0
	SET repeat_unit_amount = repeat_seconds
	FOR (duration_unit = 4; duration_unit >= 0; --duration_unit) BEGIN
		SET duration_divisor = $AD_DURATION_UNITS(~%duration_unit%~)
		PATCH_IF repeat_unit_amount == repeat_seconds AND repeat_seconds MODULO duration_divisor == 0 BEGIN
			SET repeat_unit = duration_unit
			SET repeat_unit_amount = repeat_seconds / duration_divisor
		END
	END
	PATCH_IF repeat_seconds == 1 BEGIN
		SET repeat_unit = 0
		SET repeat_unit_amount = 1
	END
	LPF ad_duration_text INT_VAR seconds = repeat_seconds RET strDuration = text END
	SET repeat_feminine = repeat_unit == 0 OR repeat_unit == 3
	PATCH_IF repeat_unit_amount == 1 BEGIN
		INNER_PATCH_SAVE strDuration ~%strDuration%~ BEGIN
			REPLACE_TEXTUALLY ~^1 ~ ~~
		END
	END
	SPRINT condition_text ~~
	PATCH_IF amount == 1 AND repeat_unit_amount == 1 AND repeat_seconds == 6 AND (~%repeat_block%~ STRING_EQUAL ~equipped~) BEGIN
		SET repeat_hide = 1
	END
	ELSE PATCH_IF amount == 1 AND repeat_unit_amount == 1 BEGIN
		SPRINT condition_text @22720010 // ~À chaque %strDuration%~
	END
	ELSE PATCH_IF amount == 1 BEGIN
		SET repeat_tra = repeat_feminine ? 22720011 : 22720012
		LPF ad_tra INT_VAR tra_id = repeat_tra RET condition_text = text END // ~Toutes les %strDuration%~
	END
	ELSE PATCH_IF repeat_unit_amount == 1 BEGIN
		SPRINT condition_text @22720013 // ~%amount% fois par %strDuration%~
	END
	ELSE BEGIN
		SET repeat_tra = repeat_feminine ? 22720014 : 22720015
		LPF ad_tra INT_VAR tra_id = repeat_tra RET condition_text = text END // ~%amount% fois toutes les %strDuration%~
	END
	SPRINT $fx_condition_text(~%repeat_id%~) ~%condition_text%~
END

DEFINE_PATCH_MACRO ad_op_272_lines BEGIN
	SPRINT line_section ~equipped~
	PHP_EACH fx_ids_272 AS _ => repeat_id BEGIN
		PATCH_IF NOT $fx_consumed(~%repeat_id%~) AND $fx_sub_count(~%repeat_id%~) > 0 BEGIN
			SET repeat_sub_opcode = $fx_sub_opcode(~%repeat_id%~)
			SET line_sort = $AD_OPCODE_SORT(~%repeat_sub_opcode%~)
			SET line_fx = repeat_id
			SPRINT line_condition $fx_condition_text(~%repeat_id%~)
			LPM ad_hit_effect_duration
			PATCH_IF NOT (~%app_duration_text%~ STRING_EQUAL ~~) AND NOT (~%line_condition%~ STRING_EQUAL ~~) BEGIN
				SPRINT line_condition ~%line_condition% %app_duration_text%~
			END
			SPRINT line_text $fx_sub_text(~%repeat_id%~)
			SET line_any_form = 1
			SET line_no_duration = 1
			LPM ad_effect_line
		END
	END
END
