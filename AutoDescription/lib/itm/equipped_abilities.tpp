/* ================================================================= *
 * Gestion de la section "Capacités d'équipement" de la description. *
 * ================================================================= */
DEFINE_PATCH_FUNCTION ~add_equipped_abilities~
	STR_VAR
		description = ~~
	RET
		description
		countGlobalLines
	RET_ARRAY
		globalLines
BEGIN
    READ_LONG ITM_flags flags

	SET abilityType = AbilityType_Equipped

	LPF ~load_equipped_abilities~ RET countLines countGlobalLines RET_ARRAY lines globalLines END

	PATCH_IF (flags BAND BIT4) != 0 BEGIN
		SET countLines += 1
		SPRINT effectDescription @102126 // ~Maudit : Ne peut être ôté qu'à l'aide d'un sort de Délivrance de la malédiction~
		SET $lines(~-2~ ~0~ ~100~ ~0~ ~99~ ~%effectDescription%~) = 1
	END

	PATCH_IF itemType == ITM_TYPE_helm BEGIN
		PATCH_IF ((flags BAND BIT25) == 0 AND itemType == ITM_TYPE_helm) OR ((flags BAND BIT25) == BIT25 AND itemType != ITM_TYPE_helm) BEGIN
			SET countLines += 1
			SPRINT effectDescription @102679 // ~Protection contre les coups critiques~
			SET $lines(~-1~ ~0~ ~100~ ~0~ ~99~ ~%effectDescription%~) = 1
		END
	END

	SPRINT title @100010 // ~Capacités d'équipement~
	LPF ~add_section_to_description~ INT_VAR count = countLines STR_VAR title arrayName = ~lines~ RET description END
END


DEFINE_PATCH_FUNCTION ~load_equipped_abilities~
	RET
		countLines
		countGlobalLines
	RET_ARRAY
		lines
		globalLines
BEGIN
	SET countLines = 0
	SET countGlobalLines = 0

	CLEAR_ARRAY lines
	CLEAR_ARRAY globalLines
	CLEAR_ARRAY opcodes

    PATCH_DEFINE_ASSOCIATIVE_ARRAY lines BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY globalLines BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY opcodes BEGIN END

	LPM ~load_feature_effects~
	LPM ~replace_effects~
	LPM ~filter_effects~
	LPM ~group_effects~

	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~
				SET isGlobal = 0
				SET baseOpcode = opcode

				// ITM global (equipped) effects: Target is always the wearer, this field isn’t relevant.
				SET target = TARGET_FX_self

				PATCH_IF opcode >= 1000 AND opcode < 2000 BEGIN
					SET opcode -= 1000
					SET isGlobal = 1
				END

				LPF ~get_effect_description~ RET effectDescription = description sort END
				PATCH_IF NOT ~%effectDescription%~ STRING_EQUAL ~~ BEGIN
					PATCH_IF isGlobal BEGIN
						SET $globalLines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 100
						SET countGlobalLines += 1
					END
					ELSE BEGIN
						SET $lines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 1
						SET countLines += 1
					END
				END
				SET opcode = baseOpcode
		    END
	    END
	END

	PATCH_IF isArmor AND NOT isRobe AND armor_show_allows_to_cast_spells BEGIN
		LPF ~has_opcode~
			INT_VAR opcode = 145
			STR_VAR expression = ~probability = 100 AND parameter2 = 0~
			RET hasOpcode
		END
		PATCH_IF NOT hasOpcode BEGIN
			SPRINT effectDescription @102127 // ~Permet de lancer des sorts profanes~
			SET sort = $sort_opcodes(~145~)
			SET $lines(~%sort%~ ~%countLines%~ ~100~ ~0~ ~99~ ~%effectDescription%~) = 1
			SET countLines += 1
		END
	END

	LPF ~get_unique_effects~ RET countLines = count RET_ARRAY lines = effects END
	LPF ~group_probability_effects~ RET countLines = count RET_ARRAY lines = effects END
END
