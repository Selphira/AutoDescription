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
