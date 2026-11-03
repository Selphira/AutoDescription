// Opcode 106 (Stat: Morale Break Modifier) : parameter1 = valeur, parameter2 = mode, comme un
// modificateur simple ; plus le point de rupture est bas, plus le moral résiste : « Le point de
// rupture de moral du porteur passe à 5 ». Code commun dans new-lib/opcodes/states.tpp (une phrase
// par variante). Un point de rupture fixé à 1 disparaît devant l'immunité à la panique avec
// AD_ENABLE_SHRINKAGE (ad_group_morale, new-lib/groups.tpp).

// Validation de l'ancien opcode_modstat2_is_valid.
DEFINE_PATCH_MACRO ad_op_106_support BEGIN
	SET stat_opcode = 106
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_106_lines BEGIN
	SET state_opcode = 106
	SPRINT state_variant_macro ~ad_op_106_variant~
	LPM ad_state_lines
END

// Ancien opcode_self_106 : valeur fixée ramenée entre 0 et 20 (0 immunise contre la panique, 1 garde
// le moral au plus haut) ; un ajout négatif renforce le moral ; un pourcentage multiplie le point de
// rupture (IESDP) : « passe à 50 % de sa valeur ».
DEFINE_PATCH_MACRO ad_op_106_variant BEGIN
	SET value = $fx_parameter1(~%line_fx%~)
	PATCH_IF $fx_parameter2(~%line_fx%~) == MOD_TYPE_flat BEGIN
		SET value = value < 0 ? 0 : (value > 20 ? 20 : value)
		SET state_variant = value == 0 ? 0 : (value == 1 ? 1 : 2)
	END
	ELSE PATCH_IF $fx_parameter2(~%line_fx%~) == MOD_TYPE_percentage BEGIN
		SET state_variant = 5
		PATCH_IF value >= 0 BEGIN
			SPRINT value @1200003 // ~%value%%PERCENT%~
		END
	END
	ELSE BEGIN
		SET state_variant = value < 0 ? 3 : 4
		SET value = ABS value
	END
END
