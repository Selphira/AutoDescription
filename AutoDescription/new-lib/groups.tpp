// Passe 3 : regroupements entre opcodes, après la prise en charge de tous les opcodes et avant
// leurs lignes. Un effet réuni à d'autres est marqué consommé (fx_consumed) : la macro
// ad_op_<N>_lines de son opcode le saute, et la ligne est celle d'un effet dérivé. Les règles
// s'appliquent dans l'ordre ci-dessous, indépendamment de l'ordre des opcodes. Une règle fixe
// l'opcode d'ancrage, les opcodes membres, l'effet dérivé, le nom de la ligne et la macro qui
// écrit la ligne (group_line), puis appelle ad_group_same_fields.
//
// Tableau écrit : fx_consumed (initialisé à 0 à la lecture, new-lib/effects.tpp).

DEFINE_PATCH_MACRO ad_cross_groups BEGIN
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_ABILITIES BEGIN
		LPM ad_group_abilities
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_SAVES_THROWS BEGIN
		LPM ad_group_saving_throws
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		LPM ad_group_exceptional_strength
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_THIEF_SKILLS BEGIN
		LPM ad_group_thief_skills
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		LPM ad_group_immunities
	END
	// L'ancien moteur tente toujours le regroupement de toutes les résistances avant ceux des
	// éléments et des dégâts physiques, qui n'ont aucun opcode commun.
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_RESISTANCES BEGIN
		LPM ad_group_all_resistances
		LPM ad_group_elemental_resistances
		LPM ad_group_physical_resistances
	END
END

// Six caractéristiques modifiées de la même façon (ancien opcode_6_group, opcode virtuel 501).
DEFINE_PATCH_MACRO ad_group_abilities BEGIN
	SET group_anchor = 6
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 10 15 19 44 49 END
	SPRINT group_derived ~ABILITIES~
	SPRINT group_name @30030000 // ~Caractéristiques~
	SPRINT group_line ~ad_group_modifier_line~
	LPM ad_group_same_fields
END

// Cinq jets de sauvegarde modifiés de la même façon (ancien opcode_33_group, qui produit un effet
// de l'opcode 325 « tous les jets de sauvegarde »).
DEFINE_PATCH_MACRO ad_group_saving_throws BEGIN
	SET group_anchor = 33
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 34 35 36 37 END
	SPRINT group_derived ~ALL_SAVES~
	SPRINT group_name @5000000 // ~Jets de sauvegarde~
	SPRINT group_line ~ad_group_modifier_line~
	LPM ad_group_same_fields
END

// Sept compétences de voleur modifiées de la même façon (ancien opcode_59_group, opcode virtuel
// 500).
DEFINE_PATCH_MACRO ad_group_thief_skills BEGIN
	SET group_anchor = 59
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 90 91 92 275 276 277 END
	SPRINT group_derived ~THIEF_SKILLS~
	SPRINT group_name @30090000 // ~Compétences de roublard~
	SPRINT group_line ~ad_group_modifier_line~
	LPM ad_group_same_fields
END

// Onze résistances modifiées de la même façon (ancien opcode_group_all_resistances, opcode
// virtuel 502).
DEFINE_PATCH_MACRO ad_group_all_resistances BEGIN
	SET group_anchor = 84
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 27 28 29 30 31 85 86 87 88 89 END
	SPRINT group_derived ~ALL_RESISTANCES~
	SET group_name_tra = 30050000 // ~Résistance aux dégâts~
	SPRINT group_line ~ad_group_resistance_line~
	LPM ad_group_same_fields
END

// Acide, froid, électricité, feu (ancien opcode_27_group, opcode virtuel 503).
DEFINE_PATCH_MACRO ad_group_elemental_resistances BEGIN
	SET group_anchor = 27
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 28 29 30 END
	SPRINT group_derived ~ELEMENTAL_RESISTANCES~
	SET group_name_tra = 30060000 // ~Résistance aux dégâts élémentaires~
	SPRINT group_line ~ad_group_resistance_line~
	LPM ad_group_same_fields
END

// Dégâts tranchants, contondants, perforants, de projectiles (ancien opcode_86_group, opcode
// virtuel 504).
DEFINE_PATCH_MACRO ad_group_physical_resistances BEGIN
	SET group_anchor = 86
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 87 88 89 END
	SPRINT group_derived ~PHYSICAL_RESISTANCES~
	SET group_name_tra = 30070000 // ~Résistance aux dégâts physiques~
	SPRINT group_line ~ad_group_resistance_line~
	LPM ad_group_same_fields
END

// Force exceptionnelle fixée et Force fixée (ancien opcode_97_group, opcode virtuel 522) :
// « Force : Passe à 18/50 » (effet dérivé EXCEPTIONAL_STRENGTH). Chaque effet 97 de valeur fixée,
// dans l'ordre du fichier, est réuni au premier effet 44 de valeur fixée non consommé qui a les
// mêmes champs sauf parameter1.
DEFINE_PATCH_MACRO ad_group_exceptional_strength BEGIN
	FOR (group_id = 0; group_id < fx_count; ++group_id) BEGIN
		PATCH_IF $fx_opcode(~%group_id%~) == 97 AND $fx_parameter2(~%group_id%~) == MOD_TYPE_flat AND NOT $fx_consumed(~%group_id%~) BEGIN
			LPF ad_fx_signature INT_VAR fx_id = group_id with_parameter1 = 0 RET group_signature = signature END
			SET group_other = 0 - 1
			FOR (group_candidate = 0; group_other < 0 AND group_candidate < fx_count; ++group_candidate) BEGIN
				PATCH_IF $fx_opcode(~%group_candidate%~) == 44 AND NOT $fx_consumed(~%group_candidate%~) BEGIN
					LPF ad_fx_signature INT_VAR fx_id = group_candidate with_parameter1 = 0 RET group_other_signature = signature END
					PATCH_IF ~%group_other_signature%~ STRING_EQUAL ~%group_signature%~ BEGIN
						SET group_other = group_candidate
					END
				END
			END
			PATCH_IF group_other >= 0 BEGIN
				SET $fx_consumed(~%group_id%~) = 1
				SET $fx_consumed(~%group_other%~) = 1
				SET strength = $fx_parameter1(~%group_other%~)
				SET strength_bonus = $fx_parameter1(~%group_id%~)
				SPRINT bonus ~%strength_bonus%~
				// Seul 100 est écrit sur deux chiffres (« 18/00 ») : l'ancien moteur écrit « 18/5 ».
				PATCH_IF strength_bonus == 100 BEGIN
					SPRINT bonus ~00~
				END
				SPRINT value ~%strength%/%bonus%~
				SPRINT value @1200002 // ~Passe à %value%~
				SPRINT name @8000036 // ~Force~
				SPRINT line_section ~equipped~
				SET line_sort = $AD_DERIVED_SORT(~EXCEPTIONAL_STRENGTH~)
				SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
				SET line_fx = group_id
				LPM ad_effect_line
			END
		END
	END
END

// Immunités (ancien opcode_101_group) : chaque immunité à l'opcode P (101), dans l'ordre du fichier,
// absorbe les effets qu'elle rend sans objet, s'ils ont la même cible, les mêmes probabilités et le
// même jet de sauvegarde :
// - ceux des lignes de 2da/immunity_absorbs.2da pour P (soins de l'état, autres immunités ; une
//   ligne CURE seulement avec AD_SHRINK_CURE_WITH_IMMUNITIES) ; une ligne RELABEL donne à
//   l'immunité ce libellé et la place après les autres, comme l'effet que l'ancien moteur ajoute ;
// - les protections contre un sort (206, 321) qui inflige P selon 2da/immunity_spells.2da, si elles
//   ont aussi les mêmes dés et la même puissance (321 : la même résistance).
DEFINE_PATCH_MACRO ad_group_immunities BEGIN
	FOR (immunity_id = 0; immunity_id < fx_count; ++immunity_id) BEGIN
		PATCH_IF $fx_opcode(~%immunity_id%~) == 101 AND NOT $fx_consumed(~%immunity_id%~) BEGIN
			SET immunity_opcode = $fx_parameter2(~%immunity_id%~)
			FOR (absorb_row = 0; absorb_row < AD_IMMUNITY_ABSORB_COUNT; ++absorb_row) BEGIN
				PATCH_IF $AD_IMMUNITY_ABSORB_IMMUNITY(~%absorb_row%~) == immunity_opcode
						AND (NOT $AD_IMMUNITY_ABSORB_CURE(~%absorb_row%~) OR AD_SHRINK_CURE_WITH_IMMUNITIES) BEGIN
					SET absorb_opcode = $AD_IMMUNITY_ABSORB_OPCODE(~%absorb_row%~)
					SET absorb_found = 0
					FOR (absorb_id = 0; absorb_id < fx_count; ++absorb_id) BEGIN
						PATCH_IF $fx_opcode(~%absorb_id%~) == absorb_opcode AND NOT $fx_consumed(~%absorb_id%~) AND absorb_id != immunity_id BEGIN
							SET absorb_parameter1 = $fx_parameter1(~%absorb_id%~)
							LPM ad_immunity_same_fields
							PATCH_IF absorb_same AND absorb_parameter1 >= $AD_IMMUNITY_ABSORB_P1_MIN(~%absorb_row%~)
									AND absorb_parameter1 <= $AD_IMMUNITY_ABSORB_P1_MAX(~%absorb_row%~)
									AND ($AD_IMMUNITY_ABSORB_ANY_P2(~%absorb_row%~) OR $fx_parameter2(~%absorb_id%~) == $AD_IMMUNITY_ABSORB_P2(~%absorb_row%~)) BEGIN
								SET $fx_consumed(~%absorb_id%~) = 1
								SET absorb_found = 1
							END
						END
					END
					PATCH_IF absorb_found AND $AD_IMMUNITY_ABSORB_RELABEL(~%absorb_row%~) >= 0 BEGIN
						SET $fx_immunity_label(~%immunity_id%~) = $AD_IMMUNITY_ABSORB_RELABEL(~%absorb_row%~)
						SET $fx_immunity_late(~%immunity_id%~) = 1
					END
				END
			END
			FOR (absorb_id = 0; absorb_id < fx_count; ++absorb_id) BEGIN
				SET absorb_opcode = $fx_opcode(~%absorb_id%~)
				PATCH_IF (absorb_opcode == 206 OR absorb_opcode == 321) AND NOT $fx_consumed(~%absorb_id%~) BEGIN
					SPRINT absorb_resref $fx_resource(~%absorb_id%~)
					TO_UPPER absorb_resref
					LPM ad_immunity_same_fields
					PATCH_IF absorb_same AND VARIABLE_IS_SET $AD_IMMUNITY_SPELLS(~%immunity_opcode% %absorb_resref%~)
							AND $fx_dice_count(~%absorb_id%~) == $fx_dice_count(~%immunity_id%~)
							AND $fx_dice_sides(~%absorb_id%~) == $fx_dice_sides(~%immunity_id%~)
							AND $fx_power(~%absorb_id%~) == $fx_power(~%immunity_id%~)
							AND (absorb_opcode == 206 OR $fx_resistance(~%absorb_id%~) == $fx_resistance(~%immunity_id%~)) BEGIN
						SET $fx_consumed(~%absorb_id%~) = 1
					END
				END
			END
		END
	END
END

// absorb_same : l'effet absorb_id a la même cible, les mêmes probabilités et le même jet de
// sauvegarde que l'immunité immunity_id.
DEFINE_PATCH_MACRO ad_immunity_same_fields BEGIN
	SET absorb_same = $fx_effective_target(~%absorb_id%~) == $fx_effective_target(~%immunity_id%~)
		AND $fx_probability1(~%absorb_id%~) == $fx_probability1(~%immunity_id%~)
		AND $fx_probability2(~%absorb_id%~) == $fx_probability2(~%immunity_id%~)
		AND $fx_save_type(~%absorb_id%~) == $fx_save_type(~%immunity_id%~)
		AND $fx_save_bonus(~%absorb_id%~) == $fx_save_bonus(~%immunity_id%~)
END

// Règle générique (ancien group_opcode_with_same_parameters) : chaque effet de l'opcode
// group_anchor, dans l'ordre du fichier, est réuni au premier effet non consommé de chacun des
// opcodes group_members qui a les mêmes champs (ad_fx_signature) ; s'ils sont tous trouvés, ils
// sont consommés et la macro group_line écrit la ligne de l'effet dérivé group_derived, d'après
// l'effet d'ancrage group_id.
DEFINE_PATCH_MACRO ad_group_same_fields BEGIN
	FOR (group_id = 0; group_id < fx_count; ++group_id) BEGIN
		PATCH_IF $fx_opcode(~%group_id%~) == group_anchor AND NOT $fx_consumed(~%group_id%~) BEGIN
			LPF ad_fx_signature INT_VAR fx_id = group_id RET group_signature = signature END
			SET group_found = 1
			PHP_EACH group_members AS _ => group_opcode BEGIN
				SET $group_member(~%group_opcode%~) = 0 - 1
				FOR (group_other = 0; group_found AND group_other < fx_count AND $group_member(~%group_opcode%~) < 0; ++group_other) BEGIN
					PATCH_IF $fx_opcode(~%group_other%~) == group_opcode AND NOT $fx_consumed(~%group_other%~) BEGIN
						LPF ad_fx_signature INT_VAR fx_id = group_other RET group_other_signature = signature END
						PATCH_IF ~%group_other_signature%~ STRING_EQUAL ~%group_signature%~ BEGIN
							SET $group_member(~%group_opcode%~) = group_other
						END
					END
				END
				SET group_found = group_found AND $group_member(~%group_opcode%~) >= 0
			END
			PATCH_IF group_found BEGIN
				SET $fx_consumed(~%group_id%~) = 1
				PHP_EACH group_members AS _ => group_opcode BEGIN
					SET group_other = $group_member(~%group_opcode%~)
					SET $fx_consumed(~%group_other%~) = 1
				END
				SPRINT line_section ~equipped~
				SET line_sort = $AD_DERIVED_SORT(~%group_derived%~)
				SET group_value = $fx_parameter1(~%group_id%~)
				SET group_mode = $fx_parameter2(~%group_id%~)
				LPM ~%group_line%~
				SET line_fx = group_id
				LPM ad_effect_line
			END
		END
	END
END

// « group_name : +1 » (modificateurs simples, new-lib/opcodes/stat_modifiers.tpp), en pourcentage
// si l'opcode d'ancrage l'est.
DEFINE_PATCH_MACRO ad_group_modifier_line BEGIN
	SET group_percent = VARIABLE_IS_SET $AD_STAT_MODIFIER_PERCENT(~%group_anchor%~)
	LPF ad_stat_modifier_value INT_VAR value = group_value mode = group_mode percent = group_percent RET value = text END
	SPRINT name ~%group_name%~
	SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
END

// Ligne de résistance (new-lib/opcodes/resistances.tpp), nom au libellé group_name_tra.
DEFINE_PATCH_MACRO ad_group_resistance_line BEGIN
	LPF ad_resistance_text INT_VAR value = group_value mode = group_mode name_tra = group_name_tra RET line_text = text END
END

// Champs qui doivent être égaux pour réunir deux effets, comme dans l'ancien moteur ; la cible
// n'en fait pas partie, l'ancien moteur la remplaçant par « soi » pour un effet d'équipement.
// with_parameter1 = 0 : parameter1 non comparé.
DEFINE_PATCH_FUNCTION ad_fx_signature
	INT_VAR
		fx_id = 0
		with_parameter1 = 1
	RET
		signature
BEGIN
	SET sig_power        = $fx_power(~%fx_id%~)
	SET sig_parameter1   = with_parameter1 ? $fx_parameter1(~%fx_id%~) : 0
	SET sig_parameter2   = $fx_parameter2(~%fx_id%~)
	SET sig_timing       = $fx_timing(~%fx_id%~)
	SET sig_resistance   = $fx_resistance(~%fx_id%~)
	SET sig_duration     = $fx_duration(~%fx_id%~)
	SET sig_probability1 = $fx_probability1(~%fx_id%~)
	SET sig_probability2 = $fx_probability2(~%fx_id%~)
	SET sig_dice_count   = $fx_dice_count(~%fx_id%~)
	SET sig_dice_sides   = $fx_dice_sides(~%fx_id%~)
	SET sig_save_type    = $fx_save_type(~%fx_id%~)
	SET sig_save_bonus   = $fx_save_bonus(~%fx_id%~)
	SET sig_special      = $fx_special(~%fx_id%~)
	SPRINT signature ~%sig_power% %sig_parameter1% %sig_parameter2% %sig_timing% %sig_resistance% %sig_duration% %sig_probability1% %sig_probability2% %sig_dice_count% %sig_dice_sides% %sig_save_type% %sig_save_bonus% %sig_special%~
END
