// Opcode 145 (Spell: Disable Spellcasting) : empêche de lancer des sorts du type parameter2 (0
// profanes, 1 divins, 2 innés ; 3, sur EE, sorts sans l'indicateur « Ignore dead/wild magic »,
// IESDP) : « Empêche le porteur de lancer des sorts profanes, divins et druidiques », « … des sorts
// sensibles aux zones de magie morte et aux hiatus entropiques » (ancien opcode_self_145). Avec AD_ENABLE_SHRINKAGE, les effets qui ne diffèrent que par
// le type de sort sont réunis (ad_group_spell_types, new-lib/groups.tpp, fx_spell_types). Avec
// AD_ARMOR_SHOW_ALLOWS_TO_CAST_SPELLS, une armure qui n'est pas une robe n'a pas de ligne pour les
// sorts profanes : elle ne dit simplement pas « Permet de lancer des sorts profanes »
// (ad_item_armor_lines, new-lib/item_render.tpp) ; l'ancien moteur appliquait cette règle à toute
// ressource (BUG-046).
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp).

// Refus : type de sort hors de 0-3 (écarté par l'ancien opcode_145_is_valid) ; type 3 réuni à
// d'autres types (l'ancien moteur en perd le nom).
DEFINE_PATCH_MACRO ad_op_145_support BEGIN
	PHP_EACH fx_ids_145 AS _ => spellcasting_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET $fx_spell_types(~%spellcasting_id%~) = 0
			// En-tête d'un sort seul : l'ancien opcode_145_is_valid n'écarte qu'un type hors de 0-3.
			PATCH_IF support_header_only BEGIN
				PATCH_IF $fx_parameter2(~%spellcasting_id%~) < 0 OR $fx_parameter2(~%spellcasting_id%~) > 3 BEGIN
					SET drop_id = spellcasting_id
					LPM ad_application_drop
				END
			END
			ELSE PATCH_IF $fx_parameter2(~%spellcasting_id%~) < 0 OR $fx_parameter2(~%spellcasting_id%~) > 3 BEGIN
				LPF ad_refusal INT_VAR fx_id = spellcasting_id STR_VAR reason = ~not_implemented:opcode145:spell_types~ message = ~spell type (parameter2) not supported~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_145_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~145~)
	LPF ad_item_is_robe RET spellcasting_robe = is_robe END
	FOR (spellcasting_late = 0; spellcasting_late <= 2; ++spellcasting_late) BEGIN
		PHP_EACH fx_ids_145 AS _ => spellcasting_id BEGIN
			PATCH_IF NOT $fx_consumed(~%spellcasting_id%~) AND $fx_late(~%spellcasting_id%~) == spellcasting_late BEGIN
				SET spellcasting_types = $fx_spell_types(~%spellcasting_id%~)
				PATCH_IF spellcasting_types == 0 BEGIN
					SET spellcasting_types = 1 << $fx_parameter2(~%spellcasting_id%~)
				END
				// Ancien opcode_self_145 : effet de type profane, ou réuni aux seuls types profanes.
				SET spellcasting_armor_rule = ($fx_parameter2(~%spellcasting_id%~) == 0 OR spellcasting_types == 1)
					AND AD_ARMOR_SHOW_ALLOWS_TO_CAST_SPELLS AND item_type == ITM_TYPE_armor AND NOT spellcasting_robe
				PATCH_IF NOT spellcasting_armor_rule AND $fx_parameter2(~%spellcasting_id%~) == 3 BEGIN
					PATCH_IF $fx_spell_types(~%spellcasting_id%~) != 0 BEGIN
						LPF ad_refusal INT_VAR fx_id = spellcasting_id STR_VAR reason = ~not_implemented:opcode145:magical_group~ message = ~spell type 3 merged with other spell types~ RET render_late_missing = refusal END
					END
					SET line_phrase = 21450120 // ~Empêche %theTarget% de lancer des sorts sensibles aux zones de magie morte et aux hiatus entropiques~
					SET line_fx = spellcasting_id
					LPM ad_effect_line
				END
				ELSE PATCH_IF NOT spellcasting_armor_rule BEGIN
					SET line_phrase = 21450110 // ~Empêche %theTarget% de lancer des sorts~
					PATCH_IF spellcasting_types != 7 BEGIN
						LPF ad_spell_types_text INT_VAR types = spellcasting_types RET spellType = text END
						SET line_phrase = 21450100 // ~Empêche %theTarget% de lancer des sorts %spellType%~
					END
					SET line_fx = spellcasting_id
					LPM ad_effect_line
				END
			END
		END
	END
END
