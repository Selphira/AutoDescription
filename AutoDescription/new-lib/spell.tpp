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
	SET resource_is_spell = 1
	// Un sort n'a pas de type d'objet (prises en charge partagées avec les objets).
	SET item_type = 0 - 1
	// Effets de lancement décrits à part (ancien add_casting_features), pas pour les sous-sorts.
	SET fx_with_casting = 1
	SPRINT description ~~
	SET covered = 0
	LPM ad_recursion_reset
	LPM ad_fx_load_spell
	PATCH_IF AD_EFFECTS_DUMP BEGIN
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
	PATCH_IF NOT covered BEGIN
		LPF ad_log_event STR_VAR event = ~%uncovered_reason%~ RET uncovered_reason = reason END
	END
END
