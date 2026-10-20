// Magasin d'effets d'une ressource : chaque effet reçoit un identifiant (fx_id, ordre de lecture)
// et ses champs bruts sont rangés dans des tableaux parallèles fx_<champ>(fx_id). Les macros de
// ce fichier s'exécutent dans la portée de ad_describe_item / ad_describe_spell : les tableaux
// disparaissent avec la fonction (V7), rien ne passe d'une ressource à la suivante.
//
// Tableaux écrits : fx_block, fx_header, fx_position, fx_opcode, fx_target, fx_power,
// fx_parameter1, fx_parameter2, fx_timing, fx_resistance, fx_duration, fx_probability1,
// fx_probability2, fx_resource, fx_dice_count, fx_dice_sides, fx_save_type, fx_save_bonus,
// fx_special, et les valeurs normalisées de new-lib/normalize.tpp ; fx_header_target,
// fx_header_target_count, fx_header_projectile et fx_potion_drinker (ad_fx_header_fields, 0 hors
// d'un en-tête d'objet) ; fx_area_target (0 à la lecture, 1 pour un effet dont les cibles sont
// nommées d'après la zone du projectile, new-lib/application.tpp) ; fx_late (0 à la lecture, 1 pour
// un effet réuni que l'ancien moteur ajoute en fin de liste, new-lib/groups.tpp) ; fx_series_of,
// fx_series_anchor (0 - 1 et 0 à la lecture, répétitions d'un effet, new-lib/application.tpp) ;
// fx_consumed (0 à la lecture,
// mis à 1 par new-lib/groups.tpp pour un effet réuni à d'autres) ; fx_opcode_count(opcode).
// Variables écrites : fx_count, fx_header_count, fx_load_error (vide si la lecture a réussi).

// Tailles fixes des formats ITM V1 et SPL V1 (IESDP) : en-tête étendu 0x38 (objet) ou 0x28
// (sort), bloc d'effet 0x30.
DEFINE_PATCH_MACRO ad_fx_reset BEGIN
	SET fx_count = 0
	SET fx_header_count = 0
	SPRINT fx_load_error ~~
	CLEAR_ARRAY fx_opcode_count
END

DEFINE_PATCH_MACRO ad_fx_load_item BEGIN
	LPM ad_fx_reset
	READ_ASCII ITM_signature fx_signature (8)
	PATCH_IF NOT (~%fx_signature%~ STRING_EQUAL ~ITM V1  ~) BEGIN
		SPRINT fx_load_error ~unsupported_format~
	END
	ELSE PATCH_IF BUFFER_LENGTH < 0x72 BEGIN
		SPRINT fx_load_error ~invalid_file~
	END
	ELSE BEGIN
		READ_LONG  ITM_feature_blocks_offset   fx_table_offset
		READ_LONG  ITM_extended_headers_offset fx_headers_offset
		READ_SHORT ITM_extended_headers_count  fx_header_count
		READ_SHORT ITM_feature_blocks_index    fx_block_index
		READ_SHORT ITM_feature_blocks_count    fx_block_count
		SPRINT fx_block_kind ~equipped~
		SET fx_block_header = 0 - 1
		LPM ad_fx_load_block
		FOR (fx_h = 0; fx_h < fx_header_count AND ~%fx_load_error%~ STRING_EQUAL ~~; ++fx_h) BEGIN
			SET fx_header_offset = fx_headers_offset + fx_h * 0x38
			PATCH_IF fx_header_offset < 0 OR fx_header_offset + 0x38 > BUFFER_LENGTH BEGIN
				SPRINT fx_load_error ~invalid_header~
			END
			ELSE BEGIN
				READ_SHORT (fx_header_offset + ITM_HEAD_feature_block_count) fx_block_count
				READ_SHORT (fx_header_offset + ITM_HEAD_feature_block_index) fx_block_index
				SPRINT fx_block_kind ~ability~
				SET fx_block_header = fx_h
				SET fx_first_id = fx_count
				LPM ad_fx_load_block
				LPM ad_fx_header_fields
			END
		END
	END
END

// Champs de l'en-tête d'objet des effets qui viennent d'être lus. Une potion dont l'en-tête vise
// son utilisateur (cible 5) est bue par lui : ses effets le touchent, quelle que soit leur cible
// (ancien load_charged_abilities). L'ancien moteur lit la cible et le nombre de cibles comme un
// seul mot de 16 bits (BUG-020) : fx_header_target_count garde ce nombre pour que la prise en
// charge refuse les cas où il en tient compte à tort.
DEFINE_PATCH_MACRO ad_fx_header_fields BEGIN
	READ_SHORT ITM_type fx_item_type
	READ_BYTE  (fx_header_offset + ITM_HEAD_target)               fx_header_target
	READ_BYTE  (fx_header_offset + ITM_HEAD_target_count)         fx_header_target_count
	READ_SHORT (fx_header_offset + ITM_HEAD_projectile_animation) fx_header_projectile
	FOR (fx_id = fx_first_id; fx_id < fx_count; ++fx_id) BEGIN
		SET $fx_header_target(~%fx_id%~) = fx_header_target
		SET $fx_header_target_count(~%fx_id%~) = fx_header_target_count
		SET $fx_header_projectile(~%fx_id%~) = fx_header_projectile
		SET $fx_potion_drinker(~%fx_id%~) = fx_item_type == ITM_TYPE_potion AND fx_header_target == TARGET_HEAD_self
		PATCH_IF $fx_potion_drinker(~%fx_id%~) BEGIN
			SET $fx_effective_target(~%fx_id%~) = TARGET_FX_self
		END
	END
END

DEFINE_PATCH_MACRO ad_fx_load_spell BEGIN
	LPM ad_fx_reset
	READ_ASCII SPL_signature fx_signature (8)
	PATCH_IF NOT (~%fx_signature%~ STRING_EQUAL ~SPL V1  ~) BEGIN
		SPRINT fx_load_error ~unsupported_format~
	END
	ELSE PATCH_IF BUFFER_LENGTH < 0x72 BEGIN
		SPRINT fx_load_error ~invalid_file~
	END
	ELSE BEGIN
		READ_LONG  SPL_feature_blocks_offset         fx_table_offset
		READ_LONG  SPL_extended_headers_offset       fx_headers_offset
		READ_SHORT SPL_extended_headers_count        fx_header_count
		// Malgré leur nom BGforge, 0x6e et 0x20 sont des index dans la table d'effets (IESDP).
		READ_SHORT SPL_casting_feature_blocks_offset fx_block_index
		READ_SHORT SPL_casting_feature_blocks_count  fx_block_count
		SPRINT fx_block_kind ~casting~
		SET fx_block_header = 0 - 1
		LPM ad_fx_load_block
		FOR (fx_h = 0; fx_h < fx_header_count AND ~%fx_load_error%~ STRING_EQUAL ~~; ++fx_h) BEGIN
			SET fx_header_offset = fx_headers_offset + fx_h * 0x28
			PATCH_IF fx_header_offset < 0 OR fx_header_offset + 0x28 > BUFFER_LENGTH BEGIN
				SPRINT fx_load_error ~invalid_header~
			END
			ELSE BEGIN
				READ_SHORT (fx_header_offset + SPL_HEAD_feature_blocks_count)  fx_block_count
				READ_SHORT (fx_header_offset + SPL_HEAD_feature_blocks_offset) fx_block_index
				SPRINT fx_block_kind ~ability~
				SET fx_block_header = fx_h
				LPM ad_fx_load_block
			END
		END
	END
END

// Lit fx_block_count effets à partir de l'index fx_block_index de la table d'effets. Une lecture
// hors du fichier ferait échouer toute la ressource (V31) : les bornes sont vérifiées avant.
DEFINE_PATCH_MACRO ad_fx_load_block BEGIN
	FOR (fx_p = 0; fx_p < fx_block_count AND ~%fx_load_error%~ STRING_EQUAL ~~; ++fx_p) BEGIN
		SET fx_offset = fx_table_offset + (fx_block_index + fx_p) * 0x30
		PATCH_IF fx_offset < 0 OR fx_offset + 0x30 > BUFFER_LENGTH BEGIN
			SPRINT fx_load_error ~invalid_effect~
		END
		ELSE BEGIN
			SET fx_id = fx_count
			SPRINT $fx_block(~%fx_id%~) ~%fx_block_kind%~
			SET $fx_header(~%fx_id%~)   = fx_block_header
			SET $fx_position(~%fx_id%~) = fx_p
			READ_SHORT (fx_offset + FX_opcode)       $fx_opcode(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_target)       $fx_target(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_power)        $fx_power(~%fx_id%~)
			READ_LONG  (fx_offset + FX_parameter1)   $fx_parameter1(~%fx_id%~)
			READ_LONG  (fx_offset + FX_parameter2)   $fx_parameter2(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_timing)       $fx_timing(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_resistance)   $fx_resistance(~%fx_id%~)
			READ_LONG  (fx_offset + FX_duration)     $fx_duration(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_probability1) $fx_probability1(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_probability2) $fx_probability2(~%fx_id%~)
			READ_ASCII (fx_offset + FX_resource)     $fx_resource(~%fx_id%~) (8) NULL
			READ_LONG  (fx_offset + FX_dice_thrown)  $fx_dice_count(~%fx_id%~)
			READ_LONG  (fx_offset + FX_dice_sides)   $fx_dice_sides(~%fx_id%~)
			READ_LONG  (fx_offset + FX_save_type)    $fx_save_type(~%fx_id%~)
			READ_LONG  (fx_offset + FX_save_bonus)   $fx_save_bonus(~%fx_id%~)
			READ_LONG  (fx_offset + FX_stacking_id_Ex) $fx_special(~%fx_id%~)
			LPM ad_fx_normalize
			SET $fx_consumed(~%fx_id%~) = 0
			SET $fx_header_target(~%fx_id%~) = 0
			SET $fx_header_target_count(~%fx_id%~) = 0
			SET $fx_header_projectile(~%fx_id%~) = 0
			SET $fx_potion_drinker(~%fx_id%~) = 0
			SET $fx_area_target(~%fx_id%~) = 0
			SET $fx_late(~%fx_id%~) = 0
			SET $fx_series_of(~%fx_id%~) = 0 - 1
			SET $fx_series_anchor(~%fx_id%~) = 0
			SET fx_opcode = $fx_opcode(~%fx_id%~)
			SET $fx_opcode_count(~%fx_opcode%~) = VARIABLE_IS_SET $fx_opcode_count(~%fx_opcode%~) ? $fx_opcode_count(~%fx_opcode%~) + 1 : 1
			SET fx_count += 1
		END
	END
END
