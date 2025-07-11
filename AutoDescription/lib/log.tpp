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
	INNER_ACTION BEGIN
		SILENT
		APPEND_OUTER ~AutoDescription/log/%log_filename%-diff.html~ ~<tr><th class="title">%filename%<br/>%itemName%</th><td class="description before"><pre>%originalDescription%</pre></td><td class="description after"><pre>%description%</pre></td></tr>~ KEEP_CRLF
		VERBOSE
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
	ACTION_IF is_ee BEGIN
		COPY ~AutoDescription/log/template_ee.html~ ~AutoDescription/log/%log_filename%-diff.html~
	END
	ELSE BEGIN
		COPY ~AutoDescription/log/template.html~ ~AutoDescription/log/%log_filename%-diff.html~
	END
END

DEFINE_ACTION_FUNCTION ~write_js~
	STR_VAR
		array = ~~
BEGIN
	<<<<<<<< .../AutoDescription/inlined/javascript.log
window.loadedData = window.loadedData || {};
>>>>>>>>
	COPY ~.../AutoDescription/inlined/javascript.log~ ~docs/data/%log_filename%.js~
    SILENT
    APPEND_OUTER ~docs/data/%log_filename%.js~ ~window.loadedData["%log_filename%"] = [~ KEEP_CRLF
	ACTION_PHP_EACH ~%array%~ AS line => _ BEGIN
        OUTER_PATCH_SAVE line_2 ~%line_2%~ BEGIN
            REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~\n~
            REPLACE_TEXTUALLY EVALUATE_REGEXP ~"~ ~\"~
        END
        OUTER_PATCH_SAVE line_3 ~%line_3%~ BEGIN
            REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~\n~
            REPLACE_TEXTUALLY EVALUATE_REGEXP ~"~ ~\"~
        END
        APPEND_OUTER ~docs/data/%log_filename%.js~ ~{"id":"%line_0%","name":"%line_1%","type":%line_4%,"level":%line_5%,"original":"%line_2%","modded":"%line_3%"},~ KEEP_CRLF
    END
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