DEFINE_ACTION_MACRO ~update_spell_descriptions~ BEGIN
	LAM ~load_clearair~
    ACTION_DEFINE_ARRAY allSpellDescriptions BEGIN END
	OUTER_SET totalSpells = 0
	COPY_EXISTING_REGEXP GLOB ~^.+\.spl$~ ~override~
		LPM ~update_spell_description~
	BUT_ONLY_IF_IT_CHANGES
	LAF ~write_js~ STR_VAR array = ~allSpellDescriptions~ END
END

DEFINE_PATCH_MACRO ~update_spell_description~ BEGIN
	SET totalSpells += 1
	PATCH_IF totalSpells MODULO 100 == 0 BEGIN
		PATCH_PRINT "%totalSpells% spells processed"
	END
	PATCH_TRY
		LPF ~update_spell_description~ RET totalIgnoredWithoutName totalIgnoredWithoutDescription totalInvalid totalSuccessful RET_ARRAY allSpellDescriptions END
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
	RET_ARRAY
	    allSpellDescriptions
BEGIN
	PATCH_SILENT

	READ_STRREF SPL_unidentified_name spellName
	READ_LONG   SPL_unidentified_name spellNameRef
	READ_LONG   SPL_level spellLevel
	READ_BYTE   SPL_school spellSchool
	READ_STRREF SPL_unidentified_description originalDescription
	READ_LONG   SPL_unidentified_description originalDescriptionRef

	LPF ~can_update_spell~
		INT_VAR originalDescriptionRef spellNameRef
		STR_VAR originalDescription spellName
		RET canUpdateSpell totalIgnoredWithoutName totalIgnoredWithoutDescription totalInvalid
	END

	PATCH_IF canUpdateSpell BEGIN
		SPRINT CURRENT_SOURCE_RES ~%SOURCE_RES%~

		LPF ~get_spell_description~ STR_VAR originalDescription spellName RET description END

		// Si l'utilisateur a choisi d'enregistrer la description des sorts dans ses fichiers
		PATCH_IF alter_spell_files BEGIN
			SAY SPL_unidentified_description ~%description%~
		END

		LPF ~add_compare_row~ STR_VAR itemName = ~%spellName%~ originalDescription description END
        SET $allSpellDescriptions(~%SOURCE_RES%~ ~%spellName%~ ~%originalDescription%~ ~%description%~ ~%spellSchool%~ ~%spellLevel%~) = 1
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
	SET isItem = 0
	SET isSpell = 1
	SET isSubSpell = 0
	SET isWeapon = 0
	SET isArmor = 0
	SET isRobe = 0
	SET isAmmo = 0

	SPRINT theSource   @102475 // ~le lanceur~
	SPRINT ofTheSource @102476 // ~du lanceur~
	SPRINT toTheSource @102477 // ~au lanceur~

	LPM ~load_level_effects~

	READ_LONG  SPL_extended_headers_offset headerOffset
	READ_SHORT SPL_extended_headers_count  headerCount

	// On récupère la description roleplay de la description originale
	LPF ~get_spell_roleplay_description~ STR_VAR description = ~%originalDescription%~ RET roleplayDescription = description END

	SET ignoreDuration = 0
	SET ignoreSavingThrow = 0

	SPRINT description ~%spellName%~

	LPF ~spell_school~ RET description END
	LPF ~appendLine~ RET description END // ~École~
	LPF ~spell_level~ RET description END
	LPF ~spell_range~ RET description END
	LPF ~spell_duration~ RET description ignoreDuration isSpecialDuration = is_special hasDuration = has_duration END
	LPF ~spell_casting_time~ RET description END
	LPF ~spell_target~ RET description END
	LPF ~spell_saving_throw~ RET description ignoreSavingThrow END
	LPF ~spell_resistance~ RET description END

	SPRINT description ~%description%%crlf%%crlf%%roleplayDescription%~

	LPF ~spell_dispellable_by_clearair~ RET description END

	PATCH_IF add_statistics_section_to_spell_description BEGIN
		LPF ~appendSection~ INT_VAR strref = 100003 RET description END // ~PARAMÈTRES~
        LPF ~appendLine~ RET description END

		LPF ~add_casting_features~ STR_VAR description RET description END
		LPF ~get_spell_effects_description~ INT_VAR ignoreDuration STR_VAR description RET description END
	END

	INNER_PATCH_SAVE description ~%description%~ BEGIN
		// Supprime les lignes vides consécutives
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~\(%crlf%%crlf%%crlf%\)+~ ~%crlf%%crlf%~
	END
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
	SPRINT saving_throw @100036 // ~Jet de sauvegarde~

	// Suppression des lignes techniques
	INNER_PATCH ~%description%~ BEGIN
		SPRINT regex ~\(.*\)%saving_throw%\(.*[%MNL%%LNL%%WNL%]*\)*~
		SPRINT replace ~~
		REPLACE_EVALUATE CASE_INSENSITIVE ~%regex%~ BEGIN
			SPRINT description ~%MATCH0%~
		END ~%replace%~
	END

	INNER_PATCH ~%description%~ BEGIN
		SPRINT regex ~^\(%saving_throw%[^%crlf%]+\)+\(.*[%MNL%%LNL%%WNL%]*\)*~
		SPRINT find ~~
		SPRINT replace ~~
		REPLACE_EVALUATE CASE_INSENSITIVE ~%regex%~ BEGIN
			SPRINT find ~%MATCH1%~
		END ~~
		PATCH_IF NOT ~%find%~ STRING_EQUAL ~~ BEGIN
			INNER_PATCH_SAVE description ~%description%~ BEGIN
				REPLACE_TEXTUALLY ~%find%%crlf%%crlf%~ ~~
				REPLACE_TEXTUALLY ~%find%%crlf%~ ~~
			END
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

DEFINE_ACTION_MACRO ~load_clearair~ BEGIN
    COPY_EXISTING ~clearair.2da~ ~override~
        COUNT_2DA_ROWS ~2~ ~rows~
        CLEAR_ARRAY ~clearair_projectiles~
        FOR ( row = 1 ; row < rows ; row = row + 1 ) BEGIN
            READ_2DA_ENTRY row 1 2 projectileId
            PATCH_IF IS_AN_INT projectileId BEGIN
                SET $clearair_projectiles(~%projectileId%~) = projectileId
            END
        END
    BUT_ONLY_IF_IT_CHANGES
END