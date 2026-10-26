// Opcode 219 (Stat: AC vs. Creature Type Modifier) : +2 à la classe d'armure et aux jets de sauvegarde
// contre le type de créature parameter1 du fichier IDS parameter2 (IESDP). Comme l'ancien
// opcode_219_replace (opcodes virtuels 219000 et 219001), un effet donne deux lignes : « Classe
// d'armure : +2 contre les créatures mauvaises » (rang AC_VS_CREATURE) et « Jets de sauvegarde : +2
// contre les créatures mauvaises » (rang SAVES_VS_CREATURE). Avec AD_ENABLE_SHRINKAGE et
// AD_SHRINK_CLASS_ARMOR, un effet d'équipement sur le porteur rejoint la ligne de la classe d'armure
// de son bloc quand celui-ci a un opcode 0 (ancien opcode_0_group, fx_ac_merged ;
// ad_op_0_group_totals, new-lib/opcodes/0.tpp) : « Classe d'armure : +2, +4 contre les créatures
// mauvaises ». Avec AD_ENABLE_SHRINKAGE, hors équipement (sorts, effets à l'impact…), les effets d'un
// bloc aux mêmes champs hormis le type de créature n'en font qu'un, rattaché au premier
// (fx_creature_anchor ; ancien opcode_219_group_versus) : « +2 contre les élémentaires, les esprits et
// les fées ».

// Refus : fichier IDS hors de 2-8, ou modificateur sans effet que l'ancien opcode_idscheck8_is_valid
// écarte (EA et valeur 100) ; type de créature sans nom ; effet probable (l'ancien moteur n'a pas de
// forme probable) ; avec AD_ENABLE_SHRINKAGE, plusieurs 219 d'équipement sur le porteur dans un bloc
// (l'ancien opcode_219001_group et opcode_0_group réunissent leurs types) ; réunion à la classe d'armure d'une armure, d'un
// modificateur de 2 contre un type d'attaque, ou qui l'annule (cas de l'ancien opcode_0_group non
// repris).
DEFINE_PATCH_MACRO ad_op_219_support BEGIN
	PHP_EACH fx_ids_219 AS _ => creature_ac_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%creature_ac_id%~) BEGIN
			SET creature_ac_file = $fx_parameter2(~%creature_ac_id%~)
			SET $fx_ac_merged(~%creature_ac_id%~) = 0
			SET $fx_creature_anchor(~%creature_ac_id%~) = creature_ac_id
			LPF ad_ids_name INT_VAR ids_file = creature_ac_file entry = $fx_parameter1(~%creature_ac_id%~) RET creature_ac_name = name END
			SPRINT creature_ac_scope $fx_scope(~%creature_ac_id%~)
			PATCH_IF creature_ac_file < 2 OR creature_ac_file > 8 OR (creature_ac_file == 2 AND $fx_parameter1(~%creature_ac_id%~) == 100) BEGIN
				SET creature_ac_value = $fx_parameter1(~%creature_ac_id%~)
				PATCH_IF creature_ac_file < 2 OR creature_ac_file > (IS_EE ? 9 : 8) BEGIN
					LPF ad_refusal INT_VAR fx_id = creature_ac_id STR_VAR reason = ~file_error:opcode219:invalid~ message = ~IDS file %creature_ac_file% is not a creature type (expected 2-8: EA, GENERAL, RACE, CLASS, SPECIFIC, GENDER, ALIGN; 9: KIT on enhanced editions)~ RET render_missing = refusal END
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = creature_ac_id STR_VAR reason = ~not_implemented:opcode219:invalid~ message = ~kit restriction or value 100 of EA.IDS not supported (IDS file %creature_ac_file%, value %creature_ac_value%)~ RET render_missing = refusal END
				END
			END
			ELSE PATCH_IF ~%creature_ac_name%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = creature_ac_id STR_VAR reason = ~not_implemented:opcode219:no_name~ message = ~creature type has no name~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_probability(~%creature_ac_id%~) < 100 BEGIN
				LPF ad_refusal INT_VAR fx_id = creature_ac_id STR_VAR reason = ~not_implemented:opcode219:probability~ message = ~probable effect~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SPRINT $fx_creature_type(~%creature_ac_id%~) ~%creature_ac_name%~
				SET creature_ac_all = 0
				SET creature_ac_zero = 0
				SET creature_ac_two = 0
				SET creature_ac_others = 0
				FOR (creature_ac_other = 0; creature_ac_other < fx_count; ++creature_ac_other) BEGIN
					SPRINT creature_ac_other_scope $fx_scope(~%creature_ac_other%~)
					SET creature_ac_other_opcode = $fx_opcode(~%creature_ac_other%~)
					PATCH_IF (~%creature_ac_other_scope%~ STRING_EQUAL ~%creature_ac_scope%~) AND NOT $fx_consumed(~%creature_ac_other%~) BEGIN
						SET creature_ac_others += creature_ac_other_opcode == 219 AND creature_ac_other != creature_ac_id
						PATCH_IF creature_ac_other_opcode == 0 BEGIN
							SET creature_ac_zero = 1
							SET creature_ac_type = $fx_parameter2(~%creature_ac_other%~)
							PATCH_IF creature_ac_type == AC_MOD_TYPE_all BEGIN
								SET creature_ac_all += $fx_parameter1(~%creature_ac_other%~)
							END
							ELSE PATCH_IF creature_ac_type != AC_MOD_TYPE_set_base AND $fx_parameter1(~%creature_ac_other%~) == 0 - 2 BEGIN
								SET creature_ac_two = 1
							END
						END
					END
				END
				SET creature_ac_equipped = (~%creature_ac_scope%~ STRING_EQUAL ~equipped~) AND $fx_timing(~%creature_ac_id%~) == TIMING_while_equipped
					AND $fx_effective_target(~%creature_ac_id%~) == TARGET_FX_self
				PATCH_IF AD_ENABLE_SHRINKAGE AND creature_ac_others > 0 AND NOT creature_ac_equipped BEGIN
					LPM ad_op_219_anchor
				END
				ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND creature_ac_others > 0 BEGIN
					LPF ad_refusal INT_VAR fx_id = creature_ac_id STR_VAR reason = ~not_implemented:opcode219:several~ message = ~several creature types~ RET render_missing = refusal END
				END
				ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_CLASS_ARMOR AND creature_ac_zero AND creature_ac_equipped BEGIN
					PATCH_IF item_type == ITM_TYPE_armor OR creature_ac_two OR creature_ac_all + 2 == 0 BEGIN
						LPF ad_refusal INT_VAR fx_id = creature_ac_id STR_VAR reason = ~not_implemented:opcode219:class_armor~ message = ~armor, two bonuses or all creatures: the old engine writes it differently~ RET render_missing = refusal END
					END
					ELSE BEGIN
						SET $fx_ac_merged(~%creature_ac_id%~) = 1
					END
				END
			END
		END
	END
END

// Premier effet d'un 219 précédent du bloc aux mêmes champs hormis le type de créature.
DEFINE_PATCH_MACRO ad_op_219_anchor BEGIN
	SET same_id = creature_ac_id
	SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2
	PHP_EACH fx_ids_219 AS _ => creature_ac_other BEGIN
		PATCH_IF creature_ac_other < creature_ac_id AND $fx_creature_anchor(~%creature_ac_id%~) == creature_ac_id
				AND NOT $fx_consumed(~%creature_ac_other%~) AND VARIABLE_IS_SET $fx_creature_type(~%creature_ac_other%~)
				AND $fx_creature_anchor(~%creature_ac_other%~) == creature_ac_other BEGIN
			SET same_other = creature_ac_other
			LPM ad_fx_same_fields
			PATCH_IF fx_same BEGIN
				SET $fx_creature_anchor(~%creature_ac_id%~) = creature_ac_other
			END
		END
	END
END

// Ligne de la classe d'armure (sauf si elle a rejoint celle de l'opcode 0), puis celle des jets de
// sauvegarde ; un effet rattaché à un autre n'en a pas.
DEFINE_PATCH_MACRO ad_op_219_lines BEGIN
	SPRINT line_section ~equipped~
	PHP_EACH fx_ids_219 AS _ => creature_ac_id BEGIN
		PATCH_IF NOT $fx_consumed(~%creature_ac_id%~) AND $fx_creature_anchor(~%creature_ac_id%~) == creature_ac_id BEGIN
			CLEAR_ARRAY creature_ac_names
			PHP_EACH fx_ids_219 AS _ => creature_ac_member BEGIN
				PATCH_IF NOT $fx_consumed(~%creature_ac_member%~) AND $fx_creature_anchor(~%creature_ac_member%~) == creature_ac_id BEGIN
					SPRINT creature_ac_name $fx_creature_type(~%creature_ac_member%~)
					SPRINT $creature_ac_names(~%creature_ac_name%~) ~%creature_ac_name%~
				END
			END
			SPRINT creature_ac_the @2002000 // ~les~
			SPRINT creature_ac_and_the @2002001 // ~et les~
			LPF ad_join STR_VAR array_name = ~creature_ac_names~ glue = EVAL ~, %creature_ac_the% ~ final_glue = EVAL ~ %creature_ac_and_the% ~ RET targetType = text END
			SPRINT versus @2002020 // ~contre les %targetType%~
			LPF ad_signed_value INT_VAR value = 2 RET value = text END
			SPRINT value ~%value% %versus%~
			SET line_fx = creature_ac_id
			PATCH_IF NOT $fx_ac_merged(~%creature_ac_id%~) BEGIN
				SPRINT name @20000000 // ~Classe d'armure~
				SET line_sort = $AD_DERIVED_SORT(~AC_VS_CREATURE~)
				SET line_phrase = 1200010 // ~%name%%AD_COLON%%value%~ (+1 : ~%name% %ofTheTarget%%AD_COLON%%value%~)
				LPM ad_effect_line
			END
			SPRINT name @5000000 // ~Jets de sauvegarde~
			SET line_sort = $AD_DERIVED_SORT(~SAVES_VS_CREATURE~)
			SET line_phrase = 1200010 // ~%name%%AD_COLON%%value%~ (+1 : ~%name% %ofTheTarget%%AD_COLON%%value%~)
			LPM ad_effect_line
		END
	END
END
