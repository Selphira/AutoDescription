// Opcode 255 (Item: Create Inventory Item (days)) : comme l'opcode 122, durée en jours
// (AD_OPCODE_DURATION_SCALE, new-lib/catalog.tpa) ; code commun dans new-lib/opcodes/create_item.tpp.

DEFINE_PATCH_MACRO ad_op_255_support BEGIN
	SET create_opcode = 255
	LPM ad_create_item_support
END

DEFINE_PATCH_MACRO ad_op_255_lines BEGIN
	SET create_opcode = 255
	SET create_phrase = 22550100 // ~Crée %amount% « %itemName% » dans l'inventaire %ofTheTarget%~
	LPM ad_create_item_lines
END
