// Code commun des emplacements de sorts (42 profanes, 62 divins), IESDP : parameter1 = nombre
// d'emplacements ajoutés (négatif : retirés), parameter2 = niveaux touchés, un bit par niveau
// (BIT0 = niveau 1) ; parameter2 = 0 double les emplacements des niveaux 1 à parameter1. Le fichier
// de chaque opcode fixe slots_opcode, slots_max_level (dernier niveau de sort de la classe) et
// slots_priest (1 : type de sort selon les clercs et druides qui peuvent utiliser l'objet).
// Phrases du bloc de l'opcode : 0100 un emplacement, 0110 plusieurs, 0120 un retiré, 0130 plusieurs
// retirés (nombre écrit sans signe), 0140 doublement.
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// lib/application.tpp).

// ---------------------------------------------------------------------------------------------
// Prise en charge (l'ancien moteur n'a pas de macro opcode_42_is_valid ni opcode_62_is_valid)

DEFINE_PATCH_MACRO ad_spell_slots_support BEGIN
	SET slots_all_levels = (1 << slots_max_level) - 1
	PHP_EACH ~fx_ids_%slots_opcode%~ AS _ => slots_id BEGIN
		SET slots_amount = $fx_parameter1(~%slots_id%~)
		SET slots_doubling = $fx_parameter2(~%slots_id%~) == 0
		SPRINT slots_scope $fx_scope(~%slots_id%~)
		SET $slots_seen_levels(~%slots_amount% %slots_doubling% %slots_scope%~) = 0
	END
	FOR (slots_id = 0; slots_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++slots_id) BEGIN
		PATCH_IF $fx_opcode(~%slots_id%~) == slots_opcode BEGIN
			SET slots_amount = $fx_parameter1(~%slots_id%~)
			SET slots_levels = $fx_parameter2(~%slots_id%~)
			// Les doublements et les ajouts d'un même nombre sont réunis séparément.
			SET slots_doubling = slots_levels == 0
			SET slots_levels_used = slots_doubling ? slots_all_levels : slots_levels
			SPRINT slots_scope $fx_scope(~%slots_id%~)
			// Valeurs que l'ancien moteur décrit mal ou pas (aucun texte, niveaux non écrits, BIT9 =
			// doublement d'un seul niveau, écrit « de 3 niveau »).
			PATCH_IF slots_amount == 0 OR slots_amount > 32767 OR slots_amount < 0 - 32768
					OR (slots_levels == 0 AND slots_amount < 0)
					OR (slots_levels BAND (BNOT slots_all_levels)) != 0 BEGIN
				SET drop_id = slots_id
				SPRINT ignored_reason ~file_error:opcode%slots_opcode%:invalid~
				SPRINT ignored_message ~invalid amount %slots_amount% or spell levels~
				LPM ad_application_drop
			END
			// Deux doublements identiques : leur cumul n'est pas décrit.
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND slots_doubling AND ($slots_seen_levels(~%slots_amount% %slots_doubling% %slots_scope%~) BAND slots_levels_used) != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = slots_id STR_VAR reason = ~not_implemented:opcode%slots_opcode%:overlapping_levels~ message = ~overlapping spell levels~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET $slots_seen_levels(~%slots_amount% %slots_doubling% %slots_scope%~) = $slots_seen_levels(~%slots_amount% %slots_doubling% %slots_scope%~) BOR slots_levels_used
			END
		END
	END
	PATCH_IF slots_priest AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_spell_slots_priest_type
		PATCH_IF slots_priest_type < 0 BEGIN
			LPF ad_refusal INT_VAR fx_id = slots_id STR_VAR reason = ~not_implemented:opcode%slots_opcode%:no_priest~ message = ~no priest class in this game~ RET render_missing = refusal END
		END
	END
END

// Index du type de sort divin dans la liste @8020000 (8 020 000 + index, + 10 au singulier) :
// 1 divins, 4 druidiques, 5 divins/druidiques ; -1 si ni les clercs ni les druides ne peuvent
// utiliser l'objet.
DEFINE_PATCH_MACRO ad_spell_slots_priest_type BEGIN
	LPF ad_item_usable_by INT_VAR class_mask = AD_USABILITY_CLERICS RET slots_clerics = usable END
	LPF ad_item_usable_by INT_VAR class_mask = AD_USABILITY_DRUIDS RET slots_druids = usable END
	SET slots_priest_type = (slots_clerics AND slots_druids) ? 5 : (slots_clerics ? 1 : (slots_druids ? 4 : 0 - 1))
END

// ---------------------------------------------------------------------------------------------
// Lignes (ancien opcode_self_42_62 et opcode_42_group)

// Un effet écarté ou réuni à un effet identique (fx_consumed) n'a pas de ligne. Avec
// AD_ENABLE_SHRINKAGE, les doublements viennent d'abord ; puis les ajouts de même portée et de même
// ligne (ad_fx_line_key : probabilité, durée, origine…) sont additionnés niveau par niveau (le jeu
// cumule les emplacements de tous les effets, effets identiques compris), et les niveaux de même
// total forment une ligne, dans l'ordre des niveaux : PXPMAESL, sept 62 de 1 emplacement aux masques
// 1 à 7, « 4 emplacements de 1er, 2ème et 3ème niveau ». Réunir des effets de masques disjoints puis
// écrire chacun des autres à part donnait deux lignes de même texte, dont ad_line_add ne gardait
// qu'une.
DEFINE_PATCH_MACRO ad_spell_slots_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%slots_opcode%~)
	PATCH_IF slots_priest BEGIN
		LPM ad_spell_slots_priest_type
	END
	FOR (slots_id = 0; slots_id < fx_count; ++slots_id) BEGIN
		SET $slots_done(~%slots_id%~) = $fx_consumed(~%slots_id%~)
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		PHP_EACH ~fx_ids_%slots_opcode%~ AS _ => slots_id BEGIN
			PATCH_IF NOT $slots_done(~%slots_id%~) AND $fx_parameter2(~%slots_id%~) == 0 BEGIN
				SET $slots_done(~%slots_id%~) = 1
				SET slots_amount = $fx_parameter1(~%slots_id%~)
				SET slots_levels = 0
				LPM ad_spell_slots_line
			END
		END
	END
	PHP_EACH ~fx_ids_%slots_opcode%~ AS _ => slots_id BEGIN
		PATCH_IF NOT $slots_done(~%slots_id%~) BEGIN
			SET $slots_done(~%slots_id%~) = 1
			PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
				LPM ad_spell_slots_total_lines
			END
			ELSE BEGIN
				SET slots_amount = $fx_parameter1(~%slots_id%~)
				SET slots_levels = $fx_parameter2(~%slots_id%~)
				LPM ad_spell_slots_line
			END
		END
	END
END

// Lignes des ajouts de slots_id et des effets restants de même portée et de même ligne : total de
// chaque niveau (slots_total), puis une ligne par total non nul, sur les niveaux qui l'ont. Un niveau
// dont les ajouts et retraits s'annulent n'est pas écrit.
DEFINE_PATCH_MACRO ad_spell_slots_total_lines BEGIN
	SET key_id = slots_id
	LPM ad_fx_line_key
	SPRINT slots_key ~%fx_line_key%~
	SPRINT slots_scope $fx_scope(~%slots_id%~)
	FOR (slots_total_level = 1; slots_total_level <= slots_max_level; ++slots_total_level) BEGIN
		SET $slots_total(~%slots_total_level%~) = 0
	END
	PHP_EACH ~fx_ids_%slots_opcode%~ AS _ => slots_other BEGIN
		PATCH_IF slots_other == slots_id OR NOT $slots_done(~%slots_other%~) BEGIN
			SET key_id = slots_other
			LPM ad_fx_line_key
			SPRINT slots_other_scope $fx_scope(~%slots_other%~)
			PATCH_IF (~%slots_other_scope%~ STRING_EQUAL ~%slots_scope%~) AND (~%fx_line_key%~ STRING_EQUAL ~%slots_key%~) BEGIN
				SET $slots_done(~%slots_other%~) = 1
				SET slots_copies = VARIABLE_IS_SET $fx_identical_count(~%slots_other%~) ? $fx_identical_count(~%slots_other%~) : 1
				SET slots_other_amount = $fx_parameter1(~%slots_other%~) * slots_copies
				SET slots_other_levels = $fx_parameter2(~%slots_other%~)
				FOR (slots_total_level = 1; slots_total_level <= slots_max_level; ++slots_total_level) BEGIN
					PATCH_IF (slots_other_levels BAND (1 << (slots_total_level - 1))) != 0 BEGIN
						SET $slots_total(~%slots_total_level%~) = $slots_total(~%slots_total_level%~) + slots_other_amount
					END
				END
			END
		END
	END
	FOR (slots_total_level = 1; slots_total_level <= slots_max_level; ++slots_total_level) BEGIN
		SET slots_amount = $slots_total(~%slots_total_level%~)
		PATCH_IF slots_amount != 0 BEGIN
			SET slots_levels = 0
			FOR (slots_match_level = slots_total_level; slots_match_level <= slots_max_level; ++slots_match_level) BEGIN
				PATCH_IF $slots_total(~%slots_match_level%~) == slots_amount BEGIN
					SET slots_levels = slots_levels BOR (1 << (slots_match_level - 1))
					SET $slots_total(~%slots_match_level%~) = 0
				END
			END
			LPM ad_spell_slots_line
		END
	END
END

// Ligne de slots_amount emplacements des niveaux slots_levels (0 : doublement des niveaux 1 à
// slots_amount).
DEFINE_PATCH_MACRO ad_spell_slots_line BEGIN
	CLEAR_ARRAY slots_level_names
	FOR (slots_level = 1; slots_level <= slots_max_level; ++slots_level) BEGIN
		PATCH_IF (slots_levels == 0 AND slots_level <= slots_amount) OR (slots_levels BAND (1 << (slots_level - 1))) != 0 BEGIN
			SET tra_id = 8010000 + slots_level SPRINT tra_out ~slots_level_name~ LPM ad_tra_to
			SPRINT $slots_level_names(~%slots_level%~) ~%slots_level_name%~
		END
	END
	LPF ad_join STR_VAR array_name = ~slots_level_names~ RET levelStr = text END
	SET amount = slots_amount
	PATCH_IF slots_priest BEGIN
		SET slots_singular = slots_levels != 0 AND (amount == 1 OR amount == 0 - 1)
		SET tra_id = 8020000 + slots_priest_type + (slots_singular ? 10 : 0) SPRINT tra_out ~spellType~ LPM ad_tra_to
	END
	SET slots_phrase = slots_levels == 0 ? 140 : (amount == 1 ? 100 : (amount > 1 ? 110 : (amount == 0 - 1 ? 120 : 130)))
	PATCH_IF slots_phrase == 130 BEGIN
		SET amount = 0 - amount
	END
	SET line_phrase = 20000000 + slots_opcode * 10000 + slots_phrase
	SET line_fx = slots_id
	LPM ad_effect_line
END
