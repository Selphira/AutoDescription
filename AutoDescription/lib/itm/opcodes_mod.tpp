OUTER_SET $entangleSpellList(~d2wk5s1a~) = 1 // The Workshop Kitpack v4.6
OUTER_SET $entangleSpellList(~d2wk5s1b~) = 1 // The Workshop Kitpack v4.6
OUTER_SET $entangleSpellList(~d2wk5s1e~) = 1 // The Workshop Kitpack v4.6
OUTER_SET $entangleSpellList(~x#kispr~) = 1 // BG1 NPC Project v32

OUTER_SET $slowSpellList(~finslow~) = 1 // Ascension v2.0.24
OUTER_SET $slowSpellList(~mels545~) = 1 // Ascension v2.0.24

DEFINE_PATCH_FUNCTION ~get_splstate_name_mod~ INT_VAR splstate = 0 RET splstateName BEGIN
	LOOKUP_IDS_SYMBOL_OF_INT splstateValue ~splstate~ ~%parameter1%~

	PATCH_MATCH ~%splstateValue%~ WITH
		// Pnp Potion
		GT_UNDER_THE_EFFECTS_OF_A_POTION
		BEGIN
			SPRINT splstateName @230009 // ~potions~
		END
		DEFAULT SPRINT splstateName ~~
	END
END

/**
 * Tweaks Anthology
 * ****************
 * On ignore les effets liés à une ressource commençant par "C!" ou "cd".
 * Ce sont des effets qui indiquent que
 * - l'on peut switcher d'une utilisation à 1 ou 2 mains (composants @2020 @2030 @2035)
 * - l'on peut switcher d'un objet de protection avec ou sans bonus à la classe d'armure (composant @2150 @2151 @2152)
 */
DEFINE_PATCH_MACRO ~opcode_122_is_valid_mod~ BEGIN
	PATCH_IF isValid == 1 BEGIN
		SET isValid = ~%resref%~ STRING_MATCHES_REGEXP ~^[Cc]d\|[Cc]\!~
	END
END

/**
 * Tweaks Anthology
 * ****************
 * @1060 : Casques, Boucliers et Armures de fer cassables
 */
DEFINE_PATCH_MACRO ~opcode_143_group_mod~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~MISC57~ OR ~%resref%~ STRING_EQUAL_CASE ~MISC58~ OR ~%resref%~ STRING_EQUAL_CASE ~cddelhlm~ BEGIN
			LPF ~delete_opcode~
				INT_VAR opcode match_position = position
				RET $opcodes(~%opcode%~) = count
				RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
	        SET opcode = 519
	        LPM ~add_opcode~
		END
	END
END

/**
 * 5E_spellcasting
 * ***************
 * On ignore les effets liés aux "fakes slots".
 */
DEFINE_PATCH_MACRO ~opcode_146_is_valid_mod~ BEGIN
	PATCH_IF isValid == 1 BEGIN
		SET isValid = ~%resref%~ STRING_MATCHES_REGEXP ~^[dD]5[zZ]~
	END
END

/**
 * Skills and Abilities
 * ********************
 * Ce regroupement n'est effectué que si les bonus de dégâts liés à la force originaux n'ont pas été modifiés par un
 * autre mod.
 *
 * - Si la force du porteur est supérieure ou égale à 18 ; Dégâts : +1 (non cumulatif)
 * - Si la force du porteur est supérieure ou égale à 19 ; Dégâts : +2 (non cumulatif)
 * - Si la force du porteur est supérieure ou égale à 20 ; Dégâts : +1 (non cumulatif)
 * - Si la force du porteur est supérieure ou égale à 22 ; Dégâts : +1 (non cumulatif)
 * - Si la force du porteur est supérieure ou égale à 24 ; Dégâts : +1 (non cumulatif)
 * - Si la force du porteur est supérieure ou égale à 25 ; Dégâts : +1 (non cumulatif)
 * ---> - Le bonus aux dégâts liés à la force est augmenté de 50% (non cumulatif)
 */
DEFINE_PATCH_MACRO ~opcode_232_group_mods~ BEGIN
	LOCAL_SET count = 0
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	// Skills and Abilities
	PATCH_IF has_base_str_damage == 1 BEGIN
		CLEAR_ARRAY positions
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND ~%resref%~ STRING_MATCHES_REGEXP ~MOSTR0[0-9]+~ == 0 BEGIN
				SET $positions(~%resref%~) = position
				SET count += 1
			END
		END
		PATCH_IF count == 6 BEGIN
			PATCH_PHP_EACH ~positions~ AS _ => position BEGIN
				LPF ~delete_opcode~
                    INT_VAR opcode = 232 match_position = position
                    RET $opcodes(~232~) = count
                    RET_ARRAY EVAL ~opcodes_232~ = opcodes_xx
                END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~232~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_232~
	        END
			// Création fake opcode "Le bonus aux dégâts liés à la force est augmenté de 50% (non cumulatif)"
			SET opcode = 523
			LPM ~add_opcode~
		END
	END
	CLEAR_ARRAY positions
END

/**
 * 5E_spellcasting
 * ***************
 * On ignore les effets liés aux "fakes slots".
 *
 * npc_ee
 * ******
 * On ignore le sort qui regroupe l'ensemble des sortilèges
 */
DEFINE_PATCH_MACRO ~opcode_321_is_valid_mod~ BEGIN
	PATCH_IF isValid == 1 BEGIN
		SET isValid = ~%resref%~ STRING_MATCHES_REGEXP ~^[dD]5[zZ]~
	END
END

DEFINE_PATCH_MACRO ~opcode_326_is_valid_mod~ BEGIN
	LOCAL_SPRINT splprot $splprots(~%parameter2%~)
	// 5E_spellcasting
	PATCH_IF isValid == 1 BEGIN
		PATCH_MATCH ~%splprot%~ WITH
			D5_DIV_1_7 D5_DIV_8_9 D5_WIZ_1_7 D5_WIZ_8_9 D5_KIT_IS D5_FATIGUE_0 D5_FATIGUE_1 ~D5_DIV=1_7~ ~D5_WIZ=1_7~ ~D5_WIZ=8_9~
			BEGIN
				SET isValid = 0
			END
			DEFAULT SET isValid = ~%resref%~ STRING_MATCHES_REGEXP ~^[dD]5[zZ]~
		END
	END
	// npc_ee
	PATCH_IF isValid == 1 BEGIN
		SET isValid = NOT ~%resref%~ STRING_EQUAL_CASE "D5_NUKT"
	END
END

/**
 * Conditions pour Skills and Abilities
 */
DEFINE_PATCH_MACRO ~opcode_326_condition_mod~ BEGIN
	SPRINT splprot $splprots(~%statType%~)
	PATCH_IF VARIABLE_IS_SET $splprotstats(~%statType%~) BEGIN
		SPRINT proficiencyId $splprotstats(~%statType%~)
	END
	PATCH_IF VARIABLE_IS_SET $tra_proficiencies(~%proficiencyId%~) BEGIN
		SPRINT proficiency $tra_proficiencies(~%proficiencyId%~)
	END
	PATCH_MATCH ~%splprot%~ WITH
		//mo_2h_bonus BEGIN END
		// Skills and Abilities
		mo_thrown_prof1 mo_thrown_prof2
		mo_con_prof1 mo_con_prof2 mo_con_prof3 mo_con_prof4 mo_con_prof5
		mo_dev_prof1 mo_dev_prof2 mo_dev_prof3 mo_dev_prof4 mo_dev_prof5
		mo_has_prof1 mo_has_prof2 mo_has_prof3 mo_has_prof4 mo_has_prof5
		mo_spl_prof1 mo_spl_prof2 mo_spl_prof3 mo_spl_prof4 mo_spl_prof5
		BEGIN
			SET strref = 13261000 // ~Si la compétence %proficiency% est supérieure ou égale à %value%~
		END
		// Skills and Abilities
		mo_armor_prof0 mo_armor_prof1 mo_armor_prof2 mo_armor_prof3 mo_armor_prof4 mo_armor_prof5
		BEGIN
			SET strref = 13261001 // ~Si la compétence %proficiency% est égale à %value%~
		END
		// Skills and Abilities
		mo_2h_bonus mo_arch_prof1 mo_arch_prof2 mo_swsh_bonus
		BEGIN
			SET strref = 13261002 // ~Si la compétence %proficiency% est inférieure à %value%~
		END
		DEFAULT
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: splprot %splprot% non gere~ END
	END
	PATCH_MATCH ~%splprot%~ WITH
		mo_armor_prof0 BEGIN SET value = 0 END
		mo_thrown_prof1 mo_armor_prof1 mo_con_prof1 mo_dev_prof1 mo_has_prof1 mo_spl_prof1 BEGIN SET value = 1 END
		mo_thrown_prof2 mo_armor_prof2 mo_con_prof2 mo_dev_prof2 mo_has_prof2 mo_spl_prof2 mo_2h_bonus mo_swsh_bonus BEGIN SET value = 2 END
		mo_armor_prof3 mo_con_prof3 mo_dev_prof3 mo_has_prof3 mo_spl_prof3 BEGIN SET value = 3 END
		mo_armor_prof4 mo_con_prof4 mo_dev_prof4 mo_has_prof4 mo_spl_prof4 BEGIN SET value = 4 END
		mo_armor_prof5 mo_con_prof5 mo_dev_prof5 mo_has_prof5 mo_spl_prof5 BEGIN SET value = 5 END
		DEFAULT
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Valeur du splprot %splprot% non geree~ END
	END
END