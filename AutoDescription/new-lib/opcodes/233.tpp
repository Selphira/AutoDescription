// Opcode 233 (Stat: Proficiency Modifier) : parameter1 = points de compétence, mot de poids faible de
// parameter2 = compétence (stats.ids 89 à 134) ; sur EE, mot de poids fort 1 = ajout (Increment),
// 0 = valeur fixée ; « Compétence martiale Épée longue : Passe à 5 ». Modificateur simple, code
// commun dans new-lib/opcodes/stat_modifiers.tpp ; nom de la compétence lu dans weapprof.2da
// (AD_PROFICIENCY_NAMES).

// Validation de l'ancien opcode_233_is_valid. Une statistique de compétence sans nom dans
// weapprof.2da (EXTRAPROFICIENCY…, que le jeu détourne en marqueur de sort) n'est pas une
// compétence du personnage : l'ancien moteur l'écarte sans rien écrire.
DEFINE_PATCH_MACRO ad_op_233_support BEGIN
	FOR (stat_id = 0; stat_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == 233 BEGIN
			SET proficiency_stat = $fx_parameter2(~%stat_id%~) BAND 65535
			SET proficiency_mode = IS_EE ? $fx_parameter2(~%stat_id%~) BLSR 16 : 0
			PATCH_IF proficiency_stat < 89 OR proficiency_stat > 134 OR proficiency_mode > 1 BEGIN
				SPRINT render_missing ~not_implemented:opcode233:invalid~
			END
			// Ajout (EE) : l'ancien moteur perd le mode dès la validation et écrit une valeur fixée
			// (BUG-028).
			ELSE PATCH_IF proficiency_mode == 1 BEGIN
				SPRINT render_missing ~not_implemented:opcode233:increment~
			END
			ELSE BEGIN
				SET $fx_stat_subject(~%stat_id%~) = proficiency_stat
				SET $fx_parameter2(~%stat_id%~) = MOD_TYPE_flat
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		SET stat_opcode = 233
		SPRINT stat_mode_3 ~invalid~
		LPM ad_stat_modifier_support
	END
	FOR (stat_id = 0; stat_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == 233 BEGIN
			SET proficiency_stat = $fx_stat_subject(~%stat_id%~)
			PATCH_IF NOT VARIABLE_IS_SET $AD_PROFICIENCY_NAMES(~%proficiency_stat%~) BEGIN
				LPM ad_op_233_ignored_support
				SET $fx_consumed(~%stat_id%~) = 1
			END
		END
	END
END

// L'ancien moteur écarte l'effet stat_id dès sa lecture, mais la durée commune des effets d'une
// potion est déjà calculée (ad_item_potion_durations) : l'effet écarté est accepté dans un en-tête si
// un autre effet décrit du même en-tête a la même durée, ou s'il est sans durée.
DEFINE_PATCH_MACRO ad_op_233_ignored_support BEGIN
	SPRINT ignored_scope $fx_scope(~%stat_id%~)
	SET ignored_timing = $fx_timing(~%stat_id%~)
	PATCH_IF NOT (~%ignored_scope%~ STRING_EQUAL ~equipped~)
			AND (ignored_timing == TIMING_duration OR ignored_timing == TIMING_duration_ticks) BEGIN
		SET ignored_twin = 0
		FOR (ignored_other = 0; ignored_other < fx_count; ++ignored_other) BEGIN
			SET render_opcode = $fx_opcode(~%ignored_other%~)
			SPRINT ignored_other_scope $fx_scope(~%ignored_other%~)
			LPM ad_opcode_is_described
			PATCH_IF ignored_other != stat_id AND opcode_described AND render_opcode != 233
					AND (~%ignored_other_scope%~ STRING_EQUAL ~%ignored_scope%~)
					AND $fx_timing(~%ignored_other%~) == ignored_timing
					AND $fx_duration(~%ignored_other%~) == $fx_duration(~%stat_id%~) BEGIN
				SPRINT ignored_duration_kind $AD_OPCODE_DURATION(~%render_opcode%~)
				PATCH_IF NOT (~%ignored_duration_kind%~ STRING_EQUAL ~IGNORED~) BEGIN
					SET ignored_twin = 1
				END
			END
		END
		PATCH_IF NOT ignored_twin BEGIN
			SPRINT render_missing ~not_implemented:opcode233:ignored_duration~
		END
	END
END

DEFINE_PATCH_MACRO ad_op_233_lines BEGIN
	SET stat_opcode = 233
	SPRINT stat_line_macro ~ad_op_233_line~
	LPM ad_stat_modifier_lines
END

DEFINE_PATCH_MACRO ad_op_233_line BEGIN
	SET proficiency_stat = $fx_stat_subject(~%line_fx%~)
	SPRINT proficiency $AD_PROFICIENCY_NAMES(~%proficiency_stat%~)
END
