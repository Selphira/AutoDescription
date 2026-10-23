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
// « alliées » ensemble (bits 6 et 7) ; area_feet rayon en pieds ; area_angle arc du cône ; area_cone
// forme de cône (bit 11, rayon s'il n'a pas d'arc) ; area_ignore_target : le projectile ne touche pas
// sa cible (bit 4 des drapeaux d'étincelles) ; area_size, area_delay, area_triggers : taille de la
// zone, délai entre deux explosions (100 par round) et nombre d'explosions lus dans le fichier ;
// area_file_missing : projectl.ids nomme un fichier .pro absent.
DEFINE_PATCH_FUNCTION ad_projectile_area
	INT_VAR
		projectile = 0
	RET
		area_shape
		area_creatures
		area_feet
		area_angle
		area_cone
		area_ignore_target
		area_size
		area_delay
		area_triggers
		area_file_missing
BEGIN
	SET area_shape = 0
	SET area_creatures = 0
	SET area_feet = 0
	SET area_angle = 0
	SET area_cone = 0
	SET area_ignore_target = 0
	SET area_size = 0
	SET area_delay = 0
	SET area_triggers = 0
	SET area_file_missing = 0
	PATCH_IF projectile > 1 BEGIN
		LOOKUP_IDS_SYMBOL_OF_INT area_file ~projectl~ (projectile - 1)
		PATCH_IF NOT IS_AN_INT area_file BEGIN
			PATCH_IF FILE_EXISTS_IN_GAME ~%area_file%.pro~ BEGIN
				INNER_PATCH_FILE ~%area_file%.pro~ BEGIN
					READ_SHORT 0x8 area_type
					PATCH_IF area_type == 3 AND BUFFER_LENGTH >= 0x226 BEGIN
						READ_LONG  0x200 area_flags
						READ_LONG  0xc   area_sparking_flags
						READ_SHORT 0x206 area_size
						READ_SHORT 0x224 area_angle
						READ_SHORT 0x210 area_delay
						READ_BYTE  0x216 area_triggers
						SET area_hostile = (area_flags BAND BIT6) != 0
						SET area_allied = (area_flags BAND BIT7) != 0
						SET area_creatures = area_hostile AND area_allied ? 2 : (area_hostile ? 1 : 0)
						SET area_cone = (area_flags BAND BIT11) != 0
						SET area_ignore_target = (area_sparking_flags BAND BIT4) != 0
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
			ELSE BEGIN
				SET area_file_missing = 1
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

// Nom d'un projectile (valeur de projectl.ids) : liste @8070000 indexée par AD_PROJECTILE_NAMES
// (new-lib/catalog.tpa) ; vide pour un projectile sans nom connu.
DEFINE_PATCH_FUNCTION ad_projectile_name
	INT_VAR
		projectile = 0
	RET
		name
BEGIN
	SPRINT name ~~
	PATCH_IF VARIABLE_IS_SET $AD_PROJECTILE_NAMES(~%projectile%~) BEGIN
		LPF ad_tra INT_VAR tra_id = 8070000 + $AD_PROJECTILE_NAMES(~%projectile%~) tra_block_start = 8070000 tra_block_size = 1000 RET name = text END // ~flèches~
	END
END

// Nom au pluriel d'une valeur d'un fichier IDS de types de créatures (parameter2 des opcodes 55,
// 177… : 2 ea.ids, 3 general.ids, 4 race.ids, 5 class.ids, 6 specific.ids, 7 gender.ids,
// 8 align.ids) : liste @8090000 (8 090 000 + 1 000 × fichier + valeur) ; vide pour un autre fichier,
// une valeur hors de 0-255 ou sans nom.
DEFINE_PATCH_FUNCTION ad_ids_name
	INT_VAR
		ids_file = 0
		entry = 0
	RET
		name
BEGIN
	SPRINT name ~~
	SET ids_name_tra = 8090000 + 1000 * ids_file + entry
	PATCH_IF ids_file >= 2 AND ids_file <= 8 AND entry >= 0 AND entry <= 255 AND TRA_ENTRY_EXISTS (~%ids_name_tra%~) BEGIN
		LPF ad_tra INT_VAR tra_id = ids_name_tra tra_block_start = 8090000 tra_block_size = 10000 RET name = text END // ~rakshasas~ (@8094128)
	END
END

// Nom d'un type secondaire de sort (msectype.ids, 1-13 : « Dégâts offensifs ») : liste @8100000 ;
// vide pour une autre valeur (type sans nom ou ajouté par un mod).
DEFINE_PATCH_FUNCTION ad_spell_secondary_type_name
	INT_VAR
		secondary_type = 0
	RET
		name
BEGIN
	SPRINT name ~~
	SET sectype_name_tra = 8100000 + secondary_type
	PATCH_IF secondary_type >= 1 AND secondary_type <= 13 AND TRA_ENTRY_EXISTS (~%sectype_name_tra%~) BEGIN
		LPF ad_tra INT_VAR tra_id = sectype_name_tra tra_block_start = 8100000 tra_block_size = 14 RET name = text END // ~Dégâts offensifs~ (@8100010)
	END
END

// Le sort resref a-t-il, dans l'un de ses en-têtes (effets de lancement exclus, comme l'ancien
// SPL_V10_HEAD_EFFECTS), un effet de l'opcode opcode (0 - 1 : tout opcode) et de la ressource
// resource (vide : toute ressource, casse ignorée) ? found : 1 si oui ; 0 si le sort n'existe pas.
DEFINE_PATCH_FUNCTION ad_spell_has_effect
	INT_VAR
		opcode = 0 - 1
	STR_VAR
		resref = ~~
		resource = ~~
	RET
		found
BEGIN
	SET found = 0
	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
		INNER_PATCH_FILE ~%resref%.spl~ BEGIN
			PATCH_IF BUFFER_LENGTH >= 0x72 BEGIN
				READ_LONG  SPL_extended_headers_offset spell_headers_offset
				READ_SHORT SPL_extended_headers_count  spell_header_count
				READ_LONG  SPL_feature_blocks_offset   spell_table_offset
				FOR (spell_h = 0; spell_h < spell_header_count AND NOT found; ++spell_h) BEGIN
					SET spell_header_offset = spell_headers_offset + spell_h * 0x28
					PATCH_IF spell_header_offset >= 0 AND spell_header_offset + 0x28 <= BUFFER_LENGTH BEGIN
						READ_SHORT (spell_header_offset + SPL_HEAD_feature_blocks_count)  spell_fx_count
						READ_SHORT (spell_header_offset + SPL_HEAD_feature_blocks_offset) spell_fx_index
						FOR (spell_p = 0; spell_p < spell_fx_count AND NOT found; ++spell_p) BEGIN
							SET spell_fx_offset = spell_table_offset + (spell_fx_index + spell_p) * 0x30
							PATCH_IF spell_fx_offset >= 0 AND spell_fx_offset + 0x30 <= BUFFER_LENGTH BEGIN
								READ_SHORT (spell_fx_offset + FX_opcode) spell_fx_opcode
								READ_ASCII (spell_fx_offset + FX_resource) spell_fx_resource (8) NULL
								SET found = (opcode < 0 OR spell_fx_opcode == opcode)
									AND (~%resource%~ STRING_EQUAL ~~ OR ~%spell_fx_resource%~ STRING_EQUAL_CASE ~%resource%~)
							END
						END
					END
				END
			END
		END
	END
END

// Niveau du sort resref (champ du fichier lu sur quatre octets, comme l'ancien moteur) ; 0 - 1 si le
// sort n'existe pas.
DEFINE_PATCH_FUNCTION ad_spell_level
	STR_VAR
		resref = ~~
	RET
		level
BEGIN
	SET level = 0 - 1
	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
		INNER_PATCH_FILE ~%resref%.spl~ BEGIN
			PATCH_IF BUFFER_LENGTH >= SPL_level + 4 BEGIN
				READ_LONG SPL_level level
			END
		END
	END
END
