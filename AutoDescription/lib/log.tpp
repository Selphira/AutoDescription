DEFINE_PATCH_FUNCTION ~add_log_warning~
	STR_VAR
		message = ~~
BEGIN
	LPF ~add_log~ STR_VAR message type = ~warning~ END
END

DEFINE_PATCH_FUNCTION ~add_log_error~
	STR_VAR
		message = ~~
BEGIN
	LPF ~add_log~ STR_VAR message type = ~error~ END
END

DEFINE_PATCH_FUNCTION ~add_log~
	STR_VAR
		message = ~~
		type = ~warning~
BEGIN
	INNER_ACTION BEGIN
		LAF ~add_log~ STR_VAR message type END
	END
END

DEFINE_ACTION_FUNCTION ~add_log_warning~
	STR_VAR
		message = ~~
		type = ~warning~
BEGIN
	LAF ~add_log~ STR_VAR message type = ~warning~ END
END

DEFINE_ACTION_FUNCTION ~add_log_error~
	STR_VAR
		message = ~~
BEGIN
	LAF ~add_log~ STR_VAR message type = ~error~ END
END

DEFINE_ACTION_FUNCTION ~add_log~
	STR_VAR
		message = ~~
		type = ~warning~
BEGIN
	APPEND_OUTER ~AutoDescription/log/%log_filename%-%type%.log~ ~%SOURCE_FILE% : %message%~
END

DEFINE_PATCH_FUNCTION ~add_compare_row~
	STR_VAR
		filename = ~%SOURCE_RES%~
		itemName = ~~
		originalDescription = ~~
		description = ~~
BEGIN
	LPF html_escape STR_VAR text = ~%itemName%~            RET htmlItemName = text END
	LPF html_escape STR_VAR text = ~%originalDescription%~ RET htmlOriginal = text END
	LPF html_escape STR_VAR text = ~%description%~         RET htmlDescription = text END
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~AutoDescription/log/%log_filename%-diff.html~ ~<tr><th class="title">%filename%<br/>%htmlItemName%</th><td class="description before"><pre>%htmlOriginal%</pre></td><td class="description after"><pre>%htmlDescription%</pre></td></tr>~ KEEP_CRLF
		VERBOSE
	END
END

// Format : RESREF<TAB>statut<TAB>texte. L'échappement (\\, \r, \n, \t) est réversible et garantit
// une ressource par ligne. Les chaînes ~...~ sont littérales, mais la regexp et le texte de
// remplacement sont interprétés par Str, où \\ désigne une seule barre oblique inverse.
DEFINE_PATCH_FUNCTION ~add_regression_dump_row~
	STR_VAR
		resref = ~%SOURCE_RES%~
		status = ~ok~
		description = ~~
BEGIN
	INNER_PATCH_SAVE description ~%description%~ BEGIN
		REPLACE_TEXTUALLY ~\\~ ~\\\\~
		REPLACE_TEXTUALLY ~%MNL%~ ~\\r~
		REPLACE_TEXTUALLY ~%LNL%~ ~\\n~
		REPLACE_TEXTUALLY ~%TAB%~ ~\\t~
	END
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~AutoDescription/log/%log_filename%-dump.txt~ ~%resref%%TAB%%status%%TAB%%description%~ KEEP_CRLF
		VERBOSE
	END
END

// Le dispatch par PATCH_TRY sert à appeler une macro/fonction optionnelle, mais WITH DEFAULT
// avale aussi les erreurs survenues dans une macro existante : seule l'absence de la ressource
// dispatchée elle-même est normale. WeiDU met dans ERROR_MESSAGE le nom non évalué
// (« opcode_%opcode%_group ») ; STRING_EQUAL le réévalue, d'où la comparaison avec le nom capturé
// avant l'appel.
DEFINE_PATCH_FUNCTION ~log_swallowed_error~
	STR_VAR
		name = ~~
		type = ~macro~
		error = ~~
BEGIN
	PATCH_IF NOT (~%error%~ STRING_EQUAL ~Failure("Unknown %type%: %name%")~) BEGIN
		LPF ~add_log_error~ STR_VAR message = ~Swallowed error in %name%: %error%~ END
	END
END

DEFINE_PATCH_FUNCTION ~html_escape~
	STR_VAR text = ~~
	RET text
BEGIN
	INNER_PATCH_SAVE text ~%text%~ BEGIN
		REPLACE_TEXTUALLY EXACT_MATCH ~&~ ~&amp;~
		REPLACE_TEXTUALLY EXACT_MATCH ~<~ ~&lt;~
		REPLACE_TEXTUALLY EXACT_MATCH ~>~ ~&gt;~
	END
END

DEFINE_ACTION_FUNCTION ~init_log_file~
	STR_VAR
		type = ~items~
		mod = ~all~
	RET log_filename
BEGIN
	LAF ~get_game_name~ RET gameName END
	OUTER_SPRINT log_filename ~%LANGUAGE%-%gameName%-%mod%-%type%~
	// Initialisation des fichiers de log
	<<<<<<<< .../AutoDescription/inlined/empty.log
>>>>>>>>
	COPY ~.../AutoDescription/inlined/empty.log~ ~AutoDescription/log/%log_filename%-warning.log~
	COPY ~.../AutoDescription/inlined/empty.log~ ~AutoDescription/log/%log_filename%-error.log~
	ACTION_IF regression_dump BEGIN
		COPY ~.../AutoDescription/inlined/empty.log~ ~AutoDescription/log/%log_filename%-dump.txt~
	END
	ACTION_IF is_ee BEGIN
		COPY ~AutoDescription/log/template_ee.html~ ~AutoDescription/log/%log_filename%-diff.html~
	END
	ELSE BEGIN
		COPY ~AutoDescription/log/template.html~ ~AutoDescription/log/%log_filename%-diff.html~
	END
END

// Données JS écrites au fil de l'eau : accumuler les résultats dans un tableau renvoyé par
// RET_ARRAY à chaque ressource coûte un temps quadratique, car chaque LPF copie aussi les
// éléments des tableaux existants (refactoring-roadmap.md §3.2, mesures X1/X2).
DEFINE_ACTION_FUNCTION ~init_js_file~ BEGIN
	<<<<<<<< .../AutoDescription/inlined/javascript.log
window.loadedData = window.loadedData || {};
>>>>>>>>
	COPY ~.../AutoDescription/inlined/javascript.log~ ~docs/data/%log_filename%.js~
    SILENT
    APPEND_OUTER ~docs/data/%log_filename%.js~ ~window.loadedData["%log_filename%-version"] = '%MOD_VERSION%';~ KEEP_CRLF
    APPEND_OUTER ~docs/data/%log_filename%.js~ ~window.loadedData["%log_filename%"] = [~ KEEP_CRLF
    VERBOSE
END

DEFINE_PATCH_FUNCTION ~add_js_row~
	STR_VAR
		id = ~~
		name = ~~
		type = ~~
		level = ~~
		original = ~~
		modded = ~~
BEGIN
	INNER_PATCH_SAVE original ~%original%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~\n~
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~"~ ~\"~
	END
	INNER_PATCH_SAVE modded ~%modded%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~\n~
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~"~ ~\"~
	END
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~docs/data/%log_filename%.js~ ~{"id":"%id%","name":"%name%","type":%type%,"level":%level%,"original":"%original%","modded":"%modded%"},~ KEEP_CRLF
		VERBOSE
	END
END

DEFINE_ACTION_FUNCTION ~close_js_file~ BEGIN
    SILENT
    APPEND_OUTER ~docs/data/%log_filename%.js~ ~{}];~ KEEP_CRLF
    APPEND_OUTER ~docs/data/%log_filename%.js~ ~window.loadedData["%log_filename%"] = window.loadedData["%log_filename%"].filter(entry => Object.keys(entry).length > 0);~ KEEP_CRLF
    VERBOSE

	<<<<<<<< .../AutoDescription/inlined/javascript.log
window.loadedMods = [...new Set([
>>>>>>>>
	COPY ~.../AutoDescription/inlined/javascript.log~ ~docs/data/mods.js~
    COPY GLOB ~docs/data~ ~override~
        SPRINT filename "%SOURCE_RES%"

        PATCH_IF (~%filename%~ STRING_MATCHES_REGEXP ~^[^-]+-[^-]+-\(.+\)-[^-]+$~ = 0) BEGIN
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