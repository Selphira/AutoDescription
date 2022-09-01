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
	APPEND_OUTER ~AutoDescription/log/%type%-%log_filename%.log~ ~%SOURCE_FILE% : %message%~
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
		APPEND_OUTER ~AutoDescription/log/diff-%log_filename%.html~ ~<tr><th class="title">%filename%<br/>%itemName%</th><td class="description before"><pre>%originalDescription%</pre></td><td class="description after"><pre>%description%</pre></td></tr>~ KEEP_CRLF
		VERBOSE
	END
END

DEFINE_ACTION_MACRO ~init_log_file~ BEGIN
	// Initialisation des fichiers de log
	<<<<<<<< .../AutoDescription/inlined/empty.log
	>>>>>>>>
	COPY ~.../AutoDescription/inlined/empty.log~ ~AutoDescription/log/warning-%log_filename%.log~
	COPY ~.../AutoDescription/inlined/empty.log~ ~AutoDescription/log/error-%log_filename%.log~
	ACTION_IF is_ee BEGIN
		COPY ~AutoDescription/log/template_ee.html~ ~AutoDescription/log/diff-%log_filename%.html~
	END
	ELSE BEGIN
		COPY ~AutoDescription/log/template.html~ ~AutoDescription/log/diff-%log_filename%.html~
	END
END