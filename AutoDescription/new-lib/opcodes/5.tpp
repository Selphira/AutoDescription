// Opcode 5 (Charm: Charm Specific Creature) : « Charme la cible » ; sur la cible d'un en-tête,
// parameter1 nomme le type de créature charmé (valeur de general.ids : « Charme les animaux »), 0 le
// charme sans restriction (« Domination sur la cible ») ; parameter2, le type de charme, n'est pas
// écrit, comme dans l'ancien moteur. Effet d'un 177 qui vise un type de créature : la cible est ce
// type (ad_application_versus), le charme ne nomme pas le sien. Code commun dans
// new-lib/opcodes/states.tpp.

// Refus : type de charme inconnu (écarté par l'ancien opcode_5_is_valid) ; type de créature sans nom
// (aucune ligne) ou cible autre que « la cible » (l'ancien moteur garde alors un nom lu pour un effet
// précédent).
DEFINE_PATCH_MACRO ad_op_5_support BEGIN
	PHP_EACH fx_ids_5 AS _ => charm_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET charm_type = $fx_parameter2(~%charm_id%~)
			SET charm_value = $fx_parameter1(~%charm_id%~)
			SET charm_target = $fx_effective_target(~%charm_id%~)
			LPF ad_ids_name INT_VAR ids_file = 3 entry = charm_value RET charm_name = name END
			SPRINT $fx_charm_name(~%charm_id%~) ~%charm_name%~
			PATCH_IF NOT ((charm_type >= 0 AND charm_type <= 5) OR (charm_type >= 1000 AND charm_type <= 1005)) BEGIN
				LPF ad_refusal INT_VAR fx_id = charm_id STR_VAR reason = ~file_error:opcode5:invalid~ message = ~charm type %charm_type% (expected 0-5 or 1000-1005)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF charm_value != 0 AND charm_target != TARGET_FX_self AND charm_target != TARGET_FX_original_caster
					AND $fx_versus_file(~%charm_id%~) == 0 BEGIN
				PATCH_IF charm_target != TARGET_FX_preset OR $fx_area_target(~%charm_id%~) BEGIN
					LPF ad_refusal INT_VAR fx_id = charm_id STR_VAR reason = ~not_implemented:opcode5:target~ message = ~target other than preset, or area target~ RET render_missing = refusal END
				END
				ELSE PATCH_IF ~%charm_name%~ STRING_EQUAL ~~ BEGIN
					LPF ad_refusal INT_VAR fx_id = charm_id STR_VAR reason = ~not_implemented:opcode5:ids_name~ message = ~creature type has no name~ RET render_missing = refusal END
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_5_lines BEGIN
	SET state_opcode = 5
	SPRINT state_variant_macro ~ad_op_5_variant~
	SPRINT the @1000008 // ~les~
	LPM ad_state_lines
END

// Variante 0 : charme (du type nommé), 1 : sans restriction, sur une autre cible que soi.
DEFINE_PATCH_MACRO ad_op_5_variant BEGIN
	SET charm_target = $fx_effective_target(~%line_fx%~)
	SET charm_self = charm_target == TARGET_FX_self OR charm_target == TARGET_FX_original_caster
	SET state_variant = (NOT charm_self AND $fx_parameter1(~%line_fx%~) == 0) ? 1 : 0
	PATCH_IF NOT charm_self AND $fx_parameter1(~%line_fx%~) != 0 AND $fx_versus_file(~%line_fx%~) == 0 BEGIN
		SPRINT charm_name $fx_charm_name(~%line_fx%~)
		SPRINT line_the_target ~%the% %charm_name%~
	END
END
