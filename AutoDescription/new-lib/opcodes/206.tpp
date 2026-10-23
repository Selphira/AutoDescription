// Opcode 206 (Spell: Protection from Spell) : immunité au sort resource, « Immunité au sort
// « Lent » » ; nom du sort par ad_spell_name (new-lib/resources.tpp), sans ligne si le nom est
// vide. Une immunité à l'opcode que le sort inflige peut l'absorber (ad_group_immunities,
// new-lib/groups.tpp).
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp). Avec AD_ENABLE_SHRINKAGE, cinq protections psioniques d'un bloc
// deviennent « Immunité aux capacités psioniques » (ad_group_psionic_immunity, new-lib/groups.tpp).

// Refus : effet sans ressource ; dans un en-tête, avec la ligne unique des immunités, immunité aux
// capacités psioniques dont les champs (ceux de la cinquième protection) diffèrent de ceux d'une
// autre immunité de l'en-tête, parameter2 mis à part (ad_op_101_ability_support).
DEFINE_PATCH_MACRO ad_op_206_support BEGIN
	PHP_EACH fx_ids_206 AS _ => spell_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SPRINT spell_resref $fx_resource(~%spell_id%~)
			TO_UPPER spell_resref
			// L'ancien moteur écarte un effet sans ressource (erreur journalisée).
			PATCH_IF ~%spell_resref%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = spell_id STR_VAR reason = ~file_error:opcode206:invalid~ message = ~empty resource field~ RET render_missing = refusal END
			END
			// Sort absent ou sans nom : pas de ligne (ad_op_206_lines), comme dans l'ancien moteur.
			ELSE BEGIN
				LPF ad_spell_name STR_VAR resref = ~%spell_resref%~ RET spell_support_name = name END
				PATCH_IF ~%spell_support_name%~ STRING_EQUAL ~~ BEGIN
					SET ignored_fx = spell_id
					SPRINT ignored_reason ~not_implemented:opcode206:no_name~
					SPRINT ignored_message ~spell %spell_resref%.SPL has no name~
					PATCH_IF NOT FILE_EXISTS_IN_GAME ~%spell_resref%.spl~ BEGIN
						SPRINT ignored_reason ~file_error:opcode206:missing_spell~
						SPRINT ignored_message ~spell %spell_resref%.SPL does not exist~
					END
					LPM ad_log_ignored
				END
			END
		END
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_IMMUNITIES_SINGLE_LINE BEGIN
		LPM ad_op_206_psionic_support
	END
END

// Cinquième protection psionique de chaque en-tête qui en a au moins cinq : mêmes champs que les
// immunités (101) de l'en-tête.
DEFINE_PATCH_MACRO ad_op_206_psionic_support BEGIN
	CLEAR_ARRAY spell_psionic_count
	FOR (spell_id = 0; spell_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++spell_id) BEGIN
		SPRINT spell_scope $fx_scope(~%spell_id%~)
		SPRINT spell_resref $fx_resource(~%spell_id%~)
		TO_UPPER spell_resref
		PATCH_IF $fx_opcode(~%spell_id%~) == 206 AND VARIABLE_IS_SET $AD_IMMUNITY_SPELLS(~505 %spell_resref%~)
				AND NOT (~%spell_scope%~ STRING_EQUAL ~equipped~) BEGIN
			SET spell_psionic_total = VARIABLE_IS_SET $spell_psionic_count(~%spell_scope%~) ? $spell_psionic_count(~%spell_scope%~) + 1 : 1
			SET $spell_psionic_count(~%spell_scope%~) = spell_psionic_total
			PATCH_IF spell_psionic_total == 5 BEGIN
				SET same_id = spell_id
				SET same_ignored = AD_SAME_PARAMETER2
				PHP_EACH fx_ids_101 AS _ => spell_other BEGIN
					SPRINT spell_other_scope $fx_scope(~%spell_other%~)
					PATCH_IF (~%spell_other_scope%~ STRING_EQUAL ~%spell_scope%~) BEGIN
						SET same_other = spell_other
						LPM ad_fx_same_fields
						PATCH_IF NOT fx_same BEGIN
							LPF ad_refusal INT_VAR fx_id = spell_other STR_VAR reason = ~not_implemented:opcode206:psionic_fields~ message = ~psionic protections and immunities of the ability with different fields~ RET render_missing = refusal END
						END
					END
				END
			END
		END
	END
END

// Lignes (ancien opcode_self_206 et opcode_206_post_group) : avec AD_ENABLE_SHRINKAGE, les
// immunités d'une même cible et d'une même portée (l'ancien moteur décrit chaque bloc à part) à au
// moins deux sorts de noms différents sont réunies en une ligne
// (effet dérivé SPELL_IMMUNITIES), noms triés ; les lignes réunies viennent après les autres.
DEFINE_PATCH_MACRO ad_op_206_lines BEGIN
	SPRINT line_section ~equipped~
	FOR (spell_id = 0; spell_id < fx_count; ++spell_id) BEGIN
		SET $spell_group(~%spell_id%~) = 0 - 1
		PATCH_IF $fx_opcode(~%spell_id%~) == 206 AND NOT $fx_consumed(~%spell_id%~) BEGIN
			SPRINT spell_resref $fx_resource(~%spell_id%~)
			LPF ad_spell_name STR_VAR resref = ~%spell_resref%~ RET spell_name = name END
			SPRINT $spell_name(~%spell_id%~) ~%spell_name%~
		END
	END
	SET spell_group_count = 0
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		PHP_EACH fx_ids_206 AS _ => spell_id BEGIN
			PATCH_IF NOT $fx_consumed(~%spell_id%~) AND $spell_group(~%spell_id%~) < 0 BEGIN
				SET spell_target = $fx_effective_target(~%spell_id%~)
				SPRINT spell_scope $fx_scope(~%spell_id%~)
				SET spell_name_count = 0
				PHP_EACH fx_ids_206 AS _ => spell_other BEGIN
					SPRINT spell_other_scope $fx_scope(~%spell_other%~)
					PATCH_IF spell_other >= spell_id AND NOT $fx_consumed(~%spell_other%~) AND $spell_group(~%spell_other%~) < 0 AND $fx_effective_target(~%spell_other%~) == spell_target AND (~%spell_other_scope%~ STRING_EQUAL ~%spell_scope%~) BEGIN
						SPRINT spell_name $spell_name(~%spell_other%~)
						PATCH_IF NOT ~%spell_name%~ STRING_EQUAL ~~ BEGIN
							SET spell_name_new = 1
							FOR (spell_member = spell_id; spell_member < spell_other; ++spell_member) BEGIN
								PATCH_IF $spell_group(~%spell_member%~) == spell_group_count BEGIN
									SPRINT spell_member_name $spell_name(~%spell_member%~)
									PATCH_IF ~%spell_member_name%~ STRING_EQUAL ~%spell_name%~ BEGIN
										SET spell_name_new = 0
									END
								END
							END
							SET $spell_group(~%spell_other%~) = spell_group_count
							SET spell_name_count += spell_name_new
						END
					END
				END
				SET $spell_group_size(~%spell_group_count%~) = spell_name_count
				SET spell_group_count += 1
			END
		END
	END
	SET line_sort = $AD_OPCODE_SORT(~206~)
	PHP_EACH fx_ids_206 AS _ => spell_id BEGIN
		PATCH_IF NOT $fx_consumed(~%spell_id%~) BEGIN
			SET spell_group_id = $spell_group(~%spell_id%~)
			SPRINT spellName $spell_name(~%spell_id%~)
			PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND (spell_group_id < 0 OR $spell_group_size(~%spell_group_id%~) < 2) BEGIN
				SET line_phrase = 22060100 // ~Immunité au sort « %spellName% »~
				SET line_fx = spell_id
				LPM ad_effect_line
			END
		END
	END
	SET line_sort = $AD_DERIVED_SORT(~SPELL_IMMUNITIES~)
	FOR (spell_group_id = 0; spell_group_id < spell_group_count; ++spell_group_id) BEGIN
		PATCH_IF $spell_group_size(~%spell_group_id%~) >= 2 BEGIN
			CLEAR_ARRAY spell_group_names
			SET spell_first = 0 - 1
			PHP_EACH fx_ids_206 AS _ => spell_id BEGIN
				PATCH_IF NOT $fx_consumed(~%spell_id%~) AND $spell_group(~%spell_id%~) == spell_group_id BEGIN
					SPRINT spell_name $spell_name(~%spell_id%~)
					SPRINT $spell_group_names(~%spell_name%~) ~%spell_name%~
					PATCH_IF spell_first < 0 BEGIN
						SET spell_first = spell_id
					END
				END
			END
			SORT_ARRAY_INDICES spell_group_names
			SPRINT and ~%AD_AND%~
			SPRINT spell_glue @1000005 // ~ », « ~
			SPRINT spell_final_glue @1000006 // ~ » %and% « ~
			LPF ad_join STR_VAR array_name = ~spell_group_names~ glue = ~%spell_glue%~ final_glue = ~%spell_final_glue%~ RET spellNames = text END
			SET line_phrase = 30100100 // ~Immunité aux sorts « %spellNames% »~
			SET line_fx = spell_first
			LPM ad_effect_line
		END
	END
END
