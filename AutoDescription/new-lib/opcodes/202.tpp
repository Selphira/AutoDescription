// Opcode 202 (Spell: Bounce (by School)) : renvoie les sorts de l'école de magie parameter2, nommée par
// son complément (liste @8150000, ancien get_spell_school) : « Renvoie les sorts de l'école de
// l'Illusion » ; code commun dans new-lib/opcodes/states.tpp. L'ancien moteur n'a de phrase que pour
// les effets sur soi : une autre cible est refusée (phrase absente).

// École 0 (aucune) : pas de ligne, l'ancien moteur n'ayant pas de nom à écrire, journalisé ; école hors
// de 0-10 : écartée et journalisée.
DEFINE_PATCH_MACRO ad_op_202_support BEGIN
	PHP_EACH fx_ids_202 AS _ => bounce_id BEGIN
		SET bounce_school = $fx_parameter2(~%bounce_id%~)
		SPRINT $fx_school_name(~%bounce_id%~) ~~
		PATCH_IF NOT $fx_dropped(~%bounce_id%~) AND (bounce_school < 0 OR bounce_school > 10) BEGIN
			SET drop_id = bounce_id
			SPRINT ignored_reason ~file_error:opcode202:invalid~
			SPRINT ignored_message ~school %bounce_school% (parameter2) outside 0-10~
			LPM ad_application_drop
		END
		ELSE PATCH_IF bounce_school == 0 AND NOT $fx_dropped(~%bounce_id%~) AND NOT support_header_only BEGIN
			SET ignored_fx = bounce_id
			SPRINT ignored_reason ~not_implemented:opcode202:no_school~
			SPRINT ignored_message ~school 0 (parameter2) has no name~
			LPM ad_log_ignored
		END
		ELSE PATCH_IF bounce_school > 0 AND bounce_school <= 10 BEGIN
			LPF ad_tra INT_VAR tra_id = 8150000 + bounce_school tra_block_start = 8150000 tra_block_size = 11 RET bounce_name = text END // ~de l'Illusion~ (@8150005)
			SPRINT $fx_school_name(~%bounce_id%~) ~%bounce_name%~
		END
	END
END

DEFINE_PATCH_MACRO ad_op_202_lines BEGIN
	PHP_EACH fx_ids_202 AS _ => bounce_id BEGIN
		PATCH_IF $fx_parameter2(~%bounce_id%~) == 0 BEGIN
			SET $fx_consumed(~%bounce_id%~) = 1
		END
	END
	SET state_opcode = 202
	SPRINT state_variant_macro ~ad_op_202_name~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_202_name BEGIN
	SPRINT spellSchoolName $fx_school_name(~%line_fx%~)
END
