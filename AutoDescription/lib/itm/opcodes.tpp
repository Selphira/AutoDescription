/*
 * Tableau servant à savoir comment trier le résultat final.
 * Vu qu'ils ne sont généralement pas
 */
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~sort_opcodes~ BEGIN

	135 => 1   // Polymorph into Specific [135]
	318 => 2   // Protection: Immunity Spell [318]
	324 => 3   // Protection: Immunity to Resource and Message [324]

	519 => 4   // Arme brisée [519]
	112 => 5   // Item: Item Remove [112]
	123 => 6   // Item: Remove Inventory Item [123]
	264 => 7   // Spell Effect: Drop Weapons in Panic [264]

	// Modification des stats longue durée
	283 => 10   // Use EFF File (Cursed) [283]
	360 => 11   // Stat: Ignore Reputation Breaking Point [360]
    214 => 12   // Select Spell [214]
	 96 => 13   // Stat: Level Change [96]
	233 => 14   // Stat: Proficiency [233]
    191 => 15   // Spell: Casting Level Modifier [191]
	507 => 16   // Emplacement sorts profanes [507]
	 42 => 17   // Spell: Wizard Spell Slots Modifier [42]
	508 => 18   // Emplacement sorts divins [508]
	 62 => 19   // Spell: Priest Spell Slots Modifier [62]
	261 => 20   // Spell: Restore Lost Spells [261]
	510 => 21   // Spell: Restore Lost Spells (cumulative) [510]

	// Modification des stats

	 12 => 22  // HP: Damage [12]
	 78 => 23  // State: Disease [78]
	 25 => 24  // State: Poison [25]

	345 => 30  // Enchantment bonus [345]
	344 => 31  // Enchantment vs. creature type [344]
	216 => 32  // Spell Effect: Level Drain [216]
	246 => 33  // Spell Effect: Berserking [246]
	  0 => 34  // Stat: AC vs. Damage Type Modifier [0]
	506 => 35  // Stat: Classe d'armure cumulable
 219000 => 36  // Stat: AC vs. Creature Type Modifier [219]
	521 => 37  // Protection: Aucune protection [521]

	  1 => 38  // Stat: Attacks Per Round Modifier [1]

	301 => 40  // Stat: Critical Hit Modifier [301]
	362 => 41  // Critical miss bonus [362]
     73 => 42  // Stat: Extra Damage Modifier [73]
	179 => 43  // Spell Effect: Damage vs. Creature Type Modifier [179]
	285 => 44  // Stat: Melee Weapon Damage Modifier [285]
	286 => 45  // Stat: Missile Weapon Damage Modifier [286]
	289 => 46  // Stat: Fist Damage Modifier [289]
	263 => 47  // Stat: Backstab [263]
	332 => 48  // Stat: Specific Damage Modifier [332] : EE only
	250 => 49  // Spell Effect: Damage Luck Modifier [250]

	 54 => 60  // Stat: THAC0 Modifier [54]
	278 => 61  // Stat: To Hit Modifier [278]
	178 => 62  // Spell Effect: THAC0 vs. Creature Type Modifier [178]
	306 => 63  // Stat: THAC0 Modifier (On-Hand) [306]
	305 => 64  // Stat: THAC0 Modifier (Off-Hand) [305]
	284 => 65  // Stat: Melee THAC0 Modifier [284]
	167 => 66  // Stat: THAC0 Modifier with Missile Weapons [167]
	288 => 67  // Stat: Fist THAC0 Modifier [288]

	325 => 70  // Stat: Save vs. all [325]
 219001 => 71  // Stat: JS vs. Creature Type Modifier [219]
	 33 => 72  // Stat: Save vs. Death Modifier [33]
	 34 => 73  // Stat: Save vs. Wands Modifier [34]
	 35 => 74  // Stat: Save vs. Petrification/Polymorph Modifier [35]
	 36 => 75  // Stat: Save vs. Breath Weapons Modifier [36]
	 37 => 76  // Stat: Save vs. Spells Modifier [37]
	346 => 77  // Save vs. school bonus [346]

	126 => 80  // Stat: Movement Modifier [126]
	176 => 81  // Stat: Movement Modifier (II) [176]

	 18 => 82  // Stat: Maximum HP Modifier [18]
	 98 => 83  // Stat: Regeneration [98]
	 17 => 84  // Stat: Current HP Modifier [17]
	343 => 85  // HP Swap [343]
	208 => 86  // Stat: Minimum HP Limit [208]

	299 => 90  // Spell Effect: Chaos Shield [299]

	 99 => 91  // Spell Effect: Duration Modifier [99]
	 60 => 92  // Stat: Miscast Magic [60]
	189 => 93  // Stat: Casting Time Modifier [189]
	190 => 94  // Stat: Attack Speed Factor [190]

	501 => 100  // Stat: Caractéristiques [501]
	132 => 101  // State: Raise Strength, Constitution, & Dexterity Non-Cumulative [132]
	 44 => 102  // Stat: Strength Modifier [44]
	 97 => 103  // Stat: Strength-Bonus Modifier [97]
	 15 => 104  // Stat: Dexterity Modifier [15]
	 10 => 105  // Stat: Constitution Modifier [10]
	 19 => 106  // Stat: Intelligence Modifier [19]
	 49 => 107  // Stat: Wisdom Modifier [49]
	  6 => 108  // Stat: Charisma Modifier [6]
	523 => 109  // Stat: Bonus force [523]

	 22 => 110  // Stat: Luck Modifier [22]
	133 => 111  // Spell Effect: Luck Non-Cumulative [133]
	131 => 112  // State: Positive Chant [131]
	137 => 113  // State: Negative Chant [137]

	500 => 120  // Stat: Compétences de voleur [500]
	 92 => 121  // Stat: Pick Pockets Modifier [92]
	 90 => 122  // Stat: Open Locks Modifier [90]
	276 => 123  // Stat: Detect Illusion Modifier [276]
	 91 => 124  // Stat: Find Traps Modifier [91]
	277 => 125 // Stat: Set Traps Modifier [277]
	275 => 126 // Stat: Hide in Shadows Modifier [275]
	 59 => 127 // Stat: Stealth Modifier [59]


	// Invocation

	 67 => 130 // Summon: Creature Summoning [67]
	127 => 131 // Summon: Monster Summoning [127]
	331 => 132 // Summon: Random Monster Summoning [331]
	151 => 133 // Summon: Replace Creature [151]

	// Dissipation

	304 => 199 // Mass Raise Dead [304]
	 58 => 200 // Cure: Dispellable Effects (Dispel Magic) [58]
	 32 => 201 // Cure: Death (Raise Dead) [32]
	 43 => 201 // Cure: Stone to Flesh [43]
	 14 => 202 // Graphics: Defrost [14]
	 224 => 203 // Cure: Level Drain (Restoration) [224]
	337 => 203 // Remove: Opcode [337]
	 46 => 204 // Cure: Stun (Unstun) [46]
    162 => 205 // Cure: Hold [162]
	270 => 205 // Cure: Unpause Target [270]
	 77 => 206 // Cure: Feeblemindedness [77]
	 79 => 207 // Cure: Disease [79]
	 11 => 208 // Cure: Poison [11]
    242 => 209 // Cure: Confusion [242]
	161 => 210 // Cure: Fear [161]
	  4 => 211 // Cure: Berserking [4]
	  2 => 212 // Cure: Sleep [2]
	 48 => 213 // Cure: Silence (Vocalize) [48]
	 75 => 214 // Cure: Blindness [75]
	 81 => 215 // Cure: Deafness [81]
    160 => 216 // Remove Sanctuary [160]
	 47 => 217 // Cure: Invisibility [47]
    116 => 218 // Cure: (Remove) Invisibility [116]
    164 => 219 // Cure: Drunkeness [164]
	 70 => 220 // Cure: Non-Detection [2]
	 64 => 221 // State: Remove Infravision [64]
	220 => 223 // Removal: Remove School [220]
	221 => 224 // Removal: Remove Secondary Type [221]
	511 => 224 // Dissipe toutes les illusions [511]
	229 => 225 // Removal: Remove One School [229]
	230 => 226 // Removal: Remove One Secondary Type [230]
	273 => 227 // Remove: Specific Area Effect(Zone of Sweet Air) [273]
	266 => 228 // Spell: Remove Protection from Spell [266]

	// Absorption

	259 => 238 // Protection: Spell Trap [259]

	// Renvoi

	198 => 239 // Spell: Bounce (by Opcode) [198]
	199 => 240 // Spell: Bounce Spells [199]
	200 => 241 // Spell: Decrementing Bounce Spells [200]
	202 => 242 // Spell: Bounce (by School) [202]
	203 => 243 // Spell: Bounce (by Secondary Type) [203]
	227 => 244 // Spell: Bounce (by School, decrementing) [227]
	228 => 245 // Spell: Bounce (by Secondary Type, decrementing) [228]
	197 => 246 // Spell: Bounce Projectile [197]
	207 => 247 // Spell: Bounce Specified Spell [207]

	// Cas particulier peut dissiper comme immuniser
	321 => 248 // Removal: Effects specified by Resource [321]

	// Les immunités
	509 => 249 // Protection: from Spell Levels (cumulable) [509]
	102 => 250 // Protection: from Spell Levels [102]
	201 => 251 // Spell: Decrementing Spell Immunity [201]
	204 => 252 // Spell: Protection from Spell (School) [204]
	205 => 253 // Spell: Protection from Spell (Secondary Type) [205]
	223 => 254 // Spell: Immunity (by School, decrementing [223]
	226 => 255 // Spell: Immunity (by Secondary Type, decrementing) [226]
	206 => 256 // Spell: Protection from Spell [206]
	518 => 256 // Fake: Immunité aux sorts [518]

	367 => 279 // Minimum base stats [367]
	100 => 280 // Protection: from Creature Type [100]
	120 => 281 // Protection: from Melee Weapons [120]
	 83 => 282 // Protection: From Projectile (Any) [83]
    101 => 283 // Protection: from Opcode [101]
	163 => 284 // Protection: Free Action [163]
	520 => 285 // Protection: Action libre [520]
    505 => 286 // Protection contre les capacités psioniques
	292 => 287 // Protection: Backstab [292]
	310 => 288 // Protection: from Timestop [310]
	212 => 289 // Protection: Freedom [212]
	 69 => 290 // Protection: From Detection (Non-Detection) [69]
	295 => 291 // Graphics: Disable Permanent Death [295]

	// Les résistances qui peuvent être des immunités

	106 => 299 // Stat: Morale Break [106]
    502 => 300 // Stat: Résistance aux dégâts [502]
    503 => 301 // Stat: Résistance aux dégâts élémentaires [503]
    504 => 302 // Stat: Résistance aux dégâts physiques [504]
	166 => 303 // Stat: Magic Resistance Modifier [166]
	 30 => 304 // Stat: Fire Resistance Modifier [30]
	 28 => 305 // Stat: Cold Resistance Modifier [28]
	 29 => 306 // Stat: Electricity Resistance Modifier [29]
	 27 => 308 // Stat: Acid Resistance Modifier [27]
	 31 => 309 // Stat: Magic Damage Resistance Modifier [31]
	 84 => 310 // Stat: Reduced Damage from Magical Fire Modifier [84]
	 85 => 311 // Stat: Reduced Damage from Magical Cold Modifier [85]
	 86 => 312 // Stat: Reduced Damage from Slashing Modifier [86]
	 87 => 313 // Stat: Reduced Damage from Crushing Modifier [87]
	 88 => 314 // Stat: Reduced Damage from Piercing Modifier [88]
	 89 => 315 // Stat: Reduced Damage from Missiles Modifier [89]
	173 => 316 // Stat: Poison Resistance Modifier [173]


	// Les états

	231 => 350 // Spell Effect: Time Stop [231]
	 13 => 351 // Death: Instant Death [13]
	 55 => 352 // Death: Kill Creature Type [55]
	238 => 353 // Death: Disintegrate [238]
	 68 => 354 // Summon: Unsummon Creature [68]
	209 => 355 // Death: Kill 60HP [209]
	211 => 366 // Spell Effect: Imprisonment [211]
	213 => 367 // Spell Effect: Maze [213]
	134 => 368 // State: Petrification [134]
	  5 => 369 // Charm: Charm Specific Creature [5]
	241 => 369 // Charm: Control Creature [241]
	 45 => 370 // State: Stun [45]
	210 => 371 // Spell Effect: Stun 90HP [210]
	109 => 372 // State: Hold Creature I [109]
	175 => 372 // State: Hold Creature II [175]
	185 => 372 // State: Hold Creature III [185]
	157 => 373 // State: Web Effect [157]
	165 => 373 // Spell Effect: Pause Target [165]
	154 => 374 // Overlay: Entangle [154]
	244 => 376 // Spell: Drain Wizard Spell [244]
	 39 => 377 // State: Unconsciousness [39]
	217 => 378 // Spell Effect: Unconsciousness 20HP [217]
	128 => 379 // State: Confusion [128]
	  3 => 380 // State: Berserking [3]
	247 => 381 // Spell Effect: Attack Nearest Creature [247]
	 76 => 383 // State: Feeblemindedness [76]
	 16 => 384 // State: Haste [16]
	317 => 385 // State: Haste2 [317]
	 40 => 386 // State: Slow [40]
	 20 => 388 // State: Invisibility [20]
	130 => 389 // State: Bless [130]
	129 => 390 // State: Aid [129]
	 65 => 391 // State: Blur [65]
	 63 => 392 // State: Infravision [63]
	 24 => 393 // State: Horror [24]
	 38 => 394 // State: Silence [38]
	 80 => 395 // Deafness [80]
	 74 => 396 // State: Blindness [74]
	136 => 397 // State: Force Visible [136]
	153 => 398 // Overlay: Sanctuary [153]
	329 => 399 // Spell Effect: Slow Poison [329] : EE only

	303 => 400 // Spell Effect: Backstab Every Hit [303]
	188 => 401 // Spell Effect: Aura Cleansing [188]
	119 => 402 // Spell Effect: Mirror Image [119]
	159 => 403 // Spell Effect: Mirror Image (Exact Number) [159]
	280 => 404 // Spell Effect: Wild Magic [280]
	193 => 405 // Spell Effect: Invisible Detection by Script [193]
	218 => 406 // Protection: Stoneskin [218]
	314 => 407 // Spell: Golem Stoneskin [314]

	281 => 420 // Stat: Wild Magic [281]
	323 => 421 // Stat: Turn Undead Level [323]
	 23 => 422 // Stat: Morale Modifier [23]
	104 => 424 // Stat: Experience Points [104]
	 21 => 425 // Stat: Lore Modifier [21]
	262 => 426 // Stat: Visual Range [262]
	 93 => 427 // Stat: Fatigue Modifier [93]
	108 => 428 // Stat: Reputation [108]
	 94 => 429 // Stat: Drunkenness Modifier [94]
	 95 => 430 // Stat: Tracking Skill Modifier [95]
	105 => 431 // Stat: Gold [105]
	245 => 432 // Check For Berserk [245]

	235 => 450 // Spell Effect: Wing Buffet [235]
	239 => 451 // Spell Effect: Farsight [239]
	125 => 452 // Spell Effect: Unlock (Knock) [125]
	124 => 453 // Spell Effect: Teleport (Dimension Door) [124]
	274 => 454 // Spell Effect: Teleport to Target [274]
	222 => 455 // Spell Effect: Teleport Field [222]
	150 => 456 // Spell Effect: Find Traps [150]
	268 => 457 // Spell Effect: Explore (Wizard Eye) [268]
	117 => 458 // Spell Effect: Reveal Area [117]
	236 => 459 // Spell Effect: Image Projection [236]
	316 => 460 // Spell: Magical Rest [316]
	115 => 461 // Detect: Alignment [115]
	 57 => 462 // Alignment: Change [57]
	 56 => 463 // Alignment: Invert [56]
	 71 => 464 // Sex Change [71]

	// Effets
	// Parfois les immunités protègent contre les effet donc...

	146 => 465 // Spell: Cast Spell (at Target) [146]
	148 => 466 // Spell: Cast Spell (at Point) [148]
	272 => 467 // Spell: Apply Repeating EFF [272]
	232 => 468 // Spell Effect: Cast Spell on Condition [232]
	326 => 469 // Apply Effects List [326]
	311 => 470 // Spell: Random Wish Spell [311]
	252 => 471 // Spell Effect: Set Trap [252]
	177 => 472 // EFF File [177]
	333 => 473 // Spell Effect: Static Charge [333]
	183 => 473 // Item: Apply Effect Itemtype [183]

	// Effets au toucher

	248 => 474 // Item: Set Melee Effect [248]
	249 => 475 // Item: Set Ranged Effect [249]
	341 => 476 // Spell Effect: Change Critical Hit Effect [341]
	361 => 477 // Cast spell on critical miss [361]
	340 => 478 // Spell Effect: Change Backstab Effect [340]

	192 => 479 // Spell Effect: Find Familiar [192]
	111 => 480 // Item: Create Magical Weapon [111]
	143 => 481 // Item: Create Item in Slot [143]
	122 => 482 // Item: Create Inventory Item [122]
	255 => 483 // Item: Create Inventory Item (days) [255]
	302 => 484 // Item: Can Use Any Item [302]
	196 => 485 // Spell Effect: Familiar Block [196]
	180 => 486 // Item: Can't Use Item [180]
	181 => 487 // Item: Can't Use Itemtype [181]
	243 => 488 // Item: Drain Item Charges [243]

	 26 => 489 // Item: Remove Curse [26]
	// 172 => 490 // Spell: Remove Spell [172]
	// 147 => 491 // Spell: Learn Spell [147]
	171 => 492 // Spell: Give Innate Ability [171]
	335 => 493 // Spell Effect: Seven Eyes [335]
	251 => 494 // Spell Effect: Change Bard Song Effect [251]


	145 => 495 // Spell: Disable Spell Casting Abilities [145]
	144 => 496 // Button: Disable Button [144]
	279 => 497 // Button: Enable Button [279]
	300 => 498 // NPC Bump [300]

	// Aucune importance => l'opcode est remplacé par d'autres
	282 => 999 // Script: Scripting State Modifier [282]
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
	114 => 0 // Graphics: Dither [114]
	138 => 0 // Graphics: Character Animation Change [138]
	139 => 0
	140 => 0 // Graphics: Casting Glow [140]
	141 => 0
	142 => 0
	147 => 0 // Spell: Learn Spell [147]
	152 => 0 // Spell Effect: Play Movie [152]
	155 => 0 // Overlay: Minor Globe [155]
	156 => 0 // Overlay: Protection from Normal Missiles Cylinder [156]
	158 => 0 // State: Grease [158]
	168 => 0 // Summon: Remove Creature [168]
	169 => 0
	170 => 0 // Graphics: Play Damage Animation [170]
	172 => 0 // Spell: Remove Spell [172]
	174 => 0 // Spell Effect: Play Sound Effect [174]
	182 => 0 // Item: Apply Effect Item [182]
	184 => 0 // Graphics: Passwall (Don't Jump) [184]
	186 => 0 // Script: MoveToArea [186] // A gérer ??
	187 => 0 // Script: Store Local Variable [187]
	194 => 0 // Ignore Dialog Pause [194]
	195 => 0 // Spell Effect: Death Dependent Constitution Loss (Familiar Bond) [195]
	215 => 0
	225 => 0 // Spell: Reveal Magic [225]
	234 => 0 // Spell Effect: Contingency Creation [234]
	237 => 0 // Spell Effect: Puppet ID [237]
	240 => 0 // Graphics: Remove Special Effect Icon [240]
	253 => 0 // Spell Effect: Add Map Marker [253]
	254 => 0 // Spell Effect: Remove Map Marker [254]
	256 => 0 // Spell: Spell Sequencer Active [256]
	257 => 0 // Spell: Spell Sequencer Creation [257]
	258 => 0 // Spell: Spell Sequencer Activation [258]
	260 => 0 // Spell: Spell Sequencer Activation [260]
	265 => 0 // Script: Set Global Variable [265]
	267 => 0
	269 => 0 // Spell Effect: Shake Window [269]
	271 => 0 // Graphics: Avatar Removal [271]
	// 282 => 0 // Script: Scripting State Modifier [282]
	287 => 0 // Graphics: Selection Circle Removal [287]
	290 => 0 // Text: Change Title [290]
	291 => 0 // Graphics: Disable Visual Effect [291]
	293 => 0 // Script: Enable Offscreen AI [293]
	294 => 0 // Existance Delay Override [294]
	296 => 0 // Graphics: Protection from Specific Animation [296]
	297 => 0 // Text: Protection from Display Specific String [297]
	298 => 0 // Spell Effect: Execute Script cut250a [298]
	307 => 0 // Ranger Tracking Ability [307]
	308 => 0 // Protection: From Tracking [308]
	309 => 0 // Script: Set/Modify Local Variable [309]
	312 => 0
	313 => 0 // High-Level Ability Denotation [313]
	315 => 0 // Graphics: Animation Removal [315]
	// EE only
	319 => 0 // Item Usability [319] // Pas nécessaire de le gérer, l'utilisabilité est gérée automatiquement par EE
	320 => 0 // Change Weather [320]
	327 => 0 // Graphics: Icewind Visual Spell Hit (plays sound) [327]
	328 => 0 // State: Set State [328]
	330 => 0 // Text: Float Text [330]
	334 => 0 // Spell Effect: Turn Undead [334]
	336 => 0 // Graphics: Display Eyes Overlay [336]
	338 => 0 // Disable Rest [338]
	339 => 0 // Alter Animation [339]
	342 => 0 // Animation: Override Data [342]
	363 => 0 // Modal state check [363]
	365 => 0 // Make unselectable [365]
	366 => 0 // Spell: Apply Spell On Move [366]
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

// Cécité
ACTION_DEFINE_ASSOCIATIVE_ARRAY blindSpellList BEGIN
	~SPDM101~ => 1 // Cécité
	~SPWI106~ => 1 // Cécité
	~SPWM178~ => 1 // Cécité
	~SPWI228~ => 1 // -
	~SPWI815~ => 1 // Mot de pouvoir : Cécité
	~SPWI958~ => 1 // Mot de pouvoir : Cécité
END

// Charmes
ACTION_DEFINE_ASSOCIATIVE_ARRAY charmSpellList BEGIN
	~SPCL641~ => 1 // Charmer une personne ou un mammifère
	~SPIN119~ => 1 // Charmer une personne
	~SPIN883~ => 1 // Domination
	~SPIN910~ => 1 // Domination
	~SPWI104~ => 1 // Charmer une personne
	~SPPR204~ => 1 // Charmer une personne ou un mammifère
	~SPWI316~ => 1 // Charme néfaste
END

// Confusion
ACTION_DEFINE_ASSOCIATIVE_ARRAY confusionSpellList BEGIN
	~SPPR311~ => 1 // Obstination bornée
	~SPPR709~ => 1 // Confusion
	~SPWI401~ => 1 // Confusion
	~SPWI508~ => 1 // Chaos
END

// Surdité
ACTION_DEFINE_ASSOCIATIVE_ARRAY deafnessSpellList BEGIN
	~spwi223~ => 1 // Surdité
END

// Enchevêtrement
ACTION_DEFINE_ASSOCIATIVE_ARRAY entangleSpellList BEGIN
	~SPIN688~ => 1 // Croissance végétale
	~SPPR105~ => 1 // Enchevêtrement
	~SPWM111~ => 1 // Enchevêtrement
END

// Débilité mentale
ACTION_DEFINE_ASSOCIATIVE_ARRAY feeblemindednessSpellList BEGIN
	~SPWI509~ => 1 // Débilité mentale
END

// Hâte
ACTION_DEFINE_ASSOCIATIVE_ARRAY hasteSpellList BEGIN
	~SPIN572~ => 1 // Hâte
	~SPIN655~ => 1 // Hâte améliorée
	~SPIN828~ => 1 // Hâte
	~SPRA301~ => 1 // Hâte
	~SPWI305~ => 1 // Hâte
	~SPWI613~ => 1 // Hâte améliorée
END

// 175: Immobilisation
ACTION_DEFINE_ASSOCIATIVE_ARRAY holdSpellList BEGIN
	~SPIN648~ => 1 // Immobilisation des personnes
	~SPIN988~ => 1 // Immobilisation des personnes
	~SPPR208~ => 1 // Immobilisation des personnes
	~SPPR305~ => 1 // Immobilisation des animaux
	~SPPR989~ => 1 // Immobilisation des personnes
	~SPWI306~ => 1 // Immobilisation des personnes
	~SPWI507~ => 1 // Immobilisation des monstres
	~SPWM122~ => 1 // Immobilisation des personnes
END

// 109: Paralysie
ACTION_DEFINE_ASSOCIATIVE_ARRAY paralyseSpellList BEGIN
END

// Horror
ACTION_DEFINE_ASSOCIATIVE_ARRAY horrorSpellList BEGIN
	~spin105~ => 1 // Horreur
	~SPIN675~ => 1 // Horreur errante
	~SPPR416~ => 1 // Manteau de terreur
	~SPPR706~ => 1 // Symbole : Terreur
	~spwi205~ => 1 // Horreur
	~SPWI811~ => 1 // Symbole : Terreur
END

// Labyrinthe
ACTION_DEFINE_ASSOCIATIVE_ARRAY mazeSpellList BEGIN
	~SPCL937~ => 1 // Labyrinthe de l'Ombre
	~SPIN774~ => 1 // Labyrinthe psionique
	~SPWI813~ => 1 // Labyrinthe
END

// Poison
ACTION_DEFINE_ASSOCIATIVE_ARRAY poisonSpellList BEGIN
	~SPIN673~ => 1 // Nuage mortel
	~SPWI016~ => 1 // Nuage mortel
	~SPWI502~ => 1 // Nuage mortel
END

// Pétrification
ACTION_DEFINE_ASSOCIATIVE_ARRAY petrificationSpellList BEGIN
	~spwi604~ => 1 // Pétrification
END

// Métamorphose
ACTION_DEFINE_ASSOCIATIVE_ARRAY polymorphSpellList BEGIN
	~SPWI415~ => 1 // Métamorphose d'autrui
	~SPWM113~ => 1 // Métamorphose d'autrui
END

// Silence
ACTION_DEFINE_ASSOCIATIVE_ARRAY silenceSpellList BEGIN
	~spin692~ => 1 // Silence dans un rayon de 4,5m
	~spin998~ => 1 // Silence dans un rayon de 4,5m
	~SPPR211~ => 1 // Silence dans un rayon de 4,5m
	~SPPR988~ => 1 // Silence dans un rayon de 4,5m
	~SPWI612~ => 1 // Mot de pouvoir : Silence
END

// Lenteur
ACTION_DEFINE_ASSOCIATIVE_ARRAY slowSpellList BEGIN
	~SPIN575~  => 1 // Toile de vortex
	~SPIN977~  => 1 // Lenteur du Golem
	~SPIN983~  => 1 // Lent
	~SPWI312~  => 1 // Lent
	~SPWISH25~ => 1 // Lent
	~SPWM164~  => 1 // Lent
END

// Etourdissement
ACTION_DEFINE_ASSOCIATIVE_ARRAY stunSpellList BEGIN
	~SPIN543~ => 1 // Douleur
	~SPPR718~ => 1 // Symbole : Etourdissement
	~SPWI715~ => 1 // Mot de pouvoir : Etourdissement
	~SPWI816~ => 1 // Symbole : Etourdissement
	~SPWI898~ => 1 // Symbole : Etourdissement
	~SPWI959~ => 1 // Mot de pouvoir : Etourdissement
END

// Inconscience
ACTION_DEFINE_ASSOCIATIVE_ARRAY unconsciousnessSpellList BEGIN
	~SPPR102~ => 1 // Injonction
	~SPPR512~ => 1 // Ordre majeur
END

// Toile d'araignée
ACTION_DEFINE_ASSOCIATIVE_ARRAY webSpellList BEGIN
	~SPDR157~ => 1
	~SPDR201~ => 1 // Toile d'araignée
	~SPIN566~ => 1 // Toile de mimique
	~SPIN683~ => 1 // Enchevêtrement de toile
	~SPIN575~ => 1 // Toile de vortex
	~SPWI215~ => 1 // Toile d'araignée
END

/*
	Opcodes dont le champ Duration n'est pas impactant
	Conséquence : La durée n'est pas à écrire car considérée comme implicite
	Plusieurs cas :
	0- l'effet est instantané et ne peut perdurer ou être dissipé
		(dissipation, soin (dans le sens où on peut les reperdre peu de temps après))
		~ duration 0
	1- l'effet est instantané mais est dissipé en cas de mort/résurrection ()
		~ permanent
	3- l'effet est soit permanent soit permanent after death (selon le timing choisi)
		~ à vérifier
	9- l'effet est instantané, définitif et ne peut être dissipé (perte d'un objet, oubli d'un sort)
		~ permanent after death
*/
// Conséquence : à définir
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcodes_ignore_duration~ BEGIN
	  2 => 0 // Cure: Sleep
	  4 => 0 // Cure: Berserking
	 11 => 0 // Cure: Poison
	 12 => 0 // HP: Damage
	 13 => 1 // Death: Instant Death
	 14 => 0 // Graphics: Defrost
	 17 => 0 // HP: Current HP Modifier
	 23 => 0 // Stat: Morale Modifier
	 26 => 0 // Item: Remove Curse
	 32 => 0 // Cure: Death (Raise Dead)
	 43 => 0 // Cure: Stone to Flesh
	 46 => 0 // Cure: Stun (Unstun)
	 47 => 0 // Cure: Invisibility
	 48 => 0 // Cure: Silence (Vocalize)
	 55 => 0 // Death: Kill Creature Type
	 58 => 0 // Cure: Dispellable Effects (Dispel Magic)
	 64 => 0 // State: Remove Infravision
	 68 => 9 // Summon: Unsummon Creature
	 70 => 0 // Cure: Non-Detection
	 75 => 0 // Cure: Blindness
	 77 => 0 // Cure: Feeblemindedness
	 79 => 0 // Cure: Disease
	 81 => 0 // Cure: Deafness
	105 => 0 // Stat: Gold
	108 => 0 // Stat: Reputation
	112 => 9 // Item: Remove Item
	116 => 0 // State: Cure Invisibility
	123 => 9 // Item: Remove Inventory Item
	124 => 0 // Spell Effect: Teleport (Dimension Door)
	125 => 9 // Spell Effect: Unlock (Knock)
	134 => 1 // State: Petrification
	136 => 0 // State: Force Visible
	147 => 9 // Spell: Learn Spell (A CONFIRMER, parfaitement adapté dans 99.9% des cas)
	150 => 0 // Spell Effect: Find Traps
	151 => 3 // Summon: Replace Creature (FIXME: peut-être des nuances selon le mode)
	160 => 0 // Remove Sanctuary
	161 => 0 // Cure: Horror
	162 => 0 // Cure: Hold
	163 => 0 // Protection: Free Action
	164 => 0 // Cure: Drunkeness
	171 => 3 // Spell: Give Ability
	172 => 9 // Spell: Remove Spell
	209 => 1 // Death: Kill 60HP
	210 => 0 // Spell Effect: Stun 90HP
	211 => 9 // Spell Effect: Imprisonment - bien qu'il puisse être dissipé sous une condition
	212 => 0 // Protection: Freedom
	220 => 0 // Removal: Remove School
	221 => 0 // Removal: Remove Secondary Type
	222 => 0 // Spell Effect: Teleport Field
	224 => 0 // Cure: Level Drain (Restoration)
	229 => 0 // Removal: Remove One School
	230 => 0 // Removal: Remove One Secondary Type
	238 => 1 // Death: Disintegrate
	242 => 0 // Cure: Confusion
	243 => 9 // Item: Drain Item Charges
	244 => 9 // Spell: Drain Wizard Spell
	251 => 9 // Spell Effect: Change Bard Song Effect
	252 => 9 // Spell Effect: Set Trap // durée : jusqu'à activation
	261 => 9 // Spell: Restore Lost Spells
	264 => 9 // Spell Effect: Drop Weapons in Panic
	270 => 0 // Cure: Unpause Target
	273 => 0 // Remove: Specific Area Effect(Zone of Sweet Air)
	316 => 0 // Spell: Magical Rest
	337 => 0 // Remove: Opcode
	343 => 0 // HP Swap
	511 => 0 // Dissipe toutes les illusions
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcodes_ignore_not_cumulable~ BEGIN
	 11 => 1
	 12 => 1
	 16 => 1
	 39 => 1
	 40 => 1
	 46 => 1
	 77 => 1
	 79 => 1
	101 => 1
	161 => 1
	177 => 1
	206 => 1
	208 => 1
	221 => 1
	224 => 1
	235 => 1
	242 => 1
	335 => 1
	337 => 1
END

// opcodes absents de opcodes_ignore_duration mais dont l'effet ne peut être permanent
// Traduction : durée normale ou jusqu'à dissipation / utilisation
// Conséquence : les durées "permanentes" et "permanentes, persiste après la mort" ne sont pas affichées
// TODO: à clarifier ou retirer
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcodes_cant_be_permanent~ BEGIN
	 20 => 1 // Invisibilité
	 94 => 1 // // Stat: Drunkenness Modifier [94]
	122 => 1 // // Item: Create Inventory Item [122]
	127 => 1 // Summon: Monster Summoning
	146 => 1 // Spell: Cast Spell (at Creature)
	148 => 1 // Spell: Cast Spell (at Point)
	177 => 1 // Use EFF File
	214 => 1 // Spell Effect: Select Spell
	218 => 1 // Protection: Stoneskin
	236 => 1 // Spell Effect: Image Projection
	274 => 1 // // Spell Effect: Teleport to Target [274]
	280 => 1 // Spell Effect: Wild Magic, est un peu tout en même temps
	331 => 1 // Summon: Random Monster Summoning
	519 => 1 // // Arme brisée
	525 => 1 // // Item: Replace item [525]
END

// Opcodes qui sont dissipés par la mort (directement ou indirectement)
// Conséquence : Timing 9 est converti en Timing 1
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcodes_cant_be_permanent_after_death~ BEGIN
	24  => 1 // State: Horror
	25  => 1 // State: Poison
	45  => 1 // State: Stun
	109 => 1 // State: Paralyze
	157 => 1 // State: Web Effect
	175 => 1 // State: Hold
	185 => 1 // State: Hold (II)
	210 => 1 // Spell Effect: Stun 90HP
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcodes_parameters_should_be_zero~ BEGIN
	  4 => 1
	 43 => 1
	 47 => 1
	 56 => 1
	 63 => 1
	 64 => 1
	 65 => 1
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

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~death_to_strref~ BEGIN
	0	 => 500001
	1	 => 500002
	2	 => 500003
	4	 => 500004
	8	 => 500005
	16	 => 500006
	32	 => 500007
	64	 => 500004
	128  => 500004
	256  => 500010
	512  => 500011
	1024 => 500012
END


// + d'autres sous condition : (opcode != 218 OR is_ee == 0 OR parameter2 == 0) AND (opcode != 127 OR is_ee == 0)
ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcode_without_level_restriction~ BEGIN
	12  => 1
	17  => 1
	18  => 1
	331 => 1
	333 => 1
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
	LOCAL_SPRINT name @10000099 // ~Classe d'armure~

	PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
		SPRINT value ~%custom_str%~
	END
	ELSE PATCH_IF parameter2 != AC_MOD_TYPE_set_base BEGIN
		LPM ~opcode_0_get_value~
		PATCH_IF parameter2 > AC_MOD_TYPE_all AND parameter2 < 0xF BEGIN
			SET strref = 10000000 + parameter2
			LPF ~getTranslation~ INT_VAR strref opcode RET versus = string END // ~contre les xxx~
			SPRINT value ~%value% %versus%~
		END
	END
	ELSE BEGIN
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
		PATCH_IF parameter2 > AC_MOD_TYPE_all AND parameter2 < 0xF BEGIN
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
		SPRINT value @10010 // ~Passe à %value%~
	END
	ELSE BEGIN
		LPM ~opcode_0_get_value~
		PATCH_IF parameter2 > AC_MOD_TYPE_all AND parameter2 < 0xF BEGIN
			SET strref = 10000000 + parameter2
			LPF ~getTranslation~ INT_VAR strref opcode RET versus = string END // ~contre les xxx~
			SPRINT value ~%value% %versus%~
		END
	END

	PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
		SPRINT name @10000099      // ~Classe d'armure~
		SPRINT description @100007 // ~%name% %ofTheTarget%%colon%%value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_0~ BEGIN
	LPM ~opcode_self_probability_0~
END

DEFINE_PATCH_MACRO ~opcode_0_get_value~ BEGIN
	PATCH_IF armor_class_show_bonus_malus BEGIN
		PATCH_IF value >= 0 BEGIN
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

// Association des classes d'armure V2
// TODO: Pour gérer le regroupement avec des target_type différents, actuellement, seuls les effets sans aucune cible particulière sont gérés
DEFINE_PATCH_MACRO ~opcode_0_group~ BEGIN
	LOCAL_SET value = 0
	LOCAL_SET baseClassArmor = 0
	LOCAL_SET allClassArmor = 0
	LOCAL_SET hasBaseClassArmor = 0
	LOCAL_SPRINT classArmorValue ~~
	LOCAL_SPRINT and @100021 // ~et~
	LOCAL_SPRINT the @11770200 // ~les~
	LOCAL_SPRINT andThe @11770201 // ~et les~
	DEFINE_ASSOCIATIVE_ARRAY ~opcode_0_CA~ BEGIN END
	DEFINE_ASSOCIATIVE_ARRAY ~opcode_0_CA_values~ BEGIN END
	DEFINE_ASSOCIATIVE_ARRAY ~opcode_0_no_protect_values~ BEGIN END
	DEFINE_ASSOCIATIVE_ARRAY ~opcode_219000_CA_values~ BEGIN END

	PATCH_IF shrink_class_armor BEGIN
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF timingMode == TIMING_while_equipped AND target == TARGET_FX_self AND ~%target_type%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF parameter2 == AC_MOD_TYPE_set_base BEGIN
					SET baseClassArmor = parameter1
					SET hasBaseClassArmor = 1
				END
				ELSE PATCH_IF NOT isArmor AND parameter2 == AC_MOD_TYPE_all BEGIN
					SET allClassArmor += parameter1
				END
				ELSE PATCH_IF parameter2 == AC_MOD_TYPE_crushing OR
		                parameter2 == AC_MOD_TYPE_missile OR
		                parameter2 == AC_MOD_TYPE_piercing OR
		                parameter2 == AC_MOD_TYPE_slashing BEGIN
					SET newValue = parameter2
					SET parameter1 *= ~-1~
					PATCH_IF VARIABLE_IS_SET $opcode_0_CA(~%parameter1%~) BEGIN
						SET currentValue = $opcode_0_CA(~%parameter1%~)
						// Que faire des doublons ?
						SET newValue = currentValue | parameter2
					END
					SET $opcode_0_CA(~%parameter1%~) = newValue
                END
			END
		END

		PATCH_PHP_EACH EVAL ~opcodes_219000~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF timingMode == TIMING_while_equipped AND target == TARGET_FX_self AND ~%target_type%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF VARIABLE_IS_SET $ids_files(~%parameter2%~) BEGIN
                    LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET idName END
                    SET $opcode_219000_CA_values(~%idName%~) = 1
                END
                ELSE BEGIN
                    LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Wrong ids file : %file%~ END
                END
				LPF ~delete_opcode~
                    INT_VAR opcode = 219000 match_position = position
                    RET $opcodes(~219000~) = count
                    RET_ARRAY EVAL ~opcodes_219000~ = opcodes_xx
                END
			END
		END
		LPF ~implode~ STR_VAR array_name = ~opcode_219000_CA_values~ glue = ~, %the% ~ final_glue = ~ %andThe% ~ RET targetType = text END

		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			// Ne pas prendre en compte la classe d'armure de base dans le regroupement
			PATCH_IF timingMode == TIMING_while_equipped AND target == TARGET_FX_self AND ((isArmor AND parameter2 != AC_MOD_TYPE_all) OR (NOT isArmor AND parameter2 != AC_MOD_TYPE_set_base)) AND ~%target_type%~ STRING_EQUAL ~~ BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
		END
		// Bug où il reste toujours un item dans le tableau si c'était le dernier
		// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
		PATCH_IF $opcodes(~0~) == 0 BEGIN
            CLEAR_ARRAY ~opcodes_0~
        END
		// Créer la donnée à ajouter en tant qu'attribut de l'objet !!
		SORT_ARRAY_INDICES ~opcode_0_CA~ NUMERICALLY

		PATCH_IF isArmor AND hasBaseClassArmor BEGIN
			SET baseClassArmor -= allClassArmor
			SPRINT classArmorValue ~%baseClassArmor%~
			PATCH_PHP_EACH ~opcode_0_CA~ AS amount => armorType BEGIN
				SET amount *= ~-1~
				SET value = baseClassArmor - amount
				SET strref = 10000000 + armorType
				LPF ~getTranslation~ INT_VAR strref opcode RET versus = string END // ~contre les xxx~
				PATCH_IF amount == 2 BEGIN
                    PATCH_IF NOT ~%targetType%~ STRING_EQUAL ~~ BEGIN
                        INNER_PATCH_SAVE versus ~%versus%~ BEGIN
                            REPLACE_TEXTUALLY ~ %and% ~ ~ ,~
                        END
                        SPRINT versus ~%versus%, %the% %targetType%~
                    END
                END
				SPRINT value ~%value% %versus%~
				SET $opcode_0_CA_values(~%value%~) = 1
			END
			PATCH_IF NOT VARIABLE_IS_SET $opcode_0_CA(~-2~) AND NOT ~%targetType%~ STRING_EQUAL ~~ BEGIN
				SET value = baseClassArmor - 2
				SPRINT versus @102387 // ~contre les %targetType%~
				SPRINT value ~%value% %targetType%~
				SET $opcode_0_CA_values(~%value%~) = 1
			END
			LPF ~implode~ STR_VAR array_name = ~opcode_0_CA_values~ glue = ~, ~ final_glue = ~, ~ RET classArmorValues = text END
			PATCH_IF NOT ~%classArmorValues%~ STRING_EQUAL ~~ BEGIN
				SPRINT classArmorValue ~%classArmorValue% (%classArmorValues%)~
			END
			// Création d'un opcode dont la description de l'effet sera ajoutée à la description globale de l'objet, et non plus à la description de la section
			SET opcode = 1000
			SPRINT custom_str ~%classArmorValue%~
            LPM ~add_opcode~
			SET opcode = 0
		END
		ELSE BEGIN
			PATCH_IF allClassArmor != 0 BEGIN
				LPF ~signed_value~ INT_VAR value = allClassArmor RET value END
				SPRINT classArmorValue ~%value%~
			END
			PATCH_PHP_EACH ~opcode_0_CA~ AS amount => armorType BEGIN
				SET amount *= ~-1~
				SET value = allClassArmor + amount
				SET strref = 10000000 + armorType
				LPF ~getTranslation~ INT_VAR strref opcode RET versus = string END // ~contre les xxx~
				PATCH_IF amount == 2 BEGIN
					PATCH_IF NOT ~%targetType%~ STRING_EQUAL ~~ BEGIN
						INNER_PATCH_SAVE versus ~%versus%~ BEGIN
							REPLACE_TEXTUALLY ~ %and% ~ ~ ,~
						END
						SPRINT versus ~%versus%, %the% %targetType%~
					END
				END
				PATCH_IF value != 0 BEGIN
					LPF ~signed_value~ INT_VAR value RET value END
					SET $opcode_0_CA_values(~%value% %versus%~) = 1
				END
				ELSE BEGIN
					SET $opcode_0_no_protect_values(~%versus%~) = 1
				END
			END
			PATCH_IF NOT VARIABLE_IS_SET $opcode_0_CA(~-2~) AND NOT ~%targetType%~ STRING_EQUAL ~~ BEGIN
				SET value = allClassArmor + 2
				SPRINT versus @102387 // ~contre les %targetType%~
				PATCH_IF value != 0 BEGIN
					LPF ~signed_value~ INT_VAR value RET value END
					SET $opcode_0_CA_values(~%value% %versus%~) = 1
				END
				ELSE BEGIN
					SET $opcode_0_no_protect_values(~%versus%~) = 1
				END
			END

			LPF ~implode~ STR_VAR array_name = ~opcode_0_no_protect_values~ glue = ~, ~ final_glue = ~, ~ RET noProtectValues = text END
			PATCH_IF NOT ~%noProtectValues%~ STRING_EQUAL ~~ BEGIN
				SET opcode = 521
                SPRINT custom_str ~%noProtectValues%~
                LPM ~add_opcode~
			END

			LPF ~implode~ STR_VAR array_name = ~opcode_0_CA_values~ glue = ~, ~ final_glue = ~, ~ RET classArmorValues = text END
			PATCH_IF NOT ~%classArmorValues%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF NOT ~%classArmorValue%~ STRING_EQUAL ~~ BEGIN
					SPRINT classArmorValue ~%classArmorValue%, %classArmorValues%~
				END
				ELSE BEGIN
					SPRINT classArmorValue ~%classArmorValues%~
				END
			END
			PATCH_IF NOT ~%classArmorValue%~ STRING_EQUAL ~~ BEGIN
				// Création d'un opcode dont la description de l'effet sera ajoutée à la description globale de l'objet, et non plus à la description de la section
				SET opcode = 0
				SPRINT custom_str ~%classArmorValue%~
				SPRINT target_type ~~
	            LPM ~add_opcode~
            END
		END
	END

	CLEAR_ARRAY opcode_0_CA

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF timingMode == TIMING_while_equipped AND ~%target_type%~ STRING_EQUAL ~~ AND (
				parameter2 == AC_MOD_TYPE_crushing OR
				parameter2 == AC_MOD_TYPE_missile OR
				parameter2 == AC_MOD_TYPE_piercing OR
				parameter2 == AC_MOD_TYPE_slashing) BEGIN
			SET newValue = parameter2
			PATCH_IF VARIABLE_IS_SET $opcode_0_CA(~%parameter1%~) BEGIN
				SET currentValue = $opcode_0_CA(~%parameter1%~)
				// PATCH_IF NOT currentValue BAND parameter2 BEGIN
				// Que faire des doublons ?
				SET newValue = currentValue | parameter2
			END
			SET $opcode_0_CA(~%parameter1%~) = newValue
		END
	END
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF timingMode == TIMING_while_equipped AND ~%target_type%~ STRING_EQUAL ~~ AND (
				parameter2 == AC_MOD_TYPE_crushing OR
				parameter2 == AC_MOD_TYPE_missile OR
				parameter2 == AC_MOD_TYPE_piercing OR
				parameter2 == AC_MOD_TYPE_slashing) BEGIN
			LPF ~delete_opcode~
				INT_VAR opcode match_position = position
				RET $opcodes(~%opcode%~) = count
				RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
			END
		END
	END

	PATCH_PHP_EACH ~opcode_0_CA~ AS amount => armorType BEGIN
		SET opcode = 506
		SET parameter1 = amount
		SET parameter2 = armorType
		SET timingMode = TIMING_while_equipped
		SET target = TARGET_FX_self
		SET probability2 = 100
		LPM ~add_opcode~
	END
END

/* ------------------------------------ *
 * Stat: Attacks Per Round Modifier [1] *
 * ------------------------------------ */

DEFINE_PATCH_MACRO ~opcode_self_1~ BEGIN
	SET strref = 10010001
	LPM ~opcode_1_common~
END

DEFINE_PATCH_MACRO ~opcode_target_1~ BEGIN
	SET strref = 10010011
	LPM ~opcode_1_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_1~ BEGIN
	SET strref = 10010021
	LPM ~opcode_1_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_1~ BEGIN
	SET strref = 10010031
	LPM ~opcode_1_common~
END

DEFINE_PATCH_MACRO ~opcode_1_common~ BEGIN
	LOCAL_SET is_negative = parameter1 < 0 ? 1 : 0
	SET value = ABS parameter1

	// P2 = 1 ou P2 = 3: si P1 > 10 ou < 0 => P1 = 10
	PATCH_IF (parameter2 == MOD_TYPE_flat OR parameter2 == 3) AND NOT VARIABLE_IS_SET $opcode_1_values(~%value%~) BEGIN
		SET value = 10
	END

	SET parameter2 = (parameter2 == 3 AND NOT is_ee) ? MOD_TYPE_cumulative : parameter2

	PATCH_IF parameter2 != MOD_TYPE_percentage BEGIN
		SPRINT oneHalf @10010101 // ~une demi~
		SPRINT andHalf @10010102 // ~\1 et demi~
		// Weidu ne gérant pas les nombres flottants, une solution est de passer par des nombres 10 fois plus grand.
		SET value = $opcode_1_values(~%value%~)

		PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
			PATCH_IF is_negative == 1 BEGIN
				SET value = 0 - value
			END
	        LPF ~signed_value~ INT_VAR value RET value END
	    END

		INNER_PATCH_SAVE value ~%value%~ BEGIN
			REPLACE_TEXTUALLY ~+5$~ ~+%oneHalf%~         // 5  => une demi
			REPLACE_TEXTUALLY ~\([0-9]\)+0$~ ~\1~        // 20 => 2
			REPLACE_TEXTUALLY ~\([0-9]\)+5$~ ~%andHalf%~ // 25 => 2 et demi
		END
	END

	PATCH_IF parameter1 == 0 AND (parameter2 == MOD_TYPE_flat OR parameter2 == MOD_TYPE_percentage OR parameter2 == 3) BEGIN
		SET strref += 4 // ~Attaque impossible~
	END
	ELSE BEGIN
		PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
			SET strref += 1 // ~Attaque par round : Passe à %value%~
		END
		ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN
			SET strref += 2 // ~Attaque par round : %value%~
			SET value = ~%parameter1%~
			SET value -= 100
			LPF ~signed_value~ INT_VAR value RET value END
			SPRINT value @10002 // ~%value% %~
		END
		ELSE PATCH_IF parameter2 == 3 BEGIN
			SET strref += 3 // ~Fixée à %value%~
		END

		PATCH_IF parameter2 == MOD_TYPE_cumulative AND ~%value%~ STRING_EQUAL ~+%oneHalf%~ BEGIN
			SPRINT value @10010103 // ~une demi supplémentaire~
		END
	END
	SPRINT description (AT strref)
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
	LPM ~opcode_3_condition~
	SPRINT description @10030001 // ~Provoque la rage du berserker chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_3~ BEGIN
	LPM ~opcode_self_3~ // ~Provoque la rage du berserker chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_3~ BEGIN
	LPM ~opcode_3_condition~
	SPRINT description @10030002 // ~de provoquer la rage du berserker chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_3~ BEGIN
	LPM ~opcode_self_probability_3~ // ~de provoquer la rage du berserker chez %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_3_condition~ BEGIN
	PATCH_IF timingMode != 1 AND (parameter2 != 1 OR NOT is_ee) BEGIN
		SPRINT condition @10030003 // En combat
	END
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
	LPF ~opcode_mod~ INT_VAR strref = 10060001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Charisme~
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

DEFINE_PATCH_MACRO ~opcode_6_group~ BEGIN
	LOCAL_SET opcode = 6
	LOCAL_SET newOpcode = 501

	PATCH_IF shrink_abilities BEGIN
		PATCH_DEFINE_ARRAY listOpcodes BEGIN 10 15 19 44 49 END

		LPM ~group_opcode_with_same_parameters~
	END
END

/* -------------------------------- *
 * Stat: Constitution Modifier [10] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_10~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10100001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Constitution~
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
	LPF ~opcode_12_common~ INT_VAR strref_0 = 10120001
								   strref_1 = 10120006
								   strref_2 = 10120007
								   strref_3 = 10120008
		RET description
	END
END

DEFINE_PATCH_MACRO ~opcode_target_12~ BEGIN
	LOCAL_SET strref_0 = 10120002 // ~Inflige %damage% %toTheTarget%~
	LOCAL_SET strref_1 = 10120006 // ~Passe les points de vie de %theTarget% à %damage%~
	LOCAL_SET strref_2 = 10120007 // ~Passe les points de vie de %theTarget% à %damage% %~
	LOCAL_SET strref_3 = 10120008 // ~Inflige %damage% % des points de vie maximums %toTheTarget%~

	LPM ~opcode_12_flags~

	PATCH_IF VARIABLE_IS_SET versus AND NOT %versus% STRING_EQUAL ~~ BEGIN
		SET strref_0 = 10120003 // ~Inflige %damage% %damageType% supplémentaires %versus%~
	END
	PATCH_IF flagDrain == 1 BEGIN
		SET strref_0 = 10120004 // ~Draine %damage% %damageType% %toTheTarget%~
	END
	PATCH_IF flagTransfert == 1 BEGIN
		SET strref_0 = 10120005 // ~Transfert %damage% %damageType% %toTheTarget%~
	END

	LPF ~opcode_12_common~ INT_VAR strref_0 strref_1 strref_2 strref_3 RET description END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_12~ BEGIN
	LPM ~opcode_12_flags~
	LPF ~opcode_12_common~ INT_VAR strref_0 = 10120011
								   strref_1 = 10120016
								   strref_2 = 10120017
								   strref_3 = 10120018
		RET description
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_12~ BEGIN
	LOCAL_SET strref_0 = 10120012 // ~d'infliger %damage% %damageType% supplémentaires~
	LOCAL_SET strref_1 = 10120016 // ~de faire passer les points de vie de %theTarget% à %damage%~
	LOCAL_SET strref_2 = 10120017 // ~de faire passer les points actuels de vie de %theTarget% à %damage% %~
	LOCAL_SET strref_3 = 10120018 // ~d'infliger %damage% % des points de vie maximums %toTheTarget%~

	LPM ~opcode_12_flags~

	PATCH_IF VARIABLE_IS_SET versus AND NOT %versus% STRING_EQUAL ~~ BEGIN
		SET strref_0 = 10120013 // ~d'infliger %damage% %damageType% supplémentaires %versus%~
	END
	PATCH_IF flagDrain == 1 BEGIN
		SET strref_0 = 10120014 // ~de drainer %damage% %damageType% %toTheTarget%~
	END
	PATCH_IF flagTransfert == 1 BEGIN
		SET strref_0 = 10120015 // ~de transférer %damage% %damageType% %toTheTarget%~
	END

	LPF ~opcode_12_common~ INT_VAR strref_0 strref_1 strref_2 strref_3 RET description END
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
		PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
			SPRINT damage ~%complex_value%~
		END
		ELSE BEGIN
			// Type de dégâts inconnus
			PATCH_IF VARIABLE_IS_SET $damage_types(~%type%~) BEGIN
				SET type = $damage_types(~%type%~)
			END
			ELSE BEGIN
				SET type = 101092 // ~points de dégâts~
			END
			LPF ~getTranslation~ INT_VAR strref = type opcode RET damageType = string END
			PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
				SPRINT damage @102166 // ~%damage% %damageType%~
			END
		END

		PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
			LPF ~getTranslation~ INT_VAR strref = strref_0 opcode RET description = string END
		END
	END
	// Set to value
	ELSE PATCH_IF mode == 1 BEGIN
		PATCH_IF ~%damage%~ STRING_EQUAL ~~ BEGIN
			SET damage = ~0~
		END
		LPF ~getTranslation~ INT_VAR strref = strref_1 opcode RET description = string END
	END
	// Set to Percentage
	ELSE PATCH_IF mode == 2 BEGIN
		PATCH_IF NOT ~%damage%~ STRING_EQUAL ~~ BEGIN
			LPF ~getTranslation~ INT_VAR strref = strref_2 opcode RET description = string END
		END
	END
	// Reduce by Percentage
	ELSE PATCH_IF mode == 3 BEGIN
		LPF ~getTranslation~ INT_VAR strref = strref_3 opcode RET description = string END
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
		SPRINT unarmed @10120041 // ~efficace si la source est désarmée~
		SPRINT description ~%description% (%unarmed%)~
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

DEFINE_PATCH_FUNCTION ~opcode_12_typed_value~ INT_VAR value = 0 RET strref BEGIN
	SET mode = parameter2 BAND 65535
	SET type = parameter2 - mode
	PATCH_IF VARIABLE_IS_SET $damage_types(~%type%~) BEGIN
		SET strref = $damage_types(~%type%~)
	END
	ELSE BEGIN
		SET strref = 101092 // ~points de dégâts~
	END
END

DEFINE_PATCH_MACRO ~opcode_12_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF saveType == 0 BEGIN
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_match_vars~
				LPM ~opcode_match_opcode_12_group~
				PATCH_IF match == 1 BEGIN
					LPF ~delete_opcode~
	                    INT_VAR opcode match_position
	                    RET $opcodes(~12~) = count
	                    RET_ARRAY EVAL ~opcodes_12~ = opcodes_xx
	                END
					LPF ~delete_opcode~
	                    INT_VAR opcode match_position = position
	                    RET $opcodes(~12~) = count
	                    RET_ARRAY EVAL ~opcodes_12~ = opcodes_xx
	                END
					// Bug où il reste toujours un item dans le tableau si c'était le dernier
					// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
					PATCH_IF $opcodes(~12~) == 0 BEGIN
			            CLEAR_ARRAY ~opcodes_12~
			        END
					SET diceCount += match_diceCount
					// special BAND BIT8
					SET special |= BIT8
					SET saveType = match_saveType
			        LPM ~add_opcode~
				END
			END
		END
	END
END

/* ------------------------- *
 * Death: Instant Death [13] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_13~ BEGIN
	SET strref = $death_to_strref(~%parameter2%~)
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_self_probability_13~ BEGIN
	LPM ~opcode_target_probability_13~
END

DEFINE_PATCH_MACRO ~opcode_target_13~ BEGIN
	LPM ~opcode_self_13~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_13~ BEGIN
	SET strref = $death_to_strref(~%parameter2%~)
	SET strref += 100
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_13_is_valid~ BEGIN
	PATCH_IF NOT VARIABLE_IS_SET $death_to_strref(~%parameter2%~) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown Death Type %parameter2%.~ END
	END
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
	LPF ~opcode_mod~ INT_VAR strref = 10150001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Dextérité~
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
				LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: mode : %parameter2% avec présence de CLSSPLAB.2da : non gere.~ END
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
	LOCAL_SET strref = 0
	PATCH_IF parameter2 == 1 BEGIN
		SET strref = 10160002 // ~Hâte améliorée~
	END
	ELSE PATCH_IF parameter2 == 2 BEGIN
		SET strref = 10160003 // ~Hâte (sans bonus d'attaque par round)~
	END
	ELSE BEGIN
		SET strref = 10160001 // ~Hâte~
	END
	PATCH_IF NOT use_short_effect_description BEGIN
		SET strref += 10
	END
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_self_probability_16~ BEGIN
	LOCAL_SET strref = 0
	PATCH_IF parameter2 == 1 BEGIN
		SET strref = 10160005 // ~de lancer Hâte améliorée sur %theTarget%~
	END
	ELSE PATCH_IF parameter2 == 2 BEGIN
		SET strref = 10160006 // ~de lancer Hâte (sans bonus d'attaque par round) sur %theTarget%~
	END
	ELSE BEGIN
		SET strref = 10160004 // ~de lancer Hâte sur %theTarget%~
	END
	PATCH_IF NOT use_short_effect_description BEGIN
		SET strref += 10
	END
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_target_16~ BEGIN
	LOCAL_SET strref = 0
	PATCH_IF parameter2 == 1 BEGIN
		SET strref = 10160008 // ~Lance Hâte améliorée sur %theTarget%~
	END
	PATCH_IF parameter2 == 2 BEGIN
		SET strref = 10160009 // ~Lance Hâte (sans bonus d'attaque par round) sur %theTarget%~
	END
	ELSE BEGIN
		SET strref = 10160007 // ~Lance Hâte sur %theTarget%~
	END
	PATCH_IF NOT use_short_effect_description BEGIN
		SET strref += 10
	END
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_target_probability_16~ BEGIN
	LPM ~opcode_self_probability_16~
END

/* ---------------------------- *
 * HP: Current HP Modifier [17] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_17~ BEGIN
	LOCAL_SET type = parameter2 BAND 65535
	LOCAL_SET subType = parameter2 / 65535
	LOCAL_SET strref_1 = 10170001 // ~Restaure %value% %toTheTarget%~
	// LOCAL_SET strref_1 = itemType == ITM_TYPE_potion : 10170001 ? 10170011 // ~Soigne 1 point de vie %ofTheTarget%~
	LOCAL_SET strref_2 = strref_1 + 1 // ~Inflige %value% %toTheTarget%~

	PATCH_IF type == 1 BEGIN
		SET damageAmount = parameter1
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END
		LPF ~opcode_mod~ INT_VAR strref = 10170021 STR_VAR value = EVAL ~%value%~ RET description END // ~Points de vie actuels~
	END
	ELSE PATCH_IF type == 0 OR type == 2 BEGIN
		LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 RET description END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_17~ BEGIN
	LOCAL_SET type = parameter2 BAND 65535
	LOCAL_SET subType = parameter2 / 65535
	LOCAL_SET strref_1 = 10170003 // ~de restaurer %value% %toTheTarget%~
	// LOCAL_SET strref_1 = itemType == ITM_TYPE_potion : 10170005 ? 10170015
	LOCAL_SET strref_2 = strref_1 + 1 // ~d'infliger %value% %toTheTarget%~

	PATCH_IF type == 0 OR type == 2 BEGIN
		LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 RET description END
	END
	ELSE BEGIN
		SET damageAmount = parameter1
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END
		LPF ~opcode_mod~ INT_VAR strref = 10170022 STR_VAR value = EVAL ~%value%~ RET description END // ~les points de vie actuels~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_17~ BEGIN
	LOCAL_SET strref_1 = 10170001 // ~Restaure %value% %toTheTarget%~
	LOCAL_SET strref_2 = strref_1 + 1 // ~Inflige %value% %toTheTarget%~
	LOCAL_SET type = parameter2 BAND 65535
	LOCAL_SET subType = parameter2 / 65535

	PATCH_IF type == 1 BEGIN
		SET damageAmount = parameter1
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END
		LPF ~opcode_mod~ INT_VAR strref = 10170021 STR_VAR value = EVAL ~%value%~ RET description END // ~Points de vie actuels~
	END
	ELSE BEGIN
		LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 RET description END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_17~ BEGIN
	LOCAL_SET strref_1 = 10170003 // ~de restaurer %value% %toTheTarget%~
	LOCAL_SET strref_2 = strref_1 + 1 // ~d'infliger %value% %toTheTarget%~
	LOCAL_SET type = parameter2 BAND 65535
	LOCAL_SET subType = parameter2 / 65535

	PATCH_IF type == 0 OR type == 2 BEGIN
		LPF ~opcode_17_common~ INT_VAR strref_1 strref_2 RET description END
	END
	ELSE BEGIN
		SET damageAmount = parameter1
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END
		LPF ~opcode_mod~ INT_VAR strref = 10170022 STR_VAR value = EVAL ~%value%~ RET description END // ~les points de vie actuels~
	END
END

DEFINE_PATCH_FUNCTION ~opcode_17_common~ INT_VAR strref_1 = 0 strref_2 = 0 RET description BEGIN
	// TODO
	// Dissipe tous les effets non permanent_after_death puis la soigne
	SET purgeEff = subType BAND BIT1 > 0
	// l'opcode s'exécute dans cet ordre (si flag actif) : rez => purge => soin

	PATCH_IF purgeEff BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: subType non gere : %subType%.~ END
	END

	SET damageAmount = parameter1
	LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END

	PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF ~%value%~ STRING_CONTAINS_REGEXP ~^-~ BEGIN
			INNER_PATCH_SAVE value ~%value%~ BEGIN
				REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
				PATCH_IF type == 2 BEGIN
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~$~ ~ %~
				END
			END

			PATCH_IF parameter2 == MOD_TYPE_cumulative AND NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
			END
			ELSE BEGIN
				PATCH_IF ~%value%~ STRING_EQUAL ~1~ OR ~%value%~ STRING_EQUAL ~1 %~ BEGIN
					LPF ~getTranslation~ INT_VAR strref = 600170 opcode RET valueType = string END // ~point de vie~
				END
				ELSE BEGIN
					LPF ~getTranslation~ INT_VAR strref = 600171 opcode RET valueType = string END // ~points de vie~
				END
				SPRINT value @102165 // ~%value% %valueType%~
			END

			LPF ~getTranslation~ INT_VAR strref = strref_1 opcode RET description = string END // ~Restaure %value% %toTheTarget%~
		END
		ELSE BEGIN
			INNER_PATCH_SAVE value ~%value%~ BEGIN
				REPLACE_TEXTUALLY EVALUATE_REGEXP ~^-~ ~~
				PATCH_IF type == 2 BEGIN
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~$~ ~ %~
				END
			END

			PATCH_IF parameter2 == MOD_TYPE_cumulative AND NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
			END
			ELSE BEGIN
				PATCH_IF ~%value%~ STRING_EQUAL ~1~ OR ~%value%~ STRING_EQUAL ~1 %~ BEGIN
					LPF ~getTranslation~ INT_VAR strref = 600172 opcode RET valueType = string END // ~point de dégât~
				END
				ELSE BEGIN
					LPF ~getTranslation~ INT_VAR strref = 600173 opcode RET valueType = string END // ~points de dégâts~
				END
				SPRINT value @102165 // ~%value% %valueType%~
			END

			LPF ~getTranslation~ INT_VAR strref = strref_2 opcode RET description = string END // ~Inflige %value% %toTheTarget%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_17_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF (parameter2 / 65535) BAND BIT0 BEGIN
			SET opcode = 32
			SET parameter1 = 0
			SET parameter2 = 0
			LPM ~add_opcode~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_17_is_valid~ BEGIN
	LOCAL_SET type = parameter2 BAND 65535
	PATCH_IF type < CURRENT_HP_MOD_TYPE_cumulative OR type > CURRENT_HP_MOD_TYPE_percentage BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %type%.~ END
	END
END

DEFINE_PATCH_FUNCTION ~opcode_17_typed_value~ INT_VAR value = 0 RET strref BEGIN
	SET strref = 600170 // ~point de vie~

	PATCH_IF value > 1 BEGIN
		SET strref = 600171 // ~points de vie~
	END
	ELSE PATCH_IF value == 0 - 1 BEGIN
		SET strref = 600172 // ~point de dégât~
	END
	ELSE PATCH_IF value < 0 - 1 BEGIN
		SET strref = 600173 // ~points de dégâts~
	END
END

/* ------------------------------ *
 * Stat: Maximum HP Modifier [18] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_18~ BEGIN
	LPM ~opcode_18_common~
	PATCH_IF healOnlyMaxPV == 1 BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 10180001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Points de vie maximum~
	END
	ELSE BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 10180003 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Points de vie maximum~
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
	PATCH_IF parameter2 == MOD_TYPE_cumulative AND NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
		SPRINT value ~%complex_value%~
	END
	ELSE BEGIN
		LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount RET value = damage END
		INNER_PATCH_SAVE value ~%value%~ BEGIN
			REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
		END
	END
END

/*
DEFINE_PATCH_MACRO ~opcode_18_not_cumulative~ BEGIN
	PATCH_IF isCumulative == 0 AND is_ee == 1 AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @101185 // ~%description% (non cumulatif)~
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
	LPF ~opcode_mod~ INT_VAR strref = 10190001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Intelligence~
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

DEFINE_PATCH_MACRO ~opcode_20_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF parameter2 == 1 BEGIN
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_match_vars~
				PATCH_IF position != match_position BEGIN
					LPM ~opcode_match_except_parameter2~

					PATCH_IF match BEGIN
						SET $positions(~%position%~) = 1
						SET count += 1
						LPF ~delete_opcode~
		                    INT_VAR opcode match_position
		                    RET $opcodes(~20~) = count
		                    RET_ARRAY EVAL ~opcodes_20~ = opcodes_xx
		                END
						// Bug où il reste toujours un item dans le tableau si c'était le dernier
						// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
						PATCH_IF $opcodes(~20~) == 0 BEGIN
							CLEAR_ARRAY ~opcodes_20~
						END
					END
				END
			END
		END
	END
END

/* ------------------------ *
 * Stat: Lore Modifier [21] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_21~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10210001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Connaissance~
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
	LPF ~opcode_mod~ INT_VAR strref = 10220001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Chance~
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
		SPRINT description @10230003 // ~Rétabli le moral %ofTheTarget%~
	END
	ELSE BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 10230001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Moral~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_23~ BEGIN
	LPM ~opcode_23_common~

	PATCH_IF parameter2 == MOD_TYPE_flat AND parameter1 == 10 BEGIN
		SPRINT description @10230004 // ~de rétablir le moral %ofTheTarget%~
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

	PATCH_IF parameter2 == MOD_TYPE_flat AND parameter1 == 10 BEGIN
		SPRINT description @10230003 // ~Le moral %ofTheTarget% ne peut flancher~
	END
	ELSE BEGIN
		LPF ~opcode_target~ INT_VAR strref = 10230002 RET description END // ~le moral~
	END

END

DEFINE_PATCH_MACRO ~opcode_23_group~ BEGIN
	// Groupement Reset moral + Immunité contre la modification du moral +
	// Immunité contre la modification du niveau de rupture de moral
	LOCAL_SET searchOpcode = 101
	LOCAL_SET found = 0b0
	LOCAL_SET groupDuration = 0
	LOCAL_SET position23 = 0
	LOCAL_SET position106 = 0
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET currentPosition = position
		PATCH_IF NOT is_ee OR special == 0 OR (parameter1 == 10 AND parameter2 == MOD_TYPE_flat) BEGIN
			PATCH_PHP_EACH EVAL ~opcodes_%searchOpcode%~ AS data => _ BEGIN
				LPM ~data_to_vars~
				SET opcode = searchOpcode
				PATCH_IF parameter2 == 23 AND (groupDuration == 0 OR groupDuration == duration) BEGIN
					SET found |= 0b01
					SET groupDuration = duration
					SET position23 = position
				END
				ELSE PATCH_IF parameter2 == 106 AND (groupDuration == 0 OR groupDuration == duration) BEGIN
					SET found |= 0b10
					SET groupDuration = duration
					SET position106 = position
				END
				PATCH_IF found == 0b11 BEGIN
					SET found = 0b111 // ~ nouvelle entrée impossible

					SET opcode = searchOpcode
					LPF ~delete_opcode~
						INT_VAR opcode
							match_parameter2 = 23
							match_position = position23
                        STR_VAR match_macro = ~opcode_match_parameter2_and_position~
						RET $opcodes(~%opcode%~) = count
						RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
					END

					SET opcode = 106
					// retrait bonus : rupture de moral fixée à 1 (non nécessaire au groupe mais redondant)
					LPF ~delete_opcode~
						INT_VAR opcode
							match_parameter1 = 1
							match_parameter2 = 1
                        STR_VAR match_macro = ~opcode_match_parameter1_and_parameter2~
						RET $opcodes(~%opcode%~) = count
						RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
					END

					// retrait de l'opcode actuel
					SET opcode = 23
					LPF ~delete_opcode~
						INT_VAR opcode match_position = currentPosition
						RET $opcodes(~%opcode%~) = count
						RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
					END
				END
			END
		END
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
DEFINE_PATCH_MACRO ~opcode_self_24~ BEGIN
	LPM ~opcode_target_24~
END

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
	SET frequency = 1
	SET p4IsActive = isExternal AND parameter4 != 0 AND is_ee
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
				SET amount = 1
			END
		END
	END
	PATCH_IF frequency < 1 BEGIN
		SET frequency = 1
	END

	LPF ~get_frequency_duration~ INT_VAR duration = frequency RET strDuration = frequency END

	PATCH_IF amount == 1 AND frequency >= 1 BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Empoisonne %theTarget%, lui infligeant 1 point de dégâts %strDuration%~
	END
	ELSE PATCH_IF amount > 1 AND frequency >= 1 BEGIN
		SET strref += 1
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Empoisonne %theTarget%, lui infligeant %amount% points de dégâts %strDuration%~
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
		LPF ~add_log_error~ STR_VAR type = ~warning~ message = EVAL ~Opcode %opcode%: This effect does not work with Timing Mode %timingMode%.~ END
	END
	PATCH_IF parameter2 > 4 OR parameter2 < 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR type = ~warning~ message = EVAL ~Opcode %opcode%: This effect does no effect with %parameter2%.~ END
	END
	PATCH_IF NOT isExternal AND parameter2 == 4 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Type 4 can only be used in external eff files.~ END
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
	SET resistName = 10270001 // ~Résistance à l'acide~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_27~ BEGIN
	SET resistName = 10270001 // ~Résistance à l'acide~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_27~ BEGIN
	SET resistName = 10270001 // ~Résistance à l'acide~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_27~ BEGIN
	LPM ~opcode_self_probability_27~
END

DEFINE_PATCH_MACRO ~opcode_27_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_27_group~ BEGIN
	LOCAL_SET opcode = 27
	LOCAL_SET newOpcode = 503 // ~Résistance aux dégâts élémentaires~

	PATCH_IF shrink_resistances BEGIN
		LPM ~opcode_group_all_resistances~

		PATCH_DEFINE_ARRAY listOpcodes BEGIN 28 29 30 END

		SET opcode = 27
		LPM ~group_opcode_with_same_parameters~
	END
END

/* ----------------------------------- *
 * Stat: Cold Resistance Modifier [28] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_28~ BEGIN
	SET resistName = 10280001 // ~Résistance au froid~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_28~ BEGIN
	SET resistName = 10280001 // ~Résistance au froid~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_28~ BEGIN
	SET resistName = 10280001 // ~Résistance au froid~
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
	SET resistName = 10290001 // ~Résistance à l'électricité~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_29~ BEGIN
	SET resistName = 10290001 // ~Résistance à l'électricité~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_29~ BEGIN
	SET resistName = 10290001 // ~Résistance à l'électricité~
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
	SET resistName = 10300001 // ~Résistance au feu~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_30~ BEGIN
	SET resistName = 10300001 // ~Résistance au feu~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_30~ BEGIN
	SET resistName = 10300001 // ~Résistance au feu~
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
	SET resistName = 10310001 // ~Résistance aux dégâts magiques~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_31~ BEGIN
	SET resistName = 10310001 // ~Résistance aux dégâts magiques~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_31~ BEGIN
	SET resistName = 10310001 // ~Résistance aux dégâts magiques~
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

DEFINE_PATCH_MACRO ~opcode_target_probability_33~ BEGIN
	LPM ~opcode_self_probability_33~
END

DEFINE_PATCH_MACRO ~opcode_33_is_valid~ BEGIN
	PATCH_IF is_ee BEGIN
		LPM ~opcode_modstat3_is_valid~
	END
	ELSE BEGIN
		LPM ~opcode_modstat2_is_valid~
	END
END

DEFINE_PATCH_MACRO ~opcode_33_group~ BEGIN
	LOCAL_SET opcode = 33
	LOCAL_SET newOpcode = 325

	PATCH_IF shrink_saves_throws BEGIN
		PATCH_DEFINE_ARRAY listOpcodes BEGIN 34 35 36 37 END

		LPM ~group_opcode_with_same_parameters~
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

DEFINE_PATCH_MACRO ~opcode_target_probability_34~ BEGIN
	LPM ~opcode_self_probability_34~
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

DEFINE_PATCH_MACRO ~opcode_target_probability_35~ BEGIN
	LPM ~opcode_self_probability_35~
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

DEFINE_PATCH_MACRO ~opcode_target_probability_36~ BEGIN
	LPM ~opcode_self_probability_36~
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

DEFINE_PATCH_MACRO ~opcode_target_probability_37~ BEGIN
	LPM ~opcode_self_probability_37~
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

DEFINE_PATCH_MACRO ~opcode_self_probability_42~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET level = parameter2
	LOCAL_SET spellLevelMax = 9

	LPF ~opcode_self_42_62~ INT_VAR level amount startStrref = 10420011 RET description END
END

DEFINE_PATCH_MACRO ~opcode_42_group~ BEGIN
	LOCAL_SET initOpcode = opcode
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions_already_check~ BEGIN END

	PATCH_PHP_EACH EVAL ~opcodes_%initOpcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET searchP1 = parameter1
		SET newP2 = 0b0
		CLEAR_ARRAY positions
		PATCH_PHP_EACH EVAL ~opcodes_%initOpcode%~ AS data => _ BEGIN
			LPM ~data_to_match_vars~
			PATCH_IF parameter2 == 0 BEGIN
				PATCH_IF match_parameter1 == searchP1 AND parameter2 == match_parameter2 AND match_probability1 == probability1 AND match_probability2 == probability2 AND NOT VARIABLE_IS_SET $positions_already_check(~%match_position%~) BEGIN
					// On retire l'opcode de ceux à checker dans les futures itérations
					SET $positions_already_check(~%match_position%~) = 1
					// On ajoute l'opcode courant à ceux qui seront désactivés
					SET $positions(~%match_position%~) = initOpcode
					// P2 retiré
					SET $positions(~%position%~) = initOpcode
					SET newP2 |= match_parameter2
				END
			END
			ELSE BEGIN
				PATCH_IF match_parameter1 == searchP1 AND match_parameter2 >= 1 AND match_parameter2 <= 256 AND match_probability1 == probability1 AND match_probability2 == probability2 AND NOT VARIABLE_IS_SET $positions_already_check(~%match_position%~) BEGIN
					// On retire l'opcode de ceux à checker dans les futures itérations
					SET $positions_already_check(~%match_position%~) = 1
					// On ajoute l'opcode courant à ceux qui seront désactivés
					SET $positions(~%match_position%~) = initOpcode
					// P2 retiré
					SET $positions(~%position%~) = initOpcode
					SET newP2 |= match_parameter2
				END
			END
		END
		PATCH_IF newP2 > 0 BEGIN
			// Suppression des effets similaires
			PATCH_PHP_EACH positions AS position1 => opcode BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position1
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
			// FIXME: à ce stade les données ne sont pas spécifiquement sauvegardées, reliquat du PATCH_PHP_EACH précédent
			// Fonctionnel dans les cas généraux
			SET opcode = initOpcode
			SET parameter2 = newP2
			SET parameter1 = searchP1
			SET position += 100
			LPM ~add_opcode~
		END
	END
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
	LPF ~opcode_mod~ INT_VAR strref = 10440001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Force~
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
	LPF ~opcode_mod~ INT_VAR strref = 10490001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Sagesse~
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
	LPF ~opcode_mod~ INT_VAR strref = 10540001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~TAC0~
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
	SET death_type = 0x4
	SET description_strref = $death_to_strref(~%death_type%~)
	LPM ~opcode_55_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_55~ BEGIN
	LPM ~opcode_target_probability_55~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_55~ BEGIN
	SET death_type = 0x4
	SET description_strref = $death_to_strref(~%death_type%~)
	SET description_strref += 100
	LPM ~opcode_55_common~
END

DEFINE_PATCH_MACRO ~opcode_55_common~ BEGIN
	PATCH_IF ~%target_type%~ STRING_EQUAL ~~ AND (NOT VARIABLE_IS_SET versus OR %versus% STRING_EQUAL ~~) BEGIN
		PATCH_IF parameter1 != 0 BEGIN
			LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET theTarget = idName END
			SPRINT pluralPronoun @100020 // ~les~
			SPRINT theTarget EVAL ~%pluralPronoun% %theTarget%~
			LPM ~add_target_level~
		END
	END
	SPRINT description (AT description_strref)
END

DEFINE_PATCH_MACRO ~opcode_55_is_valid~ BEGIN
	LOCAL_SET death_type = 0x4
	LPM ~opcode_idscheck9_is_valid~
	PATCH_IF NOT VARIABLE_IS_SET $death_to_strref(~%death_type%~) BEGIN
		isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Mort a gerer : %death_type%~ END
	END
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

DEFINE_PATCH_MACRO ~opcode_58_group~ BEGIN
	// Implicitement, la dissipation à la magie dissipe également la surdité et la débilité mentale
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET opcode = 77
		LPF ~delete_opcode~
			INT_VAR opcode
				match_diceCount = diceCount
				match_diceSides = diceSides
				match_power = power
				match_probability1 = probability1
				match_probability2 = probability2
				match_resistance = resistance
				match_target = target
				match_saveBonus = saveBonus
				match_saveType = saveType
            STR_VAR match_macro = ~opcode_match_diceCount_and_diceSides_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_target~
			RET $opcodes(~%opcode%~) = count
			RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
		END
		SET opcode = 81
		LPF ~delete_opcode~
			INT_VAR opcode
				match_diceCount = diceCount
				match_diceSides = diceSides
				match_power = power
				match_probability1 = probability1
				match_probability2 = probability2
				match_resistance = resistance
				match_target = target
				match_saveBonus = saveBonus
				match_saveType = saveType
            STR_VAR match_macro = ~opcode_match_diceCount_and_diceSides_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_target~
			RET $opcodes(~%opcode%~) = count
			RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
		END
		SET opcode = 58
	END
END

/* --------------------------- *
 * Stat: Stealth Modifier [59] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_59~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 10590001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Déplacement silencieux~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_59~ BEGIN
	LPF ~opcode_probability_percent~ INT_VAR strref = 10590002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le Déplacement silencieux~
END

DEFINE_PATCH_MACRO ~opcode_target_59~ BEGIN
	LPF ~opcode_target_percent~ INT_VAR strref = 10590002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le Déplacement silencieux~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_59~ BEGIN
	LPM ~opcode_self_probability_59~
END

DEFINE_PATCH_MACRO ~opcode_59_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_59_group~ BEGIN
	LOCAL_SET newOpcode = 500
	LOCAL_SET opcode = 59

	PATCH_IF shrink_thief_skills BEGIN
		PATCH_DEFINE_ARRAY listOpcodes BEGIN 90 91 92 275 276 277 END

		LPM ~group_opcode_with_same_parameters~
	END
END

/* ------------------------ *
 * Stat: Miscast Magic [60] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_60~ BEGIN
	LOCAL_SET value = parameter1 BAND 255
	LOCAL_SET type = parameter2

	LPM ~opcode_60_common~

	PATCH_IF spellTypes == 7 BEGIN
		SPRINT description @10600001 // ~Provoque l'échec de %percent% des sorts~
	END
	ELSE BEGIN
		SPRINT description @10600002 // ~Provoque l'échec de %percent% des sorts %spellType%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_60~ BEGIN
	LOCAL_SET value = parameter1 BAND 255

	LPM ~opcode_60_common~

	PATCH_IF spellTypes == 7 BEGIN
		SPRINT description @10600003 // ~Provoque l'échec de %percent% des sorts lancés par %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10600004 // ~Provoque l'échec de %percent% des sorts %spellType% lancés par %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_60~ BEGIN
	LOCAL_SET value = parameter1 BAND 255

	LPM ~opcode_60_common~

	PATCH_IF spellTypes == 7 BEGIN
		SPRINT description @10600005 // ~de provoquer l'échec de %percent% des sorts lancés par %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10600006 // ~de provoquer l'échec de %percent% des sorts %spellType% lancés par %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_60_common~ BEGIN
	SET spellTypes = 0

	PATCH_IF parameter2 > 2 BEGIN
		SET parameter2 -= 3
	END

	SET spellTypes = custom_int > 0 ? custom_int : (1 << parameter2)
	LPF ~get_spell_type_str~ INT_VAR value = spellTypes RET spellType END
    SPRINT percent @10002 // ~%value% %~
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

DEFINE_PATCH_MACRO ~opcode_60_group~ BEGIN
	LOCAL_SET group = 1
	LOCAL_SET newSpellType = 0
	LOCAL_SET spellType = 0

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~

		PATCH_IF parameter2 > 2 BEGIN
			SET parameter2 -= 3
		END

		SET group = 0
		SET newSpellType = 1 << %parameter2%
		CLEAR_ARRAY positions
		PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN
			~%parameter2%~ => ~%position%~
		END
		PATCH_FOR_EACH spellType IN 0 1 2 BEGIN
			LPF ~get_opcode_position~
				INT_VAR opcode
					match_position     = position
					match_custom_int   = 0
					match_target       = target
					match_probability1 = probability1
					match_probability2 = probability2
					match_parameter1   = parameter1
					match_parameter2   = spellType
					match_parameter3   = parameter3
					match_parameter4   = parameter4
					match_timingMode   = timingMode
					match_resistance   = resistance
					match_duration     = duration
					match_power        = power
			        match_diceCount    = diceCount
			        match_diceSides    = diceSides
					match_saveType     = saveType
					match_saveBonus    = saveBonus
					match_special      = special
				STR_VAR match_macro = ~opcode_match_opcode_60_145_group~
				RET opcodePosition = position
			END

			PATCH_IF opcodePosition >= 0 BEGIN
				SET group = 1
				SET newSpellType |= 1 << %spellType%
				SET $positions(~%spellType%~) = opcodePosition
			END
		END
		PATCH_IF group == 1 BEGIN
			PATCH_PHP_EACH positions AS _ => position1 BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position1
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
	        SET custom_int = newSpellType
	        LPM ~add_opcode~
		END
	END
END

/* --------------------------------------- *
 * Spell: Priest Spell Slots Modifier [62] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_62~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET level = parameter2
	LOCAL_SET spellLevelMax = 7
	LOCAL_SET spellTypes = 1 << 1

	LPF ~opcode_self_42_62~ INT_VAR level amount spellTypes startStrref = 10620001 RET description END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_62~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET level = parameter2
	LOCAL_SET spellLevelMax = 9
	LOCAL_SET spellTypes = 1 << 1

	LPF ~opcode_self_42_62~ INT_VAR level amount spellTypes startStrref = 10620011 RET description END
END

DEFINE_PATCH_MACRO ~opcode_62_group~ BEGIN
	LPM ~opcode_42_group~
END

/* ----------------------- *
 * State: Infravision [63] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_63~ BEGIN
	SPRINT description @10630001 // ~Infravision~
END

DEFINE_PATCH_MACRO ~opcode_target_63~ BEGIN
	SPRINT description @10630011 // ~Octroie la capacité d'infravision %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_63~ BEGIN
	SPRINT description @10630021 // ~d'octroyer la capacité d'infravision~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_63~ BEGIN
	SPRINT description @10630031 // ~d'octroyer la capacité d'infravision %toTheTarget% ~
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
	LOCAL_SET strref = 0
	LOCAL_SET amount = custom_int > 1 ? custom_int : 1
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END

	PATCH_IF NOT ~%creatureName%~ STRING_EQUAL ~~ BEGIN
		// Allégiance de la créature non modifiée, donc intéressant
		PATCH_IF parameter2 == 2 OR parameter2 == 4 OR parameter2 >= 6 BEGIN
			LPF ~get_creature_allegiance~ STR_VAR file = EVAL ~%resref%~ RET allegiance END
			PATCH_IF allegiance >= 200 BEGIN // EVILCUTOFF
				SET strref = 10670002 // ~Invoque une créature hostile (%creatureName%)~
			END
			ELSE PATCH_IF allegiance <= 30 BEGIN // GOODCUTOFF
				SET strref = 10670005 // ~Invoque une créature alliée (%creatureName%)~
			END
			ELSE BEGIN
				SET strref = 10670006 // ~Invoque une créature neutre (%creatureName%)~
			END
		END
		// Allégiance variable selon celle de la cible, donc pas de précision
		ELSE BEGIN
			SET strref = 10670001 // ~Invoque une créature (%creatureName%)~
		END
		PATCH_IF amount > 1 OR NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
				SPRINT amount ~%custom_str%~
			END
			SET strref += 10
		END
		SPRINT description (AT strref)
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_67~ BEGIN
	LOCAL_SET strref = 0
	LOCAL_SET amount = custom_int > 1 ? custom_int : 1
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END

	PATCH_IF NOT ~%creatureName%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF parameter2 == 2 OR parameter2 == 4 OR parameter2 >= 6 BEGIN
			LPF ~get_creature_allegiance~ STR_VAR file = EVAL ~%resref%~ RET allegiance END
			PATCH_IF allegiance >= 200 BEGIN // EVILCUTOFF
				SET strref = 10670004 // ~d'invoquer une créature hostile (%creatureName%)~
			END
			ELSE PATCH_IF allegiance <= 30 BEGIN // GOODCUTOFF
				SET strref = 10670007 // ~d'invoquer une créature alliée (%creatureName%)~
			END
			ELSE BEGIN
				SET strref = 10670008 // ~d'invoquer une créature neutre (%creatureName%)~
			END
		END
		ELSE BEGIN
			SET strref = 10670003 // ~d'invoquer une créature (%creatureName%)~
		END
		PATCH_IF amount > 1 OR NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
				SPRINT amount ~%custom_str%~
			END
			SET strref += 10
		END
		SPRINT description (AT strref)
	END
END

DEFINE_PATCH_MACRO ~opcode_67_group~ BEGIN
	LOCAL_SET countProbabilityCreature = 0
	LPM ~opcode_group_by_target~
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF probability == 100 BEGIN
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_match_vars~
				LPM ~opcode_match_opcode_67_group~
				PATCH_IF match == 1 BEGIN
					LPF ~delete_opcode~
	                    INT_VAR opcode match_position
	                    RET $opcodes(~67~) = count
	                    RET_ARRAY EVAL ~opcodes_67~ = opcodes_xx
	                END
					LPF ~delete_opcode~
	                    INT_VAR opcode match_position = position
	                    RET $opcodes(~67~) = count
	                    RET_ARRAY EVAL ~opcodes_67~ = opcodes_xx
	                END
					// Bug où il reste toujours un item dans le tableau si c'était le dernier
					// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
					PATCH_IF $opcodes(~67~) == 0 BEGIN
			            CLEAR_ARRAY ~opcodes_67~
			        END
			        SET countProbabilityCreature += 1
				END
			END
			// Si on a trouvé au moins une même créature qui est invoquée aléatoirement
			PATCH_IF countProbabilityCreature > 0 BEGIN
				SET amountMin = custom_int > 1 ? custom_int : 1
				SET amountMax = amountMin + countProbabilityCreature
				SPRINT custom_str @101130 // ~entre %amountMin% et %amountMax%~
		        LPM ~add_opcode~
			END
		END
	END
END

/* ------------------------------ *
 * Summon: Unsummon Creature [68] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_68~ BEGIN
	LPM ~opcode_target_68~
END

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
	PATCH_IF use_short_effect_description BEGIN
		SPRINT description @10690001 // ~Non-détection~
	END
	ELSE BEGIN
		SPRINT description @10690004 // ~Rend %theTarget% indétectable par des moyens magiques tels que la Détection de l'invisibilité et autres divinations~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_69~ BEGIN
	PATCH_IF use_short_effect_description BEGIN
		SPRINT description @10690003 // ~de lancer non-détection sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10690005 // ~de rendre %theTarget% indétectable par des moyens magiques tels que la Détection de l'invisibilité et autres divinations~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_69~ BEGIN
	PATCH_IF use_short_effect_description BEGIN
		SPRINT description @10690002 // ~Lance non-détection sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @10690004 // ~Rend %theTarget% indétectable par des moyens magiques tels que la Détection de l'invisibilité et autres divinations~
	END
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
	LOCAL_SET descStrref = 10710001 + parameter2 // ~Inverse le sexe %ofTheTarget%~

	LPM ~opcode_71_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_71~ BEGIN
	LOCAL_SET descStrref = 10710011 + parameter2 // ~d'inverser le sexe %ofTheTarget%~

	LPM ~opcode_71_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_71~ BEGIN
	LPM ~opcode_self_probability_71~
END

DEFINE_PATCH_MACRO ~opcode_target_71~ BEGIN
	LPM ~opcode_self_71~
END

DEFINE_PATCH_MACRO ~opcode_71_common~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		LPF ~get_ids_strref~ INT_VAR entry = parameter1 file = ~7~ RET strref END
		SET strref += 500 // mise au singulier
		LPF ~getTranslation~ INT_VAR strref opcode RET genderType = string END
	END
	LPF ~getTranslation~ INT_VAR strref = descStrref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_71_is_valid~ BEGIN
	PATCH_IF parmameter2 != MOD_TYPE_cumulative AND parameter2 != MOD_TYPE_flat BEGIN
		// Sans intérêt en terme de gameplay mais pas sans effet pour autant
		SET isValid = 0
	END
END

/* -------------------------------- *
 * Stat: Extra Damage Modifier [73] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_73~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 10730001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Dégâts~
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

DEFINE_PATCH_MACRO ~opcode_74_is_valid~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Warning ! Parameter2 %parameter2% have strong impact on the duration.~ END
	END
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
	PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
		SPRINT theAttributes ~%custom_str%~
		SET strref += 40
		PATCH_IF amount < 0 BEGIN
			SET amount = ABS amount
			SET strref += 10
		END
	END
	ELSE BEGIN
		SET type = parameter2

		PATCH_IF type >= 0 AND type <= 3 BEGIN
			// En théorie toutes les versions infligent du dégâts de poison, je laisse dans le doute
			PATCH_IF is_ee == 1 BEGIN
				SET strref += 30
			END
			LPM ~opcode_25_common~
		END
		ELSE PATCH_IF type >= 4 AND type <= 9 BEGIN
			SET strref += type
			PATCH_IF amount < 0 BEGIN
				SET amount = ABS amount
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
			SET strref += type
			PATCH_IF amount < 0 BEGIN
				SET amount = ABS amount
			END
			ELSE BEGIN
				SET strref += 10
			END
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
			 timingMode == TIMING_permanent_after_death) AND duration == 0 AND parameter2 <= 3 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR type = ~warning~ message = EVAL ~Opcode %opcode%: This effect does not work with Timing Mode %timingMode%.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_78_group~ BEGIN
	LOCAL_SPRINT and @100021 // ~et~
	PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF parameter2 >= 4 AND parameter2 <= 9 BEGIN
			CLEAR_ARRAY positions
			SET group = 0
			SET strref = 10780160 + parameter2
			SPRINT attribute (AT strref)
			SET $positions(~%attribute%~) = position
			PATCH_FOR_EACH attribute IN 4 5 6 7 8 9 BEGIN
				LPF ~get_opcode_position~
					INT_VAR opcode
						match_position     = position
						match_target       = target
						match_probability1 = probability1
						match_probability2 = probability2
						match_parameter1   = parameter1
						match_parameter2   = attribute
						match_parameter3   = parameter3
						match_parameter4   = parameter4
						match_timingMode   = timingMode
						match_resistance   = resistance
						match_duration     = duration
						match_power        = power
				        match_diceCount    = diceCount
				        match_diceSides    = diceSides
						match_saveType     = saveType
						match_saveBonus    = saveBonus
						match_special      = special
					STR_VAR match_macro = ~opcode_match_opcode_78_group~
					RET opcodePosition = position
				END
				PATCH_IF opcodePosition >= 0 BEGIN
					SET group = 1
					SET strref = 10780160 + attribute
					SPRINT attribute (AT strref)
					SET $positions(~%attribute%~) = opcodePosition
				END
			END
			PATCH_IF group == 1 BEGIN
				PATCH_PHP_EACH positions AS _ => position1 BEGIN
					LPF ~delete_opcode~
						INT_VAR opcode match_position = position1
						RET $opcodes(~%opcode%~) = count
						RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
					END
				END
				// Bug où il reste toujours un item dans le tableau si c'était le dernier
				// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
				PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
		            CLEAR_ARRAY ~opcodes_%opcode%~
		        END
				LPF ~implode~ STR_VAR array_name = ~positions~ glue = ~, ~ final_glue = ~ %and% ~ RET attributes = text END
		        SPRINT custom_str ~%attributes%~
		        SET parameter2 = 0 - 1
		        LPM ~add_opcode~
			END
		END
	END
END

/* ------------------ *
 * Cure: Disease [79] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_79~ BEGIN
	SPRINT description @10790001 // ~Guérison des maladies~
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

DEFINE_PATCH_MACRO ~opcode_79_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		// Ajout de l'opcode 77, dissipation de la débilité mentale
		SET opcode = 77
		PATCH_IF NOT VARIABLE_IS_SET $opcodes(~%opcode%~) OR $opcodes(~%opcode%~) == 0 BEGIN
			LPM ~add_opcode~
		END
		SET opcode = 79
	END
END

/* ------------- *
 * Deafness [80] *
 * ------------- */
DEFINE_PATCH_MACRO ~opcode_self_80~ BEGIN
	PATCH_IF NOT use_short_effect_description BEGIN
		SPRINT description @10800001 // ~Surdité~
	END
	ELSE BEGIN
		SET parameter1 = 50
		SET custom_int = 3 // profanes et divins
		LPM ~opcode_self_60~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_80~ BEGIN
	PATCH_IF NOT use_short_effect_description BEGIN
		SPRINT description @10800003 // ~d'assourdir %theTarget%~
	END
	ELSE BEGIN
		SET parameter1 = 50
		SET custom_int = 3 // profanes et divins
		LPM ~opcode_self_probability_60~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_80~ BEGIN
	PATCH_IF NOT use_short_effect_description BEGIN
		SPRINT description @10800002 // ~Assourdit %theTarget%~
	END
	ELSE BEGIN
		SET parameter1 = 50
		SET custom_int = 3 // profanes et divins
		LPM ~opcode_target_60~
	END
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
	LOCAL_SET strref = 10830001 // ~Immunité contre les %projectiles%~
	LPM ~opcode_83_common~
END

DEFINE_PATCH_MACRO ~opcode_target_83~ BEGIN
	LOCAL_SET strref = 10830003 // ~Immunise %theTarget% contre les %projectiles%~
	LPM ~opcode_83_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_83~ BEGIN
	LOCAL_SET strref = 10830002 // ~d'être immunisé contre les %projectiles%~
	LPM ~opcode_83_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_83~ BEGIN
	LOCAL_SET strref = 10830004 // ~d'immuniser %theTarget% contre les %projectiles%~
	LPM ~opcode_83_common~
END

DEFINE_PATCH_MACRO ~opcode_83_common~ BEGIN
	LPF ~get_projectile_name~ INT_VAR projectile = parameter2 RET projref END

	PATCH_IF projref > 0 BEGIN
		LPF ~getTranslation~ INT_VAR strref = projref opcode RET projectiles = string END
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
END

DEFINE_PATCH_MACRO ~opcode_83_group~ BEGIN
	LOCAL_SET projectile = 0
	PATCH_PHP_EACH EVAL ~opcodes_83~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET projectile = parameter2 + 1
		// Supprimer des immunités aux sorts qui utilisent le même projectile
		PATCH_PHP_EACH EVAL ~opcodes_206~ AS data => _ BEGIN
			LPM ~data_to_match_vars~
			PATCH_IF FILE_EXISTS_IN_GAME ~%match_resref%.spl~ BEGIN
				INNER_PATCH_FILE ~%match_resref%.spl~ BEGIN
					READ_SHORT (0x72 + SPL_HEAD_projectile) match_projectile
					PATCH_IF projectile == match_projectile BEGIN
						LPF ~delete_opcode~
							INT_VAR opcode = 206 match_position
							RET $opcodes(~206~) = count
							RET_ARRAY EVAL ~opcodes_206~ = opcodes_xx
						END
						// Bug où il reste toujours un item dans le tableau si c'était le dernier
						// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
						PATCH_IF $opcodes(~206~) == 0 BEGIN
				            CLEAR_ARRAY ~opcodes_206~
				        END
					END
				END
			END
		END
	END
END

/* ------------------------------------------- *
 * Stat: Magical Fire Resistance Modifier [84] *
 * ------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_84~ BEGIN
	SET resistName = 10840001 // ~Résistance aux dégâts de feu magiques~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_84~ BEGIN
	SET resistName = 10840001 // ~Résistance aux dégâts de feu magiques~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_84~ BEGIN
	SET resistName = 10840001 // ~Résistance aux dégâts de feu magiques~
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
	SET resistName = 10850001 // ~Résistance aux dégâts de froid magiques~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_85~ BEGIN
	SET resistName = 10850001 // ~Résistance aux dégâts de froid magiques~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_85~ BEGIN
	SET resistName = 10850001 // ~Résistance aux dégâts de froid magiques~
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
	SET resistName = 10860001 // ~Résistance aux dégâts tranchants~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_86~ BEGIN
	SET resistName = 10860001 // ~Résistance aux dégâts tranchants~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_86~ BEGIN
	SET resistName = 10860001 // ~Résistance aux dégâts tranchants~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_86~ BEGIN
	LPM ~opcode_self_probability_86~
END

DEFINE_PATCH_MACRO ~opcode_86_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_86_group~ BEGIN
	LOCAL_SET opcode = 86
	LOCAL_SET newOpcode = 504 // ~Résistance aux dégâts physiques~

	PATCH_IF shrink_resistances BEGIN
		LPM ~opcode_group_all_resistances~

		PATCH_DEFINE_ARRAY listOpcodes BEGIN 87 88 89 END

		SET opcode = 86
		LPM ~group_opcode_with_same_parameters~
	END
END

/* --------------------------------------- *
 * Stat: Crushing Resistance Modifier [87] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_87~ BEGIN
	SET resistName = 10870001 // ~Résistance aux dégâts contondants~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_87~ BEGIN
	SET resistName = 10870001 // ~Résistance aux dégâts contondants~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_87~ BEGIN
	SET resistName = 10870001 // ~Résistance aux dégâts contondants~
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
	SET resistName = 10880001 // ~Résistance aux dégâts perforants~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_88~ BEGIN
	SET resistName = 10880001 // ~Résistance aux dégâts perforants~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_88~ BEGIN
	SET resistName = 10880001 // ~Résistance aux dégâts perforants~
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
	SET resistName = 10890001 // ~Résistance aux dégâts de projectiles~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_89~ BEGIN
	SET resistName = 10890001 // ~Résistance aux dégâts de projectiles~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_89~ BEGIN
	SET resistName = 10890001 // ~Résistance aux dégâts de projectiles~
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
	LPF ~opcode_mod~ INT_VAR strref = 10930001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Fatigue~
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
	LPF ~opcode_mod~ INT_VAR strref = 10940001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Ivresse~
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
	LPF ~opcode_mod~ INT_VAR strref = 10950001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Pistage~
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
	LPF ~opcode_mod~ INT_VAR strref = 10960001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Niveau~
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
	LPF ~opcode_mod~ INT_VAR strref = 10970001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Force exceptionnelle~
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

DEFINE_PATCH_MACRO ~opcode_97_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
			LPF ~get_opcode_position~
				INT_VAR opcode  = 44
		            match_target       = target
			        match_power        = power
			        match_parameter2   = MOD_TYPE_flat
			        match_parameter3   = parameter3
			        match_parameter4   = parameter4
			        match_timingMode   = timingMode
			        match_resistance   = resistance
					match_duration     = duration
			        match_probability1 = probability1
			        match_probability2 = probability2
			        match_diceCount    = diceCount
			        match_diceSides    = diceSides
			        match_saveType     = saveType
			        match_saveBonus    = saveBonus
			        match_special      = special
				STR_VAR match_macro = ~opcode_match_diceCount_and_diceSides_and_duration_and_parameter2_and_parameter3_and_parameter4_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~
				RET opcodePosition = position
			END
			PATCH_IF opcodePosition >= 0 BEGIN
				LPF ~get_opcode_by_position~
					INT_VAR opcode = 44 position = opcodePosition
					RET op44_parameter1 = parameter1
				END
				LPF ~delete_opcode~
                    INT_VAR opcode match_position = position
                    RET $opcodes(~%opcode%~) = count
                    RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
                END
				LPF ~delete_opcode~
                    INT_VAR opcode = 44 match_position = opcodePosition
                    RET $opcodes(~44~) = count
                    RET_ARRAY EVAL ~opcodes_44~ = opcodes_xx
                END
				SET opcode = 522
				SET parameter2 = parameter1      // Force exceptionnelle
				SET parameter1 = op44_parameter1 // Force
				LPM ~add_opcode~
			END
        END
	END
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
	LPM ~opcode_25_common~
END

DEFINE_PATCH_MACRO ~opcode_98_is_valid~ BEGIN
	LPM ~opcode_25_is_valid~
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
	LOCAL_SET value = 0

	PATCH_IF type == 2 BEGIN // Chant du barde
		SET strref += 1
	END
	ELSE BEGIN
		SET value = custom_int > 0 ? custom_int : (1 << parameter2)
		LPF ~get_spell_type_str~ INT_VAR value RET spellType END
	END

	PATCH_IF duration < 100 AND duration > 0 BEGIN
		SET value = 100 - duration
		SPRINT duration @10002 // ~%value% %~
		SET strref += 2
	END
	ELSE PATCH_IF duration > 100 BEGIN
		SET value = duration - 100
		SPRINT duration @10002 // ~%value% %~
		SET strref += 4
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_99_group~ BEGIN
	LOCAL_SET group = 1
	LOCAL_SET newSpellType = 0b0
	LOCAL_SET spellType = 0

	PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET group = 0
		SET newSpellType = 1 << %parameter2%
		CLEAR_ARRAY positions
		PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN
			~%parameter2%~ => ~%position%~
		END
		PATCH_FOR_EACH spellType IN 0 1 BEGIN
			LPF ~get_opcode_position~
				INT_VAR opcode
					match_position     = position
					match_custom_int   = 0
					match_target       = target
					match_probability1 = probability1
					match_probability2 = probability2
					match_parameter1   = parameter1
					match_parameter2   = spellType
					match_parameter3   = parameter3
					match_parameter4   = parameter4
					match_timingMode   = timingMode
					match_resistance   = resistance
					match_duration     = duration
					match_power        = power
			        match_diceCount    = diceCount
			        match_diceSides    = diceSides
					match_saveType     = saveType
					match_saveBonus    = saveBonus
					match_special      = special
				STR_VAR match_macro = ~opcode_match_opcode_60_145_group~
				RET opcodePosition = position
			END
			PATCH_IF opcodePosition >= 0 BEGIN
				SET group = 1
				SET newSpellType |= 1 << %spellType%
				SET $positions(~%spellType%~) = opcodePosition
			END
		END
		PATCH_IF group == 1 BEGIN
			PATCH_PHP_EACH positions AS _ => position1 BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position1
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
	        SET custom_int = newSpellType
	        LPM ~add_opcode~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_99_is_valid~ BEGIN
	PATCH_IF parameter2 < 0 OR parameter2 > 2 OR parameter2 > 1 AND NOT is_ee BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid type %parameter2%.~ END
	END
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
	PATCH_IF parameter1 == 0 BEGIN
		SET strref += 1
	END
	ELSE BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_100_is_valid~ BEGIN
	LPM ~opcode_idscheck8_is_valid~
END

/* ----------------------------- *
 * Protection: from Opcode [101] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_101~ BEGIN
	LOCAL_SET strref = 0
	PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
		SPRINT opcodeStr ~%custom_str%~
	END
	ELSE BEGIN
		SET strref = 400000 + parameter2
		LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
	END
	PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11010001 // ~Immunité %opcodeStr%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_101~ BEGIN
	LOCAL_SET strref = 400000 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
	PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11010003 // ~d'être immunisé %opcodeStr%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_101~ BEGIN
	LOCAL_SET strref = 0
	PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
		SPRINT opcodeStr ~%custom_str%~
	END
	ELSE BEGIN
		SET strref = 400000 + parameter2
		LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
	END
	PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11010002 // ~Immunise %theTarget% %opcodeStr%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_101~ BEGIN
	LOCAL_SET strref = 400000 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
	PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11010004 // ~d'immuniser %theTarget% %opcodeStr%~
	END
END

DEFINE_PATCH_MACRO ~opcode_101_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET opcode = 101
		PATCH_IF parameter2 == 3 BEGIN // Folie du berserker
			SET opcode = 4 // Cure: Berserking [4]
			LPM ~delete_cure_linked_to_specific_immunity~
        END
        ELSE PATCH_IF parameter2 == 5 BEGIN // Charme-personne v1 (mineur : pas de résistance à la domination)
			//FIXME: un terme pour différencier l'opcode 5 du 241 ?
			// NPCHAN protège contre le 5, non contre le 241 et est estampillé Immunité aux charmes
			// Potentiellement la liste des sorts est beaucoup plus longue :
			// SPIN980, SPCL641, SPIN553, SPIN558, SPIN980, SPIN985, SPIN506, DEMOCHM, OHREYEB1
			// + tout ceux qui sont oubliés + les dominations
			TEXT_SPRINT spellState ~Charm~
			PATCH_PHP_EACH charmSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
		END
		ELSE PATCH_IF parameter2 == 13 BEGIN // Mort
			PATCH_IF shrink_cure_with_immunities BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode = 101
						match_parameter2 = 209
						match_probability1 = probability1
						match_probability2 = probability2
						match_saveBonus = saveBonus
						match_saveType = saveType
						match_target = target
					STR_VAR match_macro = ~opcode_match_parameter2_and_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
					RET $opcodes(~101~) = count
					RET_ARRAY EVAL ~opcodes_101~ = opcodes_xx
				END
			END
		END
		ELSE PATCH_IF parameter2 == 16 BEGIN // Hâte
			TEXT_SPRINT spellState ~Haste~
			PATCH_PHP_EACH hasteSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
		END
		ELSE PATCH_IF parameter2 == 24 BEGIN // Panique
			TEXT_SPRINT spellState ~Horror~
			PATCH_PHP_EACH horrorSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 161 // Cure: Fear [161]
			LPM ~delete_cure_linked_to_specific_immunity~
		END
		ELSE PATCH_IF parameter2 == 25 BEGIN // Empoisonnement
			TEXT_SPRINT spellState ~Poison~
			PATCH_PHP_EACH poisonSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 11 // Cure: Poison [11]
			LPM ~delete_cure_linked_to_specific_immunity~
			LPF ~has_opcode~
					INT_VAR opcode = 173
						match_probability1 = probability1
						match_probability2 = probability2
						match_target       = target
						match_saveType     = saveType
						match_saveBonus    = saveBonus
					STR_VAR match_macro = ~opcode_match_opcode_101_group~
				RET hasOpcode
			END
			PATCH_IF hasOpcode == 1 BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode = 173
						match_probability1 = probability1
						match_probability2 = probability2
						match_target       = target
						match_saveType     = saveType
						match_saveBonus    = saveBonus
					STR_VAR match_macro = ~opcode_match_opcode_101_group~
					RET $opcodes(~173~) = count
					RET_ARRAY EVAL ~opcodes_173~ = opcodes_xx
				END
				LPF ~delete_opcode~
					INT_VAR opcode = 101 match_position = position
					RET $opcodes(~101~) = count
					RET_ARRAY EVAL ~opcodes_101~ = opcodes_xx
				END
				// Bug où il reste toujours un item dans le tableau si c'était le dernier
				// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
				PATCH_IF $opcodes(~101~) == 0 BEGIN
                    CLEAR_ARRAY ~opcodes_101~
                END
				SET opcode = 101
				SET parameter2 = 507 // ~à l'empoisonnement~
				LPM ~add_opcode~
			END
		END
		ELSE PATCH_IF parameter2 == 38 BEGIN // Silence
			TEXT_SPRINT spellState ~Silence~
			PATCH_PHP_EACH silenceSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 48 // Cure: Silence (Vocalize) [48]
			LPM ~delete_cure_linked_to_specific_immunity~
		END
		ELSE PATCH_IF parameter2 == 39 BEGIN // Inconscience
			TEXT_SPRINT spellState ~Unconsciousness~
			PATCH_PHP_EACH unconsciousnessSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 2 // Cure: Sleep [2]
			LPM ~delete_cure_linked_to_specific_immunity~
			PATCH_IF shrink_cure_with_immunities BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode = 101
						match_parameter2   = 217
				        match_probability1 = probability1
				        match_probability2 = probability2
				        match_saveBonus    = saveBonus
				        match_saveType     = saveType
				        match_target       = target
					STR_VAR match_macro = ~opcode_match_parameter2_and_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
					RET $opcodes(~101~) = count
					RET_ARRAY EVAL ~opcodes_101~ = opcodes_xx
				END
			END
		END
		ELSE PATCH_IF parameter2 == 40 BEGIN // Lenteur
			TEXT_SPRINT spellState ~Slow~
			PATCH_PHP_EACH slowSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
		END
		ELSE PATCH_IF parameter2 == 45 BEGIN // Étourdissement
			TEXT_SPRINT spellState ~Stun~
			PATCH_PHP_EACH stunSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 46 // Cure: Stun (Unstun) [46]
			LPM ~delete_cure_linked_to_specific_immunity~
			PATCH_IF shrink_cure_with_immunities BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode = 101
						match_parameter2   = 210
				        match_probability1 = probability1
				        match_probability2 = probability2
				        match_saveBonus    = saveBonus
				        match_saveType     = saveType
				        match_target       = target
					STR_VAR match_macro = ~opcode_match_parameter2_and_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
					RET $opcodes(~101~) = count
					RET_ARRAY EVAL ~opcodes_101~ = opcodes_xx
				END
			END
		END
		ELSE PATCH_IF parameter2 == 74 BEGIN // Cécité
			TEXT_SPRINT spellState ~Blindness~
			PATCH_PHP_EACH blindSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 75 // Cure: Blindness [75]
			LPM ~delete_cure_linked_to_specific_immunity~
		END
		ELSE PATCH_IF parameter2 == 76 BEGIN // Débilité mentale
			TEXT_SPRINT spellState ~Feeblemindedness~
			PATCH_PHP_EACH feeblemindednessSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 77 // Cure: Feeblemindedness [77]
			LPM ~delete_cure_linked_to_specific_immunity~
		END
		ELSE PATCH_IF parameter2 == 78 BEGIN // Maladie
			// Si possède aussi le 101 pour le 76 alors supprimer l'opcode 79
			LPF ~has_opcode~
				INT_VAR opcode = 101
					match_parameter2   = 76
			        match_probability1 = probability1
			        match_probability2 = probability2
			        match_target       = target
				STR_VAR match_macro = ~opcode_match_parameter2_and_probability1_and_probability2_and_target~
				RET hasOpcode
			END
			PATCH_IF hasOpcode == 1 BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode = 79
				        match_probability1 = probability1
				        match_probability2 = probability2
					STR_VAR match_macro = ~opcode_match_probability1_and_probability2_and_target~
					RET $opcodes(~79~) = count
					RET_ARRAY EVAL ~opcodes_79~ = opcodes_xx
				END
				// Bug où il reste toujours un item dans le tableau si c'était le dernier
				// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
				PATCH_IF $opcodes(~79~) == 0 BEGIN
		            CLEAR_ARRAY ~opcodes_79~
		        END
			END
		END
		ELSE PATCH_IF parameter2 == 80 BEGIN // Surdité
			SET opcode = 81 // Cure: Deafness [81]
			PATCH_PHP_EACH deafnessSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			LPM ~delete_cure_linked_to_specific_immunity~
		END
		ELSE PATCH_IF parameter2 == 93 BEGIN // Stat: Fatigue Modifier [93]
			LPF ~delete_opcode~
				INT_VAR opcode = 93
					match_parameter1   = 0
					match_parameter2   = MOD_TYPE_flat
			        match_probability1 = probability1
			        match_probability2 = probability2
			        match_saveBonus    = saveBonus
			        match_saveType     = saveType
			        match_target       = target
				STR_VAR match_macro = ~opcode_match_parameter1_and_parameter2_and_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
				RET $opcodes(~93~) = count
				RET_ARRAY EVAL ~opcodes_93~ = opcodes_xx
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~93~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_93~
	        END
		END
		ELSE PATCH_IF parameter2 == 109 BEGIN // Paralysie
			TEXT_SPRINT spellState ~Paralyse~
			PATCH_PHP_EACH paralyseSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 162 // Cure: Hold [162]
			LPM ~delete_cure_linked_to_specific_immunity~
			SET opcode = 46 // Cure: Stun (Unstun) [46]
			LPM ~delete_cure_linked_to_specific_immunity~
		END
		ELSE PATCH_IF parameter2 == 128 BEGIN // Confusion
			TEXT_SPRINT spellState ~Confusion~
			PATCH_PHP_EACH confusionSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 242 // Cure: Confusion [242]
			LPM ~delete_cure_linked_to_specific_immunity~
		END
		ELSE PATCH_IF parameter2 == 134 BEGIN // Petrification
			TEXT_SPRINT spellState ~Petrification~
			PATCH_PHP_EACH petrificationSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
		END
		ELSE PATCH_IF parameter2 == 135 BEGIN // Polymorphie
			TEXT_SPRINT spellState ~Polymorph~
			PATCH_PHP_EACH polymorphSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
		END
		ELSE PATCH_IF parameter2 == 154 BEGIN // Enchevêtrement
			TEXT_SPRINT spellState ~Entangle~
			PATCH_PHP_EACH entangleSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
		END
		ELSE PATCH_IF parameter2 == 157 BEGIN // Toile d'araignée
			TEXT_SPRINT spellState ~Web~
			PATCH_PHP_EACH webSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 83 // Protection: From Projectile [83]
			PATCH_FOR_EACH parameter2 IN 62 63 259 319 BEGIN
				LPM ~delete_cure_linked_to_specific_immunity~
			END
		END
		ELSE PATCH_IF parameter2 == 175 BEGIN // Immobilisation
			TEXT_SPRINT spellState ~Hold~
			PATCH_PHP_EACH holdSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
			SET opcode = 162 // Cure: Hold [162]
			LPM ~delete_cure_linked_to_specific_immunity~
		END
		ELSE PATCH_IF parameter2 == 213 BEGIN // Labyrinthe
			TEXT_SPRINT spellState ~Maze~
			PATCH_PHP_EACH mazeSpellList AS resref => _ BEGIN
				LPM ~delete_immunity_to_specific_spell~
			END
		END
		ELSE PATCH_IF parameter2 == 216 BEGIN // Drain de niveau
			SET opcode = 224 // Cure: Level Drain (Restoration) [224]
			LPM ~delete_cure_linked_to_specific_immunity~
		END
	END

	PATCH_PHP_EACH EVAL ~opcodes_101~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF parameter2 == 126 BEGIN // Stat: Movement Modifier [126]
			// Action libre
			// Nécessite d'être traité à part, afin que tous les autres effets puissent grouper si nécessaire.
			PATCH_IF abilityType == AbilityType_Equipped BEGIN
				SET hasAllOpcode = 1
				LPF ~has_opcode~
					INT_VAR opcode = 163
						match_probability1 = probability1
				        match_probability2 = probability2
				        match_saveBonus    = saveBonus
				        match_saveType     = saveType
				        match_target       = target
					STR_VAR match_macro = ~opcode_match_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
					RET hasOpcode
				END
				PATCH_IF hasOpcode == 0 BEGIN
					// Au cas où le regroupement de l'opcode 163 aurait déjà été appliqué
					LPF ~has_opcode~
						INT_VAR opcode = 126
							match_parameter1   = 100
							match_parameter2   = 2
					        match_probability1 = probability1
					        match_probability2 = probability2
					        match_saveBonus    = saveBonus
					        match_saveType     = saveType
					        match_target       = target
						STR_VAR match_macro = ~opcode_match_parameter1_and_parameter2_and_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
						RET hasOpcode
					END
					PATCH_IF hasOpcode == 0 BEGIN
						hasAllOpcode = 0
					END
				END
				PATCH_FOR_EACH parameter2 IN 16 40 109 154 157 175 BEGIN
					PATCH_IF hasAllOpcode == 1 BEGIN
						LPF ~has_opcode~
							INT_VAR opcode = 101
								match_parameter2   = parameter2
						        match_probability1 = probability1
						        match_probability2 = probability2
						        match_saveBonus    = saveBonus
						        match_saveType     = saveType
						        match_target       = target
							STR_VAR match_macro = ~opcode_match_parameter2_and_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
							RET hasOpcode
						END
						PATCH_IF hasOpcode == 0 BEGIN
							hasAllOpcode = 0
						END
					END
				END
				PATCH_IF hasAllOpcode == 1 BEGIN
					SET opcode = 520
					LPM ~add_opcode~
					// 46 et 162 sont optionnels, non testés ci-dessus.
					PATCH_FOR_EACH opcode IN 46 126 162 163 BEGIN
						LPF ~delete_opcode~
							INT_VAR opcode
								match_probability1 = probability1
                                match_probability2 = probability2
                                match_saveBonus    = saveBonus
                                match_saveType     = saveType
                                match_target       = target
							STR_VAR match_macro = ~opcode_match_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
							RET $opcodes(~%opcode%~) = count
							RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
						END
						// Bug où il reste toujours un item dans le tableau si c'était le dernier
						// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
						PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
				            CLEAR_ARRAY ~opcodes_%opcode%~
				        END
					END
					PATCH_FOR_EACH parameter2 IN 16 40 109 126 154 157 175 BEGIN
						LPF ~delete_opcode~
							INT_VAR opcode = 101
								match_parameter2   = parameter2
                                match_probability1 = probability1
                                match_probability2 = probability2
                                match_saveBonus    = saveBonus
                                match_saveType     = saveType
                                match_target       = target
							STR_VAR match_macro = ~opcode_match_parameter2_and_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
							RET $opcodes(~101~) = count
							RET_ARRAY EVAL ~opcodes_101~ = opcodes_xx
						END
						// Bug où il reste toujours un item dans le tableau si c'était le dernier
						// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
						PATCH_IF $opcodes(~101~) == 0 BEGIN
				            CLEAR_ARRAY ~opcodes_101~
				        END
					END
				END
			END
			SET opcode = 126
			LPM ~delete_cure_linked_to_specific_immunity~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_101_post_group~ BEGIN
	LOCAL_SET strref = 0
	LOCAL_SET count = 0
	PATCH_IF shrink_immunities_single_line == 1 BEGIN
		//Toutes les immunités regroupées en un seul opcode
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF probability == 100 AND target = TARGET_FX_self BEGIN
				SET count += 1
			END
		END
		PATCH_IF count > 1 BEGIN
			PATCH_DEFINE_ARRAY ~immunitiesList~ BEGIN END
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_vars~
				PATCH_IF probability == 100 AND target = TARGET_FX_self BEGIN
					SET strref = 400000 + parameter2
					LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
					PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
						SET $immunitiesList(~%opcodeStr%~) = 1
					END
					LPF ~delete_opcode~
						INT_VAR opcode = 101
							match_parameter2  = parameter2
					        match_probability = 100
					        match_target      = TARGET_FX_self
						STR_VAR match_macro = ~opcode_match_parameter2_and_probability_and_target~
						RET $opcodes(~101~) = count
						RET_ARRAY EVAL ~opcodes_101~ = opcodes_xx
					END
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~101~) == 0 BEGIN
				CLEAR_ARRAY ~opcodes_101~
			END
			SPRINT and @100021 // ~et~
			LPF ~implode~ STR_VAR array_name = ~immunitiesList~ glue = ~, ~ final_glue = ~ %and% ~ RET immunities = text END
			SET opcode = 101
			SET target = TARGET_FX_self
			SPRINT custom_str ~%immunities%~
			LPM ~add_opcode~
		END

		SET count = 0
		//Toutes les immunités ciblées regroupées en un seul opcode
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF probability == 100 AND target = TARGET_FX_preset BEGIN
				SET count += 1
			END
		END
		PATCH_IF count > 1 BEGIN
			PATCH_DEFINE_ARRAY ~immunitiesList~ BEGIN END
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_vars~
				PATCH_IF probability == 100 AND target = TARGET_FX_preset BEGIN
					SET strref = 400000 + parameter2
					LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
					PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
						SET $immunitiesList(~%opcodeStr%~) = 1
					END
					LPF ~delete_opcode~
						INT_VAR opcode = 101
							match_parameter2  = parameter2
					        match_probability = 100
					        match_target      = TARGET_FX_preset
						STR_VAR match_macro = ~opcode_match_parameter2_and_probability_and_target~
						RET $opcodes(~101~) = count
						RET_ARRAY EVAL ~opcodes_101~ = opcodes_xx
					END
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~101~) == 0 BEGIN
				CLEAR_ARRAY ~opcodes_101~
			END
			SPRINT and @100021 // ~et~
			LPF ~implode~ STR_VAR array_name = ~immunitiesList~ glue = ~, ~ final_glue = ~ %and% ~ RET immunities = text END
			SET opcode = 101
			SET target = TARGET_FX_preset
			SPRINT custom_str ~%immunities%~
			LPM ~add_opcode~
		END
	END
END

DEFINE_PATCH_MACRO ~delete_immunity_to_specific_spell~ BEGIN
	// FIXME: lent, intéressant de regrouper les deletes ? (resref = SPWIxx OR resref = SPWIyy)
	LOCAL_SET oldCount = $opcodes(~%opcode%~)
	LOCAL_SET opcode = 206
	LPF ~has_opcode~
		INT_VAR opcode
		STR_VAR
			match_macro  = ~opcode_match_resref~
			match_resref = ~%resref%~
		RET hasOpcode
	END
	PATCH_IF hasOpcode BEGIN
		LPF ~delete_opcode~
			INT_VAR opcode
	            match_target       = target
		        match_probability1 = probability1
		        match_probability2 = probability2
		        match_diceCount    = diceCount
		        match_diceSides    = diceSides
		        match_power        = power
		        match_saveType     = saveType
		        match_saveBonus    = saveBonus
			STR_VAR
				match_macro = ~opcode_match_diceCount_and_diceSides_and_power_and_probability1_and_probability2_and_resref_and_target_saveBonus_and_saveType~
				match_resref = ~%resref%~
			RET $opcodes(~%opcode%~) = count
			RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
		END
	END
	PATCH_IF show_lack_immunity AND oldCount == $opcodes(~%opcode%~) BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Immunity to %spellState%: Opcode 206 with resref %resref% not found.~ END
	END

	SET opcode = 321
	LPF ~has_opcode~
		INT_VAR opcode
		STR_VAR
			match_macro  = ~opcode_match_resref~
			match_resref = ~%resref%~
		RET hasOpcode
	END
	PATCH_IF hasOpcode BEGIN
		LPF ~delete_opcode~
			INT_VAR opcode
	            match_target       = target
		        match_probability1 = probability1
		        match_probability2 = probability2
		        match_diceCount    = diceCount
		        match_diceSides    = diceSides
		        match_power        = power
		        match_resistance   = resistance
		        match_saveType     = saveType
		        match_saveBonus    = saveBonus
			STR_VAR
				match_macro = ~opcode_match_diceCount_and_diceSides_and_power_and_probability1_and_probability2_and_resistance_and_resref_and_target_and_saveBonus_and_saveType~
				match_resref = ~%resref%~
			RET $opcodes(~%opcode%~) = count
			RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
		END
	END
	PATCH_IF show_lack_immunity AND oldCount == $opcodes(~%opcode%~) BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Immunity to %spellState%: Opcode 321 with resref %resref% not found.~ END
	END
END

DEFINE_PATCH_MACRO ~delete_cure_linked_to_specific_immunity~ BEGIN
	PATCH_IF shrink_cure_with_immunities AND abilityType == AbilityType_Equipped BEGIN
		LPF ~delete_opcode~
			INT_VAR opcode
				match_probability1 = probability1
				match_probability2 = probability2
				match_target = target
				match_saveType = saveType
				match_saveBonus = saveBonus
			STR_VAR match_macro = ~opcode_match_probability1_and_probability2_and_saveBonus_and_saveType_and_target~
			RET $opcodes(~%opcode%~) = count
			RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
		END
		// Bug où il reste toujours un item dans le tableau si c'était le dernier
		// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
		PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
            CLEAR_ARRAY ~opcodes_%opcode%~
        END
	END
END

// DEFINE_PATCH_MACRO ~opcode_101_is_valid~ BEGIN
// 	PATCH_IF NOT VARIABLE_IS_SET $sort_opcodes(~%parameter2%~) BEGIN
// 		SET isValid = 0
// 		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Opcode %parameter2%.~ END
// 	END
// END

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

DEFINE_PATCH_MACRO ~opcode_102_is_valid~ BEGIN
	PATCH_IF parameter1 < 0 OR parameter1 > 9 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Spell Level %parameter1%.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_102_group~ BEGIN
	LOCAL_SET initOpcode = opcode
	LOCAL_SET maxSpellLevel = 0
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions_already_check~ BEGIN END

	PATCH_PHP_EACH EVAL ~opcodes_%initOpcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET newP1 = 0b0
		CLEAR_ARRAY positions

		PATCH_IF maxSpellLevel < parameter1 BEGIN
			SET maxSpellLevel = parameter1
		END

		PATCH_PHP_EACH EVAL ~opcodes_%initOpcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF NOT VARIABLE_IS_SET $positions_already_check(~%position%~) BEGIN
				// On retire l'opcode de ceux à checker dans les futures itérations
				SET $positions_already_check(~%position%~) = 1
				// On ajoute l'opcode courant à ceux qui seront désactivés
				SET $positions(~%position%~) = initOpcode
				// P2 retiré
				LPF ~get_opcode_position~
					INT_VAR opcode
			            match_target       = target
				        match_power        = power
				        match_timingMode   = timingMode
				        match_resistance   = resistance
						match_duration     = duration
				        match_probability1 = probability1
				        match_probability2 = probability2
				        match_diceCount    = diceCount
				        match_diceSides    = diceSides
				        match_saveType     = saveType
				        match_saveBonus    = saveBonus
					STR_VAR match_macro = ~opcode_match_diceCount_and_diceSides_and_duration_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_target_and_timingMode~
					RET opcodePosition = position
				END
				SET $positions(~%opcodePosition%~) = initOpcode
				SET parameter = parameter1 - 1
				SET newP1 |= ~%BIT%parameter%%~
			END
		END
		PATCH_IF newP1 > 0 BEGIN
			// Suppression des effets similaires
			PATCH_PHP_EACH positions AS position1 => opcode BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position1
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// FIXME: à ce stade les données ne sont pas spécifiquement sauvegardées, reliquat du PATCH_PHP_EACH précédent
			// Fonctionnel dans les cas généraux
			SET opcode = 509
			SET parameter1 = newP1
			LPM ~add_opcode~
		END
	END

	// On supprime les éventuelles immunités spécifiques à un sort dont le niveau est inférieur ou égal au niveau le plus grand de l'opcode 102
	PATCH_IF maxSpellLevel > 0 BEGIN
		PATCH_PHP_EACH EVAL ~opcodes_206~ AS data => _ BEGIN
			LPM ~data_to_vars~

			PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
				INNER_PATCH_FILE ~%resref%.spl~ BEGIN
					READ_LONG SPL_level spellLevel
					PATCH_IF spellLevel <= maxSpellLevel BEGIN
						LPF ~delete_opcode~
							INT_VAR opcode = 206 match_position = position
							RET $opcodes(~206~) = count
							RET_ARRAY EVAL ~opcodes_206~ = opcodes_xx
						END
					END
				END
			END
		END
	END
END

/* ----------------------------- *
 * Stat: Experience Points [104] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_104~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 11040001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Expérience~
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

DEFINE_PATCH_MACRO ~opcode_104_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ---------------- *
 * Stat: Gold [105] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_105~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative AND parameter1 < 0 BEGIN
		SPRINT description @11050003 // ~Déleste %theTarget% de tout son or~
	END
	ELSE BEGIN
		PATCH_IF parameter2 == MOD_TYPE_cumulative AND parameter1 > 0 BEGIN
			SET parameter1 = 0 - parameter1
		END
		ELSE PATCH_IF parameter2 == MOD_TYPE_flat AND parameter1 < 0 BEGIN
			SET parameter1 = 0
		END
		LPF ~opcode_target~ INT_VAR strref = 11050001 RET description END // ~l'or~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_105~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative AND parameter1 < 0 BEGIN
		SPRINT description @11050003 // ~Déleste %theTarget% de tout son or~
	END
	ELSE BEGIN
		PATCH_IF parameter2 == MOD_TYPE_cumulative AND parameter1 > 0 BEGIN
			SET parameter1 = 0 - parameter1
		END
		ELSE PATCH_IF parameter2 == MOD_TYPE_flat AND parameter1 < 0 BEGIN
			SET parameter1 = 0
		END
		LPF ~opcode_probability~ INT_VAR strref = 11050001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~l'or~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_105~ BEGIN
	LPM ~opcode_self_105~

END

DEFINE_PATCH_MACRO ~opcode_target_probability_105~ BEGIN
	LPM ~opcode_self_probability_105~
END

DEFINE_PATCH_MACRO ~opcode_105_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* --------------------------------- *
 * Stat: Morale Break Modifier [106] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_106~ BEGIN
	// SET ignoreDuration = 1
	PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		PATCH_IF parameter1 < 0 BEGIN
			SET parameter1 = 0
		END
		PATCH_IF parameter1 == 0 BEGIN
			SPRINT description @11060004 // ~Immunité à la panique~
		END
		ELSE PATCH_IF parameter1 == 1 BEGIN
			SPRINT description @11060001 // ~Le moral %ofTheTarget% reste au plus haut~
		END
		ELSE BEGIN
			SPRINT description @11060005 // ~Le point de rupture de moral %ofTheTarget% passe à %parameter1%~
		END
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
	// SET ignoreDuration = 1
	PATCH_IF parameter2 == MOD_TYPE_flat AND parameter1 <= 1 BEGIN
		PATCH_IF parameter1 < 0 BEGIN
			SET parameter1 = 0
		END
		PATCH_IF parameter1 == 0 BEGIN
			SPRINT description @11060009 // ~d'immuniser %theTarget% contre la rupture de moral~ // Immunité contre la rupture de moral~
		END
		ELSE PATCH_IF parameter1 == 1 BEGIN
			SPRINT description @11060006 // ~de garder le moral %ofTheTarget% au plus haut~
		END
		ELSE BEGIN
			SPRINT description @11060010 // ~de faire passer le point de rupture de moral %ofTheTarget% à %parameter1%~
		END
	END
	ELSE BEGIN
		SET value = ABS parameter1
		PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN
			LPF ~percent_value~ INT_VAR value RET value END
		END
		PATCH_IF parameter1 < 0 BEGIN
			SPRINT description @11060007 // ~de renforcer le moral %ofTheTarget% de %value%~
		END
		ELSE BEGIN
			SPRINT description @11060008 // ~d'affaiblir le moral %ofTheTarget% de %value%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_106~ BEGIN
	LPM ~opcode_self_106~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_106~ BEGIN
	LPM ~opcode_self_probability_106~
END

DEFINE_PATCH_MACRO ~opcode_106_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ---------------------- *
 * Stat: Reputation [108] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_108~ BEGIN
    LPM ~opcode_108_common~
    LPF ~opcode_mod~ INT_VAR strref = EVAL ~%strref%~ STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Réputation du personnage~
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
	SET strref = 11080003 // ~Réputation du personnage~
	PATCH_IF is_ee == 1 BEGIN
		PATCH_IF parameter2 >= 3 BEGIN
			SET strref = 11080005 // ~Réputation du groupe~
			SET parameter2 = parameter2 MODULO 3
		END
    END
	PATCH_IF parameter2 == MOD_TYPE_flat AND parameter1 < 10 BEGIN
		SET parameter1 = 10
	END
END

DEFINE_PATCH_MACRO ~opcode_108_is_valid~ BEGIN
	PATCH_IF is_ee == 0 BEGIN
		LPM ~opcode_modstat2_is_valid~
	END
	ELSE BEGIN
		PATCH_IF parameter2 < MOD_TYPE_cumulative OR parameter2 > 5 BEGIN
			SET isValid = 0
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %parameter2%.~ END
		END
	END
END

/* ----------------- *
 * State: Hold [109] *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_109~ BEGIN
	SPRINT description @11090002 // ~Paralyse %theTarget%~
	PATCH_IF parameter1 != 0 BEGIN
		SPRINT idsFile $ids_files(~%parameter2%~)
		LOOKUP_IDS_SYMBOL_OF_INT symbol ~%idsFile%~ ~%parameter1%~

		PATCH_IF NOT ~%symbol%~ STRING_EQUAL ~0~ BEGIN
			LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
			SPRINT description @11090001 // ~Paralyse les %creatureType%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_109~ BEGIN
	SPRINT description @11090004 // ~de paralyser %theTarget%~
	PATCH_IF parameter1 != 0 BEGIN
		SPRINT idsFile $ids_files(~%parameter2%~)
		LOOKUP_IDS_SYMBOL_OF_INT symbol ~%idsFile%~ ~%parameter1%~

		PATCH_IF NOT ~%symbol%~ STRING_EQUAL ~0~ BEGIN
			LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET creatureType = idName END
			SPRINT description @11090003 // ~de paralyser les %creatureType%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_109~ BEGIN
	LPM ~opcode_self_109~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_109~ BEGIN
	LPM ~opcode_self_probability_109~
END

DEFINE_PATCH_MACRO ~opcode_109_is_valid~ BEGIN
	// Cas particulier propre à l'opcode 109, non valable pour les 175 et 185
	PATCH_IF parameter2 < 2 OR parameter2 > 9 BEGIN
		SET parameter2 = 2
		SET parameter1 = 0
	END
END

/* --------------------------------- *
 * Item: Create Magical Weapon [111] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_111~ BEGIN
	LPM ~opcode_target_111~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_111~ BEGIN
	LPM ~opcode_target_probability_111~
END

DEFINE_PATCH_MACRO ~opcode_target_111~ BEGIN
	LOCAL_SET strref = 11110002
	LPM ~opcode_111_common~
END

DEFINE_PATCH_MACRO  ~opcode_target_probability_111~ BEGIN
	LOCAL_SET strref = 11110003
	LPM ~opcode_111_common~
END

DEFINE_PATCH_MACRO ~opcode_111_common~ BEGIN
	LOCAL_SET amount = parameter1 > 0 ? parameter1 : 1
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
			SPRINT amount ~%complex_value%~
			SET strref += 10
		END
		ELSE BEGIN
			SET strrefWeapon = 11110101 // ~arme magique~
			PATCH_IF amount > 1 BEGIN
				SET strrefWeapon += 1 // ~armes magiques~
				SET strref += 10
			END
			SPRINT valueType (AT strrefWeapon)
			SPRINT value ~%amount%~
			SPRINT amount @102165 // ~%value% %valueType%~
		END
		SPRINT description (AT strref) // ~Équipe %theTarget% d'%amount% (%itemName%)~
	END
END


DEFINE_PATCH_MACRO ~opcode_111_replace~ BEGIN
	PATCH_PHP_EACH ~opcodes_111~ AS data => _ BEGIN
		LPM ~data_to_vars~
		LPF ~has_opcode~
			INT_VAR opcode = 135
				match_duration  = duration
	            match_timingMode = timingMode
			STR_VAR match_macro = ~opcode_match_duration_and_timingMode~
			RET hasOpcode
		END
		PATCH_IF hasOpcode BEGIN
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
		END
		ELSE BEGIN
			SET itemPosition = position
			SET itemDuration = duration
			SET itemTimingMode = timingMode
			SET itemSaveType = saveType
			SET itemSaveBonus = saveBonus
			SET itemResistance = resistance
			SET itemProbability = probability
			SET itemProbability1 = probability1
			SET itemProbability2 = probability2
			SET itemTarget = target
			PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.itm~ BEGIN
				INNER_PATCH_FILE ~%resref%.itm~ BEGIN
					READ_LONG ITM_identified_name itemNameRef
					READ_STRREF ITM_identified_name itemName
					//lire les opcodes de l'item et les ajouter dans les opcodes actuels
				    GET_OFFSET_ARRAY offsets ITM_V10_GEN_EFFECTS
				    PHP_EACH offsets AS _ => offset BEGIN
					    LPM ~read_effect_vars~
					    PATCH_IF opcode == 135 BEGIN
							LPF ~delete_opcode~
								INT_VAR opcode = 111 match_position = itemPosition
								RET $opcodes(~111~) = count
								RET_ARRAY EVAL ~opcodes_111~ = opcodes_xx
							END
							// Bug où il reste toujours un item dans le tableau si c'était le dernier
							// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
							PATCH_IF $opcodes(~111~) == 0 BEGIN
					            CLEAR_ARRAY ~opcodes_111~
					        END
						    SET duration = itemDuration
						    SET timingMode = itemTimingMode
						    SET saveType = itemSaveType
						    SET saveBonus = itemSaveBonus
						    SET resistance = itemResistance
						    SET probability = itemProbability
						    SET probability1 = itemProbability1
						    SET probability2 = itemProbability2
						    SET target = itemTarget
						    LPM ~add_opcode~
					    END
				    END
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_111_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_111_spell_level_match~ BEGIN
	PATCH_IF parameter1 < 1 BEGIN
		SET parameter1 = 1
	END
	PATCH_IF match_parameter1 < 1 BEGIN
		SET match_parameter1 = 1
	END
END

DEFINE_PATCH_FUNCTION ~opcode_111_typed_value~ INT_VAR value = 0 RET strref BEGIN
	SET strref = 11110101 // ~arme magique~
	PATCH_IF value > 1 BEGIN
		SET strref = 11110102 // ~armes magiques~
	END
END

/* --------------------------------- *
 * Item: Remove Item [112] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_112~ BEGIN
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11120001 // ~Retire "%itemName%" de l'inventaire~
		// Hack pour forcer l'affichage de la durée / usage strictement interne
		PATCH_IF custom_int == 122 AND timingMode == TIMING_duration BEGIN
			LPF ~get_duration_value~ INT_VAR duration RET duration = value END

			PATCH_IF NOT ~%duration%~ STRING_EQUAL ~~ BEGIN
				SPRINT description ~%description% %duration%~
				SET ignoreDuration = 1
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_112~ BEGIN
	LPM ~opcode_target_probability_112~
END

DEFINE_PATCH_MACRO ~opcode_target_112~ BEGIN
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11120002 // ~Retire "%itemName%" de l'inventaire %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_112~ BEGIN
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END

	PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11120005 // ~de retirer "%itemName%" de l'inventaire %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_112_group~ BEGIN
	LOCAL_SET searchOpcode = 111
	LOCAL_SET searchOpcode2 = 122

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET group = 0
		SET currentOpcode = opcode
		SET currentDuration = duration
		SET currentPosition = position
		TEXT_SPRINT currentresref ~%resref%~

		// Group 111 - 112 (ajout d'une arme puis retrait)
		// L'arme peut posséder une durée supérieure ou permanente mais vient à être retirée de l'inventaire avant ce terme
		// La durée de l'opcode 111 est alors modifiée et l'opcode 112 est retiré
		// Ex: Cape des égouts (CLCK27) - Gelée moutarde -> Arme permanente mais retirée au bout de 2 tours => Durée 2 tours
		PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND timingMode == TIMING_delayed AND
				 VARIABLE_IS_SET $opcodes(~%searchOpcode%~) AND
				 $opcodes(~%searchOpcode%~) > 0 BEGIN
			PATCH_PHP_EACH EVAL ~opcodes_%searchOpcode%~ AS data => _ BEGIN
				PATCH_IF group == 0 BEGIN
					LPM ~data_to_vars~
					SET opcode = searchOpcode
					PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%currentresref%~ BEGIN
						PATCH_IF timingMode == TIMING_permanent OR
								timingMode == TIMING_while_equipped OR
								timingMode == TIMING_permanent_after_death OR
								timingMode == TIMING_duration AND duration > currentDuration BEGIN
							SET group = 1
							SET oldDuration = duration
							SET oldTimingMode = timingMode

							// ajout de l'opcode 111 modifié
							PATCH_IF timingMode != TIMING_duration OR duration > currentDuration BEGIN
								SET duration = currentDuration
							END
							SET timingMode = TIMING_duration
							LPM ~add_opcode~

							// suppression de l'opcode 111 initial
							// FIXME Marche pas en mettant le add_opcode après... raison ?
							// La position n'est pas une condition suffisante
							LPF ~delete_opcode~
								INT_VAR opcode
									match_timingMode = oldTimingMode
									match_duration = oldDuration
								STR_VAR match_macro = ~opcode_match_duration_and_timingMode~
								RET $opcodes(~%opcode%~) = count
								RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
							END
						END
						ELSE PATCH_IF timingMode == TIMING_duration AND duration <= currentDuration BEGIN
							// le groupe est actif mais aucune modification de l'opcode 111 nécessaire
							SET group = 1
						END
					END

					PATCH_IF group == 1 BEGIN
						// Suppression de l'opcode 112 devenu inutile
						SET opcode = currentOpcode
						LPF ~delete_opcode~
							INT_VAR opcode match_position = currentPosition
							RET $opcodes(~%opcode%~) = count
							RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
						END
					END
				END
			END
		END

		// Group 112 - 122 (retrait d'unearme puis rajout)
		// Dans le cas où l'utilisation d'une compétence de l'objet implique sa disparition temporaire de l'inventaire
		// Ex : Ras +2 (SW1H33) : l'objet est retiré puis un effet delayed vient la rajouter par la suite
		// dans ce cas, l'opcode 122 devient un effet à durée limitée (non prévu initialement)
		ELSE PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND
					  (timingMode <= TIMING_while_equipped OR timingMode >= TIMING_permanent_after_death) AND
					  VARIABLE_IS_SET $opcodes(~%searchOpcode2%~) AND
					  $opcodes(~%searchOpcode2%~) > 0 BEGIN
			PATCH_PHP_EACH EVAL ~opcodes_%searchOpcode2%~ AS data => _ BEGIN
				LPM ~data_to_vars~
				PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%currentresref%~ AND
						 timingMode == TIMING_delayed BEGIN
					// Supression de l'opcode 122
					SET opcode = searchOpcode2
					SET searchDuration = duration
					LPF ~delete_opcode~
						INT_VAR opcode match_position = position
						RET $opcodes(~%opcode%~) = count
						RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
					END
					SET opcode = currentOpcode
					PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
						LPM ~data_to_vars~
						PATCH_IF position == currentPosition BEGIN
							// Ajout du nouveau, le custom_int permettra de force l'affichage de la durée
							SET timingMode = TIMING_duration
							SET duration = searchDuration
							SET custom_int = 122
							LPM ~add_opcode~

							// Suppression de l'opcode 112 actuel
							LPF ~delete_opcode~
								INT_VAR opcode
									match_position = position
									match_duration = currentDuration
									match_custom_int = 122
								STR_VAR match_macro = ~opcode_match_opcode_112_group~
								RET $opcodes(~%opcode%~) = count
								RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
							END
						END
					END
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_112_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
	LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END
	PATCH_IF isValid == 1 AND FILE_EXISTS_IN_GAME ~%resref%.itm~ BEGIN
		INNER_PATCH_FILE ~%resref%.itm~ BEGIN
			// N'a aucune plus value pour le joueur, généralement sur des sorts ou objets qui métamorphosent.
			READ_LONG ITM_identified_name itemNameRef
			PATCH_IF itemNameRef == 25615 OR itemNameRef == 10966  // "Attaquer"
				OR itemNameRef == 6854 // "Morgenstern "
			BEGIN
				SET isValid = 0
			END
		END
	END
END

/* ----------------------- *
 * Detect: Alignment [115] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_115~ BEGIN
	LOCAL_SET strref = 11150101 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET alignment = string END // ~Détection du xxx~
	SPRINT description @11150001
END

DEFINE_PATCH_MACRO ~opcode_target_115~ BEGIN
	LOCAL_SET strref = 11150101 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET alignment = string END // ~Détection du xxx~
	SPRINT description @11150011
END

DEFINE_PATCH_MACRO ~opcode_self_probability_115~ BEGIN
	LOCAL_SET strref = 11150101 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET alignment = string END // ~Détection du xxx~
	SPRINT description @11150021
END

DEFINE_PATCH_MACRO ~opcode_target_probability_115~ BEGIN
	LOCAL_SET strref = 11150101 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET alignment = string END // ~Détection du xxx~
	SPRINT description @11150031
END

DEFINE_PATCH_MACRO ~opcode_115_is_valid~ BEGIN
	PATCH_IF parameter2 < 0 OR parameter2 > 2 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid value for Alignment Mask : %parameter2% (0, 1 or 2 expected)~ END
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

DEFINE_PATCH_MACRO ~opcode_116_is_valid~ BEGIN
	LPM ~opcode_47_is_valid~
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
	SPRINT description @11190001 // ~Image miroir~
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

DEFINE_PATCH_MACRO ~opcode_119_spell_level_match~ BEGIN
	// Parameter #1: Irrelevant
    // Parameter #2: Irrelevant
	SET match_parameter1 = parameter1
	SET match_parameter2 = parameter2
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

// regroupement des opcodes avec parameter2 == 0
// Doute pour les non_ee : TODO: regroupement classique
DEFINE_PATCH_MACRO ~opcode_120_group~ BEGIN
	PATCH_IF is_ee BEGIN
		SET maxEnchantment = ~-1~
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF parameter2 == 0 AND parameter1 > maxEnchantment BEGIN
				SET maxEnchantment = parameter1
			END
		END
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF parameter2 == 0 AND parameter1 < maxEnchantment BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_120_is_valid~ BEGIN
	PATCH_IF parameter2 < 0 OR parameter2 > 11 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid type %parameter2%~ END
	END
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

	LPF ~get_random_treasure_names~ STR_VAR file = EVAL ~%resref%~ RET itemName = randomTreasureNames END
	LPF ~item_can_stack~ STR_VAR file = EVAL ~%resref%~ RET canStack END
	PATCH_IF canStack == 0 OR amount == 0 BEGIN
		SET amount = 1
	END

	PATCH_IF is_ee == 1 AND isExternal BEGIN
		SET amount2 = parameter3
		SET amount3 = parameter4
		PATCH_IF NOT ~%resref2%~ STRING_EQUAL ~~ BEGIN
			LPF ~get_random_treasure_names~ STR_VAR file = EVAL ~%resref2%~ RET itemName2 = randomTreasureNames END
			LPF ~item_can_stack~ STR_VAR file = EVAL ~%resref2%~ RET canStack2 = canStack END
			PATCH_IF canStack2 == 0 OR amount2 == 0 BEGIN
				SET amount2 = 1
			END
		END
		PATCH_IF NOT ~%resref3%~ STRING_EQUAL ~~ BEGIN
			LPF ~get_random_treasure_names~ STR_VAR file = EVAL ~%resref3%~ RET itemName3 = randomTreasureNames END
			LPF ~item_can_stack~ STR_VAR file = EVAL ~%resref3%~ RET canStack3 = canStack END
			PATCH_IF canStack3 == 0 OR amount3 == 0 BEGIN
				SET amount3 = 1
			END
		END
		PATCH_IF amount2 == 0 AND amount3 != 0 BEGIN
			SET amount2 = amount3
			SET amount3 = 0
			SPRINT itemName2 ~%itemName3%~
		END
	END

	PATCH_IF amount2 BEGIN
		SET strref += 1 // ~Crée aléatoirement %amount% "%itemName%" ou %amount2% "%itemName2%"~
	END
	PATCH_IF amount3 BEGIN
		SET strref += 1 // ~Crée aléatoirement %amount% "%itemName%", %amount2% "%itemName2%" ou %amount3% "%itemName3%"~
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Crée %amount% "%itemName%" dans l'inventaire %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_122_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_122_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		//PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~MISC56%eet_var%~ BEGIN
		PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~MISC56~ OR ~%resref%~ STRING_EQUAL_CASE ~MISC56_~ BEGIN
			LPF ~get_opcode_position~
				INT_VAR opcode = 112
			        match_target       = target
			        match_timingMode   = timingMode
			        match_resistance   = resistance
			        match_duration     = duration
			        match_probability1 = probability1
			        match_probability2 = probability2
			        match_saveType     = saveType
			        match_saveBonus    = saveBonus
			        match_special      = special
				STR_VAR match_macro = ~opcode_match_duration_and_probability1_and_probability2_and_resistance_and_resref_and_target_and_timingMode_and_saveBonus_and_saveType_and_special~
			        match_resref = ~%CURRENT_SOURCE_RES%~
				RET opcodePosition = position
			END
			PATCH_IF opcodePosition >= 0 BEGIN
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
				LPF ~delete_opcode~
					INT_VAR opcode = 112 match_position = opcodePosition
					RET $opcodes(~112~) = count
					RET_ARRAY ~opcodes_112~ = opcodes_xx
				END
				// Bug où il reste toujours un item dans le tableau si c'était le dernier
				// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
				PATCH_IF $opcodes(~112~) == 0 BEGIN
		            CLEAR_ARRAY ~opcodes_112~
		        END

		        SET opcode = 519
		        LPM ~add_opcode~
			END
		END
		ELSE BEGIN
			LPF ~get_opcode_position~
				INT_VAR opcode = 112
			        match_target       = target
			        match_timingMode   = timingMode
			        match_resistance   = resistance
			        match_duration     = duration
			        match_probability1 = probability1
			        match_probability2 = probability2
			        match_saveType     = saveType
			        match_saveBonus    = saveBonus
			        match_special      = special
				STR_VAR match_macro = ~opcode_match_duration_and_probability1_and_probability2_and_resistance_and_target_and_timingMode_and_saveBonus_and_saveType_and_special~
				RET opcodePosition = position
			END
			PATCH_IF opcodePosition >= 0 BEGIN
				SPRINT resref2 ~%resref%~
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
				LPF ~get_opcode_by_position~
					INT_VAR opcode = 112 position = opcodePosition
					RET resref
				END
				LPF ~delete_opcode~
					INT_VAR opcode = 112 match_position = opcodePosition
					RET $opcodes(~112~) = count
					RET_ARRAY ~opcodes_112~ = opcodes_xx
				END
				// Bug où il reste toujours un item dans le tableau si c'était le dernier
				// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
				PATCH_IF $opcodes(~112~) == 0 BEGIN
		            CLEAR_ARRAY ~opcodes_112~
		        END
		        SET opcode = 525
		        LPM ~add_opcode~
			END
		END
	END
END

/* --------------------------------- *
 * Item: Remove Inventory Item [123] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_123~ BEGIN
	LPM ~opcode_self_112~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_123~ BEGIN
	LPM ~opcode_self_probability_112~
END

DEFINE_PATCH_MACRO ~opcode_target_123~ BEGIN
	LPM ~opcode_target_112~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_123~ BEGIN
	LPM ~opcode_target_probability_112~
END

DEFINE_PATCH_MACRO ~opcode_123_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END


/* --------------------------------------------- *
 * Spell Effect: Teleport (Dimension Door) [124] *
 * --------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_124~ BEGIN
	LPM ~opcode_124_common~
	SET strref = 11240001 + parameter2

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_124~ BEGIN
	LPM ~opcode_124_common~
	SET strref = 11240011 + parameter2

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_target_124~ BEGIN
	LPM ~opcode_124_common~
	SET strref = 11240001 + parameter2

	PATCH_IF parameter2 == 1 BEGIN
		SET strref = 11240005 // ~Téléporte %theTarget% vers le porteur~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SET strref = 11240006 // ~Échange la place %ofTheTarget% avec le porteur~
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_124~ BEGIN
	LPM ~opcode_124_common~
	SET strref = 11240011 + parameter2

	PATCH_IF parameter2 == 1 BEGIN
		SET strref = 11240015 // ~de téléporter %theTarget% vers le porteur~
	END
	ELSE PATCH_IF parameter2 == 3 BEGIN
		SET strref = 11240016 // ~d'échanger la place %ofTheTarget% avec le porteur~
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_124_common~ BEGIN
	PATCH_IF parameter2 > 3 OR parameter2 < 0 BEGIN
		SET parameter2 = 0
	END
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
	SET strref = 11260001 // ~Vitesse de déplacement~
	LPM ~opcode_126_common~
	PATCH_IF strref == 11260001 BEGIN
		LPF ~opcode_mod~ INT_VAR strref = strref STR_VAR value = ~%parameter1%~ complex_value RET description END
	END
	ELSE BEGIN
		SPRINT description (AT strref)
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_126~ BEGIN
	SET strref = 11260003 // ~la vitesse de déplacement~
	LPM ~opcode_126_common~
	PATCH_IF strref == 11260003 BEGIN
		LPF ~opcode_probability~ INT_VAR strref = strref STR_VAR value = EVAL ~%parameter1%~ RET description END
	END
	ELSE BEGIN
		SPRINT description (AT strref)
	END
END

DEFINE_PATCH_MACRO ~opcode_target_126~ BEGIN
	SET strref = 11260002 // ~la vitesse de déplacement~
	LPM ~opcode_126_common~
	PATCH_IF strref == 11260002 BEGIN
		LPF ~opcode_target~ INT_VAR strref = strref STR_VAR value = EVAL ~%parameter1%~ RET description END
	END
	ELSE BEGIN
		SPRINT description (AT strref)
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_126~ BEGIN
	LPM ~opcode_self_probability_126~
END

DEFINE_PATCH_MACRO ~opcode_126_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF parameter2 == MOD_TYPE_percentage AND parameter1 == 100 BEGIN
			// Suppression de l'opcode 163, redondant
			SET opcode = 163
			LPF ~delete_opcode~
				INT_VAR opcode // "Free action"
					match_probability1 = probability1
					match_probability2 = probability2
				STR_VAR match_macro = ~opcode_match_probability1_and_probability2~
				RET $opcodes(~%opcode%~) = count
				RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_126_common~ BEGIN
	SET parameter2 = parameter2 == 5 ? MOD_TYPE_percentage : parameter2

	// Contrairement aux autres opcodes, le calcul est fondé sur la vitesse de déplacement de base de la cible
	// Ainsi mettre une vitesse à 100% revient à la faire revenir à la normale
	PATCH_IF parameter1 == 0 AND parameter2 >= MOD_TYPE_flat BEGIN
		SET strref += 10
		SET cumulable = 1
	END
	ELSE PATCH_IF parameter1 == 100 AND parameter2 == MOD_TYPE_percentage BEGIN
		SET strref += 20
		SET cumulable = 1
	END
END

DEFINE_PATCH_MACRO ~opcode_126_is_valid~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative AND parameter1 == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No change detected: Value = Value + 0.~ END
	END
	PATCH_IF parameter2 < MOD_TYPE_cumulative OR (parameter2 > MOD_TYPE_percentage AND (parameter2 != 5 OR is_ee == 0)) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid type %parameter2%~ END
	END
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
	LOCAL_SET isHostile = type >= 5 AND type <= 9 ? 1 : 0

	PATCH_IF mode == 0 AND ~%resref%~ STRING_EQUAL ~~ BEGIN
		// Ces fichiers ne sont chargés que si special == 0 et strref vide
		SPRINT file $opcode_127_files(~%type%~)

		PATCH_IF type == 3 OR type == 4 OR type == 8 OR type == 9 BEGIN
			SET isMonster = 0
		END
		PATCH_IF ~%custom_str%~ STRING_EQUAL ~~ BEGIN
			LPF ~get_creatures_amount~ INT_VAR totalLevel = amount multiplier = custom_int STR_VAR file RET amount amountMin amountMax END
			SET strref += amountMax == 1 ? 4 : 6
		END
		ELSE BEGIN
			SPRINT amount ~%custom_str%~
			SET strref += 6
		END
		SET strref += isMonster == 1 ? 0 : 1
		SET strref += isHostile == 1 ? 8 : 0
	END
	ELSE BEGIN
		SPRINT file ~%resref%~

		PATCH_IF mode == 0 BEGIN
			SET strref += 16 // ~Invoque des créatures pour un total de %amount% niveaux (%creatures%)~
		END
		ELSE PATCH_IF (mode BAND BIT1) > 0 BEGIN
			SET strref += 17 // ~Invoque des créatures pour un total de niveaux égal au niveau du lanceur (%creatures%)~
		END
		ELSE BEGIN
			SET amount = custom_int > 1 ? amount * custom_int : amount
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

DEFINE_PATCH_MACRO ~opcode_127_is_valid~ BEGIN
	PATCH_IF NOT FILE_EXISTS_IN_GAME ~%resref%.2da~ AND (special != 0 OR NOT ~%resref%~ STRING_EQUAL ~~) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : File %resref%.2da does not exist, the game may crash.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_127_group~ BEGIN
	LOCAL_SET grouped = 0
	LOCAL_SET amountMin = 0
	LOCAL_SET amountMax = 0
	LOCAL_SET totalProbability = 0
	LPM ~opcode_group_by_target~

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		CLEAR_ARRAY positions
		SET grouped = 0
		SET totalProbability = probability
		LPF ~get_creatures_amount~ INT_VAR totalLevel = parameter1 multiplier = custom_int STR_VAR file = $opcode_127_files(~%parameter2%~) RET amount amountMin amountMax END
		PATCH_IF special == 0 AND ~%resref%~ STRING_EQUAL ~~ AND NOT VARIABLE_IS_SET $positions_already_check(~%position%~) BEGIN
			SET $positions(~%position%~) = 1
			SET $positions_already_check(~%position%~) = 1
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_match_vars~
				PATCH_IF NOT VARIABLE_IS_SET $positions_already_check(~%match_position%~) BEGIN
					LPM ~opcode_match_opcode_127_group~
					PATCH_IF match == 1 BEGIN
						LPF ~get_creatures_amount~ INT_VAR totalLevel = match_parameter1 multiplier = match_custom_int STR_VAR file = $opcode_127_files(~%match_parameter2%~) RET matchAmountMin = amountMin matchAmountMax = amountMax END
						PATCH_IF matchAmountMin < amountMin BEGIN
							SET amountMin = matchAmountMin
						END
						PATCH_IF matchAmountMax > amountMax BEGIN
	                        SET amountMax = matchAmountMax
	                    END
						SET $positions(~%match_position%~) = 1
						SET $positions_already_check(~%match_position%~) = 1
						SET grouped = 1
						SET totalProbability += match_probability
					END
				END
			END
		END
		PATCH_IF grouped == 1 BEGIN
			PATCH_PHP_EACH positions AS position => _ BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
	        PATCH_IF totalProbability < 100 BEGIN
	            SET amountMin = 0
	        END
			SPRINT custom_str @101130 // ~entre %amountMin% et %amountMax%~
			SET probability = 100
			SET probability1 = 100
			SET probability2 = 0
	        LPM ~add_opcode~
		END
	END
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
// TODO : split des effets
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
// TODO : split des effets
DEFINE_PATCH_MACRO ~opcode_self_130~ BEGIN
    SPRINT description @11300001 // ~Bénédiction~
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
	SET parameter1 = parameter1 < 0 ? parameter1 : parameter1 BAND 255
	LPM ~opcode_self_22~  // ~Chance~
    LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_131~ BEGIN
	SET parameter1 = parameter1 < 0 ? parameter1 : parameter1 BAND 255
	LPM ~opcode_self_probability_22~ // ~la chance~
    LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_131~ BEGIN
	SET parameter1 = parameter1 BAND 255
	LPM ~opcode_target_22~ // ~la chance~
    LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_131~ BEGIN
	SET parameter1 = parameter1 < 0 ? parameter1 : parameter1 BAND 255
    LPM ~opcode_target_probability_22~ // ~la chance~
    LPM ~opcode_not_cumulative~
END

/* --------------------------------------------------------------------- *
 * State: Raise Strength, Constitution, & Dexterity Non-Cumulative [132] *
 * --------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_132~ BEGIN
	LPM ~opcode_132_common~
	LPF ~opcode_mod~ INT_VAR strref = 11320001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Force, dextérité et constitution~
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
	// A negative value of Statistic Modifier sets the Strength, Constitution and Dexterity of the targeted creature(s) to 25.
	// N'est pas à prendre au pied de la lettre : -1 est considéré comme 255, -10 comme 246, -255 comme 1...
	SET parameter1 = parameter1 MODULO 256
	PATCH_IF parameter1 >= 25 BEGIN
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
DEFINE_PATCH_MACRO ~opcode_self_134~ BEGIN
	SPRINT description @11340001 // ~Pétrification~
END

DEFINE_PATCH_MACRO ~opcode_target_134~ BEGIN
	SPRINT description @11340002 // ~Pétrifie %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_134~ BEGIN
	SPRINT description @11340003 // ~d'être pétrifié~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_134~ BEGIN
	SPRINT description @11340004 // ~de pétrifier %theTarget%~
END

/* ----------------------------- *
 * Polymorph into Specific [135] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_135~ BEGIN
	SET strref = 11350001 // ~Transformation en %creatureName%~
	LPM ~opcode_135_common~
END

DEFINE_PATCH_MACRO ~opcode_target_135~ BEGIN
	SET strref = 11350011 // ~Transforme %theTarget% en %creatureName%~
	LPM ~opcode_135_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_135~ BEGIN
	SET strref = 11350021 // ~de se transformer en %creatureName%~
	LPM ~opcode_135_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_135~ BEGIN
	SET strref = 11350031 // ~de transformer %theTarget% en %creatureName%~
	LPM ~opcode_135_common~
END

DEFINE_PATCH_MACRO ~opcode_135_common~ BEGIN
	PATCH_IF ~%resref%~ STRING_EQUAL ~~ BEGIN
		SET ignoreDuration = 1
		SET strref += 2 // ~%theTarget% retrouve sa forme naturelle~
	END
	ELSE BEGIN
		SET strref += parameter2 == 0 ? 0 : 1 // transformation / déguisement
		LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
		PATCH_IF ~%creatureName%~ STRING_EQUAL ~~ BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% self : Nom de la créature introuvable : %resref%~ END
			SPRINT creatureName @11350100 // ~créature sans nom~
		END
		SPRINT description @11350001 // ~Transforme %theTarget% en %creatureName%~
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_135_post_group~ BEGIN
	PATCH_PHP_EACH ~opcodes_171~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET searchPosition = position
		PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
			INNER_PATCH_FILE ~%resref%.spl~ BEGIN
				GET_OFFSET_ARRAY headerOffsets SPL_V10_HEADERS
				PHP_EACH headerOffsets AS _ => headerOffset BEGIN
					GET_OFFSET_ARRAY2 offsets headerOffset SPL_V10_HEAD_EFFECTS
					PHP_EACH offsets AS _ => offset BEGIN
						LPM ~read_effect_vars~
						PATCH_IF opcode == 215 AND  ~%resref%~ STRING_EQUAL_CASE ~POLYBACK~ BEGIN
							LPF ~delete_opcode~
                                INT_VAR opcode = 171 match_position = searchPosition
                                RET $opcodes(~171~) = count
                                RET_ARRAY EVAL ~opcodes_171~ = opcodes_xx
                            END
						END
					END
				END
			END
		END
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
	SET parameter1 = parameter1 < 0 ? parameter1 : parameter1 BAND 255
	SET parameter1 = 0 - parameter1
	LPM ~opcode_self_22~  // ~Chance~
    LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_137~ BEGIN
	SET parameter1 = parameter1 < 0 ? parameter1 : parameter1 BAND 255
	SET parameter1 = 0 - parameter1
	LPM ~opcode_self_probability_22~ // ~la chance~
    LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_137~ BEGIN
	SET parameter1 = parameter1 < 0 ? parameter1 : parameter1 BAND 255
	SET parameter1 = 0 - parameter1
	LPM ~opcode_target_22~ // ~la chance~
    LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_137~ BEGIN
	SET parameter1 = parameter1 < 0 ? parameter1 : parameter1 BAND 255
	SET parameter1 = 0 - parameter1
    LPM ~opcode_target_probability_22~ // ~la chance~
    LPM ~opcode_not_cumulative~
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

DEFINE_PATCH_MACRO ~opcode_143_group~ BEGIN
	LPM ~opcode_143_group_mod~
END

DEFINE_PATCH_MACRO ~opcode_143_is_valid~ BEGIN
	PATCH_IF NOT FILE_EXISTS_IN_GAME ~%resref%.itm~ BEGIN
		isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Unknown resource %resref%.itm.~ END
	END
	PATCH_IF parameter1 < 0 OR parameter1 > 38 BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid slot %parameter1%.~ END
	END
END

/* ---------------------------- *
 * Button: Disable Button [144] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_144~ BEGIN
	LOCAL_SET strref = 11440001 + parameter2
	SPRINT action @11440020 // ~Empêche~
	LPM ~opcode_144_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_144~ BEGIN
	LOCAL_SET strref = 11440001 + parameter2
	SPRINT action @11440021 // ~d'empêcher~
	LPM ~opcode_144_common~
END

DEFINE_PATCH_MACRO ~opcode_target_144~ BEGIN
	LOCAL_SET strref = 11440021 + parameter2
	SPRINT action @11440040 // ~Empêche %theTarget%~
	LPM ~opcode_144_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_144~ BEGIN
	LOCAL_SET strref = 11440021 + parameter2
	SPRINT action @11440041 //~d'empêcher %theTarget%~
	LPM ~opcode_144_common~
END

DEFINE_PATCH_MACRO ~opcode_144_common~ BEGIN
	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END // ~Empêche %theTarget% d'utiliser xxx~
END

DEFINE_PATCH_MACRO ~opcode_144_is_valid~ BEGIN
	PATCH_IF parameter2 < 0 OR parameter2 > 15 OR
			 NOT is_ee AND (parameter2 == 15 OR parameter2 == 10) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid button %parameter2%.~ END
	END
END


/* -------------------------------------------- *
 * Spell: Disable Spell Casting Abilities [145] *
 * -------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_145~ BEGIN
	LOCAL_SET value = custom_int > 0 ? custom_int : (1 << parameter2)

	PATCH_IF value == 7 BEGIN
		SPRINT description @11450001 // ~Empêche %theTarget% de lancer des sorts~
	END
	ELSE BEGIN
		LPF ~get_spell_type_str~ INT_VAR value RET spellType END

		PATCH_IF (parameter2 == 0 OR custom_int == 1) AND (NOT armor_show_allows_to_cast_spells OR (armor_show_allows_to_cast_spells AND VARIABLE_IS_SET isRobe AND isRobe)) BEGIN
			SPRINT description @11450000 // ~Empêche %theTarget% de lancer des sorts %spellType%~
		END
		ELSE PATCH_IF parameter2 != 0 AND custom_int != 1 BEGIN
			SPRINT description @11450000 // ~Empêche %theTarget% de lancer des sorts %spellType%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_145~ BEGIN
	LOCAL_SET value = custom_int > 0 ? custom_int : (1 << parameter2)

	PATCH_IF value == 7 BEGIN
		SPRINT description @11450051 // ~d'empêcher %theTarget% de lancer des sorts~
	END
	ELSE BEGIN
		LPF ~get_spell_type_str~ INT_VAR value RET spellType END

		SPRINT description @11450050 // ~d'empêcher %theTarget% de lancer des sorts %spellType%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_145~ BEGIN
	LPM ~opcode_self_145~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_145~ BEGIN
	LPM ~opcode_self_probability_145~
END

DEFINE_PATCH_MACRO ~opcode_145_is_valid~ BEGIN
	PATCH_IF parameter2 < 0 OR parameter2 > 3 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Spell Type %parameter2%.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_145_group~ BEGIN
	LOCAL_SET group = 1
	LOCAL_SET newSpellType = 0b0
	LOCAL_SET spellType = 0

	PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		// TODO: Toute cette partie est commune avec l'opcode 60, cependant, si je déplace ce code dans une macro, le
		//       tableau opcodes_145 n'est pas mis à jour si un regroupement est effectué dans la macro...
		SET group = 0
		SET newSpellType = 1 << %parameter2%
		CLEAR_ARRAY positions
		PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN
			~%parameter2%~ => ~%position%~
		END
		PATCH_FOR_EACH spellType IN 0 1 2 BEGIN
			LPF ~get_opcode_position~
				INT_VAR opcode
					match_position     = position
					match_custom_int   = 0
					match_target       = target
					match_probability1 = probability1
					match_probability2 = probability2
					match_parameter1   = parameter1
					match_parameter2   = spellType
					match_parameter3   = parameter3
					match_parameter4   = parameter4
					match_timingMode   = timingMode
					match_resistance   = resistance
					match_duration     = duration
					match_power        = power
			        match_diceCount    = diceCount
			        match_diceSides    = diceSides
					match_saveType     = saveType
					match_saveBonus    = saveBonus
					match_special      = special
				STR_VAR match_macro = ~opcode_match_opcode_60_145_group~
				RET opcodePosition = position
			END
			PATCH_IF opcodePosition >= 0 BEGIN
				SET group = 1
				SET newSpellType |= 1 << %spellType%
				SET $positions(~%spellType%~) = opcodePosition
			END
		END
		PATCH_IF group == 1 BEGIN
			PATCH_PHP_EACH positions AS _ => position1 BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position1
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
	        SET custom_int = newSpellType
	        LPM ~add_opcode~
		END
	END
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
	LOCAL_SPRINT strDuration ~~
	TO_UPPER resref
	// FIXME: Non maintenable
	PATCH_IF VARIABLE_IS_SET $opcode_target_146_item_revision(~%resref%~) BEGIN
		SET strref = $opcode_target_146_item_revision(~%resref%~)
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
	ELSE PATCH_IF VARIABLE_IS_SET itemType AND itemType == ITM_TYPE_potion BEGIN
		PATCH_IF NOT ((type == 2 OR type == 0) AND castingLevel > 0) BEGIN
			//SET castingLevel = 0
		END
		LPF ~get_item_spell_effects_description~ INT_VAR castingLevel STR_VAR file = ~%resref%~ RET spellDescription = description END
        SPRINT description ~%spellDescription%~
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
			LPM ~opcode_146_common~
		END
		ELSE BEGIN
			// Protection contre les boucles infinies
			PATCH_IF NOT VARIABLE_IS_SET $recursive_resref(~%resref%~) BEGIN
				PATCH_IF NOT ((type == 2 OR type == 0) AND castingLevel > 0) BEGIN
					//SET castingLevel = 0
				END
				SET $recursive_resref(~%resref%~) = 1
				SET $recursive_resref(~%CURRENT_SOURCE_RES%~) = 1
				LPF ~get_item_spell_effects_description~ INT_VAR castingLevel ignoreDurationIfSameForAllEffect = timingMode == TIMING_delayed ? 1 : 0 STR_VAR file = ~%resref%~ RET description strDuration END

				// Remplacer les "pendant 1 round" par "chaque round pendant x rounds"
				SET frequency = (duration - (duration MODULO 10000)) / 10000
				PATCH_IF (timingMode == 5000 OR timingMode == 5001) AND frequency == 6 BEGIN
					SPRINT strDuration @100302 // ~1 round~
					SPRINT find @100311 // ~pendant %strDuration%~
					LPF ~get_duration_value~ INT_VAR duration RET replace = value END
					INNER_PATCH_SAVE tmp_description ~%description%~ BEGIN
						REPLACE_TEXTUALLY ~%find%~ ~%replace%~
					END
				    PATCH_IF NOT ~%description%~ STRING_EQUAL ~%tmp_description%~ BEGIN
				        SPRINT description ~%tmp_description%~
						SET timingMode = TIMING_duration // Sinon durée ajoutée tout de même
						SET ignoreDuration = 1
				    END
				END
			END
			CLEAR_ARRAY recursive_resref
		END
	END
	LPM ~opcode_146_condition~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_146~ BEGIN
	LPM ~opcode_target_probability_146~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_146~ BEGIN
	LOCAL_SET castingLevel = ~%parameter1%~
	LOCAL_SET type = parameter2
	LOCAL_SPRINT strDuration ~~
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
			LPM ~opcode_146_common~
		END
		ELSE BEGIN
			// Protection contre les boucles infinies
			PATCH_IF NOT VARIABLE_IS_SET $recursive_resref(~%resref%~) BEGIN
				PATCH_IF NOT ((type == 2 OR type == 0) AND castingLevel > 0) BEGIN
					//SET castingLevel = 0
				END
				SET $recursive_resref(~%resref%~) = 1
				SET $recursive_resref(~%CURRENT_SOURCE_RES%~) = 1
				LPF ~get_item_spell_effects_description~ INT_VAR castingLevel ignoreDurationIfSameForAllEffect = timingMode == TIMING_delayed ? 1 : 0 baseProbability = probability STR_VAR file = ~%resref%~ RET description END

				INNER_PATCH_SAVE description ~%description%~ BEGIN
					SPRINT regex @10019 // ~^[0-9]+ % de chance ~
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
				END
			END
			CLEAR_ARRAY recursive_resref
		END
	END
	LPM ~opcode_146_condition~
END

DEFINE_PATCH_MACRO ~opcode_146_common~ BEGIN
	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND (type == 2 OR castingLevel > 0 AND type == 0) BEGIN
		SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
		SPRINT description ~%description% (%castingLevelStr%)~
	END
END

DEFINE_PATCH_MACRO ~opcode_146_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_146_condition~ BEGIN
	PATCH_IF timingMode == TIMING_delayed BEGIN
		INNER_PATCH_SAVE tmp_description ~%description%~ BEGIN
			REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~~
		END
	    PATCH_IF NOT ~%description%~ STRING_EQUAL ~%tmp_description%~ BEGIN
			LPF ~get_duration_value~ INT_VAR duration RET condition = value END
			PATCH_IF NOT ~%condition%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF NOT ~%strDuration%~ STRING_EQUAL ~~ BEGIN
					SPRINT strDuration @100311 // ~pendant %strDuration%~
					SPRINT condition ~%condition%, %strDuration%~
				END
				LPF ~ucfirst~ STR_VAR value = ~%condition%~ RET condition = string END
		        PATCH_IF ~%description%~ STRING_MATCHES_REGEXP ~^%crlf%~ == 1 BEGIN
					INNER_PATCH_SAVE description ~%description%~ BEGIN
						REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~%crlf%  ~
					END
					SPRINT description ~%crlf%  - %description%~
				END
			END
			SET ignoreDuration = 1
			SET timingMode = TIMING_duration // La méthode add_duration a une exception pour les timings delayed...
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_146_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		// Si un opcode 321 pointant le même sort que le 146 existe => supprimer le  321 + ajouter (non cumulable) au 146
		LPF ~get_opcode_position~
			INT_VAR opcode = 321
				match_position     = position
				match_target       = target
				match_timingMode   = timingMode
				match_resistance   = resistance
				match_duration     = duration
				match_probability1 = probability1
				match_probability2 = probability2
				match_saveType     = saveType
				match_saveBonus    = saveBonus
				match_special      = special
			STR_VAR match_macro = ~opcode_match_opcode_146_group~
		        match_resref = ~%resref%~
			RET opcodePosition = position
		END
		PATCH_IF opcodePosition >= 0 BEGIN
			LPF ~delete_opcode~
				INT_VAR opcode = 321 match_position = opcodePosition
				RET $opcodes(~321~) = count
				RET_ARRAY EVAL ~opcodes_321~ = opcodes_xx
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~321~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_321~
	        END
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
			SET cumulable= 0
			LPM ~add_opcode~
		END
	END
END

/* ------------------------ *
 * Spell: Learn Spell [147] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_147~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	SPRINT description @11470001 // ~Retranscription du sort %spellName%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_147~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	SPRINT description @11470003 // ~de retranscrire le sort %spellName%~
END

DEFINE_PATCH_MACRO ~opcode_target_147~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	SPRINT description @11470002 // ~Fait retranscrire le sort %spellName% %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_147~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	SPRINT description @11470004 // ~de faire retranscrire le sort %spellName% %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_147_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

/* ---------------------------------- *
 * Spell: Cast Spell (at Point) [148] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_148~ BEGIN
	LPM ~opcode_self_146~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_148~ BEGIN
	LPM ~opcode_self_probability_146~
END

DEFINE_PATCH_MACRO ~opcode_target_148~ BEGIN
	LPM ~opcode_self_148~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_148~ BEGIN
	LPM ~opcode_self_probability_148~
END

DEFINE_PATCH_MACRO ~opcode_148_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

/* ------------------------------ *
 * Spell Effect: Find Traps [150] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_150~ BEGIN
	SPRINT description @11500001 // ~Détecte les pièges~
END

DEFINE_PATCH_MACRO ~opcode_target_150~ BEGIN
	SPRINT description @11500002 // ~%theTarget% détecte les pièges~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_150~ BEGIN
	SPRINT description @11500003 // ~de détecter les pièges~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_150~ BEGIN
	SPRINT description @11500004 // ~que %theTarget% détecte les pièges~
END

/* ------------------------------ *
 * Summon: Replace Creature [151] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_151~ BEGIN
	LPM ~opcode_target_151~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_151~ BEGIN
	LPM ~opcode_target_probability_151~
END

DEFINE_PATCH_MACRO ~opcode_target_151~ BEGIN
	LPF ~get_creature_name~ STR_VAR file = EVAL ~%resref%~ RET creatureName END
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @11510001 // ~Remplace %theTarget% par %creatureName%~
	END
	ELSE PATCH_IF parameter2 == 1 OR parameter2 == 2 BEGIN
		SPRINT description @11510002 // ~Tue et remplace %theTarget% par %creatureName%~
	END
	ELSE BEGIN
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
	ELSE BEGIN
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
 * Overlay: Entangle [154] *
 * ----------------------- */
DEFINE_PATCH_MACRO ~opcode_self_154~ BEGIN
	SPRINT description @11540001 // ~Enchevêtrement~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_154~ BEGIN
	SPRINT description @11540003 // ~d'enchevêtrer %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_154~ BEGIN
	SPRINT description @11540002 // ~Enchevêtre %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_154~ BEGIN
	LPM ~opcode_self_probability_154~ // ~d'enchevêtrer %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_154_group~ BEGIN
	LOCAL_SET searchOpcode = 126
	PATCH_IF VARIABLE_IS_SET $opcodes(~%searchOpcode%~) BEGIN
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~

			SET opcode = searchOpcode
			SET oldPosition = position
			SET oldCount = $opcodes(~%opcode%~)
			LPF ~delete_opcode~
				INT_VAR opcode
				    match_target       = target
			        match_timingMode   = timingMode
			        match_duration     = duration
			        match_probability1 = probability1
			        match_probability2 = probability2
			        match_diceCount    = diceCount
			        match_diceSides    = diceSides
			        match_power        = power
			        match_saveType     = saveType
			        match_saveBonus    = saveBonus
			        match_resistance   = resistance
				STR_VAR match_macro = ~opcode_match_opcode_154_group~
				RET $opcodes(~%opcode%~) = count
				RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
			END
			PATCH_IF oldCount == $opcodes(~%opcode%~) BEGIN
				SET opcode = 154
				LPF ~delete_opcode~
					INT_VAR opcode match_position = oldPosition
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
		END
	END
	ELSE BEGIN
		CLEAR_ARRAY EVAL ~opcodes_%opcode%~
		SET $opcodes(~%opcode%~) = 0
	END
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
	LOCAL_SET amount = parameter1 MODULO 65536
	PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
		SPRINT amount ~%custom_str%~
		SPRINT description @11590002 // ~Crée %amount% images miroir sur %theTarget%~
	END ELSE PATCH_IF amount == 1 BEGIN
		SPRINT description @11590001 // ~Crée 1 image miroir sur %theTarget%~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @11590002 // ~Crée %amount% images miroir sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @11590003 // ~Dissipe les images-miroir de %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_159~ BEGIN
	LOCAL_SET amount = parameter1 MODULO 65536
	PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
    	SPRINT amount ~%custom_str%~
		SPRINT description @11590012 // ~de créer %amount% images miroir sur %theTarget%~
    END ELSE PATCH_IF amount == 1 BEGIN
		SPRINT description @11590011 // ~de créer 1 image miroir sur %theTarget%~
	END
	ELSE PATCH_IF amount > 1 BEGIN
		SPRINT description @11590012 // ~de créer %amount% images miroir sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @11590013 // ~de dissiper les images-miroir de %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_159~ BEGIN
	LPM ~opcode_self_159~ // ~Crée %amount% images miroir sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_159~ BEGIN
	LPM ~opcode_self_probability_159~ // ~de créer %amount% images miroir sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_159_group~ BEGIN
	LOCAL_SET amountMin = 0
	LOCAL_SET amountMax = 0
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions_already_check~ BEGIN END
	CLEAR_ARRAY positions
	CLEAR_ARRAY positions_already_check

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET grouped = 0
		CLEAR_ARRAY positions
		PATCH_IF NOT VARIABLE_IS_SET $positions_already_check(~%position%~) BEGIN
			SET $positions(~%position%~) = 1
			SET $positions_already_check(~%position%~) = 1
			SET parameter1 = parameter1 MODULO 65536
			PATCH_IF parameter1 > 0 BEGIN
				PATCH_IF amountMin = 0 OR amountMin > parameter1 BEGIN
					SET amountMin = parameter1
				END
				PATCH_IF amountMax = 0 OR amountMax < parameter1 BEGIN
					SET amountMax = parameter1
				END
				PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
					LPM ~data_to_match_vars~
					SET match_parameter1 = match_parameter1 MODULO 65536
					PATCH_IF match_parameter1 > 0 AND NOT VARIABLE_IS_SET $positions_already_check(~%match_position%~) BEGIN
						LPM ~opcode_match_opcode_159_group~
						PATCH_IF match == 1 BEGIN
							PATCH_IF amountMin = 0 OR amountMin > match_parameter1 BEGIN
								SET amountMin = match_parameter1
							END
							PATCH_IF amountMax = 0 OR amountMax < match_parameter1 BEGIN
								SET amountMax = match_parameter1
							END
							SET $positions(~%match_position%~) = 1
							SET $positions_already_check(~%match_position%~) = 1
							SET grouped = 1
						END
					END
				END
			END
		END
		PATCH_IF grouped == 1 BEGIN
			PATCH_PHP_EACH positions AS position => _ BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
			SPRINT custom_str @101130 // ~entre %amountMin% et %amountMax%~
	        LPM ~add_opcode~
		END
	END
END

/* ---------------------- *
 * Remove Sanctuary [160] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_160~ BEGIN
	SPRINT description @11600001 // ~Dissipation de sanctuaire~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_160~ BEGIN
	SPRINT description @11600003 // ~de dissiper le sanctuaire sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_160~ BEGIN
	SPRINT description @11600002 // ~Dissipe le sanctuaire sur %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_160~ BEGIN
	LPM ~opcode_self_probability_160~
END

/* ------------------ *
 * Cure: Horror [161] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_161~ BEGIN
	SPRINT description @11610001 // ~Dissipation de l'horreur~
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

/* ---------------- *
 * Cure: Hold [162] *
 * ---------------- */
DEFINE_PATCH_MACRO ~opcode_self_162~ BEGIN
	SPRINT description @11620001 // ~Guérison de la paralysie~
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
	SPRINT description @11630001 // ~Rétablissement de la vitesse de déplacement~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_163~ BEGIN
	SPRINT description @11630003 // ~de rétablir la vitesse de déplacement %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_163~ BEGIN
	SPRINT description @11630002 // ~Rétabli la vitesse de déplacement %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_163~ BEGIN
	LPM ~opcode_self_probability_163~ // ~de rétablir la vitesse de déplacement %ofTheTarget%~
END

/* ---------------------- *
 * Cure: Drunkeness [164] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_164~ BEGIN
	SPRINT description @11640001 // ~Guérison de l'ivresse~
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
	SPRINT description @11650001 // ~Combat mental~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_165~ BEGIN
	SPRINT description @11650003 // ~d'entrer dans un combat mental~
END

DEFINE_PATCH_MACRO ~opcode_target_165~ BEGIN
	SPRINT description @11650002 // ~Combat mental %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_165~ BEGIN
	SPRINT description @11650004 // ~de faire entrer %theTarget% dans un combat mental~
END

/* ------------------------------------- *
 * Stat: Magic Resistance Modifier [166] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_166~ BEGIN
	SET resistName = 11660001 // ~Résistance à la magie~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_166~ BEGIN
	SET resistName = 11660001 // ~Résistance à la magie~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_166~ BEGIN
	SET resistName = 11660001 // ~Résistance à la magie~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_166~ BEGIN
	LPM ~opcode_self_probability_166~
END

DEFINE_PATCH_MACRO ~opcode_166_is_valid~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative AND parameter1 == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No change detected: Value = Value + 0.~ END
	END
	PATCH_IF parameter2 != MOD_TYPE_cumulative AND parameter2 != MOD_TYPE_flat BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %parameter2%.~ END
	END
END

/* ----------------------------------------------- *
 * Stat: THAC0 Modifier with Missile Weapons [167] *
 * ----------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_167~ BEGIN
	LOCAL_SET value = parameter1
	LOCAL_SET strref = 0
	SET parameter2 = parameter2 BAND 65535
	LPM ~opcode_mod_base~
	PATCH_IF NOT IS_AN_INT ~%value%~ OR value != 0 BEGIN
	    SPRINT name @10540001  // ~TAC0~
	    SPRINT value @11670001 // ~%value% avec les armes de trait et les armes de jet~
		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_167~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 11670002 RET description END // ~le TAC0 avec les armes de trait et les armes de jet~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_167~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 11670002 RET description END // ~le TAC0 avec les armes de trait et les armes de jet~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_167~ BEGIN
	LPM ~opcode_self_probability_167~
END

DEFINE_PATCH_MACRO ~opcode_167_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* -------------------------------- *
 * Spell: Give Innate Ability [171] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_171~ BEGIN
	LOCAL_SET strref = 11710001 // ~Ajoute la capacité %spellName% %toTheTarget%~
	LPM ~opcode_171_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_171~ BEGIN
	LOCAL_SET strref = 11710011 // ~d'ajouter la capacité %spellName% %toTheTarget%~
	LPM ~opcode_171_common~
END

DEFINE_PATCH_MACRO ~opcode_target_171~ BEGIN
	LPM ~opcode_self_171~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_171~ BEGIN
	LPM ~opcode_self_probability_171~
END

DEFINE_PATCH_MACRO ~opcode_171_common~ BEGIN
	PATCH_IF FILE_EXISTS_IN_GAME "%resref%.spl" BEGIN
		LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
		INNER_PATCH_FILE "%resref%.spl" BEGIN
			READ_SHORT SPL_type spellType
		END
		PATCH_IF spellType == 1 OR spellType == 2 BEGIN
			SET strref += spellType // sorts
		END
		SPRINT description (AT strref)
		// Hack pour forcer l'affichage de la durée / usage strictement interne
		PATCH_IF custom_int AND timingMode == TIMING_duration AND duration > 0 BEGIN
			LPF ~get_duration_value~ INT_VAR duration RET duration = value END

			PATCH_IF NOT ~%duration%~ STRING_EQUAL ~~ BEGIN
				SPRINT description ~%description% %duration%~
				SET ignoreDuration = 1
			END
		END
	END
END

/* ------------------------- *
 * Spell: Remove Spell [172] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_172~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		//TODO: If the key is not 8 characters long, all memorized copies will be removed.
		//TODO: @11720002 = ~Supprime le sort %spellName% de la mémoire et du livre de sorts %ofTheTarget%~
		//> Jamais observé IG : tous les sorts sont supprimés et oubliés
		SPRINT description @11720001 // ~Supprime le sort %spellName% du livre de sorts %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_172~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		//TODO: If the key is not 8 characters long, all memorized copies will be removed.
		//TODO: @11720004 = ~de supprimer le sort %spellName% de la mémoire et du livre de sorts %ofTheTarget%~
		//> Jamais observé IG : tous les sorts sont supprimés et oubliés
		SPRINT description @11720003 // ~de supprimer le sort %spellName% du livre de sorts %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_172~ BEGIN
	LPM ~opcode_self_172~ // ~Supprime le sort %spellName% du livre de sorts %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_172~ BEGIN
	LPM ~opcode_self_probability_172~ // ~de supprimer le sort %spellName% de la mémoire et du livre de sorts %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_172_group~ BEGIN
	LOCAL_SET searchOpcode = 171

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET group = 0
		SET currentOpcode = opcode
		SET currentDuration = duration
		SET currentPosition = position
		TEXT_SPRINT currentresref ~%resref%~

		// Group 171 - 172 (ajout d'un sort puis retrait)
		// L'ajout possède une durée permanente mais vient à être retirée du livre
		// La durée de l'opcode 171 est alors modifiée et l'opcode 172 est retiré
		PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND timingMode == TIMING_delayed AND
				 VARIABLE_IS_SET $opcodes(~%searchOpcode%~) AND
				 $opcodes(~%searchOpcode%~) > 0 BEGIN
			PATCH_PHP_EACH EVAL ~opcodes_%searchOpcode%~ AS data => _ BEGIN
				PATCH_IF group == 0 BEGIN
					LPM ~data_to_vars~
					SET opcode = searchOpcode
					PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%currentresref%~ BEGIN
						SET group = 1
						SET oldDuration = duration
						SET oldTimingMode = timingMode

						// ajout de l'opcode 171 modifié
						SET timingMode = TIMING_duration
						SET duration = currentDuration
						SET custom_int = 1 // Force l'affichage de la durée
						LPM ~add_opcode~

						// suppression de l'opcode 171 initial
						// FIXME Marche pas en mettant le add_opcode après... raison ?
						// La position n'est pas une condition suffisante
						LPF ~delete_opcode~
							INT_VAR opcode
								match_timingMode = oldTimingMode
								match_duration = oldDuration
							STR_VAR
								match_macro = ~opcode_match_duration_and_timingMode~
							RET $opcodes(~%opcode%~) = count
							RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
						END
					END

					PATCH_IF group == 1 BEGIN
						// Suppression de l'opcode 172 devenu inutile
						SET opcode = currentOpcode
						LPF ~delete_opcode~
							INT_VAR opcode match_position = currentPosition
							RET $opcodes(~%opcode%~) = count
							RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
						END
					END
				END
			END
		END
	END
END

/* -------------------------------------- *
 * Stat: Poison Resistance Modifier [173] *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_173~ BEGIN
	SET resistName = 11730001 // ~Résistance aux poisons~
	LPM ~opcode_173_common~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_173~ BEGIN
	SET resistName = 11730001 // ~Résistance aux poisons~
	LPM ~opcode_173_common~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_173~ BEGIN
	SET resistName = 11730001 // ~Résistance aux poisons~
	LPM ~opcode_173_common~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_173~ BEGIN
	LPM ~opcode_self_probability_173~
END

DEFINE_PATCH_MACRO ~opcode_173_common~ BEGIN
	// Sets the Poison Resistance of the target creature(s) to the value specified by 'Statistic Modifier'.
	SET parameter2 = is_ee ? MOD_TYPE_cumulative : MOD_TYPE_flat
END

DEFINE_PATCH_MACRO ~opcode_173_spell_level_match~ BEGIN
	LPM ~opcode_173_common~
END

DEFINE_PATCH_MACRO ~opcode_173_is_valid~ BEGIN
	LOCAL_SET parameter1 = parameter1 BAND 255
	PATCH_IF is_ee AND parameter1 == 0 BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : No change detected Value = Value + %parameter1%.~ END
	END
END

/* ----------------- *
 * State: Hold [175] *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_175~ BEGIN
	LPM ~opcode_self_109~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_175~ BEGIN
	LPM ~opcode_self_probability_109~
END

DEFINE_PATCH_MACRO ~opcode_target_175~ BEGIN
	LPM ~opcode_target_109~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_175~ BEGIN
	LPM ~opcode_target_probability_109~
END

DEFINE_PATCH_MACRO ~opcode_175_is_valid~ BEGIN
	LPM ~opcode_idscheck9_is_valid~
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

DEFINE_PATCH_MACRO ~opcode_176_is_valid~ BEGIN
	LPM ~opcode_126_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_176_group~ BEGIN
	LPM ~opcode_126_group~
END

/* ------------------ *
 * Use EFF File [177] *
 * ------------------ */
DEFINE_PATCH_MACRO ~opcode_self_177~ BEGIN
	PATCH_IF parameter1 == 0 BEGIN
		LPF ~get_res_description_177~ STR_VAR resref macro = ~opcode_self_~ RET description saveAdded ignoreDuration opcode END
	END
	ELSE BEGIN
		LPM ~opcode_set_target_strings~
		LPF ~get_res_description_177~ STR_VAR resref macro = ~opcode_self_~ RET description saveAdded ignoreDuration opcode END
		PATCH_IF NOT ~%targetType%~ STRING_EQUAL ~~ AND NOT ~%description%~ STRING_EQUAL ~~ BEGIN
			// On ajoute le (uniquement pour les xxx) derrière chaque sous-effets
            INNER_PATCH_SAVE description ~%description%~ BEGIN
                REPLACE_TEXTUALLY EVALUATE_REGEXP ~\(.+\)%crlf%~ ~\1 (%onlyForTarget%)%crlf%~
            END
			SPRINT description ~%description% (%onlyForTarget%)~
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
	PATCH_IF parameter1 != 0 BEGIN
		LPM ~opcode_set_target_strings~
		LPM ~add_target_level~
	END
	LPF ~get_res_description_177~ STR_VAR resref macro = ~opcode_target_~ RET description saveAdded ignoreDuration opcode END
END

DEFINE_PATCH_FUNCTION ~get_res_description_177~ INT_VAR resetTarget = 0 STR_VAR resref = ~~ macro = ~~ RET description saveAdded ignoreDuration opcode BEGIN
	INNER_PATCH_FILE ~%resref%.eff~ BEGIN
		SPRINT oldTheTarget   ~%theTarget%~
		SPRINT oldOfTheTarget ~%ofTheTarget%~
		SPRINT oldToTheTarget ~%toTheTarget%~

		SPRINT target_exceptions177 ~%target_exceptions%~
		SET timingMode177 = timingMode
		SET duration177 = duration
		SET target177 = target
		SET probability177 = probability
		SET saveType177 = saveType
		SET saveBonus177 = saveBonus
		SET diceSides177 = diceSides // levelMin
		SET diceCount177 = diceCount // levelMax
		SET custom_int177 = custom_int
		SET isExternal = 1

		LPM ~read_external_effect_vars~
		SPRINT target_exceptions ~~ // Nécessaire pour éviter d'avoir l'exception en doublon dans la description

		PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
			SET isValid = 1
			LPM ~opcode_177_replace_effect_vars~
			LPM ~opcode_is_valid~

			PATCH_IF isValid == 1 BEGIN
				LPF ~get_effect_description~ INT_VAR forceTarget = 1 ignoreDuration RET description saveAdded ignoreDuration END

				INNER_PATCH_SAVE description ~%description%~ BEGIN
					SPRINT regex @10009 // ~^[0-9]+ % de chance ~
					REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
				END
			END
		END

		SPRINT target_exceptions ~%target_exceptions177%~
		SPRINT theTarget   ~%oldTheTarget%~
		SPRINT ofTheTarget ~%oldOfTheTarget%~
		SPRINT toTheTarget ~%oldToTheTarget%~
	END
END

DEFINE_PATCH_FUNCTION ~get_res_description~ INT_VAR ignoreDuration = 0 STR_VAR resref = ~~ macro = ~~ RET description saveAdded ignoreDuration opcode BEGIN
	INNER_PATCH_FILE ~%resref%.eff~ BEGIN
		SET isExternal = 1
		LPM ~read_external_effect_vars~

		PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
			SET isValid = 1
			LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END
			LPM ~opcode_is_valid~

			PATCH_IF isValid == 1 BEGIN
				LPF ~get_effect_description~ INT_VAR ignoreDuration RET description saveAdded ignoreDuration END
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_177_is_valid~ BEGIN
	LPM ~opcode_idscheck9_is_valid~
	LPM ~opcode_resref_is_valid~
	PATCH_IF NOT FILE_EXISTS_IN_GAME ~%resref%.eff~ AND NOT ~%resref%~ STRING_EQUAL ~~ BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Resource %resref%.eff doesn't exist.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_177_replace~ BEGIN
	PATCH_PHP_EACH ~opcodes_177~ AS data => _ BEGIN
		LPM ~data_to_vars~
		INNER_PATCH_FILE ~%resref%.eff~ BEGIN
			SET timingMode177 = timingMode
			SET duration177 = duration
			SET target177 = target
			SET probability177 = probability
			SET probability1177 = probability1
			SET probability2177 = probability2
			SET saveType177 = saveType
			SET saveBonus177 = saveBonus
			SET diceSides177 = diceSides // levelMin
			SET diceCount177 = diceCount // levelMax
			SET custom_int177 = custom_int
			SET position177 = position
			SET parameter1177 = parameter1
			SET parameter2177 = parameter2
			SET isExternal = 1

			LPM ~read_external_effect_vars~

			LPF ~delete_opcode~
                INT_VAR opcode = 177 match_position = position177
                RET $opcodes(~177~) = count
                RET_ARRAY EVAL ~opcodes_177~ = opcodes_xx
            END

			PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
				LPM ~opcode_177_replace_effect_vars~

				PATCH_IF parameter1177 != 0 BEGIN
					LPF ~str_pad_left~ INT_VAR min_length = 3 STR_VAR string = ~%parameter1177%~ RET string END
					SPRINT target_type "%parameter2177%:%string%"
				END
                LPM ~add_opcode~
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_177_replace_effect_vars~ BEGIN
	LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END

	// Les paramètres timingMode, duration et target écrasent les paramètres de l'opcode pointé
	// FIXME: le parameter6 également mais non configuré dans AutoComplétion (et probablement jamais utilisé)
	// Pour les cas particuliers il sera nécessaire de trouver un moyen alternatif d'afficher la restriction
	SET timingMode = timingMode177
	SET duration = duration177
	SET target = target177

	// La restriction de niveau dépend de celle de l'opcode 177, excepté pour les opcodes qui n'en ont pas
	PATCH_IF NOT VARIABLE_IS_SET $opcode_without_level_restriction(~%opcode%~) AND (opcode != 218 OR is_ee == 0 OR parameter2 == 0) AND (opcode != 127 OR is_ee == 0) BEGIN
		SET diceSides = diceSides177
		SET diceCount = diceCount177
	END

	// Si le JS du 177 est renseigné contrairement à celui de l'opcode appelé => transmission
	// FIXME: en réalité les JS se cumulent, ne sont présents que les cas les plus simples
	// FIXME: peut créer des conflits mineurs avec l'opcode 12 + special 256 ou 512
	PATCH_IF saveType == 0 AND saveType177 != 0 BEGIN
		SET saveType = saveType177
		SET saveBonus = saveBonus177
	END
	// Si deux JS différents avec un saveBonus identiques sont présents, ils se cumulent
	// FIXME: insuffisant, deux JS identiques doivent pouvoir aussi se cumuler
	ELSE PATCH_IF saveBonus == saveBonus177 BEGIN
		SET saveType = saveType | saveType177
	END

	// Cas où 177 < 100% et opcode == 100
    PATCH_IF probability == 100 AND probability177 < 100 BEGIN
		SET probability2 = probability2177
		SET probability1 = probability1177
		SET probability  = probability177
    END
    ELSE PATCH_IF probability < 100 AND probability177 < 100 BEGIN
        // Attention à la gestion du regroupement par probabilité
        // TODO: Trouver comment calculer probability1 et probability2
		// Multiplication des probabilités de l'opcode 177 et de l'opcode pointé
        SET probability  = probability177 * probability / 100
    END

	// Gestion pour les invocations de la même créature en plusieurs exemplaires.
	PATCH_IF opcode == 67 OR opcode = 127 BEGIN
		SET custom_int = custom_int177
	END
END

DEFINE_PATCH_MACRO ~opcode_177_group~ BEGIN
	LPM ~opcode_group_by_target~
END

DEFINE_PATCH_MACRO ~opcode_group_by_target~ BEGIN
	// Un problème fait qu'avec le add_opcode() l'opcode en cours de traitement est remis, bien qu'il ai été supprimé avant...
	// On doit donc supprimer ces entrées une seconde fois à la fin du traitement
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~to_delete~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~opcode_positions~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions_already_grouped~ BEGIN END

	CLEAR_ARRAY to_delete
	CLEAR_ARRAY opcode_positions
	CLEAR_ARRAY positions_already_grouped

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET currentPosition = position

		PATCH_IF NOT VARIABLE_IS_SET $positions_already_grouped(~%position%~) BEGIN
			PATCH_IF opcode == 178 OR opcode == 179 OR opcode == 344 OR opcode == 177 OR opcode == 55 BEGIN
			    LPF opcode_177_get_all_opcode_positions
					INT_VAR
						match_opcode       = opcode
						match_isExternal   = isExternal
						match_target       = target
						match_power        = power
						match_parameter1   = parameter1
						match_parameter2   = parameter2
						match_timingMode   = timingMode
						match_resistance   = resistance
						match_duration     = duration
						match_probability  = probability
						match_probability1 = probability1
						match_probability2 = probability2
						match_diceCount    = diceCount
						match_diceSides    = diceSides
						match_saveType     = saveType
						match_saveBonus    = saveBonus
						match_special      = special
						match_parameter3   = parameter3
						match_parameter4   = parameter4
						match_custom_int   = custom_int
					STR_VAR
						match_resref     = ~%resref%~
						match_resref2    = ~%resref2%~
						match_resref3    = ~%resref3%~
						match_custom_str = ~%custom_str%~
			        RET
			            count
			        RET_ARRAY
			            opcode_positions = positions
			    END
			END
			ELSE BEGIN
			    LPF opcode_not_177_get_all_opcode_positions
					INT_VAR
						match_opcode       = opcode
						match_isExternal   = isExternal
						match_target       = target
						match_power        = power
						match_parameter1   = parameter1
						match_parameter2   = parameter2
						match_timingMode   = timingMode
						match_resistance   = resistance
						match_duration     = duration
						match_probability  = probability
						match_probability1 = probability1
						match_probability2 = probability2
						match_diceCount    = diceCount
						match_diceSides    = diceSides
						match_saveType     = saveType
						match_saveBonus    = saveBonus
						match_special      = special
						match_parameter3   = parameter3
						match_parameter4   = parameter4
						match_custom_int   = custom_int
					STR_VAR
						match_resref     = ~%resref%~
						match_resref2    = ~%resref2%~
						match_resref3    = ~%resref3%~
						match_custom_str = ~%custom_str%~
			        RET
			            count
			        RET_ARRAY
			            opcode_positions = positions
			    END
			END
		    PATCH_IF count > 1 BEGIN
		        LPF ~opcode_get_target_type~ RET target_type END

				SET $to_delete(~%currentPosition%~) = 1
				SET position += 1000
				SET custom_int = count
				PATCH_IF ~%target_type%~ STRING_EQUAL ~0:000~ BEGIN
					SPRINT target_type ~~
				END
				LPM ~add_opcode~

				PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
					LPM ~data_to_vars~
					PATCH_IF VARIABLE_IS_SET $opcode_positions(~%position%~) AND $opcode_positions(~%position%~) == 1 BEGIN
						SET $positions_already_grouped(~%position%~) = 1
						SET $opcode_positions(~%position%~) = 0
						LPF ~delete_opcode~
							INT_VAR opcode match_position = position
							RET $opcodes(~%opcode%~) = count
							RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
						END
					END
			    END
			END
			SET $opcode_positions(~%currentPosition%~) = 0
		END
	END

	PATCH_PHP_EACH EVAL ~to_delete~ AS position => _ BEGIN
		LPF ~delete_opcode~
			INT_VAR opcode match_position = position
			RET $opcodes(~%opcode%~) = count
			RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_group_by_duration~ BEGIN
	LOCAL_SET matched = 0
	LOCAL_SET has_instant_effect = 0
	LOCAL_SET delta_duration = 0
	LOCAL_SET prev_duration = 0
	LOCAL_SET is_valid_duration = 1

	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions_already_grouped~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~opcode_group_durations~ BEGIN END

	CLEAR_ARRAY opcode_group_durations
	CLEAR_ARRAY positions_already_grouped
	CLEAR_ARRAY to_delete

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~

		CLEAR_ARRAY opcode_group_durations

		PATCH_IF NOT VARIABLE_IS_SET $positions_already_grouped(~%position%~) BEGIN
			SET matched = 0
			SET has_instant_effect = 0

			PATCH_IF timingMode != TIMING_delayed OR (timingMode == TIMING_delayed AND duration == 0) BEGIN
				SET has_instant_effect = 1
			END
			PATCH_IF timingMode == TIMING_delayed BEGIN
				SET $opcode_group_durations(~%position%~) = duration
			END

			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_match_vars~
				SET match = (
						match_position     != position
					AND match_isExternal   == isExternal
			        AND match_target       == target
			        AND match_power        == power
			        AND match_parameter1   == parameter1
			        AND match_parameter2   == parameter2
			        AND match_timingMode   == TIMING_delayed
			        AND match_resistance   == resistance
			        AND match_probability  == probability
			        AND match_probability1 == probability1
			        AND match_probability2 == probability2
			        AND match_diceCount    == diceCount
			        AND match_diceSides    == diceSides
			        AND match_saveType     == saveType
			        AND match_saveBonus    == saveBonus
			        AND match_special      == special
			        AND match_parameter3   == parameter3
			        AND match_parameter4   == parameter4
			        AND match_custom_int   == custom_int
			        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
			        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
			        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
			        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
			    )
			    PATCH_IF match BEGIN
			        SET matched = 1
					SET $opcode_group_durations(~%match_position%~) = match_duration
			    END
			END

			PATCH_IF matched BEGIN
				SET delta_duration = 0
				SET prev_duration = 0
				SET is_valid_duration = 1
				PATCH_PHP_EACH ~opcode_group_durations~ AS matched_position => matched_duration BEGIN
					SET $positions_already_grouped(~%matched_position%~) = 1
					PATCH_IF delta_duration = 0 BEGIN
						SET delta_duration = matched_duration
					END
					ELSE PATCH_IF delta_duration != matched_duration - prev_duration BEGIN
						SET is_valid_duration = 0
					END
					SET prev_duration = matched_duration
				END

				PATCH_IF is_valid_duration BEGIN
					PATCH_PHP_EACH ~opcode_group_durations~ AS matched_position => matched_duration BEGIN
						LPF ~delete_opcode~
							INT_VAR opcode match_position = matched_position
							RET $opcodes(~%opcode%~) = count
							RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
						END
					END
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

					PATCH_IF has_instant_effect BEGIN
						SET timingMode = 5001
					END
					ELSE BEGIN
						SET timingMode = 5000
					END
					SET duration = (delta_duration * 10000) + prev_duration
                    LPM ~add_opcode~
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_set_target_strings~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~targetTypes~ BEGIN END
	CLEAR_ARRAY ~targetTypes~

	PATCH_IF ~%target_type%~ STRING_EQUAL ~~ AND (opcode == 178 OR opcode == 179 OR opcode == 344 OR opcode == 177) BEGIN
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET targetType = idName END
		PATCH_IF NOT ~%targetType%~ STRING_EQUAL ~~ BEGIN
			SET $targetTypes(~%targetType%~) = 1
		END
	END
	ELSE PATCH_IF NOT ~%target_type%~ STRING_EQUAL ~~ BEGIN
		SPRINT targetType ~%target_type%~

		PATCH_DEFINE_ASSOCIATIVE_ARRAY ~targetTypeGroups~ BEGIN
			~5:001 5:007 5:010 5:013 5:014 5:017~ => 11770100
			~5:004 5:009 5:010 5:013 5:015~       => 11770101
		END

		PATCH_PHP_EACH ~targetTypeGroups~ AS elements => strref BEGIN
			LPF all_elements_in_list STR_VAR elements list = ~%targetType%~ RET value END
			PATCH_IF value == 1 BEGIN
				LPF remove_elements_in_list STR_VAR elements list = ~%targetType%~ RET targetType = list END
				SPRINT string (AT strref)
				SET $targetTypes(~%string%~) = 1
			END
		END

		WHILE ~%targetType%~ STRING_COMPARE ~~ BEGIN
			LPF return_first_entry STR_VAR list = ~%targetType%~ RET entry targetType = list END
			LPF return_first_entry STR_VAR list = ~%entry%~ separator = ~:~ RET file = entry entry = list END
            PATCH_IF ~%entry%~ STRING_EQUAL ~~ BEGIN
                SPRINT idName (AT file)
            END
            ELSE BEGIN
				LPF ~get_ids_name~ INT_VAR entry file RET idName END
            END
			PATCH_IF NOT ~%idName%~ STRING_EQUAL ~~ BEGIN
				SET $targetTypes(~%idName%~) = 1
			END
		END
	END

	LPF ~array_count~ STR_VAR array_name = ~targetTypes~ RET count END

	PATCH_IF count > 0 BEGIN
		SPRINT the @11770200 // ~les~
		SPRINT andThe @11770201 // ~et les~
		SPRINT of @11770202 // ~des~
		SPRINT andOf @11770203 // ~et des~
		SPRINT to @11770204 // ~aux~
		SPRINT andTo @11770205 // ~et aux~

		LPF ~implode~ STR_VAR array_name = ~targetTypes~ glue = ~, %the% ~ final_glue = ~ %andThe% ~ RET targetType = text END
		SPRINT versus        @102387 // ~contre les %targetType%~
		PATCH_IF NOT (opcode == 178 OR opcode == 179 OR opcode == 344 OR opcode == 177) BEGIN
			SPRINT onlyForTarget @11770001 // ~uniquement pour les %targetType%~
		END
		SPRINT theTarget     @102384 // ~les %targetType%~
		LPF ~implode~ STR_VAR array_name = ~targetTypes~ glue = ~, %of% ~ final_glue = ~ %andOf% ~ RET targetType = text END
		SPRINT ofTheTarget @102385 // ~des %targetType%~
		LPF ~implode~ STR_VAR array_name = ~targetTypes~ glue = ~, %to% ~ final_glue = ~ %andTo% ~ RET targetType = text END
		SPRINT toTheTarget @102386 // ~aux %targetType%~
	END
END

DEFINE_PATCH_FUNCTION ~opcode_get_target_type~ RET target_type
BEGIN
	SPRINT targetType ~~
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF VARIABLE_IS_SET $opcode_positions(~%position%~) AND $opcode_positions(~%position%~) == 1 BEGIN
			PATCH_IF opcode == 178 OR opcode == 179 OR opcode == 344 OR opcode == 177 OR opcode == 55 BEGIN
				LPF ~str_pad_left~ INT_VAR min_length = 3 STR_VAR string = ~%parameter1%~ RET string END
				SPRINT targetType "%targetType% %parameter2%:%string%"
			END
			ELSE PATCH_IF NOT ~%target_type%~ STRING_EQUAL ~~ BEGIN
				SPRINT targetType "%targetType% %target_type%"
			END
		END
    END

	INNER_PATCH_SAVE targetType ~%targetType%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~ \(.+\)$~ ~\1~
	END

	SPRINT target_type ~%targetType%~
END

DEFINE_PATCH_FUNCTION ~opcode_177_get_all_opcode_positions~
	INT_VAR
		match_opcode       = 0
		match_isExternal   = 0
		match_target       = 0
		match_power        = 0
		match_parameter1   = 0
		match_parameter2   = 0
		match_timingMode   = 0
		match_resistance   = 0
		match_duration     = 0
		match_probability  = 0
		match_probability1 = 0
		match_probability2 = 0
		match_diceCount    = 0
		match_diceSides    = 0
		match_saveType     = 0
		match_saveBonus    = 0
		match_special      = 0
		match_parameter3   = 0
		match_parameter4   = 0
		match_custom_int   = 0
	STR_VAR
		match_resref     = ~~
		match_resref2    = ~~
		match_resref3    = ~~
		match_custom_str = ~~
	RET
		count
	RET_ARRAY
		positions
BEGIN
	SET count = 0
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	CLEAR_ARRAY ~positions~
	PATCH_PHP_EACH EVAL ~opcodes_%match_opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		LPM ~opcode_match_except_parameter1_and_parameter2~
		PATCH_IF match BEGIN
			SET $positions(~%position%~) = 1
			SET count += 1
		END
	END
END

DEFINE_PATCH_FUNCTION ~opcode_not_177_get_all_opcode_positions~
	INT_VAR
		match_opcode       = 0
		match_isExternal   = 0
		match_target       = 0
		match_power        = 0
		match_parameter1   = 0
		match_parameter2   = 0
		match_timingMode   = 0
		match_resistance   = 0
		match_duration     = 0
		match_probability  = 0
		match_probability1 = 0
		match_probability2 = 0
		match_diceCount    = 0
		match_diceSides    = 0
		match_saveType     = 0
		match_saveBonus    = 0
		match_special      = 0
		match_parameter3   = 0
		match_parameter4   = 0
		match_custom_int   = 0
	STR_VAR
		match_resref     = ~~
		match_resref2    = ~~
		match_resref3    = ~~
		match_custom_str = ~~
	RET
		count
	RET_ARRAY
		positions
BEGIN
	SET count = 0
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	CLEAR_ARRAY ~positions~
	PATCH_PHP_EACH EVAL ~opcodes_%match_opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		LPM ~opcode_match~
		PATCH_IF match BEGIN
			SET $positions(~%position%~) = 1
			SET count += 1
		END
	END
END

/* ---------------------------------------------------- *
 * Spell Effect: THAC0 vs. Creature Type Modifier [178] *
 * ---------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_178~ BEGIN
	LPM ~opcode_178_common~
	LPF ~opcode_mod~ INT_VAR strref = 10540001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~TAC0~
	LPM ~opcode_178_end~
END

DEFINE_PATCH_MACRO ~opcode_target_178~ BEGIN
	LPM ~opcode_178_common~
	LPF ~opcode_target~ INT_VAR strref = 10540002 RET description END // ~le TAC0~
	LPM ~opcode_178_end~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_178~ BEGIN
	LPM ~opcode_178_common~
	LPF ~opcode_probability~ INT_VAR strref = 10540002 RET description END // ~le TAC0~
	LPM ~opcode_178_end~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_178~ BEGIN
	LPM ~opcode_self_probability_178~
END

DEFINE_PATCH_MACRO ~opcode_178_common~ BEGIN
	SET value = isExternal? parameter3 : 0
	PATCH_IF is_ee AND value == 0 BEGIN
		SET value = special
	END

	SET parameter2 = MOD_TYPE_cumulative
	SET parameter1 = value
END

DEFINE_PATCH_MACRO ~opcode_178_end~ BEGIN
	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ AND NOT ~%versus%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11780001 // ~%description% %versus%~
	END
END

DEFINE_PATCH_MACRO ~opcode_178_spell_level_match~ BEGIN
	LPM ~opcode_178_common~
END

DEFINE_PATCH_MACRO ~opcode_178_is_valid~ BEGIN
	LOCAL_SET value = isExternal? parameter3 : 0
	PATCH_IF value == 0 AND (is_ee == 0 OR special == 0) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : No change detected : Value = Value + 0.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_178_group~ BEGIN
	LPM ~opcode_group_by_target~
END

/* ----------------------------------------------------- *
 * Spell Effect: Damage vs. Creature Type Modifier [179] *
 * ----------------------------------------------------- */
 DEFINE_PATCH_MACRO ~opcode_self_179~ BEGIN
	LPM ~opcode_179_common~
	LPF ~opcode_mod~ INT_VAR strref = 10730001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Dégâts~
	LPM ~opcode_178_end~
END

DEFINE_PATCH_MACRO ~opcode_target_179~ BEGIN
	LPM ~opcode_179_common~
	LPF ~opcode_target~ INT_VAR strref = 10730002 RET description END // ~les dégâts~
	LPM ~opcode_178_end~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_179~ BEGIN
	LPM ~opcode_179_common~
	LPF ~opcode_probability~ INT_VAR strref = 10730002 RET description END // ~les dégâts~
	LPM ~opcode_178_end~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_179~ BEGIN
	LPM ~opcode_self_probability_179~
END

DEFINE_PATCH_MACRO ~opcode_179_common~ BEGIN
	LPM ~opcode_178_common~
END

DEFINE_PATCH_MACRO ~opcode_179_is_valid~ BEGIN
	LPM ~opcode_178_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_179_group~ BEGIN
	LPM ~opcode_group_by_target~
END

/* -------------------------- *
 * Item: Can't Use Item [180] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_180~ BEGIN
	PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ BEGIN
		SET forceSort = 1
		SET sort = 0
		SPRINT description @11800001 // ~Unique : Un seul exemple peut être équipé~
	END
	ELSE BEGIN
		PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
			SPRINT itemName ~%custom_str%~
		END
		ELSE BEGIN
			LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END
		END
		PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
			SPRINT description @11800002 // ~Empêche d'utiliser %itemName%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_180_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
	PATCH_IF parameter2 != 0 BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Parameter2 %parameter2% seems to have no effect.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_180_group~ BEGIN
	PATCH_DEFINE_ARRAY ~itemNamesList~ BEGIN END
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF NOT ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ BEGIN
			LPF ~get_item_name~ STR_VAR file = EVAL ~%resref%~ RET itemName END
			PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
				SET $itemNamesList(~%itemName%~) = 1
			END
			LPF ~delete_opcode~
				INT_VAR opcode = 180 match_position = position
				RET $opcodes(~180~) = count
				RET_ARRAY EVAL ~opcodes_180~ = opcodes_xx
			END
		END
	END
	// Bug où il reste toujours un item dans le tableau si c'était le dernier
	// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
	PATCH_IF $opcodes(~180~) == 0 BEGIN
		CLEAR_ARRAY ~opcodes_180~
	END
	SPRINT and @100021 // ~et~
	LPF ~implode~ STR_VAR array_name = ~itemNamesList~ glue = ~, ~ final_glue = ~ %and% ~ RET itemNames = text END
	SET opcode = 180
	SPRINT custom_str ~%itemNames%~
	SPRINT resref ~~
	LPM ~add_opcode~
END

/* ------------------------------ *
 * Item: Can't Use Itemtype [181] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_181~ BEGIN
	LOCAL_SET strref = 230000
	SET strref += is_ee ? parameter1 : parameter2

	LPF ~getTranslation~ INT_VAR strref opcode RET itemType = string END
	SPRINT description @11810001 // ~Empêche d'utiliser les %itemType%~
END

DEFINE_PATCH_MACRO ~opcode_181_is_valid~ BEGIN
	LOCAL_SET parameter = is_ee ? parameter1 : parameter2
	PATCH_IF parameter < 0 OR parameter > 73 BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Type %parameter%.~ END
	END
END

/* ---------------------------------- *
 *  Item: Apply Effect Itemtype [183] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_183~ BEGIN
	LPM ~opcode_target_183~
END

DEFINE_PATCH_MACRO ~opcode_target_183~ BEGIN
	LOCAL_SET strref = 230000 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET itemType = string END
	SPRINT strref @11830002 // ~si l'équipement %ofTheTarget% contient des %itemType%~
	LPF ~get_res_description_177~ STR_VAR resref macro = ~opcode_self_~ RET description saveAdded ignoreDuration opcode END
	SPRINT description ~%description% %strref%~
END

DEFINE_PATCH_MACRO ~opcode_183_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
	PATCH_IF NOT is_ee BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : No effect.~ END
	END
END

/* ---------------------- *
 * State: Hold (II) [185] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_185~ BEGIN
	LPM ~opcode_self_175~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_185~ BEGIN
	LPM ~opcode_self_probability_175~
END

DEFINE_PATCH_MACRO ~opcode_target_185~ BEGIN
	LPM ~opcode_target_175~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_185~ BEGIN
	LPM ~opcode_target_probability_175~
END

DEFINE_PATCH_MACRO ~opcode_185_is_valid~ BEGIN
	LPM ~opcode_175_is_valid~
END

/* ---------------------------------- *
 * Spell Effect: Aura Cleansing [188] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_188~ BEGIN
	SET strref = 11880001 // ~Permet de lancer plusieurs sorts par round~
	SET strref += parameter2 == 0? 10 : 0 // ~Permet de ne lancer qu'un seul sort par round~
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_self_probability_188~ BEGIN
	SET strref = 11880003 // ~de permettre %toTheTarget% de lancer plusieurs sorts par round~
	SET strref += parameter2 == 0? 10 : 0 // ~de permettre %toTheTarget% de ne lancer qu'un seul sort par round~
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_target_188~ BEGIN
	SET strref = 11880002 // ~Permet %toTheTarget% de lancer plusieurs sorts par round~
	SET strref += parameter2 == 0? 10 : 0 // ~Permet %toTheTarget% de lancer qu'un seul sort par round~
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_target_probability_188~ BEGIN
	LPM ~opcode_self_probability_188~ // ~de permettre %toTheTarget% de lancer plusieurs sorts par round~
END

/* --------------------------------- *
 * Stat: Casting Time Modifier [189] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_189~ BEGIN
	PATCH_IF parameter2 <= MOD_TYPE_flat BEGIN
		LPF ~opcode_mod~ INT_VAR strref = 11890001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Temps d'incantation~
	END
	ELSE BEGIN
		SET parameter2 = MOD_TYPE_flat
		LPF ~opcode_mod~ INT_VAR strref = 11890003 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Temps d'incantation maximal~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_189~ BEGIN
	PATCH_IF parameter2 <= MOD_TYPE_flat BEGIN
		LPF ~opcode_probability~ INT_VAR strref = 11890002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le temps d'incantation~
	END
	ELSE BEGIN
		SET parameter2 = MOD_TYPE_flat
		LPF ~opcode_probability~ INT_VAR strref = 11890004 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le temps d'incantation maximal~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_189~ BEGIN
	PATCH_IF parameter2 <= MOD_TYPE_flat BEGIN
		LPF ~opcode_target~ INT_VAR strref = 11890002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le temps d'incantation~
	END
	ELSE BEGIN
		SET parameter2 = MOD_TYPE_flat
		LPF ~opcode_target~ INT_VAR strref = 11890004 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~le temps d'incantation maximal~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_189~ BEGIN
	LPM ~opcode_self_probability_189~
END

DEFINE_PATCH_MACRO ~opcode_189_is_valid~ BEGIN
	PATCH_IF (parameter1 BAND 255) == 0 AND parameter2 == 0 BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : No change detected: Value = Value + 0.~ END
	END
	ELSE BEGIN
		PATCH_IF parameter2 > 2 OR parameter2 < MOD_TYPE_cumulative OR parameter2 == 2 AND NOT is_ee BEGIN
			SET parameter2 = MOD_TYPE_cumulative
		END
		PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
			SET parameter1 = 0 - parameter1
		END
		ELSE PATCH_IF parameter1 < 0 BEGIN
			SET parameter1 = 0
		END
	END
END

/* ------------------------------- *
 * Stat: Attack Speed Factor [190] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_190~ BEGIN
	LOCAL_SET value = parameter1
	SET cumulable = 0
	PATCH_IF value >= 0 BEGIN
		SPRINT value @10000101 // ~Bonus de %value%~
	END
	ELSE BEGIN
		SET value = ABS value
		SPRINT value @10000102 // ~Malus de %value%~
	END
	LPF ~opcode_mod~ INT_VAR strref = 11900001 STR_VAR value RET description END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_190~ BEGIN
	LOCAL_SET value = parameter1 * ~-1~
	SET cumulable = 0
	SET parameter2 = MOD_TYPE_cumulative
	LPF ~opcode_probability~ INT_VAR strref = 11900002 RET description END // ~le facteur de vitesse~
END

DEFINE_PATCH_MACRO ~opcode_target_190~ BEGIN
	LOCAL_SET value = parameter1 * ~-1~
	SET cumulable = 0
	SET parameter2 = MOD_TYPE_cumulative
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
	LPF ~opcode_mod~ INT_VAR strref STR_VAR value = ~%parameter1%~ complex_value RET description END
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
	SET spellTypes = 1 << parameter2
	LPF ~get_spell_type_str~ INT_VAR value = spellTypes cleric_druid_limitation = 1 RET spellType END
	SET parameter2 = MOD_TYPE_cumulative
	SET parameter1 = parameter1 BAND 255
END

DEFINE_PATCH_MACRO ~opcode_191_is_valid~ BEGIN
	PATCH_IF parameter2 < 0 OR parameter2 > 1 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Type %parameter2%.~ END
	END
END

/* --------------------------------- *
 * Spell Effect: Find Familiar [192] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_192~ BEGIN
	SPRINT description @11920001 // ~Invocation du familier~
END

/* ------------------------------------------------- *
 * Spell Effect: Invisible Detection by Script [193] *
 * ------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_193~ BEGIN
	SET strref = 11930001 // ~Permet %toTheTarget% d'attaquer une créature cachée ou invisible~
	LPM ~opcode_193_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_193~ BEGIN
	SET strref = 11930002 // ~de permettre %toTheTarget% d'attaquer une créature cachée ou invisible~
	LPM ~opcode_193_common~
END

DEFINE_PATCH_MACRO ~opcode_target_193~ BEGIN
	LPM ~opcode_self_193~ // ~Permet %toTheTarget% d'attaquer une créature cachée ou invisible~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_193~ BEGIN
	LPM ~opcode_self_probability_193~ // ~de permettre %toTheTarget% d'attaquer une créature cachée ou invisible~
END

DEFINE_PATCH_MACRO ~opcode_193_common~ BEGIN
	SET strref += parameter2 == 0? 10 : 0
	SPRINT description (AT strref)
END

/* ---------------------------------- *
 * Spell Effect: Familiar Block [196] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_196~ BEGIN
	SPRINT description @11960001 // ~Empêche l'invocation du familier~
END

/* ------------------------------ *
 * Spell: Bounce Projectile [197] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_197~ BEGIN
	LOCAL_SET strref = 11970001 // ~Renvoie %the% %projectiles%~
	LPM ~opcode_197_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_197~ BEGIN
	LOCAL_SET strref = 11970003 // ~de renvoyer %the% %projectiles%~
	LPM ~opcode_197_common~
END

DEFINE_PATCH_MACRO ~opcode_target_197~ BEGIN
	LOCAL_SET strref = 11970002 // ~Renvoie %the% %projectiles% visant %theTarget%~
	LPM ~opcode_197_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_197~ BEGIN
	LOCAL_SET strref = 11970004 // ~de renvoyer %the% %projectiles% visant %theTarget%~
	LPM ~opcode_197_common~
END

DEFINE_PATCH_MACRO ~opcode_197_common~ BEGIN
	SPRINT the @100020 // ~les~
	PATCH_IF ~%custom_str%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_projectile_name~ INT_VAR projectile = parameter2 RET projref END

		PATCH_IF projref > 0 BEGIN
			LPF ~getTranslation~ INT_VAR strref = projref opcode RET projectiles = string END
			LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
		END
	END
	ELSE BEGIN
		SPRINT projectiles ~%custom_str%~
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
END

DEFINE_PATCH_MACRO ~opcode_197_group~ BEGIN
	LOCAL_SET deleted = 0
	// Regroupement avec l'opcode 207 pour les sorts qui utilisent le même projectile
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_PHP_EACH EVAL ~opcodes_207~ AS data => _ BEGIN
			LPM ~data_to_match_vars~
			PATCH_IF FILE_EXISTS_IN_GAME ~%match_resref%.spl~ BEGIN
				INNER_PATCH_FILE ~%match_resref%.spl~ BEGIN
					READ_LONG  SPL_extended_headers_offset headerOffset
					READ_SHORT SPL_extended_headers_count  headerCount
					SET deleted = 0
				    FOR (headerIndex = 0; headerIndex < headerCount; headerIndex += 1) BEGIN
			            SET offset = headerOffset + 0x28 * headerIndex
			            READ_SHORT (offset + SPL_HEAD_projectile) projectile
			            SET projectile -= 1 // in BG2, this value is off-by-one from projectl.ids value
						PATCH_IF projectile == parameter2 AND deleted == 0 BEGIN
							LPF ~delete_opcode~
								INT_VAR opcode = 207 match_position
								RET $opcodes(~207~) = count
								RET_ARRAY EVAL ~opcodes_207~ = opcodes_xx
							END
							// Bug où il reste toujours un item dans le tableau si c'était le dernier
							// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
							PATCH_IF $opcodes(~207~) == 0 BEGIN
					            CLEAR_ARRAY ~opcodes_207~
					        END
					        SET deleted = 1
						END
					END
				END
			END
		END
	END

	PATCH_IF $opcodes(~%opcode%~) >= 2 BEGIN
		SPRINT the @100020 // ~les~
		SPRINT myCustomStr ~~
		DEFINE_ASSOCIATIVE_ARRAY projectiles_name BEGIN END
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			LPF ~get_projectile_name~ INT_VAR projectile = parameter2 RET projref END
			PATCH_IF projref > 0 BEGIN
				LPF ~getTranslation~ INT_VAR strref = projref opcode RET projectiles = string END
				SET $projectiles_name(~%projectiles%~) = 1
			END
		END
		CLEAR_ARRAY ~opcodes_%opcode%~
		SET $opcodes(~%opcode%~) = 0
		SPRINT text ~~
		PATCH_PHP_EACH projectiles_name AS projectile_name => _ BEGIN
			PATCH_IF ~%text%~ STRING_EQUAL ~~ BEGIN
				SPRINT text ~%projectile_name%~
			END
			ELSE BEGIN
				SPRINT text ~%text%, %the% %projectile_name%~
			END
		END
		SPRINT str @100021 // ~et~
		LPF ~replace_last_comma_with~ STR_VAR text str RET custom_str = text END
		LPM ~add_opcode~
	END
END

/* ------------------------------- *
 * Spell: Bounce (by Opcode) [198] *
 * ------------------------------- */
 DEFINE_PATCH_MACRO ~opcode_self_198~ BEGIN
	LOCAL_SET strref = 401000 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
	PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11980001 // ~Renvoie %opcodeStr%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_198~ BEGIN
	LOCAL_SET strref = 401000 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
	PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11980003 // ~de renvoyer %opcodeStr%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_198~ BEGIN
	LOCAL_SET strref = 401000 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
	PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11980002 // ~Renvoie %opcodeStr% visant %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_198~ BEGIN
	LOCAL_SET strref = 401000 + parameter2
	LPF ~getTranslation~ INT_VAR strref opcode RET opcodeStr = string END
	PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @11980004 // ~de renvoyer %opcodeStr% visant %theTarget%~
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

DEFINE_PATCH_MACRO ~opcode_199_is_valid~ BEGIN
	PATCH_IF parameter1 < 0 OR parameter1 > 9 BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Power Level %parameter1%.~ END
	END
END

/* -------------------------------------------------- *
 * Spell: Bounce (by Power level, decrementing) [200] *
 * -------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_200~ BEGIN
	LOCAL_SET strref = 12000001 // ~Renvoie jusqu'à %amount% niveaux de sorts parmi ceux de %levelStr% niveau~
	LOCAL_SET strref_if_amount_0 = 110001 // ~Lance %spellName%~
	LPM ~opcode_200_common~
END

DEFINE_PATCH_MACRO ~opcode_target_200~ BEGIN
	LOCAL_SET strref = 12000002 // ~Renvoie jusqu'à %amount% niveaux de sorts ciblant %theTarget% parmi ceux de %levelStr% niveau~
	LOCAL_SET strref_if_amount_0 = 110002
	LPM ~opcode_200_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_200~ BEGIN
	LOCAL_SET strref = 12000003 // ~de renvoyer jusqu'à %amount% niveaux de sorts parmi ceux de %levelStr% niveau~
	LOCAL_SET strref_if_amount_0 = 110003
	LPM ~opcode_200_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_200~ BEGIN
	LOCAL_SET strref = 12000004 // ~de renvoyer jusqu'à %amount% niveaux de sorts ciblant %theTarget% parmi ceux de %levelStr% niveau~
	LOCAL_SET strref_if_amount_0 = 110004
	LPM ~opcode_200_common~
END

DEFINE_PATCH_MACRO ~opcode_200_common~ BEGIN
	LOCAL_SET spellStrref = 0
	LOCAL_SET amount = parameter1
	LOCAL_SET level = custom_int > 0 ? custom_int : parameter2
	LOCAL_SET spellLevelMax = 9
	LOCAL_SPRINT levelStr ~~
	LOCAL_SPRINT and @100021 // ~et~

	PATCH_IF level == 511 BEGIN
		SET strref += 10
	END
	ELSE BEGIN
		PATCH_DEFINE_ARRAY ~levels~ BEGIN END
		PATCH_DEFINE_ASSOCIATIVE_ARRAY ~levelAndBelow~ BEGIN
			  3 => 2
			  7 => 3
			 15 => 4
			 31 => 5
			 63 => 6
			127 => 7
			255 => 8
		END
		CLEAR_ARRAY ~levels~

		PATCH_IF VARIABLE_IS_SET $levelAndBelow(~%level%~) BEGIN
			SET spellStrref = 101200 + $levelAndBelow(~%level%~)
			SET strref += 20
			SPRINT levelStr (AT spellStrref)
		END
		ELSE BEGIN
			FOR (idx = 0 ; idx < spellLevelMax ; ++idx) BEGIN
				SET bit = EVAL ~%BIT%idx%%~
				PATCH_IF (level BAND bit) != 0 BEGIN
					SET spellStrref = 101200 + idx + 1
					SPRINT levelStr (AT spellStrref)
					SPRINT $levels(~%levelStr%~) ~~
				END
			END

			LPF ~implode~ STR_VAR array_name = ~levels~ glue = ~, ~ final_glue = ~ %and% ~ RET levelStr = text END
		END
	END
	LPF ~side_spell~ INT_VAR strref strref_if_amount_0 amount RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_200_is_valid~ BEGIN
	PATCH_IF parameter1 > 0 AND (parameter2 < 0 OR parameter2 > 9) BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Power Level %parameter2%.~ END
	END
	ELSE PATCH_IF is_ee == 0 AND parameter1 < 1 BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Total Amount %parameter1%.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_200_group~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions_already_check~ BEGIN END

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET searchP1 = parameter1
		SET newP2 = 0b0
		CLEAR_ARRAY positions
		PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF parameter1 == searchP1 AND parameter2 >= 1 AND parameter2 <= 256 AND NOT VARIABLE_IS_SET $positions_already_check(~%position%~) BEGIN
				// On retire l'opcode de ceux à checker dans les futures itérations
				SET $positions_already_check(~%position%~) = 1
				// On ajoute l'opcode courant à ceux qui seront désactivés
				SET $positions(~%position%~) = opcode
				// P2 retiré
				LPF ~get_opcode_position~
					INT_VAR opcode
			            match_target       = target
				        match_power        = power
				        match_parameter1   = parameter1
				        match_parameter3   = parameter3
				        match_parameter4   = parameter4
				        match_timingMode   = timingMode
				        match_resistance   = resistance
						match_duration     = duration
				        match_probability1 = probability1
				        match_probability2 = probability2
				        match_diceCount    = diceCount
				        match_diceSides    = diceSides
				        match_saveType     = saveType
				        match_saveBonus    = saveBonus
				        match_special      = special
					STR_VAR match_macro = ~opcode_match_diceCount_and_diceSides_and_duration_and_parameter1_and_parameter3_and_parameter4_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~
					RET opcodePosition = position
				END
				SET $positions(~%opcodePosition%~) = opcode
				SET parameter2 -= 1
				SET newP2 |= ~BIT%parameter2%~
			END
		END
		PATCH_IF newP2 > 0 BEGIN
			// Suppression des effets similaires
			PATCH_PHP_EACH positions AS position1 => opcode BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position1
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
			SET custom_int = newP2
			SET parameter1 = searchP1
			LPM ~add_opcode~
		END
	END

END

/* ---------------------------------------------------- *
 * Spell: Immunity (by Power Level, decrementing) [201] *
 * ---------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_201~ BEGIN
	LOCAL_SET strref = 12010001 //~Immunise jusqu'à %amount% niveaux de sorts parmi ceux de %levelStr% niveau~
	LOCAL_SET strref_if_amount_0 = 110001 // ~Lance %spellName%~
	LPM ~opcode_200_common~
END

DEFINE_PATCH_MACRO ~opcode_target_201~ BEGIN
	LOCAL_SET strref = 12010002 // ~Immunise %theTarget% jusqu'à %amount% niveaux de sorts parmi ceux de %levelStr% niveau~
	LOCAL_SET strref_if_amount_0 = 110002
	LPM ~opcode_200_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_201~ BEGIN
	LOCAL_SET strref = 12010003 // ~d'immuniser jusqu'à %amount% niveaux de sorts parmi ceux de %levelStr% niveau~
	LOCAL_SET strref_if_amount_0 = 110003
	LPM ~opcode_200_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_201~ BEGIN
	LOCAL_SET strref = 12010004 // ~d'immuniser %theTarget% jusqu'à %amount% niveaux de sorts parmi ceux de %levelStr% niveau~
	LOCAL_SET strref_if_amount_0 = 110004
	LPM ~opcode_200_common~
END

DEFINE_PATCH_MACRO ~opcode_201_is_valid~ BEGIN
	LPM ~opcode_200_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_201_group~ BEGIN
	LPM ~opcode_200_group~
END

/* ------------------------------- *
 * Spell: Bounce (by School) [202] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_202~ BEGIN
	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

	PATCH_IF NOT ~%spellSchoolName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12020001 // ~Renvoie les sorts de l'école %spellSchoolName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_202~ BEGIN
	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

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
	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

	SPRINT description @12040001 // ~Immunité aux sorts de l'école %spellSchoolName%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_204~ BEGIN
	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

	SPRINT description @12040002 // ~de résister aux sorts de l'école %spellSchoolName%~
END

DEFINE_PATCH_MACRO ~opcode_target_204~ BEGIN
	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12040003 // ~Immunise %theTarget% aux sorts de l'école %spellSchoolName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_204~ BEGIN
	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

	SPRINT description @12040004 // ~d'immuniser %theTarget% aux sorts de l'école %spellSchoolName%~
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

DEFINE_PATCH_MACRO ~opcode_target_205~ BEGIN
	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12050003 // ~Immunise %theTarget% aus sorts %spellSecondaryTypeName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_205~ BEGIN
	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

	SPRINT description @12050004 // ~d'immuniser %theTarget% aux sorts %spellSecondaryTypeName%~
END

DEFINE_PATCH_MACRO ~opcode_205_group~ BEGIN
	LOCAL_SET initOpcode = opcode
	LOCAL_SET baseSpellSecondaryType = 0

	PATCH_PHP_EACH EVAL ~opcodes_%initOpcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~

		SET baseSpellSecondaryType = parameter2

		// On supprime les éventuelles immunités spécifiques à un sort dont le type secondaire est identique à celui indiqué par l'opcode 205
		PATCH_PHP_EACH EVAL ~opcodes_206~ AS data => _ BEGIN
			LPM ~data_to_vars~

			PATCH_IF baseSpellSecondaryType > 0 AND FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
				INNER_PATCH_FILE ~%resref%.spl~ BEGIN
					READ_LONG SPL_sectype spellSecondaryType
					PATCH_IF spellSecondaryType == baseSpellSecondaryType BEGIN
						LPF ~delete_opcode~
							INT_VAR opcode = 206 match_position = position
							RET $opcodes(~206~) = count
							RET_ARRAY EVAL ~opcodes_206~ = opcodes_xx
						END
					END
				END
			END
		END
	END
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
		SPRINT description @12060003 // ~d'immuniser %theTarget% au sort %spellName%~
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

DEFINE_PATCH_MACRO ~opcode_206_group~ BEGIN
	// Immunité contre capacité psionique
	// Pas d'opcode spécifique qui peut aider à déterminer ce cas
	// TODO: vérifier que les durées et les JS correspondent
	LOCAL_SET searchOpcode = 171
	LOCAL_SET nbFound = 0
	PATCH_DEFINE_ARRAY psionicCapacities BEGIN
		"SPIN542" // PSIONIC_DISINTEGRATE
		"SPIN543" // PSIONIC_INFLICT_PAIN
		"SPIN544" // PSIONIC_SUPERIOR_INVISIBILITY
		"SPIN545" // PSIONIC_LIFE_DRAIN
		"SPIN546" // PSIONIC_INERTIAL_BARRIER
		"SPIN547" // PSIONIC_PROJECT_FORCE
		"SPIN727" // NOSAVE_PSIONIC_BLAST
		"SPIN774" // PSIONIC_MAZE
		"SPIN775" // PSIONIC_MIND_BLAST
		"SPIN804" // PSIONIC_EMOTION_KILL
		"SPIN834" // BRAIN_PSIONIC_BLAST
		"SPIN909" // PSIONIC_EGOWHIP
		"SPIN910" // PSIONIC_DOMINATION
		"SPIN911" // PSIONIC_BALLISTIC
		"SPIN912" // PSIONIC_DETONATE
		"SPIN959" // ULITHARID_PSIONIC_BLAST
		"SPIN974" // MIND_FLAYER_PSIONIC_BLAST
		"SPIN975" // Domination psionique
	END

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_PHP_EACH psionicCapacities AS _ => match_resref BEGIN
			PATCH_IF ~%match_resref%~ STRING_EQUAL_CASE ~%resref%~ BEGIN
				SET nbFound += 1
				PATCH_IF nbFound == 5 BEGIN
					SET opcode = 101
					SET parameter2 = 505
					LPM ~add_opcode~
				END
			END
		END
	END
	SET opcode = 206
	// Solution : possède la protection contre au moins 5 capacités psioniques
	PATCH_IF nbFound >= 5 BEGIN
		PATCH_IF show_lack_immunity BEGIN
			PATCH_PHP_EACH psionicCapacities AS _ => resref BEGIN
				// Affichage warning car sort non trouvé
				LPF ~has_opcode~
					INT_VAR opcode
					STR_VAR
						match_macro  = ~opcode_match_resref~
						match_resref = ~%resref%~
					RET hasOpcode
				END
				PATCH_IF NOT hasOpcode BEGIN
					LPF ~add_log_error~ STR_VAR message = EVAL ~Fichier %SOURCE_FILE% : Immunity against psionic spells: Opcode 206 with resref %resref% not found.~ END
				END
			END
		END
		PATCH_PHP_EACH psionicCapacities AS _ => resref BEGIN
			LPF ~delete_opcode~
				INT_VAR opcode
				STR_VAR
					match_macro  = ~opcode_match_resref~
					match_resref = ~%resref%~
				RET $opcodes(~%opcode%~) = count
				RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
			END
		END
	END
END

// Traitement des immunités aux sortilèges qui n'auraient pas été supprimées par les précédents regroupements
DEFINE_PATCH_MACRO ~opcode_206_post_group~ BEGIN
	LOCAL_SET count = 0
	LOCAL_SPRINT and @100021 // ~et~
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~opcode_206_positions~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~opcode_206_positions_already_check~ BEGIN END

	// Suppression opcode 321 associé à la même ressource, pour un joueur lambda, avoir l'immunité signifie aussi que les effets en cours sont dissipés.
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		LPF ~delete_opcode~
			INT_VAR opcode = 321
			STR_VAR
				match_macro  = ~opcode_match_resref~
				match_resref = ~%resref%~
			RET $opcodes(~321~) = count
			RET_ARRAY EVAL ~opcodes_321~ = opcodes_xx
		END
		// Bug où il reste toujours un item dans le tableau si c'était le dernier
		// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
		PATCH_IF $opcodes(~321~) == 0 BEGIN
            CLEAR_ARRAY ~opcodes_321~
        END
	END

	// Regroupement des immunités restantes en une seule ligne
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF NOT VARIABLE_IS_SET $opcode_206_positions_already_check(~%position%~) BEGIN
			SET searchTarget = target
			SET searchTimingMode = timingMode
			SET searchDuration = duration
			CLEAR_ARRAY opcode_206_positions
			CLEAR_ARRAY spellList
			SET $opcode_206_positions(~%position%~) = opcode
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_vars~
				PATCH_IF NOT VARIABLE_IS_SET $opcode_206_positions_already_check(~%position%~) AND searchTarget == target AND (searchTimingMode == TIMING_while_equipped OR (searchTimingMode != TIMING_while_equipped AND searchTimingMode == timingMode AND searchDuration == duration)) BEGIN
					LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

					PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
						SET $spellList(~%spellName%~) = 1
						SET $opcode_206_positions_already_check(~%position%~) = opcode
						SET $opcode_206_positions(~%position%~) = opcode
					END
				END
			END
			SET count = 0
			PATCH_PHP_EACH spellList AS spellName => _ BEGIN
				SET count += 1
			END
			PATCH_IF count > 1 BEGIN
				PATCH_PHP_EACH opcode_206_positions AS position => opcode BEGIN
					LPF ~delete_opcode~
						INT_VAR opcode match_position = position
						RET $opcodes(~%opcode%~) = count
						RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
					END
				END
				// Bug où il reste toujours un item dans le tableau si c'était le dernier
				// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
				PATCH_IF $opcodes(~206~) == 0 BEGIN
		            CLEAR_ARRAY ~opcodes_206~
		        END
				SORT_ARRAY_INDICES spellList
				SET opcode = 518
				LPF ~implode~ STR_VAR array_name = ~spellList~ glue = ~, ~ final_glue = ~ %and% ~ RET custom_str = text END
				LPM ~add_opcode~
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_206_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_206_spell_level_match~ BEGIN
	// Parameter #1: String Reference (sans importance pour AutoDescription)
    // Parameter #2: Irrelevant
	SET match_parameter1 = parameter1
	SET match_parameter2 = parameter2
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
	PATCH_IF parameter1 != 0 BEGIN
		SPRINT value ~%parameter1%~
		SPRINT description @12080001 // ~Les points de vie ne peuvent passer en dessous de %value%~
	END
	ELSE BEGIN
		SPRINT description @12080002 // ~Les points de vie ne sont plus protégés~
	END
END

/* ---------------------- *
 * Death: Kill 60HP [209] *
 * ---------------------- */
DEFINE_PATCH_MACRO ~opcode_self_209~ BEGIN
	LPM ~opcode_target_209~
END

DEFINE_PATCH_MACRO ~opcode_target_209~ BEGIN
	SET death_type = 0x4
	SET description_strref = $death_to_strref(~%death_type%~)
	SPRINT descriptionAdd @12090001 // ~si ses points de vie sont inférieurs à 60~

	SPRINT description (AT description_strref)
	SPRINT description EVAL ~%description% %descriptionAdd%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_209~ BEGIN
	SET death_type = 0x4
	SET description_strref = $death_to_strref(~%death_type%~)
	SET description_strref += 100
	SPRINT descriptionAdd @12090001 // ~si ses points de vie sont inférieurs à 60~

	SPRINT description (AT description_strref)
	SPRINT description EVAL ~%description% %descriptionAdd%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_209~ BEGIN
	LPM ~opcode_self_probability_209~
END

DEFINE_PATCH_MACRO ~opcode_209_is_valid~ BEGIN
	LOCAL_SET death_type = 0x4
	PATCH_IF NOT VARIABLE_IS_SET $death_to_strref(~%death_type%~) BEGIN
		isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Mort a gerer : %death_type%~ END
	END
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

DEFINE_PATCH_MACRO ~opcode_211_group~ BEGIN
	PATCH_PHP_EACH ~opcodes_71~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF parameter1 == 66 AND parameter2 == 1 BEGIN
			LPF ~delete_opcode~
				INT_VAR opcode = 71 match_position = position
				RET $opcodes(~71~) = count
				RET_ARRAY EVAL ~opcodes_71~ = opcodes_xx
			END
		END
	END
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
DEFINE_PATCH_MACRO ~opcode_self_213~ BEGIN
	LPM ~opcode_target_213~ // ~Enferme %theTarget% dans un labyrinthe~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_213~ BEGIN
	PATCH_IF parameter2 == 0 OR NOT is_ee BEGIN
		SET ignoreDuration = 1
		SPRINT description @12130002 // ~d'enfermer %theTarget% dans un labyrinthe, la durée varie selon l'Intelligence~
	END
	ELSE BEGIN
		SPRINT description @12130004 // ~d'enfermer %theTarget% dans un labyrinthe~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_213~ BEGIN
	PATCH_IF parameter2 == 0 OR NOT is_ee BEGIN
		SET ignoreDuration = 1
		SPRINT description @12130001 // ~Enferme %theTarget% dans un labyrinthe, la durée varie selon l'Intelligence~
	END
	ELSE BEGIN
		SPRINT description @12130003 // ~Enferme %theTarget% dans un labyrinthe~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_213~ BEGIN
	LPM ~opcode_self_probability_213~ // ~d'enfermer %theTarget% dans un labyrinthe~
END

/* -------------------------------- *
 * Spell Effect: Select Spell [214] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_214~ BEGIN
	LOCAL_SET strref = 12140001 // ~Permet de lancer un sort du livre de sorts~
	LPM ~opcode_214_common~
END

DEFINE_PATCH_MACRO ~opcode_target_214~ BEGIN
	LOCAL_SET strref = 12140003 // ~Permet %toTheTarget% de lancer un sort du livre de sorts~
	LPM ~opcode_214_common~
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
		FOR (row = 0 ; row < rows ; row = row + 1) BEGIN
			READ_2DA_ENTRY row 1 3 resref
			PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
				LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
				PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
					SPRINT spells ~%spells%%crlf%%spellName%~
				END
			END
			ELSE BEGIN
				LPF ~add_log_error~ STR_VAR message = ~Opcode %opcode% : File %resref%.spl not found~ END
			END
		END
	END

	INNER_PATCH_SAVE spells ~%spells%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE ~%crlf%~ ~%crlf%  * ~ // Indentation de la liste des sorts
	END
END

DEFINE_PATCH_MACRO ~opcode_214_common~ BEGIN
	LOCAL_SET type = parameter2

	PATCH_IF type == 0 BEGIN
		LPF ~opcode_214_get_spells~ STR_VAR file = EVAL ~%resref%~ RET spells END
		PATCH_IF NOT ~%spells%~ STRING_EQUAL ~~ BEGIN
			SET strref += 1
            SPRINT description (AT strref)
		END
	END
	ELSE BEGIN
		//TODO: IF ee ajouter sauf SPWI110 et SPWI124 ?
        SPRINT description (AT strref) // ~Permet de lancer un sort du livre de sorts~
	END
END

DEFINE_PATCH_MACRO ~opcode_214_is_valid~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		LPM ~opcode_resref_is_valid~
	END
END

/* ------------------------------- *
 * Spell Effect: Level Drain [216] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_216~ BEGIN
	SET strref = 12160001
	LPM ~opcode_216_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_216~ BEGIN
	SET strref = 12160011
	LPM ~opcode_216_common~
END

DEFINE_PATCH_MACRO ~opcode_target_216~ BEGIN
	LPM ~opcode_self_216~ // ~Draîne 1 niveau %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_216~ BEGIN
	LPM ~opcode_self_probability_216~ // ~de drainer 1 niveau %toTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_216_common~ BEGIN
	LOCAL_SET amount = ~%parameter1%~

	PATCH_IF amount > 1 BEGIN // ~Draine %amount% niveaux %toTheTarget%~
		SET strref += 1
	END
	ELSE PATCH_IF amount == 0 BEGIN // ~Inhibe le passage au niveau supérieur %ofTheTarget%~
		SET strref += 2
	END
	ELSE PATCH_IF amount == ~-1~ BEGIN // ~Injecte 1 niveau %toTheTarget%~
		SET amount = ABS amount
		SET strref += 3
	END
	ELSE PATCH_IF amount < ~-1~ BEGIN // ~Injecte %amount% niveaux %toTheTarget%~
		SET amount = ABS amount
		SET strref += 4
	END
	SPRINT description (AT strref) // ~de drainer %amount% niveaux %toTheTarget%~
END


/* ---------------------------------------- *
 * Spell Effect: Unconsciousness 20HP [217] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_217~ BEGIN
	// Durée forcée à 5 rounds
	SET duration = 30
	SET timingMode = TIMING_duration
	LPM ~opcode_self_39~
	SPRINT description @12170001 // ~%description% si ses points de vie sont inférieurs à 20~
END

DEFINE_PATCH_MACRO ~opcode_target_217~ BEGIN
	// Durée forcée à 5 rounds
	SET duration = 30
	SET timingMode = TIMING_duration
	LPM ~opcode_target_39~
	SPRINT description @12170001 // ~%description% si ses points de vie sont inférieurs à 20~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_217~ BEGIN
	// Durée forcée à 5 rounds
	SET duration = 30
	SET timingMode = TIMING_duration
	LPM ~opcode_self_probability_39~
	SPRINT description @12170001 // ~%description% si ses points de vie sont inférieurs à 20~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_217~ BEGIN
	// Durée forcée à 5 rounds
	SET duration = 30
	SET timingMode = TIMING_duration
	LPM ~opcode_target_probability_39~
	SPRINT description @12170001 // ~%description% si ses points de vie sont inférieurs à 20~
END

/* --------------------------- *
 * Protection: Stoneskin [218] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_218~ BEGIN
	LOCAL_SET strref = 12180001 // ~Crée %amount% %skinType%~

	LPM ~opcode_218_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_218~ BEGIN
	LOCAL_SET strref = 12180002 // ~de créer %amount% %skinType% sur %theTarget%~

	LPM ~opcode_218_common~
END

DEFINE_PATCH_MACRO ~opcode_target_218~ BEGIN
	LOCAL_SET strref = 12180003 // ~Crée %amount% %skinType% sur %theTarget%~

	LPM ~opcode_218_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_218~ BEGIN
	LPM ~opcode_self_probability_218~
END

// Commun aux opcodes 218 et 314
DEFINE_PATCH_MACRO ~opcode_218_common~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
		SPRINT amount ~%complex_value%~
	END
	ELSE BEGIN
		PATCH_IF is_ee == 1 AND parameter2 != 0 AND opcode == 218 BEGIN
			LPF ~get_damage_value~ INT_VAR diceCount diceSides damageAmount = amount RET amount = damage END
			INNER_PATCH_SAVE amount ~%amount%~ BEGIN
				REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
			END
		END
		// "Dissipation"
		PATCH_IF IS_AN_INT amount AND amount == 0 BEGIN
			SET strref += 10
		END

		SET skinTypeRef = 10000101 + opcode * 10000
		PATCH_IF NOT IS_AN_INT amount OR amount != 1 BEGIN
			SET skinTypeRef += 1 // ~peaux de pierre~
		END
		SPRINT valueType (AT skinTypeRef) // ~peau de pierre~
		SPRINT value ~%amount%~
		SPRINT amount @102165 // ~%value% %valueType%~
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_218_is_valid~ BEGIN
	PATCH_IF parameter1 <= 0 AND (NOT is_ee OR parameter2 == 0 OR diceCount == 0) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No stoneskin detected~ END
	END
END

DEFINE_PATCH_FUNCTION ~opcode_218_typed_value~ INT_VAR value = 0 RET strref BEGIN
	SET strref = 12180101 // ~peau de pierre~
	PATCH_IF value > 1 BEGIN
		SET strref = 12180102 // ~peaux de pierre~
	END
END

/* ----------------------------------------- *
 * Stat: AC vs. Creature Type Modifier [219] *
 * ----------------------------------------- */
// AC
DEFINE_PATCH_MACRO ~opcode_self_219000~ BEGIN
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END

	SPRINT value ~+2 %versus%~
	SPRINT name @10000099      // ~Classe d'armure~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_target_219000~ BEGIN
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END

	SPRINT value ~+2 %versus%~
	SPRINT name @10000099      // ~Classe d'armure~
	SPRINT description @100007 // ~%name% %ofTheTarget%%colon%%value%~
END

// Save throws
DEFINE_PATCH_MACRO ~opcode_self_219001~ BEGIN
	PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
		SPRINT versus ~%custom_str%~
	END
	ELSE BEGIN
		LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END
	END
	SPRINT value ~+2 %versus%~
	SPRINT name @102034        // ~Jets de sauvegarde~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_target_219001~ BEGIN
	LPF ~get_ids_versus_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET versus = idVersusName END

	SPRINT value ~+2 %versus%~
	SPRINT name @102034        // ~Jets de sauvegarde~
	SPRINT description @100007 // ~%name% %ofTheTarget%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_219001_group~ BEGIN
	LOCAL_SPRINT the @11770200 // ~les~
	LOCAL_SPRINT andThe @11770201 // ~et les~
	CLEAR_ARRAY targetTypes
    PATCH_DEFINE_ARRAY targetTypes BEGIN END

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF timingMode == TIMING_while_equipped AND target == TARGET_FX_self BEGIN
			PATCH_IF VARIABLE_IS_SET $ids_files(~%parameter2%~) BEGIN
                LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%parameter2%~ RET idName END
                SET $targetTypes(~%idName%~) = 1
            END
            ELSE BEGIN
                LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Wrong ids file : %file%~ END
            END
			LPF ~delete_opcode~
                INT_VAR opcode match_position = position
                RET $opcodes(~%opcode%~) = count
                RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
            END
		END
	END
	// Bug où il reste toujours un item dans le tableau si c'était le dernier
	// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
	PATCH_IF $opcodes(~219001~) == 0 BEGIN
        CLEAR_ARRAY ~opcodes_219001~
    END
	LPF ~implode~ STR_VAR array_name = ~targetTypes~ glue = ~, %the% ~ final_glue = ~ %andThe% ~ RET targetType = text END

	PATCH_IF NOT ~%targetType%~ STRING_EQUAL ~~ BEGIN
		SPRINT custom_str @102387 // ~contre les %targetType%~
		LPM ~add_opcode~
	END
END

DEFINE_PATCH_MACRO ~opcode_219_replace~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~

		LPF ~delete_opcode~
			INT_VAR opcode match_position = position
			RET $opcodes(~%opcode%~) = count
			RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
		END

		SET opcode = 219000
		LPM ~add_opcode~

		SET opcode = 219001
		LPM ~add_opcode~
		// Nécessaire de remettre le numéro original pour les itérations suivantes
		SET opcode = 219
	END
END

DEFINE_PATCH_MACRO ~opcode_219_is_valid~ BEGIN
	LPM ~opcode_idscheck8_is_valid~
END

/* ---------------------------- *
 * Removal: Remove School [220] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_220~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

	PATCH_IF spellLevel < 9 BEGIN
		SPRINT description @12200001 // ~Dissipe tous les sorts de l'école %spellSchoolName% de niveau %spellLevel% ou inférieur sur %theTarget%~
	END
    ELSE BEGIN
        SPRINT description @12200003 // ~Dissipe un sort de l'école %spellSchoolName% sur %theTarget%~
    END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_220~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

	PATCH_IF spellLevel < 9 BEGIN
		SPRINT description @12200002 // ~de dissiper tous les sorts de l'école %spellSchoolName% de niveau %spellLevel% ou inférieur sur %theTarget%~
	END
    ELSE BEGIN
        SPRINT description @12200004 // ~de dissiper tous les sorts de l'école %spellSchoolName% sur %theTarget%~
    END
END

DEFINE_PATCH_MACRO ~opcode_target_220~ BEGIN
	LPM ~opcode_self_220~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_220~ BEGIN
	LPM ~opcode_self_probability_220~
END

DEFINE_PATCH_MACRO ~opcode_220_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF parameter1 == 9 AND parameter2 == 5 BEGIN
			// Chercher un opcode 221 avec parameter1 == 9 ET parameter2 == 3
			// toutes les illusions
			//
			LPF ~get_opcode_position~
				INT_VAR opcode = 221
			        match_target       = target
			        match_parameter1   = 9
			        match_parameter2   = 3
			        match_timingMode   = timingMode
			        match_resistance   = resistance
					match_duration     = duration
			        match_probability1 = probability1
			        match_probability2 = probability2
			        match_saveType     = saveType
			        match_saveBonus    = saveBonus
			        match_special      = special
				STR_VAR match_macro = ~opcode_match_duration_and_parameter1_and_parameter2_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~
				RET opcodePosition = position
			END
			PATCH_IF opcodePosition >= 0 BEGIN
				LPF ~delete_opcode~
                    INT_VAR opcode = 220 match_position = position
                    RET $opcodes(~220~) = count
                    RET_ARRAY EVAL ~opcodes_220~ = opcodes_xx
                END
				LPF ~delete_opcode~
                    INT_VAR opcode = 221 match_position = opcodePosition
                    RET $opcodes(~221~) = count
                    RET_ARRAY EVAL ~opcodes_221~ = opcodes_xx
                END
                SET opcode = 511
                LPM ~add_opcode~
			END
		END
	END
END

/* ------------------------------------ *
 * Removal: Remove Secondary Type [221] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_221~ BEGIN
	LOCAL_SET spellLevel = parameter1
	PATCH_TRY
		LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

		PATCH_IF spellLevel < 9 BEGIN
			SPRINT description @12210001 // ~Dissipe tous les sorts %spellSecondaryTypeName% de niveau %spellLevel% ou inférieur sur %theTarget%~
		END
	    ELSE BEGIN
	        SPRINT description @12210003 // ~Dissipe tous les sorts %spellSecondaryTypeName% sur %theTarget%~
	    END
	WITH DEFAULT
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Wrong parameter2 : %parameter2%~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_221~ BEGIN
	LOCAL_SET spellLevel = parameter1

	PATCH_TRY
		LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

		PATCH_IF spellLevel < 9 BEGIN
			SPRINT description @12210002 // ~de dissiper tous les sorts %spellSecondaryTypeName% de niveau %spellLevel% ou inférieur sur %theTarget%~
		END
	    ELSE BEGIN
	        SPRINT description @12210004 // ~de dissiper tous les sorts %spellSecondaryTypeName% sur %theTarget%~
	    END
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

DEFINE_PATCH_MACRO ~opcode_221_is_valid~ BEGIN
	PATCH_IF parameter1 < 1 BEGIN
		isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Maximum Level %parameter1%.~ END
	END
END

/* ---------------------------------- *
 * Spell Effect: Teleport Field [222] *
 * ---------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_222~ BEGIN
	LOCAL_SET value = parameter1
	LPF ~feets_to_meters~ INT_VAR range = value RET range = rangeToMeter END

	SPRINT description @12220001 // ~Téléporte aléatoirement %theTarget% dans un rayon de %range%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_222~ BEGIN
	LOCAL_SET value = parameter1
	LOCAL_SET value = parameter1
	LPF ~feets_to_meters~ INT_VAR range = value RET range = rangeToMeter END

	SPRINT description @12220002 // ~de téléporter aléatoirement %theTarget% dans un rayon de %range%~
END

DEFINE_PATCH_MACRO ~opcode_target_222~ BEGIN
	LPM ~opcode_self_222~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_222~ BEGIN
	LPM ~opcode_self_probability_222~
END

/* ---------------------------------------------- *
 * Spell: Immunity (by School, decrementing) [223] *
 * ---------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_223~ BEGIN
	LOCAL_SET strref = 12230001 // ~Immunise jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	LOCAL_SET strref_if_amount_0 = 110001 // ~Lance %spellName%~
	LPM ~opcode_223_common~
END

DEFINE_PATCH_MACRO ~opcode_target_223~ BEGIN
	LOCAL_SET strref = 12230002 // ~Immunise %theTarget% jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	LOCAL_SET strref_if_amount_0 = 110002
	LPM ~opcode_223_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_223~ BEGIN
	LOCAL_SET strref = 12230003 // ~d'immuniser jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	LOCAL_SET strref_if_amount_0 = 110003
	LPM ~opcode_223_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_223~ BEGIN
	LOCAL_SET strref = 12230004 // ~d'immuniser %theTarget% jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	LOCAL_SET strref_if_amount_0 = 110004
	LPM ~opcode_223_common~
END

DEFINE_PATCH_MACRO ~opcode_223_common~ BEGIN
	LOCAL_SET amount = parameter1
	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END
	LPF ~side_spell~ INT_VAR strref strref_if_amount_0 amount RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_223_is_valid~ BEGIN
	PATCH_IF is_ee == 0 AND parameter1 < 1 BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Total Amount %parameter1%.~ END
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
	LOCAL_SET strref = 12260001 // ~Immunise jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	LOCAL_SET strref_if_amount_0 = 110001 // ~Lance %spellName%~
	LPM ~opcode_226_common~
END

DEFINE_PATCH_MACRO ~opcode_target_226~ BEGIN
	LOCAL_SET strref = 12260002 // ~Immunise %theTarget% jusqu'à %amount% niveaux de sorts de la sphère %spellSecondaryTypeName%~
	LOCAL_SET strref_if_amount_0 = 110002
	LPM ~opcode_226_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_226~ BEGIN
	LOCAL_SET strref = 12260003 // ~d'immuniser jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	LOCAL_SET strref_if_amount_0 = 110003
	LPM ~opcode_226_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_226~ BEGIN
	LOCAL_SET strref = 12260004 // ~d'immuniser %theTarget% jusqu'à %amount% niveaux de sorts de la sphère %spellSecondaryTypeName%~
	LOCAL_SET strref_if_amount_0 = 110004
	LPM ~opcode_226_common~
END

DEFINE_PATCH_MACRO ~opcode_226_common~ BEGIN
	LOCAL_SET amount = parameter1
	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END
	LPF ~side_spell~ INT_VAR strref strref_if_amount_0 amount RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_226_is_valid~ BEGIN
	PATCH_IF is_ee == 0 AND parameter1 < 1 BEGIN
		isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Total Amount %parameter1%.~ END
	END
END

/* --------------------------------------------- *
 * Spell: Bounce (by School, decrementing) [227] *
 * --------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_227~ BEGIN
	SET strref = 12270001 // ~Renvoie jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	SET strref_if_amount_0 = 110001 // ~Lance %spellName%~
	LPM ~opcode_227_common~
END

DEFINE_PATCH_MACRO ~opcode_target_227~ BEGIN
	SET strref = 12270002 // ~Renvoie jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName% ciblant %theTarget%~
	SET strref_if_amount_0 = 110002
	LPM ~opcode_227_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_227~ BEGIN
	SET strref = 12270003 // ~de renvoyer jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	SET strref_if_amount_0 = 110003
	LPM ~opcode_227_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_227~ BEGIN
	SET strref = 12270004 // ~de renvoyer jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	SET strref_if_amount_0 = 110004
	LPM ~opcode_227_common~
END

DEFINE_PATCH_MACRO ~opcode_227_common~ BEGIN
	LPM ~opcode_223_common~
END

DEFINE_PATCH_MACRO ~opcode_227_is_valid~ BEGIN
	LPM ~opcode_223_is_valid~
END

/* ----------------------------------------------------- *
 * Spell: Bounce (by Secondary Type, decrementing) [228] *
 * ----------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_228~ BEGIN
	SET strref = 12280001 // ~Renvoie jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	SET strref_if_amount_0 = 110001 // ~Lance %spellName%~
	LPM ~opcode_228_common~
END

DEFINE_PATCH_MACRO ~opcode_self_228~ BEGIN
	SET strref = 12280002 // ~Renvoie jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	SET strref_if_amount_0 = 110002
	LPM ~opcode_228_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_228~ BEGIN
	SET strref = 12280003 // ~de renvoyer jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	SET strref_if_amount_0 = 110003
	LPM ~opcode_228_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_228~ BEGIN
	SET strref = 12280004 // ~de renvoyer jusqu'à %amount% niveaux de sorts de l'école %spellSchoolName%~
	SET strref_if_amount_0 = 110004
	LPM ~opcode_228_common~
END

DEFINE_PATCH_MACRO ~opcode_228_common~ BEGIN
	LPM ~opcode_226_common~
END

DEFINE_PATCH_MACRO ~opcode_228_is_valid~ BEGIN
	LPM ~opcode_226_is_valid~
END

/* -------------------------------- *
 * Removal: Remove One School [229] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_229~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

	PATCH_IF spellLevel < 9 BEGIN
		SPRINT description @12290001 // ~Dissipe un sort de l'école %spellSchoolName% de niveau %spellLevel% ou inférieur sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @12290003 // ~Dissipe un sort de l'école %spellSchoolName% sur %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_229~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END

	PATCH_IF spellLevel < 9 BEGIN
		SPRINT description @12290002 // ~de dissiper un sort de l'école %spellSchoolName% de niveau %spellLevel% ou inférieur sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @12290004 // ~de dissiper un sort de l'école %spellSchoolName% sur %theTarget%~
	END
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

	PATCH_IF spellLevel < 9 BEGIN
		SPRINT description @12300001 // ~Dissipe un sort de la sphère %spellSecondaryTypeName% de niveau %spellLevel% ou inférieur sur %theTarget%~
	END
    ELSE BEGIN
        SPRINT description @12300003 // ~Dissipe un sort de la sphère %spellSecondaryTypeName% sur %theTarget%~
    END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_230~ BEGIN
	LOCAL_SET spellLevel = parameter1

	LPF ~get_spell_secondary_type~ INT_VAR secondaryType = parameter2 RET spellSecondaryTypeName END

	PATCH_IF spellLevel < 9 BEGIN
		SPRINT description @12300002 // ~de dissiper un sort de la sphère %spellSecondaryTypeName% de niveau %spellLevel% ou inférieur sur %theTarget%~
	END
	ELSE BEGIN
		SPRINT description @12300004 // ~de dissiper un sort de la sphère %spellSecondaryTypeName% sur %theTarget%~
	END
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
	// The timestop effect lasts half as long as the Duration specified for the effect.
	SET duration /= 2
	SPRINT description @12310001 // ~Arrêt du temps~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_231~ BEGIN
	SET duration /= 2
	SPRINT description @12310003 // ~de lancer Arrêt du temps~
END

DEFINE_PATCH_MACRO ~opcode_target_231~ BEGIN
	SET duration /= 2
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

	SPRINT spellName ~~
	SPRINT spellName2 ~~
	SPRINT spellName3 ~~
	SPRINT theTarget   (AT ~%theTargetRef%~)
	SPRINT ofTheTarget (AT ~%ofTheTargetRef%~)
	SPRINT toTheTarget (AT ~%toTheTargetRef%~)
	SPRINT versus (AT ~%toTheTargetRef%~)

	LPM ~opcode_232_condition~

	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_spell_name~ STR_VAR file = ~%resref%~ RET spellName END
	END
	PATCH_IF isExternal AND NOT ~%resref2%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_spell_name~ STR_VAR file = ~%resref2%~ RET spellName2 = spellName END
	END
	PATCH_IF isExternal AND NOT ~%resref3%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_spell_name~ STR_VAR file = ~%resref3%~ RET spellName3 = spellName END
	END
	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND NOT ~%spellName2%~ STRING_EQUAL ~~ AND NOT ~%spellName3%~ STRING_EQUAL ~~ BEGIN
		SET strref += 2 // ~lance les sorts %spellName%, %spellName2% et %spellName3% sur %theTarget%~
		SPRINT description (AT ~%strref%~)
    END
    ELSE PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND NOT ~%spellName2%~ STRING_EQUAL ~~ BEGIN
		SET strref += 1 // ~lance les sorts %spellName% et %spellName2% sur %theTarget%~
		SPRINT description (AT ~%strref%~)
    END
    ELSE PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND NOT ~%spellName3%~ STRING_EQUAL ~~ BEGIN
		SPRINT spellName2 ~%spellName3%~
        SET strref += 1 // ~lance les sorts %spellName% et %spellName2% sur %theTarget%~
	    SPRINT description (AT ~%strref%~)
    END
    ELSE PATCH_IF NOT ~%spellName2%~ STRING_EQUAL ~~ AND NOT ~%spellName3%~ STRING_EQUAL ~~ BEGIN
		SPRINT spellName ~%spellName3%~
		SET strref += 1 // ~lance les sorts %spellName% et %spellName2% sur %theTarget%~
		SPRINT description (AT ~%strref%~)
	END
	ELSE BEGIN // Un seul sort
		PATCH_IF parameter2 == 8 OR parameter2 == 9 OR parameter2 == 14 BEGIN
            //TODO: recalculer versus selon la cible du sort pointé ?
            SPRINT versus ~~
        END
		PATCH_IF NOT ~%spellName3%~ STRING_EQUAL ~~ BEGIN
			LPF ~get_item_spell_effects_description~ INT_VAR baseProbability = probability STR_VAR file = ~%resref3%~ RET description END
		END
		ELSE PATCH_IF NOT ~%spellName2%~ STRING_EQUAL ~~ BEGIN
			LPF ~get_item_spell_effects_description~ INT_VAR baseProbability = probability STR_VAR file = ~%resref2%~ RET description END
		END
		ELSE PATCH_IF ~%spellName%~ STRING_EQUAL ~~ BEGIN
			LPF ~get_item_spell_effects_description~ INT_VAR baseProbability = probability STR_VAR file = ~%resref%~ RET description END
	    END
	    ELSE BEGIN
			LPF ~get_item_spell_effects_description~ INT_VAR baseProbability = probability STR_VAR file = ~%resref%~ RET description totalLines END
			PATCH_IF totalLines > 1 BEGIN
		        SPRINT description (AT ~%strref%~) // ~lance le sort %spellName% sur %theTarget%~
			END
	    END
		PATCH_IF probability < 100 BEGIN
			INNER_PATCH_SAVE description ~%description%~ BEGIN
				SPRINT regex @10009 // ~^[0-9]+ % de chance ~
				REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
			END
		END
    END
END

DEFINE_PATCH_MACRO ~opcode_232_condition~ BEGIN
	SET conditionRef = 12320010 + parameter2
	SPRINT condition (AT ~%conditionRef%~)

	PATCH_IF parameter2 >= 2 AND parameter2 <= 4 OR parameter2 == 20 BEGIN
		SET value = parameter2 == 2 ? 50 : parameter2 == 3 ? 25 : parameter2 == 4 ? 10 : special
		PATCH_IF value >= 100 BEGIN
			// Un sort lancé à chaque round via une capacité d'équipement peut être considéré comme permanent.
			// Il existe un risque où il serait préférable d'indiquer que le sort est lancé chaque round, mais je n'ai pas encore rencontré ce cas.
			// Tous les sorts actuellement rencontrés et lancés de cette manière sont des buffs.
			PATCH_IF abilityType == AbilityType_Equipped BEGIN
				SPRINT condition @12320000 // ~~
				SET ignoreDuration = 1
			END
			ELSE BEGIN
				SPRINT condition @12320020 // ~À chaque round~
			END
		END
		ELSE BEGIN
			LPF ~percent_value~ INT_VAR value RET percent = value END
			SPRINT condition @12320030 // ~Lorsque les points de vie du porteur passent sous les %percent%~
		END
	END
	ELSE PATCH_IF parameter2 == 5 OR parameter2 == 6 OR parameter2 == 15 BEGIN
		PATCH_IF parameter2 == 5 BEGIN
			SET state = 0x20 // sans défense
			SET parameter1 = 1
		END
		ELSE PATCH_IF parameter2 == 6 BEGIN
			SET state = 0x4000 // empoisonné
			SET parameter1 = 1
		END
		ELSE BEGIN
			SET state = special
		END
		LPF ~get_states_str~ INT_VAR state = state RET state = descriptionState END
		SPRINT condition @12320025 // ~Lorsque %theTarget% est %state%~
	END
	ELSE PATCH_IF parameter2 == 19 BEGIN
		SET value = special
		SPRINT condition @12320029 // ~Lorsque les points de vie du porteur passent sous %value%~
	END
	ELSE PATCH_IF parameter2 == 8 OR parameter2 == 9 OR parameter2 == 14 BEGIN
		SET value = parameter2 == 8 ? 4 : parameter2 == 9 ? 10 : special
		LPF ~feets_to_meters~ INT_VAR range = value RET range = rangeToMeter END
		SPRINT condition @12320024 // ~Lorsque la cible se trouve à moins de %range%~
	END
	ELSE PATCH_IF parameter2 == 13 BEGIN
		PATCH_IF abilityType == AbilityType_Equipped BEGIN
			SET timeofdayRef = 12320300 + special
			SET ignoreDuration = 1
		END
		ELSE BEGIN
			SET timeofdayRef = 12320304 + special
		END
		LPF ~getTranslation~ INT_VAR strref = timeofdayRef opcode RET condition = string END
	END
	ELSE PATCH_IF parameter2 == 21 BEGIN
		SET stateRef = 420000 + special
		LPF ~getTranslation~ INT_VAR strref = stateRef opcode RET splstate = string END
		PATCH_IF NOT ~%splstate%~ STRING_EQUAL ~~ BEGIN
			SPRINT condition @12320031 // ~À chaque round où %theTarget% est affecté par %splstate%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_232_group~ BEGIN
	LPM ~opcode_232_group_mod~
END

DEFINE_PATCH_MACRO ~opcode_232_is_valid~ BEGIN
	PATCH_IF parameter1 < 0 OR parameter1 > 3 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Target: %parameter1% (0-3 expected)~ END
	END
	PATCH_IF parameter2 < 0 OR parameter2 > 21 OR parameter2 > 11 AND NOT is_ee BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Condition: %parameter2% (EE: 0-21 expected, non-EE: 0-11 expected)~ END
	END
	PATCH_IF parameter2 == 13 AND parameter1 != 0 BEGIN // TimeOfDay
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: TimeOfDay : Parameter1 must be equal to 0~ END
	END
	PATCH_IF parameter2 == 10 AND special == 0 BEGIN // TimeOfDay
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Crash warning: Opcode %opcode%: parameter2 = 10 and special = 0~ END
	END
	PATCH_IF ~%resref%~ STRING_EQUAL ~~ AND (NOT isExternal OR ~%resref2%~ STRING_EQUAL ~~ AND ~%resref3%~ STRING_EQUAL ~~) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: resource field are empty~ END
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

		PATCH_IF type != 0 BEGIN
			LPF ~signed_value~ INT_VAR value RET value END
		END
		ELSE BEGIN
			SPRINT value @10010 // ~Passe à %value%~
		END

		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_233~ BEGIN
	LOCAL_SPRINT proficiency ~~

	LPM ~opcode_233_common~

	PATCH_IF VARIABLE_IS_SET $tra_proficiencies(~%parameter2%~)  BEGIN
		SPRINT proficiency $tra_proficiencies(~%parameter2%~)
		SPRINT theStatistic @12330002 // ~la compétence martiale %proficiency%~
		PATCH_IF type != 0 BEGIN
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
END

DEFINE_PATCH_MACRO ~opcode_target_233~ BEGIN
	LOCAL_SPRINT proficiency ~~

	LPM ~opcode_233_common~

	PATCH_IF VARIABLE_IS_SET $tra_proficiencies(~%parameter2%~)  BEGIN
		SPRINT proficiency $tra_proficiencies(~%parameter2%~)
		SPRINT theStatistic @12330002 // ~la compétence martiale %proficiency%~

		PATCH_IF type != 0 BEGIN
			PATCH_IF value > 0 BEGIN
	            SPRINT description @102286 // ~Augmente de %value% %theStatistic% %ofTheTarget%~
			END
			ELSE BEGIN
				SET value = ABS value
				SPRINT description @102285 // ~Réduit de %value% %theStatistic% %ofTheTarget%~
			END
		END
		ELSE BEGIN
			SPRINT description @102287 // ~Porte à %value% %theStatistic% %ofTheTarget%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_233~ BEGIN
	LPM ~opcode_self_probability_233~
END

DEFINE_PATCH_MACRO ~opcode_233_common~ BEGIN
	SET value = parameter1
	SET type = is_ee ? parameter2 BLSR 16 : 0
	SET parameter2 = parameter2 BAND 65535
	PATCH_IF type != 0 AND special != 0 BEGIN
		// Cas très très particulier
		PATCH_IF parameter2 == 90 BEGIN
			SET type = 0
		END
		ELSE BEGIN
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Be careful. Special should be equal to 0.~ END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_233_is_valid~ BEGIN
	LOCAL_SET stat = parameter2 BAND 65535
	LOCAL_SET type = is_ee ? parameter2 BLSR 16 : 0
	PATCH_IF stat < 89 OR stat > 134 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Type %stat% (89-134 expected)~ END
	END
	PATCH_IF stat == 99 AND type != 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Crash Warning: Opcode %opcode%: Invalid Mode %type% with Type %stat%~ END
	END
	PATCH_IF type != 0 AND parameter1 == 0 AND special == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No change detected. Proficiency %stat% += 0~ END
	END
	LPM ~opcode_233_common~

	PATCH_IF NOT VARIABLE_IS_SET $tra_proficiencies(~%parameter2%~) BEGIN
		SET isValid = 0
	END
END

/* ------------------------------- *
 * Spell Effect: Wing Buffet [235] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_235~ BEGIN
	LOCAL_SET strref = 12350000
	LPM ~opcode_235_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_235~ BEGIN
	LOCAL_SET strref = 12350004
	LPM ~opcode_235_common~
END

DEFINE_PATCH_MACRO ~opcode_target_235~ BEGIN
	LPM ~opcode_self_235~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_235~ BEGIN
	LPM ~opcode_self_probability_235~
END

DEFINE_PATCH_MACRO ~opcode_235_common~ BEGIN
	SET strref += parameter2 > 4 OR parameter2 < 1 ? 1 : parameter2
    LPF ~feets_to_meters~ INT_VAR range = parameter1 RET range = rangeToMeter END
	SPRINT description (AT strref)
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
	LOCAL_SET type   = parameter2
	LOCAL_SET amount = custom_int

	PATCH_IF type > 3 OR type < 0 BEGIN
		SET type = 0
	END
	SET strref += type

	PATCH_IF NOT ~%custom_str%~ STRING_EQUAL ~~ BEGIN
        SPRINT amount ~%custom_str%~
		SET strref += 10
    END
    ELSE PATCH_IF amount > 1 BEGIN
		SET strref += 10
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_236_group~ BEGIN
	LOCAL_SET amountMin = 0
	LOCAL_SET amountMax = 0
	LOCAL_SET type = 0

	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions_already_check~ BEGIN END
	CLEAR_ARRAY positions
	CLEAR_ARRAY positions_already_check
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET amountMin = probability == 100 ? (custom_int ? custom_int : 1) : 0
        SET amountMax = custom_int ? custom_int : 1
		SET type = parameter2
		PATCH_IF type > 3 OR type < 0 BEGIN
			SET type = 0
		END
		SET grouped = 0
		CLEAR_ARRAY positions
		PATCH_IF NOT VARIABLE_IS_SET $positions_already_check(~%position%~) BEGIN
			SET $positions(~%position%~) = 1
			SET $positions_already_check(~%position%~) = 1

			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_match_vars~
				SET match_type = match_parameter2
				PATCH_IF match_type > 3 OR match_type < 0 BEGIN
					SET match_type = 0
				END
				PATCH_IF match_type == type AND NOT VARIABLE_IS_SET $positions_already_check(~%match_position%~) BEGIN
					// On ne gère que les probability2 == 0 pour éviter de devoir gérer les cas complexes de regroupement par probaiblité ...
					LPM ~opcode_match_opcode_236_group~
					PATCH_IF match == 1 BEGIN
						SET amountMin += match_probability == 100 ? (match_custom_int ? match_custom_int : 1) : 0
				        SET amountMax += match_custom_int ? match_custom_int : 1
						SET $positions(~%match_position%~) = 1
						SET $positions_already_check(~%match_position%~) = 1
						SET grouped = 1
					END
				END
			END
		END
		PATCH_IF grouped == 1 BEGIN
			PATCH_PHP_EACH positions AS position => _ BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
			SPRINT custom_str @101130 // ~entre %amountMin% et %amountMax%~
			SET probability = 100
			SET probability1 = 100
			SET probability2 = 0
	        LPM ~add_opcode~
		END
	END
END

/* ------------------------- *
 * Death: Disintegrate [238] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_238~ BEGIN
	LPM ~opcode_target_238~
END

DEFINE_PATCH_MACRO ~opcode_target_238~ BEGIN
	SET death_type = 0x200
	SET description_strref = $death_to_strref(~%death_type%~)
	LPM ~opcode_55_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_238~ BEGIN
	LPM ~opcode_target_probability_238~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_238~ BEGIN
	SET death_type = 0x200
	SET description_strref = $death_to_strref(~%death_type%~)
	SET description_strref += 100
	LPM ~opcode_55_common~
END

DEFINE_PATCH_MACRO ~opcode_238_is_valid~ BEGIN
	LOCAL_SET death_type = 0x200
	LPM ~opcode_idscheck9_is_valid~
	PATCH_IF NOT VARIABLE_IS_SET $death_to_strref(~%death_type%~) BEGIN
		isValid = 0
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Mort a gerer : %death_type%~ END
	END
END

/* ---------------------------- *
 * Spell Effect: Farsight [239] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_239~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @12390001 // ~Permet d'observer une zone déjà reconnue~
	END
	ELSE BEGIN
		SPRINT description @12390002 // ~Permet d'observer une zone, même inconnue~
	END
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

DEFINE_PATCH_MACRO ~opcode_241_is_valid~ BEGIN
	LPM ~opcode_5_is_valid~
END

/* --------------------- *
 * Cure: Confusion [242] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_242~ BEGIN
	SPRINT description @12420001 // ~Dissipation de la confusion~
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
		// TODO: ? You can drain charges of a particular item if the resource field is used
		// Inexistant en 2.5.16
		PATCH_IF amount != 1 BEGIN
			SET strref += 1 // ~Draine %amount% charges aux objets magiques %ofTheTarget%~
		END
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
	END
	ELSE BEGIN
		SET strref += 2 // ~Draine les charges des objets magiques %ofTheTarget%~
		LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
		PATCH_IF amount == 0 BEGIN
			SPRINT exception @12430007 // ~excepté les armes~
			SPRINT description ~%description%, %exception%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_243_is_valid~ BEGIN
	PATCH_IF is_ee AND parameter1 <= 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No effect detected. 1 > Amount to Drain (%parameter1%)~ END
	END
	PATCH_IF NOT is_ee AND GAME_IS ~tob~ BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: This effect not works in ToB~ END
	END
END

/* ------------------------------- *
 * Spell: Drain Wizard Spell [244] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_244~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF amount == 1 BEGIN
		SPRINT description @12440001 // ~Draine 1 sort profane de la mémoire %ofTheTarget%~
	END
	ELSE BEGIN
		SPRINT description @12440002 // ~Draine %amount% sorts profanes de la mémoire %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_244~ BEGIN
	LOCAL_SET amount = parameter1

	PATCH_IF amount == 1 BEGIN
		SPRINT description @12440003 // ~de drainer 1 sort profane de la mémoire %ofTheTarget%~
	END
	ELSE BEGIN
		SPRINT description @12440004 // ~de drainer %amount% sorts profanes de la mémoire %ofTheTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_244~ BEGIN
	LPM ~opcode_self_244~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_244~ BEGIN
	LPM ~opcode_self_probability_244~
END

DEFINE_PATCH_MACRO ~opcode_243_is_valid~ BEGIN
	PATCH_IF parameter1 <= 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No effect detected. 1 > Amount to Drain (%parameter1%)~ END
	END
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
	SPRINT description @12460001 // ~Points de vie +15, dégâts +1, TAC0 +1~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_246~ BEGIN
	SPRINT description @12460002 // ~d'augmenter les caractéristiques %ofTheTarget% : Points de vie +15, dégâts +1, TAC0 +1~
END

DEFINE_PATCH_MACRO ~opcode_target_246~ BEGIN
	LPM ~opcode_target_246~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_246~ BEGIN
	LPM ~opcode_target_probability_246~
END

/* ------------------------------------------- *
 * Spell Effect: Attack Nearest Creature [247] *
 * ------------------------------------------- */
 DEFINE_PATCH_MACRO ~opcode_self_247~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		LPM ~opcode_self_3~
	END
	ELSE BEGIN
		SPRINT description @12470001 // ~Apaise %theTarget%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_247~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		LPM ~opcode_self_probability_3~
	END
	ELSE BEGIN
		SPRINT description @12470002 // d'apaiser %theTarget%
	END
END

DEFINE_PATCH_MACRO ~opcode_target_247~ BEGIN
	LPM ~opcode_self_247~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_247~ BEGIN
	LPM ~opcode_self_probability_247~
END

/* ---------------------------- *
 * Item: Set Melee Effect [248] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_248~ BEGIN
	SET strref = 12480001 // ~À chaque attaque de mêlée réussie~
	LPM ~opcode_248_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_248~ BEGIN
	SET strref = 12480005 // ~par attaque de mêlée réussie par %theTarget%~
	LPM ~opcode_248_common~
END

DEFINE_PATCH_MACRO ~opcode_target_248~ BEGIN
	SET strref = 12480003 // ~À chaque attaque de mêlée réussie par %theTarget%~
	LPM ~opcode_248_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_248~ BEGIN
	LPM ~opcode_self_probability_248~
END

DEFINE_PATCH_MACRO ~opcode_248_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		LPF ~get_opcode_position~
			INT_VAR opcode  = 249
	            match_isExternal   = isExternal
	            match_target       = target
		        match_power        = power
		        match_parameter3   = parameter3
		        match_parameter4   = parameter4
		        match_timingMode   = timingMode
		        match_resistance   = resistance
				match_duration     = duration
		        match_probability  = probability
		        match_probability1 = probability1
		        match_probability2 = probability2
		        match_diceCount    = diceCount
		        match_diceSides    = diceSides
		        match_saveType     = saveType
		        match_saveBonus    = saveBonus
		        match_special      = special
		        match_custom_int   = custom_int
			STR_VAR
				match_resref     = ~%resref%~
				match_resref2    = ~%resref2%~
				match_resref3    = ~%resref3%~
				match_custom_str = ~%custom_str%~
				match_macro      = ~opcode_match_except_parameter1_and_parameter2~
			RET opcodePosition = position
		END
		PATCH_IF opcodePosition >= 0 BEGIN
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
			LPF ~delete_opcode~
				INT_VAR opcode = 249 match_position = opcodePosition
				RET $opcodes(~249~) = count
				RET_ARRAY ~opcodes_249~ = opcodes_xx
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~249~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_249~
	        END

	        SET opcode = 524
	        LPM ~add_opcode~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_248_common~ BEGIN
	SET abilityType = AbilityType_Combat
	LPF ~get_res_description_248~ STR_VAR resref RET description saveAdded opcode END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF is_ee == 1 AND (parameter2 BAND 4) BEGIN // Attaque au poing
			SET strref += 1
		END

		LPF ~get_duration_value~ INT_VAR duration RET tmpDuration = value END

		PATCH_IF ignoreDuration == 0 AND NOT ~%tmpDuration%~ STRING_EQUAL ~~ BEGIN
			SPRINT frequency (AT strref)
			SPRINT condition ~%frequency% %tmpDuration%~
		END
		ELSE BEGIN
			SPRINT condition (AT strref)
		END
		SET ignoreDuration = 1
	END
END

DEFINE_PATCH_MACRO ~opcode_248_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

DEFINE_PATCH_FUNCTION ~get_res_description_248~ INT_VAR resetTarget = 0 STR_VAR resref = ~~ macro = ~~ RET description saveAdded ignoreDuration opcode BEGIN
	INNER_PATCH_FILE ~%resref%.eff~ BEGIN
		SET isExternal = 1
		SET diceSides248 = diceSides // levelMin
		SET diceCount248 = diceCount // levelMax

		LPM ~read_external_effect_vars~

		PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
			SET isValid = 1
			LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END
			// La restriction de niveau dépend de celle de l'opcode 248, excepté pour les opcodes qui n'en ont pas
			PATCH_IF NOT VARIABLE_IS_SET $opcode_without_level_restriction(~%opcode%~) AND (opcode != 218 OR is_ee == 0 OR parameter2 == 0) AND (opcode != 127 OR is_ee == 0) BEGIN
				SET diceSides = diceSides248
				SET diceCount = diceCount248
			END
			LPM ~opcode_is_valid~

			PATCH_IF isValid == 1 BEGIN
				LPF ~get_effect_description~ RET description saveAdded ignoreDuration END
			END
		END
	END
END

/* ----------------------------- *
 * Item: Set Ranged Effect [249] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_249~ BEGIN
	SET strref = 12490001 // ~À chaque attaque à distance réussie: %description%~
	LPM ~opcode_249_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_249~ BEGIN
	SET strref = 12490003 // ~par attaque à distance réussie par %theTarget%: %description%~
	LPM ~opcode_249_common~
END

DEFINE_PATCH_MACRO ~opcode_target_249~ BEGIN
	SET strref = 12490002 // ~À chaque attaque à distance réussie par %theTarget%: %description%~
	LPM ~opcode_249_common~
END

DEFINE_PATCH_MACRO ~opcode_249_common~ BEGIN
	SET abilityType = AbilityType_Combat
	LPF ~get_res_description_248~ STR_VAR resref RET description saveAdded opcode END

	PATCH_IF NOT ~%description%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_duration_value~ INT_VAR duration RET tmpDuration = value END

		PATCH_IF ignoreDuration == 0 AND NOT ~%tmpDuration%~ STRING_EQUAL ~~ BEGIN
			SPRINT frequency (AT strref)
			SPRINT condition ~%frequency% %tmpDuration%~
		END
		ELSE BEGIN
			SPRINT condition (AT strref)
		END
		SET ignoreDuration = 1
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_249~ BEGIN
	LPM ~opcode_self_probability_249~
END

DEFINE_PATCH_MACRO ~opcode_249_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

/* ----------------------------------- *
 * Spell Effect: Damage Modifier [250] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_250~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12500001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Dégâts minimum~
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

DEFINE_PATCH_MACRO ~opcode_250_is_valid~ BEGIN
	PATCH_IF parameter1 == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No change detected: Damage Modifier == %parameter1%~ END
	END
END

/* ------------------------------------------- *
 * Spell Effect: Change Bard Song Effect [251] *
 * ------------------------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_251~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12510001
END

DEFINE_PATCH_MACRO ~opcode_self_probability_251~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12510002
END

DEFINE_PATCH_MACRO ~opcode_target_251~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12510003
END

DEFINE_PATCH_MACRO ~opcode_target_probability_251~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12510004
END

DEFINE_PATCH_MACRO ~opcode_251_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

/* ---------------------------- *
 * Spell Effect: Set Trap [252] *
 * ---------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_252~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12520001
END

DEFINE_PATCH_MACRO ~opcode_self_probability_252~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12520002
END

DEFINE_PATCH_MACRO ~opcode_target_252~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12520003
END

DEFINE_PATCH_MACRO ~opcode_target_probability_252~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	SPRINT description @12520004
END

DEFINE_PATCH_MACRO ~opcode_252_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

/* ---------------------------------------- *
 * Item: Create Inventory Item (days) [255] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_255~ BEGIN
	// Conversion en jour
	SET duration *= 7200
	LPM ~opcode_self_122~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_255~ BEGIN
	SET duration *= 7200
	LPM ~opcode_self_probability_122~
END

DEFINE_PATCH_MACRO ~opcode_target_255~ BEGIN
	SET duration *= 7200
	LPM ~opcode_target_122~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_255~ BEGIN
	SET duration *= 7200
	LPM ~opcode_target_probability_122~
END

DEFINE_PATCH_MACRO ~opcode_255_is_valid~ BEGIN
	LPM ~opcode_122_is_valid~
END

/* ---------------------------- *
 * Protection: Spell Trap [259] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_259~ BEGIN
	LOCAL_SET strref = 12590001 // ~Absorbe jusqu'à %amount% niveaux de sorts de niveau %spellLevel% ou inférieur~
	LOCAL_SET strref_if_amount_0 = 110001
	LPM ~opcode_259_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_259~ BEGIN
	LOCAL_SET strref = 12590002 // ~d'absorber jusqu'à %amount% niveaux de sorts de niveau %spellLevel% ou inférieur~
	LOCAL_SET strref_if_amount_0 = 110003
	LPM ~opcode_259_common~
END

DEFINE_PATCH_MACRO ~opcode_259_common~ BEGIN
	LOCAL_SET amount = parameter1
	LOCAL_SET spellLevel = parameter2
	//TODO: Prise en compte de power, qui décrémente le bouclier d'une valeur qui peut être différente dui niveau de sort.
	LPF ~get_spell_school~ INT_VAR school = parameter2 opcode RET spellSchoolName END
	LPF ~side_spell~ INT_VAR strref strref_if_amount_0 amount RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_259_is_valid~ BEGIN
	LPM ~opcode_223_is_valid~
	PATCH_IF parameter2 > 9 OR parameter2 < 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Power Level: %parameter2% (0-9 expected)~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_259_group~ BEGIN
	LOCAL_SET maxLevel = 0
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions_already_check~ BEGIN END
	CLEAR_ARRAY positions
	CLEAR_ARRAY positions_already_check

	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		CLEAR_ARRAY positions
		SET $positions(~%position%~) = 1
		SET maxLevel = parameter2
		SET grouped = 0
		PATCH_IF probability == 100 AND NOT VARIABLE_IS_SET $positions_already_check(~%position%~) BEGIN
			SET $positions_already_check(~%position%~) = 1
			PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_match_vars~
				PATCH_IF NOT VARIABLE_IS_SET $positions_already_check(~%match_position%~) BEGIN
					LPM ~opcode_match_opcode_259_group~
					PATCH_IF match == 1 BEGIN
						PATCH_IF maxLevel < match_parameter2 BEGIN
							SET maxLevel = match_parameter2
						END
						SET $positions(~%match_position%~) = 1
						SET $positions_already_check(~%match_position%~) = 1
						SET grouped = 1
					END
				END
			END
		END
		PATCH_IF grouped == 1 BEGIN
			PATCH_PHP_EACH positions AS position => _ BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~%opcode%~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_%opcode%~
	        END
	        SET parameter2 = maxLevel
	        LPM ~add_opcode~
		END
	END
END

/* -------------------------------- *
 * Spell: Restore Lost Spells [261] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_261~ BEGIN
	SET strref = 12610001
	LPM ~opcode_261_common~
END

DEFINE_PATCH_MACRO ~opcode_target_261~ BEGIN
	SET strref = 12610002
	LPM ~opcode_261_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_261~ BEGIN
	SET strref = 12610003
	LPM ~opcode_261_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_261~ BEGIN
	SET strref = 12610004
	LPM ~opcode_261_common~
END

DEFINE_PATCH_MACRO ~opcode_261_common~ BEGIN
	LOCAL_SET spellLevel = parameter1
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT spellType @12610010 // ~profane~
		SET spellLevel = spellLevel > 9 ? 9 : spellLevel
	END
	ELSE PATCH_IF parameter2 == 1 BEGIN
		SPRINT spellType @12610011 // ~divin~
		SET spellLevel = spellLevel > 7 ? 7 : spellLevel
	END
	PATCH_IF spellLevel == 1 BEGIN
		SET strref += 4
	END

	LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
END

DEFINE_PATCH_MACRO ~opcode_261_is_valid~ BEGIN
	PATCH_IF parameter2 != 0 AND parameter2 != 1 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Spell Type: %parameter2% (0 or 1 expected)~ END
	END
	PATCH_IF parameter1 < 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Spell Level: %parameter1% (positive value expected)~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_261_group~ BEGIN
	LOCAL_SET initOpcode = opcode
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions_already_check~ BEGIN END
	CLEAR_ARRAY positions
	CLEAR_ARRAY positions_already_check

	PATCH_PHP_EACH EVAL ~opcodes_%initOpcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET newP1 = 0b0
		CLEAR_ARRAY positions
		SET $positions_already_check(~%position%~) = 1
		PATCH_PHP_EACH EVAL ~opcodes_%initOpcode%~ AS data => _ BEGIN
			LPM ~data_to_vars~
			PATCH_IF NOT VARIABLE_IS_SET $positions_already_check(~%position%~) BEGIN
				// On retire l'opcode de ceux à checker dans les futures itérations
				SET $positions_already_check(~%position%~) = 1
				// On ajoute l'opcode courant à ceux qui seront désactivés
				SET $positions(~%position%~) = initOpcode
				// P2 retiré
				LPF ~get_opcode_position~
					INT_VAR opcode
			            match_position     = position
			            match_target       = target
				        match_parameter2   = parameter2
				        match_power        = power
				        match_timingMode   = timingMode
				        match_resistance   = resistance
						match_duration     = duration
				        match_probability1 = probability1
				        match_probability2 = probability2
				        match_diceCount    = diceCount
				        match_diceSides    = diceSides
				        match_saveType     = saveType
				        match_saveBonus    = saveBonus
					STR_VAR match_macro = ~opcode_match_not_position_and_diceCount_and_diceSides_and_duration_and_parameter2_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_target_and_timingMode~
					RET opcodePosition = position
				END
				PATCH_IF opcodePosition >= 0 BEGIN
					SET $positions(~%opcodePosition%~) = initOpcode
					SET parameter = parameter1 - 1
					SET newP1 |= ~%BIT%parameter%%~
				END
			END
		END
		PATCH_IF newP1 > 0 BEGIN
			// Suppression des effets similaires
			PATCH_PHP_EACH positions AS position1 => opcode BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position1
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			// FIXME: à ce stade les données ne sont pas spécifiquement sauvegardées, reliquat du PATCH_PHP_EACH précédent
			// Fonctionnel dans les cas généraux
			SET opcode = 510
			SET parameter1 = newP1
			LPM ~add_opcode~
		END
	END
END

/* ------------------------ *
 * Stat: Visual Range [262] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_262_common~ BEGIN
	SET value = parameter2 == MOD_TYPE_flat AND parameter1 < 0 ? 0 : parameter1
	SET isNegative = value < 0 ? 1 : 0
	SET value = ABS value
	// parameter seems to be in the 0–15 interval
	SET value = value > 15 ? 15 : value
	// Each unit of visible range equals 2ft
	SET value *= 2
	LPF ~feets_to_meters~ INT_VAR range = value RET value = rangeToMeter END
END

DEFINE_PATCH_MACRO ~opcode_self_262~ BEGIN
	LPM ~opcode_262_common~
	PATCH_IF isNegative BEGIN
		SPRINT value ~-%value%~
	END
	ELSE BEGIN
		SPRINT value ~+%value%~
	END
	PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10010 // ~Passe à %value%~
	END
	SPRINT name @12620001 // ~Champ de vision~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_262~ BEGIN
	LPM ~opcode_262_common~
	SPRINT theStatistic @12620002 // ~le champ de vision~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF isNegative BEGIN
	        SPRINT description @102543 // ~de réduire %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
	        SPRINT description @102544 // ~d'augmenter %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102545 // ~de passer %theStatistic% %ofTheTarget% à %value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_262~ BEGIN
	LPM ~opcode_262_common~
	SPRINT theStatistic @12620002 // ~le champ de vision~

	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
        PATCH_IF isNegative BEGIN
	        SPRINT description @102285 // ~Réduit %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
	        SPRINT description @102286 // ~Augmente %theStatistic% %ofTheTarget% de %value%~
        END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT description @102287 // ~Passe %theStatistic% %ofTheTarget% à %value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_262~ BEGIN
	LPM ~opcode_self_probability_262~
END

DEFINE_PATCH_MACRO ~opcode_262_is_valid~ BEGIN
	PATCH_IF parameter2 != MOD_TYPE_cumulative AND parameter2 != MOD_TYPE_flat BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Type: %parameter2% (0 or 1 expected)~ END
	END
	PATCH_IF parameter2 == MOD_TYPE_cumulative AND parameter1 == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No change detected: Visual range += 0~ END
	END
END

/* -------------------- *
 * Stat: Backstab [263] *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_263~ BEGIN
	// Spécificité de l'opcode
	SET timingMode = timingMode == TIMING_permanent ? TIMING_permanent_after_death : timingMode
	LPF ~opcode_mod~ INT_VAR strref = 12630001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Multiplicateur d'attaque sournoise~
END

DEFINE_PATCH_MACRO ~opcode_target_263~ BEGIN
	SET timingMode = timingMode == TIMING_permanent ? TIMING_permanent_after_death : timingMode
	LPF ~opcode_target~ INT_VAR strref = 12630002 RET description END // ~le multiplicateur d'attaque sournoise~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_263~ BEGIN
	SET timingMode = timingMode == TIMING_permanent ? TIMING_permanent_after_death : timingMode
	LPF ~opcode_probability~ INT_VAR strref = 12630002 RET description END // ~le multiplicateur d'attaque sournoise~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_263~ BEGIN
	LPM ~opcode_self_probability_263~
END

DEFINE_PATCH_MACRO ~opcode_263_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ----------------------------------------- *
 * Spell Effect: Drop Weapons in Panic [264] *
 * ----------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_264~ BEGIN
	LPM ~opcode_264_common~
	SPRINT description @12640001
END

DEFINE_PATCH_MACRO ~opcode_target_264~ BEGIN
	LPM ~opcode_264_common~
	SPRINT description @12640002
END

DEFINE_PATCH_MACRO ~opcode_self_probability_264~ BEGIN
	LPM ~opcode_264_common~
	SPRINT description @12640003
END

DEFINE_PATCH_MACRO ~opcode_target_probability_264~ BEGIN
	LPM ~opcode_264_common~
	SPRINT description @12640004
END

DEFINE_PATCH_MACRO ~opcode_264_common~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT objectType @12640011
	END
	ELSE BEGIN
		SPRINT objectType @12640010
	END
END

/* ----------------------------------------- *
 * Spell: Remove Protection from Spell [266] *
 * ----------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_266~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12660001 // ~Lève l'immunité au sort %spellName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_266~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12660003 // ~de lever l'immunité au sort %spellName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_266~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12660002 // ~Lève l'immunité %ofTheTarget% au sort %spellName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_266~ BEGIN
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SPRINT description @12660004 // ~de lever l'immunité au sort %spellName%~
	END
END

DEFINE_PATCH_MACRO ~opcode_266_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
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

/* -------------------------- *
 * Cure: Unpause Target [270] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_270~ BEGIN
	LPM ~opcode_target_270~ // ~Libère des combats mentaux~
END

DEFINE_PATCH_MACRO ~opcode_target_270~ BEGIN
	SPRINT description @12700001 // ~Libère des combats mentaux~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_270~ BEGIN
	LPM ~opcode_target_probability_270~ // ~de libérer des combats mentaux~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_270~ BEGIN
	SPRINT description @12700002 // ~de libérer des combats mentaux~
END

/* -------------------------------- *
 * Spell: Apply Repeating EFF [272] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_272~ BEGIN
	SET strref = 12720001
	LPM ~opcode_272_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_272~ BEGIN
	LPM ~opcode_self_272~
END

DEFINE_PATCH_MACRO ~opcode_target_272~ BEGIN
	LPM ~opcode_self_272~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_272~ BEGIN
	LPM ~opcode_self_272~
END

DEFINE_PATCH_MACRO ~opcode_272_common~ BEGIN
	LPM ~opcode_272_condition~
	LPF ~get_res_description~ INT_VAR ignoreDuration = (frequency == 6 AND abilityType == AbilityType_Equipped) STR_VAR resref RET description saveAdded opcode END
	PATCH_IF ~%description%~ STRING_EQUAL ~~ BEGIN
		SPRINT condition ~~
	END
	SET ignoreDuration = 1
END

DEFINE_PATCH_MACRO ~opcode_272_is_valid~ BEGIN
	PATCH_IF parameter2 < 0 OR parameter2 == 1 OR parameter2 > 4 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Invalid Type: 0-2-3-4 expected.~ END
	END
	PATCH_IF NOT isExternal AND parameter2 == 4 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Type 4 can only be used in external eff files.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_272_condition~ BEGIN
	SET amount = 0
	SET frequency = 1
	SET p4IsActive = isExternal AND parameter4 != 0 AND is_ee
	SET type = parameter2

	// Compliqué de faire une phrase simple
	PATCH_IF (type == 0 AND (parameter1 != 0 OR p4IsActive)) BEGIN
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
	END
	PATCH_IF frequency < 1 BEGIN
		SET frequency = 1
	END

	LPF ~get_str_duration~ INT_VAR duration = frequency RET strDuration END

	PATCH_IF amount == 1 BEGIN
		PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^1 ~ == 0 BEGIN
			PATCH_IF frequency == 6 AND abilityType == AbilityType_Equipped BEGIN
                SET strref = 12320000 // ~~
                SET ignoreDuration = 1
            END
            ELSE BEGIN
				INNER_PATCH_SAVE strDuration ~%strDuration%~ BEGIN
					REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^1 ~ ~~
				END
				SET strref = 12720010 // ~À chaque %strDuration%~
			END
		END
		ELSE BEGIN
			// FIXME: données en français et genrées => traduction impossible
			PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ heure~ == 0 OR ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ seconde~ == 0 BEGIN
				SET strref = 12720011 // ~Toutes les %strDuration%~
			END
			ELSE BEGIN
				SET strref = 12720012 // ~Tous les %strDuration%~
			END
		END
	END
	ELSE BEGIN
		PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^1 ~ == 0 BEGIN
			INNER_PATCH_SAVE strDuration ~%strDuration%~ BEGIN
				REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^1 ~ ~~
			END
			SET strref = 12720013 // ~%amount% fois par %strDuration%~
		END
		ELSE BEGIN
			// FIXME: données en français et genrées => traduction impossible
			PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ heure~ == 0 OR ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ seconde~ == 0 BEGIN
				SET strref = 12720014 // ~%amount% fois toutes les %strDuration%~
			END
			ELSE BEGIN
				SET strref = 12720015 // ~%amount% fois tous les %strDuration%~
			END
		END
	END

	LPF ~get_duration_value~ INT_VAR duration RET tmpDuration = value END

	PATCH_IF ignoreDuration == 0 AND NOT ~%tmpDuration%~ STRING_EQUAL ~~ BEGIN
		SPRINT strFrequency (AT strref)
		SPRINT condition ~%strFrequency% %tmpDuration%~
	END
	ELSE BEGIN
		SPRINT condition (AT strref)
	END
END

/* ----------------------------------------------------- *
 * Remove: Specific Area Effect(Zone of Sweet Air) [273] *
 * ----------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_273~ BEGIN
	SET strref = 12730001 // ~Zone d'air pur~
	LPM ~opcode_273_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_273~ BEGIN
	SET strref = 12730003 // ~de lancer Zone d'air pur~
	LPM ~opcode_273_common~
END

DEFINE_PATCH_MACRO ~opcode_target_273~ BEGIN
	SET strref = 12730002 // ~Lance Zone d'air pur sur %theTarget%~
	LPM ~opcode_273_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_273~ BEGIN
	SET strref = 12730004 // ~de lancer Zone d'air pur sur %theTarget%~
	LPM ~opcode_273_common~
END

DEFINE_PATCH_MACRO ~opcode_273_common~ BEGIN
	PATCH_IF NOT is_ee OR ~%resref%~ STRING_EQUAL ~~ OR ~%resref%~ STRING_EQUAL_CASE ~CLEARAIR~ BEGIN
		SPRINT description (AT strref)
	END
	ELSE BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : %resref%.2DA a gerer.~ END
		SPRINT description ~~
	END
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

DEFINE_PATCH_MACRO ~opcode_275_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
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

DEFINE_PATCH_MACRO ~opcode_276_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
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

DEFINE_PATCH_MACRO ~opcode_277_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* --------------------------- *
 * Stat: To Hit Modifier [278] *
 * --------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_278~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12780001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Chances de toucher~
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

DEFINE_PATCH_MACRO ~opcode_278_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------ *
 * Button: Enable Button [279] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_279~ BEGIN
	LOCAL_SET strref = 11440001 + parameter2
	SPRINT action @12790020 // ~Permet~
	LPM ~opcode_144_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_279~ BEGIN
	LOCAL_SET strref = 11440001 + parameter2
	SPRINT action @12790021 // ~de permettre~
	LPM ~opcode_144_common~
END

DEFINE_PATCH_MACRO ~opcode_target_279~ BEGIN
	LOCAL_SET strref = 11440021 + parameter2
	SPRINT action @12790040 // ~Permet %toTheTarget%~
	LPM ~opcode_144_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_279~ BEGIN
	LOCAL_SET strref = 11440021 + parameter2
	SPRINT action @12790041 // ~de permettre %toTheTarget%~
	LPM ~opcode_144_common~
END

DEFINE_PATCH_MACRO ~opcode_279_is_valid~ BEGIN
	LPM ~opcode_144_is_valid~
END

/* ------------------------------ *
 * Spell Effect: Wild Magic [280] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_280~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @12800001 // ~Le prochain sort lancé par %theTarget% déclenche automatiquement un hiatus entropique~
	END
	ELSE PATCH_IF parameter2 > 1 BEGIN
		SPRINT description @12800002 // ~Les sorts lancés par %theTarget% déclenchent automatiquement un hiatus entropique~
	END
	ELSE BEGIN
		SPRINT description @12800003 // ~Dissipe les effets qui forcent le déclenchement des hiatus entropiques~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_280~ BEGIN
	PATCH_IF parameter2 == 1 BEGIN
		SPRINT description @12800004 // ~que le prochain sort lancé par %theTarget% déclenche un hiatus entropique~
	END
	ELSE PATCH_IF parameter2 > 1 BEGIN
		SPRINT description @12800005 // ~que les sorts lancés par %theTarget% déclenchent un hiatus entropique~
	END
	ELSE BEGIN
		SPRINT description @12800006 // ~de dissiper les effets qui forcent le déclenchement des hiatus entropiques~
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
	LPF ~opcode_mod~ INT_VAR strref = 12810001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Modificateur des hiatus entropiques~
END

DEFINE_PATCH_MACRO ~opcode_target_281~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 12810002 RET description END // ~le modificateur des hiatus entropiques~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_281~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 12810002 RET description END // ~le modificateur des hiatus entropiques~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_281~ BEGIN
	LPM ~opcode_self_probability_281~
END

DEFINE_PATCH_MACRO ~opcode_281_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* -------------------------------------- *
 * Script: Scripting State Modifier [282] *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_282_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET currentP2 = parameter2
		PATCH_IF currentP2 >= 10 AND currentP2 <= 12 OR currentP2 == 14 OR currentP2 == 15 BEGIN
			SET opcode = parameter2 + 274
			SET parameter2 = MOD_TYPE_flat
			LPM ~add_opcode~
		END
		SET currentP2 += is_ee ? 0 : 1
		PATCH_IF currentP2 == 20 BEGIN // IMMUNITY_TO_BACKSTAB
			SET opcode = 292
			SET parameter2 = parameter1
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 31 BEGIN // NO_PERMANENT_DEATH
			SET opcode = 295
			SET parameter2 = parameter1
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 32 BEGIN // IMMUNE_TO_TURN_UNDEAD
			SET opcode = 297
			SET parameter2 = parameter1
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 33 BEGIN // CHAOS_SHIELD
			SET opcode = 299
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 34 BEGIN // NPC_BUMP
			SET opcode = 300
			SET parameter2 = parameter1
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 35 BEGIN // USE_ANY_ITEM
			SET opcode = 302
			SET parameter2 = parameter1
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 36 BEGIN // ASSASSINATE
			SET opcode = 303
			SET parameter2 = parameter1
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 37 BEGIN // SEX_CHANGED
			SET opcode = 71
			SET parameter2 = MOD_TYPE_flat
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 38 BEGIN // SPELL_FAILURE_INNATE
			SET opcode = 60
			SET parameter2 = 2
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 41 BEGIN // IMMUNE_TO_TIME_STOP
			SET opcode = 310
			SET parameter2 = parameter1
			LPM ~add_opcode~
		END
		ELSE PATCH_IF currentP2 == 43 BEGIN // STONESKINSGOLEM
			SET opcode = 314
			LPM ~add_opcode~
		END
	END
	SET opcode = 282
	CLEAR_ARRAY ~opcodes_%opcode%~
	SET $opcodes(~%opcode%~) = 0
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

DEFINE_PATCH_MACRO ~opcode_283_is_valid~ BEGIN
	LPM ~opcode_177_is_valid~
END

/* -------------------------------- *
 * Stat: Melee THAC0 Modifier [284] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_284~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12840001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~TAC0 des armes de mêlée~
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

DEFINE_PATCH_MACRO ~opcode_284_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ---------------------------------------- *
 * Stat: Melee Weapon Damage Modifier [285] *
 * ---------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_285~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12850001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Dégâts des armes de mêlée~
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

DEFINE_PATCH_MACRO ~opcode_284_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------------------ *
 * Stat: Missile Weapon Damage Modifier [286] *
 * ------------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_286~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12860001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Dégâts des armes à projectiles~
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

DEFINE_PATCH_MACRO ~opcode_286_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------- *
 * Stat: Fist THAC0 Modifier [288] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_288~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12880001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~TAC0 des poings~
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

DEFINE_PATCH_MACRO ~opcode_288_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* -------------------------------- *
 * Stat: Fist Damage Modifier [289] *
 * -------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_289~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 12890001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Dégâts des poings~
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

DEFINE_PATCH_MACRO ~opcode_289_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* -------------------------- *
 * Protection: Backstab [292] *
 * -------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_292~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12920001 // ~Immunité aux attaques sournoises~
	END
	ELSE BEGIN
		SPRINT description @12920011 // ~Sensible aux attaques sournoises~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_292~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12920003 // ~de résister aux attaques sournoises~
	END
	ELSE BEGIN
		SPRINT description @12920013 // ~de rendre sensible aux attaques sournoises~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_292~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12920002 // ~Immunise %theTarget% aux attaques sournoises~
	END
	ELSE BEGIN
		SPRINT description @12920012 // ~rend %theTarget% sensible aux attaques sournoises~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_292~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12920004 // ~d'immuniser %theTarget% aux attaques sournoises~
	END
	ELSE BEGIN
		SPRINT description @12920014 // ~de rendre %theTarget% sensible aux attaques sournoises~
	END
END

/* --------------------------------------- *
 * Graphics: Disable Permanent Death [295] *
 * --------------------------------------- */
 DEFINE_PATCH_MACRO ~opcode_self_295~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12950001 // ~Protection contre la mort permanente~
	END
	ELSE BEGIN
		SPRINT description @12950011 // ~Dissipation de la protection contre la mort permanente~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_295~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12950003 // ~d'être protégé contre la mort permanente~
	END
	ELSE BEGIN
		SPRINT description @12950013 // ~de rendre sensible à la mort permanente~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_295~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12950002 // ~Protège %theTarget% contre la mort permanente~
	END
	ELSE BEGIN
		SPRINT description @12950012 // ~rend %theTarget% sensible à la mort permanente~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_295~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT description @12950004 // ~de protéger %theTarget% contre la mort permanente~
	END
	ELSE BEGIN
		SPRINT description @12950014 // ~de rendre %theTarget% sensible à la mort permanente~
	END
END

/* --------------------------------- *
 *  Spell Effect: Chaos Shield [299] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_299~ BEGIN
	LOCAL_SET amount = parameter1
	SPRINT description @12990001 // ~Bloque %amount% hiatus entropiques~
END

DEFINE_PATCH_MACRO ~opcode_target_299~ BEGIN
	LOCAL_SET amount = parameter1
	SPRINT description @12990002 // ~Bloque %amount% hiatus entropiques %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_299~ BEGIN
	LOCAL_SET amount = parameter1
	SPRINT description @12990003 // ~de bloquer %amount% hiatus entropiques~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_299~ BEGIN
	LOCAL_SET amount = parameter1
	SPRINT description @12990004 // ~de bloquer %amount% hiatus entropiques %ofTheTarget%~
END

/* -------------- *
 * NPC Bump [300] *
 * -------------- */
// TODO: à vérifier
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
// TODO: tester les valeurs : special > 3

DEFINE_PATCH_MACRO ~opcode_self_301~ BEGIN
	PATCH_IF is_ee == 1 AND parameter2 != 0 BEGIN
		SPRINT name @13010002 // // ~Chance de coup critique avec cette arme~
	END
	ELSE BEGIN
		SPRINT name @13010001 // ~Chance de coup critique~
	END
	LPM ~opcode_301_common~
END

DEFINE_PATCH_MACRO ~opcode_301_common~ BEGIN
	LOCAL_SET value = 5 * parameter1
	LPF ~signed_value~ INT_VAR value RET value END
	SPRINT value @10002 // ~%value% %~
	PATCH_IF is_ee == 1 AND parameter2 != 0 BEGIN
		//TODO : restriction du type d'arme si parameter2 != 0 (cela a-t-il un sens ?)
		PATCH_IF isExternal AND parameter3 != 0 BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Condition %parameter2% et Weapon Category %parameter3% non gere~ END
		END
	END
	PATCH_IF is_ee AND special >= 1 BEGIN
		SET strref = 13010010 + special // ~en mêlée~
		LPF ~getTranslation~ INT_VAR strref opcode RET descriptionAdd = string END
		TEXT_SPRINT name ~%name% %descriptionAdd%~
	END
	PATCH_IF is_ee AND parameter2 == 0 AND isExternal AND parameter3 != 0 BEGIN
		SET strref = 230000 + parameter3
		SPRINT weaponType (AT strref)
		SPRINT strref @13010020 // ~avec des %weaponType%~
		TEXT_SPRINT name ~%name% %strref%~
	END
	SPRINT description @100001 // ~%name%%colon%%value%~
END

/* ---------------------------- *
 * Item: Can Use Any Item [302] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_302~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @13020001 // ~Bloque la capacité d'utiliser n'importe quel objet~
	END
	ELSE BEGIN
		SPRINT description @13020002 // ~Permet d'utiliser n'importe quel objet (si les caractéristiques sont suffisantes)~
	END
END

/* -------------------------------------- *
 * Spell Effect: Backstab Every Hit [303] *
 * -------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_303~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @13030001 // ~Bloque la capacité à infliger des dégâts sournois à chaque attaque~
	END
	ELSE BEGIN
		SPRINT description @13030011 // ~Transforme toute attaque portée en attaque sournoise (si l'arme équipée l'autorise)~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_303~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @13030003 // ~de bloquer la capacité %ofTheTarget% à infliger des dégâts sournois à chaque attaque~
	END
	ELSE BEGIN
		SPRINT description @13030013 // ~de transformer toute attaque portée par %theTarget% en attaque sournoise (si l'arme équipée l'autorise)~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_303~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @13030002 // ~Bloque la capacité %ofTheTarget% à infliger des dégâts sournois à chaque attaque~
	END
	ELSE BEGIN
		SPRINT description @13030012 // ~Transforme toute attaque portée par %theTarget% en attaque sournoise (si l'arme équipée l'autorise)~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_303~ BEGIN
	LPM ~opcode_self_probability_303~ // ~de transformer toute attaque portée par %theTarget% en attaque sournoise (si l'arme équipée l'autorise)~
END

/* --------------------- *
 * Mass Raise Dead [304] *
 * --------------------- */
DEFINE_PATCH_MACRO ~opcode_self_304~ BEGIN
	LPM ~opcode_target_304~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_304~ BEGIN
	LPM ~opcode_target_probability_304~
END

DEFINE_PATCH_MACRO ~opcode_target_304~ BEGIN
	// TODO: rendre maintenable
	SPRINT theTarget   @102473 // ~les membres du groupe~
	SPRINT ofTheTarget @101088 // ~des membres du groupe~
	SPRINT toTheTarget @101182 // ~aux membres du groupe~
	LPM ~opcode_target_32~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_304~ BEGIN
	SPRINT theTarget   @102473 // ~les membres du groupe~
	SPRINT ofTheTarget @101088 // ~des membres du groupe~
	SPRINT toTheTarget @101182 // ~aux membres du groupe~
	LPM ~opcode_target_probability_32~
END

/* ------------------------------------- *
 * Stat: THAC0 Modifier (Off-Hand) [305] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_305~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 13050001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~TAC0 de la main secondaire~
END

DEFINE_PATCH_MACRO ~opcode_target_305~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 13050002 RET description END // ~le TAC0 de la main secondaire~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_305~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 13050002 RET description END // ~le TAC0 de la main secondaire~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_305~ BEGIN
	LPM ~opcode_self_probability_305~
END

DEFINE_PATCH_MACRO ~opcode_305_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------------ *
 * Stat: THAC0 Modifier (On-Hand) [306] *
 * ------------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_306~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 13060001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~TAC0 de la main principale~
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

DEFINE_PATCH_MACRO ~opcode_306_is_valid~ BEGIN
	LPM ~opcode_modstat2_is_valid~
END

/* ------------------------------- *
 * Protection: from Timestop [310] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_310~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @13100001 // ~Bloque l'immunité à l'arrêt du temps~
	END
	ELSE BEGIN
		SPRINT description @13100011 // ~Immunité à l'arrêt du temps~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_310~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @13100003 // ~de rendre sensible %theTarget% à l'arrêt du temps~
	END
	ELSE BEGIN
		SPRINT description @13100013 // ~d'immuniser %theTarget% à l'arrêt du temps~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_310~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT description @13100002 // ~Rendre sensible %theTarget% à l'arrêt du temps~
	END
	ELSE BEGIN
		SPRINT description @13100012 // ~Immunise %theTarget% à l'arrêt du temps~
	END
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

/* ----------------------------- *
 *  Spell: Golem Stoneskin [314] *
 * ----------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_314~ BEGIN
	LPM ~opcode_self_218~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_314~ BEGIN
	LPM ~opcode_self_probability_218~
END

DEFINE_PATCH_MACRO ~opcode_target_314~ BEGIN
	LPM ~opcode_target_218~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_314~ BEGIN
	LPM ~opcode_self_probability_314~
END

/* ------------------------- *
 * Spell: Magical Rest [316] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_316~ BEGIN
	SPRINT description @13160002 // ~Repose %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_316~ BEGIN
	SPRINT description @13160001 // ~de reposer %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_316~ BEGIN
	LPM ~opcode_self_316~ // ~Repose %theTarget%~
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
	// 13210001, parfois la capacité de charge cible le porteur et la cible, utile d'expliciter la cible ?
/*
	LOCAL_SET strref = 13210004
	LPM ~opcode_321_common~
*/
END

DEFINE_PATCH_MACRO ~opcode_self_probability_321~ BEGIN
/*
	LOCAL_SET strref = 13210007
	LPM ~opcode_321_common~
*/
END

DEFINE_PATCH_MACRO ~opcode_target_321~ BEGIN
/*
	LOCAL_SET strref = 13210004
	LPM ~opcode_321_common~
*/
END

DEFINE_PATCH_MACRO ~opcode_target_probability_321~ BEGIN
	LPM ~opcode_self_probability_321~
END

DEFINE_PATCH_MACRO ~opcode_321_common~ BEGIN
	PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ AND
			(timingMode != TIMING_duration OR duration != 0) BEGIN // N'empêche rien sans durée
		SET ignoreDuration = 1
		SET forceSort = 1
		SET sort = 0
		SPRINT description @13210020 // ~Les effets ne se cumulent pas~
	END
	ELSE BEGIN
		PATCH_IF timingMode != TIMING_duration OR duration != 0 BEGIN // Dissipe & protège
			SET strref += 10
		END
		LPF ~get_spell_name~ INT_VAR showWarning = 0 STR_VAR file = EVAL ~%resref%~ RET spellName END
		LPF ~get_item_name~ INT_VAR showWarning = 0 STR_VAR file = EVAL ~%resref%~ RET itemName END
		TO_LOWER resref

		SPRINT effectType @13210100 // ~effets~
		PATCH_IF parameter2 == 1 BEGIN
			SPRINT effectType @13210101 // ~capacités d'équipement~
		END
		ELSE PATCH_IF parameter2 == 2 BEGIN
			SPRINT effectType @13210102 // ~effets non équipés~
		END

		PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
			SET strref += 2
			LPF ~getTranslation~ INT_VAR strref = strref opcode RET description = string END // ~Dissipe les %effectType% du sort %spellName% et de l'objet %itemName% sur %theTarget%~
		END
		ELSE PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
			SET strref += 1
			LPF ~getTranslation~ INT_VAR strref = strref opcode RET description = string END // ~Dissipe les %effectType% de l'objet %itemName% sur %theTarget%~
		END
		ELSE PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
			LPF ~getTranslation~ INT_VAR strref = strref opcode RET description = string END // ~Dissipe les %effectType% du sort %spellName% sur %theTarget%~
		END
		// distinguer les cas où ~%spellName%~ == ~~ parce qu'il n'existe pas ou parce qu'il n'a pas de nom
		ELSE PATCH_IF NOT FILE_EXISTS_IN_GAME ~%resref%.spl~ AND NOT FILE_EXISTS_IN_GAME ~%resref%.itm~ BEGIN
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : no %resref%.spl or %resref%.itm found~ END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_321_is_valid~ BEGIN
	// Leaving the resource field empty will remove any effect on the creature without a parent resource
	PATCH_IF ~%resref%~ STRING_EQUAL ~~ BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Resource key is empty : non gere.~ END
	END
END

/* ----------------------------- *
 * Stat: Turn Undead Level [323] *
 * ----------------------------- */

// TODO : à vérifier : pas de MOD_TYPE_percent dans 2.5.16
// FIXME: special != 0 : P1 = P1 + niveau de la classe la plus élevée
DEFINE_PATCH_MACRO ~opcode_self_323~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 13230001 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Niveau de repousser les morts-vivants~
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

DEFINE_PATCH_MACRO ~opcode_323_is_valid~ BEGIN
	LPM ~opcode_modstat1_is_valid~
	PATCH_IF parameter2 == MOD_TYPE_cumulative AND parameter1 == 0 AND special == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: No change detected: Value = Value + 0.~ END
	END
END

/* -------------------------------------------------- *
 * Protection: Immunity to Resource and Message [324] *
 * -------------------------------------------------- */
 DEFINE_PATCH_MACRO ~opcode_self_324~ BEGIN
	LOCAL_SET strref = 13240000
	LOCAL_SET descriptionStrref = 13240901 // ~Immunité au sort %spellName%~
	LPM ~opcode_common_324~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_324~ BEGIN
	LOCAL_SET strref = 13240500
	LOCAL_SET descriptionStrref = 13240903 // ~d'immuniser %theTarget% au sort %spellName%~
	LPM ~opcode_common_324~
END

DEFINE_PATCH_MACRO ~opcode_target_324~ BEGIN
	LOCAL_SET strref = 13240000
	LOCAL_SET descriptionStrref = 13240902 // ~Immunise %theTarget% au sort %spellName%~
	LPM ~opcode_common_324~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_324~ BEGIN
	LPM ~opcode_self_probability_324~
END

DEFINE_PATCH_MACRO ~opcode_common_324~ BEGIN
	LOCAL_SET value = parameter1
	LOCAL_SET statType = parameter2
	LOCAL_SET idsId = 0

	PATCH_IF NOT ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ AND parameter2 == 0 BEGIN
		LPM ~opcode_324_against_who~
		PATCH_IF isValid BEGIN
			SET strref = descriptionStrref
			LPF ~getTranslation~ INT_VAR strref opcode RET description = string END
		END
	END
	ELSE BEGIN
		SET ignoreDuration = 1
		PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ BEGIN
			PATCH_IF statType >= 102 AND statType <= 109 BEGIN // IDS
				SET idsId = statType - 100
				SET strref = strref + 301 // ~Inefficace contre les %creatureType%~
				LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%idsId%~ RET creatureType = idName END
			END
			ELSE PATCH_IF statType == 76 OR statType == 110 OR statType == 111 BEGIN // SplState
				SET statType = statType == 76 ? 110 : statType
				SET oldStrref = strref + statType
				SET strref = 420000 + parameter1
				LPF ~get_splstate_name~ INT_VAR strref opcode splstate = parameter1 RET splstateName END
				SET strref = oldStrref
			END
			ELSE PATCH_IF statType >= 112 AND statType <= 118 BEGIN // !IDS
				SET idsId = statType - 110
				SET strref = strref + 302 // ~Effectif contre les %creatureType%~
				LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%idsId%~ RET creatureType = idName END
			END
			ELSE PATCH_IF statType == 138 OR statType == 139 BEGIN // STATE
				LPF ~get_states_str~ INT_VAR state = parameter1 RET descriptionState = descriptionState END
				SET strref = strref + statType
			END
			ELSE BEGIN
				SET strref = strref + statType
			END
			LPF ~getTranslation~ INT_VAR strref opcode RET description = string exist END
			PATCH_IF exist == 0 BEGIN
				SPRINT description ~~
			END
		END
		ELSE BEGIN
			LPM ~opcode_324_against_who~
			PATCH_IF isValid BEGIN
				LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Immunité à %againstWho% différente de l'objet : %resref%~ END
			END
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_324_against_who~ BEGIN
	LPF ~get_spell_name~ INT_VAR showWarning = 0 STR_VAR file = EVAL ~%resref%~ RET spellName END
	LPF ~get_item_name~ INT_VAR showWarning = 0 STR_VAR file = EVAL ~%resref%~ RET itemName END
	SET againstWhoStrref = 13240911
	SET isValid = 1

	PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		LPF ~getTranslation~ INT_VAR strref = strref opcode RET description = string END // ~contre le sort %spellName% et l'objet %itemName%~
	END
	ELSE PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
		SET againstWhoStrref += 1
		LPF ~getTranslation~ INT_VAR strref = strref opcode RET description = string END // ~contre le sort %spellName%~
	END
	ELSE PATCH_IF NOT ~%itemName%~ STRING_EQUAL ~~ BEGIN
		SET againstWhoStrref += 2
		LPF ~getTranslation~ INT_VAR strref = strref opcode RET description = string END // ~contre l'objet %itemName%~
	END
	// distinguer les cas où ~%spellName%~ == ~~ parce qu'il n'existe pas ou parce qu'il n'a pas de nom
	ELSE PATCH_IF NOT FILE_EXISTS_IN_GAME ~%resref%.spl~ AND NOT FILE_EXISTS_IN_GAME ~%resref%.itm~ BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : no %resref%.spl or %resref%.itm found~ END
		SET isValid = 0
	END
	ELSE BEGIN
		SET isValid = 0
	END
	SPRINT againstWho (AT againstWhoStrref)
END

DEFINE_PATCH_MACRO ~opcode_324_is_valid~ BEGIN
	PATCH_IF NOT ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ AND timingMode == TIMING_duration AND duration == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : no effect : duration 0~ END
	END
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcode_324_effective~ BEGIN
	2   => ~203004~ // ~morts-vivants~
	6   => ~203001~ // ~humanoïdes~
	8   => ~203002~ // ~animaux~
	10  => ~204145~ // ~élémentaires~
	12  => ~204164~ // ~myconides~
	14  => ~13241013~ // ~créatures gigantesques~
	16  => ~204002~ // ~elfes~
	18  => ~204130~ // ~ombres des roches~
	20  => ~204003~ // ~demi-elfes~
	22  => ~203001 204145~ // ~humanoïdes~ ~animaux~
	24  => ~13241023~ // ~créatures aveuglées~
	28  => ~204144~ // ~golems~
	30  => ~204171~ // ~minotaures~
	32  => ~203004 204164~ // ~morts-vivants~ ~myconides~
	40  => ~205006~ // ~paladins~
	46  => ~204152~ // ~githyankis~
	48  => ~204144 203004 204164~ // ~golems~ ~morts-vivants~ ~myconides~
	50  => ~202028~ // ~créatures alliées~
	52  => ~202200~ // ~créatures hostiles~
	56  => ~203004 204144~ // ~morts-vivants~ ~golems~
	65  => ~204143~ // ~orques~
	67  => ~13241066~ // ~créatures sourdes~
	69  => ~13241068~ // ~créatures sous l'effet d'un toucher de la goule~
	75  => ~13241075~ // ~créatures vivantes~
	86  => ~204101~ // ~ankhegs~
	88  => ~204150~ // ~liches~
	92  => ~13241091~ // ~créatures paniquées~
	119 => ~204003~ // ~demi-elfes~
	139 => ~13241138~ // ~créatures %descriptionState%~
	143 => ~13241142~ // ~créatures invisibles~
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcode_324_not_effective~ BEGIN
	1   => ~203004~ // ~morts-vivants~
	3   => ~13241003~ // ~créatures immunisées au feu~
	4   => ~13241004~ // ~créatures sensibles au feu~
	5   => ~203001~ // ~humanoïdes~
	7   => ~203002~ // ~animaux~
	9   => ~204145~ // ~élémentaires~
	11  => ~204164~ // ~myconides~
	13  => ~13241013~ // ~créatures gigantesques~
	15  => ~204002~ // ~elfes~
	17  => ~204130~ // ~ombres des roches~
	19  => ~204003~ // ~demi-elfes~
	21  => ~203001 204145~ // ~humanoïdes~ ~animaux~
	23  => ~13241023~ // ~créatures aveuglées~
	25  => ~13241025~ // ~créatures immunisées au froid~
	26  => ~13241026~ // ~créatures sensibles au froid~
	27  => ~204144~ // ~golems~
	29  => ~204171~ // ~minotaures~
	31  => ~203004 204164~ // ~morts-vivants~ ~myconides~
	33  => ~13241033~ // ~créatures neutres~
	34  => ~13241034~ // ~créatures bonnes ou mauvaises~
	35  => ~13241035~ // ~créatures bonnes~
	36  => ~13241036~ // ~créatures neutres ou mauvaises~
	37  => ~13241037~ // ~créatures mauvaises~
	38  => ~13241038~ // ~créatures neutres ou bonnes~
	39  => ~205006~ // ~paladins~
	41  => ~13241041~ // ~créatures du même alignement que le porteur~
	42  => ~13241042~ // ~créatures d'un alignement différent du porteur~
	43  => ~12320200~ // ~le porteur~
	44  => ~13241044~ // ~créatures autre que le porteur~
	45  => ~204152~ // ~githyankis~
	47  => ~204144 203004 204164~ // ~golems~ ~morts-vivants~ ~myconides~
	49  => ~202028~ // ~créatures alliées~
	51  => ~202200~ // ~créatures hostiles~
	53  => ~13241053~ // ~créatures immunisées au feu ou au froid~
	54  => ~13241054~ // ~créatures sensibles au feu ou au froid~
	55  => ~203004 204144~ // ~morts-vivants~ ~golems~
	57  => ~13241057~ // ~créatures masculines~
	58  => ~13241058~ // ~créatures féminines~
	64  => ~204143~ // ~orques~
	66  => ~13241066~ // ~créatures sourdes~
	68  => ~13241068~ // ~créatures sous l'effet d'un toucher de la goule~
	74  => ~13241074~ // ~créatures mortes~
	77  => ~13241077~ // ~créatures immunisées aux poisons~
	78  => ~13241078~ // ~créatures sensibles aux poisons~
	79  => ~13241079~ // ~créatures immunisées à l'acide~
	80  => ~13241080~ // ~créatures sensibles à l'acide~
	81  => ~13241081~ // ~créatures immunisées à l'électricité~
	82  => ~13241082~ // ~créatures sensibles à l'électricité~
	83  => ~13241083~ // ~créatures immunisées aux dégâts magiques~
	84  => ~13241084~ // ~créatures sensibles aux dégâts magiques~
	85  => ~204101~ // ~ankhegs~
	87  => ~204150~ // ~liches~
	91  => ~13241091~ // ~créatures paniquées~
	119 => ~203001 203002~ // ~humanoïdes~ ~animaux~
	120 => ~13241120~ // ~créatures protégées contre les morts-vivants~
	122 => ~13241122~ // ~créatures possédant une dextérité supérieure ou égale à %value%~
	123 => ~13241123~ // ~créatures possédant une dextérité inférieure à %value%~
	124 => ~13241124~ // ~créatures possédant une force supérieure ou égale à %value%~
	125 => ~13241125~ // ~créatures possédant une force inférieure à %value%~
	126 => ~13241126~ // ~créatures possédant une constitution supérieure ou égale à %value%~
	127 => ~13241127~ // ~créatures possédant une constitution inférieure à %value%~
	128 => ~13241128~ // ~créatures possédant une intelligence supérieure ou égale à %value%~
	129 => ~13241129~ // ~créatures possédant une intelligence inférieure à %value%~
	130 => ~13241130~ // ~créatures possédant une sagesse supérieure ou égale à %value%~
	131 => ~13241131~ // ~créatures possédant une sagesse inférieure à %value%~
	132 => ~13241132~ // ~créatures possédant un charisme supérieur ou égal à %value%~
	133 => ~13241133~ // ~créatures possédant un charisme inférieur à %value%~
	138 => ~13241138~ // ~créatures %descriptionState%~
	140 => ~13241140~ // ~créatures sous l'effet d'une invisibilité~
	141 => ~13241141~ // ~créatures sous l'effet d'une invisibilité améliorée~
	142 => ~13241142~ // ~créatures invisibles~
	144 => ~13241144~ // ~créatures dont les points de vie sont supérieurs ou égaux à %value%~
	145 => ~13241145~ // ~créatures dont les points de vie sont inférieurs à %value%~
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcode_324_not_effective_between~ BEGIN
	89 => ~13241089~ // ~entre 6h et 20h~
	90 => ~13241090~ // ~entre 21h et 5h~
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcode_324_not_effective_if~ BEGIN
	134 => ~13241134~ // ~si le nombre de créatures invoquées est supérieur ou égal à %value%~
	135 => ~13241135~ // ~si le nombre de créatures invoquées est inférieur à %value%~
	136 => ~13241136~ // ~si le chapitre en cours est supérieur ou égal au %value%~
	137 => ~13241137~ // ~si le chapitre en cours est inférieur à %value%~
END

DEFINE_PATCH_FUNCTION ~opcode_324_target_exceptions~
	STR_VAR list = ~~
	RET target_exceptions
BEGIN
	SPRINT target_exceptions ~~

	SPRINT the @11770200 // ~les~
	SPRINT and @100021 // ~et~
	SPRINT andThe @11770201 // ~et les~
	SPRINT target_effective ~~
	SPRINT target_effective_if ~~
	SPRINT target_not_effective ~~
	SPRINT target_not_effective_between ~~
	SPRINT target_not_effective_if ~~

	PATCH_DEFINE_ARRAY keys BEGIN END
	PATCH_DEFINE_ARRAY effective_against BEGIN END
	PATCH_DEFINE_ARRAY not_effective_against BEGIN END
	PATCH_DEFINE_ARRAY not_effective_between BEGIN END // cas particulier pour 89 et 90
	PATCH_DEFINE_ARRAY not_effective_if BEGIN END // cas particulier pour 134, 135, 136, 137
	PATCH_DEFINE_ARRAY effective_if BEGIN END // cas particulier pour 136 avec valeur 6
	PATCH_DEFINE_ARRAY target_conditions BEGIN END

	LPF ~get_probability~ INT_VAR probability1 probability2 RET baseProbability = probability END
	SET baseProbability1 = probability1
	SET baseProbability2 = probability2

	WHILE "%list%" STRING_COMPARE ~~ BEGIN
		LPF return_first_entry STR_VAR list separator=" " RET list entry END
		LPF return_first_entry STR_VAR list = ~%entry%~ separator=";" RET params = entry entry = list END
		LPF return_first_pair STR_VAR list = ~%params%~ RET probability1 = key probability2 = value params = list END
		LPF return_first_entry STR_VAR list = ~%entry%~ separator=";" RET params = entry END
		LPF return_first_pair STR_VAR list = ~%params%~ RET parameter1 = key parameter2 = value END

		LPF ~get_probability~ INT_VAR probability1 probability2 RET probability END

		PATCH_IF baseProbability < 100 AND NOT (baseProbability1 < probability2 OR baseProbability2 > probability1) BEGIN
			// Recalcul de la probabilité par ratio
			PATCH_IF baseProbability1 == probability1 OR baseProbability2 == probability2 BEGIN
				SET probability = 100
			END
			ELSE PATCH_IF baseProbability1 != probability1 OR baseProbability2 != probability2 BEGIN
				SET newProbability1 = baseProbability1
				SET newProbability2 = baseProbability2

				PATCH_IF newProbability1 > probability1 BEGIN
					SET newProbability1 = probability1
				END
				PATCH_IF newProbability2 < probability2 BEGIN
					SET newProbability2 = probability2
				END
				LPF ~get_probability~ INT_VAR probability1 = newProbability1 probability2 = newProbability2 RET newProbability = probability END
				SET probability = newProbability * 100 / baseProbability
			END
        END

		SET key = 100 - probability
		SET $keys(~%key%~) = 1

		SET value = parameter1
		SET statType = parameter2

		PATCH_IF statType >= 102 AND statType <= 109 BEGIN // IDS
            SET idsId = statType - 100
            LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%idsId%~ RET creatureType = idName END
            SET $EVAL ~not_effective_against%key%~(~%creatureType%~) = 1
        END
        ELSE PATCH_IF statType == 76 OR statType == 110 OR statType == 111 BEGIN // SplState
            PATCH_IF parameter1 != 121 BEGIN // On ignore l'effet "Manteau"
	            SET strref = 420000 + parameter1
				LPF ~get_splstate_name~ INT_VAR strref opcode splstate = parameter1 RET splstateName END
				PATCH_IF NOT ~%splstateName%~ STRING_EQUAL ~~ BEGIN
		            SPRINT creatureType @13241110 // ~créatures sous l'effet de %splstateName%~
		            PATCH_IF statType == 76 OR statType == 110 BEGIN
		                SET $EVAL ~not_effective_against%key%~(~%creatureType%~) = 1
		            END
		            ELSE PATCH_IF statType == 111 BEGIN
		                SET $EVAL ~effective_against%key%~(~%creatureType%~) = 1
		            END
	            END
	        END
        END
        ELSE PATCH_IF statType >= 112 AND statType <= 118 BEGIN // !IDS
            SET idsId = statType - 110
            LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%idsId%~ RET creatureType = idName END
            SET $EVAL ~effective_against%key%~(~%creatureType%~) = 1
        END
        ELSE PATCH_IF statType == 138 OR statType == 139 BEGIN // STATE
            LPF ~get_states_str~ INT_VAR state = parameter1 RET descriptionState = descriptionState END
            SPRINT creatureType @13241138 // ~créatures %descriptionState%~
            PATCH_IF statType == 138 BEGIN
                SET $EVAL ~not_effective_against%key%~(~%creatureType%~) = 1
            END
            ELSE BEGIN
                SET $EVAL ~effective_against%key%~(~%creatureType%~) = 1
            END
        END
		ELSE PATCH_IF is_ee AND statType > 145 BEGIN
			SET strref = 0
			LPM ~opcode_326_condition_mod~
			PATCH_IF strref > 0 BEGIN
				SET strref -= 19000
				LPF ~getTranslation~ INT_VAR strref opcode RET creatureType = string END
				SET $EVAL ~not_effective_if%key%~(~%creatureType%~) = 1
			END
		END
        ELSE BEGIN
            PATCH_IF VARIABLE_IS_SET $opcode_324_effective(~%statType%~) BEGIN
                SPRINT opcode_324_list $opcode_324_effective(~%statType%~)

				WHILE NOT ~%opcode_324_list%~ STRING_EQUAL ~~ BEGIN
					LPF return_first_entry STR_VAR list = ~%opcode_324_list%~ RET strref=entry opcode_324_list = list END
					LPF ~getTranslation~ INT_VAR strref opcode RET creatureType = string END
	                SET $EVAL ~effective_against%key%~(~%creatureType%~) = 1
				END
            END
            ELSE PATCH_IF VARIABLE_IS_SET $opcode_324_not_effective(~%statType%~) BEGIN
                SPRINT opcode_324_list $opcode_324_not_effective(~%statType%~)
				WHILE NOT ~%opcode_324_list%~ STRING_EQUAL ~~ BEGIN
					LPF return_first_entry STR_VAR list = ~%opcode_324_list%~ RET strref=entry opcode_324_list = list END
					LPF ~getTranslation~ INT_VAR strref opcode RET creatureType = string END
	                SET $EVAL ~not_effective_against%key%~(~%creatureType%~) = 1
				END
            END
            ELSE PATCH_IF VARIABLE_IS_SET $opcode_324_not_effective_between(~%statType%~) BEGIN
                SPRINT opcode_324_list $opcode_324_not_effective_between(~%statType%~)
				WHILE NOT ~%opcode_324_list%~ STRING_EQUAL ~~ BEGIN
					LPF return_first_entry STR_VAR list = ~%opcode_324_list%~ RET strref=entry opcode_324_list = list END
					LPF ~getTranslation~ INT_VAR strref opcode RET creatureType = string END
	                SET $EVAL ~not_effective_between%key%~(~%creatureType%~) = 1
				END
            END
            ELSE PATCH_IF VARIABLE_IS_SET $opcode_324_not_effective_if(~%statType%~) BEGIN
                SPRINT opcode_324_list $opcode_324_not_effective_if(~%statType%~)
                PATCH_IF statType == 136 AND value == 6 BEGIN
                    SPRINT opcode_324_list ~13240401~ // ~durant la pénurie de fer~
					WHILE NOT ~%opcode_324_list%~ STRING_EQUAL ~~ BEGIN
						LPF return_first_entry STR_VAR list = ~%opcode_324_list%~ RET strref=entry opcode_324_list = list END
						LPF ~getTranslation~ INT_VAR strref opcode RET creatureType = string END
		                SET $EVAL ~effective_if%key%~(~%creatureType%~) = 1
					END
                END
                ELSE BEGIN
					WHILE NOT ~%opcode_324_list%~ STRING_EQUAL ~~ BEGIN
						LPF return_first_entry STR_VAR list = ~%opcode_324_list%~ RET strref=entry opcode_324_list = list END
						LPF ~getTranslation~ INT_VAR strref opcode RET creatureType = string END
		                SET $EVAL ~not_effective_if%key%~(~%creatureType%~) = 1
					END
				END
            END
        END
	END

	SORT_ARRAY_INDICES ~keys~ NUMERICALLY
	SPRINT effectiveAndThe ~%andThe%~
	SPRINT notEffectiveAndThe ~%andThe%~
	PATCH_PHP_EACH keys AS key => _ BEGIN
		SET probability = 100 - key
		SPRINT probabilityStr ~~
		PATCH_IF probability < 100 BEGIN
			SPRINT probabilityStr @13241503 // ~à %probability% % ~
		END

		CLEAR_ARRAY targetsList
		PATCH_PHP_EACH ~effective_against%key%~ AS target => _ BEGIN
			SET $targetsList(~%target%~) = 1
		END
		LPF ~implode~ STR_VAR array_name = ~targetsList~ glue = ~, %the% ~ final_glue = ~ %andThe% ~ RET creaturesList = text END
		PATCH_IF NOT ~%creaturesList%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF probability < 100 BEGIN
				SPRINT effectiveAndThe ~%and%~
			END
			SPRINT creaturesList @13241502 // ~contre les %creaturesList%~
			SPRINT creaturesList ~%probabilityStr%%creaturesList%~
			SET $effective_against(~%creaturesList%~) = 1
		END

		CLEAR_ARRAY targetsList
		PATCH_PHP_EACH ~not_effective_against%key%~ AS target => _ BEGIN
			SET $targetsList(~%target%~) = 1
		END
		LPF ~implode~ STR_VAR array_name = ~targetsList~ glue = ~, %the% ~ final_glue = ~ %andThe% ~ RET creaturesList = text END
		PATCH_IF NOT ~%creaturesList%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF probability < 100 BEGIN
				SPRINT notEffectiveAndThe ~%and%~
			END
			SPRINT creaturesList @13241502 // ~contre les %creaturesList%~
			SPRINT creaturesList ~%probabilityStr%%creaturesList%~
			SET $not_effective_against(~%creaturesList%~) = 1
		END

		CLEAR_ARRAY targetsList
		PATCH_PHP_EACH ~not_effective_between%key%~ AS target => _ BEGIN
			SET $targetsList(~%target%~) = 1
		END
		LPF ~implode~ STR_VAR array_name = ~targetsList~ glue = ~, ~ final_glue = ~ %and% ~ RET creaturesList = text END
		PATCH_IF NOT ~%creaturesList%~ STRING_EQUAL ~~ BEGIN
			SPRINT creaturesList ~%probabilityStr%%creaturesList%~
			SET $not_effective_between(~%creaturesList%~) = 1
		END

		CLEAR_ARRAY targetsList
		PATCH_PHP_EACH ~not_effective_if%key%~ AS target => _ BEGIN
			SET $targetsList(~%target%~) = 1
		END
		LPF ~implode~ STR_VAR array_name = ~targetsList~ glue = ~, ~ final_glue = ~ %and% ~ RET creaturesList = text END
		PATCH_IF NOT ~%creaturesList%~ STRING_EQUAL ~~ BEGIN
			SPRINT creaturesList ~%probabilityStr%%creaturesList%~
			SET $not_effective_if(~%creaturesList%~) = 1
		END

		CLEAR_ARRAY targetsList
		PATCH_PHP_EACH ~effective_if%key%~ AS target => _ BEGIN
			SET $targetsList(~%target%~) = 1
		END
		LPF ~implode~ STR_VAR array_name = ~targetsList~ glue = ~, ~ final_glue = ~ %and% ~ RET creaturesList = text END
		PATCH_IF NOT ~%creaturesList%~ STRING_EQUAL ~~ BEGIN
			SPRINT creaturesList ~%probabilityStr%%creaturesList%~
			SET $effective_if(~%creaturesList%~) = 1
		END
	END

	LPF ~implode~ STR_VAR array_name = ~effective_if~ glue = ~, ~ final_glue = ~ %and% ~ RET target_effective_if = text END
	PATCH_IF NOT ~%target_effective_if%~ STRING_EQUAL ~~ BEGIN
		SET $target_conditions(~%target_effective_if%~) = 1
	END
	LPF ~implode~ STR_VAR array_name = ~effective_against~ glue = ~, %the% ~ final_glue = ~ %effectiveAndThe% ~ RET creaturesList = text END
	PATCH_IF NOT ~%creaturesList%~ STRING_EQUAL ~~ BEGIN
		SET $target_conditions(~%creaturesList%~) = 1
	END
	LPF ~implode~ STR_VAR array_name = ~target_conditions~ glue = ~, ~ final_glue = ~, ~ RET creaturesList = text END
	PATCH_IF NOT ~%creaturesList%~ STRING_EQUAL ~~ BEGIN
		SPRINT target_effective @13241500 // ~Effectif %creaturesList%~
	END

	SPRINT target_conditions ~~
	CLEAR_ARRAY target_conditions

	LPF ~implode~ STR_VAR array_name = ~not_effective_against~ glue = ~, %the% ~ final_glue = ~ %notEffectiveAndThe% ~ RET target_not_effective = text END
	LPF ~implode~ STR_VAR array_name = ~not_effective_between~ glue = ~ %and% ~ final_glue = ~ %and% ~ RET target_not_effective_between = text END
	LPF ~implode~ STR_VAR array_name = ~not_effective_if~ glue = ~, ~ final_glue = ~ %and% ~ RET target_not_effective_if = text END

	PATCH_IF NOT ~%target_not_effective%~ STRING_EQUAL ~~ BEGIN
		SET $target_conditions(~%target_not_effective%~) = 1
	END
	PATCH_IF NOT ~%target_not_effective_between%~ STRING_EQUAL ~~ BEGIN
		SET $target_conditions(~%target_not_effective_between%~) = 1
	END
	PATCH_IF NOT ~%target_not_effective_if%~ STRING_EQUAL ~~ BEGIN
		SET $target_conditions(~%target_not_effective_if%~) = 1
	END
	LPF ~implode~ STR_VAR array_name = ~target_conditions~ glue = ~, ~ final_glue = ~, ~ RET targetCondition = text END
	PATCH_IF NOT ~%targetCondition%~ STRING_EQUAL ~~ BEGIN
		SPRINT target_not_effective @13241501 // ~Inefficace %targetCondition%~
	END


	PATCH_IF NOT ~%target_effective%~ STRING_EQUAL ~~ AND NOT ~%target_not_effective%~ STRING_EQUAL ~~ BEGIN
		SPRINT target_exceptions ~%target_effective%. %target_not_effective%~
	END
	ELSE PATCH_IF NOT ~%target_not_effective%~ STRING_EQUAL ~~ BEGIN
		SPRINT target_exceptions ~%target_not_effective%~
	END
	ELSE PATCH_IF NOT ~%target_effective%~ STRING_EQUAL ~~ BEGIN
		SPRINT target_exceptions ~%target_effective%~
	END
END

/* ------------------------ *
 * Stat: Save vs. all [325] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_325~ BEGIN
	PATCH_IF parameter2 == 3 BEGIN
		SET parameter2 = MOD_TYPE_cumulative
	END
	LPF ~opcode_mod~ INT_VAR strref = 102034 STR_VAR value = ~%parameter1%~ complex_value RET description END // ~Jets de sauvegarde~
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

DEFINE_PATCH_MACRO ~opcode_325_is_valid~ BEGIN
	LPM ~opcode_33_is_valid~
END

/* ------------------------ *
 * Apply Effects List [326] *
 * ------------------------ */
// TODO : gérer 326 avec 324
DEFINE_PATCH_MACRO ~opcode_self_326~ BEGIN
	PATCH_IF ~%target_type%~ STRING_EQUAL ~~ BEGIN
		LPM ~opcode_326_condition~
	END
	// Protection contre les boucles infinies
	PATCH_IF NOT VARIABLE_IS_SET $recursive_resref(~%resref%~) BEGIN
		SET $recursive_resref(~%resref%~) = 1
		SET $recursive_resref(~%CURRENT_SOURCE_RES%~) = 1
		LPF ~get_item_spell_effects_description~ STR_VAR file = ~%resref%~ RET description END
	END
	CLEAR_ARRAY recursive_resref
	SET ignoreDuration = 1
END

DEFINE_PATCH_MACRO ~opcode_self_probability_326~ BEGIN
	PATCH_IF ~%target_type%~ STRING_EQUAL ~~ BEGIN
		LPM ~opcode_326_condition~
	END
	// Protection contre les boucles infinies
	PATCH_IF NOT VARIABLE_IS_SET $recursive_resref(~%resref%~) BEGIN
		SET $recursive_resref(~%resref%~) = 1
		SET $recursive_resref(~%CURRENT_SOURCE_RES%~) = 1
		LPF ~get_item_spell_effects_description~ INT_VAR baseProbability = probability STR_VAR file = ~%resref%~ RET description END
		INNER_PATCH_SAVE description ~%description%~ BEGIN
			SPRINT regex @10019 // ~^[0-9]+ % de chance ~
			REPLACE_TEXTUALLY EVALUATE_REGEXP ~%regex%~ ~~
		END
	END
	CLEAR_ARRAY recursive_resref
	SET ignoreDuration = 1
END

DEFINE_PATCH_MACRO ~opcode_target_326~ BEGIN
	LPM ~opcode_self_326~
END

DEFINE_PATCH_MACRO ~opcode_326_condition~ BEGIN
	LOCAL_SET strref = 13260000
	LOCAL_SET value = parameter1
	LOCAL_SET statType = parameter2
	LOCAL_SET idsId = 0
	LOCAL_SPRINT proficiency ~~
	LOCAL_SPRINT proficiencyId ~~

	PATCH_IF statType >= 102 AND statType <= 109 BEGIN
		SET idsId = statType - 100
		SET strref = strref + 146 // ~Inefficace contre les %creatureType%~
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%idsId%~ RET creatureType = idName END
	END
	ELSE PATCH_IF statType == 76 OR statType == 110 OR statType == 111 BEGIN // SplState
		SET statType = statType == 76 ? 110 : statType
		SET oldStrref = strref + statType
		SET strref = 420000 + parameter1
		LPF ~get_splstate_name~ INT_VAR strref opcode splstate = parameter1 RET splstateName END
		SET strref = oldStrref
	END
	ELSE PATCH_IF statType >= 112 AND statType <= 118 BEGIN
		SET idsId = statType - 110
		SET strref = strref + 147 // ~Effectif contre les %creatureType%~
		LPF ~get_ids_name~ INT_VAR entry = ~%parameter1%~ file = ~%idsId%~ RET creatureType = idName END
	END
	ELSE PATCH_IF statType == 138 OR statType == 139 BEGIN // STATE
		LPF ~get_states_str~ INT_VAR state = parameter1 RET descriptionState = descriptionState END
		SET strref = strref + statType
	END
	ELSE PATCH_IF is_ee AND statType > 145 BEGIN
		LPM ~opcode_326_condition_mod~
	END
	ELSE BEGIN
		SET strref = strref + statType
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET condition = string END
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY ~opcode_326_targets~ BEGIN
	1   => ~3:004~ // ~morts-vivants~
	3   => ~13241003~ // ~créatures immunisées au feu~ //1:001 => utiliser 2001001 complètement inventé, comme un ids!
	4   => ~13241004~ // ~créatures sensibles au feu~
	5   => ~3:001~ // ~humanoïdes~
	7   => ~3:002~ // ~animaux~
	9   => ~4:145~ // ~élémentaires~
	11  => ~4:164~ // ~myconides~
	13  => ~13241013~ // ~créatures gigantesques~
	15  => ~4:002~ // ~elfes~
	17  => ~4:130~ // ~ombres des roches~
	19  => ~4:003~ // ~demi-elfes~
	21  => ~3:001 4:145~ // ~humanoïdes~ ~animaux~
	23  => ~13241023~ // ~créatures aveuglées~
	25  => ~13241025~ // ~créatures immunisées au froid~
	26  => ~13241026~ // ~créatures sensibles au froid~
	27  => ~4:144~ // ~golems~
	29  => ~4:171~ // ~minotaures~
	31  => ~3:004 4:164~ // ~morts-vivants~ ~myconides~
	33  => ~13241033~ // ~créatures neutres~
	34  => ~13241034~ // ~créatures bonnes ou mauvaises~
	35  => ~13241035~ // ~créatures bonnes~
	36  => ~13241036~ // ~créatures neutres ou mauvaises~
	37  => ~13241037~ // ~créatures mauvaises~
	38  => ~13241038~ // ~créatures neutres ou bonnes~
	39  => ~5:006~ // ~paladins~
	41  => ~13241041~ // ~créatures du même alignement que le porteur~
	42  => ~13241042~ // ~créatures d'un alignement différent du porteur~
	43  => ~12320200~ // ~le porteur~
	44  => ~13241044~ // ~créatures autre que le porteur~
	45  => ~4:152~ // ~githyankis~
	47  => ~4:144 3:004 4:164~ // ~golems~ ~morts-vivants~ ~myconides~
	49  => ~2:028~ // ~créatures alliées~
	51  => ~2:200~ // ~créatures hostiles~
	53  => ~13241053~ // ~créatures immunisées au feu ou au froid~
	54  => ~13241054~ // ~créatures sensibles au feu ou au froid~
	55  => ~3:004 4:144~ // ~morts-vivants~ ~golems~
	57  => ~13241057~ // ~créatures masculines~
	58  => ~13241058~ // ~créatures féminines~
	64  => ~4:143~ // ~orques~
	66  => ~13241066~ // ~créatures sourdes~
	68  => ~13241068~ // ~créatures sous l'effet d'un toucher de la goule~
	74  => ~13241074~ // ~créatures mortes~
	77  => ~13241077~ // ~créatures immunisées aux poisons~
	78  => ~13241078~ // ~créatures sensibles aux poisons~
	79  => ~13241079~ // ~créatures immunisées à l'acide~
	80  => ~13241080~ // ~créatures sensibles à l'acide~
	81  => ~13241081~ // ~créatures immunisées à l'électricité~
	82  => ~13241082~ // ~créatures sensibles à l'électricité~
	83  => ~13241083~ // ~créatures immunisées aux dégâts magiques~
	84  => ~13241084~ // ~créatures sensibles aux dégâts magiques~
	85  => ~4:101~ // ~ankhegs~
	87  => ~4:150~ // ~liches~
	91  => ~13241091~ // ~créatures paniquées~
	119 => ~3:001 3:002~ // ~humanoïdes~ ~animaux~
	120 => ~13241120~ // ~créatures protégées contre les morts-vivants~
	122 => ~13241122~ // ~créatures possédant une dextérité supérieure ou égale à %value%~
	123 => ~13241123~ // ~créatures possédant une dextérité inférieure à %value%~
	124 => ~13241124~ // ~créatures possédant une force supérieure ou égale à %value%~
	125 => ~13241125~ // ~créatures possédant une force inférieure à %value%~
	126 => ~13241126~ // ~créatures possédant une constitution supérieure ou égale à %value%~
	127 => ~13241127~ // ~créatures possédant une constitution inférieure à %value%~
	128 => ~13241128~ // ~créatures possédant une intelligence supérieure ou égale à %value%~
	129 => ~13241129~ // ~créatures possédant une intelligence inférieure à %value%~
	130 => ~13241130~ // ~créatures possédant une sagesse supérieure ou égale à %value%~
	131 => ~13241131~ // ~créatures possédant une sagesse inférieure à %value%~
	132 => ~13241132~ // ~créatures possédant un charisme supérieur ou égal à %value%~
	133 => ~13241133~ // ~créatures possédant un charisme inférieur à %value%~
	138 => ~13241138~ // ~créatures %descriptionState%~
	140 => ~13241140~ // ~créatures sous l'effet d'une invisibilité~
	141 => ~13241141~ // ~créatures sous l'effet d'une invisibilité améliorée~
	142 => ~13241142~ // ~créatures invisibles~
	144 => ~13241144~ // ~créatures dont les points de vie sont supérieurs ou égaux à %value%~
	145 => ~13241145~ // ~créatures dont les points de vie sont inférieurs à %value%~
END

DEFINE_PATCH_MACRO ~opcode_326_group~ BEGIN
	PATCH_DEFINE_ARRAY target_types BEGIN END
	PATCH_DEFINE_ARRAY positions BEGIN END
	PATCH_DEFINE_ARRAY counts BEGIN END

	CLEAR_ARRAY identifiants
	CLEAR_ARRAY positions
	CLEAR_ARRAY counts

	// Regroupement des conditions du style "Si la cible fait partie des xxx" et "Si la cible est un xxx" qui poitent vers une même ressource
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF VARIABLE_IS_SET $opcode_326_targets(~%parameter2%~) BEGIN
			PATCH_IF NOT VARIABLE_IS_SET $counts(~%resref%~) BEGIN
				SET $counts(~%resref%~) = 0
				SPRINT $positions(~%resref%~) ~~
				SPRINT $target_types(~%resref%~) ~~
			END
			SPRINT tmp_new_target_types $opcode_326_targets(~%parameter2%~)
			SPRINT tmp_positions $positions(~%resref%~)
			SPRINT tmp_target_types $target_types(~%resref%~)
			SPRINT $positions(~%resref%~) ~%tmp_positions% %position%~
			SPRINT $target_types(~%resref%~) ~%tmp_target_types% %tmp_new_target_types%~
			SET $counts(~%resref%~) = $counts(~%resref%~) + 1
		END
		ELSE PATCH_IF parameter2 >= 102 AND parameter2 <= 109 BEGIN
			PATCH_IF NOT VARIABLE_IS_SET $counts(~%resref%~) BEGIN
				SET $counts(~%resref%~) = 0
				SPRINT $positions(~%resref%~) ~~
				SPRINT $target_types(~%resref%~) ~~
			END
			SET idsId = parameter2 - 100
			LPF ~str_pad_left~ INT_VAR min_length = 3 STR_VAR string = ~%parameter1%~ RET string END
			SPRINT tmp_new_target_types ~%idsId%:%string%~
			SPRINT tmp_positions $positions(~%resref%~)
			SPRINT tmp_target_types $target_types(~%resref%~)
			SPRINT $positions(~%resref%~) ~%tmp_positions% %position%~
			SPRINT $target_types(~%resref%~) ~%tmp_target_types% %tmp_new_target_types%~
			SET $counts(~%resref%~) = $counts(~%resref%~) + 1
		END
	END

	PATCH_PHP_EACH EVAL ~counts~ AS resref => count BEGIN
		PATCH_IF count > 1 BEGIN
			SPRINT tmp_positions $positions(~%resref%~)
			WHILE NOT ~%tmp_positions%~ STRING_EQUAL ~~ BEGIN
				LPF return_first_entry STR_VAR list = ~%tmp_positions%~ RET position=entry EVAL tmp_positions = list END
				LPF ~delete_opcode~
                    INT_VAR opcode = 326 match_position = position
                    RET $opcodes(~326~) = count
                    RET_ARRAY EVAL ~opcodes_326~ = opcodes_xx
                END
			END
			// Bug où il reste toujours un item dans le tableau si c'était le dernier
			// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
			PATCH_IF $opcodes(~326~) == 0 BEGIN
	            CLEAR_ARRAY ~opcodes_326~
	        END
			SET opcode = 326
            SPRINT target_type $target_types(~%resref%~)
            LPM ~add_opcode~
		END
	END
END

/* ------------------------------- *
 * Spell Effect: Slow Poison [329] *
 * ------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_329~ BEGIN
	LOCAL_SET amount = parameter1
	SPRINT description @13290001 // ~Abaissement de la virulence de la plupart des poisons de %amount%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_329~ BEGIN
	LOCAL_SET amount = parameter1
	SPRINT description @13290003 // ~d'abaisser la virulence de la plupart des poisons sur %theTarget% de %amount%~
END

DEFINE_PATCH_MACRO ~opcode_target_329~ BEGIN
	LOCAL_SET amount = parameter1
	SPRINT description @13290002 // ~Abaisse la virulence de la plupart des poisons sur %theTarget% de %amount%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_329~ BEGIN
	LPM ~opcode_self_probability_329~
END

DEFINE_PATCH_MACRO ~opcode_329_is_valid~ BEGIN
	PATCH_IF parameter1 == 0 OR parameter1 == 1 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Slow Factor == %parameter1% (>= 2 expected).~ END
	END
END

/* -------------------------------------- *
 * Summon: Random Monster Summoning [331] *
 * -------------------------------------- */
// FIXME: pas de test possible en 2.5.16
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

DEFINE_PATCH_MACRO ~opcode_331_is_valid~ BEGIN
	PATCH_IF NOT FILE_EXISTS_IN_GAME ~%resref%.2da~ BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : File %resref%.2da does not exist, the game may crash.~ END
	END
	ELSE PATCH_IF NOT FILE_EXISTS_IN_GAME ~smtables.2da~ BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : File smtables.2da does not exist, the game may crash.~ END
	END
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

DEFINE_PATCH_MACRO ~opcode_332_is_valid~ BEGIN
	PATCH_IF parameter1 == 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : No change detected: Modifier == %parameter1%.~ END
	END
	PATCH_IF parameter2 < 0 OR parameter2 > 10 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Type %parameter2% (0-10 expected).~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_332_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		CLEAR_ARRAY positions
		SET found = 0
		PATCH_IF parameter2 == 1 BEGIN
			SET group = 1
			PATCH_FOR_EACH damageType IN 2 3 4 BEGIN
				LPF ~get_opcode_position~
					INT_VAR opcode
			            match_target       = target
			            match_power        = power
				        match_parameter1   = parameter1
				        match_parameter2   = damageType
				        match_parameter3   = parameter3
				        match_parameter4   = parameter4
				        match_timingMode   = timingMode
				        match_resistance   = resistance
						match_duration     = duration
				        match_probability1 = probability1
				        match_probability2 = probability2
				        match_diceCount    = diceCount
				        match_diceSides    = diceSides
				        match_saveType     = saveType
				        match_saveBonus    = saveBonus
				        match_special      = special
					STR_VAR match_macro = ~opcode_match_diceCount_and_diceSides_and_duration_and_parameter1_and_parameter2_and_parameter3_and_parameter4_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~
					RET opcodePosition = position
				END

				SET $positions(~%opcodePosition%~) = 1

				PATCH_IF opcodePosition < 0 BEGIN
					SET group = 0
				END
			END
			PATCH_IF group == 1 BEGIN
				SET $positions(~%position%~) = 1
				PATCH_PHP_EACH positions AS position1 => _ BEGIN
					LPF ~delete_opcode~
						INT_VAR opcode match_position = position1
						RET $opcodes(~%opcode%~) = count
						RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
					END
				END
		        SET parameter2 = 11 // @13320011 = ~Dégâts élémentaires~
		        LPM ~add_opcode~
			END
		END

		PATCH_IF parameter2 == 7 BEGIN
			SET group = 1
			PATCH_FOR_EACH damageType IN 8 9 10 BEGIN
				LPF ~get_opcode_position~
					INT_VAR opcode
			            match_target       = target
			            match_power        = power
				        match_parameter1   = parameter1
				        match_parameter2   = damageType
				        match_parameter3   = parameter3
				        match_parameter4   = parameter4
				        match_timingMode   = timingMode
				        match_resistance   = resistance
						match_duration     = duration
				        match_probability1 = probability1
				        match_probability2 = probability2
				        match_diceCount    = diceCount
				        match_diceSides    = diceSides
				        match_saveType     = saveType
				        match_saveBonus    = saveBonus
				        match_special      = special
					STR_VAR match_macro = ~opcode_match_diceCount_and_diceSides_and_duration_and_parameter1_and_parameter2_and_parameter3_and_parameter4_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~
					RET opcodePosition = position
				END

				SET $positions(~%opcodePosition%~) = 1

				PATCH_IF opcodePosition < 0 BEGIN
					SET group = 0
				END
			END
			PATCH_IF group == 1 BEGIN
				SET $positions(~%position%~) = 1
				PATCH_PHP_EACH positions AS position1 => _ BEGIN
					LPF ~delete_opcode~
						INT_VAR opcode match_position = position1
						RET $opcodes(~%opcode%~) = count
						RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
					END
				END
		        SET parameter2 = 12 // @13320012 = ~Dégâts physiques~
		        LPM ~add_opcode~
			END
		END
	END
END

/* --------------------------------- *
 * Spell Effect: Static Charge [333] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_333~ BEGIN
	LPM ~opcode_333_common~
	SPRINT description @13330001 // ~Lance %amount% fois le sort %spellName% %strDuration%~
	SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
	SPRINT description ~%description% (%castingLevelStr%)~
END

DEFINE_PATCH_MACRO ~opcode_target_333~ BEGIN
	LPM ~opcode_333_common~
	SPRINT description @13330002 // ~Permet à %theTarget% de lancer %amount% fois le sort %spellName% %strDuration%~
	SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
	SPRINT description ~%description% (%castingLevelStr%)~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_333~ BEGIN
	LPM ~opcode_333_common~
	SPRINT description @13330003 // ~de lancer %amount% fois le sort %spellName% %strDuration%~
	SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
	SPRINT description ~%description% (%castingLevelStr%)~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_333~ BEGIN
	LPM ~opcode_333_common~
	SPRINT description @13330004 // ~de permettre à %theTarget% de lancer %amount% fois le sort %spellName% %strDuration%~
	SPRINT castingLevelStr @102095 // ~comme un lanceur de sorts de niveau %castingLevel%~
	SPRINT description ~%description% (%castingLevelStr%)~
END

DEFINE_PATCH_MACRO ~opcode_333_common~ BEGIN
	LOCAL_SET frequency = special == 0 ? 6 : special
	SET amount = parameter1
	SET castingLevel = parameter2 <= 1 ? 1 : parameter2
	SPRINT spellName ~~
	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
	END
	ELSE BEGIN
		SET strLen = STRING_LENGTH ~%CURRENT_SOURCE_RES%~
		PATCH_IF strLen <= 7 BEGIN
			LPF ~get_spell_name~ INT_VAR showWarning = 0 STR_VAR file = EVAL ~%CURRENT_SOURCE_RES%B~ RET spellName END
		END
	END
	LPF ~get_frequency_duration~ INT_VAR duration = frequency RET strDuration = frequency END
END

DEFINE_PATCH_MACRO ~opcode_333_is_valid~ BEGIN
	PATCH_IF parameter1 <= 0 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Number %parameter1%.~ END
	END
END

/* ------------------------------ *
 * Spell Effect: Seven Eyes [335] *
 * ------------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_335~ BEGIN
	LPM ~opcode_target_335~
END

// FIXME : affecte la cible que si elle n'est pas déjà affectée
DEFINE_PATCH_MACRO ~opcode_target_335~ BEGIN
	// Si %theTarget% n'est pas affecté par %splstate%, l'affecte et lui apprend le sort %spellName%
	SET stateRef = 420000 + parameter1
	LPF ~getTranslation~ INT_VAR strref = stateRef opcode RET splstate = string END
	SPRINT description @13350002 // ~Affecte %theTarget% par %splstate%~

	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
		SPRINT descriptionAdd @13350011 // ~et lui apprend le sort %spellName%~
		SPRINT description ~%description% %descriptionAdd%~
	END
	LPM ~opcode_not_cumulative~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_335~ BEGIN
	LPM ~opcode_target_probability_335~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_335~ BEGIN
	// Si %theTarget% n'est pas affecté par %splstate%, l'affecte et lui apprend le sort %spellName%
	SET stateRef = 420000 + parameter1
	LPF ~getTranslation~ INT_VAR strref = stateRef opcode RET splstate = string END
	SPRINT description @13350004 // ~d'affecter %theTarget% par %splstate%~

	PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ BEGIN
		LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
		SPRINT descriptionAdd @13350012 // ~et de lui apprendre le sort %spellName%~
		SPRINT description ~%description% %descriptionAdd%~
	END
	LPM ~opcode_not_cumulative~
END

 /* -------------------- *
 * Remove: Opcode [337] *
 * -------------------- */
DEFINE_PATCH_MACRO ~opcode_self_337~ BEGIN
	LOCAL_SET strref = 13370001
	LPM ~opcode_337_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_337~ BEGIN
	LOCAL_SET strref = 13370003
	LPM ~opcode_337_common~
END

DEFINE_PATCH_MACRO ~opcode_target_337~ BEGIN
	LOCAL_SET strref = 13370002
	LPM ~opcode_337_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_337~ BEGIN
	LOCAL_SET strref = 13370004
	LPM ~opcode_337_common~
END

DEFINE_PATCH_MACRO ~opcode_337_common~ BEGIN
	LOCAL_SET opcodeStrref = 401000 + (parameter2 == 101 AND parameter1 >= 0 ? parameter1 : parameter2)
	LPF ~getTranslation~ INT_VAR strref = opcodeStrref opcode RET opcodeStr = string END
	PATCH_IF NOT ~%opcodeStr%~ STRING_EQUAL ~~ BEGIN
		SPRINT description (AT strref) // ~Dissipe %opcodeStr% %ofTheTarget%~
	END
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

DEFINE_PATCH_MACRO ~opcode_340_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
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
	PATCH_IF special >= 1 BEGIN
		SET strref = 13010010 + special // ~en mêlée~
		LPF ~getTranslation~ INT_VAR strref opcode RET descriptionAdd = string END
		TEXT_SPRINT condition ~%condition% %descriptionAdd%~
	END
	PATCH_IF parameter2 == 0 AND isExternal AND parameter3 != 0 BEGIN
		SET strref = 230000 + parameter3
		SPRINT weaponType (AT strref)
		SPRINT strref @13410020 // ~avec des %weaponType%~
		TEXT_SPRINT condition ~%condition% %strref%~
	END
	ELSE PATCH_IF parameter2 != 0 BEGIN
		//TODO : restriction du type d'arme si parameter2 != 0 (cela a-t-il un sens ?)
		PATCH_IF isExternal AND parameter3 != 0 BEGIN
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode%: Condition %parameter2% et Weapon Category %parameter3% non gere~ END
		END
	END

	SET abilityType = AbilityType_Combat
	LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END

	LPF ~get_item_spell_effects_description~ STR_VAR file = ~%resref%~ RET description END

	INNER_PATCH_SAVE tmp_description ~%description%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~~
	END
    PATCH_IF NOT ~%description%~ STRING_EQUAL ~%tmp_description%~ AND ~%description%~ STRING_MATCHES_REGEXP ~^%crlf%~ == 1 BEGIN
		INNER_PATCH_SAVE description ~%description%~ BEGIN
			REPLACE_TEXTUALLY EVALUATE_REGEXP ~%crlf%~ ~%crlf%  ~
		END
		SPRINT description ~%crlf%  - %description%~
	END
END

DEFINE_PATCH_MACRO ~opcode_341_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

/* ------------- *
 * HP Swap [343] *
 * ------------- */
DEFINE_PATCH_MACRO ~opcode_self_343~ BEGIN
	LOCAL_SET mode = parameter2
	PATCH_IF mode == 1 BEGIN
		SPRINT description @13430001 // ~Échange les points de vie du porteur et de la cible~
	END
	ELSE BEGIN
		SPRINT description @13430002 // ~Échange les points de vie du porteur et de la cible, si ceux du porteur sont plus grands~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_343~ BEGIN
	LOCAL_SET mode = parameter2
	PATCH_IF mode == 1 BEGIN
		SPRINT description @13430003 // ~d'échanger les points de vie du porteur et de la cible~
	END
	ELSE BEGIN
		SPRINT description @13430004 // ~d'échanger les points de vie du porteur et de la cible, si ceux du porteur sont plus grands~
	END
END

/* ----------------------------------- *
 * Enchantment vs. creature type [344] *
 * ----------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_344~ BEGIN
	// Pas de sens de cumuler parameter3 == 3 et parameter4 != 0 => ignore parameter3
	SPRINT name @13440001 // ~Enchantement~
	PATCH_IF isExternal AND parameter4 != 0 AND parameter3 >= 1 AND parameter3 <= 3 BEGIN
		SET strref = 230000 + parameter4
		LPF ~getTranslation~ INT_VAR strref opcode RET weaponType = string END
		SPRINT strref @13440020 // ~des %weaponType%~
		TEXT_SPRINT name ~%name% %strref%~
	END
	PATCH_IF isExternal AND parameter3 >= 1 AND parameter3 <= 2 OR (parameter3 == 3 AND parameter4 == 0) BEGIN // >= 4 : comme 0
		SET strref = 13440010 + parameter3 // ~dans la main directrice~
		LPF ~getTranslation~ INT_VAR strref opcode RET weaponSlot = string END
		TEXT_SPRINT name ~%name% %weaponSlot%~
	END
	SET value = special
	LPF ~signed_value~ INT_VAR value RET value END
	SPRINT description @100009 // ~%name%%colon%%value% %versus%~
END

DEFINE_PATCH_MACRO ~opcode_344_is_valid~ BEGIN
	LPM ~opcode_idscheck8_is_valid~
END

DEFINE_PATCH_MACRO ~opcode_344_group~ BEGIN
	LPM ~opcode_group_by_target~
END

/* ----------------------- *
 * Enchantment bonus [345] *
 * ----------------------- */
// Je ne comprends pas comment il peut fonctionner : où se trouve le bonus ?
// le seul cas où ça peut matcher c'est pour P2==0
// FIXME: P2 != 0
DEFINE_PATCH_MACRO ~opcode_self_345~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : parameter2 != 0 non gere : %parameter2%~ END
	END

	// Pas de sens de cumuler parameter3 == 3 et parameter4 != 0 => ignore parameter3
	SET parameter3 = special != 0 ? special : parameter3
	SPRINT name @13440001 // ~Enchantement~
	PATCH_IF isExternal AND parameter4 != 0 AND parameter3 >= 1 AND parameter3 <= 3 BEGIN
		SET strref = 230000 + parameter4
		LPF ~getTranslation~ INT_VAR strref opcode RET weaponType = string END
		SPRINT strref @13440020 // ~des %weaponType%~
		TEXT_SPRINT name ~%name% %strref%~
	END
	PATCH_IF isExternal AND parameter3 >= 1 AND parameter3 <= 2 OR (parameter3 == 3 AND parameter4 == 0) BEGIN // >= 4 : comme 0
		SET strref = 13440010 + parameter3 // ~dans la main directrice~
		LPF ~getTranslation~ INT_VAR strref opcode RET weaponSlot = string END
		TEXT_SPRINT name ~%name% %weaponSlot%~
	END
	SET value = parameter1
	LPF ~signed_value~ INT_VAR value RET value END
	SPRINT description @100001 // ~%name%%colon%%value%~
END

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

DEFINE_PATCH_MACRO ~opcode_target_probability_346~ BEGIN
	LPM ~opcode_self_probability_346~
END

DEFINE_PATCH_MACRO ~opcode_346_is_valid~ BEGIN
	// Pas de mode percent
	LPM ~opcode_modstat1_is_valid~
	PATCH_IF special < 0 OR special > 11 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Invalid Primary Type %special% (0-11 expected).~ END
	END
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

DEFINE_PATCH_MACRO ~opcode_361_is_valid~ BEGIN
	LPM ~opcode_resref_is_valid~
END

/* ------------------------- *
 * Critical miss bonus [362] *
 * ------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_362~ BEGIN
	PATCH_IF parameter2 != 0 BEGIN
		SPRINT name @13620002 // ~Chance d'échec critique avec cette arme~
	END
	ELSE BEGIN
		SPRINT name @13620001 // ~Chance d'échec critique~
	END
	LPM ~opcode_301_common~
END

/* ------------------------ *
 * Minimum base stats [367] *
 * ------------------------ */
// FIXME: Est utilisé dans certains sorts qui diminue les caractéristiques sans pouvoir tuer la cible
// Idéalement, il faudrait trouver cet effet de même durée et les grouper : Constitution -2 (minimum 1)
DEFINE_PATCH_MACRO ~opcode_self_367~ BEGIN
	SET strref = parameter2 == 0 ? 13670001 : 13670002
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_target_367~ BEGIN
	SET strref = parameter2 == 0 ? 13670011 : 13670012
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_self_probability_367~ BEGIN
	SET strref = parameter2 == 0 ? 13670021 : 13670022
	SPRINT description (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_target_probability_367~ BEGIN
	SET strref = parameter2 == 0 ? 13670031 : 13670032
	SPRINT description (AT strref)
END

/* --------------------------------- *
 * Stat: Compétences de voleur [500] *
 * --------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_500~ BEGIN
	LPF ~opcode_mod_percent~ INT_VAR strref = 15000001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Compétences de voleur~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_500~ BEGIN
	LPF ~opcode_probability_percent~ INT_VAR strref = 15000002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~les compétences de voleur~
END

DEFINE_PATCH_MACRO ~opcode_target_500~ BEGIN
	LPF ~opcode_target_percent~ INT_VAR strref = 15000002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~les compétences de voleur~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_500~ BEGIN
	LPM ~opcode_self_probability_500~
END

/* ---------------------------- *
 * Stat: Caractéristiques [501] *
 * ---------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_501~ BEGIN
	LPF ~opcode_mod~ INT_VAR strref = 15010001 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~Caractéristiques~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_501~ BEGIN
	LPF ~opcode_probability~ INT_VAR strref = 15010002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~les caractéristiques~
END

DEFINE_PATCH_MACRO ~opcode_target_501~ BEGIN
	LPF ~opcode_target~ INT_VAR strref = 15010002 STR_VAR value = EVAL ~%parameter1%~ RET description END // ~les caractéristiques~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_501~ BEGIN
	LPM ~opcode_self_probability_501~
END

/* --------------------------------- *
 * Stat: Résistance aux dégâts [502] *
 * --------------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_502~ BEGIN
	SET resistName = 15020001 // ~Résistance aux dégâts~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_502~ BEGIN
	SET resistName = 15020001 // ~Résistance aux dégâts~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_502~ BEGIN
	SET resistName = 15020001 // ~Résistance aux dégâts~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_502~ BEGIN
	LPM ~opcode_self_probability_502~
END

/* ----------------------------------------------- *
 * Stat: Résistance aux dégâts élémentaires~ [503] *
 * ----------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_503~ BEGIN
	SET resistName = 15030001 // ~Résistance aux dégâts élémentaires~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_503~ BEGIN
	SET resistName = 15030001 // ~Résistance aux dégâts élémentaires~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_503~ BEGIN
	SET resistName = 15030001 // ~Résistance aux dégâts élémentaires~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_503~ BEGIN
	LPM ~opcode_self_probability_503~
END

/* ------------------------------------------- *
 * Stat: Résistance aux dégâts physiques [504] *
 * ------------------------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_504~ BEGIN
	SET resistName = 15040001 // ~Résistance aux dégâts physiques~
	LPM ~opcode_self_resist~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_504~ BEGIN
	SET resistName = 15040001 // ~Résistance aux dégâts physiques~
	LPM ~opcode_probability_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_504~ BEGIN
	SET resistName = 15040001 // ~Résistance aux dégâts physiques~
	LPM ~opcode_target_resist~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_504~ BEGIN
	LPM ~opcode_self_probability_504~
END

/* ------------------------------------------- *
 * Stat: Immunité aux capacités psioniques [505] *
 * ------------------------------------------- */

// Opcode vide, utilisé en couple avec l'opcode 101

/* ------------------------------------- *
 * Stat: Classe d'armure cumulable [506] *
 * ------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_506~ BEGIN
	LPM ~opcode_self_0~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_506~ BEGIN
	LPM ~opcode_self_probability_0~
END

DEFINE_PATCH_MACRO ~opcode_target_506~ BEGIN
	LPM ~opcode_target_0~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_506~ BEGIN
	LPM ~opcode_target_probability_0~
END

/* --------------------------------------- *
 * Stat: Immunité aux sorts (par niveau) (cumulatif) [509] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_509~ BEGIN
	LOCAL_SET strref = 11020001
	PATCH_IF parameter1 == 0x1FF BEGIN // 511
		SPRINT description @15090001 // ~Immunité aux sorts~
	END
	ELSE BEGIN
		LPM ~opcode_509_common~
		SPRINT description (AT strref) // ~Immunité aux sorts de niveau %spellLevel%~
	END
END

DEFINE_PATCH_MACRO ~opcode_self_probability_509~ BEGIN
	LOCAL_SET strref = 11020005
	PATCH_IF parameter1 == 0x1FF BEGIN // 511
		SPRINT description @15090002 // ~d'immuniser %theTarget% aux sorts~
	END
	ELSE BEGIN
		LPM ~opcode_509_common~
		SPRINT description (AT strref) // ~d'immuniser %theTarget% aux sorts de niveau %spellLevel%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_509~ BEGIN
	LOCAL_SET strref = 11020003
	PATCH_IF parameter1 == 0x1FF BEGIN // 511
		SPRINT description @15090003 // ~Immunise %theTarget% aux sorts~
	END
	ELSE BEGIN
		LPM ~opcode_509_common~
		SPRINT description (AT strref) // ~Immunise %theTarget% aux sorts de niveau %spellLevel%~
	END
END

DEFINE_PATCH_MACRO ~opcode_target_probability_509~ BEGIN
	LPM ~opcode_self_probability_509~ // ~d'immuniser %theTarget% aux sorts de niveau %spellLevel%~
END

DEFINE_PATCH_MACRO ~opcode_509_post_group~ BEGIN
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		PATCH_IF parameter1 == 0x1FF BEGIN // 511
			PATCH_FOR_EACH searchOpcode IN 204 205 BEGIN
				LPF ~delete_opcode~
		            INT_VAR opcode = searchOpcode
			            match_target       = target
				        match_power        = power
				        match_resistance   = resistance
				        match_probability1 = probability1
				        match_probability2 = probability2
				        match_diceCount    = diceCount
				        match_diceSides    = diceSides
				        match_saveType     = saveType
				        match_saveBonus    = saveBonus
					STR_VAR match_macro = ~opcode_match_diceCount_and_diceSides_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_target~
		            RET $opcodes(~%searchOpcode%~) = count
		            RET_ARRAY EVAL ~opcodes_%searchOpcode%~ = opcodes_xx
		        END
				// Bug où il reste toujours un item dans le tableau si c'était le dernier
				// N'a aucune incidence en temps normal, mais l'ajout de l'opcode suivant fait que l'item restant revient dans la description générée.
				PATCH_IF $opcodes(~%searchOpcode%~) == 0 BEGIN
		            CLEAR_ARRAY ~opcodes_%searchOpcode%~
		        END
	        END
        END
	END
END

DEFINE_PATCH_MACRO ~opcode_509_common~ BEGIN
	LOCAL_SET levelStrref = 0
	LOCAL_SPRINT levelStr ~~
	LOCAL_SPRINT and @100021 // ~et~
	PATCH_DEFINE_ARRAY ~levels~ BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY ~levelAndBelow~ BEGIN
		  3 => 2
		  7 => 3
		 15 => 4
		 31 => 5
		 63 => 6
		127 => 7
		255 => 8
	END
	PATCH_IF opcode == 509 AND VARIABLE_IS_SET $levelAndBelow(~%parameter1%~) BEGIN
		SET levelStrref = 101200 + $levelAndBelow(~%parameter1%~)
		SET strref += 1
		SPRINT spellLevel (AT levelStrref)
	END
	ELSE BEGIN
		FOR (idx = 0 ; idx < 9 ; ++idx) BEGIN
			SET bit = EVAL ~%BIT%idx%%~
			PATCH_IF (parameter1 BAND bit) != 0 BEGIN
				SET levelStrref = 101200 + idx + 1
				SPRINT levelStr (AT levelStrref)
				SPRINT $levels(~%levelStr%~) ~~
			END
		END
		LPF ~implode~ STR_VAR array_name = ~levels~ glue = ~, ~ final_glue = ~ %and% ~ RET spellLevel = text END
	END
END

/* -------------------------------------------- *
 * Spell: Restore Lost Spells (cumulative) [510] *
 * -------------------------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_510~ BEGIN
	LOCAL_SET strref = 15100001 // ~Se remémore 1 sort %spellType% de chaque niveau~
	LPM ~opcode_510_common~
END

DEFINE_PATCH_MACRO ~opcode_target_510~ BEGIN
	LOCAL_SET strref = 15100003 // ~Remet en mémoire 1 sort %spellType% de chaque niveau %toTheTarget%~
	LPM ~opcode_510_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_510~ BEGIN
	LOCAL_SET strref = 15100005 // ~de se remémorer 1 sort %spellType% de chaque niveau~
	LPM ~opcode_510_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_510~ BEGIN
	LOCAL_SET strref = 15100007 // ~de remettre en mémoire 1 sort %spellType% de chaque niveau %toTheTarget%~
	LPM ~opcode_510_common~
END

DEFINE_PATCH_MACRO ~opcode_510_common~ BEGIN
	PATCH_IF parameter2 == 0 BEGIN
		SPRINT spellType @12610010 // ~profane~
	END
	ELSE PATCH_IF parameter2 == 1 BEGIN
		SPRINT spellType @12610011 // ~divin~
	END

	PATCH_IF parameter1 != 0x1FF BEGIN // 511
		LPM ~opcode_509_common~
		SET strref += 1
	END

	SPRINT description (AT strref)
END

/* -------------------------------------------- *
 * Spell: Dissipe toutes les illusions [511] *
 * -------------------------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_511~ BEGIN
	SPRINT description @15110001 // ~Dissipe toutes les illusions qui affectent %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_511~ BEGIN
	SPRINT description @15110002 // ~de dissiper toutes les illusions qui affectent %theTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_511~ BEGIN
	LPM ~opcode_self_511~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_511~ BEGIN
	LPM ~opcode_self_probability_511~
END

/* ------------------------ *
 * Immunité aux sorts [518] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_518~ BEGIN
	LOCAL_SPRINT spellNames ~%custom_str%~
	SPRINT description @15180001 // ~Immunité aux sorts %spellNames%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_518~ BEGIN
	LOCAL_SPRINT spellNames ~%custom_str%~
	SPRINT description @15180003 // ~d'immuniser %theTarget% au sorts %spellNames%~
END

DEFINE_PATCH_MACRO ~opcode_target_518~ BEGIN
	LOCAL_SPRINT spellNames ~%custom_str%~
	SPRINT description @15180002 // ~Immunise %theTarget% aux sorts %spellNames%~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_518~ BEGIN
	LPM ~opcode_self_probability_518~
END

/* ----------------- *
 * Arme brisée [519] *
 * ----------------- */
DEFINE_PATCH_MACRO ~opcode_self_probability_519~ BEGIN
	SPRINT description @15190001 // ~de se briser~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_519~ BEGIN
	SPRINT description @15190001 // ~de se briser~
END

/* ------------------------------ *
 * Protection: Action libre [520] *
 * ------------------------------ */

DEFINE_PATCH_MACRO ~opcode_self_520~ BEGIN
	SPRINT description @15200001 // ~Action libre~
END

/* ----------------------------------- *
 * Protection: Aucune protection [521] *
 * ----------------------------------- */

DEFINE_PATCH_MACRO ~opcode_self_521~ BEGIN
	SPRINT versus ~%custom_str%~
	SPRINT description @15210001 // ~Ne protège pas %versus%~
END

/* ----------------------------------------- *
 * Stat: Force et Force exceptionnelle [522] *
 * ----------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_522~ BEGIN
	LOCAL_SPRINT name @10440001 // ~Force~
	LOCAL_SPRINT value ~~
	PATCH_IF parameter2 == 100 BEGIN
		SPRINT parameter2 ~00~
	END
	SPRINT value ~%parameter1%/%parameter2%~
	SPRINT value @10010 // ~Passe à %value%~
	SPRINT description @100001 // ~%name%%colon%%value%~
END

DEFINE_PATCH_MACRO ~opcode_target_522~ BEGIN
	LOCAL_SPRINT theStatistic @10440002 // ~la force~
	LOCAL_SPRINT value ~~
	PATCH_IF parameter2 == 100 BEGIN
		SPRINT parameter2 ~00~
	END
	SPRINT value ~%parameter1%/%parameter2%~
	SPRINT description @102287 // ~Passe %theStatistic% %ofTheTarget% à %value%~
END

/* ------------------------ *
 * Stat : Bonus force [523] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_523~ BEGIN
	SPRINT description @15230001 // ~Le bonus aux dégâts liés à la force est augmenté de 50%~
END

/* --------------------------------------- *
 * Item: Set Melee and Ranged Effect [524] *
 * --------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_self_524~ BEGIN
	SET strref = 15240001 // ~À chaque attaque réussie~
	LPM ~opcode_248_common~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_524~ BEGIN
	SET strref = 15240003 // ~par attaque réussie par %theTarget%~
	LPM ~opcode_248_common~
END

DEFINE_PATCH_MACRO ~opcode_target_524~ BEGIN
	SET strref = 15240002 // ~À chaque attaque réussie par %theTarget%~
	LPM ~opcode_248_common~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_524~ BEGIN
	LPM ~opcode_self_probability_524~
END

/* ------------------------ *
 * Item: Replace item [525] *
 * ------------------------ */
DEFINE_PATCH_MACRO ~opcode_self_525~ BEGIN
	LPF ~get_item_name~ STR_VAR file = ~%resref%~ RET itemName END
	LPF ~get_item_name~ STR_VAR file = ~%resref2%~ RET itemName2 = itemName END

	SPRINT description @15250001 // ~Remplace "%itemName%" par "%itemName2%" dans l'inventaire %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_self_probability_525~ BEGIN
	LPF ~get_item_name~ STR_VAR file = ~%resref%~ RET itemName END
	LPF ~get_item_name~ STR_VAR file = ~%resref2%~ RET itemName2 = itemName END

	SPRINT description @15250002 // ~de remplacer "%itemName%" par "%itemName2%" dans l'inventaire %ofTheTarget%~
END

DEFINE_PATCH_MACRO ~opcode_target_525~ BEGIN
	LPM ~opcode_self_525~
END

DEFINE_PATCH_MACRO ~opcode_target_probability_525~ BEGIN
	LPM ~opcode_self_probability_525~
END

DEFINE_PATCH_MACRO ~opcode_group_all_resistances~ BEGIN
	LOCAL_SET opcode = 84
	LOCAL_SET newOpcode = 502 // ~Résistance aux dégâts~

	PATCH_DEFINE_ARRAY listOpcodes BEGIN 27 28 29 30 31 85 86 87 88 89 END

	LPM ~group_opcode_with_same_parameters~
END

DEFINE_PATCH_MACRO ~opcode_mod_base~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF IS_AN_INT ~%value%~ AND value >= 0 BEGIN
				SPRINT value ~%complex_value%~
				SPRINT value @10003
			END
			ELSE BEGIN
				SPRINT value ~%complex_value%~
			END
		END
		ELSE PATCH_IF IS_AN_INT ~%value%~ BEGIN
			LPF ~signed_value~ INT_VAR value RET value END
		END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
			SPRINT value ~%complex_value%~
		END
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
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : dice % non gere : %value%~ END
			SPRINT value @10002 // ~%value% %~
		END
	END
	PATCH_IF (NOT IS_AN_INT ~%value%~ OR value != 0) AND strref > 0 BEGIN
		LPF ~getTranslation~ INT_VAR strref opcode RET name = string END
	END
END

DEFINE_PATCH_FUNCTION ~opcode_mod~ INT_VAR strref = 0 STR_VAR value = ~~ complex_value = ~~ RET description BEGIN
	SET parameter2 = parameter2 BAND 65535
	LPM ~opcode_mod_base~
	PATCH_IF NOT IS_AN_INT ~%value%~ OR value != 0 BEGIN
		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END

DEFINE_PATCH_MACRO ~opcode_mod_percent_base~ BEGIN
	PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
		PATCH_IF IS_AN_INT ~%value%~ BEGIN
			LPF ~signed_value~ INT_VAR value RET value END
		END
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
		SPRINT value @10010 // ~Passe à %value%~
	END
	ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN
		SPRINT value @10006 // ~Multiplié par %value%~
	END
	SPRINT value @10002 // ~%value% %~
	LPF ~getTranslation~ INT_VAR strref opcode RET name = string END
END

DEFINE_PATCH_FUNCTION ~opcode_mod_percent~ INT_VAR strref = 0 STR_VAR value = ~~ RET description BEGIN
	SET parameter2 = parameter2 BAND 65535
	LPM ~opcode_mod_percent_base~
	SPRINT description @100001 // ~%name%%colon%%value%~
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
			PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
			END
	        SPRINT description @102286 // ~Augmente %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
			PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
			END
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
			PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
			END
	        SPRINT description @102544 // ~d'augmenter %theStatistic% %ofTheTarget% de %value%~
        END
        ELSE BEGIN
            value = ABS value
			PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
			END
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
DEFINE_PATCH_MACRO ~opcode_self_resist~ BEGIN
	LOCAL_SET value = parameter1

	PATCH_IF parameter2 == MOD_TYPE_flat AND value == 100 BEGIN
		SET resistName += 1
		SPRINT resistName (AT resistName)
		SPRINT description @102547 // ~Immunité %resistName%~
	END
	ELSE BEGIN
		PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
			PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
			END
			ELSE BEGIN
				PATCH_IF value >= 0 BEGIN
					LPF ~signed_value~ INT_VAR value RET value END
				END
				SPRINT value @10002 // ~%value% %~
			END
		END
		ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
			PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
				SPRINT value @10010 // ~Passe à %value%~
			END
			ELSE BEGIN
				SPRINT value @10010 // ~Passe à %value%~
				SPRINT value @10002 // ~%value% %~
			END
		END
		ELSE PATCH_IF parameter2 == MOD_TYPE_percentage BEGIN // percent
			SPRINT value @10006 // ~Multiplié par %value%~
			SPRINT value @10002 // ~%value% %~
		END
		SPRINT name (AT resistName)
		SPRINT description @100001 // ~%name%%colon%%value%~
	END
END


DEFINE_PATCH_MACRO ~opcode_target_resist~ BEGIN
	LOCAL_SET value = parameter1

	PATCH_IF parameter2 == MOD_TYPE_flat AND value == 100 BEGIN
		SET resistName += 1
		SPRINT resistName (AT resistName)
		SPRINT description @102552 // ~d'immuniser %theTarget% %resistName%~
	END
	ELSE BEGIN
		SET resistName += 2
		SPRINT theStatistic (AT resistName)

		PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
			PATCH_IF value >= 0 OR NOT IS_AN_INT ~%value%~ BEGIN
				SPRINT value @10002 // ~%value% %~
				PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
					SPRINT value ~%complex_value%~
				END
				SPRINT description @102286 // ~Augmente de %value% %theStatistic% %ofTheTarget%~
			END
			ELSE BEGIN
				value = ABS value
				SPRINT value @10002 // ~%value% %~
				PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
					SPRINT value ~%complex_value%~
				END
				SPRINT description @102285 // ~Réduit de %value% %theStatistic% %ofTheTarget%~
			END
		END
		ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
			PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
			END
			ELSE BEGIN
				SPRINT value @10002 // ~%value% %~
			END
			SPRINT description @102287 // ~Porte à %value% %theStatistic% %ofTheTarget%~
		END
		ELSE BEGIN // percent
			SPRINT value @10002 // ~%value% %~
			SPRINT description @102288 // ~Multiplie par %value% %theStatistic% %ofTheTarget%~
		END
	END
END

/* --------------------------------------------------------- *
 * Gestion des modifications des résistances par probabilité *
 * --------------------------------------------------------- */
DEFINE_PATCH_MACRO ~opcode_probability_resist~ BEGIN
	LOCAL_SET value = parameter1

	PATCH_IF parameter2 == MOD_TYPE_flat AND value == 100 BEGIN
		SET resistName += 1
		SPRINT resistName (AT resistName)
		SPRINT description @102549 // ~d'immuniser %theTarget% %resistName%~
	END
	ELSE BEGIN
		SET resistName += 2
		SPRINT theStatistic (AT resistName)

		PATCH_IF parameter2 == MOD_TYPE_cumulative BEGIN
			PATCH_IF value >= 0 BEGIN
				SPRINT value @10002 // ~%value% %~
				PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
					SPRINT value ~%complex_value%~
				END
				SPRINT description @102544 // ~d'augmenter de %value% %theStatistic% %ofTheTarget%~
			END
			ELSE BEGIN
				value = ABS value
				SPRINT value @10002 // ~%value% %~
				PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
					SPRINT value ~%complex_value%~
				END
				SPRINT description @102543 // ~de réduire de %value% %theStatistic% %ofTheTarget%~
			END
		END
		ELSE PATCH_IF parameter2 == MOD_TYPE_flat BEGIN
			PATCH_IF NOT ~%complex_value%~ STRING_EQUAL ~~ BEGIN
				SPRINT value ~%complex_value%~
			END
			ELSE BEGIN
				SPRINT value @10002 // ~%value% %~
			END
			SPRINT description @102545 // ~de passer à %value% %theStatistic% %ofTheTarget%~
		END
		ELSE BEGIN // percent
			SPRINT value @10002 // ~%value% %~
			SPRINT description @102546 // ~de multiplier par %value% %theStatistic% %ofTheTarget%~
		END
	END
END

DEFINE_PATCH_MACRO ~opcode_not_cumulative~ BEGIN
    SPRINT notCumulative @102682 // ~non cumulatif~
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
			END
		END
		ELSE PATCH_IF showWarning BEGIN
			LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Resource %file%.spl doesn't exist.~ END
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_school~ INT_VAR school = 0 opcode = 0 RET spellSchoolName BEGIN
	SET strref = 100100 + school
	LPF ~getTranslation~ INT_VAR strref opcode RET spellSchoolName = string END
END

DEFINE_PATCH_FUNCTION ~get_spell_school_name~ INT_VAR school = 0 opcode = 0 RET spellSchoolName BEGIN
	SET strref = 100120 + school
	LPF ~getTranslation~ INT_VAR strref opcode RET spellSchoolName = string END
END

DEFINE_PATCH_FUNCTION ~get_spell_secondary_type~ INT_VAR secondaryType = 0 RET spellSecondaryTypeName BEGIN
	SET strref = 100200 + secondaryType
	PATCH_IF secondaryType > 13 OR secondaryType < 0 BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: secondary type (%secondaryType%) must be between 0 and 13 inclusive~ END
	END
	LPF ~getTranslation~ INT_VAR strref opcode RET spellSecondaryTypeName = string END
END

// Rajout d'un paramètre pour bloquer l'affichage du warning (dans le cas où l'objet n'a pas besoin d'exister (opcode 321))
// Va chercher le nom non identifié si le nom identifié n'existe pas
DEFINE_PATCH_FUNCTION ~get_item_name~ INT_VAR showWarning = 1 STR_VAR file = "" RET itemName BEGIN
	SPRINT itemName ~~
	SPRINT itemFilename ~%SOURCE_FILE%~
	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.itm~ BEGIN
		INNER_PATCH_FILE ~%file%.itm~ BEGIN
			READ_LONG ITM_identified_name itemNameRef
			PATCH_IF itemNameRef > 0 BEGIN
				READ_STRREF ITM_identified_name itemName
			END
			ELSE BEGIN
				READ_LONG ITM_unidentified_name itemNameRef
				PATCH_IF itemNameRef > 0 BEGIN
					READ_STRREF ITM_unidentified_name itemName
				END
			END
			/*
			ELSE BEGIN
				LPF ~add_log_warning~ STR_VAR message = EVAL ~%itemFilename% : Opcode %opcode% : Nom de l'objet introuvable pour %file%.itm.~ END
			END
			*/
		END
	END
	ELSE PATCH_IF showWarning BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Resource %file%.itm doesn't exist.~ END
	END
END

DEFINE_PATCH_FUNCTION ~item_can_stack~ STR_VAR file = "" RET canStack BEGIN
	SET canStack = 0
	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.itm~ BEGIN
		INNER_PATCH_FILE ~%file%.itm~ BEGIN
			READ_BYTE ITM_stack_amount nb_stack
			PATCH_IF nb_stack > 1 BEGIN
				SET canStack = 1
			END
		END
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
				SPRINT creatureName @102550 // ~Créature inconnue~
				LPF ~add_log_warning~ STR_VAR message = EVAL ~%itemFilename% : Opcode %opcode% : Nom de la créature introuvable pour %file%.cre~ END
			END
			*/
		END
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Resource %file%.cre doesn't exist.~ END
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

DEFINE_PATCH_FUNCTION ~get_creatures_amount~
	INT_VAR
		totalLevel = 0
		multiplier = 1
	STR_VAR
		file = ~~
	RET
		amount
		amountMin
		amountMax
BEGIN
	SET amount = 0
	SET amountMin = 0
	SET amountMax = 0

	PATCH_IF multiplier < 1 BEGIN
		SET multiplier = 1
	END

	LPF ~get_summon_limit~ RET limitNormal limitCelestial END

	INNER_PATCH_FILE ~%file%.2da~ BEGIN
		COUNT_2DA_ROWS ~2~ ~rows~
		FOR (row = 1 ; row < rows ; row = row + 1) BEGIN
			READ_2DA_ENTRY row 0 2 id
			READ_2DA_ENTRY row 1 2 resref

			PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.cre~ BEGIN
				INNER_PATCH_FILE ~%resref%.cre~ BEGIN
					READ_LONG CRE_XP_power_level powerLevel
					READ_LONG CRE_animation animation
					READ_BYTE CRE_allegiance allegiance
					READ_BYTE CRE_gender gender

					SET count = (totalLevel * 10 / powerLevel)
					// Summon until Creature Power Level equals/exceeds Number
					SET remains = count MODULO 10
					SET count /= 10
					PATCH_IF remains > 0 BEGIN
						SET count += 1
					END
					SET limit = 0
					// NORMAL = (EA <= 15 and EA != FAMILIAR) and (GENDER == SUMMONED or GENDER == SUMMONED_DEMON)
					PATCH_IF (allegiance <= 15 AND allegiance != 3) AND (gender == 6 OR gender == 9) BEGIN
						SET limit = limitNormal
					END
					// CELESTIAL = resref IN ["DEVAGOOD", "DEVAEVIL", "PLANGOOD", "PLANEVIL"] OR ((EA <= 15 and EA != FAMILIAR) and (GENDER == BOTH) and (animationID == 0x7F3B or animationID == 0x7F3C))
					ELSE PATCH_IF ("%resref%" STRING_MATCHES_REGEXP "^\(DEVAGOOD\|DEVAEVIL\|PLANGOOD\|PLANEVIL\)$") == 0 OR ((allegiance <= 15 AND allegiance != 3) AND gender == 5 AND (animation == 0x7F3B OR animation == 0x7F3C)) BEGIN
						SET limit = limitNormal
					END
					PATCH_IF count == 0 BEGIN
						SET count = 1
					END
					PATCH_IF count > limit BEGIN
						SET count = limit
					END

					PATCH_IF amountMin == 0 OR amountMin > count BEGIN
						SET amountMin = count
					END
					PATCH_IF amountMax == 0 OR amountMax < count BEGIN
						SET amountMax = count
					END
				END
			END
		END
		SET amount    *= multiplier
		SET amountMin *= multiplier
		SET amountMax *= multiplier
		PATCH_IF amountMin == amountMax BEGIN
			SET amount = amountMin
		END
		ELSE BEGIN
			SPRINT amount @101130 // ~entre %amountMin% et %amountMax%~
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_summon_limit~
	RET
		limitNormal
		limitCelestial
BEGIN
	SET limitNormal = 5
	SET limitCelestial = 1

	PATCH_IF FILE_EXISTS_IN_GAME ~summlimt.2da~ BEGIN
		INNER_PATCH_FILE ~summlimt.2da~ BEGIN
			COUNT_2DA_COLS numCols
			COUNT_2DA_ROWS numCols numRows
			FOR (row = 0; row < numRows; row += 1) BEGIN
				READ_2DA_ENTRY row 0 numCols type
				PATCH_IF (~%type%~ STR_EQ ~NORMAL~) BEGIN
					READ_2DA_ENTRY row 1 numCols limitNormal
				END
				ELSE BEGIN
					READ_2DA_ENTRY row 1 numCols limitCelestial
				END
			END
		END
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
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode% : Resource %file%.cre doesn't exist.~ END
	END
END

DEFINE_PATCH_FUNCTION ~opcode_self_42_62~ INT_VAR level = 0 amount = 0 spellTypes = 1 startStrref = 0 RET description BEGIN
	SPRINT levelStr ~~

	PATCH_IF amount > 32768 BEGIN
		SET amount = amount - 65536
	END

	PATCH_IF level == 0 BEGIN
		// Double le nombre de sorts de niveau amount et moins (pas de binaire ici !)
		SET amount = amount > spellLevelMax ? spellLevelMax : amount
		PATCH_IF amount > 0 BEGIN
			LPM ~opcode_self_42_62_get_levelstr~
			LPF ~get_spell_type_str~ INT_VAR value = spellTypes cleric_druid_limitation = 1 STR_VAR final_glue = ~/~ RET spellType END
			SET strref = startStrref + 4
			LPF ~getTranslation~ INT_VAR strref opcode RET description = string END //~Double le nombre de sorts [profanes|divins] mémorisables de niveau inférieur ou égal à %levelStr%~
		END
	END
	ELSE PATCH_IF level == 512 BEGIN
		// Double le niveau de sorts de niveau amount
		PATCH_IF amount > 0 AND amount <= spellLevelMax BEGIN
			LPF ~get_spell_type_str~ INT_VAR value = spellTypes cleric_druid_limitation = 1 STR_VAR final_glue = ~/~ RET spellType END
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
		LPF ~get_spell_type_str~ INT_VAR value = spellTypes singular = ABS amount == 1 cleric_druid_limitation = 1 STR_VAR final_glue = ~/~ RET spellType END
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
	LOCAL_SET strref = 0
	SPRINT levelStr ~~
	SPRINT and @100021 // ~et~
	PATCH_DEFINE_ARRAY ~levels~ BEGIN END

	PATCH_IF level == 0 BEGIN
		FOR (idx = 1 ; idx <= amount ; ++idx) BEGIN
			SET strref = 101200 + idx
			SPRINT levelStr (AT strref)
			SPRINT $levels(~%levelStr%~) ~~
		END
	END
	ELSE BEGIN
		FOR (idx = 0 ; idx < spellLevelMax ; ++idx) BEGIN
			SET bit = EVAL ~%BIT%idx%%~
			PATCH_IF (level BAND bit) != 0 BEGIN
				SET strref = 101200 + idx + 1
				SPRINT levelStr (AT strref)
				SPRINT $levels(~%levelStr%~) ~~
			END
		END
	END

	LPF ~implode~ STR_VAR array_name = ~levels~ glue = ~, ~ final_glue = ~ %and% ~ RET levelStr = text END
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
		// si une entrée n'est pas définie dans le fichier ids, elle peut quand même l'être dans les strrefs
		LPF ~get_ids_strref~ INT_VAR entry file RET strref END
		LPF ~getTranslation~ INT_VAR strref opcode RET idName = string END
	END
	ELSE BEGIN
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Wrong ids file : %file%~ END
	END
END

DEFINE_PATCH_FUNCTION ~get_ids_strref~ INT_VAR entry = 0 file = 0 RET strref BEGIN
	SET strref = 200000 + (file * 1000) + entry
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

DEFINE_PATCH_MACRO ~opcode_modstat1_is_valid~ BEGIN
	LPM ~opcode_modstat_is_valid~
	PATCH_IF parameter2 < MOD_TYPE_cumulative OR parameter2 > MOD_TYPE_flat BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown type %parameter2%.~ END
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

DEFINE_PATCH_MACRO ~opcode_idscheck9_is_valid~ BEGIN
	LPM ~opcode_modstat_is_valid~
	PATCH_IF parameter2 < 2 OR parameter2 > 9 OR (parameter2 > 8 AND is_ee == 0) BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown IDS file %parameter2%.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_idscheck8_is_valid~ BEGIN
	LPM ~opcode_modstat_is_valid~
	PATCH_IF parameter2 < 2 OR parameter2 > 8 BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Unknown IDS file %parameter2%.~ END
	END
END

DEFINE_PATCH_MACRO ~opcode_resref_is_valid~ BEGIN
	PATCH_IF ~%resref%~ STRING_EQUAL ~~ BEGIN
		SET isValid = 0
		LPF ~add_log_error~ STR_VAR message = EVAL ~Opcode %opcode%: Resource key is empty.~ END
	END
END

/**
 * Si tous les effets contenus dans listOpcodes ont les mêmes paramètres, chacun de ces effets est supprimés, et un
 * effet [newOpcode] est créé avec ces mêmes paramètres.
 */
DEFINE_PATCH_MACRO ~group_opcode_with_same_parameters~ BEGIN
	LOCAL_SET group = 1
	LOCAL_SET currentOpcode = opcode
	PATCH_PHP_EACH EVAL ~opcodes_%opcode%~ AS data => _ BEGIN
		LPM ~data_to_vars~
		SET group = 1
		CLEAR_ARRAY positions
		// On ajoute l'opcode courant à ceux qui seront désactivés
		PATCH_DEFINE_ASSOCIATIVE_ARRAY ~positions~ BEGIN
			~%opcode%~ => ~%position%~
		END

		PATCH_PHP_EACH ~listOpcodes~ AS _ => opcode BEGIN
			LPF ~get_opcode_position~
				INT_VAR opcode
		            match_target       = target
		            match_power        = power
			        match_parameter1   = parameter1
			        match_parameter2   = parameter2
			        match_parameter3   = parameter3
			        match_parameter4   = parameter4
			        match_timingMode   = timingMode
			        match_resistance   = resistance
					match_duration     = duration
			        match_probability1 = probability1
			        match_probability2 = probability2
			        match_diceCount    = diceCount
			        match_diceSides    = diceSides
			        match_saveType     = saveType
			        match_saveBonus    = saveBonus
			        match_special      = special
				STR_VAR match_macro = ~opcode_match_diceCount_and_diceSides_and_duration_and_parameter1_and_parameter2_and_parameter3_and_parameter4_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~
				RET opcodePosition = position
			END

			SET $positions(~%opcode%~) = opcodePosition

			PATCH_IF opcodePosition < 0 BEGIN
				SET group = 0
			END
		END

		PATCH_IF group == 1 BEGIN
			// Suppression des effets similaires
			PATCH_PHP_EACH positions AS opcode => position1 BEGIN
				LPF ~delete_opcode~
					INT_VAR opcode match_position = position1
					RET $opcodes(~%opcode%~) = count
					RET_ARRAY EVAL ~opcodes_%opcode%~ = opcodes_xx
				END
			END
			SET opcode = newOpcode
            LPM ~add_opcode~
		END
		SET opcode = currentOpcode
	END

	CLEAR_ARRAY listOpcodes
	// Nécessaire de remettre le numéro original pour les itérations suivantes
	SET opcode = currentOpcode
END


// Comment trouver les correspondances sans checker tous les sorts ??

DEFINE_PATCH_FUNCTION ~get_projectile_name~ INT_VAR projectile = 0 RET projref BEGIN
	SET projref = 0
	PATCH_MATCH projectile WITH
		1 2 3 4 5 101 102 187 283 284 285 286 287 288 289 290 291
			BEGIN SET projref = 300001 END // ~flèches~
		6 7 8 9 10 292 293 294 295 296
			BEGIN SET projref = 300006 END // ~haches de jet~
		11 12 13 14 15 225 240 297 298 299 300 301 302 303
			BEGIN SET projref = 300011 END // ~carreaux~
		16 17 18 19 20 263 304 305 306 307 308
			BEGIN SET projref = 300016 END // ~billes~
		23
			BEGIN SET projref = 300023 END // ~orbes chromatiques~
		26 27 28 29 30 309 310 311 312
			BEGIN SET projref = 300026 END // ~dagues de jet~
		31 32 33 34 35 244 313 314 315 316 317 318
			BEGIN SET projref = 300031 END // ~fléchettes~
		36 67 68 69 70 71 72 73 74 75 76 77
			BEGIN SET projref = 300036 END // ~projectiles magiques~
		39 80 81 82 83 84 85 86 87 88 89 90 92 205 206 212 219 442
			BEGIN SET projref = 300039 END // ~éclairs~
		55 56 57 58 59
			BEGIN SET projref = 300055 END // ~lances de jet~
		62 63 259 319
			BEGIN SET projref = 300062 END // ~toiles d'araignées~
		64 274
			BEGIN SET projref = 300064 END // ~attaques de regard~
		94
			BEGIN SET projref = 300094 END // ~nuages puants~
		208
			BEGIN SET projref = 300208 END // ~rayons des spectateurs~
		218
			BEGIN SET projref = 300218 END // ~désintégrations~
		226 227 229 232
			BEGIN SET projref = 300227 END // ~nuées d'insectes~
		320
			BEGIN SET projref = 0 END // Aucune correspondance connue
		DEFAULT
			LPF ~add_log_warning~ STR_VAR message = EVAL ~Opcode %opcode% : Réflection du type de projectile '%projectile%'~ END
	END
END

DEFINE_PATCH_FUNCTION ~side_spell~ INT_VAR strref = 0 strref_if_amount_0 = 0 amount = 0 RET string BEGIN
	PATCH_IF is_ee BEGIN
		SPRINT spellName ~~
		PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ BEGIN
			LPF ~get_spell_name~ STR_VAR file = EVAL ~%resref%~ RET spellName END
		END
		ELSE BEGIN
			SET strLen = STRING_LENGTH ~%CURRENT_SOURCE_RES%~
			PATCH_IF strLen <= 7 BEGIN
				LPF ~get_spell_name~ INT_VAR showWarning = 0 STR_VAR file = EVAL ~%CURRENT_SOURCE_RES%B~ RET spellName END
			END
		END

		PATCH_IF amount >= 1 BEGIN
			LPF ~getTranslation~ INT_VAR strref RET string END
		END

		PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ BEGIN
			PATCH_IF amount >= 1 BEGIN
				SET strref = 110011 // ~puis lance %spellName%~
				LPF ~getTranslation~ INT_VAR strref RET descAdd = string END
				TEXT_SPRINT string ~%string% %descAdd%~
			END
			ELSE BEGIN
				SET strref = strref_if_amount_0 // ~Lance %spellName%~
				LPF ~getTranslation~ INT_VAR strref RET string END
			END
		END
	END
	ELSE BEGIN
		LPF ~getTranslation~ INT_VAR strref RET string END
	END
END

DEFINE_PATCH_FUNCTION ~get_states_str~ INT_VAR state = 0 RET descriptionState BEGIN
	SPRINT descriptionState ~~
	SET hexValue = 0b1
	SET initRef = 410000
	SPRINT sep @100004 // ~ou~
	FOR (i = 1 ; i <= 32 ; ++i) BEGIN
		PATCH_IF state BAND hexValue BEGIN
			SET strref = initRef + i
			LPF ~getTranslation~ INT_VAR strref RET stateRef = string END
			PATCH_IF ~%descriptionState%~ STRING_EQUAL ~~ BEGIN
				SPRINT descriptionState ~%stateRef%~
			END
			ELSE BEGIN
				SPRINT descriptionState ~%descriptionState% %sep% %stateRef%~
			END
		END
		SET hexValue <<= 1
	END
	PATCH_IF ~%descriptionState%~ STRING_EQUAL ~~ BEGIN
		SPRINT descriptionState @410000 // ~normal~
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_type_str~ INT_VAR value = 0 singular = 0 cleric_druid_limitation = 0 STR_VAR final_glue = ~~ RET spellType BEGIN
	PATCH_IF ~%final_glue%~ STRING_EQUAL ~~ BEGIN
		SPRINT final_glue @100021 // ~et~
		SPRINT final_glue ~ %final_glue% ~
	END
	SET offset = singular > 0 ? 10 : 0
	PATCH_DEFINE_ARRAY ~spellTypes~ BEGIN END
	FOR (idx = 0 ; idx < 3 ; ++idx) BEGIN
		SET bit = EVAL ~%BIT%idx%%~
		PATCH_IF (value BAND bit) != 0 BEGIN
			PATCH_IF idx == 1 BEGIN
				SET clericCanUse = 1
				SET druidCanUse = 1
				PATCH_IF isItem AND cleric_druid_limitation BEGIN
					LPF ~cleric_can_use_item~ RET clericCanUse = canUse END
					LPF ~druid_can_use_item~ RET druidCanUse = canUse END
					PATCH_IF !druidCanUse AND !clericCanUse BEGIN
						LPF ~add_log_warning~ STR_VAR message = ~Opcode %opcode%: Item not usable by cleric or druid.~ END
					END
				END
				PATCH_IF cleric_druid_limitation AND clericCanUse AND druidCanUse BEGIN
					SET strref = 101305 + offset // ~divins/druidiques~
					SPRINT spellTypeStr (AT strref)
					SPRINT $spellTypes(~%spellTypeStr%~) ~~
				END
				ELSE BEGIN
					PATCH_IF clericCanUse BEGIN
						SET strref = 101301 + offset // ~divins~
						SPRINT spellTypeStr (AT strref)
						SPRINT $spellTypes(~%spellTypeStr%~) ~~
					END
					PATCH_IF druidCanUse BEGIN
						SET strref = 101304 + offset // ~druidiques~
						SPRINT spellTypeStr (AT strref)
						SPRINT $spellTypes(~%spellTypeStr%~) ~~
					END
				END
			END
			ELSE BEGIN
				SET strref = 101300 + idx + offset
				SPRINT spellTypeStr (AT strref)
				SPRINT $spellTypes(~%spellTypeStr%~) ~~
			END
		END
	END
	LPF ~implode~ STR_VAR array_name = ~spellTypes~ glue = ~, ~ final_glue RET spellType = text END
END

DEFINE_PATCH_FUNCTION ~get_splstate_name~ INT_VAR strref = 0 opcode = 0 splstate = 0 RET splstateName BEGIN
	PATCH_TRY
        LPF ~getTranslation~ INT_VAR strref opcode warning = 0 RET splstateName = string END
	WITH DEFAULT
		LPF ~get_splstate_name_mod~ INT_VAR splstate RET splstateName END
	END
END

DEFINE_PATCH_FUNCTION ~get_frequency_duration~ INT_VAR duration = 0 strref = 100320 RET frequency BEGIN // ~par %strDuration%~
	LPF ~get_str_duration~ INT_VAR duration RET strDuration END
	PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^1 ~ == 0 BEGIN
		INNER_PATCH_SAVE strDuration ~%strDuration%~ BEGIN
			REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~^1 ~ ~~
		END
	END
	ELSE BEGIN
		// FIXME: données en français et genrées => traduction impossible
		PATCH_IF ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ heure~ == 0 OR ~%strDuration%~ STRING_MATCHES_REGEXP ~^[0-9]+ seconde~ == 0 BEGIN
			SET strref = 100321 // ~toutes les %strDuration%~
		END
		ELSE BEGIN
			SET strref = 100322 // ~tous les %strDuration%~
		END
	END
	SPRINT frequency (AT strref)
END

DEFINE_PATCH_MACRO ~opcode_match_except_parameter1_and_parameter2~ BEGIN
	SET match = (
	        match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        // AND match_parameter1   == parameter1
        // AND match_parameter2   == parameter2
        AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_probability  == probability
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_except_parameter2~ BEGIN
	SET match = (
	        match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        AND match_parameter1   == parameter1
        // AND match_parameter2   == parameter2
        AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_probability  == probability
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_except_parameter1_and_duration~ BEGIN
	SET match = (
	        match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        // AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        // AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_probability  == probability
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END
DEFINE_PATCH_MACRO ~opcode_match_except_diceCount_and_duration~ BEGIN
	SET match = (
	        match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        // AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_probability  == probability
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        // AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_except_diceCount_and_duration_and_parameter1~ BEGIN
	SET match = (
	        match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        // AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        // AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_probability  == probability
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        // AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match~ BEGIN
	SET match = (
	        match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_probability  == probability
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_except_duration~ BEGIN
	SET match = (
			match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        // AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_probability  == probability
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_except_saveBonus~ BEGIN
	SET match = (
			match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_probability  == probability
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        // AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_diceCount_and_diceSides_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_target~ BEGIN
	SET match = (
            match_target       == target
        AND match_power        == power
        AND match_resistance   == resistance
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
    )
END

DEFINE_PATCH_MACRO ~opcode_match_duration_and_parameter1_and_parameter2_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~ BEGIN
	SET match = (
            match_target       == target
        AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
		AND match_duration     == duration
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_diceCount_and_diceSides_and_duration_and_parameter1_and_parameter2_and_parameter3_and_parameter4_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~ BEGIN
	SET match = (
            match_target       == target
        AND match_power        == power
        AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
		AND match_duration     == duration
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_diceCount_and_diceSides_and_duration_and_parameter1_and_parameter3_and_parameter4_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~ BEGIN
	SET match = (
            match_target       == target
        AND match_power        == power
        AND match_parameter1   == parameter1
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
		AND match_duration     == duration
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_not_position_and_diceCount_and_diceSides_and_duration_and_parameter2_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_target_and_timingMode~ BEGIN
	SET match = (
            match_position     != position
        AND match_target       == target
        AND match_parameter2   == parameter2
        AND match_power        == power
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
		AND match_duration     == duration
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
    )
END

DEFINE_PATCH_MACRO ~opcode_match_diceCount_and_diceSides_and_duration_and_parameter2_and_parameter3_and_parameter4_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_special_and_target_and_timingMode~ BEGIN
	SET match = (
            match_target       == target
        AND match_power        == power
        AND match_parameter2   == parameter2
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
		AND match_duration     == duration
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_diceCount_and_diceSides_and_duration_and_power_and_probability1_and_probability2_and_resistance_and_saveBonus_and_saveType_and_target_and_timingMode~ BEGIN
	SET match = (
            match_target       == target
        AND match_power        == power
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
		AND match_duration     == duration
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
    )
END

DEFINE_PATCH_MACRO ~opcode_match_diceCount_and_diceSides_and_power_and_probability1_and_probability2_and_resref_and_target_saveBonus_and_saveType~ BEGIN
	SET match = (
            match_target       == target
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_power        == power
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND ~%match_resref%~   STRING_EQUAL_CASE ~%resref%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_diceCount_and_diceSides_and_power_and_probability1_and_probability2_and_resistance_and_resref_and_target_and_saveBonus_and_saveType~ BEGIN
	SET match = (
            match_target       == target
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_power        == power
        AND match_resistance   == resistance
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND ~%match_resref%~   STRING_EQUAL_CASE ~%resref%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_duration_and_probability1_and_probability2_and_resistance_and_resref_and_target_and_timingMode_and_saveBonus_and_saveType_and_special~ BEGIN
	SET match = (
            match_target       == target
        AND ~%match_resref%~   STRING_EQUAL_CASE ~%resref%~
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_duration     == duration
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_duration_and_probability1_and_probability2_and_resistance_and_target_and_timingMode_and_saveBonus_and_saveType_and_special~ BEGIN
	SET match = (
            match_target       == target
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        AND match_duration     == duration
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_duration_and_timingMode~ BEGIN
	SET match = (
			match_duration   == duration
        AND match_timingMode == timingMode
    )
END

DEFINE_PATCH_MACRO ~opcode_match_parameter1_and_parameter2~ BEGIN
	SET match = (
			match_parameter1 == parameter1
        AND match_parameter2 == parameter2
    )
END

DEFINE_PATCH_MACRO ~opcode_match_parameter2_and_position~ BEGIN
	SET match = (
			match_position   == position
        AND match_parameter2 == parameter2
    )
END

DEFINE_PATCH_MACRO ~opcode_match_parameter1_and_parameter2_and_probability1_and_probability2_and_saveBonus_and_saveType_and_target~ BEGIN
	SET match = (
			match_parameter1   == parameter1
		AND match_parameter2   == parameter2
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_saveBonus    == saveBonus
        AND match_saveType     == saveType
        AND match_target       == target
    )
END

DEFINE_PATCH_MACRO ~opcode_match_probability1_and_probability2_and_target~ BEGIN
	SET match = (
			match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_target       == target
    )
END

DEFINE_PATCH_MACRO ~opcode_match_parameter2_and_probability1_and_probability2_and_target~ BEGIN
	SET match = (
			match_parameter2   == parameter2
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_target       == target
    )
END

DEFINE_PATCH_MACRO ~opcode_match_parameter2_and_probability1_and_probability2_and_saveBonus_and_saveType_and_target~ BEGIN
	SET match = (
			match_parameter2   == parameter2
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_saveBonus    == saveBonus
        AND match_saveType     == saveType
        AND match_target       == target
    )
END

DEFINE_PATCH_MACRO ~opcode_match_parameter2_and_probability~ BEGIN
	SET match = (
			match_parameter2  == parameter2
        AND match_probability == probability
    )
END

DEFINE_PATCH_MACRO ~opcode_match_parameter2_and_probability_and_target~ BEGIN
	SET match = (
			match_parameter2  == parameter2
        AND match_probability == probability
        AND match_target      == target
    )
END

DEFINE_PATCH_MACRO ~opcode_match_position~ BEGIN
	SET match = (
		match_position == position
    )
END

DEFINE_PATCH_MACRO ~opcode_match_probability1_and_probability2~ BEGIN
	SET match = (
			match_probability1 == probability1
        AND match_probability2 == probability2
    )
END

DEFINE_PATCH_MACRO ~opcode_match_probability1_and_probability2_and_saveBonus_and_saveType_and_target~ BEGIN
	SET match = (
			match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_saveBonus    == saveBonus
        AND match_saveType     == saveType
        AND match_target       == target
    )
END

DEFINE_PATCH_MACRO ~opcode_match_resref~ BEGIN
	SET match = (
		~%match_resref%~ STRING_EQUAL_CASE ~%resref%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_12_group~ BEGIN
	SET match = (
			match_position     != position
	    AND match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        AND match_duration     == duration
        AND match_timingMode   == timingMode
        // AND match_resistance   == resistance
        AND match_probability  == probability
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        // AND match_saveType     == saveType
        // AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_60_145_group~ BEGIN
	// ~NOT position = %position% AND custom_int = 0 AND target = %target% AND power = %power% AND parameter1 = %parameter1% AND parameter2 = %spellType% AND parameter3 = %parameter3% AND parameter4 = %parameter4% AND timingMode = %timingMode% AND resistance = %resistance% AND duration = %duration% AND probability1 = %probability1% AND probability2 = %probability2% AND diceCount = %diceCount% AND diceSides = %diceSides% AND saveType = %saveType% AND saveBonus = %saveBonus% AND special = %special%~
	SET match = (
		    match_position     != position
		AND match_custom_int   == custom_int
		AND match_target       == target
		AND match_probability1 == probability1
		AND match_probability2 == probability2
		AND match_parameter1   == parameter1
		AND match_parameter2   == parameter2
		AND match_parameter3   == parameter3
		AND match_parameter4   == parameter4
		AND match_timingMode   == timingMode
		AND match_resistance   == resistance
		AND match_duration     == duration
		AND match_power        == power
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
		AND match_saveType     == saveType
		AND match_saveBonus    == saveBonus
		AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_67_group~ BEGIN
	SET match = (
		    match_position     != position
		AND match_target       == target
		AND match_power        == power
		AND match_parameter1   == parameter1
		AND match_parameter2   == parameter2
		AND match_parameter3   == parameter3
		AND match_parameter4   == parameter4
		AND match_timingMode   == timingMode
		AND match_resistance   == resistance
		AND match_duration     == duration
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
		AND match_saveType     == saveType
		AND match_saveBonus    == saveBonus
		AND match_special      == special
        AND ~%match_resref%~   STRING_EQUAL_CASE ~%resref%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_78_group~ BEGIN
	// ~NOT position = %position% AND target = %target% AND power = %power% AND parameter1 = %parameter1% AND parameter2 = %attribute% AND parameter3 = %parameter3% AND parameter4 = %parameter4% AND timingMode = %timingMode% AND resistance = %resistance% AND duration = %duration% AND probability1 = %probability1% AND probability2 = %probability2% AND diceCount = %diceCount% AND diceSides = %diceSides% AND saveType = %saveType% AND saveBonus = %saveBonus% AND special = %special%~
	SET match = (
		    match_position     != position
		AND match_target       == target
		AND match_power        == power
		AND match_parameter1   == parameter1
		AND match_parameter2   == parameter2
		AND match_parameter3   == parameter3
		AND match_parameter4   == parameter4
		AND match_timingMode   == timingMode
		AND match_resistance   == resistance
		AND match_duration     == duration
		AND match_probability1 == probability1
		AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
		AND match_saveType     == saveType
		AND match_saveBonus    == saveBonus
		AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_101_group~ BEGIN
	// ~parameter1 > 99 AND (parameter2 = %MOD_TYPE_flat% OR parameter2 = %MOD_TYPE_cumulative%) AND probability1 = %probability1% AND probability2 = %probability2% AND target = %target% AND saveType = %saveType% AND saveBonus = %saveBonus%~
	SET match = (
			parameter1 > 99
		AND (
				MOD_TYPE_flat      == parameter2
			OR MOD_TYPE_cumulative == parameter2
		)
		AND match_probability1 == probability1
		AND match_probability2 == probability2
		AND match_target       == target
		AND match_saveType     == saveType
		AND match_saveBonus    == saveBonus
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_112_group~ BEGIN
	SET match = (
			match_position       == position
        AND match_duration       == duration
        AND NOT match_custom_int == custom_int
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_127_group~ BEGIN
	SET match = (
	        match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        // AND match_parameter1   == parameter1
        AND match_parameter2   == parameter2
        AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        // AND match_probability  == probability
        // AND match_probability1 == probability1
        // AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        // AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_146_group~ BEGIN
	// ~position < %position% AND resref = %resref% AND target = %target% AND timingMode = %timingMode% AND resistance = %resistance% AND duration = %duration% AND probability1 = %probability1% AND probability2 = %probability2% AND saveType = %saveType% AND saveBonus = %saveBonus% AND special = %special%~
	SET match = (
			position < match_position
        AND ~%match_resref%~   STRING_EQUAL_CASE ~%resref%~
		AND match_target       == target
		AND match_timingMode   == timingMode
		AND match_resistance   == resistance
		AND match_duration     == duration
		AND match_probability1 == probability1
		AND match_probability2 == probability2
		AND match_saveType     == saveType
		AND match_saveBonus    == saveBonus
		AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_154_group~ BEGIN
	// ~parameter1 = 0 AND (parameter2 = 1 OR parameter2 = 2 OR parameter2 = 5) AND target=%target% AND timingMode=%timingMode% AND duration=%duration% AND probability1=%probability1% AND probability2=%probability2% AND diceCount=%diceCount% AND diceSides=%diceSides% AND power=%power% AND saveType=%saveType% AND saveBonus=%saveBonus% AND resistance=%resistance%~
	SET match = (
			0 == parameter1
        AND (
	           1 == parameter2
	        OR 2 == parameter2
	        OR 5 == parameter2
	    )
	    AND match_target       == target
        AND match_timingMode   == timingMode
        AND match_duration     == duration
        AND match_probability1 == probability1
        AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_power        == power
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_resistance   == resistance
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_159_group~ BEGIN
	SET match = (
	        match_isExternal   == isExternal
        AND match_target       == target
        AND match_power        == power
        // AND match_parameter1   == parameter1
        // AND match_parameter2   == parameter2
        AND match_duration     == duration
        AND match_timingMode   == timingMode
        AND match_resistance   == resistance
        // AND match_probability  == probability
        // AND match_probability1 == probability1
        // AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
        AND match_saveType     == saveType
        AND match_saveBonus    == saveBonus
        AND match_special      == special
        AND match_parameter3   == parameter3
        AND match_parameter4   == parameter4
        AND match_custom_int   == custom_int
        AND ~%match_resref%~     STRING_EQUAL_CASE ~%resref%~
        AND ~%match_resref2%~    STRING_EQUAL_CASE ~%resref2%~
        AND ~%match_resref3%~    STRING_EQUAL_CASE ~%resref3%~
        AND ~%match_custom_str%~ STRING_EQUAL_CASE ~%custom_str%~
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_236_group~ BEGIN
	SET match = (
		    match_position     != position
		AND match_target       == target
		AND match_power        == power
		AND match_parameter1   == parameter1
		AND match_parameter3   == parameter3
		AND match_parameter4   == parameter4
		AND match_timingMode   == timingMode
		AND match_resistance   == resistance
		AND match_duration     == duration
		// AND match_probability1 == probability1
		AND match_probability2 == 0
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
		AND match_saveType     == saveType
		AND match_saveBonus    == saveBonus
		AND match_special      == special
    )
END

DEFINE_PATCH_MACRO ~opcode_match_opcode_259_group~ BEGIN
	// ~NOT position = %position% AND target = %target% AND power = %power% AND parameter1 = %parameter1% AND parameter3 = %parameter3% AND parameter4 = %parameter4% AND timingMode = %timingMode% AND resistance = %resistance% AND duration = %duration% AND probability1 = %probability1% AND probability2 = %probability2% AND diceCount = %diceCount% AND diceSides = %diceSides% AND saveType = %saveType% AND saveBonus = %saveBonus% AND special = %special%~
	SET match = (
		    match_position     != position
		AND match_target       == target
		AND match_power        == power
		AND match_parameter1   == parameter1
		AND match_parameter3   == parameter3
		AND match_parameter4   == parameter4
		AND match_timingMode   == timingMode
		AND match_resistance   == resistance
		AND match_duration     == duration
		AND match_probability1 == probability1
		AND match_probability2 == probability2
        AND match_diceCount    == diceCount
        AND match_diceSides    == diceSides
		AND match_saveType     == saveType
		AND match_saveBonus    == saveBonus
		AND match_special      == special
    )
END