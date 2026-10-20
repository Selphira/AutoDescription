// Opcode 67 (Summon: Creature Summoning) : invoque la créature resource : « Invoque 1 « Ras » pendant
// 4 rounds ». parameter2 règle l'allégeance de la créature (IESDP) : 0, 1, 3 et 5 la font dépendre de
// celle du lanceur, sinon l'ancien moteur précise celle du fichier de la créature (hostile, alliée,
// neutre). Avec AD_ENABLE_SHRINKAGE, des invocations identiques n'en font qu'une, avec leur nombre
// (fx_identical_count, ad_group_identical_effects).

// Refus : créature sans nom (aucune ligne) ; avec AD_ENABLE_SHRINKAGE, invocations identiques sauf
// leurs probabilités, dont une certaine (l'ancien opcode_67_group en écrit le nombre « entre 1 et
// 2 »).
DEFINE_PATCH_MACRO ad_op_67_support BEGIN
	FOR (summon_id = 0; summon_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++summon_id) BEGIN
		PATCH_IF $fx_opcode(~%summon_id%~) == 67 BEGIN
			SPRINT summon_resref $fx_resource(~%summon_id%~)
			LPF ad_creature_info STR_VAR resref = ~%summon_resref%~ RET summon_name = name summon_allegiance = allegiance END
			PATCH_IF ~%summon_name%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode67:no_name~
			END
			ELSE BEGIN
				SPRINT $fx_creature_name(~%summon_id%~) ~%summon_name%~
				SET summon_mode = $fx_parameter2(~%summon_id%~)
				// Seuils GOODCUTOFF (30) et EVILCUTOFF (200) de ea.ids.
				SET $fx_creature_side(~%summon_id%~) = (summon_mode == 0 OR summon_mode == 1 OR summon_mode == 3 OR summon_mode == 5) ? 0
					: (summon_allegiance >= 200 ? 1 : (summon_allegiance <= 30 ? 2 : 3))
				PATCH_IF AD_ENABLE_SHRINKAGE AND $fx_probability(~%summon_id%~) == 100 BEGIN
					LPM ad_op_67_random_support
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_67_random_support BEGIN
	LPF ad_fx_signature INT_VAR fx_id = summon_id with_probability = 0 RET summon_signature = signature END
	FOR (summon_other = 0; summon_other < fx_count; ++summon_other) BEGIN
		PATCH_IF summon_other != summon_id AND $fx_opcode(~%summon_other%~) == 67 AND $fx_probability(~%summon_other%~) < 100 BEGIN
			LPF ad_fx_signature INT_VAR fx_id = summon_other with_probability = 0 RET summon_other_signature = signature END
			SPRINT summon_other_resref $fx_resource(~%summon_other%~)
			PATCH_IF (~%summon_other_signature%~ STRING_EQUAL ~%summon_signature%~) AND (~%summon_other_resref%~ STRING_EQUAL_CASE ~%summon_resref%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode67:random_amount~
			END
		END
	END
END

// Phrase : 20 670 100 + 10 × variante + forme ; variante = côté (0 selon le lanceur, 1 hostile,
// 2 allié, 3 neutre), + 4 pour plusieurs créatures.
DEFINE_PATCH_MACRO ad_op_67_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~67~)
	FOR (summon_id = 0; summon_id < fx_count; ++summon_id) BEGIN
		PATCH_IF $fx_opcode(~%summon_id%~) == 67 AND NOT $fx_consumed(~%summon_id%~) BEGIN
			SPRINT creatureName $fx_creature_name(~%summon_id%~)
			SET amount = AD_ENABLE_SHRINKAGE ? $fx_identical_count(~%summon_id%~) : 1
			// L'ancien moteur n'ajoute les dés de vie de la créature qu'à la description d'un sort.
			SPRINT lifeDice ~~
			SET line_phrase = 20670100 + 10 * ($fx_creature_side(~%summon_id%~) + (amount > 1 ? 4 : 0)) // ~Invoque 1 « %creatureName% »%lifeDice%~
			SET line_fx = summon_id
			LPM ad_effect_line
		END
	END
END
