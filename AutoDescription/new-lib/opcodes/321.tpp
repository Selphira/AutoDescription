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

// Ressource vide : écarté (opcode_321_is_valid). Refus : effet d'un EFF ; un 146 ou un 148 de la même
// portée lance ce sort.
DEFINE_PATCH_MACRO ad_op_321_support BEGIN
	FOR (removal_id = 0; removal_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++removal_id) BEGIN
		PATCH_IF $fx_opcode(~%removal_id%~) == 321 AND NOT $fx_consumed(~%removal_id%~) BEGIN
			SPRINT removal_resource $fx_resource(~%removal_id%~)
			PATCH_IF $fx_external(~%removal_id%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode321:external~
			END
			ELSE PATCH_IF NOT (~%removal_resource%~ STRING_EQUAL ~~) BEGIN
				SPRINT removal_scope $fx_scope(~%removal_id%~)
				FOR (removal_other = 0; removal_other < fx_count; ++removal_other) BEGIN
					SET removal_other_opcode = $fx_opcode(~%removal_other%~)
					SPRINT removal_other_scope $fx_scope(~%removal_other%~)
					SPRINT removal_other_resource $fx_resource(~%removal_other%~)
					PATCH_IF (removal_other_opcode == 146 OR removal_other_opcode == 148) AND (~%removal_other_scope%~ STRING_EQUAL ~%removal_scope%~)
							AND (~%removal_other_resource%~ STRING_EQUAL_CASE ~%removal_resource%~) BEGIN
						SPRINT render_missing ~not_implemented:opcode321:cast_spell~
					END
				END
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
				SET drop_id = removal_id
				LPM ad_application_drop
			END
		END
	END
END

// Aucune ligne : tous les effets sont écartés ou refusés.
DEFINE_PATCH_MACRO ad_op_321_lines BEGIN
END
