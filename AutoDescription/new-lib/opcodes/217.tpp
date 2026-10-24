// Opcode 217 (Spell Effect: Unconsciousness 20HP) : « Endort la cible si ses points de vie sont
// inférieurs à 20 », phrases de l'opcode 39 ; le sommeil dure toujours 5 rounds (IESDP), durée écrite
// à la place de celle de l'effet (AD_OPCODE_FIXED_DURATION, new-lib/catalog.tpa). Comme l'ancien
// opcode_self_217 lit alors un timing limité, seul parameter2 1 sur EE donne le sommeil profond. Code
// commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_217_support BEGIN END

DEFINE_PATCH_MACRO ad_op_217_lines BEGIN
	SET state_opcode = 217
	SPRINT state_variant_macro ~ad_op_217_variant~
	LPM ad_state_lines
END

// Variante 1 : sommeil profond.
DEFINE_PATCH_MACRO ad_op_217_variant BEGIN
	SET state_variant = IS_EE AND $fx_parameter2(~%line_fx%~) == 1
	SPRINT line_suffix @22170001 // ~si ses points de vie sont inférieurs à 20~
END
