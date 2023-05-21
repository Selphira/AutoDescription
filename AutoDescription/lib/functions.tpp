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
		exist
BEGIN
	SET exist = 1
	PATCH_IF (NOT TRA_ENTRY_EXISTS (~%strref%~ ~AutoDescription/tra/french/description.tra~)) BEGIN
		SET exist = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~opcode %opcode%: Traduction %strref% manquante~ END
		SPRINT string @9999
	END
	ELSE BEGIN
		SPRINT string (AT %strref%)
	END
END


DEFINE_PATCH_FUNCTION ~get_tooltip~ INT_VAR index = 0 STR_VAR resource = ~~ RET tooltip BEGIN
	TO_LOWER resource

	SPRINT tooltip ~~
	SPRINT strref $tra_tooltips(~%resource%~ ~%index%~)

	PATCH_IF IS_AN_INT strref  BEGIN
		GET_STRREF strref tooltip
	END
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

/* ===================================================== *
 * Retourne le nom du jeu sur lequel on installe le mod. *
 * ===================================================== */
DEFINE_ACTION_FUNCTION ~get_game_name~
	RET gameName
BEGIN
	OUTER_SPRINT gameName ~unknown~
	ACTION_IF GAME_IS ~eet~ BEGIN
		OUTER_SPRINT gameName ~eet~
	END
	ELSE ACTION_IF GAME_IS ~bg2ee~ BEGIN
		OUTER_SPRINT gameName ~bg2ee~
	END
	ELSE ACTION_IF GAME_IS ~bgee~ AND GAME_INCLUDES ~sod~ BEGIN
		OUTER_SPRINT gameName ~bgeesod~
	END
	ELSE ACTION_IF GAME_IS ~bgee~ BEGIN
		OUTER_SPRINT gameName ~bgee~
	END
	ELSE ACTION_IF GAME_IS ~bgt~ BEGIN
		OUTER_SPRINT gameName ~bgt~
	END
	ELSE ACTION_IF GAME_IS ~tob~ BEGIN
		OUTER_SPRINT gameName ~tob~
	END
	ELSE ACTION_IF GAME_IS ~soa~ BEGIN
		OUTER_SPRINT gameName ~soa~
	END
END

DEFINE_PATCH_FUNCTION ~feets_to_meters~ INT_VAR range = 0 RET range rangeToMeter BEGIN
	SET range *= 10000
	SET range /= 3281
	SET rangeToMeter = range

	PATCH_IF range > 10 BEGIN
		SET decimal = range MODULO 10
		INNER_PATCH_SAVE rangeToMeter ~%range%~ BEGIN
			REPLACE_TEXTUALLY ~\([0-9]+\)+[0-9]$~ ~\1~
		END
		PATCH_IF decimal > 0 BEGIN
			PATCH_IF decimal >= 3 AND decimal <= 7 BEGIN
				SPRINT rangeToMeter ~%rangeToMeter%,5~
			END
			ELSE PATCH_IF decimal > 7 BEGIN
				SET rangeToMeter += 1
			END
		END
	END

	PATCH_IF range < 20 BEGIN
		SPRINT rangeToMeter ~%rangeToMeter% %meter%~
	END
	ELSE BEGIN
		SPRINT rangeToMeter ~%rangeToMeter% %meters%~
	END
END

/* ============================================== *
 * Complète une chaîne jusqu'à une taille donnée. *
 * ============================================== */
DEFINE_PATCH_FUNCTION ~str_pad_left~ INT_VAR min_length = 3 STR_VAR string = ~~ pad = ~0~ RET string BEGIN
	WHILE (STRING_LENGTH ~%string%~ < min_length) BEGIN
		TEXT_SPRINT string ~%pad%%string%~
	END
END

/* ================================================================================== *
 * Supprime tous les élements de la liste "elements" se trouvant dans la liste "list" *
 * ================================================================================== */
DEFINE_PATCH_FUNCTION remove_elements_in_list
	STR_VAR
        elements = ~~
        list = ~~
	RET
		list
BEGIN
	WHILE ~%elements%~ STRING_COMPARE ~~ BEGIN
		LPF return_first_entry STR_VAR list = ~%elements%~ RET entry elements = list END

		INNER_PATCH_SAVE list ~%list%~ BEGIN
			REPLACE_TEXTUALLY ~ %entry%~ ~~
			REPLACE_TEXTUALLY ~%entry% ~ ~~
			REPLACE_TEXTUALLY ~%entry%~ ~~
		END
	END
END

/* ==================================================================================== *
 * Indique si tous les élements de la liste "elements" se trouvant dans la liste "list" *
 * ==================================================================================== */
DEFINE_PATCH_FUNCTION all_elements_in_list
	STR_VAR
        elements = ~~
        list = ~~
	RET
		value
BEGIN
	SET value = 1

	WHILE ~%elements%~ STRING_COMPARE ~~ AND value == 1 BEGIN
		LPF return_first_entry STR_VAR list = ~%elements%~ RET element = entry elements = list END
		LPF element_in_list STR_VAR element list RET value END
	END
END

//TODO: lowerFirst
/*
		        REPLACE_EVALUATE CASE_INSENSITIVE ~^\(.\)~ BEGIN // First char to lower
		            TO_LOWER MATCH1
		        END ~%MATCH1%~
*/