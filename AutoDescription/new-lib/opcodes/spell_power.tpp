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
// moteur le lit comme une liste de niveaux, BUG-034) ; avec AD_ENABLE_SHRINKAGE, effets de même total
// aux autres champs différents (l'ancien moteur les réunit et garde ceux du dernier effet lu).
DEFINE_PATCH_MACRO ad_spell_power_support BEGIN
	SPRINT power_own_spell ~~
	PATCH_IF IS_EE AND STRING_LENGTH ~%ctx_resource%~ <= 7 BEGIN
		LPF ad_spell_name STR_VAR resref = EVAL ~%ctx_resource%B~ RET power_own_spell = name END
	END
	FOR (power_id = 0; power_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++power_id) BEGIN
		PATCH_IF $fx_opcode(~%power_id%~) == power_opcode BEGIN
			SET power_level = $fx_parameter2(~%power_id%~)
			SPRINT power_resref $fx_resource(~%power_id%~)
			SPRINT power_spell ~%power_own_spell%~
			PATCH_IF NOT (~%power_resref%~ STRING_EQUAL ~~) BEGIN
				LPF ad_spell_name STR_VAR resref = ~%power_resref%~ RET power_spell = name END
			END
			PATCH_IF power_level < 1 OR power_level > 9 BEGIN
				SPRINT render_missing ~not_implemented:opcode%power_opcode%:level~
			END
			ELSE PATCH_IF $fx_parameter1(~%power_id%~) < 1 BEGIN
				SPRINT render_missing ~not_implemented:opcode%power_opcode%:amount~
			END
			ELSE PATCH_IF IS_EE AND NOT (~%power_spell%~ STRING_EQUAL ~~) BEGIN
				SPRINT render_missing ~not_implemented:opcode%power_opcode%:spell~
			END
			ELSE PATCH_IF NOT AD_ENABLE_SHRINKAGE AND power_level > 2 BEGIN
				SPRINT render_missing ~not_implemented:opcode%power_opcode%:level_mask~
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
				LPM ad_spell_power_group_support
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_spell_power_group_support BEGIN
	LPF ad_fx_signature INT_VAR fx_id = power_id with_parameter2 = 0 with_special = 0 RET power_signature = signature END
	SPRINT power_scope $fx_scope(~%power_id%~)
	FOR (power_other = 0; power_other < fx_count; ++power_other) BEGIN
		SPRINT power_other_scope $fx_scope(~%power_other%~)
		PATCH_IF $fx_opcode(~%power_other%~) == power_opcode AND (~%power_other_scope%~ STRING_EQUAL ~%power_scope%~)
				AND $fx_parameter1(~%power_other%~) == $fx_parameter1(~%power_id%~) BEGIN
			LPF ad_fx_signature INT_VAR fx_id = power_other with_parameter2 = 0 with_special = 0 RET power_other_signature = signature END
			PATCH_IF NOT (~%power_other_signature%~ STRING_EQUAL ~%power_signature%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode%power_opcode%:group_fields~
			END
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
		FOR (power_id = 0; power_id < fx_count; ++power_id) BEGIN
			SPRINT power_scope $fx_scope(~%power_id%~)
			PATCH_IF $fx_opcode(~%power_id%~) == power_opcode AND NOT $fx_consumed(~%power_id%~) AND $power_anchor(~%power_id%~) == power_id BEGIN
				FOR (power_other = power_id + 1; power_other < fx_count; ++power_other) BEGIN
					SPRINT power_other_scope $fx_scope(~%power_other%~)
					PATCH_IF $fx_opcode(~%power_other%~) == power_opcode AND NOT $fx_consumed(~%power_other%~)
							AND (~%power_other_scope%~ STRING_EQUAL ~%power_scope%~)
							AND $fx_parameter1(~%power_other%~) == $fx_parameter1(~%power_id%~) BEGIN
						SET $power_anchor(~%power_other%~) = power_id
					END
				END
			END
		END
	END
	FOR (power_id = 0; power_id < fx_count; ++power_id) BEGIN
		PATCH_IF $fx_opcode(~%power_id%~) == power_opcode AND NOT $fx_consumed(~%power_id%~) AND $power_anchor(~%power_id%~) == power_id BEGIN
			SET power_mask = 0
			FOR (power_member = power_id; power_member < fx_count; ++power_member) BEGIN
				PATCH_IF $fx_opcode(~%power_member%~) == power_opcode AND NOT $fx_consumed(~%power_member%~) AND $power_anchor(~%power_member%~) == power_id BEGIN
					SET power_bit = 1
					FOR (power_shift = 1; power_shift < $fx_parameter2(~%power_member%~); ++power_shift) BEGIN
						SET power_bit *= 2
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
