// Opcode 341 (Spell Effect: Change Critical Hit Effect, EE) : sort resource lancé à chaque coup
// critique, de toute arme (parameter2 0) ou de cette arme (ancien opcode_341_common) : « À chaque coup
// critique provoqué avec cette arme ; Inflige 2d4 points de dégâts de froid à la cible ». Le sort est
// toujours décrit par ses effets (new-lib/recursion.tpp), chacun avec ses propres cibles.

// Refus : effet d'un EFF (l'ancien moteur y lit parameter3, la catégorie d'arme) ; ressource vide ;
// parameter2 hors de 0-1 ; special non nul (type d'attaque, « en mêlée ») ; effet sur une cible (« À
// chaque coup critique de la cible ») ; effet d'un sous-sort (l'ancien moteur n'y limite pas la
// profondeur) ; refus de ad_recursion_support.
DEFINE_PATCH_MACRO ad_op_341_support BEGIN
	FOR (critical_id = 0; critical_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++critical_id) BEGIN
		PATCH_IF $fx_opcode(~%critical_id%~) == 341 AND NOT $fx_consumed(~%critical_id%~) BEGIN
			SPRINT critical_resref $fx_resource_lower(~%critical_id%~)
			SET critical_target = $fx_effective_target(~%critical_id%~)
			PATCH_IF $fx_external(~%critical_id%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode341:external~
			END
			ELSE PATCH_IF ~%critical_resref%~ STRING_EQUAL ~~ OR $fx_parameter2(~%critical_id%~) < 0 OR $fx_parameter2(~%critical_id%~) > 1 BEGIN
				SPRINT render_missing ~not_implemented:opcode341:invalid~
			END
			ELSE PATCH_IF $fx_special(~%critical_id%~) != 0 BEGIN
				SPRINT render_missing ~not_implemented:opcode341:attack_type~
			END
			ELSE PATCH_IF critical_target != TARGET_FX_self AND critical_target != TARGET_FX_original_caster BEGIN
				SPRINT render_missing ~not_implemented:opcode341:target~
			END
			ELSE PATCH_IF ctx_depth > 0 BEGIN
				SPRINT render_missing ~not_implemented:recursion:nested_condition~
			END
			ELSE BEGIN
				SET recursion_fx = critical_id
				SPRINT recursion_resref ~%critical_resref%~
				SET recursion_casting_level = 0
				SPRINT recursion_targets ~own~
				SET recursion_ignore_duration = 0
				SET recursion_series = 0
				SET recursion_tracked = 0
				SPRINT recursion_kind ~spl~
				SET recursion_parent_dice = 0
				SET recursion_versus_set = 0
				SPRINT recursion_versus ~~
				LPM ad_recursion_support
			END
		END
	END
END

// Une ligne par effet dont le sous-sort en a.
DEFINE_PATCH_MACRO ad_op_341_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~341~)
	FOR (critical_id = 0; critical_id < fx_count; ++critical_id) BEGIN
		PATCH_IF $fx_opcode(~%critical_id%~) == 341 AND NOT $fx_consumed(~%critical_id%~) AND $fx_sub_count(~%critical_id%~) > 0 BEGIN
			SET recursion_fx = critical_id
			LPM ad_recursion_condition_text
			PATCH_IF $fx_parameter2(~%critical_id%~) == 0 BEGIN
				SPRINT line_condition @23410001 // ~À chaque coup critique~
			END
			ELSE BEGIN
				SPRINT line_condition @23410003 // ~À chaque coup critique provoqué avec cette arme~
			END
			SET line_any_form = 1
			SET line_fx = critical_id
			LPM ad_effect_line
		END
	END
END
