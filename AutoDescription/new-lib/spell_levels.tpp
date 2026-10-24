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
// Un effet est écarté par son opcode (fx_consumed) ou, pour un effet dérivé, par sa ligne
// (derived_line) ; il est rangé dans sa section par fx_line_section. Sections : statistics_section,
// statistics_level_min, statistics_level_max, triées par niveaux (clé (min + 100) × 100 + max).
// Comme l'ancien moteur, une position marquée écarte tout effet de cette position dans l'en-tête.
// Refus (render_late_missing) : opcodes 173 et 178, dont l'ancien moteur réécrit les champs avant de
// les comparer ; immunités aux sorts réunies pour l'en-tête (518, ad_op_206_header_groups), qui
// ne sont pas dans les listes ; effet que l'ancien moteur réunit en progression, présent à tous les
// niveaux à la durée, au bonus du jet de sauvegarde, à la valeur ou aux dés près
// (group_spell_effects_by_duration, _by_saving_throw et _by_parameters ; étape suivante).
DEFINE_PATCH_MACRO ad_spell_levels BEGIN
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
			PATCH_IF (level_opcode == 173 OR level_opcode == 178) AND ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:levels_opcode%level_opcode%~ message = ~opcode %level_opcode% in a spell with several abilities~ RET render_late_missing = refusal END
			END
			PATCH_IF level_opcode == 518 AND ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:levels_immunities~ message = ~spell immunities merged in a spell with several abilities~ RET render_late_missing = refusal END
			END
		END
	END
	SET level_skip_duration = ctx_ignore_duration
	SET level_skip_save_bonus = 0
	SET level_skip_values = 0
	PATCH_IF ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_spell_levels_common
		LPM ad_spell_levels_chains
		LPM ad_spell_levels_progressions
	END
	PATCH_IF ~%render_late_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_spell_levels_ranges
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

// Refus des effets du premier en-tête que l'ancien moteur réunirait en progression : semblables, à
// la durée, au bonus du jet de sauvegarde et (opcodes de AD_LEVEL_PROGRESSION_OPCODES) à la valeur et
// aux dés près, à un effet de chaque en-tête qui a encore des effets, et d'au moins deux en-têtes
// (ancien spell_has_same_effects_on_all_levels_except_duration). Le refus couvre aussi les cas où
// l'ancien moteur, faute de formule, ne réunit rien.
DEFINE_PATCH_MACRO ad_spell_levels_progressions BEGIN
	FOR (level_k0 = 0; level_k0 < $spell_fx_count(~0~) AND ~%render_late_missing%~ STRING_EQUAL ~~; ++level_k0) BEGIN
		SPRINT level_a ~0 %level_k0%~
		PATCH_IF $level_on(~%level_a%~) BEGIN
			SET level_opcode = $level_opcode(~%level_a%~)
			SET level_skip_duration = 1
			SET level_skip_save_bonus = 1
			SET level_skip_values = VARIABLE_IS_SET $AD_LEVEL_PROGRESSION_OPCODES(~%level_opcode%~)
			SET level_in_all = 1
			SET level_total = 0
			FOR (level_h = 0; level_h < fx_header_count AND level_in_all; ++level_h) BEGIN
				SET level_found = 0
				SET level_has_on = 0
				FOR (level_k = 0; level_k < $spell_fx_count(~%level_h%~); ++level_k) BEGIN
					SPRINT level_b ~%level_h% %level_k%~
					PATCH_IF $level_on(~%level_b%~) BEGIN
						SET level_has_on = 1
					END
					PATCH_IF NOT level_found AND $level_opcode(~%level_b%~) == level_opcode BEGIN
						LPM ad_spell_level_same
						PATCH_IF level_same BEGIN
							SET level_found = 1
							SET level_total += $level_on(~%level_b%~)
						END
					END
				END
				PATCH_IF NOT level_found AND level_has_on BEGIN
					SET level_in_all = 0
				END
			END
			SET level_skip_duration = ctx_ignore_duration
			SET level_skip_save_bonus = 0
			SET level_skip_values = 0
			PATCH_IF level_in_all AND level_total > 1 BEGIN
				SET level_id = $level_id(~%level_a%~)
				LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell:progression~ message = ~effect varying with the level (duration, saving throw bonus, value or dice): progression not supported yet~ RET render_late_missing = refusal END
			END
		END
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
				END
			END
		END
	END
	FOR (level_h = 0; level_h < fx_header_count; ++level_h) BEGIN
		FOR (level_k = 0; level_k < $spell_fx_count(~%level_h%~); ++level_k) BEGIN
			SPRINT level_a ~%level_h% %level_k%~
			PATCH_IF NOT $level_emitted(~%level_a%~) BEGIN
				SET level_derived = $level_derived(~%level_a%~)
				PATCH_IF level_derived >= 0 BEGIN
					SPRINT $derived_line(~%level_derived%~) ~~
				END
				ELSE BEGIN
					SET level_id = $level_id(~%level_a%~)
					SET $fx_consumed(~%level_id%~) = 1
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
// de l'en-tête), sauf ceux de AD_LEVEL_SAME_IGNORED pour leur opcode ; level_skip_duration,
// level_skip_save_bonus et level_skip_values (valeur et nombre de dés) en laissent d'autres de côté.
// L'ancien moteur compare parameter2 tel que lu, et le nombre d'effets identiques réunis.
DEFINE_PATCH_MACRO ad_spell_level_same BEGIN
	SET same_a = $level_id(~%level_a%~)
	SET same_b = $level_id(~%level_b%~)
	SET same_opcode = $level_opcode(~%level_a%~)
	SET same_ignored = 0
	PATCH_IF VARIABLE_IS_SET $AD_LEVEL_SAME_IGNORED(~%same_opcode%~) BEGIN
		SET same_ignored = $AD_LEVEL_SAME_IGNORED(~%same_opcode%~)
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
		AND ((same_ignored BAND AD_SAME_PARAMETER1) != 0 OR level_skip_values OR same_parameter1_a == same_parameter1_b)
		AND ((same_ignored BAND AD_SAME_PARAMETER2) != 0 OR $fx_parameter2_raw(~%same_a%~) == $fx_parameter2_raw(~%same_b%~))
		AND (level_skip_duration OR $fx_duration(~%same_a%~) == $fx_duration(~%same_b%~))
		AND $fx_timing(~%same_a%~) == $fx_timing(~%same_b%~)
		AND $fx_resistance(~%same_a%~) == $fx_resistance(~%same_b%~)
		AND $fx_probability1(~%same_a%~) == $fx_probability1(~%same_b%~)
		AND $fx_probability2(~%same_a%~) == $fx_probability2(~%same_b%~)
		AND (level_skip_values OR $fx_dice_count(~%same_a%~) == $fx_dice_count(~%same_b%~))
		AND $fx_dice_sides(~%same_a%~) == $fx_dice_sides(~%same_b%~)
		AND $fx_save_type(~%same_a%~) == $fx_save_type(~%same_b%~)
		AND (level_skip_save_bonus OR $fx_save_bonus(~%same_a%~) == $fx_save_bonus(~%same_b%~))
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
END
