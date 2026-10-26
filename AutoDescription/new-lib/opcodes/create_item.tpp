// Code commun des objets créés dans l'inventaire (opcodes 122 et 255) : parameter1 exemplaires de
// l'objet resource, un seul si l'objet ne s'empile pas ou si parameter1 vaut 0 : « Crée 5 « Bille +4 »
// dans l'inventaire du porteur ». Les macros ad_op_<N>_* fixent create_opcode (et create_phrase pour
// les lignes) puis appellent les macros ci-dessous.

// Un trésor aléatoire RNDTRE01 à RNDTRE05 absent de rndtres.2da est nommé d'après sa qualité
// (ancien get_random_treasure_names, liste @8170000) : « trésor aléatoire de qualité exceptionnelle ».
// Ressource vide (comme l'ancien opcode_resref_is_valid) ou objet absent : effet écarté sans
// rien écrire, erreur journalisée.
// Refus : autre trésor aléatoire
// (l'ancien moteur énumère les objets possibles), objet sans nom (aucune ligne).
DEFINE_PATCH_MACRO ad_create_item_support BEGIN
	PHP_EACH ~fx_ids_%create_opcode%~ AS _ => create_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SPRINT create_resref $fx_resource(~%create_id%~)
			LPF ad_item_is_random_treasure STR_VAR resref = ~%create_resref%~ RET create_random = random create_listed = listed create_quality = quality END
			LPF ad_item_info STR_VAR resref = ~%create_resref%~ RET create_name = name create_stackable = stackable END
			PATCH_IF ~%create_resref%~ STRING_EQUAL ~~ BEGIN
				SET drop_id = create_id
				SPRINT ignored_reason ~file_error:opcode%create_opcode%:invalid~
				SPRINT ignored_message ~empty resource field~
				LPM ad_application_drop
			END
			ELSE PATCH_IF create_random AND NOT support_header_only BEGIN
				PATCH_IF NOT create_listed BEGIN
					LPF ad_tra INT_VAR tra_id = 8170000 + create_quality tra_block_start = 8170000 tra_block_size = 10 RET create_name = text END // ~trésor aléatoire de qualité exceptionnelle~ (@8170005)
					SPRINT $fx_item_name(~%create_id%~) ~%create_name%~
					SET $fx_item_amount(~%create_id%~) = 1
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = create_id STR_VAR reason = ~not_implemented:opcode%create_opcode%:random_treasure~ message = ~random treasure %create_resref% listed in RNDTRES.2DA~ RET render_missing = refusal END
				END
			END
			// En-tête d'un sort seul : seul compte un objet absent, que l'ancien moteur écarte.
			ELSE PATCH_IF ~%create_name%~ STRING_EQUAL ~~ AND (NOT support_header_only OR NOT FILE_EXISTS_IN_GAME ~%create_resref%.itm~) BEGIN
				PATCH_IF FILE_EXISTS_IN_GAME ~%create_resref%.itm~ BEGIN
					LPF ad_refusal INT_VAR fx_id = create_id STR_VAR reason = ~not_implemented:opcode%create_opcode%:no_name~ message = ~item %create_resref%.ITM has no name~ RET render_missing = refusal END
				END
				ELSE BEGIN
					SET drop_id = create_id
					SPRINT ignored_reason ~file_error:opcode%create_opcode%:missing_item~
					SPRINT ignored_message ~item %create_resref%.ITM does not exist~
					LPM ad_application_drop
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
	PHP_EACH ~fx_ids_%create_opcode%~ AS _ => create_id BEGIN
		PATCH_IF NOT $fx_consumed(~%create_id%~) BEGIN
			SPRINT itemName $fx_item_name(~%create_id%~)
			SET amount = $fx_item_amount(~%create_id%~)
			SET line_phrase = create_phrase
			SET line_fx = create_id
			LPM ad_effect_line
		END
	END
END
