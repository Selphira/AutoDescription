DEFINE_PATCH_FUNCTION ~add_combat_abilities~
	STR_VAR
		description = ~~
	RET
		description
BEGIN
    READ_LONG ITM_flags flags

	SET abilityType = AbilityType_Equipped
	SET countLines = 0
	SET countHeaders = 0

    PATCH_DEFINE_ASSOCIATIVE_ARRAY lines BEGIN END
    PATCH_DEFINE_ASSOCIATIVE_ARRAY opcodes BEGIN END

	GET_OFFSET_ARRAY headerOffsets ITM_V10_HEADERS
	PHP_EACH headerOffsets AS _ => headerOffset BEGIN
		READ_SHORT (headerOffset + ITM_HEAD_charges) charges

		PATCH_IF charges == 0 BEGIN
			SET countHeaders += 1

			CLEAR_ARRAY lines
			CLEAR_ARRAY opcodes

			LPM ~load_extended_effects~
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

			//TODO: Ne garder que les effets uniques  : ATTENTION ! Un effet est unique si la chaîne est la même ET que sa probabilité l'est aussi
			//TODO: Tout placer dans un tableau spécifique à l'en-tête
			//En fonction du nombre de ces tableaux, on saura combien de sections "Capacités de combat [(En mêlée|A distance|Etc.)]" générer

		END
	END

	//TODO: Pour chaque en-tête, vérifier si certaines ont les mêmes capacités afin de les regrouper
	//TODO: Si plusieurs et non regroupées, ne pas oublier d'ajouter le type d'attaque à côté du nom de la section


END

