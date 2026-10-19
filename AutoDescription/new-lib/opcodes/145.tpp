// Opcode 145 (Spell: Disable Spellcasting) : empêche de lancer des sorts du type parameter2 (0
// profanes, 1 divins, 2 innés). Seul cas pris en charge : l'unique effet 145 profane d'une armure qui
// n'est pas une robe, avec AD_ARMOR_SHOW_ALLOWS_TO_CAST_SPELLS : il n'a pas de ligne, l'armure ne
// disant simplement pas « Permet de lancer des sorts profanes » (ad_item_armor_lines,
// new-lib/item_render.tpp). Les autres cas attendent les formes de phrase selon la cible.
//
// Pris en charge : effets d'équipement certains, actifs tant que l'objet est équipé.

DEFINE_PATCH_MACRO ad_op_145_support BEGIN
	LPF ad_item_is_robe RET spellcasting_robe = is_robe END
	FOR (spellcasting_id = 0; spellcasting_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++spellcasting_id) BEGIN
		PATCH_IF $fx_opcode(~%spellcasting_id%~) == 145 BEGIN
			SPRINT spellcasting_block $fx_block(~%spellcasting_id%~)
			SPRINT spellcasting_timing_kind $fx_timing_kind(~%spellcasting_id%~)
			PATCH_IF NOT (~%spellcasting_block%~ STRING_EQUAL ~equipped~) OR NOT (~%spellcasting_timing_kind%~ STRING_EQUAL ~while_equipped~)
					OR $fx_probability(~%spellcasting_id%~) != 100 BEGIN
				SPRINT render_missing ~not_implemented:opcode145:effect_kind~
			END
			ELSE PATCH_IF NOT (item_type == ITM_TYPE_armor AND NOT spellcasting_robe AND AD_ARMOR_SHOW_ALLOWS_TO_CAST_SPELLS
					AND $fx_parameter2(~%spellcasting_id%~) == 0 AND $fx_opcode_count(~145~) == 1) BEGIN
				SPRINT render_missing ~not_implemented:opcode145:spell_types~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_145_lines BEGIN
END
