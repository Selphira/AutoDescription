// Opcode 266 (Spell: Remove Protection from Spell) : retire les immunités 206 au sort resource (IESDP) :
// « Lève l'immunité contre le sort « Brise-Magie » » ; code commun dans new-lib/opcodes/states.tpp.

// Ressource vide : écartée et journalisée (ancien opcode_resref_is_valid) ; sort sans nom : aucune
// ligne, comme l'ancien moteur, journalisé ; l'effet compte encore pour l'en-tête.
DEFINE_PATCH_MACRO ad_op_266_support BEGIN
	PHP_EACH fx_ids_266 AS _ => unprotect_id BEGIN
		SPRINT unprotect_resref $fx_resource(~%unprotect_id%~)
		SPRINT unprotect_name ~~
		PATCH_IF NOT (~%unprotect_resref%~ STRING_EQUAL ~~) AND NOT support_header_only BEGIN
			LPF ad_spell_name STR_VAR resref = ~%unprotect_resref%~ RET unprotect_name = name END
		END
		SPRINT $fx_unprotect_name(~%unprotect_id%~) ~%unprotect_name%~
		PATCH_IF NOT $fx_dropped(~%unprotect_id%~) AND ~%unprotect_resref%~ STRING_EQUAL ~~ BEGIN
			SET drop_id = unprotect_id
			SPRINT ignored_reason ~file_error:opcode266:invalid~
			SPRINT ignored_message ~empty resource field~
			LPM ad_application_drop
		END
		ELSE PATCH_IF NOT $fx_dropped(~%unprotect_id%~) AND ~%unprotect_name%~ STRING_EQUAL ~~ AND NOT support_header_only BEGIN
			SET ignored_fx = unprotect_id
			SPRINT ignored_reason ~not_implemented:opcode266:no_name~
			SPRINT ignored_message ~spell %unprotect_resref%.SPL has no name~
			LPM ad_log_ignored
		END
	END
END

DEFINE_PATCH_MACRO ad_op_266_lines BEGIN
	PHP_EACH fx_ids_266 AS _ => unprotect_id BEGIN
		SPRINT unprotect_name $fx_unprotect_name(~%unprotect_id%~)
		PATCH_IF ~%unprotect_name%~ STRING_EQUAL ~~ BEGIN
			SET $fx_consumed(~%unprotect_id%~) = 1
		END
	END
	SET state_opcode = 266
	SPRINT state_variant_macro ~ad_op_266_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_266_variant BEGIN
	SPRINT spellName $fx_unprotect_name(~%line_fx%~)
END
