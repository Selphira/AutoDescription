// Opcode 122 (Item: Create Inventory Item) : objet créé dans l'inventaire, code commun dans
// new-lib/opcodes/create_item.tpp. Avec AD_ENABLE_SHRINKAGE, l'objet qu'un effet 112 retire dans les
// mêmes conditions s'écrit « Remplace « A » par « B » » (ad_group_replace_item), et l'objet que le
// porteur retrouve après un délai prolonge son retrait (ad_group_item_return, new-lib/groups.tpp) ;
// l'arme brisée (MISC56) qui remplace la ressource décrite s'écrit « de se briser ».

DEFINE_PATCH_MACRO ad_op_122_support BEGIN
	SET create_opcode = 122
	LPM ad_create_item_support
END

DEFINE_PATCH_MACRO ad_op_122_lines BEGIN
	SET create_opcode = 122
	SET create_phrase = 21220100 // ~Crée %amount% « %itemName% » dans l'inventaire %ofTheTarget%~
	LPM ad_create_item_lines
END
