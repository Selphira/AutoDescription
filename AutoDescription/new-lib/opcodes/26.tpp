// Opcode 26 (Item: Remove Curse) : « Délivre la cible des malédictions » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_26_support BEGIN END

DEFINE_PATCH_MACRO ad_op_26_lines BEGIN
	SET state_opcode = 26
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
