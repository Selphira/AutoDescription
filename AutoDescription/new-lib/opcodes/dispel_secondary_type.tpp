// Code commun des dissipations par type secondaire de sort (opcode 221, tous les sorts du type ;
// opcode 230, un seul sort), anciens opcode_self_221 et opcode_self_230 : « Dissipe tous les sorts de
// type Protection de combat sur la cible » ; jusqu'au niveau parameter1, « de niveau 8 ou inférieur »,
// sauf à partir du niveau 9. Type parameter2 nommé par ad_spell_secondary_type_name
// (new-lib/resources.tpp). Phrase : 2OOO 0100 avec un niveau, 0110 tous les niveaux (+ forme). Les
// macros ad_op_<N>_* fixent dispel_type_opcode puis appellent celles-ci.

// Refus : niveau négatif (l'ancien opcode_221_is_valid l'écarte) ; type sans nom (type 0, nommé en
// anglais mais pas en français ; type ajouté par un mod).
DEFINE_PATCH_MACRO ad_dispel_type_support BEGIN
	FOR (dispel_id = 0; dispel_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++dispel_id) BEGIN
		PATCH_IF $fx_opcode(~%dispel_id%~) == dispel_type_opcode AND NOT $fx_consumed(~%dispel_id%~) BEGIN
			LPF ad_spell_secondary_type_name INT_VAR secondary_type = $fx_parameter2(~%dispel_id%~) RET dispel_name = name END
			PATCH_IF $fx_parameter1(~%dispel_id%~) < 0 BEGIN
				SPRINT render_missing ~not_implemented:opcode%dispel_type_opcode%:invalid~
			END
			ELSE PATCH_IF ~%dispel_name%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode%dispel_type_opcode%:no_name~
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
	FOR (dispel_id = 0; dispel_id < fx_count; ++dispel_id) BEGIN
		PATCH_IF $fx_opcode(~%dispel_id%~) == dispel_type_opcode AND NOT $fx_consumed(~%dispel_id%~) BEGIN
			SPRINT spellSecondaryTypeName $fx_secondary_type_name(~%dispel_id%~)
			SET spellLevel = $fx_parameter1(~%dispel_id%~)
			SET line_fx = dispel_id
			SET line_phrase = 20000000 + dispel_type_opcode * 10000 + (spellLevel < 9 ? 100 : 110) // ~Dissipe tous les sorts de type %spellSecondaryTypeName% de niveau %spellLevel% ou inférieur sur %theTarget%~ (@22210100)
			LPM ad_effect_line
		END
	END
END
