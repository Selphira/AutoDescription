// Opcode 12 (HP: Damage) : parameter1 et les dés = dégâts, parameter2 = type de dégâts (mots de poids
// fort, AD_DAMAGE_TYPES) + mode (mot de poids faible : 0 dégâts, 1 points de vie fixés, 2 fixés en
// pourcentage, 3 pourcentage des points de vie maximums). Sur EE, special : bits 0-1 et 3-4 drain ou
// transfert des points de vie (bits 3-4 non cumulatifs), bit 2 seulement à mains nues, bits 8 et 9
// moitié des dégâts au jet réussi ou raté (mode 0), bit 10 sans réveiller la cible.
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp). La durée n'est pas affichée (colonne DURATION). Un drain ou un transfert
// d'une durée limitée augmente les points de vie maximums pendant ce temps : l'ancien moteur le dit
// à part, pas encore repris. Des dégâts qui visent un type de créature (effet d'un 177) s'écrivent
// « contre les X » à la forme « cible » (versus, ad_application_versus, new-lib/application.tpp).

// ---------------------------------------------------------------------------------------------
// Prise en charge (ancien opcode_12_is_valid, plus les cas que ce moteur ne décrit pas encore)

DEFINE_PATCH_MACRO ad_op_12_support BEGIN
	FOR (damage_id = 0; damage_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++damage_id) BEGIN
		PATCH_IF $fx_opcode(~%damage_id%~) == 12 BEGIN
			LPM ad_op_12_value
			PATCH_IF damage_mode > 3 BEGIN
				SPRINT render_missing ~not_implemented:opcode12:invalid~
			END
			// Dégâts sans dé ni valeur : l'ancien moteur n'écrit pas de ligne.
			ELSE PATCH_IF (damage_mode == 0 OR damage_mode == 2) AND ~%damage_text%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode12:no_damage~
			END
			ELSE PATCH_IF (damage_drain OR damage_transfer) AND $fx_duration(~%damage_id%~) > 0 BEGIN
				SPRINT render_missing ~not_implemented:opcode12:max_hp~
			END
		END
	END
END

// ---------------------------------------------------------------------------------------------
// Lignes (ancien opcode_self_12, opcode_target_12 et opcode_12_common) : une par effet non consommé ;
// les effets réunis par ad_group_damage_halves (new-lib/groups.tpp) viennent après les autres, comme
// l'effet que l'ancien moteur ajoute en fin de liste.

DEFINE_PATCH_MACRO ad_op_12_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~12~)
	FOR (damage_late = 0; damage_late <= 1; ++damage_late) BEGIN
		FOR (damage_id = 0; damage_id < fx_count; ++damage_id) BEGIN
			PATCH_IF $fx_opcode(~%damage_id%~) == 12 AND NOT $fx_consumed(~%damage_id%~) AND $fx_late(~%damage_id%~) == damage_late BEGIN
				LPM ad_op_12_value
				SPRINT damage ~%damage_text%~
				PATCH_IF damage_mode == 0 BEGIN
					PATCH_IF VARIABLE_IS_SET $AD_DAMAGE_TYPES(~%damage_type%~) BEGIN
						SET damage_type_tra = $AD_DAMAGE_TYPES(~%damage_type%~)
					END
					ELSE BEGIN
						SET damage_type_tra = 20120010 // ~points de dégâts~
					END
					LPF ad_tra INT_VAR tra_id = damage_type_tra RET damageType = text END
					SPRINT damage @20120001 // ~%damage% %damageType%~
					SET line_phrase = damage_drain ? 20120110 : (damage_transfer ? 20120120 : 20120100) // ~Inflige %damage% %toTheTarget%~
					SET damage_target = $fx_effective_target(~%damage_id%~)
					PATCH_IF line_phrase == 20120100 AND ($fx_versus_file(~%damage_id%~) > 0 OR ctx_versus_set)
							AND damage_target != TARGET_FX_self AND damage_target != TARGET_FX_original_caster BEGIN
						SET line_phrase = 20120160 // ~Inflige %damage% %versus%~ (+1)
					END
				END
				ELSE PATCH_IF damage_mode == 1 BEGIN
					PATCH_IF ~%damage%~ STRING_EQUAL ~~ BEGIN
						SPRINT damage ~0~
					END
					SET line_phrase = 20120130
				END
				ELSE PATCH_IF damage_mode == 2 BEGIN
					SET line_phrase = 20120140
				END
				ELSE BEGIN
					SET line_phrase = 20120150
				END
				PATCH_IF damage_dont_wake BEGIN
					SPRINT damage_note @20120040 // ~ne réveille pas la cible~
					SPRINT line_suffix ~(%damage_note%)~
				END
				PATCH_IF damage_fist BEGIN
					SPRINT damage_note @20120041 // ~efficace si la source est désarmée~
					PATCH_IF ~%line_suffix%~ STRING_EQUAL ~~ BEGIN
						SPRINT line_suffix ~(%damage_note%)~
					END
					ELSE BEGIN
						SPRINT line_suffix ~%line_suffix% (%damage_note%)~
					END
				END
				SET line_save_for_half = damage_save_for_half
				SET line_fail_for_half = damage_fail_for_half
				SET line_fx = damage_id
				LPM ad_effect_line
			END
		END
	END
END

// Écrit damage_mode, damage_type, damage_text (dés et parameter1, sans le signe « + » de tête) et
// les drapeaux EE de l'effet damage_id (ancien opcode_12_flags).
DEFINE_PATCH_MACRO ad_op_12_value BEGIN
	SET damage_parameter2 = $fx_parameter2(~%damage_id%~)
	SET damage_mode = damage_parameter2 BAND 65535
	SET damage_type = damage_parameter2 - damage_mode
	LPF ad_dice_text INT_VAR dice_count = $fx_dice_count(~%damage_id%~) dice_sides = $fx_dice_sides(~%damage_id%~)
		bonus = $fx_parameter1(~%damage_id%~) RET damage_text = text END
	INNER_PATCH_SAVE damage_text ~%damage_text%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~^\+~ ~~
	END
	SET damage_special = IS_EE ? $fx_special(~%damage_id%~) : 0
	SET damage_drain = (damage_special BAND 0b11011) == BIT0 OR (damage_special BAND 0b11011) == BIT3
	SET damage_transfer = (damage_special BAND 0b11011) == BIT1 OR (damage_special BAND 0b11011) == BIT4
	SET damage_fist = (damage_special BAND BIT2) != 0
	SET damage_save_for_half = (damage_special BAND BIT8) != 0 AND damage_mode == 0
	SET damage_fail_for_half = (damage_special BAND BIT9) != 0 AND damage_mode == 0
	SET damage_dont_wake = (damage_special BAND BIT10) != 0
END
