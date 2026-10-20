// Opcode 122 (Item: Create Inventory Item) : crée parameter1 exemplaires de l'objet resource, un seul
// si l'objet ne s'empile pas ou si parameter1 vaut 0 : « Crée 5 « Bille +4 » dans l'inventaire du
// porteur ». Avec AD_ENABLE_SHRINKAGE, l'objet qu'un effet 112 retire dans les mêmes conditions
// s'écrit « Remplace « A » par « B » » (ad_group_replace_item), et l'objet que le porteur retrouve
// après un délai prolonge son retrait (ad_group_item_return, new-lib/groups.tpp).

// Refus : ressource vide (écartée par l'ancien opcode_resref_is_valid), trésor aléatoire (l'ancien
// moteur énumère les objets possibles), objet sans nom (aucune ligne), objet MISC56 qui remplace une
// arme brisée (opcode virtuel 519 de l'ancien opcode_122_group).
DEFINE_PATCH_MACRO ad_op_122_support BEGIN
	FOR (create_id = 0; create_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++create_id) BEGIN
		PATCH_IF $fx_opcode(~%create_id%~) == 122 BEGIN
			SPRINT create_resref $fx_resource(~%create_id%~)
			LPF ad_item_is_random_treasure STR_VAR resref = ~%create_resref%~ RET create_random = random END
			LPF ad_item_info STR_VAR resref = ~%create_resref%~ RET create_name = name create_stackable = stackable END
			PATCH_IF ~%create_resref%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode122:invalid~
			END
			ELSE PATCH_IF create_random BEGIN
				SPRINT render_missing ~not_implemented:opcode122:random_treasure~
			END
			ELSE PATCH_IF ~%create_name%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode122:no_name~
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND (~%create_resref%~ STRING_EQUAL_CASE ~MISC56~ OR ~%create_resref%~ STRING_EQUAL_CASE ~MISC56_~) BEGIN
				SPRINT render_missing ~not_implemented:opcode122:broken_weapon~
			END
			ELSE BEGIN
				SET create_amount = $fx_parameter1(~%create_id%~)
				SPRINT $fx_item_name(~%create_id%~) ~%create_name%~
				SET $fx_item_amount(~%create_id%~) = (create_stackable AND create_amount != 0) ? create_amount : 1
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_122_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~122~)
	FOR (create_id = 0; create_id < fx_count; ++create_id) BEGIN
		PATCH_IF $fx_opcode(~%create_id%~) == 122 AND NOT $fx_consumed(~%create_id%~) BEGIN
			SPRINT itemName $fx_item_name(~%create_id%~)
			SET amount = $fx_item_amount(~%create_id%~)
			SET line_phrase = 21220100 // ~Crée %amount% « %itemName% » dans l'inventaire %ofTheTarget%~
			SET line_fx = create_id
			LPM ad_effect_line
		END
	END
END
