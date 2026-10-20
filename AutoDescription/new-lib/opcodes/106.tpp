// Opcode 106 (Stat: Morale Break Modifier) : parameter1 = valeur, parameter2 = mode, comme un
// modificateur simple ; plus le point de rupture est bas, plus le moral résiste : « Le point de
// rupture de moral du porteur passe à 5 ». Code commun dans new-lib/opcodes/states.tpp (une phrase
// par variante). Un point de rupture fixé à 1 disparaît devant l'immunité à la panique avec
// AD_ENABLE_SHRINKAGE (ad_group_morale, new-lib/groups.tpp).

// Validation de l'ancien opcode_modstat2_is_valid. En mode pourcentage, l'ancien moteur décrit la
// valeur comme un renforcement ou un affaiblissement du moral (BUG-027) : refusé.
DEFINE_PATCH_MACRO ad_op_106_support BEGIN
	SET stat_opcode = 106
	SPRINT stat_mode_3 ~invalid~
	SPRINT stat_percentage ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_106_lines BEGIN
	SET state_opcode = 106
	SPRINT state_variant_macro ~ad_op_106_variant~
	LPM ad_state_lines
END

// Ancien opcode_self_106 : valeur fixée ramenée entre 0 et 20 (0 immunise contre la panique, 1 garde
// le moral au plus haut) ; un ajout négatif renforce le moral.
DEFINE_PATCH_MACRO ad_op_106_variant BEGIN
	SET value = $fx_parameter1(~%line_fx%~)
	PATCH_IF $fx_parameter2(~%line_fx%~) == MOD_TYPE_flat BEGIN
		SET value = value < 0 ? 0 : (value > 20 ? 20 : value)
		SET state_variant = value == 0 ? 0 : (value == 1 ? 1 : 2)
	END
	ELSE BEGIN
		SET state_variant = value < 0 ? 3 : 4
		SET value = ABS value
	END
END
