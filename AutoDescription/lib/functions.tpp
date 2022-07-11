/* ============================================================== *
 * Retourne un tableau contenant la liste de tous les objets      *
 * ajoutés ou modifiés par un mod                                 *
 * ============================================================== */
DEFINE_ACTION_FUNCTION ~getItemsFromOtherMod~
	STR_VAR
		directory = ~~
	RET_ARRAY
		itemFiles
BEGIN
	GET_DIRECTORY_ARRAY $directories(~%directory%~) ~%directory%~ ~~
	GET_FILE_ARRAY files ~%directory%~ ~^.+\.itm$~

	ACTION_PHP_EACH files AS k => vFile BEGIN
		OUTER_INNER_PATCH_SAVE vFile ~%vFile%~ BEGIN
			REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^.*/~ ~~
		END

		OUTER_SPRINT $itemFiles(~%vFile%~) ~~
	END

	ACTION_PHP_EACH $directories(~%directory%~) AS k => vDirectory BEGIN
        LAF getItemsFromOtherMod STR_VAR directory = EVAL ~%vDirectory%~ RET_ARRAY itemFiles END
	END
END

/* ============================================================== *
 * Retourne la chaîne correspondant à la variable strref.         *
 * Si la traduction n'existe pas, une entrée de log est créée.    *
 * ============================================================== */
DEFINE_PATCH_FUNCTION ~getTranslation~
	INT_VAR
		opcode = 0
		strref = 0
	RET
		string
BEGIN
	PATCH_IF (NOT TRA_ENTRY_EXISTS (~%strref%~ ~AutoDescription/tra/french/description.tra~)) BEGIN
		LPF ~log_warning~ STR_VAR message = EVAL ~opcode %opcode%: Traduction %strref% manquante~ END
	END
	SPRINT string (AT %strref%)
END
