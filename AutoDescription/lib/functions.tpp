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

/**
 * @see https://www.gibberlings3.net/forums/topic/28835-toss-your-semi-useful-weidu-macros-here/page/2/#comment-254894
 * Patch function. Converts any decimal number into a hexadecimal number.
 * INT_VAR value      The decimal number to convert.
 * INT_VAR minDigits  Minimum number of digits for the returned hex value. (default: 1)
 * INT_VAR prefix     A flag that indicates whether the returned number will be prefixed with "0x". (default: 0)
 * RET hexNumber      The converted hexadecimal number as string.
 */
DEFINE_PATCH_FUNCTION TO_HEX_NUMBER
	INT_VAR
		value     = 0
		minDigits = 1
		prefix    = 0
	RET
		hexNumber
BEGIN
	SET minDigits = (minDigits < 1) ? 1 : minDigits
	SET minDigits = (minDigits > 8) ? 8 : minDigits
	TEXT_SPRINT hexNumber ~~
	PATCH_DEFINE_ARRAY digit BEGIN ~0~ ~1~ ~2~ ~3~ ~4~ ~5~ ~6~ ~7~ ~8~ ~9~ ~a~ ~b~ ~c~ ~d~ ~e~ ~f~ END

	PATCH_IF (value < 0) BEGIN
		SET signed = 1
		SET value = 0 - value
	END ELSE BEGIN
		SET signed = 0
	END

	WHILE (value != 0) BEGIN
		SET curDigit = value BAND 0xf
		SET value = value BLSR 4
		TEXT_SPRINT hexDigit $EVAL digit(~%curDigit%~)
		TEXT_SPRINT hexNumber ~%hexDigit%%hexNumber%~
	END

	WHILE (STRING_LENGTH ~%hexNumber%~ < minDigits) BEGIN
		TEXT_SPRINT hexNumber ~0%hexNumber%~
	END

	PATCH_IF (prefix) BEGIN
		TEXT_SPRINT hexNumber ~0x%hexNumber%~
	END

	PATCH_IF (signed) BEGIN
		TEXT_SPRINT hexNumber ~-%hexNumber%~
	END
END

// Action version of TO_HEX_NUMBER
DEFINE_ACTION_FUNCTION TO_HEX_NUMBER
	INT_VAR
		value     = 0
		minDigits = 1
		prefix    = 0
	RET
		hexNumber
BEGIN
	OUTER_PATCH ~~ BEGIN
		LPF TO_HEX_NUMBER INT_VAR value = value minDigits = minDigits prefix = prefix RET hexNumber END
	END
END