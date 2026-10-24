// Opcode 226 (Spell: Immunity (by Secondary Type, decrementing)) : « Immunise jusqu'à 2 niveaux de sorts
// de type Attaque magique » ; parameter1 = total de niveaux, diminué du niveau du premier sort bloqué,
// parameter2 = type secondaire (IESDP) ;
// code commun dans new-lib/opcodes/states.tpp.

// Refus : total inférieur à 1 (écarté par l'ancien opcode_226_is_valid sur un jeu classique,
// « Lance » sur EE) ; type secondaire sans nom (l'ancien moteur n'écrit rien) ; sur EE, sort lancé à la
// fin de l'effet qui a un nom (la ressource, sinon le sort <ressource>B : l'ancien side_spell ajoute
// « puis lance « … » »).
DEFINE_PATCH_MACRO ad_op_226_support BEGIN
	SPRINT immunity_own_spell ~~
	PATCH_IF IS_EE AND STRING_LENGTH ~%ctx_resource%~ <= 7 BEGIN
		LPF ad_spell_name STR_VAR resref = EVAL ~%ctx_resource%B~ RET immunity_own_spell = name END
	END
	PHP_EACH fx_ids_226 AS _ => immunity_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET immunity_type = $fx_parameter2(~%immunity_id%~)
			LPF ad_spell_secondary_type_name INT_VAR secondary_type = immunity_type RET immunity_type_name = name END
			SPRINT $fx_immunity_type_name(~%immunity_id%~) ~%immunity_type_name%~
			SPRINT immunity_resref $fx_resource(~%immunity_id%~)
			SPRINT immunity_spell ~%immunity_own_spell%~
			PATCH_IF NOT (~%immunity_resref%~ STRING_EQUAL ~~) BEGIN
				LPF ad_spell_name STR_VAR resref = ~%immunity_resref%~ RET immunity_spell = name END
			END
			PATCH_IF $fx_parameter1(~%immunity_id%~) < 1 BEGIN
				LPF ad_refusal INT_VAR fx_id = immunity_id STR_VAR reason = ~file_error:opcode226:amount~ message = ~amount of 0 or less~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ~%immunity_type_name%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = immunity_id STR_VAR reason = ~not_implemented:opcode226:secondary_type~ message = ~secondary type %immunity_type% has no name~ RET render_missing = refusal END
			END
			ELSE PATCH_IF IS_EE AND NOT (~%immunity_spell%~ STRING_EQUAL ~~) BEGIN
				LPF ad_refusal INT_VAR fx_id = immunity_id STR_VAR reason = ~not_implemented:opcode226:spell~ message = ~spell cast when the effect ends~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_226_lines BEGIN
	SET state_opcode = 226
	SPRINT state_variant_macro ~ad_op_226_variant~
	LPM ad_state_lines
END

// Variante 1 : total de 1, épuisé par le premier sort bloqué quel que soit son niveau (« Immunise contre
// le prochain sort de type Attaque magique »).
DEFINE_PATCH_MACRO ad_op_226_variant BEGIN
	SET amount = $fx_parameter1(~%line_fx%~)
	SPRINT spellSecondaryTypeName $fx_immunity_type_name(~%line_fx%~)
	SET state_variant = amount == 1
END
