// Pilotage de l'installation : parcours des objets et des sorts, filtres des options include_*,
// écriture dans les fichiers du jeu (alter_item_files, alter_spell_files), journaux de la
// boucle (warning, error, diff.html, dump de régression), données JS de docs/data/ et
// statistiques. log_name (« <langue>-<jeu>-<mod>-<type> ») est renvoyé par ad_install_init et
// transmis à chaque appel.

// ---------------------------------------------------------------------------------------------
// Début et fin d'un composant

DEFINE_ACTION_FUNCTION ad_game_name
	RET
		game_name
BEGIN
	OUTER_SPRINT game_name ~unknown~
	ACTION_IF GAME_IS ~eet~ BEGIN
		OUTER_SPRINT game_name ~eet~
	END
	ELSE ACTION_IF GAME_IS ~bg2ee~ BEGIN
		OUTER_SPRINT game_name ~bg2ee~
	END
	ELSE ACTION_IF GAME_IS ~bgee~ AND GAME_INCLUDES ~sod~ BEGIN
		OUTER_SPRINT game_name ~bgeesod~
	END
	ELSE ACTION_IF GAME_IS ~bgee~ BEGIN
		OUTER_SPRINT game_name ~bgee~
	END
	ELSE ACTION_IF GAME_IS ~bgt~ BEGIN
		OUTER_SPRINT game_name ~bgt~
	END
	ELSE ACTION_IF GAME_IS ~tob~ BEGIN
		OUTER_SPRINT game_name ~tob~
	END
	ELSE ACTION_IF GAME_IS ~soa~ BEGIN
		OUTER_SPRINT game_name ~soa~
	END
END

// Crée les journaux du composant et ouvre les données JS ; type : items ou spells, mod : all ou
// le dossier du mod traité.
DEFINE_ACTION_FUNCTION ad_install_init
	STR_VAR
		type = ~items~
		mod = ~all~
	RET
		log_name
BEGIN
	ACTION_TIME ~step:init~ BEGIN
		LAF ad_game_name RET game_name END
		OUTER_SPRINT log_name ~%LANGUAGE%-%game_name%-%mod%-%type%~
		<<<<<<<< .../AutoDescription/inlined/ad_install_empty.txt
>>>>>>>>
		COPY ~.../AutoDescription/inlined/ad_install_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-warning.log~
		COPY ~.../AutoDescription/inlined/ad_install_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-error.log~
		ACTION_IF regression_dump BEGIN
			COPY ~.../AutoDescription/inlined/ad_install_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-dump.txt~
		END
		ACTION_IF IS_EE BEGIN
			COPY ~%MOD_FOLDER%/log/template_ee.html~ ~%MOD_FOLDER%/log/%log_name%-diff.html~
		END
		ELSE BEGIN
			COPY ~%MOD_FOLDER%/log/template.html~ ~%MOD_FOLDER%/log/%log_name%-diff.html~
		END
		LAF ad_init_log STR_VAR log_name END
		LAF ad_init_js_file STR_VAR log_name END
	END
END

// Compteurs du composant, lus par ad_install_close : ressources parcourues, décrites, en échec, et
// ignorées par raison ($ad_ignored(raison), raisons et libellés dans AD_IGNORE_LABELS).
DEFINE_ACTION_MACRO ad_init_statistics BEGIN
	OUTER_SET ad_processed = 0
	OUTER_SET ad_successful = 0
	OUTER_SET ad_failed = 0
	ACTION_CLEAR_ARRAY ad_ignored
END

DEFINE_ACTION_MACRO ad_install_close BEGIN
	ACTION_TIME ~step:join_logs~ BEGIN
		LAF ad_join_all_log_parts STR_VAR log_name END
	END
	ACTION_TIME ~step:close_js~ BEGIN
		LAF ad_close_js_file STR_VAR log_name END
	END
	ACTION_TIME ~step:close_log~ BEGIN
		LAF ad_close_log STR_VAR log_name END
	END
	ACTION_TIME ~step:clear_cache~ BEGIN
		LAF ad_subspell_cache_close END
	END

	OUTER_SET ad_ignored_total = 0
	OUTER_SPRINT ad_ignored_lines ~~
	ACTION_PHP_EACH AD_IGNORE_LABELS AS ad_reason => ad_label BEGIN
		ACTION_IF VARIABLE_IS_SET $ad_ignored(~%ad_reason%~) BEGIN
			OUTER_SET ad_count = $ad_ignored(~%ad_reason%~)
			OUTER_SET ad_ignored_total += ad_count
			OUTER_SPRINT ad_ignored_lines ~%ad_ignored_lines%
   %ad_label% : %ad_count%~
		END
	END
	OUTER_SET ad_total = ad_successful + ad_failed + ad_ignored_total
	PRINT "Reussis : %ad_successful%
Echoues : %ad_failed%
Ignores : %ad_ignored_total%%ad_ignored_lines%

Total : %ad_total%"
END

// ---------------------------------------------------------------------------------------------
// Parcours

// step:loop contient aussi la lecture des fichiers et l'écriture de ceux qui changent, hors des
// PATCH_TIME par ressource.
DEFINE_ACTION_MACRO ad_install_all_items BEGIN
	LAM ad_init_statistics
	ACTION_TIME ~step:loop~ BEGIN
		COPY_EXISTING_REGEXP GLOB ~^.+\.itm$~ ~override~
			PATCH_TIME ~%SOURCE_FILE%~ BEGIN
				LPM ad_install_item
			END
		BUT_ONLY_IF_IT_CHANGES
	END
END

DEFINE_ACTION_MACRO ad_install_all_spells BEGIN
	LAM ad_init_statistics
	ACTION_TIME ~step:loop~ BEGIN
		COPY_EXISTING_REGEXP GLOB ~^.+\.spl$~ ~override~
			PATCH_TIME ~%SOURCE_FILE%~ BEGIN
				LPM ad_install_spell
			END
		BUT_ONLY_IF_IT_CHANGES
	END
END

// Fichiers <extension> du dossier d'un mod et de ses sous-dossiers : $files(NOM.EXT).
DEFINE_ACTION_FUNCTION ad_mod_files
	STR_VAR
		directory = ~~
		extension = ~itm~
	RET_ARRAY
		files
BEGIN
	GET_DIRECTORY_ARRAY $directories(~%directory%~) ~%directory%~ ~~
	GET_FILE_ARRAY found ~%directory%~ ~^.+\.%extension%$~
	ACTION_PHP_EACH found AS _ => path BEGIN
		OUTER_INNER_PATCH_SAVE path ~%path%~ BEGIN
			REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^.*/~ ~~
		END
		OUTER_SPRINT $files(~%path%~) ~~
	END
	ACTION_PHP_EACH $directories(~%directory%~) AS _ => subdirectory BEGIN
		LAF ad_mod_files STR_VAR directory = EVAL ~%subdirectory%~ extension RET_ARRAY files END
	END
END

DEFINE_PATCH_MACRO ad_install_item BEGIN
	SET ad_processed += 1
	PATCH_IF ad_processed MODULO 100 == 0 BEGIN
		PATCH_PRINT "%ad_processed% items processed"
	END
	PATCH_TRY
		LPF ad_install_item_description STR_VAR log_name RET ad_status = status ad_ignore_reason = ignore_reason END
	WITH DEFAULT
		SPRINT ad_status ~failed~
		SPRINT ad_error ~%ERROR_MESSAGE%~
	END
	LPM ad_count_install_status
END

DEFINE_PATCH_MACRO ad_install_spell BEGIN
	SET ad_processed += 1
	PATCH_IF ad_processed MODULO 100 == 0 BEGIN
		PATCH_PRINT "%ad_processed% spells processed"
	END
	PATCH_TRY
		LPF ad_install_spell_description STR_VAR log_name RET ad_status = status ad_ignore_reason = ignore_reason END
	WITH DEFAULT
		SPRINT ad_status ~failed~
		SPRINT ad_error ~%ERROR_MESSAGE%~
	END
	LPM ad_count_install_status
END

// ad_status : ok, ignored (ad_ignore_reason) ou failed (ad_error).
DEFINE_PATCH_MACRO ad_count_install_status BEGIN
	PATCH_IF ~%ad_status%~ STRING_EQUAL ~ok~ BEGIN
		SET ad_successful += 1
	END
	ELSE PATCH_IF ~%ad_status%~ STRING_EQUAL ~ignored~ BEGIN
		PATCH_IF NOT VARIABLE_IS_SET $ad_ignored(~%ad_ignore_reason%~) BEGIN
			SET $ad_ignored(~%ad_ignore_reason%~) = 0
		END
		SET $ad_ignored(~%ad_ignore_reason%~) += 1
	END
	ELSE BEGIN
		SET ad_failed += 1
		LPF ad_add_install_log STR_VAR log_name message = ~FAILURE: %ad_error%~ END
		PATCH_IF regression_dump BEGIN
			LPF ad_add_dump_row STR_VAR log_name status = ~failed~ description = ~%ad_error%~ END
		END
	END
END

// ---------------------------------------------------------------------------------------------
// Objets

DEFINE_PATCH_FUNCTION ad_install_item_description
	STR_VAR
		log_name = ~~
	RET
		status
		ignore_reason
BEGIN
	PATCH_SILENT
	SPRINT status ~ignored~
	PATCH_TIME ~step:filter~ BEGIN
		LPF ad_item_ignore_reason STR_VAR log_name RET ignore_reason END
	END
	PATCH_IF ~%ignore_reason%~ STRING_EQUAL ~~ BEGIN
		READ_SHORT  ITM_type              item_type
		READ_SHORT  ITM_enchantment       enchantment
		READ_LONG   ITM_identified_desc   description_ref
		READ_STRREF ITM_identified_desc   original_description
		// Sans description identifiée, c'est la description non identifiée qui est décrite.
		SET use_unidentified = ~%original_description%~ STRING_EQUAL ~~ OR description_ref <= 0
		PATCH_IF use_unidentified BEGIN
			READ_STRREF ITM_unidentified_desc original_description
		END
		PATCH_TIME ~step:describe~ BEGIN
			LPF ad_describe_item STR_VAR original_description log_name RET description covered END
		END
		PATCH_IF covered BEGIN
			PATCH_IF alter_item_files BEGIN
				PATCH_IF use_unidentified BEGIN
					SAY UNIDENTIFIED_DESC ~%description%~
				END
				ELSE BEGIN
					SAY DESC ~%description%~
				END
			END
			PATCH_TIME ~step:outputs~ BEGIN
				LPF ad_item_name RET item_name END
				LPF ad_add_compare_row STR_VAR log_name name = ~%item_name%~ original_description description END
				LPF ad_add_js_row STR_VAR log_name id = ~%SOURCE_RES%~ name = ~%item_name%~ type = ~%item_type%~ level = ~%enchantment%~ original = ~%original_description%~ modded = ~%description%~ END
				SPRINT status ~ok~
				// En dernier : une erreur plus haut ne doit laisser que la ligne « failed » de l'appelant.
				PATCH_IF regression_dump BEGIN
					LPF ad_add_dump_row STR_VAR log_name description END
				END
			END
		END
		ELSE BEGIN
			SPRINT ignore_reason ~not_covered~
		END
	END
	PATCH_IF ~%status%~ STRING_EQUAL ~ignored~ AND regression_dump BEGIN
		PATCH_TIME ~step:outputs~ BEGIN
			LPF ad_add_dump_row STR_VAR log_name status = ~ignored:%ignore_reason%~ END
		END
	END
END

// Raison pour laquelle l'objet n'est pas décrit (clé de AD_IGNORE_LABELS), vide s'il l'est.
DEFINE_PATCH_FUNCTION ad_item_ignore_reason
	STR_VAR
		log_name = ~~
	RET
		ignore_reason
BEGIN
	SPRINT ignore_reason ~~
	SPRINT signature ~~
	PATCH_IF SOURCE_SIZE > 0x71 BEGIN
		READ_ASCII 0 signature (8)
	END
	PATCH_IF SOURCE_SIZE <= 0x71 BEGIN
		SPRINT ignore_reason ~invalid_file~
		LPF ad_add_install_log STR_VAR log_name type = ~error~ message = ~Invalid file.~ END
	END
	ELSE PATCH_IF NOT (~%signature%~ STRING_EQUAL ~ITM V1  ~) BEGIN
		SPRINT ignore_reason ~invalid_file~
		LPF ad_add_install_log STR_VAR log_name type = ~error~ message = ~Invalid file: signature "%signature%" (expected "ITM V1  ").~ END
	END
	ELSE BEGIN
		READ_SHORT  ITM_type              item_type
		READ_SHORT  ITM_flags             flags
		READ_LONG   ITM_identified_desc   description_ref
		READ_STRREF ITM_identified_desc   description
		READ_LONG   ITM_unidentified_desc unidentified_ref
		READ_STRREF ITM_unidentified_desc unidentified
		PATCH_IF NOT include_cursed_items AND (flags BAND BIT4) == BIT4 BEGIN
			SPRINT ignore_reason ~cursed~
		END
		ELSE PATCH_IF NOT include_items_without_description AND (~%description%~ STRING_EQUAL ~~ OR description_ref <= 0) AND (~%unidentified%~ STRING_EQUAL ~~ OR unidentified_ref <= 0) BEGIN
			SPRINT ignore_reason ~without_description~
		END
		// Un objet qui ne peut pas être déplacé n'est normalement pas accessible au joueur.
		ELSE PATCH_IF NOT include_non_moveable_items AND (flags BAND BIT2) == 0 BEGIN
			SPRINT ignore_reason ~not_moveable~
		END
		ELSE BEGIN
			PATCH_MATCH item_type
			WITH
				// Les armes
				ITM_TYPE_bow ITM_TYPE_dagger ITM_TYPE_mace ITM_TYPE_sling ITM_TYPE_small_sword ITM_TYPE_large_sword
				ITM_TYPE_hammer ITM_TYPE_morning_star ITM_TYPE_flail ITM_TYPE_dart ITM_TYPE_axe ITM_TYPE_quarterstaff
				ITM_TYPE_crossbow ITM_TYPE_hand_to_hand_hth ITM_TYPE_spear ITM_TYPE_halberd ITM_TYPE_polearm
				// Les autres objets équipables
				ITM_TYPE_armor ITM_TYPE_shield_not_in_iwd ITM_TYPE_necklace ITM_TYPE_amulet ITM_TYPE_belt ITM_TYPE_girdle
				ITM_TYPE_boots ITM_TYPE_bracers ITM_TYPE_gauntlets ITM_TYPE_helm ITM_TYPE_ring ITM_TYPE_cloak
				// Les consommables
				ITM_TYPE_potion ITM_TYPE_wand ITM_TYPE_scroll
				// Les munitions
				ITM_TYPE_arrows ITM_TYPE_bullets ITM_TYPE_bolts
			BEGIN
			END
			DEFAULT
				SPRINT ignore_reason ~type~
			END
		END
	END
END

DEFINE_PATCH_FUNCTION ad_item_name
	RET
		item_name
BEGIN
	SPRINT item_name ~~
	READ_LONG ITM_identified_name name_ref
	PATCH_IF name_ref > 0 BEGIN
		READ_STRREF ITM_identified_name item_name
	END
	ELSE BEGIN
		READ_LONG ITM_unidentified_name name_ref
		PATCH_IF name_ref > 0 BEGIN
			READ_STRREF ITM_unidentified_name item_name
		END
	END
END

// ---------------------------------------------------------------------------------------------
// Sorts

DEFINE_PATCH_FUNCTION ad_install_spell_description
	STR_VAR
		log_name = ~~
	RET
		status
		ignore_reason
BEGIN
	PATCH_SILENT
	SPRINT status ~ignored~
	PATCH_TIME ~step:filter~ BEGIN
		LPF ad_spell_ignore_reason STR_VAR log_name RET ignore_reason END
	END
	PATCH_IF ~%ignore_reason%~ STRING_EQUAL ~~ BEGIN
		READ_STRREF SPL_unidentified_name        spell_name
		READ_LONG   SPL_level                    spell_level
		READ_BYTE   SPL_school                   spell_school
		READ_STRREF SPL_unidentified_description original_description
		PATCH_TIME ~step:describe~ BEGIN
			LPF ad_describe_spell STR_VAR original_description log_name RET description covered END
		END
		PATCH_IF covered BEGIN
			PATCH_IF alter_spell_files BEGIN
				SAY SPL_unidentified_description ~%description%~
			END
			PATCH_TIME ~step:outputs~ BEGIN
				LPF ad_add_compare_row STR_VAR log_name name = ~%spell_name%~ original_description description END
				LPF ad_add_js_row STR_VAR log_name id = ~%SOURCE_RES%~ name = ~%spell_name%~ type = ~%spell_school%~ level = ~%spell_level%~ original = ~%original_description%~ modded = ~%description%~ END
				SPRINT status ~ok~
				// En dernier : une erreur plus haut ne doit laisser que la ligne « failed » de l'appelant.
				PATCH_IF regression_dump BEGIN
					LPF ad_add_dump_row STR_VAR log_name description END
				END
			END
		END
		ELSE BEGIN
			SPRINT ignore_reason ~not_covered~
		END
	END
	PATCH_IF ~%status%~ STRING_EQUAL ~ignored~ AND regression_dump BEGIN
		PATCH_TIME ~step:outputs~ BEGIN
			LPF ad_add_dump_row STR_VAR log_name status = ~ignored:%ignore_reason%~ END
		END
	END
END

// Raison pour laquelle le sort n'est pas décrit (clé de AD_IGNORE_LABELS), vide s'il l'est.
DEFINE_PATCH_FUNCTION ad_spell_ignore_reason
	STR_VAR
		log_name = ~~
	RET
		ignore_reason
BEGIN
	SPRINT ignore_reason ~~
	SPRINT signature ~~
	SET header_count = 1
	PATCH_IF SOURCE_SIZE > 0x71 BEGIN
		READ_ASCII 0 signature (8)
		READ_SHORT SPL_extended_headers_count header_count
	END
	PATCH_IF SOURCE_SIZE <= 0x71 BEGIN
		SPRINT ignore_reason ~invalid_file~
		LPF ad_add_install_log STR_VAR log_name type = ~error~ message = ~Invalid file.~ END
	END
	ELSE PATCH_IF NOT (~%signature%~ STRING_EQUAL ~SPL V1  ~) BEGIN
		SPRINT ignore_reason ~invalid_file~
		LPF ad_add_install_log STR_VAR log_name type = ~error~ message = ~Invalid file: signature "%signature%" (expected "SPL V1  ").~ END
	END
	// Un sort sans en-tête étendu n'a ni portée, ni cible, ni projectile à décrire.
	ELSE PATCH_IF header_count == 0 BEGIN
		SPRINT ignore_reason ~no_ability~
		LPF ad_add_install_log STR_VAR log_name message = ~Spell without extended header (%SOURCE_RES%): ignored.~ END
	END
	ELSE BEGIN
		READ_LONG   SPL_unidentified_name        name_ref
		READ_STRREF SPL_unidentified_name        spell_name
		READ_LONG   SPL_unidentified_description description_ref
		READ_STRREF SPL_unidentified_description description
		PATCH_IF NOT include_spells_without_description AND (~%description%~ STRING_EQUAL ~~ OR description_ref <= 0) BEGIN
			SPRINT ignore_reason ~without_description~
		END
		ELSE PATCH_IF NOT include_spells_without_name AND (~%spell_name%~ STRING_EQUAL ~~ OR name_ref <= 0) BEGIN
			SPRINT ignore_reason ~without_name~
		END
		// STRING_MATCHES_REGEXP vaut 0 quand le texte correspond.
		ELSE PATCH_IF NOT ~%description%~ STRING_MATCHES_REGEXP ~<Invalid Strref -?[0-9]+>~ OR NOT ~%spell_name%~ STRING_MATCHES_REGEXP ~<Invalid Strref -?[0-9]+>~ BEGIN
			SPRINT ignore_reason ~invalid_strref~
		END
	END
END

// ---------------------------------------------------------------------------------------------
// Journaux de la boucle

// Pendant la boucle, les lignes d'un journal log_file vont dans son tronçon log_part
// (« <log_file>.<n>.part », n = ad_processed / AD_LOG_PART_SIZE), créé vide au besoin : APPEND_OUTER
// échoue sur un fichier absent. ad_join_log_parts les réunit à la fermeture. Le COPY qui crée le
// tronçon remplace les variables SOURCE_* et DEST_* de la ressource en cours, que la ligne écrite
// ensuite et le reste de sa description lisent : elles sont restaurées à la sortie de la macro.
DEFINE_PATCH_MACRO ad_log_part BEGIN
	LOCAL_SPRINT SOURCE_DIRECTORY ~%SOURCE_DIRECTORY%~
	LOCAL_SPRINT SOURCE_FILESPEC ~%SOURCE_FILESPEC%~
	LOCAL_SPRINT SOURCE_FILE ~%SOURCE_FILE%~
	LOCAL_SPRINT SOURCE_RES ~%SOURCE_RES%~
	LOCAL_SPRINT SOURCE_EXT ~%SOURCE_EXT%~
	LOCAL_SET SOURCE_SIZE = SOURCE_SIZE
	LOCAL_SPRINT DEST_DIRECTORY ~%DEST_DIRECTORY%~
	LOCAL_SPRINT DEST_FILESPEC ~%DEST_FILESPEC%~
	LOCAL_SPRINT DEST_FILE ~%DEST_FILE%~
	LOCAL_SPRINT DEST_RES ~%DEST_RES%~
	LOCAL_SPRINT DEST_EXT ~%DEST_EXT%~
	SET log_part_index = ad_processed / AD_LOG_PART_SIZE
	SPRINT log_part ~%log_file%.%log_part_index%.part~
	PATCH_IF NOT FILE_EXISTS ~%log_part%~ BEGIN
		INNER_ACTION BEGIN
			SILENT
			COPY ~.../AutoDescription/inlined/ad_install_empty.txt~ ~%log_part%~
			VERBOSE
		END
	END
END

// Ajoute à la fin de file, dans l'ordre, les tronçons écrits par ad_log_part, puis les supprime. Le
// résultat est celui des APPEND_OUTER faits directement sur file : un APPEND_OUTER écrit « \r\n »
// avant le texte si le fichier est vide ou ne finit pas par un saut de ligne, puis le texte et
// « \r\n ». Chaque tronçon, créé vide, commence donc par « \r\n », gardé seulement devant le premier
// si file en demande un. WRITE_ASCIIE recopie le tronçon lu sans réévaluer les « %…% » de son texte.
DEFINE_ACTION_FUNCTION ad_join_log_parts
	STR_VAR
		file = ~~
BEGIN
	OUTER_SET join_last = ad_processed / AD_LOG_PART_SIZE
	OUTER_SET join_found = 0
	OUTER_FOR (join_n = 0; join_n <= join_last; ++join_n) BEGIN
		ACTION_IF SIZE_OF_FILE ~%file%.%join_n%.part~ > 0 BEGIN
			OUTER_SET join_found = 1
		END
	END
	ACTION_IF join_found BEGIN
		COPY ~%file%~ ~%file%~
			SET join_separator = 1
			PATCH_IF BUFFER_LENGTH > 0 BEGIN
				SET join_separator = (BYTE_AT (BUFFER_LENGTH - 1) != 10)
			END
			FOR (join_n = 0; join_n <= join_last; ++join_n) BEGIN
				PATCH_IF SIZE_OF_FILE ~%file%.%join_n%.part~ > 0 BEGIN
					SET join_skip = join_separator ? 0 : 2
					INNER_PATCH_FILE ~%file%.%join_n%.part~ BEGIN
						READ_ASCII join_skip join_chunk (BUFFER_LENGTH - join_skip)
					END
					SET join_separator = 0
					SET join_at = BUFFER_LENGTH
					INSERT_BYTES join_at (STRING_LENGTH ~%join_chunk%~)
					WRITE_ASCIIE join_at ~%join_chunk%~
				END
			END
	END
	OUTER_FOR (join_n = 0; join_n <= join_last; ++join_n) BEGIN
		ACTION_IF FILE_EXISTS ~%file%.%join_n%.part~ BEGIN
			DELETE + ~%file%.%join_n%.part~
		END
	END
END

// Journaux écrits pendant la boucle, réunis avant que la fermeture ne les complète ou ne les lise.
DEFINE_ACTION_FUNCTION ad_join_all_log_parts
	STR_VAR
		log_name = ~~
BEGIN
	ACTION_FOR_EACH join_log IN ~warning.log~ ~error.log~ ~diff.html~ ~dump.txt~ ~events.txt~ ~file-errors.md~ ~not-implemented.md~ ~recursion.txt~ BEGIN
		LAF ad_join_log_parts STR_VAR file = EVAL ~%MOD_FOLDER%/log/%log_name%-%join_log%~ END
	END
	LAF ad_join_log_parts STR_VAR file = EVAL ~docs/data/%log_name%.js~ END
END

// type : warning ou error (AutoDescription/log/<log_name>-<type>.log).
DEFINE_PATCH_FUNCTION ad_add_install_log
	STR_VAR
		log_name = ~~
		type = ~warning~
		message = ~~
BEGIN
	PATCH_TIME ~step:install_log~ BEGIN
		SPRINT log_file ~%MOD_FOLDER%/log/%log_name%-%type%.log~
		LPM ad_log_part
		INNER_ACTION BEGIN
			APPEND_OUTER ~%log_part%~ ~%SOURCE_FILE% : %message%~
		END
	END
END

// Échappe escape_in et range le résultat dans la variable nommée par escape_out (macro : un LPF par
// texte copierait chaque fois toutes les variables).
DEFINE_PATCH_MACRO ad_html_escape_to BEGIN
	INNER_PATCH_SAVE escape_text ~%escape_in%~ BEGIN
		REPLACE_TEXTUALLY EXACT_MATCH ~&~ ~&amp;~
		REPLACE_TEXTUALLY EXACT_MATCH ~<~ ~&lt;~
		REPLACE_TEXTUALLY EXACT_MATCH ~>~ ~&gt;~
	END
	SPRINT ~%escape_out%~ ~%escape_text%~
END

DEFINE_PATCH_FUNCTION ad_add_compare_row
	STR_VAR
		log_name = ~~
		name = ~~
		original_description = ~~
		description = ~~
BEGIN
	SPRINT escape_in ~%name%~                 SPRINT escape_out ~html_name~        LPM ad_html_escape_to
	SPRINT escape_in ~%original_description%~ SPRINT escape_out ~html_original~    LPM ad_html_escape_to
	SPRINT escape_in ~%description%~          SPRINT escape_out ~html_description~ LPM ad_html_escape_to
	SPRINT log_file ~%MOD_FOLDER%/log/%log_name%-diff.html~
	LPM ad_log_part
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~%log_part%~ ~<tr><th class="title">%SOURCE_RES%<br/>%html_name%</th><td class="description before"><pre>%html_original%</pre></td><td class="description after"><pre>%html_description%</pre></td></tr>~ KEEP_CRLF
		VERBOSE
	END
END

// Format : RESREF<TAB>statut<TAB>texte. L'échappement (\\, \r, \n, \t) est réversible et garantit
// une ressource par ligne. Les chaînes ~...~ sont littérales, mais la regexp et le texte de
// remplacement sont interprétés par Str, où \\ désigne une seule barre oblique inverse.
DEFINE_PATCH_FUNCTION ad_add_dump_row
	STR_VAR
		log_name = ~~
		status = ~ok~
		description = ~~
BEGIN
	INNER_PATCH_SAVE description ~%description%~ BEGIN
		REPLACE_TEXTUALLY ~\\~ ~\\\\~
		REPLACE_TEXTUALLY ~%MNL%~ ~\\r~
		REPLACE_TEXTUALLY ~%LNL%~ ~\\n~
		REPLACE_TEXTUALLY ~%TAB%~ ~\\t~
	END
	SPRINT log_file ~%MOD_FOLDER%/log/%log_name%-dump.txt~
	LPM ad_log_part
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~%log_part%~ ~%SOURCE_RES%%TAB%%status%%TAB%%description%~ KEEP_CRLF
		VERBOSE
	END
END

// ---------------------------------------------------------------------------------------------
// Données JS de docs/data/, écrites au fil de l'eau : accumuler les résultats dans un tableau
// renvoyé par RET_ARRAY à chaque ressource coûte un temps quadratique, car chaque LPF copie aussi
// les éléments des tableaux existants.

DEFINE_ACTION_FUNCTION ad_init_js_file
	STR_VAR
		log_name = ~~
BEGIN
	<<<<<<<< .../AutoDescription/inlined/ad_javascript.txt
window.loadedData = window.loadedData || {};
>>>>>>>>
	COPY ~.../AutoDescription/inlined/ad_javascript.txt~ ~docs/data/%log_name%.js~
	SILENT
	APPEND_OUTER ~docs/data/%log_name%.js~ ~window.loadedData["%log_name%-version"] = '%MOD_VERSION%';~ KEEP_CRLF
	APPEND_OUTER ~docs/data/%log_name%.js~ ~window.loadedData["%log_name%"] = [~ KEEP_CRLF
	VERBOSE
END

// Comme ad_html_escape_to.
DEFINE_PATCH_MACRO ad_js_escape_to BEGIN
	INNER_PATCH_SAVE escape_text ~%escape_in%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~\\~ ~\\\\~
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~%WNL%~ ~\n~
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~%LNL%~ ~\n~
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~%MNL%~ ~\n~
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~%TAB%~ ~\t~
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~"~ ~\"~
	END
	SPRINT ~%escape_out%~ ~%escape_text%~
END

DEFINE_PATCH_FUNCTION ad_add_js_row
	STR_VAR
		log_name = ~~
		id = ~~
		name = ~~
		type = ~~
		level = ~~
		original = ~~
		modded = ~~
BEGIN
	SPRINT escape_in ~%id%~       SPRINT escape_out ~id~       LPM ad_js_escape_to
	SPRINT escape_in ~%name%~     SPRINT escape_out ~name~     LPM ad_js_escape_to
	SPRINT escape_in ~%original%~ SPRINT escape_out ~original~ LPM ad_js_escape_to
	SPRINT escape_in ~%modded%~   SPRINT escape_out ~modded~   LPM ad_js_escape_to
	SPRINT log_file ~docs/data/%log_name%.js~
	LPM ad_log_part
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~%log_part%~ ~{"id":"%id%","name":"%name%","type":%type%,"level":%level%,"original":"%original%","modded":"%modded%"},~ KEEP_CRLF
		VERBOSE
	END
END

// Ferme le tableau du composant et refait docs/data/mods.js, liste des mods dont des données
// existent (nom des fichiers « <langue>-<jeu>-<mod>-<type>.js »).
DEFINE_ACTION_FUNCTION ad_close_js_file
	STR_VAR
		log_name = ~~
BEGIN
	SILENT
	APPEND_OUTER ~docs/data/%log_name%.js~ ~{}];~ KEEP_CRLF
	APPEND_OUTER ~docs/data/%log_name%.js~ ~window.loadedData["%log_name%"] = window.loadedData["%log_name%"].filter(entry => Object.keys(entry).length > 0);~ KEEP_CRLF
	VERBOSE

	<<<<<<<< .../AutoDescription/inlined/ad_javascript.txt
window.loadedMods = [...new Set([
>>>>>>>>
	COPY ~.../AutoDescription/inlined/ad_javascript.txt~ ~docs/data/mods.js~
	COPY GLOB ~docs/data~ ~override~
		SPRINT file_name ~%SOURCE_RES%~
		PATCH_IF (~%file_name%~ STRING_MATCHES_REGEXP ~^[^-]+-[^-]+-\(.+\)-[^-]+$~ = 0) BEGIN
			INNER_PATCH ~%SOURCE_RES%~ BEGIN
				REPLACE_EVALUATE ~^[^-]+-[^-]+-\(.+\)-[^-]+$~ BEGIN
					INNER_ACTION BEGIN
						APPEND_OUTER ~docs/data/mods.js~ ~"%MATCH1%",~ KEEP_CRLF
					END
				END ~~
			END
		END
	BUT_ONLY_IF_IT_CHANGES
	APPEND_OUTER ~docs/data/mods.js~ ~"all"])];~ KEEP_CRLF
END
