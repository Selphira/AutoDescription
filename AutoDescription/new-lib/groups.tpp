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
				LPM ad_line_add
			END
		END
	END
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
				LPM ad_line_add
			END
		END
	END
END

// « group_name : +1 » (modificateurs simples, new-lib/opcodes/stat_modifiers.tpp).
DEFINE_PATCH_MACRO ad_group_modifier_line BEGIN
	LPF ad_stat_modifier_value INT_VAR value = group_value mode = group_mode RET value = text END
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
