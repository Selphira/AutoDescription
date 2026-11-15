// Journaux propres au nouveau moteur, dans AutoDescription/log/ à côté de ceux de la boucle
// commune ; log_name (« <langue>-<jeu>-<mod>-<type> ») est transmis par la boucle.

DEFINE_ACTION_FUNCTION ad_init_log
	STR_VAR
		log_name = ~~
BEGIN
	<<<<<<<< .../AutoDescription/inlined/ad_empty.txt
>>>>>>>>
	COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-opcodes.txt~
	COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-recursion.txt~
	// Tableaux markdown de ad_log_event : titre, puis en-tête du tableau.
	OUTER_SPRINT ad_log_table ~| Resource | Problem | Location | Effect data | Reason | Consequence |%WNL%|---|---|---|---|---|---|~
	COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-file-errors.md~
	COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-not-implemented.md~
	SILENT
	APPEND_OUTER ~%MOD_FOLDER%/log/%log_name%-file-errors.md~ ~# New engine: errors in the game files%WNL%%WNL%%ad_log_table%~ KEEP_CRLF
	APPEND_OUTER ~%MOD_FOLDER%/log/%log_name%-not-implemented.md~ ~# New engine: cases not supported%WNL%%WNL%%ad_log_table%~ KEEP_CRLF
	VERBOSE
	COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-events.txt~
	ACTION_IF AD_EFFECTS_DUMP BEGIN
		COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-effects.txt~
	END
	LAF ad_subspell_cache_init STR_VAR log_name END
END

// Remplace les lignes RESREF<TAB>opcode<TAB>occurrences<TAB>genre écrites par ad_set_coverage
// par une ligne par opcode, triée : opcode<TAB>genre<TAB>occurrences<TAB>ressources<TAB>exemples
// (cinq premières ressources). Genres : todo (pas encore pris en charge), absent (hors du
// catalogue), unavailable (inexistant dans ce jeu).
DEFINE_ACTION_FUNCTION ad_close_log
	STR_VAR
		log_name = ~~
BEGIN
	COPY - ~%MOD_FOLDER%/log/%log_name%-opcodes.txt~ ~override~
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
	COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-opcodes.txt~
	ACTION_IF NOT (~%cov_summary%~ STRING_EQUAL ~~) BEGIN
		SILENT
		APPEND_OUTER ~%MOD_FOLDER%/log/%log_name%-opcodes.txt~ ~%cov_summary%~ KEEP_CRLF
		VERBOSE
	END
	PRINT "Nouveau moteur : %cov_todo_count% opcodes a prendre en charge, %cov_unknown_count% opcodes inconnus (AutoDescription/log/%log_name%-opcodes.txt)"
	// Les compteurs ne peuvent pas être tenus par ad_log_event : c'est une fonction, appelée depuis
	// d'autres fonctions, et rien n'en remonte hors de ses RET. COUNT_REGEXP_INSTANCES compte sans
	// réécrire le fichier, contrairement à un REPLACE_EVALUATE ligne par ligne (6,4 s contre 0,03 s
	// pour 9 718 lignes).
	COPY - ~%MOD_FOLDER%/log/%log_name%-events.txt~ ~override~
		COUNT_REGEXP_INSTANCES CASE_SENSITIVE ~^[^%TAB%%MNL%%LNL%]+%TAB%[a-z_]+%TAB%[^%TAB%%MNL%%LNL%]*%TAB%[a-z]+~ event_count
		COUNT_REGEXP_INSTANCES CASE_SENSITIVE ~^[^%TAB%%MNL%%LNL%]+%TAB%[a-z_]+%TAB%[^%TAB%%MNL%%LNL%]*%TAB%refused%TAB%~ event_refused
		COUNT_REGEXP_INSTANCES CASE_SENSITIVE ~^[^%TAB%%MNL%%LNL%]+%TAB%file_error%TAB%[^%TAB%%MNL%%LNL%]*%TAB%refused%TAB%~ event_file_errors
		SET event_ignored = event_count - event_refused
		SET event_not_implemented = event_refused - event_file_errors
	PRINT "Nouveau moteur : %event_file_errors% ressources non decrites pour une erreur dans leurs fichiers, %event_ignored% effets invalides ou douteux (AutoDescription/log/%log_name%-file-errors.md), %event_not_implemented% ressources non decrites pour un cas non pris en charge (AutoDescription/log/%log_name%-not-implemented.md)"
END

// Refus d'une ressource, rendu dans render_missing, render_late_missing ou sub_missing :
// « <nature>:<raison><TAB><emplacement><TAB><données><TAB><message> », écrit dans les journaux par
// ad_log_event. Nature : file_error, erreur dans les fichiers du jeu (ressource absente, valeur hors
// de celles qu'admet l'opcode, fichier IDS invalide…), ou not_implemented, choix de l'outil (cas non
// encore pris en charge, ou volontairement non décrit, dont une valeur sans nom que le jeu
// applique) ; raison : code stable (« opcode151:missing_creature »), seul repris dans
// …-compare.txt ; emplacement et données : ceux de l'effet fx_id (ad_event_location, ad_event_data),
// aucun si fx_id < 0 ; message : ce qui ne va pas, en anglais, pour les moddeurs, avec les valeurs
// attendues.
DEFINE_PATCH_FUNCTION ad_refusal
	INT_VAR
		fx_id = 0 - 1
	STR_VAR
		reason = ~~
		message = ~~
	RET
		refusal
BEGIN
	PATCH_TIME ~step:refusal~ BEGIN
		SET event_fx = fx_id
		SET event_with_opcode = 0
		LPM ad_event_location
		LPM ad_event_data
		SPRINT refusal ~%reason%%TAB%%event_location%%TAB%%event_data%%TAB%%message%~
	END
END

// Emplacement de l'effet fx_id (ad_event_location), suivi de son opcode si with_opcode vaut 1.
DEFINE_PATCH_FUNCTION ad_fx_location
	INT_VAR
		fx_id = 0 - 1
		with_opcode = 0
	RET
		location
BEGIN
	SET event_fx = fx_id
	SET event_with_opcode = with_opcode
	LPM ad_event_location
	SPRINT location ~%event_location%~
END

// event_location : emplacement de l'effet event_fx dans son fichier, numéroté à partir de 0 comme dans
// le fichier : « ability 1, effect 2 », « equipped effect 0 » ; pour l'effet d'un 177 remplacé par
// celui de son EFF, « ability 1, effect 2, OHBWHIT.EFF (opcode 177) », de même pour la métamorphose de
// l'arme d'un 111. Avec event_with_opcode (effet parent d'une sous-ressource), suivi de son opcode :
// « equipped effect 0 (opcode 232) », « ability 1, effect 2 (opcode 177 > OHBWHIT.EFF: opcode 146) ».
// Dans une sous-ressource, précédé de son chemin (ctx_origin, lib/recursion.tpp) : « equipped effect 0
// (opcode 232) > BDDRAGBL.SPL: ability 0, effect 6 » ; l'effet unique d'un EFF n'y ajoute rien.
// Aucun emplacement propre si event_fx < 0. Macro : ad_log_ignored l'appelle dans la portée de la
// description, sans le coût d'un LPF ; ses variables location_* ne servent nulle part ailleurs.
DEFINE_PATCH_MACRO ad_event_location BEGIN
	SPRINT event_location ~~
	PATCH_IF event_fx >= 0 AND event_fx < fx_count AND NOT ctx_single_effect BEGIN
		SPRINT location_block $fx_block(~%event_fx%~)
		SET location_position = $fx_position(~%event_fx%~)
		SET location_header = $fx_header(~%event_fx%~)
		PATCH_IF ~%location_block%~ STRING_EQUAL ~ability~ BEGIN
			SPRINT event_location ~ability %location_header%, effect %location_position%~
		END
		ELSE BEGIN
			SPRINT event_location ~%location_block% effect %location_position%~
		END
	END
	PATCH_IF event_fx >= 0 AND event_fx < fx_count BEGIN
		SET location_opcode = $fx_opcode(~%event_fx%~)
		SPRINT location_parent_text ~~
		PATCH_IF VARIABLE_IS_SET $fx_parent_resource(~%event_fx%~) BEGIN
			SPRINT location_parent $fx_parent_resource(~%event_fx%~)
			TO_UPPER location_parent
			PATCH_IF $fx_from_111(~%event_fx%~) BEGIN
				SPRINT location_parent_text ~%location_parent%.ITM (opcode 111)~
				SPRINT location_parent_opcode ~opcode 111 > %location_parent%.ITM: ~
			END
			ELSE PATCH_IF $fx_external(~%event_fx%~) BEGIN
				SPRINT location_parent_text ~%location_parent%.EFF (opcode 177)~
				SPRINT location_parent_opcode ~opcode 177 > %location_parent%.EFF: ~
			END
		END
		PATCH_IF event_with_opcode BEGIN
			PATCH_IF ~%location_parent_text%~ STRING_EQUAL ~~ BEGIN
				SPRINT location_parent_opcode ~~
			END
			SPRINT location_opcode_text ~(%location_parent_opcode%opcode %location_opcode%)~
			SPRINT event_location ~%event_location% %location_opcode_text%~
		END
		ELSE PATCH_IF NOT (~%location_parent_text%~ STRING_EQUAL ~~) BEGIN
			SPRINT event_location ~%event_location%, %location_parent_text%~
		END
		INNER_PATCH_SAVE event_location ~%event_location%~ BEGIN
			REPLACE_TEXTUALLY ~^[ ,]+~ ~~
		END
	END
	PATCH_IF NOT (~%ctx_origin%~ STRING_EQUAL ~~) BEGIN
		PATCH_IF ~%event_location%~ STRING_EQUAL ~~ BEGIN
			SPRINT event_location ~%ctx_origin%~
		END
		ELSE PATCH_IF ctx_single_effect BEGIN
			SPRINT event_location ~%ctx_origin% %event_location%~
		END
		ELSE BEGIN
			SPRINT event_location ~%ctx_origin%: %event_location%~
		END
	END
END

// event_data : champs de l'effet event_fx, tels qu'ils ont été lus (fx_<champ>_raw pour ceux que des
// passes réécrivent) : toujours opcode, cible, parameter1, parameter2, timing et durée, puis ceux qui
// ne valent pas leur valeur par défaut (puissance, résistance, probabilités autres que 100 et 0, dés,
// jet de sauvegarde, special, parameter3 et parameter4 d'un EFF, ressources). Un champ que l'opcode
// n'utilise pas vaut d'ordinaire sa valeur par défaut et n'apparaît pas ; une valeur inattendue
// apparaît, ce qui peut expliquer le problème. Macro, comme ad_event_location (variables data_*).
DEFINE_PATCH_MACRO ad_event_data BEGIN
	SPRINT event_data ~~
	PATCH_IF event_fx >= 0 AND event_fx < fx_count BEGIN
		SET data_opcode = $fx_opcode(~%event_fx%~)
		SET data_target = $fx_target(~%event_fx%~)
		SET data_parameter1 = $fx_parameter1_raw(~%event_fx%~)
		SET data_parameter2 = $fx_parameter2_raw(~%event_fx%~)
		SET data_timing = $fx_timing_raw(~%event_fx%~)
		SET data_duration = $fx_duration_raw(~%event_fx%~)
		SPRINT event_data ~opcode %data_opcode%, target %data_target%, parameter1 %data_parameter1%, parameter2 %data_parameter2%, timing %data_timing%, duration %data_duration%~
		SET data_value = $fx_power(~%event_fx%~)
		PATCH_IF data_value != 0 BEGIN
			SPRINT event_data ~%event_data%, power %data_value%~
		END
		SET data_value = $fx_resistance(~%event_fx%~)
		PATCH_IF data_value != 0 BEGIN
			SPRINT event_data ~%event_data%, resistance %data_value%~
		END
		SET data_probability1 = $fx_probability1(~%event_fx%~)
		SET data_probability2 = $fx_probability2(~%event_fx%~)
		PATCH_IF data_probability1 != 100 OR data_probability2 != 0 BEGIN
			SPRINT event_data ~%event_data%, probability1 %data_probability1%, probability2 %data_probability2%~
		END
		SET data_dice_count = $fx_dice_count_raw(~%event_fx%~)
		SET data_dice_sides = $fx_dice_sides(~%event_fx%~)
		PATCH_IF data_dice_count != 0 OR data_dice_sides != 0 BEGIN
			SPRINT event_data ~%event_data%, dice %data_dice_count%d%data_dice_sides%~
		END
		SET data_save_type = $fx_save_type_raw(~%event_fx%~)
		SET data_save_bonus = $fx_save_bonus(~%event_fx%~)
		PATCH_IF data_save_type != 0 OR data_save_bonus != 0 BEGIN
			SPRINT event_data ~%event_data%, saving throw type %data_save_type%, saving throw bonus %data_save_bonus%~
		END
		SET data_value = $fx_special_raw(~%event_fx%~)
		PATCH_IF data_value != 0 BEGIN
			SPRINT event_data ~%event_data%, special %data_value%~
		END
		SET data_value = $fx_parameter3(~%event_fx%~)
		PATCH_IF data_value != 0 BEGIN
			SPRINT event_data ~%event_data%, parameter3 %data_value%~
		END
		SET data_value = $fx_parameter4(~%event_fx%~)
		PATCH_IF data_value != 0 BEGIN
			SPRINT event_data ~%event_data%, parameter4 %data_value%~
		END
		FOR (data_n = 1; data_n <= 3; ++data_n) BEGIN
			SPRINT data_field ~resource~
			PATCH_IF data_n > 1 BEGIN
				SPRINT data_field ~resource%data_n%~
			END
			SPRINT data_resource $EVAL ~fx_%data_field%~(~%event_fx%~)
			TO_UPPER data_resource
			PATCH_IF NOT (~%data_resource%~ STRING_EQUAL ~~) BEGIN
				SPRINT event_data ~%event_data%, %data_field% %data_resource%~
			END
		END
	END
END

// Refus refusal d'une sous-ressource, lancée ou appliquée par l'effet fx_id : sa raison prend le
// préfixe recursion: (une seule fois sur la chaîne) ; son emplacement porte déjà le chemin de la
// sous-ressource (ctx_origin). Un refus de la sous-ressource elle-même (fichier absent…) reçoit les
// données de l'effet parent.
DEFINE_PATCH_FUNCTION ad_refusal_nest
	INT_VAR
		fx_id = 0 - 1
	STR_VAR
		refusal = ~~
	RET
		refusal
BEGIN
	SPRINT event ~%refusal%~
	LPM ad_event_split
	PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~recursion:~ ~%event_code%~) != 0 BEGIN
		SPRINT event_code ~recursion:%event_code%~
	END
	PATCH_IF ~%event_data%~ STRING_EQUAL ~~ BEGIN
		SET event_fx = fx_id
		LPM ad_event_data
	END
	SPRINT refusal ~%event_kind%:%event_code%%TAB%%event_location%%TAB%%event_data%%TAB%%event_message%~
END

// Effet ignored_fx écarté sans rien écrire alors que la ressource reste décrite : donnée invalide
// (file_error) ou information perdue (not_implemented), raison ignored_reason (avec sa nature) et
// message ignored_message ; ignored_consequence : ignored, ou kept pour un effet douteux décrit quand
// même (« points de dégâts » pour un type inconnu). Les trois sont remis à zéro. Mêmes journaux que
// ad_refusal suivi de ad_log_event, sans assembler l'événement pour le redécouper.
DEFINE_PATCH_MACRO ad_log_ignored BEGIN
	PATCH_TIME ~step:refusal~ BEGIN
		SET event_fx = ignored_fx
		SET event_with_opcode = 0
		LPM ad_event_location
		LPM ad_event_data
		SPRINT event_message ~%ignored_message%~
		SPRINT event_reason ~%ignored_reason%~
		LPM ad_event_kind
	END
	PATCH_TIME ~step:log_event~ BEGIN
		SPRINT event_outcome ~%ignored_consequence%~
		LPM ad_event_write
	END
	SPRINT ignored_reason ~~
	SPRINT ignored_message ~~
	SPRINT ignored_consequence ~ignored~
END

// Champs de l'événement event (refus de ad_refusal) : event_location, event_data, event_message, et
// ceux de ad_event_kind.
DEFINE_PATCH_MACRO ad_event_split BEGIN
	SPRINT event_reason ~%event%~
	SPRINT event_location ~~
	SPRINT event_data ~~
	SPRINT event_message ~~
	INNER_PATCH ~%event%~ BEGIN
		REPLACE_EVALUATE CASE_SENSITIVE ~^\([^%TAB%]*\)%TAB%\([^%TAB%]*\)%TAB%\([^%TAB%]*\)%TAB%\(.*\)$~ BEGIN
			SPRINT event_reason ~%MATCH1%~
			SPRINT event_location ~%MATCH2%~
			SPRINT event_data ~%MATCH3%~
			SPRINT event_message ~%MATCH4%~
		END ~~
	END
	LPM ad_event_kind
END

// Raison event_reason : event_kind (file_error, not_implemented) et event_code (raison sans la
// nature). Une raison sans nature reconnue est comptée comme un cas non pris en charge.
DEFINE_PATCH_MACRO ad_event_kind BEGIN
	SPRINT event_kind ~not_implemented~
	SPRINT event_code ~%event_reason%~
	INNER_PATCH ~%event_reason%~ BEGIN
		REPLACE_EVALUATE CASE_SENSITIVE ~^\(file_error\|not_implemented\):\(.*\)$~ BEGIN
			SPRINT event_kind ~%MATCH1%~
			SPRINT event_code ~%MATCH2%~
		END ~~
	END
END

// Écrit l'événement event (refus de ad_refusal) de la ressource en cours (ad_event_write), de
// conséquence consequence : refused (ressource non décrite), ignored (effet écarté, la ressource reste
// décrite) ou kept (effet douteux décrit quand même). Renvoie la raison avec sa nature, pour
// …-compare.txt.
DEFINE_PATCH_FUNCTION ad_log_event
	STR_VAR
		event = ~~
		consequence = ~refused~
	RET
		reason
BEGIN
	PATCH_TIME ~step:log_event~ BEGIN
		LPM ad_event_split
		SPRINT reason ~%event_kind%:%event_code%~
		SPRINT event_outcome ~%consequence%~
		LPM ad_event_write
	END
END

// Écrit l'événement (event_kind, event_code, event_location, event_data, event_message) de
// conséquence event_outcome : une ligne du tableau markdown de …-file-errors.md ou …-not-implemented.md
// selon sa nature (ressource, problème, emplacement, données de l'effet, raison, conséquence ; « | »
// des cellules échappé), et une ligne en colonnes dans …-events.txt : ressource<TAB>nature<TAB>raison
// <TAB>conséquence<TAB>emplacement<TAB>données<TAB>message. event_message, event_location et
// event_data sont échappés sur place.
DEFINE_PATCH_MACRO ad_event_write BEGIN
	SPRINT event_consequence ~not described~
	PATCH_IF ~%event_outcome%~ STRING_EQUAL ~ignored~ BEGIN
		SPRINT event_consequence ~effect ignored~
	END
	ELSE PATCH_IF ~%event_outcome%~ STRING_EQUAL ~kept~ BEGIN
		SPRINT event_consequence ~described anyway~
	END
	SPRINT event_columns ~%SOURCE_FILE%%TAB%%event_kind%%TAB%%event_code%%TAB%%event_outcome%%TAB%%event_location%%TAB%%event_data%%TAB%%event_message%~
	// Dans le texte de remplacement, \\ désigne une seule barre oblique inverse (V21).
	INNER_PATCH_SAVE event_message ~%event_message%~ BEGIN
		REPLACE_TEXTUALLY ~|~ ~\\|~
	END
	INNER_PATCH_SAVE event_location ~%event_location%~ BEGIN
		REPLACE_TEXTUALLY ~|~ ~\\|~
	END
	INNER_PATCH_SAVE event_data ~%event_data%~ BEGIN
		REPLACE_TEXTUALLY ~|~ ~\\|~
	END
	// Valeurs des données en gras (« opcode **151**, target **2** ») : dernier mot de chaque champ.
	INNER_PATCH_SAVE event_data ~%event_data%,~ BEGIN
		REPLACE_TEXTUALLY ~ \([^ ,]+\),~ ~ **\1**,~
		REPLACE_TEXTUALLY ~,$~ ~~
	END
	SPRINT event_row ~| %SOURCE_FILE% | %event_message% | %event_location% | %event_data% | `%event_code%` | %event_consequence% |~
	SPRINT event_file ~not-implemented~
	PATCH_IF ~%event_kind%~ STRING_EQUAL ~file_error~ BEGIN
		SPRINT event_file ~file-errors~
	END
	SPRINT log_file ~%MOD_FOLDER%/log/%log_name%-%event_file%.md~
	LPM ad_log_part
	SPRINT event_table_part ~%log_part%~
	SPRINT log_file ~%MOD_FOLDER%/log/%log_name%-events.txt~
	LPM ad_log_part
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~%event_table_part%~ ~%event_row%~ KEEP_CRLF
		APPEND_OUTER ~%log_part%~ ~%event_columns%~ KEEP_CRLF
		VERBOSE
	END
END

// Sous-ressource que la récursion ne décrit pas (ad_recursion_allowed, lib/recursion.tpp) :
// chaîne des ressources recursion_chain<TAB>sous-ressource recursion_upper<TAB>raison recursion_reason
// (depth : au-delà de AD_RECURSION_MAX_DEPTH ; loop : déjà dans la chaîne).
DEFINE_PATCH_MACRO ad_log_recursion BEGIN
	PATCH_TIME ~step:recursion_log~ BEGIN
		SPRINT log_file ~%MOD_FOLDER%/log/%log_name%-recursion.txt~
		LPM ad_log_part
		INNER_ACTION BEGIN
			SILENT
			APPEND_OUTER ~%log_part%~ ~%recursion_chain%%TAB%%recursion_upper%%TAB%%recursion_reason%~ KEEP_CRLF
			VERBOSE
		END
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
		LPM ad_fx_ticks
		PHP_EACH AD_FX_FIELDS AS fx_i => fx_field BEGIN
			PATCH_IF ~%fx_field%~ STRING_EQUAL ~delay_ticks~ BEGIN
				SET fx_value = fx_delay_ticks
			END
			ELSE PATCH_IF ~%fx_field%~ STRING_EQUAL ~duration_ticks~ BEGIN
				SET fx_value = fx_duration_ticks
			END
			ELSE BEGIN
				SPRINT fx_value $EVAL ~fx_%fx_field%~(~%fx_id%~)
			END
			SPRINT fx_line ~%fx_line%%TAB%%fx_value%~
		END
		SPRINT fx_dump ~%fx_dump%%WNL%%fx_line%~
	END
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~%MOD_FOLDER%/log/%log_name%-effects.txt~ ~%fx_dump%~ KEEP_CRLF
		VERBOSE
	END
END
