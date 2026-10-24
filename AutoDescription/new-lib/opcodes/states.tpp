// États, soins et autres effets à phrase fixe : états (opcodes 3, 13, 16, 20, 24, 38, 39, 40, 45,
// 63, 74, 76, 80, 109, 128, 134, 165, 175, 185, 210, 211, 213, 217, 231, 247, 317), morts (209, 238),
// soins et dissipations (2, 4, 11, 32, 43, 46, 47, 48, 58, 75, 77,
// 79, 81, 116, 161-164), capacité ajoutée (171), drain de niveaux (216), point de rupture de moral (106), charme (5, 241),
// inversion de l'alignement (56) et du sexe (71), protection contre un type de créature (100),
// métamorphose (135), remplacement d'une créature (151), peau de pierre (218), téléportation auprès
// d'un ennemi (274) ; une phrase par variante de l'opcode, « Réduit la cible au silence ».
// Chaque fichier d'opcode fixe state_opcode et state_variant_macro (vide si l'opcode n'a qu'une
// variante) ; cette macro choisit state_variant pour l'effet line_fx et peut fixer line_condition,
// line_suffix ou line_no_duration.
// Phrase : 20 000 000 + opcode × 10 000 + 100 + 10 × variante, plus la forme (ad_effect_line,
// new-lib/application.tpp).

// Une ligne par effet non consommé, dans l'ordre du fichier (ancien opcode_<self|target>[_probability]_N).
DEFINE_PATCH_MACRO ad_state_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%state_opcode%~)
	PHP_EACH ~fx_ids_%state_opcode%~ AS _ => state_id BEGIN
		PATCH_IF NOT $fx_consumed(~%state_id%~) BEGIN
			SET line_fx = state_id
			SET state_variant = 0
			PATCH_IF NOT (~%state_variant_macro%~ STRING_EQUAL ~~) BEGIN
				LPM ~%state_variant_macro%~
			END
			SET line_phrase = 20000000 + state_opcode * 10000 + 100 + 10 * state_variant
			LPM ad_effect_line
		END
	END
END

// Paralysies (opcodes 109, 175, 185 : hold_opcode) : parameter1 non nul paralyse un type de créature,
// valeur du fichier IDS parameter2, nommé (ancien opcode_self_109 : « Paralyse les morts-vivants »).
// L'ancien moteur décrit le 109 comme une paralysie simple quand ce fichier est inhabituel ou, sur EE,
// quand special n'est pas nul (opcode_109_common) ; il écarte un 175 ou un 185 de fichier hors de 2-9
// (9 sur EE seulement) ou de valeur 100 d'ea.ids (opcode_idscheck9_is_valid). Refus : ces effets
// écartés ; type de créature sans nom (dont kit.ids).
DEFINE_PATCH_MACRO ad_hold_support BEGIN
	PHP_EACH ~fx_ids_%hold_opcode%~ AS _ => hold_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%hold_id%~) BEGIN
			SET hold_ids = $fx_parameter2(~%hold_id%~)
			SET hold_value = $fx_parameter1(~%hold_id%~)
			SET hold_invalid = hold_ids < 2 OR hold_ids > 9 OR (hold_ids == 9 AND NOT IS_EE)
			SET $fx_hold_plain(~%hold_id%~) = hold_value == 0
				OR (hold_opcode == 109 AND (hold_invalid OR (IS_EE AND $fx_special(~%hold_id%~) != 0)))
			SPRINT $fx_hold_name(~%hold_id%~) ~~
			PATCH_IF hold_opcode != 109 AND (hold_invalid OR (hold_ids == 2 AND hold_value == 100)) BEGIN
				LPF ad_refusal INT_VAR fx_id = hold_id STR_VAR reason = ~file_error:opcode%hold_opcode%:invalid~ message = ~IDS file %hold_ids% is not a creature type (expected 2-9: EA, GENERAL, RACE, CLASS, SPECIFIC, GENDER, ALIGN, KIT (enhanced editions))~ RET render_missing = refusal END
			END
			ELSE PATCH_IF NOT $fx_hold_plain(~%hold_id%~) AND NOT support_header_only BEGIN
				LPF ad_ids_name INT_VAR ids_file = hold_ids entry = hold_value RET hold_name = name END
				SPRINT $fx_hold_name(~%hold_id%~) ~%hold_name%~
				PATCH_IF ~%hold_name%~ STRING_EQUAL ~~ BEGIN
					LPF ad_refusal INT_VAR fx_id = hold_id STR_VAR reason = ~not_implemented:opcode%hold_opcode%:ids_name~ message = ~value %hold_value% of IDS file %hold_ids% has no name~ RET render_missing = refusal END
				END
			END
		END
	END
END

// Variante 1 : type de créature nommé (creatureType).
DEFINE_PATCH_MACRO ad_hold_variant BEGIN
	SET state_variant = $fx_hold_plain(~%line_fx%~) ? 0 : 1
	SPRINT creatureType $fx_hold_name(~%line_fx%~)
END
