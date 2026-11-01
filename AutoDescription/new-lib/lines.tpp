// Lignes d'une description, rangées avant le rendu : section, rang de tri, texte. Le texte n'est
// assemblé qu'au rendu de la section, dans l'ordre des rangs ; à rang égal, la ligne qui vient en
// dernier dans la section vient en premier, comme dans l'ancien moteur (son tri ne compare que le
// rang et inverse l'ordre des égalités, V37). L'ordre d'une section est celui des ajouts, sauf après
// un passage de tri (ad_lines_sort_pass), pour une section que l'ancien moteur trie deux fois. Une
// ligne d'effet probable garde sa probabilité (line_probability, 0 pour une autre ligne), sa plage
// (line_probability_low, line_probability_high) et son texte sans « N % de chances » (line_core),
// pour le regroupement par plage (ad_lines_probability_groups) ; line_nested : ligne en retrait sous
// le titre de son groupe ; line_effect : effet (line_fx) d'une ligne probable ; line_composite : ligne
// d'un groupe de probabilité propre réunie sous la probabilité du parent (0, ou rang dans ce groupe).
//
// Tableaux écrits : line_section, line_sort, line_text, line_order, line_probability,
// line_probability_low, line_probability_high, line_core, line_nested, line_effect, line_composite ;
// variable écrite : line_count.

DEFINE_PATCH_MACRO ad_lines_reset BEGIN
	SET line_count = 0
	SET line_phrase = 0
	SET line_any_form = 0
	SET line_no_duration = 0
	SET line_probability = 0
	SET line_sub_probability = 0
	SPRINT line_core ~~
	SET line_nested = 0
	SET line_composite = 0
	SPRINT line_suffix ~~
	SPRINT line_sentence ~~
	SPRINT line_condition ~~
	SPRINT line_the_target ~~
	SPRINT line_only_for ~~
	SPRINT stat_line_macro ~~
	SPRINT stat_percent_100 ~~
	SET line_save_for_half = 0
	SET line_fail_for_half = 0
END

// Ajoute la ligne line_text à la section line_section, au rang line_sort (effet probable :
// line_probability et sa plage, line_core). Une ligne de même texte (casse ignorée) et de même plage
// déjà dans la section n'est pas ajoutée : l'ancien moteur garde la première (get_unique_effects).
DEFINE_PATCH_MACRO ad_line_add BEGIN
	SPRINT line_new_text ~%line_text%~
	TO_LOWER line_new_text
	SET line_duplicate = 0
	FOR (line_id = 0; line_id < line_count AND NOT line_duplicate; ++line_id) BEGIN
		SPRINT line_old_section $line_section(~%line_id%~)
		SPRINT line_old_text $line_text(~%line_id%~)
		TO_LOWER line_old_text
		SET line_duplicate = (~%line_old_section%~ STRING_EQUAL ~%line_section%~) AND (~%line_old_text%~ STRING_EQUAL ~%line_new_text%~)
			AND (line_probability == 0 OR ($line_probability_low(~%line_id%~) == line_probability_low
				AND $line_probability_high(~%line_id%~) == line_probability_high))
	END
	PATCH_IF NOT line_duplicate BEGIN
		SET line_nested = 0
		LPM ad_line_append
	END
END

// Ajoute la ligne sans contrôle de doublon (ad_line_add), en retrait si line_nested.
DEFINE_PATCH_MACRO ad_line_append BEGIN
	SET $line_order(~%line_count%~) = line_count
	SPRINT $line_section(~%line_count%~) ~%line_section%~
	SET $line_sort(~%line_count%~) = line_sort
	SPRINT $line_text(~%line_count%~) ~%line_text%~
	SET $line_probability(~%line_count%~) = line_probability
	SET $line_probability_low(~%line_count%~) = line_probability > 0 ? line_probability_low : 0
	SET $line_probability_high(~%line_count%~) = line_probability > 0 ? line_probability_high : 0
	SET $line_sub_probability(~%line_count%~) = line_sub_probability
	PATCH_IF line_probability > 0 OR line_sub_probability > 0 BEGIN
		SET $line_effect(~%line_count%~) = line_fx
	END
	SPRINT $line_core(~%line_count%~) ~%line_core%~
	SET $line_nested(~%line_count%~) = line_nested
	SET $line_composite(~%line_count%~) = line_composite
	SET line_count += 1
END

// Regroupement par probabilité des lignes probables de la section prob_section (ancien
// group_probability_effects, pour les capacités de combat) : ces lignes sont retirées puis
// réécrites après les autres, segment par segment. Le tri de l'ancien moteur les range par plage
// (borne basse, puis haute), égalités dans l'ordre inverse de ses lignes (V37), produites opcode par
// opcode dans l'ordre où chacun apparaît d'abord dans le bloc (ad_lines_opcode_rank), puis dans
// l'ordre de la section. Segments : une plage
// par couple de bornes ; avec AD_USE_COMPLEX_GROUPING_OF_PROBABILITY_RANGES, chaque intervalle entre
// deux bornes consécutives, avec les effets actifs sur tout l'intervalle (un effet peut être dans
// plusieurs), les segments aux mêmes effets réunis en additionnant leurs probabilités. Un segment
// d'un effet garde sa ligne (avec la probabilité du segment) ; un segment de plusieurs a un titre
// « 11 % de chances » suivi de ses effets en retrait.
// Rang prob_rank de l'opcode de la ligne probable prob_id parmi les opcodes de son bloc, dans l'ordre
// de leur premier effet lu (ordre du tableau des opcodes de l'ancien moteur).
DEFINE_PATCH_MACRO ad_lines_opcode_rank BEGIN
	SET prob_fx = $line_effect(~%prob_id%~)
	SET prob_opcode = $fx_opcode(~%prob_fx%~)
	SPRINT prob_scope $fx_scope(~%prob_fx%~)
	// Marque propre à cet appel : CLEAR_ARRAY ne défait pas les éléments que VARIABLE_IS_SET teste (V36).
	SET prob_rank_call = VARIABLE_IS_SET prob_rank_call ? prob_rank_call + 1 : 1
	SET prob_rank = 0
	FOR (prob_other = 0; prob_other < fx_count AND prob_rank >= 0; ++prob_other) BEGIN
		SPRINT prob_other_scope $fx_scope(~%prob_other%~)
		SET prob_other_opcode = $fx_opcode(~%prob_other%~)
		PATCH_IF ~%prob_other_scope%~ STRING_EQUAL ~%prob_scope%~ BEGIN
			PATCH_IF prob_other_opcode == prob_opcode BEGIN
				SET prob_final_rank = prob_rank
				SET prob_rank = 0 - 1
			END
			ELSE PATCH_IF NOT VARIABLE_IS_SET $prob_rank_seen(~%prob_other_opcode%~) OR $prob_rank_seen(~%prob_other_opcode%~) != prob_rank_call BEGIN
				SET $prob_rank_seen(~%prob_other_opcode%~) = prob_rank_call
				SET prob_rank += 1
			END
		END
	END
	SET prob_rank = prob_final_rank > 99 ? 99 : prob_final_rank
END

// Sous-sort d'un effet probable (146, 148 : ctx_base_lines) : ses effets certains ont la plage du
// parent (fx_parent_probability), ses effets probables gardent la leur, même égale. Comme l'ancien moteur, ces derniers sont d'abord
// regroupés entre eux (passe intérieure, prob_inner) ; chaque groupe devient une ligne composée
// (line_composite), à la plage du parent, écrite sous son titre avec les effets certains : « 2 % de
// chances » puis « 66 % de chances de… », ou « 13 % de chances » et ses lignes en second retrait.
DEFINE_PATCH_MACRO ad_lines_probability_groups BEGIN
	LPM ad_lines_split_sub_probability
	SET prob_inner = 0
	PATCH_IF ctx_base_probability < 100 AND ctx_base_lines BEGIN
		SPRINT prob_outer_section ~%prob_section%|outer~
		FOR (prob_id = 0; prob_id < line_count; ++prob_id) BEGIN
			SPRINT prob_line_section $line_section(~%prob_id%~)
			PATCH_IF (~%prob_line_section%~ STRING_EQUAL ~%prob_section%~) AND $line_probability(~%prob_id%~) > 0 BEGIN
				SET prob_fx = $line_effect(~%prob_id%~)
				PATCH_IF $fx_parent_probability(~%prob_fx%~) BEGIN
					SPRINT $line_section(~%prob_id%~) ~%prob_outer_section%~
				END
				ELSE BEGIN
					SET prob_inner = 1
				END
			END
		END
		PATCH_IF prob_inner BEGIN
			LPM ad_lines_probability_pass
			SET prob_inner = 0
		END
		FOR (prob_id = 0; prob_id < line_count; ++prob_id) BEGIN
			SPRINT prob_line_section $line_section(~%prob_id%~)
			PATCH_IF ~%prob_line_section%~ STRING_EQUAL ~%prob_outer_section%~ BEGIN
				SPRINT $line_section(~%prob_id%~) ~%prob_section%~
			END
		END
	END
	LPM ad_lines_probability_pass
END

// Ligne d'un sort lancé par un effet probable (146, 148), dont les lignes sont déjà réunies sous sa
// probabilité (line_sub_probability) : comme dans l'ancien moteur, chacune rejoint le regroupement de
// la section, avec les effets de même plage (C!KT30 : « 11 % de chances » puis la paralysie du sort et
// la vitesse de l'arme). Une ligne d'une autre forme (sous une condition) reste entière. Les
// sous-lignes sont ajoutées de la dernière à la première : à rang égal, la dernière ajoutée vient en
// premier.
DEFINE_PATCH_MACRO ad_lines_split_sub_probability BEGIN
	SET split_line_count = line_count
	FOR (split_id = 0; split_id < split_line_count; ++split_id) BEGIN
		SPRINT split_section $line_section(~%split_id%~)
		SET split_opcode = 0
		PATCH_IF $line_sub_probability(~%split_id%~) > 0 BEGIN
			SET split_fx = $line_effect(~%split_id%~)
			SET split_opcode = $fx_opcode(~%split_fx%~)
		END
		PATCH_IF (~%split_section%~ STRING_EQUAL ~%prob_section%~) AND (split_opcode == 146 OR split_opcode == 148) BEGIN
			SET value = $line_sub_probability(~%split_id%~)
			SPRINT probability @1200003 // ~%value%%PERCENT%~
			SPRINT split_title @4000001 // ~%probability% de chances~
			SPRINT split_text $line_text(~%split_id%~)
			SET split_title_length = STRING_LENGTH ~%split_title%~
			CLEAR_ARRAY split_members
			SET split_member_count = 0
			SET split_title_form = INDEX (CASE_SENSITIVE EXACT_MATCH ~%split_title%%CRLF%  - ~ ~%split_text%~) == 0
			PATCH_IF split_title_form BEGIN
				SPRINT split_rest ~~
				INNER_PATCH_SAVE split_rest ~%split_text%~ BEGIN
					DELETE_BYTES 0 split_title_length
				END
				SPRINT split_check ~%split_title%~
				INNER_PATCH ~%split_rest%~ BEGIN
					REPLACE_EVALUATE CASE_SENSITIVE ~%CRLF%  - \(\([^%CRLF%]\|%CRLF%    \)*\)~ BEGIN
						SPRINT $split_members(~%split_member_count%~) ~%MATCH1%~
						SPRINT split_check ~%split_check%%CRLF%  - %MATCH1%~
						SET split_member_count += 1
					END ~~
				END
				// Texte d'une autre forme que prévu : ligne gardée entière.
				PATCH_IF NOT (~%split_check%~ STRING_EQUAL ~%split_text%~) BEGIN
					SET split_member_count = 0
				END
			END
			ELSE PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~%split_title% ~ ~%split_text%~) == 0 BEGIN
				INNER_PATCH_SAVE split_core ~%split_text%~ BEGIN
					DELETE_BYTES 0 split_title_length + 1
				END
				SPRINT $split_members(~0~) ~%split_core%~
				SET split_member_count = 1
			END
			PATCH_IF split_member_count > 0 BEGIN
				SET line_probability = value
				SET line_probability_low = $fx_probability_low(~%split_fx%~)
				SET line_probability_high = $fx_probability_high(~%split_fx%~)
				SET line_fx = split_fx
				SET line_sort = $line_sort(~%split_id%~)
				SET line_nested = 0
				SPRINT line_section ~%split_section%~
				SET line_sub_probability = 0
				FOR (split_k = split_member_count - 1; split_k >= 0; split_k = split_k - 1) BEGIN
					SPRINT line_core $split_members(~%split_k%~)
					SPRINT line_text ~%split_title% %line_core%~
					// Groupe intérieur seul sous le titre du sort : il garde ce titre. Plusieurs sous-lignes
					// gardent l'ordre du sort.
					SET line_composite = 0
					PATCH_IF split_title_form AND split_member_count == 1 BEGIN
						SET line_composite = 1000000
					END
					PATCH_IF split_k == split_member_count - 1 BEGIN
						SPRINT $line_text(~%split_id%~) ~%line_text%~
						SET $line_probability(~%split_id%~) = line_probability
						SET $line_probability_low(~%split_id%~) = line_probability_low
						SET $line_probability_high(~%split_id%~) = line_probability_high
						SPRINT $line_core(~%split_id%~) ~%line_core%~
						SET $line_composite(~%split_id%~) = line_composite
						SET $line_sub_probability(~%split_id%~) = 0
					END
					ELSE BEGIN
						LPM ad_line_append
					END
				END
				SET line_probability = 0
				SPRINT line_core ~~
				SET line_composite = 0
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_lines_probability_pass BEGIN
	CLEAR_ARRAY prob_keys
	FOR (prob_id = 0; prob_id < line_count; ++prob_id) BEGIN
		SPRINT prob_line_section $line_section(~%prob_id%~)
		PATCH_IF (~%prob_line_section%~ STRING_EQUAL ~%prob_section%~) AND $line_probability(~%prob_id%~) > 0 BEGIN
			LPM ad_lines_opcode_rank
			SET prob_key = ($line_probability_low(~%prob_id%~) * 100 + $line_probability_high(~%prob_id%~)) * 100000
				+ (99 - prob_rank) * 1000 + 999 - $line_order(~%prob_id%~)
			SET $prob_keys(~%prob_key%~) = prob_id
			SPRINT $line_section(~%prob_id%~) ~~
		END
	END
	SORT_ARRAY_INDICES prob_keys NUMERICALLY
	CLEAR_ARRAY prob_lines
	SET prob_count = 0
	PHP_EACH prob_keys AS _ => prob_id BEGIN
		SET $prob_lines(~%prob_count%~) = prob_id
		SET prob_count += 1
	END

	// Segments : seg_low, seg_high, seg_size, seg_member(~s k~), seg_probability, seg_duplicate.
	SET seg_count = 0
	PATCH_IF NOT AD_USE_COMPLEX_GROUPING_OF_PROBABILITY_RANGES BEGIN
		FOR (prob_k = 0; prob_k < prob_count; ++prob_k) BEGIN
			SET prob_id = $prob_lines(~%prob_k%~)
			SET prob_low = $line_probability_low(~%prob_id%~)
			SET prob_high = $line_probability_high(~%prob_id%~)
			SET seg_last = seg_count - 1
			PATCH_IF seg_count == 0 BEGIN
				SET prob_new_segment = 1
			END
			ELSE BEGIN
				SET prob_new_segment = prob_low != $seg_low(~%seg_last%~) OR prob_high != $seg_high(~%seg_last%~)
			END
			PATCH_IF prob_new_segment BEGIN
				SET $seg_low(~%seg_count%~) = prob_low
				SET $seg_high(~%seg_count%~) = prob_high
				SET $seg_size(~%seg_count%~) = 0
				SET seg_count += 1
			END
			SET seg_last = seg_count - 1
			SET seg_k = $seg_size(~%seg_last%~)
			SET $seg_member(~%seg_last% %seg_k%~) = prob_id
			SET $seg_size(~%seg_last%~) = seg_k + 1
		END
	END
	ELSE BEGIN
		CLEAR_ARRAY prob_bounds
		FOR (prob_k = 0; prob_k < prob_count; ++prob_k) BEGIN
			SET prob_id = $prob_lines(~%prob_k%~)
			SET prob_low = $line_probability_low(~%prob_id%~)
			SET prob_after = $line_probability_high(~%prob_id%~) + 1
			SET $prob_bounds(~%prob_low%~) = 1
			SET $prob_bounds(~%prob_after%~) = 1
		END
		SORT_ARRAY_INDICES prob_bounds NUMERICALLY
		SET prob_previous = 0 - 1
		PHP_EACH prob_bounds AS prob_bound => _ BEGIN
			PATCH_IF prob_previous >= 0 BEGIN
				SET $seg_low(~%seg_count%~) = prob_previous
				SET $seg_high(~%seg_count%~) = prob_bound - 1
				SET seg_k = 0
				FOR (prob_k = 0; prob_k < prob_count; ++prob_k) BEGIN
					SET prob_id = $prob_lines(~%prob_k%~)
					PATCH_IF $line_probability_low(~%prob_id%~) <= prob_previous AND $line_probability_high(~%prob_id%~) >= prob_bound - 1 BEGIN
						SET $seg_member(~%seg_count% %seg_k%~) = prob_id
						SET seg_k += 1
					END
				END
				SET $seg_size(~%seg_count%~) = seg_k
				PATCH_IF seg_k > 0 BEGIN
					SET seg_count += 1
				END
			END
			SET prob_previous = prob_bound
		END
	END
	FOR (seg_s = 0; seg_s < seg_count; ++seg_s) BEGIN
		SET $seg_probability(~%seg_s%~) = $seg_high(~%seg_s%~) - $seg_low(~%seg_s%~) + 1
		SET $seg_duplicate(~%seg_s%~) = 0
	END
	// Mode complexe : les segments sont disjoints, ceux aux mêmes effets s'additionnent sans erreur.
	PATCH_IF AD_USE_COMPLEX_GROUPING_OF_PROBABILITY_RANGES BEGIN
		CLEAR_ARRAY prob_signatures
		FOR (seg_s = 0; seg_s < seg_count; ++seg_s) BEGIN
			SPRINT prob_signature ~~
			FOR (seg_k = 0; seg_k < $seg_size(~%seg_s%~); ++seg_k) BEGIN
				SET prob_id = $seg_member(~%seg_s% %seg_k%~)
				SPRINT prob_core $line_core(~%prob_id%~)
				SPRINT prob_signature ~%prob_signature%|%prob_core%~
			END
			PATCH_IF VARIABLE_IS_SET $prob_signatures(~%prob_signature%~) BEGIN
				SET prob_owner = $prob_signatures(~%prob_signature%~)
				SET $seg_probability(~%prob_owner%~) = $seg_probability(~%prob_owner%~) + $seg_probability(~%seg_s%~)
				SET $seg_duplicate(~%seg_s%~) = 1
			END
			ELSE BEGIN
				SET $prob_signatures(~%prob_signature%~) = seg_s
			END
		END
	END

	// Lignes rangées par probabilité décroissante ; à probabilité égale, un titre suit les lignes
	// seules (SPWI714). Deux titres de même probabilité : l'ancien moteur les range selon l'opcode du
	// dernier effet lu, connu seulement de lui, refus ; sous la probabilité d'un parent, il les garde
	// dans l'ordre de leurs plages (PXW7ENER).
	CLEAR_ARRAY prob_band_titles
	FOR (seg_s = 0; seg_s < seg_count; ++seg_s) BEGIN
		PATCH_IF NOT prob_inner AND NOT $seg_duplicate(~%seg_s%~) AND $seg_size(~%seg_s%~) > 1 BEGIN
			SET prob_band = 100 - $seg_probability(~%seg_s%~)
			PATCH_IF VARIABLE_IS_SET $prob_band_titles(~%prob_band%~) BEGIN
				LPF ad_refusal STR_VAR reason = ~not_implemented:application:probability_order~ message = ~probable titles of the same probability, whose order the old engine sets differently~ RET render_late_missing = refusal END
			END
			SET $prob_band_titles(~%prob_band%~) = 1
		END
	END

	SPRINT line_section ~%prob_section%~
	SET line_probability = 0
	SPRINT line_core ~~
	FOR (seg_s = 0; seg_s < seg_count; ++seg_s) BEGIN
		PATCH_IF NOT $seg_duplicate(~%seg_s%~) BEGIN
			SET value = $seg_probability(~%seg_s%~)
			SPRINT probability @1200003 // ~%value%%PERCENT%~
			SET prob_first = $seg_member(~%seg_s% 0~)
			PATCH_IF $seg_size(~%seg_s%~) == 1 AND NOT $line_composite(~%prob_first%~) BEGIN
				SET prob_id = prob_first
				SPRINT description_saved ~%description%~
				SPRINT description $line_core(~%prob_id%~)
				SPRINT line_text @4000000 // ~%probability% de chances %description%~
				SPRINT description ~%description_saved%~
				SET line_sort = $line_sort(~%prob_id%~)
				SET line_nested = 0
				// Ligne seule d'un groupe intérieur : sa probabilité, égalités inversées.
				SET prob_composite = (100 - value) * 1000 + 999 - seg_s
				LPM ad_lines_probability_emit
			END
			ELSE BEGIN
				SET line_sort = (100 - value) * 10000 + 9999 - $seg_size(~%seg_s%~)
				SPRINT line_text @4000001 // ~%probability% de chances~
				SET line_nested = 0
				SPRINT prob_composite_text ~%line_text%~
				PATCH_IF NOT prob_inner BEGIN
					LPM ad_line_append
				END
				SET line_nested = 1
				// Lignes d'un sort lancé par un effet probable (146, 148) : l'ancien moteur les écrit dans
				// l'ordre de leurs rangs, sous la ligne de l'effet (SPPR450) : line_sort, rang de l'opcode
				// plus (100 - probabilité) × 10 000 (ancien set_opcode_sort), la probabilité du parent pour
				// un effet certain, la sienne pour une ligne seule d'un groupe intérieur ; les titres
				// intérieurs ensuite.
				CLEAR_ARRAY prob_nested
				FOR (seg_k = 0; seg_k < $seg_size(~%seg_s%~); ++seg_k) BEGIN
					SET prob_id = $seg_member(~%seg_s% %seg_k%~)
					SET prob_member_composite = $line_composite(~%prob_id%~)
					SET prob_member_sort = $line_sort(~%prob_id%~) < 0 ? 0 : ($line_sort(~%prob_id%~) > 1999999 ? 1999999 : $line_sort(~%prob_id%~))
					PATCH_IF prob_member_composite > 0 AND prob_member_composite < 1000000 BEGIN
						SET prob_nested_key = 100000000 + prob_member_sort * 500 + prob_member_composite MODULO 500
					END
					ELSE PATCH_IF prob_member_composite >= 1000000 BEGIN
						SET prob_nested_key = 2000000000 + prob_member_composite - 1000000
					END
					ELSE PATCH_IF ctx_base_lines AND NOT prob_inner BEGIN
						SET prob_nested_key = 100000000 + prob_member_sort * 500 + (seg_k > 499 ? 499 : seg_k)
					END
					ELSE BEGIN
						SET prob_nested_key = seg_k
					END
					SET $prob_nested(~%prob_nested_key%~) = prob_id
				END
				SORT_ARRAY_INDICES prob_nested NUMERICALLY
				SET prob_title_sort = line_sort
				PHP_EACH prob_nested AS _ => prob_id BEGIN
					SPRINT line_text $line_core(~%prob_id%~)
					PATCH_IF prob_inner BEGIN
						SPRINT prob_composite_text ~%prob_composite_text%%CRLF%    - %line_text%~
					END
					ELSE BEGIN
						SET line_sort += 1
						LPM ad_line_append
					END
				END
				PATCH_IF prob_inner BEGIN
					SET line_sort = prob_title_sort
					SET line_nested = 0
					SPRINT line_text ~%prob_composite_text%~
					// Titres intérieurs : par probabilité décroissante, égalités dans l'ordre des plages.
					SET prob_composite = 1000000 + (100 - value) * 1000 + seg_s
					LPM ad_lines_probability_emit
				END
			END
		END
	END
	SET line_nested = 0
END

// Ligne d'un segment (line_text, line_sort) : écrite telle quelle, ou, dans la passe intérieure, ligne
// composée à la plage du parent, de rang prob_composite sous son titre.
DEFINE_PATCH_MACRO ad_lines_probability_emit BEGIN
	PATCH_IF prob_inner BEGIN
		SET line_fx = $line_effect(~%prob_first%~)
		SET line_probability = ctx_base_probability
		SET line_probability_low = ctx_base_low
		SET line_probability_high = ctx_base_high
		SPRINT line_core ~%line_text%~
		SET line_composite = prob_composite
		LPM ad_line_append
		SET line_probability = 0
		SPRINT line_core ~~
		SET line_composite = 0
	END
	ELSE BEGIN
		LPM ad_line_append
	END
END

// Passage de tri de la section line_pass_section : ses lignes prennent l'ordre que leur donne un tri
// de l'ancien moteur (rang croissant, égalités inversées) ; une ligne ajoutée ensuite vient après
// elles.
DEFINE_PATCH_MACRO ad_lines_sort_pass BEGIN
	CLEAR_ARRAY line_pass_keys
	SET line_pass_count = 0
	FOR (line_pass_id = 0; line_pass_id < line_count; ++line_pass_id) BEGIN
		SPRINT line_pass_line_section $line_section(~%line_pass_id%~)
		PATCH_IF ~%line_pass_line_section%~ STRING_EQUAL ~%line_pass_section%~ BEGIN
			SET line_pass_key = ($line_sort(~%line_pass_id%~) + 100) * 1000 + 999 - $line_order(~%line_pass_id%~)
			SET $line_pass_keys(~%line_pass_key%~) = line_pass_id
			SET line_pass_count += 1
		END
	END
	SORT_ARRAY_INDICES line_pass_keys NUMERICALLY
	SET line_pass_order = 0
	PHP_EACH line_pass_keys AS _ => line_pass_id BEGIN
		SET $line_order(~%line_pass_id%~) = line_pass_order
		SET line_pass_order += 1
	END
END

// Lignes de la section, chacune précédée d'un saut de ligne et de la marque de son niveau (ancien
// add_items_section_to_description) : 1 puce, 2 retrait sous un titre, 0 rien ; vide si la section
// n'a aucune ligne. count : nombre de lignes.
DEFINE_PATCH_FUNCTION ad_lines_section_text
	INT_VAR
		level = 1
		strip_sections = 1
	STR_VAR
		section = ~~
	RET
		text
		count
BEGIN
	SPRINT text ~~
	SET count = 0
	SPRINT line_prefix ~~
	PATCH_IF level == 1 BEGIN
		SPRINT line_prefix ~- ~
	END
	ELSE PATCH_IF level == 2 BEGIN
		SPRINT line_prefix ~  ~
	END
	// Clé numérique unique (rang, ordre d'ajout inversé) ; le décalage rend les rangs négatifs
	// triables.
	PATCH_IF line_count > 1000 BEGIN
		PATCH_FAIL ~New engine: more than 1000 lines in a description~
	END
	CLEAR_ARRAY section_lines
	FOR (line_id = 0; line_id < line_count; ++line_id) BEGIN
		SPRINT line_section $line_section(~%line_id%~)
		PATCH_IF ~%line_section%~ STRING_EQUAL ~%section%~ BEGIN
			SET line_sort = $line_sort(~%line_id%~)
			PATCH_IF line_sort < 0 - 100 OR line_sort > 2000000 BEGIN
				PATCH_FAIL ~New engine: line sort %line_sort% out of bounds~
			END
			SET line_key = (line_sort + 100) * 1000 + 999 - $line_order(~%line_id%~)
			SET $section_lines(~%line_key%~) = line_id
		END
	END
	SORT_ARRAY_INDICES section_lines NUMERICALLY
	PHP_EACH section_lines AS _ => line_id BEGIN
		SPRINT line_text $line_text(~%line_id%~)
		// Texte qui commence par deux sauts de ligne (sections de niveaux d'un sous-sort) : écrit sans
		// puce, ces sauts retirés, comme l'ancien add_items_section_to_description ; gardé tel quel dans
		// le texte d'un sous-sort (strip_sections à 0), qui le transmet à sa ligne parente.
		PATCH_IF strip_sections AND INDEX (CASE_SENSITIVE EXACT_MATCH ~%CRLF%%CRLF%~ ~%line_text%~) == 0 BEGIN
			INNER_PATCH_SAVE line_text ~%line_text%~ BEGIN
				DELETE_BYTES 0 2 * STRING_LENGTH ~%CRLF%~
			END
			SPRINT text ~%text%%CRLF%%line_text%~
		END
		ELSE PATCH_IF $line_nested(~%line_id%~) BEGIN
			SPRINT text ~%text%%CRLF%  %line_prefix%%line_text%~
		END
		ELSE BEGIN
			SPRINT text ~%text%%CRLF%%line_prefix%%line_text%~
		END
		SET count += 1
	END
	PATCH_IF level == 1 BEGIN
		LPF ad_group_condition_lines STR_VAR text RET text END
	END
END

// Lignes de même condition réunies (« - Si … ; 7 % de chances … » et « - Si … ; 2 % de chances … », ancien
// group_condition_lines) : la condition seule à la place de la première, puis la suite de chacune en retrait, avec
// ses sous-lignes. Une condition dont une ligne n'a pas de suite (ses effets sont déjà en retrait dessous) n'est pas
// réunie.
DEFINE_PATCH_FUNCTION ad_group_condition_lines
	STR_VAR
		text = ~~
	RET
		text
BEGIN
	CLEAR_ARRAY cond_lines
	CLEAR_ARRAY cond_names
	CLEAR_ARRAY cond_counts
	CLEAR_ARRAY cond_bare
	CLEAR_ARRAY cond_done
	SET cond_line_count = 0
	INNER_PATCH ~%text%~ BEGIN
		REPLACE_EVALUATE CASE_SENSITIVE ~%CRLF%\([^%CRLF%]*\)~ BEGIN
			SPRINT $cond_lines(~%cond_line_count%~) ~%MATCH1%~
			SET cond_line_count += 1
		END ~~
	END
	SET cond_found = 0
	SET cond_semicolon_length = STRING_LENGTH ~%AD_SEMICOLON%~
	FOR (cond_i = 0; cond_i < cond_line_count; ++cond_i) BEGIN
		SPRINT cond_line $cond_lines(~%cond_i%~)
		SPRINT cond_name ~~
		PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~- ~ ~%cond_line%~) == 0 BEGIN
			SET cond_at = INDEX (CASE_SENSITIVE EXACT_MATCH ~%AD_SEMICOLON%~ ~%cond_line%~)
			PATCH_IF cond_at > 2 BEGIN
				INNER_PATCH_SAVE cond_name ~%cond_line%~ BEGIN
					DELETE_BYTES cond_at (BUFFER_LENGTH - cond_at)
					DELETE_BYTES 0 2
				END
				SET cond_seen = VARIABLE_IS_SET $cond_counts(~%cond_name%~) ? $cond_counts(~%cond_name%~) : 0
				SET $cond_counts(~%cond_name%~) = cond_seen + 1
				PATCH_IF cond_seen == 1 BEGIN
					SET cond_found = 1
				END
				PATCH_IF cond_at + cond_semicolon_length >= STRING_LENGTH ~%cond_line%~ BEGIN
					SET $cond_bare(~%cond_name%~) = 1
				END
			END
		END
		SPRINT $cond_names(~%cond_i%~) ~%cond_name%~
	END
	PATCH_IF cond_found BEGIN
		SPRINT text ~~
		SET cond_i = 0
		WHILE cond_i < cond_line_count BEGIN
			SPRINT cond_line $cond_lines(~%cond_i%~)
			SPRINT cond_name $cond_names(~%cond_i%~)
			SET cond_grouped = 0
			PATCH_IF NOT (~%cond_name%~ STRING_EQUAL ~~) BEGIN
				SET cond_grouped = $cond_counts(~%cond_name%~) > 1 AND NOT VARIABLE_IS_SET $cond_bare(~%cond_name%~)
			END
			PATCH_IF NOT cond_grouped BEGIN
				SPRINT text ~%text%%CRLF%%cond_line%~
				SET cond_i += 1
			END
			ELSE BEGIN
				PATCH_IF NOT VARIABLE_IS_SET $cond_done(~%cond_name%~) BEGIN
					SET $cond_done(~%cond_name%~) = 1
					SPRINT text ~%text%%CRLF%- %cond_name%%AD_SEMICOLON%~
					SET cond_head_length = STRING_LENGTH ~- %cond_name%%AD_SEMICOLON%~
					FOR (cond_j = cond_i; cond_j < cond_line_count; ++cond_j) BEGIN
						SPRINT cond_other $cond_names(~%cond_j%~)
						PATCH_IF ~%cond_other%~ STRING_EQUAL ~%cond_name%~ BEGIN
							SPRINT cond_member $cond_lines(~%cond_j%~)
							INNER_PATCH_SAVE cond_member ~%cond_member%~ BEGIN
								DELETE_BYTES 0 cond_head_length
							END
							SPRINT text ~%text%%CRLF%  - %cond_member%~
							// Sous-lignes de la ligne réunie : un retrait de plus.
							SET cond_k = cond_j + 1
							SET cond_sub = 1
							WHILE cond_sub AND cond_k < cond_line_count BEGIN
								SPRINT cond_member $cond_lines(~%cond_k%~)
								SET cond_sub = INDEX (CASE_SENSITIVE EXACT_MATCH ~ ~ ~%cond_member%~) == 0
								PATCH_IF cond_sub BEGIN
									// Retrait d'origine des sous-lignes remplacé par celui du niveau suivant.
									PATCH_IF cond_k == cond_j + 1 BEGIN
										INNER_PATCH ~%cond_member%~ BEGIN
											REPLACE_EVALUATE ~^\( *\)~ BEGIN SET cond_indent = STRING_LENGTH ~%MATCH1%~ END ~%MATCH1%~
										END
									END
									INNER_PATCH_SAVE cond_member ~%cond_member%~ BEGIN
										DELETE_BYTES 0 (cond_indent < BUFFER_LENGTH ? cond_indent : 0)
									END
									SPRINT text ~%text%%CRLF%    %cond_member%~
									SET cond_k += 1
								END
							END
						END
					END
				END
				// La ligne et ses sous-lignes sont déjà écrites avec la condition.
				SET cond_i += 1
				SET cond_sub = 1
				WHILE cond_sub AND cond_i < cond_line_count BEGIN
					SPRINT cond_member $cond_lines(~%cond_i%~)
					SET cond_sub = INDEX (CASE_SENSITIVE EXACT_MATCH ~ ~ ~%cond_member%~) == 0
					PATCH_IF cond_sub BEGIN
						SET cond_i += 1
					END
				END
			END
		END
	END
END

// Valeur signée : « +2 » pour un nombre positif, inchangée sinon.
DEFINE_PATCH_FUNCTION ad_signed_value
	INT_VAR
		value = 0
	RET
		text
BEGIN
	SPRINT text ~%value%~
	PATCH_IF value > 0 BEGIN
		SPRINT text @1200001 // ~+%value%~
	END
END

// Dés de dégâts (ancien get_damage_value) : « 1d8 », « 1d6 +2 », « +3 » ; un dé à une face compte
// comme un bonus ; vide sans dé ni bonus.
DEFINE_PATCH_FUNCTION ad_dice_text
	INT_VAR
		dice_count = 0
		dice_sides = 0
		bonus = 0
	RET
		text
BEGIN
	SPRINT text ~~
	PATCH_IF dice_count > 0 BEGIN
		PATCH_IF dice_sides <= 1 BEGIN
			SET bonus += dice_count
		END
		ELSE BEGIN
			SET diceCount = dice_count
			SET diceSides = dice_sides
			SPRINT text @1200005 // ~%diceCount%d%diceSides%~
		END
	END
	PATCH_IF bonus != 0 BEGIN
		LPF ad_signed_value INT_VAR value = bonus RET dice_bonus = text END
		PATCH_IF ~%text%~ STRING_EQUAL ~~ BEGIN
			SPRINT text ~%dice_bonus%~
		END
		ELSE BEGIN
			SPRINT text ~%text% %dice_bonus%~
		END
	END
END

// Distance donnée en pieds : « 4,5 mètres » ou « 15 feet », le .tra choisissant l'unité. Mètres
// arrondis au demi-mètre comme l'ancien feets_to_meters (« 0,5 mètre », « 1 mètre » pour un mètre ou
// moins), pluriel à partir de 2 ; vide en deçà de 0,3 mètre, que l'ancien moteur écrit en décimètres.
DEFINE_PATCH_FUNCTION ad_distance_text
	INT_VAR
		feet = 0
	RET
		text
BEGIN
	SPRINT text ~~
	// Décimètres, troncature de l'ancien moteur (1 pied = 0,3048 mètre).
	SET distance_decimeters = feet * 10000 / 3281
	PATCH_IF distance_decimeters >= 3 BEGIN
		SET distance_units = distance_decimeters / 10
		SET distance_tenths = distance_decimeters MODULO 10
		SET distance_half = distance_tenths >= 3 AND distance_tenths <= 7
		PATCH_IF distance_tenths > 7 BEGIN
			SET distance_units += 1
		END
		SET distance_feet = feet
		LPF ad_tra INT_VAR tra_id = 1100000 + (distance_units > 1 ? 1 : 0) + 2 * distance_half
			tra_block_start = 1100000 tra_block_size = 4 RET text END // ~%distance_units% mètre~
	END
END

// Nombre de lignes de premier niveau (« - » en début de ligne) du texte text (ancien
// count_description_lines) : un titre de section s'accorde à ce nombre.
DEFINE_PATCH_FUNCTION ad_count_text_lines
	STR_VAR
		text = ~~
	RET
		count
BEGIN
	SET count = 0
	INNER_PATCH ~%text%~ BEGIN
		COUNT_REGEXP_INSTANCES CASE_SENSITIVE EXACT_MATCH ~%CRLF%- ~ count
	END
END

// Texte à première lettre capitale (ancien ucfirst) : seul un premier caractère ASCII change.
DEFINE_PATCH_FUNCTION ad_ucfirst
	STR_VAR
		text = ~~
	RET
		text
BEGIN
	PATCH_IF STRING_LENGTH ~%text%~ > 0 BEGIN
		SNPRINT 1 ucfirst_first ~%text%~
		TO_UPPER ucfirst_first
		INNER_PATCH_SAVE text ~%text%~ BEGIN
			WRITE_ASCIIE 0 ~%ucfirst_first%~
		END
	END
END

// Éléments du tableau array_name, dans l'ordre d'ajout : « a », « a et b », « a, b et c » ;
// séparateurs glue et final_glue (vide : « et » entouré d'espaces).
DEFINE_PATCH_FUNCTION ad_join
	STR_VAR
		array_name = ~~
		glue = ~, ~
		final_glue = ~~
	RET
		text
BEGIN
	PATCH_IF ~%final_glue%~ STRING_EQUAL ~~ BEGIN
		SPRINT final_glue ~ %AD_AND% ~
	END
	SET join_count = 0
	PHP_EACH ~%array_name%~ AS _ => _ BEGIN
		SET join_count += 1
	END
	SPRINT text ~~
	SET join_index = 0
	PHP_EACH ~%array_name%~ AS _ => join_item BEGIN
		SET join_index += 1
		PATCH_IF join_index == 1 BEGIN
			SPRINT text ~%join_item%~
		END
		ELSE PATCH_IF join_index < join_count BEGIN
			SPRINT text ~%text%%glue%%join_item%~
		END
		ELSE BEGIN
			SPRINT text ~%text%%final_glue%%join_item%~
		END
	END
END
