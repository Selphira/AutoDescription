/* ================================================================= *
 * Gestion de la section "Capacités d'équipement" de la description. *
 * ================================================================= */
DEFINE_PATCH_FUNCTION ~add_equipped_abilities~
	STR_VAR
		description = ~~
	RET
		description
BEGIN
    READ_LONG ITM_flags flags

	SET abilityType = AbilityType_Equipped

	LPF ~load_equipped_abilities~ RET countLines RET_ARRAY lines END

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


DEFINE_PATCH_FUNCTION ~load_equipped_abilities~
	RET
		countLines
	RET_ARRAY
		lines
BEGIN
	SET countLines = 0

	CLEAR_ARRAY lines
	CLEAR_ARRAY opcodes

    PATCH_DEFINE_ASSOCIATIVE_ARRAY lines BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY opcodes BEGIN END

	LPM ~load_feature_effects~
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

	LPF ~get_unique_effects~ RET countLines = count RET_ARRAY lines = effects END
END

/* --------------------------------------------------------------------------------------------------------- *
 * Groupement des résistances aux dégâts, uniquement si les toutes les résistances d'un groupe sont          *
 * présentes ET ont la même valeur.                                                                          *
 * --------------------------------------------------------------------------------------------------------- *
 * - Résistance aux dégâts tranchants : +5 %                                                                 *
 * - Résistance aux dégâts contondants : +5 %                                                                *
 * - Résistance aux dégâts perforants : +5 %                                                                 *
 * - Résistance aux dégâts de projectiles : +5 %                                                             *
 * Devient                                                                                                   *
 * - Résistance aux dégâts physiques : +5 %                                                                  *
 * --------------------------------------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~shrink_resistances~ RET description BEGIN
	PATCH_IF shrink_resistances BEGIN
		// Contient les différentes valeurs trouvées des résistances
		// Pour chaque valeur, un tableau du même nom est créé dynamiquement, contenant la liste de toutes les résistances ayant cette même valeur
		PATCH_DEFINE_ARRAY ~groups~ BEGIN 102227 102225 102226 END
		PATCH_DEFINE_ARRAY ~g102227~ BEGIN // ~Résistance aux dégâts~
			10300001 10280001 10290001 10270001 10310001 10840001 10850001 10860001 10870001 10880001 10890001
		END
		PATCH_DEFINE_ARRAY ~g102225~ BEGIN // ~Résistance aux dégâts physiques~
			10860001 10870001 10880001 10890001
		END
		PATCH_DEFINE_ARRAY ~g102226~ BEGIN // ~Résistance aux dégâts élémentaires~
			10300001 10280001 10290001 10270001
		END

		LPF ~shrink_find_values~ STR_VAR group = ~g102227~ RET_ARRAY values matches END

		PATCH_PHP_EACH ~groups~ AS _ => group BEGIN
			LPF ~shrink_replace_values~ INT_VAR strref = EVAL ~%group%~ STR_VAR description group = EVAL ~g%group%~ RET description END
		END
	END
END

/* --------------------------------------------------------------------------------------------------------- *
 * Groupement des caractéristiques du personnage                                                             *
 * --------------------------------------------------------------------------------------------------------- *
 * - Force : +3                                                                                              *
 * - Dextérité : +3                                                                                          *
 * - Constitution : +3                                                                                       *
 * - Intelligence : +3                                                                                       *
 * - Sagesse : +3                                                                                            *
 * - Charisme : +3                                                                                           *
 * Devient                                                                                                   *
 * - Caractéristiques : +3                                                                                   *
 * --------------------------------------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~shrink_abilities~ RET description BEGIN
	PATCH_IF shrink_abilities BEGIN
		PATCH_DEFINE_ARRAY ~group~ BEGIN // ~Résistance aux dégâts~
			10440001 10150001 10100001 10190001 10490001 10060001
		END

		LPF ~shrink_find_values~ STR_VAR group RET_ARRAY values matches END
		LPF ~shrink_replace_values~ INT_VAR strref = 102228 STR_VAR description group RET description END // ~Caractéristiques~
	END
END

/* --------------------------------------------------------------------------------------------------------- *
 * Groupement des compétences de voleur du personnage.                                                       *
 * --------------------------------------------------------------------------------------------------------- *
 * - Vol à la tire : +15 %                                                                                   *
 * - Crochetage de serrures : +15 %                                                                          *
 * - Détection des illusions : +15 %                                                                         *
 * - Détection/désamorçage des pièges : +15 %                                                                *
 * - Pose de pièges : +15 %                                                                                  *
 * - Camouflage dans l'ombre : +15 %                                                                         *
 * - Furtivité : +15 %                                                                                       *
 * Devient                                                                                                   *
 * - Compétences de voleur : +3                                                                                   *
 * --------------------------------------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~shrink_thief_skills~ RET description BEGIN
	PATCH_IF shrink_thief_skills BEGIN
		PATCH_DEFINE_ARRAY ~group~ BEGIN // ~Résistance aux dégâts~
			10920001 10900001 12760001 10910001 12770001 12750001 10590001
		END

		LPF ~shrink_find_values~ STR_VAR group RET_ARRAY values matches END
		LPF ~shrink_replace_values~ INT_VAR strref = 102229 STR_VAR description group RET description END // ~Compétences de voleur~
	END
END

DEFINE_PATCH_FUNCTION ~shrink_find_values~
	STR_VAR
		group = ~~
	RET_ARRAY
		values
		matches
BEGIN
	SET indexValues = 0
	PATCH_DEFINE_ARRAY ~values~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~matches~ BEGIN END

	PATCH_PHP_EACH ~%group%~ AS _ => strref BEGIN
		SPRINT name (AT ~%strref%~)
		SPRINT value ~\(.*\)\(%crlf%\)*~
		SPRINT regex @100001 // ~%name%%colon%%value%~
		SPRINT regex ~- %regex%~
		INNER_PATCH ~%description%~ BEGIN
            REPLACE_EVALUATE CASE_INSENSITIVE ~%regex%~ BEGIN
		        PATCH_IF NOT VARIABLE_IS_SET $matches(~%MATCH1%~ ~0~) BEGIN
		            SPRINT $values(~%indexValues%~) ~%MATCH1%~
			        SET indexValues += 1
					PATCH_DEFINE_ARRAY EVAL ~%MATCH1%~ BEGIN END
					SET EVAL ~index%MATCH1%~ = 0
		        END
		        SET idxMatch = EVAL ~index%MATCH1%~
			    SPRINT $matches(~%MATCH1%~ ~%idxMatch%~) ~%strref%~
			    SET EVAL ~index%MATCH1%~ += 1
		    END ~%MATCH1%~
		END
    END
END


DEFINE_PATCH_FUNCTION ~shrink_replace_values~
	INT_VAR
		strref = 0
	STR_VAR
		description = ~~
		group = ~~
	RET
		description
BEGIN
	PATCH_PHP_EACH values AS _ => match BEGIN
		SET allFound = 1
		PATCH_PHP_EACH ~%group%~ AS _ => resistance BEGIN
			SET found = 0
			PATCH_IF allFound == 1 BEGIN
				PATCH_PHP_EACH ~matches~ AS data => value BEGIN
					PATCH_IF ~%data_0%~ STRING_EQUAL ~%match%~ AND value == resistance BEGIN
						SET found = 1
					END
				END
				PATCH_IF found == 0 BEGIN
					SET allFound = 0
				END
			END
		END
		//FIXME: Possible problème si un même effet est présent 2 fois avec la même valeur
		//FIXME: Possible problème si un effet est présent 2 fois, empêchant la regex de bien fonctionner
		PATCH_IF allFound == 1 BEGIN
			SPRINT regexTemplate ~~
			PATCH_PHP_EACH ~%group%~ AS _ => groupStrref BEGIN
				SPRINT name (AT ~%groupStrref%~)
				SPRINT value ~value~
				SPRINT value ~\%%value%%~
				SPRINT name @100001 // ~%name%%colon%%value%~
		        SPRINT regexTemplate ~%regexTemplate%%crlf%- %name%~
			END
	        SPRINT value ~%match%~
	        SPRINT name (AT ~%strref%~)
			SPRINT replace @100001 // %name%%colon%%value%~
	        SPRINT regex EVAL ~%regexTemplate%~
			INNER_PATCH_SAVE description ~%description%~ BEGIN
				REPLACE_TEXTUALLY CASE_INSENSITIVE ~%regex%~ ~%crlf%- %replace%~
			END
		END
	END
END