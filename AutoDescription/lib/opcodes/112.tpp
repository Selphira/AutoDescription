// Opcode 112 (Item: Remove Item) : retire l'objet resource de l'inventaire : « Retire « Ras +2 » de
// l'inventaire » ; code commun avec l'opcode 123 dans lib/opcodes/remove_item.tpp.

DEFINE_PATCH_MACRO ad_op_112_support BEGIN
	SET remove_opcode = 112
	LPM ad_remove_item_support
END

DEFINE_PATCH_MACRO ad_op_112_lines BEGIN
	SET remove_opcode = 112
	LPM ad_remove_item_lines
END
