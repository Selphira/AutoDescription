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
	PATCH_DEFINE_ASSOCIATIVE_ARRAY array_usabilities BEGIN
	    BARD,                "BIT6"  => 1 // ~Barde~
		CLERIC,              "BIT7"  => 1 // ~Clerc~
		CLERIC_MAGE,         "BIT8"  => 1 // ~Clerc / Mage~
	    CLERIC_THIEF,        "BIT9"  => 1 // ~Clerc / Voleur~
		CLERIC_RANGER,       "BIT10" => 1 // ~Clerc / Rôdeur~
		FIGHTER,             "BIT11" => 1 // ~Guerrier~
		FIGHTER_DRUID,       "BIT12" => 1 // ~Guerrier / Druide~
		FIGHTER_MAGE,        "BIT13" => 1 // ~Guerrier / Mage~
		FIGHTER_CLERIC,      "BIT14" => 1 // ~Guerrier / Clerc~
		FIGHTER_MAGE_CLERIC, "BIT15" => 1 // ~Guerrier / Mage / Clerc~
		FIGHTER_MAGE_THIEF,  "BIT16" => 1 // ~Guerrier / Mage / Voleur~
		FIGHTER_THIEF,       "BIT17" => 1 // ~Guerrier / Voleur~
		MAGE,                "BIT18" => 1 // ~Mage~
		MAGE_THIEF,          "BIT19" => 1 // ~Mage / Voleur~
		PALADIN,             "BIT20" => 1 // ~Paladin~
		RANGER,              "BIT21" => 1 // ~Rôdeur~
		THIEF,               "BIT22" => 1 // ~Voleur~
		MONK,                "BIT29" => 1 // ~Moine~
		DRUID,               "BIT30" => 1 // ~Druide~
	END

	// Les groupes ne contiennent pas le bit de la classe de base
	PATCH_DEFINE_ARRAY class_group_clerc BEGIN
		"BIT8" "BIT9" "BIT10" "BIT14" "BIT15"
	END

	PATCH_DEFINE_ARRAY class_group_figther BEGIN
		"BIT12" "BIT13" "BIT14" "BIT15" "BIT16" "BIT17"
	END

	PATCH_DEFINE_ARRAY class_group_mage BEGIN
		"BIT13" "BIT15" "BIT16" "BIT18" "BIT19"
	END

	PATCH_DEFINE_ARRAY class_group_thief BEGIN
		"BIT9" "BIT16" "BIT17" "BIT19"
	END
END

DEFINE_PATCH_MACRO ~kits1~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY array_usabilities BEGIN
		TALOS,         "BIT0" => 1 // ~Prêtre de Talos~
		HELM,          "BIT1" => 1 // ~Prêtre de Helm~
		LATHANDER,     "BIT2" => 1 // ~Prêtre de Lathandre~
		TOTEMIC_DRUID, "BIT3" => 1 // ~Chaman~
		SHAPESHIFTER,  "BIT4" => 1 // ~Métamorphe~
		BEAST_FRIEND,  "BIT5" => 1 // ~Justicier~
		BARBARIAN,     "BIT6" => 1 // ~Barbare~
		WILDMAGE,      "BIT7" => 1 // ~Entropiste~
	END
END

DEFINE_PATCH_MACRO ~kits2~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY array_usabilities BEGIN
		STALKER,       "BIT0" => 1 // ~Traqueur~
		BEASTMASTER,   "BIT1" => 1 // ~Maîtres des bêtes~
		ASSASIN,       "BIT2" => 1 // ~Assassin~
		BOUNTY_HUNTER, "BIT3" => 1 // ~Chasseur de primes~
		SWASHBUCKLER,  "BIT4" => 1 // ~Bretteur~
		BLADE,         "BIT5" => 1 // ~Maître-lames~
		JESTER,        "BIT6" => 1 // ~Bouffon~
		SKALD,         "BIT7" => 1 // ~Scalde~
	END
END

DEFINE_PATCH_MACRO ~kits3~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY array_usabilities BEGIN
		DIVINER,     "BIT0" => 1 // ~Devin~
		ENCHANTER,   "BIT1" => 1 // ~Enchanteur~
		ILLUSIONIST, "BIT2" => 1 // ~Illusionniste~
		INVOKER,     "BIT3" => 1 // ~Invocateur~
		NECROMANCER, "BIT4" => 1 // ~Nécromancien~
		TRANSMUTER,  "BIT5" => 1 // ~Transmutateur~
		101054,      "BIT6" => 1 // ~Tous (aucun kit)~
		FERALAN,     "BIT7" => 1 // ~Archer~
	END
END

DEFINE_PATCH_MACRO ~kits4~ BEGIN
	PATCH_DEFINE_ASSOCIATIVE_ARRAY array_usabilities BEGIN
		BERSERKER,     "BIT0" => 1 // ~Berserker~
		WIZARD_SLAYER, "BIT1" => 1 // ~Tueur de magiciens~
		KENSAI,        "BIT2" => 1 // ~Kensai~
		CAVALIER,      "BIT3" => 1 // ~Chevalier~
		INQUISITOR,    "BIT4" => 1 // ~Inquisiteur~
		UNDEAD_HUNTER, "BIT5" => 1 // ~Chasseur de morts-vivants~
		ABJURER,       "BIT6" => 1 // ~Abjurateur~
		CONJURER,      "BIT7" => 1 // ~Conjurateur~
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
	LPM ~usability_class~
	LPM ~usability_kit~

	LPF ~usability_add_to_description~ INT_VAR strref = 101070 all = (usableByAll AND usable) RET description END                        // Utilisable par
	LPF ~usability_add_to_description~ INT_VAR strref = 101071 all = (usable == 0) STR_VAR type = "unuse" RET description END // Non utilisable par
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
DEFINE_PATCH_MACRO ~usability_class~ BEGIN
	PATCH_IF usable = 1 BEGIN
		LPF usability_split INT_VAR useMask STR_VAR array_name = "classes" RET useCount unuseCount smallest RET_ARRAY use unuse END

		PATCH_IF useCount = 0 BEGIN
			SET usable = 0
		END
		ELSE PATCH_IF unuseCount > 0 BEGIN
			CLEAR_ARRAY useClass
			CLEAR_ARRAY unuseClass

			PATCH_DEFINE_ARRAY useClass BEGIN END
			PATCH_DEFINE_ARRAY unuseClass BEGIN END

			SET usableByAll = 0
			SET useClassCount = 0
			SET unuseClassCount = 0

			LPM ~classes~
			LPF ~usability_class_compress~ INT_VAR baseClass = BIT11 baseRef = 101011 STR_VAR array_name = "class_group_figther" useArray = EVAL "%smallest%" RET useClassCount unuseClassCount RET_ARRAY useClass use unuse END
			LPF ~usability_class_compress~ INT_VAR baseClass = BIT7  baseRef = 101007 STR_VAR array_name = "class_group_clerc"   useArray = EVAL "%smallest%" RET useClassCount unuseClassCount RET_ARRAY useClass use unuse END
			LPF ~usability_class_compress~ INT_VAR baseClass = BIT18 baseRef = 101018 STR_VAR array_name = "class_group_mage"    useArray = EVAL "%smallest%" RET useClassCount unuseClassCount RET_ARRAY useClass use unuse END
			LPF ~usability_class_compress~ INT_VAR baseClass = BIT22 baseRef = 101022 STR_VAR array_name = "class_group_thief"   useArray = EVAL "%smallest%" RET useClassCount unuseClassCount RET_ARRAY useClass use unuse END

			PATCH_PHP_EACH "%smallest%" AS data => value BEGIN
				PATCH_IF value = 1 BEGIN
					SET EVAL "%smallest%ClassCount" += 1
					SPRINT key EVAL "%%smallest%ClassCount%"
					SPRINT $useClass("%smallest%-%key%") "%data_1%"
				END
			END

			// TODO: Trier par ordre alphabetique ?
			PATCH_PHP_EACH useClass AS data => value BEGIN
				SET EVAL "%smallest%ListCount" += 1
				SPRINT key EVAL "%%smallest%ListCount%"
				SPRINT $useList("%data_0%-%key%") "%value%"
			END
		END
	END
END

/* ----------------------------------------------------------------------------------- *
 * Fusionne les entrées en une seule ligne si toutes les variantes multiclassées de la *
 * classe de base sont présentes.                                                      *
 * Selon le cas, on remplacera la liste par                                            *
 * - [classname]                                                                       *
 * - [classname] monoclassé                                                            *
 * - [classname] multiclassé                                                           *
 * ----------------------------------------------------------------------------------- */
DEFINE_PATCH_FUNCTION ~usability_class_compress~ INT_VAR baseClass = 0 baseRef = 0 STR_VAR array_name = "" useArray = "" RET useClassCount unuseClassCount RET_ARRAY useClass use unuse BEGIN
	SET none = 1 // Est-ce qu'aucun élément est présent ?
	SET base = 0 // Est-ce que la classe de base est présente ?
	SET count = 0
	SET total = 0

	SPRINT classname (AT %baseRef%)

	PATCH_PHP_EACH "%array_name%" AS data => value BEGIN
		SET total += 1
		PATCH_PHP_EACH "%useArray%" AS useData => useValue BEGIN
			SET useBit = EVAL "%value%"
			PATCH_IF useBit == useData_0 BEGIN
				SET count += 1
				none = 0
			END
			PATCH_IF useData_0 == baseClass BEGIN
				SET base = 1
			END
		END
	END
	PATCH_IF count == total BEGIN
		PATCH_IF base == 1 BEGIN // La classe et toutes se déclinaisons hors kit
			SPRINT string @101074
			SET EVAL "%useArray%ClassCount" += 1
			SPRINT key EVAL "%%useArray%ClassCount%"
			SPRINT $useClass("%useArray%" "%key%") "%string%"
		END
		ELSE BEGIN // La classe multiclassée
			SPRINT string @101072
			SET EVAL "%useArray%ClassCount" += 1
			SPRINT key EVAL "%%useArray%ClassCount%"
			SPRINT $useClass("%useArray%" "%key%") "%string%"
		END
	END
	ELSE BEGIN
		PATCH_IF none == 1 AND base == 1 BEGIN // La classe monoclassée
			SPRINT string @101073
			SET EVAL "%useArray%ClassCount" += 1
			SPRINT key EVAL "%%useArray%ClassCount%"
			SPRINT $useClass("%useArray%" "%key%") "%string%"

			// Désactivation de la classe de base dans la liste principale
			PATCH_PHP_EACH "%useArray%" AS useData => useValue BEGIN
				PATCH_IF useData_0 == baseClass BEGIN
					SET $EVAL "%useArray%"("%useData_0%" "%useData_1%") = 0
				END
			END
		END
	END

	PATCH_IF count == total BEGIN
		PATCH_PHP_EACH "%array_name%" AS key => class BEGIN
			PATCH_PHP_EACH "%useArray%" AS useData => useValue BEGIN
				SET class = EVAL "%class%"
				PATCH_IF useData_0 == class BEGIN
					SET $EVAL "%useArray%"("%useData_0%" "%useData_1%") = 0
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ~usability_kit~ BEGIN
	PATCH_IF usable = 1 BEGIN
		LPF usability_split INT_VAR useMask = kitUsability1 STR_VAR array_name = "kits1" RET useCountKit1 = useCount unuseCountKit1 = unuseCount smallest RET_ARRAY useKit1 = use unuseKit1 = unuse END
		LPF usability_split INT_VAR useMask = kitUsability2 STR_VAR array_name = "kits2" RET useCountKit2 = useCount unuseCountKit2 = unuseCount smallest RET_ARRAY useKit2 = use unuseKit2 = unuse END
		LPF usability_split INT_VAR useMask = kitUsability3 STR_VAR array_name = "kits3" RET useCountKit3 = useCount unuseCountKit3 = unuseCount smallest RET_ARRAY useKit3 = use unuseKit3 = unuse END
		LPF usability_split INT_VAR useMask = kitUsability4 STR_VAR array_name = "kits4" RET useCountKit4 = useCount unuseCountKit4 = unuseCount smallest RET_ARRAY useKit4 = use unuseKit4 = unuse END

		SET useCount   = useCountKit1 + useCountKit2 + useCountKit3 + useCountKit4
		SET unuseCount = unuseCountKit1 + unuseCountKit2 + unuseCountKit3 + unuseCountKit4

		PATCH_IF useCount = 0 BEGIN
			SET usable = 0
		END
		ELSE PATCH_IF unuseCount > 0 BEGIN
			SET usableByAll = 0

			SPRINT smallest "use"
			PATCH_IF useCount > unuseCount BEGIN
				SPRINT smallest "unuse"
			END

            PATCH_DEFINE_ARRAY ~numbers~ BEGIN 1 2 3 4 END
			// TODO: Trier par ordre alphabetique ?
			PATCH_PHP_EACH numbers AS key => number BEGIN
				PATCH_PHP_EACH "%smallest%Kit%number%" AS data => value BEGIN
					PATCH_IF value == 1 BEGIN
						SET EVAL "%smallest%ListCount" += 1
						SPRINT key EVAL "%%smallest%ListCount%"
						SPRINT $useList("%smallest%-%key%") "%data_1%"
					END
				END
			END
		END
	END
END