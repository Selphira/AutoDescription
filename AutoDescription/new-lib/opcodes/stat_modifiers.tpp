// Code commun de la famille des modificateurs simples d'une statistique (IESDP) : parameter1 =
// valeur, parameter2 = mode (0 ajoute la valeur, 1 fixe la statistique à la valeur, 2 la multiplie
// par valeur %). Un opcode de la famille a une entrée dans AD_STAT_MODIFIER_NAMES
// (new-lib/catalog.tpa) et son fichier new-lib/opcodes/<N>.tpp, dont les deux macros ad_op_<N>_*
// fixent stat_opcode et stat_mode_3 puis appellent les macros ci-dessous ; un opcode dont la
// statistique est un pourcentage (compétences de voleur…) est listé dans AD_STAT_MODIFIER_PERCENT ;
// un opcode sans mode
// pourcentage fixe aussi stat_percentage à invalid, remis à valid après la prise en charge ; un
// opcode dont le jeu ignore parameter2 fixe stat_forced_mode au mode qu'il applique réellement, écrit
// dans l'effet avant toute validation pour que les passes suivantes lisent le vrai mode.
//
// Mode 3 (EE seulement ; sur un jeu classique, il est invalide pour tous les opcodes), selon
// stat_mode_3 : added (traité comme un ajout, ex. jets de sauvegarde), unsupported (pas encore
// décrit), invalid.
//
// Pris en charge : effets d'équipement certains, actifs tant que l'objet est équipé.

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
			SET $stat_seen(~%stat_value%~ ~%stat_mode%~) = 0
		END
	END
	FOR (stat_id = 0; stat_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == stat_opcode BEGIN
			SPRINT stat_block $fx_block(~%stat_id%~)
			SPRINT stat_timing_kind $fx_timing_kind(~%stat_id%~)
			SET stat_value = $fx_parameter1(~%stat_id%~)
			SET stat_mode = $fx_parameter2(~%stat_id%~)
			PATCH_IF NOT (~%stat_block%~ STRING_EQUAL ~equipped~) OR NOT (~%stat_timing_kind%~ STRING_EQUAL ~while_equipped~)
					OR $fx_probability(~%stat_id%~) != 100 BEGIN
				SPRINT render_missing ~not_implemented:opcode%stat_opcode%:effect_kind~
			END
			ELSE PATCH_IF stat_mode == 3 AND IS_EE AND (~%stat_mode_3%~ STRING_EQUAL ~unsupported~) BEGIN
				SPRINT render_missing ~not_implemented:opcode%stat_opcode%:mode3~
			END
			// L'ancien moteur écarte un mode inconnu ou un effet sans changement (erreur journalisée) ;
			// en mode 3, une valeur nulle n'est pas écartée.
			ELSE PATCH_IF ((stat_mode < MOD_TYPE_cumulative OR stat_mode > MOD_TYPE_percentage)
					AND NOT (stat_mode == 3 AND IS_EE AND (~%stat_mode_3%~ STRING_EQUAL ~added~)))
					OR (stat_mode == MOD_TYPE_cumulative AND stat_value == 0)
					OR (stat_mode == MOD_TYPE_percentage AND (stat_value == 100 OR (~%stat_percentage%~ STRING_EQUAL ~invalid~))) BEGIN
				SPRINT render_missing ~not_implemented:opcode%stat_opcode%:invalid~
			END
			// L'ancien moteur fusionne deux effets identiques au lieu de les cumuler.
			ELSE PATCH_IF $stat_seen(~%stat_value%~ ~%stat_mode%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode%stat_opcode%:same_effect_twice~
			END
			ELSE BEGIN
				SET $stat_seen(~%stat_value%~ ~%stat_mode%~) = 1
			END
		END
	END
	SPRINT stat_percentage ~valid~
	SPRINT stat_forced_mode ~~
END

// ---------------------------------------------------------------------------------------------
// Lignes (ancien opcode_self_<N> et opcode_mod) : une par effet non consommé par un regroupement.

DEFINE_PATCH_MACRO ad_stat_modifier_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%stat_opcode%~)
	SET stat_name_tra = $AD_STAT_MODIFIER_NAMES(~%stat_opcode%~)
	SET stat_percent = VARIABLE_IS_SET $AD_STAT_MODIFIER_PERCENT(~%stat_opcode%~)
	LPF ad_tra INT_VAR tra_id = stat_name_tra RET name = text END
	FOR (stat_id = 0; stat_id < fx_count; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == stat_opcode AND NOT $fx_consumed(~%stat_id%~) BEGIN
			SET stat_value = $fx_parameter1(~%stat_id%~)
			SET stat_mode = $fx_parameter2(~%stat_id%~)
			LPF ad_stat_modifier_value INT_VAR value = stat_value mode = stat_mode percent = stat_percent RET value = text END
			SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
			LPM ad_line_add
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
