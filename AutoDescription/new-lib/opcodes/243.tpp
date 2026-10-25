// Opcode 243 (Item: Drain Item Charges) : « Draine une charge aux objets magiques de la cible » ;
// parameter1 = charges drainées (EE) ; code commun dans new-lib/opcodes/states.tpp.

// Refus : jeu classique (l'ancien moteur y draine toutes les charges, non vérifié ; effet écarté pour ToB) ;
// total inférieur à 1 (écarté par l'ancien opcode_243_is_valid) ; objet précis (resource, IESDP), que
// l'ancien moteur ne nomme pas.
DEFINE_PATCH_MACRO ad_op_243_support BEGIN
	PHP_EACH fx_ids_243 AS _ => drain_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET drain_amount = $fx_parameter1(~%drain_id%~)
			SPRINT drain_item $fx_resource(~%drain_id%~)
			PATCH_IF NOT IS_EE BEGIN
				LPF ad_refusal INT_VAR fx_id = drain_id STR_VAR reason = ~not_implemented:opcode243:classic~ message = ~classic game~ RET render_missing = refusal END
			END
			ELSE PATCH_IF drain_amount < 1 BEGIN
				LPF ad_refusal INT_VAR fx_id = drain_id STR_VAR reason = ~file_error:opcode243:amount~ message = ~amount %drain_amount% (expected 1 or more)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF NOT (~%drain_item%~ STRING_EQUAL ~~) BEGIN
				LPF ad_refusal INT_VAR fx_id = drain_id STR_VAR reason = ~not_implemented:opcode243:item~ message = ~item %drain_item%~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_243_lines BEGIN
	SET state_opcode = 243
	SPRINT state_variant_macro ~ad_op_243_variant~
	LPM ad_state_lines
END

// Variante 1 : plusieurs charges.
DEFINE_PATCH_MACRO ad_op_243_variant BEGIN
	SET amount = $fx_parameter1(~%line_fx%~)
	SET state_variant = amount != 1
END
