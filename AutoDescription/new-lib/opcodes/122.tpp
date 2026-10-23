// Opcode 122 (Item: Create Inventory Item) : objet créé dans l'inventaire, code commun dans
// new-lib/opcodes/create_item.tpp. Avec AD_ENABLE_SHRINKAGE, l'objet qu'un effet 112 retire dans les
// mêmes conditions s'écrit « Remplace « A » par « B » » (ad_group_replace_item), et l'objet que le
// porteur retrouve après un délai prolonge son retrait (ad_group_item_return, new-lib/groups.tpp).

// Refus propre à l'opcode : objet MISC56 qui remplace une arme brisée (opcode virtuel 519 de l'ancien
// opcode_122_group).
DEFINE_PATCH_MACRO ad_op_122_support BEGIN
	SET create_opcode = 122
	LPM ad_create_item_support
	FOR (create_id = 0; create_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++create_id) BEGIN
		SPRINT create_resref $fx_resource(~%create_id%~)
		PATCH_IF $fx_opcode(~%create_id%~) == 122 AND AD_ENABLE_SHRINKAGE
				AND (~%create_resref%~ STRING_EQUAL_CASE ~MISC56~ OR ~%create_resref%~ STRING_EQUAL_CASE ~MISC56_~) BEGIN
			LPF ad_refusal INT_VAR fx_id = create_id STR_VAR reason = ~not_implemented:opcode122:broken_weapon~ message = ~item replacing a broken weapon~ RET render_missing = refusal END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_122_lines BEGIN
	SET create_opcode = 122
	SET create_phrase = 21220100 // ~Crée %amount% « %itemName% » dans l'inventaire %ofTheTarget%~
	LPM ad_create_item_lines
END
