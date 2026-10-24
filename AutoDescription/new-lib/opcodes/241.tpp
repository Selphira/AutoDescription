// Opcode 241 (Charm: Control Creature) : phrases de l'opcode 5, dont l'ancien moteur reprend les
// macros (opcode_target_241) : « Charme la cible », sans restriction « Domination sur la cible »
// (parameter1 0) ; parameter2, le type de charme, n'est pas écrit. Code commun dans
// new-lib/opcodes/states.tpp.

// Refus : type de charme inconnu (écarté par l'ancien opcode_5_is_valid) ; parameter1 non nul sur une
// autre cible que soi, sans restriction de niveau : l'ancien moteur nomme alors un type de créature
// de general.ids, pas encore repris (une restriction de niveau, déjà écrite dans la cible, l'en
// empêche).
DEFINE_PATCH_MACRO ad_op_241_support BEGIN
	PHP_EACH fx_ids_241 AS _ => control_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET control_type = $fx_parameter2(~%control_id%~)
			SET control_target = $fx_effective_target(~%control_id%~)
			PATCH_IF NOT ((control_type >= 0 AND control_type <= 5) OR (control_type >= 1000 AND control_type <= 1005)) BEGIN
				LPF ad_refusal INT_VAR fx_id = control_id STR_VAR reason = ~file_error:opcode241:invalid~ message = ~charm type %control_type% (expected 0-5 or 1000-1005)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_parameter1(~%control_id%~) != 0 AND control_target != TARGET_FX_self AND control_target != TARGET_FX_original_caster
					AND $fx_level_max(~%control_id%~) == 0 AND $fx_level_min(~%control_id%~) <= 1 AND NOT support_header_only BEGIN
				LPF ad_refusal INT_VAR fx_id = control_id STR_VAR reason = ~not_implemented:opcode241:creature_type~ message = ~control of a creature type~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_241_lines BEGIN
	SET state_opcode = 241
	SPRINT state_variant_macro ~ad_op_241_variant~
	LPM ad_state_lines
END

// Variante 0 : charme, 1 : sans restriction, sur une autre cible que soi.
DEFINE_PATCH_MACRO ad_op_241_variant BEGIN
	SET control_target = $fx_effective_target(~%line_fx%~)
	SET state_variant = control_target != TARGET_FX_self AND control_target != TARGET_FX_original_caster AND $fx_parameter1(~%line_fx%~) == 0
END
