// Code commun des protections qui s'épuisent (opcodes 223, 226, 227, 228) : parameter1 = total de
// niveaux, diminué de la puissance du premier sort bloqué ou renvoyé ; parameter2 = école (223, 227)
// ou type secondaire (226, 228) (IESDP) : « Immunise jusqu'à 2 niveaux de sorts de type Attaque
// magique », « Renvoie jusqu'à 3 niveaux de sorts de l'école de l'Illusion ». L'opcode fixe
// decrement_opcode, decrement_by_school (1 : école) et, pour ses lignes, decrement_variant_macro (vide
// sans variante) ; phrases du code commun des états (new-lib/opcodes/states.tpp).

// Total inférieur à 1 sur un jeu classique : écarté et journalisé (ancien opcode_<N>_is_valid). Refus :
// total inférieur à 1 sur EE (l'ancien moteur écrit « Lance ») ; sur EE, sort lancé à la fin de l'effet qui a un nom (la ressource, sinon le sort
// <ressource>B : l'ancien side_spell ajoute « puis lance « … » »). École ou type secondaire sans nom
// (ajouté par un mod) : comme l'ancien moteur, pas de ligne ; l'effet compte encore pour l'en-tête,
// journalisé.
DEFINE_PATCH_MACRO ad_decrement_support BEGIN
	SPRINT decrement_own_spell ~~
	PATCH_IF IS_EE AND STRING_LENGTH ~%ctx_resource%~ <= 7 BEGIN
		LPF ad_spell_name STR_VAR resref = EVAL ~%ctx_resource%B~ RET decrement_own_spell = name END
	END
	PHP_EACH ~fx_ids_%decrement_opcode%~ AS _ => decrement_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET decrement_kind = $fx_parameter2(~%decrement_id%~)
			SPRINT decrement_kind_name ~~
			PATCH_IF NOT decrement_by_school BEGIN
				LPF ad_spell_secondary_type_name INT_VAR secondary_type = decrement_kind RET decrement_kind_name = name END
			END
			ELSE PATCH_IF decrement_kind >= 1 AND decrement_kind <= 10 BEGIN
				LPF ad_tra INT_VAR tra_id = 8150000 + decrement_kind tra_block_start = 8150000 tra_block_size = 11 RET decrement_kind_name = text END // ~de l'Illusion~ (@8150005)
			END
			SPRINT $fx_decrement_name(~%decrement_id%~) ~%decrement_kind_name%~
			SPRINT decrement_resref $fx_resource(~%decrement_id%~)
			SPRINT decrement_spell ~%decrement_own_spell%~
			PATCH_IF NOT (~%decrement_resref%~ STRING_EQUAL ~~) BEGIN
				LPF ad_spell_name STR_VAR resref = ~%decrement_resref%~ RET decrement_spell = name END
			END
			PATCH_IF $fx_parameter1(~%decrement_id%~) < 1 BEGIN
				// Sur EE, l'ancien moteur ne l'écarte pas : effet en jeu non établi.
				PATCH_IF IS_EE BEGIN
					LPF ad_refusal INT_VAR fx_id = decrement_id STR_VAR reason = ~not_implemented:opcode%decrement_opcode%:amount~ message = ~amount of 0 or less on enhanced editions~ RET render_missing = refusal END
				END
				ELSE BEGIN
					SET drop_id = decrement_id
					SPRINT ignored_reason ~file_error:opcode%decrement_opcode%:amount~
					SPRINT ignored_message ~amount of 0 or less~
					LPM ad_application_drop
				END
			END
			ELSE PATCH_IF ~%decrement_kind_name%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF NOT support_header_only BEGIN
					SET ignored_fx = decrement_id
					SPRINT ignored_reason ~not_implemented:opcode%decrement_opcode%:no_name~
					SPRINT ignored_message ~secondary type %decrement_kind% has no name~
					PATCH_IF decrement_by_school BEGIN
						SPRINT ignored_message ~school %decrement_kind% has no name~
					END
					LPM ad_log_ignored
				END
			END
			ELSE PATCH_IF IS_EE AND NOT (~%decrement_spell%~ STRING_EQUAL ~~) BEGIN
				LPF ad_refusal INT_VAR fx_id = decrement_id STR_VAR reason = ~not_implemented:opcode%decrement_opcode%:spell~ message = ~spell cast when the effect ends~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_decrement_lines BEGIN
	PHP_EACH ~fx_ids_%decrement_opcode%~ AS _ => decrement_id BEGIN
		SPRINT decrement_kind_name $fx_decrement_name(~%decrement_id%~)
		PATCH_IF ~%decrement_kind_name%~ STRING_EQUAL ~~ BEGIN
			SET $fx_consumed(~%decrement_id%~) = 1
		END
	END
	SET state_opcode = decrement_opcode
	SPRINT state_variant_macro ~ad_decrement_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_decrement_variant BEGIN
	SET amount = $fx_parameter1(~%line_fx%~)
	SPRINT spellSchoolName $fx_decrement_name(~%line_fx%~)
	SPRINT spellSecondaryTypeName $fx_decrement_name(~%line_fx%~)
	PATCH_IF NOT (~%decrement_variant_macro%~ STRING_EQUAL ~~) BEGIN
		LPM ~%decrement_variant_macro%~
	END
END
