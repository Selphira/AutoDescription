/* ============================================================== *
 * Gestion de la section "Nécessite" de la description.           *
 * ============================================================== */

DEFINE_PATCH_FUNCTION ~needs~ RET description BEGIN
	READ_BYTE ITM_min_level          minLevel
	READ_BYTE ITM_min_strength       minStrength
	READ_BYTE ITM_min_strength_bonus minStrengthBonus
	READ_BYTE ITM_min_intelligence   minIntelligence
	READ_BYTE ITM_min_dexterity      minDexterite
	READ_BYTE ITM_min_wisdom         minWisdom
	READ_BYTE ITM_min_constitution   minConstitution
	READ_BYTE ITM_min_charisma       minCharisma

	PATCH_DEFINE_ARRAY ~needs~ BEGIN END
	SET countNeeds = 0

 	LPF ~needs_attribute~ INT_VAR value = minLevel strref = 101082 RET countNeeds RET_ARRAY needs END
 	LPF ~needs_attribute~ INT_VAR value = minStrength bonus = minStrengthBonus strref = 101076 RET countNeeds RET_ARRAY needs END
 	LPF ~needs_attribute~ INT_VAR value = minIntelligence strref = 101077 RET countNeeds RET_ARRAY needs END
 	LPF ~needs_attribute~ INT_VAR value = minDexterite strref = 101078 RET countNeeds RET_ARRAY needs END
 	LPF ~needs_attribute~ INT_VAR value = minWisdom strref = 101079 RET countNeeds RET_ARRAY needs END
 	LPF ~needs_attribute~ INT_VAR value = minConstitution strref = 101080 RET countNeeds RET_ARRAY needs END
 	LPF ~needs_attribute~ INT_VAR value = minCharisma strref = 101081 RET countNeeds RET_ARRAY needs END

 	PATCH_IF countNeeds > 0 BEGIN
		LPF ~appendSection~ INT_VAR strref = 101075 RET description END
		PATCH_PHP_EACH needs AS name => value BEGIN
			LPF ~appendProperty~ STR_VAR name value RET description END
		END
 	END
END

DEFINE_PATCH_FUNCTION ~needs_attribute~ INT_VAR value = 0 bonus = 0 strref = 0 RET countNeeds RET_ARRAY needs BEGIN
 	PATCH_IF value > 0 BEGIN
		SET countNeeds += 1
		SPRINT name (AT %strref%)
		PATCH_IF value == 18 AND bonus > 0 AND bonus <= 100 BEGIN
			PATCH_IF bonus == 100 BEGIN
				SPRINT bonus ~00~
			END
			SPRINT $needs(~%name%~)  ~%value%/%bonus%~
		END
		ELSE BEGIN
			SET $needs(~%name%~) = value
		END
 	END
END