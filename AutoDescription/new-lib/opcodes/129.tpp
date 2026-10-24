// Opcode 129 (State: Aid) : « Aide (+1) (non cumulatif) » ; comme pour l'opcode 130, le jeu ne lit que
// le premier octet de parameter1 pour les jets de sauvegarde, le TAC0 et les dégâts, et l'effet ne se
// cumule pas (ancien opcode_not_cumulative, ajouté au texte avant la durée, une seule fois après un
// 321 sur la ressource elle-même).

// Refus : parameter1 hors de 0-255, dont les points de vie gagnés (lus sur quatre octets, IESDP)
// différeraient du bonus écrit ; parameter2 d'un EFF, nombre exact de points de vie gagnés (IESDP),
// que l'ancien moteur ne lit pas.
DEFINE_PATCH_MACRO ad_op_129_support BEGIN
	PHP_EACH fx_ids_129 AS _ => aid_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET aid_value = $fx_parameter1(~%aid_id%~)
			SET aid_hit_points = $fx_parameter2(~%aid_id%~)
			PATCH_IF aid_value < 0 OR aid_value > 255 BEGIN
				LPF ad_refusal INT_VAR fx_id = aid_id STR_VAR reason = ~not_implemented:opcode129:value~ message = ~bonus %aid_value% outside 0-255 (hit points read from the four bytes)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_external(~%aid_id%~) AND aid_hit_points != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = aid_id STR_VAR reason = ~not_implemented:opcode129:eff_hit_points~ message = ~exact hit points %aid_hit_points% (parameter2 of an EFF file)~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_129_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~129~)
	PHP_EACH fx_ids_129 AS _ => aid_id BEGIN
		PATCH_IF NOT $fx_consumed(~%aid_id%~) BEGIN
			LPF ad_signed_value INT_VAR value = $fx_parameter1(~%aid_id%~) RET value = text END
			SPRINT aid_not_cumulative @4000010 // ~non cumulatif~
			SPRINT line_suffix ~(%aid_not_cumulative%)~
			SET line_fx = aid_id
			SET $fx_not_cumulative(~%aid_id%~) = 0
			SET line_phrase = 21290100 // ~Aide (%value%)~
			LPM ad_effect_line
		END
	END
END
