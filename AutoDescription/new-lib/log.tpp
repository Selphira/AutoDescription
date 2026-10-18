// Journaux propres au nouveau moteur, dans AutoDescription/log/ à côté de ceux de la boucle
// commune ; log_name (« <langue>-<jeu>-<mod>-<type> ») est transmis par la boucle.

DEFINE_ACTION_FUNCTION ad_init_log
	STR_VAR
		log_name = ~~
BEGIN
	<<<<<<<< .../AutoDescription/inlined/ad_empty.txt
>>>>>>>>
	COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~AutoDescription/log/%log_name%-opcodes.txt~
	ACTION_IF AD_EFFECTS_DUMP BEGIN
		COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~AutoDescription/log/%log_name%-effects.txt~
	END
END

// Remplace les lignes RESREF<TAB>opcode<TAB>occurrences<TAB>genre écrites par ad_set_coverage
// par une ligne par opcode, triée : opcode<TAB>genre<TAB>occurrences<TAB>ressources<TAB>exemples
// (cinq premières ressources). Genres : todo (pas encore pris en charge), absent (hors du
// catalogue), unavailable (inexistant dans ce jeu).
DEFINE_ACTION_FUNCTION ad_close_log
	STR_VAR
		log_name = ~~
BEGIN
	COPY - ~AutoDescription/log/%log_name%-opcodes.txt~ ~override~
		REPLACE_EVALUATE ~^\([^%TAB%%MNL%%LNL%]+\)%TAB%\([0-9]+\)%TAB%\([0-9]+\)%TAB%\([a-z]+\)~ BEGIN
			PATCH_IF NOT VARIABLE_IS_SET $cov_resources(~%MATCH2%~) BEGIN
				SET $cov_resources(~%MATCH2%~) = 0
				SET $cov_occurrences(~%MATCH2%~) = 0
				SPRINT $cov_kind(~%MATCH2%~) ~%MATCH4%~
				SPRINT $cov_examples(~%MATCH2%~) ~%MATCH1%~
			END
			ELSE PATCH_IF $cov_resources(~%MATCH2%~) < 5 BEGIN
				SPRINT cov_example $cov_examples(~%MATCH2%~)
				SPRINT $cov_examples(~%MATCH2%~) ~%cov_example%, %MATCH1%~
			END
			SET $cov_resources(~%MATCH2%~) += 1
			SET $cov_occurrences(~%MATCH2%~) += MATCH3
		END ~~
		SPRINT cov_summary ~~
		SET cov_todo_count = 0
		SET cov_unknown_count = 0
		SORT_ARRAY_INDICES cov_resources NUMERICALLY
		PHP_EACH cov_resources AS cov_opcode => cov_resource_count BEGIN
			SPRINT cov_kind_value $cov_kind(~%cov_opcode%~)
			SET cov_occurrence_count = $cov_occurrences(~%cov_opcode%~)
			SPRINT cov_example $cov_examples(~%cov_opcode%~)
			PATCH_IF ~%cov_kind_value%~ STRING_EQUAL ~todo~ BEGIN
				SET cov_todo_count += 1
			END
			ELSE BEGIN
				SET cov_unknown_count += 1
			END
			PATCH_IF NOT (~%cov_summary%~ STRING_EQUAL ~~) BEGIN
				SPRINT cov_summary ~%cov_summary%%WNL%~
			END
			SPRINT cov_summary ~%cov_summary%%cov_opcode%%TAB%%cov_kind_value%%TAB%%cov_occurrence_count%%TAB%%cov_resource_count%%TAB%%cov_example%~
		END
	COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~AutoDescription/log/%log_name%-opcodes.txt~
	ACTION_IF NOT (~%cov_summary%~ STRING_EQUAL ~~) BEGIN
		SILENT
		APPEND_OUTER ~AutoDescription/log/%log_name%-opcodes.txt~ ~%cov_summary%~ KEEP_CRLF
		VERBOSE
	END
	PRINT "Nouveau moteur : %cov_todo_count% opcodes a prendre en charge, %cov_unknown_count% opcodes inconnus (AutoDescription/log/%log_name%-opcodes.txt)"
END

// Format (une ligne par ressource, puis une par effet) :
// RESREF<TAB>resource<TAB>nombre d'en-têtes<TAB>nombre d'effets<TAB>erreur de lecture
// RESREF<TAB>fx<TAB>id<TAB>bloc<TAB>en-tête<TAB>position<TAB>opcode<TAB>cible<TAB>puissance
//   <TAB>paramètre 1<TAB>paramètre 2<TAB>timing<TAB>résistance<TAB>durée<TAB>probabilité 1
//   <TAB>probabilité 2<TAB>ressource<TAB>dés<TAB>faces<TAB>type de JS<TAB>bonus de JS<TAB>spécial
// Valeurs brutes : entiers sur 4 octets signés, sur 1 ou 2 octets non signés (V31).
DEFINE_PATCH_MACRO ad_fx_dump BEGIN
	SPRINT fx_dump ~%SOURCE_RES%%TAB%resource%TAB%%fx_header_count%%TAB%%fx_count%%TAB%%fx_load_error%~
	FOR (fx_id = 0; fx_id < fx_count; ++fx_id) BEGIN
		SPRINT fx_line ~%SOURCE_RES%%TAB%fx%TAB%%fx_id%~
		PHP_EACH AD_FX_FIELDS AS fx_i => fx_field BEGIN
			SPRINT fx_value $EVAL ~fx_%fx_field%~(~%fx_id%~)
			SPRINT fx_line ~%fx_line%%TAB%%fx_value%~
		END
		SPRINT fx_dump ~%fx_dump%%WNL%%fx_line%~
	END
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~AutoDescription/log/%log_name%-effects.txt~ ~%fx_dump%~ KEEP_CRLF
		VERBOSE
	END
END
