// Premier rendu des objets : partie roleplay d'origine, titre « PARAMÈTRES », lignes fixes des
// capacités d'équipement (maudit, protection contre les coups critiques), « Nécessite », poids.
// Seuls les objets que ce rendu décrit entièrement sont couverts (ad_item_render_support).

// Raison de non-couverture si l'objet demande un rendu qui n'existe pas encore, vide sinon :
// en-têtes de capacités (charge, combat), sections propres aux armes, armures et munitions,
// utilisabilité (affichée seulement sur les jeux classiques).
DEFINE_PATCH_MACRO ad_item_render_support BEGIN
	READ_SHORT ITM_type item_type
	SPRINT render_missing ~~
	PATCH_IF fx_header_count > 0 BEGIN
		SPRINT render_missing ~not_implemented:headers~
	END
	ELSE PATCH_IF (item_type >= ITM_TYPE_bow AND item_type <= ITM_TYPE_polearm) OR item_type == ITM_TYPE_armor
			OR item_type == ITM_TYPE_arrows OR item_type == ITM_TYPE_bullets OR item_type == ITM_TYPE_bolts BEGIN
		SPRINT render_missing ~not_implemented:item_type~
	END
	ELSE PATCH_IF NOT IS_EE BEGIN
		SPRINT render_missing ~not_implemented:usability~
	END
END

DEFINE_PATCH_MACRO ad_item_render BEGIN
	LPF ad_strip_technical_part STR_VAR text = ~%original_description%~ RET description = text END
	LPM ad_item_equipped_section
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

// Le moteur EE protège des coups critiques les casques sans le drapeau 25 et les autres objets
// qui l'ont.
DEFINE_PATCH_MACRO ad_item_equipped_section BEGIN
	READ_LONG ITM_flags item_flags
	SPRINT equipped_lines ~~
	PATCH_IF (item_flags BAND BIT4) != 0 BEGIN
		SPRINT line @6000000 // ~Maudit%AD_COLON%Ne peut être ôté qu'à l'aide d'un sort de Délivrance de la malédiction~
		SPRINT equipped_lines ~%equipped_lines%%CRLF%- %line%~
	END
	PATCH_IF IS_EE AND (((item_flags BAND BIT25) == 0 AND item_type == ITM_TYPE_helm) OR ((item_flags BAND BIT25) != 0 AND item_type != ITM_TYPE_helm)) BEGIN
		SPRINT line @6000001 // ~Protection contre les coups critiques~
		SPRINT equipped_lines ~%equipped_lines%%CRLF%- %line%~
	END
	PATCH_IF NOT (~%equipped_lines%~ STRING_EQUAL ~~) BEGIN
		SPRINT title @1300001 // ~Capacités d'équipement~
		SPRINT description ~%description%%CRLF%%CRLF%%title%%AD_COLON%%equipped_lines%~
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
