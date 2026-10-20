// Opcode 218 (Protection: Stoneskin) : crée parameter1 peaux de pierre : « Crée 2 peaux de pierre
// sur la cible » ; code commun dans new-lib/opcodes/states.tpp.

// Refus : aucune peau (écartée par l'ancien opcode_218_is_valid) ; sur EE, nombre tiré aux dés
// (parameter2 non nul).
DEFINE_PATCH_MACRO ad_op_218_support BEGIN
	FOR (skin_id = 0; skin_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++skin_id) BEGIN
		PATCH_IF $fx_opcode(~%skin_id%~) == 218 BEGIN
			PATCH_IF IS_EE AND $fx_parameter2(~%skin_id%~) != 0 BEGIN
				SPRINT render_missing ~not_implemented:opcode218:dice~
			END
			ELSE PATCH_IF $fx_parameter1(~%skin_id%~) <= 0 BEGIN
				SPRINT render_missing ~not_implemented:opcode218:invalid~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_218_lines BEGIN
	SET state_opcode = 218
	SPRINT state_variant_macro ~ad_op_218_amount~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_218_amount BEGIN
	SET value = $fx_parameter1(~%line_fx%~)
	PATCH_IF value == 1 BEGIN
		SPRINT valueType @22180001 // ~peau de pierre~
	END
	ELSE BEGIN
		SPRINT valueType @22180002 // ~peaux de pierre~
	END
	SPRINT amount @22180000 // ~%value% %valueType%~
END
