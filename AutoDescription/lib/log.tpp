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

// L'échappement (\\, \r, \n, \t) est réversible et garantit une ressource par ligne. Les chaînes
// ~...~ sont littérales, mais la regexp et le texte de remplacement sont interprétés par Str, où
// \\ désigne une seule barre oblique inverse.
DEFINE_PATCH_FUNCTION ~escape_dump_text~
	STR_VAR
		text = ~~
	RET
		text
BEGIN
	INNER_PATCH_SAVE text ~%text%~ BEGIN
		REPLACE_TEXTUALLY ~\\~ ~\\\\~
		REPLACE_TEXTUALLY ~%MNL%~ ~\\r~
		REPLACE_TEXTUALLY ~%LNL%~ ~\\n~
		REPLACE_TEXTUALLY ~%TAB%~ ~\\t~
	END
END

// Format : RESREF<TAB>statut<TAB>texte échappé.
DEFINE_PATCH_FUNCTION ~add_regression_dump_row~
	STR_VAR
		resref = ~%SOURCE_RES%~
		status = ~ok~
		description = ~~
BEGIN
	LPF ~escape_dump_text~ STR_VAR text = ~%description%~ RET description = text END
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~AutoDescription/log/%log_filename%-dump.txt~ ~%resref%%TAB%%status%%TAB%%description%~ KEEP_CRLF
		VERBOSE
	END
END

// Choisit la description enregistrée selon description_engine et, en modes 2 et 3, compare les
// deux moteurs. Une ressource non couverte par le nouveau moteur est exclue de la comparaison et,
// en modes 1 et 3, n'est pas décrite : un texte partiel ne doit jamais être enregistré.
DEFINE_PATCH_FUNCTION ~select_engine_description~
	INT_VAR
		covered = 0
	STR_VAR
		description = ~~
		new_description = ~~
		uncovered_reason = ~~
	RET
		description
		is_described
		totalEngineIdentical
		totalEngineDifferent
		totalEngineNotCovered
BEGIN
	PATCH_IF NOT covered BEGIN
		SET totalEngineNotCovered += 1
	END
	PATCH_IF description_engine >= 2 BEGIN
		LPF ~add_engine_comparison_row~ INT_VAR covered STR_VAR old_description = ~%description%~ new_description uncovered_reason RET totalEngineIdentical totalEngineDifferent END
	END
	SET is_described = 1
	PATCH_IF description_engine == 1 OR description_engine == 3 BEGIN
		SPRINT description ~%new_description%~
		SET is_described = covered
	END
END

// En modes 1 et 3, les ressources non couvertes sont aussi comptées parmi les ignorées.
DEFINE_ACTION_MACRO ~show_engine_statistics~ BEGIN
	ACTION_IF description_engine == 1 BEGIN
		PRINT "Non couverts par le nouveau moteur (non modifies) : %totalEngineNotCovered%"
	END
	ELSE ACTION_IF description_engine >= 2 BEGIN
		PRINT "Comparaison des moteurs :
   Identiques : %totalEngineIdentical%
   Differents : %totalEngineDifferent%
   Non couverts par le nouveau moteur : %totalEngineNotCovered%"
	END
END

// Format : RESREF<TAB>identical | RESREF<TAB>not_covered<TAB>raison |
// RESREF<TAB>different<TAB>ancien texte<TAB>nouveau texte, textes échappés comme dans le dump.
// Comme toute copie par SPRINT ou STR_VAR, STRING_EQUAL substitue les %variables% contenues dans
// les textes (weidu-reference.md V29), de la même façon des deux côtés.
DEFINE_PATCH_FUNCTION ~add_engine_comparison_row~
	INT_VAR
		covered = 0
	STR_VAR
		old_description = ~~
		new_description = ~~
		uncovered_reason = ~~
	RET
		totalEngineIdentical
		totalEngineDifferent
BEGIN
	PATCH_IF NOT covered BEGIN
		LPF ~escape_dump_text~ STR_VAR text = ~%uncovered_reason%~ RET reason = text END
		SPRINT row ~not_covered%TAB%%reason%~
	END
	ELSE PATCH_IF ~%old_description%~ STRING_EQUAL ~%new_description%~ BEGIN
		SET totalEngineIdentical += 1
		SPRINT row ~identical~
	END
	ELSE BEGIN
		SET totalEngineDifferent += 1
		LPF ~escape_dump_text~ STR_VAR text = ~%old_description%~ RET old_text = text END
		LPF ~escape_dump_text~ STR_VAR text = ~%new_description%~ RET new_text = text END
		SPRINT row ~different%TAB%%old_text%%TAB%%new_text%~
	END
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~AutoDescription/log/%log_filename%-compare.txt~ ~%SOURCE_RES%%TAB%%row%~ KEEP_CRLF
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
	ACTION_IF description_engine >= 2 BEGIN
		COPY ~.../AutoDescription/inlined/empty.log~ ~AutoDescription/log/%log_filename%-compare.txt~
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