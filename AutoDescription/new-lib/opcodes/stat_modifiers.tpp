// Code commun de la famille des modificateurs simples d'une statistique (IESDP) : parameter1 =
// valeur, parameter2 = mode (0 ajoute la valeur, 1 fixe la statistique à la valeur, 2 la multiplie
// par valeur %). Un opcode de la famille a une entrée dans AD_STAT_MODIFIER_NAMES
// (new-lib/catalog.tpa) et son fichier new-lib/opcodes/<N>.tpp, dont les deux macros ad_op_<N>_*
// fixent stat_opcode et stat_mode_3 puis appellent les macros ci-dessous ; un opcode dont la
// statistique est un pourcentage (compétences de voleur…) est listé dans AD_STAT_MODIFIER_PERCENT ;
// un opcode sans mode
// pourcentage fixe aussi stat_percentage à invalid, remis à valid après la prise en charge ; un
// opcode dont le jeu ignore parameter2 fixe stat_forced_mode au mode qu'il applique réellement, écrit
// dans l'effet avant toute validation pour que les passes suivantes lisent le vrai mode. Un opcode
// pour qui un pourcentage de 100 a un sens fixe stat_percent_100 à valid. Un opcode aux cas
// particuliers fixe stat_line_macro : appelée pour chaque effet line_fx (forme dans line_form), elle
// peut changer le nom (stat_name_tra) ou écrire elle-même la ligne (stat_line_done à 1).
// Un opcode dont la statistique dépend d'un autre champ que la valeur et le mode (type de sort,
// compétence) l'écrit dans fx_stat_subject, pour que deux effets de statistiques différentes ne
// passent pas pour le même effet.
//
// Mode 3 (EE seulement ; sur un jeu classique, il est invalide pour tous les opcodes), selon
// stat_mode_3 : added (traité comme un ajout, ex. jets de sauvegarde), unsupported (pas encore
// décrit), invalid.
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp).

// ---------------------------------------------------------------------------------------------
// Prise en charge (ancien opcode_modstat2_is_valid / opcode_modstat3_is_valid)

DEFINE_PATCH_MACRO ad_stat_modifier_support BEGIN
	FOR (stat_id = 0; stat_id < fx_count; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == stat_opcode BEGIN
			PATCH_IF IS_AN_INT ~%stat_forced_mode%~ BEGIN
				SET $fx_parameter2(~%stat_id%~) = stat_forced_mode
			END
			SET stat_value = $fx_parameter1(~%stat_id%~)
			SET stat_mode = $fx_parameter2(~%stat_id%~)
			SPRINT stat_scope $fx_scope(~%stat_id%~)
			LPM ad_stat_modifier_subject
			SET stat_versus_file = $fx_versus_file(~%stat_id%~)
			SET stat_versus_value = $fx_versus_value(~%stat_id%~)
			SET stat_versus_inner_file = $fx_versus_inner_file(~%stat_id%~)
			SET stat_versus_inner_value = $fx_versus_inner_value(~%stat_id%~)
			SPRINT stat_versus ~%stat_versus_file% %stat_versus_value% %stat_versus_inner_file% %stat_versus_inner_value%~
			SET $stat_seen(~%stat_scope%~ ~%stat_value%~ ~%stat_mode%~ ~%stat_subject%~ ~%stat_versus%~) = 0
		END
	END
	FOR (stat_id = 0; stat_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == stat_opcode BEGIN
			SET stat_value = $fx_parameter1(~%stat_id%~)
			SET stat_mode = $fx_parameter2(~%stat_id%~)
			SPRINT stat_scope $fx_scope(~%stat_id%~)
			LPM ad_stat_modifier_subject
			SET stat_versus_file = $fx_versus_file(~%stat_id%~)
			SET stat_versus_value = $fx_versus_value(~%stat_id%~)
			SET stat_versus_inner_file = $fx_versus_inner_file(~%stat_id%~)
			SET stat_versus_inner_value = $fx_versus_inner_value(~%stat_id%~)
			SPRINT stat_versus ~%stat_versus_file% %stat_versus_value% %stat_versus_inner_file% %stat_versus_inner_value%~
			PATCH_IF stat_mode == 3 AND IS_EE AND (~%stat_mode_3%~ STRING_EQUAL ~unsupported~) BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode%stat_opcode%:mode3~ message = ~mode 3 not supported for this opcode~ RET render_missing = refusal END
			END
			// L'ancien moteur écarte un mode inconnu ou un effet sans changement (erreur journalisée) ;
			// en mode 3, une valeur nulle n'est pas écartée.
			ELSE PATCH_IF ((stat_mode < MOD_TYPE_cumulative OR stat_mode > MOD_TYPE_percentage)
					AND NOT (stat_mode == 3 AND IS_EE AND (~%stat_mode_3%~ STRING_EQUAL ~added~)))
					OR (stat_mode == MOD_TYPE_cumulative AND stat_value == 0)
					OR (stat_mode == MOD_TYPE_percentage AND ((stat_value == 100 AND NOT (~%stat_percent_100%~ STRING_EQUAL ~valid~))
					OR (~%stat_percentage%~ STRING_EQUAL ~invalid~))) BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~file_error:opcode%stat_opcode%:invalid~ message = ~invalid mode or no change (mode %stat_mode%, value %stat_value%)~ RET render_missing = refusal END
			END
			// L'ancien moteur fusionne deux effets identiques au lieu de les cumuler ; un effet d'un 177
			// contre un type de créature n'est pas identique à celui qui vaut pour tous.
			ELSE PATCH_IF $stat_seen(~%stat_scope%~ ~%stat_value%~ ~%stat_mode%~ ~%stat_subject%~ ~%stat_versus%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode%stat_opcode%:same_effect_twice~ message = ~same effect twice (the old engine merges them)~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET $stat_seen(~%stat_scope%~ ~%stat_value%~ ~%stat_mode%~ ~%stat_subject%~ ~%stat_versus%~) = 1
			END
		END
	END
	SPRINT stat_percentage ~valid~
	SPRINT stat_percent_100 ~~
	SPRINT stat_forced_mode ~~
END

DEFINE_PATCH_MACRO ad_stat_modifier_subject BEGIN
	SPRINT stat_subject ~~
	PATCH_IF VARIABLE_IS_SET $fx_stat_subject(~%stat_id%~) BEGIN
		SPRINT stat_subject $fx_stat_subject(~%stat_id%~)
	END
END

// ---------------------------------------------------------------------------------------------
// Lignes (ancien opcode_self_<N> et opcode_mod) : une par effet non consommé par un regroupement.

DEFINE_PATCH_MACRO ad_stat_modifier_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%stat_opcode%~)
	SET stat_base_name_tra = $AD_STAT_MODIFIER_NAMES(~%stat_opcode%~)
	SET stat_percent = VARIABLE_IS_SET $AD_STAT_MODIFIER_PERCENT(~%stat_opcode%~)
	FOR (stat_id = 0; stat_id < fx_count; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == stat_opcode AND NOT $fx_consumed(~%stat_id%~) BEGIN
			SET stat_value = $fx_parameter1(~%stat_id%~)
			SET stat_mode = $fx_parameter2(~%stat_id%~)
			SET stat_name_tra = stat_base_name_tra
			SET line_fx = stat_id
			LPM ad_application_form
			SET stat_line_done = 0
			PATCH_IF NOT (~%stat_line_macro%~ STRING_EQUAL ~~) BEGIN
				LPM ~%stat_line_macro%~
			END
			PATCH_IF NOT stat_line_done BEGIN
				LPF ad_tra INT_VAR tra_id = stat_name_tra RET name = text END
				PATCH_IF line_form == 0 BEGIN
					LPF ad_stat_modifier_value INT_VAR value = stat_value mode = stat_mode percent = stat_percent RET value = text END
					SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
				END
				ELSE BEGIN
					LPM ad_stat_modifier_target_phrase
				END
				LPM ad_effect_line
			END
		END
	END
	SPRINT stat_line_macro ~~
END

// Phrase à la forme « cible » de l'effet stat_id (ancien opcode_target) : line_phrase, identifiant de
// base d'une série de 1 210 1x0 selon le mode (10 augmentation, 20 réduction, 30 valeur fixée, 40
// multiplication), et ses variables value et theStatistic. La statistique (« la dextérité ») suit le
// nom : liste 8 060 000 + valeur de stats.ids pour un nom de la liste des statistiques, libellé
// 2OOO0002 pour un nom 2OOO0000 ; sans statistique dans le .tra, pas de phrase.
DEFINE_PATCH_MACRO ad_stat_modifier_target_phrase BEGIN
	SET stat_statistic_tra = stat_name_tra < 9000000 ? stat_name_tra + 60000 : stat_name_tra + 2
	SET line_phrase = 0
	PATCH_IF TRA_ENTRY_EXISTS (~%stat_statistic_tra%~) BEGIN
		LPF ad_tra INT_VAR tra_id = stat_statistic_tra RET theStatistic = text END
		SET value = ABS stat_value
		PATCH_IF stat_mode == MOD_TYPE_flat BEGIN
			SET line_phrase = 1210130
		END
		ELSE PATCH_IF stat_mode == MOD_TYPE_percentage BEGIN
			SET line_phrase = 1210140
		END
		ELSE PATCH_IF stat_value >= 0 BEGIN
			SET line_phrase = 1210110 // ~Augmente de %value% %theStatistic% %ofTheTarget%~ (+1)
		END
		ELSE BEGIN
			SET line_phrase = 1210120 // ~Réduit de %value% %theStatistic% %ofTheTarget%~ (+1)
		END
	END
END

// « +2 », « Passe à 18 » ou « -30 % » (mode 2 : valeur exprimée en pourcentage de la statistique).
// Statistique en pourcentage (percent = 1, ancien opcode_mod_percent_base) : « +20 % »,
// « Passe à 50 % », « Multiplié par 50 % ».
DEFINE_PATCH_FUNCTION ad_stat_modifier_value
	INT_VAR
		value = 0
		mode = 0
		percent = 0
	RET
		text
BEGIN
	// Le mode 3 n'arrive ici que s'il vaut un ajout (stat_mode_3 = added).
	PATCH_IF mode == MOD_TYPE_flat BEGIN
		SPRINT text @1200002 // ~Passe à %value%~
	END
	ELSE PATCH_IF mode == MOD_TYPE_percentage AND percent BEGIN
		SPRINT text @1200004 // ~Multiplié par %value%~
	END
	ELSE PATCH_IF mode == MOD_TYPE_percentage BEGIN
		LPF ad_signed_value INT_VAR value = value - 100 RET value = text END
		SPRINT text @1200003 // ~%value%%PERCENT%~
	END
	ELSE BEGIN
		LPF ad_signed_value INT_VAR value RET text END
	END
	PATCH_IF percent BEGIN
		SPRINT value ~%text%~
		SPRINT text @1200003 // ~%value%%PERCENT%~
	END
END
