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
        SORT_ARRAY_INDICES ~%arrayName%~ NUMERICALLY
		LPF ~appendSection~ STR_VAR string = ~%title%~ RET description END

	    PATCH_PHP_EACH ~%arrayName%~ AS data => value BEGIN
	        PATCH_IF value MODULO 2 == 1 BEGIN
				LPF ~appendProperty~ INT_VAR indentation_num = value / 2 STR_VAR name = EVAL ~%data_5%~ RET description END
			END
			ELSE PATCH_IF value MODULO 2 == 0 BEGIN
				LPF ~appendSubProperty~ STR_VAR name = EVAL ~%data_5%~ RET description END
			END
	    END
	END
END

DEFINE_PATCH_FUNCTION ~removeTechnicalDescription~ STR_VAR description = "" RET description BEGIN
	// On ne garde que le texte roleplay
	INNER_PATCH_SAVE description ~%description%~ BEGIN
		SPRINT regex @10008     // ~^[ %TAB%]*\(CARACTÉRISTIQUES\|STATISTIQUES\|PARAMETRES\|PARAMÈTRES\)+\(.*[%MNL%%LNL%%WNL%]*\)*~
		SPRINT replace @100003  // ~PARAMÈTRES~
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~%regex%~ ~%replace%%colon%%crlf%~
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
	SPRINT string @100001 // %name% : %value%
    SPRINT description "%description%%crlf%%string%"
END

DEFINE_PATCH_FUNCTION ~appendProperty~ INT_VAR strref = 0 indentation_num = 0 STR_VAR name = "" value = "" RET description BEGIN
	PATCH_IF strref > 0 BEGIN
		SPRINT name (AT %strref%)
	END

	PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
		SPRINT name @100001 // %name% : %value%
	END

	SPRINT indentation ~~

	FOR (i = 0 ; i < indentation_num ; ++i ) BEGIN
		SPRINT indentation ~%indentation%  ~
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
	PATCH_IF value >= 0 BEGIN
		SPRINT value @10003
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

	SPRINT final_glue @100004 //= ~ou~
	SPRINT final_glue ~" %final_glue% "~
	LPF ~implode~ STR_VAR array_name = ~random_treasures_%file%~ glue = ~", "~ final_glue RET randomTreasureNames = text END

	PATCH_IF ~%randomTreasureNames%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_item_name~ STR_VAR file RET randomTreasureNames = itemName END
	END
END
