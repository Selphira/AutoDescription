// Code commun des sorts lancés à chaque événement d'un combat (opcodes 340, attaque sournoise ; 341,
// coup critique ; 361, échec critique ; ancien opcode_341_common) : sort resource lancé à chaque
// événement, de toute arme (parameter2 0) ou de cette arme (parameter2 1, 341 et 361) : « À chaque coup
// critique provoqué avec cette arme ; Inflige 2d4 points de dégâts de froid à la cible ». Le sort est
// toujours décrit par ses effets (new-lib/recursion.tpp), chacun avec ses propres cibles, sans limite
// de profondeur comme pour l'opcode 232 (recursion_depth_reset). L'opcode fixe event_opcode,
// event_weapon (1 : parameter2 et special lus, IESDP ; le 340 ne les lit pas) et, pour ses lignes,
// event_condition_tra (condition de toute arme, suivie de celle de cette arme à + 2).

// Refus : effet d'un EFF (l'ancien moteur y lit parameter3, la catégorie d'arme) ; ressource vide ;
// parameter2 hors de 0-1 ; special non nul (type d'attaque, « en mêlée ») ; effet sur une cible (« À
// chaque coup critique de la cible ») ; refus de ad_recursion_support.
DEFINE_PATCH_MACRO ad_event_spell_support BEGIN
	PHP_EACH ~fx_ids_%event_opcode%~ AS _ => event_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%event_id%~) BEGIN
			SPRINT event_resref $fx_resource_lower(~%event_id%~)
			SET event_target = $fx_effective_target(~%event_id%~)
			PATCH_IF $fx_external(~%event_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = event_id STR_VAR reason = ~not_implemented:opcode%event_opcode%:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ~%event_resref%~ STRING_EQUAL ~~ OR (event_weapon AND ($fx_parameter2(~%event_id%~) < 0 OR $fx_parameter2(~%event_id%~) > 1)) BEGIN
				LPF ad_refusal INT_VAR fx_id = event_id STR_VAR reason = ~file_error:opcode%event_opcode%:invalid~ message = ~empty resource field or parameter2 outside 0-1~ RET render_missing = refusal END
			END
			ELSE PATCH_IF event_weapon AND $fx_special(~%event_id%~) != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = event_id STR_VAR reason = ~not_implemented:opcode%event_opcode%:attack_type~ message = ~attack type (special) other than 0~ RET render_missing = refusal END
			END
			ELSE PATCH_IF event_target != TARGET_FX_self AND event_target != TARGET_FX_original_caster BEGIN
				LPF ad_refusal INT_VAR fx_id = event_id STR_VAR reason = ~not_implemented:opcode%event_opcode%:target~ message = ~target other than self~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET recursion_fx = event_id
				SPRINT recursion_resref ~%event_resref%~
				SET recursion_casting_level = 0
				SPRINT recursion_targets ~own~
				SET recursion_ignore_duration = 0
				SET recursion_series = 0
				SET recursion_depth_reset = 1
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

// Une ligne par effet dont le sous-sort en a.
DEFINE_PATCH_MACRO ad_event_spell_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%event_opcode%~)
	PHP_EACH ~fx_ids_%event_opcode%~ AS _ => event_id BEGIN
		PATCH_IF NOT $fx_consumed(~%event_id%~) AND $fx_sub_count(~%event_id%~) > 0 BEGIN
			SET recursion_fx = event_id
			LPM ad_recursion_condition_text
			SET event_condition = event_condition_tra + (event_weapon AND $fx_parameter2(~%event_id%~) != 0 ? 2 : 0)
			LPF ad_tra INT_VAR tra_id = event_condition RET line_condition = text END // ~À chaque coup critique~
			SET line_any_form = 1
			SET line_fx = event_id
			LPM ad_effect_line
		END
	END
END
