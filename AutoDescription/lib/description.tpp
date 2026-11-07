DEFINE_PATCH_FUNCTION ~add_section_to_description~
	INT_VAR
		count = 0
	STR_VAR
		title = ~~
		arrayName = ~~
	RET
		description
BEGIN
	PATCH_IF count > 0 BEGIN
		LPF ~appendSection~ STR_VAR string = ~%title%~ RET description END
		LPF ~add_items_section_to_description~ STR_VAR arrayName RET description END
	END
END

/*
 * Nombre de lignes de premier niveau (« - » en début de ligne) du texte text.
 */
DEFINE_PATCH_FUNCTION ~count_description_lines~
	STR_VAR
		text = ~~
	RET
		countLines
BEGIN
	SET countLines = 0
	INNER_PATCH ~%text%~ BEGIN
		COUNT_REGEXP_INSTANCES CASE_SENSITIVE EXACT_MATCH ~%crlf%- ~ countLines
	END
END

DEFINE_PATCH_FUNCTION ~add_items_section_to_description~
	STR_VAR
		arrayName = ~~
	RET
		description
BEGIN
	SPRINT section_before ~%description%~
	SPRINT description ~~
    SORT_ARRAY_INDICES ~%arrayName%~ NUMERICALLY
    PATCH_PHP_EACH ~%arrayName%~ AS data => value BEGIN
        // Prise en compte des cas où un sort lancé depuis un opcode 146 (ou autre), génère plusieurs lignes...
        // Pas vraiment top de le faire ici...
        INNER_PATCH_SAVE data_5 ~%data_5%~ BEGIN
            found = INDEX_BUFFER (CASE_INSENSITIVE EVALUATE_REGEXP ~^%crlf%%crlf%~)
            PATCH_IF found != "-1" BEGIN
                REPLACE_TEXTUALLY EVALUATE_REGEXP ~^%crlf%%crlf%~ ~~
                SET value = 100
            END
        END

        PATCH_IF value == 100 BEGIN
            LPF ~appendLine~ STR_VAR string = EVAL ~%data_5%~ RET description END
        END
        ELSE PATCH_IF value MODULO 2 == 1 BEGIN
			LPF ~appendProperty~ INT_VAR indentation_num = value / 2 STR_VAR name = EVAL ~%data_5%~ RET description END
		END
		ELSE PATCH_IF value MODULO 2 == 0 BEGIN
			LPF ~appendSubProperty~ STR_VAR name = EVAL ~%data_5%~ RET description END
		END
    END
	LPF ~group_condition_lines~ STR_VAR text = ~%description%~ RET description = text END
	SPRINT description ~%section_before%%description%~
END

DEFINE_PATCH_FUNCTION ~add_global_effects_to_description~
	RET
		description
BEGIN
	PATCH_IF countGlobalLines > 0 BEGIN
        LPF ~appendLine~ RET description END
		LPF ~add_items_section_to_description~ STR_VAR arrayName = ~globalLines~ RET description END
	END
END

DEFINE_PATCH_FUNCTION ~removeTechnicalDescription~ STR_VAR description = "" RET description BEGIN
	SPRINT regex @10008     // ~^[ %TAB%]*\(CARACTÉRISTIQUES\|STATISTIQUES\|PARAMETRES\|PARAMÈTRES\)+\(.*[%MNL%%LNL%%WNL%]*\)*~
	SPRINT replace @100003  // ~PARAMÈTRES~
	// On ne garde que le texte roleplay
	INNER_PATCH_SAVE description ~%description%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~%regex%~ ~%replace%%colon%%crlf%~
	END
	INNER_PATCH ~%description%~ BEGIN
		SET found = 0
        REPLACE_EVALUATE CASE_INSENSITIVE ~\(%replace%\)~ BEGIN
            SPRINT find ~%MATCH1%~
            SET found = 1
        END ~%MATCH1%~
	END
	PATCH_IF found == 0 BEGIN
		SPRINT description ~%description%%crlf%%crlf%%replace%%colon%%crlf%~
	END
END

DEFINE_PATCH_FUNCTION ~appendLine~ INT_VAR strref = 0 STR_VAR string = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT string (AT %strref%)
	END
    SPRINT description "%description%%crlf%%string%"
END

DEFINE_PATCH_FUNCTION ~appendSection~ INT_VAR strref = 0 STR_VAR string = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT string (AT %strref%)
	END
    SPRINT description "%description%%crlf%%crlf%%string%%colon%"
END

DEFINE_PATCH_FUNCTION ~appendValue~ INT_VAR strref = 0 STR_VAR name = "" value = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT name (AT %strref%)
	END
	SPRINT string @100001 // %name%%colon%%value%
    SPRINT description "%description%%crlf%%string%"
END

DEFINE_PATCH_FUNCTION ~appendProperty~ INT_VAR strref = 0 indentation_num = 0 STR_VAR name = "" value = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT name (AT %strref%)
	END

	PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
		SPRINT name @100001 // %name%%colon%%value%
	END

	SPRINT indentation ~~

	FOR (i = 0 ; i < indentation_num ; ++i ) BEGIN
		SPRINT indentation ~%indentation%  ~
	END
    // Cas de l'opcode 146 qui peut retourner plusieurs lignes. Sans cela, seule la première est correctement indentée.
    INNER_PATCH_SAVE name ~%name%~ BEGIN
        REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%- ~ ~%crlf%%indentation%- ~
    END

    SPRINT description "%description%%crlf%%indentation%- %name%"
END

DEFINE_PATCH_FUNCTION ~appendSubProperty~ INT_VAR strref = 0 STR_VAR name = "" value = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT name (AT %strref%)
	END

	PATCH_IF NOT "%value%" STRING_EQUAL "" BEGIN
		SPRINT name @100001 // %name% : %value%
	END
    SPRINT description "%description%%crlf%  %name%"
END

DEFINE_PATCH_FUNCTION ~signed_value~ INT_VAR value = 0 RET value BEGIN
	PATCH_IF value > 0 BEGIN
		SPRINT value @10003
	END
END

// Progression (complex_value) sans le signe de tête : la phrase dit déjà s'il s'agit d'une réduction.
DEFINE_PATCH_FUNCTION ~unsigned_complex_value~ STR_VAR value = ~~ RET value BEGIN
	INNER_PATCH_SAVE value ~%value%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~^- ?~ ~~
	END
END

DEFINE_PATCH_FUNCTION ~percent_value~ INT_VAR value = 0 RET value BEGIN
	PATCH_IF value >= 0 BEGIN
		SPRINT value @10002 // ~%value% %~
	END
END

DEFINE_PATCH_FUNCTION ~replace_last_comma_with~ STR_VAR text = "" str = "" RET text BEGIN
	INNER_PATCH_SAVE text ~%text%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~,\([^,]+\)$~ ~ %str%\1~
	END
END

DEFINE_PATCH_FUNCTION ~array_count~ STR_VAR array_name = ~~ RET count BEGIN
	SET count = 0

	PATCH_PHP_EACH ~%array_name%~ AS entry => _ BEGIN
		SET count += 1
	END
END

DEFINE_PATCH_FUNCTION ~implode~ STR_VAR array_name = ~~ glue = ~, ~ final_glue = ~~ RET text BEGIN
	SPRINT text ~~
	SET idx = 0

	LPF ~array_count~ STR_VAR array_name RET count END

	PATCH_PHP_EACH ~%array_name%~ AS entry => _ BEGIN
		SET idx += 1

		PATCH_IF ~%text%~ STRING_EQUAL ~~ BEGIN
			SPRINT text ~%entry%~
		END
		ELSE BEGIN
			PATCH_IF idx < count BEGIN
				SPRINT real_glue ~%glue%~
			END
			ELSE BEGIN
				SPRINT real_glue ~%final_glue%~
			END
			SPRINT text ~%text%%real_glue%%entry%~
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_random_treasure_names~ STR_VAR file = ~~ RET randomTreasureNames BEGIN
	TO_LOWER file

	SPRINT and @100004 // ~ou~
	SPRINT glue @10020 // ~ », « ~
	SPRINT final_glue @10021 // ~ » %and% « ~
	LPF ~implode~ STR_VAR array_name = ~random_treasures_%file%~ glue final_glue RET randomTreasureNames = text END

	PATCH_IF ~%randomTreasureNames%~ STRING_EQUAL ~~ BEGIN
		PATCH_MATCH ~%file%~ WITH
			RNDTRE01 BEGIN SPRINT randomTreasureNames @100401 END // ~trésor aléatoire de qualité médiocre~
			RNDTRE02 BEGIN SPRINT randomTreasureNames @100402 END // ~trésor aléatoire de qualité ordinaire~
			RNDTRE03 BEGIN SPRINT randomTreasureNames @100403 END // ~trésor aléatoire de qualité~
			RNDTRE04 BEGIN SPRINT randomTreasureNames @100404 END // ~trésor aléatoire de qualité supérieure~
			RNDTRE05 BEGIN SPRINT randomTreasureNames @100405 END // ~trésor aléatoire de qualité exceptionnelle~
			DEFAULT LPF ~get_item_name~ STR_VAR file RET randomTreasureNames = itemName END
		END
	END
END

/*
 * Lignes de même condition réunies (« - Si … ; 7 % de chances … » et « - Si … ; 2 % de chances … ») : la condition
 * seule à la place de la première, puis la suite de chacune en retrait, avec ses sous-lignes. Une condition dont une
 * ligne n'a pas de suite (ses effets sont déjà en retrait dessous) n'est pas réunie.
 */
DEFINE_PATCH_FUNCTION ~group_condition_lines~ STR_VAR text = ~~ RET text BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~gc_lines~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~gc_conds~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~gc_counts~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~gc_bare~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~gc_done~ BEGIN END
	CLEAR_ARRAY gc_lines
	CLEAR_ARRAY gc_conds
	CLEAR_ARRAY gc_counts
	CLEAR_ARRAY gc_bare
	CLEAR_ARRAY gc_done
	SET gc_count = 0
	INNER_PATCH ~%text%~ BEGIN
		REPLACE_EVALUATE CASE_SENSITIVE ~%crlf%\([^%crlf%]*\)~ BEGIN
			SPRINT $gc_lines(~%gc_count%~) ~%MATCH1%~
			SET gc_count += 1
		END ~~
	END
	SET gc_found = 0
	SET gc_semicolon_length = STRING_LENGTH ~%semicolon%~
	FOR (gc_i = 0; gc_i < gc_count; ++gc_i) BEGIN
		SPRINT gc_line $gc_lines(~%gc_i%~)
		SPRINT gc_condition ~~
		PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~- ~ ~%gc_line%~) == 0 BEGIN
			SET gc_at = INDEX (CASE_SENSITIVE EXACT_MATCH ~%semicolon%~ ~%gc_line%~)
			PATCH_IF gc_at > 2 BEGIN
				INNER_PATCH_SAVE gc_condition ~%gc_line%~ BEGIN
					DELETE_BYTES gc_at (BUFFER_LENGTH - gc_at)
					DELETE_BYTES 0 2
				END
				SET gc_seen = VARIABLE_IS_SET $gc_counts(~%gc_condition%~) ? $gc_counts(~%gc_condition%~) : 0
				SET $gc_counts(~%gc_condition%~) = gc_seen + 1
				PATCH_IF gc_seen == 1 BEGIN
					SET gc_found = 1
				END
				PATCH_IF gc_at + gc_semicolon_length >= STRING_LENGTH ~%gc_line%~ BEGIN
					SET $gc_bare(~%gc_condition%~) = 1
				END
			END
		END
		SPRINT $gc_conds(~%gc_i%~) ~%gc_condition%~
	END
	PATCH_IF gc_found BEGIN
		SPRINT text ~~
		SET gc_i = 0
		WHILE gc_i < gc_count BEGIN
			SPRINT gc_line $gc_lines(~%gc_i%~)
			SPRINT gc_condition $gc_conds(~%gc_i%~)
			SET gc_grouped = 0
			PATCH_IF NOT ~%gc_condition%~ STRING_EQUAL ~~ BEGIN
				SET gc_grouped = $gc_counts(~%gc_condition%~) > 1 AND NOT VARIABLE_IS_SET $gc_bare(~%gc_condition%~)
			END
			PATCH_IF NOT gc_grouped BEGIN
				SPRINT text ~%text%%crlf%%gc_line%~
				SET gc_i += 1
			END
			ELSE BEGIN
				PATCH_IF NOT VARIABLE_IS_SET $gc_done(~%gc_condition%~) BEGIN
					SET $gc_done(~%gc_condition%~) = 1
					SPRINT text ~%text%%crlf%- %gc_condition%%semicolon%~
					SET gc_head_length = STRING_LENGTH ~- %gc_condition%%semicolon%~
					FOR (gc_j = gc_i; gc_j < gc_count; ++gc_j) BEGIN
						SPRINT gc_other $gc_conds(~%gc_j%~)
						PATCH_IF ~%gc_other%~ STRING_EQUAL ~%gc_condition%~ BEGIN
							SPRINT gc_member $gc_lines(~%gc_j%~)
							INNER_PATCH_SAVE gc_member ~%gc_member%~ BEGIN
								DELETE_BYTES 0 gc_head_length
							END
							SPRINT text ~%text%%crlf%  - %gc_member%~
							// Sous-lignes de la ligne réunie : un retrait de plus.
							SET gc_k = gc_j + 1
							SET gc_sub = 1
							WHILE gc_sub AND gc_k < gc_count BEGIN
								SPRINT gc_member $gc_lines(~%gc_k%~)
								SET gc_sub = INDEX (CASE_SENSITIVE EXACT_MATCH ~ ~ ~%gc_member%~) == 0
								PATCH_IF gc_sub BEGIN
									// Retrait d'origine des sous-lignes remplacé par celui du niveau suivant.
									PATCH_IF gc_k == gc_j + 1 BEGIN
										INNER_PATCH ~%gc_member%~ BEGIN
											REPLACE_EVALUATE ~^\( *\)~ BEGIN SET gc_indent = STRING_LENGTH ~%MATCH1%~ END ~%MATCH1%~
										END
									END
									INNER_PATCH_SAVE gc_member ~%gc_member%~ BEGIN
										DELETE_BYTES 0 (gc_indent < BUFFER_LENGTH ? gc_indent : 0)
									END
									SPRINT text ~%text%%crlf%    %gc_member%~
									SET gc_k += 1
								END
							END
						END
					END
				END
				// La ligne et ses sous-lignes sont déjà écrites avec la condition.
				SET gc_i += 1
				SET gc_sub = 1
				WHILE gc_sub AND gc_i < gc_count BEGIN
					SPRINT gc_member $gc_lines(~%gc_i%~)
					SET gc_sub = INDEX (CASE_SENSITIVE EXACT_MATCH ~ ~ ~%gc_member%~) == 0
					PATCH_IF gc_sub BEGIN
						SET gc_i += 1
					END
				END
			END
		END
	END
END
