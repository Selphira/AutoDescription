// Lignes d'une description, rangées avant le rendu : section, rang de tri, texte. Le texte n'est
// assemblé qu'au rendu de la section, dans l'ordre des rangs ; à rang égal, la ligne qui vient en
// dernier dans la section vient en premier, comme dans l'ancien moteur (son tri ne compare que le
// rang et inverse l'ordre des égalités, V37). L'ordre d'une section est celui des ajouts, sauf après
// un passage de tri (ad_lines_sort_pass), pour une section que l'ancien moteur trie deux fois.
//
// Tableaux écrits : line_section, line_sort, line_text, line_order ; variable écrite : line_count.

DEFINE_PATCH_MACRO ad_lines_reset BEGIN
	SET line_count = 0
	SET line_phrase = 0
	SPRINT line_suffix ~~
	SET line_save_for_half = 0
	SET line_fail_for_half = 0
END

// Ajoute la ligne line_text à la section line_section, au rang line_sort. Une ligne de même texte
// (casse ignorée) déjà dans la section n'est pas ajoutée : l'ancien moteur garde la première
// (get_unique_effects).
DEFINE_PATCH_MACRO ad_line_add BEGIN
	SPRINT line_new_text ~%line_text%~
	TO_LOWER line_new_text
	SET line_duplicate = 0
	FOR (line_id = 0; line_id < line_count AND NOT line_duplicate; ++line_id) BEGIN
		SPRINT line_old_section $line_section(~%line_id%~)
		SPRINT line_old_text $line_text(~%line_id%~)
		TO_LOWER line_old_text
		SET line_duplicate = (~%line_old_section%~ STRING_EQUAL ~%line_section%~) AND (~%line_old_text%~ STRING_EQUAL ~%line_new_text%~)
	END
	PATCH_IF NOT line_duplicate BEGIN
		SET $line_order(~%line_count%~) = line_count
		SPRINT $line_section(~%line_count%~) ~%line_section%~
		SET $line_sort(~%line_count%~) = line_sort
		SPRINT $line_text(~%line_count%~) ~%line_text%~
		SET line_count += 1
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
		SPRINT text ~%text%%CRLF%%line_prefix%%line_text%~
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
