// Rendu des objets : partie roleplay d'origine, titre « PARAMÈTRES », capacités d'équipement
// (lignes fixes et lignes des opcodes décrits), capacités de charge (new-lib/item_charged.tpp),
// capacités de combat et attributs des armes et munitions (new-lib/item_combat.tpp), « Nécessite »,
// poids. Seuls les objets que ce rendu décrit
// entièrement sont couverts (ad_item_render_support).

// Raison de non-couverture si l'objet demande un rendu qui n'existe pas encore, vide sinon :
// fléchettes (ligne « Utilisation »), cas que ad_item_combat_support ou ad_item_charged_support
// refuse, utilisabilité (affichée seulement sur les jeux classiques), cas
// d'un opcode décrit que sa macro ad_op_<N>_support refuse.
DEFINE_PATCH_MACRO ad_item_render_support BEGIN
	READ_SHORT ITM_type item_type
	SPRINT render_missing ~~
	SET combat_is_ammo = 0
	SET item_has_combat = (item_type >= ITM_TYPE_bow AND item_type <= ITM_TYPE_polearm)
		OR item_type == ITM_TYPE_arrows OR item_type == ITM_TYPE_bullets OR item_type == ITM_TYPE_bolts
	PATCH_IF item_type == ITM_TYPE_dart BEGIN
		SPRINT render_missing ~not_implemented:item_type~
	END
	ELSE PATCH_IF item_has_combat BEGIN
		LPM ad_item_combat_support
	END
	SET item_has_charged = fx_header_count > 0 AND item_type != ITM_TYPE_dart
	PATCH_IF item_has_charged BEGIN
		LPM ad_item_charged_support
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT IS_EE BEGIN
		SPRINT render_missing ~not_implemented:usability~
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_application_support
	END
	PHP_EACH fx_opcode_count AS render_opcode => _ BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			LPM ad_opcode_is_described
			PATCH_IF opcode_described BEGIN
				LPM ~ad_op_%render_opcode%_support~
			END
		END
	END
END

// Un opcode inconnu (absent du catalogue ou du jeu courant) n'est jamais décrit.
DEFINE_PATCH_MACRO ad_opcode_is_described BEGIN
	SET opcode_described = 0
	PATCH_IF VARIABLE_IS_SET $AD_OPCODE_STATUS(~%render_opcode%~) BEGIN
		SPRINT opcode_status $AD_OPCODE_STATUS(~%render_opcode%~)
		SET opcode_described = $AD_OPCODE_AVAILABLE(~%render_opcode%~) AND (~%opcode_status%~ STRING_EQUAL ~DESCRIBED~)
	END
END

DEFINE_PATCH_MACRO ad_item_render BEGIN
	LPF ad_strip_technical_part STR_VAR text = ~%original_description%~ RET description = text END
	LPM ad_lines_reset
	LPM ad_item_equipped_lines
	LPM ad_cross_groups
	// fx_opcode_count est trié (ad_set_coverage) : l'ordre des ajouts ne dépend pas du fichier.
	PHP_EACH fx_opcode_count AS render_opcode => _ BEGIN
		LPM ad_opcode_is_described
		PATCH_IF opcode_described BEGIN
			LPM ~ad_op_%render_opcode%_lines~
		END
	END
	LPM ad_item_armor_lines
	PATCH_IF item_has_combat BEGIN
		LPM ad_item_combat_lines
	END
	LPF ad_lines_section_text STR_VAR section = ~equipped~ RET equipped_lines = text END
	PATCH_IF NOT (~%equipped_lines%~ STRING_EQUAL ~~) BEGIN
		SPRINT title @1300001 // ~Capacités d'équipement~
		SPRINT description ~%description%%CRLF%%CRLF%%title%%AD_COLON%%equipped_lines%~
	END
	PATCH_IF item_has_charged BEGIN
		LPM ad_item_charged_section
	END
	PATCH_IF item_has_combat BEGIN
		LPM ad_item_combat_section
	END
	// Section de l'armure : lignes sans puce, après une ligne vide (ancien
	// add_global_effects_to_description).
	LPF ad_lines_section_text INT_VAR level = 0 STR_VAR section = ~armor~ RET armor_lines = text END
	PATCH_IF NOT (~%armor_lines%~ STRING_EQUAL ~~) BEGIN
		SPRINT description ~%description%%CRLF%%armor_lines%~
	END
	PATCH_IF item_has_combat BEGIN
		LPM ad_item_weapon_attributes
	END
	LPM ad_item_requirements_section
	// Ligne vide avant le poids, comme dans l'ancien moteur.
	SPRINT description ~%description%%CRLF%~
	READ_LONG ITM_weight value
	SPRINT name @6200001 // ~Poids~
	SPRINT line @1200000 // ~%name%%AD_COLON%%value%~
	SPRINT description ~%description%%CRLF%%line%~
	INNER_PATCH_SAVE description ~%description%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~\(%CRLF%%CRLF%%CRLF%\)+~ ~%CRLF%%CRLF%~
	END
END

// Retire de la description d'origine sa partie technique (repérée par son titre) et la remplace
// par le titre « PARAMÈTRES », ajouté en fin de texte s'il n'y en avait pas.
DEFINE_PATCH_FUNCTION ad_strip_technical_part
	STR_VAR
		text = ~~
	RET
		text
BEGIN
	SPRINT strip_regex @1900000 // titres de partie technique connus, suivis du reste du texte
	SPRINT strip_title @1300000 // ~PARAMÈTRES~
	INNER_PATCH_SAVE text ~%text%~ BEGIN
		REPLACE_TEXTUALLY CASE_INSENSITIVE EVALUATE_REGEXP ~%strip_regex%~ ~%strip_title%%AD_COLON%%CRLF%~
	END
	PATCH_IF INDEX (CASE_INSENSITIVE EVALUATE_REGEXP ~%strip_title%~ ~%text%~) < 0 BEGIN
		SPRINT text ~%text%%CRLF%%CRLF%%strip_title%%AD_COLON%%CRLF%~
	END
END

// Lignes fixes, avant celles des effets (rangs inférieurs à toute valeur SORT du catalogue). Le
// moteur EE protège des coups critiques les casques sans le drapeau 25 et les autres objets qui
// l'ont.
DEFINE_PATCH_MACRO ad_item_equipped_lines BEGIN
	READ_LONG ITM_flags item_flags
	SPRINT line_section ~equipped~
	PATCH_IF (item_flags BAND BIT4) != 0 BEGIN
		SET line_sort = 0 - 2
		SPRINT line_text @6000000 // ~Maudit%AD_COLON%Ne peut être ôté qu'à l'aide d'un sort de Délivrance de la malédiction~
		LPM ad_line_add
	END
	PATCH_IF IS_EE AND (((item_flags BAND BIT25) == 0 AND item_type == ITM_TYPE_helm) OR ((item_flags BAND BIT25) != 0 AND item_type != ITM_TYPE_helm)) BEGIN
		SET line_sort = 0 - 1
		SPRINT line_text @6000001 // ~Protection contre les coups critiques~
		LPM ad_line_add
	END
END

// Une ligne par caractéristique minimale, dans l'ordre de AD_ITEM_REQUIREMENTS ; la Force
// exceptionnelle (bonus 1-100) ne s'affiche qu'avec une Force de 18.
DEFINE_PATCH_MACRO ad_item_requirements_section BEGIN
	READ_BYTE ITM_min_strength_bonus strength_bonus
	SPRINT requirement_lines ~~
	PHP_EACH AD_ITEM_REQUIREMENTS AS requirement_stat => requirement_offset BEGIN
		READ_BYTE requirement_offset value
		PATCH_IF value > 0 BEGIN
			LPF ad_tra INT_VAR tra_id = 8000000 + requirement_stat tra_block_start = 8000000 tra_block_size = 10000 RET attribute = text END
			PATCH_IF requirement_stat == 36 AND value == 18 AND strength_bonus > 0 AND strength_bonus <= 100 BEGIN
				SPRINT bonus ~%strength_bonus%~
				PATCH_IF strength_bonus == 100 BEGIN
					SPRINT bonus ~00~
				END
				ELSE PATCH_IF strength_bonus < 10 BEGIN
					SPRINT bonus ~0%bonus%~
				END
				SPRINT value ~18/%bonus%~
			END
			SPRINT line @6200000 // ~%value% en %attribute%~
			SPRINT requirement_lines ~%requirement_lines%%CRLF%- %line%~
		END
	END
	PATCH_IF NOT (~%requirement_lines%~ STRING_EQUAL ~~) BEGIN
		SPRINT title @1300002 // ~Nécessite~
		SPRINT description ~%description%%CRLF%%CRLF%%title%%AD_COLON%%requirement_lines%~
	END
END

// L'objet est utilisable par au moins une classe du groupe class_mask (bits d'exclusion des classes
// dans les drapeaux d'utilisabilité, ex. AD_USABILITY_CLERICS) ; les exclusions de kits ne sont pas
// lues, comme dans l'ancien moteur.
DEFINE_PATCH_FUNCTION ad_item_usable_by
	INT_VAR
		class_mask = 0
	RET
		usable
BEGIN
	READ_LONG ITM_usability_flags usability_flags
	SET usable = (usability_flags BAND class_mask) != class_mask
END

// Une armure qui n'est pas une robe et n'empêche pas de lancer des sorts profanes (opcode 145,
// parameter2 = 0) le dit, avec AD_ARMOR_SHOW_ALLOWS_TO_CAST_SPELLS ; ligne ajoutée après celles des
// effets, comme dans l'ancien moteur.
DEFINE_PATCH_MACRO ad_item_armor_lines BEGIN
	PATCH_IF item_type == ITM_TYPE_armor AND AD_ARMOR_SHOW_ALLOWS_TO_CAST_SPELLS BEGIN
		LPF ad_item_is_robe RET armor_is_robe = is_robe END
		SET armor_blocks_arcane = 0
		FOR (armor_id = 0; armor_id < fx_count; ++armor_id) BEGIN
			SPRINT armor_block $fx_block(~%armor_id%~)
			PATCH_IF $fx_opcode(~%armor_id%~) == 145 AND $fx_parameter2(~%armor_id%~) == 0 AND $fx_probability(~%armor_id%~) == 100
					AND ~%armor_block%~ STRING_EQUAL ~equipped~ BEGIN
				SET armor_blocks_arcane = 1
			END
		END
		PATCH_IF NOT armor_is_robe AND NOT armor_blocks_arcane BEGIN
			SPRINT line_section ~equipped~
			SET line_sort = $AD_OPCODE_SORT(~145~)
			SPRINT line_text @6000002 // ~Permet de lancer des sorts profanes~
			LPM ad_line_add
		END
	END
END

// Robe : armure dont l'animation est celle d'une robe de mage (2W, 3W, 4W), comme l'ancien is_robe.
DEFINE_PATCH_FUNCTION ad_item_is_robe
	RET
		is_robe
BEGIN
	READ_ASCII ITM_animation robe_animation (2)
	SET is_robe = ~%robe_animation%~ STRING_EQUAL ~2W~ OR ~%robe_animation%~ STRING_EQUAL ~3W~ OR ~%robe_animation%~ STRING_EQUAL ~4W~
END
