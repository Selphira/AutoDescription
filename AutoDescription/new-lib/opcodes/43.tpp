// Opcode 43 (Cure: Stone to Flesh) : « Dépétrifie la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_43_support BEGIN END

DEFINE_PATCH_MACRO ad_op_43_lines BEGIN
	SET state_opcode = 43
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
