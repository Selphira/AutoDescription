// Armes et munitions : en-têtes de combat, section « Capacités de combat », attributs d'arme et
// compétence (anciens add_combat_abilities, add_weapon_attributes_to_description, proficiency).
// Pris en charge : effets des en-têtes de combat sans charges, dans leur section « Capacités de
// combat » (section ability<h> du magasin de lignes, comme les autres effets d'en-tête) ; un en-tête à
// charges a aussi sa capacité de charge (new-lib/item_charged.tpp), sans effet pour l'instant.
//
// Tableaux écrits (en-tête de combat combat_id, dans l'ordre du fichier) : combat_header (index
// de l'en-tête dans l'objet), combat_attack_type, combat_location, combat_charges,
// combat_depletion, combat_flags, combat_tooltip, combat_section_type (infobulle, ou « au corps à
// corps » / « à distance » pour une arme en main), combat_tac0, combat_damage (vide : aucun dégât),
// combat_damage_type, combat_speed, combat_launcher ; variables écrites : combat_count,
// combat_other_count (en-têtes d'un autre type), combat_charged_effects (effets des en-têtes à
// charges ou utilisés depuis l'objet).

DEFINE_PATCH_MACRO ad_item_combat_load BEGIN
	SET combat_count = 0
	SET combat_other_count = 0
	SET combat_charged_effects = 0
	SPRINT combat_resref ~%SOURCE_RES%~
	TO_LOWER combat_resref
	READ_LONG  ITM_extended_headers_offset combat_headers_offset
	READ_SHORT ITM_extended_headers_count  combat_header_count
	FOR (combat_h = 0; combat_h < combat_header_count; ++combat_h) BEGIN
		SET combat_offset = combat_headers_offset + combat_h * 0x38
		READ_BYTE  (combat_offset + ITM_HEAD_attack_type)        combat_attack_type
		READ_SHORT (combat_offset + ITM_HEAD_feature_block_count) combat_effects
		PATCH_IF combat_attack_type == ITM_ATTACK_TYPE_melee OR combat_attack_type == ITM_ATTACK_TYPE_projectile
				OR combat_attack_type == ITM_ATTACK_TYPE_launcher BEGIN
			SET combat_id = combat_count
			SET $combat_header(~%combat_id%~) = combat_h
			SET $combat_attack_type(~%combat_id%~) = combat_attack_type
			READ_BYTE   (combat_offset + ITM_HEAD_location)        $combat_location(~%combat_id%~)
			READ_SHORT  (combat_offset + ITM_HEAD_charges)         $combat_charges(~%combat_id%~)
			READ_SHORT  (combat_offset + ITM_HEAD_depletion)       $combat_depletion(~%combat_id%~)
			READ_LONG   (combat_offset + ITM_HEAD_flags)           $combat_flags(~%combat_id%~)
			READ_SSHORT (combat_offset + ITM_HEAD_thac0_bonus)     $combat_tac0(~%combat_id%~)
			READ_SHORT  (combat_offset + ITM_HEAD_damage_type)     $combat_damage_type(~%combat_id%~)
			READ_BYTE   (combat_offset + ITM_HEAD_speed)           $combat_speed(~%combat_id%~)
			READ_BYTE   (combat_offset + ITM_HEAD_projectile_type) $combat_launcher(~%combat_id%~)
			PATCH_IF $combat_charges(~%combat_id%~) > 0 OR $combat_location(~%combat_id%~) == 3 BEGIN
				SET combat_charged_effects += combat_effects
			END
			LPM ad_item_combat_damage
			LPM ad_item_combat_tooltip
			SET combat_count += 1
		END
		ELSE BEGIN
			SET combat_other_count += 1
		END
	END
END

// Dégâts de l'en-tête (« 1d8 +2 ») ; un dé à une face compte comme un bonus. Sans dé ni bonus,
// l'arme n'inflige aucun dégât (même avec ses modificateurs) : combat_damage reste vide et
// combat_damage_invalid signale des faces sans dés.
DEFINE_PATCH_MACRO ad_item_combat_damage BEGIN
	READ_BYTE   (combat_offset + ITM_HEAD_dice_thrown)  combat_dice_thrown
	READ_BYTE   (combat_offset + ITM_HEAD_dice_sides)   combat_dice_sides
	READ_SSHORT (combat_offset + ITM_HEAD_damage_bonus) combat_damage_bonus
	SET $combat_damage_invalid(~%combat_id%~) = combat_dice_thrown == 0 AND combat_dice_sides != 0 AND combat_damage_bonus == 0
	SPRINT combat_damage ~~
	PATCH_IF combat_dice_thrown > 0 BEGIN
		PATCH_IF combat_dice_sides <= 1 BEGIN
			SET combat_damage_bonus += combat_dice_thrown
		END
		ELSE BEGIN
			SET diceCount = combat_dice_thrown
			SET diceSides = combat_dice_sides
			SPRINT combat_damage @1200005 // ~%diceCount%d%diceSides%~
		END
	END
	PATCH_IF combat_damage_bonus != 0 BEGIN
		LPF ad_signed_value INT_VAR value = combat_damage_bonus RET combat_bonus_text = text END
		PATCH_IF ~%combat_damage%~ STRING_EQUAL ~~ BEGIN
			SPRINT combat_damage ~%combat_bonus_text%~
		END
		ELSE BEGIN
			SPRINT combat_damage ~%combat_damage% %combat_bonus_text%~
		END
	END
	SPRINT $combat_damage(~%combat_id%~) ~%combat_damage%~
END

DEFINE_PATCH_MACRO ad_item_combat_tooltip BEGIN
	SPRINT combat_tooltip ~~
	PATCH_IF VARIABLE_IS_SET $AD_TOOLTIPS(~%combat_resref% %combat_h%~) BEGIN
		SPRINT combat_strref $AD_TOOLTIPS(~%combat_resref% %combat_h%~)
		PATCH_IF IS_AN_INT combat_strref BEGIN
			PATCH_IF combat_strref > 0 BEGIN
				GET_STRREF combat_strref combat_tooltip
			END
		END
	END
	SPRINT $combat_tooltip(~%combat_id%~) ~%combat_tooltip%~
	SPRINT combat_section_type ~%combat_tooltip%~
	PATCH_IF ~%combat_section_type%~ STRING_EQUAL ~~ AND $combat_location(~%combat_id%~) == 1 BEGIN
		PATCH_IF combat_attack_type == ITM_ATTACK_TYPE_melee BEGIN
			SPRINT combat_section_type @6100020 // ~au corps à corps~
		END
		ELSE BEGIN
			SPRINT combat_section_type @6100021 // ~à distance~
		END
	END
	SPRINT $combat_section_type(~%combat_id%~) ~%combat_section_type%~
END

// Raison de non-couverture d'une arme ou munition (render_missing), vide si ce rendu la décrit.
// Les cas refusés sont ceux que l'ancien moteur décrit avec des règles pas encore reprises
// (effets et titres des capacités) ou mal (bonus de Force, BUG-018 ; munition à plusieurs
// en-têtes, dont il lit des valeurs d'un autre en-tête, BUG-019).
DEFINE_PATCH_MACRO ad_item_combat_support BEGIN
	SET combat_is_ammo = item_type == ITM_TYPE_arrows OR item_type == ITM_TYPE_bullets OR item_type == ITM_TYPE_bolts
	LPM ad_item_combat_load
	PATCH_IF combat_count == 0 OR combat_other_count > 0 OR combat_charged_effects > 0 BEGIN
		SPRINT render_missing ~not_implemented:headers~
	END
	ELSE PATCH_IF combat_is_ammo AND combat_count > 1 BEGIN
		SPRINT render_missing ~not_implemented:combat:ammo_headers~
	END
	FOR (combat_id = 0; combat_id < combat_count AND ~%render_missing%~ STRING_EQUAL ~~; ++combat_id) BEGIN
		SPRINT combat_section_type $combat_section_type(~%combat_id%~)
		PATCH_IF $combat_damage_invalid(~%combat_id%~) BEGIN
			SPRINT render_missing ~not_implemented:combat:damage~
		END
		ELSE PATCH_IF $combat_damage_type(~%combat_id%~) > 9 BEGIN
			SPRINT render_missing ~not_implemented:combat:damage_type~
		END
		ELSE PATCH_IF combat_is_ammo AND ($combat_launcher(~%combat_id%~) < 1 OR $combat_launcher(~%combat_id%~) > 3) BEGIN
			SPRINT render_missing ~not_implemented:combat:launcher~
		END
		ELSE PATCH_IF combat_count > 1 AND ~%combat_section_type%~ STRING_EQUAL ~~ BEGIN
			SPRINT render_missing ~not_implemented:combat:section_type~
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT combat_is_ammo BEGIN
		READ_BYTE ITM_weapon_proficiency combat_proficiency
		PATCH_IF NOT VARIABLE_IS_SET $AD_PROFICIENCY_NAMES(~%combat_proficiency%~) BEGIN
			SPRINT render_missing ~not_implemented:combat:proficiency~
		END
		ELSE PATCH_IF combat_count == 1 BEGIN
			LPM ad_item_strength_bonus
			PATCH_IF strength_bonus_invalid BEGIN
				SPRINT render_missing ~not_implemented:combat:strength_bonus~
			END
		END
	END
END

// Ligne de l'unique en-tête d'une arme sur les bonus de Force (strength_bonus_tra, 0 sans ligne).
// Drapeaux de l'en-tête (IESDP) : bit 0, bonus de Force au toucher et aux dégâts ; sur EE, bit 2
// aux dégâts seuls, bit 3 au toucher seul. Une arme de jet le signale quand le bonus s'applique,
// les autres armes quand il ne s'applique pas. strength_bonus_invalid : combinaison que l'ancien
// moteur décrit mal (BUG-018).
DEFINE_PATCH_MACRO ad_item_strength_bonus BEGIN
	SET strength_flags = $combat_flags(~0~)
	SET strength_both = (strength_flags BAND BIT0) != 0
	SET strength_damage = (strength_flags BAND BIT2) != 0
	SET strength_tac0 = (strength_flags BAND BIT3) != 0
	SET strength_bonus_tra = 0
	SET strength_bonus_invalid = 0
	PATCH_IF item_type == ITM_TYPE_bow OR item_type == ITM_TYPE_sling OR item_type == ITM_TYPE_crossbow BEGIN
		PATCH_IF strength_both OR (IS_EE AND strength_damage AND strength_tac0) BEGIN
			SET strength_bonus_tra = 6010010 // ~Les bonus au toucher et aux dégâts liés à la force s'appliquent à cette arme~
		END
		ELSE PATCH_IF strength_tac0 BEGIN
			SET strength_bonus_tra = 6010012 // ~Le bonus au toucher lié à la force s'applique à cette arme~
		END
		ELSE PATCH_IF strength_damage BEGIN
			SET strength_bonus_invalid = 1
		END
	END
	ELSE PATCH_IF NOT strength_both BEGIN
		PATCH_IF strength_tac0 BEGIN
			SET strength_bonus_invalid = 1
		END
		ELSE PATCH_IF strength_damage BEGIN
			SET strength_bonus_tra = 6010014 // ~Le bonus au toucher lié à la force ne s'applique pas à cette arme~
		END
		ELSE BEGIN
			SET strength_bonus_tra = 6010013 // ~Les bonus au toucher et aux dégâts liés à la force ne s'appliquent pas à cette arme~
		END
	END
END

// Lignes ajoutées à la section « Capacités de combat » de chaque en-tête (section ability<h>, après
// celles de ses effets ; combat_line_count(combat_id) les compte toutes) : projectile sans munition
// ou qui revient, et bonus de Force d'une arme à un seul en-tête. combat_same_abilities : les
// en-têtes qui ont des lignes d'effet ont les mêmes (ancien has_same_combat_abilities, avant ces
// ajouts) ; combat_special : la dernière ligne de projectile écrite.
DEFINE_PATCH_MACRO ad_item_combat_lines BEGIN
	LPM ad_item_combat_same_abilities
	SPRINT combat_special ~~
	FOR (combat_id = 0; combat_id < combat_count; ++combat_id) BEGIN
		SET combat_h = $combat_header(~%combat_id%~)
		SET combat_charges = $combat_charges(~%combat_id%~)
		PATCH_IF $combat_attack_type(~%combat_id%~) == ITM_ATTACK_TYPE_projectile
				AND (combat_charges == 0 OR ($combat_depletion(~%combat_id%~) >= 3 AND combat_charges == 1 AND combat_is_ammo)) BEGIN
			SPRINT line_section ~ability%combat_h%~
			SET line_sort = 0
			PATCH_IF combat_is_ammo BEGIN
				SPRINT line_text @6010002 // ~Munition à usage illimité~
			END
			ELSE PATCH_IF item_type == ITM_TYPE_bow OR item_type == ITM_TYPE_sling OR item_type == ITM_TYPE_crossbow BEGIN
				SPRINT line_text @6010001 // ~Ne nécessite pas de munitions~
			END
			ELSE BEGIN
				SPRINT line_text @6010000 // ~Revient dans la main de son porteur après avoir été lancée~
			END
			SPRINT combat_special ~%line_text%~
			LPM ad_line_add
		END
		LPF ad_lines_section_text STR_VAR section = ~ability%combat_h%~ RET combat_line_text = text combat_lines_now = count END
		SET $combat_line_count(~%combat_id%~) = combat_lines_now
	END
	PATCH_IF NOT combat_is_ammo AND combat_count == 1 BEGIN
		LPM ad_item_strength_bonus
		PATCH_IF strength_bonus_tra > 0 BEGIN
			SET combat_h = $combat_header(~0~)
			SPRINT line_section ~ability%combat_h%~
			SET line_sort = 0
			LPF ad_tra INT_VAR tra_id = strength_bonus_tra RET line_text = text END
			LPM ad_line_add
		END
	END
END

// combat_same_abilities (ancien has_same_combat_abilities) : chaque en-tête qui a des lignes d'effet en
// a autant que le premier, et chaque ligne du premier s'y trouve ; si le premier n'en a aucune, aucun
// autre n'en a. Les en-têtes sans ligne ne comptent pas.
DEFINE_PATCH_MACRO ad_item_combat_same_abilities BEGIN
	SET combat_same_abilities = 1
	FOR (combat_id = 0; combat_id < combat_count; ++combat_id) BEGIN
		SET combat_h = $combat_header(~%combat_id%~)
		LPF ad_lines_section_text STR_VAR section = ~ability%combat_h%~ RET combat_line_text = text combat_effect_lines = count END
		SET $combat_effect_lines(~%combat_id%~) = combat_effect_lines
	END
	SET combat_first_h = $combat_header(~0~)
	FOR (combat_id = 1; combat_id < combat_count; ++combat_id) BEGIN
		SET combat_h = $combat_header(~%combat_id%~)
		SET combat_other_lines = $combat_effect_lines(~%combat_id%~)
		PATCH_IF combat_other_lines > 0 BEGIN
			PATCH_IF $combat_effect_lines(~0~) != combat_other_lines BEGIN
				SET combat_same_abilities = 0
			END
			FOR (combat_line = 0; combat_line < line_count; ++combat_line) BEGIN
				SPRINT combat_line_section $line_section(~%combat_line%~)
				PATCH_IF ~%combat_line_section%~ STRING_EQUAL ~ability%combat_first_h%~ BEGIN
					SPRINT combat_line_text $line_text(~%combat_line%~)
					SET combat_found = 0
					FOR (combat_other = 0; combat_other < line_count; ++combat_other) BEGIN
						SPRINT combat_other_section $line_section(~%combat_other%~)
						SPRINT combat_other_text $line_text(~%combat_other%~)
						PATCH_IF (~%combat_other_section%~ STRING_EQUAL ~ability%combat_h%~) AND (~%combat_other_text%~ STRING_EQUAL ~%combat_line_text%~) BEGIN
							SET combat_found = 1
						END
					END
					PATCH_IF NOT combat_found BEGIN
						SET combat_same_abilities = 0
					END
				END
			END
		END
	END
END

// Section « Capacités de combat » : une seule si les en-têtes ont mêmes capacités, TAC0, dégâts et
// facteur de vitesse (lignes de l'en-tête qui en a le plus, plus la ligne de projectile), sinon une
// par en-tête, titrée de son type.
DEFINE_PATCH_MACRO ad_item_combat_section BEGIN
	SET combat_same = combat_same_abilities
	FOR (combat_id = 1; combat_id < combat_count; ++combat_id) BEGIN
		SPRINT combat_damage_first $combat_damage(~0~)
		SPRINT combat_damage $combat_damage(~%combat_id%~)
		PATCH_IF $combat_tac0(~%combat_id%~) != $combat_tac0(~0~) OR $combat_speed(~%combat_id%~) != $combat_speed(~0~)
				OR NOT (~%combat_damage%~ STRING_EQUAL ~%combat_damage_first%~) BEGIN
			SET combat_same = 0
		END
	END
	SPRINT combat_title @1300003 // ~Capacités de combat~
	PATCH_IF combat_same BEGIN
		SET combat_selected = 0
		FOR (combat_id = 1; combat_id < combat_count; ++combat_id) BEGIN
			PATCH_IF $combat_line_count(~%combat_id%~) > $combat_line_count(~%combat_selected%~) BEGIN
				SET combat_selected = combat_id
			END
		END
		SET combat_h = $combat_header(~%combat_selected%~)
		PATCH_IF NOT (~%combat_special%~ STRING_EQUAL ~~) BEGIN
			SPRINT line_section ~ability%combat_h%~
			SET line_sort = 0
			SPRINT line_text ~%combat_special%~
			LPM ad_line_add
		END
		LPF ad_lines_section_text STR_VAR section = ~ability%combat_h%~ RET combat_lines = text END
		PATCH_IF NOT (~%combat_lines%~ STRING_EQUAL ~~) BEGIN
			SPRINT description ~%description%%CRLF%%CRLF%%combat_title%%AD_COLON%%combat_lines%~
		END
	END
	ELSE BEGIN
		FOR (combat_id = 0; combat_id < combat_count; ++combat_id) BEGIN
			SET combat_h = $combat_header(~%combat_id%~)
			LPF ad_lines_section_text STR_VAR section = ~ability%combat_h%~ RET combat_lines = text END
			PATCH_IF NOT (~%combat_lines%~ STRING_EQUAL ~~) BEGIN
				SPRINT combat_section_type $combat_section_type(~%combat_id%~)
				SPRINT combat_header_title ~%combat_title% (%combat_section_type%)~
				SPRINT description ~%description%%CRLF%%CRLF%%combat_header_title%%AD_COLON%%combat_lines%~
			END
		END
	END
END

// Valeurs distinctes de combat_<group_attr> dans l'ordre des en-têtes : group_counts(group_attr),
// <group_attr>_group_value(g), <group_attr>_group_size(g), <group_attr>_group_of(combat_id).
DEFINE_PATCH_MACRO ad_combat_groups BEGIN
	SET group_count = 0
	FOR (group_c = 0; group_c < combat_count; ++group_c) BEGIN
		SPRINT group_value $EVAL ~combat_%group_attr%~(~%group_c%~)
		SET group_found = 0 - 1
		FOR (group_g = 0; group_g < group_count AND group_found < 0; ++group_g) BEGIN
			SPRINT group_old_value $EVAL ~%group_attr%_group_value~(~%group_g%~)
			PATCH_IF ~%group_old_value%~ STRING_EQUAL ~%group_value%~ BEGIN
				SET group_found = group_g
			END
		END
		PATCH_IF group_found < 0 BEGIN
			SET group_found = group_count
			SPRINT $EVAL ~%group_attr%_group_value~(~%group_found%~) ~%group_value%~
			SET $EVAL ~%group_attr%_group_size~(~%group_found%~) = 0
			SET group_count += 1
		END
		SET $EVAL ~%group_attr%_group_of~(~%group_c%~) = group_found
		SET $EVAL ~%group_attr%_group_size~(~%group_found%~) += 1
	END
	SET $group_counts(~%group_attr%~) = group_count
END

// Précision « (a et b) » des types (combat_section_type) des en-têtes du groupe group_g de
// group_attr, sans doublon, en écartant les en-têtes dont combat_type_shown vaut 1 si
// group_skip_shown ; vide si group_attr n'a qu'une valeur.
DEFINE_PATCH_MACRO ad_combat_suffix BEGIN
	SPRINT group_suffix ~~
	PATCH_IF $group_counts(~%group_attr%~) > 1 BEGIN
		CLEAR_ARRAY group_types
		SET group_type_count = 0
		FOR (group_c = 0; group_c < combat_count; ++group_c) BEGIN
			PATCH_IF $EVAL ~%group_attr%_group_of~(~%group_c%~) == group_g AND NOT (group_skip_shown AND $combat_type_shown(~%group_c%~)) BEGIN
				SPRINT group_type $combat_section_type(~%group_c%~)
				SET group_duplicate = 0
				FOR (group_t = 0; group_t < group_type_count; ++group_t) BEGIN
					SPRINT group_old_type $group_types(~%group_t%~)
					PATCH_IF ~%group_old_type%~ STRING_EQUAL ~%group_type%~ BEGIN
						SET group_duplicate = 1
					END
				END
				PATCH_IF NOT group_duplicate BEGIN
					SPRINT $group_types(~%group_type_count%~) ~%group_type%~
					SET group_type_count += 1
				END
			END
		END
		LPF ad_join STR_VAR array_name = ~group_types~ RET group_suffix = text END
		SPRINT group_suffix ~ (%group_suffix%)~
	END
	SET group_skip_shown = 0
END

// Ligne « nom : valeur » des attributs d'arme, ajoutée à weapon_text.
DEFINE_PATCH_MACRO ad_weapon_attribute_line BEGIN
	LPF ad_tra INT_VAR tra_id = weapon_name_tra RET name = text END
	SPRINT name ~%name%%group_suffix%~
	SPRINT value ~%weapon_value%~
	SPRINT weapon_line @1200000 // ~%name%%AD_COLON%%value%~
	SPRINT weapon_text ~%weapon_text%%CRLF%%weapon_line%~
END

// Attributs d'arme, après une ligne vide : niveau d'enchantement, TAC0, dégâts et leurs types,
// facteur de vitesse (arme) ou arme de trait (munition), puis compétence et maniement (arme). Une
// valeur qui diffère selon l'en-tête est précisée du type des en-têtes qui l'ont.
DEFINE_PATCH_MACRO ad_item_weapon_attributes BEGIN
	SPRINT weapon_text ~~
	SET group_skip_shown = 0
	SPRINT group_suffix ~~
	// L'enchantement est celui de l'objet : souvent égal au TAC0, il ne le répète pas.
	READ_LONG ITM_enchantment weapon_enchantment
	PATCH_IF weapon_enchantment != 0 AND NOT (AD_SHOW_WEAPON_ENCHANTMENT_IF_DIFFERENT_THAC0 AND weapon_enchantment == $combat_tac0(~0~)) BEGIN
		LPF ad_signed_value INT_VAR value = weapon_enchantment RET weapon_value = text END
		SET weapon_name_tra = 6100000 // ~Niveau d'enchantement~
		LPM ad_weapon_attribute_line
	END

	SPRINT group_attr ~tac0~
	LPM ad_combat_groups
	FOR (group_g = 0; group_g < $group_counts(~tac0~); ++group_g) BEGIN
		SET weapon_tac0 = $tac0_group_value(~%group_g%~)
		PATCH_IF weapon_tac0 != 0 BEGIN
			LPM ad_combat_suffix
			LPF ad_signed_value INT_VAR value = weapon_tac0 RET weapon_value = text END
			SET weapon_name_tra = 6100001 // ~TAC0~
			LPM ad_weapon_attribute_line
		END
	END

	LPM ad_item_weapon_damage_lines

	PATCH_IF NOT combat_is_ammo BEGIN
		SPRINT group_attr ~speed~
		LPM ad_combat_groups
		FOR (group_g = 0; group_g < $group_counts(~speed~); ++group_g) BEGIN
			LPM ad_combat_suffix
			SPRINT weapon_value $speed_group_value(~%group_g%~)
			SET weapon_name_tra = 6100004 // ~Facteur de vitesse~
			LPM ad_weapon_attribute_line
		END
		READ_BYTE ITM_weapon_proficiency weapon_proficiency
		SPRINT group_suffix ~~
		SPRINT weapon_value $AD_PROFICIENCY_NAMES(~%weapon_proficiency%~)
		SET weapon_name_tra = 6100006 // ~Type de compétence~
		LPM ad_weapon_attribute_line
		READ_LONG ITM_flags weapon_flags
		PATCH_IF (weapon_flags BAND BIT1) == 0 BEGIN
			SPRINT weapon_value @6100010 // ~Arme à 1 main~
		END
		ELSE BEGIN
			SPRINT weapon_value @6100011 // ~Arme à 2 mains~
		END
		SET weapon_name_tra = 6100007 // ~Type~
		LPM ad_weapon_attribute_line
	END
	ELSE BEGIN
		SPRINT group_attr ~launcher~
		LPM ad_combat_groups
		FOR (group_g = 0; group_g < $group_counts(~launcher~); ++group_g) BEGIN
			LPM ad_combat_suffix
			SET weapon_launcher = $launcher_group_value(~%group_g%~)
			LPF ad_tra INT_VAR tra_id = 8050000 + weapon_launcher tra_block_start = 8050000 tra_block_size = 10000 RET weapon_value = text END
			SET weapon_name_tra = 6100005 // ~Arme de trait~
			LPM ad_weapon_attribute_line
		END
	END
	SPRINT description ~%description%%CRLF%%weapon_text%~
END

// Dégâts et types de dégâts. Avec AD_SHRINK_WEAPON_ATTRIBUTES, le type suit les dégâts entre
// parenthèses quand il est le même pour tous les en-têtes, ou quand ces dégâts et ce type sont
// ceux d'un seul en-tête ; les autres types ont leur ligne, si leurs en-têtes infligent des dégâts.
DEFINE_PATCH_MACRO ad_item_weapon_damage_lines BEGIN
	SET weapon_shrink = AD_ENABLE_SHRINKAGE AND AD_SHRINK_WEAPON_ATTRIBUTES
	SPRINT group_attr ~damage_type~
	LPM ad_combat_groups
	SPRINT group_attr ~damage~
	LPM ad_combat_groups
	FOR (combat_id = 0; combat_id < combat_count; ++combat_id) BEGIN
		SET $combat_type_shown(~%combat_id%~) = 0
	END
	FOR (group_g = 0; group_g < $group_counts(~damage~); ++group_g) BEGIN
		SPRINT weapon_damage $damage_group_value(~%group_g%~)
		PATCH_IF NOT (~%weapon_damage%~ STRING_EQUAL ~~) BEGIN
			SPRINT weapon_value ~%weapon_damage%~
			SET weapon_type_added = 0
			FOR (combat_id = 0; combat_id < combat_count AND weapon_shrink; ++combat_id) BEGIN
				SET weapon_type_group = $damage_type_group_of(~%combat_id%~)
				PATCH_IF $damage_group_of(~%combat_id%~) == group_g AND ($group_counts(~damage_type~) == 1
						OR ($damage_type_group_size(~%weapon_type_group%~) == 1 AND $damage_group_size(~%group_g%~) == 1)) BEGIN
					PATCH_IF NOT weapon_type_added BEGIN
						SET weapon_type = $combat_damage_type(~%combat_id%~)
						LPF ad_tra INT_VAR tra_id = 8040000 + weapon_type tra_block_start = 8040000 tra_block_size = 10000 RET weapon_type_name = text END
						SPRINT weapon_value ~%weapon_value% (%weapon_type_name%)~
						SET weapon_type_added = 1
					END
					SET $combat_type_shown(~%combat_id%~) = 1
				END
			END
			LPM ad_combat_suffix
			SET weapon_name_tra = 6100002 // ~Dégâts~
			LPM ad_weapon_attribute_line
		END
	END
	PATCH_IF $group_counts(~damage_type~) > 1 OR NOT weapon_shrink BEGIN
		SPRINT group_attr ~damage_type~
		FOR (group_g = 0; group_g < $group_counts(~damage_type~); ++group_g) BEGIN
			SET weapon_type_line = 0
			FOR (combat_id = 0; combat_id < combat_count; ++combat_id) BEGIN
				SPRINT weapon_damage $combat_damage(~%combat_id%~)
				PATCH_IF $damage_type_group_of(~%combat_id%~) == group_g AND NOT $combat_type_shown(~%combat_id%~)
						AND NOT (~%weapon_damage%~ STRING_EQUAL ~~) BEGIN
					SET weapon_type_line = 1
				END
			END
			PATCH_IF weapon_type_line BEGIN
				SET group_skip_shown = 1
				LPM ad_combat_suffix
				SET weapon_type = $damage_type_group_value(~%group_g%~)
				LPF ad_tra INT_VAR tra_id = 8040000 + weapon_type tra_block_start = 8040000 tra_block_size = 10000 RET weapon_value = text END
				SET weapon_name_tra = 6100003 // ~Type de dégâts~
				LPM ad_weapon_attribute_line
			END
		END
	END
END
