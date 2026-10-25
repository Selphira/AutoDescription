// Opcode 102 (Spell: Immunity by Power Level) : immunité aux sorts de niveau parameter1. Avec
// AD_ENABLE_SHRINKAGE, les 102 d'une même portée n'en font qu'un (ancien opcode_102_group, opcode
// virtuel 509 ; ad_group_spell_levels, new-lib/groups.tpp) : masque des niveaux fx_spell_levels,
// « Immunité aux sorts de 5ème niveau et inférieurs », ou « Immunité aux sorts » pour les neuf
// niveaux.

// Refus : effet d'un EFF ; niveau hors de 1-9 ; 102 non réuni (l'ancien opcode_self_102 écrit le
// nombre à la place du rang et ses formes « cible » et probables prennent les chaînes d'autres
// formes, BUG-041) ; 102 de la même portée aux champs différents (l'ancien moteur les réunit tous,
// avec les champs du dernier lu) ; niveaux réunis qui ne vont pas de 1 à N (l'ancien moteur en
// écrit la liste par une fonction non reproduite) ou niveau 1 seul.
DEFINE_PATCH_MACRO ad_op_102_support BEGIN
	PHP_EACH fx_ids_102 AS _ => levels_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%levels_id%~) BEGIN
			SET levels_level = $fx_parameter1(~%levels_id%~)
			SET $fx_spell_levels(~%levels_id%~) = 0
			PATCH_IF $fx_external(~%levels_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = levels_id STR_VAR reason = ~not_implemented:opcode102:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF levels_level < 1 OR levels_level > 9 BEGIN
				LPF ad_refusal INT_VAR fx_id = levels_id STR_VAR reason = ~file_error:opcode102:invalid~ message = ~spell level %levels_level% (expected 1-9)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF NOT AD_ENABLE_SHRINKAGE BEGIN
				LPF ad_refusal INT_VAR fx_id = levels_id STR_VAR reason = ~not_implemented:opcode102:single~ message = ~single spell level without AD_ENABLE_SHRINKAGE~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET same_id = levels_id
				SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2
				SPRINT levels_scope $fx_scope(~%levels_id%~)
				SET levels_mask = 0
				PHP_EACH fx_ids_102 AS _ => levels_other BEGIN
					SPRINT levels_other_scope $fx_scope(~%levels_other%~)
					PATCH_IF NOT $fx_consumed(~%levels_other%~) AND (~%levels_other_scope%~ STRING_EQUAL ~%levels_scope%~) BEGIN
						SET same_other = levels_other
						LPM ad_fx_same_fields
						SET levels_other_level = $fx_parameter1(~%levels_other%~)
						PATCH_IF NOT fx_same BEGIN
							LPF ad_refusal INT_VAR fx_id = levels_other STR_VAR reason = ~not_implemented:opcode102:group_fields~ message = ~spell level immunities with different fields~ RET render_missing = refusal END
						END
						ELSE PATCH_IF levels_other_level >= 1 AND levels_other_level <= 9 BEGIN
							SET levels_mask = levels_mask BOR (1 << (levels_other_level - 1))
						END
					END
				END
				PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND levels_mask != 0x1FF AND (levels_mask == 1 OR (levels_mask BAND (levels_mask + 1)) != 0) BEGIN
					LPF ad_refusal INT_VAR fx_id = levels_id STR_VAR reason = ~not_implemented:opcode102:levels~ message = ~spell levels that are not a range~ RET render_missing = refusal END
				END
			END
		END
	END
END

// Une ligne par effet réuni : niveaux 1 à N (« de 5ème niveau et inférieurs ») ou tous les niveaux.
DEFINE_PATCH_MACRO ad_op_102_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_DERIVED_SORT(~SPELL_LEVELS~)
	PHP_EACH fx_ids_102 AS _ => levels_id BEGIN
		PATCH_IF NOT $fx_consumed(~%levels_id%~) AND $fx_spell_levels(~%levels_id%~) > 0 BEGIN
			SET levels_mask = $fx_spell_levels(~%levels_id%~)
			SET line_fx = levels_id
			PATCH_IF levels_mask == 0x1FF BEGIN
				SET line_phrase = 21020120 // ~Immunité contre les sorts~
			END
			ELSE BEGIN
				SET levels_top = 0
				WHILE (levels_mask >> levels_top) > 0 BEGIN
					SET levels_top += 1
				END
				LPF ad_tra INT_VAR tra_id = 8010000 + levels_top tra_block_start = 8010001 tra_block_size = 9 RET spellLevel = text END // ~5ème~ (@8010005)
				SET line_phrase = 21020110 // ~Immunité contre les sorts de %spellLevel% niveau et inférieurs~
			END
			LPM ad_effect_line
		END
	END
END
