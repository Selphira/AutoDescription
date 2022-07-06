/* =============================================================== *
 * Gestion de la section "[Non] Utilisable par" de la description. *
 * =============================================================== */

DEFINE_PATCH_MACRO ~moral_alignments~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY array_usabilities BEGIN
		EVIL,    "BIT1" => 1 // ~mauvais~
		GOOD,    "BIT2" => 1 // ~bon~
		NEUTRAL, "BIT3" => 1 // ~neutre~
	END
END

DEFINE_PATCH_MACRO ~social_alignments~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY array_usabilities BEGIN
		CHAOTIC, "BIT0" => 1 // ~chaotique~
		NEUTRAL, "BIT4" => 1 // ~neutre~
		LOYAL,   "BIT5" => 1 // ~loyal~
	END
END

DEFINE_PATCH_MACRO ~races~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY array_usabilities BEGIN
		ELF,      "BIT23" => 1 // ~Elfe~
		DWARF,    "BIT24" => 1 // ~Nain~
		HALF_ELF, "BIT25" => 1 // ~Demi-Elfe~
		HALFLING, "BIT26" => 1 // ~Petite-personne~
		HUMAN,    "BIT27" => 1 // ~Humain~
		GNOME,    "BIT28" => 1 // ~Gnome~
		HALFORC,  "BIT31" => 1 // ~Demi-Orque~
	END
END

DEFINE_PATCH_MACRO ~classes~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY classes BEGIN
	    BARD,    "BIT6",  0, 1 => 1 // ~Barde~
		CLERIC,  "BIT7",  1, 1 => 1 // ~Clerc~
		DRUID,   "BIT30", 1, 1 => 1 // ~Druide~
		FIGHTER, "BIT11", 1, 1 => 1 // ~Guerrier~
		MAGE,    "BIT18", 1, 1 => 1 // ~Mage~
		101129,  "BIT18", 0, 0 => 1 // ~Sorcier~
		MONK,    "BIT29", 0, 0 => 1 // ~Moine~
		PALADIN, "BIT20", 0, 1 => 1 // ~Paladin~
		RANGER,  "BIT21", 0, 1 => 1 // ~Rôdeur~
		THIEF,   "BIT22", 1, 1 => 1 // ~Voleur~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY useMulticlasses BEGIN
		CLERIC_MAGE         => 1 // ~Clerc / Mage~
	    CLERIC_THIEF        => 1 // ~Clerc / Voleur~
		CLERIC_RANGER       => 1 // ~Clerc / Rôdeur~
		FIGHTER_DRUID       => 1 // ~Guerrier / Druide~
		FIGHTER_MAGE        => 1 // ~Guerrier / Mage~
		FIGHTER_CLERIC      => 1 // ~Guerrier / Clerc~
		FIGHTER_MAGE_CLERIC => 1 // ~Guerrier / Mage / Clerc~
		FIGHTER_MAGE_THIEF  => 1 // ~Guerrier / Mage / Voleur~
		FIGHTER_THIEF       => 1 // ~Guerrier / Voleur~
		MAGE_THIEF          => 1 // ~Mage / Voleur~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY unuseMulticlasses BEGIN
		CLERIC_MAGE         => 1 // ~Clerc / Mage~
	    CLERIC_THIEF        => 1 // ~Clerc / Voleur~
		CLERIC_RANGER       => 1 // ~Clerc / Rôdeur~
		FIGHTER_DRUID       => 1 // ~Guerrier / Druide~
		FIGHTER_MAGE        => 1 // ~Guerrier / Mage~
		FIGHTER_CLERIC      => 1 // ~Guerrier / Clerc~
		FIGHTER_MAGE_CLERIC => 1 // ~Guerrier / Mage / Clerc~
		FIGHTER_MAGE_THIEF  => 1 // ~Guerrier / Mage / Voleur~
		FIGHTER_THIEF       => 1 // ~Guerrier / Voleur~
		MAGE_THIEF          => 1 // ~Mage / Voleur~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY cleric_class_group BEGIN
		CLERIC_MAGE,         "BIT8"  => 1 // ~Clerc / Mage~
	    CLERIC_THIEF,        "BIT9"  => 1 // ~Clerc / Voleur~
		CLERIC_RANGER,       "BIT10" => 1 // ~Clerc / Rôdeur~
		FIGHTER_CLERIC,      "BIT14" => 1 // ~Guerrier / Clerc~
		FIGHTER_MAGE_CLERIC, "BIT15" => 1 // ~Guerrier / Mage / Clerc~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY fighter_class_group BEGIN
		FIGHTER_DRUID,       "BIT12" => 1 // ~Guerrier / Druide~
		FIGHTER_MAGE,        "BIT13" => 1 // ~Guerrier / Mage~
		FIGHTER_CLERIC,      "BIT14" => 1 // ~Guerrier / Clerc~
		FIGHTER_MAGE_CLERIC, "BIT15" => 1 // ~Guerrier / Mage / Clerc~
		FIGHTER_MAGE_THIEF,  "BIT16" => 1 // ~Guerrier / Mage / Voleur~
		FIGHTER_THIEF,       "BIT17" => 1 // ~Guerrier / Voleur~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY mage_class_group BEGIN
		FIGHTER_MAGE,        "BIT13" => 1 // ~Guerrier / Mage~
		FIGHTER_MAGE_CLERIC, "BIT15" => 1 // ~Guerrier / Mage / Clerc~
		FIGHTER_MAGE_THIEF,  "BIT16" => 1 // ~Guerrier / Mage / Voleur~
		MAGE_THIEF,          "BIT19" => 1 // ~Mage / Voleur~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY thief_class_group BEGIN
	    CLERIC_THIEF,       "BIT9"  => 1 // ~Clerc / Voleur~
		FIGHTER_MAGE_THIEF, "BIT16" => 1 // ~Guerrier / Mage / Voleur~
		FIGHTER_THIEF,      "BIT17" => 1 // ~Guerrier / Voleur~
		MAGE_THIEF,         "BIT19" => 1 // ~Mage / Voleur~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY druid_class_group BEGIN
		FIGHTER_DRUID, "BIT12" => 1 // ~Guerrier / Druide~
	END
END

DEFINE_PATCH_MACRO ~kits~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY bard_kit_group BEGIN
		BLADE,  2, "BIT5" => 1 // ~Maître-lames~
		JESTER, 2, "BIT6" => 1 // ~Bouffon~
		SKALD,  2, "BIT7" => 1 // ~Scalde~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY cleric_kit_group BEGIN
		TALOS,     1, "BIT0" => 1 // ~Prêtre de Talos~
		HELM,      1, "BIT1" => 1 // ~Prêtre de Helm~
		LATHANDER, 1, "BIT2" => 1 // ~Prêtre de Lathandre~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY thief_kit_group BEGIN
		ASSASIN,       2, "BIT2" => 1 // ~Assassin~
		BOUNTY_HUNTER, 2, "BIT3" => 1 // ~Chasseur de primes~
		SWASHBUCKLER,  2, "BIT4" => 1 // ~Bretteur~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY mage_kit_group BEGIN
		WILDMAGE,    1, "BIT7" => 1 // ~Entropiste~
		DIVINER,     3, "BIT0" => 1 // ~Devin~
		ENCHANTER,   3, "BIT1" => 1 // ~Enchanteur~
		ILLUSIONIST, 3, "BIT2" => 1 // ~Illusionniste~
		INVOKER,     3, "BIT3" => 1 // ~Invocateur~
		NECROMANCER, 3, "BIT4" => 1 // ~Nécromancien~
		TRANSMUTER,  3, "BIT5" => 1 // ~Transmutateur~
		ABJURER,     4, "BIT6" => 1 // ~Abjurateur~
		CONJURER,    4, "BIT7" => 1 // ~Conjurateur~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY fighter_kit_group BEGIN
		BERSERKER,     4, "BIT0" => 1 // ~Berserker~
		WIZARD_SLAYER, 4, "BIT1" => 1 // ~Tueur de magiciens~
		KENSAI,        4, "BIT2" => 1 // ~Kensai~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY druid_kit_group BEGIN
		TOTEMIC_DRUID, 1, "BIT3" => 1 // ~Chaman~
		SHAPESHIFTER,  1, "BIT4" => 1 // ~Métamorphe~
		BEAST_FRIEND,  1, "BIT5" => 1 // ~Justicier~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY paladin_kit_group BEGIN
		CAVALIER,      4, "BIT3" => 1 // ~Chevalier~
		INQUISITOR,    4, "BIT4" => 1 // ~Inquisiteur~
		UNDEAD_HUNTER, 4, "BIT5" => 1 // ~Chasseur de morts-vivants~
	END

	PATCH_DEFINE_ASSOCIATIVE_ARRAY ranger_kit_group BEGIN
		STALKER,     2, "BIT0" => 1 // ~Traqueur~
		BEASTMASTER, 2, "BIT1" => 1 // ~Maîtres des bêtes~
		FERALAN,     3, "BIT7" => 1 // ~Archer~
	END
END


/* ----------------------------------------------------------------------------------------- *
 * Génère les sections "Utilisable par" et "Non utilisable par" de la description.           *
 *                                                                                           *
 * Le processus va essayer de compresser au maximum le nombre de lignes générées, ceci afin  *
 * de correspondre au plus proche des descriptions manuelles.                                *
 *                                                                                           *
 * - La partie "Utilisable par" et "Non utilisable par" peuvent toutes les deux se trouver   *
 *   dans la description.                                                                    *
 * - Les restrictions d'alignement sont toujours condensées en une seule ligne.              *
 * - L'ordre est toujours Alignement > Race > Classe > Kit                                   *
 * ----------------------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~usability~ RET description BEGIN
	PATCH_IF NOT is_ee BEGIN
		SET usable         = 1
		SET usableByAll    = 1
		SET useListCount   = 0
		SET unuseListCount = 0

		READ_LONG  ITM_usability_flags useMask
		READ_BYTE  ITM_kit_usability1  kitUsability1
		READ_BYTE  ITM_kit_usability2  kitUsability2
		READ_BYTE  ITM_kit_usability3  kitUsability3
		READ_BYTE  ITM_kit_usability4  kitUsability4

		PATCH_DEFINE_ARRAY useList BEGIN END

		LPM ~usability_alignment~
		LPM ~usability_race~
		LPM ~usability_class_kit~

		LPF ~usability_add_to_description~ INT_VAR strref = 101070 all = (usableByAll AND usable) RET description END                        // Utilisable par
		LPF ~usability_add_to_description~ INT_VAR strref = 101071 all = (usable == 0) STR_VAR type = "unuse" RET description END // Non utilisable par
	END
END

/* -------------------------------------------------------------------------- *
 * Ajoute, si nécessaire, la section "[Non] Utilisable par" à la description. *
 * -------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~usability_add_to_description~ INT_VAR strref = 101070 all = 0 STR_VAR type = "use" RET description BEGIN
	PATCH_IF EVAL "%type%ListCount" > 0 OR all = 1 BEGIN
		LPF ~appendSection~ INT_VAR strref RET description END

		PATCH_IF all == 1 BEGIN
			LPF ~appendProperty~ INT_VAR strref = 101069 RET description END // Tous
		END
		ELSE BEGIN
			PATCH_PHP_EACH useList AS key => name BEGIN
				PATCH_IF "%key_0%" STRING_MATCHES_REGEXP "^%type%" = 0 BEGIN
					PATCH_IF VARIABLE_IS_SET $translations("%name%") BEGIN
						SPRINT name $translations("%name%")
					END
					ELSE PATCH_IF ("%name%" STRING_MATCHES_REGEXP "[0-9]+" = 0) BEGIN
						SPRINT name (AT ~%name%~)
					END
					LPF ~appendProperty~ STR_VAR name RET description END
				END
			END
		END
	END
END

/* -------------------------------------------------------------------------- *
 * Divise les éléments et les place dans leur catégorie respective.           *
 * Des compteurs pour savoir combien il y a d'éléments par catégorie sont     *
 * également incrémentés.                                                     *
 * - use   : Utilisable par                                                   *
 * - unuse : Non utilisable par                                               *
 * RET                                                                        *
 *    use : Le tableau contenant l'ensemble des éléments.                     *
 * -------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~usability_split~ INT_VAR useMask = 0 STR_VAR array_name = "" RET useCount unuseCount smallest RET_ARRAY use unuse BEGIN
	CLEAR_ARRAY use
	CLEAR_ARRAY unuse

	PATCH_DEFINE_ARRAY use BEGIN END
	PATCH_DEFINE_ARRAY unuse BEGIN END
	SET useCount = 0
	SET unuseCount = 0
	// FIXME: Les 2 lignes suivantes ont été ajoutées pour éviter un bug (de WeidU ?)
	// Plusieurs tests "PATCH_IF value == 1 BEGIN" ont du être réalisés pour éviter de traiter ces entrées fictives
	// Le bug fait que si on a un objet non utilisable par les "personnages bons" ET les races "Demi-elfe, Petite-personne, Humain et Gnome" uniquement
	// lors du traitement des classes, l'erreur suivante survient : ERROR: Failure("Unknown return value: unuse_268435456_Gnome")
	// On dirait que Weidu se souvient d'une ancienne valeur du tableau, alors qu'on l'a CLEAR juste au dessus.
	SET $use("-1") = 0
	SET $unuse("-1") = 0

	// Nécessaire de vider le tableau pour éviter que les éléments ajoutés par un précédent appel ne soient encore présent
	CLEAR_ARRAY array_usabilities

	LPM ~%array_name%~

	PATCH_PHP_EACH array_usabilities AS matches => value BEGIN
		SET bit = EVAL "%%matches_1%%"
		PATCH_IF (useMask BAND %bit%) = 0 BEGIN
			SET useCount += 1
			SET $use("%bit%" "%matches_0%") = 1
		END
		ELSE BEGIN
			SET unuseCount += 1
			SET $unuse("%bit%" "%matches_0%") = 1
		END
	END
	PATCH_IF useCount > unuseCount BEGIN
		SPRINT smallest "unuse"
	END
	ELSE BEGIN
		SPRINT smallest "use"
	END
END

/* ----------------------------------------------------------------------------------------- *
 * Génère la section "[Non] Utilisable par" relative à l'alignement du personnage.           *
 *                                                                                           *
 * Social          | Moral                                                                   *
 * --------------- | -------------                                                           *
 * 0 - Chaotique   | 1 - Mauvais                                                             *
 * 4 - Loyal       | 2 - Bon                                                                 *
 * 5 - Neutre      | 3 - Neutre                                                              *
 *                                                                                           *
 * - Si tout est coché, rien ne sera généré, il n'est pas nécessaire de préciser que         *
 *   tous les alignements peuvent le porter.                                                 *
 * - Si les 3 d'une catégorie sont cochés, les noms de l'autre catégorie sont affichés.      *
 * - Si aucun n'est coché dans l'une des catégories, l'objet devient inutilisable pour tous. *
 * - 1 seule entrée est générée au maximum.                                                  *
 * ----------------------------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~usability_alignment~ BEGIN
	LOCAL_SET count = 0
	PATCH_IF NOT (useMask BAND 0x3f) = 0 BEGIN
		// Aucun alignement (moral et/ou social) ne peut le porter
		PATCH_IF ((useMask BAND 0xe) = 0xe) OR ((useMask BAND 0x31) = 0x31) BEGIN
			SET usable = 0
		END
		ELSE BEGIN
			SET usableByAll = 0

			LPF usability_split INT_VAR useMask STR_VAR array_name = "social_alignments" RET useCountSocial = useCount unuseCountSocial = unuseCount RET_ARRAY usesSocial = use unusesSocial = unuse END
			LPF usability_split INT_VAR useMask STR_VAR array_name = "moral_alignments" RET useCountMoral = useCount unuseCountMoral = unuseCount RET_ARRAY usesMoral = use unusesMoral = unuse END

			SPRINT useOrUnuse "use"
			PATCH_IF (useCountSocial + useCountMoral) > (unuseCountSocial + unuseCountMoral) BEGIN
				SPRINT useOrUnuse "unuse"
			END

			PATCH_IF useCountSocial = 3 BEGIN
				SPRINT useArray "%useOrUnuse%sMoral"
				LPM ~usability_alignment_compress~
			END
			ELSE PATCH_IF useCountMoral = 3 BEGIN
				SPRINT useArray "%useOrUnuse%sSocial"
				LPM ~usability_alignment_compress~
			END
			ELSE BEGIN
				PATCH_PHP_EACH "%useOrUnuse%sSocial" AS keySocial => sValue BEGIN
					PATCH_IF sValue == 1 BEGIN
						SET $usesSocialMoral("%keySocial_1%" "%keySocial_1%") = 1
						PATCH_PHP_EACH "%useOrUnuse%sMoral" AS keyMoral => mValue BEGIN
							PATCH_IF mValue == 1 BEGIN
								SET $usesSocialMoral("%keyMoral_1%" "%keyMoral_1%") = 1
							END
						END
					END
				END
				SPRINT useArray "usesSocialMoral"
				LPM ~usability_alignment_compress~
			END
		END
	END
END

/* ----------------------------------------------------------------------------------- *
 * Fusionne les entrées en une seule ligne dont les éléments sont séparés par un "ou". *
 * ----------------------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~usability_alignment_compress~ BEGIN
	LOCAL_SPRINT str @101090 // Personnage d'alignement
	SPRINT str "%str% "

	PATCH_PHP_EACH "%useArray%" AS data => value BEGIN
		PATCH_IF value == 1 BEGIN
			PATCH_IF count > 0 BEGIN
				SPRINT strOr @100004 // ~ou~
				SPRINT str "%str% %strOr% "
			END
			PATCH_IF VARIABLE_IS_SET $translations("%data_1%") BEGIN
				SPRINT data_1 $translations("%data_1%")
			END
			SET count += 1
			SPRINT str "%str%%data_1%"
		END
	END
	SET EVAL "%useOrUnuse%ListCount" += 1
	SPRINT key EVAL "%%useOrUnuse%ListCount%"
	SPRINT $useList("%useOrUnuse%-%key%") "%str%"
END

/* -------------------------------------------------------------------------- *
 * Génère la section "[Non] Utilisable par" relative à la race du personnage. *
 * -------------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~usability_race~ BEGIN
	PATCH_IF usable = 1 BEGIN
		LPF usability_split INT_VAR useMask STR_VAR array_name = "races" RET useCount unuseCount smallest RET_ARRAY use unuse END

		PATCH_IF useCount = 0 BEGIN
			SET usable = 0
		END
		ELSE PATCH_IF unuseCount > 0 BEGIN
			SET usableByAll = 0
			// TODO: Trier par ordre alphabetique ?
			PATCH_PHP_EACH "%smallest%" AS data => value BEGIN
				PATCH_IF value == 1 BEGIN
					SET EVAL "%smallest%ListCount" += 1
					SPRINT key EVAL "%%smallest%ListCount%"
					SPRINT $useList("%smallest%-%key%") "%data_1%"
				END
			END
		END
	END
END


/* ---------------------------------------------------------------------------- *
 * Génère la section "[Non] Utilisable par" relative à la classe du personnage. *
 * ---------------------------------------------------------------------------- */
DEFINE_PATCH_MACRO ~usability_class_kit~ BEGIN
	PATCH_DEFINE_ARRAY use BEGIN END
	PATCH_DEFINE_ARRAY unuse BEGIN END

	SET useCount = 0
	SET unuseCount = 0

	CLEAR_ARRAY use
	CLEAR_ARRAY unuse

	//SET $use("-1") = 0
	//SET $unuse("-1") = 0

	LPM ~classes~
	LPM ~kits~

	// Barbare
	// Bien qu'étant considéré comme une classe à part, techniquement, le Barbare est bien un kit de guerrier !
	// On le traite alors différemment pour afficher tel que le joueur s'y attendrait
	PATCH_IF (useMask BAND %BIT11%) = 0 AND (kitUsability1 BAND %BIT6%) = 0 BEGIN
		SET useCount += 1
		SET useKey = useCount
		SPRINT name $translations("BARBARIAN")
		SPRINT $use(~%useKey%~ ~BARBARIAN~) ~%name%~
	END
	ELSE BEGIN
		SET usableByAll = 0
		SET unuseCount += 1
		SET useKey = unuseCount
		SPRINT name $translations("BARBARIAN")
		SPRINT $unuse(~%useKey%~ ~BARBARIAN~) ~%name%~
	END

	PATCH_PHP_EACH classes AS data => value BEGIN
		SPRINT classname EVAL ~%data_0%~
		SET bitClass      = EVAL ~%data_1%~
		SET hasMulticlass = EVAL ~%data_2%~
		SET hasKits       = EVAL ~%data_3%~

		LPM ~compress_class_kit~
	END

	// Filtre des multiclasses afin que la liste finale ne contienne pas de doublon
	PATCH_PHP_EACH ~useMulticlasses~ AS data => value BEGIN
		PATCH_IF value == 0 BEGIN
			PATCH_PHP_EACH ~use~ AS uData => uValue BEGIN
				PATCH_IF ~%data_0%~ STRING_EQUAL ~%uData_1%~ BEGIN
					SPRINT $use(~%uData_0%~ ~%uData_1%~) ~~
				END
			END
		END
	END
	PATCH_PHP_EACH ~unuseMulticlasses~ AS data => value BEGIN
		PATCH_IF value == 0 BEGIN
			PATCH_PHP_EACH ~unuse~ AS uData => uValue BEGIN
				PATCH_IF ~%data_0%~ STRING_EQUAL ~%uData_1%~ BEGIN
					SPRINT $unuse(~%uData_0%~ ~%uData_1%~) ~~
				END
			END
		END
	END

	SPRINT useArray ~use~

	PATCH_PHP_EACH ~use~ AS data => value BEGIN
		PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
			SET useListCount += 1
		END
	END
	PATCH_PHP_EACH ~unuse~ AS data => value BEGIN
		PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
			SET unuseListCount += 1
		END
	END

	PATCH_IF unuseListCount < useListCount BEGIN
		SPRINT useArray ~unuse~
		SET useListCount = 0
	END
	ELSE BEGIN
		SET unuseListCount = 0
	END

	SORT_ARRAY_INDICES ~%useArray%~ NUMERICALLY

	PATCH_PHP_EACH ~%useArray%~ AS data => value BEGIN
		PATCH_IF NOT ~%value%~ STRING_EQUAL ~~ BEGIN
			SPRINT $useList("%useArray%%data_1%") "%value%"
		END
	END
END

DEFINE_PATCH_MACRO ~compress_class_kit~ BEGIN
	SPRINT lowerClassname ~%classname%~
	TO_LOWER lowerClassname

	SPRINT classgroup ~%lowerClassname%_class_group~
	SPRINT kitgroup   ~%lowerClassname%_kit_group~

	PATCH_IF ("%classname%" STRING_MATCHES_REGEXP "[0-9]+" = 0) BEGIN
		SPRINT classname (AT ~%classname%~)
	END
	ELSE BEGIN
		SPRINT classname  $translations("%classname%")
	END

	SET baseClassCan = 0
	SET allMulticlassesCan = 1
	SET allMulticlassesCanNot = 1
	SET allKitsCan = 1
	SET allKitsCanNot = 1

	PATCH_IF (useMask BAND %bitClass%) = 0 BEGIN
		SET baseClassCan = 1
	END
	ELSE BEGIN
		SET usableByAll = 0
		SET allKitsCan = 0
	END

	PATCH_IF hasMulticlass == 1 BEGIN
		PATCH_PHP_EACH "%classgroup%" AS data => value BEGIN
			SET bit = EVAL "%%data_1%%"

			PATCH_IF (useMask BAND %bit%) = 0 BEGIN
				SET allMulticlassesCanNot = 0
			END
			ELSE BEGIN
				SET allMulticlassesCan = 0
				SET usableByAll = 0
			END
		END
	END
	PATCH_IF baseClassCan == 1 AND hasKits == 1 BEGIN
		PATCH_PHP_EACH "%kitgroup%" AS data => value BEGIN
			SET bit = EVAL "%%data_2%%"

			PATCH_IF (EVAL ~kitUsability%data_1%~ BAND %bit%) = 0 BEGIN
				SET allKitsCanNot = 0
			END
			ELSE BEGIN
				SET allKitsCan = 0
				SET usableByAll = 0
			END
		END
	END

	PATCH_IF allMulticlassesCan == 1 BEGIN
		PATCH_PHP_EACH "%classgroup%" AS data => value BEGIN
			SET $useMulticlasses("%data_0%") = 0
		END
	END
	PATCH_IF allMulticlassesCanNot == 1 BEGIN
		PATCH_PHP_EACH "%classgroup%" AS data => value BEGIN
			SET $unuseMulticlasses("%data_0%") = 0
		END
	END

	PATCH_IF baseClassCan == 1 AND hasMulticlass == 1 AND allMulticlassesCan == 1 AND hasKits == 1 AND allKitsCan == 1 BEGIN
		SPRINT useName @101127 // ~%classname% monoclassé, multiclassé et ses kits~
		SET useCount += 1
		SPRINT $use(~%useCount%~ ~%data_0%-mc-k~) ~%useName%~
	END
	ELSE PATCH_IF baseClassCan == 1 AND hasMulticlass == 0 AND hasKits == 1 AND allKitsCan == 1 BEGIN
		SPRINT useName @101128 // ~%classname% et ses kits~
		SET useCount += 1
		SPRINT $use(~%useCount%~ ~%data_0%-k~) ~%useName%~
	END
	ELSE PATCH_IF baseClassCan == 1 AND hasMulticlass == 1 AND allMulticlassesCan == 1 AND hasKits == 0 BEGIN
		SPRINT useName @101074 // ~%classname% monoclassé et multiclassé~
		SET useCount += 1
		SPRINT $use(~%useCount%~ ~%data_0%-mc~) ~%useName%~
	END
	ELSE PATCH_IF baseClassCan == 0 AND hasMulticlass == 1 AND allMulticlassesCanNot == 1 AND hasKits == 1 AND allKitsCanNot == 1 BEGIN
		SPRINT useName @101127 // ~%classname% monoclassé, multiclassé et ses kits~
		SET unuseCount += 1
		SPRINT $unuse(~%unuseCount%~ ~%data_0%-mc-k~) ~%useName%~
    END
    ELSE PATCH_IF baseClassCan == 0 AND hasMulticlass == 0 AND hasKits == 1 AND allKitsCanNot == 1 BEGIN
		SPRINT useName @101128 // ~%classname% et ses kits~
		SET unuseCount += 1
		SPRINT $unuse(~%unuseCount%~ ~%data_0%-k~) ~%useName%~
    END
    ELSE PATCH_IF baseClassCan == 0 AND hasMulticlass == 1 AND allMulticlassesCanNot == 1 AND hasKits == 0 BEGIN
		SPRINT useName @101074 // ~%classname% monoclassé et multiclassé~
		SET unuseCount += 1
		SPRINT $unuse(~%unuseCount%~ ~%data_0%-mc~) ~%useName%~
    END
    ELSE BEGIN
        PATCH_IF hasMulticlass == 1 AND hasKits == 1 BEGIN
			SET listKits = 1
			SET listMulticlasses = 1

            PATCH_IF baseClassCan == 0 AND allKitsCanNot == 1 BEGIN
				SPRINT useName @101128 // ~%classname% et ses kits~
				SET unuseCount += 1
				SET listKits = 0
				SPRINT $unuse(~%unuseCount%~ ~%data_0%-k~) ~%useName%~
            END
            ELSE PATCH_IF baseClassCan == 0 AND allMulticlassesCanNot == 1 BEGIN
				SPRINT useName @101074 // ~%classname% monoclassé et multiclassé~
				SET unuseCount += 1
				SET listMulticlasses = 0
				SPRINT $unuse(~%unuseCount%~ ~%data_0%-mc~) ~%useName%~
            END
            ELSE PATCH_IF baseClassCan == 1 AND allMulticlassesCan == 1 BEGIN
				SPRINT useName @101074 // ~%classname% monoclassé et multiclassé~
				SET useCount += 1
				SET listMulticlasses = 0
				SPRINT $use(~%useCount%~ ~%data_0%-mc~) ~%useName%~
            END
            ELSE PATCH_IF baseClassCan == 1 AND allKitsCan == 1 BEGIN
				SPRINT useName @101128 // ~%classname% et ses kits~
				SET useCount += 1
				SET listKits = 0
				SPRINT $use(~%useCount%~ ~%data_0%-k~) ~%useName%~
            END
            ELSE BEGIN
                LPM ~list_baseclass~
            END

            PATCH_IF listMulticlasses == 1 BEGIN
				LPM ~list_multiclasses~
            END

            PATCH_IF listKits == 1 BEGIN
				LPM ~list_kits~
            END
        END
        ELSE PATCH_IF hasMulticlass == 1 BEGIN
            LPM ~list_baseclass~
            LPM ~list_multiclasses~
        END
        ELSE PATCH_IF hasKits == 1 BEGIN
            LPM ~list_baseclass~
            LPM ~list_kits~
        END
        ELSE BEGIN
            LPM ~list_baseclass~
        END
    END
END

DEFINE_PATCH_MACRO ~list_baseclass~ BEGIN
	PATCH_IF baseClassCan == 1 BEGIN
		SET useCount += 1
		SPRINT $use(~%useCount%~ ~%data_0%~) ~%classname%~
	END
	ELSE BEGIN
		SET unuseCount += 1
		SPRINT $unuse(~%unuseCount%~ ~%data_0%~) ~%classname%~
	END
END

DEFINE_PATCH_MACRO ~list_multiclasses~ BEGIN
	PATCH_PHP_EACH "%classgroup%" AS data => value BEGIN
		SET bit = EVAL "%%data_1%%"

		PATCH_IF (useMask BAND %bit%) = 0 BEGIN
			SET useCount += 1
			SPRINT name $translations("%data_0%")
			SPRINT $use(~%useCount%~ ~%data_0%~) ~%name%~
		END
		ELSE BEGIN
			SET unuseCount += 1
			SPRINT name $translations("%data_0%")
			SPRINT $unuse(~%unuseCount%~ ~%data_0%~) ~%name%~
		END
	END
END

DEFINE_PATCH_MACRO ~list_kits~ BEGIN
	PATCH_PHP_EACH "%kitgroup%" AS data => value BEGIN
		SET bit = EVAL "%%data_2%%"

		PATCH_IF (EVAL ~kitUsability%data_1%~ BAND %bit%) = 0 BEGIN
			SET useCount += 1
			SET useKey = 100 + useCount
			SPRINT name $translations("%data_0%")
			SPRINT $use(~%useKey%~ ~%data_0%~) ~%name%~
		END
		ELSE BEGIN
			SET unuseCount += 1
			SET useKey = 100 + unuseCount
			SPRINT name $translations("%data_0%")
			SPRINT $unuse(~%useKey%~ ~%data_0%~) ~%name%~
		END
	END
END