// Code commun des objets créés dans l'inventaire (opcodes 122 et 255) : parameter1 exemplaires de
// l'objet resource, un seul si l'objet ne s'empile pas ou si parameter1 vaut 0 : « Crée 5 « Bille +4 »
// dans l'inventaire du porteur ». Les macros ad_op_<N>_* fixent create_opcode (et create_phrase pour
// les lignes) puis appellent les macros ci-dessous.

// Refus : ressource vide (écartée par l'ancien opcode_resref_is_valid), trésor aléatoire (l'ancien
// moteur énumère les objets possibles), objet sans nom (aucune ligne).
DEFINE_PATCH_MACRO ad_create_item_support BEGIN
	FOR (create_id = 0; create_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++create_id) BEGIN
		PATCH_IF $fx_opcode(~%create_id%~) == create_opcode BEGIN
			SPRINT create_resref $fx_resource(~%create_id%~)
			LPF ad_item_is_random_treasure STR_VAR resref = ~%create_resref%~ RET create_random = random END
			LPF ad_item_info STR_VAR resref = ~%create_resref%~ RET create_name = name create_stackable = stackable END
			PATCH_IF ~%create_resref%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = create_id STR_VAR reason = ~file_error:opcode%create_opcode%:invalid~ message = ~empty resource field~ RET render_missing = refusal END
			END
			ELSE PATCH_IF create_random BEGIN
				LPF ad_refusal INT_VAR fx_id = create_id STR_VAR reason = ~not_implemented:opcode%create_opcode%:random_treasure~ message = ~random treasure %create_resref%~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ~%create_name%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF FILE_EXISTS_IN_GAME ~%create_resref%.itm~ BEGIN
					LPF ad_refusal INT_VAR fx_id = create_id STR_VAR reason = ~not_implemented:opcode%create_opcode%:no_name~ message = ~item %create_resref%.ITM has no name~ RET render_missing = refusal END
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = create_id STR_VAR reason = ~file_error:opcode%create_opcode%:missing_item~ message = ~item %create_resref%.ITM does not exist~ RET render_missing = refusal END
				END
			END
			ELSE BEGIN
				SET create_amount = $fx_parameter1(~%create_id%~)
				SPRINT $fx_item_name(~%create_id%~) ~%create_name%~
				SET $fx_item_amount(~%create_id%~) = (create_stackable AND create_amount != 0) ? create_amount : 1
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_create_item_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%create_opcode%~)
	FOR (create_id = 0; create_id < fx_count; ++create_id) BEGIN
		PATCH_IF $fx_opcode(~%create_id%~) == create_opcode AND NOT $fx_consumed(~%create_id%~) BEGIN
			SPRINT itemName $fx_item_name(~%create_id%~)
			SET amount = $fx_item_amount(~%create_id%~)
			SET line_phrase = create_phrase
			SET line_fx = create_id
			LPM ad_effect_line
		END
	END
END
