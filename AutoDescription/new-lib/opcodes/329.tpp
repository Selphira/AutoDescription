// Opcode 329 (Spell Effect: Slow Poison, EE) : multiplicateur de fréquence parameter1 écrit dans les
// poisons 25 de type 2 et plus (IESDP) : « Abaisse la virulence de la plupart des poisons sur la cible de
// 10 » ; code commun dans new-lib/opcodes/states.tpp.

// Facteur nul : écarté et journalisé (ancien opcode_329_is_valid : le jeu peut planter).
DEFINE_PATCH_MACRO ad_op_329_support BEGIN
	PHP_EACH fx_ids_329 AS _ => slow_id BEGIN
		PATCH_IF NOT $fx_dropped(~%slow_id%~) AND $fx_parameter1(~%slow_id%~) == 0 BEGIN
			SET drop_id = slow_id
			SPRINT ignored_reason ~file_error:opcode329:invalid~
			SPRINT ignored_message ~slow factor of 0 (the game may crash)~
			LPM ad_application_drop
		END
	END
END

DEFINE_PATCH_MACRO ad_op_329_lines BEGIN
	SET state_opcode = 329
	SPRINT state_variant_macro ~ad_op_329_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_329_variant BEGIN
	SET amount = $fx_parameter1(~%line_fx%~)
END
