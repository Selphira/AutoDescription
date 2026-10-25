// Opcode 283 (Use EFF File (Cursed)) : applique l'effet du fichier EFF resource, comme l'opcode 177
// (mêmes paramètres), effet qu'une délivrance des malédictions retire aussi (IESDP). Remplacé dès la
// lecture comme un 177 (ad_fx_substitute_177, new-lib/opcodes/177.tpp ; fx_cursed) ; la ligne de
// l'effet de l'EFF commence par « Malédiction : » (ad_effect_line, new-lib/application.tpp :
// « Malédiction : Aveugle la cible »).

// Refus : 283 non remplacé (raisons du 177).
DEFINE_PATCH_MACRO ad_op_283_support BEGIN
	SET substitute_parent = 283
	LPM ad_fx_substitution_support
END

// Refus : effet maudit réuni à d'autres par un regroupement, qui perdrait « Malédiction ».
DEFINE_PATCH_MACRO ad_op_283_lines BEGIN
	FOR (cursed_id = 0; cursed_id < fx_count; ++cursed_id) BEGIN
		PATCH_IF $fx_cursed(~%cursed_id%~) AND $fx_consumed(~%cursed_id%~) AND NOT $fx_dropped(~%cursed_id%~)
				AND $fx_identical_anchor(~%cursed_id%~) == cursed_id BEGIN
			LPF ad_refusal INT_VAR fx_id = cursed_id STR_VAR reason = ~not_implemented:opcode283:group~ message = ~cursed effect grouped with other effects~ RET render_late_missing = refusal END
		END
	END
END
