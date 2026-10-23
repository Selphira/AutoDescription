// Opcode 235 (Spell Effect: Wing Buffet) : repousse ou attire la cible de parameter1 pieds, selon
// parameter2 (IESDP : 0 et 1 en s'éloignant du point visé, 2 de la source, 3 vers le point visé, 4
// vers la source ; autre valeur : comme 1) : « Repousse la cible à 6 mètres du porteur ». La source
// est le porteur, ou le buveur d'une potion. Phrase : 2235 0100 + 10 × (direction - 1) (+ forme).

// Refus : distance d'un mètre ou moins (ad_distance_text).
DEFINE_PATCH_MACRO ad_op_235_support BEGIN
	PHP_EACH fx_ids_235 AS _ => buffet_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%buffet_id%~) BEGIN
			LPF ad_distance_text INT_VAR feet = $fx_parameter1(~%buffet_id%~) RET buffet_range = text END
			PATCH_IF ~%buffet_range%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = buffet_id STR_VAR reason = ~not_implemented:opcode235:range~ message = ~no text for this distance~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_235_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~235~)
	LPF ad_tra INT_VAR tra_id = item_type == ITM_TYPE_potion ? 2000110 : 2000100 RET theSource = text END // ~le porteur~
	LPF ad_tra INT_VAR tra_id = item_type == ITM_TYPE_potion ? 2000111 : 2000101 RET ofTheSource = text END // ~du porteur~
	LPF ad_tra INT_VAR tra_id = item_type == ITM_TYPE_potion ? 2000112 : 2000102 RET toTheSource = text END // ~au porteur~
	PHP_EACH fx_ids_235 AS _ => buffet_id BEGIN
		PATCH_IF NOT $fx_consumed(~%buffet_id%~) BEGIN
			SET buffet_direction = $fx_parameter2(~%buffet_id%~)
			SET buffet_direction = buffet_direction < 1 OR buffet_direction > 4 ? 1 : buffet_direction
			LPF ad_distance_text INT_VAR feet = $fx_parameter1(~%buffet_id%~) RET range = text END
			SET line_fx = buffet_id
			SET line_phrase = 22350100 + 10 * (buffet_direction - 1) // ~Repousse %theTarget% à %range% de l'endroit visé~
			LPM ad_effect_line
		END
	END
END
