// Opcode 127 (Summon: Monster Summoning) : invoque des créatures de la table parameter2 (0 à 4 :
// MONSUM01, MONSUM02, MONSUM03, ANISUM01, ANISUM02, dont les deux dernières d'animaux ; 5 à 9 : les
// mêmes, hostiles) jusqu'à un total de niveaux de puissance parameter1 : « Invoque entre 3 et 5
// monstres (Garde d'élite gnoll, Loup noir, Garde d'élite hobgobelin ou Ogre) ». Nombre de chaque
// créature (ancien get_creatures_amount) : le total divisé par son niveau de puissance, arrondi
// au-dessus, au moins 1, au plus la limite des invocations (ligne NORMAL de SUMMLIMT.2DA, 5 sans
// elle) ; la ligne donne le plus petit et le plus grand de la table, multipliés par le nombre
// d'effets identiques (fx_identical_count, avec AD_ENABLE_SHRINKAGE).

// Refus : table de la ressource ou special non nul (niveau du lanceur) ; parameter2 hors de 0-9,
// parameter1 négatif ; table absente ou sans créature, ou dont aucune n'a de nom ; créature de niveau
// de puissance nul, hors des invocations ordinaires (allégeance au plus 15 sauf familier, genre
// invoqué : l'ancien moteur en compte 0, ou applique aux célestes la limite ordinaire), dont l'ancien
// arrondi diffère de l'arrondi au-dessus (BUG-033) ou dont le nom contient une virgule (l'ancien
// moteur y coupe la liste) ; avec AD_ENABLE_SHRINKAGE, invocations du même bloc qui ne diffèrent que
// par parameter1 ou leur probabilité (l'ancien opcode_127_group en écrit le nombre « entre 0 et N »).
// Pour l'en-tête d'un sort seul, seuls comptent l'ancien opcode_127_is_valid, qui écarte l'effet
// d'une table resource absente, et ces regroupements (ad_op_127_header_group).
DEFINE_PATCH_MACRO ad_op_127_support BEGIN
	PHP_EACH fx_ids_127 AS _ => monster_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET monster_table = $fx_parameter2(~%monster_id%~)
			SPRINT monster_resref $fx_resource(~%monster_id%~)
			SET monster_custom = $fx_special(~%monster_id%~) != 0 OR NOT (~%monster_resref%~ STRING_EQUAL ~~)
			PATCH_IF support_header_only BEGIN
				PATCH_IF monster_custom AND NOT FILE_EXISTS_IN_GAME ~%monster_resref%.2da~ BEGIN
					SET drop_id = monster_id
					SPRINT ignored_reason ~file_error:opcode127:no_table~
					SPRINT ignored_message ~table %monster_resref%.2DA does not exist~
					LPM ad_application_drop
				END
				ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND NOT monster_custom AND NOT $fx_consumed(~%monster_id%~) BEGIN
					LPM ad_op_127_header_group
				END
			END
			ELSE PATCH_IF $fx_special(~%monster_id%~) != 0 OR NOT (~%monster_resref%~ STRING_EQUAL ~~) OR monster_table < 0 OR monster_table > 9 BEGIN
				PATCH_IF (monster_table < 0 OR monster_table > 9) AND $fx_special(~%monster_id%~) == 0 AND ~%monster_resref%~ STRING_EQUAL ~~ BEGIN
					LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~file_error:opcode127:table~ message = ~monster table %monster_table% (expected 0-9)~ RET render_missing = refusal END
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~not_implemented:opcode127:table~ message = ~custom table or special value not supported~ RET render_missing = refusal END
				END
			END
			ELSE PATCH_IF $fx_parameter1(~%monster_id%~) < 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~file_error:opcode127:level~ message = ~negative total level~ RET render_missing = refusal END
			END
			ELSE BEGIN
				LPM ad_op_127_table
				PATCH_IF AD_ENABLE_SHRINKAGE AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
					LPM ad_op_127_similar_support
				END
			END
		END
	END
END

// Créatures de la table de l'effet monster_id : noms (fx_monster_creatures), plus petit et plus grand
// nombre pour un seul effet (fx_monster_min, fx_monster_max).
DEFINE_PATCH_MACRO ad_op_127_table BEGIN
	SET monster_index = monster_table MODULO 5
	PATCH_IF monster_index < 3 BEGIN
		SET monster_number = monster_index + 1
		SPRINT monster_file ~MONSUM0%monster_number%~
	END
	ELSE BEGIN
		SET monster_number = monster_index - 2
		SPRINT monster_file ~ANISUM0%monster_number%~
	END
	SET monster_total = $fx_parameter1(~%monster_id%~)
	SET monster_limit = 5
	PATCH_IF FILE_EXISTS_IN_GAME ~summlimt.2da~ BEGIN
		INNER_PATCH_FILE ~summlimt.2da~ BEGIN
			COUNT_2DA_ROWS 2 monster_rows
			FOR (monster_row = 0; monster_row < monster_rows; ++monster_row) BEGIN
				READ_2DA_ENTRY monster_row 0 2 monster_kind
				PATCH_IF ~%monster_kind%~ STRING_EQUAL ~NORMAL~ BEGIN
					READ_2DA_ENTRY monster_row 1 2 monster_limit
				END
			END
		END
	END
	SET monster_min = 0
	SET monster_max = 0
	CLEAR_ARRAY monster_names
	PATCH_IF NOT FILE_EXISTS_IN_GAME ~%monster_file%.2da~ BEGIN
		LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~file_error:opcode127:no_table~ message = ~table %monster_file%.2DA does not exist~ RET render_missing = refusal END
	END
	ELSE BEGIN
		INNER_PATCH_FILE ~%monster_file%.2da~ BEGIN
			COUNT_2DA_ROWS 2 monster_rows
			FOR (monster_row = 1; monster_row < monster_rows; ++monster_row) BEGIN
				READ_2DA_ENTRY monster_row 1 2 monster_resref
				PATCH_IF FILE_EXISTS_IN_GAME ~%monster_resref%.cre~ BEGIN
					LPM ad_op_127_creature
				END
			END
		END
	END
	SPRINT monster_or @1000007 // ~ou~
	LPF ad_join STR_VAR array_name = ~monster_names~ final_glue = EVAL ~ %monster_or% ~ RET monster_creatures = text END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND (monster_max == 0 OR ~%monster_creatures%~ STRING_EQUAL ~~) BEGIN
		LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~not_implemented:opcode127:no_creature~ message = ~no named creature in table %monster_file%.2DA~ RET render_missing = refusal END
	END
	SPRINT $fx_monster_creatures(~%monster_id%~) ~%monster_creatures%~
	SET $fx_monster_min(~%monster_id%~) = monster_min
	SET $fx_monster_max(~%monster_id%~) = monster_max
END

// Créature monster_resref (ligne monster_row) de la table.
DEFINE_PATCH_MACRO ad_op_127_creature BEGIN
	INNER_PATCH_FILE ~%monster_resref%.cre~ BEGIN
		READ_LONG CRE_XP_power_level monster_power
		READ_BYTE CRE_allegiance monster_allegiance
		READ_BYTE CRE_gender monster_gender
	END
	LPF ad_creature_info STR_VAR resref = ~%monster_resref%~ RET monster_name = name END
	// Genres SUMMONED (6) et SUMMONED_DEMON (9) de gender.ids, allégeance FAMILIAR (3) de ea.ids.
	PATCH_IF monster_allegiance > 15 OR monster_allegiance == 3 OR (monster_gender != 6 AND monster_gender != 9) BEGIN
		LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~not_implemented:opcode127:limit~ message = ~creature %monster_resref%.CRE that does not count towards the summoning limit~ RET render_missing = refusal END
	END
	ELSE PATCH_IF monster_power <= 0 BEGIN
		LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~not_implemented:opcode127:power~ message = ~creature %monster_resref%.CRE with a power level of %monster_power%~ RET render_missing = refusal END
	END
	ELSE BEGIN
		// L'ancien moteur arrondit au dixième, puis au-dessus.
		SET monster_count = monster_total * 10 / monster_power
		SET monster_tenths = monster_count MODULO 10
		SET monster_count = monster_count / 10 + (monster_tenths > 0 ? 1 : 0)
		PATCH_IF monster_count != (monster_total + monster_power - 1) / monster_power BEGIN
			LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~not_implemented:opcode127:rounding~ message = ~number of creatures rounded differently by the old engine~ RET render_missing = refusal END
		END
		SET monster_count = (monster_count < 1) ? 1 : monster_count
		SET monster_count = (monster_count > monster_limit) ? monster_limit : monster_count
		SET monster_min = (monster_min == 0 OR monster_min > monster_count) ? monster_count : monster_min
		SET monster_max = (monster_max < monster_count) ? monster_count : monster_max
	END
	PATCH_IF ~%monster_name%~ STRING_CONTAINS_REGEXP ~,~ == 0 BEGIN
		LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~not_implemented:opcode127:name~ message = ~creature name with a comma~ RET render_missing = refusal END
	END
	ELSE PATCH_IF NOT (~%monster_name%~ STRING_EQUAL ~~) BEGIN
		SPRINT $monster_names(~%monster_row%~) ~%monster_name%~
	END
END

// L'ancien opcode_127_group remplace les invocations semblables à monster_id par un seul effet, de
// ses champs, ajouté après les autres effets 127.
DEFINE_PATCH_MACRO ad_op_127_header_group BEGIN
	SET same_id = monster_id
	SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PROBABILITY
	PHP_EACH fx_ids_127 AS _ => monster_other BEGIN
		PATCH_IF monster_other != monster_id AND NOT $fx_consumed(~%monster_other%~) BEGIN
			SET same_other = monster_other
			LPM ad_fx_same_fields
			PATCH_IF fx_same BEGIN
				SET $fx_consumed(~%monster_other%~) = 1
				SET $fx_late(~%monster_id%~) = 1
			END
		END
	END
	SET same_ignored = 0
END

DEFINE_PATCH_MACRO ad_op_127_similar_support BEGIN
	SET same_id = monster_id
	PHP_EACH fx_ids_127 AS _ => monster_other BEGIN
		PATCH_IF monster_other != monster_id BEGIN
			SET same_other = monster_other
			SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PROBABILITY
			LPM ad_fx_same_fields
			SET monster_other_similar = fx_same
			SET same_ignored = 0
			LPM ad_fx_same_fields
			SPRINT monster_other_resref $fx_resource(~%monster_other%~)
			PATCH_IF monster_other_similar AND NOT fx_same AND ~%monster_other_resref%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = monster_other STR_VAR reason = ~not_implemented:opcode127:similar~ message = ~similar summonings with different fields~ RET render_missing = refusal END
			END
		END
	END
END

// Phrase : 21 270 100 + 10 × variante + forme ; variante = 0 un monstre, 1 un animal, 2 plusieurs
// monstres, 3 plusieurs animaux, + 4 hostiles. Un effet identique à d'autres est écrit après les
// autres effets 127 (fx_late), comme celui que l'ancien moteur ajoute en fin de liste.
DEFINE_PATCH_MACRO ad_op_127_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~127~)
	FOR (monster_late = 0; monster_late <= 1; ++monster_late) BEGIN
		PHP_EACH fx_ids_127 AS _ => monster_id BEGIN
			PATCH_IF NOT $fx_consumed(~%monster_id%~) AND $fx_late(~%monster_id%~) == monster_late BEGIN
				SET monster_copies = AD_ENABLE_SHRINKAGE ? $fx_identical_count(~%monster_id%~) : 1
				SET amountMin = $fx_monster_min(~%monster_id%~) * monster_copies
				SET amountMax = $fx_monster_max(~%monster_id%~) * monster_copies
				PATCH_IF amountMin == amountMax BEGIN
					SET amount = amountMax
				END
				ELSE BEGIN
					SPRINT amount @21270000 // ~entre %amountMin% et %amountMax%~
				END
				SPRINT creatures $fx_monster_creatures(~%monster_id%~)
				SET monster_table = $fx_parameter2(~%monster_id%~)
				SET monster_variant = (amountMax == 1 ? 0 : 2) + ((monster_table MODULO 5) >= 3 ? 1 : 0) + (monster_table >= 5 ? 4 : 0)
				SET line_phrase = 21270100 + 10 * monster_variant // ~Invoque 1 monstre (%creatures%)~
				SET line_fx = monster_id
				LPM ad_effect_line
			END
		END
	END
END
