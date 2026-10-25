// Opcode 252 (Spell Effect: Set Trap) : pose le sort resource comme piège (IESDP : réussite selon le
// talent, échec critique lançant resource + F) : « Tente de poser un piège « Glyphe de garde » » pour un
// sort nommé (fx_trap_spell) ; sinon « Tente de poser un piège : » suivi des effets du sort, décrits par
// leurs propres cibles, sans niveau de lancement (ancien opcode_252_common) ; code commun dans
// new-lib/recursion.tpp.

// Refus : ressource vide (écartée par l'ancien opcode_resref_is_valid) ; refus de la sous-description
// (ad_recursion_support).
DEFINE_PATCH_MACRO ad_op_252_support BEGIN
	PHP_EACH fx_ids_252 AS _ => heading_id BEGIN
		SET $fx_sub_count(~%heading_id%~) = 0
		SPRINT $fx_trap_spell(~%heading_id%~) ~~
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%heading_id%~) BEGIN
			SPRINT heading_resref $fx_resource_lower(~%heading_id%~)
			LPF ad_spell_name STR_VAR resref = ~%heading_resref%~ RET heading_spell = name END
			SPRINT $fx_trap_spell(~%heading_id%~) ~%heading_spell%~
			PATCH_IF ~%heading_resref%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = heading_id STR_VAR reason = ~file_error:opcode252:invalid~ message = ~empty resource field~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ~%heading_spell%~ STRING_EQUAL ~~ BEGIN
				SET recursion_fx = heading_id
				SPRINT recursion_resref ~%heading_resref%~
				SET recursion_casting_level = 0
				SPRINT recursion_targets ~own~
				SET recursion_ignore_duration = 0
				SET recursion_series = 0
				SET recursion_depth_reset = 0
				SPRINT recursion_kind ~spl~
				SET recursion_parent_dice = 0
				SET recursion_versus_set = 0
				SPRINT recursion_versus ~~
				SPRINT recursion_single_reason ~~
				LPM ad_recursion_support
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_252_lines BEGIN
	SET heading_opcode = 252
	SET heading_tra = 22520000 // ~Tente de poser un piège~
	LPM ad_recursion_heading_lines
	PHP_EACH fx_ids_252 AS _ => trap_id BEGIN
		SPRINT spellName $fx_trap_spell(~%trap_id%~)
		PATCH_IF NOT $fx_consumed(~%trap_id%~) AND NOT (~%spellName%~ STRING_EQUAL ~~) BEGIN
			SET line_fx = trap_id
			SET line_phrase = 22520100 // ~Tente de poser un piège « %spellName% »~
			LPM ad_effect_line
		END
	END
END
