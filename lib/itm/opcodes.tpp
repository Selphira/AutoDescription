/*
 * Tableau servant à savoir comment trier le résultat final.
 * Vu qu'ils ne sont généralement pas
 */
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~sort_opcodes~ BEGIN
	216 => 1   // Spell Effect: Level Drain [216]
	  0 => 2   // Stat: AC vs. Damage Type Modifier [0]
	219 => 3   // Stat: AC vs. Creature Type Modifier [219]
	 54 => 4   // Stat: THAC0 Modifier [54]
	284 => 5   // Stat: Melee THAC0 Modifier [284]
	305 => 6   // Stat: THAC0 Modifier (Off-Hand) [305]
	288 => 7   // Stat: Fist THAC0 Modifier [288]
	278 => 9   // Stat: To Hit Modifier [278]
	 33 => 10  // Stat: Save vs. Death Modifier [33]
	 34 => 11  // Stat: Save vs. Wands Modifier [34]
	 35 => 12  // Stat: Save vs. Petrification/Polymorph Modifier [35]
	 36 => 13  // Stat: Save vs. Breath Weapons Modifier [36]
	 37 => 14  // Stat: Save vs. Spells Modifier [37]
	 12 => 15  // HP: Damage [12]
	 73 => 16  // Stat: Extra Damage Modifier [73]
	285 => 17  // Stat: Melee Weapon Damage Modifier [285]
	286 => 18  // Stat: Missile Weapon Damage Modifier [286]
	289 => 19  // Stat: Fist Damage Modifier [289]
	 25 => 20  // State: Poison [25]
	 78 => 21  // State: Disease [78]
    214 => 22  // Select Spell [214]
    191 => 23  // Spell: Casting Level Modifier [191]
	 42 => 24  // Spell: Wizard Spell Slots Modifier [42]
	 62 => 25  // Spell: Priest Spell Slots Modifier [62]
	145 => 26  // Spell: Disable Spell Casting Abilities [145]
	189 => 28  // Stat: Casting Time Modifier [189]
	 60 => 29  // Stat: Miscast Magic [60]
	190 => 30  // Stat: Attack Speed Factor [190]
	  1 => 31  // Stat: Attacks Per Round Modifier [1]
	 98 => 35  // Stat: Regeneration [98]
	 18 => 39  // Stat: Maximum HP Modifier [18]
	 44 => 40  // Stat: Strength Modifier [44]
	 97 => 41  // Stat: Strength-Bonus Modifier [97]
	 15 => 42  // Stat: Dexterity Modifier [15]
	 10 => 43  // Stat: Constitution Modifier [10]
	 19 => 44  // Stat: Intelligence Modifier [19]
	 49 => 45  // Stat: Wisdom Modifier [49]
	  6 => 46  // Stat: Charisma Modifier [6]
	 22 => 47  // Stat: Luck Modifier [22]
	281 => 60  // Stat: Wild Magic [281]
	301 => 90  // Stat: Critical Hit Modifier [301]
	 92 => 98  // Stat: Pick Pockets Modifier [92]
	 90 => 99  // Stat: Open Locks Modifier [90]
	276 => 100 // Stat: Detect Illusion Modifier [276]
	 91 => 101 // Stat: Find Traps Modifier [91]
	277 => 102 // Stat: Set Traps Modifier [277]
	275 => 103 // Stat: Hide in Shadows Modifier [275]
	 59 => 104 // Stat: Stealth Modifier [59]
	263 => 105 // Stat: Backstab [263]
	126 => 108 // Stat: Movement Modifier [126]
	176 => 108 // Stat: Movement Modifier (II) [176]
	233 => 110 // Stat: Proficiency [233]
	166 => 119 // Stat: Magic Resistance Modifier [166]
	 30 => 120 // Stat: Fire Resistance Modifier [30]
	 28 => 121 // Stat: Cold Resistance Modifier [28]
	 29 => 122 // Stat: Electricity Resistance Modifier [29]
	173 => 123 // Stat: Poison Resistance Modifier [173]
	 27 => 124 // Stat: Acid Resistance Modifier [27]
	 31 => 125 // Stat: Magic Damage Resistance Modifier [31]
	 84 => 126 // Stat: Reduced Damage from Magical Fire Modifier [84]
	 85 => 127 // Stat: Reduced Damage from Magical Cold Modifier [85]
	 86 => 136 // Stat: Reduced Damage from Slashing Modifier [86]
	 87 => 137 // Stat: Reduced Damage from Crushing Modifier [87]
	 88 => 138 // Stat: Reduced Damage from Piercing Modifier [88]
	 89 => 139 // Stat: Reduced Damage from Missiles Modifier [89]
	 17 => 145 // Stat: Current HP Modifier [17]
	106 => 150 // Stat: Morale Break [106]
	 21 => 155 // Stat: Lore Modifier [21]
	262 => 160 // Stat: Visual Range [262]
	 69 => 162 // Protection: From Detection (Non-Detection) [69]
	 16 => 170 // State: Haste [16]
	130 => 171 // State: Bless [130]
	 40 => 172 // State: Slow [40]
	  3 => 173 // State: Berserking [3]
	 24 => 174 // State: Horror [24]
	 74 => 175 // State: Blindness [74]
	 45 => 176 // State: Stun [45]
	 20 => 177 // State: Invisibility [20]
	 63 => 178 // State: Infravision [63]
	 39 => 179 // State : Unconsciousness [39]
	154 => 180 // State: Entangle [154]
	 65 => 181 // State: Blur [65]
	 39 => 182 // State: Unconsciousness [39]
	109 => 185 // State: Hold Creature I [109]
	175 => 185 // State: Hold Creature II [175]
	185 => 185 // State: Hold Creature III [185]
	 55 => 189 // Death: Kill Creature Type [55]
	206 => 190 // Spell: Protection from Spell [206]
	162 => 191 // Cure: Hold [162]
	161 => 192 // Cure: Fear [161]
	 23 => 193 // Cure: Horror [23]
	 79 => 194 // Cure: Disease [79]
	 75 => 195 // Cure: Blindness [75]
	 81 => 196 // Cure: Deafness [81]
	 77 => 197 // Cure: Feeblemindedness [77]
	116 => 198 // Cure: (Remove) Invisibility [116]
	163 => 231 // Protection: Free Action [163]
	204 => 232 // Spell: Protection from Spell (School) [204]
	102 => 233 // Protection: from Spell Levels [102]
	292 => 234 // Protection: Backstab [292]
	100 => 235 // Protection: from Creature Type [100]
	120 => 236 // Protection: from Melee Weapons [120]
	 83 => 237 // Protection: From Projectile (Any) [83]
	 13 => 238 // Death: Instant Death [13]
	238 => 239 // Death: Disintegrate [238]
	197 => 249 // Spell: Bounce Projectile [197]
	280 => 250 // Spell Effect: Wild Magic [280]
	235 => 251 // Spell Effect: Wing Buffet [235]
	 57 => 255 // Alignment: Change [57]
	 56 => 256 // Alignment: Invert [56]
	 71 => 257 // Sex Change [71]


	 // Charge
	146 => 260 // Spell: Cast Spell (at Target) [146]
	 67 => 270 // Summon: Creature Summoning [67]
	208 => 300 // Stat: Minimum HP Limit [208]
	273 => 350 // Remove: Specific Area Effect(Zone of Sweet Air) [273]
END

/*
 * Liste des opcodes ignorés. La plupart du temps car ils n'ont rien à proposer à la description.
 */
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~ignored_opcodes~ BEGIN
	  7 => 1
	  8 => 1 // Colour: Change by RGB [8]
	  9 => 1
	 50 => 1
	 51 => 1 // Colour: Strong/Dark by RGB [51]
	 53 => 1 // Graphics: Animation Change [53]
	 66 => 1 // Graphics: Transparency Fade [66]
	101 => 1 // Protection: from Opcode [101] // TODO: A gérer quand même ? Ne fait pas forcément doublon avec le 206 ?
	110 => 1 // (Retreat From) [110]
	139 => 1
	141 => 1
	142 => 1
	144 => 1 // Button: Disable Button [144] // TODO: A gérer ! Empêche le personnage de faire certaines actions !
	169 => 1
	174 => 1 // Spell Effect: Play Sound Effect [174]
	180 => 1 // Item: Can't Use Item [180] // TODO: A gérer, et grouper (BOW15...)
	193 => 1 // Spell Effect: Invisible Detection by Script [193]
	215 => 1
	221 => 1 // Removal: Remove Secondary Type [221]
	232 => 1 // Spell Effect: Cast Spell on Condition [232]
	240 => 1 // Graphics: Remove Special Effect Icon [240]
	251 => 1 // Spell Effect: Change Bard Song Effect [251] // TODO: A gérer !
	267 => 1
	272 => 1 // Spell: Apply Effect on Condition [272] // TODO: A gérer !
	282 => 1 // Script: Scripting State Modifier [282]
	291 => 1 // Graphics: Disable Visual Effect [291]
	293 => 1 // Script: Enable Offscreen AI [293]
	295 => 1
	296 => 1
	297 => 1 // Text: Protection from Display Specific String [267]
	300 => 1 // NPC Bump [300] // TODO: A gérer ? Vérifier les objets qui l'utilisent
	309 => 1 // Script: Set/Modify Local Variable [309]
	318 => 1 // Protection: Immunity Spell [318] // TODO: A gérer quand même ? Stat: Set Stat (TobEx)
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~damage_types~ BEGIN
	~%DAMAGETYPE_crushing%~    => 101104 //        0 ~points de dégâts contondants~
	~%DAMAGETYPE_acid%~        => 101096 //    65536 ~points de dégâts d'acide~
	~%DAMAGETYPE_cold%~        => 101095 //   131072 ~points de dégâts de froid~
	~%DAMAGETYPE_electricity%~ => 101093 //   262144 ~points de dégâts d'électricité~
	~%DAMAGETYPE_fire%~        => 101094 //   524288 ~points de dégâts de feu~
	~%DAMAGETYPE_piercing%~    => 101100 //  1048576 ~points de dégâts de perforants~
	~%DAMAGETYPE_poison%~      => 101097 //  2097152 ~points de dégâts de poison~
	~%DAMAGETYPE_magic%~       => 101101 //  4194304 ~points de dégâts magiques~
	~%DAMAGETYPE_slashing%~    => 101103 // 16777216 ~points de dégâts tranchants~
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~feets_to_meters~ BEGIN
	1 => ~0,6 %meter%~
	2 => ~1,2 %meter%~
	3 => ~1,8 %meter%~
	4 => ~2,5 %meters%~
	5 => ~3 %meters%~
	6 => ~3,5 %meters%~
	7 => ~4,5 %meters%~
	8 => ~5 %meters%~
	9 => ~5,5 %meters%~
	10 => ~6 %meters%~
	11 => ~7 %meters%~
	12 => ~7,5 %meters%~
	13 => ~8 %meters%~
	15 => ~9 %meters%~
END

ACTION_DEFINE_ARRAY ~opcode_1_values~ BEGIN 0 10 20 30 40 50 5 15 25 35 45 END

OUTER_SET AbilityType_Charge = 1
OUTER_SET AbilityType_Combat = 2
OUTER_SET AbilityType_Equipped = 3


/* --------------- *
 * Classe d'armure *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_self_0~ BEGIN
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

DEFINE_PATCH_MACRO ~opcode_target_probability_0~ BEGIN
	LOCAL_SPRINT versus ~~
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == AC_MOD_TYPE_set_base BEGIN
		// xx% de chance de faire passer la classe d'armure de la cible [contre les] à yy [pendant ...]
		PATCH_WARN "%SOURCE_FILE% : opcode_target_probability_0 pourcentage d'armure de la cible à gérer"
	END
	ELSE BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%value%~ RET value END
		PATCH_IF parameter2 != AC_MOD_TYPE_all BEGIN
			SET strref = 102020 + parameter2
			SPRINT versus (AT ~strref~) // ~contre les xxx~
			SPRINT value ~%value% %versus%~
		END
	END

	SPRINT description @102134 // ~%probability% de chance de modifier la classe d'armure de la cible de %value%~
	PATCH_WARN "%description%"
END

/* ----------------- *
 * Attaque par round *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_1~ BEGIN
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

/* --------------------- *
 * State: Berserking [3] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_3~ BEGIN
	SPRINT description @102197 // ~Rage berserk permanente~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_3~ BEGIN
	SPRINT description @102166 // ~%probability%  de chance de provoquer Rage berserk chez le porteur~
END

/* -------- *
 * Charisme *
 * -------- */
DEFINE_PATCH_MACRO ~opcode_self_6~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101081 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Charisme~
END

/* ------------ *
 * Constitution *
 * ------------ */
DEFINE_PATCH_MACRO ~opcode_self_10~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101080 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Constitution~
END

/* ------ *
 * Dégâts *
 * ------ */
DEFINE_PATCH_MACRO ~opcode_target_12~ BEGIN
	LPM ~opcode_12_common~
	PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
		SPRINT value @102092 // ~Inflige %damage% %damageType% supplémentaires~
		SPRINT name @102001
		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END

/* -------------------- *
 * Dégâts - Probabilité *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_probability_12~ BEGIN
	LPM ~opcode_12_common~
	PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @102224 // ~%probability% de chance d'infliger %damage% %damageType% au porteur~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_12~ BEGIN
	LPM ~opcode_12_common~
	PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @102091 // ~%probability% de chances d'infliger %damage% %damageType% supplémentaires~
	END
END

/* -------------------------- *
 * Dégâts - Traitement commun *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_12_common~ BEGIN
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
END

/* ------------------------------ *
 * Mort instantanée - Probabilité *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_target_13~ BEGIN
	SPRINT description @102222 // ~Tue instantanément la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_13~ BEGIN
	SPRINT description @102124 // ~%probability% de chance de tuer instantanément la cible~
END

/* ----------------------------- *
 * Stat: Dexterity Modifier [15] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_15~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101078 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dextérité~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_15~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT description @102225 // ~%probability% de chance de modifier la dextérité de la cible de %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10010 // ~Passe à %value%~
		SPRINT description @102226 // ~%probability% de chance de passer la dextérité de la cible à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT value @10006 // ~Multiplié par %value%~
		SPRINT description @102227 // ~%probability% de chance de multiplier la dextérité de la cible par %value%~
	END
END

/* ----------------- *
 * State: Haste [16] *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_16~ BEGIN
	SPRINT description @102214 // ~Hâte permanente~
END

/* ----------------------------- *
 * Modification de points de vie *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_17~ BEGIN
	LOCAL_SET value = parameter1 + diceCount
	PATCH_IF parameter1 != 0 BEGIN
		PATCH_IF value > 0 BEGIN
			PATCH_IF value == 1 BEGIN
				SPRINT description @102097 // ~Rend un point de vie au porteur~
			END
			ELSE BEGIN
				SPRINT description @102098 // ~Rend %value% points de vie au porteur~
			END
		END
		ELSE PATCH_IF value < 0 BEGIN
			PATCH_IF value == ~-1~ BEGIN
				SPRINT description @102099 // ~Inflige un point de vie au porteur~
			END
			ELSE BEGIN
				SPRINT description @102100 // ~Inflige %value% points de vie au porteur~
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_17~ BEGIN
	LOCAL_SET value = parameter1 + diceCount
	PATCH_IF parameter1 != 0 BEGIN
		PATCH_IF value > 0 BEGIN
			PATCH_IF value == 1 BEGIN
				SPRINT description @102130 // ~Rend un point de vie à la cible~
			END
			ELSE BEGIN
				SPRINT description @102131 // ~Rend %value% points de vie à la cible~
			END
		END
		ELSE PATCH_IF value < 0 BEGIN
			PATCH_IF value == ~-1~ BEGIN
				SPRINT description @102132 // ~Inflige un point de vie à la cible~
			END
			ELSE BEGIN
				SPRINT description @102133 // ~Inflige %value% points de vie à la cible~
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_party_17~ BEGIN
	LOCAL_SET value = parameter1 + diceCount
	PATCH_IF parameter1 != 0 BEGIN
		PATCH_IF value > 0 BEGIN
			PATCH_IF value == 1 BEGIN
				SPRINT description @102215 // ~Rend un point de vie au groupe~
			END
			ELSE BEGIN
				SPRINT description @102216 // ~Rend %value% points de vie au groupe~
			END
		END
		ELSE PATCH_IF value < 0 BEGIN
			PATCH_IF value == ~-1~ BEGIN
				SPRINT description @102217 // ~Inflige un point de vie au groupe~
			END
			ELSE BEGIN
				SPRINT description @102218 // ~Inflige %value% points de vie au groupe~
			END
		END
	END
END

/* ------------------------------ *
 * Stat: Maximum HP Modifier [18] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_18~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative OR parameter2 == 3 BEGIN
		LPF ~signed_value~ INT_VAR value = ~%parameter2%~ RET value END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat OR parameter2 == 4 BEGIN
		SPRINT value @10010 // ~Passe à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT value @10006 // ~Multiplié par %value%~
	END

	SPRINT name @102168 // ~Points de vie~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

/* ------------ *
 * Intelligence *
 * ------------ */
DEFINE_PATCH_MACRO ~opcode_self_19~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101077 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Intelligence~
END

/* ----------------------- *
 * Invisibilité permanente *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_20~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @102111 // ~Invisibilité permanente~
	END
	ELSE BEGIN
		SPRINT description @102112 // ~Invisibilité améliorée permanente~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_20~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @102231 // ~Invisibilité~
	END
	ELSE BEGIN
		SPRINT description @102232 // ~Invisibilité améliorée~
	END
END

/* ------------------------ *
 * Stat: Lore Modifier [21] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_21~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102172 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Connaissance~
END

/* ------ *
 * Chance *
 * ------ */
DEFINE_PATCH_MACRO ~opcode_self_22~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101075 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Chance~
END

/* -------------------- *
 * Immunité à l'horreur *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_23~ BEGIN
	SPRINT description @102039 // ~Immunité à l'horreur~
END

/* ------------------ *
 * State: Horror [24] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_target_24~ BEGIN
	SPRINT description @102148 // ~Inflige Horreur à la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_24~ BEGIN
	SPRINT description @102167 // ~%probability% de chance d'infliger Horreur à la cible~
END

/* ------------------ *
 * State: Poison [25] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_target_25~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF (parameter2 == 0 AND amount != 0) OR (parameter2 == 1 AND amount > 1) BEGIN
		SPRINT description @102160 // ~Empoisonne la cible et lui inflige 1 point de dégât par seconde~
	END
	ELSE PATCH_IF parameter2 == 2 BEGIN
		SPRINT description @102161 // ~Empoisonne la cible et lui inflige %amount% points de dégâts par seconde~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SPRINT description @102162 // ~Empoisonne la cible et lui inflige 1 point de dégât toutes les %amount% secondes~
	END
	ELSE PATCH_IF parameter2 == 4 BEGIN
		SET amount = 3
		SPRINT description @102161 // ~Empoisonne la cible et lui inflige %amount% points de dégâts par seconde~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_25~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF (parameter2 == 0 AND amount != 0) OR (parameter2 == 1 AND amount > 1) BEGIN
		SPRINT description @102190 // ~Empoisonne la cible et lui inflige 1 point de dégât par seconde~
	END
	ELSE PATCH_IF parameter2 == 2 BEGIN
		SPRINT description @102191 // ~Empoisonne la cible et lui inflige %amount% points de dégâts par seconde~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SPRINT description @102192 // ~Empoisonne la cible et lui inflige 1 point de dégât toutes les %amount% secondes~
	END
	ELSE PATCH_IF parameter2 == 4 BEGIN
		SET amount = 3
		SPRINT description @102191 // ~Empoisonne la cible et lui inflige %amount% points de dégâts par seconde~
	END
END

/* ----------------------------------- *
 * Stat: Acid Resistance Modifier [27] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_27~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102055 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à l'acide~
END

/* ------------------- *
 * Résistance au froid *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_self_28~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102059 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance au froid~
END

/* -------------------------- *
 * Résistance à l'électricité *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_29~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102057 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à l'électricité
END

/* ----------------- *
 * Résistance au feu *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_30~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102056 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance au feu~
END

/* ------------------------------ *
 * Résistance aux dégâts magiques *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_31~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102065 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts magiques~
END

/* -------------------------------------------------------------- *
 * Jets de sauvegarde contre la paralysie, la mort et les poisons *
 * -------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_33~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102029 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre la paralysie, la mort et les poisons~
END

DEFINE_PATCH_MACRO ~opcode_party_33~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102029 STR_VAR value = EVAL ~%parameter1%~ group = 1 RET description END // ~contre la paralysie, la mort et les poisons~
	PATCH_PRINT ~%description%~
END

/* ------------------------------------------------------------------- *
 * Jets de sauvegarde contre les baguettes, les sceptres et les bâtons *
 * ------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_34~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102030 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les baguettes, les sceptres et les bâtons~
END

/* ------------------------------------------------------------- *
 * Jets de sauvegarde contre la pétrification et la métamorphose *
 * ------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_35~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102031 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre la pétrification et la métamorphose~
END

/* -------------------------------------- *
 * Jets de sauvegarde contre les souffles *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_36~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102032 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les souffles~
END

/* ----------------------------------- *
 * Jets de sauvegarde contre les sorts *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_37~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102033 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les sorts~
END

/* ------------------ *
 * Rendre inconscient *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_target_39~ BEGIN
	SPRINT description @102139 // ~Assome la cible~
	/*PATCH_IF abilityType == AbilityType_Combat BEGIN
		SPRINT description @102096 // ~%description% à chaque attaque réussie~
	END*/
END

DEFINE_PATCH_MACRO ~opcode_target_probability_39~ BEGIN
	SPRINT description @102135 // ~%probability% de chance d'assommer la cible~
END

/* ------------------ *
 * State: Slow [40] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_target_40~ BEGIN
	SPRINT description @102175 // ~Inflige Lenteur à la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_40~ BEGIN
	SPRINT description @102189 // ~%probability% de chance d'infliger Lenteur à la cible~
END

/* ----------------------------- *
 * Mémorisation de sort profanes *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_42~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET level = parameter2

	LPF ~opcode_self_42_62~ INT_VAR level amount startStrref = 102085 RET description END
END

/* ----- *
 * Force *
 * ----- */
DEFINE_PATCH_MACRO ~opcode_self_44~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101076 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force~
END

/* ----------------- *
 * Etourdir la cible *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_target_45~ BEGIN
	SPRINT description @102123 // ~Chaque attaque réussie étourdi la cible~
END

/* --------------------------- *
 * Chances d'étourdir la cible *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_probability_45~ BEGIN
	SPRINT description @102120 // ~%probability% de chances d'étourdir la cible~
END

/* ------- *
 * Sagesse *
 * ------- */
DEFINE_PATCH_MACRO ~opcode_self_49~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101079 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Sagesse~
END

/* ---- *
 * TAC0 *
 * ---- */
DEFINE_PATCH_MACRO ~opcode_self_54~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102000 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_54~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT description @102219 // ~%probability% de chance de modifier le TAC0 de la cible de %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10010 // ~Passe à %value%~
		SPRINT description @102220 // ~%probability% de chance de passer le TAC0 de la cible à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT value @10006 // ~Multiplié par %value%~
		SPRINT description @102221 // ~%probability% de chance de multiplier le TAC0 de la cible par %value%~
	END
END

/* ------------------------------------------------------ *
 * Tue les créatures de type xx de yy dés de vie ou moins *
 * ------------------------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_target_55~ BEGIN
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

/* ---------------------- *
 * Inversion d'alignement *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_56~ BEGIN
	SPRINT description @102138 // ~Inverse l'alignement du porteur~
END

/* ------------------------- *
 * Modification d'alignement *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_57~ BEGIN
	LOCAL_SET alignment = ~%parameter2%~
	LOCAL_SPRINT chaotic @101000
	LOCAL_SPRINT lawful @101004
	LOCAL_SPRINT neutral @101003
	LOCAL_SPRINT good @101002
	LOCAL_SPRINT evil @101001
	LOCAL_SPRINT trueNeutral @101091

	PATCH_IF alignment == 17 BEGIN SPRINT alignment ~%lawful% %good%~ END
	ELSE PATCH_IF alignment == 18 BEGIN SPRINT alignment ~%lawful% %neutral%~ END
	ELSE PATCH_IF alignment == 19 BEGIN SPRINT alignment ~%lawful% %evil%~ END
	ELSE PATCH_IF alignment == 33 BEGIN SPRINT alignment ~%neutral% %good%~ END
	ELSE PATCH_IF alignment == 34 BEGIN SPRINT alignment ~%trueNeutral%~ END
	ELSE PATCH_IF alignment == 35 BEGIN SPRINT alignment ~%neutral% %evil%~ END
	ELSE PATCH_IF alignment == 49 BEGIN SPRINT alignment ~%chaotic% %evil%~ END
	ELSE PATCH_IF alignment == 50 BEGIN SPRINT alignment ~%chaotic% %evil%~ END
	ELSE PATCH_IF alignment == 51 BEGIN SPRINT alignment ~%chaotic% %evil%~ END

	SPRINT description @102116 // ~Le porteur voit son alignement modifié à %alignment%~
END

/* --------- *
 * Furtivité *
 * --------- */
DEFINE_PATCH_MACRO ~opcode_self_59~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102073 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Furtivité~
END

/* ------------------------ *
 * Stat: Miscast Magic [60] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_60~ BEGIN
	LOCAL_SET percentChance = parameter1
	LOCAL_SET type = parameter2

	PATCH_IF percentChance == 100 BEGIN
		PATCH_IF type == 0 OR type== 3 BEGIN
			SPRINT description @102228 // ~Empêche de lancer des sorts profanes~
		END
		ELSE PATCH_IF type == 1 OR type== 4 BEGIN
			SPRINT description @102229 // ~Empêche de lancer des sorts divins~
		END
		ELSE PATCH_IF type == 2 OR type== 5 BEGIN
			SPRINT description @102230 // ~Empêche de lancer des sorts innés~
		END
	END
	ELSE BEGIN
		PATCH_WARN "%SOURCE_FILE% : opcode_target_60 pourcentage plus petit que 100 à gérer"
	END
END

DEFINE_PATCH_MACRO ~opcode_target_60~ BEGIN
	LOCAL_SET percentChance = parameter1
	LOCAL_SET type = parameter2

	PATCH_IF percentChance == 100 BEGIN
		PATCH_IF type == 0 OR type== 3 BEGIN
			SPRINT description @102163 // ~Empêche la cible de lancer des sorts profanes~
		END
		ELSE PATCH_IF type == 1 OR type== 4 BEGIN
			SPRINT description @102164 // ~Empêche la cible de lancer des sorts divins~
		END
		ELSE PATCH_IF type == 2 OR type== 5 BEGIN
			SPRINT description @102165 // ~Empêche la cible de lancer des sorts innés~
		END
	END
	ELSE BEGIN
		PATCH_WARN "%SOURCE_FILE% : opcode_target_60 pourcentage plus petit que 100 à gérer"
	END
END

/* -------------------------- *
 * Mémorisation de sort divin *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_62~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET level = parameter2

	LPF ~opcode_self_42_62~ INT_VAR level amount startStrref = 102080 RET description END
END

/* ---------------------- *
 * Infravision permanente *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_63~ BEGIN
	SPRINT description @102077 // ~Infravision permanente~
END

/* -------------- *
 * Flou permanent *
 * -------------- */
DEFINE_PATCH_MACRO ~opcode_self_65~ BEGIN
	SPRINT description @102078 // ~Flou permanent~
END

/* ------------------------------- *
 * Summon: Creature Summoning [67] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_67~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
	SPRINT description @102173 // ~Invoque une créature (%creatureName%)~
END

/* ------------------------ *
 * Non-détection permanente *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_69~ BEGIN
	SPRINT description @102117 // ~Non-détection permanente~
END

/* --------------- *
 * Sex Change [71] *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_self_71~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @102195 // ~Change le sexe du porteur~
	END
	ELSE BEGIN
		/*1 MALE
		2 FEMALE*/
		PATCH_WARN "%SOURCE_FILE% : Fixation du genre à gérer"
	END
END

/* ------ *
 * Dégâts *
 * ------ */
DEFINE_PATCH_MACRO ~opcode_self_73~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts~
END

/* ----------- *
 * Aveuglement *
 * ----------- */
DEFINE_PATCH_MACRO ~opcode_target_74~ BEGIN
	SPRINT description @102137 // ~Chaque attaque réussie aveugle la cible~
END

/* -------------------- *
 * Cure: Blindness [75] *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_target_75~ BEGIN
	SPRINT description @102144 // ~Guérison de la cécité~
END

/* --------------------------- *
 * Cure: Feeblemindedness [77] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_77~ BEGIN
	SPRINT description @102146 // ~Guérison de la faiblesse mentale~
END

/* ------------------- *
 * State: Disease [78] *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_target_78~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET type = parameter2

	PATCH_IF type >= 4 AND type <= 9 BEGIN
		PATCH_IF amount > 0 BEGIN
			SET strref = 102197 + type
			SPRINT description (AT ~%strref%~) //  ~Inocule une maladie qui diminue [la caractéristique] de la cible de %amount%~
		END
		ELSE BEGIN
			SET amount *= ~-1~
			SET strref = 102204 + type
			SPRINT description (AT ~%strref%~) //  ~Inocule une maladie qui augmente [la caractéristique] de la cible de %amount%~
		END
	END
	ELSE PATCH_IF type == 0 OR type == 1 OR (type == 3 AND amount == 1) BEGIN
		SPRINT description @102198 // ~Inocule une maladie qui inflige 1 point de dégâts par seconde à la cible~
	END
	ELSE PATCH_IF type == 2 BEGIN
		SPRINT description @102199 // ~Inocule une maladie qui inflige %amount% points de dégâts par seconde à la cible~
	END
	ELSE PATCH_IF type == 3 BEGIN
		SPRINT description @102200 // ~Inocule une maladie qui inflige 1 point de dégâts toutes les %amount% secondes à la cible~
	END
	ELSE PATCH_IF type == 10 BEGIN
		SPRINT description @102207 // ~Inocule une maladie qui ralenti la cible~
	END
END

/* ------------------ *
 * Cure: Disease [79] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_target_79~ BEGIN
	SPRINT description @102143 // ~Guérison des maladies~
END

/* ------------------- *
 * Cure: Deafness [81] *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_target_81~ BEGIN
	SPRINT description @102145 // ~Guérison de la surdité~
END

/* ------------------------------------- *
 * Immunité contre un type de projectile *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_83~ BEGIN
	PATCH_MATCH parameter2 WITH
		~64~ BEGIN SPRINT description @102125 END // = ~Immunité aux attaques de regard~
		DEFAULT PATCH_WARN "%SOURCE_FILE% : Opcode %opcode% : Type de projectile '%parameter2%' à gérer"
    END
END

/* ------------------------------------- *
 * Résistance aux dégâts de feu magiques *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_84~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102066 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts de feu magiques~
END

/* --------------------------------------- *
 * Résistance aux dégâts de froid magiques *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_85~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102067 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts de froid magiques~
END

/* -------------------------------- *
 * Résistance aux dégâts tranchants *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_86~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102061 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts tranchants~
END

/* -------------------------------- *
 * Résistance aux dégâts contondants *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_87~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102062 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts contondants~
END

/* -------------------------------- *
 * Résistance aux dégâts perforants *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_88~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102063 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts perforants~
END

/* ------------------------------------ *
 * Résistance aux dégâts de projectiles *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_89~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102064 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts de projectiles~
END

/* ------------------------------ *
 * Stat: Open Locks Modifier [90] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_90~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102071 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Crochetage de serrures~
END

/* ------------------------------ *
 * Stat: Find Traps Modifier [91] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_91~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102072 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Détection/désamorçage des pièges~
END

/* -------------------------------- *
 * Stat: Pick Pockets Modifier [92] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_92~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102070 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Vol à la tire~
END

/* ------- *
 * Fatigue *
 * ------- */
DEFINE_PATCH_MACRO ~opcode_self_93~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102136 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Fatigue~
END

/* ---------------------------------- *
 * Stat: Strength-Bonus Modifier [97] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_97~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101087 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force exceptionnelle~
END

/* ------------------------------ *
 * Régénération des points de vie *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_98~ BEGIN
	LOCAL_SET value = parameter1

	PATCH_IF parameter2 == 0 OR parameter2 == 2 BEGIN
		PATCH_IF value == 1 BEGIN
			SPRINT description @102101 // ~Régénère 1 point de vie par seconde~
		END
		ELSE BEGIN
			SPRINT description @102102 // ~Régénère %value% points de vie par seconde~
		END
	END
	ELSE PATCH_IF parameter2 == 1 BEGIN
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102104 // ~Régénère %value% des points de vie~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SPRINT description @102103 // ~Régénère 1 point de vie tous les %value% secondes~
	END
	ELSE BEGIN
		SPRINT description @102105 // ~Régénère 3 points de vie tous les %value% secondes~
	END
END

/* ------------------------------------- *
 * Protection contre un type de créature *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_100~ BEGIN
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
END

/* -------------------------------------- *
 * Immunité contre les sorts de niveau xx *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_102~ BEGIN
	LOCAL_SET spellLevel = ~%parameter1%~
	SPRINT description @102118 // ~Immunité contre les sorts de niveau %spellLevel%~
END

/* ----- *
 * Moral *
 * ----- */
DEFINE_PATCH_MACRO ~opcode_self_106~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102110 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Moral~
END

/* --------------------------------- *
 * Paralyse les créatures de type xx *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_109~ BEGIN
	LPM ~opcode_target_109~
END

DEFINE_PATCH_MACRO ~opcode_target_109~ BEGIN
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

/* --------------------------------- *
 * Cure: (Remove) Invisibility [116] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_116~ BEGIN
	SPRINT description @102223 // ~Dissipe toutes formes d'invisibilité~
END

/* ------------------------------------ *
 * Protection: from Melee Weapons [120] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_120~ BEGIN
	LOCAL_SET enchantment = parameter1
	LOCAL_SET type = parameter2

	PATCH_IF type == 0 OR type == 1 BEGIN SPRINT weaponType @102178 END // ~armes de mêlée magiques~
	ELSE PATCH_IF type == 2 BEGIN SPRINT weaponType @102179 END // ~armes de mêlée non-magiques~
	ELSE PATCH_IF type == 3 BEGIN SPRINT weaponType @102180 END // ~armes de mêlée en argent~
	ELSE PATCH_IF type == 6 BEGIN SPRINT weaponType @102181 END // ~armes de mêlée à 2 mains~
	ELSE PATCH_IF type == 7 BEGIN SPRINT weaponType @102182 END // ~armes de mêlée à 1 main~
	ELSE PATCH_IF type == 8 BEGIN SPRINT weaponType @102183 END // ~armes de mêlée maudites~
	ELSE PATCH_IF type == 98 BEGIN SPRINT weaponType @102184 END // ~armes de mêlée non-maudites~
	ELSE BEGIN
		PATCH_WARN "%SOURCE_FILE% : Type d'arme %type% à gérer"
	END

	PATCH_IF type == 0 BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%enchantment%~ RET enchantment = value END
		SPRINT description @102176 // ~Immunité contre les %weaponType% %enchantment%~
	END
	ELSE PATCH_IF type == 1 BEGIN
        SPRINT description @102177 // ~Immunité contre les %weaponType%~
    END
END

/* --------------------- *
 * Capacité de mouvement *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_126~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102115 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Capacité de mouvement~
END

DEFINE_PATCH_MACRO ~opcode_target_126~ BEGIN
	LPF ~opcode_target_mod~ INT_VAR strref = 102115 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Capacité de mouvement~
END

/* ------------------ *
 * State: Bless [130] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_130~ BEGIN
    SPRINT description @102196 // ~Bénédiction permanente~
END

/* ---------------------------- *
 * Empêcher de lancer des sorts *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_145~ BEGIN
	LOCAL_SET spellType = ~%parameter2%~

	PATCH_IF spellType == 0 BEGIN SPRINT description @102127 END // ~Empêche de lancer des sorts profanes~
	PATCH_IF spellType == 1 BEGIN SPRINT description @102128 END // ~Empêche de lancer des sorts divins~
	PATCH_IF spellType == 2 BEGIN SPRINT description @102129 END // ~Empêche de lancer des sorts innés~
END

/* -------------- *
 * Lancer un sort *
 * -------------- */
DEFINE_PATCH_MACRO ~opcode_self_146~ BEGIN
	LPM ~opcode_target_146~
END

DEFINE_PATCH_MACRO ~opcode_target_146~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET description = spellName END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 BEGIN
		SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
		SPRINT description ~'%description%' (%castingLevelStr%)~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_146~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @102185 // ~%probability% de chance de lancer le sort %spellName%~

		PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 BEGIN
			SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
			SPRINT description ~'%description%' (%castingLevelStr%)~
		END
	END
	ELSE BEGIN
		PATCH_WARN "%SOURCE_FILE% : opcode_target_probability_146 nom du sort introuvable pour %resref%"
	END
END

/* ---------------------------------- *
 * Spell: Cast Spell (at Point) [148] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_probability_148~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @102193 // ~%probability% de chance de lancer le sort %spellName% sur le porteur~

		PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 BEGIN
			SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
			SPRINT description ~'%description%' (%castingLevelStr%)~
		END
	END
	ELSE BEGIN
		PATCH_WARN "%SOURCE_FILE% : opcode_self_probability_148 nom du sort introuvable pour %resref%"
	END
END

/* --------------------- *
 * State: Entangle [154] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_target_154~ BEGIN
	SPRINT description @102241 // ~Enchevêtre la cible~
END

/* ---------------- *
 * Cure: Fear [161] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_161~ BEGIN
	SPRINT description @102038 // ~Immunité à la peur~
END

/* ---------------- *
 * Cure: Hold [162] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_162~ BEGIN
	SPRINT description @102233 // ~Immunité à la paralysie~
END

/* ----------------------------- *
 * Protection: Free Action [163] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_163~ BEGIN
	SPRINT description @102234 // ~Action libre~
END

/* --------------------- *
 * Résistance à la magie *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_166~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102060 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à la magie~
END

/* ------------------------------------- *
 * Stat: THAC0 Modifier with Missile Weapons [167] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_167~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102235 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 des armes à projectiles~
END

/* -------------------- *
 * Résistance au poison *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_173~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102058 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance au poison~
END

/* --------------------------------- *
 * Paralyse les créatures de type xx *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_175~ BEGIN
	LPM ~opcode_109~
END

/* --------------------- *
 * Capacité de mouvement *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_176~ BEGIN
	LPM ~opcode_self_126~
END

/* -------------------------------- *
 * Applique un effet à une creature *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_177~ BEGIN
	LPM ~opcode_target_177~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_177~ BEGIN
	LPM ~opcode_target_177~
END

DEFINE_PATCH_MACRO ~opcode_target_177~ BEGIN
	// TODO: Effect utilise aussi des opcodes, créer une fonction qui va générer une description pour chaque opcode de l'effet
	// comme pour les autres tout simplement !
	// Sauf que attention, le opcode 177 peut avoir un js, et l'effet avoir plusieurs opcode ayant chacun leur JS !!
	// Un truc dans le genre dans les plus complexes ? (et si l'effet utilise un autre effet ? ce qui théoriquezment est possible...) Gérer une indentation ?
	// - 13% de chance d'infliger effet 11 (JS contre xx pour annuler)
	//   Inflige un truc à la cible (JS contre yy pour annuler)
	//   50% d'enflammer
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
	PATCH_WARN "%SOURCE_FILE%: opcode 177 à gérer %idsFile%"
	// Applique un effet à une creature
END

/* --------------------------------- *
 * Paralyse les créatures de type xx *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_185~ BEGIN
	LPM ~opcode_109~
END

/* --------------------------------- *
 * Stat: Casting Time Modifier [189] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_189~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102169 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Vitesse d'incantation~
END

/* ------------------ *
 * Facteur de vitesse *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_190~ BEGIN
	LPF ~signed_value~ INT_VAR value = EVAL ~%parameter1%~ RET value END
	SPRINT name @102002 //~Facteur de vitesse~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

/* ----------------------------------- *
 * Spell: Casting Level Modifier [191] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_191~ BEGIN
	LOCAL_SET value = parameter1

	PATCH_IF parameter2 == 0 BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 102170 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Niveau de lanceur de sorts profanes~
	END
	ELSE BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 102171 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Niveau de lanceur de sorts divins~
	END
END

/* ------------------------------ *
 * Spell: Bounce Projectile [197] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_197~ BEGIN
	PATCH_MATCH parameter2 WITH
		~64~ BEGIN SPRINT description @102147 END // = ~Réfléchit les attaques de regard~
		DEFAULT PATCH_WARN "%SOURCE_FILE% : Opcode %opcode% : Réflection du Type de projectile '%parameter2%' à gérer"
    END
END

/* ------------------------------------------- *
 * Spell: Protection from Spell (School) [204] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_204~ BEGIN
	LOCAL_SET school = parameter2
	LOCAL_SET strref = 102150

	PATCH_IF school == 0 BEGIN
		PATCH_WARN "%SOURCE_FILE% : opcode_self_204 école 0 à gérer"
	END
	ELSE BEGIN
		SET strref += school
		SPRINT description (AT ~%strref%~) //  ~Immunité aux sorts de l'école de xxxx~
	END
END

/* ------------------ *
 * Immunité à un sort *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_206~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF ~%spellName%~ STRING_EQUAL ~~ BEGIN
		PATCH_WARN ~%SOURCE_FILE% : Opcode %opcode% : Aucune chaine trouvee pour le sort '%resref%'~
	END
	ELSE BEGIN
		SPRINT description @102035 // ~Immunité à %spellName%~
	END
END

/* --------------------- *
 * Points de vie minimum *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_208~ BEGIN
	SPRINT value ~%parameter1%~
	SPRINT description @102109 // ~Les points de vie ne peuvent passer en dessous de %value%~
END

/* ----------------------------------- *
 * Lancer un sort parmis une sélection *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_214~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @102106 //  ~Permet de lancer n'importe quel sort de son livre de sorts~
	END
	ELSE BEGIN
		PATCH_WARN  ~%SOURCE_FILE% : Opcode %opcode% : Lire les sorts utilisables depuis le fichier 2da %resref%~
	END
END

/* --------------- *
 * Drain de niveau *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_target_216~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102113 // ~Chaque attaque réussie draine un niveau à la cible~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @102114 // ~Chaque attaque réussie draine %amount% niveaux à la cible~
	END
	ELSE BEGIN
		PATCH_WARN ~%SOURCE_FILE% : Opcode %opcode% : Niveau draine negatif !!~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_216~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102141 // ~%probability% de chance de draîner un niveau à la cible~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @102142 // ~%probability% de chance de draîner %amount% niveaux à la cible~
	END
	ELSE BEGIN
		PATCH_WARN ~%SOURCE_FILE% : Opcode %opcode% : Niveau draine negatif !!~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_216~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102186 // ~%probability% de chance de draîner un niveau au porteur~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @102187 // ~%probability% de chance de draîner %amount% niveaux au porteur~
	END
	ELSE BEGIN
		PATCH_WARN ~%SOURCE_FILE% : Opcode %opcode% : Niveau draine negatif !!~
	END
END

/* ----------------------------------------- *
 * Stat: AC vs. Creature Type Modifier [219] *
 * ----------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_219~ BEGIN
	//Parameter #1: IDS Entry
    //Parameter #2: IDS File
	//LPF ~opcode_mod~ INT_VAR strref = 101076 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force~
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~ids_files~ BEGIN
		2 => ~Object.IDS~
		3 => ~General.ids~
		4 => ~Race.ids~
		5 => ~Class.ids~
		7 => ~Gender.ids~
		8 => ~Align.ids~
	END
	PATCH_PHP_EACH ids_files AS k => file BEGIN
	END
	SPRINT idsFile $ids_files(~%parameter2%~)
	PATCH_WARN "%SOURCE_FILE%: opcode_self_219 à gérer %idsFile%"
END

DEFINE_PATCH_MACRO ~opcode_self_220~ BEGIN
	LOCAL_SET school = parameter2

	PATCH_IF school > 0 BEGIN
		// Dissipe tous les sorts de l'école de %school% de niveau %level% et moins
		PATCH_WARN "%SOURCE_FILE% : opcode_self_220 à gérer"
	END
END

/* ------------------- *
 * Compétence martiale *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_self_233~ BEGIN
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

DEFINE_PATCH_MACRO ~opcode_target_probability_233~ BEGIN
	LOCAL_SET value = ~%parameter1%~
	LOCAL_SPRINT proficiency ~~

	SPRINT description ~~

	PATCH_IF VARIABLE_IS_SET $tra_proficiencies(~%parameter2%~)  BEGIN
		SPRINT value @10010 // ~Passe à %value%~
		TO_LOWER value
		SPRINT proficiency $tra_proficiencies(~%parameter2%~)
		SPRINT value ~%proficiency% %value%~
		SPRINT description @102188 // ~%probability% de passer la compétence martiale de la cible à %value%~
	END
END

/* ------------------------------- *
 * Spell Effect: Wing Buffet [235] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_probability_235~ BEGIN
	SPRINT description @102174 // ~%probability% de chance de renverser et sonner la cible~
END

/* ------------------------- *
 * Death: Disintegrate [238] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_probability_238~ BEGIN
	SPRINT description @102194 // ~%probability% de chance de désintégrer la cible~
END

/* --------------- *
 * Champ de vision *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_self_262~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF value < 0 BEGIN
		PATCH_WARN ~%SOURCE_FILE% : Opcode %opcode% : Valeur negative pour le champ de vision a gerer~
	END
	ELSE BEGIN
		SPRINT value $feets_to_meters(~%value%~)
		PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
			SPRINT value ~+%value%~
		END
		ELSE BEGIN
			SPRINT value @10010 // ~Passe à %value%~
		END
		SPRINT name @102119 // ~Champ de vision~
		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END

/* ---------------------------------- *
 * Multiplicateur d'attaque sournoise *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_263~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102006 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Multiplicateur d'attaque sournoise~
END

/* ---------------------------------- *
 * Multiplicateur d'attaque sournoise *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_263~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102006 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Multiplicateur d'attaque sournoise~
END

/* -------------- *
 * Zone d'air pur *
 * -------------- */
DEFINE_PATCH_MACRO ~opcode_self_273~ BEGIN
	SPRINT description @102140 // ~Zone d'air pur~
END

/* ----------------------- *
 * Camouflage dans l'ombre *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_275~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102074 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Camouflage dans l'ombre~
END

/* ------------------------------------ *
 * Stat: Detect Illusion Modifier [276] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_276~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102075 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Détection des illusions~
END

/* ------------------------------ *
 * Stat: Set Traps Modifier [277] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_277~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102076 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Pose des pièges~
END

/* -------------------------------------------- *
 * Chance de toucher (Agis sur le TAC0 modifié) *
 * -------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_278~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102036 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Chances de toucher~
END

/* -------------------------------------------- *
 * Chance de toucher (Agis sur le TAC0 modifié) *
 * -------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_278~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102036 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Chances de toucher~
END


/* ---------------------------------- *
 * Déclenchement de hiatus entropique *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_280~ BEGIN
	PATCH_IF abilityType == AbilityType_Charge BEGIN
		PATCH_IF parameter2 == 1 BEGIN
			SPRINT description @102107 // ~Le prochain sort lancé déclenche automatiquement un hiatus entropique~
		END
		ELSE BEGIN
			PATCH_WARN ~%SOURCE_FILE% : Opcode %opcode% : A gerer pour capacite de charge et parameter2 = %parameter2% (etrange)~
		END
	END
	ELSE BEGIN
		SPRINT description @102108 // ~Tous sorts lancés déclenchent automatiquement un hiatus entropique~
	END
END

/* ----------------- *
 * Hiatus entropique *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_281~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102079 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Hiatus entropique~
END

/* -------------------------------- *
 * Stat: Melee THAC0 Modifier [284] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_284~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102237 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 des armes de mêlée~
END

/* ---------------------------------------- *
 * Stat: Melee Weapon Damage Modifier [285] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_285~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102238 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts des armes de mêlée~
END

/* ------------------------------------------ *
 * Stat: Missile Weapon Damage Modifier [286] *
 * ------------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_286~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102236 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts des armes à projectiles~
END

/* ------------------------------- *
 * Stat: Fist THAC0 Modifier [288] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_288~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102239 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 des poings~
END

/* -------------------------------- *
 * Stat: Fist Damage Modifier [289] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_289~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102240 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts des poings~
END

/* -------------------------------- *
 * Immunité aux attaques sournoises *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_292~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @102037 // ~Immunité aux attaques sournoises~
	END
END

/* ------------------------ *
 * Chances de coup critique *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_301~ BEGIN
	LPF ~percent_value~ INT_VAR value = EVAL ~%parameter1%~ * 5 RET probability = value END
	SPRINT description @102093 // ~%probability% de chance d'infliger un coup critique~
END

/* ------------------------------------- *
 * Stat: THAC0 Modifier (Off-Hand) [305] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_305~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102010 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 de la main secondaire~
END

DEFINE_PATCH_MACRO ~opcode_mod_base~ BEGIN
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
END

DEFINE_PATCH_FUNCTION ~opcode_mod~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	LPM ~opcode_mod_base~

	SPRINT name (AT ~%strref%~)
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_FUNCTION ~opcode_target_mod~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	LPM ~opcode_mod_base~

	SPRINT name (AT ~%strref%~)
	SPRINT target @101085
	SPRINT description @100007 // ~%name% %target%%colon%%value%~
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

DEFINE_PATCH_FUNCTION ~opcode_save_vs~ INT_VAR strref = 0 group = 0 STR_VAR value = ~~ RET description BEGIN
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

	PATCH_IF group == 1 BEGIN
		SPRINT description @101103 // ~%name% (du groupe)%colon%%value%~
	END
	ELSE BEGIN
		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_name~ STR_VAR file = "" RET spellName BEGIN
	SPRINT spellName ~~
	INNER_ACTION BEGIN
		SILENT
		ACTION_IF FILE_EXISTS_IN_GAME ~%file%.spl~ BEGIN
			COPY_EXISTING ~%file%.spl~ ~override~
				READ_LONG SPL_unidentified_name spellNameRef
				PATCH_IF spellNameRef > 0 BEGIN
					READ_STRREF SPL_unidentified_name spellName
				END
				ELSE BEGIN
					PATCH_WARN "%SOURCE_FILE% : Opcode %opcode% : Nom du sort introuvable pour %file%.spl"
				END
			BUT_ONLY_IF_IT_CHANGES
		END
		ELSE BEGIN
			WARN "%SOURCE_FILE% : Opcode %opcode% : La ressource %file%.spl n'existe pas"
		END
        VERBOSE
    END
END

DEFINE_PATCH_FUNCTION ~get_creature_name~ STR_VAR file = "" RET creatureName BEGIN
	SPRINT creatureName ~~
	INNER_ACTION BEGIN
		SILENT
		ACTION_IF FILE_EXISTS_IN_GAME ~%file%.cre~ BEGIN
			COPY_EXISTING ~%file%.cre~ ~override~
				READ_LONG CRE_name spellNameRef
				PATCH_IF spellNameRef > 0 BEGIN
					READ_STRREF CRE_name creatureName
				END
				ELSE BEGIN
					PATCH_WARN "%SOURCE_FILE% : Opcode %opcode% : Nom de la créature introuvable pour %file%.cre"
				END
			BUT_ONLY_IF_IT_CHANGES
		END
		ELSE BEGIN
			WARN "%SOURCE_FILE% : Opcode %opcode% : La ressource %file%.cre n'existe pas"
		END
        VERBOSE
    END
END

DEFINE_PATCH_FUNCTION ~opcode_self_42_62~ INT_VAR level = 0 amount = 0 startStrref = 0 RET description BEGIN
	SPRINT levelStr ~~

	PATCH_IF amount > 32768 BEGIN
		SET amount = amount - 65536
	END

	PATCH_FOR_EACH idx IN 0 1 2 3 4 5 6 7 8 BEGIN
		SET bit = EVAL ~%BIT%idx%%~
		PATCH_IF (level BAND bit) != 0 BEGIN
			SET spellLevel = idx + 1
			SPRINT levelStr ~%levelStr%, %spellLevel%~
		END
	END

	INNER_PATCH_SAVE levelStr ~%levelStr%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~, \([0-9]\)$~ ~ et \1~
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^, ~ ~~
	END

	PATCH_IF level == 0 BEGIN
		SET strref = startStrref + 4
		SPRINT description (AT %strref%) //~Double le nombre de sorts [profanes|divins] de niveau %levelStr% que le personnage peut mémoriser.~
	END
	ELSE PATCH_IF amount > 0 BEGIN // Mémorisation
        PATCH_IF amount == 1 BEGIN
			SET strref = startStrref
            SPRINT description (AT %strref%) // ~Mémorisation d'un sort [profane|divin] supplémentaire de niveau %levelStr%~
        END
        ELSE BEGIN
			SET strref = startStrref + 1
            SPRINT description (AT %strref%) // ~Mémorisation de %amount% sorts [profanes|divins] supplémentaires de niveau %levelStr%~
        END
    END
    ELSE PATCH_IF amount < 0 BEGIN // Oubli
        PATCH_IF amount == ~-1~ BEGIN
			SET strref = startStrref + 2
            SPRINT description (AT %strref%) // ~Oubli d'un sort [profane|divin] de niveau %levelStr%~
        END
        ELSE BEGIN
			SET strref = startStrref + 3
            SPRINT description (AT %strref%) // ~Oubli de %amount% sorts [profanes|divins] de niveau %levelStr%~
        END
	END
END
