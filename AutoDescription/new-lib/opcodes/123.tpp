// Opcode 123 (Item: Remove Inventory Item) : retire l'objet resource de l'inventaire, avec la phrase
// de l'opcode 112 (ancien opcode_self_123) : « Retire « Sceptre des Failles » de l'inventaire ».
// L'ancien moteur ne lui applique ni la validation ni les regroupements du 112 : un objet sans nom
// (MINHP1, la régénération des trolls) ne donne aucune ligne.

// Refus : ressource vide (l'ancien opcode_123_is_valid l'écarte, erreur journalisée).
DEFINE_PATCH_MACRO ad_op_123_support BEGIN
	FOR (remove_id = 0; remove_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++remove_id) BEGIN
		PATCH_IF $fx_opcode(~%remove_id%~) == 123 AND NOT $fx_consumed(~%remove_id%~) BEGIN
			SPRINT remove_resref $fx_resource(~%remove_id%~)
			LPF ad_item_info STR_VAR resref = ~%remove_resref%~ RET remove_name = name END
			PATCH_IF ~%remove_resref%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode123:invalid~
			END
			ELSE PATCH_IF ~%remove_name%~ STRING_EQUAL ~~ BEGIN
				SET drop_id = remove_id
				LPM ad_application_drop
			END
			ELSE BEGIN
				SPRINT $fx_item_name(~%remove_id%~) ~%remove_name%~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_123_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~123~)
	FOR (remove_id = 0; remove_id < fx_count; ++remove_id) BEGIN
		PATCH_IF $fx_opcode(~%remove_id%~) == 123 AND NOT $fx_consumed(~%remove_id%~) BEGIN
			SPRINT itemName $fx_item_name(~%remove_id%~)
			SET line_fx = remove_id
			SET line_phrase = 21120100 // ~Retire « %itemName% » de l'inventaire~ (+1 : ~Retire « %itemName% » de l'inventaire %ofTheTarget%~)
			LPM ad_effect_line
		END
	END
END
