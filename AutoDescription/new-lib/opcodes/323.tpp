// Opcode 323 (Stat: Turn Undead Level, EE) : niveau de repousser les morts-vivants, modificateur simple
// sans pourcentage (IESDP : modes 0 et 1), code commun dans new-lib/opcodes/stat_modifiers.tpp.
// Refus : special 1, qui ajoute à la valeur le plus haut niveau de la cible (IESDP ; l'ancien moteur
// n'en dit rien).

DEFINE_PATCH_MACRO ad_op_323_support BEGIN
	PHP_EACH fx_ids_323 AS _ => stat_id BEGIN
		SET turn_mode = $fx_special(~%stat_id%~)
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND turn_mode != 0 AND NOT support_header_only BEGIN
			LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:opcode323:mode~ message = ~mode (special) %turn_mode%: the highest level of the target is added~ RET render_missing = refusal END
		END
	END
	SET stat_opcode = 323
	SPRINT stat_mode_3 ~invalid~
	SPRINT stat_percentage ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_323_lines BEGIN
	SET stat_opcode = 323
	LPM ad_stat_modifier_lines
END
