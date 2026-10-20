// Capacités de charge d'un objet (ancien add_charged_abilities) : en-têtes à charges (charges > 0)
// ou utilisés depuis l'objet (emplacement 3), dans l'ordre du fichier ; ceux d'une arme sont aussi
// ses en-têtes de combat (new-lib/item_combat.tpp). Leurs lignes sont celles des effets de l'en-tête (section ability<h> du magasin de lignes,
// new-lib/application.tpp). Une potion les liste sans titre, suivies de leur durée commune ; les
// autres objets ont une section « Capacité(s) de charge », avec un titre par capacité.
//
// Tableaux écrits (en-tête à charges charged_id) : charged_header, charged_charges,
// charged_depletion, charged_tooltip ; charged_global_duration(h) (pour chaque en-tête h : durée
// commune des effets d'une potion, 0 sans durée commune), charged_other(h) (1 pour un en-tête sans
// charges hors de l'objet) ; variables écrites : charged_count, charged_global_timing (timing de la
// durée commune du premier en-tête).

DEFINE_PATCH_MACRO ad_item_charged_load BEGIN
	SET charged_count = 0
	SPRINT charged_resref ~%SOURCE_RES%~
	TO_LOWER charged_resref
	READ_LONG  ITM_extended_headers_offset charged_headers_offset
	READ_SHORT ITM_extended_headers_count  charged_header_count
	FOR (charged_h = 0; charged_h < charged_header_count; ++charged_h) BEGIN
		SET $charged_global_duration(~%charged_h%~) = 0
		SET $charged_other(~%charged_h%~) = 0
		SET charged_offset = charged_headers_offset + charged_h * 0x38
		READ_BYTE  (charged_offset + ITM_HEAD_location)           charged_location
		READ_SHORT (charged_offset + ITM_HEAD_charges)            charged_charges
		READ_SHORT (charged_offset + ITM_HEAD_depletion)          charged_depletion
		PATCH_IF charged_charges > 0 OR charged_location == 3 BEGIN
			SET charged_id = charged_count
			SET $charged_header(~%charged_id%~) = charged_h
			SET $charged_charges(~%charged_id%~) = charged_charges
			SET $charged_depletion(~%charged_id%~) = charged_depletion
			SPRINT charged_tooltip ~~
			PATCH_IF VARIABLE_IS_SET $AD_TOOLTIPS(~%charged_resref% %charged_h%~) BEGIN
				SPRINT charged_strref $AD_TOOLTIPS(~%charged_resref% %charged_h%~)
				PATCH_IF IS_AN_INT charged_strref BEGIN
					PATCH_IF charged_strref > 0 BEGIN
						GET_STRREF charged_strref charged_tooltip
					END
				END
			END
			SPRINT $charged_tooltip(~%charged_id%~) ~%charged_tooltip%~
			SET charged_count += 1
		END
		ELSE BEGIN
			SET $charged_other(~%charged_h%~) = 1
		END
	END
END

// Raison de non-couverture (render_missing), vide si ce rendu décrit les en-têtes de l'objet. Hors
// des armes et munitions, un en-tête sans charges hors de l'objet est une capacité de combat pour
// l'ancien moteur : refusé s'il a un effet décrit (un effet ignoré n'a pas de ligne).
DEFINE_PATCH_MACRO ad_item_charged_support BEGIN
	LPM ad_item_charged_load
	FOR (charged_fx = 0; charged_fx < fx_count AND NOT item_has_combat; ++charged_fx) BEGIN
		SET render_opcode = $fx_opcode(~%charged_fx%~)
		SET charged_h = $fx_header(~%charged_fx%~)
		LPM ad_opcode_is_described
		PATCH_IF opcode_described AND charged_h >= 0 BEGIN
			PATCH_IF $charged_other(~%charged_h%~) BEGIN
				SPRINT render_missing ~not_implemented:headers~
			END
		END
	END
	PATCH_IF item_type == ITM_TYPE_potion BEGIN
		LPM ad_item_potion_durations
		// Ligne « Utilisation » de l'ancien moteur (uses) : potion à un seul en-tête à charges, sauf
		// usage unique ; pas encore reprise.
		SET charged_with_charges = 0
		FOR (charged_id = 0; charged_id < charged_count; ++charged_id) BEGIN
			PATCH_IF $charged_charges(~%charged_id%~) > 0 BEGIN
				SET charged_with_charges += 1
				SET charged_uses_id = charged_id
			END
		END
		PATCH_IF charged_with_charges == 1 BEGIN
			PATCH_IF $charged_charges(~%charged_uses_id%~) != 1 OR $charged_depletion(~%charged_uses_id%~) != 1 BEGIN
				SPRINT render_missing ~not_implemented:charged:uses~
			END
		END
	END
END

// Durée commune des effets de chaque en-tête d'une potion (ancien load_charged_abilities) : les
// effets d'une durée limitée (timing 0 ou 10) ont tous la même durée brute, comparée sans tenir
// compte de l'unité ; elle remplace alors toutes les durées de l'en-tête. Les effets des opcodes
// ignorés ou dont la durée n'est jamais comptée (colonne DURATION à IGNORED) n'y participent pas.
DEFINE_PATCH_MACRO ad_item_potion_durations BEGIN
	SET charged_global_timing = 0 - 1
	FOR (charged_id = 0; charged_id < charged_count; ++charged_id) BEGIN
		SET charged_h = $charged_header(~%charged_id%~)
		SET charged_global = 0 - 1
		SET charged_global_valid = 1
		SET charged_timing = 0 - 1
		FOR (charged_fx = 0; charged_fx < fx_count; ++charged_fx) BEGIN
			SET render_opcode = $fx_opcode(~%charged_fx%~)
			SPRINT charged_scope $fx_scope(~%charged_fx%~)
			LPM ad_opcode_is_described
			PATCH_IF opcode_described AND (~%charged_scope%~ STRING_EQUAL ~ability%charged_h%~) BEGIN
				SPRINT charged_duration_kind $AD_OPCODE_DURATION(~%render_opcode%~)
				SET charged_fx_timing = $fx_timing(~%charged_fx%~)
				PATCH_IF NOT (~%charged_duration_kind%~ STRING_EQUAL ~IGNORED~)
						AND (charged_fx_timing == TIMING_duration OR charged_fx_timing == TIMING_duration_ticks) BEGIN
					PATCH_IF charged_global < 0 BEGIN
						SET charged_global = $fx_duration(~%charged_fx%~)
						SET charged_timing = charged_fx_timing
					END
					PATCH_IF charged_global != $fx_duration(~%charged_fx%~) BEGIN
						SET charged_global_valid = 0
					END
				END
			END
		END
		PATCH_IF charged_global_valid AND charged_global > 0 BEGIN
			SET $charged_global_duration(~%charged_h%~) = charged_global
			// Moins de 15 ticks : l'ancien moteur écrit une ligne « Durée » vide.
			PATCH_IF charged_timing == TIMING_duration_ticks AND charged_global < 15 BEGIN
				SPRINT render_missing ~not_implemented:charged:ticks~
			END
		END
		PATCH_IF charged_id == 0 BEGIN
			SET charged_global_timing = charged_timing
		END
	END
END

// « usage unique », « 3 fois par jour »… (ancien get_charged_string).
DEFINE_PATCH_MACRO ad_item_charged_uses BEGIN
	SET charges = $charged_charges(~%charged_id%~)
	SET charged_depletion = $charged_depletion(~%charged_id%~)
	PATCH_IF charges == 0 BEGIN
		SPRINT charged_uses @6020000 // ~usage illimité~
	END
	ELSE PATCH_IF charged_depletion == 1 AND charges == 1 BEGIN
		SPRINT charged_uses @6020001 // ~usage unique~
	END
	ELSE PATCH_IF charged_depletion == 1 BEGIN
		SPRINT charged_uses @6020002 // ~%charges% charges, l'objet est détruit quand toutes les charges sont utilisées~
	END
	ELSE BEGIN
		SPRINT charged_uses @6020003 // ~%charges% fois par jour~
	END
END

// Section des capacités de charge, après les capacités d'équipement. Les lignes de l'unique en-tête
// à charges d'une munition vont dans « Capacités de combat » : sans effet d'en-tête pris en charge
// (new-lib/item_combat.tpp), elle n'en a aucune.
DEFINE_PATCH_MACRO ad_item_charged_section BEGIN
	SPRINT charged_text ~~
	PATCH_IF combat_is_ammo AND charged_count == 1 AND item_has_combat BEGIN
		SET charged_count = 0
	END
	SET charged_multiple = charged_count > 1
	FOR (charged_id = 0; charged_id < charged_count; ++charged_id) BEGIN
		SET charged_h = $charged_header(~%charged_id%~)
		PATCH_IF item_type == ITM_TYPE_potion BEGIN
			LPF ad_lines_section_text STR_VAR section = ~ability%charged_h%~ RET charged_lines = text END
			SPRINT charged_text ~%charged_text%%charged_lines%~
		END
		ELSE BEGIN
			LPM ad_item_charged_ability_text
		END
	END
	PATCH_IF item_type == ITM_TYPE_potion BEGIN
		SPRINT description ~%description%%charged_text%~
		PATCH_IF charged_count == 1 AND $charged_global_duration(~%charged_h%~) > 0 BEGIN
			SET charged_seconds = $charged_global_duration(~%charged_h%~)
			PATCH_IF charged_global_timing == TIMING_duration_ticks BEGIN
				SET charged_seconds = charged_seconds / 15
			END
			LPF ad_duration_text INT_VAR seconds = charged_seconds RET value = text END
			SPRINT name @6200002 // ~Durée~
			SPRINT charged_line @1200000 // ~%name%%AD_COLON%%value%~
			SPRINT description ~%description%%CRLF%%CRLF%%charged_line%~
		END
	END
	ELSE PATCH_IF NOT (~%charged_text%~ STRING_EQUAL ~~) BEGIN
		PATCH_IF charged_multiple BEGIN
			SPRINT charged_title @1300004 // ~Capacités de charge~
		END
		ELSE BEGIN
			SET charged_id = 0
			LPM ad_item_charged_uses
			SPRINT charged_title @1300005 // ~Capacité de charge~
			SPRINT charged_title ~%charged_title% (%charged_uses%)~
		END
		SPRINT description ~%description%%CRLF%%CRLF%%charged_title%%AD_COLON%%charged_text%~
	END
END

// Lignes d'une capacité d'un objet autre qu'une potion, ajoutées à charged_text. Son titre est son
// infobulle (« Capacité N » sans infobulle, si l'objet en a plusieurs et qu'elle a plusieurs lignes),
// suivi de ses utilisations si l'objet a plusieurs capacités, et ses lignes sont en retrait dessous.
// Une ligne unique sert de titre si la capacité n'a pas d'infobulle ou si la ligne commence par
// elle.
DEFINE_PATCH_MACRO ad_item_charged_ability_text BEGIN
	LPF ad_lines_section_text INT_VAR level = 0 STR_VAR section = ~ability%charged_h%~ RET charged_raw = text charged_line_count = count END
	SPRINT charged_title $charged_tooltip(~%charged_id%~)
	SET charged_title_repeated = 0
	PATCH_IF NOT (~%charged_title%~ STRING_EQUAL ~~) AND charged_line_count == 1 BEGIN
		SPRINT charged_lower_title ~%charged_title%~
		TO_LOWER charged_lower_title
		SPRINT charged_lower_line ~%charged_raw%~
		INNER_PATCH_SAVE charged_lower_line ~%charged_lower_line%~ BEGIN
			DELETE_BYTES 0 STRING_LENGTH ~%CRLF%~
		END
		TO_LOWER charged_lower_line
		SET charged_title_repeated = INDEX (~%charged_lower_title%~ ~%charged_lower_line%~) == 0
	END
	SET charged_line_is_title = charged_line_count == 1 AND (charged_title_repeated OR ~%charged_title%~ STRING_EQUAL ~~)
	PATCH_IF ~%charged_title%~ STRING_EQUAL ~~ AND charged_multiple AND charged_line_count > 1 BEGIN
		SET abilityNumber = charged_id + 1
		SPRINT charged_title @1300006 // ~Capacité %abilityNumber%~
	END
	LPM ad_item_charged_uses
	SET charged_level = 1
	PATCH_IF NOT charged_line_is_title AND NOT (~%charged_title%~ STRING_EQUAL ~~) BEGIN
		PATCH_IF charged_multiple BEGIN
			SPRINT charged_title ~%charged_title% (%charged_uses%)~
		END
		SPRINT charged_text ~%charged_text%%CRLF%- %charged_title%~
		SET charged_level = 2
	END
	LPF ad_lines_section_text INT_VAR level = charged_level STR_VAR section = ~ability%charged_h%~ RET charged_lines = text END
	PATCH_IF charged_line_is_title AND charged_multiple BEGIN
		SPRINT charged_lines ~%charged_lines% (%charged_uses%)~
	END
	SPRINT charged_text ~%charged_text%%charged_lines%~
END
