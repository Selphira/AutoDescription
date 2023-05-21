DEFINE_ACTION_MACRO ~update_spell_descriptions~ BEGIN
	OUTER_SET totalSpells = 0
	COPY_EXISTING_REGEXP GLOB ~^.+\.spl$~ ~override~
		LPM ~update_spell_description~
	BUT_ONLY_IF_IT_CHANGES
END

DEFINE_PATCH_MACRO ~update_spell_description~ BEGIN
	PATCH_TRY
		PATCH_PRINT "Traitement de %SOURCE_FILE%..."
		LPF ~update_spell_description~ RET totalIgnoredWithoutName totalIgnoredWithoutDescription totalInvalid totalSuccessful END
	WITH DEFAULT
		LPF ~add_log_warning~ STR_VAR message = ~FAILURE: %ERROR_MESSAGE%~ END
		SET totalFailed += 1
	END
END

DEFINE_PATCH_FUNCTION ~update_spell_description~
	RET
		totalIgnoredWithoutName
		totalIgnoredWithoutDescription
		totalInvalid
		totalSuccessful
BEGIN
	PATCH_SILENT

	READ_STRREF SPL_unidentified_name spellName
	READ_LONG   SPL_unidentified_name spellNameRef
	READ_STRREF SPL_unidentified_description originalDescription
	READ_LONG   SPL_unidentified_description originalDescriptionRef

	LPF ~can_update_spell~
		INT_VAR originalDescriptionRef spellNameRef
		STR_VAR originalDescription spellName
		RET canUpdateSpell totalIgnoredWithoutName totalIgnoredWithoutDescription totalInvalid
	END

	PATCH_IF canUpdateSpell BEGIN
		LPF ~get_spell_description~ STR_VAR originalDescription spellName RET description END

		// Si l'utilisateur a choisi d'enregistrer la description des sorts dans ses fichiers
		PATCH_IF alter_spell_files BEGIN
			SAY SPL_unidentified_description ~%description%~
		END

		// Ecrire dans le fichier de comparaison
		LPF ~add_compare_row~ STR_VAR itemName = ~%spellName%~ originalDescription description END

		SET totalSuccessful += 1
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_description~
	STR_VAR
		originalDescription = ~~
		spellName = ~~
	RET
		description
BEGIN
	READ_LONG  SPL_extended_headers_offset headerOffset
	READ_SHORT SPL_extended_headers_count  headerCount

	// On récupère la description roleplay de la description originale
	LPF ~get_spell_roleplay_description~ STR_VAR description = ~%originalDescription%~ RET roleplayDescription = description END

	SET ignoreDuration = 0

	SPRINT parameters @100003  // ~PARAMÈTRES~
	SPRINT description ~%spellName%%crlf%~

	LPF ~spell_school~ RET description END
	LPF ~spell_level~ RET description END
	LPF ~spell_range~ RET description END
	LPF ~spell_duration~ RET description ignoreDuration END
	LPF ~spell_casting_time~ RET description END
	LPF ~spell_target~ RET description END
	LPF ~spell_saving_throw~ RET description END

	SPRINT description ~%description%%crlf%%crlf%%roleplayDescription%~

	LPF ~appendSection~ STR_VAR string = ~%parameters%~ RET description END

	LPF ~add_casting_features~ STR_VAR description RET description END
	LPF ~add_extended_effects~ STR_VAR description RET description END
END

DEFINE_PATCH_FUNCTION ~can_update_spell~
	INT_VAR
		originalDescriptionRef = 0
		spellNameRef = 0
	STR_VAR
		originalDescription = ~~
		spellName = ~~
	RET
		canUpdateSpell
		totalIgnoredWithoutName
		totalIgnoredWithoutDescription
		totalInvalid
BEGIN
	SET canUpdateSpell = 1

	// Evite un crash sur les sorts vides
	PATCH_IF SOURCE_SIZE <= 0x71 BEGIN
		SET canUpdateSpell = 0
		LPF ~add_log_error~ STR_VAR message = ~Invalid file.~ END
	END
	// Si l'utilisateur ne veut pas inclure les sorts sans description
	ELSE PATCH_IF NOT include_spells_without_description AND (~%originalDescription%~ STRING_EQUAL ~~ OR originalDescriptionRef <= 0) BEGIN
		SET totalIgnoredWithoutDescription += 1
		SET canUpdateSpell = 0
	END
	// Si l'utilisateur ne veut pas inclure les sorts sans nom
	ELSE PATCH_IF NOT include_spells_without_name AND (~%spellName%~ STRING_EQUAL ~~ OR spellNameRef <= 0) BEGIN
		SET totalIgnoredWithoutName += 1
		SET canUpdateSpell = 0
	END
	ELSE PATCH_IF NOT ~%originalDescription%~ STRING_MATCHES_REGEXP ~<Invalid Strref -?[0-9]+>~ OR NOT ~%spellName%~ STRING_MATCHES_REGEXP ~<Invalid Strref -?[0-9]+>~ BEGIN
		SET totalInvalid += 1
		SET canUpdateSpell = 0
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_roleplay_description~ STR_VAR description = "" RET description BEGIN
	// Suppression des lignes techniques
	INNER_PATCH ~%description%~ BEGIN
		SPRINT regex ~\(.*\)Jet de sauvegarde\(.*[%MNL%%LNL%%WNL%]*\)*~
		SPRINT replace ~~
		REPLACE_EVALUATE CASE_INSENSITIVE ~%regex%~ BEGIN
			SPRINT description ~%MATCH0%~
		END ~%replace%~
	END

	INNER_PATCH ~%description%~ BEGIN
		SPRINT regex ~\(Jet de sauvegarde[^%crlf%]+\)+\(.*[%MNL%%LNL%%WNL%]*\)*~
		SPRINT find ~~
		SPRINT replace ~~
		REPLACE_EVALUATE CASE_INSENSITIVE ~%regex%~ BEGIN
			SPRINT find ~%MATCH1%%crlf%%crlf%~
		END ~~
		INNER_PATCH_SAVE description ~%description%~ BEGIN
			REPLACE_TEXTUALLY ~%find%~ ~~
		END
	END
END

DEFINE_ACTION_MACRO ~init_spell_statistics~ BEGIN
	OUTER_SET total = 0
	OUTER_SET totalFailed = 0
	OUTER_SET totalSuccessful = 0
	OUTER_SET totalIgnored = 0
	OUTER_SET totalIgnoredWithoutName = 0
	OUTER_SET totalIgnoredWithoutDescription = 0
	OUTER_SET totalInvalid = 0
	OUTER_SET opcodeTodo = 0
END

DEFINE_ACTION_MACRO ~show_spell_statistics~ BEGIN
	ACTION_PHP_EACH ignored_opcodes AS opcode => value BEGIN
		ACTION_IF value == 1 BEGIN
			OUTER_SET opcodeTodo += 1
		END
	END

	OUTER_SET totalIgnored = totalIgnoredWithoutName + totalIgnoredWithoutDescription + totalInvalid
	OUTER_SET total = totalIgnored + totalSuccessful + totalFailed

	PRINT "Reussis : %totalSuccessful%
Echoues : %totalFailed%
Ignores : %totalIgnored%
   Invalide : %totalInvalid%
   Sans description : %totalIgnoredWithoutDescription%
   Sans nom : %totalIgnoredWithoutName%

Total : %total%

Opcodes a coder : %opcodeTodo%"
END