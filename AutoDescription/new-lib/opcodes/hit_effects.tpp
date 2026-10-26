// Code commun des effets appliqués à chaque attaque réussie (opcodes 248, mêlée, et 249, distance ;
// ancien opcode_248_common) : l'effet du fichier EFF resource est décrit par les passes du moteur
// (new-lib/recursion.tpp, avec ses propres cibles et durées, et les dés de l'effet parent quand ils
// donnent des niveaux), sous la condition « À chaque attaque de mêlée réussie » (« … par la cible »
// pour un effet sur une cible, « … à mains nues » pour parameter2 bit 2 sur EE), suivie de la durée
// de l'effet parent, qui n'est pas répétée en fin de ligne. La ligne prend le rang de l'opcode de l'EFF,
// que l'ancien get_res_description_248 renvoie à la place du sien. Avec AD_ENABLE_SHRINKAGE, un 248 et un 249
// aux mêmes champs, hors parameter1 et parameter2, n'en font qu'un (ancien opcode_248_group, opcode
// 524) : « À chaque attaque réussie ». Les macros ad_op_<N>_* fixent hit_opcode puis appellent les
// macros ci-dessous.

// Ressource vide : effet écarté sans rien écrire, erreur journalisée ; EFF absent : aucune ligne
// (ad_recursion_support). L'EFF
// s'applique à la créature touchée : sa propre cible ne sert pas (ctx_hit_target).
// Refus : effet d'un EFF ; effet probable (l'ancien moteur écrit « par attaque… ») ;
// réunion avec plusieurs effets possibles ou d'un 248 à mains nues (l'ancien moteur y lirait la forme
// « cible ») ; plusieurs lignes ; refus de ad_recursion_support.
DEFINE_PATCH_MACRO ad_hit_effect_support BEGIN
	PHP_EACH ~fx_ids_%hit_opcode%~ AS _ => hit_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%hit_id%~) BEGIN
			SPRINT hit_resref $fx_resource_lower(~%hit_id%~)
			SET $fx_hit_any(~%hit_id%~) = 0
			PATCH_IF $fx_external(~%hit_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = hit_id STR_VAR reason = ~not_implemented:opcode%hit_opcode%:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ~%hit_resref%~ STRING_EQUAL ~~ BEGIN
				SET drop_id = hit_id
				SPRINT ignored_reason ~file_error:opcode%hit_opcode%:invalid~
				SPRINT ignored_message ~empty resource field~
				LPM ad_application_drop
			END
			ELSE PATCH_IF $fx_probability(~%hit_id%~) < 100 BEGIN
				LPF ad_refusal INT_VAR fx_id = hit_id STR_VAR reason = ~not_implemented:opcode%hit_opcode%:probability~ message = ~probable effect~ RET render_missing = refusal END
			END
			ELSE BEGIN
				PATCH_IF hit_opcode == 248 AND AD_ENABLE_SHRINKAGE BEGIN
					LPM ad_hit_effect_group
				END
				PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
					SET recursion_fx = hit_id
					SPRINT recursion_resref ~%hit_resref%~
					SPRINT recursion_kind ~eff~
					SET recursion_parent_dice = 1
					SET recursion_hit_target = 1
					SET recursion_casting_level = 0
					SPRINT recursion_targets ~own~
					SET recursion_ignore_duration = 0
					SET recursion_series = 0
					SET recursion_depth_reset = 0
					SET recursion_versus_set = 0
					SPRINT recursion_versus ~~
					SPRINT recursion_single_reason ~not_implemented:opcode%hit_opcode%:lines~
					SPRINT recursion_single_message ~several lines in the applied EFF file~
					LPM ad_recursion_support
				END
			END
		END
	END
END

// Le 249 de même portée et de mêmes champs que le 248 hit_id, hors parameter1 et parameter2 : consommé,
// et le 248 vaut pour toute attaque (fx_hit_any).
DEFINE_PATCH_MACRO ad_hit_effect_group BEGIN
	SET same_id = hit_id
	SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2
	SPRINT hit_scope $fx_scope(~%hit_id%~)
	SET hit_matches = 0
	FOR (hit_other = 0; hit_other < fx_count; ++hit_other) BEGIN
		SET hit_other_opcode = $fx_opcode(~%hit_other%~)
		SPRINT hit_other_scope $fx_scope(~%hit_other%~)
		PATCH_IF (hit_other_opcode == 248 OR hit_other_opcode == 249) AND hit_other != hit_id AND NOT $fx_consumed(~%hit_other%~)
				AND (~%hit_other_scope%~ STRING_EQUAL ~%hit_scope%~) BEGIN
			SET same_other = hit_other
			LPM ad_fx_same_fields
			SPRINT hit_other_resref $fx_resource_lower(~%hit_other%~)
			PATCH_IF fx_same AND (~%hit_other_resref%~ STRING_EQUAL ~%hit_resref%~) BEGIN
				SET hit_matches += 1
				SET hit_match = hit_other
				SET hit_match_opcode = hit_other_opcode
			END
		END
	END
	PATCH_IF hit_matches > 1 OR (hit_matches == 1 AND hit_match_opcode == 248) BEGIN
		LPF ad_refusal INT_VAR fx_id = hit_id STR_VAR reason = ~not_implemented:opcode248:group~ message = ~on-hit effect grouped with another one~ RET render_missing = refusal END
	END
	ELSE PATCH_IF hit_matches == 1 AND IS_EE AND ($fx_parameter2(~%hit_id%~) BAND BIT2) != 0 BEGIN
		LPF ad_refusal INT_VAR fx_id = hit_id STR_VAR reason = ~not_implemented:opcode248:group_fist~ message = ~on-hit effect of fists grouped with another one~ RET render_missing = refusal END
	END
	ELSE PATCH_IF hit_matches == 1 BEGIN
		SET $fx_consumed(~%hit_match%~) = 1
		SET $fx_hit_any(~%hit_id%~) = 1
	END
END

// Durée de l'effet line_fx écrite après la condition (app_duration_text, ad_application_duration) :
// aucune pour un effet d'équipement, actif tant que l'objet est équipé.
DEFINE_PATCH_MACRO ad_hit_effect_duration BEGIN
	SPRINT app_duration_text ~~
	SPRINT hit_block $fx_block(~%line_fx%~)
	PATCH_IF ~%hit_block%~ STRING_EQUAL ~ability~ BEGIN
		LPM ad_application_duration
	END
END

// Une ligne par effet dont l'EFF en a une. Condition : hit_condition_self (forme « soi ») ou
// hit_condition_target (« … par %theTarget% »), + 1 à mains nues pour l'opcode 248.
DEFINE_PATCH_MACRO ad_hit_effect_lines BEGIN
	SPRINT line_section ~equipped~
	PHP_EACH ~fx_ids_%hit_opcode%~ AS _ => hit_id BEGIN
		PATCH_IF NOT $fx_consumed(~%hit_id%~) AND $fx_sub_count(~%hit_id%~) > 0 BEGIN
			SET hit_sub_opcode = $fx_sub_opcode(~%hit_id%~)
			SET line_sort = $AD_OPCODE_SORT(~%hit_sub_opcode%~)
			SET line_fx = hit_id
			SPRINT line_the_target ~~
			LPM ad_application_form
			LPM ad_application_target_strings
			SPRINT line_only_for ~~
			SET hit_condition_tra = line_form == 0 ? hit_condition_self : hit_condition_target
			PATCH_IF $fx_hit_any(~%hit_id%~) BEGIN
				SET hit_condition_tra = line_form == 0 ? 22480010 : 22480011 // ~À chaque attaque réussie~
			END
			ELSE PATCH_IF hit_opcode == 248 AND IS_EE AND ($fx_parameter2(~%hit_id%~) BAND BIT2) != 0 BEGIN
				SET hit_condition_tra += 1
			END
			LPF ad_tra INT_VAR tra_id = hit_condition_tra RET line_condition = text END // ~À chaque attaque de mêlée réussie~
			LPM ad_hit_effect_duration
			PATCH_IF NOT (~%app_duration_text%~ STRING_EQUAL ~~) BEGIN
				SPRINT line_condition ~%line_condition% %app_duration_text%~
			END
			SPRINT line_text $fx_sub_text(~%hit_id%~)
			SET line_any_form = 1
			SET line_no_duration = 1
			LPM ad_effect_line
		END
	END
END
