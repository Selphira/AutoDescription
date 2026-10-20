// Opcode 164 (Cure: Drunkeness) : « Dissipe l'état d'ébriété de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_164_support BEGIN END

DEFINE_PATCH_MACRO ad_op_164_lines BEGIN
	SET state_opcode = 164
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
