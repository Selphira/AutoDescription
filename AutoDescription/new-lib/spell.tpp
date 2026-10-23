// Appelée sur le fichier .spl en cours de traitement ; même contrat que ad_describe_item. Seul
// l'en-tête est rendu (new-lib/spell_header.tpp) : sans section « PARAMÈTRES »
// (AD_ADD_STATISTICS_SECTION_TO_SPELL_DESCRIPTION = 0), les effets ne sont pas décrits et un opcode
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
	SPRINT description ~~
	SET covered = 0
	// Fixé dès la lecture des effets : le remplacement d'un 177 en dépend (ad_fx_substitute_177).
	SET support_header_only = NOT AD_ADD_STATISTICS_SECTION_TO_SPELL_DESCRIPTION
	SET group_spell_as_equipped = 1
	// Un sort n'a pas de type d'objet (prises en charge partagées avec les objets).
	SET item_type = 0 - 1
	// L'en-tête seul ne lit pas le bloc de lancement, comme l'ancien load_level_effects.
	SET fx_with_casting = AD_ADD_STATISTICS_SECTION_TO_SPELL_DESCRIPTION
	LPM ad_recursion_reset
	LPM ad_fx_load_spell
	PATCH_IF AD_EFFECTS_DUMP BEGIN
		LPM ad_fx_dump
	END
	LPM ad_set_coverage
	PATCH_IF ~%fx_load_error%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF AD_ADD_STATISTICS_SECTION_TO_SPELL_DESCRIPTION BEGIN
			LPF ad_refusal STR_VAR reason = ~not_implemented:spell:statistics~ message = ~statistics section of spell descriptions not supported yet~ RET uncovered_reason = refusal END
		END
		ELSE BEGIN
			LPM ad_spell_header_support
			PATCH_IF ~%header_missing%~ STRING_EQUAL ~~ BEGIN
				LPM ad_spell_header_render
			END
			SET covered = ~%header_missing%~ STRING_EQUAL ~~
			SPRINT uncovered_reason ~%header_missing%~
		END
	END
	PATCH_IF NOT covered BEGIN
		LPF ad_log_event STR_VAR event = ~%uncovered_reason%~ RET uncovered_reason = reason END
	END
END
