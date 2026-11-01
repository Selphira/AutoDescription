// Opcode 199 (Spell: Bounce (by Power Level)) : renvoie les effets dont la puissance (power) vaut
// parameter1 (IESDP : 0 à 9) : « Renvoie les sorts de niveau 2 » ; code commun dans
// new-lib/opcodes/states.tpp. À la forme « cible », l'ancien moteur n'écrit rien (sa macro porte un
// autre nom) : la phrase qu'il prévoyait pour cette forme est reprise (« … ciblant la cible »).

// Puissance hors de 0-9 : écartée et journalisée (ancien opcode_199_is_valid).
DEFINE_PATCH_MACRO ad_op_199_support BEGIN
	PHP_EACH fx_ids_199 AS _ => bounce_id BEGIN
		SET bounce_level = $fx_parameter1(~%bounce_id%~)
		PATCH_IF NOT $fx_dropped(~%bounce_id%~) AND (bounce_level < 0 OR bounce_level > 9) BEGIN
			SET drop_id = bounce_id
			SPRINT ignored_reason ~file_error:opcode199:level~
			SPRINT ignored_message ~power level %bounce_level% (expected 0-9)~
			LPM ad_application_drop
		END
	END
END

DEFINE_PATCH_MACRO ad_op_199_lines BEGIN
	SET state_opcode = 199
	SPRINT state_variant_macro ~ad_op_199_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_199_variant BEGIN
	SET spellLevel = $fx_parameter1(~%line_fx%~)
END
