// Passe 3 : regroupements entre opcodes, après la prise en charge de tous les opcodes et avant
// leurs lignes. Un effet réuni à d'autres est marqué consommé (fx_consumed) : la macro
// ad_op_<N>_lines de son opcode le saute, et la ligne est celle d'un effet dérivé. Les règles
// s'appliquent dans l'ordre ci-dessous, indépendamment de l'ordre des opcodes.
//
// Tableau écrit : fx_consumed (initialisé à 0 à la lecture, new-lib/effects.tpp).

DEFINE_PATCH_MACRO ad_cross_groups BEGIN
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_ABILITIES BEGIN
		LPM ad_group_abilities
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_SAVES_THROWS BEGIN
		LPM ad_group_saving_throws
	END
END

// Six caractéristiques modifiées de la même façon (ancien opcode_6_group, opcode virtuel 501).
DEFINE_PATCH_MACRO ad_group_abilities BEGIN
	SET group_anchor = 6
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 10 15 19 44 49 END
	SPRINT group_derived ~ABILITIES~
	SPRINT group_name @30030000 // ~Caractéristiques~
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
	LPM ad_group_same_fields
END

// Règle générique (ancien group_opcode_with_same_parameters) : chaque effet de l'opcode
// group_anchor, dans l'ordre du fichier, est réuni au premier effet non consommé de chacun des
// opcodes group_members qui a les mêmes champs (ad_fx_signature) ; s'ils sont tous trouvés, ils
// sont consommés et forment une ligne « group_name : valeur » de l'effet dérivé group_derived.
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
				SET group_value = $fx_parameter1(~%group_id%~)
				SET group_mode = $fx_parameter2(~%group_id%~)
				LPF ad_stat_modifier_value INT_VAR value = group_value mode = group_mode RET value = text END
				SPRINT name ~%group_name%~
				SPRINT line_section ~equipped~
				SET line_sort = $AD_DERIVED_SORT(~%group_derived%~)
				SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
				LPM ad_line_add
			END
		END
	END
END

// Champs qui doivent être égaux pour réunir deux effets, comme dans l'ancien moteur ; la cible
// n'en fait pas partie, l'ancien moteur la remplaçant par « soi » pour un effet d'équipement.
DEFINE_PATCH_FUNCTION ad_fx_signature
	INT_VAR
		fx_id = 0
	RET
		signature
BEGIN
	SET sig_power        = $fx_power(~%fx_id%~)
	SET sig_parameter1   = $fx_parameter1(~%fx_id%~)
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
