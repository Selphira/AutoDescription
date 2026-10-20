// Opcode 154 (Overlay: Entangle) : « Enchevêtre la cible » ; code commun dans
// new-lib/opcodes/states.tpp. Avec AD_ENABLE_SHRINKAGE, l'enchevêtrement n'est écrit qu'avec
// l'immobilisation qui l'accompagne, qu'il absorbe (ad_group_entangle, new-lib/groups.tpp).

DEFINE_PATCH_MACRO ad_op_154_support BEGIN END

DEFINE_PATCH_MACRO ad_op_154_lines BEGIN
	SET state_opcode = 154
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
