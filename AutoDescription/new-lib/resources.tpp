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
// jeu remplace à sa création par un objet tiré au sort : random ; listed, ligne de rndtres.2da (dont
// l'ancien moteur énumère les objets) ; quality, numéro de RNDTRE01 à RNDTRE05 (0 sinon).
DEFINE_PATCH_FUNCTION ad_item_is_random_treasure
	STR_VAR
		resref = ~~
	RET
		random
		listed
		quality
BEGIN
	SPRINT random_key ~%resref%~
	TO_LOWER random_key
	SET quality = 0
	PATCH_IF (~%random_key%~ STRING_MATCHES_REGEXP ~^rndtre0[1-5]$~) == 0 BEGIN
		INNER_PATCH_SAVE random_number ~%random_key%~ BEGIN
			DELETE_BYTES 0 6
		END
		SET quality = random_number
	END
	SET listed = 0
	PATCH_IF FILE_EXISTS_IN_GAME ~rndtres.2da~ BEGIN
		INNER_PATCH_FILE ~rndtres.2da~ BEGIN
			COUNT_2DA_ROWS 2 random_rows
			FOR (random_row = 0; random_row < random_rows AND NOT listed; ++random_row) BEGIN
				READ_2DA_ENTRY random_row 0 2 random_label
				TO_LOWER random_label
				SET listed = ~%random_label%~ STRING_EQUAL ~%random_key%~
			END
		END
	END
	SET random = quality > 0 OR listed
END

// Objets que le trésor aléatoire resref de rndtres.2da peut donner (ancien get_random_treasure_names et
// strings.tpa) : noms dans l'ordre de la ligne, chacun une fois, jusqu'au premier « * », sans les
// objets absents ou sans nom ; « « A », « B » ou « C » » à placer entre les guillemets de la phrase ;
// vide si aucun objet n'a de nom.
DEFINE_PATCH_FUNCTION ad_random_treasure_names
	STR_VAR
		resref = ~~
	RET
		names
BEGIN
	SPRINT names ~~
	SET random_count = 0
	SET random_done = 0
	CLEAR_ARRAY ad_random_seen
	PATCH_IF FILE_EXISTS_IN_GAME ~rndtres.2da~ BEGIN
		INNER_PATCH_FILE ~rndtres.2da~ BEGIN
			REPLACE_EVALUATE CASE_INSENSITIVE ~^%resref%[ %TAB%]+\([^%MNL%%LNL%]*\)~ BEGIN
				PATCH_IF NOT random_done BEGIN
					SET random_done = 1
					INNER_PATCH ~%MATCH1%~ BEGIN
						SET random_end = 0
						REPLACE_EVALUATE ~[^ %TAB%]+~ BEGIN
							PATCH_IF ~%MATCH0%~ STRING_EQUAL ~*~ BEGIN
								SET random_end = 1
							END
							ELSE PATCH_IF NOT random_end BEGIN
								LPF ad_item_info STR_VAR resref = ~%MATCH0%~ RET random_name = name END
								PATCH_IF NOT (~%random_name%~ STRING_EQUAL ~~) AND NOT VARIABLE_IS_SET $ad_random_seen(~%random_name%~) BEGIN
									SET $ad_random_seen(~%random_name%~) = 1
									SPRINT $ad_random_names(~%random_count%~) ~%random_name%~
									SET random_count += 1
								END
							END
						END ~%MATCH0%~
					END
				END
			END ~%MATCH0%~
		END
	END
	SPRINT and @1000007 // ~ou~
	SPRINT random_glue @1000005 // ~ », « ~
	SPRINT random_final_glue @1000006 // ~ » %and% « ~
	FOR (random_i = 0; random_i < random_count; ++random_i) BEGIN
		SPRINT random_name $ad_random_names(~%random_i%~)
		PATCH_IF random_i == 0 BEGIN
			SPRINT names ~%random_name%~
		END
		ELSE PATCH_IF random_i == random_count - 1 BEGIN
			SPRINT names ~%names%%random_final_glue%%random_name%~
		END
		ELSE BEGIN
			SPRINT names ~%names%%random_glue%%random_name%~
		END
	END
END

// Créature resref (ancien get_creature_name, get_creature_allegiance) : nom (vide si la créature
// n'existe pas ou n'a pas de nom), allégeance (ea.ids) et niveau de sa première classe.
DEFINE_PATCH_FUNCTION ad_creature_info
	STR_VAR
		resref = ~~
	RET
		name
		allegiance
		level
BEGIN
	SPRINT name ~~
	SET allegiance = 0
	SET level = 0
	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~%resref%.cre~ BEGIN
		INNER_PATCH_FILE ~%resref%.cre~ BEGIN
			READ_LONG CRE_name creature_name_ref
			READ_BYTE CRE_allegiance allegiance
			READ_BYTE CRE_level_first_class level
			PATCH_IF creature_name_ref > 0 BEGIN
				READ_STRREF CRE_name name
			END
		END
	END
END

// Vrai si tous les effets de tous les en-têtes du sort resref passent par la zone ronde de leur
// projectile, d'un rayon d'au plus feet pieds (ancien spell_area_within_distance) : lancé sur une
// créature, il ne touche que des créatures à moins de cette distance d'elle.
DEFINE_PATCH_FUNCTION ad_spell_area_within_distance
	INT_VAR
		feet = 0
	STR_VAR
		resref = ~~
	RET
		within_distance
BEGIN
	SET within_distance = 0
	PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
		INNER_PATCH_FILE ~%resref%.spl~ BEGIN
			READ_LONG  SPL_extended_headers_offset area_headers_offset
			READ_SHORT SPL_extended_headers_count  area_header_count
			READ_LONG  SPL_feature_blocks_offset   area_table_offset
			SET within_distance = area_header_count > 0
			FOR (area_h = 0; area_h < area_header_count AND within_distance; ++area_h) BEGIN
				SET area_header_offset = area_headers_offset + area_h * 0x28
				SET within_distance = area_header_offset >= 0 AND area_header_offset + 0x28 <= BUFFER_LENGTH
				PATCH_IF within_distance BEGIN
					READ_SHORT (area_header_offset + SPL_HEAD_projectile)            area_projectile
					READ_SHORT (area_header_offset + SPL_HEAD_feature_blocks_count)  area_fx_count
					READ_SHORT (area_header_offset + SPL_HEAD_feature_blocks_offset) area_fx_index
					// Un effet sur la cible de l'en-tête (le porteur du 232) ne dépend pas de la zone.
					SET within_distance = area_fx_count > 0
					FOR (area_p = 0; area_p < area_fx_count AND within_distance; ++area_p) BEGIN
						SET area_fx_offset = area_table_offset + (area_fx_index + area_p) * 0x30
						SET within_distance = area_fx_offset >= 0 AND area_fx_offset + 0x30 <= BUFFER_LENGTH
						PATCH_IF within_distance BEGIN
							READ_BYTE (area_fx_offset + FX_target) area_fx_target
							SET within_distance = area_fx_target == 2
						END
					END
				END
				PATCH_IF within_distance BEGIN
					LPF ad_projectile_area INT_VAR projectile = area_projectile RET area_shape area_feet area_cone END
					SET within_distance = area_shape == 1 AND NOT area_cone AND area_feet > 0 AND area_feet <= feet
				END
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
// type ajouté par un mod nommé dans AD_SECONDARY_TYPE_MODS ; vide pour une autre valeur.
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
	ELSE PATCH_IF VARIABLE_IS_SET $AD_SECONDARY_TYPE_MOD_NAME(~%secondary_type%~) BEGIN
		SET sectype_name_tra = $AD_SECONDARY_TYPE_MOD_NAME(~%secondary_type%~)
		LPF ad_tra INT_VAR tra_id = sectype_name_tra tra_block_start = 8100100 tra_block_size = 100 RET name = text END // ~Potion~ (@8100100)
	END
END

// Nom au pluriel du type d'objet item_type (itemcat.ids, « robes »), vide hors de 0-73 ou sans chaîne.
DEFINE_PATCH_FUNCTION ad_item_type_name
	INT_VAR
		item_type = 0
	RET
		name
BEGIN
	SPRINT name ~~
	SET item_type_tra = 8180000 + item_type
	PATCH_IF item_type >= 0 AND item_type <= 73 AND TRA_ENTRY_EXISTS (~%item_type_tra%~) BEGIN
		LPF ad_tra INT_VAR tra_id = item_type_tra tra_block_start = 8180000 tra_block_size = 74 RET name = text END // ~robes~ (@8180067)
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

// Niveaux d'immunité (opcode 102) qui bloquent le sort resref, en masque (0 : sort absent). L'opcode
// 102 bloque les effets dont la puissance est égale au niveau (IESDP) : le niveau 1 à 9 d'un sort en
// tient lieu (ses effets techniques de puissance 0, 146 ou 321, ne comptent pas) ; un niveau 0 ou au-delà
// de 9 n'en dit rien (SPWISH27 : niveau 0, effets de puissance 9), les puissances de ses effets (en-têtes
// et lancement) sont lues : AD_SPELL_LEVEL_ZERO pour 0, BIT10 au-delà de 9 (aucun niveau ne la bloque) ;
// sans effet, niveau 0.
DEFINE_PATCH_FUNCTION ad_spell_effects_powers
	STR_VAR
		resref = ~~
	RET
		mask
BEGIN
	SET mask = 0
	SET powers_level = 0 - 1
	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
		INNER_PATCH_FILE ~%resref%.spl~ BEGIN
			PATCH_IF BUFFER_LENGTH >= 0x72 BEGIN
				READ_LONG  SPL_level                         powers_level
				READ_LONG  SPL_feature_blocks_offset         powers_table
				READ_LONG  SPL_extended_headers_offset       powers_headers
				READ_SHORT SPL_extended_headers_count        powers_header_count
				READ_SHORT SPL_casting_feature_blocks_offset powers_index
				READ_SHORT SPL_casting_feature_blocks_count  powers_count
				LPM ad_spell_effects_powers_block
				FOR (powers_h = 0; powers_h < powers_header_count; ++powers_h) BEGIN
					SET powers_header = powers_headers + powers_h * 0x28
					PATCH_IF powers_header >= 0 AND powers_header + 0x28 <= BUFFER_LENGTH BEGIN
						READ_SHORT (powers_header + SPL_HEAD_feature_blocks_count)  powers_count
						READ_SHORT (powers_header + SPL_HEAD_feature_blocks_offset) powers_index
						LPM ad_spell_effects_powers_block
					END
				END
			END
		END
	END
	PATCH_IF powers_level >= 1 AND powers_level <= 9 BEGIN
		SET mask = 1 << (powers_level - 1)
	END
	ELSE PATCH_IF mask == 0 AND powers_level >= 0 BEGIN
		SET mask = AD_SPELL_LEVEL_ZERO
	END
END

DEFINE_PATCH_MACRO ad_spell_effects_powers_block BEGIN
	FOR (powers_k = 0; powers_k < powers_count; ++powers_k) BEGIN
		SET powers_offset = powers_table + (powers_index + powers_k) * 0x30
		PATCH_IF powers_offset >= 0 AND powers_offset + 0x30 <= BUFFER_LENGTH BEGIN
			READ_BYTE (powers_offset + EFF_power) powers_value
			SET mask = mask BOR (powers_value == 0 ? AD_SPELL_LEVEL_ZERO : (powers_value <= 9 ? 1 << (powers_value - 1) : BIT10))
		END
	END
END
