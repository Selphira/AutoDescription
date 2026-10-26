// Code commun des renvois et des immunités décroissants par niveau de sort (opcodes 200 et 201) :
// jusqu'à parameter1 niveaux de sorts du niveau parameter2 : « Immunise jusqu'à 9 niveaux de sorts
// parmi ceux de 5ème niveau ». Avec AD_ENABLE_SHRINKAGE, les effets d'un même bloc de même total
// n'en font qu'un (ancien opcode_200_group), ses niveaux réunis : tous (« jusqu'à 9 niveaux de
// sorts »), du 1er au N-ième (« parmi ceux de 5ème niveau et inférieur »), sinon leur liste (« de 1er
// et 3ème niveau »). Les macros ad_op_<N>_* fixent power_opcode (et power_phrase pour les lignes)
// puis appellent les macros ci-dessous.

// Refus : niveau hors de 1-9 (l'ancien moteur écarte un niveau hors de 0-9 et écrit le niveau 0 sans
// nom) ; total inférieur à 1 (écarté par l'ancien opcode_200_is_valid sur un jeu classique, « Lance »
// sur EE) ; sur EE, sort à lancer qui a un nom (la ressource, sinon le sort <objet>B : l'ancien
// side_spell ajoute « puis lance « … » ») ; sans AD_ENABLE_SHRINKAGE, niveau au-delà de 2 (l'ancien
// moteur le lit comme une liste de niveaux, BUG-034). Avec AD_ENABLE_SHRINKAGE, des effets de même
// total aux autres champs différents (durée…) forment des lignes distinctes ; l'anomalie de la série
// est journalisée (erreur de fichier, décrit quand même : SPWI318 au niveau 11).
DEFINE_PATCH_MACRO ad_spell_power_support BEGIN
	SPRINT power_own_spell ~~
	PATCH_IF IS_EE AND STRING_LENGTH ~%ctx_resource%~ <= 7 BEGIN
		LPF ad_spell_name STR_VAR resref = EVAL ~%ctx_resource%B~ RET power_own_spell = name END
	END
	PHP_EACH ~fx_ids_%power_opcode%~ AS _ => power_id BEGIN
		SET $fx_power_mask(~%power_id%~) = 0
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET power_level = $fx_parameter2(~%power_id%~)
			SPRINT power_resref $fx_resource(~%power_id%~)
			SPRINT power_spell ~%power_own_spell%~
			PATCH_IF NOT (~%power_resref%~ STRING_EQUAL ~~) BEGIN
				LPF ad_spell_name STR_VAR resref = ~%power_resref%~ RET power_spell = name END
			END
			PATCH_IF power_level < 1 OR power_level > 9 BEGIN
				LPF ad_refusal INT_VAR fx_id = power_id STR_VAR reason = ~file_error:opcode%power_opcode%:level~ message = ~spell level %power_level% (expected 1-9)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_parameter1(~%power_id%~) < 1 BEGIN
				LPF ad_refusal INT_VAR fx_id = power_id STR_VAR reason = ~file_error:opcode%power_opcode%:amount~ message = ~amount of 0 or less~ RET render_missing = refusal END
			END
			ELSE PATCH_IF IS_EE AND NOT (~%power_spell%~ STRING_EQUAL ~~) BEGIN
				LPF ad_refusal INT_VAR fx_id = power_id STR_VAR reason = ~not_implemented:opcode%power_opcode%:spell~ message = ~spell given in the resource field~ RET render_missing = refusal END
			END
			ELSE PATCH_IF NOT AD_ENABLE_SHRINKAGE AND power_level > 2 BEGIN
				LPF ad_refusal INT_VAR fx_id = power_id STR_VAR reason = ~not_implemented:opcode%power_opcode%:level_mask~ message = ~spell level above 2 without AD_ENABLE_SHRINKAGE~ RET render_missing = refusal END
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
				LPM ad_spell_power_group_support
			END
		END
	END
END

// Effets de même total de la portée de power_id, s'il en est le premier, aux autres champs
// différents : journalisés.
DEFINE_PATCH_MACRO ad_spell_power_group_support BEGIN
	SET same_id = power_id
	SET same_ignored = AD_SAME_PARAMETER2 BOR AD_SAME_SPECIAL
	SPRINT power_scope $fx_scope(~%power_id%~)
	SET power_first = 1
	PHP_EACH ~fx_ids_%power_opcode%~ AS _ => power_other BEGIN
		SPRINT power_other_scope $fx_scope(~%power_other%~)
		PATCH_IF power_other < power_id AND (~%power_other_scope%~ STRING_EQUAL ~%power_scope%~) AND $fx_parameter1(~%power_other%~) == $fx_parameter1(~%power_id%~) BEGIN
			SET power_first = 0
		END
	END
	PHP_EACH ~fx_ids_%power_opcode%~ AS _ => power_other BEGIN
		SPRINT power_other_scope $fx_scope(~%power_other%~)
		PATCH_IF power_first AND power_other > power_id AND (~%power_other_scope%~ STRING_EQUAL ~%power_scope%~) AND $fx_parameter1(~%power_other%~) == $fx_parameter1(~%power_id%~) BEGIN
			SET same_other = power_other
			LPM ad_fx_same_fields
			PATCH_IF NOT fx_same BEGIN
				SET power_other_duration = $fx_duration(~%power_other%~)
				SET power_duration = $fx_duration(~%power_id%~)
				SET power_other_level = $fx_parameter2(~%power_other%~)
				LPF ad_refusal INT_VAR fx_id = power_other STR_VAR reason = ~file_error:opcode%power_opcode%:inconsistent_series~ message = ~spell level %power_other_level% with other fields than the first effect of the same total (duration %power_other_duration% instead of %power_duration%), written on its own line~ RET power_event = refusal END
				LPF ad_log_event STR_VAR event = ~%power_event%~ consequence = ~kept~ RET power_logged = reason END
			END
		END
	END
END

// Sort à plusieurs en-têtes (new-lib/spell_header.tpp), comme l'ancien opcode_200_group avant la
// comparaison des niveaux : dans chaque en-tête, les effets de même total et de mêmes champs sont
// réunis au premier (fx_power_mask : masque des niveaux), les autres écartés ; les en-têtes se
// comparent avec ce masque (ad_spell_level_same).
DEFINE_PATCH_MACRO ad_spell_power_header_groups BEGIN
	PHP_EACH ~fx_ids_%power_opcode%~ AS _ => power_id BEGIN
		PATCH_IF NOT $fx_consumed(~%power_id%~) AND $fx_power_mask(~%power_id%~) == 0 BEGIN
			SET power_mask = 1 << ($fx_parameter2(~%power_id%~) - 1)
			SET same_id = power_id
			SET same_ignored = AD_SAME_PARAMETER2 BOR AD_SAME_SPECIAL
			PHP_EACH ~fx_ids_%power_opcode%~ AS _ => power_other BEGIN
				PATCH_IF power_other > power_id AND NOT $fx_consumed(~%power_other%~) AND $fx_header(~%power_other%~) == $fx_header(~%power_id%~)
						AND $fx_parameter1(~%power_other%~) == $fx_parameter1(~%power_id%~) BEGIN
					SET same_other = power_other
					LPM ad_fx_same_fields
					PATCH_IF fx_same BEGIN
						SET power_mask = power_mask BOR (1 << ($fx_parameter2(~%power_other%~) - 1))
						SET $fx_consumed(~%power_other%~) = 1
					END
				END
			END
			SET $fx_power_mask(~%power_id%~) = power_mask
		END
	END
END

// Phrase : power_phrase + 10 × variante + forme ; variante 0 liste de niveaux, 1 tous les niveaux,
// 2 du 1er au N-ième.
DEFINE_PATCH_MACRO ad_spell_power_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%power_opcode%~)
	FOR (power_id = 0; power_id < fx_count; ++power_id) BEGIN
		SET $power_anchor(~%power_id%~) = power_id
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		PHP_EACH ~fx_ids_%power_opcode%~ AS _ => power_id BEGIN
			SPRINT power_scope $fx_scope(~%power_id%~)
			PATCH_IF NOT $fx_consumed(~%power_id%~) AND $power_anchor(~%power_id%~) == power_id BEGIN
				PHP_EACH ~fx_ids_%power_opcode%~ AS _ => power_other BEGIN
					SPRINT power_other_scope $fx_scope(~%power_other%~)
					PATCH_IF power_other >= power_id + 1 AND NOT $fx_consumed(~%power_other%~) AND (~%power_other_scope%~ STRING_EQUAL ~%power_scope%~) AND $fx_parameter1(~%power_other%~) == $fx_parameter1(~%power_id%~)
							AND $power_anchor(~%power_other%~) == power_other BEGIN
						SET same_id = power_id
						SET same_other = power_other
						SET same_ignored = AD_SAME_PARAMETER2 BOR AD_SAME_SPECIAL
						LPM ad_fx_same_fields
						PATCH_IF fx_same BEGIN
							SET $power_anchor(~%power_other%~) = power_id
						END
					END
				END
			END
		END
	END
	PHP_EACH ~fx_ids_%power_opcode%~ AS _ => power_id BEGIN
		PATCH_IF NOT $fx_consumed(~%power_id%~) AND $power_anchor(~%power_id%~) == power_id BEGIN
			SET power_mask = 0
			PHP_EACH ~fx_ids_%power_opcode%~ AS _ => power_member BEGIN
				PATCH_IF power_member >= power_id AND NOT $fx_consumed(~%power_member%~) AND $power_anchor(~%power_member%~) == power_id BEGIN
					SET power_bit = 1
					FOR (power_shift = 1; power_shift < $fx_parameter2(~%power_member%~); ++power_shift) BEGIN
						SET power_bit *= 2
					END
					// Effet qui en réunit déjà d'autres dans son en-tête (ad_spell_power_header_groups).
					PATCH_IF $fx_power_mask(~%power_member%~) > 0 BEGIN
						SET power_bit = $fx_power_mask(~%power_member%~)
					END
					SET power_mask = power_mask BOR power_bit
				END
			END
			LPM ad_spell_power_levels
			SET amount = $fx_parameter1(~%power_id%~)
			SET line_phrase = power_phrase + 10 * power_variant // ~Immunise jusqu'à %amount% niveaux de sorts parmi ceux de %levelStr% niveau~
			SET line_fx = power_id
			LPM ad_effect_line
		END
	END
END

// Variante et niveaux (levelStr) du masque power_mask (bit n : niveau n + 1).
DEFINE_PATCH_MACRO ad_spell_power_levels BEGIN
	CLEAR_ARRAY power_levels
	SET power_count = 0
	SET power_top = 0
	FOR (power_level = 1; power_level <= 9; ++power_level) BEGIN
		SET power_bit = 1
		FOR (power_shift = 1; power_shift < power_level; ++power_shift) BEGIN
			SET power_bit *= 2
		END
		PATCH_IF (power_mask BAND power_bit) != 0 BEGIN
			LPF ad_tra INT_VAR tra_id = 8010000 + power_level tra_block_start = 8010000 tra_block_size = 10 RET power_ordinal = text END // ~5ème~ (@8010005)
			SPRINT $power_levels(~%power_count%~) ~%power_ordinal%~
			SET power_count += 1
			SET power_top = power_level
		END
	END
	PATCH_IF power_mask == 511 BEGIN
		SET power_variant = 1
		SPRINT levelStr ~~
	END
	// Masques 3, 7… 255 : du 1er au N-ième niveau, sans trou.
	ELSE PATCH_IF power_count == power_top AND power_count > 1 BEGIN
		SET power_variant = 2
		SPRINT levelStr ~%power_ordinal%~
	END
	ELSE BEGIN
		SET power_variant = 0
		LPF ad_join STR_VAR array_name = ~power_levels~ RET levelStr = text END
	END
END
