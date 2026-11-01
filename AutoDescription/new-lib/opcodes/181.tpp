// Opcode 181 (Item: Can't Use Itemtype) : la cible ne peut plus utiliser les objets du type
// parameter1 (IESDP ; parameter2 sur un jeu classique, comme l'ancien opcode_self_181) : « Empêche
// d'utiliser les robes ». L'ancien moteur n'a de phrase qu'à la forme « soi » ; les autres sont
// refusées (ad_effect_line). Code commun dans new-lib/opcodes/states.tpp.

// Type hors de 0-73 : écarté et journalisé (ancien opcode_181_is_valid) ; type sans nom : aucune
// ligne, journalisé, l'effet compte encore pour l'en-tête.
DEFINE_PATCH_MACRO ad_op_181_support BEGIN
	PHP_EACH fx_ids_181 AS _ => item_type_id BEGIN
		SET item_type = IS_EE ? $fx_parameter1(~%item_type_id%~) : $fx_parameter2(~%item_type_id%~)
		LPF ad_item_type_name INT_VAR item_type RET item_type_name = name END
		SPRINT $fx_item_type_name(~%item_type_id%~) ~%item_type_name%~
		PATCH_IF NOT $fx_dropped(~%item_type_id%~) AND (item_type < 0 OR item_type > 73) BEGIN
			SET drop_id = item_type_id
			SPRINT ignored_reason ~file_error:opcode181:type~
			SPRINT ignored_message ~item type %item_type% (expected 0-73)~
			LPM ad_application_drop
		END
		ELSE PATCH_IF NOT $fx_dropped(~%item_type_id%~) AND ~%item_type_name%~ STRING_EQUAL ~~ AND NOT support_header_only BEGIN
			SET ignored_fx = item_type_id
			SPRINT ignored_reason ~not_implemented:opcode181:no_name~
			SPRINT ignored_message ~item type %item_type% has no name~
			LPM ad_log_ignored
		END
	END
END

DEFINE_PATCH_MACRO ad_op_181_lines BEGIN
	PHP_EACH fx_ids_181 AS _ => item_type_id BEGIN
		SPRINT item_type_name $fx_item_type_name(~%item_type_id%~)
		PATCH_IF ~%item_type_name%~ STRING_EQUAL ~~ BEGIN
			SET $fx_consumed(~%item_type_id%~) = 1
		END
	END
	SET state_opcode = 181
	SPRINT state_variant_macro ~ad_op_181_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_181_variant BEGIN
	SPRINT itemType $fx_item_type_name(~%line_fx%~)
END
