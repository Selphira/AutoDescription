// Opcode 123 (Item: Remove Inventory Item) : retire l'objet resource de l'inventaire, avec la phrase
// de l'opcode 112 : « Retire « Sceptre des Failles » de l'inventaire » ; code commun avec l'opcode 112
// dans lib/opcodes/remove_item.tpp (validation et regroupements, que l'ancien moteur ne lui appliquait
// pas).

DEFINE_PATCH_MACRO ad_op_123_support BEGIN
	SET remove_opcode = 123
	LPM ad_remove_item_support
END

DEFINE_PATCH_MACRO ad_op_123_lines BEGIN
	SET remove_opcode = 123
	LPM ad_remove_item_lines
END
