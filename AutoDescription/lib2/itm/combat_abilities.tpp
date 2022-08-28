/*
 * Règles pour la génération de cette section
 * - Si le premier header est de type "projectile"
 *   - Ajout la chaîne "Ne nécessite pas de munition" ou "Revient dans la main du lanceur" (selon le type d'arme)
 *   - Ignorer les autres headers de type "projectile" et "launcher"
 * - Si le premier header est de type "launcher"
 *   - Ignorer les autres headers de type "projectile" et "launcher"
 * - Les headers de type "melee" sont toujours pris en compte
 * - Si les effets des sections restantes sont tous les mêmes, les regrouper en une seule section "Capacités de combat"
 */
DEFINE_PATCH_FUNCTION ~add_combat_abilities~
	STR_VAR
		description = ~~
	RET
		description
BEGIN
    READ_LONG ITM_flags flags

	SET abilityType = AbilityType_Combat
	SET countHeaders = 0
	SET hasProjectile = 0
	SET hasLauncher = 0
	SET selectedHeader = 0
	SET headerIndex = 0

	GET_OFFSET_ARRAY headerOffsets ITM_V10_HEADERS
	PHP_EACH headerOffsets AS _ => headerOffset BEGIN
		READ_BYTE  (headerOffset + ITM_HEAD_attack_type) attackType
		READ_BYTE  (headerOffset + ITM_HEAD_location) location
		READ_SHORT (headerOffset + ITM_HEAD_charges) charges

		PATCH_IF charges == 0
			AND NOT (attackType == ITM_ATTACK_TYPE_projectile AND (hasProjectile == 1 OR hasLauncher == 1))
			AND NOT (attackType == ITM_ATTACK_TYPE_launcher AND (hasLauncher == 1 OR hasProjectile == 1))
		BEGIN
			PATCH_IF attackType == ITM_ATTACK_TYPE_projectile BEGIN
				SET hasProjectile = 1
			END
			ELSE PATCH_IF attackType == ITM_ATTACK_TYPE_launcher BEGIN
				SET hasLauncher = 1
			END

			LPF ~load_combat_abilities~ INT_VAR headerOffset RET EVAL ~countLines%countHeaders%~ = countLines RET_ARRAY EVAL ~lines%countHeaders%~ = lines END
			SET $EVAL ~headers%countHeaders%~(~%attackType%~ ~%location%~ ~%headerIndex%~) = 1

			SET countHeaders += 1
		END
		SET headerIndex += 1
	END

	LPF ~has_same_combat_abilities~ INT_VAR countHeaders RET hasSame END

	// Ajout de l'effet spécifique si l'arme a un header projectile
	FOR (index = 0; index < countHeaders; index += 1) BEGIN
		PATCH_PHP_EACH ~headers%index%~ AS data => _ BEGIN
			SET attackType = ~%data_0%~

			PATCH_IF attackType == ITM_ATTACK_TYPE_projectile BEGIN
				PATCH_IF itemType == ITM_TYPE_bow OR itemType == ITM_TYPE_sling OR itemType == ITM_TYPE_crossbow BEGIN
					SPRINT effectDescription @102270 // ~Ne nécessite pas de munitions~
				END
				ELSE BEGIN
					SPRINT effectDescription @102269 // ~Revient dans la main du lanceur~
				END

				SET $EVAL ~lines%index%~(~0~ ~0~ ~100~ ~0~ ~99~ ~%effectDescription%~) = 1
				SET ~countLines%index%~ += 1
			END
		END
		SORT_ARRAY_INDICES ~lines%index%~ NUMERICALLY

		PATCH_IF ~countLines%index%~ > ~countLines%selectedHeader%~ BEGIN
			SET selectedHeader = index
		END
	END

	PATCH_IF (countHeaders > 0 AND hasSame == 1) OR countHeaders == 1 BEGIN
		SPRINT title @100011 // ~Capacités de combat~
		LPF ~add_section_to_description~ INT_VAR count = ~countLines%selectedHeader%~ STR_VAR title arrayName = ~lines%selectedHeader%~ RET description END
	END
	ELSE BEGIN
		FOR (index = 0; index < countHeaders; index += 1) BEGIN
			PATCH_PHP_EACH ~headers%index%~ AS data => _ BEGIN
				SET attackType = ~%data_0%~
				SET location = ~%data_1%~
				SET headerIndex = ~%data_2%~

				LPF ~get_combat_section_title~ INT_VAR headerIndex attackType location RET title END
				LPF ~add_section_to_description~ INT_VAR count = ~countLines%index%~ STR_VAR title arrayName = ~lines%index%~ RET description END
			END
		END
	END
END


DEFINE_PATCH_FUNCTION ~load_combat_abilities~
	INT_VAR
		headerOffset = 0
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

	LPM ~load_extended_effects~
	LPM ~replace_effects~
	LPM ~filter_effects~
	LPM ~group_effects~

	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
		    PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		        LPM ~data_to_vars~

				LPF ~get_effect_description~ RET effectDescription = description sort END
				PATCH_IF NOT ~%effectDescription%~ STRING_EQUAL ~~ BEGIN
					SET $lines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 1
					SET countLines += 1
				END
		    END
	    END
	END

	//TODO: Supprimer les lignes en doublon
	//      ATTENTION ! Un effet est unique si la chaîne est la même ET que sa probabilité l'est aussi
	//      ATTENTION ! Certains effets peuvent être en doublon ! 2 effets qui ajoutent un bonus de caractéristique peuvent se cumuler...
END


DEFINE_PATCH_FUNCTION ~has_same_combat_abilities~
	INT_VAR
		countHeaders = 0
	RET
		hasSame
BEGIN
	SET hasSame = 1

	PATCH_IF countHeaders > 1 BEGIN
		PATCH_PHP_EACH ~lines0~ AS base => _ BEGIN
			FOR (index = 1; index < countHeaders; index += 1) BEGIN
				PATCH_IF EVAL ~countLines%index%~ > 0 BEGIN
	                PATCH_PHP_EACH ~lines%index%~ AS data => _ BEGIN
						PATCH_IF NOT ~%base_5%~ STRING_EQUAL ~%data_5%~ BEGIN
	                        SET hasSame = 0
	                        SET index = countHeaders
						END
	                END
				END
			END
		END
	END
END


DEFINE_PATCH_FUNCTION ~get_combat_section_title~
	INT_VAR
		headerIndex = 0
		attackType = 0
		location = 0
	RET
		title
BEGIN
	SPRINT title @100011 // ~Capacités de combat~

	LPF ~get_tooltip~ INT_VAR index = headerIndex STR_VAR resource = ~%SOURCE_RES%~ RET sectionType = tooltip END

	PATCH_IF ~%sectionType%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF location == 1 BEGIN
			PATCH_IF attackType == ITM_ATTACK_TYPE_melee BEGIN
				SPRINT sectionType @100013 // ~au corps à corps~
			END
			ELSE PATCH_IF attackType == ITM_ATTACK_TYPE_projectile OR attackType == ITM_ATTACK_TYPE_launcher BEGIN
				SPRINT sectionType @100014 // ~à distance~
			END
		END
	END

	PATCH_IF NOT ~%sectionType%~ STRING_EQUAL ~~ BEGIN
		SPRINT title ~%title% (%sectionType%)~
	END
END
