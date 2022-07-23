DEFINE_PATCH_MACRO ~update_description~ BEGIN
	PATCH_IF (SOURCE_SIZE > 0x71) BEGIN // Evite un crash sur les objets vides
		READ_SHORT  ITM_type itemType
		READ_STRREF ITM_identified_desc description
		READ_LONG   ITM_identified_desc strref
        READ_SHORT  ITM_flags           flags
        READ_SHORT  ITM_enchantment     enchantment

		SET total += 1
        SET isWeapon = 0

        PATCH_SILENT

		PATCH_IF NOT include_items_without_description AND (~%description%~ STRING_EQUAL ~~ OR strref == ~-1~ OR strref == 0) BEGIN
			SET totalWithoutDescription += 1
			SET totalIgnored += 1
		END
		ELSE BEGIN
	        SPRINT oldDescription "%description%"

			LPF ~removeTechnicalDescription~ STR_VAR description RET description END

			// Si l'objet ne peut être déplacé, il n'est pas accessible au joueur
			PATCH_IF NOT include_non_moveable_items AND (flags BAND BIT2) == 0 BEGIN
				SET totalIgnored += 1
			END
			ELSE BEGIN
				PATCH_TRY
				    PATCH_IF itemType > 0xe AND itemType < 0x1f BEGIN // Les armes
				        SET isWeapon = 1
						LPM ~description~
						SET totalSuccessful += 1
						LPM ~log~
				    END
				    ELSE BEGIN
						PATCH_MATCH itemType
						WITH
							// Description de l'équipement
							ITM_TYPE_armor ITM_TYPE_shield_not_in_iwd ITM_TYPE_necklace ITM_TYPE_amulet ITM_TYPE_belt ITM_TYPE_girdle ITM_TYPE_boots ITM_TYPE_bracers ITM_TYPE_gauntlets ITM_TYPE_helm ITM_TYPE_ring ITM_TYPE_cloak
							BEGIN
								LPM ~description~
								SET totalSuccessful += 1
								LPM ~log~
							END
							// Description des consommables
							ITM_TYPE_potion ITM_TYPE_wand ITM_TYPE_scroll
							BEGIN
								// LPM ~description_potion~
								SET totalPotion += 1
								SET totalIgnored += 1
							END
							// Description des munitions
							ITM_TYPE_arrows ITM_TYPE_bullets ITM_TYPE_bolts
							BEGIN
								// LPM ~description_ammo~
								SET totalAmmo += 1
								SET totalIgnored += 1
							END
							DEFAULT
								SET totalIgnored += 1
						END
				    END
				WITH DEFAULT
					PATCH_WARN ~%SOURCE_FILE% : %ERROR_MESSAGE%~
					SET totalFailed += 1
				END
			END
		END
	END
	ELSE BEGIN
		LPF ~log_warning~ STR_VAR message = ~Fichier invalide.~ END
	END
END

DEFINE_PATCH_MACRO ~description_ammo~ BEGIN
	PATCH_PRINT "----------- MUNITION : %SOURCE_FILE% -----------"
END

DEFINE_PATCH_MACRO ~description_potion~ BEGIN
	PATCH_PRINT "----------- POTION : %SOURCE_FILE% -----------"
	READ_STRREF ITM_identified_desc description

	// TODO: Supprimer le texte non roleplay si présent (pas toujours de "PARAMETRES" ici..)

	LPF ~usability~ RET description END
END

DEFINE_PATCH_MACRO ~description~ BEGIN
	LPF ~equipped_abilities~ RET description END
	LPF ~extended_abilities~ RET description END

	PATCH_IF isWeapon == 1 BEGIN
		LPF ~proficiency~   RET description END
	END

	LPF ~appendLine~         RET description END
	LPF ~weight~             RET description END
	LPF ~needs~              RET description END
	LPF ~usability~          RET description END

	INNER_PATCH_SAVE description ~%description%~ BEGIN
		// Supprime les lignes vides consécutives
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~\(%crlf%%crlf%%crlf%\)+~ ~%crlf%%crlf%~
	END

	PATCH_IF alter_item_files BEGIN
		SAY DESC ~%description%~
	END
END

DEFINE_PATCH_FUNCTION ~append~ INT_VAR strref = 0 STR_VAR string = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT string (AT %strref%)
	END
    SPRINT description "%description%%crlf%%string%"
END

DEFINE_PATCH_FUNCTION ~removeTechnicalDescription~ STR_VAR description = "" RET description BEGIN
	// On ne garde que le texte roleplay
	INNER_PATCH_SAVE description ~%description%~ BEGIN
		SPRINT regex @10008     // ~^[ %TAB%]*\(CARACTÉRISTIQUES\|STATISTIQUES\|PARAMETRES\|PARAMÈTRES\)+\(.*[%MNL%%LNL%%WNL%]*\)*~
		SPRINT replace @100003  // ~PARAMÈTRES~
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~%regex%~ ~%replace%%colon%%crlf%~
	END
END

DEFINE_PATCH_FUNCTION ~appendLine~ INT_VAR strref = 0 STR_VAR string = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT string (AT %strref%)
	END
    SPRINT description "%description%%crlf%%string%"
END

DEFINE_PATCH_FUNCTION ~appendSection~ INT_VAR strref = 0 STR_VAR string = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT string (AT %strref%)
	END
    SPRINT description "%description%%crlf%%crlf%%string%%colon%"
END

DEFINE_PATCH_FUNCTION ~appendValue~ INT_VAR strref = 0 STR_VAR name = "" value = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT name (AT %strref%)
	END
	SPRINT string @100001 // %name% : %value%
    SPRINT description "%description%%crlf%%string%"
END

DEFINE_PATCH_FUNCTION ~appendProperty~ INT_VAR strref = 0 STR_VAR name = "" value = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT name (AT %strref%)
	END

	PATCH_IF NOT "%value%" STRING_EQUAL "" BEGIN
		SPRINT name @100001 // %name% : %value%
	END
    SPRINT description "%description%%crlf%- %name%"
END

DEFINE_PATCH_FUNCTION ~appendSubProperty~ INT_VAR strref = 0 STR_VAR name = "" value = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT name (AT %strref%)
	END

	PATCH_IF NOT "%value%" STRING_EQUAL "" BEGIN
		SPRINT name @100001 // %name% : %value%
	END
    SPRINT description "%description%%crlf%  %name%"
END

DEFINE_PATCH_FUNCTION ~signed_value~ INT_VAR value = 0 RET value BEGIN
	PATCH_IF value > 0 BEGIN
		SPRINT value @10003
	END
END

DEFINE_PATCH_FUNCTION ~percent_value~ INT_VAR value = 0 RET value BEGIN
	PATCH_IF value > 0 BEGIN
		SPRINT value @10002 // ~%value% %~
	END
END