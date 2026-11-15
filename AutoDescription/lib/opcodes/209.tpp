// Opcode 209 (Death: Kill 60HP) : « Tue instantanément la cible si ses points de vie sont
// inférieurs à 60 », phrase de la mort normale de l'opcode 13 (ancien opcode_target_209) ; code
// commun dans lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_209_variant BEGIN
	SPRINT line_suffix @22090001 // ~si ses points de vie sont inférieurs à 60~
END
