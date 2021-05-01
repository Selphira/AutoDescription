/* ====================================================================================== *
 * Gestion des sections "Capacités de charge" et "Capacités de combat" de la description. *
 * ====================================================================================== */

DEFINE_PATCH_FUNCTION ~extended_abilities~ RET description BEGIN
	READ_LONG  ITM_extended_headers_offset headerOffset
	READ_SHORT ITM_extended_headers_count  headerCount

	PATCH_IF headerCount > 0 BEGIN
		SET chargeCount = 0
		SET combatCount = 0

		PATCH_DEFINE_ARRAY chargeAbilities BEGIN END
		PATCH_DEFINE_ARRAY combat_abilities BEGIN END

	    FOR (headerIndex = 0; headerIndex < headerCount; headerIndex += 1) BEGIN
	        SET offset = headerOffset + 0x38 * headerIndex
			READ_ASCII (offset + ITM_HEAD_use_icon) icon
			READ_BYTE  (offset + ITM_HEAD_location) location
			READ_SHORT (offset + ITM_HEAD_charges) charges
			READ_SHORT (offset + ITM_HEAD_depletion) depletion

			PATCH_IF charges > 0 BEGIN
				LPM ~add_charge_abilitie~
				PATCH_IF isWeapon == 1 AND location == 1 BEGIN
					SET $combatAbilitiesCount(~%combatCount%~) = 0
					PATCH_DEFINE_ARRAY $combatAbilities(~%combatCount%~) BEGIN 0 ~%SOURCE_RES%~ END
					LPM ~add_weapon_statistics~
					SET combatCount += 1
				END
			END
			ELSE PATCH_IF location == 1 BEGIN
				SET $combatAbilitiesCount(~%combatCount%~) = 0
				PATCH_DEFINE_ARRAY $combatAbilities(~%combatCount%~) BEGIN 0 ~%SOURCE_RES%~ END

				PATCH_IF isWeapon == 1 BEGIN
					LPM ~add_combat_abilitie~
					LPM ~add_weapon_statistics~
				END
				ELSE BEGIN
					LPM ~add_combat_abilitie~
				END
				SET combatCount += 1
			END
			ELSE BEGIN
				PATCH_WARN ~%SOURCE_FILE% : extended_abilities : effet numero '%headerIndex%' pas encore gere~
			END
		END

		// Trier les tableau de capacités
		FOR (index = 0; index < combatCount; index += 1) BEGIN
			PATCH_IF $combatAbilities(~%index%~ 0) > 0 BEGIN
				PATCH_PHP_EACH ~combat_abilities_%index%~ AS k => v BEGIN
					PATCH_IF NOT IS_AN_INT ~%k_0%~ BEGIN
						PATCH_WARN ~WARNING: La valeur pour le tri n'est pas definie dans $sort_opcodes pour %k_0%~
					END
				END
				// Si WARNING : to be sorted numerically was not of the expcted form
				// C'est que la valeur pour le tri du opcode n'est pas présente dans le tableau $sort_opcodes
                SORT_ARRAY_INDICES ~combat_abilities_%index%~ NUMERICALLY
			END
        END

		PATCH_IF chargeCount > 0 BEGIN LPM ~add_charge_abilities_to_description~ END
		LPM ~add_combat_abilities_to_description~
	END
END

DEFINE_PATCH_MACRO ~add_charge_abilitie~ BEGIN
	LOCAL_SET chargeStrref = 0
	LOCAL_SET sort = ( headerIndex + 1 ) * 10000
	LOCAL_SET chargeAbilityCount = 0
	LOCAL_SPRINT chargeTitle ~~

	LPF ~get_strrefs_from_tooltip~ STR_VAR id = EVAL ~%SOURCE_RES%~ RET strref_0 strref_1 strref_2 END

	PATCH_IF headerIndex < 3 BEGIN // Max 3 tooltips par objet
		SPRINT chargeStrref EVAL ~%strref_%headerIndex%%~

		PATCH_IF EVAL ~%chargeStrref%~ > 0 BEGIN
			GET_STRREF chargeStrref chargeTitle
			// TODO: Pour chaque effet non ignoré, récupérer la durée et les jets de sauvegarde (C2STAF02 -> Invoquer tertre errant + Charme-animal)
			//       Si tous sont égaux, alors les utiliser
			//       Sinon ne rien faire

			SET abilitySort = sort + chargeCount
			SET $charge_abilities(~%abilitySort%~ ~%chargeAbilityCount%~ ~%chargeTitle%~) = 2
			SET chargeCount += 1
			SET chargeAbilityCount += 1
		END
		ELSE BEGIN
			GET_OFFSET_ARRAY2 blockOffsets offset ITM_V10_HEAD_EFFECTS
			PATCH_PHP_EACH blockOffsets AS int => blockOffset BEGIN
				READ_SHORT blockOffset opcode

				PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
					SET abilityType = AbilityType_Charge
					PATCH_IF opcode == 219 BEGIN
						SET opcodeBase = opcode
						PATCH_FOR_EACH subOpcode IN 0 1 BEGIN
							SET opcode = opcodeBase * 1000 + subOpcode
							LPF ~get_description_effect~ RET desc = description END
							PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
								SET abilitySort = sort + $sort_opcodes(~%opcode%~)
								SET $charge_abilities(~%abilitySort%~ ~%chargeAbilityCount%~ ~%desc%~) = 2
								SET chargeCount += 1
								SET chargeAbilityCount += 1
							END
						END
					END
					ELSE BEGIN
						LPF ~get_description_effect~ RET desc = description END
						PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
							SET abilitySort = sort + $sort_opcodes(~%opcode%~)
							SET $charge_abilities(~%abilitySort%~ ~%chargeAbilityCount%~ ~%desc%~) = 2
							SET chargeCount += 1
							SET chargeAbilityCount += 1
						END
					END
				END
			END
		END
	END

	PATCH_IF chargeAbilityCount == 1 /*AND ~%chargeTitle%~ STRING_EQUAL ~~*/ BEGIN
		PATCH_PHP_EACH charge_abilities AS data => v BEGIN
			PATCH_IF data_0 == abilitySort AND data_1 == 0 BEGIN
				SPRINT lowerChargeTitle ~%chargeTitle%~
				SPRINT lowerData_2 ~%data_2%~
				TO_LOWER lowerChargeTitle
				TO_LOWER lowerData_2
				// Si le titre est compris dans la description, on récupère la description qui possède généralement le niveau du lanceur de sorts
				PATCH_IF (~%lowerData_2%~ STRING_MATCHES_REGEXP ~^%lowerChargeTitle%~) == 0 BEGIN
					SPRINT chargeTitle "%data_2%"
					// Mise à 0 pour ne pas que la² sous-propriété ne soit affichée (je ne sais pas comment supprimer une seule entrée dans un ARRAY)
					SET $charge_abilities(~%data_0%~ ~%data_1%~ ~%data_2%~) = 0
				END
			END
		END
	END
	ELSE PATCH_IF chargeAbilityCount > 1 AND ~%chargeTitle%~ STRING_EQUAL ~~ BEGIN
		SET abilityNumber = headerIndex + 1
		SPRINT chargeTitle @101124 // ~Capacité %abilityNumber%~
	END

    PATCH_IF depletion == 1 BEGIN
		SPRINT chargeStr @102159 // ~%charges% charges, l'objet est détruit quand toutes les charges sont utilisées~
    END
    ELSE BEGIN
		SPRINT chargeStr @102094 // ~%charges% fois par jour~
    END

	SPRINT chargeTitle ~%chargeTitle% (%chargeStr%)~
	SET $charge_abilities(~%sort%~ ~%chargeAbilityCount%~ ~%chargeTitle%~) = 1
END

DEFINE_PATCH_MACRO ~add_combat_abilitie~ BEGIN
	GET_OFFSET_ARRAY2 blockOffsets offset ITM_V10_HEAD_EFFECTS
	PATCH_PHP_EACH blockOffsets AS int => blockOffset BEGIN
		READ_SHORT blockOffset opcode

		PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
			SET abilityType = AbilityType_Combat
			PATCH_IF opcode == 219 BEGIN
				SET opcodeBase = opcode
				PATCH_FOR_EACH subOpcode IN 0 1 BEGIN
					SET opcode = opcodeBase * 1000 + subOpcode
					LPF ~get_description_effect~ RET desc = description END
					PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
						SET $EVAL ~combat_abilities_%combatCount%~($sort_opcodes(~%opcode%~) $combatAbilities(~%combatCount%~ 0) ~%desc%~) = 1
						SET $combatAbilities(~%combatCount%~ 0) += 1
					END
				END
			END
			ELSE BEGIN
				LPF ~get_description_effect~ RET desc = description END
				PATCH_IF NOT ~%desc%~ STRING_EQUAL ~~ BEGIN
					SET $EVAL ~combat_abilities_%combatCount%~($sort_opcodes(~%opcode%~) $combatAbilities(~%combatCount%~ 0) ~%desc%~) = 1
					SET $combatAbilities(~%combatCount%~ 0) += 1
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ~add_weapon_statistics~ BEGIN
	READ_BYTE  (offset + ITM_HEAD_speed) speedFactor
	READ_SHORT (offset + ITM_HEAD_thac0_bonus) tac0
	READ_BYTE  (offset + ITM_HEAD_dice_sides) diceSides
	READ_BYTE  (offset + ITM_HEAD_dice_thrown) diceThrown
	READ_SHORT (offset + ITM_HEAD_damage_bonus) damageBonus
	READ_SHORT (offset + ITM_HEAD_damage_type) damageType

	SPRINT damage ~~
	/*  TODO: Cas limites à gérer
		- If Dice thrown, Dice size, and Damage bonus are all 0: Always deals zero damage (ignores all modifiers, like Weapon Proficiency).
	      If you want zero base damage + modifiers, you can use 1d1 - 1.
	    - Dice thrown d Dice size + Damage bonus = Xd0 + 0: Deals X damage, regardless of other modifiers.
	    - Dice thrown d Dice size + Damage bonus = 0d0 + X: Deals X + modifiers damage.
	    - Dice thrown d Dice size + Damage bonus = 0dX + 0: Also deals 0 damage.
	*/
	PATCH_IF diceThrown > 0 AND diceSides > 0 BEGIN
		SPRINT damage ~%damage%%diceThrown%d%diceSides% ~
	END
	PATCH_IF damageBonus > 0 BEGIN
		PATCH_IF damageBonus > 32768 BEGIN
			SET damageBonus = damageBonus - 65536
		END
		LPF ~signed_value~ INT_VAR value = damageBonus RET damageBonus = value END
		SPRINT damage ~%damage%%damageBonus%~
	END

    SET $EVAL ~weapon_statistics_%combatCount%~(~%tac0%~ ~%damage%~ ~%damageType%~ ~%speedFactor%~) = 1
END

DEFINE_PATCH_MACRO ~add_charge_abilities_to_description~ BEGIN
	LPF ~appendSection~ INT_VAR strref = 100012 RET description END // ~Capacités de charge~

	SORT_ARRAY_INDICES ~charge_abilities~ NUMERICALLY

    PATCH_PHP_EACH ~charge_abilities~ AS data => value BEGIN
        PATCH_IF value == 1 BEGIN
			LPF ~appendProperty~ STR_VAR name = EVAL ~%data_2%~ RET description END
		END
		ELSE PATCH_IF value == 2 BEGIN
			LPF ~appendSubProperty~ STR_VAR name = EVAL ~%data_2%~ RET description END
		END
    END
END

DEFINE_PATCH_MACRO ~add_combat_abilities_to_description~ BEGIN
	LPF ~weapon_modes_has_same_statistics~ RET hasSameStatistics END

	// TODO: Si les statistiques de l'arme ET les capacités de combat associées sont les mêmes, afficher comme si on n'avait qu'un seul effet étendu (Ex: U#STAF01.itm)

	PATCH_IF combatCount == 1 BEGIN
		PATCH_IF $combatAbilities(0 0) > 0 BEGIN
			LPF ~appendSection~ INT_VAR strref = 100011 RET description END // ~Capacités de combat~
	        PATCH_PHP_EACH ~combat_abilities_0~ AS data => value BEGIN
				LPF ~appendProperty~ STR_VAR name = EVAL ~%data_2%~ RET description END
	        END
		END
		PATCH_PHP_EACH weapon_statistics_0 AS stats => v BEGIN
			LPF ~appendLine~ RET description END
			LPM ~add_weapon_statistics_to_description~
		END
	END
	ELSE BEGIN
		PATCH_IF hasSameStatistics == 1 BEGIN // On affiche une seule fois les statistiques de l'arme
			PATCH_PHP_EACH weapon_statistics_0 AS stats => v BEGIN
				FOR (index = 0; index < combatCount; index += 1) BEGIN
					PATCH_IF $combatAbilities(~%index%~ 0) > 0 BEGIN
						SPRINT itemRef $combatAbilities(~%index%~ 1)
						LPF ~add_combat_section_to_description~ STR_VAR itemRef RET description END

	                    PATCH_PHP_EACH ~combat_abilities_%index%~ AS data => value BEGIN
							LPF ~appendProperty~ STR_VAR name = EVAL ~%data_2%~ RET description END
	                    END
					END
				END
				LPF ~appendLine~ RET description END
				LPM ~add_weapon_statistics_to_description~
			END
		END
		ELSE BEGIN // On affiche les statistiques de l'arme pour chaque utilisation différentes (jeté, melée, etc...)
			FOR (index = 0; index < combatCount; index += 1) BEGIN
				SPRINT itemRef $combatAbilities(~%index%~ 1)
				LPF ~add_combat_section_to_description~ STR_VAR itemRef RET description END

				PATCH_IF $combatAbilities(~%index%~ 0) > 0 BEGIN
                    PATCH_PHP_EACH ~combat_abilities_%index%~ AS data => value BEGIN
						LPF ~appendProperty~ STR_VAR name = EVAL ~%data_2%~ RET description END
                    END
				END
				PATCH_PHP_EACH ~weapon_statistics_%index%~ AS stats => value BEGIN
					LPF ~appendLine~    RET description END
					LPM ~add_weapon_statistics_to_description~
				END
			END
			LPF ~appendLine~ RET description END
		END
	END
END


DEFINE_PATCH_FUNCTION ~add_combat_section_to_description~ STR_VAR itemRef = ~~ RET description BEGIN
	LPF ~get_strrefs_from_tooltip~ STR_VAR id = EVAL ~%itemRef%~ RET strref_0 strref_1 strref_2 END
	SPRINT strref EVAL ~%strref_%index%%~
	SPRINT section @100011 // ~Capacités de combat~

	PATCH_IF EVAL ~%strref%~ > 0 BEGIN
		GET_STRREF strref sectionType
		SPRINT string @10013   // ~%section% (%sectionType%)~
		LPF ~appendSection~ STR_VAR string RET description END
	END
	ELSE BEGIN
	    SET offset = headerOffset + 0x38 * index
		READ_BYTE  (offset + ITM_HEAD_location) location
		READ_BYTE  (offset + ITM_HEAD_attack_type) attackType
		PATCH_IF location == 1 BEGIN
			PATCH_IF attackType == 1 BEGIN
				SPRINT sectionType @100013 // ~au corps à corps~
			END
			ELSE PATCH_IF attackType == 2 OR attackType == 4 BEGIN
				SPRINT sectionType @100014 // ~à distance~
			END
			SPRINT string @10013   // ~%section% (%sectionType%)~
			LPF ~appendSection~ STR_VAR string RET description END
		END
		ELSE BEGIN
			LPF ~appendSection~ INT_VAR strref = 100011 RET description END // ~Capacités de combat~
		END
	END
END

DEFINE_PATCH_MACRO ~add_weapon_statistics_to_description~ BEGIN
	LOCAL_SET strref = 0
	// ~%tac0%~ ~%damage%~ ~%damageType%~ ~%speedFactor%~
	PATCH_IF enchantment > 0 BEGIN
		LPF ~signed_value~ INT_VAR value = enchantment RET value END
		LPF ~appendValue~ INT_VAR strref = 102481 STR_VAR value RET description END // ~Enchantement~
	END
    PATCH_IF ~%stats_0%~ != 0 BEGIN //  AND enchantment != stats_0 // Pour ne l'afficher que si différent du TAC0 ?
		LPF ~signed_value~ INT_VAR value = stats_0 RET value END
		LPF ~appendValue~ INT_VAR strref = 102000 STR_VAR value RET description END // ~TAC0~
    END
	PATCH_IF ~%stats_1%~ STRING_EQUAL ~~ = 0 BEGIN
		LPF ~appendValue~ INT_VAR strref = 102001 STR_VAR value = EVAL ~%stats_1%~ RET description END // ~Dégâts~
	END
	PATCH_IF ~%stats_2%~ > 0 BEGIN
		SET strref = 102010 + stats_2
		SPRINT value (AT ~%strref%~)

		LPF ~appendValue~ INT_VAR strref = 102005 STR_VAR value RET description END // ~Type de dégâts~
	END
	LPF ~appendValue~ INT_VAR strref = 102002 STR_VAR value = EVAL ~%stats_3%~ RET description END // ~Facteur de vitesse~
END

DEFINE_PATCH_FUNCTION ~weapon_modes_has_same_statistics~ RET hasSameStatistics BEGIN
	SET hasSameStatistics = 1

	PATCH_IF combatCount > 1 BEGIN
		PATCH_PHP_EACH weapon_statistics_0 AS base => value BEGIN
			FOR (index = 1; index < combatCount; index += 1) BEGIN
				PATCH_PHP_EACH ~weapon_statistics_%index%~ AS data => value2 BEGIN
					PATCH_IF ~%base_0%~ != ~%data_0%~ OR (~%base_1%~ STRING_EQUAL ~%data_1%~) == 0 OR ~%base_2%~ != ~%data_2%~ OR ~%base_3%~ != ~%data_3%~ BEGIN
						SET hasSameStatistics = 0
					END
				END
			END
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_strrefs_from_tooltip~ STR_VAR id = ~~ RET strref_0 strref_1 strref_2 BEGIN
	SET strref_0 = 0
	SET strref_1 = 0
	SET strref_2 = 0
	TO_LOWER id

	PATCH_FOR_EACH idx IN 0 1 2 BEGIN
		SPRINT strref $tra_tooltips(~%id%~ ~%idx%~)
		PATCH_IF IS_AN_INT strref BEGIN
			SPRINT EVAL ~strref_%idx%~ ~%strref%~
		END
	END
END
