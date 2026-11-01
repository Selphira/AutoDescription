// Opcode 333 (Spell Effect: Static Charge, EE) : lance parameter1 fois le sort resource (à défaut,
// <ressource>B), une fois toutes les special secondes (6, un round, sans valeur) ; parameter2 = niveau
// de lancement, 0 : niveau 1, les dégâts du sort prenant alors les dés de l'effet (IESDP). L'effet
// dure donc parameter1 × special secondes, durée qui compte pour l'en-tête d'un sort (« Durée : 1
// tour par niveau du lanceur/30 »). Écrit comme une répétition : sort nommé, « Lance le sort
// « Projectile magique » chaque round pendant 3 rounds » ; sinon ses effets, chacun suivi de la
// fréquence (ctx_frequency, new-lib/recursion.tpp) : « Inflige 9d8 points de dégâts d'électricité à la
// cible chaque tour pendant 7 tours (jet de sauvegarde contre les sorts pour réduire de moitié) ».

// Nombre nul ou négatif : écarté et journalisé (ancien opcode_333_is_valid).
// Refus : effet différé ou de durée limitée (la fin de l'effet et celle des décharges ne sont pas
// établies) ; jet de sauvegarde (IESDP : tenté à chaque décharge, qui met fin à l'effet) ; sort qui
// contient lui-même un 333 ; refus de ad_recursion_support.
DEFINE_PATCH_MACRO ad_op_333_support BEGIN
	PHP_EACH fx_ids_333 AS _ => charge_id BEGIN
		SET charge_count = $fx_parameter1(~%charge_id%~)
		SET charge_timing = $fx_timing(~%charge_id%~)
		SET charge_delay = $fx_special(~%charge_id%~) > 0 ? $fx_special(~%charge_id%~) : 6
		SPRINT charge_resref $fx_resource_lower(~%charge_id%~)
		PATCH_IF ~%charge_resref%~ STRING_EQUAL ~~ AND STRING_LENGTH ~%ctx_resource%~ <= 7 BEGIN
			SPRINT charge_resref ~%ctx_resource%B~
			TO_LOWER charge_resref
		END
		PATCH_IF NOT $fx_dropped(~%charge_id%~) AND charge_count <= 0 BEGIN
			SET drop_id = charge_id
			SPRINT ignored_reason ~file_error:opcode333:invalid~
			SPRINT ignored_message ~number of strikes %charge_count%~
			LPM ad_application_drop
		END
		ELSE PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_dropped(~%charge_id%~) BEGIN
			// Timing déjà réécrit par une passe précédente (en-tête d'un sort) : durée des décharges.
			PATCH_IF NOT $fx_charge_rewritten(~%charge_id%~) BEGIN
				SET charge_duration = $fx_duration(~%charge_id%~)
				PATCH_IF NOT (charge_timing == TIMING_permanent OR (charge_timing == TIMING_delayed AND charge_duration == 0)) BEGIN
					LPF ad_refusal INT_VAR fx_id = charge_id STR_VAR reason = ~not_implemented:opcode333:timing~ message = ~timing %charge_timing%, duration %charge_duration% (only permanent or delayed by 0 seconds)~ RET render_missing = refusal END
				END
				ELSE BEGIN
					SET $fx_timing(~%charge_id%~) = TIMING_duration
					SET $fx_duration(~%charge_id%~) = charge_count * charge_delay
					SET $fx_charge_rewritten(~%charge_id%~) = 1
				END
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND $fx_save_type(~%charge_id%~) != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = charge_id STR_VAR reason = ~not_implemented:opcode333:save~ message = ~saving throw attempted at each strike~ RET render_missing = refusal END
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT support_header_only BEGIN
				LPF ad_spell_name STR_VAR resref = ~%charge_resref%~ RET charge_name = name END
				SPRINT $fx_charge_name(~%charge_id%~) ~%charge_name%~
				LPF ad_duration_text INT_VAR seconds = charge_delay tra_base = 3020000 RET charge_frequency = text END // ~chaque round~
				SPRINT $fx_charge_frequency(~%charge_id%~) ~%charge_frequency%~
				PATCH_IF ~%charge_name%~ STRING_EQUAL ~~ BEGIN
					LPM ad_op_333_nested
					PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
						SET recursion_fx = charge_id
						SPRINT recursion_resref ~%charge_resref%~
						SET recursion_casting_level = $fx_parameter2(~%charge_id%~) > 0 ? $fx_parameter2(~%charge_id%~) : 1
						// Le sort part de la cible de l'effet (IESDP) : ses effets en reprennent les chaînes.
						SPRINT recursion_targets ~effect~
						SET recursion_ignore_duration = 0
						SET recursion_series = 0
						SET recursion_depth_reset = 0
						SPRINT recursion_kind ~spl~
						SET recursion_parent_dice = 0
						SET recursion_versus_set = 0
						SPRINT recursion_versus ~~
						SPRINT recursion_single_reason ~~
						SPRINT recursion_frequency ~%charge_frequency%~
						SET recursion_inherit_dice = $fx_parameter2(~%charge_id%~) == 0
						LPM ad_recursion_support
					END
				END
			END
		END
	END
END

// Refus d'un sort charge_resref qui contient lui-même un 333 (décharges imbriquées).
DEFINE_PATCH_MACRO ad_op_333_nested BEGIN
	SET charge_nested = 0
	PATCH_IF FILE_EXISTS_IN_GAME ~%charge_resref%.spl~ BEGIN
		INNER_PATCH_FILE ~%charge_resref%.spl~ BEGIN
			PATCH_IF BUFFER_LENGTH >= 0x72 BEGIN
				READ_LONG SPL_feature_blocks_offset charge_blocks_offset
				FOR (charge_at = charge_blocks_offset; charge_at + 0x30 <= BUFFER_LENGTH; charge_at += 0x30) BEGIN
					READ_SHORT charge_at charge_opcode
					SET charge_nested = charge_nested OR charge_opcode == 333
				END
			END
		END
	END
	PATCH_IF charge_nested BEGIN
		LPF ad_refusal INT_VAR fx_id = charge_id STR_VAR reason = ~not_implemented:opcode333:nested~ message = ~spell %charge_resref% casting itself strikes (opcode 333)~ RET render_missing = refusal END
	END
END

// Sort nommé : 2333 0100 + forme, la fréquence dans la phrase, la durée après. Sinon, les lignes du
// sort, qui écrivent la fréquence et la durée.
DEFINE_PATCH_MACRO ad_op_333_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~333~)
	PHP_EACH fx_ids_333 AS _ => charge_id BEGIN
		PATCH_IF NOT $fx_consumed(~%charge_id%~) BEGIN
			SET line_fx = charge_id
			SPRINT spellName $fx_charge_name(~%charge_id%~)
			PATCH_IF NOT (~%spellName%~ STRING_EQUAL ~~) BEGIN
				SPRINT frequency $fx_charge_frequency(~%charge_id%~)
				SET line_phrase = 23330100 // ~Lance le sort « %spellName% » %frequency%~
				LPM ad_effect_line
			END
			ELSE PATCH_IF $fx_sub_count(~%charge_id%~) > 0 BEGIN
				SPRINT line_text $fx_sub_text(~%charge_id%~)
				SET line_any_form = 1
				SET line_no_duration = 1
				LPM ad_effect_line
			END
		END
	END
END
