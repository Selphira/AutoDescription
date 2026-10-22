// Opcode 145 (Spell: Disable Spellcasting) : empêche de lancer des sorts du type parameter2 (0
// profanes, 1 divins, 2 innés) : « Empêche le porteur de lancer des sorts profanes, divins et
// druidiques » (ancien opcode_self_145). Avec AD_ENABLE_SHRINKAGE, les effets qui ne diffèrent que par
// le type de sort sont réunis (ad_group_spell_types, new-lib/groups.tpp, fx_spell_types). Avec
// AD_ARMOR_SHOW_ALLOWS_TO_CAST_SPELLS, une armure qui n'est pas une robe n'a pas de ligne pour les
// sorts profanes : elle ne dit simplement pas « Permet de lancer des sorts profanes »
// (ad_item_armor_lines, new-lib/item_render.tpp) ; l'ancien moteur appliquait cette règle à toute
// ressource (BUG-046).
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp).

// Refus : type de sort hors de 0-2 (l'ancien opcode_145_is_valid écarte un type hors de 0-3 ; le
// type 3 n'a pas de nom).
DEFINE_PATCH_MACRO ad_op_145_support BEGIN
	FOR (spellcasting_id = 0; spellcasting_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++spellcasting_id) BEGIN
		PATCH_IF $fx_opcode(~%spellcasting_id%~) == 145 BEGIN
			SET $fx_spell_types(~%spellcasting_id%~) = 0
			PATCH_IF $fx_parameter2(~%spellcasting_id%~) < 0 OR $fx_parameter2(~%spellcasting_id%~) > 2 BEGIN
				SPRINT render_missing ~not_implemented:opcode145:spell_types~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_145_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~145~)
	LPF ad_item_is_robe RET spellcasting_robe = is_robe END
	FOR (spellcasting_late = 0; spellcasting_late <= 1; ++spellcasting_late) BEGIN
		FOR (spellcasting_id = 0; spellcasting_id < fx_count; ++spellcasting_id) BEGIN
			PATCH_IF $fx_opcode(~%spellcasting_id%~) == 145 AND NOT $fx_consumed(~%spellcasting_id%~) AND $fx_late(~%spellcasting_id%~) == spellcasting_late BEGIN
				SET spellcasting_types = $fx_spell_types(~%spellcasting_id%~)
				PATCH_IF spellcasting_types == 0 BEGIN
					SET spellcasting_types = 1 << $fx_parameter2(~%spellcasting_id%~)
				END
				// Ancien opcode_self_145 : effet de type profane, ou réuni aux seuls types profanes.
				SET spellcasting_armor_rule = ($fx_parameter2(~%spellcasting_id%~) == 0 OR spellcasting_types == 1)
					AND AD_ARMOR_SHOW_ALLOWS_TO_CAST_SPELLS AND item_type == ITM_TYPE_armor AND NOT spellcasting_robe
				PATCH_IF NOT spellcasting_armor_rule BEGIN
					SET line_phrase = 21450110 // ~Empêche %theTarget% de lancer des sorts~
					PATCH_IF spellcasting_types != 7 BEGIN
						CLEAR_ARRAY spellcasting_names
						SET spellcasting_count = 0
						FOR (spellcasting_bit = 0; spellcasting_bit < 3; ++spellcasting_bit) BEGIN
							PATCH_IF (spellcasting_types BAND (1 << spellcasting_bit)) != 0 BEGIN
								LPF ad_tra INT_VAR tra_id = 8020000 + spellcasting_bit tra_block_start = 8020000 tra_block_size = 10 RET spellcasting_name = text END // ~profanes~
								SPRINT $spellcasting_names(~%spellcasting_count%~) ~%spellcasting_name%~
								SET spellcasting_count += 1
								// Les sorts divins sont ceux des clercs et des druides (ancien get_spell_type_str).
								PATCH_IF spellcasting_bit == 1 BEGIN
									SPRINT $spellcasting_names(~%spellcasting_count%~) @8020004 // ~druidiques~
									SET spellcasting_count += 1
								END
							END
						END
						LPF ad_join STR_VAR array_name = ~spellcasting_names~ RET spellType = text END
						SET line_phrase = 21450100 // ~Empêche %theTarget% de lancer des sorts %spellType%~
					END
					SET line_fx = spellcasting_id
					LPM ad_effect_line
				END
			END
		END
	END
END
