/*
 * Tableau servant à savoir comment trier le résultat final.
 * Vu qu'ils ne sont généralement pas
 */
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~sort_opcodes~ BEGIN
	  0 => 1   // Stat: AC vs. Damage Type Modifier [0]
	 54 => 3   // Stat: THAC0 Modifier [54]
	305 => 5   // Stat: THAC0 Modifier (Off-Hand) [305]
	278 => 9   // Stat: To Hit Modifier [278]
	 33 => 10  // Stat: Save vs. Death Modifier [33]
	 34 => 11  // Stat: Save vs. Wands Modifier [34]
	 35 => 12  // Stat: Save vs. Petrification/Polymorph Modifier [35]
	 36 => 13  // Stat: Save vs. Breath Weapons Modifier [36]
	 37 => 14  // Stat: Save vs. Spells Modifier [37]
	 12 => 15  // HP: Damage [12]
	 42 => 20  // Spell: Wizard Spell Slots Modifier [42]
	 62 => 21  // Spell: Priest Spell Slots Modifier [62]
	190 => 30  // Stat: Attack Speed Factor [190]
	  1 => 31  // Stat: Attacks Per Round Modifier [1]
	 44 => 40  // Stat: Strength Modifier [44]
	 15 => 41  // Stat: Dexterity Modifier [15]
	 19 => 43  // Stat: Intelligence Modifier [19]
	  6 => 45  // Stat: Charisma Modifier [6]
	 22 => 46  // Stat: Luck Modifier [22]
	301 => 90  // Stat: Critical Hit Modifier [301]
	275 => 103 // Stat: Hide in Shadows Modifier [275]
	 59 => 104 // Stat: Stealth Modifier [59]
	 /*
	 @102070 = ~Vol à la tire~
     @102071 = ~Crochetage de serrures~
     @102075 = ~Détection des illusions~
     @102072 = ~Détection/désamorçage des pièges~
     @102076 = ~Pose des pièges~
     @102074 = ~Camouflage dans l'ombre~
     @102073 = ~Furtivité~
     */
	263 => 105 // Stat: Backstab [263]
	233 => 110 // Stat: Proficiency [233]
	166 => 120 // Stat: Magic Resistance Modifier [166]
	 28 => 122 // Stat: Cold Resistance Modifier [28]
	173 => 123 // Stat: Poison Resistance Modifier [173]
	 86 => 126 // Stat: Reduced Damage from Slashing Modifier [86]
	 87 => 127 // Stat: Reduced Damage from Crushing Modifier [87]
	 88 => 128 // Stat: Reduced Damage from Piercing Modifier [88]
	 89 => 129 // Stat: Reduced Damage from Missiles Modifier [89]
	206 => 130 // Spell: Protection from Spell [206]
	292 => 135 // Protection: Backstab [292]
	 39 => 150 // State : Unconsciousness [39]
	109 => 151 // State: Hold Creature I [109]
	175 => 151 // State: Hold Creature II [175]
	185 => 151 // State: Hold Creature III [185]
	 55 => 160 // Death: Kill Creature Type [55]

	 // Charge
	146 => 200 // Spell: Cast Spell (at Target) [146]
END

/*
 * Liste des opcodes ignorés. La plupart du temps car ils n'ont rien à proposer à la description.
 */
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~ignored_opcodes~ BEGIN
	  7 => 1
	  9 => 1
	 50 => 1
	101 => 1 // Protection: from Opcode [101] TODO: A gérer quand même ? Ne fait pas forcément doublon avec le 206 ?
	139 => 1
	141 => 1
	142 => 1
	169 => 1
	267 => 1
	296 => 1
	318 => 1 // Protection: Immunity Spell [318] TODO: A gérer quand même ? Stat: Set Stat (TobEx)
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~spell_levels~ BEGIN
		   0 => 0
	~%BIT0%~ => 1
	~%BIT1%~ => 2
	~%BIT2%~ => 3
	~%BIT3%~ => 4
	~%BIT4%~ => 5
	~%BIT5%~ => 6
	~%BIT6%~ => 7
	~%BIT7%~ => 8
	~%BIT8%~ => 9
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~damage_types~ BEGIN
	~%DAMAGETYPE_electricity%~ => 101093 // ~points de dégâts d'électricité~
	~%DAMAGETYPE_acid%~        => 101096 // ~points de dégâts d'acide~
	~%DAMAGETYPE_fire%~        => 101094 // ~points de dégâts de feu~
	~%DAMAGETYPE_cold%~        => 101095 // ~points de dégâts de froid~
	~%DAMAGETYPE_piercing%~    => 101100 // ~points de dégâts de perforants~
	~%DAMAGETYPE_magic%~       => 101101 // ~points de dégâts magiques~
END

ACTION_DEFINE_ARRAY ~opcode_1_values~ BEGIN 0 10 20 30 40 50 5 15 25 35 45 END


/* --------------- *
 * Classe d'armure *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_0~ BEGIN
	LOCAL_SPRINT versus ~~
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == AC_MOD_TYPE_set_base BEGIN
		PATCH_IF %itemType% != ITM_TYPE_armor BEGIN
			SPRINT value @10010 // ~Passe à %value%~
		END
	END
	ELSE BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%value%~ RET value END
		PATCH_IF parameter2 != AC_MOD_TYPE_all BEGIN
			SET strref = 102020 + parameter2
			SPRINT versus (AT ~strref~) // ~contre les xxx~
			SPRINT value ~%value% %versus%~
		END
	END

	SPRINT name @102008        // ~Classe d'armure~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

/* ----------------- *
 * Attaque par round *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_1~ BEGIN
	PATCH_IF parameter2 != MOD_TYPE_percentage BEGIN
		// Weidu ne gérant pas les nombres flottants, une solution est de passer par des nombres 10 fois plus grand.
		SET value = $opcode_1_values(~%parameter1%~)

		PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
            LPF ~signed_value~ INT_VAR value RET value END
        END

		INNER_PATCH_SAVE value ~%value%~ BEGIN
			SPRINT oneHalf @10011
			SPRINT andHalf @10012
			REPLACE_TEXTUALLY ~\([0-9]\)+0$~ ~\1~        // 20 => 2
			REPLACE_TEXTUALLY ~\([0-9]\)+5$~ ~%andHalf%~ // 25 => 2 et demi
			REPLACE_TEXTUALLY ~5$~ ~ %oneHalf%~          // 5  => une demi
		END

		PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
			SPRINT value @10010 // ~Passe à %value%~
		END
	END
	ELSE BEGIN
		SET value = ~%parameter1%~
		SPRINT value @10002 // ~%value% %~
		SPRINT value @10006 // ~Multiplié par %value%~
	END

	SPRINT name @102007 // ~Attaque par round~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

/* -------- *
 * Charisme *
 * -------- */
DEFINE_PATCH_MACRO ~opcode_6~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101081 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Charisme~
END

/* ------ *
 * Dégâts *
 * ------ */
DEFINE_PATCH_MACRO ~opcode_12~ BEGIN
	LOCAL_SET damageAmount = %parameter1%
	LOCAL_SET type = %parameter2%

	PATCH_IF special > 0 BEGIN
		PATCH_WARN "%SOURCE_FILE% : Valeur spéciale '%special%' pour le opcode 12 pas encore geree"
	END
	PATCH_IF NOT VARIABLE_IS_SET $damage_types(~%type%~) BEGIN
		PATCH_WARN "%SOURCE_FILE% : Type de degat '%type%' pour le opcode 12 pas encore gere"
	END

	SET type = $damage_types(~%type%~)
	SPRINT damageType (AT ~%type%~)
	LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET damage END

	PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF probability < 100 BEGIN
			LPF ~percent_value~ INT_VAR value = EVAL ~%probability%~ + 1 RET probability = value END
			SPRINT description @102091 // ~%probability% de chances d'infliger %damage% %damageType% supplémentaires~
		END
		ELSE BEGIN
			SPRINT value @102092 // ~Inflige %damage% %damageType% supplémentaires~
			SPRINT name @102001
			SPRINT description @100001 // ~%name%%colon%%value%~
		END
	END
END

/* --------- *
 * Dextérité *
 * --------- */
DEFINE_PATCH_MACRO ~opcode_15~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101078 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dextérité~
END

/* ------------ *
 * Intelligence *
 * ------------ */
DEFINE_PATCH_MACRO ~opcode_19~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101077 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Intelligence~
END

/* ------ *
 * Chance *
 * ------ */
DEFINE_PATCH_MACRO ~opcode_22~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101075 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Chance~
END

/* ------------------- *
 * Résistance au froid *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_28~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102059 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance au froid~
END

/* -------------------------------------------------------------- *
 * Jets de sauvegarde contre la paralysie, la mort et les poisons *
 * -------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_33~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102029 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre la paralysie, la mort et les poisons~
END

/* ------------------------------------------------------------------- *
 * Jets de sauvegarde contre les baguettes, les sceptres et les bâtons *
 * ------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_34~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102030 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les baguettes, les sceptres et les bâtons~
END

/* ------------------------------------------------------------- *
 * Jets de sauvegarde contre la pétrification et la métamorphose *
 * ------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_35~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102031 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre la pétrification et la métamorphose~
END

/* -------------------------------------- *
 * Jets de sauvegarde contre les souffles *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_36~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102032 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les souffles~
END

/* ----------------------------------- *
 * Jets de sauvegarde contre les sorts *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_37~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102033 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les sorts~
END

/* ----------------------------- *
 * Mémorisation de sort profanes *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_42~ BEGIN
	LOCAL_SET amount = $spell_levels(~%parameter1%~)
	LOCAL_SET level = $spell_levels(~%parameter2%~)

	PATCH_IF level == 0 BEGIN
		SET level = $spell_levels(~%parameter1%~)
		SPRINT description @102089 //~Double le nombre de sorts profanes de niveau %level% que le personnage peut mémoriser.~
	END
	ELSE PATCH_IF amount > 0 BEGIN // Mémorisation
		PATCH_IF amount == 1 BEGIN
			SPRINT description @102085 // ~Mémorisation d'un sort profane supplémentaire de niveau %level%~
		END
		ELSE BEGIN
			SPRINT description @102086 // ~Mémorisation de %amount% sorts profanes supplémentaires de niveau %level%~
		END
	END
	ELSE PATCH_IF amount < 0 BEGIN // Oubli
		PATCH_IF amount == ~-1~ BEGIN
			SPRINT description @102087 // ~Oubli d'un sort profane de niveau %level%~
		END
		ELSE BEGIN
			SPRINT description @102088 // ~Oubli de %amount% sorts profanes de niveau %level%~
		END
	END
END

/* ----- *
 * Force *
 * ----- */
DEFINE_PATCH_MACRO ~opcode_44~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101076 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force~
END

/* ---- *
 * TAC0 *
 * ---- */
DEFINE_PATCH_MACRO ~opcode_54~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102000 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0~
END

/* --------- *
 * Furtivité *
 * --------- */
DEFINE_PATCH_MACRO ~opcode_59~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102073 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Furtivité~
END

/* -------------------------- *
 * Mémorisation de sort divin *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_62~ BEGIN
	LOCAL_SET amount = $spell_levels(~%parameter1%~)
	LOCAL_SET level = $spell_levels(~%parameter2%~)

	PATCH_IF level == 0 BEGIN
		SET level = $spell_levels(~%parameter1%~)
		SPRINT description @102084 //~Double le nombre de sorts divins de niveau %level% que le personnage peut mémoriser.~
	END
	ELSE PATCH_IF amount > 0 BEGIN // Mémorisation
		PATCH_IF amount == 1 BEGIN
			SPRINT description @102080 // ~Mémorisation d'un sort divin supplémentaire de niveau %level%~
		END
		ELSE BEGIN
			SPRINT description @102081 // ~Mémorisation de %amount% sorts divins supplémentaires de niveau %level%~
		END
	END
	ELSE PATCH_IF amount < 0 BEGIN // Oubli
		PATCH_IF amount == ~-1~ BEGIN
			SPRINT description @102082 // ~Oubli d'un sort divin de niveau %level%~
		END
		ELSE BEGIN
			SPRINT description @102083 // ~Oubli de %amount% sorts divins de niveau %level%~
		END
	END
END

/* ----- *
 * Tue les créatures de type xx de yy dés de vie ou moins *
 * ----- */
DEFINE_PATCH_MACRO ~opcode_55~ BEGIN
	PATCH_IF diceCount > 0 BEGIN
		//Parameter #1: IDS Entry
	    //Parameter #2: IDS File
		//LPF ~opcode_mod~ INT_VAR strref = 101076 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force~
		PATCH_DEFINE_ASSOCIATIVE_ARRAY ~ids_files~ BEGIN
			2 => ~EA.ids~
			3 => ~General.ids~
			4 => ~Race.ids~
			5 => ~Class.ids~
			6 => ~Specific.ids~
			7 => ~Gender.ids~
			8 => ~Align.ids~
			9 => ~Kit.ids~
		END
		PATCH_PHP_EACH ids_files AS k => file BEGIN
		END
		SPRINT idsFile $ids_files(~%parameter2%~)
		PATCH_WARN "%SOURCE_FILE%: opcode 55 à gérer %idsFile%"
		// Tue instantanément les GOLEM (race) de xx dés de vie ou moins
	END
END

/* -------------------------------- *
 * Résistance aux dégâts tranchants *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_86~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102061 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts tranchants~
END

/* -------------------------------- *
 * Résistance aux dégâts contondants *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_87~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102062 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts contondants~
END

/* -------------------------------- *
 * Résistance aux dégâts perforants *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_88~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102063 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts perforants~
END

/* ------------------------------------ *
 * Résistance aux dégâts de projectiles *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_89~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102064 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts de projectiles~
END

/* --------------------------------- *
 * Paralyse les créatures de type xx *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_109~ BEGIN
	//Parameter #1: IDS Entry
    //Parameter #2: IDS File
	//LPF ~opcode_mod~ INT_VAR strref = 101076 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force~
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~ids_files~ BEGIN
		2 => ~EA.ids~
		3 => ~General.ids~
		4 => ~Race.ids~
		5 => ~Class.ids~
		6 => ~Specific.ids~
		7 => ~Gender.ids~
		8 => ~Align.ids~
		9 => ~Kit.ids~
	END
	PATCH_PHP_EACH ids_files AS k => file BEGIN
	END
	SPRINT idsFile $ids_files(~%parameter2%~)
	PATCH_WARN "%SOURCE_FILE%: opcode 109 à gérer %idsFile%"
	// Paralyse les GOLEM (race) de xx dés de vie ou moins
END

/* -------------- *
 * Lancer un sort *
 * -------------- */
DEFINE_PATCH_MACRO ~opcode_146~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET description = spellName END

	PATCH_IF castingLevel > 0 BEGIN
		SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
		SPRINT description ~%description% (%castingLevelStr%)~
	END
END

/* --------------------- *
 * Résistance à la magie *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_166~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102060 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à la magie~
END

/* -------------------- *
 * Résistance au poison *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_173~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102058 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance au poison~
END

/* --------------------------------- *
 * Paralyse les créatures de type xx *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_175~ BEGIN
	LPM ~opcode_109~
END

/* --------------------------------- *
 * Paralyse les créatures de type xx *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_185~ BEGIN
	LPM ~opcode_109~
END

/* ------------------ *
 * Facteur de vitesse *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_190~ BEGIN
	LPF ~signed_value~ INT_VAR value = EVAL ~%parameter1%~ RET value END
	SPRINT name @102002 //~Facteur de vitesse~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

/* ------------------ *
 * Immunité à un sort *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_206~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @102035 // ~Immunité à %spellName%~
END

/* ------------------- *
 * Compétence martiale *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_233~ BEGIN
	LOCAL_SET value = ~%parameter1%~
	LOCAL_SPRINT proficiency ~~

	SPRINT description ~~

	PATCH_IF VARIABLE_IS_SET $tra_proficiencies(~%parameter2%~)  BEGIN
		SPRINT value @10010 // ~Passe à %value%~
		TO_LOWER value
		SPRINT proficiency $tra_proficiencies(~%parameter2%~)
		SPRINT value ~%proficiency% %value%~

		SPRINT name @102009
		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END

/* ---------------------------------- *
 * Multiplicateur d'attaque sournoise *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_263~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102006 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Multiplicateur d'attaque sournoise~
END

/* ----------------------- *
 * Camouflage dans l'ombre *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_275~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102074 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Camouflage dans l'ombre~
END

/* -------------------------------------------- *
 * Chance de toucher (Agis sur le TAC0 modifié) *
 * -------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_278~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102036 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Chances de toucher~
END

/* -------------------------------- *
 * Immunité aux attaques sournoises *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_292~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @102037 // ~Immunité aux attaques sournoises~
	END
END

/* ------------------------ *
 * Chances de coup critique *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_301~ BEGIN
	LPF ~percent_value~ INT_VAR value = EVAL ~%parameter1%~ * 5 RET probability = value END
	SPRINT description @102093 // ~%probability% de chance d'infliger un coup critique~
END

/* -------------------- *
 * TAC0 main secondaire *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_305~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102010 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 de la main secondaire~
END

DEFINE_PATCH_FUNCTION ~opcode_mod~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10010 // ~Passe à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT value @10006 // ~Multiplié par %value%~
	END

	SPRINT name (AT ~%strref%~)
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_FUNCTION ~opcode_mod_percent~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	PATCH_MATCH parameter2 WITH
		MOD_TYPE_cumulative BEGIN
			LPF ~signed_value~ INT_VAR value RET value END
			SPRINT value @10002 // ~%value% %~
			SPRINT name (AT ~%strref%~)
			SPRINT description @100001 // ~%name%%colon%%value%~
		END
		MOD_TYPE_flat BEGIN
			SPRINT value @10002 // ~%value% %~
			SPRINT value @10010 // ~Passe à %value%~
			SPRINT name (AT ~%strref%~)
			SPRINT description @100001 // ~%name%%colon%%value%~
		END
		DEFAULT PATCH_WARN ~%SOURCE_FILE% : Opcode %opcode% : Valeur du second parametre invalide (%parameter2%), l'effet est annule ~
	END
END

DEFINE_PATCH_FUNCTION ~opcode_save_vs~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	SPRINT name @102034 // ~Jets de sauvegarde~
	SPRINT strSave (AT ~%strref%~)

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT value ~%value% %strSave%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10010 // ~Passe à %value%~
		SPRINT name ~%name% %strSave%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT value @10006 // ~Multiplié par %value%~
		SPRINT name ~%name% %strSave%~
	END

	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_FUNCTION ~get_spell_name~ STR_VAR file = "" RET spellName BEGIN
	INNER_ACTION BEGIN
		SILENT
		COPY_EXISTING ~%resref%.spl~ ~override~
			READ_STRREF SPL_unidentified_name spellName
		BUT_ONLY_IF_IT_CHANGES
        VERBOSE
    END
END

