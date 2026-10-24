// Opcode 220 (Removal: Remove School) : « Dissipe tous les sorts de l'école de l'Illusion de
// niveau 5 ou inférieur sur la cible », de tous niveaux à partir de 9 ; avec le 221 de l'illusion,
// « Dissipe toutes les illusions » (ad_group_all_illusions, new-lib/groups.tpp). Code commun dans
// new-lib/opcodes/states.tpp.

// Refus : école hors de 0-10 (l'ancien get_spell_school la ramène à 0) ou sans nom (0).
DEFINE_PATCH_MACRO ad_op_220_support BEGIN
	PHP_EACH fx_ids_220 AS _ => school_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET school = $fx_parameter2(~%school_id%~)
			SPRINT school_name ~~
			PATCH_IF school >= 0 AND school <= 10 BEGIN
				LPF ad_tra INT_VAR tra_id = 8150000 + school tra_block_start = 8150000 tra_block_size = 11 RET school_name = text END // ~de l'Illusion~ (@8150005)
			END
			SPRINT $fx_school_name(~%school_id%~) ~%school_name%~
			PATCH_IF ~%school_name%~ STRING_EQUAL ~~ AND NOT support_header_only BEGIN
				LPF ad_refusal INT_VAR fx_id = school_id STR_VAR reason = ~not_implemented:opcode220:school~ message = ~school %school% has no name (expected 1-10)~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_220_lines BEGIN
	SET state_opcode = 220
	SPRINT state_variant_macro ~ad_op_220_variant~
	LPM ad_state_lines
END

// Variante 0 : jusqu'au niveau parameter1, 1 : tous les niveaux (9 ou plus).
DEFINE_PATCH_MACRO ad_op_220_variant BEGIN
	SET spellLevel = $fx_parameter1(~%line_fx%~)
	SET state_variant = spellLevel >= 9
	SPRINT spellSchoolName $fx_school_name(~%line_fx%~)
END
