// Noms des ressources citées par les effets.

// Nom d'un sort : nom imposé par AD_SPELL_NAMES (new-lib/catalog.tpa ; vide : sort à ne pas citer),
// sinon nom non identifié du fichier ; vide si le sort n'existe pas ou n'a pas de nom.
DEFINE_PATCH_FUNCTION ad_spell_name
	STR_VAR
		resref = ~~
	RET
		name
BEGIN
	SPRINT name ~~
	SPRINT spell_key ~%resref%~
	TO_LOWER spell_key
	PATCH_IF VARIABLE_IS_SET $AD_SPELL_NAMES(~%spell_key%~) BEGIN
		SET spell_name_tra = $AD_SPELL_NAMES(~%spell_key%~)
		LPF ad_tra INT_VAR tra_id = spell_name_tra RET name = text END
	END
	ELSE PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
		INNER_PATCH_FILE ~%resref%.spl~ BEGIN
			READ_LONG SPL_unidentified_name spell_name_ref
			PATCH_IF spell_name_ref > 0 BEGIN
				READ_STRREF SPL_unidentified_name name
			END
		END
	END
END

// Zone du projectile projectile (index du champ d'un en-tête, 1 : aucun) d'un projectile de zone
// (.pro de type 3), comme l'ancien get_target_by_projectile : area_shape 1 rayon, 2 cône (0 sans
// zone, 0 - 1 fichier illisible) ; area_creatures 0 toutes, 1 hostiles, 2 drapeaux « hostiles » et
// « alliées » ensemble (bits 6 et 7) ; area_feet rayon en pieds ; area_angle arc du cône.
DEFINE_PATCH_FUNCTION ad_projectile_area
	INT_VAR
		projectile = 0
	RET
		area_shape
		area_creatures
		area_feet
		area_angle
BEGIN
	SET area_shape = 0
	SET area_creatures = 0
	SET area_feet = 0
	SET area_angle = 0
	PATCH_IF projectile > 1 BEGIN
		LOOKUP_IDS_SYMBOL_OF_INT area_file ~projectl~ (projectile - 1)
		PATCH_IF NOT IS_AN_INT area_file BEGIN
			PATCH_IF FILE_EXISTS_IN_GAME ~%area_file%.pro~ BEGIN
				INNER_PATCH_FILE ~%area_file%.pro~ BEGIN
					READ_SHORT 0x8 area_type
					PATCH_IF area_type == 3 AND BUFFER_LENGTH >= 0x226 BEGIN
						READ_LONG  0x200 area_flags
						READ_SHORT 0x206 area_size
						READ_SHORT 0x224 area_angle
						SET area_hostile = (area_flags BAND BIT6) != 0
						SET area_allied = (area_flags BAND BIT7) != 0
						SET area_creatures = area_hostile AND area_allied ? 2 : (area_hostile ? 1 : 0)
						// Conversion de l'ancien moteur en pieds : taille divisée par 17 (rayon d'une zone) ou
						// par 8,5 (cône).
						PATCH_IF (area_flags BAND BIT11) != 0 BEGIN
							SET area_feet = area_size * 10 / 85
							SET area_shape = area_angle == 0 ? 1 : 2
						END
						ELSE BEGIN
							SET area_feet = area_size / 17
							SET area_shape = 1
						END
					END
					ELSE PATCH_IF area_type == 3 BEGIN
						SET area_shape = 0 - 1
					END
				END
			END
		END
	END
END

// Objet resref (ancien get_item_name, item_can_stack) : nom identifié, sinon non identifié (vide si
// l'objet n'existe pas ou n'a pas de nom), strref du nom identifié, empilable (taille de pile
// supérieure à 1).
DEFINE_PATCH_FUNCTION ad_item_info
	STR_VAR
		resref = ~~
	RET
		name
		name_ref
		stackable
BEGIN
	SPRINT name ~~
	SET name_ref = 0
	SET stackable = 0
	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~%resref%.itm~ BEGIN
		INNER_PATCH_FILE ~%resref%.itm~ BEGIN
			READ_LONG ITM_identified_name name_ref
			READ_LONG ITM_unidentified_name item_unidentified_ref
			READ_BYTE ITM_stack_amount item_stack
			PATCH_IF name_ref > 0 BEGIN
				READ_STRREF ITM_identified_name name
			END
			ELSE PATCH_IF item_unidentified_ref > 0 BEGIN
				READ_STRREF ITM_unidentified_name name
			END
			SET stackable = item_stack > 1
		END
	END
END

// L'objet resref est un trésor aléatoire (RNDTRE01 à RNDTRE05, ou ligne de rndtres.2da), que le
// jeu remplace à sa création par un objet tiré au sort.
DEFINE_PATCH_FUNCTION ad_item_is_random_treasure
	STR_VAR
		resref = ~~
	RET
		random
BEGIN
	SPRINT random_key ~%resref%~
	TO_LOWER random_key
	SET random = (~%random_key%~ STRING_MATCHES_REGEXP ~^rndtre0[1-5]$~) == 0
	PATCH_IF NOT random AND FILE_EXISTS_IN_GAME ~rndtres.2da~ BEGIN
		INNER_PATCH_FILE ~rndtres.2da~ BEGIN
			COUNT_2DA_ROWS 2 random_rows
			FOR (random_row = 0; random_row < random_rows AND NOT random; ++random_row) BEGIN
				READ_2DA_ENTRY random_row 0 2 random_label
				TO_LOWER random_label
				SET random = ~%random_label%~ STRING_EQUAL ~%random_key%~
			END
		END
	END
END

// Créature resref (ancien get_creature_name, get_creature_allegiance) : nom (vide si la créature
// n'existe pas ou n'a pas de nom) et allégeance (ea.ids).
DEFINE_PATCH_FUNCTION ad_creature_info
	STR_VAR
		resref = ~~
	RET
		name
		allegiance
BEGIN
	SPRINT name ~~
	SET allegiance = 0
	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~%resref%.cre~ BEGIN
		INNER_PATCH_FILE ~%resref%.cre~ BEGIN
			READ_LONG CRE_name creature_name_ref
			READ_BYTE CRE_allegiance allegiance
			PATCH_IF creature_name_ref > 0 BEGIN
				READ_STRREF CRE_name name
			END
		END
	END
END
