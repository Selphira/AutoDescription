// Opcode 321 (Removal: Effects specified by Resource) : l'ancien moteur n'en écrit rien (macros
// opcode_*_321 vides) ; ses regroupements le retirent sans rien ajouter (immunités, 206), sauf
// avec un 146 qui lance le même sort, qu'il dit alors non cumulatif (opcode_146_group). Sur la
// ressource elle-même, avec une durée ou un autre timing que 0 (ancien load_opcode), il est écarté dès
// la lecture et les effets lus après lui dans son bloc sont « (non cumulatif) » (ad_effect_line,
// new-lib/application.tpp, hors AD_OPCODES_ALWAYS_CUMULATIVE).

// Au chargement (ad_fx_load_block, new-lib/effects.tpp) : fx_not_cumulative. Un 321 d'un EFF n'en
// est pas un : l'ancien moteur ne teste que l'opcode lu dans la ressource, avant de remplacer le 177.
DEFINE_PATCH_MACRO ad_fx_mark_not_cumulative BEGIN
	SET $fx_not_cumulative(~%fx_id%~) = fx_block_not_cumulative
	PATCH_IF $fx_opcode(~%fx_id%~) == 321 AND NOT $fx_external(~%fx_id%~) BEGIN
		SPRINT removal_resource $fx_resource(~%fx_id%~)
		PATCH_IF (~%removal_resource%~ STRING_EQUAL_CASE ~%ctx_resource%~)
				AND ($fx_timing(~%fx_id%~) != TIMING_duration OR $fx_duration(~%fx_id%~) != 0) BEGIN
			SET fx_block_not_cumulative = 1
			SET $fx_consumed(~%fx_id%~) = 1
			SET $fx_dropped(~%fx_id%~) = 1
		END
	END
END

// Prise en charge : ad_op_321_header_support pour l'en-tête d'un sort seul, ad_op_321_item_support
// sinon.
DEFINE_PATCH_MACRO ad_op_321_support BEGIN
	PATCH_IF support_header_only BEGIN
		LPM ad_op_321_header_support
	END
	ELSE BEGIN
		LPM ad_op_321_item_support
	END
END

// En-tête d'un sort seul (new-lib/spell_header.tpp) : l'ancien moteur garde le 321 parmi les effets de
// l'en-tête, sans rien en écrire, sauf s'il est vide (écarté, opcode_321_is_valid) ou si un 146 de
// même portée, lu après lui, lance le même sort avec les mêmes cible, timing, durée, résistance,
// probabilités, jet de sauvegarde et special (ancien opcode_146_group : le 321 disparaît, le 146 passe
// après les autres effets de son opcode). Une immunité au même sort le retire après les regroupements
// (ad_op_321_after_groups).
DEFINE_PATCH_MACRO ad_op_321_header_support BEGIN
	PHP_EACH fx_ids_321 AS _ => removal_id BEGIN
		PATCH_IF NOT $fx_consumed(~%removal_id%~) BEGIN
			SPRINT removal_resource $fx_resource_lower(~%removal_id%~)
			PATCH_IF ~%removal_resource%~ STRING_EQUAL ~~ BEGIN
				SET drop_id = removal_id
				SPRINT ignored_reason ~file_error:opcode321:invalid~
				SPRINT ignored_message ~empty resource field~
				LPM ad_application_drop
			END
			ELSE BEGIN
				SPRINT removal_scope $fx_scope(~%removal_id%~)
				PHP_EACH fx_ids_146 AS _ => removal_other BEGIN
					SPRINT removal_other_scope $fx_scope(~%removal_other%~)
					SPRINT removal_other_resource $fx_resource_lower(~%removal_other%~)
					PATCH_IF NOT $fx_consumed(~%removal_id%~) AND NOT $fx_consumed(~%removal_other%~)
							AND (~%removal_other_scope%~ STRING_EQUAL ~%removal_scope%~)
							AND (~%removal_other_resource%~ STRING_EQUAL ~%removal_resource%~)
							AND $fx_position(~%removal_other%~) > $fx_position(~%removal_id%~)
							AND $fx_target(~%removal_other%~) == $fx_target(~%removal_id%~)
							AND $fx_timing(~%removal_other%~) == $fx_timing(~%removal_id%~)
							AND $fx_duration(~%removal_other%~) == $fx_duration(~%removal_id%~)
							AND $fx_resistance(~%removal_other%~) == $fx_resistance(~%removal_id%~)
							AND $fx_probability1(~%removal_other%~) == $fx_probability1(~%removal_id%~)
							AND $fx_probability2(~%removal_other%~) == $fx_probability2(~%removal_id%~)
							AND $fx_save_type(~%removal_other%~) == $fx_save_type(~%removal_id%~)
							AND $fx_save_bonus(~%removal_other%~) == $fx_save_bonus(~%removal_id%~)
							AND $fx_special(~%removal_other%~) == $fx_special(~%removal_id%~) BEGIN
						SET $fx_consumed(~%removal_id%~) = 1
						SET $fx_late(~%removal_other%~) = 1
					END
				END
			END
		END
	END
END

// En-tête d'un sort seul, après les regroupements : un 321 disparaît si une immunité au même sort
// (206) de même portée reste (ancien opcode_206_post_group).
DEFINE_PATCH_MACRO ad_op_321_after_groups BEGIN
	PHP_EACH fx_ids_321 AS _ => removal_id BEGIN
		SPRINT removal_resource $fx_resource_lower(~%removal_id%~)
		SPRINT removal_scope $fx_scope(~%removal_id%~)
		PHP_EACH fx_ids_206 AS _ => removal_other BEGIN
			SPRINT removal_other_scope $fx_scope(~%removal_other%~)
			SPRINT removal_other_resource $fx_resource_lower(~%removal_other%~)
			PATCH_IF NOT $fx_consumed(~%removal_other%~) AND (~%removal_other_scope%~ STRING_EQUAL ~%removal_scope%~)
					AND (~%removal_other_resource%~ STRING_EQUAL ~%removal_resource%~) BEGIN
				SET $fx_consumed(~%removal_id%~) = 1
			END
		END
	END
END

// Ressource vide : écarté (opcode_321_is_valid) ; les autres sont écartés aussi, l'ancien moteur n'en
// écrivant rien. Refus : effet d'un EFF ; un 146 ou un 148 de la même portée lance ce sort.
DEFINE_PATCH_MACRO ad_op_321_item_support BEGIN
	PHP_EACH fx_ids_321 AS _ => removal_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%removal_id%~) BEGIN
			SPRINT removal_resource $fx_resource(~%removal_id%~)
			PATCH_IF $fx_external(~%removal_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = removal_id STR_VAR reason = ~not_implemented:opcode321:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF NOT (~%removal_resource%~ STRING_EQUAL ~~) BEGIN
				SPRINT removal_scope $fx_scope(~%removal_id%~)
				FOR (removal_other = 0; removal_other < fx_count; ++removal_other) BEGIN
					SET removal_other_opcode = $fx_opcode(~%removal_other%~)
					SPRINT removal_other_scope $fx_scope(~%removal_other%~)
					SPRINT removal_other_resource $fx_resource(~%removal_other%~)
					PATCH_IF (removal_other_opcode == 146 OR removal_other_opcode == 148) AND (~%removal_other_scope%~ STRING_EQUAL ~%removal_scope%~)
							AND (~%removal_other_resource%~ STRING_EQUAL_CASE ~%removal_resource%~) BEGIN
						LPF ad_refusal INT_VAR fx_id = removal_other STR_VAR reason = ~not_implemented:opcode321:cast_spell~ message = ~spell cast by opcode 146 or 148 and removed by opcode 321~ RET render_missing = refusal END
					END
				END
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
				SET drop_id = removal_id
				PATCH_IF ~%removal_resource%~ STRING_EQUAL ~~ BEGIN
					SPRINT ignored_reason ~file_error:opcode321:invalid~
					SPRINT ignored_message ~empty resource field~
				END
				LPM ad_application_drop
			END
		END
	END
END

// Aucune ligne : tous les effets sont écartés ou refusés.
DEFINE_PATCH_MACRO ad_op_321_lines BEGIN
END
