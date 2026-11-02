// Opcode 314 (Spell: Golem Stoneskin) : crée parameter1 peaux de golem, protections contre les attaques
// physiques (IESDP), décrites par les phrases de l'opcode 218 (ancien opcode_218_common : « Crée 5 peaux de
// golem ») ; code commun dans new-lib/opcodes/states.tpp.

// Aucune peau : écartée et journalisée (l'ancien moteur écrit « Crée 0 peaux de pierre »).
DEFINE_PATCH_MACRO ad_op_314_support BEGIN
	PHP_EACH fx_ids_314 AS _ => skin_id BEGIN
		PATCH_IF NOT $fx_dropped(~%skin_id%~) AND $fx_parameter1(~%skin_id%~) <= 0 BEGIN
			SET drop_id = skin_id
			SPRINT ignored_reason ~file_error:opcode314:invalid~
			SPRINT ignored_message ~number of skins of 0 or less~
			LPM ad_application_drop
		END
	END
END

DEFINE_PATCH_MACRO ad_op_314_lines BEGIN
	SET state_opcode = 314
	SPRINT state_variant_macro ~ad_op_314_amount~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_314_amount BEGIN
	SET value = $fx_parameter1(~%line_fx%~)
	PATCH_IF value == 1 BEGIN
		SPRINT valueType @23140001 // ~peau de golem~
	END
	ELSE BEGIN
		SPRINT valueType @23140002 // ~peaux de golem~
	END
	SPRINT amount @22180000 // ~%value% %valueType%~
END
