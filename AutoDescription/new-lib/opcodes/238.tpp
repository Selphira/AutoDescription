// Opcode 238 (Death: Disintegrate) : « Désintègre la cible », phrase de la désintégration de
// l'opcode 13 (ancien opcode_target_238) ; code commun dans new-lib/opcodes/states.tpp.

// Refus : fichier IDS hors de 2-9 (9 sur EE seulement), ou valeur 100 d'ea.ids, que l'ancien
// opcode_idscheck9_is_valid écarte ; parameter1 non nul : désintégration d'un type de créature, que
// l'ancien moteur nomme (opcode_55_common), pas encore reprise.
DEFINE_PATCH_MACRO ad_op_238_support BEGIN
	PHP_EACH fx_ids_238 AS _ => disintegrate_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%disintegrate_id%~) BEGIN
			SET disintegrate_ids = $fx_parameter2(~%disintegrate_id%~)
			SET disintegrate_value = $fx_parameter1(~%disintegrate_id%~)
			PATCH_IF disintegrate_ids < 2 OR disintegrate_ids > 9 OR (disintegrate_ids == 9 AND NOT IS_EE) OR (disintegrate_ids == 2 AND disintegrate_value == 100) BEGIN
				LPF ad_refusal INT_VAR fx_id = disintegrate_id STR_VAR reason = ~file_error:opcode238:invalid~ message = ~IDS file %disintegrate_ids% is not a creature type (expected 2-9: EA, GENERAL, RACE, CLASS, SPECIFIC, GENDER, ALIGN, KIT (enhanced editions))~ RET render_missing = refusal END
			END
			ELSE PATCH_IF disintegrate_value != 0 AND NOT support_header_only BEGIN
				LPF ad_refusal INT_VAR fx_id = disintegrate_id STR_VAR reason = ~not_implemented:opcode238:creature_type~ message = ~disintegration of a creature type~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_238_lines BEGIN
	SET state_opcode = 238
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
