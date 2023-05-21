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
	SPRINT specialProjectileAbility ~~

	GET_OFFSET_ARRAY headerOffsets ITM_V10_HEADERS
	PHP_EACH headerOffsets AS _ => headerOffset BEGIN
		READ_BYTE  (headerOffset + ITM_HEAD_attack_type) attackType
		READ_BYTE  (headerOffset + ITM_HEAD_location) location
		READ_SHORT (headerOffset + ITM_HEAD_charges) charges
		READ_SHORT (headerOffset + ITM_HEAD_flags) flags

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
			SET $EVAL ~headers%countHeaders%~(~%attackType%~ ~%location%~ ~%headerIndex%~ ~%charges%~ ~%flags%~) = 1

			SET countHeaders += 1
		END
		// Les cas où on a une capacité de charge qui diminue à chaque attaque (Ex: BG2 => STAF05)
		ELSE PATCH_IF attackType == ITM_ATTACK_TYPE_projectile OR attackType == ITM_ATTACK_TYPE_launcher OR attackType == ITM_ATTACK_TYPE_melee BEGIN
			PATCH_DEFINE_ARRAY EVAL ~lines%countHeaders%~ BEGIN END
			SET EVAL ~countLines%countHeaders%~ = 0
			LPF ~load_weapon_attributes~ INT_VAR headerOffset RET_ARRAY EVAL ~weaponAttributes%countHeaders%~ = attributes END
			SET $EVAL ~headers%countHeaders%~(~%attackType%~ ~%location%~ ~%headerIndex%~ ~%charges%~ ~%flags%~) = 1
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
				PATCH_IF isAmmo BEGIN
					SPRINT specialProjectileAbility @102271 // ~Munition à usage illimité~
				END
				ELSE PATCH_IF itemType == ITM_TYPE_bow OR itemType == ITM_TYPE_sling OR itemType == ITM_TYPE_crossbow BEGIN
					SPRINT specialProjectileAbility @102270 // ~Ne nécessite pas de munitions~
				END
				ELSE BEGIN
					SPRINT specialProjectileAbility @102269 // ~Revient dans la main du lanceur~
				END

				SET $EVAL ~lines%index%~(~0~ ~0~ ~100~ ~0~ ~99~ ~%specialProjectileAbility%~) = 1
				SET ~countLines%index%~ += 1
			END
		END
		SORT_ARRAY_INDICES ~lines%index%~ NUMERICALLY

		PATCH_IF ~countLines%index%~ > ~countLines%selectedHeader%~ BEGIN
			SET selectedHeader = index
		END
	END

	// Ajoute la ligne indiquant si l'arme utilise ou non le bonus de force
	// - Arcs et arbalètes : On affiche s'ils utilisent le bonus de force
    // - Autres armes: On affiche s'ils n'utilisent pas le bonus de force
    // Cas d'une cape et d'un anneau avec des capacités de combat à ne pas prendre en compte ici
    // TODO: Pour le moment, on évite les armes qui peuvent être utilisées en mêlée et à distance, cela génère des
    //       des lignes faisant croire que le bonus n'est pas actif quelle que soit la façon d'utliser l'arme.
    PATCH_IF isWeapon AND countHeaders == 1 BEGIN
		FOR (index = 0; index < countHeaders; index += 1) BEGIN
			PATCH_PHP_EACH ~headers%index%~ AS data => _ BEGIN
				SET flags = ~%data_4%~
				SET useStrengthBonus = (flags BAND BIT0) > 0
				SET useEEStrengthBonus = (flags BAND BIT2) > 0
				SET useEETac0Bonus = (flags BAND BIT3) > 0
				SPRINT effectDescription ~~

				PATCH_IF itemType == ITM_TYPE_bow OR itemType == ITM_TYPE_sling OR itemType == ITM_TYPE_crossbow BEGIN
					PATCH_IF useStrengthBonus OR (is_ee AND useEEStrengthBonus AND useEETac0Bonus) BEGIN
						SPRINT effectDescription @102263 // ~Les bonus aux jets de toucher et aux dégâts en fonction de la force s'appliquent à cette arme~
					END
					ELSE PATCH_IF NOT useStrengthBonus AND useStrengthBonus BEGIN
						SPRINT effectDescription @102264 // ~Les bonus aux dégâts en fonction de la force s'appliquent à cette arme~
					END
					ELSE PATCH_IF NOT useStrengthBonus AND useEETac0Bonus BEGIN
						SPRINT effectDescription @102265 // ~Les bonus aux jets de toucher en fonction de la force s'appliquent à cette arme~
					END
				END
				ELSE PATCH_IF NOT useStrengthBonus AND NOT useEEStrengthBonus AND NOT useEETac0Bonus BEGIN
					SPRINT effectDescription @102266 // ~Les bonus aux jets de toucher et aux dégâts en fonction de la force ne s'appliquent pas à cette arme~
				END
				ELSE PATCH_IF NOT useStrengthBonus AND NOT useStrengthBonus BEGIN
					SPRINT effectDescription @102267 // ~Les bonus aux jets de toucher en fonction de la force ne s'appliquent pas à cette arme~
				END
				ELSE PATCH_IF NOT useStrengthBonus AND NOT useEETac0Bonus BEGIN
					SPRINT effectDescription @102268 // ~Les bonus aux dégâts en fonction de la force ne s'appliquent pas à cette arme~
				END

				PATCH_IF NOT ~%effectDescription%~ STRING_EQUAL ~~ BEGIN
					SET $EVAL ~lines%index%~(~0~ ~0~ ~100~ ~0~ ~99~ ~%effectDescription%~) = 1
					SET ~countLines%index%~ += 1
				END
			END
		END
	END

	PATCH_IF countHeaders == 1 OR (countHeaders > 0 AND hasSameAbilities == 1 AND hasSameAttributes == 1) BEGIN
		PATCH_IF NOT ~%specialProjectileAbility%~ STRING_EQUAL ~~ BEGIN
			SET $EVAL ~lines%selectedHeader%~(~0~ ~0~ ~100~ ~0~ ~99~ ~%specialProjectileAbility%~) = 1
			SET ~countLines%selectedHeader%~ += 1
		END
		SPRINT title @100011 // ~Capacités de combat~
		LPF ~add_section_to_description~ INT_VAR count = ~countLines%selectedHeader%~ STR_VAR title arrayName = ~lines%selectedHeader%~ RET description END
	END
	ELSE PATCH_IF (hasSameAbilities == 0 AND hasSameAttributes == 1) OR (hasSameAbilities == 0 AND hasSameAttributes == 0) OR (hasSameAbilities == 1 AND hasSameAttributes == 0) BEGIN
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

	PATCH_IF isWeapon == 1 OR isAmmo == 1 BEGIN
		LPF ~add_weapon_attributes_to_description~ RET description END
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
	LPF ~group_probability_effects~ RET countLines = count RET_ARRAY lines = effects END
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
		READ_BYTE  (headerOffset + ITM_HEAD_projectile_type) projectileType
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

        SET $attributes(~%tac0%~ ~%damage%~ ~%damageType%~ ~%speedFactor%~ ~%range%~ ~%enchantment%~ ~%flags%~ ~%isRanged%~ ~%projectileType%~) = 1
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
	RET
		description
BEGIN
	FOR (index = 0; index < countHeaders; index += 1) BEGIN
		PATCH_PHP_EACH ~weaponAttributes%index%~ AS data => value BEGIN
	        SPRINT damage ~%data_1%~
	        SET tac0           = ~%data_0%~
	        SET damageType     = ~%data_2%~
	        SET speedFactor    = ~%data_3%~
	        SET range          = ~%data_4%~
	        SET enchantment    = ~%data_5%~
	        SET flags          = ~%data_6%~
	        SET isRanged       = ~%data_7%~
	        SET projectileType = ~%data_8%~

	        SET $enchantments(~enchantments%enchantment%~) = enchantment
	        SET $EVAL ~enchantments%enchantment%~(~%index%~) = 0
	        SET $tac0s(~tac0s%tac0%~) = tac0
	        SET $EVAL ~tac0s%tac0%~(~%index%~) = 0
	        PATCH_IF ~%damage%~ STRING_EQUAL ~~ BEGIN
				SPRINT $damages(~damages0~) ~%damage%~
				SPRINT $EVAL ~damages0~(~%index%~) ~~
	        END
			ELSE BEGIN
				SPRINT $damages(~damages%damage%~) ~%damage%~
				SPRINT $EVAL ~damages%damage%~(~%index%~) ~~
			END
	        SET $damageTypes(~damageTypes%damageType%~) = damageType
	        SET $EVAL ~damageTypes%damageType%~(~%index%~) = 0
	        SET $speedFactors(~speedFactors%speedFactor%~) = speedFactor
	        SET $EVAL ~speedFactors%speedFactor%~(~%index%~) = 0
	        SET $isRangeds(~isRangeds%isRanged%~) = isRanged
	        SET $EVAL ~isRangeds%isRanged%~(~%index%~) = 0
	        SET $projectileTypes(~projectileTypes%projectileType%~) = projectileType
	        SET $EVAL ~projectileTypes%projectileType%~(~%index%~) = 0
        END
    END

	SPRINT damageNone @10015 // ~Aucun~

    LPF ~appendLine~ RET description END

	// Enchantement
	LPF ~array_count~ STR_VAR array_name = ~enchantments~ RET count END
	PATCH_PHP_EACH ~enchantments~ AS array_name => value BEGIN
	    PATCH_IF ~%value%~ != 0 BEGIN
	        LPF ~get_combat_attribute_name~ INT_VAR strref = 13440001 count STR_VAR array_name RET name END
			LPF ~signed_value~ INT_VAR value RET value END
			LPF ~appendValue~ STR_VAR name value RET description END // ~TAC0~
		END
	END

	// TAC0
	LPF ~array_count~ STR_VAR array_name = ~tac0s~ RET count END
	PATCH_PHP_EACH ~tac0s~ AS array_name => value BEGIN
	    PATCH_IF ~%value%~ != 0 BEGIN
	        LPF ~get_combat_attribute_name~ INT_VAR strref = 10540001 count STR_VAR array_name RET name END
			LPF ~signed_value~ INT_VAR value RET value END
			LPF ~appendValue~ STR_VAR name value RET description END // ~TAC0~
		END
	END

	// Dégâts
	LPF ~array_count~ STR_VAR array_name = ~damages~ RET count END
	LPF ~array_count~ STR_VAR array_name = ~damageTypes~ RET damageTypeCount = count END
	PATCH_PHP_EACH ~damages~ AS array_name => value BEGIN
	    PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ AND NOT ~%value%~ STRING_EQUAL ~%damageNone%~ BEGIN
	        PATCH_IF damageTypeCount == 1 BEGIN
				PATCH_PHP_EACH ~damageTypes~ AS array_damageTypes => damageType BEGIN
					SET strref = 102010 + damageType
					SPRINT string_value (AT ~%strref%~)
	                SPRINT value ~%value% (%string_value%)~
				END
	        END
	        LPF ~get_combat_attribute_name~ INT_VAR strref = 10730001 count STR_VAR array_name RET name END // ~Dégâts~
			LPF ~appendValue~ STR_VAR name value RET description END
		END
	END

	LPF ~array_count~ STR_VAR array_name = ~damageTypes~ RET count END
	PATCH_IF count > 1 BEGIN
		PATCH_PHP_EACH ~damageTypes~ AS array_name => value BEGIN
			SET found = 0
			PATCH_PHP_EACH ~%array_name%~ AS index => _ BEGIN
				PATCH_PHP_EACH ~damages~ AS array_damages => damage BEGIN
					PATCH_PHP_EACH ~%array_damages%~ AS index_damage => _ BEGIN
						PATCH_IF found == 0 BEGIN
							PATCH_IF NOT ~%damage%~ STRING_EQUAL ~%damageNone%~ BEGIN
								PATCH_IF index == index_damage BEGIN
									SET strref = 102010 + value
									SPRINT string_value (AT ~%strref%~)
									LPF ~get_combat_attribute_name~ INT_VAR strref = 102005 count STR_VAR array_name RET name END // ~Type de dégâts~
									LPF ~appendValue~ STR_VAR name value = ~%string_value%~ RET description END
									SET found = 1
								END
							END
						END
					END
				END
			END
		END
	END

	// Facteur de vitesse
	PATCH_IF NOT isAmmo BEGIN
		LPF ~array_count~ STR_VAR array_name = ~speedFactors~ RET count END
		PATCH_PHP_EACH ~speedFactors~ AS array_name => value BEGIN
			LPF ~get_combat_attribute_name~ INT_VAR strref = 11900001 count STR_VAR array_name RET name END // ~Facteur de vitesse~
			LPF ~appendValue~ STR_VAR name value RET description END
		END
	END
	// Arme de jet
	ELSE BEGIN
		PATCH_PHP_EACH ~projectileTypes~ AS array_name => value BEGIN
			SET strref = 101078 + value
			SPRINT value (AT ~%strref%~)
			LPF ~get_combat_attribute_name~ INT_VAR strref = 101082 count STR_VAR array_name RET name END // ~Arme de jet~
			LPF ~appendValue~ STR_VAR name value RET description END
		END
	END

	// TODO: Ou si la portée d'une arme de mêlée est différente de sa portée par défaut
	//PATCH_IF isRanged == 1 BEGIN
	//	LPF ~appendValue~ INT_VAR strref = 102006 STR_VAR value = ~%range%~ RET description END // ~Portée~
	//END
END


DEFINE_PATCH_FUNCTION ~get_combat_attribute_name~
	INT_VAR
		strref = 0
		count = 0
	STR_VAR
		array_name = ~~
	RET
		name
BEGIN
	SPRINT name (AT strref)
	SPRINT and @100021 // ~et~

	PATCH_IF count > 1 BEGIN
		PATCH_DEFINE_ARRAY ~sectionTypes~ BEGIN END
		PATCH_PHP_EACH ~%array_name%~ AS index => _ BEGIN
			PATCH_PHP_EACH ~headers%index%~ AS headerData => _ BEGIN
				SET attackType = ~%headerData_0%~
				SET location = ~%headerData_1%~
                SET headerIndex = ~%headerData_2%~
                LPF ~get_combat_section_type~ INT_VAR headerIndex attackType location RET sectionType END
                SET $sectionTypes(~%sectionType%~) = 0
            END
		END
		LPF ~implode~ STR_VAR array_name = ~sectionTypes~ glue = ~, ~ final_glue = ~ %and% ~ RET sectionType = text END
        SPRINT name ~%name% (%sectionType%)~
	END
END
