// Opcode 0, classe d'armure (IESDP) : parameter1 = modificateur, parameter2 = attaques concernées
// (0 toutes ; masque 1 contondantes, 2 projectiles, 4 perforantes, 8 tranchantes), ou 16 = CA de
// base fixée à parameter1. Le moteur du jeu cumule les modificateurs.
//
// Pris en charge : effets d'équipement certains, actifs tant que l'objet est équipé, d'un objet
// qui n'est pas une armure.
//
// CLEAR_ARRAY laisse lisibles les anciennes entrées (V36) : chaque entrée des tableaux de travail
// est remise à zéro avant d'être combinée.

// ---------------------------------------------------------------------------------------------
// Prise en charge (ancien opcode_0_is_valid, plus les cas que ce moteur ne décrit pas encore)

DEFINE_PATCH_MACRO ad_op_0_support BEGIN
	LOCAL_SET ac_base_count = 0
	LOCAL_SET ac_modifier_count = 0
	FOR (ac_id = 0; ac_id < fx_count; ++ac_id) BEGIN
		PATCH_IF $fx_opcode(~%ac_id%~) == 0 BEGIN
			SET ac_value = $fx_parameter1(~%ac_id%~)
			SET $ac_seen_all(~%ac_value%~) = 0
			SET $ac_seen_types(~%ac_value%~) = 0
		END
	END
	FOR (ac_id = 0; ac_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++ac_id) BEGIN
		PATCH_IF $fx_opcode(~%ac_id%~) == 0 BEGIN
			SPRINT ac_block $fx_block(~%ac_id%~)
			SPRINT ac_timing_kind $fx_timing_kind(~%ac_id%~)
			SET ac_value = $fx_parameter1(~%ac_id%~)
			SET ac_type = $fx_parameter2(~%ac_id%~)
			PATCH_IF NOT (~%ac_block%~ STRING_EQUAL ~equipped~) OR NOT (~%ac_timing_kind%~ STRING_EQUAL ~while_equipped~)
					OR $fx_probability(~%ac_id%~) != 100 BEGIN
				SPRINT render_missing ~not_implemented:opcode0:effect_kind~
			END
			// L'ancien moteur intègre la CA d'une armure à un attribut de l'objet.
			ELSE PATCH_IF item_type == ITM_TYPE_armor BEGIN
				SPRINT render_missing ~not_implemented:opcode0:armor~
			END
			ELSE PATCH_IF ac_type == AC_MOD_TYPE_set_base BEGIN
				SET ac_base_count += 1
			END
			// L'ancien moteur écarte un modificateur nul ou un type inconnu (erreur journalisée).
			ELSE PATCH_IF ac_value == 0 OR (ac_type != AC_MOD_TYPE_all AND ac_type != AC_MOD_TYPE_crushing
					AND ac_type != AC_MOD_TYPE_missile AND ac_type != AC_MOD_TYPE_piercing AND ac_type != AC_MOD_TYPE_slashing) BEGIN
				SPRINT render_missing ~not_implemented:opcode0:invalid~
			END
			ELSE BEGIN
				SET ac_modifier_count += 1
				// L'ancien moteur fusionne deux effets identiques au lieu de les cumuler.
				PATCH_IF ac_type == AC_MOD_TYPE_all BEGIN
					PATCH_IF $ac_seen_all(~%ac_value%~) BEGIN
						SPRINT render_missing ~not_implemented:opcode0:same_effect_twice~
					END
					SET $ac_seen_all(~%ac_value%~) = 1
				END
				ELSE BEGIN
					SET ac_mask = $ac_seen_types(~%ac_value%~)
					PATCH_IF (ac_mask BAND ac_type) != 0 BEGIN
						SPRINT render_missing ~not_implemented:opcode0:same_effect_twice~
					END
					SET $ac_seen_types(~%ac_value%~) = ac_mask BOR ac_type
					// Les quatre types à la fois : l'ancien moteur n'a pas de texte pour ce cas.
					PATCH_IF $ac_seen_types(~%ac_value%~) == 15 BEGIN
						SPRINT render_missing ~not_implemented:opcode0:all_attack_types~
					END
				END
			END
		END
	END
	// L'ancien moteur ajoute la ligne regroupée après celle de la CA de base : ordre non vérifié.
	PATCH_IF ac_base_count > 1 OR (ac_base_count > 0 AND ac_modifier_count > 0) BEGIN
		SPRINT render_missing ~not_implemented:opcode0:base_with_other~
	END
END

// ---------------------------------------------------------------------------------------------
// Regroupement (ancien opcode_0_group), selon AD_ENABLE_SHRINKAGE et AD_SHRINK_CLASS_ARMOR :
// - les deux à 1 : une ligne de totaux (ad_op_0_group_totals) ;
// - AD_SHRINK_CLASS_ARMOR à 0 : une ligne par effet, sauf les effets de même modificateur contre
//   des types d'attaque, réunis en une ligne (ad_op_0_group_attack_types) ;
// - AD_ENABLE_SHRINKAGE à 0 : une ligne par effet (ad_op_0_group_attack_types).

DEFINE_PATCH_MACRO ad_op_0_lines BEGIN
	SPRINT line_section ~equipped~
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_CLASS_ARMOR BEGIN
		LPM ad_op_0_group_totals
	END
	ELSE BEGIN
		LPM ad_op_0_group_attack_types
	END
END

// Total contre toutes les attaques, puis total contre chaque type d'attaque qui en diffère ; les
// types dont le total est nul forment la ligne « Ne protège pas » (effet dérivé AC_NO_PROTECTION).
DEFINE_PATCH_MACRO ad_op_0_group_totals BEGIN
	LOCAL_SET ac_all = 0
	LOCAL_SPRINT ac_values ~~
	LOCAL_SPRINT ac_unprotected ~~
	// Clé opposée au modificateur : les types d'attaque viennent du plus grand bonus au plus petit,
	// comme dans l'ancien moteur.
	CLEAR_ARRAY ac_masks
	FOR (ac_id = 0; ac_id < fx_count; ++ac_id) BEGIN
		PATCH_IF $fx_opcode(~%ac_id%~) == 0 AND NOT $fx_consumed(~%ac_id%~) AND $fx_parameter2(~%ac_id%~) != AC_MOD_TYPE_set_base
				AND $fx_parameter2(~%ac_id%~) != AC_MOD_TYPE_all BEGIN
			SET ac_key = 0 - $fx_parameter1(~%ac_id%~)
			SET $ac_masks(~%ac_key%~) = 0
		END
	END
	SET line_sort = $AD_OPCODE_SORT(~0~)
	FOR (ac_id = 0; ac_id < fx_count; ++ac_id) BEGIN
		PATCH_IF $fx_opcode(~%ac_id%~) == 0 AND NOT $fx_consumed(~%ac_id%~) BEGIN
			SET ac_type = $fx_parameter2(~%ac_id%~)
			SET ac_value = $fx_parameter1(~%ac_id%~)
			PATCH_IF ac_type == AC_MOD_TYPE_set_base BEGIN
				LPM ad_op_0_base_line
			END
			ELSE PATCH_IF ac_type == AC_MOD_TYPE_all BEGIN
				SET ac_all += ac_value
			END
			ELSE BEGIN
				SET ac_key = 0 - ac_value
				SET $ac_masks(~%ac_key%~) = $ac_masks(~%ac_key%~) BOR ac_type
			END
		END
	END
	PATCH_IF ac_all != 0 BEGIN
		LPF ad_signed_value INT_VAR value = ac_all RET ac_values = text END
	END
	SORT_ARRAY_INDICES ac_masks NUMERICALLY
	PHP_EACH ac_masks AS ac_key => ac_mask BEGIN
		LPF ad_tra INT_VAR tra_id = 20001000 + ac_mask tra_block_start = 20001000 tra_block_size = 16 RET versus = text END
		SET ac_total = ac_all - ac_key
		PATCH_IF ac_total == 0 BEGIN
			PATCH_IF NOT (~%ac_unprotected%~ STRING_EQUAL ~~) BEGIN
				SPRINT ac_unprotected ~%ac_unprotected%, ~
			END
			SPRINT ac_unprotected ~%ac_unprotected%%versus%~
		END
		ELSE BEGIN
			LPF ad_signed_value INT_VAR value = ac_total RET ac_total_text = text END
			PATCH_IF NOT (~%ac_values%~ STRING_EQUAL ~~) BEGIN
				SPRINT ac_values ~%ac_values%, ~
			END
			SPRINT ac_values ~%ac_values%%ac_total_text% %versus%~
		END
	END
	PATCH_IF NOT (~%ac_values%~ STRING_EQUAL ~~) BEGIN
		SPRINT name @20000000 // ~Classe d'armure~
		SPRINT value ~%ac_values%~
		SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
		LPM ad_line_add
	END
	PATCH_IF NOT (~%ac_unprotected%~ STRING_EQUAL ~~) BEGIN
		SPRINT versus ~%ac_unprotected%~
		SET line_sort = $AD_DERIVED_SORT(~AC_NO_PROTECTION~)
		SPRINT line_text @30010100 // ~Ne protège pas %versus%~
		LPM ad_line_add
	END
END

// Une ligne par effet, dans l'ordre du fichier ; avec AD_ENABLE_SHRINKAGE, les effets de même
// modificateur contre des types d'attaque forment une seule ligne (effet dérivé
// AC_BY_ATTACK_TYPE), dans l'ordre de première apparition du modificateur.
DEFINE_PATCH_MACRO ad_op_0_group_attack_types BEGIN
	CLEAR_ARRAY ac_type_groups
	FOR (ac_id = 0; ac_id < fx_count AND AD_ENABLE_SHRINKAGE; ++ac_id) BEGIN
		PATCH_IF $fx_opcode(~%ac_id%~) == 0 AND NOT $fx_consumed(~%ac_id%~) AND $fx_parameter2(~%ac_id%~) != AC_MOD_TYPE_set_base
				AND $fx_parameter2(~%ac_id%~) != AC_MOD_TYPE_all BEGIN
			SET ac_value = $fx_parameter1(~%ac_id%~)
			SET $ac_type_groups(~%ac_value%~) = 0
		END
	END
	SET line_sort = $AD_OPCODE_SORT(~0~)
	FOR (ac_id = 0; ac_id < fx_count; ++ac_id) BEGIN
		PATCH_IF $fx_opcode(~%ac_id%~) == 0 AND NOT $fx_consumed(~%ac_id%~) BEGIN
			SET ac_type = $fx_parameter2(~%ac_id%~)
			SET ac_value = $fx_parameter1(~%ac_id%~)
			PATCH_IF ac_type == AC_MOD_TYPE_set_base BEGIN
				LPM ad_op_0_base_line
			END
			ELSE PATCH_IF ac_type == AC_MOD_TYPE_all OR NOT AD_ENABLE_SHRINKAGE BEGIN
				SET ac_mask = ac_type
				LPM ad_op_0_modifier_line
			END
			ELSE BEGIN
				SET $ac_type_groups(~%ac_value%~) = $ac_type_groups(~%ac_value%~) BOR ac_type
			END
		END
	END
	SET line_sort = $AD_DERIVED_SORT(~AC_BY_ATTACK_TYPE~)
	PHP_EACH ac_type_groups AS ac_value => ac_mask BEGIN
		LPM ad_op_0_modifier_line
	END
END

// ---------------------------------------------------------------------------------------------
// Texte d'une ligne (ancien opcode_self_0)

DEFINE_PATCH_MACRO ad_op_0_base_line BEGIN
	SPRINT name @20000001 // ~Classe d'armure de base~
	SPRINT value ~%ac_value%~
	SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
	LPM ad_line_add
END

// Modificateur ac_value contre les attaques du masque ac_mask (0 : toutes) : « +2 », ou « Bonus
// de 2 » avec AD_ARMOR_CLASS_SHOW_BONUS_MALUS.
DEFINE_PATCH_MACRO ad_op_0_modifier_line BEGIN
	PATCH_IF NOT AD_ARMOR_CLASS_SHOW_BONUS_MALUS BEGIN
		LPF ad_signed_value INT_VAR value = ac_value RET value = text END
	END
	ELSE PATCH_IF ac_value >= 0 BEGIN
		SET value = ac_value
		SPRINT value @20000002 // ~Bonus de %value%~
	END
	ELSE BEGIN
		SET value = 0 - ac_value
		SPRINT value @20000003 // ~Malus de %value%~
	END
	PATCH_IF ac_mask != AC_MOD_TYPE_all BEGIN
		LPF ad_tra INT_VAR tra_id = 20001000 + ac_mask tra_block_start = 20001000 tra_block_size = 16 RET versus = text END
		SPRINT value ~%value% %versus%~
	END
	SPRINT name @20000000 // ~Classe d'armure~
	SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
	LPM ad_line_add
END
