// Opcode 1 (Stat: Attacks Per Round Modifier) : parameter1 = attaques par round, parameter2 = mode
// (0 ajout, 1 valeur fixée, 2 pourcentage ; 3, EE seulement : valeur finale fixée, un ajout sur un
// jeu classique). Les valeurs 0 à 5 sont des attaques entières, 6 à 10 des demi-attaques (½, 1½…
// 4½) : AD_ATTACKS_PER_ROUND donne leur nombre en dixièmes. En valeur fixée, l'ancien moteur ramène
// une valeur négative à 0 et une valeur au-delà de 10 à 10 ; une valeur fixée nulle empêche
// d'attaquer.
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp).

// ---------------------------------------------------------------------------------------------
// Prise en charge (ancien opcode_1_is_valid, plus les cas que ce moteur ne décrit pas encore)

DEFINE_PATCH_MACRO ad_op_1_support BEGIN
	PHP_EACH fx_ids_1 AS _ => apr_id BEGIN
		LPM ad_op_1_value
		SET $apr_seen(~%apr_scope% %apr_parameter1% %apr_mode%~) = 0
	END
	PHP_EACH fx_ids_1 AS _ => apr_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			LPM ad_op_1_value
			SET apr_timing = $fx_timing(~%apr_id%~)
			// L'ancien moteur écarte un mode inconnu, un effet sans changement, un ajout hors de la table
			// et une valeur finale d'une durée limitée (sans effet dans le jeu) ; il accepte le mode 4,
			// sans texte.
			PATCH_IF apr_mode < MOD_TYPE_cumulative OR apr_mode > 3
					OR (apr_mode == MOD_TYPE_cumulative AND (apr_parameter1 == 0 OR apr_value > 10))
					OR (apr_mode == MOD_TYPE_percentage AND apr_parameter1 == 100)
					OR (apr_mode == 3 AND (apr_timing == TIMING_duration OR apr_timing == TIMING_delayed_duration OR apr_timing == 6
						OR apr_timing == TIMING_permanent_after_death OR apr_timing == TIMING_duration_ticks)) BEGIN
				LPF ad_refusal INT_VAR fx_id = apr_id STR_VAR reason = ~file_error:opcode1:invalid~ message = ~invalid or ineffective number of attacks (mode %apr_mode%, value %apr_value%)~ RET render_missing = refusal END
			END
			// Une demi-attaque retirée : l'ancien moteur écrit « -5 » (BUG-021).
			ELSE PATCH_IF apr_mode == MOD_TYPE_cumulative AND apr_parameter1 < 0 AND apr_value == 6 BEGIN
				LPF ad_refusal INT_VAR fx_id = apr_id STR_VAR reason = ~not_implemented:opcode1:half_removed~ message = ~half attack removed (BUG-021)~ RET render_missing = refusal END
			END
			// L'ancien moteur fusionne deux effets identiques au lieu de les cumuler.
			ELSE PATCH_IF $apr_seen(~%apr_scope% %apr_parameter1% %apr_mode%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = apr_id STR_VAR reason = ~not_implemented:opcode1:same_effect_twice~ message = ~same effect twice (the old engine merges them)~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET $apr_seen(~%apr_scope% %apr_parameter1% %apr_mode%~) = 1
			END
		END
	END
END

// ---------------------------------------------------------------------------------------------
// Lignes (ancien opcode_self_1 et opcode_1_common) : une par effet.

DEFINE_PATCH_MACRO ad_op_1_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~1~)
	SPRINT apr_half @20010001 // ~une demi~
	SPRINT apr_and_half @20010002 // ~\1 et demi~
	PHP_EACH fx_ids_1 AS _ => apr_id BEGIN
		PATCH_IF NOT $fx_consumed(~%apr_id%~) BEGIN
			LPM ad_op_1_value
			PATCH_IF apr_mode == MOD_TYPE_flat OR apr_mode == 3 BEGIN
				SET apr_value = apr_parameter1 < 0 ? 0 : (apr_value > 10 ? 10 : apr_value)
			END
			PATCH_IF apr_mode == MOD_TYPE_percentage BEGIN
				LPF ad_signed_value INT_VAR value = apr_parameter1 - 100 RET value = text END
				SPRINT value @1200003 // ~%value%%PERCENT%~
			END
			ELSE BEGIN
				SET value = $AD_ATTACKS_PER_ROUND(~%apr_value%~)
				PATCH_IF apr_mode == MOD_TYPE_cumulative BEGIN
					PATCH_IF apr_parameter1 < 0 BEGIN
						SET value = 0 - value
					END
					LPF ad_signed_value INT_VAR value RET value = text END
				END
				// Dixièmes vers texte, dans l'ordre de l'ancien moteur : 5 => une demi, 20 => 2,
				// 25 => 2 et demi.
				INNER_PATCH_SAVE value ~%value%~ BEGIN
					REPLACE_TEXTUALLY ~+5$~ ~+%apr_half%~
					REPLACE_TEXTUALLY ~^5$~ ~%apr_half%~
					REPLACE_TEXTUALLY ~\([0-9]\)+0$~ ~\1~
					REPLACE_TEXTUALLY ~\([0-9]\)+5$~ ~%apr_and_half%~
				END
			END
			PATCH_IF apr_parameter1 <= 0 AND (apr_mode == MOD_TYPE_flat OR apr_mode == MOD_TYPE_percentage OR apr_mode == 3) BEGIN
				SET line_phrase = 20010140 // ~Attaque impossible~
			END
			ELSE BEGIN
				PATCH_IF apr_mode == MOD_TYPE_flat BEGIN
					SPRINT value @1200002 // ~Passe à %value%~
				END
				ELSE PATCH_IF apr_mode == 3 BEGIN
					SPRINT value @1200006 // ~Fixée à %value%~
				END
				ELSE PATCH_IF apr_mode == MOD_TYPE_cumulative AND (~%value%~ STRING_EQUAL ~+%apr_half%~) BEGIN
					SPRINT value @20010003 // ~une demi supplémentaire~
				END
				SPRINT name @20010000 // ~Attaque par round~
				SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
			END
			SET line_fx = apr_id
			LPM ad_effect_line
		END
	END
END

// Écrit apr_parameter1, apr_mode (parameter2 ; 3 devient un ajout sur un jeu classique), apr_value
// (index de AD_ATTACKS_PER_ROUND : valeur absolue sur 16 bits) et apr_scope de l'effet apr_id.
DEFINE_PATCH_MACRO ad_op_1_value BEGIN
	SET apr_parameter1 = $fx_parameter1(~%apr_id%~)
	SET apr_mode = $fx_parameter2(~%apr_id%~)
	PATCH_IF apr_mode == 3 AND NOT IS_EE BEGIN
		SET apr_mode = MOD_TYPE_cumulative
	END
	SET apr_value = (ABS apr_parameter1) BAND 0xffff
	SPRINT apr_scope $fx_scope(~%apr_id%~)
END
