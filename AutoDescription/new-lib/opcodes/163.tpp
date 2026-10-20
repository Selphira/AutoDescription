// Opcode 163 (Protection: Free Action) : « Rétabli la vitesse de déplacement de la cible » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_163_support BEGIN END

DEFINE_PATCH_MACRO ad_op_163_lines BEGIN
	SET state_opcode = 163
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
