// Opcode 101 (Protection: from Opcode) : immunité à l'opcode parameter2, « Immunité au silence ».
// Libellé « au silence » dans la liste @8030000 (8 030 000 + opcode ; libellé vide : immunité non
// décrite, comme dans l'ancien moteur). La passe des regroupements (ad_group_immunities,
// new-lib/groups.tpp) lui fait absorber les effets qu'elle rend sans objet et peut changer son
// libellé (fx_immunity_label) en le plaçant après les autres (fx_immunity_late, comme un effet
// identique à un autre, fx_late).
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp). Dans un en-tête autre que celui d'une potion, l'ancien moteur n'applique
// pas les absorptions des soins (delete_cure_linked_to_specific_immunity, lignes EQUIPPED de
// 2da/immunity_absorbs.2da) ni celle de l'action libre ; la ligne unique qu'il y forme prend les
// champs (durée, jet de sauvegarde…) de la dernière immunité de son groupe.

// Refus : opcode du catalogue sans libellé. Opcode hors du catalogue (ADTIM13 : 999) : erreur de fichier,
// effet écarté comme dans l'ancien moteur.

DEFINE_PATCH_MACRO ad_op_101_support BEGIN
	PHP_EACH fx_ids_101 AS _ => immunity_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET immunity_opcode = $fx_parameter2(~%immunity_id%~)
			SET immunity_label_tra = 8030000 + immunity_opcode
			// Opcode sans libellé : l'ancien moteur échoue sur la chaîne absente.
			PATCH_IF immunity_opcode < 0 OR immunity_opcode > 999 OR NOT TRA_ENTRY_EXISTS (~%immunity_label_tra%~) BEGIN
				PATCH_IF immunity_opcode < 0 OR immunity_opcode > 999 BEGIN
					SET drop_id = immunity_id
					SPRINT ignored_reason ~file_error:opcode101:unknown_opcode~
					SPRINT ignored_message ~opcode %immunity_opcode% does not exist (expected 0-999)~
					LPM ad_application_drop
				END
				ELSE PATCH_IF NOT VARIABLE_IS_SET $AD_OPCODE_AVAILABLE(~%immunity_opcode%~) BEGIN
					SET drop_id = immunity_id
					SPRINT ignored_reason ~file_error:opcode101:unknown_opcode~
					SPRINT ignored_message ~opcode %immunity_opcode% is not in the opcode catalog (2da/opcodes.2da) and has no name (string %immunity_label_tra%)~
					LPM ad_application_drop
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = immunity_id STR_VAR reason = ~not_implemented:opcode101:unknown_opcode~ message = ~no name for opcode %immunity_opcode%~ RET render_missing = refusal END
				END
			END
			ELSE BEGIN
				SET $fx_immunity_label(~%immunity_id%~) = immunity_opcode
				SET $fx_immunity_late(~%immunity_id%~) = 0
			END
		END
	END
END

// Lignes (ancien opcode_self_101 et opcode_101_post_group) : avec AD_SHRINK_IMMUNITIES_SINGLE_LINE,
// les immunités certaines d'un même bloc, d'une même classe de cible (soi ou lanceur d'origine ;
// cible prédéfinie) et aux mêmes champs écrits (parameter2, résistance et puissance mis à part : une ligne
// commune cacherait la durée ou la restriction de niveau des autres, SPPR403) sont réunies en une
// ligne si elles sont plusieurs, libellés identiques fusionnés ;
// les lignes réunies viennent après les autres, comme les effets que l'ancien moteur ajoute en fin de
// liste.
DEFINE_PATCH_MACRO ad_op_101_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~101~)
	CLEAR_ARRAY immunity_key_count
	PHP_EACH fx_ids_101 AS _ => immunity_id BEGIN
		PATCH_IF NOT $fx_consumed(~%immunity_id%~) BEGIN
			LPM ad_immunity_class
			PATCH_IF immunity_class > 0 BEGIN
				PATCH_IF NOT VARIABLE_IS_SET $immunity_key_count(~%immunity_key%~) BEGIN
					SET $immunity_key_count(~%immunity_key%~) = 0
				END
				SET $immunity_key_count(~%immunity_key%~) += 1
			END
		END
	END
	FOR (immunity_late = 0; immunity_late <= 1; ++immunity_late) BEGIN
		PHP_EACH fx_ids_101 AS _ => immunity_id BEGIN
			PATCH_IF NOT $fx_consumed(~%immunity_id%~) AND ($fx_immunity_late(~%immunity_id%~) OR $fx_late(~%immunity_id%~)) == immunity_late BEGIN
				LPM ad_immunity_class
				LPM ad_immunity_merged
				PATCH_IF NOT immunity_merged BEGIN
					LPM ad_immunity_label
					PATCH_IF NOT ~%immunity_label%~ STRING_EQUAL ~~ BEGIN
						SPRINT opcodeStr ~%immunity_label%~
						SET line_phrase = 21010100 // ~Immunité contre %opcodeStr%~ (+1 : ~Immunise %theTarget% %opcodeStr%~)
						SET line_fx = immunity_id
						LPM ad_effect_line
					END
				END
			END
		END
	END
	PHP_EACH immunity_key_count AS immunity_merged_key => immunity_merged_count BEGIN
		PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_IMMUNITIES_SINGLE_LINE AND immunity_merged_count > 1 BEGIN
			CLEAR_ARRAY immunity_labels
			SET immunity_label_count = 0
			SET immunity_first = 0 - 1
			FOR (immunity_late = 0; immunity_late <= 1; ++immunity_late) BEGIN
				PHP_EACH fx_ids_101 AS _ => immunity_id BEGIN
					PATCH_IF NOT $fx_consumed(~%immunity_id%~) AND ($fx_immunity_late(~%immunity_id%~) OR $fx_late(~%immunity_id%~)) == immunity_late BEGIN
						LPM ad_immunity_class
						PATCH_IF immunity_class > 0 AND (~%immunity_key%~ STRING_EQUAL ~%immunity_merged_key%~) BEGIN
							LPM ad_immunity_label
							PATCH_IF NOT ~%immunity_label%~ STRING_EQUAL ~~ BEGIN
								SPRINT $immunity_labels(~%immunity_label%~) ~%immunity_label%~
								SET immunity_label_count += 1
								PATCH_IF immunity_first < 0 BEGIN
									SET immunity_first = immunity_id
								END
							END
						END
					END
				END
			END
			PATCH_IF immunity_label_count > 0 BEGIN
				LPF ad_join STR_VAR array_name = ~immunity_labels~ RET opcodeStr = text END
				SET line_phrase = 21010100 // ~Immunité contre %opcodeStr%~
				SET line_fx = immunity_first
				LPM ad_effect_line
			END
		END
	END
END

// Classe de cible de l'effet immunity_id pour la ligne unique : 1 soi ou lanceur d'origine, 2 cible
// prédéfinie, 0 jamais réunie (immunité probable hors d'un sous-sort probable, autre cible) ; immunity_key : classe
// dans sa portée et champs comparés (une ligne unique par bloc et par jeu de champs).
DEFINE_PATCH_MACRO ad_immunity_class BEGIN
	SET immunity_target = $fx_effective_target(~%immunity_id%~)
	// Dans un sous-sort lancé sous une probabilité, toutes les immunités ont celle du parent : réunies
	// comme des immunités certaines (ancien opcode_101_post_group, qui les lit avant de l'appliquer, POTN21).
	SET immunity_class = ($fx_probability(~%immunity_id%~) < 100 AND ctx_base_probability >= 100) ? 0
		: ((immunity_target == TARGET_FX_self OR immunity_target == TARGET_FX_original_caster) ? 1
		: (immunity_target == TARGET_FX_preset ? 2 : 0))
	SPRINT immunity_key_scope $fx_scope(~%immunity_id%~)
	// Seuls les champs que la ligne écrit : parameter1 et special ne servent pas à l'opcode 101 ; la
	// durée d'un effet permanent ou tant que l'objet est équipé, et le bonus d'un effet sans jet, sont
	// ignorés par le jeu (SW2H21).
	SET immunity_external = $fx_external(~%immunity_id%~)
	SET immunity_timing = $fx_timing(~%immunity_id%~)
	SET immunity_duration = (immunity_timing == TIMING_permanent OR immunity_timing == TIMING_while_equipped OR immunity_timing == TIMING_permanent_after_death) ? 0 : $fx_duration(~%immunity_id%~)
	SET immunity_probability1 = $fx_probability1(~%immunity_id%~)
	SET immunity_probability2 = $fx_probability2(~%immunity_id%~)
	SET immunity_dice_count = $fx_dice_count(~%immunity_id%~)
	SET immunity_dice_sides = $fx_dice_sides(~%immunity_id%~)
	SET immunity_save_type = $fx_save_type(~%immunity_id%~)
	SET immunity_save_bonus = (immunity_save_type == 0) ? 0 : $fx_save_bonus(~%immunity_id%~)
	SPRINT immunity_key ~%immunity_key_scope% %immunity_class% %immunity_external% %immunity_timing% %immunity_duration% %immunity_probability1% %immunity_probability2% %immunity_dice_count% %immunity_dice_sides% %immunity_save_type% %immunity_save_bonus%~
END

// L'immunité immunity_id (classe et clé de ad_immunity_class) est-elle dans une ligne unique ?
DEFINE_PATCH_MACRO ad_immunity_merged BEGIN
	SET immunity_merged = AD_ENABLE_SHRINKAGE AND AD_SHRINK_IMMUNITIES_SINGLE_LINE AND immunity_class > 0
		AND VARIABLE_IS_SET $immunity_key_count(~%immunity_key%~)
	PATCH_IF immunity_merged BEGIN
		SET immunity_merged = $immunity_key_count(~%immunity_key%~) > 1
	END
END

DEFINE_PATCH_MACRO ad_immunity_label BEGIN
	SET immunity_label_tra = 8030000 + $fx_immunity_label(~%immunity_id%~)
	LPF ad_tra INT_VAR tra_id = immunity_label_tra RET immunity_label = text END
END
