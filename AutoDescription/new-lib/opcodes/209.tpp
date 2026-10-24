// Opcode 209 (Death: Kill 60HP) : « Tue instantanément la cible si ses points de vie sont
// inférieurs à 60 », phrase de la mort normale de l'opcode 13 (ancien opcode_target_209) ; code
// commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_209_support BEGIN END

DEFINE_PATCH_MACRO ad_op_209_lines BEGIN
	SET state_opcode = 209
	SPRINT state_variant_macro ~ad_op_209_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_209_variant BEGIN
	SPRINT line_suffix @22090001 // ~si ses points de vie sont inférieurs à 60~
END
