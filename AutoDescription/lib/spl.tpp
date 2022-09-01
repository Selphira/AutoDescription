DEFINE_PATCH_FUNCTION ~update_spell_description~
BEGIN
END

/*
DEFINE_PATCH_FUNCTION ~get_spell_description~
	STR_VAR
		file = ~~
	RET
		description
BEGIN
	INNER_PATCH_FILE ~%file%.spl~ BEGIN
	END
END
*/