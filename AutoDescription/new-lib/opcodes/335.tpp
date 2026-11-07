// Opcode 335 (Spell Effect: Seven Eyes, EE) : pose l'état de sort parameter1 s'il ne l'est pas déjà
// (sinon l'effet n'est pas appliqué : « non cumulatif ») et accorde le sort resource comme un 171,
// jusqu'au premier effet bloqué de la ligne parameter2 de 7EYES.2DA (IESDP) : « Affecte le porteur par
// … et lui apprend le sort « … » (non cumulatif) » (ancien opcode_target_335) ; code commun dans
// new-lib/opcodes/states.tpp.

// État de sort hors de 0-255 : écarté (erreur de fichier) ; sans nom (état ajouté par un mod, comme
// D5_SNAREARROW de BRAC18) : pas de ligne, journalisé, l'ancien moteur n'en écrivant plus rien.
// Refus : sort accordé sans nom.
DEFINE_PATCH_MACRO ad_op_335_support BEGIN
	PHP_EACH fx_ids_335 AS _ => eyes_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%eyes_id%~) BEGIN
			SET eyes_splstate = $fx_parameter1(~%eyes_id%~)
			SET eyes_tra = 8120000 + eyes_splstate
			SPRINT eyes_resref $fx_resource(~%eyes_id%~)
			SPRINT $fx_spell_name(~%eyes_id%~) ~~
			PATCH_IF eyes_splstate < 0 OR eyes_splstate > 255 BEGIN
				SET drop_id = eyes_id
				SPRINT ignored_reason ~file_error:opcode335:splstate~
				SPRINT ignored_message ~spell state %eyes_splstate% (expected 0-255)~
				LPM ad_application_drop
			END
			// Pas de ligne (ad_op_335_lines), mais l'effet reste lu pour l'en-tête d'un sort, comme dans
			// l'ancien moteur (« Durée : Spéciale », SPWI201).
			ELSE PATCH_IF NOT TRA_ENTRY_EXISTS (~%eyes_tra%~) BEGIN
				PATCH_IF NOT support_header_only BEGIN
					SET ignored_fx = eyes_id
					SPRINT ignored_reason ~not_implemented:opcode335:no_name~
					SPRINT ignored_message ~spell state %eyes_splstate% has no name~
					LPM ad_log_ignored
				END
			END
			ELSE PATCH_IF TRA_ENTRY_EXISTS (~%eyes_tra%~) AND NOT (~%eyes_resref%~ STRING_EQUAL ~~) AND NOT support_header_only BEGIN
				LPF ad_spell_name STR_VAR resref = ~%eyes_resref%~ RET eyes_spell_name = name END
				SPRINT $fx_spell_name(~%eyes_id%~) ~%eyes_spell_name%~
				PATCH_IF ~%eyes_spell_name%~ STRING_EQUAL ~~ BEGIN
					LPF ad_refusal INT_VAR fx_id = eyes_id STR_VAR reason = ~not_implemented:opcode335:spell_no_name~ message = ~spell %eyes_resref%.SPL granted by the effect has no name~ RET render_missing = refusal END
				END
			END
		END
	END
END

// Comme ad_state_lines (new-lib/opcodes/states.tpp), sans les effets dont l'état de sort n'a pas de nom.
DEFINE_PATCH_MACRO ad_op_335_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~335~)
	FOR (eyes_late = 0; eyes_late <= 2; ++eyes_late) BEGIN
		PHP_EACH fx_ids_335 AS _ => eyes_id BEGIN
			SET eyes_tra = 8120000 + $fx_parameter1(~%eyes_id%~)
			PATCH_IF NOT $fx_consumed(~%eyes_id%~) AND $fx_late(~%eyes_id%~) == eyes_late AND TRA_ENTRY_EXISTS (~%eyes_tra%~) BEGIN
				SET line_fx = eyes_id
				LPM ad_op_335_variant
				SET line_phrase = 23350100 + 10 * state_variant
				LPM ad_effect_line
			END
		END
	END
END

// Variante 1 : sort accordé (spellName).
DEFINE_PATCH_MACRO ad_op_335_variant BEGIN
	SET eyes_tra = 8120000 + $fx_parameter1(~%line_fx%~)
	LPF ad_tra INT_VAR tra_id = eyes_tra tra_block_start = 8120000 tra_block_size = 256 RET splstate = text END // ~la folie du berserker~ (@8120104)
	SPRINT spellName $fx_spell_name(~%line_fx%~)
	SET state_variant = (~%spellName%~ STRING_EQUAL ~~) ? 0 : 1
	SPRINT line_suffix @4000010 // ~non cumulatif~
	SPRINT line_suffix ~(%line_suffix%)~
END
