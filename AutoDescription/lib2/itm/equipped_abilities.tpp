DEFINE_PATCH_FUNCTION ~add_equipped_abilities~
	STR_VAR
		description = ~~
	RET
		description
BEGIN
    READ_LONG ITM_flags flags

	SET abilityType = AbilityType_Equipped
	SET countLines = 0

	CLEAR_ARRAY lines
	CLEAR_ARRAY opcodes

    PATCH_DEFINE_ASSOCIATIVE_ARRAY lines BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY opcodes BEGIN END

	LPM ~load_feature_effects~

	//TODO: remplacer les opcodes 177 par l'opcode pointé ? Afin qu'ils soient pris en compte pour le regroupement
	//TODO: Déjà gérer le cas de l'opcode 177 ?
	//        Un opcode 177 va en vérité lancer un autre opcode, et ces ce dernier qui devra être groupé (sauf s'il appele aussi un 177...)
	//        L'opcode 177 modifie simplement la cible...


	LPM ~replace_effects~
	LPM ~filter_effects~
	LPM ~group_effects~

	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~

				// ITM global (equipped) effects: Target is always the wearer, this field isn’t relevant.
				SET target = TARGET_FX_self

				LPF ~get_effect_description~ RET effectDescription = description sort END
				PATCH_IF NOT ~%effectDescription%~ STRING_EQUAL ~~ BEGIN
					SET $lines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 1
					SET countLines += 1
				END
		    END
	    END
	END

	//TODO: Ne garder que les effets uniques  : ATTENTION ! Un effet est unique si la chaîne est la même ET que sa probabilité l'est aussi
    //LPF ~get_unique_equipped_abilities~ STR_VAR array_name = "lines" RET count RET_ARRAY lines = newAbilities END

	PATCH_IF (flags BAND BIT4) != 0 BEGIN
		SET countLines += 1
		SPRINT effectDescription @102126 // ~Maudit : Ne peut être ôté qu'à l'aide d'un sort de Délivrance de la malédiction~
		SET $lines(~0~ ~0~ ~100~ ~0~ ~99~ ~%effectDescription%~) = 1
	END

	PATCH_IF itemType == ITM_TYPE_helm BEGIN
		PATCH_IF ((flags BAND BIT25) == 0 AND itemType == ITM_TYPE_helm) OR ((flags BAND BIT25) == BIT25 AND itemType != ITM_TYPE_helm) BEGIN
			SET countLines += 1
			SPRINT effectDescription @102679 // ~Protection contre les coups critiques~
			SET $lines(~0~ ~0~ ~100~ ~0~ ~99~ ~%effectDescription%~) = 1
		END
	END

	SPRINT title @100010 // ~Capacités d'équipement~
	LPF ~add_section_to_description~ INT_VAR count = countLines STR_VAR title arrayName = ~lines~ RET description END
END

