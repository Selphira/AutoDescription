DEFINE_PATCH_FUNCTION ~proficiency~ RET description BEGIN
	READ_BYTE ITM_flags              flags
	READ_BYTE ITM_weapon_proficiency proficiency

	PATCH_IF (flags BAND BIT1) = 0 BEGIN
		SPRINT value @101083 // Arme à 1 main
	END
	ELSE BEGIN
		SPRINT value @101084 // Arme à 2 mains
	END

	LPF ~appendValue~ INT_VAR strref = 102003 STR_VAR value = $tra_proficiencies(~%proficiency%~) RET description END
	LPF ~appendValue~ INT_VAR strref = 102004 STR_VAR value RET description END
END

DEFINE_PATCH_FUNCTION ~weight~ RET description BEGIN
	READ_LONG ITM_weight weight
	LPF ~appendValue~ INT_VAR strref = 100002 STR_VAR value = EVAL ~%weight%~ RET description END
END

DEFINE_PATCH_FUNCTION ~uses~ RET description BEGIN
	SET countHeaders = 0

	GET_OFFSET_ARRAY headerOffsets ITM_V10_HEADERS
	PHP_EACH headerOffsets AS _ => headerOffset BEGIN
		READ_SHORT (headerOffset + ITM_HEAD_charges) charges
		READ_SHORT (headerOffset + ITM_HEAD_depletion) depletion

		PATCH_IF charges > 0 BEGIN
			SET countHeaders += 1
		END
	END

	PATCH_IF countHeaders == 1 AND NOT (charges == 1 AND depletion == 1) BEGIN
		LPF ~get_charged_string~ INT_VAR charges depletion RET chargeStr END
		LPF ~ucfirst~ STR_VAR value = ~%chargeStr%~ RET value = string END
		LPF ~appendValue~ INT_VAR strref = 101131 STR_VAR value RET description END // ~Utilisation~
	END
END