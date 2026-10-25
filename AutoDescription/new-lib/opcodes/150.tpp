// Opcode 150 (Spell Effect: Find Traps) : « Détection des pièges par la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_150_support BEGIN END

DEFINE_PATCH_MACRO ad_op_150_lines BEGIN
	SET state_opcode = 150
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
