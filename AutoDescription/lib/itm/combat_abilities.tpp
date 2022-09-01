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

			LPF ~load_weapon_attributes~ INT_VAR headerOffset RET_ARRAY EVAL ~weaponAttributes%countHeaders%~ = attributes END
			LPF ~load_combat_abilities~ INT_VAR headerOffset RET EVAL ~countLines%countHeaders%~ = countLines RET_ARRAY EVAL ~lines%countHeaders%~ = lines END
			SET $EVAL ~headers%countHeaders%~(~%attackType%~ ~%location%~ ~%headerIndex%~ ~%charges%~) = 1

			SET countHeaders += 1
		END
		// Les cas où on a une capacité de charge qui diminue à chaque attaque (Ex: BG2 => STAF05)
		ELSE PATCH_IF attackType == ITM_ATTACK_TYPE_projectile OR attackType == ITM_ATTACK_TYPE_launcher OR attackType == ITM_ATTACK_TYPE_melee BEGIN
			PATCH_DEFINE_ARRAY EVAL ~lines%countHeaders%~ BEGIN END
			SET EVAL ~countLines%countHeaders%~ = 0
			LPF ~load_weapon_attributes~ INT_VAR headerOffset RET_ARRAY EVAL ~weaponAttributes%countHeaders%~ = attributes END
			SET $EVAL ~headers%countHeaders%~(~%attackType%~ ~%location%~ ~%headerIndex%~ ~%charges%~) = 1
			SET countHeaders += 1
		END

		SET headerIndex += 1
	END

	LPF ~has_same_combat_abilities~ INT_VAR countHeaders RET hasSameAbilities END
	LPF ~has_same_weapon_attributes~ RET hasSameAttributes END

	// Ajout de l'effet spécifique si l'arme a un header projectile
	FOR (index = 0; index < countHeaders; index += 1) BEGIN
		PATCH_PHP_EACH ~headers%index%~ AS data => _ BEGIN
			SET attackType = ~%data_0%~
			SET charges = ~%data_3%~

			PATCH_IF attackType == ITM_ATTACK_TYPE_projectile AND charges == 0 BEGIN
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

	PATCH_IF countHeaders == 1 OR (countHeaders > 0 AND hasSameAbilities == 1 AND hasSameAttributes == 1) BEGIN
		SPRINT title @100011 // ~Capacités de combat~
		LPF ~add_section_to_description~ INT_VAR count = ~countLines%selectedHeader%~ STR_VAR title arrayName = ~lines%selectedHeader%~ RET description END
		LPF ~add_weapon_attributes_to_description~ INT_VAR index = 0 group = countHeaders != 1 RET description END
	END
	ELSE PATCH_IF hasSameAbilities == 0 AND hasSameAttributes == 1 BEGIN
		FOR (index = 0; index < countHeaders; index += 1) BEGIN
			PATCH_PHP_EACH ~headers%index%~ AS data => _ BEGIN
				SET attackType = ~%data_0%~
				SET location = ~%data_1%~
				SET headerIndex = ~%data_2%~
				LPF ~get_combat_section_title~ INT_VAR headerIndex attackType location RET title END
				LPF ~add_section_to_description~ INT_VAR count = ~countLines%index%~ STR_VAR title arrayName = ~lines%index%~ RET description END
			END
		END
		LPF ~add_weapon_attributes_to_description~ INT_VAR index = selectedHeader group = 1 RET description END
	END
	ELSE PATCH_IF( hasSameAbilities == 0 AND hasSameAttributes == 0) OR (hasSameAbilities == 1 AND hasSameAttributes == 0) BEGIN
		FOR (index = 0; index < countHeaders; index += 1) BEGIN
			PATCH_PHP_EACH ~headers%index%~ AS data => _ BEGIN
				SET attackType = ~%data_0%~
				SET location = ~%data_1%~
				SET headerIndex = ~%data_2%~
				LPF ~get_combat_section_title~ INT_VAR headerIndex attackType location RET title END
				LPF ~add_section_to_description~ INT_VAR count = ~countLines%index%~ STR_VAR title arrayName = ~lines%index%~ RET description END
				LPF ~add_weapon_attributes_to_description~ INT_VAR index = index RET description END
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

	LPF ~get_unique_effects~ RET countLines = count RET_ARRAY lines = effects END
END


DEFINE_PATCH_FUNCTION ~load_weapon_attributes~
	INT_VAR
		headerOffset = 0
	RET_ARRAY
		attributes
BEGIN
	READ_BYTE  (headerOffset + ITM_HEAD_attack_type) attackType

	CLEAR_ARRAY attributes

    PATCH_DEFINE_ASSOCIATIVE_ARRAY attributes BEGIN END

	PATCH_IF attackType == ITM_ATTACK_TYPE_melee OR attackType == ITM_ATTACK_TYPE_projectile OR attackType == ITM_ATTACK_TYPE_launcher BEGIN
        READ_SHORT ITM_enchantment enchantment

		READ_BYTE  (headerOffset + ITM_HEAD_range) range
		READ_BYTE  (headerOffset + ITM_HEAD_speed) speedFactor
		READ_SHORT (headerOffset + ITM_HEAD_thac0_bonus) tac0
		READ_BYTE  (headerOffset + ITM_HEAD_dice_sides) diceSides
		READ_BYTE  (headerOffset + ITM_HEAD_dice_thrown) diceThrown
		READ_SHORT (headerOffset + ITM_HEAD_damage_bonus) damageBonus
		READ_SHORT (headerOffset + ITM_HEAD_damage_type) damageType
		READ_SHORT (headerOffset + ITM_HEAD_flags) flags

		SET isRanged = (attackType == ITM_ATTACK_TYPE_projectile OR attackType == ITM_ATTACK_TYPE_launcher)

		PATCH_IF damageBonus > 32768 BEGIN
			SET damageBonus = damageBonus - 65536
		END

		PATCH_IF tac0 > 32767 BEGIN
			SET tac0 -= 65536
		END

		// If Dice thrown, Dice size, and Damage bonus are all 0: Always deals zero damage (ignores all modifiers, like Weapon Proficiency).
		PATCH_IF diceThrown == 0 AND diceSides == 0 AND damageBonus == 0 BEGIN
			SPRINT damage @10015 // ~Aucun~
		END
		ELSE BEGIN
			LPF ~get_damage_value~ INT_VAR diceCount = diceThrown diceSides damageAmount = damageBonus RET damage END
		END

        SET $attributes(~%tac0%~ ~%damage%~ ~%damageType%~ ~%speedFactor%~ ~%range%~ ~%enchantment%~ ~%flags%~ ~%isRanged%~) = 1
	END
END

DEFINE_PATCH_FUNCTION ~has_same_combat_abilities~
	INT_VAR
		countHeaders = 0
	RET
		hasSameAbilities
BEGIN
	SET hasSameAbilities = 1

	PATCH_IF countHeaders > 1 BEGIN
		PATCH_PHP_EACH ~lines0~ AS base => _ BEGIN
			FOR (index = 1; index < countHeaders; index += 1) BEGIN
				PATCH_IF EVAL ~countLines%index%~ > 0 BEGIN
					PATCH_IF ~countLines0~ != ~countLines%index%~ BEGIN
	                    SET hasSameAbilities = 0
	                    SET index = countHeaders
					END
					ELSE BEGIN
						SET hasSameAbility = 0
		                PATCH_PHP_EACH ~lines%index%~ AS data => _ BEGIN
							PATCH_IF ~%base_5%~ STRING_EQUAL ~%data_5%~ BEGIN
		                        SET hasSameAbility = 1
							END
		                END
		                PATCH_IF hasSameAbility == 0 BEGIN
		                    SET hasSameAbilities = 0
		                    SET index = countHeaders
		                END
					END
				END
			END
		END
	END
END


DEFINE_PATCH_FUNCTION ~has_same_weapon_attributes~ RET hasSameAttributes BEGIN
	SET hasSameAttributes = 1
	// ~%tac0%~ ~%damage%~ ~%damageType%~ ~%speedFactor%~ ~%range%~ ~%enchantment%~ ~%flags%~ ~%isRanged%~
	PATCH_IF countHeaders > 1 BEGIN
		PATCH_PHP_EACH weaponAttributes0 AS base => _ BEGIN
			FOR (index = 1; index < countHeaders; index += 1) BEGIN
				PATCH_PHP_EACH ~weaponAttributes%index%~ AS data => _ BEGIN
					PATCH_IF ~%base_0%~ != ~%data_0%~             // tac0
					    OR NOT ~%base_1%~ STRING_EQUAL ~%data_1%~ // damage
					    OR ~%base_3%~ != ~%data_3%~ BEGIN         // speedFactor
						SET hasSameAttributes = 0
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

	LPF ~get_combat_section_type~ INT_VAR headerIndex attackType location RET sectionType END

	PATCH_IF NOT ~%sectionType%~ STRING_EQUAL ~~ BEGIN
		SPRINT title ~%title% (%sectionType%)~
	END
END


DEFINE_PATCH_FUNCTION ~get_combat_section_type~
	INT_VAR
		headerIndex = 0
		attackType = 0
		location = 0
	RET
		sectionType
BEGIN
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
END


DEFINE_PATCH_FUNCTION ~add_weapon_attributes_to_description~
	INT_VAR
		index = 0
		group = 0
	RET
		description
BEGIN
    PATCH_PHP_EACH ~weaponAttributes%index%~ AS data => value BEGIN
        SPRINT damage ~%data_1%~
        SET tac0        = ~%data_0%~
        SET damageType  = ~%data_2%~
        SET speedFactor = ~%data_3%~
        SET range       = ~%data_4%~
        SET enchantment = ~%data_5%~
        SET flags       = ~%data_6%~
        SET isRanged    = ~%data_7%~

        LPF ~appendLine~ RET description END

		PATCH_IF enchantment > 0 BEGIN
			LPF ~signed_value~ INT_VAR value = enchantment RET value END
			LPF ~appendValue~ INT_VAR strref = 13440001 STR_VAR value RET description END // ~Enchantement~
		END

	    PATCH_IF ~%tac0%~ != 0 BEGIN
			LPF ~signed_value~ INT_VAR value = tac0 RET value END
			LPF ~appendValue~ INT_VAR strref = 10540001 STR_VAR value RET description END // ~TAC0~
	    END

		PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
			LPF ~appendValue~ INT_VAR strref = 10730001 STR_VAR value = ~%damage%~ RET description END // ~Dégâts~
		END

		SPRINT damageNone @10015 // ~Aucun~

		PATCH_IF NOT ~%damage%~ STRING_EQUAL ~%damageNone%~ BEGIN
			PATCH_IF countHeaders == 1 OR group = 0 BEGIN
				SET strref = 102010 + damageType
		        SPRINT value (AT ~%strref%~)
				LPF ~appendValue~ INT_VAR strref = 102005 STR_VAR value RET description END // ~Type de dégâts~
			END
			ELSE BEGIN
				FOR (index2 = 0; index2 < countHeaders; index2 += 1) BEGIN
					PATCH_PHP_EACH ~weaponAttributes%index2%~ AS weaponData => _ BEGIN
	                    SET damageType  = ~%weaponData_2%~
						SET strref = 102010 + damageType
				        SPRINT value (AT ~%strref%~)

						PATCH_PHP_EACH ~headers%index2%~ AS headerData => _ BEGIN
							SET attackType = ~%headerData_0%~
							SET location = ~%headerData_1%~
	                        SET headerIndex = ~%headerData_2%~
	                        LPF ~get_combat_section_type~ INT_VAR headerIndex attackType location RET sectionType END
	                    END

	                    SPRINT value ~%value% (%sectionType%)~

						LPF ~appendValue~ INT_VAR strref = 102005 STR_VAR value RET description END // ~Type de dégâts~
					END
	            END
			END
		END

		LPF ~appendValue~ INT_VAR strref = 11900001 STR_VAR value = ~%speedFactor%~ RET description END // ~Facteur de vitesse~

		// TODO: Ou si la portée d'une arme de mêlée est différente de sa portée par défaut
		//PATCH_IF isRanged == 1 BEGIN
		//	LPF ~appendValue~ INT_VAR strref = 102006 STR_VAR value = ~%range%~ RET description END // ~Portée~
		//END
    END
END
