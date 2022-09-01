/*
 * Tableau servant à savoir comment trier le résultat final.
 * Vu qu'ils ne sont généralement pas
 */
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~sort_opcodes~ BEGIN
	147 => 0   // Spell: Learn Spell [147]
	360 => 0   // Stat: Ignore Reputation Breaking Point [360]
	283 => 0   // Use EFF File (Cursed) [283]
	318 => 0   // Protection: Immunity Spell [318]
	324 => 0   // Protection: Immunity to Resource and Message [324]
	216 => 1   // Spell Effect: Level Drain [216]
	344 => 1   // Enchantment vs. creature type [344]
	  0 => 2   // Stat: AC vs. Damage Type Modifier [0]
 219000 => 3   // Stat: AC vs. Creature Type Modifier [219]
	 54 => 4   // Stat: THAC0 Modifier [54]
	178 => 5   // Spell Effect: THAC0 vs. Creature Type Modifier [178]
	306 => 6   // Stat: THAC0 Modifier (On-Hand) [306]
	305 => 6   // Stat: THAC0 Modifier (Off-Hand) [305]
	284 => 7   // Stat: Melee THAC0 Modifier [284]
	167 => 8   // Stat: THAC0 Modifier with Missile Weapons [167]
	288 => 8   // Stat: Fist THAC0 Modifier [288]
	278 => 9   // Stat: To Hit Modifier [278]
 219001 => 10  // Stat: AC vs. Creature Type Modifier [219]
	325 => 11  // Stat: Save vs. all [325]
	 33 => 11  // Stat: Save vs. Death Modifier [33]
	 34 => 12  // Stat: Save vs. Wands Modifier [34]
	 35 => 13  // Stat: Save vs. Petrification/Polymorph Modifier [35]
	 36 => 14  // Stat: Save vs. Breath Weapons Modifier [36]
	 37 => 15  // Stat: Save vs. Spells Modifier [37]
	346 => 16  // Save vs. school bonus [346]
	 12 => 16  // HP: Damage [12]
	 73 => 17  // Stat: Extra Damage Modifier [73]
	332 => 17  // Stat: Specific Damage Modifier [332] : EE only
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
	132 => 40  // State: Raise Strength, Constitution, & Dexterity Non-Cumulative [132]
	 44 => 41  // Stat: Strength Modifier [44]
	 97 => 42  // Stat: Strength-Bonus Modifier [97]
	 15 => 43  // Stat: Dexterity Modifier [15]
	 10 => 44  // Stat: Constitution Modifier [10]
	 19 => 45  // Stat: Intelligence Modifier [19]
	 49 => 46  // Stat: Wisdom Modifier [49]
	  6 => 47  // Stat: Charisma Modifier [6]
	 22 => 48  // Stat: Luck Modifier [22]
	281 => 60  // Stat: Wild Magic [281]
	301 => 90  // Stat: Critical Hit Modifier [301]
	362 => 91  // Critical miss bonus [362]
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
	343 => 140 // HP Swap [343]
	 17 => 145 // Stat: Current HP Modifier [17]
	323 => 146 // Stat: Turn Undead Level [323]
	 23 => 149 // Stat: Morale Modifier [23]
	106 => 150 // Stat: Morale Break [106]
	 21 => 155 // Stat: Lore Modifier [21]
	262 => 157 // Stat: Visual Range [262]
	 93 => 160 // Stat: Fatigue Modifier [93]
	104 => 161 // Stat: Experience Points [104]
	108 => 165 // Stat: Reputation [108]
	 94 => 163 // Stat: Drunkenness Modifier [94]
	 95 => 164 // Stat: Tracking Skill Modifier [95]
	105 => 165 // Stat: Gold [105]
	 16 => 169 // State: Haste [16]
	317 => 169 // State: Haste2 [317]
	130 => 170 // State: Bless [130]
	129 => 171 // State: Aid [129]
	 20 => 173 // State: Invisibility [20]
	 65 => 174 // State: Blur [65]
	 63 => 175 // State: Infravision [63]
	 64 => 175 // State: Remove Infravision [64]
	 40 => 176 // State: Slow [40]
	  3 => 177 // State: Berserking [3]
	246 => 177 // Spell Effect: Berserking [246]
	245 => 177 // Check For Berserk [245]
	247 => 177 // Spell Effect: Attack Nearest Creature [247]
	 24 => 178 // State: Horror [24]
	 74 => 179 // State: Blindness [74]
	 45 => 180 // State: Stun [45]
	210 => 180 // Spell Effect: Stun 90HP [210]
	165 => 180 // Spell Effect: Pause Target [165]
	 80 => 181 // Deafness [80]
	 39 => 183 // State: Unconsciousness [39]
	217 => 183 // Spell Effect: Unconsciousness 20HP [217]
	128 => 184 // State: Confusion [128]
	 38 => 185 // State: Silence [38]
	134 => 186 // State: Petrification [134]
	109 => 188 // State: Hold Creature I [109]
	175 => 188 // State: Hold Creature II [175]
	185 => 188 // State: Hold Creature III [185]
	157 => 189 // State: Web Effect [157]
	 76 => 190 // State: Feeblemindedness [76]
	136 => 190 // State: Force Visible [136]
	153 => 190 // Overlay: Sanctuary [153]
	 55 => 191 // Death: Kill Creature Type [55]
	209 => 192 // Death: Kill 60HP [209]
	 13 => 193 // Death: Instant Death [13]
	238 => 194 // Death: Disintegrate [238]
	206 => 197 // Spell: Protection from Spell [206]
	224 => 199 // Cure: Level Drain (Restoration) [224]
	 58 => 200 // Cure: Dispellable Effects (Dispel Magic) [58]
	160 => 200 // Remove Sanctuary [160]
	162 => 201 // Cure: Hold [162]
	161 => 202 // Cure: Fear [161]
	 48 => 204 // Cure: Silence (Vocalize) [48]
	 79 => 205 // Cure: Disease [79]
	 11 => 206 // Cure: Poison [11]
	 75 => 207 // Cure: Blindness [75]
	 81 => 208 // Cure: Deafness [81]
	 77 => 209 // Cure: Feeblemindedness [77]
	116 => 210 // Cure: (Remove) Invisibility [116]
	 32 => 211 // Cure: Death (Raise Dead) [32]
	  4 => 213 // Cure: Berserking [4]
	 46 => 214 // Cure: Stun (Unstun) [46]
	 47 => 215 // Cure: Invisibility [47]
	 43 => 216 // Cure: Stone to Flesh [43]
	 14 => 216 // Graphics: Defrost [14]
	  2 => 217 // Cure: Sleep [2]
	242 => 218 // Cure: Confusion [242]
	 70 => 219 // Cure: Non-Detection [2]
	164 => 219 // Cure: Drunkeness [164]
    101 => 220 // Protection: from Opcode [101]
	163 => 229 // Protection: Free Action [163]
	223 => 230 // Spell: Immunity (by School, decrementing [223]
	226 => 230 // Spell: Immunity (by Secondary Type, decrementing) [226]
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
	 69 => 240 // Protection: From Detection (Non-Detection) [69]
	212 => 241 // Protection: Freedom [212]
	172 => 244 // Spell: Remove Spell [172]
	272 => 245 // Spell: Apply Repeating EFF [272]
	148 => 245 // Spell: Cast Spell (at Point) [148]
	311 => 245 // Spell: Random Wish Spell [311]
	201 => 246 // Spell: Decrementing Spell Immunity [201]
	199 => 247 // Spell: Bounce Spells [199]
	202 => 247 // Spell: Bounce (by School) [202]
	203 => 247 // Spell: Bounce (by Secondary Type) [203]
	227 => 247 // Spell: Bounce (by School, decrementing) [227]
	228 => 247 // Spell: Bounce (by Secondary Type, decrementing) [228]
	200 => 248 // Spell: Decrementing Bounce Spells [200]
	207 => 249 // Spell: Bounce Specified Spell [207]
	197 => 250 // Spell: Bounce Projectile [197]
	232 => 250 // Spell Effect: Cast Spell on Condition [232]
	326 => 251 // Apply Effects List [326]
	303 => 252 // Spell Effect: Backstab Every Hit [303]
	231 => 253 // Spell Effect: Time Stop [231]
	188 => 254 // Spell Effect: Aura Cleansing [188]
	119 => 255 // Spell Effect: Mirror Image [119]
	159 => 256 // Spell Effect: Mirror Image (Exact Number) [159]
	280 => 257 // Spell Effect: Wild Magic [280]
	235 => 258 // Spell Effect: Wing Buffet [235]
	239 => 259 // Spell Effect: Farsight [239]
	125 => 260 // Spell Effect: Unlock (Knock) [125]
	213 => 261 // Spell Effect: Maze [213]
	211 => 262 // Spell Effect: Imprisonment [211]
	329 => 263 // Spell Effect: Slow Poison [329] : EE only
	124 => 264 // Spell Effect: Teleport (Dimension Door) [124]
	274 => 267 // Spell Effect: Teleport to Target [274]
	222 => 268 // Spell Effect: Teleport Field [222]
	150 => 269 // Spell Effect: Find Traps [150]
	268 => 270 // Spell Effect: Explore (Wizard Eye) [268]
	117 => 271 // Spell Effect: Reveal Area [117]
	236 => 272 // Spell Effect: Image Projection [236]
	316 => 275 // Spell: Magical Rest [316]
	131 => 276 // State: Positive Chant [131]
	137 => 277 // State: Negative Chant [137]
	133 => 278 // Spell Effect: Luck Non-Cumulative [133]
	  5 => 279 // Charm: Charm Specific Creature [5]
	241 => 280 // Charm: Control Creature [241]
	115 => 281 // Detect: Alignment [115]
	 57 => 282 // Alignment: Change [57]
	 56 => 283 // Alignment: Invert [56]
	 71 => 284 // Sex Change [71]
	111 => 285 // Item: Create Magical Weapon [111]
	143 => 286 // Item: Create Item in Slot [143]
	122 => 287 // Item: Create Inventory Item [122]
	255 => 288 // Item: Create Inventory Item (days) [255]
	302 => 289 // Item: Can Use Any Item [302]
	180 => 289 // Item: Can't Use Item [180]
	181 => 289 // Item: Can't Use Itemtype [181]
	 26 => 290 // Item: Remove Curse [26]
	248 => 291 // Item: Set Melee Effect [248]
	249 => 292 // Item: Set Ranged Effect [249]
	243 => 292 // Item: Drain Item Charges [243]
	341 => 293 // Spell Effect: Change Critical Hit Effect [341]
	361 => 293 // Cast spell on critical miss [361]
	340 => 294 // Spell Effect: Change Backstab Effect [340]
	127 => 295 // Summon: Monster Summoning [127]
	331 => 295 // Summon: Random Monster Summoning [331]
	 68 => 295 // Summon: Unsummon Creature [68]
	151 => 296 // Summon: Replace Creature [151]
	135 => 297 // Polymorph into Specific [135]
	321 => 298 // Removal: Effects specified by Resource [321]
	220 => 298 // Removal: Remove School [220]
	221 => 298 // Removal: Remove Secondary Type [221]
	229 => 298 // Removal: Remove One School [229]
	230 => 298 // Removal: Remove One Secondary Type [230]
	193 => 299 // Spell Effect: Invisible Detection by Script [193]
	144 => 300 // Button: Disable Button [144]
	300 => 301 // NPC Bump [300]

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
	  7 => 0 // Colour: Set Character colours by Palette
	  8 => 0 // Colour: Change by RGB [8]
	  9 => 0 // Colour: Glow Pulse
	 41 => 0 // Graphics: Sparkle [41]
	 50 => 0 // Colour: Glow by RGB (Brief)
	 51 => 0 // Colour: Strong/Dark by RGB [51]
	 52 => 0 // Colour: Very Bright by RGB [52]
	 53 => 0 // Graphics: Animation Change [53]
	 61 => 0 // Creature RGB color fade [61]
	 65 => 0 // Overlay: Blur [65]
	 66 => 0 // Graphics: Transparency Fade [66]
	 72 => 0 // State: Set IDS State [72]
	 82 => 0 // Set AI Script [82]
	103 => 0 // Text: Change Name [103]
	107 => 0 // Portrait Change [107]
	110 => 0 // (Retreat From) [110]
	112 => 1 // Item: Remove Item [112]
	114 => 0 // Graphics: Dither [114]
	123 => 1 // Item: Remove Inventory Item
	138 => 0 // Graphics: Character Animation Change [138]
	139 => 0
	140 => 0 // Graphics: Casting Glow [140]
	141 => 0
	142 => 0
	152 => 0 // Spell Effect: Play Movie [152]
	154 => 0 // Overlay: Entangle [154]
	155 => 0 // Overlay: Minor Globe [155]
	156 => 0 // Overlay: Protection from Normal Missiles Cylinder [156]
	158 => 0 // State: Grease [158]
	168 => 0 // Summon: Remove Creature [168]
	169 => 0
	170 => 0 // Graphics: Play Damage Animation [170]
	174 => 0 // Spell Effect: Play Sound Effect [174]
	182 => 0 // Item: Apply Effect Item [182]
	183 => 0 // Item: Apply Effect Itemtype [183]
	184 => 0 // Graphics: Passwall (Don't Jump) [184]
	186 => 0 // Script: MoveToArea [186] // A gérer ??
	187 => 0 // Script: Store Local Variable [187]
	192 => 1 // Spell Effect: Find Familiar [192]
	194 => 0 // Ignore Dialog Pause [194]
	195 => 1 // Spell Effect: Death Dependent Constitution Loss (Familiar Bond) [195]
	196 => 1 // Spell Effect: Familiar Block [196]
	198 => 1 // Spell: Bounce (by Opcode) [198]
	215 => 0
	225 => 0 // Spell: Reveal Magic [225]
	234 => 0 // Spell Effect: Contingency Creation [234]
	237 => 0 // Spell Effect: Puppet ID [237]
	240 => 0 // Graphics: Remove Special Effect Icon [240]
	251 => 1 // Spell Effect: Change Bard Song Effect [251]
	252 => 1 // Spell Effect: Set Trap [252]
	253 => 0 // Spell Effect: Add Map Marker [253]
	254 => 0 // Spell Effect: Remove Map Marker [254]
	256 => 0 // Spell: Spell Sequencer Active [256]
	257 => 0 // Spell: Spell Sequencer Creation [257]
	258 => 0 // Spell: Spell Sequencer Activation [258]
	260 => 0 //
	264 => 1 // Spell Effect: Drop Weapons in Panic [264]
	265 => 0 // Script: Set Global Variable [265]
	266 => 1 // Spell: Remove Protection from Spell [266]
	267 => 0
	269 => 0 // Spell Effect: Shake Window [269]
	270 => 0 // Cure: Unpause Target [270]
	271 => 0 // Graphics: Avatar Removal [271]
	279 => 1 // Button: Enable Button [279]
	282 => 0 // Script: Scripting State Modifier [282]
	287 => 0 // Graphics: Selection Circle Removal [287]
	290 => 0 // Text: Change Title [290]
	291 => 0 // Graphics: Disable Visual Effect [291]
	293 => 0 // Script: Enable Offscreen AI [293]
	294 => 0 // Existance Delay Override [294]
	295 => 0
	296 => 0
	297 => 0 // Text: Protection from Display Specific String [297]
	298 => 0 // Spell Effect: Execute Script cut250a [298]
	299 => 1 // Spell Effect: Chaos Shield [299]
	304 => 1 // Mass Raise Dead [304]
	307 => 0 // Ranger Tracking Ability [307]
	308 => 0 // Protection: From Tracking [308]
	309 => 0 // Script: Set/Modify Local Variable [309]
	312 => 0
	313 => 0 // High-Level Ability Denotation [313]
	314 => 1 // Spell: Golem Stoneskin [314]
	315 => 0 // Graphics: Animation Removal [315]
	// EE only
	319 => 0 // Item Usability [319] // Pas nécessaire de le gérer, l'utilisabilité est gérée automatiquement par EE
	320 => 0 // Change Weather [320]
	327 => 0 // Graphics: Icewind Visual Spell Hit (plays sound) [327]
	328 => 0 // State: Set State [328]
	330 => 0 // Text: Float Text [330]
	333 => 1 // Spell Effect: Static Charge [333]
	334 => 0 // Spell Effect: Turn Undead [334]
	335 => 1 // Spell Effect: Seven Eyes [335]
	336 => 0 // Graphics: Display Eyes Overlay [336]
	337 => 1 // Remove: Opcode [337]
	338 => 0 // Disable Rest [338]
	339 => 0 // Alter Animation [339]
	342 => 0 // Animation: Override Data [342]
	345 => 1 // Enchantment bonus [345]
	363 => 0 // Modal state check [363]
	365 => 0 // Make unselectable [365]
	366 => 0 // Spell: Apply Spell On Move [366]
	367 => 0 // Minimum base stats [367]
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~damage_types~ BEGIN
	~%DAMAGETYPE_crushing%~    => 10120020 //         0 ~points de dégâts contondants~
	~%DAMAGETYPE_acid%~        => 10120021 //     65536 ~points de dégâts d'acide~
	~%DAMAGETYPE_cold%~        => 10120022 //    131072 ~points de dégâts de froid~
	~%DAMAGETYPE_electricity%~ => 10120023 //    262144 ~points de dégâts d'électricité~
	~%DAMAGETYPE_fire%~        => 10120024 //    524288 ~points de dégâts de feu~
	~%DAMAGETYPE_piercing%~    => 10120025 //   1048576 ~points de dégâts perforants~
	~%DAMAGETYPE_poison%~      => 10120026 //   2097152 ~points de dégâts de poison~
	~%DAMAGETYPE_magic%~       => 10120027 //   4194304 ~points de dégâts magiques~
	~%DAMAGETYPE_missile%~     => 10120028 //   8388608 ~points de dégâts de projectiles~
	~%DAMAGETYPE_slashing%~    => 10120029 //  16777216 ~points de dégâts tranchants~
	~%DAMAGETYPE_magic_fire%~  => 10120030 //  33554432 ~points de dégâts de feu magique~
	~%DAMAGETYPE_magic_cold%~  => 10120031 //  67108864 ~points de dégâts de froid magique~
	~%DAMAGETYPE_stunning%~    => 10120032 // 134217728 ~points de dégâts non létal~
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
	16 => ~9,5 %meters%~
	17 => ~10 %meters%~
	18 => ~11 %meters%~
	19 => ~11,5 %meters%~
	20 => ~12 %meters%~
	21 => ~13 %meters%~
	22 => ~13,5 %meters%~
	23 => ~14 %meters%~
	24 => ~14,5 %meters%~
	25 => ~15 %meters%~
	26 => ~16 %meters%~
	27 => ~16,5 %meters%~
	28 => ~17 %meters%~
	29 => ~17,5 %meters%~
	30 => ~18 %meters%~
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
   20 => ~slots~
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~spellnames~ BEGIN
	~tb#petri~ => 102355 // ~Pétrification~
	~tb#depet~ => 102356 // ~Transmutation de la pierre en chair~
	~tb#impri~ => 102469 // ~Emprisonnement~
	~x#kispr~  => 102468 // ~Enchevêtrement~
	~dventgl~  => 102468 // ~Enchevêtrement~
	~blakblad~ => 102470 // ~Lame noire du désastre~
	// Ignorés car redondant avec les autres effets qui les accompagnent
	~fl#glor2~ => 102150 // ~~
	~fl#glord~ => 102150 // ~~
	~fl#gmum~  => 102150 // ~~
	~fl#gmumn~ => 102150 // ~~
	~fl#mum~   => 102150 // ~~
	~fl#mumfh~ => 102150 // ~~
	~fl#mumfn~ => 102150 // ~~
	~fl#zomsd~ => 102150 // ~~
	~spwi604d~ => 102150 // ~~
	// Ignorés car ne font rien de concret pour le gameplay
	~lcarmor~ => 102150 // ~~
	~lcrobe~ => 102150 // ~~
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcodes_ignore_duration~ BEGIN
	  2 => 1
	  4 => 1
	 11 => 1 // Neutralisation du poison
	 12 => 1 // Dégâts
	 13 => 1 // Mort
	 14 => 1
	 17 => 1
	 23 => 1 // Modification du moral
	 26 => 1
	 32 => 1
	 43 => 1
	 46 => 1
	 47 => 1
	 48 => 1
	 55 => 1 // Mort
	 58 => 1 // Dissipation : Magie
	 64 => 1 // Dissipation : Infravision
	 68 => 1 // Désinvocation
	 70 => 1 // Dissipation non détection
	 75 => 1 // Dissipation : Aveuglement
	 77 => 1
	 79 => 1
	 81 => 1
	107 => 1
	116 => 1
	161 => 1
	210 => 1
	217 => 1
END

// opcodes absents de opcodes_ignore_duration mais dont l'effet ne peut être permanent
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcodes_cant_be_permanent~ BEGIN
	 20 => 1 // Invisibilité
	 24 => 1 // Panique
	125 => 1
	146 => 1
	148 => 1
	161 => 1
	162 => 1
	177 => 1
	214 => 1
	218 => 1
	230 => 1
	233 => 1
	238 => 1
	244 => 1
	261 => 1
	273 => 1
	280 => 1
	316 => 1
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcodes_parameters_should_be_zero~ BEGIN
	  4 => 1
	 43 => 1
	 47 => 1
	 56 => 1
	 63 => 1
	 64 => 1
	 65 => 1
	 74 => 1 // Aveuglement, ne pas toucher
	 75 => 1
	 77 => 1
	 79 => 1
	 81 => 1
	116 => 1
	125 => 1
	134 => 1
	150 => 1
	153 => 1
	154 => 1
	156 => 1
	157 => 1
	158 => 1
	160 => 1
	165 => 1
	168 => 1
	172 => 1
	231 => 1
	340 => 1
END

ACTION_DEFINE_ARRAY ~opcode_1_values~ BEGIN 0 10 20 30 40 50 5 15 25 35 45 END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcode_127_files~ BEGIN
	0 => ~MONSUM01~
	1 => ~MONSUM02~
	2 => ~MONSUM03~
	3 => ~ANISUM01~
	4 => ~ANISUM02~
	5 => ~MONSUM01~
	6 => ~MONSUM02~
	7 => ~MONSUM03~
    8 => ~ANISUM01~
    9 => ~ANISUM02~
END

OUTER_SET AbilityType_Charge = 1
OUTER_SET AbilityType_Combat = 2
OUTER_SET AbilityType_Equipped = 3


/* ------------------------------------- *
 * Stat: AC vs. Damage Type Modifier [0] *
 * ------------------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_0~ BEGIN
	LOCAL_SPRINT versus ~~
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 != AC_MOD_TYPE_set_base BEGIN
		LPM ~opcode_0_get_value~
		PATCH_IF parameter2 != AC_MOD_TYPE_all BEGIN
			SET strref = 10000000 + parameter2
			LPF ~getTranslation~ INT_VAR strref opcode RET versus = string END // ~contre les xxx~
			SPRINT value ~%value% %versus%~
		END
	END

	SPRINT name @102008 // ~Classe d'armure~

	PATCH_IF parameter2 == AC_MOD_TYPE_set_base BEGIN
		SPRINT name @10000100  // ~Classe d'armure de base~
	END

	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_0~ BEGIN
	LOCAL_SPRINT versus ~~
	LOCAL_SET value = ABS ~%parameter1%~

	PATCH_IF parameter2 == AC_MOD_TYPE_set_base BEGIN
		// xx% de chance de faire passer la classe d'armure du porteur [contre les] à yy [pendant ...]
		PATCH_FAIL "%SOURCE_FILE% : opcode_target_probability_0 pourcentage d'armure de la cible à gérer"
	END
	ELSE BEGIN
		PATCH_IF parameter2 != AC_MOD_TYPE_all BEGIN
			SET strref = 10000000 + parameter2
			LPF ~getTranslation~ INT_VAR strref opcode RET versus = string END // ~contre les xxx~
			SPRINT value ~%value% %versus%~
		END

		PATCH_IF parameter1 > 0 BEGIN
			SPRINT description @10000103 // ~d'accorder un bonus de %value% à la classe d'armure %ofTheTarget%~
		END
		ELSE BEGIN
			SPRINT description @10000104 // ~d'infliger un malus de %value% à la classe d'armure %ofTheTarget%~
		END
	END
END


DEFINE_PATCH_MACRO ~opcode_target_0~ BEGIN
	LOCAL_SPRINT versus ~~
	LOCAL_SET value = ~%parameter1%~

	PATCH_IF parameter2 == AC_MOD_TYPE_set_base BEGIN
		// FIXME ? Pas compris la condition
		PATCH_IF %itemType% != ITM_TYPE_armor BEGIN
			SPRINT value @10010 // ~Passe à %value%~
		END
	END
	ELSE BEGIN
		LPM ~opcode_0_get_value~
		PATCH_IF parameter2 != AC_MOD_TYPE_all BEGIN
			SET strref = 10000000 + parameter2
			LPF ~getTranslation~ INT_VAR strref opcode RET versus = string END // ~contre les xxx~
			SPRINT value ~%value% %versus%~
		END
	END

	PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
		SPRINT name @102008        // ~Classe d'armure~
		SPRINT description @100007 // ~%name% %ofTheTarget%%colon%%value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_0~ BEGIN
	LPM ~opcode_self_probability_0~
END

DEFINE_PATCH_MACRO ~opcode_0_get_value~ BEGIN
	PATCH_IF armor_class_show_bonus_malus BEGIN
		PATCH_IF value > 0 BEGIN
			SPRINT value @10000101 // ~Bonus de %value%~
		END
		ELSE BEGIN
			SET value = ABS value
			SPRINT value @10000102 // ~Malus de %value%~
		END
	END
	ELSE BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%value%~ RET value END
	END
END

DEFINE_PATCH_MACRO ~opcode_0_is_valid~ BEGIN
	// Armure non reconnue
	PATCH_IF parameter2 != AC_MOD_TYPE_all AND
			 parameter2 != AC_MOD_TYPE_crushing AND
			 parameter2 != AC_MOD_TYPE_missile AND
			 parameter2 != AC_MOD_TYPE_piercing AND
			 parameter2 != AC_MOD_TYPE_slashing AND
			 parameter2 != AC_MOD_TYPE_set_base BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid parameter2 value (0 1 2 4 8 16 expected).~ END
		SET isValid = 0
	END
	// Valeur = valeur + 0
	PATCH_IF parameter1 == 0 AND parameter2 != AC_MOD_TYPE_set_base BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: parameter1 equal to 0 for a bonus/malus to the armor class.~ END
		SET isValid = 0
	END
END

/* ------------------------------------ *
 * Stat: Attacks Per Round Modifier [1] *
 * ------------------------------------ */

DEFINE_PATCH_MACRO ~opcode_self_1~ BEGIN
	LPM ~opcode_1_common~

	PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10010 // ~Passe à %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN
		SET value = ~%parameter1%~
		SET value -= 100
		LPF ~signed_value~ INT_VAR value RET value END
		SPRINT value @10002 // ~%value% %~
	END
	ELSE PATCH_IF parameter2 == 3 AND is_ee == 1 BEGIN
		SPRINT value @10010008 // ~Fixée à %value%~
	END

	PATCH_IF ~%value%~ STRING_EQUAL ~+%oneHalf%~ BEGIN
		SPRINT value @10010007 // ~une demi supplémentaire~
	END

	SPRINT name @102007 // ~Attaque par round~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_1~ BEGIN
	LPM ~opcode_1_common~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		SPRINT description @10010001 // ~de modifier le nombre d'attaque par round %ofTheTarget% de %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN
		SET value = ~%parameter1%~
		SPRINT value @10002 // ~%value% %~
		SPRINT description @10010003 // ~de multiplier le nombre d'attaque par round %ofTheTarget% par %value%~
	END
	// ne doit pas passer par un EFF et doit être de timing 2, 5, 8 => sinon comme Type 1
	ELSE PATCH_IF parameter2 == 3 AND is_ee == 1 AND NOT isExternal AND (timingMode == TIMING_while_equipped OR timingMode == 5 OR timingMode == 8) BEGIN
		SPRINT description @10010004 // ~de fixer le nombre d'attaque par round %ofTheTarget% à %value%~
	END
	ELSE BEGIN
		SPRINT description @10010002 // ~de passer le nombre d'attaque par round %ofTheTarget% à %value%~
	END
END

// TODO
// DEFINE_PATCH_MACRO ~opcode_target_1~ BEGIN
// END

DEFINE_PATCH_MACRO ~opcode_target_probability_1~ BEGIN
	LPM ~opcode_self_probability_1~
END

DEFINE_PATCH_MACRO ~opcode_1_common~ BEGIN
	LOCAL_SET is_negative = parameter1 < 0 ? 1 : 0
	SET value = ABS parameter1

	// P2 = 1 ou P2 = 3: si P1 > 10 ou < 0 => P1 = 10
	PATCH_IF (parameter2 == MOD_TYPE_flat OR parameter2 == 3) AND NOT VARIABLE_IS_SET $opcode_1_values(~%value%~) BEGIN
		SET value = 10
	END

	PATCH_IF parameter2 != MOD_TYPE_percentage BEGIN
		SPRINT oneHalf @10010005 // ~une demi~
		SPRINT andHalf @10010006 // ~\1 et demi~
		// Weidu ne gérant pas les nombres flottants, une solution est de passer par des nombres 10 fois plus grand.
		SET value = $opcode_1_values(~%value%~)

		PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
			PATCH_IF is_negative == 1 BEGIN
				SET value = 0 - value
			END
	        LPF ~signed_value~ INT_VAR value RET value END
	    END

		INNER_PATCH_SAVE value ~%value%~ BEGIN
			REPLACE_TEXTUALLY ~\([0-9]\)+0$~ ~\1~        // 20 => 2
			REPLACE_TEXTUALLY ~\([0-9]\)+5$~ ~%andHalf%~ // 25 => 2 et demi
			REPLACE_TEXTUALLY ~5$~ ~%oneHalf%~           // 5  => une demi
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_1_is_valid~ BEGIN
	LOCAL_SET value = ABS parameter1

	LPM ~opcode_modstat_is_valid~
	PATCH_IF parameter2 < 0 OR parameter2 > 4 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unkwnow method : %parameter1%.~ END
	END

	PATCH_IF parameter2 == MOD_TYPE_cumulative AND NOT VARIABLE_IS_SET $opcode_1_values(~%value%~) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid parameter1 value ([-10 10] expected).~ END
	END

	PATCH_IF parameter2 == 3
		AND NOT isExternal // Si on n'est pas dans un fichier .eff
		AND (
			timingMode == TIMING_duration
			OR timingMode == TIMING_delayed_duration
			OR timingMode == 6
			OR timingMode == TIMING_permanent_after_death
			OR timingMode == TIMING_duration_ticks
		)
	BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No effect with this timing : %timingMode%.~ END
	END
END

/* --------------- *
 * Cure: Sleep [2] *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_self_2~ BEGIN
	SPRINT description @10020001 // ~Réveille %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_2~ BEGIN
	SPRINT description @10020002 // ~de réveiller %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_2~ BEGIN
	SPRINT description @10020001 // ~Réveille %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_2~ BEGIN
	LPM ~opcode_self_probability_2~ // ~de réveiller %theTarget%~
END

/* --------------------- *
 * State: Berserking [3] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_3~ BEGIN
	SPRINT description @10030001 // ~Provoque la rage du berserker chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_3~ BEGIN
	LPM ~opcode_self_3~ // ~Provoque la rage du berserker chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_3~ BEGIN
	SPRINT description @10030002 // ~de provoquer la rage du berserker chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_3~ BEGIN
	LPM ~opcode_self_probability_3~ // ~de provoquer la rage du berserker chez %theTarget%~
END

/* -------------------- *
 * Cure: Berserking [4] *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_4~ BEGIN
	SPRINT description @10040001 // ~Apaise %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_4~ BEGIN
	SPRINT description @10040002 // ~d'apaiser %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_4~ BEGIN
	SPRINT description @10040001 // ~Apaise %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_4~ BEGIN
	LPM ~opcode_self_probability_4~ // ~d'apaiser %theTarget%~
END

/* ---------------------------------- *
 * Charm: Charm Specific Creature [5] *
 * ---------------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_5~ BEGIN
	SPRINT description @10050001 // ~Charme %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_5~ BEGIN
	PATCH_IF parameter1 == 0 BEGIN
		SPRINT description @10050003 // ~Charme universel sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT theTargetBasic @102471 // ~la cible~
		PATCH_IF ~%theTarget%~ STRING_EQUAL ~%theTargetBasic%~ BEGIN
			LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~3~ RET targetType = idName END
			SPRINT theTarget   @102384 // ~les %targetType%~
			SPRINT ofTheTarget @102385 // ~des %targetType%~
			SPRINT toTheTarget @102386 // ~aux %targetType%~
			LPM ~add_target_level~
		END

		PATCH_IF NOT ~%idName%~ STRING_EQUAL ~~ BEGIN
			SPRINT description @10050001 // ~Charme %theTarget%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_5~ BEGIN
	PATCH_IF parameter1 == 0 BEGIN
		SPRINT description @10050002 // ~de charmer %theTarget%~
	END
	ELSE BEGIN
		SPRINT theTargetBasic @102471 // ~la cible~
		PATCH_IF ~%theTarget%~ STRING_EQUAL ~%theTargetBasic%~ BEGIN
			LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~3~ RET targetType = idName END
			SPRINT theTarget   @102384 // ~les %targetType%~
			SPRINT ofTheTarget @102385 // ~des %targetType%~
			SPRINT toTheTarget @102386 // ~aux %targetType%~
			LPM ~add_target_level~
		END

		PATCH_IF NOT ~%idName%~ STRING_EQUAL ~~ BEGIN
			SPRINT description @10050002 // ~de charmer %theTarget%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_5_is_valid~ BEGIN
	PATCH_IF NOT (parameter2 >= 0 AND parameter2 <= 5 OR parameter2 >= 1000 AND parameter2 <= 1005) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown Charm Type : %parameter2%.~ END
	END
END

/* --------------------------- *
 * Stat: Charisma Modifier [6] *
 * --------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_6~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10060001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Charisme~
END

DEFINE_PATCH_MACRO ~opcode_target_6~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10060002 RET description END // ~le charisme~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_6~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10060002 RET description END // ~le charisme~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_6~ BEGIN
	LPM ~opcode_self_probability_6~
END

DEFINE_PATCH_MACRO ~opcode_6_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* -------------------------------- *
 * Stat: Constitution Modifier [10] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_10~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10100001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Constitution~
END

DEFINE_PATCH_MACRO ~opcode_target_10~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10100002 RET description END // ~la constitution~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_10~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10100002 RET description END // ~la constitution~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_10~ BEGIN
	LPM ~opcode_self_probability_10~
END

DEFINE_PATCH_MACRO ~opcode_10_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ----------------- *
 * Cure: Poison [11] *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_11~ BEGIN
	SPRINT description @10110001 // ~Neutralisation des poisons~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_11~ BEGIN
	SPRINT description @10110003 // ~de neutraliser les poisons sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_11~ BEGIN
	SPRINT description @10110002 // ~Neutralise les poisons %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_11~ BEGIN
	LPM ~opcode_self_probability_11~
END

/* --------------- *
 * HP: Damage [12] *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_self_12~ BEGIN
	LPM ~opcode_12_flags~
	LPF ~opcode_12_common~ INT_VAR strref_0 = 10120001 RET description END // ~Inflige %damage% %damageType% %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_12~ BEGIN
	LOCAL_SET strref_0 = 10120002 // ~Inflige %damage% %damageType% %toTheTarget%~

	LPM ~opcode_12_flags~

	PATCH_IF VARIABLE_IS_SET versus BEGIN
		SET strref_0 = 10120003 // ~Inflige %damage% %damageType% supplémentaires %versus%~
	END
	PATCH_IF flagDrain == 1 BEGIN
		SET strref_0 = 10120004 // ~Draine %damage% %damageType% %toTheTarget%~
	END
	PATCH_IF flagTransfert == 1 BEGIN
		SET strref_0 = 10120005 // ~Transfert %damage% %damageType% %toTheTarget%~
	END

	LPF ~opcode_12_common~ INT_VAR strref_0 RET description END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_12~ BEGIN
	LPM ~opcode_12_flags~
	LPF ~opcode_12_common~ INT_VAR strref_0 = 10120011 RET description END // ~d'infliger %damage% %damageType% %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_12~ BEGIN
	LOCAL_SET strref_0 = 10120012 // ~d'infliger %damage% %damageType% supplémentaires~
	LOCAL_SET strref_3 = 10120016 // ~de retirer %value% des points de vie de la cible sous forme de %damageType%~

	LPM ~opcode_12_flags~

	PATCH_IF VARIABLE_IS_SET versus BEGIN
		SET strref_0 = 10120013 // ~d'infliger %damage% %damageType% supplémentaires %versus%~
	END
	PATCH_IF flagDrain == 1 BEGIN
		SET strref_0 = 10120014 // ~de drainer %damage% %damageType% %toTheTarget%~
	END
	PATCH_IF flagTransfert == 1 BEGIN
		SET strref_0 = 10120015 // ~de transférer %damage% %damageType% %toTheTarget%~
	END

	LPF ~opcode_12_common~ INT_VAR strref_0 strref_3 RET description END
END

DEFINE_PATCH_MACRO ~opcode_12_flags~ BEGIN
	SET flagDrain = 0
	SET flagTransfert = 0
	SET flagFistDamage = 0
	SET flagSaveForHalf = 0
	SET flagFailForHalf = 0
	SET flagDontWake = 0
	SET isNotCumulative = 0
	SET upMaxHp = 0
	SET mode = parameter2 BAND 65535

	PATCH_IF is_ee == 1 BEGIN
		SET flagDrain = ((special BAND 0b11011) == BIT0 OR (special BAND 0b11011) == BIT3)
		SET flagTransfert = ((special BAND 0b11011) == BIT1 OR (special BAND 0b11011) == BIT4)
		SET flagFistDamage = (special BAND BIT2) > 0
		SET flagSaveForHalf = (special BAND BIT8) > 0 AND mode == 0
		SET flagFailForHalf = (special BAND BIT9) > 0 AND mode == 0
		SET flagDontWake = (special BAND BIT10) > 0
		// TODO : manque l'affichage : augmente les pv max
		SET upMaxHp = (flagDrain OR flagTransfert) AND duration > 0
		SET isNotCumulative = (special BAND BIT3) > 0 OR (special BAND BIT4) > 0
	END
END

DEFINE_PATCH_FUNCTION ~opcode_12_common~ INT_VAR strref_0 = 0 strref_1 = 0 strref_2 = 0 strref_3 = 0 RET description BEGIN
	SET damageAmount = %parameter1%
	SET mode = parameter2 BAND 65535
	SET type = parameter2 - mode
	SPRINT description ~~

	// Les dés influencent tous les modes
	LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET damage END
	INNER_PATCH_SAVE damage ~%damage%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
	END

	// Dégâts basiques
	PATCH_IF mode == 0 BEGIN
		// Type de dégâts inconnus
		PATCH_IF VARIABLE_IS_SET $damage_types(~%type%~) BEGIN
			SET type = $damage_types(~%type%~)
		END
		ELSE BEGIN
			SET type = 101092 // ~points de dégâts~
		END
		LPF ~getTranslation~ INT_VAR strref = type opcode RET damageType = string END

		PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
			LPF ~getTranslation~ INT_VAR strref = strref_0 opcode RET description = string END
		END
	END
	// Set to value
	ELSE PATCH_IF mode == 1 BEGIN
		PATCH_IF ~%damage%~ STRING_EQUAL ~~ BEGIN
			SET damage = ~0~
		END
		PATCH_FAIL "%SOURCE_FILE%: opcode_12_common: mode 1 a gerer : les points de vie de la cible passent a %damage%"
	END
	// Set to Percentage
	ELSE PATCH_IF mode == 2 BEGIN
		PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
			PATCH_FAIL "%SOURCE_FILE%: opcode_12_common: mode 2 a gerer : les points de vie de la cible passent à %damage% % de ses pv max"
		END
	END
	// Reduce by Percentage
	ELSE PATCH_IF mode == 3 BEGIN
		PATCH_FAIL "%SOURCE_FILE%: opcode_12_common: mode 3 a gerer : la cible perd %damage% % de ses pv max"
	END

	// Hack pour forcer l'affichage de la durée de l'augmentation des points de vie maximum
	PATCH_IF upMaxHp BEGIN
		SET timingMode = TIMING_duration
		LPF ~get_duration_value~ INT_VAR duration RET duration = value END

		PATCH_IF NOT ~%duration%~ STRING_EQUAL ~~ BEGIN
			SPRINT description ~%description% %duration%~
			SET ignoreDuration = 1
			PATCH_IF isNotCumulative BEGIN
				LPM ~opcode_not_cumulative~
			END
		END
	END
	PATCH_IF flagDontWake == 1 AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT dontWakeUp @10120040 // ~Ne réveille pas la cible~
		SPRINT description ~%description% (%dontWakeUp%)~
	END
	PATCH_IF flagFistDamage == 1 BEGIN
		// FIXME : formulation
		PATCH_FAIL "%SOURCE_FILE%: opcode_12_common: flagFistDamage : l'effet est n'efficace que si la source est désarmée"
	END
END

DEFINE_PATCH_MACRO ~opcode_12_is_valid~ BEGIN
	// On scinde parameter2 en deux blocs
	// On pourrait mettre des SET pour les utiliser ailleurs mais je considère que ce bloc est facultatif
	LOCAL_SET mode = parameter2 BAND 65535
	LOCAL_SET damage_type = parameter2 - mode

	PATCH_IF NOT VARIABLE_IS_SET $damage_types(~%damage_type%~) BEGIN
		// 	SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown damage type : %damage_type%.~ END
	END
	PATCH_IF mode > 3 OR mode < 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown mode : %mode%.~ END
	END
END

/* ------------------------- *
 * Death: Instant Death [13] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_13~ BEGIN
	SPRINT description @10130001 // ~Tue instantanément %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_13~ BEGIN
	LPM ~opcode_target_probability_13~
END

DEFINE_PATCH_MACRO ~opcode_target_13~ BEGIN
	LPM ~opcode_self_13~ // ~Tue instantanément %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_13~ BEGIN
	SPRINT description @10130002 // ~de tuer instantanément %theTarget%~
END

/* ----------------------------- *
 * Graphics: Defrost [14] *
 * ----------------------------- */
 DEFINE_PATCH_MACRO ~opcode_self_14~ BEGIN
	SPRINT description @10140001
END

DEFINE_PATCH_MACRO ~opcode_self_probability_14~ BEGIN
	SPRINT description @10140002
END

DEFINE_PATCH_MACRO ~opcode_target_14~ BEGIN
	SPRINT description @10140003
END

DEFINE_PATCH_MACRO ~opcode_target_probability_14~ BEGIN
	LPM ~opcode_self_probability_14~
END

/* ----------------------------- *
 * Stat: Dexterity Modifier [15] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_15~ BEGIN
	LPM ~opcode_15_common~
	LPF ~opcode_mod~ INT_VAR strref = 10150001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dextérité~
END

DEFINE_PATCH_MACRO ~opcode_target_15~ BEGIN
	LPM ~opcode_15_common~
	LPF ~opcode_target~ INT_VAR strref = 10150002 RET description END // ~la dextérité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_15~ BEGIN
	LPM ~opcode_15_common~
	LPF ~opcode_probability~ INT_VAR strref = 10150002 RET description END // ~la dextérité~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_15~ BEGIN
	LPM ~opcode_self_probability_15~
END

DEFINE_PATCH_MACRO ~opcode_15_common~ BEGIN
	PATCH_IF parameter2 == 3 BEGIN
		// TODO? efficace que si dextérité de base < 20
		SET parameter2 = MOD_TYPE_cumulative
		PATCH_IF NOT isExternal BEGIN
			PATCH_IF NOT FILE_EXISTS_IN_GAME ~CLSSPLAB.2da~ BEGIN
				SET parameter1 = 1
			END
			ELSE BEGIN
				LPF ~add_log_warning~ STR_VAR type = ~warning~ message = EVAL ~Opcode %opcode%: mode : %parameter2% avec présence de CLSSPLAB.2da : non gere.~ END
			END
		END
		// issu d'un EFF et parameter1 == 0: sans effet
		ELSE PATCH_IF parameter1 == 0 BEGIN
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No effect detected : Valeur = Valeur + 0.~ END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_15_is_valid~ BEGIN
	PATCH_IF is_ee == 1 BEGIN
		LPM ~opcode_modstat3_is_valid~
	END
	ELSE BEGIN
		LPM ~opcode_modstat2_is_valid~
	END
END

/* ----------------- *
 * State: Haste [16] *
 * ----------------- */
// TODO : parameter2 == 1 : l'APR est arrondie au supérieur, 1 => 1, 3/2 => 2
DEFINE_PATCH_MACRO ~opcode_self_16~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @10160002 // ~Hâte améliorée~
	END
	ELSE PATCH_IF parameter2 == 2 BEGIN
		SPRINT description @10160003 // ~Hâte (sans bonus d'attaque par round)~
	END
	ELSE BEGIN
		SPRINT description @10160001 // ~Hâte~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_16~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @10160005 // ~de lancer Hâte améliorée sur %theTarget%~
	END
	ELSE PATCH_IF parameter2 == 2 BEGIN
		SPRINT description @10160006 // ~de lancer Hâte (sans bonus d'attaque par round) sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10160004 // ~de lancer Hâte sur %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_16~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @10160008 // ~Lance Hâte améliorée sur %theTarget%~
	END
	PATCH_IF parameter2 == 2 BEGIN
		SPRINT description @10160009 // ~Lance Hâte (sans bonus d'attaque par round) sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10160007 // ~Lance Hâte sur %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_16~ BEGIN
	LPM ~opcode_self_probability_16~
END

/* ---------------------------- *
 * HP: Current HP Modifier [17] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_17~ BEGIN
	LOCAL_SET strref_1 = 10170001 // ~Soigne 1 point de vie %toTheTarget%~
	LOCAL_SET strref_2 = 10170002 // ~Soigne %value% points de vie %toTheTarget%~
	LOCAL_SET strref_3 = 10170003 // ~Inflige 1 point de dégâts %toTheTarget%~
	LOCAL_SET strref_4 = 10170004 // ~Inflige %value% points de dégâts %toTheTarget%~
	LOCAL_SET strref_5 = 10170009 // ~Ressuscite~
	// fix: renommage en rtype pour éviter conflit avec le 'type' de log_warning
	SET rtype = parameter2 BAND 65535
	SET subType = parameter2 / 65535
	SET isRez = subType BAND BIT0 > 0

	PATCH_IF rtype == 1 BEGIN
		SET damageAmount = parameter1
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END
		LPF ~opcode_mod~ INT_VAR strref = 10170021 STR_VAR value = EVAL ~%value%~ RET description END // ~Points de vie actuels~
	END
	ELSE PATCH_IF rtype == 0 OR rtype == 2 BEGIN
		LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 strref_3 strref_4 strref_5 RET description END
	END

	// FIXME v0.9.20 > afficher les effets sur plusieurs lignes
	// PATCH_IF isRez BEGIN
	// 	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
	// 		LPF ~getTranslation~ INT_VAR strref = strref_5+2 opcode RET effect = string END // ~sans %theTarget%~
	// 		TO_LOWER description
	// 		SPRINT description @10170020
	// 	END
	// 	ELSE BEGIN
	// 		LPF ~getTranslation~ INT_VAR strref = strref_5 opcode RET effect = string END // ~avec %theTarget%~
	// 		SPRINT description ~%description%%effect%~
	// 	END
	// END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_17~ BEGIN
	LOCAL_SET strref_1 = 10170005 // ~de soigner 1 point de vie %toTheTarget%~
	LOCAL_SET strref_2 = 10170006 // ~de soigner %value% points de vie %toTheTarget%~
	LOCAL_SET strref_3 = 10170007 // ~d'infliger 1 point de dégâts %toTheTarget%~
	LOCAL_SET strref_4 = 10170008 // ~d'infliger %value% points de dégâts %toTheTarget%
	LOCAL_SET strref_5 = 10170010 // ~de ressusciter~
	SET rtype = parameter2 BAND 65535
	SET subType = parameter2 / 65535
	SET isRez = subType BAND BIT0 > 0

	PATCH_IF rtype == 0 OR rtype == 2 BEGIN
		LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 strref_3 strref_4 strref_5 RET description END
	END
	ELSE PATCH_IF rtype == 1 BEGIN
		SET damageAmount = parameter1
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END
		LPF ~opcode_mod~ INT_VAR strref = 10170022 STR_VAR value = EVAL ~%value%~ RET description END // ~les points de vie actuels~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_17~ BEGIN
	LPM ~opcode_self_17~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_17~ BEGIN
	LPM ~opcode_self_probability_17~
END

DEFINE_PATCH_MACRO ~opcode_party_17~ BEGIN
	LPM ~opcode_self_17~
END

DEFINE_PATCH_FUNCTION ~opcode_17_common~ INT_VAR strref_1 = 0 strref_2 = 0 strref_3 = 0 strref_4 = 0 strref_5 = 0 RET description BEGIN
	// TODO
	// Dissipe tous les effets non permanent_after_death puis la soigne
	SET purgeEff = subType BAND BIT1 > 0
	// l'opcode s'exécute dans cet ordre (si flag actif) : rez => purge => soin

	PATCH_IF isRez OR purgeEff BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: subType non gere : %subType%.~ END
	END

	SET damageAmount = parameter1
	LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END

	PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF ~%value%~ STRING_CONTAINS_REGEXP ~^-~ BEGIN
			INNER_PATCH_SAVE value ~%value%~ BEGIN
				REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
				PATCH_IF rtype == 2 BEGIN
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~$~ ~ %~
				END
			END

			PATCH_IF ~%value%~ STRING_EQUAL ~1~ OR ~%value%~ STRING_EQUAL ~1 %~ BEGIN
				LPF ~getTranslation~ INT_VAR strref = strref_1 opcode RET description = string END // ~Soigne %value% point de vie~
			END
			ELSE BEGIN
				LPF ~getTranslation~ INT_VAR strref = strref_2 opcode RET description = string END // ~Soigne %value% points de vie~
			END
		END
		ELSE BEGIN
			INNER_PATCH_SAVE value ~%value%~ BEGIN
				REPLACE_TEXTUALLY EVALUATE_REGEXP ~^-~ ~~
				PATCH_IF rtype == 2 BEGIN
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~$~ ~ %~
				END
			END

			PATCH_IF ~%value%~ STRING_EQUAL ~1~ OR ~%value%~ STRING_EQUAL ~1 %~ BEGIN
				LPF ~getTranslation~ INT_VAR strref = strref_3 opcode RET description = string END // ~Inflige %value% point de vie~
			END
			ELSE BEGIN
				LPF ~getTranslation~ INT_VAR strref = strref_4 opcode RET description = string END // ~Inflige %value% points de vie~
			END
		END
	END

	PATCH_IF isRez BEGIN
		PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
			LPF ~getTranslation~ INT_VAR strref = strref_5+2 opcode RET effect = string END // ~sans %theTarget%~
			TO_LOWER description
			SPRINT description @10170020 // ~%effect% puis %description%~
		END
		ELSE BEGIN
			LPF ~getTranslation~ INT_VAR strref = strref_5 opcode RET effect = string END // ~avec %theTarget%~
			SPRINT description ~%effect%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_17_is_valid~ BEGIN
	SET rtype = parameter2 BAND 65535
	PATCH_IF rtype < CURRENT_HP_MOD_TYPE_cumulative OR rtype > CURRENT_HP_MOD_TYPE_percentage BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %rtype%.~ END
	END
END

/* ------------------------------ *
 * Stat: Maximum HP Modifier [18] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_18~ BEGIN
	LPM ~opcode_18_common~
	PATCH_IF healOnlyMaxPV == 1 BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 10180001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Points de vie maximum~
	END
	ELSE BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 10180003 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Points de vie maximum~
	END
	// LPM ~opcode_18_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_18~ BEGIN
	LPM ~opcode_18_common~

	PATCH_IF healOnlyMaxPV == 1 BEGIN
		SPRINT theStatistic @10180002 // ~les points de vie maximum~
	END
	ELSE BEGIN
		SPRINT theStatistic @10180004 // ~les points de vie actuel et maximum~
	END

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF parameter1 >= 0 OR NOT IS_AN_INT value BEGIN
	        SPRINT description @102286 // ~Augmente %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
	        SPRINT description @102285 // ~Réduit %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102287 // ~Passe %theStatistic% %ofTheTarget% à %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102288 // ~Multiplie %theStatistic% %ofTheTarget% par %value%~
	END

	// LPM ~opcode_18_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_18~ BEGIN
	LPM ~opcode_18_common~

	PATCH_IF healOnlyMaxPV == 1 BEGIN
		SPRINT theStatistic @10180002 // ~les points de vie maximum~
	END
	ELSE BEGIN
		SPRINT theStatistic @10180004 // ~les points de vie actuel et maximum~
	END

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF parameter1 >= 0 OR NOT IS_AN_INT value BEGIN
	        SPRINT description @102544 // ~d'augmenter %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
	        SPRINT description @102543 // ~de réduire %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102545 // ~de passer %theStatistic% %ofTheTarget% à %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102546 // ~de multiplier %theStatistic% %ofTheTarget% par %value%~
	END

	// LPM ~opcode_18_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_18~ BEGIN
	LPM ~opcode_self_probability_18~
END

DEFINE_PATCH_MACRO ~opcode_18_common~ BEGIN
	// SET isCumulative = parameter2 != 6
	SET damageAmount = parameter1
	SET healOnlyMaxPV = parameter2 >= 3 AND parameter2 <= 5 OR is_ee == 1 AND special != 0
	SET parameter2 = parameter2 MODULO 3
	LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END
	INNER_PATCH_SAVE value ~%value%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
	END
END

/*
DEFINE_PATCH_MACRO ~opcode_18_not_cumulative~ BEGIN
	PATCH_IF isCumulative == 0 AND is_ee == 1 AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @101185 // ~%description% (non cumulable)~
	END
END
*/

DEFINE_PATCH_MACRO ~opcode_18_is_valid~ BEGIN
	PATCH_IF parameter2 < MOD_TYPE_cumulative OR (parameter2 > 5 AND is_ee == 0 OR parameter2 > 6) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %type%.~ END
	END
END

/* -------------------------------- *
 * Stat: Intelligence Modifier [19] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_19~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10190001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Intelligence~
END

DEFINE_PATCH_MACRO ~opcode_target_19~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10190002 RET description END // ~l'intelligence~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_19~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10190002 RET description END // ~l'intelligence~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_19~ BEGIN
	LPM ~opcode_self_probability_19~
END

DEFINE_PATCH_MACRO ~opcode_19_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------ *
 * State: Invisibility [20] *
 * ------------------------ */
 // TODO: parameter2 == 2 (EE)
DEFINE_PATCH_MACRO ~opcode_self_20~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @10200001 // ~Invisibilité~
	END
	ELSE BEGIN
		SPRINT description @10200002 // ~Invisibilité améliorée~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_20~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @10200003 // ~de lancer Invisibilité sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10200004 // ~de lancer Invisibilité améliorée sur %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_20~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @10200005 // ~Lance Invisibilité sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10200006 // ~Lance Invisibilité améliorée sur %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_20~ BEGIN
	LPM ~opcode_self_probability_20~
END

/* ------------------------ *
 * Stat: Lore Modifier [21] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_21~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10210001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Connaissance~
END

DEFINE_PATCH_MACRO ~opcode_target_21~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10210002 RET description END // ~les connaissances~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_21~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10210002 RET description END // ~les connaissances~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_21~ BEGIN
	LPM ~opcode_self_probability_21~
END

DEFINE_PATCH_MACRO ~opcode_21_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
	// L'effet ne fonctionne pas avec un timing ==  1
	// Les timings 4 et 7 ajoutent un délai entre le moment où l'effet est lancé et le moment où l'effet s'active
	// Une fois le délai écoulé, l'effet est appliqué avec un timing 1, donc...
	PATCH_IF timingMode == TIMING_permanent OR timingMode == TIMING_delayed OR timingMode == 7 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: This effect does not work with Timing Mode %timingMode%.~ END
	END
END

/* -------------------------------- *
 * Stat: Cumulative Luck Bonus [22] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_22~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10220001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Chance~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_22~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10220002 RET description END // ~la chance~
END

DEFINE_PATCH_MACRO ~opcode_target_22~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10220002 RET description END // ~la chance~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_22~ BEGIN
	LPM ~opcode_self_probability_22~ // ~la chance~
END

DEFINE_PATCH_MACRO ~opcode_22_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* -------------------------- *
 * Stat: Morale Modifier [23] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_23~ BEGIN
	LPM ~opcode_23_common~

	PATCH_IF parameter2 == MOD_TYPE_flat AND parameter1 == 10 BEGIN
		SPRINT description @10230003 // ~Le moral %ofTheTarget% ne peut flancher~
	END
	ELSE BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 10230001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Moral~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_23~ BEGIN
	LPM ~opcode_23_common~

	PATCH_IF parameter2 == MOD_TYPE_flat AND parameter1 == 10 BEGIN
		SPRINT description @10230004 // ~de garder le moral %ofTheTarget% au plus haut~
	END
	ELSE BEGIN
		LPF ~opcode_probability~ INT_VAR strref = 10230002 RET description END // ~le moral~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_23~ BEGIN
	LPM ~opcode_23_common~
	PATCH_IF parameter2 == MOD_TYPE_flat AND parameter1 == 10 BEGIN
		SPRINT description @10230003 // ~Le moral %ofTheTarget% ne peut flancher~
	END
	ELSE BEGIN
		LPF ~opcode_target~ INT_VAR strref = 10230002 RET description END // ~le moral~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_23~ BEGIN
	LPM ~opcode_self_probability_23~ // ~le moral~
END

DEFINE_PATCH_MACRO ~opcode_23_common~ BEGIN
	PATCH_IF is_ee == 0 OR special == 0 BEGIN
		//TODO: Pour ce cas, plutot avoir une phrase du genre: Le moral est à son maximum
		SET parameter1 = 10
		SET parameter2 = MOD_TYPE_flat
	END
END

DEFINE_PATCH_MACRO ~opcode_23_is_valid~ BEGIN
	PATCH_IF is_ee == 1 AND special != 0 BEGIN
		LPM ~opcode_modstat2_is_valid~
	END
END


/* ------------------ *
 * State: Horror [24] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_probability_24~ BEGIN
	SPRINT description @10240002 // ~d'infliger Horreur %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_24~ BEGIN
	SPRINT description @10240001 // ~Inflige Horreur %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_24~ BEGIN
	LPM ~opcode_self_probability_24~
END

/* ------------------ *
 * State: Poison [25] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_25~ BEGIN
	LOCAL_SET strref = 10250001

	LPM ~opcode_25_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_25~ BEGIN
	LOCAL_SET strref = 10250005

	LPM ~opcode_25_common~
END

DEFINE_PATCH_MACRO ~opcode_target_25~ BEGIN
	LPM ~opcode_self_25~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_25~ BEGIN
	LPM ~opcode_self_probability_25~
END

DEFINE_PATCH_MACRO ~opcode_25_common~ BEGIN
	SET amount = 0
	SET frequencyMultiplier = 1
	SET frequency = 1
	SET p4IsActive = isExternal AND parameter4 != 0
	SET type = parameter2

	// TODO parameter == 1 : Efficace que si les points de vie actuels >= 100 / Valeur ou si #P4 != 0
	// Compliqué de faire une phrase simple
	PATCH_IF (type == 0 AND (parameter1 != 0 OR p4IsActive)) OR
			 (type == 1 AND (parameter1 > 1 OR p4IsActive)) BEGIN
		SET amount = 1
	END
	ELSE PATCH_IF type == 2 AND parameter1 > 0 BEGIN
		SET amount = parameter1
	END
	ELSE PATCH_IF type == 3 BEGIN
		SET amount = 1
		SET frequency = parameter1
	END
	ELSE PATCH_IF type == 4 AND isExternal BEGIN
		SET amount = parameter3
		SET frequency = parameter1
	END

	PATCH_IF p4IsActive AND type >= 2 BEGIN
		SET frequency = frequency * parameter4
		// P4 divise également les dégâts si P2 == 2, avec un minimum à 1
		PATCH_IF type == 2 BEGIN
			SET amount = amount / parameter4
			PATCH_IF amount < 1 BEGIN
				amount = 1
			END
		END
	END
	PATCH_IF frequency < 1 BEGIN
		SET frequency = 1
	END

	PATCH_IF amount == 1 AND frequency == 1 BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Empoisonne %theTarget%, lui infligeant 1 point de dégâts par seconde~
	END
	ELSE PATCH_IF amount > 1 AND frequency == 1 BEGIN
		SET strref += 1
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Empoisonne %theTarget%, lui infligeant %amount% points de dégâts par seconde~
	END
	ELSE PATCH_IF amount == 1 AND frequency > 1 BEGIN
		SET strref += 2
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Empoisonne %theTarget%, lui infligeant 1 point de dégâts toutes les %frequency% secondes~
	END
	ELSE PATCH_IF amount > 1 AND frequency > 1 BEGIN
		SET strref += 3
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Empoisonne %theTarget%, lui infligeant 1 point de dégâts toutes les %frequency% secondes~
	END
	ELSE PATCH_IF amount < 0 BEGIN
		// TODO: Dans le cas où P2 == 4 et & P3 < 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Degats negatifs non geres.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_25_is_valid~ BEGIN
	PATCH_IF (timingMode == TIMING_permanent OR
			 timingMode == TIMING_delayed OR
			 timingMode == 7 OR
			 timingMode == TIMING_permanent_after_death) AND duration == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_warning~ STR_VAR type = ~warning~ message = EVAL ~Opcode %opcode%: This effect does not work with Timing Mode %timingMode%.~ END
	END
	PATCH_IF parameter2 > 4 OR parameter2 < 0 BEGIN
		LPF ~add_log_warning~ STR_VAR type = ~warning~ message = EVAL ~Opcode %opcode%: This effect does no effect with %parameter2%.~ END
	END
END

/* ----------------------- *
 * Item: Remove Curse [26] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_26~ BEGIN
	SPRINT description @10260001 // ~Délivre %theTarget% des malédictions~
END

DEFINE_PATCH_MACRO ~opcode_target_26~ BEGIN
	LPM ~opcode_self_26~ // ~Délivre %theTarget% des malédictions~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_26~ BEGIN
	SPRINT description @10260002 // ~de délivrer %theTarget% des malédictions~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_26~ BEGIN
	LPM ~opcode_self_probability_26~ // ~de délivrer %theTarget% des malédictions~
END

/* ----------------------------------- *
 * Stat: Acid Resistance Modifier [27] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_27~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10270001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à l'acide~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_27~ BEGIN
	LOCAL_SPRINT resistName @10270001 // ~Résistance à l'acide~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_27~ BEGIN
	LOCAL_SPRINT resistName @10270001 // ~Résistance à l'acide~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_27~ BEGIN
	LPM ~opcode_self_probability_27~
END

DEFINE_PATCH_MACRO ~opcode_27_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ----------------------------------- *
 * Stat: Cold Resistance Modifier [28] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_28~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10280001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance au froid~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_28~ BEGIN
	LOCAL_SPRINT resistName @10280001 // ~Résistance au froid~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_28~ BEGIN
	LOCAL_SPRINT resistName @10280001 // ~Résistance au froid~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_28~ BEGIN
	LPM ~opcode_self_probability_28~
END

DEFINE_PATCH_MACRO ~opcode_28_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------------------ *
 * Stat: Electricity Resistance Modifier [29] *
 * ------------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_29~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10290001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à l'électricité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_29~ BEGIN
	LOCAL_SPRINT resistName @10290001 // ~Résistance à l'électricité~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_29~ BEGIN
	LOCAL_SPRINT resistName @10290001 // ~Résistance à l'électricité~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_29~ BEGIN
	LPM ~opcode_self_probability_29~
END

DEFINE_PATCH_MACRO ~opcode_29_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ----------------------------------- *
 * Stat: Fire Resistance Modifier [30] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_30~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10300001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance au feu~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_30~ BEGIN
	LOCAL_SPRINT resistName @10300001 // ~Résistance au feu~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_30~ BEGIN
	LOCAL_SPRINT resistName @10300001 // ~Résistance au feu~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_30~ BEGIN
	LPM ~opcode_self_probability_30~
END

DEFINE_PATCH_MACRO ~opcode_30_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------------------- *
 * Stat: Magic Damage Resistance Modifier [31] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_31~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10310001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts magiques~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_31~ BEGIN
	LOCAL_SPRINT resistName @10310001 // ~Résistance aux dégâts magiques~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_31~ BEGIN
	LOCAL_SPRINT resistName @10310001 // ~Résistance aux dégâts magiques~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_31~ BEGIN
	LPM ~opcode_self_probability_31~
END

DEFINE_PATCH_MACRO ~opcode_31_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ----------------------------- *
 * Cure: Death (Raise Dead) [32] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_32~ BEGIN
	LPM ~opcode_target_32~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_32~ BEGIN
	LPM ~opcode_target_probability_32~
END

DEFINE_PATCH_MACRO ~opcode_target_32~ BEGIN
	SPRINT description @10320001 // ~Ressuscite %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_32~ BEGIN
	SPRINT description @10320002 // ~de ressusciter %theTarget%~
END

/* ---------------------------------- *
 * Stat: Save vs. Death Modifier [33] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_33~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10330001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre la paralysie, la mort et les poisons~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_33~ BEGIN
	LOCAL_SPRINT versus @10330001 // ~contre la paralysie, la mort et les poisons~
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_probability~ INT_VAR strref = 10330002 RET description END // ~les jets de sauvegarde %versus%~
END

DEFINE_PATCH_MACRO ~opcode_target_33~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10330001 STR_VAR value = EVAL ~%parameter1%~ target = 1 RET description END // ~contre la paralysie, la mort et les poisons~
END

DEFINE_PATCH_MACRO ~opcode_party_33~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10330001 STR_VAR value = EVAL ~%parameter1%~ group = 1 RET description END // ~contre la paralysie, la mort et les poisons~
END

DEFINE_PATCH_MACRO ~opcode_33_is_valid~ BEGIN
	LPM ~opcode_modstat3_is_valid~
	PATCH_IF parameter2 > 2 AND is_ee == 0 BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %parameter2%.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_33_group~ BEGIN
	LOCAL_SET group = 1
	// Pour chaque opcode 33, y a-t-il un opcode 34, 35, 36 et 37 avec les mêmes valeurs ?
	// Si oui, on désactive toutes ces entrées (1 de chaque) et on crée un simple opcode 325 avec les mêmes valeurs.
	PATCH_PHP_EACH ~opcodes_33~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET group = 1
		CLEAR_ARRAY positions
		// On ajoute l'opcode courant à ceux qui seront désactivés
		PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN
			33 => ~%position%~
		END

		FOR (opcode = 34; opcode <= 37; opcode += 1) BEGIN
			LPF ~get_opcode_position~ INT_VAR opcode STR_VAR expression = ~target = %target% AND power = %power% AND parameter1 = %parameter1% AND parameter2 = %parameter2% AND parameter3 = %parameter3% AND parameter4 = %parameter4% AND timingMode = %timingMode% AND resistance = %resistance% AND duration = %duration% AND probability1 = %probability1% AND probability2 = %probability2% AND diceCount = %diceCount% AND diceSides = %diceSides% AND saveType = %saveType% AND saveBonus = %saveBonus% AND special = %special%~ RET opcodePosition = position END

			SET $positions(~%opcode%~) = opcodePosition

			PATCH_IF opcodePosition < 0 BEGIN
				SET group = 0
				SET opcode = 38
			END
		END

		PATCH_IF group == 1 BEGIN
			// Suppression des effets similaires
			PATCH_PHP_EACH positions AS opcode => position1 BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode
					STR_VAR expression = ~position = %position1%~
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			SET opcode = 325
            LPM ~add_opcode~
		END
	END
END

/* ---------------------------------- *
 * Stat: Save vs. Wands Modifier [34] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_34~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10340001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les baguettes, les sceptres et les bâtons~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_34~ BEGIN
	LOCAL_SPRINT versus @10340001 // ~contre les baguettes, les sceptres et les bâtons~
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_probability~ INT_VAR strref = 10330002 RET description END // ~les jets de sauvegarde %versus%~
END

DEFINE_PATCH_MACRO ~opcode_target_34~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10340001 STR_VAR value = EVAL ~%parameter1%~ target = 1 RET description END // ~contre les baguettes, les sceptres et les bâtons~
END

DEFINE_PATCH_MACRO ~opcode_party_34~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10340001 STR_VAR value = EVAL ~%parameter1%~ group = 1 RET description END // ~contre les baguettes, les sceptres et les bâtons~
END

DEFINE_PATCH_MACRO ~opcode_34_is_valid~ BEGIN
	LPM ~opcode_33_is_valid~
END

/* ---------------------------------------------------- *
 * Stat: Save vs. Petrification/Polymorph Modifier [35] *
 * ---------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_35~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10350001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre la pétrification et la métamorphose~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_35~ BEGIN
	LOCAL_SPRINT versus @10350001 // ~contre la pétrification et la métamorphose~
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_probability~ INT_VAR strref = 10330002 RET description END // ~les jets de sauvegarde %versus%~
END

DEFINE_PATCH_MACRO ~opcode_target_35~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10350001 STR_VAR value = EVAL ~%parameter1%~ target = 1 RET description END // ~contre la pétrification et la métamorphose~
END

DEFINE_PATCH_MACRO ~opcode_party_35~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10350001 STR_VAR value = EVAL ~%parameter1%~ group = 1 RET description END // ~contre la pétrification et la métamorphose~
END

DEFINE_PATCH_MACRO ~opcode_35_is_valid~ BEGIN
	LPM ~opcode_33_is_valid~
END

/* ------------------------------------------- *
 * Stat: Save vs. Breath Weapons Modifier [36] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_36~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10360001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les souffles~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_36~ BEGIN
	LOCAL_SPRINT versus @10360001 // ~contre les souffles~
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_probability~ INT_VAR strref = 10330002 RET description END // ~les jets de sauvegarde %versus%~
END

DEFINE_PATCH_MACRO ~opcode_target_36~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10360001 STR_VAR value = EVAL ~%parameter1%~ target = 1 RET description END // ~contre les souffles~
END

DEFINE_PATCH_MACRO ~opcode_party_36~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10360001 STR_VAR value = EVAL ~%parameter1%~ group = 1 RET description END // ~contre les souffles~
END

DEFINE_PATCH_MACRO ~opcode_36_is_valid~ BEGIN
	LPM ~opcode_33_is_valid~
END

/* ----------------------------------- *
 * Stat: Save vs. Spells Modifier [37] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_37~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10370001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les sorts~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_37~ BEGIN
	LOCAL_SPRINT versus @10370001 // ~contre les sorts~
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_probability~ INT_VAR strref = 10330002 RET description END // ~les jets de sauvegarde %versus%~
END

DEFINE_PATCH_MACRO ~opcode_target_37~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10370001 target = 1 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les sorts~
END

DEFINE_PATCH_MACRO ~opcode_party_37~ BEGIN
	SET parameter2 = parameter2 MODULO 3
	LPF ~opcode_save_vs~ INT_VAR strref = 10370001 STR_VAR value = EVAL ~%parameter1%~ group = 1 RET description END // ~contre les sorts~
END

DEFINE_PATCH_MACRO ~opcode_37_is_valid~ BEGIN
	LPM ~opcode_33_is_valid~
END

/* ------------------- *
 * State: Silence [38] *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_self_38~ BEGIN
	SPRINT description @10380001 // ~Silence~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_38~ BEGIN
	SPRINT description @10380002 // ~de réduire %theTarget% au silence~
END

DEFINE_PATCH_MACRO ~opcode_target_38~ BEGIN
	SPRINT description @10380003 // ~Réduit %theTarget% au silence~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_38~ BEGIN
	LPM ~opcode_self_probability_38~ // ~de réduire %theTarget% au silence~
END

/* --------------------------- *
 * State: Unconsciousness [39] *
 * --------------------------- */
// TODO: P2 == 1: endort profondemment la cible (ne se réveille si subit des dégâts)
DEFINE_PATCH_MACRO ~opcode_self_39~ BEGIN
	PATCH_IF is_ee == 0 OR parameter2 != 1 BEGIN
		SPRINT description @10390001 // ~Endort %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10390003 // ~Endort profondément %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_39~ BEGIN
	PATCH_IF is_ee == 0 OR parameter2 != 1 BEGIN
		SPRINT description @10390002 // ~d'endormir %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10390004 // ~d'endormir profondément %theTarget%%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_39~ BEGIN
	LPM ~opcode_self_39~ // ~Endort %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_39~ BEGIN
	LPM ~opcode_self_probability_39~ // ~d'endormir %theTarget%~
END

/* ---------------- *
 * State: Slow [40] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_40~ BEGIN
	SPRINT description @10400001 // ~Lenteur~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_40~ BEGIN
	SPRINT description @10400002 // ~d'infliger lenteur %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_40~ BEGIN
	SPRINT description @10400003 // ~Inflige lenteur %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_40~ BEGIN
	LPM ~opcode_self_probability_40~ // ~d'infliger lenteur %toTheTarget%~
END

/* --------------------------------------- *
 * Spell: Wizard Spell Slots Modifier [42] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_42~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET level = parameter2
	LOCAL_SET spellLevelMax = 9

	LPF ~opcode_self_42_62~ INT_VAR level amount startStrref = 10420001 RET description END
END

/* ------------------------- *
 * Cure: Stone to Flesh [43] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_43~ BEGIN
	SPRINT description @10430001 // ~Transmutation de la pierre en chair~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_43~ BEGIN
	SPRINT description @10430002 // ~de dépétrifier %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_43~ BEGIN
	SPRINT description @10430003 // ~Dépétrifie %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_43~ BEGIN
	LPM ~opcode_self_probability_43~ // ~de dépétrifier %theTarget%~
END

/* ---------------------------- *
 * Stat: Strength Modifier [44] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_44~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10440001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_44~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10440002 RET description END // ~la force~
END

DEFINE_PATCH_MACRO ~opcode_target_44~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10440002 RET description END // ~la force~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_44~ BEGIN
	LPM ~opcode_self_probability_44~ // ~la force~
END

DEFINE_PATCH_MACRO ~opcode_44_common~ BEGIN
	// parameter2 == 3 efficace si Force <= 18
	LPM ~opcode_15_common~
END

DEFINE_PATCH_MACRO ~opcode_44_is_valid~ BEGIN
	LPM ~opcode_15_is_valid~
END

/* ---------------- *
 * State: Stun [45] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_45~ BEGIN
	SPRINT description @10450001 // ~Étourdit %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_45~ BEGIN
	SPRINT description @10450002 // ~d'étourdir %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_45~ BEGIN
	LPM ~opcode_self_45~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_45~ BEGIN
	LPM ~opcode_self_probability_45~
END

/* ------------------------ *
 * Cure: Stun (Unstun) [46] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_46~ BEGIN
	SPRINT description @10460001 // ~Immunité à l'étourdissement~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_46~ BEGIN
	SPRINT description @10460002 // ~de ranimer %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_46~ BEGIN
	SPRINT description @10460003 // ~Ranime %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_46~ BEGIN
	LPM ~opcode_self_probability_46~ // ~de ranimer %theTarget%~
END

/* ----------------------- *
 * Cure: Invisibility [47] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_47~ BEGIN
	SPRINT description @10470001 // ~Immunité à l'invisibilité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_47~ BEGIN
	SPRINT description @10470002 // ~de dissiper l'invisibilité %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_47~ BEGIN
	SPRINT description @10470003 // ~Dissipe l'invisibilité %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_47~ BEGIN
	LPM ~opcode_self_probability_47~ // ~de dissiper l'invisibilité %ofTheTarget%~
END

/* ----------------------------- *
 * Cure: Silence (Vocalize) [48] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_48~ BEGIN
	SPRINT description @10480001 // ~Immunité au silence~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_48~ BEGIN
	SPRINT description @10470002 // ~de rendre la parole %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_48~ BEGIN
	SPRINT description @10470003 // ~Rend la parole %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_48~ BEGIN
	LPM ~opcode_self_probability_48~ // ~de rendre la parole %toTheTarget%~
END

/* -------------------------- *
 * Stat: Wisdom Modifier [49] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_49~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10490001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Sagesse~
END

DEFINE_PATCH_MACRO ~opcode_target_49~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10490002 RET description END // ~la sagesse~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_49~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10490002 RET description END // ~la sagesse~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_49~ BEGIN
	LPM ~opcode_self_probability_49~
END

DEFINE_PATCH_MACRO ~opcode_49_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------- *
 * Stat: THAC0 Modifier [54] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_54~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10540001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0~
END

DEFINE_PATCH_MACRO ~opcode_target_54~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10540002 RET description END // ~le TAC0~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_54~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10540002 RET description END // ~le TAC0~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_54~ BEGIN
	LPM ~opcode_self_probability_54~
END

DEFINE_PATCH_MACRO ~opcode_54_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------ *
 * Death: Kill Creature Type [55] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_55~ BEGIN
	LPM ~opcode_target_55~
END

DEFINE_PATCH_MACRO ~opcode_target_55~ BEGIN
	// Ici pas besoin de calcul compliqué
	// A partir du moment où le fichier ids est correct (checké dans opcode_x_is_valid)
	// Si P1 == 0 => aucune restriction
	PATCH_IF parameter1 == 0 BEGIN
		SPRINT description @10550005 // ~Tue instantanément %theTarget%~
	END
	ELSE BEGIN
		// FIXME : la restriction de niveau devrait être simplement géré par add_target_level
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
		 PATCH_IF diceCount > 0 BEGIN
			SPRINT description @10550002 // ~Tue instantanément les %creatureType% de %diceCount% dés de vie ou moins~
		END ELSE BEGIN
			SPRINT description @10550001 // ~Tue instantanément les %creatureType%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_55~ BEGIN
	PATCH_IF parameter1 == 0 BEGIN
		SPRINT description @10550006 // ~de tuer instantanément %theTarget%~
	END
	ELSE BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
		PATCH_IF diceCount > 0 BEGIN
			SPRINT description @10550004 // ~de tuer instantanément les %creatureType% de %diceCount% dés de vie ou moins~
		END ELSE BEGIN
			SPRINT description @10550003 // ~de tuer instantanément les %creatureType%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_55_is_valid~ BEGIN
	LPM ~opcode_idscheck_is_valid~
END

/* ---------------------- *
 * Alignment: Invert [56] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_56~ BEGIN
	SPRINT description @10560001 // ~Inverse l'alignement %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_56~ BEGIN
	SPRINT description @10560002 // ~d'inverser l'alignement %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_56~ BEGIN
	LPM ~opcode_self_56~ // ~Inverse l'alignement %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_56~ BEGIN
	LPM ~opcode_self_probability_56~ // ~d'inverser l'alignement %ofTheTarget%~
END

/* ---------------------- *
 * Alignment: Change [57] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_57~ BEGIN
	LOCAL_SET alignment = ~%parameter2%~
	LPM ~opcode_57_common~
	SPRINT description @10570001 // ~Alignement modifié en %alignment%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_57~ BEGIN
	LOCAL_SET alignment = ~%parameter2%~
	LPM ~opcode_57_common~
	SPRINT description @10570002 // ~de modifier l'alignement %ofTheTarget% en %alignment%~
END

DEFINE_PATCH_MACRO ~opcode_target_57~ BEGIN
	LOCAL_SET alignment = ~%parameter2%~
	LPM ~opcode_57_common~
	SPRINT description @10570003 // ~Modifie l'alignement %ofTheTarget% en %alignment%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_57~ BEGIN
	LPM ~opcode_self_probability_57~ // ~de modifier l'alignement %ofTheTarget% en %alignment%~
END

DEFINE_PATCH_MACRO ~opcode_57_common~ BEGIN
	LOCAL_SPRINT chaotic $translations(~CHAOTIC~)
	LOCAL_SPRINT lawful $translations(~LOYAL~)
	LOCAL_SPRINT neutral $translations(~NEUTRAL~)
	LOCAL_SPRINT good $translations(~GOOD~)
	LOCAL_SPRINT evil $translations(~EVIL~)
	LOCAL_SPRINT trueNeutral @10570004 // ~neutre strict~

	PATCH_IF alignment == 17 BEGIN SPRINT alignment ~%lawful% %good%~ END
	ELSE PATCH_IF alignment == 18 BEGIN SPRINT alignment ~%lawful% %neutral%~ END
	ELSE PATCH_IF alignment == 19 BEGIN SPRINT alignment ~%lawful% %evil%~ END
	ELSE PATCH_IF alignment == 33 BEGIN SPRINT alignment ~%neutral% %good%~ END
	ELSE PATCH_IF alignment == 34 BEGIN SPRINT alignment ~%trueNeutral%~ END
	ELSE PATCH_IF alignment == 35 BEGIN SPRINT alignment ~%neutral% %evil%~ END
	ELSE PATCH_IF alignment == 49 BEGIN SPRINT alignment ~%chaotic% %good%~ END
	ELSE PATCH_IF alignment == 50 BEGIN SPRINT alignment ~%chaotic% %neutral%~ END
	ELSE PATCH_IF alignment == 51 BEGIN SPRINT alignment ~%chaotic% %evil%~ END
END

DEFINE_PATCH_MACRO ~opcode_57_is_valid~ BEGIN
	PATCH_IF parameter2 < 17 OR parameter2 > 51 OR
			 parameter2 > 19 AND parameter2 < 33 OR
			 parameter2 > 35 AND parameter2 < 49
			 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown alignment %parameter2%.~ END
	END
END


/* --------------------------------------------- *
 * Cure: Dispellable Effects (Dispel Magic) [58] *
 * --------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_58~ BEGIN
	LPM ~opcode_target_58~
END

DEFINE_PATCH_MACRO ~opcode_target_58~ BEGIN
	LOCAL_SET strref = 10580001 // ~Dissipation de la magie sur %theTarget%~
	LPM ~opcode_58_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_58~ BEGIN
	LOCAL_SET strref = 10580003 // ~de dissiper la magie sur %theTarget%~
	LPM ~opcode_58_common~
END

DEFINE_PATCH_MACRO ~opcode_58_common~ BEGIN
	LOCAL_SET castingLevel = parameter1
	LOCAL_SET type = parameter2
	LOCAL_SET mwType = type BLSR 16

	SET type = type BAND 255

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END

	PATCH_IF type == 0 BEGIN
		SET strref += 1
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
	ELSE PATCH_IF type >= 2 BEGIN
		SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
		SPRINT description ~%description% (%castingLevelStr%)~
	END

	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF mwType == 0 AND type != 0 BEGIN
			SPRINT weaponStr @10580006 // ~les armes invoquées sont toujours dissipées~
			SPRINT description ~%description% (%weaponStr%)~
		END
		ELSE PATCH_IF mwType != 0 AND mwType != 2 BEGIN
			SPRINT weaponStr @10580005 // ~les armes invoquées ne sont pas affectées~
			SPRINT description ~%description% (%weaponStr%)~
		END
	END
END

/* --------------------------- *
 * Stat: Stealth Modifier [59] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_59~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10590001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Furtivité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_59~ BEGIN
	LPF ~opcode_probability_percent~ INT_VAR strref = 10590002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la furtivité~
END

DEFINE_PATCH_MACRO ~opcode_target_59~ BEGIN
	LPF ~opcode_target_percent~ INT_VAR strref = 10590002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la furtivité~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_59~ BEGIN
	LPM ~opcode_self_probability_59~
END

DEFINE_PATCH_MACRO ~opcode_59_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------ *
 * Stat: Miscast Magic [60] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_60~ BEGIN
	LOCAL_SET value = parameter1 BAND 255
	LOCAL_SET type = parameter2

	LPM ~opcode_60_common~

	PATCH_IF value >= 100 BEGIN
		SPRINT description @10600004 // ~Empêche l'incantation des sorts %spellType%~
	END
	ELSE BEGIN
		SPRINT description @10600005 // ~Provoque l'échec de %percent% des sorts %spellType%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_60~ BEGIN
	LOCAL_SET value = parameter1 BAND 255
	LOCAL_SET type = parameter2

	LPM ~opcode_60_common~

	PATCH_IF value >= 100 BEGIN
		SPRINT description @10600006 // ~Provoque l'échec des sorts %spellType% incantés par %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10600007 // ~Provoque l'échec de %percent% des sorts %spellType% incantés par %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_60~ BEGIN
	LOCAL_SET value = parameter1 BAND 255
	LOCAL_SET type = parameter2

	LPM ~opcode_60_common~

	PATCH_IF value >= 100 BEGIN
		SPRINT description @10600008 // ~de provoquer l'échec des sorts %spellType% incantés par %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10600009 // ~de provoquer l'échec de %percent% des sorts %spellType% incantés par %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_60_common~ BEGIN
    SPRINT percent @10002 // ~%value% %~

	PATCH_IF type == 0 OR type== 3 BEGIN
		SPRINT spellType @10600001 // ~profanes~
	END
	ELSE PATCH_IF type == 1 OR type== 4 BEGIN
		SPRINT spellType @10600002 // ~divins~
	END
	ELSE PATCH_IF type == 2 OR type== 5 BEGIN
		SPRINT spellType @10600003 // ~innés~
	END
END

DEFINE_PATCH_MACRO ~opcode_60_is_valid~ BEGIN
	PATCH_IF (parameter1 BAND 255) == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No change detected: Value = Value + 0.~ END
	END
	PATCH_IF parameter2 < 0 OR parameter2 > 5 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %parameter2%.~ END
	END
END

/* --------------------------------------- *
 * Spell: Priest Spell Slots Modifier [62] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_62~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET level = parameter2
	LOCAL_SET spellLevelMax = 7

	LPF ~opcode_self_42_62~ INT_VAR level amount startStrref = 10620001 RET description END
END

/* ----------------------- *
 * State: Infravision [63] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_63~ BEGIN
	SPRINT description @10630001 // ~Infravision~
END

/* ------------------------------ *
 * State: Remove Infravision [64] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_64~ BEGIN
	SPRINT description @10640001 // ~Neutralise l'infravision~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_64~ BEGIN
	SPRINT description @10640003 // ~de neutraliser l'infravision %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_64~ BEGIN
	SPRINT description @10640002 // ~Neutralise l'infravision %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_64~ BEGIN
	LPM ~opcode_self_probability_64~ // ~de neutraliser l'infravision %ofTheTarget%~
END

/* ------------------------------- *
 * Summon: Creature Summoning [67] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_67~ BEGIN
	LPM ~opcode_target_67~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_67~ BEGIN
	LPM ~opcode_target_probability_67~
END

DEFINE_PATCH_MACRO ~opcode_target_67~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END

	PATCH_IF NOT ~%creatureName%~ STRING_EQUAL ~~ BEGIN
		// Allégiance de la créature non modifiée, donc intéressant
		PATCH_IF parameter2 == 2 OR parameter2 == 4 OR parameter2 >= 6 BEGIN
			LPF ~get_creature_allegiance~ STR_VAR file = EVAL ~%resref%~ RET allegiance END
			PATCH_IF allegiance >= 200 BEGIN // EVILCUTOFF
				SPRINT description @10670002 // ~Invoque une créature hostile (%creatureName%)~
			END
			ELSE PATCH_IF allegiance <= 30 BEGIN // GOODCUTOFF
				SPRINT description @10670005 // ~Invoque une créature alliée (%creatureName%)~
			END
			ELSE BEGIN
				SPRINT description @10670006 // ~Invoque une créature neutre (%creatureName%)~
			END
		END
		// Allégiance variable selon celle de la cible, donc pas de précision
		ELSE BEGIN
			SPRINT description @10670001 // ~Invoque une créature (%creatureName%)~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_67~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END

	PATCH_IF NOT ~%creatureName%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF parameter2 == 2 OR parameter2 == 4 OR parameter2 >= 6 BEGIN
			LPF ~get_creature_allegiance~ STR_VAR file = EVAL ~%resref%~ RET allegiance END
			PATCH_IF allegiance >= 200 BEGIN // EVILCUTOFF
				SPRINT description @10670004 // ~d'invoquer une créature hostile (%creatureName%)~
			END
			ELSE PATCH_IF allegiance <= 30 BEGIN // GOODCUTOFF
				SPRINT description @10670007 // ~d'invoquer une créature alliée (%creatureName%)~
			END
			ELSE BEGIN
				SPRINT description @10670008 // ~d'invoquer une créature neutre (%creatureName%)~
			END
		END
		ELSE BEGIN
			SPRINT description @10670003 // ~d'invoquer une créature (%creatureName%)~
		END
	END
END

/* ------------------------------ *
 * Summon: Unsummon Creature [68] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_target_68~ BEGIN
	//FIXME fonctionne aussi si la créature n'est pas invoquée...
	SPRINT description @10680001 // ~Renvoie %theTarget% si c'est une créature invoquée~
END


DEFINE_PATCH_MACRO ~opcode_target_probability_68~ BEGIN
	SPRINT description @10680002 // ~de renvoyer %theTarget% si c'est une créature invoquée~
END

/* ----------------------------------------------- *
 * Protection: From Detection (Non-Detection) [69] *
 * ----------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_69~ BEGIN
	SPRINT description @10690001 // ~Non-détection~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_69~ BEGIN
	SPRINT description @10690003 // ~de lancer non-détection sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_69~ BEGIN
	SPRINT description @10690002 // ~Lance non-détection sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_69~ BEGIN
	LPM ~opcode_self_probability_69~ // ~de lancer non-détection sur %theTarget%~
END

/* ------------------------ *
 * Cure: Non-Detection [70] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_70~ BEGIN
	SPRINT description @10700001 // ~Immunité à la non-détection~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_70~ BEGIN
	SPRINT description @10700003 // ~de dissiper la non-détection %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_70~ BEGIN
	SPRINT description @10700002 // ~Dissipe la non-détection %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_70~ BEGIN
	SPRINT description @10700003 // ~de dissiper la non-détection %ofTheTarget%~
END

/* --------------- *
 * Sex Change [71] *
 * --------------- */
DEFINE_PATCH_MACRO ~opcode_self_71~ BEGIN
	LOCAL_SET strref = 10710001 // ~Inverse le sexe %ofTheTarget%~

	LPM ~opcode_71_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_71~ BEGIN
	LOCAL_SET strref = 10710011 // ~d'inverser le sexe %ofTheTarget%~

	LPM ~opcode_71_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_71~ BEGIN
	LPM ~opcode_self_71~
END

DEFINE_PATCH_MACRO ~opcode_target_71~ BEGIN
	LPM ~opcode_self_probability_71~
END

DEFINE_PATCH_MACRO ~opcode_71_common~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		PATCH_IF parameter1 >= 1 AND parameter1 <= 2 BEGIN
			SET strref += parameter1
        END
        ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Sexe a gerer : %parameter1%~ END
        END
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

/* -------------------------------- *
 * Stat: Extra Damage Modifier [73] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_73~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10730001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_73~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10730002 RET description END // ~les dégâts~
END

DEFINE_PATCH_MACRO ~opcode_target_73~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10730002 RET description END // ~les dégâts~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_73~ BEGIN
	LPM ~opcode_self_probability_73~
END

DEFINE_PATCH_MACRO ~opcode_73_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* --------------------- *
 * State: Blindness [74] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_74~ BEGIN
	SPRINT description @10740001 // ~Cécité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_74~ BEGIN
	SPRINT description @10740003 // ~d'aveugler %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_74~ BEGIN
	SPRINT description @10740002 // ~Aveugle %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_74~ BEGIN
	LPM ~opcode_self_probability_74~ // ~d'aveugler %theTarget%~
END

/* -------------------- *
 * Cure: Blindness [75] *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_75~ BEGIN
	SPRINT description @10750001 // ~Immunité à la cécité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_75~ BEGIN
	SPRINT description @10750003 // ~de guérir la cécité %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_75~ BEGIN
	SPRINT description @10750002 // ~Guérit la cécité %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_75~ BEGIN
	LPM ~opcode_self_probability_75~ // ~de guérir la cécité %ofTheTarget%~
END

/* --------------------------- *
 * State: Feeblemindedness [76] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_76~ BEGIN
	SPRINT description @10760001 // ~Débilité mentale~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_76~ BEGIN
	SPRINT description @10760003 // ~d'infliger Débilité mentale %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_76~ BEGIN
	SPRINT description @10760002 // ~Inflige Débilité mentale %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_76~ BEGIN
	LPM ~opcode_self_probability_76~ // ~d'infliger Débilité mentale %toTheTarget%~
END

/* --------------------------- *
 * Cure: Feeblemindedness [77] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_77~ BEGIN
	SPRINT description @10770001 // ~Immunité à la débilité mentale~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_77~ BEGIN
	SPRINT description @10770003 // ~de guérir la Débilité mentale %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_77~ BEGIN
	SPRINT description @10770002 // ~Guérit la Débilité mentale %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_77~ BEGIN
	LPM ~opcode_self_probability_77~ // ~de guérir la Débilité mentale %ofTheTarget%~
END

/* ------------------- *
 * State: Disease [78] *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_self_78~ BEGIN
	SET strref = 10780000
	LPM ~opcode_78_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_78~ BEGIN
	SET strref = 10780100
	LPM ~opcode_78_common~
END

DEFINE_PATCH_MACRO ~opcode_target_78~ BEGIN
	LPM ~opcode_self_78~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_78~ BEGIN
	LPM ~opcode_self_probability_78~
END

DEFINE_PATCH_MACRO ~opcode_78_common~ BEGIN
	SET amount = parameter1
	SET frequencyMultiplier = 1
	SET frequency = 1
	SET p4IsActive = isExternal AND parameter4 != 0 AND is_ee
	SET type = parameter2

	PATCH_IF type >= 0 AND type <= 3 BEGIN
		// TODO parameter == 1 : Efficace que si les points de vie actuels >= 100 / Valeur ou si #P4 != 0
		// Compliqué de faire une phrase simple
		// FIXME Ces 4 entrée sont identiques à celle de l'opcode 25 (poison)
		PATCH_IF (type == 0 AND (parameter1 != 0 OR p4IsActive)) OR
				(type == 1 AND (parameter1 > 1 OR p4IsActive)) BEGIN
			SET amount = 1
		END
		ELSE PATCH_IF type == 2 AND parameter1 > 0 BEGIN
			SET amount = parameter1
		END
		ELSE BEGIN
			SET amount = 1
			SET frequency = parameter1
		END

		PATCH_IF p4IsActive AND type >= 2 AND type <= 3 BEGIN
			SET frequency = frequency * parameter4
			// P4 divise également les dégâts si P2 == 2, avec un minimum à 1
			PATCH_IF type == 2 BEGIN
				SET amount = amount / parameter4
				PATCH_IF amount < 1 BEGIN
					amount = 1
				END
			END
		END
		PATCH_IF frequency < 1 BEGIN
			SET frequency = 1
		END

		PATCH_IF amount == 1 AND frequency == 1 BEGIN
			SET strref += 20
		END
		ELSE PATCH_IF amount > 1 AND frequency == 1 BEGIN
			SET strref += 22
		END
		ELSE PATCH_IF amount == 1 AND frequency > 1 BEGIN
			SET strref += 21
		END
		ELSE BEGIN
			SET strref += 23
		END
		// En théorie toutes les versions infligent du dégâts de poison, je laisse dans le doute
		PATCH_IF is_ee == 1 BEGIN
			SET strref += 4
		END
	END
	ELSE PATCH_IF type >= 4 AND type <= 9 BEGIN
		SET strref += type
		PATCH_IF amount < 0 BEGIN
			amount = ABS amount
			SET strref += 10
		END
	END
	ELSE PATCH_IF type == 10 BEGIN
		SET strref += type
	END
	ELSE PATCH_IF type == 11 OR type == 12 BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Mold touch à gerer : %amount% : %frequency% : %resref%~ END
	END
	ELSE PATCH_IF type == 13 BEGIN
		SET strref = 10780003
		PATCH_IF amount < 0 BEGIN
			amount = ABS amount
			SET strref += 10
		END
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_78_is_valid~ BEGIN
	PATCH_IF parameter2 < 0 OR parameter2 > 13 OR parameter2 > 10 AND NOT is_ee BEGIN
		SET isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Unknown type : %parameter2%~ END
	END
	PATCH_IF (timingMode == TIMING_permanent OR
			 timingMode == TIMING_delayed OR
			 timingMode == 7 OR
			 timingMode == TIMING_permanent_after_death) AND duration == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_warning~ STR_VAR type = ~warning~ message = EVAL ~Opcode %opcode%: This effect does not work with Timing Mode %timingMode%.~ END
	END
END

/* ------------------ *
 * Cure: Disease [79] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_79~ BEGIN
	SPRINT description @10790001 // ~Immunité aux maladies~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_79~ BEGIN
	SPRINT description @10790003 // ~de guérir les maladies %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_79~ BEGIN
	SPRINT description @10790002 // ~Guérit les maladies %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_79~ BEGIN
	LPM ~opcode_self_probability_79~ // ~de guérir les maladies %ofTheTarget%~
END

/* ------------- *
 * Deafness [80] *
 * ------------- */
DEFINE_PATCH_MACRO ~opcode_self_80~ BEGIN
	SPRINT description @10800001 // ~Surdité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_80~ BEGIN
	SPRINT description @10800003 // ~d'assourdir %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_80~ BEGIN
	SPRINT description @10800002 // ~Assourdit %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_80~ BEGIN
	LPM ~opcode_self_probability_80~ // @~d'assourdir %theTarget%~
END

/* ------------------- *
 * Cure: Deafness [81] *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_self_81~ BEGIN
	SPRINT description @10810001 // ~Immunité à la surdité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_81~ BEGIN
	SPRINT description @10810003 // ~de guérir la surdité %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_81~ BEGIN
	SPRINT description @10810002 // ~Guérit la surdité %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_81~ BEGIN
	LPM ~opcode_self_probability_81~ // ~de guérir la surdité %ofTheTarget%~
END

/* -------------------------------- *
 * Protection: From Projectile [83] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_83~ BEGIN
	// Comment trouver les correspondances sans checker tous les sorts ??
	// TODO une seule liste pour cet opcode et le 197

	// Warning de Region of Terror + Auror kit
	// 94 : Instant area effect : Tremblement de terre (SPPR720), Zone de magie entropique (SPIN778), Terreur de l'Ecorcheur (SPIN807)
	// 226 : Fireseed : aucune correspondance
	// 227 : convocation d'insecte SPPR319
	// 229 : Nuée de météores SPWI911, Tempête de feu SPPR705
	// 231 : Icewind Glyph hit : aucune correspondance

	// ITEMS BG2EE
	// 219 : Désintégration (SPWI616)
	// 205 : Instant area small => Repousser les morts-vivants (SPPR515), Invisibilité sur 3 mètre (SPWI307)
	// 320 : aucune correspondance
	PATCH_MATCH parameter2 WITH
		  1 2 3 4 5 283 284 285 286 287 288 289 290 291 BEGIN SPRINT description @10830001 END // ~Immunité contre les flèches~
		  6 7 8 9 10 292 293 294 295 296 BEGIN SPRINT description @10830002 END // ~Immunité contre les haches de jet~
		 297 298 299 300 301 302 303 BEGIN SPRINT description @10830004 END // ~Immunité contre les carreaux~
		 16 17 18 19 304 305 306 307 308 BEGIN SPRINT description @10830005 END // ~Immunité contre les billes~
		 26 27 28 29 30 309 310 311 313 BEGIN SPRINT description @10830006 END // ~Immunité contre les dagues de jet~
		 31 32 33 34 35 313 314 315 316 317 318 BEGIN SPRINT description @10830007 END // ~Immunité contre les flèchettes~
		 55 56 57 58 59 BEGIN SPRINT description @10830008 END // ~Immunité contre les lances de jet~
		 14 64 208 274 BEGIN SPRINT description @10830003 END // ~Immunité contre les attaques de regard~
		 36 67 68 69 70 71 72 73 74 75 76 77 BEGIN SPRINT description @10830009 END // ~Immunité contre les missiles magiques~
		 102 BEGIN SPRINT description @10830010 END // ~Immunité contre les flèches à flamme bleue~
		 39 442 BEGIN SPRINT description @10830011 END // ~Immunité contre les éclairs~
		 62 63 259 319 BEGIN SPRINT description @10830012 END // ~Immunité contre les toiles d'araignées~
		DEFAULT
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Type de projectile '%parameter2%'~ END
    END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_83~ BEGIN
	LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: TODO: self_probability~ END
END

DEFINE_PATCH_MACRO ~opcode_target_83~ BEGIN
	LPM ~opcode_self_83~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_83~ BEGIN
	LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: TODO: target_probability~ END
END

/* ------------------------------------------- *
 * Stat: Magical Fire Resistance Modifier [84] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_84~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10840001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts de feu magiques~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_84~ BEGIN
	LOCAL_SPRINT resistName @10840001 // ~Résistance aux dégâts de feu magiques~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_84~ BEGIN
	LOCAL_SPRINT resistName @10840001 // ~Résistance aux dégâts de feu magiques~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_84~ BEGIN
	LPM ~opcode_self_probability_84~
END

DEFINE_PATCH_MACRO ~opcode_84_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------------------- *
 * Stat: Magical Cold Resistance Modifier [85] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_85~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10850001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts de froid magiques~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_85~ BEGIN
	LOCAL_SPRINT resistName @10850001 // ~Résistance aux dégâts de froid magiques~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_85~ BEGIN
	LOCAL_SPRINT resistName @10850001 // ~Résistance aux dégâts de froid magiques~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_85~ BEGIN
	LPM ~opcode_self_probability_85~
END

DEFINE_PATCH_MACRO ~opcode_85_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* --------------------------------------- *
 * Stat: Slashing Resistance Modifier [86] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_86~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10860001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts tranchants~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_86~ BEGIN
	LOCAL_SPRINT resistName @10860001 // ~Résistance aux dégâts tranchants~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_86~ BEGIN
	LOCAL_SPRINT resistName @10860001 // ~Résistance aux dégâts tranchants~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_86~ BEGIN
	LPM ~opcode_self_probability_86~
END

DEFINE_PATCH_MACRO ~opcode_86_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* --------------------------------------- *
 * Stat: Crushing Resistance Modifier [87] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_87~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10870001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts contondants~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_87~ BEGIN
	LOCAL_SPRINT resistName @10870001 // ~Résistance aux dégâts contondants~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_87~ BEGIN
	LOCAL_SPRINT resistName @10870001 // ~Résistance aux dégâts contondants~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_87~ BEGIN
	LPM ~opcode_self_probability_87~
END

DEFINE_PATCH_MACRO ~opcode_87_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* --------------------------------------- *
 * Stat: Piercing Resistance Modifier [88] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_88~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10880001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts perforants~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_88~ BEGIN
	LOCAL_SPRINT resistName @10880001 // ~Résistance aux dégâts perforants~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_88~ BEGIN
	LOCAL_SPRINT resistName @10880001 // ~Résistance aux dégâts perforants~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_88~ BEGIN
	LPM ~opcode_self_probability_88~
END

DEFINE_PATCH_MACRO ~opcode_88_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* --------------------------------------- *
 * Stat: Missiles Resistance Modifier [89] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_89~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10890001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux dégâts de projectiles~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_89~ BEGIN
	LOCAL_SPRINT resistName @10890001 // ~Résistance aux dégâts de projectiles~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_89~ BEGIN
	LOCAL_SPRINT resistName @10890001 // ~Résistance aux dégâts de projectiles~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_89~ BEGIN
	LPM ~opcode_self_probability_89~
END

DEFINE_PATCH_MACRO ~opcode_89_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------ *
 * Stat: Open Locks Modifier [90] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_90~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10900001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Crochetage de serrures~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_90~ BEGIN
	LPF ~opcode_probability_percent~ INT_VAR strref = 10900002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le crochetage de serrures~
END

DEFINE_PATCH_MACRO ~opcode_target_90~ BEGIN
	LPF ~opcode_target_percent~ INT_VAR strref = 10900002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le crochetage de serrures~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_90~ BEGIN
	LPM ~opcode_self_probability_90~
END

/* ------------------------------ *
 * Stat: Find Traps Modifier [91] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_91~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10910001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Détection / désamorçage des pièges~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_91~ BEGIN
	LPF ~opcode_probability_percent~ INT_VAR strref = 10910002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la détection / désamorçage des pièges~
END

DEFINE_PATCH_MACRO ~opcode_target_91~ BEGIN
	LPF ~opcode_target_percent~ INT_VAR strref = 10910002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la détection / désamorçage des pièges~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_91~ BEGIN
	LPM ~opcode_self_probability_91~
END

DEFINE_PATCH_MACRO ~opcode_91_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* -------------------------------- *
 * Stat: Pick Pockets Modifier [92] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_92~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10920001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Vol à la tire~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_92~ BEGIN
	LPF ~opcode_probability_percent~ INT_VAR strref = 10920002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la détection/désamorçage des pièges~
END

DEFINE_PATCH_MACRO ~opcode_target_92~ BEGIN
	LPF ~opcode_target_percent~ INT_VAR strref = 10920002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la détection/désamorçage des pièges~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_92~ BEGIN
	LPM ~opcode_self_probability_92~
END

DEFINE_PATCH_MACRO ~opcode_92_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* --------------------------- *
 * Stat: Fatigue Modifier [93] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_93~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10930001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Fatigue~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_93~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10930002 RET description END // ~la fatigue~
END

DEFINE_PATCH_MACRO ~opcode_target_93~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10930002 RET description END // ~la fatigue~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_93~ BEGIN
	LPM ~opcode_self_probability_93~ // ~la fatigue~
END

DEFINE_PATCH_MACRO ~opcode_93_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------- *
 * Stat: Drunkenness Modifier [94] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_94~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10940001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Ivresse~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_94~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10940002 RET description END // ~l'ivresse~
END

DEFINE_PATCH_MACRO ~opcode_target_94~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10940002 RET description END // ~l'ivresse~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_94~ BEGIN
	LPM ~opcode_self_probability_94~ // ~l'ivresse~
END

DEFINE_PATCH_MACRO ~opcode_94_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ---------------------------- *
 * Tracking Skill Modifier [95] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_95~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10950001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Pistage~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_95~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10950002 RET description END // ~le pistage~
END

DEFINE_PATCH_MACRO ~opcode_target_95~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10950002 RET description END // ~le pistage~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_95~ BEGIN
	LPM ~opcode_self_probability_95~ // ~le pistage~
END

DEFINE_PATCH_MACRO ~opcode_95_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ----------------------- *
 * Stat: Level Change [96] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_96~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10960001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Niveau~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_96~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10960002 RET description END // ~le niveau~
END

DEFINE_PATCH_MACRO ~opcode_target_96~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10960002 RET description END // ~le niveau~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_96~ BEGIN
	LPM ~opcode_self_probability_96~ // ~le niveau~
END

DEFINE_PATCH_MACRO ~opcode_96_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ---------------------------------- *
 * Stat: Strength-Bonus Modifier [97] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_97~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10970001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force exceptionnelle~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_97~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 10970002 RET description END // ~la force exceptionnelle~
END

DEFINE_PATCH_MACRO ~opcode_target_97~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 10970002 RET description END // ~la force exceptionnelle~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_97~ BEGIN
	LPM ~opcode_self_probability_97~ // ~la force exceptionnelle~
END

DEFINE_PATCH_MACRO ~opcode_97_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* --------------------- *
 * HP: Regeneration [98] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_98~ BEGIN
	SET strref = 10980001
	LPM ~opcode_98_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_98~ BEGIN
	SET strref = 10980011
	LPM ~opcode_98_common~
END

DEFINE_PATCH_MACRO ~opcode_target_98~ BEGIN
	SET strref = 10980006
	LPM ~opcode_98_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_98~ BEGIN
	LPM ~opcode_self_probability_98~
END

DEFINE_PATCH_MACRO ~opcode_98_common~ BEGIN
	// TODO QUASI identique à opcode 25 et 78 => Mixin
	SET amount1 = parameter1
	SET amount2 = 0
	SET frequencyMultiplier = 1
	SET amount = 0
	SET frequency = 1

	PATCH_IF parameter2 >= 5 BEGIN
        LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid value for parameter2 : %parameter2% >= 5 == crash the game~ END
    END

	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF isExternal BEGIN
			SET amount2 = parameter3
			SET frequencyMultiplier = parameter4
		END

		PATCH_IF parameter2 == 0 OR parameter2 == 1 BEGIN
			PATCH_IF parameter2 == 0 AND amount1 == 0 BEGIN
				LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: parameter1 needs to be non-zero : %parameter1%~ END
			END
			PATCH_IF parameter2 == 1 AND (amount1 < 1 OR amount1 > 101) BEGIN
				LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: parameter1 between 1 and 101 : %parameter1%~ END
			END
			SET amount = 1
		END
		ELSE PATCH_IF parameter2 == 2 BEGIN
			SET amount = amount1
			SET frequency = frequencyMultiplier
		END
		ELSE PATCH_IF parameter2 == 3 OR parameter2 == 4 BEGIN
			SET frequency = amount1 * frequencyMultiplier
			PATCH_IF parameter2 == 3 BEGIN
				SET amount = 1
			END
			ELSE PATCH_IF parameter2 == 4 BEGIN
				SET amount = amount2
			END
		END
	END
	ELSE BEGIN
		PATCH_IF parameter2 == 0 OR parameter2 == 1 OR parameter2 == 2 BEGIN
			SET amount = amount1
		END
		ELSE PATCH_IF parameter2 == 3 BEGIN
			SET amount = 1
			SET frequency = amount1
		END
		ELSE PATCH_IF parameter2 == 4 BEGIN
			PATCH_IF isExternal BEGIN
				SET amount = parameter3
				SET frequency = amount1
			END
			ELSE BEGIN
				LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Verifier le fonctionnement avec type == 4~ END
			END
		END
	END

	PATCH_IF is_ee == 0 AND parameter2 == 2 BEGIN
		SET value = amount
		SPRINT amount @10002 // ~%value% %~
		SET strref += 4
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Régénère %percent% des points de vie~
	END
	ELSE PATCH_IF amount == 1 AND frequency == 1 BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Régénère 1 point de vie par seconde~
	END
	ELSE PATCH_IF amount > 1 AND frequency == 1 BEGIN
		SET strref += 1
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Régénère %amount% points de vie par seconde~
	END
	ELSE PATCH_IF amount == 1 AND frequency > 1 BEGIN
		SET strref += 2
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Régénère 1 point de vie toutes les %frequency% secondes~
	END
	ELSE PATCH_IF amount > 1 AND frequency > 1 BEGIN
		SET strref += 3
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Régénère %amount% points de vie toutes les %frequency% secondes~
	END
END

/* ------------------------------------ *
 * Spell Effect: Duration Modifier [99] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_99~ BEGIN
	SET strref = 10990001

	LPM ~opcode_99_common~
END
DEFINE_PATCH_MACRO ~opcode_self_probability_99~ BEGIN
	SET strref = 10990021

	LPM ~opcode_99_common~
END
DEFINE_PATCH_MACRO ~opcode_target_99~ BEGIN
	SET strref = 10990011

	LPM ~opcode_99_common~
END
DEFINE_PATCH_MACRO ~opcode_target_probability_99~ BEGIN
	LPM ~opcode_self_probability_99~
END

DEFINE_PATCH_MACRO ~opcode_99_common~ BEGIN
	LOCAL_SET duration = parameter1
	LOCAL_SET type = parameter2

	SET strref += type

	PATCH_IF duration < 100 AND duration > 0 BEGIN
		SET value = 100 - duration
		SPRINT duration @10002 // ~%value% %~
		SET strref += 3
	END
	ELSE PATCH_IF duration > 100 BEGIN
		SET value = duration - 100
		SPRINT duration @10002 // ~%value% %~
		SET strref += 6
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

/* ------------------------------------ *
 * Protection: from Creature Type [100] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_100~ BEGIN
	SET strref = 11000001 // ~Immunité aux attaques et aux sorts de %creatureType%~
	LPM ~opcode_100_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_100~ BEGIN
	SET strref = 11000005 // ~de résister aux attaques et aux sorts des %creatureType%~
	LPM ~opcode_100_common~
END

DEFINE_PATCH_MACRO ~opcode_target_100~ BEGIN
	SET strref = 11000003 // ~Immunise %theTarget% contre les attaques et les sorts des %creatureType%~
	LPM ~opcode_100_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_100~ BEGIN
	LPM ~opcode_self_probability_100~
END

DEFINE_PATCH_MACRO ~opcode_100_common~ BEGIN
	PATCH_IF parameter1 == 0 AND parameter2 == 2 BEGIN
		SET strref += 1
	END
	ELSE BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

/* ----------------------------- *
 * Protection: from Opcode [101] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_101~ BEGIN
	LOCAL_SET cOpcode = parameter2
	LOCAL_SET strref = 11010000 + cOpcode
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Immunité à xxx~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_101~ BEGIN
	LOCAL_SET cOpcode = parameter2
	LOCAL_SET strref = 11011000 + cOpcode
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~d'immuniser %theTarget% à xxx~
END

DEFINE_PATCH_MACRO ~opcode_target_101~ BEGIN
	LOCAL_SET cOpcode = parameter2
	LOCAL_SET strref = 11012000 + cOpcode
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Immunise %theTarget% à xxx~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_101~ BEGIN
	LPM ~opcode_self_probability_101~ // ~que %theTarget% résiste à xxx~
END

/* -------------------------------------- *
 * Spell: Immunity (by Power Level) [102] *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_102~ BEGIN
	LOCAL_SET spellLevel = ~%parameter1%~
	SPRINT description @11020001 // ~Immunité aux sorts de niveau %spellLevel%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_102~ BEGIN
	LOCAL_SET spellLevel = ~%parameter1%~
	SPRINT description @11020003 // ~d'immuniser %theTarget% aux sorts de niveau %spellLevel%~
END

DEFINE_PATCH_MACRO ~opcode_target_102~ BEGIN
	LOCAL_SET spellLevel = ~%parameter1%~
	SPRINT description @11020002 // ~Immunise %theTarget% aux sorts de niveau %spellLevel%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_102~ BEGIN
	LPM ~opcode_self_probability_102~ // ~d'immuniser %theTarget% aux sorts de niveau %spellLevel%~
END

/* ----------------------------- *
 * Stat: Experience Points [104] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_104~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 11040001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Expérience~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_104~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 11040002 RET description END // ~l'expérience~
END

DEFINE_PATCH_MACRO ~opcode_target_104~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 11040002 RET description END // ~l'expérience~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_104~ BEGIN
	LPM ~opcode_self_probability_104~
END

/* ---------------- *
 * Stat: Gold [105] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_105~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @11050002 // ~Diminue le nombre de pièces d'or %ofTheTarget% à %amount%~
	END
	ELSE BEGIN
		LPF ~opcode_target~ INT_VAR strref = 11050001 RET description END // ~l'or~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_105~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @11050002 // ~Diminue le nombre de pièces d'or %ofTheTarget% à %amount%~
	END
	ELSE BEGIN
		LPF ~opcode_probability~ INT_VAR strref = 11050001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~l'or~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_105~ BEGIN
	LPM ~opcode_self_105~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_105~ BEGIN
	LPM ~opcode_self_probability_105~
END

/* --------------------------------- *
 * Stat: Morale Break Modifier [106] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_106~ BEGIN
	SET ignoreDuration = 1
	PATCH_IF parameter1 <= 1 AND parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @11060001 // ~Le moral %ofTheTarget% ne peut flancher~
	END
	ELSE BEGIN
		SET value = ABS parameter1
		PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN
			LPF ~percent_value~ INT_VAR value RET value END
		END
		PATCH_IF parameter1 < 0 BEGIN
			SPRINT description @11060002 // ~Le moral %ofTheTarget% est renforcé de %value%~
		END
		ELSE BEGIN
			SPRINT description @11060003 // ~Le moral %ofTheTarget% est affaibli de %value%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_106~ BEGIN
	SET ignoreDuration = 1
	PATCH_IF parameter1 <= 1 AND parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @11060004 // ~de garder le moral %ofTheTarget% au plus haut~
	END
	ELSE BEGIN
		SET value = ABS parameter1
		PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN
			LPF ~percent_value~ INT_VAR value RET value END
		END
		PATCH_IF parameter1 < 0 BEGIN
			SPRINT description @11060005 // ~de renforcer le moral %ofTheTarget% de %value%~
		END
		ELSE BEGIN
			SPRINT description @11060006 // ~d'affaiblir le moral %ofTheTarget% de %value%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_106~ BEGIN
	LPM ~opcode_self_106~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_106~ BEGIN
	LPM ~opcode_self_probability_106~
END

/* ---------------------- *
 * Stat: Reputation [108] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_108~ BEGIN
    LPM ~opcode_108_common~
    LPF ~opcode_mod~ INT_VAR strref = EVAL ~%strref%~ STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Réputation du personnage~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_108~ BEGIN
    LPM ~opcode_108_common~
    SET strref += 1
	LPF ~opcode_probability~ INT_VAR strref = EVAL ~%strref%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_108~ BEGIN
    LPM ~opcode_108_common~
    SET strref += 1
    LPF ~opcode_target~ INT_VAR strref = EVAL ~%strref%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_108~ BEGIN
	LPM ~opcode_self_probability_108~
END

DEFINE_PATCH_MACRO ~opcode_108_common~ BEGIN
	SET strref = 11080001 // ~Réputation~
    PATCH_IF is_ee == 1 BEGIN
		SET strref = 11080003 // ~Réputation du personnage~
		PATCH_IF parameter2 == 3 OR parameter2 == 4 BEGIN
			SET strref = 11080005 // ~Réputation du groupe~
			PATCH_IF parameter2 == 3 BEGIN
				SET parameter1 = parameter1 * 10
				SET parameter2 = MOD_TYPE_cumulative
			END
			ELSE PATCH_IF parameter2 == 4 BEGIN
				SET parameter1 = 100
				SET parameter2 = MOD_TYPE_flat
			END
		END
    END
END

/* ----------------- *
 * State: Hold [109] *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_109~ BEGIN
	SPRINT idsFile $ids_files(~%parameter2%~)
	LOOKUP_IDS_SYMBOL_OF_INT symbol ~%idsFile%~ ~%parameter1%~

	PATCH_IF NOT ~%symbol%~ STRING_EQUAL ~0~ BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
		SPRINT description @11090001 // ~Paralyse les %creatureType%~
	END
	ELSE BEGIN
		SPRINT description @11090002 // ~Paralyse %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_109~ BEGIN
	SPRINT idsFile $ids_files(~%parameter2%~)
	LOOKUP_IDS_SYMBOL_OF_INT symbol ~%idsFile%~ ~%parameter1%~

	PATCH_IF NOT ~%symbol%~ STRING_EQUAL ~0~ BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
		SPRINT description @11090001 // ~Paralyse les %creatureType%~
	END
	ELSE BEGIN
		SPRINT description @11090002 // ~Paralyse %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_109~ BEGIN
	SPRINT idsFile $ids_files(~%parameter2%~)
	LOOKUP_IDS_SYMBOL_OF_INT symbol ~%idsFile%~ ~%parameter1%~

	PATCH_IF NOT ~%symbol%~ STRING_EQUAL ~0~ BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
		SPRINT description @11090003 // ~de paralyser les %creatureType%~
	END
	ELSE BEGIN
		SPRINT description @11090004 // ~de paralyser %theTarget%~
	END
END

/* --------------------------------- *
 * Item: Create Magical Weapon [111] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_111~ BEGIN
	LOCAL_SET amount = parameter1
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF amount == 1 BEGIN
			SPRINT description @11110001 // ~Crée une arme magique (%itemName%)~
		END
		ELSE BEGIN
			SPRINT description @11110002 // ~Crée %amount% armes magiques (%itemName%)~
		END
	END
END

/* ----------------------- *
 * Detect: Alignment [115] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_115~ BEGIN
	LOCAL_SET strref = 11150001 + parameter2

	PATCH_IF parameter2 > 2 BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid value for parameter2 : %parameter2% (0, 1 or 2 expected)~ END
	END
	ELSE BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Détection du xxx~
	END
END

/* --------------------------------- *
 * Cure: (Remove) Invisibility [116] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_116~ BEGIN
	LPM ~opcode_self_47~ // ~Immunité à l'invisibilité~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_116~ BEGIN
	LPM ~opcode_self_probability_47~ // ~de dissiper l'invisibilité %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_116~ BEGIN
	LPM ~opcode_target_47~ // ~Dissipe l'invisibilité %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_116~ BEGIN
	LPM ~opcode_self_probability_116~ // ~de dissiper l'invisibilité %ofTheTarget%~
END

/* ------------------------------- *
 * Spell Effect: Reveal Area [117] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_117~ BEGIN
	SPRINT description @11170001 // ~Révèle l'entièreté de la carte~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_117~ BEGIN
	SPRINT description @11170002 // ~de révéler l'entièreté de la carte~
END

DEFINE_PATCH_MACRO ~opcode_target_117~ BEGIN
	LPM ~opcode_self_117~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_117~ BEGIN
	LPM ~opcode_self_probability_117~
END

/* -------------------------------- *
 * Spell Effect: Mirror Image [119] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_119~ BEGIN
END

DEFINE_PATCH_MACRO ~opcode_self_probability_119~ BEGIN
	SPRINT description @11190003 // ~de lancer Image miroir sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_119~ BEGIN
	SPRINT description @11190002 // ~Lance Image miroir sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_119~ BEGIN
	LPM ~opcode_self_probability_119~ // ~de lancer Image miroir sur %theTarget%~
END

/* ------------------------------------ *
 * Protection: from Melee Weapons [120] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_120~ BEGIN
	SET strref = 11200001 // ~Immunité contre les %weaponType% %enchantment%~
	LPM ~opcode_120_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_120~ BEGIN
	SET strref = 11200005 // ~d'immuniser %theTarget% contre les %weaponType% %enchantment%~
	LPM ~opcode_120_common~
END

DEFINE_PATCH_MACRO ~opcode_target_120~ BEGIN
	SET strref = 11200003 // ~Immunise %theTarget% contre les %weaponType% %enchantment%~
	LPM ~opcode_120_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_120~ BEGIN
	LPM ~opcode_self_probability_120~
END

DEFINE_PATCH_MACRO ~opcode_120_common~ BEGIN
	SET enchantment = parameter1
	SET type = parameter2
	SET strrefWeaponType = 11200010 + type

	LPF ~getTranslation~ INT_VAR strref = strrefWeaponType opcode RET weaponType = string END // ~armes de mêlée xxx~

	PATCH_IF type == 0 BEGIN
		LPF ~signed_value~ INT_VAR value = EVAL ~%enchantment%~ RET enchantment = value END
	END
	ELSE BEGIN
		SET strref += 1
    END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Immunité contre les %weaponType%~
END

/* --------------------------------- *
 * Item: Create Inventory Item [122] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_122~ BEGIN
	LOCAL_SET strref = 11220001
	LPM ~opcode_122_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_122~ BEGIN
	LOCAL_SET strref = 11220004
	LPM ~opcode_122_common~
END

DEFINE_PATCH_MACRO ~opcode_target_122~ BEGIN
	LPM ~opcode_self_122~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_122~ BEGIN
	LPM ~opcode_self_probability_122~
END

DEFINE_PATCH_MACRO ~opcode_122_common~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET amount2 = 0
	LOCAL_SET amount3 = 0
	LOCAL_SPRINT itemName2 ~~
	LOCAL_SPRINT itemName3 ~~

	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END

	PATCH_IF is_ee == 1 AND isExternal BEGIN
		SET amount2 = parameter3
		SET amount3 = parameter4
		PATCH_IF NOT ~%resref2%~ STRING_EQUAL ~~ BEGIN
			LPF ~get_item_name~ STR_VAR file = EVAL ~%resref2%~ RET itemName2 = itemName END
		END
		PATCH_IF NOT ~%resref3%~ STRING_EQUAL ~~ BEGIN
			LPF ~get_item_name~ STR_VAR file = EVAL ~%resref3%~ RET itemName3 = itemName END
		END
		PATCH_IF amount2 == 0 AND amount3 > 0 BEGIN
			SET amount2 = amount3
			SET amount3 = 0
			SPRINT itemName2 ~%itemName3%~
		END
	END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ AND amount > 0 AND NOT ~%itemName2%~ STRING_EQUAL ~~ AND amount2 > 0 AND NOT ~%itemName3%~ STRING_EQUAL ~~ AND amount3 > 0 BEGIN
		SET strref += 2
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Crée aléatoirement %amount% "%itemName%", %amount2% "%itemName2%" ou %amount3% "%itemName3%"~
	END
	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ AND amount > 0 AND NOT ~%itemName2%~ STRING_EQUAL ~~ AND amount2 > 0 BEGIN
		SET strref += 1
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Crée aléatoirement %amount% "%itemName%" ou %amount2% "%itemName2%"~
	END
	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ AND amount > 0 BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Crée %amount% "%itemName%" dans l'inventaire %ofTheTarget%~
	END
END

/* --------------------------------------------- *
 * Spell Effect: Teleport (Dimension Door) [124] *
 * --------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_124~ BEGIN
	LOCAL_SET strref = 11240001 + parameter2

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_124~ BEGIN
	LOCAL_SET strref = 11240011 + parameter2

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_target_124~ BEGIN
	LOCAL_SET strref = 11240001 + parameter2

	PATCH_IF parameter2 == 1 BEGIN
		SET strref = 11240005 // ~Téléporte %theTarget% vers le porteur~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SET strref = 11240006 // ~Échange la place %ofTheTarget% avec le porteur~
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_124~ BEGIN
	LOCAL_SET strref = 11240011 + parameter2

	PATCH_IF parameter2 == 1 BEGIN
		SET strref = 11240015 // ~de téléporter %theTarget% vers le porteur~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SET strref = 11240016 // ~d'échanger la place %ofTheTarget% avec le porteur~
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

/* ---------------------------------- *
 * Spell Effect: Unlock (Knock) [125] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_125~ BEGIN
	SPRINT description @11250001 // ~Déverrouille la serrure ciblée~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_125~ BEGIN
	SPRINT description @11250002 // ~de déverrouiller la serrure ciblée~
END

/* ----------------------------- *
 * Stat: Movement Modifier [126] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_126~ BEGIN
	PATCH_IF is_ee == 1 AND parameter2 == 5 BEGIN
		SET parameter2 = MOD_TYPE_percentage
	END
	PATCH_IF parameter1 == 0 AND (parameter2 == MOD_TYPE_flat OR parameter2 == MOD_TYPE_percentage) BEGIN
		SPRINT description @11260003 // ~Immobilise %theTarget%~
	END
	ELSE BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 11260001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Vitesse de déplacement~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_126~ BEGIN
	PATCH_IF is_ee == 1 AND parameter2 == 5 BEGIN
		SET parameter2 = MOD_TYPE_percentage
	END
	PATCH_IF parameter1 == 0 AND (parameter2 == MOD_TYPE_flat OR parameter2 == MOD_TYPE_percentage) BEGIN
		SPRINT description @11260004 // ~d'immobiliser %theTarget%~
	END
	ELSE BEGIN
		LPF ~opcode_probability~ INT_VAR strref = 11260002 RET description END // ~la vitesse de déplacement~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_126~ BEGIN
	PATCH_IF is_ee == 1 AND parameter2 == 5 BEGIN
		SET parameter2 = MOD_TYPE_percentage
	END
	PATCH_IF parameter1 == 0 AND (parameter2 == MOD_TYPE_flat OR parameter2 == MOD_TYPE_percentage) BEGIN
		SPRINT description @11260003 // ~Immobilise %theTarget%~
	END
	ELSE BEGIN
		LPF ~opcode_target~ INT_VAR strref = 11260002 RET description END // ~la vitesse de déplacement~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_126~ BEGIN
	LPM ~opcode_self_probability_126~
END

/* ------------------------------- *
 * Summon: Monster Summoning [127] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_127~ BEGIN
	LOCAL_SET strref = 11270001 // ~Invoque des monstres pour un total de %amount% niveaux (%creatures%)~
	LPM ~opcode_127_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_127~ BEGIN
	LOCAL_SET strref = 11270021
	LPM ~opcode_127_common~
END

DEFINE_PATCH_MACRO ~opcode_127_common~ BEGIN
	LOCAL_SET amount    = parameter1
	LOCAL_SET type      = parameter2
	LOCAL_SET mode      = special
	LOCAL_SET isMonster = 1
	LOCAL_SET isHostile = type >= 5 ? 1 : 0

	PATCH_IF ~%resref%~ STRING_EQUAL ~~ BEGIN
		SPRINT file $opcode_127_files(~%type%~)

		PATCH_IF type == 3 OR type == 4 OR type == 8 OR type == 9 BEGIN
			SET isMonster = 0
		END

		PATCH_IF mode == 2 BEGIN
			SET strref += 2 // ~Invoque des monstres pour un total de niveaux égal au niveau du lanceur (%creatures%)~
		END
		ELSE PATCH_IF mode == 1 BEGIN
			PATCH_IF isExternal BEGIN
				LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount = amount RET amount = damage END
				INNER_PATCH_SAVE amount ~%amount%~ BEGIN
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
				END
				SET strref += ~%amount%~ STRING_EQUAL ~1~ ? 4 : 6
			END
			ELSE BEGIN
				SET strref += amount == 1 ? 4 : 6
			END
		END

		SET strref += isMonster == 1 ? 0 : 1

		PATCH_IF isHostile == 1 BEGIN
			SET strref += 8
		END
	END
	ELSE BEGIN
		SPRINT file ~%resref%~

		PATCH_IF mode == 0 BEGIN
			SET strref += 16 // ~Invoque des créatures pour un total de %amount% niveaux (%creatures%)~
		END
		ELSE PATCH_IF mode == 2 BEGIN
			SET strref += 17 // ~Invoque des créatures pour un total de niveaux égal au niveau du lanceur (%creatures%)~
		END
		ELSE PATCH_IF mode == 1 BEGIN
			PATCH_IF isExternal BEGIN
				LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount = amount RET amount = damage END
				INNER_PATCH_SAVE amount ~%amount%~ BEGIN
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
				END
				SET strref += ~%amount%~ STRING_EQUAL ~1~ ? 18 : 19
			END
			ELSE BEGIN
				SET strref += amount == 1 ? 18 : 19
			END
		END
	END

	LPF ~get_creatures_names~ STR_VAR file RET creatures END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

/* ---------------------- *
 * State: Confusion [128] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_128~ BEGIN
    SPRINT description @11280001 // ~Confusion~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_128~ BEGIN
    SPRINT description @11280003 // ~d'infliger confusion %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_128~ BEGIN
    SPRINT description @11280002 // ~Inflige confusion %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_128~ BEGIN
    LPM ~opcode_self_probability_128~ // ~d'infliger Confusion à la cible~
END

/* ---------------- *
 * State: Aid [129] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_129~ BEGIN
	LPM ~opcode_129_common~
    SPRINT description @11290001 // ~Aide (%value%)~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_129~ BEGIN
	LPM ~opcode_129_common~
    SPRINT description @11290003 // ~de lancer Aide (%value%) sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_129~ BEGIN
	LPM ~opcode_129_common~
    SPRINT description @11290002 // ~Lance Aide (%value%) sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_129~ BEGIN
	LPM ~opcode_self_probability_129~ // ~de lancer Aide (%value%) sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_129_common~ BEGIN
	//Saving throws, THAC0, and Damage modifiers read only the first byte of Statistic Modifier for their value, the last 3 bytes are ignored.
	SET parameter1 = parameter1 BAND 255
	//FIXME: HP modifier uses the whole 4 bytes of Statistic Modifier.
	//TODO ?? : Si dans un fichier .eff, parameter2 = nombre exact de PV
	LPF ~signed_value~ INT_VAR value = EVAL ~%parameter1%~ RET value END
END

/* ------------------ *
 * State: Bless [130] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_130~ BEGIN
    SPRINT description @11300001 // ~Bénédiction permanente~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_130~ BEGIN
    SPRINT description @11300003 // ~de lancer Bénédiction sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_130~ BEGIN
    SPRINT description @11300002 // ~Lance Bénédiction sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_130~ BEGIN
	LPM ~opcode_self_probability_130~ // ~de lancer Bénédiction sur %theTarget%~
END

/* --------------------------- *
 * State: Positive Chant [131] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_131~ BEGIN
	//Statistic Modifier only reads the first byte for its value, the last 3 bytes are ignored.
	SET parameter1 = parameter1 BAND 255
	LPM ~opcode_self_22~  // ~Chance~
    LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_131~ BEGIN
	SET parameter1 = parameter1 BAND 255
	LPM ~opcode_self_probability_22~ // ~la chance~
    LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_131~ BEGIN
	SET parameter1 = parameter1 BAND 255
	LPM ~opcode_target_22~ // ~la chance~
    LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_131~ BEGIN
	SET parameter1 = parameter1 BAND 255
    LPM ~opcode_target_probability_22~ // ~la chance~
    LPM ~opcode_not_cumulative~
END

/* --------------------------------------------------------------------- *
 * State: Raise Strength, Constitution, & Dexterity Non-Cumulative [132] *
 * --------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_132~ BEGIN
	LPM ~opcode_132_common~
	LPF ~opcode_mod~ INT_VAR strref = 11320001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Force, dextérité et constitution~
	LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_132~ BEGIN
	LPM ~opcode_132_common~
	LPF ~opcode_target~ INT_VAR strref = 11320002 RET description END // ~la force, la dextérité et la constitution~
	LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_132~ BEGIN
	LPM ~opcode_132_common~
	LPF ~opcode_probability~ INT_VAR strref = 11320002 RET description END // ~la force, la dextérité et la constitution~
	LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_132~ BEGIN
	LPM ~opcode_self_probability_132~
END

DEFINE_PATCH_MACRO ~opcode_132_common~ BEGIN
	SET parameter1 = parameter1 BAND 255
	PATCH_IF parameter1 < 0 BEGIN
		SET parameter2 = MOD_TYPE_flat
		SET parameter1 = 25
	END
END

/* --------------------------------------- *
 * Spell Effect: Luck Non-Cumulative [133] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_133~ BEGIN
	LPM ~opcode_self_131~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_133~ BEGIN
	LPM ~opcode_self_probability_131~
END

DEFINE_PATCH_MACRO ~opcode_target_133~ BEGIN
	LPM ~opcode_target_131~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_133~ BEGIN
	LPM ~opcode_target_probability_131~
END

/* -------------------------- *
 * State: Petrification [134] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_134~ BEGIN
	SPRINT description @11340001 // ~Pétrifie %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_134~ BEGIN
	SPRINT description @11340002 // ~de pétrifier %theTarget%~
END

/* ----------------------------- *
 * Polymorph into Specific [135] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_135~ BEGIN
	//TODO: type == 0 => Gain Resistances/statistics (spell-casting disabled)
	//TODO: If the resource key is empty, other Polymorph effects are removed, allowing for removal of permanent effects.
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
	PATCH_IF NOT ~%creatureName%~ STRING_EQUAL ~~ BEGIN
        SPRINT description @11350001 // ~Transforme le porteur en %creatureName%~
	END
	ELSE BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% self : Nom de la créature introuvable : %resref%~ END
	END
END

/* -------------------------- *
 * State: Force Visible [136] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_136~ BEGIN
	SPRINT description @11360001 // ~Devient partiellement visible~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_136~ BEGIN
	SPRINT description @11360003 // ~de rendre %theTarget% partiellement visible~
END

DEFINE_PATCH_MACRO ~opcode_target_136~ BEGIN
	SPRINT description @11360002 // ~Rend %theTarget% partiellement visible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_136~ BEGIN
	LPM ~opcode_self_probability_136~ // ~de rendre %theTarget% partiellement visible~
END

/* --------------------------- *
 * State: Negative Chant [137] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_137~ BEGIN
	SET parameter1 = 0 - parameter1
    LPM ~opcode_self_131~ // ~Chance~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_137~ BEGIN
	SET parameter1 = 0 - parameter1
    LPM ~opcode_self_probability_131~ // ~Chance~
END

DEFINE_PATCH_MACRO ~opcode_target_137~ BEGIN
	SET parameter1 = 0 - parameter1
    LPM ~opcode_target_131~ // ~Chance~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_137~ BEGIN
	SET parameter1 = 0 - parameter1
    LPM ~opcode_target_probability_131~ // ~Chance~
END

/* ------------------------------- *
 * Item: Create Item in Slot [143] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_143~ BEGIN
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END
	LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~20~ RET slotName = idName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11430001 // ~Crée 1 "%itemName%" à l'emplacement %slotName% %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_143~ BEGIN
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END
	LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~20~ RET slotName = idName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11430002 // ~de créer 1 "%itemName%" à l'emplacement (%slotName%) %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_143~ BEGIN
	LPM ~opcode_self_143~ // ~Crée 1 "%itemName%" à l'emplacement %slotName% %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_143~ BEGIN
	LPM ~opcode_self_probability_143~ // ~de créer 1 "%itemName%" à l'emplacement (%slotName%) %ofTheTarget%~
END

/* ---------------------------- *
 * Button: Disable Button [144] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_144~ BEGIN
	LOCAL_SET strref = 11440001 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Empêche l'utilisation de xxx~
END

DEFINE_PATCH_MACRO ~opcode_target_144~ BEGIN
	LOCAL_SET strref = 11440021 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Empêche %theTarget% d'utiliser xxx~
END

/* -------------------------------------------- *
 * Spell: Disable Spell Casting Abilities [145] *
 * -------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_145~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN SPRINT description @11450001 END // ~Empêche %theTarget% de lancer des sorts profanes~
	PATCH_IF parameter2 == 1 BEGIN SPRINT description @11450002 END // ~Empêche %theTarget% de lancer des sorts divins~
	PATCH_IF parameter2 == 2 BEGIN SPRINT description @11450003 END // ~Empêche %theTarget% de lancer des sorts innés~
	PATCH_IF parameter2 == 3 BEGIN SPRINT description @11450004 END // ~Empêche %theTarget% de lancer des sorts magiques~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_145~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN SPRINT description @11450005 END // ~d'empêcher %theTarget% de lancer des sorts profanes~
	PATCH_IF parameter2 == 1 BEGIN SPRINT description @11450006 END // ~d'empêcher %theTarget% de lancer des sorts divins~
	PATCH_IF parameter2 == 2 BEGIN SPRINT description @11450007 END // ~d'empêcher %theTarget% de lancer des sorts innés~
	PATCH_IF parameter2 == 3 BEGIN SPRINT description @11450008 END // ~d'empêcher %theTarget% de lancer des sorts magiques~
END

DEFINE_PATCH_MACRO ~opcode_target_145~ BEGIN
	LPM ~opcode_self_145~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_145~ BEGIN
	LPM ~opcode_self_probability_145~
END

/* ------------------------------------- *
 * Spell: Cast Spell (at Creature) [146] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_146~ BEGIN
	LPM ~opcode_target_146~
END

DEFINE_PATCH_MACRO ~opcode_target_146~ BEGIN
	LOCAL_SET castingLevel = parameter1
	LOCAL_SET type = parameter2
	TO_UPPER resref
	PATCH_IF VARIABLE_IS_SET $opcode_target_146_item_revision(~%resref%~) BEGIN
		SET strref = $opcode_target_146_item_revision(~%resref%~)
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
	ELSE BEGIN
		LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

		PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF abilityType == AbilityType_Charge BEGIN
				PATCH_IF type > 0 BEGIN
					SPRINT description @11460005 // ~%spellName% (instantané)~
				END
				ELSE BEGIN
					SPRINT description ~%spellName%~
				END
			END
			ELSE BEGIN
				PATCH_IF type > 0 BEGIN
					SPRINT description @11460002 // ~Lance instantanément %spellName% sur %theTarget%~
				END
				ELSE BEGIN
					SPRINT description @11460001 // ~Lance %spellName% sur %theTarget%~
				END
			END

			PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 BEGIN
				SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
				SPRINT description ~%description% (%castingLevelStr%)~
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_146~ BEGIN
	LPM ~opcode_target_probability_146~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_146~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~
	LOCAL_SET type = parameter2
	TO_UPPER resref
	PATCH_IF VARIABLE_IS_SET $opcode_target_probability_146_item_revision(~%resref%~) BEGIN
		SET strref = $opcode_target_probability_146_item_revision(~%resref%~)
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
	ELSE BEGIN
		LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

		PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN

			PATCH_IF type > 0 BEGIN
				SPRINT description @11460004 // ~de lancer instantanément le sort %spellName% sur %theTarget%~
			END
			ELSE BEGIN
				SPRINT description @11460003 // ~de lancer le sort %spellName% sur %theTarget%~
			END

			PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 BEGIN
				SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
				SPRINT description ~%description% (%castingLevelStr%)~
			END
		END
	END
END

/* ------------------------ *
 * Spell: Learn Spell [147] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_147~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	SPRINT description @11470001 // ~Fait apprendre le sort %spellName% %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_147~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	SPRINT description @11470002 // ~de faire apprendre le sort %spellName% %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_147~ BEGIN
	LPM ~opcode_self_147~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_147~ BEGIN
	LPM ~opcode_self_probability_147~
END

/* ---------------------------------- *
 * Spell: Cast Spell (at Point) [148] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_148~ BEGIN
	LOCAL_SET castingLevel = parameter1
	LOCAL_SET type = parameter2

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF type == 1 BEGIN
			SPRINT description @11460005 // ~%spellName% (instantané)~
		END
		ELSE BEGIN
			SPRINT description ~%spellName%~
		END

		PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 AND type == 0 BEGIN
			SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
			SPRINT description ~%description% (%castingLevelStr%)~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_148~ BEGIN
	LOCAL_SET castingLevel = parameter1
	LOCAL_SET type = parameter2

	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF type == 1 BEGIN
			SPRINT description @11480003 // ~de lancer instantanément le sort %spellName% sur %theTarget%~
		END
		ELSE BEGIN
			SPRINT description @11480003 // ~de lancer le sort %spellName% sur %theTarget%~
		END

		PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND castingLevel > 0 AND type == 0 BEGIN
			SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
			SPRINT description ~%description% (%castingLevelStr%)~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_148~ BEGIN
	LPM ~opcode_self_148~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_148~ BEGIN
	LPM ~opcode_self_probability_148~
END

/* ------------------------------ *
 * Spell Effect: Find Traps [150] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_150~ BEGIN
	SPRINT description @11500001 // ~Détecte les pièges~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_150~ BEGIN
	SPRINT description @11500002 // ~de détecter les pièges~
END

/* ------------------------------ *
 * Summon: Replace Creature [151] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_151~ BEGIN
	LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Version self à gérer.~ END
END

DEFINE_PATCH_MACRO ~opcode_target_151~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @11510001 // ~Remplace la cible par %creatureName%~
	END
	ELSE PATCH_IF parameter2 == 1 OR parameter2 == 2 BEGIN
		SPRINT description @11510002 // ~Tue et remplace %theTarget% par %creatureName%~
	END
	ELSE PATCH_IF parameter2 ==3 BEGIN
		SPRINT description @11510003 // ~Invoque %creatureName% sur %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_151~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @11510004 // ~de remplacer %theTarget% par %creatureName%~
	END
	ELSE PATCH_IF parameter2 == 1 OR parameter2 == 2 BEGIN
		SPRINT description @11510005 // ~de tuer et remplacer %theTarget% par %creatureName%~
	END
	ELSE PATCH_IF parameter2 ==3 BEGIN
		SPRINT description @11510006 // ~d'invoquer %creatureName% sur %theTarget%~
	END
END

/* ----------------------- *
 * Overlay: Sanctuary [153] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_153~ BEGIN
	SPRINT description @11530001 // ~Sanctuaire~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_153~ BEGIN
	SPRINT description @11530002 // ~de lancer Sanctuaire sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_153~ BEGIN
	SPRINT description @11530003 // ~Lance Sanctuaire sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_153~ BEGIN
	LPM ~opcode_self_probability_153~ // ~de lancer Sanctuaire sur %theTarget%~
END

/* ----------------------- *
 * State: Web Effect [157] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_157~ BEGIN
	SPRINT description @11570001 // ~Entoile %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_157~ BEGIN
	SPRINT description @11570002 // ~d'entoiler %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_157~ BEGIN
	SPRINT description @11570001 // ~Entoile %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_157~ BEGIN
	LPM ~opcode_self_probability_157~ // ~d'entoiler %theTarget%~
END

/* ----------------------------------------------- *
 * Spell Effect: Mirror Image (Exact Number) [159] *
 * ----------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_159~ BEGIN
	LOCAL_SET amount = parameter1
	PATCH_IF amount == 1 BEGIN
		SPRINT description @11590001 // ~Crée 1 image miroir sur %theTarget%~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @11590002 // ~Crée %amount% images miroir sur %theTarget%~
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~opcode %opcode%: parameter1 should be > 0 : %parameter1%~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_159~ BEGIN
	LOCAL_SET amount = parameter1
	PATCH_IF amount == 1 BEGIN
		SPRINT description @11590003 // ~de créer 1 image miroir sur %theTarget%~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @11590004 // ~de créer %amount% images miroir sur %theTarget%~
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~opcode %opcode%: parameter1 should be > 0 : %parameter1%~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_159~ BEGIN
	LPM ~opcode_self_159~ // ~Crée %amount% images miroir sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_159~ BEGIN
	LPM ~opcode_self_probability_159~ // ~de créer %amount% images miroir sur %theTarget%~
END

/* ------------------ *
 * Cure: Horror [161] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_161~ BEGIN
	SPRINT description @11610001 // ~Immunité à l'horreur~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_161~ BEGIN
	SPRINT description @11610003 // ~de dissiper l'horreur %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_161~ BEGIN
	SPRINT description @11610002 // ~Dissipe l'horreur %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_161~ BEGIN
	LPM ~opcode_self_probability_161~ // ~de dissiper l'horreur %ofTheTarget%~
END

/* ---------------------- *
 * Remove Sanctuary [160] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_160~ BEGIN
	SPRINT description @11600001 // ~Dissipe le sanctuaire sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_160~ BEGIN
	SPRINT description @11600002 // ~de dissiper le sanctuaire sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_160~ BEGIN
	LPM ~opcode_self_160~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_160~ BEGIN
	LPM ~opcode_self_probability_160~
END

/* ---------------- *
 * Cure: Hold [162] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_162~ BEGIN
	SPRINT description @11620001 // ~Immunité à la paralysie~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_162~ BEGIN
	SPRINT description @11620003 // ~de guérir la paralysie %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_162~ BEGIN
	SPRINT description @11620002 // ~Guérison de la paralysie %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_162~ BEGIN
	LPM ~opcode_self_probability_162~ // ~de guérir la paralysie %ofTheTarget%~
END

/* ----------------------------- *
 * Protection: Free Action [163] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_163~ BEGIN
	SPRINT description @11630001 // ~Action libre~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_163~ BEGIN
	SPRINT description @11630003 // ~de lancer Action libre sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_163~ BEGIN
	SPRINT description @11630002 // ~Lance Action libre sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_163~ BEGIN
	LPM ~opcode_self_probability_163~ // ~de lancer Action libre sur %theTarget%~
END

/* ---------------------- *
 * Cure: Drunkeness [164] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_164~ BEGIN
	SPRINT description @11640001 // ~Immunité à l'ivresse~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_164~ BEGIN
	SPRINT description @11640003 // ~de dessoûler %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_164~ BEGIN
	SPRINT description @11640002 // ~Dessoûle %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_164~ BEGIN
	LPM ~opcode_self_probability_164~ // ~de dessoûler %theTarget%~
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
	LPF ~opcode_mod_percent~ INT_VAR strref = 11660001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance à la magie~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_166~ BEGIN
	LOCAL_SPRINT resistName @11660001 // ~Résistance à la magie~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_166~ BEGIN
	LOCAL_SPRINT resistName @11660001 // ~Résistance à la magie~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_166~ BEGIN
	LPM ~opcode_self_probability_166~
END

/* ----------------------------------------------- *
 * Stat: THAC0 Modifier with Missile Weapons [167] *
 * ----------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_167~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 11670001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 des armes à projectiles~
END

DEFINE_PATCH_MACRO ~opcode_target_167~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 11670002 RET description END // ~le TAC0 des armes à projectiles~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_167~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 11670002 RET description END // ~le TAC0 des armes à projectiles~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_167~ BEGIN
	LPM ~opcode_self_probability_167~
END

/* -------------------------------- *
 * Spell: Give Innate Ability [171] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_171~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET description = spellName END
END

/* ------------------------- *
 * Spell: Remove Spell [172] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_172~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		//TODO: If the key is not 8 characters long, all memorized copies will be removed.
		//TODO: @11720002 = ~Supprime le sort %spellName% de la mémoire et du livre de sorts %ofTheTarget%~
		SPRINT description @11720001 // ~Supprime le sort %spellName% du livre de sorts %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_172~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		//TODO: If the key is not 8 characters long, all memorized copies will be removed.
		//TODO: @11720004 = ~de supprimer le sort %spellName% de la mémoire et du livre de sorts %ofTheTarget%~
		SPRINT description @11720003 // ~de supprimer le sort %spellName% du livre de sorts %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_172~ BEGIN
	LPM ~opcode_self_172~ // ~Supprime le sort %spellName% du livre de sorts %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_172~ BEGIN
	LPM ~opcode_self_probability_172~ // ~de supprimer le sort %spellName% de la mémoire et du livre de sorts %ofTheTarget%~
END

/* -------------------------------------- *
 * Stat: Poison Resistance Modifier [173] *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_173~ BEGIN
	LPM ~opcode_173_common~
	LPF ~opcode_mod_percent~ INT_VAR strref = 11730001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Résistance aux poisons~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_173~ BEGIN
	LOCAL_SPRINT resistName @11730001 // ~Résistance aux poisons~
	LPM ~opcode_173_common~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_173~ BEGIN
	LOCAL_SPRINT resistName @11730001 // ~Résistance aux poisons~
	LPM ~opcode_173_common~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_173~ BEGIN
	LPM ~opcode_self_probability_173~
END

DEFINE_PATCH_MACRO ~opcode_173_common~ BEGIN
	PATCH_IF is_ee == 0 BEGIN
		// Sets the Poison Resistance of the target creature(s) to the value specified by 'Statistic Modifier'.
		SET parameter2 = MOD_TYPE_flat
	END
	ELSE BEGIN
		SET parameter2 = MOD_TYPE_cumulative
	END
END

/* ----------------- *
 * State: Hold [175] *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_175~ BEGIN
	LPM ~opcode_self_109~
END

DEFINE_PATCH_MACRO ~opcode_target_175~ BEGIN
	LPM ~opcode_target_109~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_175~ BEGIN
	LPM ~opcode_target_probability_109~
END

/* ---------------------------------- *
 * Stat: Movement Modifier (II) [176] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_176~ BEGIN
	LPM ~opcode_self_126~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_176~ BEGIN
	LPM ~opcode_self_probability_126~
END

DEFINE_PATCH_MACRO ~opcode_target_176~ BEGIN
	LPM ~opcode_target_126~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_176~ BEGIN
	LPM ~opcode_self_probability_176~
END

/* ------------------ *
 * Use EFF File [177] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_177~ BEGIN
	PATCH_IF ~%resref%~ STRING_MATCHES_REGEXP ~^AG#IRS~ == 0 BEGIN // Effet d'Item Revision v4
		LPF ~opcode_self_177_item_revision_casting_penality~ RET description forceSort sort END
	END
	ELSE PATCH_IF parameter1 == 0 AND parameter2 == 2 BEGIN
		LPF ~get_res_description_177~ STR_VAR resref macro = ~opcode_self_~ RET description saveAdded ignoreDuration opcode END
	END
	ELSE BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET targetType = idName END
		LPF ~get_res_description_177~ STR_VAR resref macro = ~opcode_self_~ RET description saveAdded ignoreDuration opcode END
		PATCH_IF NOT ~%targetType%~ STRING_EQUAL ~~ AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
			SPRINT selfTarget @11770001 // ~ uniquement pour les %targetType%~
			SPRINT description ~%description% (%selfTarget%)~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_177~ BEGIN
	LPM ~opcode_target_177~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_177~ BEGIN
	LPM ~opcode_target_177~
END

DEFINE_PATCH_MACRO ~opcode_target_177~ BEGIN
	PATCH_IF NOT (parameter1 == 0 AND parameter2 == 2) BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET targetType = idName END
		SPRINT theTarget   @102384 // ~les %targetType%~
		SPRINT ofTheTarget @102385 // ~des %targetType%~
		SPRINT toTheTarget @102386 // ~aux %targetType%~
		SPRINT versus      @102387 // ~contre les %targetType%~
		LPM ~add_target_level~
	END
	LPF ~get_res_description_177~ STR_VAR resref macro = ~opcode_target_~ RET description saveAdded ignoreDuration opcode END
END

DEFINE_PATCH_FUNCTION ~get_res_description_177~ INT_VAR resetTarget = 0 STR_VAR resref = ~~ macro = ~~ RET description saveAdded ignoreDuration opcode BEGIN
	PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.eff~ BEGIN
		INNER_PATCH_FILE ~%resref%.eff~ BEGIN
			READ_SHORT EFF2_opcode opcode

	        SPRINT oldTheTarget   ~%theTarget%~
	        SPRINT oldOfTheTarget ~%ofTheTarget%~
	        SPRINT oldToTheTarget ~%toTheTarget%~

			LPF ~get_description_effect2~ INT_VAR resetTarget RET description saveAdded ignoreDuration END

	        SPRINT theTarget   ~%oldTheTarget%~
	        SPRINT ofTheTarget ~%oldOfTheTarget%~
	        SPRINT toTheTarget ~%oldToTheTarget%~
	    END
	END
	ELSE BEGIN
		PATCH_IF ~%resref%~ STRING_EQUAL ~~ BEGIN
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: The resref parameter is empty~ END
		END
		ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : La ressource %resref%.eff n'existe pas.~ END
		END
	END
END

/* ---------------------------------------------------- *
 * Spell Effect: THAC0 vs. Creature Type Modifier [178] *
 * ---------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_178~ BEGIN
	LPM ~opcode_178_common~
	LPF ~opcode_mod~ INT_VAR strref = 10540001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0~
	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11780001 // ~%description% %versus%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_178~ BEGIN
	LPM ~opcode_178_common~
	LPF ~opcode_target~ INT_VAR strref = 10540002 RET description END // ~le TAC0~
	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11780001 // ~%description% %versus%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_178~ BEGIN
	LPM ~opcode_178_common~
	LPF ~opcode_probability~ INT_VAR strref = 10540002 RET description END // ~le TAC0~
	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11780001 // ~%description% %versus%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_178~ BEGIN
	LPM ~opcode_self_probability_178~
END

DEFINE_PATCH_MACRO ~opcode_178_common~ BEGIN
	LOCAL_SET strref = 10540001 // TAC0
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END

	PATCH_IF isExternal BEGIN
		SET value = ~%parameter3%~
	END
	ELSE BEGIN
		//TODO: Vérifier si la valeur ne devrait pas se trouver dans la variable "special" au lieu de "power"
		SET value = ~%power%~
	END

	SET parameter2 = MOD_TYPE_cumulative
	SET parameter1 = value
END

/* ----------------------------------------------------- *
 * Spell Effect: Damage vs. Creature Type Modifier [179] *
 * ----------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_179~ BEGIN
	LOCAL_SET strref = 10120003 // ~Inflige %damage% %damageType% supplémentaires %versus%~
	LPM ~opcode_179_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_179~ BEGIN
	LOCAL_SET strref = 10120013 // ~d'infliger %damage% %damageType% supplémentaires %versus%~
	LPM ~opcode_179_common~
END

DEFINE_PATCH_MACRO ~opcode_target_179~ BEGIN
	LPM ~opcode_self_179~ // ~Inflige %damage% %damageType% supplémentaires %versus%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_179~ BEGIN
	LPM ~opcode_self_probability_179~ // ~d'infliger %damage% %damageType% supplémentaires %versus%~
END

DEFINE_PATCH_MACRO ~opcode_179_common~ BEGIN
	//TODO: Multiple opcode #179 effects only allow additional targeting, they do not stack their damage bonus.
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END

	PATCH_IF isExternal BEGIN
		SET damageAmount = ~%parameter3%~
	END
	ELSE BEGIN
		//TODO: Vérifier si la valeur ne devrait pas se trouver dans la variable "special" au lieu de "power"
		SET damageAmount = ~%power%~
	END

	SET parameter2 = MOD_TYPE_cumulative
	LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET damage END

	INNER_PATCH_SAVE damage ~%damage%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
	END

	SPRINT damageType @101092 // ~points de dégâts~
	SPRINT description @10120003 // ~Inflige %damage% %damageType% supplémentaires %versus%~
END

/* -------------------------- *
 * Item: Can't Use Item [180] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_180~ BEGIN
	PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%SOURCE_RES%~ BEGIN
		SET forceSort = 1
		SET sort = 0
		SPRINT description @11800001 // ~Unique : Un seul exemple peut être équipé~
	END
	ELSE BEGIN
		LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END
		PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
			SPRINT description @11800002 // ~Empêche d'utiliser %itemName%~
		END
	END
END

/* ------------------------------ *
 * Item: Can't Use Itemtype [181] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_181~ BEGIN
	LOCAL_SET strref = 11810100

	PATCH_IF is_ee == 1 BEGIN
		SET strref = strref + parameter1
	END
	ELSE BEGIN
		SET strref = strref + parameter2
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET itemType = string END
	SPRINT description @11810001 // ~Empêche d'utiliser les %itemType%~
END

/* ---------------------- *
 * State: Hold (II) [185] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_185~ BEGIN
	LPM ~opcode_self_175~
END

DEFINE_PATCH_MACRO ~opcode_target_185~ BEGIN
	LPM ~opcode_target_175~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_185~ BEGIN
	LPM ~opcode_target_probability_175~
END

/* ---------------------------------- *
 * Spell Effect: Aura Cleansing [188] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_188~ BEGIN
	SPRINT description @11880001 // ~Permet de lancer plusieurs sorts par round~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_188~ BEGIN
	SPRINT description @11880003 // ~de permettre %toTheTarget% de lancer plusieurs sorts par round~
END

DEFINE_PATCH_MACRO ~opcode_target_188~ BEGIN
	SPRINT description @11880002 // ~Permet %toTheTarget% de lancer plusieurs sorts par round~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_188~ BEGIN
	LPM  ~opcode_self_probability_188~ // ~de permettre %toTheTarget% de lancer plusieurs sorts par round~
END

/* --------------------------------- *
 * Stat: Casting Time Modifier [189] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_189~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 11890001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Vitesse d'incantation~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_189~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 11890002 RET description END // ~la vitesse d'incantation~
END

DEFINE_PATCH_MACRO ~opcode_target_189~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 11890002 RET description END // ~la vitesse d'incantation~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_189~ BEGIN
	LPM ~opcode_self_probability_189~
END

/* ------------------------------- *
 * Stat: Attack Speed Factor [190] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_190~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 11900001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Facteur de vitesse~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_190~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 11900002 RET description END // ~le facteur de vitesse~
END

DEFINE_PATCH_MACRO ~opcode_target_190~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 11900002 RET description END // ~le facteur de vitesse~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_190~ BEGIN
	LPM ~opcode_self_probability_190~
END

/* ----------------------------------- *
 * Spell: Casting Level Modifier [191] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_191~ BEGIN
	LOCAL_SET strref = 11910001 // ~Niveau de lanceur de sorts profanes~

	LPM ~opcode_191_common~
	LPF ~opcode_mod~ INT_VAR strref STR_VAR value = EVAL ~%parameter1%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_191~ BEGIN
	LOCAL_SET strref = 11910001 // ~Niveau de lanceur de sorts profanes~

	LPM ~opcode_191_common~
	LPF ~opcode_probability~ INT_VAR strref RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_191~ BEGIN
	LOCAL_SET strref = 11910003 // ~le niveau de lanceur de sorts profanes~

	LPM ~opcode_191_common~
	LPF ~opcode_target~ INT_VAR strref STR_VAR value = EVAL ~%parameter1%~ RET description END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_191~ BEGIN
	LPM ~opcode_self_probability_191~
END

DEFINE_PATCH_MACRO ~opcode_191_common~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SET strref += 1 // ~le niveau de lanceur de sorts divins~
	END
	SET parameter2 = MOD_TYPE_cumulative
END

/* ------------------------------------------------- *
 * Spell Effect: Invisible Detection by Script [193] *
 * ------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_193~ BEGIN
	SPRINT description @11930001 // ~Permet %toTheTarget% d'attaquer une créature cachée ou invisible~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_193~ BEGIN
	SPRINT description @11930002 // ~de permettre %toTheTarget% d'attaquer une créature cachée ou invisible~
END

DEFINE_PATCH_MACRO ~opcode_target_193~ BEGIN
	LPM ~opcode_self_193~ // ~Permet %toTheTarget% d'attaquer une créature cachée ou invisible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_193~ BEGIN
	LPM ~opcode_self_probability_193~ // ~de permettre %toTheTarget% d'attaquer une créature cachée ou invisible~
END

/* ------------------------------ *
 * Spell: Bounce Projectile [197] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_197~ BEGIN
	LOCAL_SET strref = 11970001 // ~Renvoie les %projectiles%~
	LPM ~opcode_197_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_197~ BEGIN
	LOCAL_SET strref = 11970002 // ~de renvoyer les %projectiles%~
	LPM ~opcode_197_common~
END

DEFINE_PATCH_MACRO ~opcode_197_common~ BEGIN
	LOCAL_SET projref = 0
	PATCH_MATCH parameter2 WITH
		1 2 3 4 5 101 102 187 283 284 285 286 287 288 289 290 291
			BEGIN SET projref = 11971001 END // ~flèches~
		6 7 8 9 10 292 293 294 295 296
			BEGIN SET projref = 11971006 END // ~haches~
		11 12 13 14 15 225 240 297 298 299 300 301 302 303
			BEGIN SET projref = 11971011 END // ~carreaux~
		16 17 18 19 20 263 304 305 306 307 308
			BEGIN SET projref = 11971016 END // ~billes~
		23
			BEGIN SET projref = 11971023 END // ~orbes chromatiques~
		26 27 28 29 30 309 310 311 312
			BEGIN SET projref = 11971026 END // ~dagues~
		31 32 33 34 35 244 313 314 315 316 317 318
			BEGIN SET projref = 11971031 END // ~fléchettes~
		36 67 68 69 70 71 72 73 74 75 76 77
			BEGIN SET projref = 11971036 END // ~projectiles magiques~
		39 80 81 82 83 84 85 86 87 88 89 90 91 206 212 442
			BEGIN SET projref = 11971039 END // ~éclairs~
		55 56 57 58 59
			BEGIN SET projref = 11971055 END // ~lances~
		64
			BEGIN SET projref = 11971064 END // ~attaques de regard~
		208
			BEGIN SET projref = 11971208 END // ~rayons des spectateurs~
		DEFAULT
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Réflection du type de projectile '%parameter2%'~ END
    END

	PATCH_IF projref > 0 BEGIN
		LPF ~getTranslation~ INT_VAR strref = projref opcode RET projectiles = string END
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
END

/* ------------------------------------- *
 *  Spell: Bounce (by Power Level) [199] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_199~ BEGIN
	LOCAL_SET spellLevel = parameter1
	SPRINT description @11990001 // ~Renvoie les sorts de niveau %spellLevel%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_199~ BEGIN
	LOCAL_SET spellLevel = parameter1
	SPRINT description @11990002 // ~de renvoyer les sorts de niveau %spellLevel%~
END

/* -------------------------------------------------- *
 * Spell: Bounce (by Power level, decrementing) [200] *
 * -------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_200~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	SPRINT description @12000001 // ~Renvoie jusque %amount% sorts de niveau %spellLevel%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_200~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2

	SPRINT description @12000002 // ~de renvoyer jusque %amount% sorts de niveau %spellLevel%~
END

/* ---------------------------------------------------- *
 * Spell: Immunity (by Power Level, decrementing) [201] *
 * ---------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_201~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12010001 // ~Absorbe 1 sort de niveau %spellLevel%~
	END
	ELSE BEGIN
		SPRINT description @12010002 // ~Absorbe %amount% sorts de niveau %spellLevel%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_201~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12010003 // ~d'absorber 1 sort de niveau %spellLevel%~
	END
	ELSE BEGIN
		SPRINT description @12010004 // ~d'absorber %amount% sorts de niveau %spellLevel%~
	END
END

/* ------------------------------- *
 * Spell: Bounce (by School) [202] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_202~ BEGIN
	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END

	PATCH_IF NOT ~%spellSchoolName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12020001 // ~Renvoie les sorts de l'école %spellSchoolName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_202~ BEGIN
	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END

	PATCH_IF NOT ~%spellSchoolName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12020002 // ~de renvoyer les sorts de l'école %spellSchoolName%~
	END
END

/* --------------------------------------- *
 * Spell: Bounce (by Secondary Type) [203] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_203~ BEGIN
	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

	SPRINT description @12030001 // ~Renvoie les sorts %spellSecondaryTypeName%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_203~ BEGIN
	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

	SPRINT description @12030002 // ~de renvoyer les sorts %spellSecondaryTypeName%~
END

/* ------------------------------------------- *
 * Spell: Protection from Spell (School) [204] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_204~ BEGIN
	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END

	SPRINT description @12040001 // ~Immunité aux sorts de l'école %spellSchoolName%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_204~ BEGIN
	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END

	SPRINT description @12040002 // ~de résister aux sorts de l'école %spellSchoolName%~
END

/* --------------------------------------------------- *
 * Spell: Protection from Spell (Secondary Type) [205] *
 * --------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_205~ BEGIN
	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

	SPRINT description @12050001 // ~Immunité aux sorts %spellSecondaryTypeName%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_205~ BEGIN
	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

	SPRINT description @12050002 // ~de résister aux sorts %spellSecondaryTypeName%~
END

/* ---------------------------------- *
 * Spell: Protection from Spell [206] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_206~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12060001 // ~Immunité au sort %spellName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_206~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12060003 // ~de résister au sort %spellName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_206~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12060002 // ~Immunise %theTarget% au sort %spellName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_206~ BEGIN
	LPM ~opcode_self_probability_206~ // ~de résister au sort %spellName%~
END

DEFINE_PATCH_MACRO ~opcode_party_206~ BEGIN
	LPM ~opcode_target_206~
END

/* ----------------------------------- *
 * Spell: Bounce Specified Spell [207] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_207~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12070001 // ~Renvoie le sort %spellName%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_207~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12070002 // ~de renvoyer le sort %spellName%~
END

/* ----------------------- *
 * HP: Minimum Limit [208] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_208~ BEGIN
	SPRINT value ~%parameter1%~
	SPRINT description @12080001 // ~Les points de vie ne peuvent passer en dessous de %value%~
END

/* ---------------------- *
 * Death: Kill 60HP [209] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_209~ BEGIN
	LPM ~opcode_target_209~
END

DEFINE_PATCH_MACRO ~opcode_target_209~ BEGIN
	SPRINT description @12090001 // ~Tue instantanément %theTarget% si ses points de vie sont inférieurs à 60~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_209~ BEGIN
	SPRINT description @12090002 // ~de tuer instantanément %theTarget% si ses points de vie sont inférieurs à 60~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_209~ BEGIN
	LPM ~opcode_self_probability_209~
END

/* ----------------------------- *
 * Spell Effect: Stun 90HP [210] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_210~ BEGIN
	//TODO: Ajouter la durée ?
	// 1 to 29 HP ⟶ stunned for 4d4 rounds
    // 30 to 59 HP ⟶ stunned for 2d4 rounds
    // 60 to 89 HP ⟶ stunned for 1d4 rounds
	SPRINT description @12100001 // ~Étourdit %theTarget% lorsque ses points de vie sont inférieurs à 90, la durée varie selon les points de vie restant~
END

DEFINE_PATCH_MACRO ~opcode_target_210~ BEGIN
	LPM ~opcode_self_210~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_210~ BEGIN
	SPRINT description @12100002 // ~d'étourdir %theTarget% lorsque ses points de vie sont inférieurs à 90, la durée varie selon les points de vie restant~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_210~ BEGIN
	LPM ~opcode_self_probability_210~
END

/* -------------------------------- *
 * Spell Effect: Imprisonment [211] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_211~ BEGIN
	SPRINT description @12110001 // ~Emprisonne %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_211~ BEGIN
	LPM ~opcode_self_211~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_211~ BEGIN
	SPRINT description @12110002 // ~d'emprisonner %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_211~ BEGIN
	LPM ~opcode_self_probability_211~
END

/* ------------------------ *
 * Protection: Freedom [212] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_probability_212~ BEGIN
	SPRINT description @12120002 // ~de libérer %theTarget% des effets de l'emprisonnement et du labyrinthe~
END

DEFINE_PATCH_MACRO ~opcode_target_212~ BEGIN
	SPRINT description @12120001 // ~Libère %theTarget% des effets de l'emprisonnement et du labyrinthe~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_212~ BEGIN
	LPM ~opcode_self_probability_212~ // ~de libérer %theTarget% des effets de l'emprisonnement et du labyrinthe~
END

/* ------------------------ *
 * Spell Effect: Maze [213] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_probability_213~ BEGIN
	SPRINT description @12130002 // ~d'enfermer %theTarget% dans un labyrinthe~
END

DEFINE_PATCH_MACRO ~opcode_target_213~ BEGIN
	SPRINT description @12130001 // ~Enferme %theTarget% dans un labyrinthe~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_213~ BEGIN
	LPM ~opcode_self_probability_213~ // ~d'enfermer %theTarget% dans un labyrinthe~
END

/* -------------------------------- *
 * Spell Effect: Select Spell [214] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_214~ BEGIN
	LOCAL_SET type = parameter2

	PATCH_IF type == 0 BEGIN
		LPF ~opcode_214_get_spells~ STR_VAR file = EVAL ~%resref%~ RET spells END
		PATCH_IF NOT ~%spells%~ STRING_EQUAL ~~ BEGIN
            SPRINT description @12140002 // ~Permet de lancer l'un des sorts de cette liste%colon%%spells%~
		END
	END
	ELSE BEGIN
		//TODO: IF ee ajouter sauf SPWI110 et SPWI124 ?
        SPRINT description @12140001 // ~Permet de lancer un sort du livre de sorts~
	END
END

DEFINE_PATCH_FUNCTION ~opcode_214_get_spells~
	STR_VAR
		file = ~~
	RET
		spells
BEGIN
	SPRINT spells ~~

	INNER_PATCH_FILE ~%file%.2da~ BEGIN
		COUNT_2DA_ROWS ~3~ ~rows~
		FOR (row = 1 ; row < rows ; row = row + 1) BEGIN
			READ_2DA_ENTRY row 1 3 resref
			PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
				LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
				PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
					SPRINT spells ~%spells%%crlf%%spellName%~
				END
			END
		END
	END

	INNER_PATCH_SAVE spells ~%spells%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE ~%crlf%~ ~%crlf%  * ~ // Indentation de la liste des sorts
	END
END

/* ------------------------------- *
 * Spell Effect: Level Drain [216] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_216~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount == 1 BEGIN
		SPRINT description @12160001 // ~Draîne 1 niveau %toTheTarget%~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @12160002 // ~Draîne %amount% niveaux %toTheTarget%~
	END
	ELSE PATCH_IF amount < 0 BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Niveau draine negatif !!~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_216~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount == 1 BEGIN
		SPRINT description @12160003 // ~de drainer 1 niveau %toTheTarget%~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @12160004 // ~de drainer %amount% niveaux %toTheTarget%~
	END
	ELSE PATCH_IF amount < 0 BEGIN
		PATCH_FAIL ~%SOURCE_FILE% : Opcode %opcode% : Niveau draine negatif !!~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_216~ BEGIN
	LPM ~opcode_self_216~ // ~Draîne 1 niveau %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_216~ BEGIN
	LPM ~opcode_self_probability_216~ // ~de drainer 1 niveau %toTheTarget%~
END

/* ---------------------------------------- *
 * Spell Effect: Unconsciousness 20HP [217] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_217~ BEGIN
	// Durée forcée à 5 rounds
	SET duration = 30
	SET timingMode = TIMING_duration
	SPRINT description @12170001 // ~Endort %theTarget% si ses points de vie sont inférieurs à 20~
END

DEFINE_PATCH_MACRO ~opcode_target_217~ BEGIN
	LPM ~opcode_self_217~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_217~ BEGIN
	// Durée forcée à 5 rounds
	SET duration = 30 // 5 rounds
	SET timingMode = TIMING_duration
	SPRINT description @12170002 // ~d'endormir %theTarget% si ses points de vie sont inférieurs à 20~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_217~ BEGIN
	LPM ~opcode_self_probability_217~
END

/* --------------------------- *
 * Protection: Stoneskin [218] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_218~ BEGIN
	LOCAL_SET strref = 12180001 // ~Peau de pierre (1 peau)~

	LPM ~opcode_218_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_218~ BEGIN
	LOCAL_SET strref = 12180003 // ~de lancer Peau de pierre (1 peau) sur %theTarget%~

	LPM ~opcode_218_common~
END

DEFINE_PATCH_MACRO ~opcode_target_218~ BEGIN
	LOCAL_SET strref = 12180005 // ~Lance Peau de pierre (1 peau) sur %theTarget%~

	LPM ~opcode_218_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_218~ BEGIN
	LPM ~opcode_self_probability_218~
END

DEFINE_PATCH_MACRO ~opcode_218_common~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF is_ee == 1 AND parameter2 == 1 BEGIN
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount = amount RET amount = damage END
		INNER_PATCH_SAVE amount ~%amount%~ BEGIN
			REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
		END
	END

	PATCH_IF IS_AN_INT amount AND amount == 1 BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
	ELSE BEGIN
		SET strref += 1
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
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
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END

	SPRINT description @12200001 // ~Dissipe tous les sorts de l'école %spellSchoolName% de niveau %spellLevel% ou moins sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_220~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END

	SPRINT description @12200002 // ~de dissiper tous les sorts de l'école %spellSchoolName% de niveau %spellLevel% ou moins sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_220~ BEGIN
	LPM ~opcode_self_220~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_220~ BEGIN
	LPM ~opcode_self_probability_220~
END

/* ------------------------------------ *
 * Removal: Remove Secondary Type [221] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_221~ BEGIN
	LOCAL_SET spellLevel = parameter1
	PATCH_TRY
		LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

		SPRINT description @12210001 // ~Dissipe tous les sorts %spellSecondaryTypeName% de niveau %spellLevel% ou moins sur %theTarget%~
	WITH DEFAULT
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Wrong parameter2 : %parameter2%~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_221~ BEGIN
	LOCAL_SET spellLevel = parameter1

	PATCH_TRY
		LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

		SPRINT description @12210002 // ~de dissiper tous les sorts %spellSecondaryTypeName% de niveau %spellLevel% ou moins sur %theTarget%~
	WITH DEFAULT
        LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Wrong parameter2 : %parameter2%~ END
    END
END

DEFINE_PATCH_MACRO ~opcode_target_221~ BEGIN
	LPM ~opcode_self_221~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_221~ BEGIN
	LPM ~opcode_self_probability_221~
END

/* ---------------------------------- *
 * Spell Effect: Teleport Field [222] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_222~ BEGIN
	LOCAL_SET value = parameter1
	SPRINT range $feets_to_meters(~%value%~)

	SPRINT description @12220001 // ~Téléporte aléatoirement %theTarget% dans un rayon de %range%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_222~ BEGIN
	LOCAL_SET value = parameter1
	SPRINT range $feets_to_meters(~%value%~)

	SPRINT description @12220002 // ~de téléporter aléatoirement %theTarget% dans un rayon de %range%~
END

DEFINE_PATCH_MACRO ~opcode_target_222~ BEGIN
	LPM ~opcode_self_222~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_222~ BEGIN
	LPM ~opcode_self_probability_222~
END

/* ---------------------------------------------- *
 * Spell: Immunity (by School, decrementing [223] *
 * ---------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_223~ BEGIN
	LOCAL_SET amount = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12230001 // ~Absorbe 1 sort de l'école %spellSchoolName%~
	END
	ELSE BEGIN
		SPRINT description @12230002 // ~Absorbe %amount% sorts de l'école %spellSchoolName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_223~ BEGIN
	LOCAL_SET amount = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12230003 // ~d'absorber 1 sort de l'école %spellSchoolName%~
	END
	ELSE BEGIN
		SPRINT description @12230004 // ~d'absorber %amount% sorts de l'école %spellSchoolName%~
	END
END

/* ------------------------------------- *
 * Cure: Level Drain (Restoration) [224] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_224~ BEGIN
	SPRINT description @12240001 // ~Restaure les niveaux drainés %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_224~ BEGIN
	LPM ~opcode_self_224~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_224~ BEGIN
	SPRINT description @12240002 // ~de restaurer les niveaux drainés %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_224~ BEGIN
	LPM ~opcode_self_probability_224~
END

/* ------------------------------------------------------- *
 * Spell: Immunity (by Secondary Type, decrementing) [226] *
 * ------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_226~ BEGIN
	LOCAL_SET amount = parameter1

	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12260001 // ~Absorbe 1 sort %spellSecondaryTypeName%~
	END
	ELSE BEGIN
		SPRINT description @12260002 // ~Absorbe %amount% sorts %spellSecondaryTypeName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_226~ BEGIN
	LOCAL_SET amount = parameter1

	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12260003 // ~d'absorber 1 sort %spellSecondaryTypeName%~
	END
	ELSE BEGIN
		SPRINT description @12260004 // ~d'absorber %amount% sorts %spellSecondaryTypeName%~
	END
END

/* --------------------------------------------- *
 * Spell: Bounce (by School, decrementing) [227] *
 * --------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_227~ BEGIN
	LOCAL_SET amount = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12270001 // ~Renvoie 1 sort de l'école %spellSchoolName%~
	END
	ELSE BEGIN
		SPRINT description @12270002 // ~Renvoie %amount% sorts de l'école %spellSchoolName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_227~ BEGIN
	LOCAL_SET amount = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12270003 // ~de renvoyer 1 sort de l'école %spellSchoolName%~
	END
	ELSE BEGIN
		SPRINT description @12270004 // ~de renvoyer %amount% sorts de l'école %spellSchoolName%~
	END
END

/* ----------------------------------------------------- *
 * Spell: Bounce (by Secondary Type, decrementing) [228] *
 * ----------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_228~ BEGIN
	LOCAL_SET amount = parameter1

	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12280001 // ~Renvoie 1 sort %spellSecondaryTypeName%~
	END
	ELSE BEGIN
		SPRINT description @12280002 // ~Renvoie %amount% sorts %spellSecondaryTypeName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_228~ BEGIN
	LOCAL_SET amount = parameter1

	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	PATCH_IF amount == 1 BEGIN
		SPRINT description @12280003 // ~de renvoyer 1 sort %spellSecondaryTypeName%~
	END
	ELSE BEGIN
		SPRINT description @12280004 // ~de renvoyer %amount% sorts %spellSecondaryTypeName%~
	END
END

/* -------------------------------- *
 * Removal: Remove One School [229] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_229~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END

	SPRINT description @12290001 // ~Dissipe 1 sort de l'école %spellSchoolName% de niveau %spellLevel% ou moins sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_229~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 RET spellSchoolName END

	SPRINT description @12290002 // ~de dissiper 1 sort de l'école %spellSchoolName% de niveau %spellLevel% ou moins sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_229~ BEGIN
	LPM ~opcode_self_229~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_229~ BEGIN
	LPM ~opcode_self_probability_229~
END

/* ---------------------------------------- *
 * Removal: Remove One Secondary Type [230] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_230~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

	SPRINT description @12300001 // ~Dissipe 1 sort %spellSecondaryTypeName% de niveau %spellLevel% ou moins sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_230~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

	SPRINT description @12300002 // ~de dissiper 1 sort %spellSecondaryTypeName% de niveau %spellLevel% ou moins sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_230~ BEGIN
	LPM ~opcode_self_230~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_230~ BEGIN
	LPM ~opcode_self_probability_230~
END

/* ----------------------------- *
 * Spell Effect: Time Stop [231] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_231~ BEGIN
	SPRINT description @12310001 // ~Arrêt du temps~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_231~ BEGIN
	SPRINT description @12310003 // ~de lancer Arrêt du temps~
END

DEFINE_PATCH_MACRO ~opcode_target_231~ BEGIN
	SPRINT description @12310002 // ~Lance Arrêt du temps~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_231~ BEGIN
	LPM ~opcode_self_probability_231~ // ~de lancer Arrêt du temps~
END

/* ------------------------------------------- *
 * Spell Effect: Cast Spell on Condition [232] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_232~ BEGIN
	SET strref = 12320001
	LPM ~opcode_232_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_232~ BEGIN
	SET strref = 12320005
	LPM ~opcode_232_common~
END

DEFINE_PATCH_MACRO ~opcode_target_232~ BEGIN
	LPM ~opcode_self_232~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_232~ BEGIN
	LPM ~opcode_self_probability_232~
END

DEFINE_PATCH_MACRO ~opcode_232_common~ BEGIN
	SET featureCount   = 0
	SET theTargetRef   = 12320200 + parameter1
	SET ofTheTargetRef = 12320210 + parameter1
	SET toTheTargetRef = 12320220 + parameter1

	SPRINT spellName2 ~~
	SPRINT spellName3 ~~
	SPRINT theTarget   (AT ~%theTargetRef%~)
	SPRINT ofTheTarget (AT ~%ofTheTargetRef%~)
	SPRINT toTheTarget (AT ~%toTheTargetRef%~)

	LPM ~opcode_232_condition~

	LPF ~get_spell_name~ STR_VAR file = ~%resref%~ RET spellName END
	PATCH_IF isExternal AND NOT ~%resref2%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_spell_name~ STR_VAR file = ~%resref2%~ RET spellName2 = spellName END
	END
	PATCH_IF isExternal AND NOT ~%resref3%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_spell_name~ STR_VAR file = ~%resref3%~ RET spellName3 = spellName END
	END

	LPF ~get_spell_description~ INT_VAR forceTarget = 1 forcedProbability = probability STR_VAR file = EVAL ~%resref%~ theTarget ofTheTarget toTheTarget RET spellDescription count featureCount END

	INNER_PATCH_SAVE spellDescription ~%spellDescription%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE ~%crlf%~ ~%crlf%  ~ // Indentation de la description du sort
	END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND NOT ~%spellName2%~ STRING_EQUAL ~~ AND NOT ~%spellName3%~ STRING_EQUAL ~~ BEGIN
		SET strref += 2 // ~lance les sorts %spellName%, %spellName2% et %spellName3% sur %theTarget%~
	    SPRINT description (AT ~%strref%~)
    END
    ELSE PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND NOT ~%spellName2%~ STRING_EQUAL ~~ BEGIN
        SET strref += 1 // ~lance les sorts %spellName% et %spellName2% sur %theTarget%~
	    SPRINT description (AT ~%strref%~)
    END
    ELSE BEGIN
		PATCH_IF count == 1 AND featureCount == 1 BEGIN
			LPF ~get_single_spell_effect~ INT_VAR forceTarget = 1 forcedProbability = probability STR_VAR file = ~%resref%~ theTarget ofTheTarget toTheTarget RET effectDescription END

			INNER_PATCH_SAVE description ~%effectDescription%~ BEGIN
		        SPRINT regex @10009 // ~^[0-9]+ % de chance ~
				REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
			END
		END
		ELSE PATCH_IF ~%spellName%~ STRING_EQUAL ~~ BEGIN
	        SET strref += 3 // ~lance un sort sur %theTarget%~
		    SPRINT description (AT ~%strref%~)
			SPRINT description ~%description%%spellDescription%~
	    END
	    ELSE BEGIN
		    SPRINT description (AT ~%strref%~) // ~lance le sort %spellName% sur %theTarget%~
	    END
    END
END

DEFINE_PATCH_MACRO ~opcode_232_condition~ BEGIN
	SET conditionRef = 12320010 + parameter2
	SPRINT condition (AT ~%conditionRef%~)

	PATCH_IF parameter2 == 2 OR parameter2 == 3 OR parameter2 == 4 OR parameter2 == 20 BEGIN
		PATCH_IF parameter2 == 2 BEGIN
			SET value = 50
		END
		ELSE PATCH_IF parameter2 == 3 BEGIN
			SET value = 25
		END
		ELSE PATCH_IF parameter2 == 4 BEGIN
			SET value = 10
		END
		ELSE BEGIN
			SET value = special
		END
		PATCH_IF value >= 100 BEGIN
			SPRINT condition @12320020 // ~À chaque round~
		END
		ELSE BEGIN
			LPF ~percent_value~ INT_VAR value RET percent = value END
			SPRINT condition @12320030 // ~Lorsque les points de vie du porteur passent sous les %percent%~
		END
	END
	ELSE PATCH_IF parameter2 == 19 BEGIN
		SET value = special
		SPRINT condition @12320029 // ~Lorsque les points de vie du porteur passent sous %value%~
	END
	ELSE PATCH_IF parameter2 == 8 OR parameter2 == 9 OR parameter2 == 14 BEGIN
		PATCH_IF parameter2 == 8 BEGIN
			SET value = 4
		END
		ELSE PATCH_IF parameter2 == 9 BEGIN
            SET value = 10
        END
		ELSE BEGIN
            SET value = special
        END
		SPRINT range $feets_to_meters(~%value%~)
		SPRINT condition @12320024 // ~Lorsque la cible se trouve à moins de %range%~
	END
	ELSE PATCH_IF parameter2 == 13 BEGIN
		PATCH_IF parameter1 != 0 BEGIN
            LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: TimeOfDay : Parameter1 must be equal to 0~ END
		END
		SET timeofdayRef = 12320300 + special
		LPF ~getTranslation~ INT_VAR strref = timeofdayRef opcode RET condition = string END
	END
	ELSE PATCH_IF parameter2 == 21 BEGIN
		SET stateRef = 12320500 + special
		LPF ~getTranslation~ INT_VAR strref = stateRef opcode RET splstate = string END
		PATCH_IF NOT ~%splstate%~ STRING_EQUAL ~~ BEGIN
			SPRINT condition @12320031 // ~À chaque round où %theTarget% est affecté par %splstate%~
		END
	END
	ELSE PATCH_IF parameter2 == 15 OR parameter2 == 18 BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: TODO parameter2 : %parameter2% : %parameter1% : %special%~ END
	END
END

/* -------------------------------- *
 * Stat: Proficiency Modifier [233] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_233~ BEGIN
	LOCAL_SPRINT proficiency ~~

	LPM ~opcode_233_common~

	PATCH_IF VARIABLE_IS_SET $tra_proficiencies(~%parameter2%~)  BEGIN
		SPRINT proficiency $tra_proficiencies(~%parameter2%~)
		SPRINT name @12330001 // ~Compétence martiale %proficiency%~

		PATCH_IF type == 1 BEGIN
			LPF ~signed_value~ INT_VAR value RET value END
		END
		ELSE BEGIN
			SPRINT value @10010 // ~Passe à %value%~
		END

		SPRINT description @100001 // ~%name%%colon%%value%~
	END
	ELSE PATCH_IF parameter2 != 109 BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Proficiency not found : %parameter2%~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_233~ BEGIN
	LOCAL_SPRINT proficiency ~~

	LPM ~opcode_233_common~

	PATCH_IF VARIABLE_IS_SET $tra_proficiencies(~%parameter2%~)  BEGIN
		SPRINT proficiency $tra_proficiencies(~%parameter2%~)
		SPRINT theStatistic @12330002 // ~la compétence martiale %proficiency%~
		PATCH_IF type == 1 BEGIN
			PATCH_IF value > 0 BEGIN
	            SPRINT description @102544 // ~d'augmenter de %value% %theStatistic% %ofTheTarget%~
			END
			ELSE BEGIN
				SET value = ABS value
				SPRINT description @102543 // ~de réduire de %value% %theStatistic% %ofTheTarget%~
			END
		END
		ELSE BEGIN
			SPRINT description @102545 // ~de passer à %value% %theStatistic% %ofTheTarget%~
		END
	END
	ELSE PATCH_IF parameter2 != 109 BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Proficiency not found : %parameter2%~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_233~ BEGIN
	LPM ~opcode_self_probability_233~
END

DEFINE_PATCH_MACRO ~opcode_233_common~ BEGIN
	SET value = parameter1
	SET type = 0
	PATCH_IF is_ee == 1 BEGIN
		SET type = parameter2 BLSR 16
		SET parameter2 = parameter2 BAND 255
	END
END

/* ------------------------------- *
 * Spell Effect: Wing Buffet [235] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_235~ BEGIN
	SPRINT description @12350001 // ~Renverse et sonne %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_235~ BEGIN
	SPRINT description @12350002 // ~de renverser et sonner %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_235~ BEGIN
	LPM ~opcode_self_235~ // ~Renverse et sonne %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_235~ BEGIN
	LPM ~opcode_self_probability_235~ // ~de renverser et sonner %theTarget%~
END

/* ------------------------------------ *
 * Spell Effect: Image Projection [236] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_236~ BEGIN
	LOCAL_SET strref = 12360001 // ~Crée un clône %ofTheTarget% possédant le même nombre de points de vie (Utilisable après une rechargement du jeu dû à un bug)~
	LPM ~opcode_236_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_236~ BEGIN
	LOCAL_SET strref = 12360005 // ~de créer un clône %ofTheTarget% possédant le même nombre de points de vie (Utilisable après une rechargement du jeu dû à un bug)~
	LPM ~opcode_236_common~
END

DEFINE_PATCH_MACRO ~opcode_target_236~ BEGIN
	LPM ~opcode_self_236~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_236~ BEGIN
	LPM ~opcode_self_probability_236~
END

DEFINE_PATCH_MACRO ~opcode_236_common~ BEGIN
	LOCAL_SET type = parameter2

	PATCH_IF type > 4 BEGIN
		SET type = 0
	END
	SET strref += type

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

/* ------------------------- *
 * Death: Disintegrate [238] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_238~ BEGIN
	LOCAL_SET strref = 12380001 // ~Désintègre %theTarget%~

	PATCH_IF NOT (parameter1 == 0 AND parameter2 == 2) BEGIN
		SET strref += 1 // ~Désintègre les %creatureType%~
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_238~ BEGIN
	LOCAL_SET strref = 12380003 // ~de désintégrer %theTarget%~

	PATCH_IF NOT (parameter1 == 0 AND parameter2 == 2) BEGIN
		SET strref += 1 // ~de désintégrer les %creatureType%~
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_target_238~ BEGIN
	LPM ~opcode_self_238~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_238~ BEGIN
	LPM ~opcode_self_probability_238~
END

/* ---------------------------- *
 * Spell Effect: Farsight [239] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_239~ BEGIN
	SPRINT description @12390001 // ~Permet de voir au loin~
END

/* ----------------------------- *
 * Charm: Control Creature [241] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_241~ BEGIN
	LPM ~opcode_self_5~
END

DEFINE_PATCH_MACRO ~opcode_target_241~ BEGIN
	LPM ~opcode_target_5~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_241~ BEGIN
	LPM ~opcode_target_probability_5~
END

/* --------------------- *
 * Cure: Confusion [242] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_242~ BEGIN
	SPRINT description @12420001 // ~Immunité à la confusion~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_242~ BEGIN
	SPRINT description @12420003 // ~de dissiper la confusion %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_242~ BEGIN
	SPRINT description @12420002 // ~Dissipe la confusion %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_242~ BEGIN
	LPM ~opcode_self_probability_242~
END

/* ------------------------------ *
 * Item: Drain Item Charges [243] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_243~ BEGIN
	LOCAL_SET strref = 12430001 // ~Draine une charge aux objets magiques %ofTheTarget%~
	LPM ~opcode_243_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_243~ BEGIN
	LOCAL_SET strref = 12430004 // ~de drainer une charge aux objets magiques %ofTheTarget%~
	LPM ~opcode_243_common~
END

DEFINE_PATCH_MACRO ~opcode_target_243~ BEGIN
	LPM ~opcode_self_243~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_243~ BEGIN
	LPM ~opcode_self_probability_243~
END

DEFINE_PATCH_MACRO ~opcode_243_common~ BEGIN
	LOCAL_SET amount = parameter1
	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF amount != 1 BEGIN
			SET strref += 1 // ~Draine %amount% charges aux objets magiques %ofTheTarget%~
		END
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
	ELSE PATCH_IF NOT GAME_IS ~tob~ BEGIN
		SET strref += 2 // ~Draine les charges des objets magiques %ofTheTarget%~
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
		PATCH_IF amount == 0 BEGIN
			SPRINT exception @12430007 // ~excepté les armes~
			SPRINT description ~%description%, %exception%~
		END
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: This effect not works in ToB~ END
	END
END

/* ------------------------------- *
 * Spell: Drain Wizard Spell [244] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_244~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF amount == 1 BEGIN
		SPRINT description @12440001 // ~Supprime 1 sort profane de la mémoire %ofTheTarget%~
	END
	ELSE BEGIN
		SPRINT description @12440002 // ~Supprime %amount% sorts profanes de la mémoire %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_244~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF amount == 1 BEGIN
		SPRINT description @12440003 // ~de supprimer 1 sort profane de la mémoire %ofTheTarget%~
	END
	ELSE BEGIN
		SPRINT description @12440004 // ~de supprimer %amount% sorts profanes de la mémoire %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_244~ BEGIN
	LPM ~opcode_self_244~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_244~ BEGIN
	LPM ~opcode_self_probability_244~
END

/* ----------------------- *
 * Check For Berserk [245] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_245~ BEGIN
	SPRINT description @12450001 // ~Chaque attaque réussie a 1% de chance de provoquer la folie du berserker chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_245~ BEGIN
	SPRINT description @12450002 // ~que chaque attaque réussie a 1% de chance de provoquer la folie du berserker chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_245~ BEGIN
	LPM ~opcode_self_245~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_245~ BEGIN
	LPM ~opcode_self_probability_245~
END

/* ------------------------------ *
 * Spell Effect: Berserking [246] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_246~ BEGIN
	LPM ~opcode_self_3~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_246~ BEGIN
	LPM ~opcode_self_probability_3~
END

DEFINE_PATCH_MACRO ~opcode_target_246~ BEGIN
	LPM ~opcode_target_3~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_246~ BEGIN
	LPM ~opcode_target_probability_3~
END

/* ------------------------------------------- *
 * Spell Effect: Attack Nearest Creature [247] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_247~ BEGIN
	SPRINT description @12470001 // ~Provoque la folie du berserker (+2 au TAC0 et aux dégâts) chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_247~ BEGIN
	SPRINT description @12470002 // ~de provoquer la folie du berserker (+2 au TAC0 et aux dégâts) chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_247~ BEGIN
	LPM ~opcode_self_247~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_245~ BEGIN
	LPM ~opcode_self_probability_247~
END

/* ---------------------------- *
 * Item: Set Melee Effect [248] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_248~ BEGIN
	SET abilityType = AbilityType_Combat
	LPF ~get_res_description_177~ INT_VAR resetTarget = 1 STR_VAR resref RET description saveAdded ignoreDuration opcode END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF is_ee == 1 AND parameter2 == 4 BEGIN
			SPRINT description @12480002 // ~À chaque attaque au poing réussie: %description%~
		END
		ELSE BEGIN
			SPRINT description @12480001 // ~À chaque attaque de mêlée réussie: %description%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_248~ BEGIN
	SET abilityType = AbilityType_Combat
	LPF ~get_res_description_177~ INT_VAR resetTarget = 1 STR_VAR resref RET description saveAdded ignoreDuration opcode END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF is_ee == 1 AND parameter2 == 4 BEGIN
			SPRINT description @12480004 // ~par attaque au poing réussie par %theTarget%: %description%~
		END
		ELSE BEGIN
			SPRINT description @12480003 // ~par attaque de mêlée réussie par %theTarget%: %description%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_248~ BEGIN
	SET abilityType = AbilityType_Combat
	LPF ~get_res_description_177~ INT_VAR resetTarget = 1 STR_VAR resref RET description saveAdded ignoreDuration opcode END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF is_ee == 1 AND parameter2 == 4 BEGIN
			SPRINT description @12480004 // ~À chaque attaque au poing réussie par %theTarget%: %description%~
		END
		ELSE BEGIN
			SPRINT description @12480003 // ~À chaque attaque de mêlée réussie par %theTarget%: %description%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_248~ BEGIN
	LPM ~opcode_self_probability_248~
END

/* ----------------------------- *
 * Item: Set Ranged Effect [249] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_249~ BEGIN
	SET abilityType = AbilityType_Combat
	LPF ~get_res_description_177~ INT_VAR resetTarget = 1 STR_VAR resref RET description saveAdded ignoreDuration opcode END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12490001 // ~À chaque attaque à distance réussie: %description%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_249~ BEGIN
	SET abilityType = AbilityType_Combat
	LPF ~get_res_description_177~ INT_VAR resetTarget = 1 STR_VAR resref RET description saveAdded ignoreDuration opcode END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12490003 // ~par attaque à distance réussie par %theTarget%: %description%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_249~ BEGIN
	SET abilityType = AbilityType_Combat
	LPF ~get_res_description_177~ INT_VAR resetTarget = 1 STR_VAR resref RET description saveAdded ignoreDuration opcode END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12490002 // ~À chaque attaque à distance réussie par %theTarget%: %description%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_249~ BEGIN
	LPM ~opcode_self_probability_249~
END

/* ----------------------------------- *
 * Spell Effect: Damage Modifier [250] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_250~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12500001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts minimum~
END

DEFINE_PATCH_MACRO ~opcode_target_250~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12500002 RET description END // ~les dégâts minimum~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_250~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12500002 RET description END // ~les dégâts minimum~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_250~ BEGIN
	LPM ~opcode_self_probability_250~
END

/* ---------------------------------------- *
 * Item: Create Inventory Item (days) [255] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_255~ BEGIN
	// TODO: duration in days !
	LPM ~opcode_self_122~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_255~ BEGIN
	LPM ~opcode_self_probability_122~
END

DEFINE_PATCH_MACRO ~opcode_target_255~ BEGIN
	LPM ~opcode_target_122~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_255~ BEGIN
	LPM ~opcode_target_probability_122~
END

/* ---------------------------- *
 * Protection: Spell Trap [259] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_259~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	SPRINT description @12590001 // ~Piège à sorts (piège des sorts de niveau %spellLevel% ou moins, jusqu'à ce que %amount% niveaux de sort aient été emprisonnés)~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_259~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	SPRINT description @12590003 // ~de lancer Piège à sorts (piège des sorts de niveau %spellLevel% ou moins, jusqu'à ce que %amount% niveaux de sort aient été emprisonnés) sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_259~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2
	//TODO: On EE games, resource field ⟶ Spell cast when this effect self-terminates, default = Parent + "B".
	SPRINT description @12590002 // ~Lance Piège à sorts (piège des sorts de niveau %spellLevel% ou moins, jusqu'à ce que %amount% niveaux de sort aient été emprisonnés) sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_259~ BEGIN
	LPM ~opcode_self_probability_259~
END

/* -------------------------------- *
 * Spell: Restore Lost Spells [261] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_261~ BEGIN
	LOCAL_SET spellLevel = parameter1
	LOCAL_SET strref = 12610001

	PATCH_IF spellLevel > 1 BEGIN
		SET strref += 1
	END
	PATCH_IF parameter2 != 0 BEGIN
		SET strref += 2
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_261~ BEGIN
	LOCAL_SET spellLevel = parameter1
	LOCAL_SET strref = 12610005

	PATCH_IF spellLevel > 1 BEGIN
		SET strref += 1
	END
	PATCH_IF parameter2 != 0 BEGIN
		SET strref += 2
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_target_261~ BEGIN
	LPM ~opcode_self_261~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_261~ BEGIN
	LPM ~opcode_self_probability_261~
END

/* ------------------------ *
 * Stat: Visual Range [262] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_262~ BEGIN
	LOCAL_SET value = ~%parameter1%~
	LOCAL_SET isNegative = 0

	PATCH_IF value < 0 BEGIN
		SET isNegative = 1
		SET value = ABS value
	END

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		PATCH_IF value < 0 BEGIN
			SPRINT value $feets_to_meters(~%value%~)
			SPRINT value ~-%value%~
		END
		ELSE BEGIN
			SPRINT value $feets_to_meters(~%value%~)
			SPRINT value ~+%value%~
		END
	END
	ELSE BEGIN
		SPRINT value $feets_to_meters(~%value%~)
		SPRINT value @10010 // ~Passe à %value%~
	END
	SPRINT name @12620001 // ~Champ de vision~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_262~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	SPRINT theStatistic @12620002 // ~le champ de vision~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF value > 0 BEGIN
			SPRINT value $feets_to_meters(~%value%~)
	        SPRINT description @102544 // ~d'augmenter %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
			SPRINT value $feets_to_meters(~%value%~)
	        SPRINT description @102543 // ~de réduire %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value $feets_to_meters(~%value%~)
		SPRINT description @102545 // ~de passer %theStatistic% %ofTheTarget% à %value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_262~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	SPRINT theStatistic @12620002 // ~le champ de vision~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF value > 0 BEGIN
			SPRINT value $feets_to_meters(~%value%~)
	        SPRINT description @102286 // ~Augmente %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
			SPRINT value $feets_to_meters(~%value%~)
	        SPRINT description @102285 // ~Réduit %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value $feets_to_meters(~%value%~)
		SPRINT description @102287 // ~Passe %theStatistic% %ofTheTarget% à %value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_262~ BEGIN
	LPM ~opcode_self_probability_262~
END

/* -------------------- *
 * Stat: Backstab [263] *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_263~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12630001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Multiplicateur d'attaque sournoise~
END

DEFINE_PATCH_MACRO ~opcode_target_263~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12630002 RET description END // ~le multiplicateur d'attaque sournoise~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_263~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12630002 RET description END // ~le multiplicateur d'attaque sournoise~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_263~ BEGIN
	LPM ~opcode_self_probability_263~
END

/* ---------------------------------------- *
 * Spell Effect: Explore (Wizard Eye) [268] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_268~ BEGIN
	SPRINT description @12680001 // ~Permet %toTheTarget% d'explorer la carte~
END

DEFINE_PATCH_MACRO ~opcode_target_268~ BEGIN
	LPM ~opcode_self_268~ // ~Permet %toTheTarget% d'explorer la carte~
END

/* -------------------------------- *
 * Spell: Apply Repeating EFF [272] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_272~ BEGIN
	LOCAL_SET strref = 12720000 + parameter2
	LOCAL_SET amount1 = parameter1
	LOCAL_SET amount2 = 0
	LOCAL_SET frequencyMultiplier = 1
	LOCAL_SET amount = amount1
	LOCAL_SET frequency = 1

	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF isExternal BEGIN
			SET amount2 = parameter3
			SET frequencyMultiplier = parameter4
		END
		PATCH_IF parameter2 == 4 BEGIN
			SET amount = amount2
		END
		PATCH_IF parameter2 == 2 BEGIN
			SET frequency = frequencyMultiplier
		END
		ELSE PATCH_IF parameter2 == 3 OR parameter2 == 4 BEGIN
			SET frequency = amount1 * frequencyMultiplier
		END

		PATCH_IF parameter2 == 2 OR parameter2 == 3 OR parameter2 == 4 BEGIN
			LPF ~get_str_duration~ INT_VAR duration = frequency RET strDuration END

			PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^1 ~ == 0 BEGIN
				INNER_PATCH_SAVE strDuration ~%strDuration%~ BEGIN
					REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^1 ~ ~~
				END
				PATCH_IF parameter2 == 2 OR parameter2 == 4 BEGIN
					SET strref = 12720010 // ~%description%, %amount% fois par %strDuration%~
				END
				ELSE BEGIN
					SET strref = 12720005 // ~%description%, à chaque %strDuration%~
				END
			END
			ELSE BEGIN
				PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ heure~ == 0 OR ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ seconde~ == 0 BEGIN
					PATCH_IF parameter2 == 2 OR parameter2 == 4 BEGIN
						SET strref = 12720008 // ~%description%, %amount% fois toutes les %strDuration%~
					END
					ELSE BEGIN
						SET strref = 12720003 // ~%description%, toutes les %strDuration%~
					END
				END
				ELSE BEGIN
					PATCH_IF parameter2 == 2 OR parameter2 == 4 BEGIN
                        SET strref = 12720009 // ~%description%, %amount% fois tous les %strDuration%~
                    END
                    ELSE BEGIN
						SET strref = 12720004 // ~%description%, tous les %strDuration%~
                    END
				END
			END
		END
	END
	ELSE BEGIN
		SET frequency = amount1
		PATCH_IF parameter2 == 3 BEGIN
			LPF ~get_str_duration~ INT_VAR duration = frequency RET strDuration END

			PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^1 ~ == 0 BEGIN
				INNER_PATCH_SAVE strDuration ~%strDuration%~ BEGIN
					REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^1 ~ ~~
				END
				SET strref = 12720005 // ~%description%, à chaque %strDuration%~
			END
			ELSE BEGIN
				PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ heure~ == 0 OR ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ seconde~ == 0 BEGIN
					SET strref = 12720003 // ~%description%, toutes les %strDuration%~
				END
				ELSE BEGIN
					SET strref = 12720004 // ~%description%, tous les %strDuration%~
				END
			END
		END
		ELSE PATCH_IF parameter2 == 4 BEGIN
			PATCH_IF isExternal BEGIN
				SET amount = parameter3
				SET strref = frequency == 1 ? 12720007 : 12720006
			END
			ELSE BEGIN
				SET strref = 0
	            LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: parameter2 = 4 can only be used in external eff files~ END
			END
		END
	END
	PATCH_IF parameter1 <= 0 BEGIN
        LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid value for parameter1 : %parameter2%~ END
	END
	PATCH_IF parameter2 == 1 OR parameter2 >= 5 BEGIN
        LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid value for parameter2 : %parameter2% >= 5 OR %parameter2% == 2 => crash the game~ END
	END
	ELSE PATCH_IF strref > 0 BEGIN
		LPF ~get_res_description_177~ STR_VAR resref macro = ~opcode_self_~ RET description saveAdded ignoreDuration opcode END
		PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
			LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_272~ BEGIN
	LPM ~opcode_self_272~
END

DEFINE_PATCH_MACRO ~opcode_target_272~ BEGIN
	LPM ~opcode_self_272~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_272~ BEGIN
	LPM ~opcode_self_probability_272~
END

/* ----------------------------------------------------- *
 * Remove: Specific Area Effect(Zone of Sweet Air) [273] *
 * ----------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_273~ BEGIN
	SPRINT description @12730001 // ~Zone d'air pur~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_273~ BEGIN
	SPRINT description @12730003 // ~de lancer Zone d'air pur sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_273~ BEGIN
	SPRINT description @12730002 // ~Lance Zone d'air pur sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_273~ BEGIN
	LPM ~opcode_self_probability_273~
END

/* -------------------------------------- *
 * Spell Effect: Teleport to Target [274] *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_274~ BEGIN
	SPRINT description @12740001 // ~Téléporte %theTarget% sur un ennemi aléatoire~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_274~ BEGIN
	SPRINT description @12740002 // ~de téléporter %theTarget% sur un ennemi aléatoire~
END

DEFINE_PATCH_MACRO ~opcode_target_274~ BEGIN
	LPM ~opcode_self_274~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_274~ BEGIN
	LPM ~opcode_self_probability_274~
END

/* ------------------------------------ *
 * Stat: Hide in Shadows Modifier [275] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_275~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 12750001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Camouflage dans l'ombre~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_275~ BEGIN
	LPF ~opcode_probability_percent~ INT_VAR strref = 12750002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le camouflage dans l'ombre~
END

DEFINE_PATCH_MACRO ~opcode_target_275~ BEGIN
	LPF ~opcode_target_percent~ INT_VAR strref = 12750002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le camouflage dans l'ombre~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_275~ BEGIN
	LPM ~opcode_self_probability_275~
END

/* ------------------------------------ *
 * Stat: Detect Illusion Modifier [276] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_276~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 12760001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Détection des illusions~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_276~ BEGIN
	LPF ~opcode_probability_percent~ INT_VAR strref = 12760002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la détection des illusions~
END

DEFINE_PATCH_MACRO ~opcode_target_276~ BEGIN
	LPF ~opcode_target_percent~ INT_VAR strref = 12760002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la détection des illusions~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_276~ BEGIN
	LPM ~opcode_self_probability_276~
END

/* ------------------------------ *
 * Stat: Set Traps Modifier [277] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_277~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 12770001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Pose de pièges~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_277~ BEGIN
	LPF ~opcode_probability_percent~ INT_VAR strref = 12770002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la pose de pièges~
END

DEFINE_PATCH_MACRO ~opcode_target_277~ BEGIN
	LPF ~opcode_target_percent~ INT_VAR strref = 12770002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~la pose de pièges~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_277~ BEGIN
	LPM ~opcode_self_probability_277~
END

/* --------------------------- *
 * Stat: To Hit Modifier [278] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_278~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12780001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Chances de toucher~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_278~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12780002 RET description END // ~les chances de toucher~
END

DEFINE_PATCH_MACRO ~opcode_target_278~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12780002 RET description END // ~les chances de toucher~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_278~ BEGIN
	LPM ~opcode_self_probability_278~
END

/* ------------------------------ *
 * Spell Effect: Wild Magic [280] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_280~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @12800001 // ~Le prochain sort lancé par %theTarget% déclenche automatiquement un hiatus entropique~
	END
	ELSE BEGIN
		SPRINT description @12800002 // ~Les sorts lancés par %theTarget% déclenchent automatiquement un hiatus entropique~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_280~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @12800003 // ~que le prochain sort lancé par %theTarget% déclenche un hiatus entropique~
	END
	ELSE BEGIN
		SPRINT description @12800004 // ~que les sorts lancés par %theTarget% déclenchent un hiatus entropique~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_280~ BEGIN
	LPM ~opcode_self_280~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_280~ BEGIN
	LPM ~opcode_self_probability_280~
END

/* ----------------------- *
 *  Stat: Wild Magic [281] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_281~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12810001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Hiatus entropique~
END

DEFINE_PATCH_MACRO ~opcode_target_281~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12810002 RET description END // ~le hiatus entropique~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_281~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12810002 RET description END // ~le hiatus entropique~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_281~ BEGIN
	LPM ~opcode_self_probability_281~
END

/* --------------------------- *
 * Use EFF File (Cursed) [283] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_283~ BEGIN
	LPM ~opcode_self_177~

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT name @12830001 // ~Malédiction~
		SPRINT description ~%name%%colon%%description%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_283~ BEGIN
	SET forceSort = 1
	SET sort = 0
	LPM ~opcode_self_probability_177~

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT name @12830002 // ~de maudir %theTarget% et~
		SPRINT description ~%name% %description%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_283~ BEGIN
	LPM ~opcode_target_177~

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT name @12830003 // ~Maudit %theTarget% et~
		SPRINT description ~%name% %description%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_283~ BEGIN
	SET forceSort = 1
	SET sort = 0
	LPM ~opcode_target_probability_177~

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT name @12830002 // ~de maudir %theTarget% et~
		SPRINT description ~%name%%colon%%description%~
	END
END

/* -------------------------------- *
 * Stat: Melee THAC0 Modifier [284] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_284~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12840001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 des armes de mêlée~
END

DEFINE_PATCH_MACRO ~opcode_target_284~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12840002 RET description END // ~le TAC0 des armes de mêlée~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_284~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12840002 RET description END // ~le TAC0 des armes de mêlée~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_284~ BEGIN
	LPM ~opcode_self_probability_584~
END

/* ---------------------------------------- *
 * Stat: Melee Weapon Damage Modifier [285] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_285~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12850001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts des armes de mêlée~
END

DEFINE_PATCH_MACRO ~opcode_target_285~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12850002 RET description END // ~les dégâts des armes de mêlée~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_285~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12850002 RET description END // ~les dégâts des armes de mêlée~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_285~ BEGIN
	LPM ~opcode_self_probability_285~
END

/* ------------------------------------------ *
 * Stat: Missile Weapon Damage Modifier [286] *
 * ------------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_286~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12860001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts des armes à projectiles~
END

DEFINE_PATCH_MACRO ~opcode_target_286~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12860002 RET description END // ~les dégâts des armes à projectiles~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_286~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12860002 RET description END // ~les dégâts des armes à projectiles~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_286~ BEGIN
	LPM ~opcode_self_probability_286~
END

/* ------------------------------- *
 * Stat: Fist THAC0 Modifier [288] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_288~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12880001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 des poings~
END

DEFINE_PATCH_MACRO ~opcode_target_288~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12880002 RET description END // ~le TAC0 des poings~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_288~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12880002 RET description END // ~le TAC0 des poings~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_288~ BEGIN
	LPM ~opcode_self_probability_288~
END

/* -------------------------------- *
 * Stat: Fist Damage Modifier [289] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_289~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12890001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Dégâts des poings~
END

DEFINE_PATCH_MACRO ~opcode_target_289~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12890002 RET description END // ~les dégâts des poings~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_289~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12890002 RET description END // ~les dégâts des poings~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_289~ BEGIN
	LPM ~opcode_self_probability_289~
END

/* -------------------------- *
 * Protection: Backstab [292] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_292~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12920001 // ~Immunité aux attaques sournoises~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_292~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12920003 // ~de résister aux attaques sournoises~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_292~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12920002 // ~Immunise %theTarget% aux attaques sournoises~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_292~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12920004 // ~d'immuniser %theTarget% aux attaques sournoises~
	END
END

/* -------------- *
 * NPC Bump [300] *
 * -------------- */
DEFINE_PATCH_MACRO ~opcode_self_300~ BEGIN
	PATCH_IF parameter2 > 0 BEGIN
		SET strref = 13000000 + parameter2
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_300~ BEGIN
	LPM ~opcode_self_300~
END

/* --------------------------------- *
 * Stat: Critical Hit Modifier [301] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_301~ BEGIN
	// TODO: Gérer attack type de EE
	LOCAL_SET value = 5 * parameter1
	LPF ~signed_value~ INT_VAR value RET value END
	SPRINT value @10002 // ~%value% %~
	SPRINT name @13010001 // ~Chance de coup critique~
	PATCH_IF is_ee == 1 AND parameter2 == 1 BEGIN
		SPRINT name @13010002 // ~Chance de coup critique avec cette arme~
	END
	SPRINT description @100001 // ~%name%%colon%%value%~
END

/* ---------------------------- *
 * Item: Can Use Any Item [302] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_302~ BEGIN
	//TODO:si parameter2 == 0, désactive l'effet sur la cible si elle l'avait déjà par un autre moyen
	SPRINT description @13020001 // ~Permet d'utiliser n'importe quel objet~
END

/* -------------------------------------- *
 * Spell Effect: Backstab Every Hit [303] *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_303~ BEGIN
	//TODO:si parameter2 == 0, désactive l'effet sur la cible si elle l'avait déjà par un autre moyen
	SPRINT description @13030001 // ~Transforme toute attaque portée en attaque sournoise (si l'arme équipée l'autorise)~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_303~ BEGIN
	SPRINT description @13030003 // ~de transformer toute attaque portée par %theTarget% en attaque sournoise (si l'arme équipée l'autorise)~
END

DEFINE_PATCH_MACRO ~opcode_target_303~ BEGIN
	SPRINT description @13030002 // ~Transforme toute attaque portée par %theTarget% en attaque sournoise (si l'arme équipée l'autorise)~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_303~ BEGIN
	LPM ~opcode_self_probability_303~ // ~de transformer toute attaque portée par %theTarget% en attaque sournoise (si l'arme équipée l'autorise)~
END

/* ------------------------------------- *
 * Stat: THAC0 Modifier (Off-Hand) [305] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_305~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 13050001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 de la main secondaire~
END

DEFINE_PATCH_MACRO ~opcode_target_605~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 13050002 RET description END // ~le TAC0 de la main secondaire~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_605~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 13050002 RET description END // ~le TAC0 de la main secondaire~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_605~ BEGIN
	LPM ~opcode_self_probability_605~
END

/* ------------------------------------ *
 * Stat: THAC0 Modifier (On-Hand) [306] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_306~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 13060001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~TAC0 de la main principale~
END

DEFINE_PATCH_MACRO ~opcode_target_306~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 13060002 RET description END // ~le TAC0 de la main principale~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_306~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 13060002 RET description END // ~le TAC0 de la main principale~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_306~ BEGIN
	LPM ~opcode_self_probability_306~
END

/* ------------------------------- *
 * Protection: from Timestop [310] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_310~ BEGIN
	SPRINT description @13100001 // ~Immunité à l'arrêt du temps~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_310~ BEGIN
	SPRINT description @13100003 // ~d'immuniser %theTarget% à l'arrêt du temps~
END

DEFINE_PATCH_MACRO ~opcode_target_310~ BEGIN
	SPRINT description @13100002 // ~Immunise %theTarget% à l'arrêt du temps~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_310~ BEGIN
	LPM ~opcode_self_probability_310~ // ~d'immuniser %theTarget% à l'arrêt du temps~
END

/* ------------------------------ *
 * Spell: Random Wish Spell [311] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_311~ BEGIN
	SPRINT description @13110001 // ~Lance un souhait aléatoire sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_311~ BEGIN
	SPRINT description @13110002 // ~de lancer un souhait aléatoire sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_311~ BEGIN
	LPM ~opcode_self_311~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_311~ BEGIN
	LPM ~opcode_self_probability_311~
END

/* ------------------------- *
 * Spell: Magical Rest [316] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_probability_316~ BEGIN
	SPRINT description @13160001 // ~de reposer %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_316~ BEGIN
	LPM ~opcode_self_probability_316~ // ~de reposer %theTarget%~
END

/* ------------------- *
 * State: Haste2 [317] *
 * ------------------- */
DEFINE_PATCH_MACRO ~opcode_self_317~ BEGIN
	LPM ~opcode_self_16~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_317~ BEGIN
	LPM ~opcode_self_probability_16~
END

DEFINE_PATCH_MACRO ~opcode_target_317~ BEGIN
	LPM ~opcode_target_16~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_317~ BEGIN
	LPM ~opcode_target_probability_16~
END

/* ----------------------------------------------------------- *
 * Stat: Set Stat (TobEx) [318] // Ignoré en version classique *
 * EE: Protection from Resource [318]                          *
 * ----------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_318~ BEGIN
	LPM ~opcode_self_324~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_318~ BEGIN
	LPM ~opcode_self_probability_324~
END

DEFINE_PATCH_MACRO ~opcode_target_318~ BEGIN
	LPM ~opcode_target_324~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_318~ BEGIN
	LPM ~opcode_target_probability_324~
END

/* -------------------------------------------- *
 * Removal: Effects specified by Resource [321] *
 * -------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_321~ BEGIN
	LOCAL_SET strref = 13210001
	LPM ~opcode_321_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_321~ BEGIN
	LOCAL_SET strref = 13210004
	LPM ~opcode_321_common~
END

DEFINE_PATCH_MACRO ~opcode_target_321~ BEGIN
	LPM ~opcode_self_321~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_321~ BEGIN
	LPM ~opcode_self_probability_321~
END

DEFINE_PATCH_MACRO ~opcode_321_common~ BEGIN
	// TODO: Gérer le type = parameter2
	PATCH_IF ~%resref%~ STRING_EQUAL ~%SOURCE_RES%~ BEGIN
		SET ignoreDuration = 1
		SET forceSort = 1
		SET sort = 0
		SPRINT description @13210007 // ~Les effets ne se cumulent pas~
	END
	ELSE BEGIN
		LPF ~get_spell_name~ INT_VAR showWarning = 0 STR_VAR file = EVAL ~%resref%~ RET spellName END
		LPF ~get_item_name~ INT_VAR showWarning = 0 STR_VAR file = EVAL ~%resref%~ RET itemName END

		PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
			SET strref += 2
			LPF ~getTranslation~ INT_VAR strref = strref opcode RET description = string END // ~Dissipe les effets du sort %spellName% et de l'objet %itemName% sur %theTarget%~
		END
		ELSE PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
			SET strref += 1
			LPF ~getTranslation~ INT_VAR strref = strref opcode RET description = string END // ~Dissipe les effets de l'objet %itemName% sur %theTarget%~
		END
		ELSE PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
			LPF ~getTranslation~ INT_VAR strref = strref opcode RET description = string END // ~Dissipe les effets du sort %spellName% sur %theTarget%~
		END
		ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : no names of spells or items found~ END
		END
	END
END

/* ----------------------------- *
 * Stat: Turn Undead Level [323] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_323~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 13230001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Niveau de repousser les morts-vivants~
END

DEFINE_PATCH_MACRO ~opcode_target_323~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 13230002 RET description END // ~le niveau de repousser les morts-vivants~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_323~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 13230002 RET description END // ~le niveau de repousser les morts-vivants~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_323~ BEGIN
	LPM ~opcode_self_probability_323~
END

/* -------------------------------------------------- *
 * Protection: Immunity to Resource and Message [324] *
 * -------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_324~ BEGIN
	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF NOT ~%resref%~ STRING_EQUAL_CASE ~%SOURCE_RES%~ AND parameter1 == 0 AND parameter2 = 0 BEGIN
			LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
			PATCH_IF NOT ~%spellName%~ STRING_EQUAL_CASE ~~ BEGIN
				SPRINT description @13240501 // ~Immunité au sort %spellName%~
			END
		END
		ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : self avec parameter1 et parameter2 différent de 0~ END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_324~ BEGIN
	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF NOT ~%resref%~ STRING_EQUAL_CASE ~%SOURCE_RES%~ AND parameter1 == 0 AND parameter2 = 0 BEGIN
			LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
			PATCH_IF NOT ~%spellName%~ STRING_EQUAL_CASE ~~ BEGIN
				SPRINT description @13240503 // ~d'immuniser %theTarget% au sort %spellName%~
			END
		END
		ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : self_probability avec parameter1 et parameter2 différent de 0~ END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_324~ BEGIN
	LOCAL_SET strref = 13240000

	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF NOT ~%resref%~ STRING_EQUAL_CASE ~%SOURCE_RES%~ AND parameter1 == 0 AND parameter2 = 0 BEGIN
			LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
			PATCH_IF NOT ~%spellName%~ STRING_EQUAL_CASE ~~ BEGIN
				SPRINT description @13240502 // ~Immunise %theTarget% au sort %spellName%~
			END
		END
		ELSE BEGIN
			LPM ~opcode_common_324~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_324~ BEGIN
	LOCAL_SET strref = 13240151

	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF NOT ~%resref%~ STRING_EQUAL_CASE ~%SOURCE_RES%~ AND parameter1 == 0 AND parameter2 = 0 BEGIN
			LPM ~opcode_self_probability_324~
		END
		ELSE BEGIN
			LPM ~opcode_common_324~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_common_324~ BEGIN
	LOCAL_SET value = parameter1
	LOCAL_SET statType = parameter2
	LOCAL_SET idsId = 0
	SET ignoreDuration = 1
	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%SOURCE_RES%~ BEGIN
			PATCH_IF (statType >= 102 AND statType <= 108) OR (statType >= 112 AND statType <= 118) BEGIN
				SET idsId = statType - 100
				SET strref = strref + 146 // ~Inefficace contre les %creatureType%~
				PATCH_IF (statType >= 112 AND statType <= 118) BEGIN
					SET idsId = statType - 110
					SET strref = strref + 147 // ~Effectif contre les %creatureType%~
				END
				LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%idsId%~ RET creatureType = idName END
			END
			ELSE BEGIN
				SET strref = strref + statType
			END
			LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
		END
		ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Immunité à une ressource (spl ou itm) différente de l'objet : %resref%~ END
		END
	END
END

/* ------------------------ *
 * Stat: Save vs. all [325] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_325~ BEGIN
	PATCH_IF parameter2 == 3 BEGIN
		SET parameter2 = MOD_TYPE_cumulative
	END
	LPF ~opcode_mod~ INT_VAR strref = 102034 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Jets de sauvegarde~
END

DEFINE_PATCH_MACRO ~opcode_target_325~ BEGIN
	PATCH_IF parameter2 == 3 BEGIN
		SET parameter2 = MOD_TYPE_cumulative
	END
	LPF ~opcode_target~ INT_VAR strref = 13250002 RET description END // ~les jets de sauvegarde~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_325~ BEGIN
	PATCH_IF parameter2 == 3 BEGIN
		SET parameter2 = MOD_TYPE_cumulative
	END
	LPF ~opcode_probability~ INT_VAR strref = 13250002 RET description END // ~les jets de sauvegarde~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_325~ BEGIN
	LPM ~opcode_self_probability_325~
END

/* ------------------------ *
 * Apply Effects List [326] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_326~ BEGIN
	SET ignoreDuration = 1
	LPM ~opcode_326_condition~

	LPF ~get_spell_description~ INT_VAR forcedProbability = probability STR_VAR file = EVAL ~%resref%~ theTarget ofTheTarget toTheTarget RET spellDescription count featureCount END

	PATCH_IF count == 1 AND featureCount == 1 BEGIN
		LPF ~get_single_spell_effect~ INT_VAR forcedProbability = probability STR_VAR file = EVAL ~%resref%~ theTarget ofTheTarget toTheTarget RET effectDescription END

		INNER_PATCH_SAVE description ~%effectDescription%~ BEGIN
			REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%- ~ ~~
		END
	END
    ELSE BEGIN
		INNER_PATCH_SAVE spellDescription ~%spellDescription%~ BEGIN
			REPLACE_TEXTUALLY CASE_INSENSITIVE ~%crlf%~ ~%crlf%  ~ // Indentation de la description du sort
		END
	    SPRINT description ~%spellDescription%~
    END
END

DEFINE_PATCH_MACRO ~opcode_target_326~ BEGIN
	LPM ~opcode_self_326~
END

DEFINE_PATCH_MACRO ~opcode_326_condition~ BEGIN
	LOCAL_SET strref = 13260000
	LOCAL_SET value = parameter1
	LOCAL_SET statType = parameter2
	LOCAL_SET idsId = 0
	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF (statType >= 102 AND statType <= 108) OR (statType >= 112 AND statType <= 118) BEGIN
			SET idsId = statType - 100
			SET strref = strref + 146 // ~Inefficace contre les %creatureType%~
			PATCH_IF (statType >= 112 AND statType <= 118) BEGIN
				SET idsId = statType - 110
				SET strref = strref + 147 // ~Effectif contre les %creatureType%~
			END
			LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%idsId%~ RET creatureType = idName END
		END
		ELSE BEGIN
			SET strref = strref + statType
		END
		LPF ~getTranslation~ INT_VAR strref opcode RET condition = string END
	END
END

/* ------------------------------- *
 * Spell Effect: Slow Poison [329] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_329~ BEGIN
	LOCAL_SET seconds = parameter1
	SPRINT description @13290001 // ~Force la plupart des poisons sur %theTarget% à agir toutes les %seconds% secondes~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_329~ BEGIN
	LOCAL_SET seconds = parameter1
	SPRINT description @13290002 // ~de forcer la plupart des poisons sur %theTarget% à agir toutes les %seconds% secondes~
END

DEFINE_PATCH_MACRO ~opcode_target_329~ BEGIN
	LPM ~opcode_self_329~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_329~ BEGIN
	LPM ~opcode_self_probability_329~
END

/* -------------------------------------- *
 * Summon: Random Monster Summoning [331] *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_331~ BEGIN
	LOCAL_SET strref = 13310001 // ~Invoque des créatures pour un total de %amount% niveaux (%creatures%)~
	LPM ~opcode_331_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_331~ BEGIN
	LOCAL_SET strref = 13310005 // ~d'invoquer des créatures pour un total de %amount% niveaux (%creatures%)~
	LPM ~opcode_331_common~
END

DEFINE_PATCH_MACRO ~opcode_331_common~ BEGIN
	LOCAL_SET amount    = parameter1
	LOCAL_SET type      = parameter2
	LOCAL_SET mode      = special
	LOCAL_SET isMonster = 1

	PATCH_IF ~%resref%~ STRING_EQUAL ~~ BEGIN
		INNER_PATCH_FILE ~smtables.2da~ BEGIN
			SET row = 1 + type
			READ_2DA_ENTRY row 0 2 id
			READ_2DA_ENTRY row 1 2 file
		END
	END
	ELSE BEGIN
		SPRINT file ~%resref%~
	END

	PATCH_IF (NOT isExternal AND mode == 0) OR mode == 1 BEGIN
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount = amount RET amount = damage END
		INNER_PATCH_SAVE amount ~%amount%~ BEGIN
			REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
		END
		SET strref += ~%amount%~ STRING_EQUAL ~1~ ? 2 : 3 // ~Invoque 1 créature (%creatures%)~
	END
	ELSE PATCH_IF mode == 2 BEGIN
		SET strref += 1 // ~Invoque des créatures pour un total de niveaux égal au niveau du lanceur (%creatures%)~
	END

	LPF ~get_creatures_names~ STR_VAR file RET creatures END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

/* ------------------------------------ *
 * Stat: Specific Damage Modifier [332] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_332~ BEGIN
	LOCAL_SET strref = 13320000 + parameter2
	LOCAL_SET value = parameter1

	LPF ~signed_value~ INT_VAR value RET value END
	LPF ~getTranslation~ INT_VAR strref opcode RET name = string END
	SPRINT value @10002 // ~%value% %~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

/* ---------------------------------------------- *
 * Spell Effect: Change Backstab Effect [340]     *
 * ---------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_340~ BEGIN
	SPRINT condition @13400001 // ~À chaque attaque sournoise~
	LPM ~opcode_341_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_340~ BEGIN
	LPM ~opcode_self_340~
END

DEFINE_PATCH_MACRO ~opcode_target_340~ BEGIN
	SPRINT condition @13400002 // ~À chaque attaque sournoise %ofTheTarget%~
	LPM ~opcode_341_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_340~ BEGIN
	LPM ~opcode_target_340~
END

/* ---------------------------------------------- *
 * Spell Effect: Change Critical Hit Effect [341] *
 * ---------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_341~ BEGIN
	//TODO: Gérer Weapon category ~À chaque coup critique provoqué avec des [épées]~
	//TODO: Gérer attack type ~À chaque coup critique [de mélée] provoqué avec des [épées]~
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT condition @13410001 // ~À chaque coup critique~
	END
	ELSE BEGIN
		SPRINT condition @13410003 // ~À chaque coup critique provoqué avec cette arme~
	END

	LPM ~opcode_341_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_341~ BEGIN
	LPM ~opcode_self_341~
END

DEFINE_PATCH_MACRO ~opcode_target_341~ BEGIN
	SPRINT condition @13410002 // ~À chaque coup critique %ofTheTarget%~
	LPM ~opcode_341_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_341~ BEGIN
	LPM ~opcode_target_341~
END

DEFINE_PATCH_MACRO ~opcode_341_common~ BEGIN
	SET abilityType = AbilityType_Combat
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	LPF ~get_spell_description~ STR_VAR file = EVAL ~%resref%~ RET spellDescription count featureCount END

	INNER_PATCH_SAVE spellDescription ~%spellDescription%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE ~%crlf%~ ~%crlf%  ~ // Indentation de la description du sort
	END

	PATCH_IF count == 1 AND featureCount == 1 BEGIN
		LPF ~get_single_spell_effect~ INT_VAR forcedProbability = probability STR_VAR file = EVAL ~%resref%~ RET effectDescription END

		INNER_PATCH_SAVE description ~%effectDescription%~ BEGIN
	        SPRINT regex @10009 // ~^[0-9]+ % de chance ~
			REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
		END
	END
	ELSE PATCH_IF ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description ~%description%%spellDescription%~
    END
    ELSE BEGIN
	    SPRINT description @12320001 // ~Lance le sort %spellName% sur %theTarget%~
    END
END

/* ------------- *
 * HP Swap [343] *
 * ------------- */
DEFINE_PATCH_MACRO ~opcode_self_343~ BEGIN
	LOCAL_SET mode = parameter2
	PATCH_IF mode == 0 BEGIN
		SPRINT description @13430002 // ~Échange les points de vie du porteur et de la cible, si ceux du porteur sont plus grands~
	END
	ELSE BEGIN
		SPRINT description @13430001 // ~Échange les points de vie du porteur et de la cible~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_343~ BEGIN
	LOCAL_SET mode = parameter2
	PATCH_IF mode == 0 BEGIN
		SPRINT description @13430004 // ~d'échanger les points de vie du porteur et de la cible, si ceux du porteur sont plus grands~
	END
	ELSE BEGIN
		SPRINT description @13430003 // ~d'échanger les points de vie du porteur et de la cible~
	END
END

/* ----------------------------------- *
 * Enchantment vs. creature type [344] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_344~ BEGIN
	//TODO: weaponSlot + weaponCategory
	LOCAL_SET strref = 13440001 // ~Enchantement~
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END
	SET value = special
	SET parameter2 = MOD_TYPE_cumulative
	LPM ~opcode_mod_base~
	SPRINT description @100009 // ~%name%%colon%%value% %versus%~
END

//TODO: 345: arme visée considérée comme une arme du type configuré...

/* --------------------------- *
 * Save vs. school bonus [346] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_346~ BEGIN
	LOCAL_SET strref = 13460010 + special
	LPF ~opcode_save_vs~ INT_VAR strref = EVAL ~%strref%~ STR_VAR value = EVAL ~%parameter1%~ RET description END // ~contre les sorts de l'école xxx~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_346~ BEGIN
	LOCAL_SET strref = 13460010 + special
	LPF ~getTranslation~ INT_VAR strref opcode RET versus = string END
	LPF ~opcode_probability~ INT_VAR strref = 10330002 RET description END // ~les jets de sauvegarde %versus%~
END

DEFINE_PATCH_MACRO ~opcode_target_346~ BEGIN
	LOCAL_SET strref = 13460010 + special
	LPF ~opcode_save_vs~ INT_VAR strref = EVAL ~%strref%~ STR_VAR value = EVAL ~%parameter1%~ target = 1 RET description END // ~contre les baguettes, les sceptres et les bâtons~
END

DEFINE_PATCH_MACRO ~opcode_party_346~ BEGIN
	LOCAL_SET strref = 13460010 + special
	LPF ~opcode_save_vs~ INT_VAR strref = EVAL ~%strref%~ STR_VAR value = EVAL ~%parameter1%~ group = 1 RET description END // ~contre les baguettes, les sceptres et les bâtons~
END

/* -------------------------------------------- *
 * Stat: Ignore Reputation Breaking Point [360] *
 * -------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_360~ BEGIN
	SPRINT description @13600001 // ~Ne quitte plus le groupe si la réputation ne convient pas %toTheTarget%~
END

/* --------------------------------- *
 * Cast spell on critical miss [361] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_361~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT condition @13610001 // ~À chaque échec critique~
	END
	ELSE BEGIN
		SPRINT condition @13610003 // ~À chaque échec critique provoqué avec cette arme~
	END

	LPM ~opcode_341_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_361~ BEGIN
	LPM ~opcode_self_361~
END

DEFINE_PATCH_MACRO ~opcode_target_361~ BEGIN
	SPRINT condition @13610002 // ~À chaque échec critique %ofTheTarget%~
	LPM ~opcode_341_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_361~ BEGIN
	LPM ~opcode_target_361~
END

/* ------------------------- *
 * Critical miss bonus [362] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_362~ BEGIN
	//TODO: Gérer attack type
	LOCAL_SET value = 5 * parameter1
	LPF ~signed_value~ INT_VAR value RET value END
	SPRINT value @10002 // ~%value% %~
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT name @13620002 // ~Chance d'échec critique avec cette arme~
	END
	ELSE BEGIN
		SPRINT name @13620001 // ~Chance d'échec critique~
	END
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_mod_base~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		PATCH_IF IS_AN_INT ~%value%~ BEGIN
			LPF ~signed_value~ INT_VAR value RET value END
		END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10010 // ~Passe à %value%~
	END
	ELSE BEGIN // percent
		PATCH_IF IS_AN_INT ~%value%~ BEGIN
			PATCH_IF value != 100 BEGIN
				SET value -= 100
				LPF ~signed_value~ INT_VAR value RET value END
				SPRINT value @10002 // ~%value% %~
			END
		END
		ELSE BEGIN
			// TODO !
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : dice % non gere : %value%~ END
			SPRINT value @10002 // ~%value% %~
		END
	END
	PATCH_IF NOT IS_AN_INT ~%value%~ OR value != 0 BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET name = string END
	END
END

DEFINE_PATCH_FUNCTION ~opcode_mod~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	parameter2 = parameter2 BAND 65535
	PATCH_IF parameter2 >= MOD_TYPE_cumulative AND parameter2 <= 3 BEGIN
		LPM ~opcode_mod_base~
		PATCH_IF NOT IS_AN_INT ~%value%~ OR value != 0 BEGIN
			SPRINT description @100001 // ~%name%%colon%%value%~
		END
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid value for parameter2 : %parameter2%~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_mod_percent_base~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		PATCH_IF IS_AN_INT ~%value%~ BEGIN
			LPF ~signed_value~ INT_VAR value RET value END
		END
		SPRINT value @10002 // ~%value% %~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10002 // ~%value% %~
		SPRINT value @10010 // ~Passe à %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN
		SPRINT value @10002 // ~%value% %~
		SPRINT value @10006 // ~Multiplié par %value%~
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET name = string END
END

DEFINE_PATCH_FUNCTION ~opcode_mod_percent~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	PATCH_IF parameter2 >= MOD_TYPE_cumulative AND parameter2 <= MOD_TYPE_percentage BEGIN
		LPM ~opcode_mod_percent_base~

		SPRINT description @100001 // ~%name%%colon%%value%~
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid value for parameter2 : %parameter2%~ END
	END
END

DEFINE_PATCH_FUNCTION ~opcode_target_percent~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	SET value = ~%parameter1%~
	LPF ~getTranslation~ INT_VAR strref opcode RET theStatistic = string END

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF value >= 0 OR NOT IS_AN_INT ~%value%~ BEGIN
			SPRINT value @10002 // ~%value% %~
	        SPRINT description @102286 // ~Augmente %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
			SPRINT value @10002 // ~%value% %~
	        SPRINT description @102285 // ~Réduit %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102287 // ~Passe %theStatistic% %ofTheTarget% à %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102288 // ~Multiplie %theStatistic% %ofTheTarget% par %value%~
	END
END

DEFINE_PATCH_FUNCTION ~opcode_probability_percent~ INT_VAR strref = 0 RET description BEGIN
	SET value = ~%parameter1%~
	LPF ~getTranslation~ INT_VAR strref opcode RET theStatistic = string END

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF value >= 0 OR NOT IS_AN_INT ~%value%~ BEGIN
			SPRINT value @10002 // ~%value% %~
	        SPRINT description @102544 // ~d'augmenter %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
			SPRINT value @10002 // ~%value% %~
	        SPRINT description @102543 // ~de réduire %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102545 // ~de passer %theStatistic% %ofTheTarget% à %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102546 // ~de multiplier %theStatistic% %ofTheTarget% par %value%~
	END
END

DEFINE_PATCH_FUNCTION ~opcode_save_vs~ INT_VAR strref = 0 group = 0 target = 0 STR_VAR value = ~~ RET description BEGIN
	SPRINT name @102034 // ~Jets de sauvegarde~

	PATCH_IF target == 1 OR group == 1 BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET versus = string END
		SPRINT theStatistic @10330002 // ~les jets de sauvegarde %versus%~

		PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
	        PATCH_IF value >= 0 OR NOT IS_AN_INT ~%value%~ BEGIN
		        SPRINT description @102286 // ~Augmente %theStatistic% %ofTheTarget% de %value%~
	        END
	        ELSE BEGIN
	            value = ABS value
		        SPRINT description @102285 // ~Réduit %theStatistic% %ofTheTarget% de %value%~
	        END
		END
		ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
			SPRINT description @102287 // ~Passe %theStatistic% %ofTheTarget% à %value%~
		END
		ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN // percent
			SPRINT value @10002 // ~%value% %~
			SPRINT description @102288 // ~Multiplie %theStatistic% %ofTheTarget% par %value%~
		END
	END
	ELSE BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET strSave = string END
		PATCH_IF parameter2 == MOD_TYPE_cumulative OR parameter2 == 3 BEGIN
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

		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END

DEFINE_PATCH_FUNCTION ~opcode_target~ INT_VAR strref = 0 RET description BEGIN
	SET value = ~%parameter1%~
	LPF ~getTranslation~ INT_VAR strref opcode RET theStatistic = string END

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF value >= 0 OR NOT IS_AN_INT ~%value%~ BEGIN
	        SPRINT description @102286 // ~Augmente %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
	        SPRINT description @102285 // ~Réduit %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102287 // ~Passe %theStatistic% %ofTheTarget% à %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102288 // ~Multiplie %theStatistic% %ofTheTarget% par %value%~
	END
END

DEFINE_PATCH_FUNCTION ~opcode_probability~ INT_VAR strref = 0 RET description BEGIN
	SET value = ~%parameter1%~
	LPF ~getTranslation~ INT_VAR strref opcode RET theStatistic = string END

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF value >= 0 OR NOT IS_AN_INT ~%value%~ BEGIN
	        SPRINT description @102544 // ~d'augmenter %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
	        SPRINT description @102543 // ~de réduire %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102545 // ~de passer %theStatistic% %ofTheTarget% à %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102546 // ~de multiplier %theStatistic% %ofTheTarget% par %value%~
	END
END

/* ----------------------------------------- *
 * Gestion des modifications des résistances *
 * ----------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_target_resist~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	TO_LOWER resistName

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF value >= 0 OR NOT IS_AN_INT ~%value%~ BEGIN
	        SPRINT value @10002 // ~%value% %~
	        SPRINT description @102282 // ~Augmente la %resistName% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
	        SPRINT value @10002 // ~%value% %~
	        SPRINT description @102281 // ~Réduit la %resistName% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
	    SPRINT value @10002 // ~%value% %~
		SPRINT description @102283 // ~Passe la %resistName% %ofTheTarget% à %value%~
	END
	ELSE BEGIN // percent
		SPRINT value @10002 // ~%value% %~
		SPRINT description @102284 // ~Multiplie la %resistName% %ofTheTarget% par %value%~
	END
END

/* --------------------------------------------------------- *
 * Gestion des modifications des résistances par probabilité *
 * --------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_probability_resist~ BEGIN
	LOCAL_SET value = ~%parameter1%~

	TO_LOWER resistName

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF value >= 0 OR NOT IS_AN_INT ~%value%~ BEGIN
	        SPRINT value @10002 // ~%value% %~
	        SPRINT description @102540 // ~d'augmenter la %resistName% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
	        SPRINT value @10002 // ~%value% %~
	        SPRINT description @102539 // ~de réduire la %resistName% %ofTheTarget% de %value%~
        END
    END
    ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
	    SPRINT value @10002 // ~%value% %~
        SPRINT description @102541 // ~de passer la %resistName% %ofTheTarget% à %value%~
    END
    ELSE BEGIN // percent
        SPRINT value @10002 // ~%value% %~
        SPRINT description @102542 // ~de multiplier la %resistName% %ofTheTarget% par %value%~
    END
END

DEFINE_PATCH_MACRO ~opcode_not_cumulative~ BEGIN
    SPRINT notCumulative @102682 // ~non cumulable~
    SPRINT description ~%description% (%notCumulative%)~
END

// Rajout d'un paramètre pour bloquer l'affichage du warning (dans le cas où l'objet n'a pas besoin d'exister (opcode 321))
DEFINE_PATCH_FUNCTION ~get_spell_name~ INT_VAR showWarning = 1 STR_VAR file = "" RET spellName BEGIN
	TO_LOWER file
	PATCH_IF VARIABLE_IS_SET $spellnames(~%file%~) BEGIN
		SET strref = $spellnames(~%file%~)
		LPF ~getTranslation~ INT_VAR strref opcode RET spellName = string END
	END
	ELSE BEGIN
		SPRINT spellName ~~
		SPRINT itemFilename ~%SOURCE_FILE%~
		PATCH_IF FILE_EXISTS_IN_GAME ~%file%.spl~ BEGIN
			INNER_PATCH_FILE ~%file%.spl~ BEGIN
				READ_LONG SPL_unidentified_name spellNameRef
				PATCH_IF spellNameRef > 0 BEGIN
					READ_STRREF SPL_unidentified_name spellName
				END
				ELSE BEGIN
					READ_LONG SPL_unidentified_description spellDescriptionRef
					PATCH_IF spellDescriptionRef > 0 BEGIN
						READ_STRREF SPL_unidentified_description spellDescription

						INNER_PATCH_SAVE spellName ~%spellDescription%~ BEGIN
							REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~\([ ]*%crlf%+.*\)~ ~~
							REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~[ ]*(.*)*~ ~~
						END
					END
				END
				/*
				PATCH_IF ~%spellName%~ STRING_EQUAL ~~ BEGIN
					LPF ~add_log_warning~ STR_VAR message = EVAL ~%itemFilename% : Opcode %opcode% : Nom du sort introuvable pour %file%.spl.~ END
				END
				*/
			END
		END
		ELSE PATCH_IF showWarning BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : La ressource %file%.spl n'existe pas.~ END
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_school~ INT_VAR school = 0 RET spellSchoolName BEGIN
	SET strref = 100100 + school
	LPF ~getTranslation~ INT_VAR strref opcode RET spellSchoolName = string END
END

DEFINE_PATCH_FUNCTION ~get_spell_secondary_type~ INT_VAR secondaryType = 0 RET spellSecondaryTypeName BEGIN
	SET strref = 100200 + secondaryType
	PATCH_IF secondaryType > 13 OR secondaryType < 0 BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: secondary type must be between 0 and 13 inclusive~ END
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET spellSecondaryTypeName = string END
END

// Rajout d'un paramètre pour bloquer l'affichage du warning (dans le cas où l'objet n'a pas besoin d'exister (opcode 321))
DEFINE_PATCH_FUNCTION ~get_item_name~ INT_VAR showWarning = 1 STR_VAR file = "" RET itemName BEGIN
	SPRINT itemName ~~
	SPRINT itemFilename ~%SOURCE_FILE%~
	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.itm~ BEGIN
		INNER_PATCH_FILE ~%file%.itm~ BEGIN
			READ_LONG SPL_unidentified_name itemNameRef
			PATCH_IF itemNameRef > 0 BEGIN
				READ_STRREF ITM_identified_name itemName
			END
			/*
			ELSE BEGIN
				LPF ~add_log_warning~ STR_VAR message = EVAL ~%itemFilename% : Opcode %opcode% : Nom de l'objet introuvable pour %file%.itm.~ END
			END
			*/
		END
	END
	ELSE PATCH_IF showWarning BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : La ressource %file%.itm n'existe pas.~ END
	END
END

DEFINE_PATCH_FUNCTION ~get_creature_name~ STR_VAR file = "" RET creatureName BEGIN
	SPRINT creatureName ~~
	SPRINT itemFilename ~%SOURCE_FILE%~
	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.cre~ BEGIN
		INNER_PATCH_FILE ~%file%.cre~ BEGIN
			READ_LONG CRE_name spellNameRef
			PATCH_IF spellNameRef > 0 BEGIN
				READ_STRREF CRE_name creatureName
			END
			/*
			ELSE BEGIN
				SPRINT creatureName @102549 // ~Créature inconnue~
				LPF ~add_log_warning~ STR_VAR message = EVAL ~%itemFilename% : Opcode %opcode% : Nom de la créature introuvable pour %file%.cre~ END
			END
			*/
		END
	END
	ELSE BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : La ressource %file%.cre n'existe pas.~ END
	END
END

DEFINE_PATCH_FUNCTION ~get_creatures_names~
	STR_VAR
		file = ~~
	RET
		creatures
BEGIN
	SPRINT creatures  ~~

	INNER_PATCH_FILE ~%file%.2da~ BEGIN
		COUNT_2DA_ROWS ~2~ ~rows~
		FOR (row = 1 ; row < rows ; row = row + 1) BEGIN
			READ_2DA_ENTRY row 0 2 id
			READ_2DA_ENTRY row 1 2 resref

			PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.cre~ BEGIN
				LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
				PATCH_IF NOT ~%creatureName%~ STRING_EQUAL ~~ BEGIN
					SPRINT creatures ~%creatures%, %creatureName%~
				END
			END
		END
	END

	INNER_PATCH_SAVE creatures ~%creatures%~ BEGIN
		SPRINT strOr @100004 // ~ou~
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~, \([^,]+\)$~ ~ %strOr% \1~
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^\(, \| %strOr% \)~ ~~
	END
END

DEFINE_PATCH_FUNCTION ~get_creature_allegiance~ STR_VAR file = "" RET allegiance BEGIN
	SPRINT creatureName ~~
	SPRINT allegiance ~~
	SPRINT itemFilename ~%SOURCE_FILE%~
	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.cre~ BEGIN
		INNER_PATCH_FILE ~%file%.cre~ BEGIN
			READ_BYTE CRE_allegiance allegiance
			// Retiré car la valeur numérique est bien plus exploitable que son équivalent str
			// LOOKUP_IDS_SYMBOL_OF_INT allegiance EA allegiance
		END
	END
	ELSE BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : La ressource %file%.cre n'existe pas.~ END
	END
END

DEFINE_PATCH_FUNCTION ~opcode_self_42_62~ INT_VAR level = 0 amount = 0 startStrref = 0 RET description BEGIN
	SPRINT levelStr ~~

	PATCH_IF amount > 32768 BEGIN
		SET amount = amount - 65536
	END

	PATCH_IF level == 0 BEGIN
		// Double le nombre de sorts de niveau amount et moins (pas de binaire ici !)
		PATCH_IF amount > 0 AND amount <= spellLevelMax BEGIN
			LPM ~opcode_self_42_62_get_levelstr~
			SET strref = startStrref + 4
			LPF ~getTranslation~ INT_VAR strref opcode RET description = string END //~Double le nombre de sorts [profanes|divins] mémorisables de niveau inférieur ou égal à %levelStr%~
		END
		ELSE BEGIN
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid parameter1/parameter2 %amount%/%level%~ END
		END
	END
	ELSE PATCH_IF level == 512 BEGIN
		// Double le niveau de sorts de niveau amount
		PATCH_IF amount > 0 AND amount <= spellLevelMax BEGIN
			SPRINT levelStr ~%amount%~
			SET strref = startStrref + 4
			LPF ~getTranslation~ INT_VAR strref opcode RET description = string END //~Double le nombre de sorts [profanes|divins] mémorisables de niveau inférieur ou égal à %levelStr%~
		END
		ELSE BEGIN
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid parameter1/parameter2 %amount%/%level%~ END
		END
	END
	ELSE BEGIN
		LPM ~opcode_self_42_62_get_levelstr~
		PATCH_IF amount > 0 BEGIN // Mémorisation
			SET strref = amount == 1 ? startStrref: (startStrref+1)
        END
        ELSE PATCH_IF amount < 0 BEGIN // Oubli
			SET strref = amount == ~-1~ ? (startStrref + 2): (startStrref + 3)
    	END
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Suppression de %amount% sorts [profanes|divins] de niveau %levelStr%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_42_62_get_levelstr~ BEGIN
	PATCH_IF level == 0 BEGIN
		FOR (i = 1 ; i <= amount ; ++i) BEGIN
			SPRINT levelStr ~%levelStr%, %i%~
		END
	END
	ELSE BEGIN
		FOR (idx = 0 ; idx < spellLevelMax ; ++idx) BEGIN
			SET bit = EVAL ~%BIT%idx%%~
			PATCH_IF (level BAND bit) != 0 BEGIN
				SET spellLevel = idx + 1
				SPRINT levelStr ~%levelStr%, %spellLevel%~
			END
		END
	END

	INNER_PATCH_SAVE levelStr ~%levelStr%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~, \([0-9]\)$~ ~ et \1~
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^\(, \| et \)~ ~~
	END
END

DEFINE_PATCH_FUNCTION ~get_ids_name~ INT_VAR entry = 0 file = 0 RET idName BEGIN
	SPRINT idName ~~

	PATCH_IF file == 9 BEGIN
		LPF ~TO_HEX_NUMBER~ INT_VAR value = entry prefix = 1 minDigits = 8 RET entryHex = hexNumber END
		PATCH_IF VARIABLE_IS_SET $kits(~%entryHex%~) BEGIN
			SPRINT idName $kits(~%entryHex%~)
		END
		ELSE BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Kit utilise n'existe pas : %entry% : %entryHex%~ END
		END
	END
	ELSE PATCH_IF VARIABLE_IS_SET $ids_files(~%file%~) BEGIN
		SPRINT idsFile $ids_files(~%file%~)
		LOOKUP_IDS_SYMBOL_OF_INT idsEntry ~%idsFile%~ ~%entry%~
		PATCH_IF ~%entry%~ STRING_EQUAL ~%idsEntry%~ BEGIN
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid ids entry : %idsFile%.ids (%idsEntry%)~ END
		END
		ELSE BEGIN
			SET strref = 200000 + (file * 1000) + entry
			LPF ~getTranslation~ INT_VAR strref opcode RET idName = string END
		END
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Wrong ids file : %file%~ END
	END
END


DEFINE_PATCH_FUNCTION ~get_ids_versus_name~ INT_VAR entry = 0 file = 0 RET idVersusName BEGIN
	SPRINT idVersusName ~~
	PATCH_IF VARIABLE_IS_SET $ids_files(~%file%~) BEGIN
		LPF ~get_ids_name~ INT_VAR entry file RET targetType = idName END

		SPRINT idVersusName @102387 // ~contre les %targetType%~
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Wrong ids file : %file%~ END
	END
END

/* ========================================= *
 * Fonctions qui gèrent les cas particuliers *
 * ========================================= */

/* ------------------------ *
 * Item revision v4 beta 10 *
 * ------------------------ */
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcode_target_146_item_revision~ BEGIN
	// Item revision
	DVAFFLIC => 102495 // ~Ralentit et inflige 1 point de dégât à la cible toutes les 3 secondes pendants 4 rounds (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	DVBANISH => 102483 // ~Détruit les créatures convoquées~
	DVBLEED0 => 102519 // ~Inflige 1 point de dégâts de poison à la cible à chaque round pendant 1 tour~
	DVBLEED2 => 102509 // ~Inflige 1 point de dégâts de poison à la cible à chaque round pendant 2 rounds~
	DVBLEED5 => 102507 // ~Inflige 1 point de dégâts de poison à la cible à chaque round pendant 5 rounds~
	DVBONEBR => 102482 // ~Réduit les points de vie maximum des créatures vertébrées de 3 pendant 1 tour~
	DVBOOM   => 102500 // ~Étourdit %theTarget% durant 1 round (jet de sauvegarde contre les sorts pour éviter)~
	DVBRAM   => 102502 // ~Inflige 2d6 points de dégâts contondants supplémentaires à la cible, la renverse et la sonne pendant 1 round (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	DVBRNWND => 102518 // ~Réduit le TAC0 de la cible de 1 et inflige 1 point de dégâts de feu supplémentaire à chaque round pendant 3 rounds (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	DVCUTTHR => 102523 // ~Réduit au silence et inflige 1 point de dégâts de poison toutes les 3 secondes à la cible pendant 3 rounds (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	DVDISPEL => 102487 // ~Dissipation de la magie (jet de sauvegarde contre les sorts pour éviter)~
	DVDOOM   => 102503 // ~Réduit les jets de sauvegarde, le TAC0 et les dégâts de la cible de 1 pendant 4 rounds (jet de sauvegarde contre les sorts pour éviter)~
	DVENFEBL => 102516 // ~Ralentit et réduit le TAC0 et la classe d'armure de la cible de 1 pendant 1 round (jet de sauvegarde contre les sorts pour éviter)~
	DVFFIRE  => 102522 // ~Réduit la classe d'armure de la cible de 2 et l'empêche de se cacher pendant 4 rounds (jet de sauvegarde contre les sorts pour éviter)~
	DVFLWHIP => 102484 // ~Emprisonne %theTarget% dans les flammes pendant 2 rounds (jet de sauvegarde contre les souffles pour éviter)~
	DVFRBOLT => 102494 // ~Inflige 2d6 points de dégâts de feu supplémentaires aux adversaires dans un rayon de 1,50 mètre (jet de sauvegarde contre les souffles pour moitié)~
	DVHOLDUN => 102524 // ~Immobilise les cibles mort-vivantes pendant 2 rounds (jet de sauvegarde contre les sorts pour éviter)~
	DVKNBACK => 102492 // ~Renverse et sonne %theTarget% (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	DVNAMARR => 102520 // ~Réduit au silence %theTarget% ainsi que les adversaires dans un rayon de 4,5 mètres pendant 2 rounds (jet de sauvegarde contre les sorts pour éviter)~
	DVPIN    => 102529 // ~Immobilise et inflige 1d4 +5 points de dégâts perforants supplémentaires à chaque round à la cible pendant 2 rounds (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	DVSHARP  => 102499 // ~Réduit la force et la dextérité de 1 pendant 5 rounds (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	DVSINGSW => 102517 // ~Augmente le TAC0, les dégâts et les jets de sauvegarde contre les sorts des alliés dans un rayon de 6 mètres de 1~ // !!! La définition dans l'objet semble erronée si on regarde le sort dans DLTC (range à 1) (à teser !)
	DVSPABSR => 102496 // ~Fait oublier 1 sort profane à la cible tandis que le porteur se remémore 1 sort de niveau 4 maximum (jet de sauvegarde contre les sorts pour éviter)~
	DVSPDRNK => 102521 // ~Fait oublier 1 sort profane à la cible tandis que les points de vie du porteur sont augmentés de 2 pendant 1 heure (jet de sauvegarde contre les sorts pour éviter)~
	DVSTAG   => 102505 // ~Passe l'attaque par round de la cible à une demi et réduit sa vitesse d'incantation des sorts de 4 pendant 1 round (jet de sauvegarde contre les souffles pour éviter)~
	DVSTUN   => 102500 // ~Étourdit %theTarget% durant 1 round (jet de sauvegarde contre les sorts pour éviter)~
	DVSUNDER => 102486 // ~Réduit la classe d'armure de la cible de 1 pendant 2 rounds~
	DVTHCLAP => 102531 // ~Etourdit les adversaires dans un rayon d'1,50 mètre pendant 1 round (jet de sauvegarde contre les souffles pour éviter)~
	DVVAMPIR => 102485 // ~Draîne 1d4 points de vie si la cible possède du sang et les transfère au porteur~
	// Autres
	DVFEARSM => 102604 //
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcode_target_probability_146_item_revision~ BEGIN
	// Item revision
	DVCHILL  => 102490 // ~de ralentir %theTarget% pendant 3 rounds (jet de sauvegarde contre les sorts pour éviter)~
	DVCORROS => 102533 // ~de réduire la classe d'armure de la cible de 1 pendant 2 rounds~
	DVCRIPPL => 102511 // ~de réduire de moitié la vitesse de déplacement de la cible pendant 4 rounds~
	DVDETON  => 102514 // ~d'infliger 6d6 points de dégâts de feu à la cible et aux adversaires dans un rayon de 1,50 mètre~
	DVFEARSM => 102489 // ~d'infliger Horreur à la cible pendant 2 rounds (jet de sauvegarde contre les sorts pour éviter)~
	DVFLBRST => 102501 // ~d'infliger 4d6 points de dégâts de feu supplémentaires à la cible ainsi qu'aux adversaires dans un rayon de 1,50 mètre~
	DVFREEZE => 102488 // ~d’immobiliser %theTarget% pendant 1 round (jet de sauvegarde contre la pétrification et la métamorphose pour éviter)~
	DVHOPLES => 102506 // ~de réduire le TAC0 et la classe d'armure de la cible de 2 pendant 5 rounds (jet de sauvegarde contre les sorts pour éviter)~
	DVHSEEK  => 102513 // ~de tuer instantanément %theTarget% (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	DVHSMITE => 102532 // ~d'infliger 5d4 points de dégâts magiques, et d'aveugler %theTarget% pendant 1 round (jet de sauvegarde contre les sorts pour éviter)~
	DVILLBAN => 102512 // ~de dissiper les protections et les invocations illusoires~
	DVMINDBR => 102497 // ~d'infliger Débilité mentale à la cible (jet de sauvegarde contre les sorts à -4 pour éviter)~
	DVPRLYZE => 102498 // ~de paralyser %theTarget% pendant 2 rounds (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	DVRESON  => 102534 // ~d'infliger 4d4 points de dégâts contondants aux adversaires dans un rayon de 3 mètres~
	DVSBURST => 102530 // ~d'infliger 4d4 points de dégâts contondants aux adversaires dans un rayon de 3 mètres et de les étourdir pendant 1 round (jet de sauvegarde contre les sorts pour éviter d'être étourdi)~
	DVSHAKE  => 102528 // ~de renverser %theTarget% et les adversaires dans un rayon d'1,50 mètre pendant 1 round (jet de sauvegarde contre les souffles pour éviter)~
	DVSLEEP  => 102493 // ~d'endormir %theTarget% pendant 2 rounds (jet de sauvegarde contre les sorts pour éviter)~
	DVSTDUST => 102508 // ~d'aveugler tous les adversaires dans un rayon de 1,50 mètre pendant 4 rounds (jet de sauvegarde contre les souffles à -4 pour éviter)~
	DVSTNHLD => 102525 // ~de pétrifier %theTarget% pendant 2 rounds (jet de sauvegarde contre la pétrification et la métamorphose pour éviter)~
	DVSWAVE  => 102504 // ~de renverser, de sonner et d'infliger 4d6 points de dégâts contondants supplémentaires à la cible ainsi qu'aux adversaires dans un rayon de 1,50 mètre (jet de sauvegarde contre les souffles pour éviter d'être renversé et sonné)~
	DVTHCLAP => 102527 // ~d'étourdir %theTarget% et les adversaires dans un rayon d'1,50 mètre pendant 1 round (jet de sauvegarde contre les souffles pour éviter)~
	DVVORPAL => 102491 // ~de décapiter %theTarget% (jet de sauvegarde contre la paralysie, la mort et les poisons à -2 pour éviter)~
	DVVTRSPH => 102515 // ~d'infliger 4d4 points de dégâts d'acide à la cible et aux adversaires dans un rayon de 1,50 mètre~
	DVWEB    => 102510 // ~d'entoiler %theTarget% pendant 2 rounds (jet de sauvegarde contre les souffles pour éviter)~
	DVWHIRLS => 102526 // ~d'infliger 1d6 +2 points de dégâts contondants aux adversaires dans un rayon d'1,50 mètre~
	// Autres
	RR#WEAR  => 10020001 // ~d'endormir %theTarget% (jet de sauvegarde contre la paralysie, la mort et les poisons pour éviter)~
	RR#BBOW  => 102602 // ~d'aveugler %theTarget% pendant 3 rounds (jet de sauvegarde contre les sorts pour éviter, les spectateurs ont une pénalité de -5)~
	RR#SCAXE => 102603 // ~d'étourdir la cible pendant 1 round~
END

/* ----------------------------------------------------------------------------------- *
 * Gestion de la pénalité à la vitesse d'incantation sur les armures ajoutée par IR v4 *
 * ----------------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~opcode_self_177_item_revision_casting_penality~ RET description forceSort sort BEGIN
	SET forceSort = 0
	SET sort = 0
	SPRINT description ~~
	INNER_PATCH_SAVE value ~%resref%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~\(.*\)\([0-9]+\)$~ ~-\2~
	END
	PATCH_IF parameter1 == 1 BEGIN // mage
		SET forceSort = 1
		SET sort = $sort_opcodes(~189~) // Après Stat: Casting Time Modifier [189]
		SET parameter2 = MOD_TYPE_cumulative
		LPF ~opcode_mod~ INT_VAR strref = 102478 STR_VAR value RET description END // ~Vitesse d'incantation des sorts profanes~
		SET exceptBards = 1
        INNER_PATCH_FILE ~%SOURCE_FILE%~ BEGIN
            GET_OFFSET_ARRAY blockOffsets_177 ITM_V10_GEN_EFFECTS
            PHP_EACH blockOffsets_177 AS int => blockOffset_177 BEGIN
                READ_SHORT (blockOffset_177)                  opcode_177
                READ_BYTE  (blockOffset_177 + EFF_parameter1) parameter1_177
                READ_ASCII (blockOffset_177 + EFF_resref_key) resref_177
                PATCH_IF opcode_177 == 177 AND ~%resref_177%~ STRING_MATCHES_REGEXP ~^AG#IRS~ == 0 AND parameter1_177 == 5 BEGIN // Barde
                    SET exceptBards = 0
                END
            END
        END
        PATCH_IF exceptBards == 1 BEGIN
            SPRINT except @102480 // ~excepté pour les bardes~
            SPRINT description ~%description% (%except%)~
        END
	END
	ELSE PATCH_IF parameter1 == 3 BEGIN // clerc
		SET forceSort = 1
		SET sort = 35
		SET parameter2 = MOD_TYPE_cumulative
		LPF ~opcode_mod~ INT_VAR strref = 102479 STR_VAR value RET description END // ~Vitesse d'incantation des sorts divins~
	END
END


// Macro pour opcode de modificateur de caractéristiques
DEFINE_PATCH_MACRO ~opcode_modstat_is_valid~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative AND parameter1 == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No change detected: Value = Value + 0.~ END
	END
	PATCH_IF parameter2 == MOD_TYPE_percentage AND parameter1 == 100 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No change detected: Value = Value * 100 / 100.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_modstat2_is_valid~ BEGIN
	LPM ~opcode_modstat_is_valid~
	PATCH_IF parameter2 < MOD_TYPE_cumulative OR parameter2 > MOD_TYPE_percentage BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %parameter2%.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_modstat3_is_valid~ BEGIN
	LPM ~opcode_modstat_is_valid~
	PATCH_IF parameter2 < MOD_TYPE_cumulative OR parameter2 > 3 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %parameter2%.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_idscheck_is_valid~ BEGIN
	LPM ~opcode_modstat_is_valid~
	PATCH_IF parameter2 < 2 OR parameter2 > 9 OR (parameter2 > 8 AND is_ee == 0) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown IDS file %parameter2%.~ END
	END
END
