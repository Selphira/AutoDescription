// Opcode 180 (Item: Can't Use Item) : empêche d'équiper l'objet resource. Sur l'objet lui-même :
// « Unique : Un seul exemplaire peut être équipé », en tête des capacités d'équipement (rang 0).
// Un objet du même nom n'écrit rien, comme dans l'ancien moteur.

// Ressource vide ou parameter2 non nul : effet écarté sans rien écrire, erreur journalisée
// (comme l'ancien opcode_180_is_valid).
// Refus : objet
// d'un autre nom : l'ancien moteur y écrit le nom de l'objet décrit (BUG-031).
DEFINE_PATCH_MACRO ad_op_180_support BEGIN
	LPF ad_item_info STR_VAR resref = ~%ctx_resource%~ RET forbid_own_name = name END
	PHP_EACH fx_ids_180 AS _ => forbid_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SPRINT forbid_resref $fx_resource(~%forbid_id%~)
			SET $fx_forbid_unique(~%forbid_id%~) = ~%forbid_resref%~ STRING_EQUAL_CASE ~%ctx_resource%~
			LPF ad_item_info STR_VAR resref = ~%forbid_resref%~ RET forbid_name = name END
			PATCH_IF ~%forbid_resref%~ STRING_EQUAL ~~ OR $fx_parameter2(~%forbid_id%~) != 0 BEGIN
				PATCH_IF ~%forbid_resref%~ STRING_EQUAL ~~ BEGIN
					SET drop_id = forbid_id
					SPRINT ignored_reason ~file_error:opcode180:invalid~
					SPRINT ignored_message ~empty resource field~
					LPM ad_application_drop
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = forbid_id STR_VAR reason = ~not_implemented:opcode180:invalid~ message = ~parameter2 other than 0 not supported~ RET render_missing = refusal END
				END
			END
			ELSE PATCH_IF NOT $fx_forbid_unique(~%forbid_id%~) AND NOT (~%forbid_name%~ STRING_EQUAL ~~)
					AND NOT (~%forbid_name%~ STRING_EQUAL ~%forbid_own_name%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = forbid_id STR_VAR reason = ~not_implemented:opcode180:other_item~ message = ~forbidden item with another name (BUG-031)~ RET render_missing = refusal END
			END
		END
	END
END

// L'ancien moteur n'a de phrase qu'à la forme « soi ».
DEFINE_PATCH_MACRO ad_op_180_lines BEGIN
	SPRINT line_section ~equipped~
	PHP_EACH fx_ids_180 AS _ => forbid_id BEGIN
		PATCH_IF NOT $fx_consumed(~%forbid_id%~) AND $fx_forbid_unique(~%forbid_id%~) BEGIN
			SET line_sort = 0
			SET line_phrase = 21800100 // ~Unique%AD_COLON%Un seul exemplaire peut être équipé~
			SET line_fx = forbid_id
			LPM ad_effect_line
		END
	END
END
