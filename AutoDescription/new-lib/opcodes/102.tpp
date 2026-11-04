// Opcode 102 (Spell: Immunity by Power Level) : immunité aux effets de puissance parameter1 (0-9,
// IESDP), écrite comme une immunité aux sorts de ce niveau. Avec
// AD_ENABLE_SHRINKAGE, les 102 d'une même portée n'en font qu'un (ancien opcode_102_group, opcode
// virtuel 509 ; ad_group_spell_levels, new-lib/groups.tpp) : masque des niveaux fx_spell_levels
// (niveaux 1 à 9 aux bits 0 à 8, niveau 0 au bit 9, AD_SPELL_LEVEL_ZERO),
// « Immunité aux sorts de 5ème niveau et inférieurs », ou « Immunité aux sorts » pour les neuf
// niveaux.

// Niveau hors de 0-9 : écarté et journalisé. Sans AD_ENABLE_SHRINKAGE, chaque 102 est un masque d'un
// seul niveau (« de 5ème niveau », « de niveau 0 »). Refus : effet d'un EFF ; 102 de la même portée
// aux champs différents (l'ancien moteur les réunit tous, avec les champs du dernier lu).
DEFINE_PATCH_MACRO ad_op_102_support BEGIN
	PHP_EACH fx_ids_102 AS _ => levels_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%levels_id%~) BEGIN
			SET levels_level = $fx_parameter1(~%levels_id%~)
			SET $fx_spell_levels(~%levels_id%~) = 0
			PATCH_IF $fx_external(~%levels_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = levels_id STR_VAR reason = ~not_implemented:opcode102:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF levels_level < 0 OR levels_level > 9 BEGIN
				SET drop_id = levels_id
				SPRINT ignored_reason ~file_error:opcode102:invalid~
				SPRINT ignored_message ~spell level %levels_level% (expected 0-9)~
				LPM ad_application_drop
			END
			ELSE PATCH_IF NOT AD_ENABLE_SHRINKAGE BEGIN
				SET $fx_spell_levels(~%levels_id%~) = levels_level == 0 ? AD_SPELL_LEVEL_ZERO : 1 << (levels_level - 1)
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
						ELSE PATCH_IF levels_other_level >= 0 AND levels_other_level <= 9 BEGIN
							SET levels_mask = levels_mask BOR (levels_other_level == 0 ? AD_SPELL_LEVEL_ZERO : 1 << (levels_other_level - 1))
						END
					END
				END
			END
		END
	END
END

// Une ligne par effet réuni (ou, sans AD_ENABLE_SHRINKAGE, par 102 d'un seul niveau) : niveaux 1 à 9 (« Immunité contre les sorts »), 1 à N (« de 5ème niveau
// et inférieurs »), qui couvrent le niveau 0 s'il est réuni, ou leur liste (« de 1er, 3ème et 5ème
// niveau », ancien opcode_509_common), y compris le niveau 1 seul ; le niveau 0 est nommé à part
// (« de niveau 0 », « de niveau 0 et de 1er et 3ème niveau »).
DEFINE_PATCH_MACRO ad_op_102_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_DERIVED_SORT(~SPELL_LEVELS~)
	PHP_EACH fx_ids_102 AS _ => levels_id BEGIN
		PATCH_IF NOT $fx_consumed(~%levels_id%~) AND $fx_spell_levels(~%levels_id%~) > 0 BEGIN
			SET levels_zero = ($fx_spell_levels(~%levels_id%~) BAND AD_SPELL_LEVEL_ZERO) != 0
			SET levels_mask = $fx_spell_levels(~%levels_id%~) BAND 0x1FF
			SET line_fx = levels_id
			PATCH_IF levels_mask == 0x1FF BEGIN
				SET line_phrase = 21020120 // ~Immunité contre les sorts~
			END
			ELSE PATCH_IF levels_mask == 0 BEGIN
				SET line_phrase = 21020130 // ~Immunité contre les sorts de niveau 0~
			END
			ELSE PATCH_IF levels_mask != 1 AND (levels_mask BAND (levels_mask + 1)) == 0 BEGIN
				SET levels_top = 0
				WHILE (levels_mask >> levels_top) > 0 BEGIN
					SET levels_top += 1
				END
				LPF ad_tra INT_VAR tra_id = 8010000 + levels_top tra_block_start = 8010001 tra_block_size = 9 RET spellLevel = text END // ~5ème~ (@8010005)
				SET line_phrase = 21020110 // ~Immunité contre les sorts de %spellLevel% niveau et inférieurs~
			END
			ELSE BEGIN
				CLEAR_ARRAY levels_names
				FOR (levels_level = 1; levels_level <= 9; ++levels_level) BEGIN
					PATCH_IF (levels_mask BAND (1 << (levels_level - 1))) != 0 BEGIN
						LPF ad_tra INT_VAR tra_id = 8010000 + levels_level tra_block_start = 8010001 tra_block_size = 9 RET levels_name = text END // ~5ème~ (@8010005)
						SPRINT $levels_names(~%levels_level%~) ~%levels_name%~
					END
				END
				LPF ad_join STR_VAR array_name = ~levels_names~ RET spellLevel = text END
				SET line_phrase = levels_zero ? 21020140 : 21020100 // ~Immunité contre les sorts de %spellLevel% niveau~ (21020140 : ~Immunité contre les sorts de niveau 0 et de %spellLevel% niveau~)
			END
			LPM ad_effect_line
		END
	END
END
