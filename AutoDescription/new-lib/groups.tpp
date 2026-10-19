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
END

// Six caractéristiques modifiées de la même façon (ancien opcode_6_group, opcode virtuel 501) :
// une ligne « Caractéristiques » (effet dérivé ABILITIES). Chaque effet de Charisme (6), dans
// l'ordre du fichier, est réuni au premier effet non consommé de chacune des cinq autres
// caractéristiques qui a les mêmes champs (ad_fx_signature).
DEFINE_PATCH_MACRO ad_group_abilities BEGIN
	FOR (group_id = 0; group_id < fx_count; ++group_id) BEGIN
		PATCH_IF $fx_opcode(~%group_id%~) == 6 BEGIN
			LPF ad_fx_signature INT_VAR fx_id = group_id RET group_signature = signature END
			SET group_found = 1
			PATCH_FOR_EACH group_opcode IN 10 15 19 44 49 BEGIN
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
				PATCH_FOR_EACH group_opcode IN 10 15 19 44 49 BEGIN
					SET group_other = $group_member(~%group_opcode%~)
					SET $fx_consumed(~%group_other%~) = 1
				END
				SET group_value = $fx_parameter1(~%group_id%~)
				SET group_mode = $fx_parameter2(~%group_id%~)
				LPF ad_stat_modifier_value INT_VAR value = group_value mode = group_mode RET value = text END
				SPRINT name @30030000 // ~Caractéristiques~
				SPRINT line_section ~equipped~
				SET line_sort = $AD_DERIVED_SORT(~ABILITIES~)
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
