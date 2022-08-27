DEFINE_PATCH_FUNCTION ~update_item_description~
BEGIN
	READ_SHORT  ITM_type            itemType
	READ_STRREF ITM_identified_desc originalDescription
	READ_LONG   ITM_identified_desc originalDescriptionRef
    READ_SHORT  ITM_flags           flags

	LPF ~can_update_item~ INT_VAR itemType originalDescriptionRef flags STR_VAR originalDescription RET canUpdateItem END

	PATCH_IF canUpdateItem BEGIN
		LPF ~get_item_description~ INT_VAR itemType flags STR_VAR originalDescription RET description END

		// Si l'utilisateur a choisi d'enregistrer la description dans ses fichiers
		PATCH_IF alter_item_files BEGIN
			SAY DESC ~%description%~
		END

		// Ecrire dans le fichier de comparaison
		READ_STRREF ITM_identified_name itemName
		LPF ~add_compare_row~ STR_VAR itemName originalDescription description END
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
	// On supprime la description technique de la description originale
	LPF ~removeTechnicalDescription~ STR_VAR description = EVAL ~%originalDescription%~ RET description END
	LPF ~is_weapon~ INT_VAR itemType RET isWeapon END

	LPF ~add_equipped_abilities~ STR_VAR description RET description END
	LPF ~add_combat_abilities~ STR_VAR description RET description END
	LPF ~add_charged_abilities~ STR_VAR description RET description END

	PATCH_IF isWeapon == 1 BEGIN
		LPF ~add_weapon_attributes~ STR_VAR description RET description END
	END

	LPF ~appendLine~         RET description END
	LPF ~weight~             RET description END
	LPF ~needs~              RET description END
	LPF ~usability~          RET description END

	INNER_PATCH_SAVE description ~%description%~ BEGIN
		// Supprime les lignes vides consécutives
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~\(%crlf%%crlf%%crlf%\)+~ ~%crlf%%crlf%~
	END

	PATCH_PRINT "%description%"
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

DEFINE_PATCH_FUNCTION ~can_update_item~
	INT_VAR
		itemType = 0
		originalDescriptionRef = 0
		flags = 0
	STR_VAR
		originalDescription = ~~
	RET
		canUpdateItem
BEGIN
	SET canUpdateItem = 1

	// Evite un crash sur les objets vides
	PATCH_IF SOURCE_SIZE <= 0x71 BEGIN
		SET canUpdateItem = 0
		LPF ~add_log_error~ STR_VAR message = ~Fichier invalide.~ END
	END
	ELSE PATCH_IF
		 // Si l'utilisateur ne veut pas modifier la description des objets maudits
		(NOT include_cursed_items AND (flags BAND BIT4) == BIT4)
		// Si l'utilisateur ne veut pas inclure les objets sans description
		OR (NOT include_items_without_description AND (~%originalDescription%~ STRING_EQUAL ~~ OR originalDescriptionRef <= 0))
		// Si l'utilisateur ne veut pas inclure les objets qui ne peuvent être déplacés (Ils ne sont pas accessibles au joueur)
		OR (NOT include_non_moveable_items AND (flags BAND BIT2) == 0)
	BEGIN
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
			// ITM_TYPE_potion ITM_TYPE_wand ITM_TYPE_scroll
			// Les munitions
			// ITM_TYPE_arrows ITM_TYPE_bullets ITM_TYPE_bolts
			BEGIN
				SET canUpdateItem = 1
			END
			DEFAULT
				SET canUpdateItem = 0
		END
    END
END