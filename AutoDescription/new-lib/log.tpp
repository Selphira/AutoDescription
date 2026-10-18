// Journaux propres au nouveau moteur, dans AutoDescription/log/ à côté de ceux de la boucle
// commune ; log_name (« <langue>-<jeu>-<mod>-<type> ») est transmis par la boucle.

DEFINE_ACTION_FUNCTION ad_init_log
	STR_VAR
		log_name = ~~
BEGIN
	ACTION_IF AD_EFFECTS_DUMP BEGIN
		<<<<<<<< .../AutoDescription/inlined/ad_empty.txt
>>>>>>>>
		COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~AutoDescription/log/%log_name%-effects.txt~
	END
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
