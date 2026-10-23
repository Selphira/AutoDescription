// Opcode 80 (State: Deafness) : « Assourdit la cible » ; code commun dans new-lib/opcodes/states.tpp.

// Avec AD_USE_SHORT_EFFECT_DESCRIPTION, l'ancien moteur décrit la surdité comme 50 % d'échec des sorts
// (opcode 60), pas encore décrit.
DEFINE_PATCH_MACRO ad_op_80_support BEGIN
	PATCH_IF AD_USE_SHORT_EFFECT_DESCRIPTION BEGIN
		LPF ad_refusal STR_VAR reason = ~not_implemented:opcode80:short~ message = ~short text of the effect (AD_USE_SHORT_EFFECT_DESCRIPTION)~ RET render_missing = refusal END
	END
END

DEFINE_PATCH_MACRO ad_op_80_lines BEGIN
	SET state_opcode = 80
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
