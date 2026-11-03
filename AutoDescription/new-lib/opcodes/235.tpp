// Opcode 235 (Spell Effect: Wing Buffet) : repousse ou attire la cible selon parameter2 (IESDP : 0 et
// 1 en s'éloignant du point visé, 2 de la source, 3 vers le point visé, 4 vers la source ; autre
// valeur : comme 1) : « Repousse la cible loin du porteur ». parameter1 est la vitesse de la poussée,
// non une distance : elle n'est pas écrite. La source
// est le porteur, ou le buveur d'une potion. Phrase : 2235 0100 + 10 × (direction - 1) (+ forme).

DEFINE_PATCH_MACRO ad_op_235_support BEGIN
END

DEFINE_PATCH_MACRO ad_op_235_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~235~)
	LPM ad_application_source
	LPF ad_tra INT_VAR tra_id = source_tra     RET theSource = text END // ~le porteur~ (@2000100)
	LPF ad_tra INT_VAR tra_id = source_tra + 1 RET ofTheSource = text END // ~du porteur~ (@2000101)
	LPF ad_tra INT_VAR tra_id = source_tra + 2 RET toTheSource = text END // ~au porteur~ (@2000102)
	PHP_EACH fx_ids_235 AS _ => buffet_id BEGIN
		PATCH_IF NOT $fx_consumed(~%buffet_id%~) BEGIN
			SET buffet_direction = $fx_parameter2(~%buffet_id%~)
			SET buffet_direction = buffet_direction < 1 OR buffet_direction > 4 ? 1 : buffet_direction
			SET line_fx = buffet_id
			SET line_phrase = 22350100 + 10 * (buffet_direction - 1) // ~Repousse %theTarget% loin de l'endroit visé~
			LPM ad_effect_line
		END
	END
END
