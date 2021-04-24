/*
 * Tableau servant à savoir comment trier le résultat final.
 * Vu qu'ils ne sont généralement pas
 */
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~sort_opcodes~ BEGIN
	216 => 1   // Spell Effect: Level Drain [216]
	  0 => 2   // Stat: AC vs. Damage Type Modifier [0]
 219000 => 3   // Stat: AC vs. Creature Type Modifier [219]
	 54 => 4   // Stat: THAC0 Modifier [54]
	178 => 5   // Spell Effect: THAC0 vs. Creature Type Modifier [178]
	284 => 6   // Stat: Melee THAC0 Modifier [284]
	305 => 7   // Stat: THAC0 Modifier (Off-Hand) [305]
	288 => 8   // Stat: Fist THAC0 Modifier [288]
	278 => 9   // Stat: To Hit Modifier [278]
 219001 => 10  // Stat: AC vs. Creature Type Modifier [219]
	 33 => 11  // Stat: Save vs. Death Modifier [33]
	 34 => 12  // Stat: Save vs. Wands Modifier [34]
	 35 => 13  // Stat: Save vs. Petrification/Polymorph Modifier [35]
	 36 => 14  // Stat: Save vs. Breath Weapons Modifier [36]
	 37 => 15  // Stat: Save vs. Spells Modifier [37]
	 12 => 16  // HP: Damage [12]
	 73 => 17  // Stat: Extra Damage Modifier [73]
	179 => 18  // Spell Effect: Damage vs. Creature Type Modifier [179]
	250 => 19  // Spell Effect: Damage Luck Modifier [250]
	285 => 20  // Stat: Melee Weapon Damage Modifier [285]
	286 => 21  // Stat: Missile Weapon Damage Modifier [286]
	289 => 22  // Stat: Fist Damage Modifier [289]
	 25 => 23  // State: Poison [25]
	 78 => 24  // State: Disease [78]
    214 => 25  // Select Spell [214]
    191 => 26  // Spell: Casting Level Modifier [191]
	 42 => 27  // Spell: Wizard Spell Slots Modifier [42]
	 62 => 28  // Spell: Priest Spell Slots Modifier [62]
	145 => 29  // Spell: Disable Spell Casting Abilities [145]
	261 => 30  // Spell: Restore Lost Spells [261]
	244 => 31  // Spell: Drain Wizard Spell [244]
	 99 => 32  // Spell Effect: Duration Modifier [99]
	 96 => 33  // Stat: Level Change [96]
	189 => 34  // Stat: Casting Time Modifier [189]
	 60 => 35  // Stat: Miscast Magic [60]
	190 => 36  // Stat: Attack Speed Factor [190]
	  1 => 37  // Stat: Attacks Per Round Modifier [1]
	 98 => 38  // Stat: Regeneration [98]
	 18 => 39  // Stat: Maximum HP Modifier [18]
	 44 => 40  // Stat: Strength Modifier [44]
	 97 => 41  // Stat: Strength-Bonus Modifier [97]
	 15 => 42  // Stat: Dexterity Modifier [15]
	 10 => 43  // Stat: Constitution Modifier [10]
	 19 => 44  // Stat: Intelligence Modifier [19]
	 49 => 45  // Stat: Wisdom Modifier [49]
	  6 => 46  // Stat: Charisma Modifier [6]
	 22 => 47  // Stat: Luck Modifier [22]
	132 => 48  // State: Raise Strength, Constitution, & Dexterity Non-Cumulative [132]
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
	 93 => 160 // Stat: Fatigue Modifier [93]
	104 => 161 // Stat: Experience Points [104]
	 69 => 162 // Protection: From Detection (Non-Detection) [69]
	156 => 167 // State: Protection from Normal Missiles Cylinder [156]
	153 => 168 // State: Sanctuary [153]
	 16 => 169 // State: Haste [16]
	317 => 169 // State: Haste2 [317]
	130 => 170 // State: Bless [130]
	129 => 171 // State: Aid [129]
	155 => 172 // State: Minor Globe [155]
	 20 => 173 // State: Invisibility [20]
	 65 => 174 // State: Blur [65]
	 63 => 175 // State: Infravision [63]
	 40 => 176 // State: Slow [40]
	  3 => 177 // State: Berserking [3]
	 24 => 178 // State: Horror [24]
	 74 => 179 // State: Blindness [74]
	 45 => 180 // State: Stun [45]
	165 => 180 // Spell Effect: Pause Target [165]
	154 => 182 // State: Entangle [154]
	 39 => 183 // State: Unconsciousness [39]
	128 => 184 // State: Confusion [128]
	 38 => 185 // State: Silence [38]
	109 => 188 // State: Hold Creature I [109]
	175 => 188 // State: Hold Creature II [175]
	185 => 188 // State: Hold Creature III [185]
	157 => 189 // State: Web Effect [157]
	 76 => 190 // State: Feeblemindedness [76]
	 55 => 191 // Death: Kill Creature Type [55]
	206 => 192 // Spell: Protection from Spell [206]
	 58 => 200 // Cure: Dispellable Effects (Dispel Magic) [58]
	162 => 201 // Cure: Hold [162]
	161 => 202 // Cure: Fear [161]
	 23 => 203 // Cure: Horror [23]
	 48 => 204 // Cure: Silence (Vocalize) [48]
	 79 => 205 // Cure: Disease [79]
	 11 => 206 // Cure: Poison [11]
	 75 => 207 // Cure: Blindness [75]
	 81 => 208 // Cure: Deafness [81]
	 77 => 209 // Cure: Feeblemindedness [77]
	116 => 210 // Cure: (Remove) Invisibility [116]
	 32 => 211 // Cure: Death (Raise Dead) [32]
	 14 => 212 // Cure: (Frozen state) [14]
	  4 => 213 // Cure: Berserking [4]
	163 => 229 // Protection: Free Action [163]
	204 => 230 // Spell: Protection from Spell (School) [204]
	205 => 231 // Spell: Protection from Spell (Secondary Type) [205]
	102 => 232 // Protection: from Spell Levels [102]
	259 => 233 // Protection: Spell Trap [259]
	292 => 234 // Protection: Backstab [292]
	100 => 235 // Protection: from Creature Type [100]
	120 => 236 // Protection: from Melee Weapons [120]
	 83 => 237 // Protection: From Projectile (Any) [83]
	310 => 238 // Protection: from Timestop [310]
	218 => 239 // Protection: Stoneskin [218]
	 13 => 240 // Death: Instant Death [13]
	238 => 241 // Death: Disintegrate [238]
	148 => 246 // Spell: Cast Spell (at Point) [148]
	201 => 247 // Spell: Decrementing Spell Immunity [201]
	199 => 248 // Spell: Bounce Spells [199]
	200 => 249 // Spell: Decrementing Bounce Spells [200]
	200 => 249 // Spell: Decrementing Bounce Spells [200]
	207 => 250 // Spell: Bounce Specified Spell [207]
	197 => 251 // Spell: Bounce Projectile [197]
	119 => 252 // Spell Effect: Mirror Image [119]
	280 => 253 // Spell Effect: Wild Magic [280]
	235 => 254 // Spell Effect: Wing Buffet [235]
	239 => 255 // Spell Effect: Farsight [239]
	125 => 256 // Spell Effect: Unlock (Knock) [125]
	213 => 257 // Spell Effect: Maze [213]
	316 => 258 // Spell: Magical Rest [316]
	133 => 259 // Spell Effect: Luck Non-Cumulative [133]
	  5 => 260 // Charm: Charm Specific Creature [5]
	 57 => 261 // Alignment: Change [57]
	 56 => 262 // Alignment: Invert [56]
	 71 => 263 // Sex Change [71]
	111 => 264 // Item: Create Magical Weapon [111]
	143 => 265 // Item: Create Item in Slot [143]
	122 => 266 // Item: Create Inventory Item [122]
	255 => 267 // Item: Create Inventory Item (days) [255]
	 68 => 268 // Summon: Unsummon Creature [68]
	151 => 269 // Summon: Replace Creature [151]
	135 => 270 // Polymorph into Specific [135]
	135 => 271 // Item: Can Use Any Item [302]
	230 => 272 // Removal: Remove One Secondary Type [230]

	 // Charge
	146 => 274 // Spell: Cast Spell (at Target) [146]
	171 => 275 // Spell: Give Innate Ability [171]
	 67 => 280 // Summon: Creature Summoning [67]
	208 => 300 // Stat: Minimum HP Limit [208]
	273 => 350 // Remove: Specific Area Effect(Zone of Sweet Air) [273]

	177 => 400
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
	 52 => 1 // Colour: Very Bright by RGB [52]
	 53 => 1 // Graphics: Animation Change [53]
	 66 => 1 // Graphics: Transparency Fade [66]
	 72 => 1 // State: Set IDS State [72]
	 82 => 1 // Set AI Script [82]
	101 => 1 // Protection: from Opcode [101] // TODO: A gérer quand même ? Ne fait pas forcément doublon avec le 206 ?
	110 => 1 // (Retreat From) [110]
	112 => 1 // Item: Remove Item [112]
	139 => 1
	141 => 1
	142 => 1
	144 => 1 // Button: Disable Button [144] // TODO: A gérer ! Empêche le personnage de faire certaines actions !
	158 => 1 // State: Grease [158] // Applique seulement un effet visuel
	164 => 1 // Cure: Intoxication [164]
	169 => 1
	170 => 1 // Graphics: Play Damage Animation [170]
	172 => 1 // Spell: Remove Spell [172]
	174 => 1 // Spell Effect: Play Sound Effect [174]
	180 => 1 // Item: Can't Use Item [180] // TODO: A gérer, et grouper (BOW15...)
	184 => 1 // Graphics: Passwall (Don't Jump) [184]
	186 => 1 // Script: MoveToArea [186] // A gérer ??
	188 => 1 // Spell Effect: Aura Cleansing [188] // TODO: A gérer, je ne sais pas ce que cela fait pour le moent
	193 => 1 // Spell Effect: Invisible Detection by Script [193]
	215 => 1
	221 => 1 // Removal: Remove Secondary Type [221]
	232 => 1 // Spell Effect: Cast Spell on Condition [232]
	240 => 1 // Graphics: Remove Special Effect Icon [240]
	243 => 1 // Item: Drain Item Charges [243]
	248 => 1 // Item: Set Melee Effect [248]  // TODO: A gérer ! Attention, un effet a d'autres variables à prendre en compte (CBWTNI6A.ITM)
	249 => 1 // Item: Set Ranged Effect [249]  // TODO: A gérer ! Attention, un effet a d'autres variables à prendre en compte
	251 => 1 // Spell Effect: Change Bard Song Effect [251] // TODO: A gérer !
	265 => 1 // Script: Set Global Variable [265]
	267 => 1
	268 => 1 // Spell Effect: Explore (Wizard Eye) [268] // TODO: A gérer ?
	272 => 1 // Spell: Apply Effect on Condition [272] // TODO: A gérer !
	282 => 1 // Script: Scripting State Modifier [282]
	287 => 1 // Graphics: Selection Circle Removal [287]
	291 => 1 // Graphics: Disable Visual Effect [291]
	293 => 1 // Script: Enable Offscreen AI [293]
	294 => 1 // Existance Delay Override [294]
	295 => 1
	296 => 1
	297 => 1 // Text: Protection from Display Specific String [267]
	300 => 1 // NPC Bump [300] // TODO: A gérer ? Vérifier les objets qui l'utilisent
	309 => 1 // Script: Set/Modify Local Variable [309]
	318 => 1 // Protection: Immunity Spell [318] // TODO: A gérer quand même ? Stat: Set Stat (TobEx)
	319 => 1 // Item Usability [319] // EE only
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~damage_types~ BEGIN
	~%DAMAGETYPE_crushing%~    => 101098 //         0 ~points de dégâts contondants~
	~%DAMAGETYPE_acid%~        => 101096 //     65536 ~points de dégâts d'acide~
	~%DAMAGETYPE_cold%~        => 101095 //    131072 ~points de dégâts de froid~
	~%DAMAGETYPE_electricity%~ => 101093 //    262144 ~points de dégâts d'électricité~
	~%DAMAGETYPE_fire%~        => 101094 //    524288 ~points de dégâts de feu~
	~%DAMAGETYPE_piercing%~    => 101100 //   1048576 ~points de dégâts perforants~
	~%DAMAGETYPE_poison%~      => 101097 //   2097152 ~points de dégâts de poison~
	~%DAMAGETYPE_magic%~       => 101101 //   4194304 ~points de dégâts magiques~
	~%DAMAGETYPE_slashing%~    => 101099 //  16777216 ~points de dégâts tranchants~
	~%DAMAGETYPE_magic_fire%~  => 101105 //  33554432 ~points de dégâts de feu magique~
	~%DAMAGETYPE_magic_cold%~  => 101104 //  67108864 ~points de dégâts de froid magique~
	~%DAMAGETYPE_stunning%~    => 101103 // 134217728 ~points de dégâts non mortels~
	~%DAMAGETYPE_piercing_reduce_by_percentage%~ => 101100 //   1048579 ~points de dégâts perforants~
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

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~ids_files~ BEGIN
	2 => ~ea~
	3 => ~general~
	4 => ~race~
	5 => ~class~
	6 => ~specific~
	7 => ~gender~
	8 => ~align~
	9 => ~kit~
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

DEFINE_PATCH_MACRO ~opcode_self_probability_0~ BEGIN
	LOCAL_SPRINT versus ~~
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == AC_MOD_TYPE_set_base BEGIN
		// xx% de chance de faire passer la classe d'armure du porteur [contre les] à yy [pendant ...]
		PATCH_FAIL "%SOURCE_FILE% : opcode_target_probability_0 pourcentage d'armure du porteur à gérer"
	END
	ELSE BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%value%~ RET value END
		PATCH_IF parameter2 != AC_MOD_TYPE_all BEGIN
			SET strref = 102020 + parameter2
			SPRINT versus (AT ~strref~) // ~contre les xxx~
			SPRINT value ~%value% %versus%~
		END
	END

	SPRINT description @102370 // ~de modifier la classe d'armure du porteur de %value%~
END


DEFINE_PATCH_MACRO ~opcode_target_0~ BEGIN
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
	SPRINT target @101085 // ~de la cible~
	SPRINT description @100007 // ~%name% %target%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_0~ BEGIN
	LOCAL_SPRINT versus ~~
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == AC_MOD_TYPE_set_base BEGIN
		// xx% de chance de faire passer la classe d'armure de la cible [contre les] à yy [pendant ...]
		PATCH_FAIL "%SOURCE_FILE% : opcode_target_probability_0 pourcentage d'armure de la cible à gérer"
	END
	ELSE BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%value%~ RET value END
		PATCH_IF parameter2 != AC_MOD_TYPE_all BEGIN
			SET strref = 102020 + parameter2
			SPRINT versus (AT ~strref~) // ~contre les xxx~
			SPRINT value ~%value% %versus%~
		END
	END

	SPRINT description @102134 // ~de modifier la classe d'armure de la cible de %value%~
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
		SET value -= 100
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT value @10002 // ~%value% %~
	END

	SPRINT name @102007 // ~Attaque par round~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_1~ BEGIN
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
			SPRINT description @102344 // ~de passer l'attaque par round du porteur à %value%~
		END
		ELSE BEGIN
			SPRINT description @102343 // ~de modifier l'attaque par round du porteur de %value%~
		END
	END
	ELSE BEGIN
		SET value = ~%parameter1%~
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102345 // ~de multiplier l'attaque par round du porteur par %value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_1~ BEGIN
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
			SPRINT description @102446 // ~de passer l'attaque par round de la cible à %value%~
		END
		ELSE BEGIN
			SPRINT description @102445 // ~de modifier l'attaque par round de la cible de %value%~
		END
	END
	ELSE BEGIN
		SET value = ~%parameter1%~
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102447 // ~de multiplier l'attaque par round de la cible par %value%~
	END
END

/* --------------------- *
 * State: Berserking [3] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_3~ BEGIN
	SPRINT description @102197 // ~Rage berserk permanente~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_3~ BEGIN
	SPRINT description @102166 // ~de provoquer Rage berserk chez le porteur~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_3~ BEGIN
	SPRINT description @102320 // ~de provoquer Rage berserk chez la cible~
END

/* -------------------- *
 * Cure: Berserking [4] *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_4~ BEGIN
	SPRINT description @102449 // ~Immunité à Rage berserk~
END

/* ---------------------------------- *
 * Charm: Charm Specific Creature [5] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_5~ BEGIN
	PATCH_FAIL "%SOURCE_FILE%: opcode_self_5: valide comme configuration ??"
END

DEFINE_PATCH_MACRO ~opcode_target_5~ BEGIN
	PATCH_IF parameter1 == 0 BEGIN
		SPRINT description @102387 // ~Charme extrême~
	END
	ELSE BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~3~ RET idName END

		PATCH_IF NOT ~%idName%~ STRING_EQUAL ~~ BEGIN
			SPRINT description @102249 // ~Charme une créature (%creatureType%)~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_5~ BEGIN
	PATCH_IF parameter1 == 0 BEGIN
		SPRINT description @102388 // ~de charmer la cible~
	END
	ELSE BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~3~ RET idName END

		PATCH_IF NOT ~%idName%~ STRING_EQUAL ~~ BEGIN
			SPRINT description @102389 // ~de charmer la cible si c'est une créature (%creatureType%)~
		END
	END
END

/* -------- *
 * Charisme *
 * -------- */
DEFINE_PATCH_MACRO ~opcode_self_6~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101081 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Charisme~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_6~ BEGIN
	// @102277 = ~de modifier le charisme du porteur de %value%~
	// @102278 = ~de passer le charisme du porteur à %value%~
	// @102279 = ~de multiplier le charisme du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102277 strrefFlat = 102278 strrefPercent = 102279 STR_VAR value = ~%parameter1%~ RET description END
END

/* ------------ *
 * Constitution *
 * ------------ */
DEFINE_PATCH_MACRO ~opcode_self_10~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101080 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Constitution~
END

DEFINE_PATCH_MACRO ~opcode_target_10~ BEGIN
	LPF ~opcode_target_mod~ INT_VAR strref = 101080 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Constitution~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_10~ BEGIN
	// @102280 = ~de modifier la constitution du porteur de %value%~
	// @102281 = ~de passer la constitution du porteur à %value%~
	// @102282 = ~de multiplier la constitution du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102280 strrefFlat = 102281 strrefPercent = 102282 STR_VAR value = ~%parameter1%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_10~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT description @102309 // ~de modifier la constitution de la cible de %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102310 // ~de passer la constitution de la cible à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102311 // ~de multiplier la constitution de la cible par %value%~
	END
END

/* ----------------- *
 * Cure: Poison [11] *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_11~ BEGIN
	SPRINT description @102319 // ~Immunité aux poisons~
END

DEFINE_PATCH_MACRO ~opcode_target_11~ BEGIN
	SPRINT description @102352 // ~Neutralisation du poison~
END

/* ------ *
 * Dégâts *
 * ------ */
DEFINE_PATCH_MACRO ~opcode_self_12~ BEGIN
	// @102359 = ~Inflige %damage% %damageType% au porteur~
	LPF ~opcode_12_common~ INT_VAR strref_0 = 102359 RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_12~ BEGIN
	// @102092 = ~Inflige %damage% %damageType% supplémentaires~
	LPF ~opcode_12_common~ INT_VAR strref_0 = 102092 RET description END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_12~ BEGIN
	// @102224 = ~d'infliger %damage% %damageType% au porteur~
	LPF ~opcode_12_common~ INT_VAR strref_0 = 102224 RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_12~ BEGIN
	// @102091 = ~d'infliger %damage% %damageType% supplémentaires~
	// @102385 = ~de retirer %value% des points de vie de la cible sous forme de %damageType%~

	LPF ~opcode_12_common~ INT_VAR strref_0 = 102091 strref_3 = 102385 RET description END
END

/* -------------------------- *
 * Dégâts - Traitement commun *
 * -------------------------- */
DEFINE_PATCH_FUNCTION ~opcode_12_common~ INT_VAR strref_0 = 0 strref_1 = 0 strref_2 = 0 strref_3 = 0 RET description BEGIN
	SET damageAmount = %parameter1%
	SET type = %parameter2%
	SET subType = type MODULO 4
	SPRINT description ~~

	PATCH_IF special > 0 BEGIN
		PATCH_FAIL "%SOURCE_FILE% : Valeur spéciale '%special%' pour le opcode 12 pas encore geree"
	END
	PATCH_IF NOT VARIABLE_IS_SET $damage_types(~%type%~) BEGIN
		PATCH_FAIL "%SOURCE_FILE% : Type de degat '%type%' pour le opcode 12 pas encore gere"
	END

	SET type = $damage_types(~%type%~)
	SPRINT damageType (AT ~%type%~)

	// Dégâts basiques
	PATCH_IF subType == 0 BEGIN
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET damage END

		INNER_PATCH_SAVE damage ~%damage%~ BEGIN
			REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
		END

		PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
			SPRINT description (AT ~%strref_0%~ )
		END
	END
	// Set to value
	ELSE PATCH_IF subType == 1 BEGIN
		PATCH_FAIL "%SOURCE_FILE%: opcode_12_common: subType 1 à gérer"
	END
	// Set to Percentage
	ELSE PATCH_IF subType == 2 BEGIN
		PATCH_FAIL "%SOURCE_FILE%: opcode_12_common: subType 2 à gérer"
	END
	// Reduce by Percentage
	ELSE PATCH_IF subType == 3 BEGIN
		SET value = damageAmount
		SPRINT value @10002 // ~%value% %~
		SPRINT description (AT ~%strref_3%~ )
	END
END

/* ------------------------------ *
 * Mort instantanée - Probabilité *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_target_13~ BEGIN
	SPRINT description @102222 // ~Tue instantanément la cible~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_13~ BEGIN
	SPRINT description @102300 // ~de tuer instantanément le porteur~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_13~ BEGIN
	SPRINT description @102124 // ~de tuer instantanément la cible~
END

/* ------------------------- *
 * Cure: (Frozen state) [14] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_14~ BEGIN
	SPRINT description @102425 // ~Immunité au gel~
END

/* ----------------------------- *
 * Stat: Dexterity Modifier [15] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_15~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101078 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dextérité~
END

DEFINE_PATCH_MACRO ~opcode_target_15~ BEGIN
	LPF ~opcode_target_mod~ INT_VAR strref = 101078 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dextérité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_15~ BEGIN
	// @102274 = ~de modifier la dextérité du porteur de %value%~
	// @102275 = ~de passer la dextérité du porteur à %value%~
	// @102276 = ~de multiplier la dextérité du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102274 strrefFlat = 102275 strrefPercent = 102276 STR_VAR value = ~%parameter1%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_15~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT description @102225 // ~de modifier la dextérité de la cible de %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102226 // ~de passer la dextérité de la cible à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102227 // ~de multiplier la dextérité de la cible par %value%~
	END
END

/* ----------------- *
 * State: Haste [16] *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_16~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @102214 // ~Hâte permanente~
	END
	ELSE PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @102261 // ~Hâte améliorée permanente~
	END
	ELSE BEGIN
		SPRINT description @102262 // ~Hâte permanente (sans bonus d'attaque par round)~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_16~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @102348 // ~de lancer Hâte sur le porteur~
	END
	ELSE PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @102349 // ~de lancer Hâte améliorée sur le porteur~
	END
	ELSE BEGIN
		SPRINT description @102350 // ~de lancer Hâte (sans bonus d'attaque par round) sur le porteur~
	END
END

/* ----------------------------- *
 * Modification de points de vie *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_17~ BEGIN
	LOCAL_SET strref_1 = 102097 // ~Soigne un point de vie au porteur~
	LOCAL_SET strref_2 = 102098 // ~Soigne %value% points de vie au porteur~
	LOCAL_SET strref_3 = 102099 // ~Inflige un point de dégâts au porteur~
	LOCAL_SET strref_4 = 102100 // ~Inflige %value% points de dégâts au porteur~

	LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 strref_3 strref_4 RET description END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_17~ BEGIN
	LOCAL_SET strref_1 = 102301 // ~de soigner un point de vie au porteur~
	LOCAL_SET strref_2 = 102302 // ~de soigner %value% points de vie au porteur~
	LOCAL_SET strref_3 = 102303 // ~d'infliger un point de dégâts au porteur~
	LOCAL_SET strref_4 = 102304 // ~d'infliger %value% points de dégâts au porteur~

	LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 strref_3 strref_4 RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_17~ BEGIN
	LOCAL_SET strref_1 = 102130 // ~Soigne un point de vie à la cible~
	LOCAL_SET strref_2 = 102131 // ~Soigne %value% points de vie à la cible~
	LOCAL_SET strref_3 = 102132 // ~Inflige un point de dégâts à la cible~
	LOCAL_SET strref_4 = 102133 // ~Inflige %value% points de dégâts à la cible~

	LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 strref_3 strref_4 RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_17~ BEGIN
	LOCAL_SET strref_1 = 102413 // ~de soigner un point de vie au porteur~
	LOCAL_SET strref_2 = 102414 // ~de soigner %value% points de vie au porteur~
	LOCAL_SET strref_3 = 102415 // ~d'infliger un point de dégâts au porteur~
	LOCAL_SET strref_4 = 102416 // ~d'infliger %value% points de dégâts au porteur~

	LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 strref_3 strref_4 RET description END
END

DEFINE_PATCH_MACRO ~opcode_party_17~ BEGIN
	LOCAL_SET strref_1 = 102215 // ~Soigne un point de vie au groupe~
	LOCAL_SET strref_2 = 102216 // ~Soigne %value% points de vie au groupe~
	LOCAL_SET strref_3 = 102217 // ~Inflige un point de dégâts au groupe~
	LOCAL_SET strref_4 = 102218 // ~Inflige %value% points de dégâts au groupe~

	LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 strref_3 strref_4 RET description END
END

DEFINE_PATCH_FUNCTION ~opcode_17_common~ INT_VAR strref_1 = 0 strref_2 = 0 strref_3 = 0 strref_4 = 0 RET description BEGIN
	SET damageAmount = parameter1
	LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END

	PATCH_IF ~%value%~ STRING_CONTAINS_REGEXP ~^-~ BEGIN
		PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF ~%value%~ STRING_EQUAL ~1~ BEGIN
				SPRINT description (AT ~%strref_1%~) // ~Soigne un point de vie~
			END
			ELSE BEGIN
				SPRINT description (AT ~%strref_2%~) // ~Soigne %value% points de vie~
			END
		END
	END
	ELSE BEGIN
		PATCH_IF ~%value%~ STRING_EQUAL ~-1~ BEGIN
			SPRINT description (AT ~%strref_3%~) // ~Inflige un point de vie~
		END
		ELSE BEGIN
			SPRINT description (AT ~%strref_4%~) // ~Inflige %value% points de vie~
		END
	END
END

/* ------------------------------ *
 * Stat: Maximum HP Modifier [18] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_18~ BEGIN
	LPM ~opcode_18_common~

	SPRINT name @102168 // ~Points de vie maximum~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_18~ BEGIN
	// @102267 = ~de modifier les points de vie maximum du porteur de %value%~
	// @102268 = ~de passer les points de vie maximum du porteur à %value%~
	// @102269 = ~de multiplier les points de vie maximum du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102267 strrefFlat = 102268 strrefPercent = 102269 STR_VAR value = ~%parameter1%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_18~ BEGIN
	LPM ~opcode_18_common~

	SPRINT name @102168 // ~Points de vie maximum~
	SPRINT target @101085 // ~de la cible~
	SPRINT description @100007 // ~%name% %target%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_18~ BEGIN
	// @102417 = ~de modifier les points de vie maximum de la cible de %value%~
	// @102418 = ~de passer les points de vie maximum de la cible à %value%~
	// @102419 = ~de multiplier les points de vie maximum de la cible par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102417 strrefFlat = 102418 strrefPercent = 102419 STR_VAR value = ~%parameter1%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_18_common~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative OR parameter2 == 3 BEGIN
		LPF ~signed_value~ INT_VAR value = ~%parameter1%~ RET value END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat OR parameter2 == 4 BEGIN
		SET value = ~%parameter1%~
		SPRINT value @10010 // ~Passe à %value%~
	END
	ELSE BEGIN // percent
		SET value = ~%parameter1%~
		SET value -= 100
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT value @10002 // ~%value% %~
	END
END

/* ------------ *
 * Intelligence *
 * ------------ */
DEFINE_PATCH_MACRO ~opcode_self_19~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101077 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Intelligence~
END

DEFINE_PATCH_MACRO ~opcode_target_19~ BEGIN
	LPF ~opcode_target_mod~ INT_VAR strref = 101077 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Intelligence~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_19~ BEGIN
	// @102283 = ~de modifier l'intelligence du porteur de %value%~
	// @102284 = ~de passer l'intelligence du porteur à %value%~
	// @102285 = ~de multiplier l'intelligence du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102283 strrefFlat = 102284 strrefPercent = 102285 STR_VAR value = ~%parameter1%~ RET description END
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

DEFINE_PATCH_MACRO ~opcode_self_probability_20~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @102315 // ~de lancer Invisibilité sur le porteur~
	END
	ELSE BEGIN
		SPRINT description @102316 // ~de lancer Invisibilité améliorée sur le porteur~
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
	SPRINT description @102167 // ~d'infliger Horreur à la cible~
END

/* ------------------ *
 * State: Poison [25] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_25~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF (parameter2 == 0 AND amount != 0) OR (parameter2 == 1 AND amount > 1) BEGIN
		SPRINT description @102326 // ~Empoisonne le porteur et lui inflige 1 point de dégât par seconde~
	END
	ELSE PATCH_IF parameter2 == 2 BEGIN
		SPRINT description @102327 // ~Empoisonne le porteur et lui inflige %amount% points de dégâts par seconde~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SPRINT description @102328 // ~Empoisonne le porteur et lui inflige 1 point de dégât toutes les %amount% secondes~
	END
	ELSE PATCH_IF parameter2 == 4 BEGIN
		SET amount = 3
		SPRINT description @102327 // ~Empoisonne le porteur et lui inflige %amount% points de dégâts par seconde~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_25~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF (parameter2 == 0 AND amount != 0) OR (parameter2 == 1 AND amount > 1) BEGIN
		SPRINT description @102306 //~d'empoisonner le porteur et lui infliger 1 point de dégât par seconde~
	END
	ELSE PATCH_IF parameter2 == 2 BEGIN
		SPRINT description @102307 // ~d'empoisonner le porteur et lui infliger %amount% points de dégâts par seconde~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SPRINT description @102308 // ~d'empoisonner le porteur et lui infliger 1 point de dégât  toutes les %amount% secondes~
	END
	ELSE PATCH_IF parameter2 == 4 BEGIN
		SET amount = 3
		SPRINT description @102307 // ~d'empoisonner le porteur et lui infliger %amount% points de dégâts par seconde~
	END
END

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

DEFINE_PATCH_MACRO ~opcode_target_27~ BEGIN
	LPF ~opcode_target_mod_percent~ INT_VAR strref = 102055 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à l'acide~
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
	LPF ~opcode_mod_percent~ INT_VAR strref = 102057 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à l'électricité~
END

DEFINE_PATCH_MACRO ~opcode_target_29~ BEGIN
	LPF ~opcode_target_mod_percent~ INT_VAR strref = 102057 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à l'électricité~
END

/* ----------------- *
 * Résistance au feu *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_30~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102056 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance au feu~
END

DEFINE_PATCH_MACRO ~opcode_target_30~ BEGIN
	LPF ~opcode_target_mod_percent~ INT_VAR strref = 102056 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance au feu~
END

/* ------------------------------ *
 * Résistance aux dégâts magiques *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_31~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102065 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts magiques~
END

/* ----------------------------- *
 * Cure: Death (Raise Dead) [32] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_32~ BEGIN
	SPRINT description @102424 // ~Résurrection~
END

/* -------------------------------------------------------------- *
 * Jets de sauvegarde contre la paralysie, la mort et les poisons *
 * -------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_33~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102029 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre la paralysie, la mort et les poisons~
END

DEFINE_PATCH_MACRO ~opcode_target_33~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102033 STR_VAR value = EVAL ~%parameter1%~ target = 1 RET description END // ~contre les sorts~
END

DEFINE_PATCH_MACRO ~opcode_party_33~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102029 STR_VAR value = EVAL ~%parameter1%~ group = 1 RET description END // ~contre la paralysie, la mort et les poisons~
END

/* ------------------------------------------------------------------- *
 * Jets de sauvegarde contre les baguettes, les sceptres et les bâtons *
 * ------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_34~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102030 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les baguettes, les sceptres et les bâtons~
END

DEFINE_PATCH_MACRO ~opcode_target_34~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102030 STR_VAR value = EVAL ~%parameter1%~ target = 1 RET description END // ~contre les sorts~
END

/* ------------------------------------------------------------- *
 * Jets de sauvegarde contre la pétrification et la métamorphose *
 * ------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_35~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102031 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre la pétrification et la métamorphose~
END

DEFINE_PATCH_MACRO ~opcode_target_35~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102031 STR_VAR value = EVAL ~%parameter1%~ target = 1 RET description END // ~contre les sorts~
END

/* -------------------------------------- *
 * Jets de sauvegarde contre les souffles *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_36~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102032 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les souffles~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_36~ BEGIN
	PATCH_FAIL "%SOURCE_FILE%: opcode_self_probability_36: a terminer"
END

DEFINE_PATCH_MACRO ~opcode_target_36~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102032 STR_VAR value = EVAL ~%parameter1%~ target = 1 RET description END // ~contre les sorts~
END

/* ----------------------------------- *
 * Jets de sauvegarde contre les sorts *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_37~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102033 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les sorts~
END

DEFINE_PATCH_MACRO ~opcode_target_37~ BEGIN
	LPF ~opcode_save_vs~ INT_VAR strref = 102033 target = 1 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les sorts~
END

/* ------------------- *
 * State: Silence [38] *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_target_38~ BEGIN
	SPRINT description @102248 // ~Réduit la cible au silence~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_38~ BEGIN
	SPRINT description @102323 // ~de réduire la cible au silence~
END

/* --------------------------- *
 * State: Unconsciousness [39] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_39~ BEGIN
	SPRINT description @102139 // ~Assome la cible~ // Endors la cible
END

DEFINE_PATCH_MACRO ~opcode_target_probability_39~ BEGIN
	SPRINT description @102135 // ~d'assommer la cible~ // d'endormir la cible
END

/* ---------------- *
 * State: Slow [40] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_40~ BEGIN
	SPRINT description @102290 // ~Lenteur permanente~
END

DEFINE_PATCH_MACRO ~opcode_target_40~ BEGIN
	SPRINT description @102175 // ~Inflige Lenteur à la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_40~ BEGIN
	SPRINT description @102189 // ~d'infliger Lenteur à la cible~
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

DEFINE_PATCH_MACRO ~opcode_target_44~ BEGIN
	LPF ~opcode_target_mod~ INT_VAR strref = 101076 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_44~ BEGIN
	// @102271 = ~de modifier la force du porteur de %value%~
	// @102272 = ~de passer la force du porteur à %value%~
	// @102273 = ~de multiplier la force du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102271 strrefFlat = 102272 strrefPercent = 102273 STR_VAR value = ~%parameter1%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_44~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT description @102312 // ~de modifier la force de la cible de %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102313 // ~de passer la force de la cible à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102314 // ~de multiplier la force de la cible par %value%~
	END
END

/* ---------------- *
 * State: Stun [45] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_45~ BEGIN
	SPRINT description @102255 // ~Étourdi le porteur~
END

DEFINE_PATCH_MACRO ~opcode_target_45~ BEGIN
	SPRINT description @102123 // ~Étourdi la cible~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_45~ BEGIN
	SPRINT description @102420 // ~d'étourdir le porteur~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_45~ BEGIN
	SPRINT description @102120 // ~d'étourdir la cible~
END

/* ------------------------ *
 * Cure: Stun (Unstun) [46] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_46~ BEGIN
	SPRINT description @102422 // ~Immunité à l'étourdissement~
END

/* ----------------------------- *
 * Cure: Silence (Vocalize) [48] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_48~ BEGIN
	SPRINT description @102242 // ~Immunité au silence~
END

/* ------- *
 * Sagesse *
 * ------- */
DEFINE_PATCH_MACRO ~opcode_self_49~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 101079 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Sagesse~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_49~ BEGIN
	// @102286 = ~de modifier la sagesse du porteur de %value%~
	// @102287 = ~de passer la sagesse du porteur à %value%~
	// @102288 = ~de multiplier la sagesse du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102286 strrefFlat = 102287 strrefPercent = 102288 STR_VAR value = ~%parameter1%~ RET description END
END

/* ---- *
 * TAC0 *
 * ---- */
DEFINE_PATCH_MACRO ~opcode_self_54~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102000 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0~
END

DEFINE_PATCH_MACRO ~opcode_target_54~ BEGIN
	LPF ~opcode_target_mod~ INT_VAR strref = 102000 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_54~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT description @102219 // ~de modifier le TAC0 de la cible de %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102220 // ~de passer le TAC0 de la cible à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102221 // ~de multiplier le TAC0 de la cible par %value%~
	END
END

/* ------------------------------ *
 * Death: Kill Creature Type [55] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_55~ BEGIN
	LPM ~opcode_target_55~
END

DEFINE_PATCH_MACRO ~opcode_target_55~ BEGIN
	// TODO: Fonctionne pour tous les lvl si diceCount == 0 ?!
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
		PATCH_FAIL "%SOURCE_FILE%: opcode 55 à gérer %idsFile%(~%parameter1%~)"
		// Tue instantanément les GOLEM (race) de xx dés de vie ou moins
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_55~ BEGIN
	LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END

	SPRINT description @102458 // ~de tuer instantanément les %creatureType%~
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

/* --------------------------------------------- *
 * Cure: Dispellable Effects (Dispel Magic) [58] *
 * --------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_58~ BEGIN
	SPRINT description @102243 // ~Dissipation de la magie~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_58~ BEGIN
	SPRINT description @102331 // ~de dissiper la magie~
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
	LOCAL_SET value = parameter1
	LOCAL_SET type = parameter2

	PATCH_IF value == 100 BEGIN
		PATCH_IF type == 0 OR type== 3 BEGIN
			SPRINT description @102228 // ~Échec systématique des sorts profanes lancés~
		END
		ELSE PATCH_IF type == 1 OR type== 4 BEGIN
			SPRINT description @102229 // ~Échec systématique des sorts divins lancés~
		END
		ELSE PATCH_IF type == 2 OR type== 5 BEGIN
			SPRINT description @102230 // ~Échec systématique des sorts innés lancés~
		END
	END
	ELSE BEGIN
        SPRINT percent @10002 // ~%value% %~
		PATCH_IF type == 0 OR type== 3 BEGIN
			SPRINT description @102296 // ~Échec de %percent% des sorts profanes lancés~
		END
		ELSE PATCH_IF type == 1 OR type== 4 BEGIN
			SPRINT description @102297 // ~Échec de %percent% des sorts divins lancés~
		END
		ELSE PATCH_IF type == 2 OR type== 5 BEGIN
			SPRINT description @102298 // ~Échec de %percent% des sorts innés lancés~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_60~ BEGIN
	LOCAL_SET value = parameter1
	LOCAL_SET type = parameter2

	PATCH_IF value == 100 BEGIN
		PATCH_IF type == 0 OR type== 3 BEGIN
			SPRINT description @102163 // ~Échec systématique des sorts profanes lancés par la cible~
		END
		ELSE PATCH_IF type == 1 OR type== 4 BEGIN
			SPRINT description @102164 // ~Échec systématique des sorts divins lancés par la cible~
		END
		ELSE PATCH_IF type == 2 OR type== 5 BEGIN
			SPRINT description @102165 // ~Échec systématique des sorts innés lancés par la cible~
		END
	END
	ELSE BEGIN
        SPRINT percent @10002 // ~%value% %~
		PATCH_IF type == 0 OR type== 3 BEGIN
			SPRINT description @102293 // ~Échec de %percent% des sorts profanes lancés par la cible~
		END
		ELSE PATCH_IF type == 1 OR type== 4 BEGIN
			SPRINT description @102294 // ~Échec de %percent% des sorts divins lancés par la cible~
		END
		ELSE PATCH_IF type == 2 OR type== 5 BEGIN
			SPRINT description @102295 // ~Échec de %percent% des sorts innés lancés par la cible~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_60~ BEGIN
	LOCAL_SET value = parameter1
	LOCAL_SET type = parameter2

	PATCH_IF value == 100 BEGIN
		PATCH_IF type == 0 OR type== 3 BEGIN
			SPRINT description @102378 // ~d'ôter la possibilité de lancer des sorts profanes à la cible~
		END
		ELSE PATCH_IF type == 1 OR type== 4 BEGIN
			SPRINT description @102379 // ~d'ôter la possibilité de lancer des sorts divins à la cible~
		END
		ELSE PATCH_IF type == 2 OR type== 5 BEGIN
			SPRINT description @102380 // ~d'ôter la possibilité de lancer des sorts innés à la cible~
		END
	END
	ELSE BEGIN
        PATCH_FAIL "%SOURCE_FILE%: opcode_target_probability_60: gestion de value < 100"
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

DEFINE_PATCH_MACRO ~opcode_target_probability_65~ BEGIN
	SPRINT description @102299 // ~que la cible devienne floue~
END

/* ------------------------------- *
 * Summon: Creature Summoning [67] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_67~ BEGIN
	LPM ~opcode_target_67~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_67~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
	SPRINT description @102256 // ~d'invoquer une créature (%creatureName%)~
END

DEFINE_PATCH_MACRO ~opcode_target_67~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
	SPRINT description @102173 // ~Invoque une créature (%creatureName%)~
END

/* ------------------------------ *
 * Summon: Unsummon Creature [68] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_target_probability_68~ BEGIN
	SPRINT description @102325 // ~de renvoyer la cible (si c'est une créature invoquée)~
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
		PATCH_FAIL "%SOURCE_FILE% : Fixation du genre à gérer"
	END
END

/* ------ *
 * Dégâts *
 * ------ */
DEFINE_PATCH_MACRO ~opcode_self_73~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts~
END

DEFINE_PATCH_MACRO ~opcode_target_73~ BEGIN
	LPF ~opcode_target_mod~ INT_VAR strref = 102001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts~
END

/* --------------------- *
 * State: Blindness [74] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_probability_74~ BEGIN
	SPRINT description @102421 // ~d'aveugler le porteur~
END

DEFINE_PATCH_MACRO ~opcode_target_74~ BEGIN
	SPRINT description @102137 // ~Aveugle la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_74~ BEGIN
	SPRINT description @102247 // ~d'aveugler la cible~
END

/* -------------------- *
 * Cure: Blindness [75] *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_75~ BEGIN
	SPRINT description @102369 // ~Immunité à l'aveuglement~
END

DEFINE_PATCH_MACRO ~opcode_target_75~ BEGIN
	SPRINT description @102144 // ~Guérison de la cécité~
END

/* --------------------------- *
 * State: Feeblemindedness [76] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_76~ BEGIN
	SPRINT description @102384 // ~Débilité mentale permanente~
END

DEFINE_PATCH_MACRO ~opcode_target_76~ BEGIN
	SPRINT description @102337 // ~Inflige Débilité mentale à la cible~
END

/* --------------------------- *
 * Cure: Feeblemindedness [77] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_77~ BEGIN
	SPRINT description @102450 // ~Immunité à la Débilité mentale~
END

DEFINE_PATCH_MACRO ~opcode_target_77~ BEGIN
	SPRINT description @102146 // ~Guérison de la Débilité mentale~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_77~ BEGIN
	SPRINT description @102412 // ~de guérir la Débilité mentale~
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

DEFINE_PATCH_MACRO ~opcode_target_probability_78~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET type = parameter2

	PATCH_IF type >= 4 AND type <= 9 BEGIN
		PATCH_IF amount > 0 BEGIN
			SET strref = 102428 + type
			SPRINT description (AT ~%strref%~) //  ~d'inoculer une maladie qui diminue [la caractéristique] de la cible de %amount%~
		END
		ELSE BEGIN
			SET amount *= ~-1~
			SET strref = 102435 + type
			SPRINT description (AT ~%strref%~) //  ~d'inoculer une maladie qui augmente [la caractéristique] de la cible de %amount%~
		END
	END
	ELSE PATCH_IF type == 0 OR type == 1 OR (type == 3 AND amount == 1) BEGIN
		SPRINT description @102426 // ~d'inoculer une maladie qui inflige 1 point de dégâts par seconde à la cible~
	END
	ELSE PATCH_IF type == 2 BEGIN
		SPRINT description @102427 // ~d'inoculer une maladie qui inflige %amount% points de dégâts par seconde à la cible~
	END
	ELSE PATCH_IF type == 3 BEGIN
		SPRINT description @102428 // ~d'inoculer une maladie qui inflige 1 point de dégâts toutes les %amount% secondes à la cible~
	END
	ELSE PATCH_IF type == 10 BEGIN
		SPRINT description @102435 // ~d'inoculer une maladie qui ralenti la cible~
	END
END

/* ------------------ *
 * Cure: Disease [79] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_79~ BEGIN
	SPRINT description @102318 // ~Immunité aux maladies~
END

DEFINE_PATCH_MACRO ~opcode_target_79~ BEGIN
	SPRINT description @102143 // ~Guérison des maladies~
END

/* ------------- *
 * Deafness [80] *
 * ------------- */
DEFINE_PATCH_MACRO ~opcode_self_probability_80~ BEGIN
	SPRINT description @102442 // ~de causer la surdité au porteur~
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
		DEFAULT PATCH_FAIL "%SOURCE_FILE% : Opcode %opcode% : Type de projectile '%parameter2%' à gérer"
    END
END

DEFINE_PATCH_MACRO ~opcode_target_83~ BEGIN
	LPM ~opcode_self_83~
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

DEFINE_PATCH_MACRO ~opcode_target_probability_88~ BEGIN
	LPF ~opcode_target_mod_percent~ INT_VAR strref = 102063 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts perforants~
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

/* --------------------------- *
 * Stat: Fatigue Modifier [93] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_93~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102136 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Fatigue~
END

/* ----------------------- *
 * Stat: Level Change [96] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_target_96~ BEGIN
	LPF ~opcode_target_mod~ INT_VAR strref = 101082 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Niveau~
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
		SPRINT description @102103 // ~Régénère 1 point de vie toutes les %value% secondes~
	END
	ELSE BEGIN
		SPRINT description @102105 // ~Régénère 3 points de vie toutes les %value% secondes~
	END
END
DEFINE_PATCH_MACRO ~opcode_target_98~ BEGIN
	LOCAL_SET value = parameter1

	PATCH_IF parameter2 == 0 OR parameter2 == 2 BEGIN
		PATCH_IF value == 1 BEGIN
			SPRINT description @102250 //~Régénère 1 point de vie par seconde à la cible~
		END
		ELSE BEGIN
			SPRINT description @102251 // ~Régénère %value% points de vie par seconde à la cible~
		END
	END
	ELSE PATCH_IF parameter2 == 1 BEGIN
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102253 // ~Régénère %value% des points de vie de la cible~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SPRINT description @102252 // ~Régénère 1 point de vie toutes les %value% secondes à la cible~
	END
	ELSE BEGIN
		SPRINT description @102254 // ~Régénère 3 points de vie toutes les %value% secondes à la cible~
	END
END

/* ------------------------------------ *
 * Spell Effect: Duration Modifier [99] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_99~ BEGIN
	LOCAL_SET duration = parameter1
	LOCAL_SET type = parameter2

	PATCH_IF duration == 0 BEGIN
		PATCH_IF type == 0 BEGIN
			SPRINT description @102363 // ~Les sorts profanes n'ont plus aucune durée~
		END
		ELSE BEGIN
			SPRINT description @102366 // ~Les sorts divins n'ont plus aucune durée~
		END
	END
	ELSE PATCH_IF duration < 100 AND duration > 0 BEGIN
		SET value = 100 - duration
		SPRINT duration @10002 // ~%value% %~

		PATCH_IF type == 0 BEGIN
			SPRINT description @102364 // ~Les sorts profanes durent %duration% moins longtemps~
		END
		ELSE BEGIN
			SPRINT description @102367 // ~Les sorts divins durent %duration% moins longtemps~
		END
	END
	ELSE PATCH_IF duration > 100 BEGIN
		SET value = duration - 100
		SPRINT duration @10002 // ~%value% %~

		PATCH_IF type == 0 BEGIN
			SPRINT description @102365 // ~Les sorts profanes durent %duration% plus longtemps~
		END
		ELSE BEGIN
			SPRINT description @102368 // ~Les sorts divins durent %duration% plus longtemps~
		END
	END
END

/* ------------------------------------- *
 * Protection contre un type de créature *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_100~ BEGIN
	// To be protected from any creature, leave IDS Entry at 0 (zero), and IDS File at 2.
	PATCH_IF parameter1 == 0 AND parameter2 == 2 BEGIN
		SPRINT description @102459 // ~Immunité contre les attaques de toutes les créatures~
	END
	ELSE BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END

		SPRINT description @102457 // ~Immunité contre les attaques des %creatureType%~
	END
END

/* -------------------------------------- *
 * Immunité contre les sorts de niveau xx *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_102~ BEGIN
	LOCAL_SET spellLevel = ~%parameter1%~
	SPRINT description @102118 // ~Immunité contre les sorts de niveau %spellLevel%~
END

/* ----------------------------- *
 * Stat: Experience Points [104] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_104~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102377 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Expérience gagnée~
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
	SPRINT idsFile $ids_files(~%parameter2%~)
	LOOKUP_IDS_SYMBOL_OF_INT symbol ~%idsFile%~ ~%parameter1%~

	PATCH_IF NOT ~%symbol%~ STRING_EQUAL ~0~ BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
		SPRINT description @102452 // ~Paralyse les %creatureType%~
	END
	ELSE BEGIN
		SPRINT description @102454 // ~Paralyse le porteur~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_109~ BEGIN
	SPRINT idsFile $ids_files(~%parameter2%~)
	LOOKUP_IDS_SYMBOL_OF_INT symbol ~%idsFile%~ ~%parameter1%~

	PATCH_IF NOT ~%symbol%~ STRING_EQUAL ~0~ BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
		SPRINT description @102452 // ~Paralyse les %creatureType%~
	END
	ELSE BEGIN
		SPRINT description @102453 // ~Paralyse la cible~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_109~ BEGIN
	SPRINT idsFile $ids_files(~%parameter2%~)
	LOOKUP_IDS_SYMBOL_OF_INT symbol ~%idsFile%~ ~%parameter1%~

	PATCH_IF NOT ~%symbol%~ STRING_EQUAL ~0~ BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
		SPRINT description @102456 // ~de paralyser les %creatureType%~
	END
	ELSE BEGIN
		SPRINT description @102455 // ~de paralyser la cible~
	END
END

/* --------------------------------- *
 * Item: Create Magical Weapon [111] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_111~ BEGIN
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @102265 // ~Crée une arme magique (%itemName%)~
	END
END

/* --------------------------------- *
 * Cure: (Remove) Invisibility [116] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_116~ BEGIN
	SPRINT description @102223 // ~Dissipe toutes formes d'invisibilité~
END

DEFINE_PATCH_MACRO ~opcode_target_116~ BEGIN
	LPM ~opcode_self_116~ // TODO: Pas sûr du tout
END

/* -------------------------------- *
 * Spell Effect: Mirror Image [119] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_119~ BEGIN
	SPRINT description @102405 // ~Image miroir~
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
		PATCH_FAIL "%SOURCE_FILE% : Type d'arme %type% à gérer"
	END

	PATCH_IF type == 0 BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%enchantment%~ RET enchantment = value END
		SPRINT description @102176 // ~Immunité contre les %weaponType% %enchantment%~
	END
	ELSE PATCH_IF type == 1 OR type == 2 OR type == 3 OR type == 6 OR type == 7 OR type == 8 OR type == 98 BEGIN
        SPRINT description @102177 // ~Immunité contre les %weaponType%~
    END
END

/* --------------------------------- *
 * Item: Create Inventory Item [122] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_122~ BEGIN
	LPM ~opcode_target_122~
END

DEFINE_PATCH_MACRO ~opcode_target_122~ BEGIN
	LOCAL_SET amount = parameter1
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET description = itemName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF amount == 1 BEGIN
			SPRINT description @102263 // ~Crée un objet (%itemName%)~
		END
		ELSE BEGIN
			SPRINT description @102266 // ~Crée %amount% objets (%itemName%)~
		END
	END
	ELSE BEGIN
		PATCH_FAIL "%SOURCE_FILE% : opcode_self_122 nom de l'objet non trouvé : %resref%"
	END
END

/* ---------------------------------- *
 * Spell Effect: Unlock (Knock) [125] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_125~ BEGIN
	SPRINT description @102322 // ~Déverrouille la serrure ciblée~
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

DEFINE_PATCH_MACRO ~opcode_target_probability_126~ BEGIN
	// @102360 = ~de modifier la capacité de mouvement de la cible de %value%~
	// @102361 = ~de passer la capacité de mouvement de la cible à %value%~
	// @102362 = ~de multiplier la capacité de mouvement de la cible par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102360 strrefFlat = 102361 strrefPercent = 102362 STR_VAR value = ~%parameter1%~ RET description END
END

/* ---------------------- *
 * State: Confusion [128] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_target_128~ BEGIN
    SPRINT description @102386 // ~Inflige Confusion à la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_128~ BEGIN
    SPRINT description @102246 // ~d'infliger Confusion à la cible~
END

/* ---------------- *
 * State: Aid [129] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_target_129~ BEGIN
    SPRINT description @102373 // ~Aide sur la cible~
END

/* ------------------ *
 * State: Bless [130] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_130~ BEGIN
    SPRINT description @102196 // ~Bénédiction permanente~
END

/* --------------------------------------------------------------------- *
 * State: Raise Strength, Constitution, & Dexterity Non-Cumulative [132] *
 * --------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_132~ BEGIN
	PATCH_IF parameter1 < 0 BEGIN
     SPRINT description @102376 // ~Force, dextérité et constitution : Passe à 25~
	END
	ELSE PATCH_IF parameter1 > 0 BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%parameter1%~ RET value END
		SPRINT description @102375 // ~Force, dextérité et constitution : %value% (non cumulable)~
	END
END

/* --------------------------------------- *
 * Spell Effect: Luck Non-Cumulative [133] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_133~ BEGIN
	LOCAL_SET value = parameter1

	SPRINT value @10010        // ~Passe à %value%~
	SPRINT name @101075        // ~Chance~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_target_133~ BEGIN
	LOCAL_SET value = parameter1

	SPRINT value @10010        // ~Passe à %value%~
	SPRINT name @101075        // ~Chance~
	SPRINT target @101085      // ~de la cible~
	SPRINT description @100007 // ~%name% %target%%colon%%value%~
END

/* ----------------------------- *
 * Polymorph into Specific [135] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_135~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
	PATCH_IF NOT ~%creatureName%~ STRING_EQUAL ~~ BEGIN
        SPRINT description @102358 // ~Transforme le porteur en %creatureName%~
	END
	ELSE BEGIN
		PATCH_FAIL "%SOURCE_FILE%: opcode_self_135 : Nom de la créature introuvable"
	END
END

/* ------------------------------- *
 * Item: Create Item in Slot [143] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_143~ BEGIN
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET description = itemName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @102263 // ~Crée un objet (%itemName%)~
	END
	ELSE BEGIN
		PATCH_FAIL "%SOURCE_FILE% : opcode_self_143 nom de l'objet non trouvé : %resref%"
	END
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
	TO_LOWER resref

	PATCH_IF ~%resref%~ STRING_EQUAL ~lcarmor~ BEGIN
		SPRINT description @102460 // ~Permet de lancer des sorts~
	END
	ELSE BEGIN
		LPM ~opcode_target_146~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_146~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET description = spellName END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 BEGIN
		SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
		SPRINT description ~%description% (%castingLevelStr%)~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_146~ BEGIN
	LPM ~opcode_target_probability_146~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_146~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @102185 // ~de lancer le sort %spellName%~

		PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 BEGIN
			SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
			SPRINT description ~%description% (%castingLevelStr%)~
		END
	END
	ELSE BEGIN
		PATCH_FAIL "%SOURCE_FILE% : opcode_target_probability_146 nom du sort introuvable pour %resref%"
	END
END

/* ---------------------------------- *
 * Spell: Cast Spell (at Point) [148] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_148~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description ~%spellName%~

		PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 BEGIN
			SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
			SPRINT description ~%description% (%castingLevelStr%)~
		END
	END
	ELSE BEGIN
		PATCH_FAIL "%SOURCE_FILE% : opcode_self_148 nom du sort introuvable pour %resref%"
	END
END

DEFINE_PATCH_MACRO ~opcode_target_148~ BEGIN
	LPM ~opcode_self_148~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_148~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @102193 // ~de lancer le sort %spellName% sur le porteur~

		PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 BEGIN
			SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
			SPRINT description ~%description% (%castingLevelStr%)~
		END
	END
	ELSE BEGIN
		PATCH_FAIL "%SOURCE_FILE% : opcode_self_probability_148 nom du sort introuvable pour %resref%"
	END
END

/* ------------------------------ *
 * Summon: Replace Creature [151] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_target_151~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @102332 // ~Transforme la cible en %creatureName%~
	END
	ELSE BEGIN
		PATCH_FAIL "%SOURCE_FILE%: opcode_target_151 : parameter2 != 0 à gerer"
	END
END

/* ---------------------- *
 * State: Sanctuary [153] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_153~ BEGIN
	SPRINT description @102336 // ~Sanctuaire~
END

/* --------------------- *
 * State: Entangle [154] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_target_154~ BEGIN
	SPRINT description @102241 // ~Enchevêtre la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_154~ BEGIN
	SPRINT description @102324 // ~d'enchevêtrer la cible~
END

/* ------------------------ *
 * State: Minor Globe [155] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_155~ BEGIN
	SPRINT description @102244 // ~Globe mineur d'invulnérabilité permanent~
END

/* ----------------------------------------------------- *
 * State: Protection from Normal Missiles Cylinder [156] *
 * ----------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_156~ BEGIN
	SPRINT description @102245 // ~Protection contre les projectiles non-magiques~
END

DEFINE_PATCH_MACRO ~opcode_target_156~ BEGIN
	LPM ~opcode_self_156~
END

/* ----------------------- *
 * State: Web Effect [157] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_target_157~ BEGIN
	SPRINT description @102321 // ~Entoile la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_157~ BEGIN
	SPRINT description @102423 // ~d'entoiler la cible~
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

DEFINE_PATCH_MACRO ~opcode_target_162~ BEGIN
	SPRINT description @102404 // ~Guérison à la paralysie~
END

/* ----------------------------- *
 * Protection: Free Action [163] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_163~ BEGIN
	SPRINT description @102234 // ~Action libre~
END

/* -------------------------------- *
 * Spell Effect: Pause Target [165] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_165~ BEGIN
	LPM ~opcode_self_45~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_165~ BEGIN
	LPM ~opcode_self_probability_45~
END

/* ------------------------------------- *
 * Stat: Magic Resistance Modifier [166] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_166~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 102060 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à la magie~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_166~ BEGIN
	// @102355 = ~de modifier la résistance à la magie du porteur de %value%~
	// @102356 = ~de passer la résistance à la magie du porteur à %value%~
	// @102357 = ~de multiplier la résistance à la magie du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102355 strrefFlat = 102356 strrefPercent = 102357 STR_VAR value = ~%parameter1%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_166~ BEGIN
	LPF ~opcode_target_mod_percent~ INT_VAR strref = 102060 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à la magie~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_166~ BEGIN
	// @102333 = ~de modifier la résistance à la magie de la cible de %value%~
	// @102334 = ~de passer la résistance à la magie de la cible à %value%~
	// @102335 = ~de multiplier la résistance à la magie de la cible par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102333 strrefFlat = 102334 strrefPercent = 102335 STR_VAR value = ~%parameter1%~ RET description END
END

/* ------------------------------------- *
 * Stat: THAC0 Modifier with Missile Weapons [167] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_167~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102235 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 des armes à projectiles~
END

/* -------------------------------- *
 * Spell: Give Innate Ability [171] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_171~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET description = spellName END
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
DEFINE_PATCH_MACRO ~opcode_target_175~ BEGIN
	LPM ~opcode_target_109~
END

/* --------------------- *
 * Capacité de mouvement *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_176~ BEGIN
	LPM ~opcode_self_126~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_176~ BEGIN
	// @102409 = ~de modifier la capacité de mouvement du porteur de %value%~
	// @102410 = ~de passer la capacité de mouvement du porteur à %value%~
	// @102411 = ~de multiplier la capacité de mouvement du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102409 strrefFlat = 102410 strrefPercent = 102411 STR_VAR value = ~%parameter1%~ RET description END
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

DEFINE_PATCH_MACRO ~opcode_target_probability_177~ BEGIN
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
	PATCH_FAIL "%SOURCE_FILE%: opcode 177 à gérer %idsFile% (%parameter1%)"
	// Applique un effet à une creature
END

/* ---------------------------------------------------- *
 * Spell Effect: THAC0 vs. Creature Type Modifier [178] *
 * ---------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_178~ BEGIN
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END

	SPRINT name @102000 // TAC0
	SET parameter2 = MOD_TYPE_cumulative
	LPF ~opcode_mod~ INT_VAR strref = 100008 STR_VAR value = EVAL ~%power%~ RET description END
END

/* ----------------------------------------------------- *
 * Spell Effect: Damage vs. Creature Type Modifier [179] *
 * ----------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_179~ BEGIN
	LPM ~opcode_target_179~
END

DEFINE_PATCH_MACRO ~opcode_target_179~ BEGIN
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END

	SET parameter2 = MOD_TYPE_cumulative
	LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount = ~%power%~ RET value = damage END

	SPRINT name @102001 // Dégâts
	SPRINT description @100009 // ~%name%%colon%%value% %versus%~
END

/* --------------------------------- *
 * Paralyse les créatures de type xx *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_185~ BEGIN
	LPM ~opcode_target_109~
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

DEFINE_PATCH_MACRO ~opcode_self_probability_190~ BEGIN
	// @102340 = ~de modifier le facteur de vitesse du porteur de %value%~
	// @102341 = ~de passer le facteur de vitesse du porteur à %value%~
	// @102342 = ~de multiplier le facteur de vitesse du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102340 strrefFlat = 102341 strrefPercent = 102342 STR_VAR value = ~%parameter1%~ RET description END
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
		DEFAULT PATCH_FAIL "%SOURCE_FILE% : Opcode %opcode% : Réflection du Type de projectile '%parameter2%' à gérer"
    END
END

/* -------------------------- *
 * Spell: Bounce Spells [199] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_199~ BEGIN
	LOCAL_SET spellLevel = parameter1
	SPRINT description @102305 // ~Renvoi les sorts de niveau %spellLevel%~
END

/* --------------------------------------- *
 * Spell: Decrementing Bounce Spells [200] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_200~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2

	SPRINT description @102372 // ~Renvoi jusque %amount% sorts de niveau %spellLevel%~
END

/* ---------------------------------------- *
 * Spell: Decrementing Spell Immunity [201] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_201~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102346 // ~Absorbe 1 sort de niveau %spellLevel%~
	END
	ELSE BEGIN
		SPRINT description @102347 // ~Absorbe %amount% sorts de niveau %spellLevel%~
	END
END

/* ------------------------------------------- *
 * Spell: Protection from Spell (School) [204] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_204~ BEGIN
	LOCAL_SET school = parameter2
	LOCAL_SET strref = 102150

	PATCH_IF school == 0 BEGIN
		PATCH_FAIL "%SOURCE_FILE% : opcode_self_204 école 0 à gérer"
	END
	ELSE BEGIN
		SET strref += school
		SPRINT description (AT ~%strref%~) //  ~Immunité aux sorts de l'école de xxxx~
	END
END

/* --------------------------------------------------- *
 * Spell: Protection from Spell (Secondary Type) [205] *
 * --------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_205~ BEGIN
	LOCAL_SET strref = 102390 + parameter2

	SPRINT description (AT ~%strref%~)
END

/* ------------------ *
 * Immunité à un sort *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_206~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF ~%spellName%~ STRING_EQUAL ~~ BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Aucune chaine trouvee pour le sort '%resref%'~
	END
	ELSE BEGIN
		SPRINT description @102035 // ~Immunité à %spellName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_206~ BEGIN
	LPM ~opcode_self_206~ // TODO: Améliorer ?
END

DEFINE_PATCH_MACRO ~opcode_target_probability_206~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF ~%spellName%~ STRING_EQUAL ~~ BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Aucune chaine trouvee pour le sort '%resref%'~
	END
	ELSE BEGIN
		SPRINT description @102289 // ~d'immuniser au sort %spellName%~
	END
END

/* ----------------------------------- *
 * Spell: Bounce Specified Spell [207] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_207~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @102317 // ~Renvoi le sort %spellName%~
END

/* --------------------- *
 * Points de vie minimum *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_208~ BEGIN
	SPRINT value ~%parameter1%~
	SPRINT description @102109 // ~Les points de vie ne peuvent passer en dessous de %value%~
END

/* ------------------------ *
 * Spell Effect: Maze [213] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_target_probability_213~ BEGIN
	SPRINT description @102448 // ~d'enfermer la cible dans un labyrinthe~
END

/* ----------------------------------- *
 * Lancer un sort parmis une sélection *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_214~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @102106 //  ~Permet de lancer n'importe quel sort de son livre de sorts~
	END
	ELSE BEGIN
		PATCH_FAIL  ~%SOURCE_FILE% : Opcode %opcode% : Lire les sorts utilisables depuis le fichier 2da %resref%~
	END
END

/* --------------- *
 * Drain de niveau *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_self_216~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102291 // ~Draîne un niveau au porteur~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @102292 // ~Draîne %amount% niveaux au porteur~
	END
	ELSE BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Niveau draine negatif !!~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_216~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102113 // ~Draîne un niveau à la cible~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @102114 // ~Draîne %amount% niveaux à la cible~
	END
	ELSE BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Niveau draine negatif !!~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_216~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102141 // ~de draîner un niveau à la cible~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @102142 // ~de draîner %amount% niveaux à la cible~
	END
	ELSE BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Niveau draine negatif !!~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_216~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102186 // ~de draîner un niveau au porteur~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @102187 // ~de draîner %amount% niveaux au porteur~
	END
	ELSE BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Niveau draine negatif !!~
	END
END

/* --------------------------- *
 * Protection: Stoneskin [218] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_218~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF amount > 1 BEGIN
		SPRINT description @102260 // ~Peau de pierre (%amount% peaux)~
	END
	ELSE BEGIN
		SPRINT description @102259 // ~Peau de pierre (1 peau)~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_218~ BEGIN
	LPM ~opcode_self_218~
END

/* ----------------------------------------- *
 * Stat: AC vs. Creature Type Modifier [219] *
 * ----------------------------------------- */
// AC
DEFINE_PATCH_MACRO ~opcode_self_219000~ BEGIN
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END

	SPRINT value ~+2 %versus%~
	SPRINT name @102008        // ~Classe d'armure~
	SPRINT description @100001 // ~%name%%colon%%value%~
END
// Save throws
DEFINE_PATCH_MACRO ~opcode_self_219001~ BEGIN
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END

	SPRINT value ~+2 %versus%~
	SPRINT name @102034        // ~Jets de sauvegarde~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

/* ---------------------------- *
 * Removal: Remove School [220] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_220~ BEGIN
	LOCAL_SET school = parameter2

	PATCH_IF school > 0 BEGIN
		// Dissipe tous les sorts de l'école de %school% de niveau %level% et moins
		PATCH_FAIL "%SOURCE_FILE% : opcode_self_220 à gérer"
	END
END

/* ---------------------------------------- *
 * Removal: Remove One Secondary Type [230] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_230~ BEGIN
	LOCAL_SET maxLevel = parameter1

	PATCH_MATCH parameter2 WITH
		1 BEGIN SPRINT description @102374 END // ~Dissipe un sort de protection de niveau inférieur ou égal à %maxLevel%~
		DEFAULT PATCH_FAIL "%SOURCE_FILE% : Opcode %opcode% : Type d'effet à dissiper '%parameter2%' à gérer"
    END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_230~ BEGIN
	LOCAL_SET maxLevel = parameter1

	PATCH_MATCH parameter2 WITH
		1 BEGIN SPRINT description @102382 END // ~de dissiper un sort de protection de niveau inférieur ou égal à %maxLevel%~
		DEFAULT PATCH_FAIL "%SOURCE_FILE% : opcode_target_probability_230 : Type d'effet à dissiper '%parameter2%' à gérer"
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
DEFINE_PATCH_MACRO ~opcode_target_235~ BEGIN
	SPRINT description @102264 // ~Renverse et sonne la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_235~ BEGIN
	SPRINT description @102174 // ~de renverser et sonner la cible~
END

/* ------------------------- *
 * Death: Disintegrate [238] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_238~ BEGIN
	SPRINT description @102383 // ~Désintègre la cible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_238~ BEGIN
	SPRINT description @102194 // ~de désintégrer la cible~
END

/* ---------------------------- *
 * Spell Effect: Farsight [239] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_239~ BEGIN
	SPRINT description @102257 // ~Permet de voir au loin~
END

/* ------------------------------- *
 * Spell: Drain Wizard Spell [244] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_244~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102338 // ~Fait oublier 1 sort à la cible~
	END
	ELSE BEGIN
		SPRINT description @102339 // ~Fait oublier %amount% sorts à la cible~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_244~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF amount == 1 BEGIN
		SPRINT description @102443 // ~de faire oublier 1 sort à la cible~
	END
	ELSE BEGIN
		SPRINT description @102444 // ~de faire %amount% sorts à la cible~
	END
END

/* ---------------------------------------- *
 * Spell Effect: Damage Luck Modifier [250] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_250~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102270 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts minimum~
END

/* ---------------------------------------- *
 * Item: Create Inventory Item (days) [255] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_255~ BEGIN
	LPM ~opcode_target_122~
END

DEFINE_PATCH_MACRO ~opcode_target_255~ BEGIN
	LPM ~opcode_target_122~
END

/* ---------------------------- *
 * Protection: Spell Trap [259] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_259~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2

	SPRINT description @102381 // ~Emprisonne jusque %amount% niveaux de sorts de niveau %spellLevel%~
END

/* -------------------------------- *
 * Spell: Restore Lost Spells [261] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_261~ BEGIN
	LOCAL_SET spellLevel = parameter1

	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @102329 // ~Remémorise un sort profane de niveau %spellLevel%~
	END
	ELSE BEGIN
		SPRINT description @102330 // ~Remémorise un sort divin de niveau %spellLevel%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_261~ BEGIN
	LOCAL_SET spellLevel = parameter1

	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @102353 // ~de remémoriser un sort profane de niveau %spellLevel%~
	END
	ELSE BEGIN
		SPRINT description @102354 // ~de remémoriser un sort divin de niveau %spellLevel%~
	END
END

/* --------------- *
 * Champ de vision *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_self_262~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF value < 0 BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Valeur negative pour le champ de vision a gerer~
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

DEFINE_PATCH_MACRO ~opcode_self_probability_278~ BEGIN
	// @102406 = ~de modifier les chances de toucher du porteur de %value%~
	// @102407 = ~de passer les chances de toucher du porteur à %value%~
	// @102408 = ~de multiplier les chances de toucher du porteur par %value%~
	LPF ~opcode_self_probability~ INT_VAR strrefCumul = 102406 strrefFlat = 102407 strrefPercent = 102408 STR_VAR value = ~%parameter1%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_278~ BEGIN
	LPF ~opcode_target_mod~ INT_VAR strref = 102036 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Chances de toucher~
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
			PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : A gerer pour capacite de charge et parameter2 = %parameter2% (etrange)~
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

DEFINE_PATCH_MACRO ~opcode_target_284~ BEGIN
	LPF ~opcode_target_mod_percent~ INT_VAR strref = 102237 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 des armes de mêlée~
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
	LOCAL_SET score = 20 - parameter1

	SPRINT description @102093 // ~Un coup critique est déclenché à partir d'un score de %score%~
END

/* ---------------------------- *
 * Item: Can Use Any Item [302] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_302~ BEGIN
	SPRINT description @102371 // ~Permet d'utiliser n'importe quel objet (si les statistiques sont suffisantes)~
END

/* ------------------------------------- *
 * Stat: THAC0 Modifier (Off-Hand) [305] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_305~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 102010 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 de la main secondaire~
END

/* ------------------------------- *
 * Protection: from Timestop [310] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_310~ BEGIN
	SPRINT description @102258 // ~Immunité à l'arrêt du temps~
END

/* ------------------------- *
 * Spell: Magical Rest [316] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_probability_316~ BEGIN
	SPRINT description @102451 // ~de reposer le porteur~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_316~ BEGIN
	SPRINT description @102351 // ~de reposer la cible~
END

/* ------------------- *
 * State: Haste2 [317] *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_self_317~ BEGIN
	LPM ~opcode_self_16~
END

DEFINE_PATCH_MACRO ~opcode_mod_base~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10010 // ~Passe à %value%~
	END
	ELSE BEGIN // percent
		SET value -= 100
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT value @10002 // ~%value% %~
	END
	SPRINT name (AT ~%strref%~)
END

DEFINE_PATCH_FUNCTION ~opcode_mod~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	LPM ~opcode_mod_base~

	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_FUNCTION ~opcode_target_mod~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	LPM ~opcode_mod_base~

	SPRINT target @101085 // ~de la cible~
	SPRINT description @100007 // ~%name% %target%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_mod_percent_base~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT value @10002 // ~%value% %~
		SPRINT name (AT ~%strref%~)
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10002 // ~%value% %~
		SPRINT value @10010 // ~Passe à %value%~
		SPRINT name (AT ~%strref%~)
	END
	ELSE BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Valeur du second parametre invalide (%parameter2%), l'effet est annule ~
	END
END
DEFINE_PATCH_FUNCTION ~opcode_mod_percent~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	LPM ~opcode_mod_percent_base~

	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_FUNCTION ~opcode_target_mod_percent~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	LPM ~opcode_mod_percent_base~

	SPRINT target @101085 // ~de la cible~
	SPRINT description @100007 // ~%name% %target%%colon%%value%~
END

DEFINE_PATCH_FUNCTION ~opcode_save_vs~ INT_VAR strref = 0 group = 0 target = 0 STR_VAR value = ~~ RET description BEGIN
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
		SET value -= 100
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT value @10002 // ~%value% %~
		SPRINT name ~%name% %strSave%~
	END

	PATCH_IF target == 1 BEGIN
		SPRINT target @101085 // ~de la cible~
		SPRINT description @101123 // ~%name% %target%%colon%%value%~
	END ELSE PATCH_IF group == 1 BEGIN
		SPRINT target @101088 // ~du groupe~
		SPRINT description @101123 // ~%name% %target%%colon%%value%~
	END
	ELSE BEGIN
		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END

DEFINE_PATCH_FUNCTION ~opcode_self_probability~ INT_VAR strrefCumul = 0 strrefFlat = 0 strrefPercent = 0 RET description BEGIN
	SET value = ~%parameter1%~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT description (AT ~%strrefCumul%~) // ~de modifier [a statistic] du porteur de %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description (AT ~%strrefFlat%~) // ~de passer [a statistic] du porteur à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description (AT ~%strrefPercent%~) // ~de multiplier [a statistic] du porteur par %value%~
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_name~ STR_VAR file = "" RET spellName BEGIN
	SPRINT spellName ~~
	SPRINT itemFilename ~%SOURCE_FILE%~
	INNER_ACTION BEGIN
		SILENT
		ACTION_IF FILE_EXISTS_IN_GAME ~%file%.spl~ BEGIN
			COPY_EXISTING ~%file%.spl~ ~override~
				READ_LONG SPL_unidentified_name spellNameRef
				PATCH_IF spellNameRef > 0 BEGIN
					READ_STRREF SPL_unidentified_name spellName
				END
				ELSE BEGIN
					PATCH_FAIL "%itemFilename% : Opcode %opcode% : Nom du sort introuvable pour %file%.spl"
				END
			BUT_ONLY_IF_IT_CHANGES
		END
		ELSE BEGIN
			FAIL "%SOURCE_FILE% : Opcode %opcode% : La ressource %file%.spl n'existe pas"
		END
        VERBOSE
    END
END

DEFINE_PATCH_FUNCTION ~get_item_name~ STR_VAR file = "" RET itemName BEGIN
	SPRINT itemName ~~
	SPRINT itemFilename ~%SOURCE_FILE%~
	INNER_ACTION BEGIN
		SILENT
		ACTION_IF FILE_EXISTS_IN_GAME ~%file%.itm~ BEGIN
			COPY_EXISTING ~%file%.itm~ ~override~
				READ_LONG SPL_unidentified_name itemNameRef
				PATCH_IF itemNameRef > 0 BEGIN
					READ_STRREF ITM_identified_name itemName
				END
				ELSE BEGIN
					PATCH_FAIL "%itemFilename% : Opcode %opcode% : Nom de l'objet introuvable pour %file%.itm"
				END
			BUT_ONLY_IF_IT_CHANGES
		END
		ELSE BEGIN
			FAIL "%SOURCE_FILE% : Opcode %opcode% : La ressource %file%.itm n'existe pas"
		END
        VERBOSE
    END
END

DEFINE_PATCH_FUNCTION ~get_creature_name~ STR_VAR file = "" RET creatureName BEGIN
	SPRINT creatureName ~~
	SPRINT itemFilename ~%SOURCE_FILE%~
	INNER_ACTION BEGIN
		SILENT
		ACTION_IF FILE_EXISTS_IN_GAME ~%file%.cre~ BEGIN
			COPY_EXISTING ~%file%.cre~ ~override~
				READ_LONG CRE_name spellNameRef
				PATCH_IF spellNameRef > 0 BEGIN
					READ_STRREF CRE_name creatureName
				END
				ELSE BEGIN
					PATCH_FAIL "%itemFilename% : Opcode %opcode% : Nom de la créature introuvable pour %file%.cre"
				END
			BUT_ONLY_IF_IT_CHANGES
		END
		ELSE BEGIN
			FAIL "%SOURCE_FILE% : Opcode %opcode% : La ressource %file%.cre n'existe pas"
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
            SPRINT description (AT %strref%) // ~Suppression d'un sort [profane|divin] de niveau %levelStr%~
        END
        ELSE BEGIN
			SET strref = startStrref + 3
            SPRINT description (AT %strref%) // ~Suppression de %amount% sorts [profanes|divins] de niveau %levelStr%~
        END
	END
END


DEFINE_PATCH_FUNCTION ~get_ids_name~ INT_VAR entry = 0 file = 0 RET idName BEGIN
	PATCH_IF VARIABLE_IS_SET $ids_files(~%file%~) BEGIN
		SET strref = 200000 + (file * 1000) + entry

		SPRINT idName (AT ~%strref%~)
	END
	ELSE BEGIN
		SPRINT idName ~~
		PATCH_FAIL "%SOURCE_FILE%: opcode %opcode%: Fichier ids numero '%file%' n'existe pas. Objet corrompu ?"
	END
END


DEFINE_PATCH_FUNCTION ~get_ids_versus_name~ INT_VAR entry = 0 file = 0 RET idVersusName BEGIN
	PATCH_IF VARIABLE_IS_SET $ids_files(~%file%~) BEGIN
		LPF ~get_ids_name~ INT_VAR entry file RET name = idName END

		SPRINT idVersusName @101126 // ~contre les %name%~
	END
	ELSE BEGIN
		SPRINT idVersusName ~~
		PATCH_FAIL "%SOURCE_FILE%: opcode %opcode%: Fichier ids numero '%file%' n'existe pas. Objet corrompu ?"
	END
END