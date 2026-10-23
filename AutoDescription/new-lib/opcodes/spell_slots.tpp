// Code commun des emplacements de sorts (42 profanes, 62 divins), IESDP : parameter1 = nombre
// d'emplacements ajoutés (négatif : retirés), parameter2 = niveaux touchés, un bit par niveau
// (BIT0 = niveau 1) ; parameter2 = 0 double les emplacements des niveaux 1 à parameter1. Le fichier
// de chaque opcode fixe slots_opcode, slots_max_level (dernier niveau de sort de la classe) et
// slots_priest (1 : type de sort selon les clercs et druides qui peuvent utiliser l'objet).
// Phrases du bloc de l'opcode : 0100 un emplacement, 0110 plusieurs, 0120 un retiré, 0140 doublement.
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp).

// ---------------------------------------------------------------------------------------------
// Prise en charge (l'ancien moteur n'a pas de macro opcode_42_is_valid ni opcode_62_is_valid)

DEFINE_PATCH_MACRO ad_spell_slots_support BEGIN
	SET slots_all_levels = (1 << slots_max_level) - 1
	PHP_EACH ~fx_ids_%slots_opcode%~ AS _ => slots_id BEGIN
		SET slots_amount = $fx_parameter1(~%slots_id%~)
		SET slots_doubling = $fx_parameter2(~%slots_id%~) == 0
		SET $slots_seen_levels(~%slots_amount% %slots_doubling%~) = 0
	END
	FOR (slots_id = 0; slots_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++slots_id) BEGIN
		PATCH_IF $fx_opcode(~%slots_id%~) == slots_opcode BEGIN
			SET slots_amount = $fx_parameter1(~%slots_id%~)
			SET slots_levels = $fx_parameter2(~%slots_id%~)
			// Les doublements et les ajouts d'un même nombre sont réunis séparément.
			SET slots_doubling = slots_levels == 0
			SET slots_levels_used = slots_doubling ? slots_all_levels : slots_levels
			// Valeurs que l'ancien moteur décrit mal ou pas (aucun texte, niveaux non écrits, BIT9 =
			// doublement d'un seul niveau, écrit « de 3 niveau »).
			PATCH_IF slots_amount == 0 OR slots_amount > 32767 OR slots_amount < 0 - 32768
					OR (slots_levels == 0 AND slots_amount < 0)
					OR (slots_levels BAND (BNOT slots_all_levels)) != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = slots_id STR_VAR reason = ~file_error:opcode%slots_opcode%:invalid~ message = ~invalid amount %slots_amount% or spell levels~ RET render_missing = refusal END
			END
			// L'ancien moteur écrit le nombre négatif : « Suppression de -2 sorts ».
			ELSE PATCH_IF slots_amount < 0 - 1 BEGIN
				LPF ad_refusal INT_VAR fx_id = slots_id STR_VAR reason = ~not_implemented:opcode%slots_opcode%:removal~ message = ~several spell slots removed~ RET render_missing = refusal END
			END
			// En réunissant les effets d'un même nombre, l'ancien moteur fusionne les niveaux
			// communs (ou deux doublements identiques) au lieu de cumuler leurs emplacements.
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND ($slots_seen_levels(~%slots_amount% %slots_doubling%~) BAND slots_levels_used) != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = slots_id STR_VAR reason = ~not_implemented:opcode%slots_opcode%:overlapping_levels~ message = ~overlapping spell levels~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET $slots_seen_levels(~%slots_amount% %slots_doubling%~) = $slots_seen_levels(~%slots_amount% %slots_doubling%~) BOR slots_levels_used
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

// Avec AD_ENABLE_SHRINKAGE, les effets d'un même nombre d'emplacements sont réunis en une ligne
// (niveaux réunis) ; l'ancien moteur range les effets réunis après les doublements, d'où leurs
// lignes ajoutées après celles-ci.
DEFINE_PATCH_MACRO ad_spell_slots_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%slots_opcode%~)
	PATCH_IF slots_priest BEGIN
		LPM ad_spell_slots_priest_type
	END
	FOR (slots_id = 0; slots_id < fx_count; ++slots_id) BEGIN
		SET $slots_done(~%slots_id%~) = 0
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		PHP_EACH ~fx_ids_%slots_opcode%~ AS _ => slots_id BEGIN
			PATCH_IF $fx_parameter2(~%slots_id%~) == 0 BEGIN
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
			SET slots_amount = $fx_parameter1(~%slots_id%~)
			SET slots_levels = $fx_parameter2(~%slots_id%~)
			PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
				PHP_EACH ~fx_ids_%slots_opcode%~ AS _ => slots_other BEGIN
					PATCH_IF slots_other >= slots_id + 1 AND NOT $slots_done(~%slots_other%~) AND $fx_parameter1(~%slots_other%~) == slots_amount BEGIN
						SET $slots_done(~%slots_other%~) = 1
						SET slots_levels = slots_levels BOR $fx_parameter2(~%slots_other%~)
					END
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
			LPF ad_tra INT_VAR tra_id = 8010000 + slots_level RET slots_level_name = text END
			SPRINT $slots_level_names(~%slots_level%~) ~%slots_level_name%~
		END
	END
	LPF ad_join STR_VAR array_name = ~slots_level_names~ RET levelStr = text END
	SET amount = slots_amount
	PATCH_IF slots_priest BEGIN
		SET slots_singular = slots_levels != 0 AND (amount == 1 OR amount == 0 - 1)
		LPF ad_tra INT_VAR tra_id = 8020000 + slots_priest_type + (slots_singular ? 10 : 0) RET spellType = text END
	END
	SET slots_phrase = slots_levels == 0 ? 140 : (amount == 1 ? 100 : (amount > 1 ? 110 : 120))
	SET line_phrase = 20000000 + slots_opcode * 10000 + slots_phrase
	SET line_fx = slots_id
	LPM ad_effect_line
END
