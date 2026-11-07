// Opcode 282 (Script: Scripting State Modifier) : modifie un état de script (parameter2) lu par les
// scripts du jeu. L'ancien moteur n'en écrit rien ; avec AD_ENABLE_SHRINKAGE, il convertit certains
// états en l'opcode qui a le même effet (ancien opcode_282_group : TAC0 et dégâts des armes,
// attaques sournoises, mort permanente, renvoi des morts-vivants…, ad_op_282_convert) et écarte les
// autres.

// Au chargement (ad_fx_add_effect, new-lib/effects.tpp), avec AD_ENABLE_SHRINKAGE : état converti
// en l'opcode de même effet, comme l'ancien opcode_282_group, si cet opcode est décrit ou ignoré.
// États 10-12, 14, 15 (stats 166-171 : TAC0 et dégâts des armes de mêlée, des projectiles et à mains
// nues, IESDP : état = stat - 156) : opcodes 284-289 en mode « fixe » (« TAC0 des armes de mêlée :
// Passe à 1 ») ; les autres (20, 31-38, 41, 43, décalés de 1 sur un jeu classique) prennent la valeur
// en parameter2. L'effet converti suit les effets de son nouvel opcode (fx_late), comme l'effet
// ajouté par l'ancien add_opcode ; fx_282_converted : 1 si l'effet fx_id est converti.
DEFINE_PATCH_MACRO ad_op_282_convert BEGIN
	SET fx_282_converted = 0
	SET script_state = $fx_parameter2(~%fx_id%~)
	SET script_shifted = script_state + (IS_EE ? 0 : 1)
	SET script_value = $fx_parameter1(~%fx_id%~)
	SET script_opcode = 0
	SET script_parameter2 = script_value
	PATCH_IF (script_state >= 10 AND script_state <= 12) OR script_state == 14 OR script_state == 15 BEGIN
		SET script_opcode = script_state + 274
		SET script_parameter2 = MOD_TYPE_flat
	END
	ELSE PATCH_IF script_shifted == 20 BEGIN SET script_opcode = 292 END
	ELSE PATCH_IF script_shifted == 31 BEGIN SET script_opcode = 295 END
	ELSE PATCH_IF script_shifted == 32 BEGIN SET script_opcode = 297 END
	ELSE PATCH_IF script_shifted == 33 BEGIN
		SET script_opcode = 299
		SET script_parameter2 = script_state
	END
	ELSE PATCH_IF script_shifted == 34 BEGIN SET script_opcode = 300 END
	ELSE PATCH_IF script_shifted == 35 BEGIN SET script_opcode = 302 END
	ELSE PATCH_IF script_shifted == 36 BEGIN SET script_opcode = 303 END
	ELSE PATCH_IF script_shifted == 37 BEGIN
		SET script_opcode = 71
		SET script_parameter2 = MOD_TYPE_flat
	END
	ELSE PATCH_IF script_shifted == 38 BEGIN
		SET script_opcode = 60
		SET script_parameter2 = 2
	END
	ELSE PATCH_IF script_shifted == 41 BEGIN SET script_opcode = 310 END
	ELSE PATCH_IF script_shifted == 43 BEGIN
		SET script_opcode = 314
		SET script_parameter2 = script_state
	END
	PATCH_IF script_opcode > 0 AND VARIABLE_IS_SET $AD_OPCODE_STATUS(~%script_opcode%~) BEGIN
		SPRINT script_status $AD_OPCODE_STATUS(~%script_opcode%~)
		PATCH_IF ~%script_status%~ STRING_EQUAL ~DESCRIBED~ OR ~%script_status%~ STRING_EQUAL ~IGNORED~ BEGIN
			SET $fx_opcode(~%fx_id%~) = script_opcode
			SET $fx_parameter2(~%fx_id%~) = script_parameter2
			SET $fx_parameter2_raw(~%fx_id%~) = script_parameter2
			SET fx_282_converted = 1
		END
	END
END

// Les états restants que l'ancien moteur convertit (vers un opcode encore non décrit) : refusés.
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
