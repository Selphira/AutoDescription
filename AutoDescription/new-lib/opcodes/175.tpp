// Opcode 175 (State: Hold) : paralyse la cible, avec la phrase de l'opcode 109 (ancien
// opcode_self_175) : « Paralyse la cible ». Code commun dans new-lib/opcodes/states.tpp.

// Refus : fichier IDS hors de 2-9 (9 sur EE seulement), ou EA et valeur 100, que l'ancien
// opcode_idscheck9_is_valid écarte ; parameter1 non nul : paralysie d'un type de créature, que
// l'ancien moteur nomme, pas encore reprise (comme pour le 109). Contrairement au 109, l'ancien
// moteur ne ramène pas un fichier inhabituel à une paralysie simple.
DEFINE_PATCH_MACRO ad_op_175_support BEGIN
	PHP_EACH fx_ids_175 AS _ => hold_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%hold_id%~) BEGIN
			SET hold_ids = $fx_parameter2(~%hold_id%~)
			PATCH_IF hold_ids < 2 OR hold_ids > 9 OR (hold_ids == 9 AND NOT IS_EE) OR (hold_ids == 2 AND $fx_parameter1(~%hold_id%~) == 100) BEGIN
				LPF ad_refusal INT_VAR fx_id = hold_id STR_VAR reason = ~file_error:opcode175:invalid~ message = ~IDS file %hold_ids% is not a creature type (expected 2-9: EA, GENERAL, RACE, CLASS, SPECIFIC, GENDER, ALIGN, KIT (enhanced editions))~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_parameter1(~%hold_id%~) != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = hold_id STR_VAR reason = ~not_implemented:opcode175:creature_type~ message = ~hold of a creature type~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_175_lines BEGIN
	SET state_opcode = 175
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
