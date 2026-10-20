// Opcode 100 (Protection: from Creature Type) : immunise contre les attaques et les sorts des
// créatures de la valeur parameter1 du fichier IDS parameter2 (ad_ids_name, new-lib/resources.tpp) :
// « Immunité aux attaques et aux sorts des morts-vivants » ; valeur 0 : de toutes les créatures.
// Code commun dans new-lib/opcodes/states.tpp.

// Refus : fichier hors de 2-8 et valeur 100 de ea.ids (écartés par l'ancien opcode_idscheck8_is_valid) ;
// valeur sans nom.
DEFINE_PATCH_MACRO ad_op_100_support BEGIN
	FOR (versus_id = 0; versus_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++versus_id) BEGIN
		PATCH_IF $fx_opcode(~%versus_id%~) == 100 BEGIN
			SET versus_file = $fx_parameter2(~%versus_id%~)
			SET versus_value = $fx_parameter1(~%versus_id%~)
			LPF ad_ids_name INT_VAR ids_file = versus_file entry = versus_value RET versus_name = name END
			SPRINT $fx_versus_name(~%versus_id%~) ~%versus_name%~
			PATCH_IF versus_file < 2 OR versus_file > 8 OR (versus_file == 2 AND versus_value == 100) BEGIN
				SPRINT render_missing ~not_implemented:opcode100:ids_file~
			END
			ELSE PATCH_IF versus_value != 0 AND ~%versus_name%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode100:ids_name~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_100_lines BEGIN
	SET state_opcode = 100
	SPRINT state_variant_macro ~ad_op_100_variant~
	LPM ad_state_lines
END

// Variante 0 : créatures nommées, 1 : toutes les créatures.
DEFINE_PATCH_MACRO ad_op_100_variant BEGIN
	SET state_variant = $fx_parameter1(~%line_fx%~) == 0 ? 1 : 0
	SPRINT creatureType $fx_versus_name(~%line_fx%~)
END
