// Section « PARAMÈTRES » d'un sort (ancien get_spell_effects_description et
// build_spell_effects_description, lib/spl/extended_effects.tpp), après l'en-tête
// (new-lib/spell_header.tpp) : lignes des effets restants de ses en-têtes, après la chaîne
// (ad_spell_header_pipeline). Un sort à un en-tête n'a qu'une section, sans titre de niveau. Avec
// plusieurs en-têtes, les effets de tous les niveaux viennent d'abord, puis une section par plage de
// niveaux (ad_spell_levels).

// Lignes des sous-ressources et des effets dérivés (ad_recursion_describe_pending, ad_derived_lines),
// puis des opcodes décrits, puis lignes probables regroupées par plage (ancien
// group_probability_effects), section par section ; refus d'une forme ou d'une cible sans texte
// (render_late_missing) et d'une ligne hors des sections du sort. Les opcodes écrivent leurs lignes
// dans l'ordre de leur premier effet restant (ad_spell_header_effects), comme l'ancien moteur depuis
// leveled_opcodes : à rang égal, l'ordre des lignes et celle qu'un doublon garde en dépendent ; les
// autres opcodes suivent, dans l'ordre numérique.
DEFINE_PATCH_MACRO ad_spell_statistics BEGIN
	// Les lignes, et celles des sous-sorts, taisent la durée et le jet de sauvegarde que l'en-tête
	// écrit (ancien ignoreDuration et ignoreSavingThrow).
	SET ctx_ignore_duration = header_hide_duration
	SET ctx_ignore_save = header_hide_save
	SET statistics_sections = 1
	SPRINT $statistics_section(~0~) ~ability0~
	PATCH_IF fx_header_count > 1 BEGIN
		LPM ad_spell_levels
	END
	LPM ad_lines_reset
	LPM ad_recursion_describe_pending
	LPM ad_derived_lines
	SET statistics_opcodes = 0
	FOR (statistics_n = 0; statistics_n < $spell_fx_count(~0~); ++statistics_n) BEGIN
		SET statistics_id = $spell_fx_0(~%statistics_n%~)
		SET statistics_opcode = $fx_opcode(~%statistics_id%~)
		PATCH_IF NOT VARIABLE_IS_SET $statistics_listed(~%statistics_opcode%~) BEGIN
			SET $statistics_listed(~%statistics_opcode%~) = 1
			SET $statistics_order(~%statistics_opcodes%~) = statistics_opcode
			SET statistics_opcodes += 1
		END
	END
	PHP_EACH fx_opcode_count AS statistics_opcode => _ BEGIN
		PATCH_IF NOT VARIABLE_IS_SET $statistics_listed(~%statistics_opcode%~) BEGIN
			SET $statistics_listed(~%statistics_opcode%~) = 1
			SET $statistics_order(~%statistics_opcodes%~) = statistics_opcode
			SET statistics_opcodes += 1
		END
	END
	FOR (statistics_k = 0; statistics_k < statistics_opcodes; ++statistics_k) BEGIN
		SET render_opcode = $statistics_order(~%statistics_k%~)
		LPM ad_opcode_is_described
		PATCH_IF opcode_described BEGIN
			LPM ~ad_op_%render_opcode%_lines~
		END
	END
	SPRINT render_missing ~%render_late_missing%~
	FOR (statistics_s = 0; statistics_s < statistics_sections AND ~%render_missing%~ STRING_EQUAL ~~; ++statistics_s) BEGIN
		SPRINT prob_section $statistics_section(~%statistics_s%~)
		SET statistics_probable = 0
		FOR (statistics_line = 0; statistics_line < line_count; ++statistics_line) BEGIN
			SPRINT statistics_line_section $line_section(~%statistics_line%~)
			PATCH_IF $line_probability(~%statistics_line%~) > 0 AND ~%statistics_line_section%~ STRING_EQUAL ~%prob_section%~ BEGIN
				SET statistics_probable = 1
			END
		END
		PATCH_IF statistics_probable BEGIN
			LPM ad_lines_probability_groups
			SPRINT render_missing ~%render_late_missing%~
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		FOR (statistics_line = 0; statistics_line < line_count; ++statistics_line) BEGIN
			SPRINT statistics_line_section $line_section(~%statistics_line%~)
			SET statistics_known = ~%statistics_line_section%~ STRING_EQUAL ~~
			FOR (statistics_s = 0; statistics_s < statistics_sections; ++statistics_s) BEGIN
				SPRINT statistics_name $statistics_section(~%statistics_s%~)
				PATCH_IF ~%statistics_line_section%~ STRING_EQUAL ~%statistics_name%~ BEGIN
					SET statistics_known = 1
				END
			END
			PATCH_IF NOT statistics_known BEGIN
				LPF ad_refusal STR_VAR reason = ~not_implemented:spell:section~ message = ~line outside the sections of the spell~ RET render_missing = refusal END
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPF ad_lines_section_text STR_VAR section = ~ability0~ RET statistics_lines = text END
		SPRINT title @1300000 // ~PARAMÈTRES~
		SPRINT description ~%description%%CRLF%%CRLF%%title%%AD_COLON%%CRLF%%statistics_lines%~
		FOR (statistics_s = 1; statistics_s < statistics_sections; ++statistics_s) BEGIN
			SPRINT statistics_name $statistics_section(~%statistics_s%~)
			LPF ad_lines_section_text STR_VAR section = ~%statistics_name%~ RET statistics_lines = text statistics_count = count END
			// Une plage sans ligne n'a pas de titre.
			PATCH_IF statistics_count > 0 BEGIN
				SET minRequiredLevel = $statistics_level_min(~%statistics_s%~)
				SET maxRequiredLevel = $statistics_level_max(~%statistics_s%~)
				PATCH_IF maxRequiredLevel == 99 BEGIN
					SPRINT statistics_title @7002000 // ~À partir du niveau %minRequiredLevel%~
				END
				ELSE PATCH_IF minRequiredLevel == maxRequiredLevel BEGIN
					SPRINT statistics_title @7002002 // ~Au niveau %minRequiredLevel%~
				END
				ELSE BEGIN
					SPRINT statistics_title @7002001 // ~Entre le niveau %minRequiredLevel% et %maxRequiredLevel%~
				END
				SPRINT description ~%description%%CRLF%%CRLF%%statistics_title%%statistics_lines%~
			END
		END
	END
	ELSE BEGIN
		SPRINT header_missing ~%render_missing%~
	END
END

// Sort à plusieurs en-têtes (ancien get_spell_effects_description) : chaque effet restant d'un
// en-tête (liste de ad_spell_header_effects, effets dérivés compris) est comparé à ceux des autres
// en-têtes (ad_spell_level_same), en trois passes :
// 1. un effet du premier en-tête est commun à tous les niveaux si, dans chaque autre en-tête, tous
//    les effets de son opcode lui sont semblables (un en-tête sans cet opcode ne l'empêche pas) : il
//    est écrit sans titre de niveau, et ses semblables sont écartés ;
// 2. un effet est semblable à au plus un effet de l'en-tête suivant, qui est écarté ;
// 3. chaque effet restant couvre les niveaux de son en-tête jusqu'au dernier en-tête suivi sans
//    interruption d'un effet semblable (« À partir du niveau » s'il va jusqu'au dernier) ; une plage
//    qui commence au niveau 1 et va jusqu'au dernier est celle des effets communs.
// Entre les passes 2 et 3, un effet du premier en-tête présent à tous les niveaux à la durée, au
// bonus du jet de sauvegarde, à la valeur ou aux dés près est écrit une fois, sans titre de niveau,
// avec la progression de sa valeur (ad_spell_levels_by_duration, _by_save, _by_values).
// Un effet est écarté par son opcode (fx_consumed) ou, pour un effet dérivé, par sa ligne
// (derived_line) ; il est rangé dans sa section par fx_line_section. Sections : statistics_section,
// statistics_level_min, statistics_level_max, triées par niveaux (clé (min + 100) × 100 + max).
// Comme l'ancien moteur, une position marquée écarte tout effet de cette position dans l'en-tête.
// Les immunités aux sorts réunies pour l'en-tête (518, ad_op_206_header_groups) se comparent aussi
// par leurs noms ; leurs immunités, cachées aux listes, suivent leur effet dérivé : écartées avec lui,
// rangées dans sa section ; elles n'ont pas de progression.
// Refus (render_late_missing) : opcodes 173 et 178, dont l'ancien moteur réécrit les champs avant de
// les comparer.
DEFINE_PATCH_MACRO ad_spell_levels BEGIN
	LPM ad_spell_levels_entries
	FOR (level_h = 0; level_h < fx_header_count; ++level_h) BEGIN
		FOR (level_k = 0; level_k < $spell_fx_count(~%level_h%~); ++level_k) BEGIN
			SPRINT level_a ~%level_h% %level_k%~
			SET level_id = $level_id(~%level_a%~)
			SET level_opcode = $level_opcode(~%level_a%~)
			PATCH_IF (level_opcode == 173 OR level_opcode == 178) AND ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:levels_opcode%level_opcode%~ message = ~opcode %level_opcode% in a spell with several abilities~ RET render_late_missing = refusal END
			END
		END
	END
	// L'ancien moteur ne compare pas les durées quand l'en-tête écrit celle du sort (ignoreDuration),
	// qui n'est alors pas « Spéciale » (isSpecialDuration).
	SET level_skip_default = ctx_ignore_duration ? AD_SAME_TIMING : 0
	SET level_skip = level_skip_default
	SET level_special_duration = NOT ctx_ignore_duration
	PATCH_IF ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_spell_levels_common
		LPM ad_spell_levels_chains
		LPM ad_spell_levels_by_duration
		LPM ad_spell_levels_by_save
		LPM ad_spell_levels_by_values
	END
	PATCH_IF ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_spell_levels_ranges
	END
END

// Effets restants de chaque en-tête, « en-tête rang » (listes de ad_spell_header_effects, effets
// dérivés compris) : level_id, level_header, level_identical, level_position, level_opcode,
// level_derived, level_on (1 : pas encore écarté), level_emitted (1 : écrit), level_mark (position
// marquée). level_first : premier niveau de lanceur, calculé à la première progression.
DEFINE_PATCH_MACRO ad_spell_levels_entries BEGIN
	SET level_first = 0 - 1
	FOR (level_h = 0; level_h < fx_header_count; ++level_h) BEGIN
		FOR (level_k = 0; level_k < $spell_fx_count(~%level_h%~); ++level_k) BEGIN
			SPRINT level_a ~%level_h% %level_k%~
			SET level_id = $EVAL ~spell_fx_%level_h%~(~%level_k%~)
			SET level_opcode = $EVAL ~spell_fx_opcode_%level_h%~(~%level_k%~)
			SET $level_id(~%level_a%~) = level_id
			SET $level_header(~%level_a%~) = level_h
			// Effets identiques réunis (ad_group_identical_effects) : l'ancien moteur garde leur nombre dans
			// custom_int, qu'il compare, et décale de 1000 la position de l'effet qui les représente.
			SET level_identical = 0
			PATCH_IF AD_ENABLE_SHRINKAGE AND $EVAL ~spell_fx_derived_%level_h%~(~%level_k%~) < 0 BEGIN
				PATCH_IF $fx_identical_count(~%level_id%~) > 1 BEGIN
					SET level_identical = $fx_identical_count(~%level_id%~)
				END
			END
			SET $level_identical(~%level_a%~) = level_identical
			SET $level_position(~%level_a%~) = $fx_position(~%level_id%~) + (level_identical > 0 ? 1000 : 0)
			SET $level_opcode(~%level_a%~) = level_opcode
			SET $level_derived(~%level_a%~) = $EVAL ~spell_fx_derived_%level_h%~(~%level_k%~)
			SET $level_on(~%level_a%~) = 1
			SET $level_emitted(~%level_a%~) = 0
			SET level_position = $level_position(~%level_a%~)
			SET $level_mark(~%level_h% %level_position%~) = 0
		END
	END
END

// Passe 1 : effets communs (ancien group_identical_spell_effects_between_level, première partie),
// dans level_common_list.
DEFINE_PATCH_MACRO ad_spell_levels_common BEGIN
	SET level_common_count = 0
	FOR (level_k0 = 0; level_k0 < $spell_fx_count(~0~); ++level_k0) BEGIN
		SPRINT level_a ~0 %level_k0%~
		SET level_opcode = $level_opcode(~%level_a%~)
		SET level_in_all = 1
		SET level_similar = 0
		FOR (level_h = 1; level_h < fx_header_count AND level_in_all; ++level_h) BEGIN
			FOR (level_k = 0; level_k < $spell_fx_count(~%level_h%~) AND level_in_all; ++level_k) BEGIN
				SPRINT level_b ~%level_h% %level_k%~
				PATCH_IF $level_opcode(~%level_b%~) == level_opcode BEGIN
					LPM ad_spell_level_same
					PATCH_IF level_same BEGIN
						SPRINT $level_similar_list(~%level_similar%~) ~%level_b%~
						SET level_similar += 1
					END
					ELSE BEGIN
						SET level_in_all = 0
					END
				END
			END
		END
		PATCH_IF level_in_all BEGIN
			SPRINT $level_common_list(~%level_common_count%~) ~%level_a%~
			SET level_common_count += 1
			SET $level_emitted(~%level_a%~) = 1
			SET level_position = $level_position(~%level_a%~)
			SET $level_mark(~0 %level_position%~) = 1
			FOR (level_n = 0; level_n < level_similar; ++level_n) BEGIN
				SPRINT level_b $level_similar_list(~%level_n%~)
				SET level_b_h = $level_header(~%level_b%~)
				SET level_b_position = $level_position(~%level_b%~)
				SET $level_mark(~%level_b_h% %level_b_position%~) = 1
			END
		END
	END
	LPM ad_spell_levels_disable_marked
END

// Passe 2 : chaque effet écarte l'effet semblable de l'en-tête suivant (ancien
// group_identical_spell_effects_between_level, seconde partie).
DEFINE_PATCH_MACRO ad_spell_levels_chains BEGIN
	FOR (level_h = 0; level_h < fx_header_count; ++level_h) BEGIN
		FOR (level_k = 0; level_k < $spell_fx_count(~%level_h%~); ++level_k) BEGIN
			SPRINT level_a ~%level_h% %level_k%~
			PATCH_IF $level_on(~%level_a%~) AND level_h + 1 < fx_header_count BEGIN
				SET level_opcode = $level_opcode(~%level_a%~)
				SET level_next = level_h + 1
				SET level_found = 0
				FOR (level_k2 = 0; level_k2 < $spell_fx_count(~%level_next%~) AND NOT level_found; ++level_k2) BEGIN
					SPRINT level_b ~%level_next% %level_k2%~
					SET level_b_position = $level_position(~%level_b%~)
					PATCH_IF $level_on(~%level_b%~) AND $level_opcode(~%level_b%~) == level_opcode AND NOT $level_mark(~%level_next% %level_b_position%~) BEGIN
						LPM ad_spell_level_same
						PATCH_IF level_same BEGIN
							SET $level_mark(~%level_next% %level_b_position%~) = 1
							SET level_found = 1
						END
					END
				END
			END
		END
	END
	LPM ad_spell_levels_disable_marked
END

// Progressions par la durée (ancien group_spell_effects_by_duration) : effet semblable à la durée
// près. Une durée qu'écrivent les lignes (« Spéciale » dans l'en-tête) doit varier à chaque niveau
// et suivre une formule (ad_spell_level_duration), sinon l'effet garde ses sections.
DEFINE_PATCH_MACRO ad_spell_levels_by_duration BEGIN
	SET level_skip = AD_SAME_TIMING
	SET level_duration_by_timing = 1
	FOR (level_k0 = 0; level_k0 < $spell_fx_count(~0~) AND ~%render_late_missing%~ STRING_EQUAL ~~; ++level_k0) BEGIN
		SPRINT level_a ~0 %level_k0%~
		PATCH_IF $level_on(~%level_a%~) AND $level_opcode(~%level_a%~) != 518 BEGIN
			LPM ad_spell_level_search
			PATCH_IF search_in_all AND search_total > 1 BEGIN
				SPRINT level_value_text ~~
				SET level_mode = MOD_TYPE_cumulative
				LPM ad_spell_level_duration
				PATCH_IF level_grouped BEGIN
					LPM ad_spell_level_group
				END
			END
		END
	END
	SET level_skip = level_skip_default
END

// Progressions du bonus du jet de sauvegarde (ancien group_spell_effects_by_saving_throw) : effet
// semblable à ce bonus près, durée comprise, dont les bonus suivent une formule
// (ad_spell_level_formula). Les lignes ne l'écrivent pas quand l'en-tête écrit le jet ; sinon,
// refus tant qu'aucun sort ne le demande.
DEFINE_PATCH_MACRO ad_spell_levels_by_save BEGIN
	SET level_skip = AD_SAME_SAVE
	FOR (level_k0 = 0; level_k0 < $spell_fx_count(~0~) AND ~%render_late_missing%~ STRING_EQUAL ~~; ++level_k0) BEGIN
		SPRINT level_a ~0 %level_k0%~
		PATCH_IF $level_on(~%level_a%~) AND $level_opcode(~%level_a%~) != 518 BEGIN
			LPM ad_spell_level_search
			PATCH_IF search_in_all AND search_total > 1 BEGIN
				SPRINT formula_array ~search_save~
				SET formula_percent = 0
				SET formula_flat = 0
				SET formula_dice_sides = 0
				SET formula_opcode = 0
				LPM ad_spell_level_formula
				PATCH_IF formula_valid OR formula_rank == 2 BEGIN
					PATCH_IF NOT ctx_ignore_save BEGIN
						SET level_id = $level_id(~%level_a%~)
						LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:save_progression~ message = ~saving throw bonus varying with the level, written in the line~ RET render_late_missing = refusal END
					END
					SPRINT level_value_text ~~
					SPRINT level_duration_text ~~
					SET level_mode = MOD_TYPE_cumulative
					LPM ad_spell_level_group
				END
			END
		END
	END
	SET level_skip = level_skip_default
END

// Progressions de la valeur (ancien group_spell_effects_by_parameters) : effet d'un opcode de
// AD_LEVEL_PROGRESSION_OPCODES, de mode 0, 1 ou 2 (mot de poids faible pour l'opcode 12), semblable
// à parameter1 et à la durée près, dont les valeurs suivent une formule ; les dés d'un effet des
// opcodes 12 et 17 la précèdent (« 2d8 + 1 point de dégâts par niveau »). Des dégâts de l'opcode 12
// (mode 0) peuvent aussi progresser par le nombre de dés, et à défaut par les dés et parameter1
// (« 1d4 … par niveau + 1 … par niveau »). Une durée écrite par les lignes doit suivre sa formule.
DEFINE_PATCH_MACRO ad_spell_levels_by_values BEGIN
	FOR (level_k0 = 0; level_k0 < $spell_fx_count(~0~) AND ~%render_late_missing%~ STRING_EQUAL ~~; ++level_k0) BEGIN
		SPRINT level_a ~0 %level_k0%~
		SET level_opcode = $level_opcode(~%level_a%~)
		SET level_id = $level_id(~%level_a%~)
		SET level_mode = $fx_parameter2(~%level_id%~)
		PATCH_IF level_opcode == 12 BEGIN
			SET level_mode = level_mode BAND 65535
		END
		PATCH_IF $level_on(~%level_a%~) AND VARIABLE_IS_SET $AD_LEVEL_PROGRESSION_OPCODES(~%level_opcode%~)
				AND level_mode >= MOD_TYPE_cumulative AND level_mode <= MOD_TYPE_percentage BEGIN
			SET level_skip = AD_SAME_PARAMETER1 BOR AD_SAME_TIMING
			LPM ad_spell_level_search
			PATCH_IF search_in_all AND search_total > 1 BEGIN
				SPRINT formula_array ~search_parameter1~
				SET formula_percent = VARIABLE_IS_SET $AD_LEVEL_PERCENT_OPCODES(~%level_opcode%~)
				SET formula_flat = level_mode == MOD_TYPE_flat
				SET formula_dice_sides = 0
				SET formula_opcode = level_opcode
				LPM ad_spell_level_formula
				// Deux valeurs seulement : la formule de l'ancien moteur, sans dés ni unité.
				PATCH_IF NOT (~%formula_two_text%~ STRING_EQUAL ~~) AND level_opcode != 12 AND level_opcode != 17 BEGIN
					SPRINT formula_text ~%formula_two_text%~
					SET formula_valid = 1
					SET formula_rank = 0
				END
				LPM ad_spell_level_formula_check
				SET level_duration_by_timing = 0
				PATCH_IF formula_valid BEGIN
					SPRINT level_value_text ~%formula_text%~
					PATCH_IF level_opcode == 12 OR level_opcode == 17 BEGIN
						LPF ad_dice_text INT_VAR dice_count = $fx_dice_count(~%level_id%~) dice_sides = $fx_dice_sides(~%level_id%~) RET level_dice_text = text END
						PATCH_IF NOT (~%level_dice_text%~ STRING_EQUAL ~~) BEGIN
							SPRINT level_value_text ~%level_dice_text% %formula_text%~
							PATCH_IF formula_base > 0 BEGIN
								SPRINT level_value_text ~%level_dice_text% + %formula_text%~
							END
						END
					END
					LPM ad_spell_level_duration
					PATCH_IF level_grouped BEGIN
						LPM ad_spell_level_group
					END
				END
			END
		END
		PATCH_IF level_opcode == 12 AND level_mode == 0 AND $level_on(~%level_a%~) AND ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
			SET formula_valid = 0
			SET level_skip = AD_SAME_DICE BOR AD_SAME_TIMING
			LPM ad_spell_level_search
			SET formula_percent = 0
			SET formula_flat = 0
			SET formula_opcode = 12
			SET level_duration_by_timing = 0
			PATCH_IF search_in_all AND search_total > 1 BEGIN
				SPRINT formula_array ~search_dice~
				SET formula_dice_sides = $fx_dice_sides(~%level_id%~)
				LPM ad_spell_level_formula
				LPM ad_spell_level_formula_check
				PATCH_IF formula_valid BEGIN
					SPRINT level_value_text ~%formula_text%~
					LPM ad_spell_level_duration
					PATCH_IF level_grouped BEGIN
						LPM ad_spell_level_group
					END
				END
			END
			PATCH_IF NOT formula_valid AND ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
				SET level_skip = AD_SAME_DICE BOR AD_SAME_PARAMETER1 BOR AD_SAME_TIMING
				LPM ad_spell_level_search
				PATCH_IF search_in_all AND search_total > 1 BEGIN
					SPRINT formula_array ~search_dice~
					SET formula_dice_sides = $fx_dice_sides(~%level_id%~)
					LPM ad_spell_level_formula
					LPM ad_spell_level_formula_check
					SET level_dice_valid = formula_valid
					SPRINT level_dice_text ~%formula_text%~
					SPRINT formula_array ~search_parameter1~
					SET formula_dice_sides = 0
					LPM ad_spell_level_formula
					LPM ad_spell_level_formula_check
					PATCH_IF level_dice_valid AND formula_valid BEGIN
						SPRINT level_value_text ~%level_dice_text% + %formula_text%~
						LPM ad_spell_level_duration
						PATCH_IF level_grouped BEGIN
							LPM ad_spell_level_group
						END
					END
				END
			END
		END
	END
	SET level_skip = level_skip_default
END

// Recherche de l'effet level_a du premier en-tête dans chaque en-tête (ancien
// spell_has_same_effects_on_all_levels_except_duration) : le premier effet de son opcode semblable
// (ad_spell_level_same, champs level_skip laissés de côté), écarté ou non. search_in_all : 1 si
// chaque en-tête qui a encore des effets en a un ; les effets non écartés trouvés, dans l'ordre des
// en-têtes, en comptent search_total : search_match (« en-tête rang »), search_level (niveau
// requis), search_parameter1 (au moins 1 pour l'opcode 111, ancien opcode_111_spell_level_match),
// search_dice, search_save ; search_self : 1 si level_a en est. Durées (search_duration_level,
// search_duration_value, search_durations) : celles qui changent depuis celle de level_a. Une durée
// écrite par les lignes (level_special_duration) doit changer à chaque effet trouvé après le premier,
// écartés compris : l'ancienne fonction rend positif l'opcode d'un effet écarté avant de le compter.
DEFINE_PATCH_MACRO ad_spell_level_search BEGIN
	SET search_opcode = $level_opcode(~%level_a%~)
	SET search_id = $level_id(~%level_a%~)
	SET search_previous_duration = $fx_duration(~%search_id%~)
	SET search_previous_any = search_previous_duration
	SET search_in_all = 1
	SET search_total = 0
	SET search_durations = 0
	SET search_found_any = 0
	SET search_changes_any = 0
	SET search_self = 0
	FOR (search_h = 0; search_h < fx_header_count AND search_in_all; ++search_h) BEGIN
		SET search_found = 0
		SET search_has_on = 0
		FOR (search_k = 0; search_k < $spell_fx_count(~%search_h%~); ++search_k) BEGIN
			SPRINT level_b ~%search_h% %search_k%~
			PATCH_IF $level_on(~%level_b%~) BEGIN
				SET search_has_on = 1
			END
			PATCH_IF NOT search_found AND $level_opcode(~%level_b%~) == search_opcode BEGIN
				LPM ad_spell_level_same
				PATCH_IF level_same BEGIN
					SET search_found = 1
					SET search_found_any += 1
					SET search_any_id = $level_id(~%level_b%~)
					PATCH_IF $fx_duration(~%search_any_id%~) != search_previous_any BEGIN
						SET search_previous_any = $fx_duration(~%search_any_id%~)
						SET search_changes_any += 1
					END
					PATCH_IF $level_on(~%level_b%~) BEGIN
						SET search_id = $level_id(~%level_b%~)
						SPRINT $search_match(~%search_total%~) ~%level_b%~
						SET $search_level(~%search_total%~) = $spell_level(~%search_h%~)
						SET search_parameter1 = $fx_parameter1(~%search_id%~)
						PATCH_IF search_opcode == 111 AND search_parameter1 < 1 BEGIN
							SET search_parameter1 = 1
						END
						SET $search_parameter1(~%search_total%~) = search_parameter1
						SET $search_dice(~%search_total%~) = $fx_dice_count(~%search_id%~)
						SET $search_save(~%search_total%~) = $fx_save_bonus(~%search_id%~)
						SET search_total += 1
						PATCH_IF ~%level_b%~ STRING_EQUAL ~%level_a%~ BEGIN
							SET search_self = 1
						END
						PATCH_IF $fx_duration(~%search_id%~) != search_previous_duration BEGIN
							SET search_previous_duration = $fx_duration(~%search_id%~)
							SET $search_duration_level(~%search_durations%~) = $spell_level(~%search_h%~)
							SET $search_duration_value(~%search_durations%~) = search_previous_duration
							SET search_durations += 1
						END
					END
				END
			END
		END
		PATCH_IF NOT search_found AND search_has_on BEGIN
			SET search_in_all = 0
		END
	END
	PATCH_IF level_special_duration AND search_changes_any > 0 AND search_found_any - 1 != search_changes_any BEGIN
		SET search_in_all = 0
	END
END

// L'effet trouvé par ad_spell_level_search peut-il être réuni d'après ses durées ? level_grouped : 1
// si les lignes n'écrivent pas sa durée, sinon si ses durées changent au moins deux fois (une seule
// durée ne donne pas de formule : celle de level_a n'est pas comptée) et suivent une formule
// (ad_spell_header_complex_duration). level_duration_text : la formule écrite par les lignes,
// « pendant … » ; avec level_duration_by_timing (passe des durées), « après … » pour un effet
// différé, « après … et pendant … » pour un effet différé limité, refus pour un autre timing.
DEFINE_PATCH_MACRO ad_spell_level_duration BEGIN
	SET level_grouped = 1
	SPRINT level_duration_text ~~
	PATCH_IF level_special_duration AND search_durations > 0 BEGIN
		SPRINT complex_array ~search_duration~
		SET complex_count = search_durations
		LPM ad_spell_header_complex_duration
		SET level_grouped = search_durations > 1 AND NOT (~%complex_text%~ STRING_EQUAL ~~)
		PATCH_IF level_grouped BEGIN
			SPRINT strDuration ~%complex_text%~
			SET level_id = $level_id(~%level_a%~)
			SET level_timing = $fx_timing(~%level_id%~)
			PATCH_IF NOT level_duration_by_timing OR level_timing == TIMING_duration OR level_timing == TIMING_duration_ticks BEGIN
				SPRINT level_duration_text @3000000 // ~pendant %strDuration%~
			END
			ELSE PATCH_IF level_timing == TIMING_delayed BEGIN
				SPRINT level_duration_text @3000005 // ~après %strDuration%~
			END
			ELSE PATCH_IF level_timing == TIMING_delayed_duration BEGIN
				SPRINT level_duration_text @3000006 // ~après %strDuration% et pendant %strDuration%~
			END
			ELSE BEGIN
				SET level_id = $level_id(~%level_a%~)
				LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:duration_progression_timing~ message = ~duration varying with the level, timing %level_timing%~ RET render_late_missing = refusal END
			END
		END
	END
END

// Réunit l'effet level_a à ceux que ad_spell_level_search a trouvés (ancien
// group_spell_effects_disable) : il est écrit sans titre de niveau, avec la progression
// level_value_text de sa valeur (mode level_mode) et level_duration_text de sa durée, et les autres
// sont écartés. Refus : level_a n'est
// pas lui-même trouvé (l'ancien moteur écrirait l'effet deux fois) ; progression de la valeur d'un
// opcode dont les lignes ne l'écrivent pas (AD_LEVEL_VALUE_OPCODES), ou d'un autre mode que l'ajout ou
// la valeur fixée ;
// progression d'un opcode dont le premier en-tête a des effets du fichier et d'un EFF (177 : l'ancien
// moteur ordonne autrement les lignes, SPCL236).
DEFINE_PATCH_MACRO ad_spell_level_group BEGIN
	SET level_id = $level_id(~%level_a%~)
	SET level_opcode = $level_opcode(~%level_a%~)
	SET level_ext_count = 0
	SET level_plain_count = 0
	FOR (level_ext_k = 0; level_ext_k < $spell_fx_count(~0~); ++level_ext_k) BEGIN
		SPRINT level_ext_a ~0 %level_ext_k%~
		PATCH_IF $level_opcode(~%level_ext_a%~) == level_opcode BEGIN
			SET level_ext_id = $level_id(~%level_ext_a%~)
			PATCH_IF $fx_external(~%level_ext_id%~) BEGIN
				SET level_ext_count += 1
			END
			ELSE BEGIN
				SET level_plain_count += 1
			END
		END
	END
	SET level_external = level_ext_count > 0 AND level_plain_count > 0
	PATCH_IF NOT search_self BEGIN
		LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:progression_other_effect~ message = ~effect of the first ability merged with another effect of its opcode~ RET render_late_missing = refusal END
	END
	ELSE PATCH_IF NOT (~%level_value_text%~ STRING_EQUAL ~~) AND NOT VARIABLE_IS_SET $AD_LEVEL_VALUE_OPCODES(~%level_opcode%~) BEGIN
		LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:progression_opcode%level_opcode%~ message = ~value varying with the level, not written by the lines of opcode %level_opcode%~ RET render_late_missing = refusal END
	END
	ELSE PATCH_IF NOT (~%level_value_text%~ STRING_EQUAL ~~) AND level_mode != MOD_TYPE_cumulative AND level_mode != MOD_TYPE_flat BEGIN
		LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:progression_mode~ message = ~value varying with the level in mode %level_mode%~ RET render_late_missing = refusal END
	END
	ELSE PATCH_IF level_external BEGIN
		LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:progression_external~ message = ~progression of opcode %level_opcode% with effects from an EFF file mixed with others in the first ability~ RET render_late_missing = refusal END
	END
	ELSE BEGIN
		SET $level_emitted(~%level_a%~) = 1
		FOR (group_n = 0; group_n < search_total; ++group_n) BEGIN
			SPRINT level_b $search_match(~%group_n%~)
			SET $level_on(~%level_b%~) = 0
		END
		SPRINT $fx_level_value(~%level_id%~) ~%level_value_text%~
		SPRINT $fx_level_duration(~%level_id%~) ~%level_duration_text%~
	END
END

// Refus d'une formule de valeur que l'ancien moteur écrit en français dans les deux langues (deux
// valeurs seulement : « … + … au niveau N », « … jusqu'au niveau N »).
DEFINE_PATCH_MACRO ad_spell_level_formula_check BEGIN
	PATCH_IF formula_rank == 2 AND ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
		SET level_id = $level_id(~%level_a%~)
		LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:progression_two_values~ message = ~value taking only two values between the abilities~ RET render_late_missing = refusal END
	END
END

// Valeur d'une progression (ancien get_complex_value) : valeurs <formula_array>(n) aux niveaux
// search_level(n), n < search_total, un niveau requis de 1 ou moins comptant pour le premier niveau
// de lanceur. Le pas (valeur et niveaux entre deux changements) est cherché en quatre essais : sur
// tous les changements, puis sans le premier, sans le premier en comptant un niveau de plus au pas,
// sans le premier en admettant un niveau de plus ou de moins. formula_valid : 1 si un pas tient ;
// formula_text : « 1 par niveau du lanceur/20 », « 2 par tranche de 3 niveaux du lanceur/18 »,
// précédé du reste de la valeur au dernier niveau (« 10 % + 1 % par niveau du lanceur/20 », sans le
// signe du pas), une valeur constante seule ; formula_base : valeur de départ. formula_percent :
// valeurs en pourcentage ; formula_dice_sides : valeurs en nombre de dés de ces faces ;
// formula_flat : valeur fixée (l'ancien moteur ajoute « niveau + valeur » devant une valeur constante
// ou un pas négatif) ; formula_opcode : opcode dont l'unité suit la valeur (AD_LEVEL_UNIT_OPCODES),
// sur l'effet level_id ; formula_unit_used : 1 si elle a été écrite. formula_rank : nombre de valeurs
// distinctes successives ; avec deux, formula_valid vaut 0 (ad_spell_level_formula_check) et, sans
// dés, formula_two_text est la formule de l'ancien get_complex_value (« 1 + 1 au niveau 20 »,
// « 2 jusqu'au niveau 9 » quand la seconde valeur est nulle), sans unité.
DEFINE_PATCH_MACRO ad_spell_level_formula BEGIN
	SPRINT formula_text ~~
	SET formula_base = 0
	SET formula_unit_used = 0
	SET formula_valid = 1
	SET formula_start = 0
	SET formula_delta = 0
	SET formula_delta_level = 0
	SET formula_previous = 0
	SET formula_previous_level = 0
	SET formula_rank = 0
	FOR (formula_n = 0; formula_n < search_total; ++formula_n) BEGIN
		LPM ad_spell_level_formula_entry
		PATCH_IF formula_rank > 0 BEGIN
			PATCH_IF formula_value != formula_previous BEGIN
				PATCH_IF formula_delta == 0 BEGIN
					SET formula_delta = formula_value - formula_previous
					SET formula_delta_level = formula_level - formula_previous_level
				END
				ELSE PATCH_IF formula_delta != formula_value - formula_previous OR formula_delta_level != formula_level - formula_previous_level BEGIN
					SET formula_valid = 0
				END
			END
		END
		ELSE BEGIN
			SET formula_start = formula_value
		END
		PATCH_IF formula_previous_level == 0 OR formula_value != formula_previous BEGIN
			SET formula_previous_level = formula_level
			SET formula_rank += 1
		END
		SET formula_previous = formula_value
	END
	// Les essais suivants gardent le niveau du précédent jusqu'au premier changement.
	FOR (formula_pass = 2; formula_pass <= 4; ++formula_pass) BEGIN
		PATCH_IF NOT formula_valid BEGIN
			SET formula_valid = 1
			SET formula_rank = 0
			SET formula_previous = 0
			SET formula_start = 0
			SET formula_delta = 0
			SET formula_delta_level = 0
			FOR (formula_n = 0; formula_n < search_total; ++formula_n) BEGIN
				LPM ad_spell_level_formula_entry
				PATCH_IF formula_rank > 1 AND formula_previous != formula_value BEGIN
					PATCH_IF formula_delta == 0 BEGIN
						SET formula_delta = formula_value - formula_previous
						SET formula_delta_level = formula_level - formula_previous_level + (formula_pass == 3 ? 1 : 0)
					END
					ELSE PATCH_IF formula_delta != formula_value - formula_previous OR (formula_delta_level != formula_level - formula_previous_level
							AND (formula_pass != 4 OR formula_delta_level + 1 != formula_level - formula_previous_level)) BEGIN
						SET formula_valid = 0
					END
				END
				ELSE BEGIN
					SET formula_start = formula_value
				END
				PATCH_IF formula_previous != formula_value OR (formula_pass == 4 AND formula_rank < 2) BEGIN
					SET formula_previous = formula_value
					SET formula_previous_level = formula_level
				END
				SET formula_rank += 1
			END
		END
	END
	SPRINT formula_two_text ~~
	PATCH_IF formula_rank == 2 BEGIN
		SET formula_valid = 0
		PATCH_IF formula_dice_sides == 0 BEGIN
			LPM ad_spell_level_formula_two_values
		END
	END
	ELSE PATCH_IF formula_valid BEGIN
		SET formula_last = formula_value
		SET formula_base = formula_start
		SET formula_unit_tra = 0
		PATCH_IF VARIABLE_IS_SET $AD_LEVEL_UNIT_OPCODES(~%formula_opcode%~) BEGIN
			SET unit_value = formula_delta
			SET unit_fx = level_id
			LPM ~ad_op_%formula_opcode%_level_unit~
			SET formula_unit_tra = unit_tra
		END
		PATCH_IF formula_dice_sides > 0 BEGIN
			SET diceCount = ABS formula_delta
			SET diceSides = formula_dice_sides
			SPRINT formula_step @1200005 // ~%diceCount%d%diceSides%~
		END
		ELSE BEGIN
			SPRINT formula_step ~%formula_delta%~
		END
		PATCH_IF formula_start > 0 AND formula_delta == 0 BEGIN
			SPRINT formula_typed ~%formula_start%~
			LPM ad_spell_level_formula_typed
			SPRINT formula_text ~%formula_typed%~
			PATCH_IF formula_flat BEGIN
				SET formula_flat_value = formula_previous_level + formula_last
				SPRINT formula_text ~%formula_flat_value% %formula_text%~
			END
		END
		ELSE PATCH_IF formula_delta_level != 0 BEGIN
			SET levelMax = formula_previous_level
			// Reste au niveau du dernier changement (levelMax) : un dernier en-tête à la même valeur ne le
			// change pas.
			SET formula_remains = (ABS formula_previous) - (ABS formula_delta * formula_previous_level / formula_delta_level)
			SPRINT formula_typed ~%formula_step%~
			LPM ad_spell_level_formula_typed
			SPRINT value ~%formula_typed%~
			PATCH_IF formula_flat AND formula_delta < 0 BEGIN
				SET formula_flat_value = formula_previous_level + formula_last
				SPRINT value ~%formula_flat_value% %value%~
			END
			PATCH_IF ABS formula_delta_level == 1 BEGIN
				SPRINT formula_text @7002010 // ~%value% par niveau du lanceur/%levelMax%~
			END
			ELSE BEGIN
				SET level = formula_delta_level
				SPRINT formula_text @7002011 // ~%value% par tranche de %level% niveaux du lanceur/%levelMax%~
			END
			PATCH_IF formula_remains > 0 BEGIN
				SPRINT formula_remains_text ~%formula_remains%~
				PATCH_IF formula_dice_sides > 0 BEGIN
					SET diceCount = formula_remains
					SET diceSides = formula_dice_sides
					SPRINT formula_remains_text @1200005 // ~%diceCount%d%diceSides%~
				END
				PATCH_IF formula_percent BEGIN
					SPRINT value ~%formula_remains_text%~
					SPRINT formula_remains_text @1200003 // ~%value%%PERCENT%~
				END
				PATCH_IF formula_delta_level < 0 BEGIN
					SPRINT formula_text ~%formula_remains_text% %formula_text%~
				END
				ELSE BEGIN
					LPF ad_level_unsigned STR_VAR text = ~%formula_text%~ RET formula_text = text END
					SPRINT formula_text ~%formula_remains_text% + %formula_text%~
				END
			END
		END
		ELSE BEGIN
			SPRINT formula_text ~%formula_start%~
		END
	END
END

// Niveau formula_level et valeur formula_value du rang formula_n de ad_spell_level_formula.
DEFINE_PATCH_MACRO ad_spell_level_formula_entry BEGIN
	SET formula_level = $search_level(~%formula_n%~)
	SET formula_value = $EVAL ~%formula_array%~(~%formula_n%~)
	PATCH_IF formula_level <= 1 BEGIN
		PATCH_IF level_first < 0 BEGIN
			LPF ad_spell_first_level RET level_first = first_level END
		END
		SET formula_level = level_first
	END
END

// Formule à deux valeurs (formula_two_text) : première valeur, seconde valeur et niveau requis de son
// premier en-tête.
DEFINE_PATCH_MACRO ad_spell_level_formula_two_values BEGIN
	SET formula_two_first = 0
	SET formula_two_second = 0
	SET formula_two_level = 0
	FOR (formula_n = 0; formula_n < search_total; ++formula_n) BEGIN
		LPM ad_spell_level_formula_entry
		PATCH_IF formula_n == 0 BEGIN
			SET formula_two_first = formula_value
		END
		ELSE PATCH_IF formula_two_level == 0 AND formula_value != formula_two_first BEGIN
			SET formula_two_second = formula_value
			SET formula_two_level = formula_level
		END
	END
	SPRINT baseValue ~%formula_two_first%~
	SET formula_two_delta = formula_two_second - formula_two_first
	SPRINT value ~%formula_two_delta%~
	PATCH_IF formula_percent BEGIN
		SPRINT value ~%formula_two_first%~
		SPRINT baseValue @1200003 // ~%value%%PERCENT%~
		SPRINT value ~%formula_two_delta%~
		SPRINT value @1200003 // ~%value%%PERCENT%~
	END
	PATCH_IF formula_two_first > 0 AND formula_two_second == 0 BEGIN
		SET level = formula_two_level - 1
		SPRINT formula_two_text @3000013 // ~%baseValue% jusqu'au niveau %level%~
	END
	ELSE BEGIN
		SET level = formula_two_level
		SPRINT formula_two_text @3000010 // ~%baseValue% + %value% au niveau %level%~
	END
END

// formula_typed suivi de l'unité formula_unit_tra (ancien get_complex_typed_value), en
// pourcentage avec formula_percent.
DEFINE_PATCH_MACRO ad_spell_level_formula_typed BEGIN
	PATCH_IF formula_percent BEGIN
		SPRINT value ~%formula_typed%~
		SPRINT formula_typed @1200003 // ~%value%%PERCENT%~
	END
	PATCH_IF formula_unit_tra > 0 BEGIN
		LPF ad_tra INT_VAR tra_id = formula_unit_tra RET valueType = text END
		SPRINT value ~%formula_typed%~
		SPRINT formula_typed @7002012 // ~%value% %valueType%~
		SET formula_unit_used = 1
	END
END

// text sans le signe « - » de tête, ni l'espace qui le suit.
DEFINE_PATCH_FUNCTION ad_level_unsigned
	STR_VAR
		text = ~~
	RET
		text
BEGIN
	INNER_PATCH_SAVE text ~%text%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~^- ?~ ~~
	END
END

// Passe 3 : plage de niveaux de chaque effet restant (ancien get_spell_effects_description) ; les
// effets communs de la passe 1 viennent avant ceux qu'elle trouve.
DEFINE_PATCH_MACRO ad_spell_levels_ranges BEGIN
	SET level_keys_count = 0
	FOR (level_h = 0; level_h < fx_header_count; ++level_h) BEGIN
		FOR (level_k = 0; level_k < $spell_fx_count(~%level_h%~); ++level_k) BEGIN
			SPRINT level_a ~%level_h% %level_k%~
			PATCH_IF $level_on(~%level_a%~) BEGIN
				SET level_opcode = $level_opcode(~%level_a%~)
				SET level_from = $spell_level(~%level_h%~)
				SET level_to = 99
				SET level_open = 1
				FOR (level_h2 = level_h + 1; level_h2 < fx_header_count AND level_open; ++level_h2) BEGIN
					SET level_found = 0
					FOR (level_k2 = 0; level_k2 < $spell_fx_count(~%level_h2%~) AND NOT level_found; ++level_k2) BEGIN
						SPRINT level_b ~%level_h2% %level_k2%~
						PATCH_IF $level_opcode(~%level_b%~) == level_opcode BEGIN
							LPM ad_spell_level_same
							SET level_found = level_same
						END
					END
					PATCH_IF NOT level_found BEGIN
						SET level_to = $spell_level(~%level_h2%~) - 1
						SET level_open = 0
					END
				END
				SET $level_emitted(~%level_a%~) = 1
				PATCH_IF level_from > 1 OR level_to < 99 BEGIN
					SET level_key = (level_from + 100) * 100 + level_to
					SET $level_keys(~%level_key%~) = 1
					SET level_keys_count += 1
					SET level_id = $level_id(~%level_a%~)
					SPRINT $fx_line_section(~%level_id%~) ~level%level_key%~
					SET level_derived = $level_derived(~%level_a%~)
					PATCH_IF level_opcode == 518 BEGIN
						PHP_EACH fx_ids_206 AS _ => level_member BEGIN
							PATCH_IF $fx_immunity_derived(~%level_member%~) == level_derived BEGIN
								SPRINT $fx_line_section(~%level_member%~) ~level%level_key%~
							END
						END
					END
				END
			END
		END
	END
	FOR (level_h = 0; level_h < fx_header_count; ++level_h) BEGIN
		FOR (level_k = 0; level_k < $spell_fx_count(~%level_h%~); ++level_k) BEGIN
			SPRINT level_a ~%level_h% %level_k%~
			PATCH_IF NOT $level_emitted(~%level_a%~) BEGIN
				SET level_derived = $level_derived(~%level_a%~)
				PATCH_IF $level_opcode(~%level_a%~) == 518 BEGIN
					PHP_EACH fx_ids_206 AS _ => level_member BEGIN
						PATCH_IF $fx_immunity_derived(~%level_member%~) == level_derived BEGIN
							SET $fx_consumed(~%level_member%~) = 1
							SET $fx_level_merged(~%level_member%~) = 1
						END
					END
				END
				ELSE PATCH_IF level_derived >= 0 BEGIN
					SPRINT $derived_line(~%level_derived%~) ~~
				END
				ELSE BEGIN
					SET level_id = $level_id(~%level_a%~)
					SET $fx_consumed(~%level_id%~) = 1
					SET $fx_level_merged(~%level_id%~) = 1
				END
			END
		END
	END
	PATCH_IF level_keys_count > 0 BEGIN
		SORT_ARRAY_INDICES level_keys NUMERICALLY
	END
	PHP_EACH level_keys AS level_key => _ BEGIN
		SPRINT $statistics_section(~%statistics_sections%~) ~level%level_key%~
		SET $statistics_level_max(~%statistics_sections%~) = level_key MODULO 100
		SET $statistics_level_min(~%statistics_sections%~) = level_key / 100 - 100
		SET statistics_sections += 1
	END
END

// Écarte les effets restants dont la position est marquée dans leur en-tête.
DEFINE_PATCH_MACRO ad_spell_levels_disable_marked BEGIN
	FOR (level_h = 0; level_h < fx_header_count; ++level_h) BEGIN
		FOR (level_k = 0; level_k < $spell_fx_count(~%level_h%~); ++level_k) BEGIN
			SPRINT level_a ~%level_h% %level_k%~
			SET level_position = $level_position(~%level_a%~)
			PATCH_IF $level_mark(~%level_h% %level_position%~) BEGIN
				SET $level_on(~%level_a%~) = 0
			END
		END
	END
END

// level_same : les effets level_a et level_b (« en-tête rang ») de deux en-têtes ont les champs que
// compare l'ancien moteur entre niveaux (opcode_match, ou opcode_match_except_duration sous la durée
// de l'en-tête), sauf ceux de AD_LEVEL_SAME_IGNORED pour leur opcode et ceux de level_skip : bits
// AD_SAME_PARAMETER1 (parameter1), AD_SAME_DICE (nombre de dés), AD_SAME_SAVE (bonus du jet de
// sauvegarde), AD_SAME_TIMING (durée).
// L'ancien moteur compare parameter2 tel que lu, et le nombre d'effets identiques réunis.
DEFINE_PATCH_MACRO ad_spell_level_same BEGIN
	SET same_a = $level_id(~%level_a%~)
	SET same_b = $level_id(~%level_b%~)
	SET same_opcode = $level_opcode(~%level_a%~)
	SET same_ignored = level_skip
	PATCH_IF VARIABLE_IS_SET $AD_LEVEL_SAME_IGNORED(~%same_opcode%~) BEGIN
		SET same_ignored = level_skip BOR $AD_LEVEL_SAME_IGNORED(~%same_opcode%~)
	END
	SET same_parameter1_a = $fx_parameter1(~%same_a%~)
	SET same_parameter1_b = $fx_parameter1(~%same_b%~)
	// Opcode 111 : un nombre d'armes inférieur à 1 en vaut une (ancien opcode_111_spell_level_match).
	PATCH_IF same_opcode == 111 BEGIN
		SET same_parameter1_a = same_parameter1_a < 1 ? 1 : same_parameter1_a
		SET same_parameter1_b = same_parameter1_b < 1 ? 1 : same_parameter1_b
	END
	SET level_same = $fx_external(~%same_a%~) == $fx_external(~%same_b%~)
		AND $fx_target(~%same_a%~) == $fx_target(~%same_b%~)
		AND $fx_power(~%same_a%~) == $fx_power(~%same_b%~)
		AND ((same_ignored BAND AD_SAME_PARAMETER1) != 0 OR same_parameter1_a == same_parameter1_b)
		AND ((same_ignored BAND AD_SAME_PARAMETER2) != 0 OR $fx_parameter2_raw(~%same_a%~) == $fx_parameter2_raw(~%same_b%~))
		AND ((same_ignored BAND AD_SAME_TIMING) != 0 OR $fx_duration(~%same_a%~) == $fx_duration(~%same_b%~))
		AND $fx_timing(~%same_a%~) == $fx_timing(~%same_b%~)
		AND $fx_resistance(~%same_a%~) == $fx_resistance(~%same_b%~)
		AND $fx_probability1(~%same_a%~) == $fx_probability1(~%same_b%~)
		AND $fx_probability2(~%same_a%~) == $fx_probability2(~%same_b%~)
		AND ((same_ignored BAND AD_SAME_DICE) != 0 OR $fx_dice_count(~%same_a%~) == $fx_dice_count(~%same_b%~))
		AND $fx_dice_sides(~%same_a%~) == $fx_dice_sides(~%same_b%~)
		AND $fx_save_type(~%same_a%~) == $fx_save_type(~%same_b%~)
		AND ((same_ignored BAND AD_SAME_SAVE) != 0 OR $fx_save_bonus(~%same_a%~) == $fx_save_bonus(~%same_b%~))
		AND $fx_special(~%same_a%~) == $fx_special(~%same_b%~)
		AND $fx_parameter3(~%same_a%~) == $fx_parameter3(~%same_b%~)
		AND $fx_parameter4(~%same_a%~) == $fx_parameter4(~%same_b%~)
		AND $level_identical(~%level_a%~) == $level_identical(~%level_b%~)
	PATCH_IF level_same BEGIN
		SPRINT same_resource_a $fx_resource_lower(~%same_a%~)
		SPRINT same_resource_b $fx_resource_lower(~%same_b%~)
		SPRINT same_resource2_a $fx_resource2(~%same_a%~)
		SPRINT same_resource2_b $fx_resource2(~%same_b%~)
		SPRINT same_resource3_a $fx_resource3(~%same_a%~)
		SPRINT same_resource3_b $fx_resource3(~%same_b%~)
		SET level_same = (~%same_resource_a%~ STRING_EQUAL ~%same_resource_b%~)
			AND (~%same_resource2_a%~ STRING_EQUAL_CASE ~%same_resource2_b%~)
			AND (~%same_resource3_a%~ STRING_EQUAL_CASE ~%same_resource3_b%~)
	END
	PATCH_IF level_same AND same_opcode == 518 BEGIN
		SET same_derived_a = $level_derived(~%level_a%~)
		SET same_derived_b = $level_derived(~%level_b%~)
		SPRINT same_signature_a $derived_signature(~%same_derived_a%~)
		SPRINT same_signature_b $derived_signature(~%same_derived_b%~)
		SET level_same = ~%same_signature_a%~ STRING_EQUAL ~%same_signature_b%~
	END
END
