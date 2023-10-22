DEFINE_ACTION_MACRO ~update_item_descriptions~ BEGIN
	OUTER_SET totalItems = 0
	COPY_EXISTING_REGEXP GLOB ~^.+\.itm$~ ~override~
		LPM ~update_item_description~
	BUT_ONLY_IF_IT_CHANGES
END

DEFINE_PATCH_MACRO ~update_item_description~ BEGIN
	SET totalItems += 1
	PATCH_IF totalItems MODULO 100 == 0 BEGIN
		PATCH_PRINT "%totalItems% items processed"
	END
	PATCH_TRY
		LPF ~update_item_description~ RET totalIgnoredCursed totalIgnoredWithoutDescription totalIgnoredNotMoveable totalIgnoredType totalSuccessful END
	WITH DEFAULT
		LPF ~add_log_warning~ STR_VAR message = ~FAILURE: %ERROR_MESSAGE%~ END
		SET totalFailed += 1
	END
END

DEFINE_PATCH_FUNCTION ~update_item_description~
	RET
		totalIgnoredCursed
		totalIgnoredWithoutDescription
		totalIgnoredNotMoveable
		totalIgnoredType
		totalSuccessful
BEGIN
	PATCH_SILENT

	READ_SHORT  ITM_type            itemType
	READ_STRREF ITM_identified_desc originalDescription
	READ_LONG   ITM_identified_desc originalDescriptionRef
	READ_STRREF ITM_unidentified_desc originalUnidentifiedDescription
	READ_LONG   ITM_unidentified_desc originalUnidentifiedDescriptionRef
    READ_SHORT  ITM_flags           flags

	LPF ~can_update_item~
		INT_VAR itemType originalDescriptionRef flags originalUnidentifiedDescriptionRef
		STR_VAR originalDescription originalUnidentifiedDescription
		RET canUpdateItem totalIgnoredCursed totalIgnoredWithoutDescription totalIgnoredNotMoveable totalIgnoredType
	END

	PATCH_IF canUpdateItem BEGIN
		SPRINT CURRENT_SOURCE_RES ~%SOURCE_RES%~

		PATCH_IF ~%originalDescription%~ STRING_EQUAL ~~ OR originalDescriptionRef <= 0 BEGIN
			LPF ~get_item_description~ INT_VAR itemType flags STR_VAR originalDescription = ~%originalUnidentifiedDescription%~ RET description END
			// Si l'utilisateur a choisi d'enregistrer la description dans ses fichiers
			PATCH_IF alter_item_files BEGIN
				SAY UNIDENTIFIED_DESC ~%description%~
			END
			// Ecrire dans le fichier de comparaison
			READ_STRREF ITM_unidentified_name itemName
			LPF ~add_compare_row~ STR_VAR itemName originalDescription = ~%originalUnidentifiedDescription%~ description END
		END
		ELSE BEGIN
			LPF ~get_item_description~ INT_VAR itemType flags STR_VAR originalDescription RET description END
			// Si l'utilisateur a choisi d'enregistrer la description dans ses fichiers
			PATCH_IF alter_item_files BEGIN
				SAY DESC ~%description%~
			END
			// Ecrire dans le fichier de comparaison
			READ_STRREF ITM_identified_name itemName
			LPF ~add_compare_row~ STR_VAR itemName originalDescription description END
		END

		SET totalSuccessful += 1
	END
END


DEFINE_PATCH_FUNCTION ~get_item_description~
	INT_VAR
		itemType = 0
		flags = 0
	STR_VAR
		originalDescription = ~~
	RET
		description
BEGIN
	SET isItem = 1
	SET isSpell = 0

	PATCH_IF itemType == ITM_TYPE_potion BEGIN
		SPRINT theSource   @102451 // ~le buveur~
		SPRINT ofTheSource @102452 // ~du buveur~
		SPRINT toTheSource @102453 // ~au buveur~
	END
	ELSE BEGIN
		SPRINT theSource   @102472 // ~le porteur~
		SPRINT ofTheSource @101086 // ~du porteur~
		SPRINT toTheSource @101180 // ~au porteur~
	END

	// On supprime la description technique de la description originale
	LPF ~removeTechnicalDescription~ STR_VAR description = EVAL ~%originalDescription%~ RET description END
	LPF ~is_weapon~ INT_VAR itemType RET isWeapon END
	LPF ~is_armor~ INT_VAR itemType RET isArmor END
	LPF ~is_robe~ INT_VAR itemType RET isRobe END
	LPF ~is_ammo~ INT_VAR itemType RET isAmmo END

	LPF ~add_equipped_abilities~ STR_VAR description RET description countGlobalLines RET_ARRAY globalLines END
	LPF ~add_charged_abilities~ STR_VAR description RET description END
	LPF ~add_combat_abilities~ STR_VAR description RET description END

	PATCH_IF isArmor == 1 BEGIN
		LPF ~add_global_effects_to_description~ RET description END
	END
	ELSE PATCH_IF isWeapon == 1 BEGIN
		LPF ~proficiency~ RET description END
	END

	LPF ~needs~              RET description END
	LPF ~appendLine~         RET description END
	PATCH_IF itemType == ITM_TYPE_potion OR itemType == ITM_TYPE_dart BEGIN
		LPF ~uses~ RET description END
	END
	LPF ~weight~             RET description END
	LPF ~usability~          RET description END

	INNER_PATCH_SAVE description ~%description%~ BEGIN
		// Supprime les lignes vides consécutives
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~\(%crlf%%crlf%%crlf%\)+~ ~%crlf%%crlf%~
	END
END

DEFINE_PATCH_FUNCTION ~is_weapon~
	INT_VAR
		itemType = 0
	RET
		isWeapon
BEGIN
	SET isWeapon = 0
	PATCH_IF itemType > 0xe AND itemType < 0x1f BEGIN
		SET isWeapon = 1
	END
END

DEFINE_PATCH_FUNCTION ~is_armor~
	INT_VAR
		itemType = 0
	RET
		isArmor
BEGIN
	SET isArmor = 0
	PATCH_IF itemType == ITM_TYPE_armor BEGIN
		SET isArmor = 1
	END
END

DEFINE_PATCH_FUNCTION ~is_robe~
	INT_VAR
		itemType = 0
	RET
		isRobe
BEGIN
	READ_ASCII ITM_animation animation (2)
	SET isRobe = 0
	PATCH_IF ~%animation%~ STRING_EQUAL ~2W~ OR ~%animation%~ STRING_EQUAL ~3W~ OR ~%animation%~ STRING_EQUAL ~4W~ BEGIN
		SET isRobe = 1
	END
END

DEFINE_PATCH_FUNCTION ~is_ammo~
	INT_VAR
		itemType = 0
	RET
		isAmmo
BEGIN
	SET isAmmo = 0
	PATCH_IF itemType == ITM_TYPE_arrows OR itemType == ITM_TYPE_bullets OR itemType == ITM_TYPE_bolts BEGIN
		SET isAmmo = 1
	END
END

DEFINE_PATCH_FUNCTION ~can_update_item~
	INT_VAR
		itemType = 0
		originalDescriptionRef = 0
		originalUnidentifiedDescriptionRef = 0
		flags = 0
	STR_VAR
		originalDescription = ~~
		originalUnidentifiedDescription = ~~
	RET
		canUpdateItem
		totalIgnoredCursed
		totalIgnoredWithoutDescription
		totalIgnoredNotMoveable
		totalIgnoredType
BEGIN
	SET canUpdateItem = 1

	// Evite un crash sur les objets vides
	PATCH_IF SOURCE_SIZE <= 0x71 BEGIN
		SET canUpdateItem = 0
		LPF ~add_log_error~ STR_VAR message = ~Invalid file.~ END
	END
	// Si l'utilisateur ne veut pas modifier la description des objets maudits
	ELSE PATCH_IF NOT include_cursed_items AND (flags BAND BIT4) == BIT4 BEGIN
		SET totalIgnoredCursed += 1
		SET canUpdateItem = 0
	END
	// Si l'utilisateur ne veut pas inclure les objets sans description
	ELSE PATCH_IF NOT include_items_without_description AND (~%originalDescription%~ STRING_EQUAL ~~ OR originalDescriptionRef <= 0) AND (~%originalUnidentifiedDescription%~ STRING_EQUAL ~~ OR originalUnidentifiedDescriptionRef <= 0) BEGIN
		SET totalIgnoredWithoutDescription += 1
		SET canUpdateItem = 0
	END
	// Si l'utilisateur ne veut pas inclure les objets qui ne peuvent être déplacés (Ils ne sont pas accessibles au joueur)
	ELSE PATCH_IF NOT include_non_moveable_items AND (flags BAND BIT2) == 0 BEGIN
		SET totalIgnoredNotMoveable += 1
		SET canUpdateItem = 0
	END
    ELSE BEGIN
		PATCH_MATCH itemType
		WITH
			// Les armes
			ITM_TYPE_bow ITM_TYPE_dagger ITM_TYPE_mace ITM_TYPE_sling ITM_TYPE_small_sword ITM_TYPE_large_sword
			ITM_TYPE_hammer ITM_TYPE_morning_star ITM_TYPE_flail ITM_TYPE_dart ITM_TYPE_axe ITM_TYPE_quarterstaff
			ITM_TYPE_crossbow ITM_TYPE_hand_to_hand_hth ITM_TYPE_spear ITM_TYPE_halberd ITM_TYPE_polearm
			// Les autres objets équipables
			ITM_TYPE_armor ITM_TYPE_shield_not_in_iwd ITM_TYPE_necklace ITM_TYPE_amulet ITM_TYPE_belt ITM_TYPE_girdle
			ITM_TYPE_boots ITM_TYPE_bracers ITM_TYPE_gauntlets ITM_TYPE_helm ITM_TYPE_ring ITM_TYPE_cloak
			// Les consommables
			ITM_TYPE_potion //ITM_TYPE_wand ITM_TYPE_scroll
			// Les munitions
			ITM_TYPE_arrows ITM_TYPE_bullets ITM_TYPE_bolts
			BEGIN
				SET canUpdateItem = 1
			END
			DEFAULT
				SET totalIgnoredType += 1
				SET canUpdateItem = 0
		END
    END
END

DEFINE_ACTION_MACRO ~init_item_statistics~ BEGIN
	OUTER_SET total = 0
	OUTER_SET totalFailed = 0
	OUTER_SET totalSuccessful = 0
	OUTER_SET totalIgnored = 0
	OUTER_SET totalIgnoredCursed = 0
	OUTER_SET totalIgnoredWithoutDescription = 0
	OUTER_SET totalIgnoredNotMoveable = 0
	OUTER_SET totalIgnoredType = 0
	OUTER_SET opcodeTodo = 0
END

DEFINE_ACTION_MACRO ~show_item_statistics~ BEGIN
	ACTION_PHP_EACH ignored_opcodes AS opcode => value BEGIN
		ACTION_IF value == 1 BEGIN
			OUTER_SET opcodeTodo += 1
		END
	END

	OUTER_SET totalIgnored = totalIgnoredCursed + totalIgnoredWithoutDescription + totalIgnoredNotMoveable + totalIgnoredType
	OUTER_SET total = totalIgnored + totalSuccessful + totalFailed

	PRINT "Reussis : %totalSuccessful%
Echoues : %totalFailed%
Ignores : %totalIgnored%
   Maudits : %totalIgnoredCursed%
   Sans description : %totalIgnoredWithoutDescription%
   Non deplacables : %totalIgnoredNotMoveable%
   Type non gere : %totalIgnoredType%

Total : %total%

Opcodes a coder : %opcodeTodo%"
END