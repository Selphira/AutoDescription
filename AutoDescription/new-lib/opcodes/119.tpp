// Opcode 119 (Spell Effect: Mirror Image) : « Image miroir », « Lance Image miroir sur la cible » ;
// code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_119_support BEGIN END

DEFINE_PATCH_MACRO ad_op_119_lines BEGIN
	SET state_opcode = 119
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
