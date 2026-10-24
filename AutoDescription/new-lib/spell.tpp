// Appelée sur le fichier .spl en cours de traitement ; même contrat que ad_describe_item. En-tête
// (new-lib/spell_header.tpp), puis, avec AD_ADD_STATISTICS_SECTION_TO_SPELL_DESCRIPTION, la section
// « PARAMÈTRES » (new-lib/spell_levels.tpp). Sans elle, les effets ne sont pas décrits et un opcode
// pas encore pris en charge n'empêche pas la couverture.
DEFINE_PATCH_FUNCTION ad_describe_spell
	STR_VAR
		original_description = ~~
		log_name = ~~
	RET
		description
		covered
		uncovered_reason
BEGIN
	// Fixé dès la lecture des effets : le remplacement d'un 177 en dépend (ad_fx_substitute_177).
	SET support_header_only = NOT AD_ADD_STATISTICS_SECTION_TO_SPELL_DESCRIPTION
	SET support_spell = 1
	SET source_is_spell = 1
	// Effets d'un en-tête de sort, rangés par l'ancien moteur dans leveled_opcodes, où un effet ajouté
	// par un regroupement écrase celui dont il a tous les champs (BUG-052).
	SET store_leveled = 1
	SET group_spell_as_equipped = 1
	// Un sort n'a pas de type d'objet (prises en charge partagées avec les objets).
	SET item_type = 0 - 1
	// Ni l'en-tête ni la section « PARAMÈTRES » de l'ancien moteur ne lisent le bloc de lancement
	// (load_level_effects ; add_casting_features est vide).
	SET fx_with_casting = 0
	// Les lignes taisent la durée et le jet de sauvegarde que l'en-tête écrit (ancien ignoreDuration et
	// ignoreSavingThrow, hérités par les sous-sorts). L'en-tête se lit après la chaîne des effets, dont
	// les regroupements et les sous-sorts écrivent déjà des lignes : il est supposé les écrire, et le
	// sort est décrit une seconde fois, sans journaux, s'il ne le fait pas.
	SET spell_hide_duration = 1
	SET spell_hide_save = 1
	SET log_muted = 0
	LPM ad_spell_describe
	PATCH_IF covered AND NOT support_header_only AND (header_hide_duration != spell_hide_duration OR header_hide_save != spell_hide_save) BEGIN
		SET spell_hide_duration = header_hide_duration
		SET spell_hide_save = header_hide_save
		SET log_muted = 1
		LPM ad_spell_describe
		SET log_muted = 0
	END
	PATCH_IF NOT covered BEGIN
		LPF ad_log_event STR_VAR event = ~%uncovered_reason%~ RET uncovered_reason = reason END
	END
END

// Une description du sort : description, covered, uncovered_reason.
DEFINE_PATCH_MACRO ad_spell_describe BEGIN
	SPRINT description ~~
	SET covered = 0
	LPM ad_recursion_reset
	SET ctx_ignore_duration = spell_hide_duration
	SET ctx_ignore_save = spell_hide_save
	LPM ad_fx_load_spell
	PATCH_IF AD_EFFECTS_DUMP AND NOT log_muted BEGIN
		LPM ad_fx_dump
	END
	LPM ad_set_coverage
	PATCH_IF ~%fx_load_error%~ STRING_EQUAL ~~ BEGIN
		SPRINT header_missing ~~
		PATCH_IF NOT support_header_only AND NOT (~%uncovered_reason%~ STRING_EQUAL ~not_implemented~) BEGIN
			SPRINT header_missing ~%uncovered_reason%~
		END
		ELSE BEGIN
			LPM ad_spell_header_support
		END
		PATCH_IF ~%header_missing%~ STRING_EQUAL ~~ BEGIN
			LPM ad_spell_header_render
		END
		PATCH_IF ~%header_missing%~ STRING_EQUAL ~~ AND NOT support_header_only BEGIN
			LPM ad_spell_statistics
		END
		// Le repère de l'en-tête redevient %theTarget% (ad_spell_header_render) : la valeur de
		// remplacement est évaluée deux fois (V41), theTarget doit donc valoir ce texte même.
		SPRINT target_percent ~%~
		SPRINT theTarget ~%target_percent%theTarget%target_percent%~
		INNER_PATCH_SAVE description ~%description%~ BEGIN
			REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~\(%CRLF%%CRLF%%CRLF%\)+~ ~%CRLF%%CRLF%~
			REPLACE_TEXTUALLY EXACT_MATCH ~AD_THE_TARGET_MARK~ ~%theTarget%~
		END
		SET covered = ~%header_missing%~ STRING_EQUAL ~~
		SPRINT uncovered_reason ~%header_missing%~
	END
END
