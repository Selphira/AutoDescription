// Code commun des dissipations par type secondaire de sort (opcode 221, tous les sorts du type ;
// opcode 230, un seul sort), anciens opcode_self_221 et opcode_self_230 : « Dissipe tous les sorts de
// type Protection de combat sur la cible » ; jusqu'au niveau parameter1, « de niveau 8 ou inférieur »,
// sauf à partir du niveau 9. Type parameter2 nommé par ad_spell_secondary_type_name
// (new-lib/resources.tpp). Phrase : 2OOO 0100 avec un niveau, 0110 tous les niveaux (+ forme). Les
// macros ad_op_<N>_* fixent dispel_type_opcode puis appellent celles-ci.

// Refus : niveau négatif (l'ancien opcode_221_is_valid l'écarte) ; type sans nom (type 0, nommé en
// anglais mais pas en français ; type ajouté par un mod).
DEFINE_PATCH_MACRO ad_dispel_type_support BEGIN
	PHP_EACH ~fx_ids_%dispel_type_opcode%~ AS _ => dispel_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%dispel_id%~) BEGIN
			LPF ad_spell_secondary_type_name INT_VAR secondary_type = $fx_parameter2(~%dispel_id%~) RET dispel_name = name END
			PATCH_IF $fx_parameter1(~%dispel_id%~) < 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = dispel_id STR_VAR reason = ~file_error:opcode%dispel_type_opcode%:invalid~ message = ~negative secondary type~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ~%dispel_name%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = dispel_id STR_VAR reason = ~not_implemented:opcode%dispel_type_opcode%:no_name~ message = ~secondary type has no name~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SPRINT $fx_secondary_type_name(~%dispel_id%~) ~%dispel_name%~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_dispel_type_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%dispel_type_opcode%~)
	PHP_EACH ~fx_ids_%dispel_type_opcode%~ AS _ => dispel_id BEGIN
		PATCH_IF NOT $fx_consumed(~%dispel_id%~) BEGIN
			SPRINT spellSecondaryTypeName $fx_secondary_type_name(~%dispel_id%~)
			SET spellLevel = $fx_parameter1(~%dispel_id%~)
			SET line_fx = dispel_id
			SET line_phrase = 20000000 + dispel_type_opcode * 10000 + (spellLevel < 9 ? 100 : 110) // ~Dissipe tous les sorts de type %spellSecondaryTypeName% de niveau %spellLevel% ou inférieur sur %theTarget%~ (@22210100)
			LPM ad_effect_line
		END
	END
END
