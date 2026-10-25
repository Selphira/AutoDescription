// Opcode 67 (Summon: Creature Summoning) : invoque la créature resource : « Invoque 1 « Ras » pendant
// 4 rounds ». parameter2 règle l'allégeance de la créature (IESDP) : 0, 1, 3 et 5 la font dépendre de
// celle du lanceur, sinon l'ancien moteur précise celle du fichier de la créature (hostile, alliée,
// neutre). Avec AD_ENABLE_SHRINKAGE, des invocations identiques n'en font qu'une, avec leur nombre
// (fx_identical_count, ad_group_identical_effects).

// Avec AD_ENABLE_SHRINKAGE, une invocation certaine réunit aussi les invocations probables identiques à
// la probabilité près (ancien opcode_67_group) : chacune compte pour une créature de plus au plus,
// « Invoque entre 2 et 5 « Rat » » (fx_summon_random).
// Refus : créature sans nom (aucune ligne).
DEFINE_PATCH_MACRO ad_op_67_support BEGIN
	PHP_EACH fx_ids_67 AS _ => summon_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SPRINT summon_resref $fx_resource(~%summon_id%~)
			LPF ad_creature_info STR_VAR resref = ~%summon_resref%~ RET summon_name = name summon_allegiance = allegiance
				summon_level = level END
			PATCH_IF ~%summon_name%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF FILE_EXISTS_IN_GAME ~%summon_resref%.cre~ BEGIN
					LPF ad_refusal INT_VAR fx_id = summon_id STR_VAR reason = ~not_implemented:opcode67:no_name~ message = ~creature %summon_resref%.CRE has no name~ RET render_missing = refusal END
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = summon_id STR_VAR reason = ~file_error:opcode67:missing_creature~ message = ~creature %summon_resref%.CRE does not exist~ RET render_missing = refusal END
				END
			END
			ELSE BEGIN
				SPRINT $fx_creature_name(~%summon_id%~) ~%summon_name%~
				SET $fx_creature_level(~%summon_id%~) = summon_level
				SET summon_mode = $fx_parameter2(~%summon_id%~)
				// Seuils GOODCUTOFF (30) et EVILCUTOFF (200) de ea.ids.
				SET $fx_creature_side(~%summon_id%~) = (summon_mode == 0 OR summon_mode == 1 OR summon_mode == 3 OR summon_mode == 5) ? 0
					: (summon_allegiance >= 200 ? 1 : (summon_allegiance <= 30 ? 2 : 3))
				SET $fx_summon_random(~%summon_id%~) = 0
				PATCH_IF AD_ENABLE_SHRINKAGE AND $fx_probability(~%summon_id%~) == 100 AND NOT support_header_only BEGIN
					LPM ad_op_67_random_support
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_67_random_support BEGIN
	SET same_id = summon_id
	SET same_ignored = AD_SAME_PROBABILITY
	PHP_EACH fx_ids_67 AS _ => summon_other BEGIN
		PATCH_IF summon_other != summon_id AND $fx_probability(~%summon_other%~) < 100 AND NOT $fx_consumed(~%summon_other%~) BEGIN
			SET same_other = summon_other
			LPM ad_fx_same_fields
			SPRINT summon_other_resref $fx_resource(~%summon_other%~)
			PATCH_IF fx_same AND (~%summon_other_resref%~ STRING_EQUAL_CASE ~%summon_resref%~) BEGIN
				SET $fx_consumed(~%summon_other%~) = 1
				SET $fx_summon_random(~%summon_id%~) += 1
			END
		END
	END
END

// Phrase : 20 670 100 + 10 × variante + forme ; variante = côté (0 selon le lanceur, 1 hostile,
// 2 allié, 3 neutre), + 4 pour plusieurs créatures.
DEFINE_PATCH_MACRO ad_op_67_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~67~)
	PHP_EACH fx_ids_67 AS _ => summon_id BEGIN
		PATCH_IF NOT $fx_consumed(~%summon_id%~) BEGIN
			SPRINT creatureName $fx_creature_name(~%summon_id%~)
			SET amount = AD_ENABLE_SHRINKAGE ? $fx_identical_count(~%summon_id%~) : 1
			// Invocations probables réunies aux effets certains que celui-ci représente.
			SET summon_random = 0
			FOR (summon_member = 0; summon_member < fx_count; ++summon_member) BEGIN
				PATCH_IF $fx_opcode(~%summon_member%~) == 67 AND $fx_identical_anchor(~%summon_member%~) == summon_id
						AND VARIABLE_IS_SET $fx_summon_random(~%summon_member%~) BEGIN
					SET summon_random += $fx_summon_random(~%summon_member%~)
				END
			END
			PATCH_IF summon_random > 0 BEGIN
				SET amountMin = amount
				SET amountMax = amount + summon_random
				LPF ad_tra INT_VAR tra_id = 21270000 RET amount = text END // ~entre %amountMin% et %amountMax%~
			END
			// L'ancien moteur n'ajoute les dés de vie de la créature (niveau de sa première classe) qu'à la
			// description d'un sort.
			SPRINT lifeDice ~~
			PATCH_IF resource_is_spell BEGIN
				SET creatureLevel = $fx_creature_level(~%summon_id%~)
				LPF ad_tra INT_VAR tra_id = creatureLevel == 1 ? 20670020 : 20670021 RET lifeDice = text END // ~ de 1 dé de vie~
			END
			SET line_phrase = 20670100 + 10 * ($fx_creature_side(~%summon_id%~) + ((summon_random > 0 OR amount > 1) ? 4 : 0)) // ~Invoque 1 « %creatureName% »%lifeDice%~
			SET line_fx = summon_id
			LPM ad_effect_line
		END
	END
END
