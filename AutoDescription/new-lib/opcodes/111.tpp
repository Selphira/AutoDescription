// Opcode 111 (Item: Create Magical Weapon) : équipe la cible de parameter1 armes resource (au moins
// une) : « Équipe le porteur d'1 arme magique (Attaquer) ». Comme l'ancien opcode_111_replace, une
// arme dont les effets d'équipement métamorphosent (135) remplace le 111 dès la lecture
// (ad_fx_substitute_111, appelée par ad_fx_add_effect, new-lib/effects.tpp) par cette métamorphose,
// décrite par l'opcode 135 : opcode, puissance, paramètres, ressource, dés et special de l'effet de
// l'arme ; cible, timing, durée, probabilités, jet de sauvegarde et résistance du 111. L'effet
// remplacé n'est pas externe (l'ancien moteur garde isExternal du 111) ; fx_from_111 le distingue.

// Remplace l'effet fx_id (opcode 111) par la métamorphose de son arme, ou laisse la raison du refus
// dans fx_substitution_error : plusieurs métamorphoses (l'ancien moteur ajoute un effet par
// métamorphose).
DEFINE_PATCH_MACRO ad_fx_substitute_111 BEGIN
	SPRINT $fx_substitution_error(~%fx_id%~) ~~
	SPRINT weapon_resref $fx_resource(~%fx_id%~)
	SET weapon_polymorphs = 0
	PATCH_IF NOT (~%weapon_resref%~ STRING_EQUAL ~~) AND FILE_EXISTS_IN_GAME ~%weapon_resref%.itm~ BEGIN
		INNER_PATCH_FILE ~%weapon_resref%.itm~ BEGIN
			PATCH_IF BUFFER_LENGTH >= 0x72 BEGIN
				READ_LONG  ITM_feature_blocks_offset weapon_table_offset
				READ_SHORT ITM_feature_blocks_index  weapon_fx_index
				READ_SHORT ITM_feature_blocks_count  weapon_fx_count
				FOR (weapon_p = 0; weapon_p < weapon_fx_count; ++weapon_p) BEGIN
					SET weapon_fx_offset = weapon_table_offset + (weapon_fx_index + weapon_p) * 0x30
					PATCH_IF weapon_fx_offset >= 0 AND weapon_fx_offset + 0x30 <= BUFFER_LENGTH BEGIN
						READ_SHORT (weapon_fx_offset + FX_opcode) weapon_opcode
						PATCH_IF weapon_opcode == 135 BEGIN
							SET weapon_polymorphs += 1
							READ_BYTE  (weapon_fx_offset + FX_power)          weapon_power
							READ_LONG  (weapon_fx_offset + FX_parameter1)     weapon_parameter1
							READ_LONG  (weapon_fx_offset + FX_parameter2)     weapon_parameter2
							READ_ASCII (weapon_fx_offset + FX_resource)       weapon_resource (8) NULL
							READ_LONG  (weapon_fx_offset + FX_dice_thrown)    weapon_dice_count
							READ_LONG  (weapon_fx_offset + FX_dice_sides)     weapon_dice_sides
							READ_LONG  (weapon_fx_offset + FX_stacking_id_Ex) weapon_special
						END
					END
				END
			END
		END
	END
	PATCH_IF weapon_polymorphs > 1 BEGIN
		SPRINT $fx_substitution_error(~%fx_id%~) ~polymorphs~
	END
	ELSE PATCH_IF weapon_polymorphs == 1 BEGIN
		SET $fx_opcode(~%fx_id%~)         = 135
		SET $fx_power(~%fx_id%~)          = weapon_power
		SET $fx_parameter1(~%fx_id%~)     = weapon_parameter1
		SET $fx_parameter2(~%fx_id%~)     = weapon_parameter2
		SET $fx_parameter2_raw(~%fx_id%~) = weapon_parameter2
		SPRINT $fx_resource(~%fx_id%~)    ~%weapon_resource%~
		SET $fx_dice_count(~%fx_id%~)     = weapon_dice_count
		SET $fx_dice_sides(~%fx_id%~)     = weapon_dice_sides
		SET $fx_special(~%fx_id%~)        = weapon_special
		SET $fx_from_111(~%fx_id%~)       = 1
		SPRINT $fx_parent_resource(~%fx_id%~) ~%weapon_resref%~
	END
END

// Refus : effet d'un EFF ; arme à plusieurs métamorphoses (ad_fx_substitute_111) ; ressource vide
// (l'ancien opcode_111_is_valid l'écarte) ; arme sans nom (l'ancien moteur n'écrit rien) ; avec
// AD_ENABLE_SHRINKAGE, retrait différé de la même arme (112), qui fixe la durée du 111 (ancien
// opcode_112_group).
DEFINE_PATCH_MACRO ad_op_111_support BEGIN
	PHP_EACH fx_ids_111 AS _ => weapon_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%weapon_id%~) BEGIN
			SPRINT weapon_resref $fx_resource(~%weapon_id%~)
			SPRINT weapon_error $fx_substitution_error(~%weapon_id%~)
			LPF ad_item_info STR_VAR resref = ~%weapon_resref%~ RET weapon_name = name END
			PATCH_IF $fx_external(~%weapon_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = weapon_id STR_VAR reason = ~not_implemented:opcode111:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF NOT (~%weapon_error%~ STRING_EQUAL ~~) BEGIN
				LPF ad_refusal INT_VAR fx_id = weapon_id STR_VAR reason = ~not_implemented:opcode111:%weapon_error%~ message = ~weapon %weapon_resref%.ITM with several polymorph effects~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ~%weapon_resref%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = weapon_id STR_VAR reason = ~file_error:opcode111:invalid~ message = ~empty resource field~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ~%weapon_name%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF FILE_EXISTS_IN_GAME ~%weapon_resref%.itm~ BEGIN
					LPF ad_refusal INT_VAR fx_id = weapon_id STR_VAR reason = ~not_implemented:opcode111:no_name~ message = ~item %weapon_resref%.ITM has no name~ RET render_missing = refusal END
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = weapon_id STR_VAR reason = ~file_error:opcode111:missing_item~ message = ~item %weapon_resref%.ITM does not exist~ RET render_missing = refusal END
				END
			END
			ELSE BEGIN
				SPRINT $fx_item_name(~%weapon_id%~) ~%weapon_name%~
				SPRINT weapon_scope $fx_scope(~%weapon_id%~)
				PHP_EACH fx_ids_112 AS _ => weapon_other BEGIN
					SPRINT weapon_other_scope $fx_scope(~%weapon_other%~)
					SPRINT weapon_other_resref $fx_resource(~%weapon_other%~)
					PATCH_IF AD_ENABLE_SHRINKAGE AND $fx_timing(~%weapon_other%~) == TIMING_delayed AND (~%weapon_other_scope%~ STRING_EQUAL ~%weapon_scope%~) AND (~%weapon_other_resref%~ STRING_EQUAL_CASE ~%weapon_resref%~) BEGIN
						LPF ad_refusal INT_VAR fx_id = weapon_other STR_VAR reason = ~not_implemented:opcode111:remove_group~ message = ~weapon removed later by opcode 112~ RET render_missing = refusal END
					END
				END
			END
		END
	END
END

// Unité d'un pas de unit_value armes (ancien opcode_111_typed_value) : unit_tra.
DEFINE_PATCH_MACRO ad_op_111_level_unit BEGIN
	SET unit_tra = unit_value > 1 ? 21110002 : 21110001 // ~arme magique~
END

// Une ligne par effet : « d'1 arme magique », « de 2 armes magiques ».
DEFINE_PATCH_MACRO ad_op_111_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~111~)
	PHP_EACH fx_ids_111 AS _ => weapon_id BEGIN
		PATCH_IF NOT $fx_consumed(~%weapon_id%~) BEGIN
			SPRINT itemName $fx_item_name(~%weapon_id%~)
			SET value = $fx_parameter1(~%weapon_id%~) > 0 ? $fx_parameter1(~%weapon_id%~) : 1
			LPF ad_tra INT_VAR tra_id = value > 1 ? 21110002 : 21110001 RET valueType = text END // ~arme magique~
			SPRINT amount @21110003 // ~%value% %valueType%~
			SET line_fx = weapon_id
			SET line_phrase = value > 1 ? 21110110 : 21110100 // ~Équipe %theTarget% d'%amount% (%itemName%)~
			// Progression selon le niveau du sort (new-lib/spell_levels.tpp) : « de 1 arme magique par niveau ».
			SPRINT weapon_level_value $fx_level_value(~%weapon_id%~)
			PATCH_IF NOT (~%weapon_level_value%~ STRING_EQUAL ~~) BEGIN
				SPRINT amount ~%weapon_level_value%~
				SET line_phrase = 21110110 // ~Équipe %theTarget% de %amount% (%itemName%)~
			END
			LPM ad_effect_line
		END
	END
END
