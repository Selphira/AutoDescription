// Opcode 224 (Cure: Level Drain (Restoration)) : « Restaure les niveaux drainés de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_224_support BEGIN END

DEFINE_PATCH_MACRO ad_op_224_lines BEGIN
	SET state_opcode = 224
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
