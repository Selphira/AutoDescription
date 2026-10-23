// Opcode 282 (Script: Scripting State Modifier) : modifie un état de script (parameter2) lu par les
// scripts du jeu. L'ancien moteur n'en écrit rien ; avec AD_ENABLE_SHRINKAGE, il convertit certains
// états en l'opcode qui a le même effet (ancien opcode_282_group : TAC0 et dégâts des armes,
// attaques sournoises, mort permanente, renvoi des morts-vivants…) et écarte les autres.

// Les conversions de l'ancien moteur ne sont pas reprises : refusées.
DEFINE_PATCH_MACRO ad_op_282_support BEGIN
	PHP_EACH fx_ids_282 AS _ => script_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND AD_ENABLE_SHRINKAGE BEGIN
			SET script_state = $fx_parameter2(~%script_id%~)
			// Sur un jeu classique, l'ancien moteur décale de 1 les états qui suivent.
			SET script_shifted = script_state + (IS_EE ? 0 : 1)
			PATCH_IF (script_state >= 10 AND script_state <= 12) OR script_state == 14 OR script_state == 15
					OR script_shifted == 20 OR (script_shifted >= 31 AND script_shifted <= 38)
					OR script_shifted == 41 OR script_shifted == 43 BEGIN
				LPF ad_refusal INT_VAR fx_id = script_id STR_VAR reason = ~not_implemented:opcode282:converted~ message = ~script state that the old engine converts to another opcode~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET drop_id = script_id
				LPM ad_application_drop
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_282_lines BEGIN END
