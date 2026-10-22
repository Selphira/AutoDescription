// Lignes d'une description, rangées avant le rendu : section, rang de tri, texte. Le texte n'est
// assemblé qu'au rendu de la section, dans l'ordre des rangs ; à rang égal, la ligne qui vient en
// dernier dans la section vient en premier, comme dans l'ancien moteur (son tri ne compare que le
// rang et inverse l'ordre des égalités, V37). L'ordre d'une section est celui des ajouts, sauf après
// un passage de tri (ad_lines_sort_pass), pour une section que l'ancien moteur trie deux fois. Une
// ligne d'effet probable garde sa probabilité (line_probability, 0 pour une autre ligne), sa plage
// (line_probability_low, line_probability_high) et son texte sans « N % de chances » (line_core),
// pour le regroupement par plage (ad_lines_probability_groups) ; line_nested : ligne en retrait sous
// le titre de son groupe ; line_effect : effet (line_fx) d'une ligne probable.
//
// Tableaux écrits : line_section, line_sort, line_text, line_order, line_probability,
// line_probability_low, line_probability_high, line_core, line_nested, line_effect ; variable écrite :
// line_count.

DEFINE_PATCH_MACRO ad_lines_reset BEGIN
	SET line_count = 0
	SET line_phrase = 0
	SET line_any_form = 0
	SET line_no_duration = 0
	SET line_probability = 0
	SPRINT line_core ~~
	SET line_nested = 0
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
	PATCH_IF line_probability > 0 BEGIN
		SET $line_effect(~%line_count%~) = line_fx
	END
	SPRINT $line_core(~%line_count%~) ~%line_core%~
	SET $line_nested(~%line_count%~) = line_nested
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

DEFINE_PATCH_MACRO ad_lines_probability_groups BEGIN
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

	// Rang d'un titre : l'ancien moteur le calcule avec l'opcode du dernier effet lu, connu seulement
	// de lui ; il ne compte que face aux lignes de même probabilité, refusées.
	CLEAR_ARRAY prob_band_lines
	CLEAR_ARRAY prob_band_titles
	FOR (seg_s = 0; seg_s < seg_count; ++seg_s) BEGIN
		PATCH_IF NOT $seg_duplicate(~%seg_s%~) BEGIN
			PATCH_IF $seg_size(~%seg_s%~) == 1 BEGIN
				SET prob_id = $seg_member(~%seg_s% 0~)
				SET prob_band = $line_sort(~%prob_id%~) / 10000
				SET $prob_band_lines(~%prob_band%~) = 1
			END
			ELSE BEGIN
				SET prob_band = 100 - $seg_probability(~%seg_s%~)
				PATCH_IF VARIABLE_IS_SET $prob_band_titles(~%prob_band%~) BEGIN
					SPRINT render_late_missing ~not_implemented:application:probability_order~
				END
				SET $prob_band_titles(~%prob_band%~) = 1
			END
		END
	END
	PHP_EACH prob_band_titles AS prob_band => _ BEGIN
		PATCH_IF VARIABLE_IS_SET $prob_band_lines(~%prob_band%~) BEGIN
			SPRINT render_late_missing ~not_implemented:application:probability_order~
		END
	END

	SPRINT line_section ~%prob_section%~
	SET line_probability = 0
	SPRINT line_core ~~
	FOR (seg_s = 0; seg_s < seg_count; ++seg_s) BEGIN
		PATCH_IF NOT $seg_duplicate(~%seg_s%~) BEGIN
			SET value = $seg_probability(~%seg_s%~)
			SPRINT probability @1200003 // ~%value%%PERCENT%~
			PATCH_IF $seg_size(~%seg_s%~) == 1 BEGIN
				SET prob_id = $seg_member(~%seg_s% 0~)
				SPRINT description_saved ~%description%~
				SPRINT description $line_core(~%prob_id%~)
				SPRINT line_text @4000000 // ~%probability% de chances %description%~
				SPRINT description ~%description_saved%~
				SET line_sort = $line_sort(~%prob_id%~)
				SET line_nested = 0
				LPM ad_line_append
			END
			ELSE BEGIN
				SET line_sort = (100 - value) * 10000
				SPRINT line_text @4000001 // ~%probability% de chances~
				SET line_nested = 0
				LPM ad_line_append
				SET line_nested = 1
				FOR (seg_k = 0; seg_k < $seg_size(~%seg_s%~); ++seg_k) BEGIN
					SET prob_id = $seg_member(~%seg_s% %seg_k%~)
					SPRINT line_text $line_core(~%prob_id%~)
					SET line_sort += 1
					LPM ad_line_append
				END
			END
		END
	END
	SET line_nested = 0
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
		PATCH_IF $line_nested(~%line_id%~) BEGIN
			SPRINT text ~%text%%CRLF%  %line_prefix%%line_text%~
		END
		ELSE BEGIN
			SPRINT text ~%text%%CRLF%%line_prefix%%line_text%~
		END
		SET count += 1
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
// arrondis au demi-mètre comme l'ancien feets_to_meters, pluriel à partir de 2 ; vide pour 1 mètre
// ou moins, que l'ancien moteur écrit faux (« 9 mètres » pour 0,9 mètre).
DEFINE_PATCH_FUNCTION ad_distance_text
	INT_VAR
		feet = 0
	RET
		text
BEGIN
	SPRINT text ~~
	// Décimètres, troncature de l'ancien moteur (1 pied = 0,3048 mètre).
	SET distance_decimeters = feet * 10000 / 3281
	PATCH_IF distance_decimeters > 10 BEGIN
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
