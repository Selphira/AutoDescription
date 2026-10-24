// Opcode 212 (Protection: Freedom) : « Libère les créatures dans la zone d'effet des effets de
// l'emprisonnement et du labyrinthe » (IESDP : retire les opcodes 211 et 213) ; pas de forme « soi »,
// comme dans l'ancien moteur ; code commun dans new-lib/opcodes/states.tpp.

// Refus : effet qui ne vise pas toutes les créatures de la zone (cible 4), que la phrase nomme
// pourtant.
DEFINE_PATCH_MACRO ad_op_212_support BEGIN
	PHP_EACH fx_ids_212 AS _ => freedom_id BEGIN
		SET freedom_target = $fx_target(~%freedom_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND freedom_target != 4 AND NOT support_header_only BEGIN
			LPF ad_refusal INT_VAR fx_id = freedom_id STR_VAR reason = ~not_implemented:opcode212:target~ message = ~target %freedom_target% (the sentence names the creatures in the area of effect, target 4)~ RET render_missing = refusal END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_212_lines BEGIN
	SET state_opcode = 212
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
