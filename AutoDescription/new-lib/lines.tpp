// Lignes d'une description, rangées avant le rendu : section, rang de tri, texte. Le texte n'est
// assemblé qu'au rendu de la section, dans l'ordre des rangs ; à rang égal, la dernière ligne
// ajoutée vient en premier, comme dans l'ancien moteur (son tri ne compare que le rang et inverse
// l'ordre d'insertion des égalités, V37).
//
// Tableaux écrits : line_section, line_sort, line_text ; variable écrite : line_count.

DEFINE_PATCH_MACRO ad_lines_reset BEGIN
	SET line_count = 0
	SET line_phrase = 0
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
		SPRINT $line_section(~%line_count%~) ~%line_section%~
		SET $line_sort(~%line_count%~) = line_sort
		SPRINT $line_text(~%line_count%~) ~%line_text%~
		SET line_count += 1
	END
END

// Lignes de la section, chacune précédée d'un saut de ligne et d'une puce (sans puce si bullet = 0) ;
// vide si la section n'a aucune ligne.
DEFINE_PATCH_FUNCTION ad_lines_section_text
	INT_VAR
		bullet = 1
	STR_VAR
		section = ~~
	RET
		text
BEGIN
	SPRINT text ~~
	SPRINT line_prefix ~~
	PATCH_IF bullet BEGIN
		SPRINT line_prefix ~- ~
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
			SET line_key = (line_sort + 100) * 1000 + 999 - line_id
			SET $section_lines(~%line_key%~) = line_id
		END
	END
	SORT_ARRAY_INDICES section_lines NUMERICALLY
	PHP_EACH section_lines AS _ => line_id BEGIN
		SPRINT line_text $line_text(~%line_id%~)
		SPRINT text ~%text%%CRLF%%line_prefix%%line_text%~
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
