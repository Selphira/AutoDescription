// Opcode 233 (Stat: Proficiency Modifier) : parameter1 = points de compétence, mot de poids faible de
// parameter2 = compétence (stats.ids 89 à 134) ; sur EE, mot de poids fort 1 = ajout (Increment),
// 0 = valeur fixée ; « Compétence martiale Épée longue : Passe à 5 », « +1 » pour un ajout. Avec
// special non nul, l'ajout vise la valeur parameter1 (IESDP), décrite par l'ancien moteur comme une
// valeur fixée pour l'épée longue (90) seulement, la seule compétence où le jeu l'applique ; pour une
// autre, special est sans effet. Modificateur simple, code
// commun dans new-lib/opcodes/stat_modifiers.tpp ; nom de la compétence lu dans weapprof.2da
// (AD_PROFICIENCY_NAMES).

// Validation de l'ancien opcode_233_is_valid. Une statistique de compétence sans nom dans
// weapprof.2da (EXTRAPROFICIENCY…, que le jeu détourne en marqueur de sort) n'est pas une
// compétence du personnage : l'ancien moteur l'écarte sans rien écrire, avant de réunir les effets
// identiques (plusieurs marqueurs d'un même sort ne sont pas des doublons).
DEFINE_PATCH_MACRO ad_op_233_support BEGIN
	PHP_EACH fx_ids_233 AS _ => stat_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET proficiency_stat = $fx_parameter2(~%stat_id%~) BAND 65535
			SET proficiency_mode = IS_EE ? $fx_parameter2(~%stat_id%~) BLSR 16 : 0
			PATCH_IF proficiency_stat < 89 OR proficiency_stat > 134 OR proficiency_mode > 1 BEGIN
				SET drop_id = stat_id
				SPRINT ignored_reason ~file_error:opcode233:invalid~
				SPRINT ignored_message ~proficiency %proficiency_stat% (expected 89-134) or mode %proficiency_mode% (expected 0-1)~
				LPM ad_application_drop
			END
			ELSE PATCH_IF NOT VARIABLE_IS_SET $AD_PROFICIENCY_NAMES(~%proficiency_stat%~) BEGIN
				SET $fx_stat_subject(~%stat_id%~) = proficiency_stat
				SET drop_id = stat_id
				SPRINT ignored_reason ~not_implemented:opcode233:no_name~
				SPRINT ignored_message ~proficiency %proficiency_stat% has no name~
				LPM ad_application_drop
			END
			ELSE BEGIN
				SET $fx_stat_subject(~%stat_id%~) = proficiency_stat
				SET proficiency_delta = proficiency_mode == 1 AND $fx_special(~%stat_id%~) != 0 AND proficiency_stat == 90
				SET $fx_parameter2(~%stat_id%~) = (proficiency_mode == 1 AND NOT proficiency_delta) ? MOD_TYPE_cumulative : MOD_TYPE_flat
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		SET stat_opcode = 233
		SPRINT stat_mode_3 ~invalid~
		LPM ad_stat_modifier_support
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
