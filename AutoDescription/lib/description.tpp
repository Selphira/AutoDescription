DEFINE_ACTION_MACRO ~update_descriptions~ BEGIN
	LAM ~update_item_descriptions~
	//LAM ~update_spell_descriptions~
END

DEFINE_ACTION_MACRO ~update_item_descriptions~ BEGIN
	COPY_EXISTING_REGEXP GLOB ~^.+\.itm$~ ~override~
		PATCH_TRY
			LPF ~update_item_description~ RET totalIgnoredCursed totalIgnoredWithoutDescription totalIgnoredNotMoveable totalIgnoredType totalSuccessful END
		WITH DEFAULT
			LPF ~add_log_warning~ STR_VAR message = ~FAILURE: %ERROR_MESSAGE%~ END
			SET totalFailed += 1
		END
	BUT_ONLY_IF_IT_CHANGES
END

DEFINE_ACTION_MACRO ~update_spell_descriptions~ BEGIN
	COPY_EXISTING_REGEXP GLOB ~^.+\.spl$~ ~override~
		LPF ~update_spell_description~ END
	BUT_ONLY_IF_IT_CHANGES
END


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