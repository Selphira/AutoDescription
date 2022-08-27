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
		APPEND_OUTER ~AutoDescription/log/%type%-%log_filename%.log~ ~%SOURCE_FILE% : %message%~
	END
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