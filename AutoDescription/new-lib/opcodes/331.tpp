// Opcode 331 (Summon: Random Monster Summoning, EE) : invoque des créatures de la table resource, ou
// sinon de la table de la ligne parameter2 de SMTABLES.2DA (IESDP). Selon special (mode) : dans un
// sort ou un objet, 0 et 1 invoquent parameter1 + dés créatures (« Invoque 1d2 +1 créatures
// (Scarabée bombardier ou Scarabée scolyte) ») ; dans un EFF (177), 0 invoque jusqu'à un total de
// niveaux de puissance parameter1 ; 2 invoque jusqu'au niveau du lanceur. Créatures nommées de la
// table comme pour le 127 (ad_op_127_resource_table, new-lib/opcodes/127.tpp, ancien
// get_creatures_names).
//
// Comme l'ancien opcode_331_is_valid, un effet dont la table est absente est écarté, de même qu'un
// effet dont la ligne de SMTABLES.2DA n'existe pas, et, ce qui diffère de l'ancien moteur (« Invoque
// créatures »), un effet qui n'invoque aucune créature (ni nombre ni dé).
// Refus : special hors de 0-2 ; ceux de ad_op_127_resource_table.
DEFINE_PATCH_MACRO ad_op_331_support BEGIN
	SET monster_opcode = 331
	PHP_EACH fx_ids_331 AS _ => monster_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_dropped(~%monster_id%~) BEGIN
			SPRINT monster_resref $fx_resource(~%monster_id%~)
			SET monster_type = $fx_parameter2(~%monster_id%~)
			PATCH_IF ~%monster_resref%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~smtables.2da~ BEGIN
				INNER_PATCH_FILE ~smtables.2da~ BEGIN
					COUNT_2DA_ROWS 2 monster_rows
					// Ligne 0 : en-tête « 2DA V1.0 ».
					PATCH_IF monster_type >= 0 AND monster_type + 1 < monster_rows BEGIN
						READ_2DA_ENTRY (monster_type + 1) 1 2 monster_resref
					END
				END
			END
			PATCH_IF ~%monster_resref%~ STRING_EQUAL ~~ OR NOT FILE_EXISTS_IN_GAME ~%monster_resref%.2da~ BEGIN
				SET drop_id = monster_id
				SPRINT ignored_reason ~file_error:opcode331:no_table~
				SPRINT ignored_message ~no creature table (resource %monster_resref%, SMTABLES.2DA row %monster_type%)~
				LPM ad_application_drop
			END
			ELSE PATCH_IF NOT support_header_only BEGIN
				SET monster_mode = $fx_special(~%monster_id%~)
				SET monster_dice = $fx_dice_count(~%monster_id%~)
				SET monster_count = $fx_parameter1(~%monster_id%~) + ($fx_dice_sides(~%monster_id%~) > 1 ? 0 : monster_dice)
				PATCH_IF monster_mode < 0 OR monster_mode > 2 BEGIN
					LPF ad_refusal INT_VAR fx_id = monster_id STR_VAR reason = ~not_implemented:opcode331:mode~ message = ~special %monster_mode% (expected 0-2)~ RET render_missing = refusal END
				END
				// Sans dé ni nombre, rien n'est invoqué.
				ELSE PATCH_IF monster_mode != 2 AND monster_count <= 0 AND (monster_dice <= 0 OR $fx_dice_sides(~%monster_id%~) <= 1) BEGIN
					SET drop_id = monster_id
					SPRINT ignored_reason ~file_error:opcode331:no_creature~
					SPRINT ignored_message ~no creature summoned (count %monster_count%, no dice)~
					LPM ad_application_drop
				END
				ELSE BEGIN
					LPM ad_op_127_resource_table
				END
			END
		END
	END
END

// Phrase : 23 310 100 + 10 × variante + forme ; variante = 0 total de niveaux parameter1, 1 niveau
// du lanceur, 2 une créature, 3 plusieurs (parameter1 + dés, « 1 » seul étant une créature).
DEFINE_PATCH_MACRO ad_op_331_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~331~)
	PHP_EACH fx_ids_331 AS _ => monster_id BEGIN
		PATCH_IF NOT $fx_consumed(~%monster_id%~) BEGIN
			SET monster_mode = $fx_special(~%monster_id%~)
			SET amount = $fx_parameter1(~%monster_id%~)
			PATCH_IF monster_mode == 2 BEGIN
				SET monster_variant = 1
			END
			ELSE PATCH_IF monster_mode == 0 AND $fx_external(~%monster_id%~) BEGIN
				SET monster_variant = 0
			END
			ELSE BEGIN
				SET monster_dice = $fx_dice_count(~%monster_id%~)
				SET monster_sides = $fx_dice_sides(~%monster_id%~)
				// Un dé à une face compte comme un nombre, écrit sans « + » : « Invoque 3 créatures ».
				PATCH_IF monster_dice > 0 AND monster_sides > 1 BEGIN
					LPF ad_dice_text INT_VAR dice_count = monster_dice dice_sides = monster_sides bonus = amount RET amount = text END
				END
				ELSE PATCH_IF monster_dice > 0 BEGIN
					SET amount += monster_dice
				END
				SET monster_variant = ~%amount%~ STRING_EQUAL ~1~ ? 2 : 3
			END
			SPRINT creatures $fx_monster_creatures(~%monster_id%~)
			SET line_phrase = 23310100 + 10 * monster_variant // ~Invoque des créatures pour un total de %amount% niveaux (%creatures%)~
			SET line_fx = monster_id
			LPM ad_effect_line
		END
	END
END
