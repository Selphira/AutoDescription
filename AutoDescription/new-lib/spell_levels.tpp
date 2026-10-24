// Section « PARAMÈTRES » d'un sort (ancien get_spell_effects_description et
// build_spell_effects_description, lib/spl/extended_effects.tpp), après l'en-tête
// (new-lib/spell_header.tpp) : lignes des effets restants de son unique en-tête, après la chaîne
// (ad_spell_header_pipeline). Un en-tête unique n'a pas de titre de niveau, même requis au-dessus
// du niveau 1 : l'ancien moteur n'en écrit qu'avec plusieurs niveaux.

// Lignes des opcodes décrits, puis lignes probables regroupées par plage (ancien
// group_probability_effects) ; refus d'une forme ou d'une cible sans texte (render_late_missing)
// et d'une ligne hors de la section de l'en-tête. Les opcodes écrivent leurs lignes dans l'ordre de
// leur premier effet restant (ad_spell_header_effects), comme l'ancien moteur depuis
// leveled_opcodes : à rang égal, l'ordre des lignes et celle qu'un doublon garde en dépendent ; les
// autres opcodes suivent, dans l'ordre numérique.
DEFINE_PATCH_MACRO ad_spell_statistics BEGIN
	// Clés propres à cet appel : une seconde description du sort les retrouverait (V36).
	SET statistics_call = VARIABLE_IS_SET statistics_call ? statistics_call + 1 : 1
	SET statistics_opcodes = 0
	FOR (statistics_n = 0; statistics_n < $spell_fx_count(~0~); ++statistics_n) BEGIN
		SET statistics_id = $spell_fx_0(~%statistics_n%~)
		SET statistics_opcode = $fx_opcode(~%statistics_id%~)
		PATCH_IF NOT VARIABLE_IS_SET $statistics_listed(~%statistics_call% %statistics_opcode%~) BEGIN
			SET $statistics_listed(~%statistics_call% %statistics_opcode%~) = 1
			SET $statistics_order(~%statistics_opcodes%~) = statistics_opcode
			SET statistics_opcodes += 1
		END
	END
	PHP_EACH fx_opcode_count AS statistics_opcode => _ BEGIN
		PATCH_IF NOT VARIABLE_IS_SET $statistics_listed(~%statistics_call% %statistics_opcode%~) BEGIN
			SET $statistics_listed(~%statistics_call% %statistics_opcode%~) = 1
			SET $statistics_order(~%statistics_opcodes%~) = statistics_opcode
			SET statistics_opcodes += 1
		END
	END
	FOR (statistics_k = 0; statistics_k < statistics_opcodes; ++statistics_k) BEGIN
		SET render_opcode = $statistics_order(~%statistics_k%~)
		LPM ad_opcode_is_described
		PATCH_IF opcode_described BEGIN
			LPM ~ad_op_%render_opcode%_lines~
		END
	END
	SPRINT render_missing ~%render_late_missing%~
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		SET statistics_probable = 0
		FOR (statistics_line = 0; statistics_line < line_count; ++statistics_line) BEGIN
			PATCH_IF $line_probability(~%statistics_line%~) > 0 BEGIN
				SET statistics_probable = 1
			END
		END
		PATCH_IF statistics_probable BEGIN
			SPRINT prob_section ~ability0~
			LPM ad_lines_probability_groups
			SPRINT render_missing ~%render_late_missing%~
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		FOR (statistics_line = 0; statistics_line < line_count; ++statistics_line) BEGIN
			SPRINT statistics_section $line_section(~%statistics_line%~)
			PATCH_IF NOT (~%statistics_section%~ STRING_EQUAL ~~) AND NOT (~%statistics_section%~ STRING_EQUAL ~ability0~) BEGIN
				LPF ad_refusal STR_VAR reason = ~not_implemented:spell:section~ message = ~line outside the section of the ability~ RET render_missing = refusal END
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPF ad_lines_section_text STR_VAR section = ~ability0~ RET statistics_lines = text END
		SPRINT title @1300000 // ~PARAMÈTRES~
		SPRINT description ~%description%%CRLF%%CRLF%%title%%AD_COLON%%CRLF%%statistics_lines%~
	END
	ELSE BEGIN
		SPRINT header_missing ~%render_missing%~
	END
END
