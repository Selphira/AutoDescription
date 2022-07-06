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

