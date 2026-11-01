// Opcode 108 (Stat: Reputation) : réputation du personnage, modificateur simple, code commun dans
// new-lib/opcodes/stat_modifiers.tpp ; sur EE, parameter2 3 à 5 modifient de même la réputation du
// groupe (IESDP). Comme l'ancien opcode_108_common, une valeur fixée inférieure à 10 vaut 10.

DEFINE_PATCH_MACRO ad_op_108_support BEGIN
	PHP_EACH fx_ids_108 AS _ => stat_id BEGIN
		SET reputation_mode = $fx_parameter2_raw(~%stat_id%~)
		SET $fx_reputation_party(~%stat_id%~) = IS_EE AND reputation_mode >= 3 AND reputation_mode <= 5
		PATCH_IF $fx_reputation_party(~%stat_id%~) BEGIN
			SET reputation_mode -= 3
			SET $fx_parameter2(~%stat_id%~) = reputation_mode
			SPRINT $fx_stat_subject(~%stat_id%~) ~party~
		END
		PATCH_IF reputation_mode == MOD_TYPE_flat AND $fx_parameter1(~%stat_id%~) < 10 BEGIN
			SET $fx_parameter1(~%stat_id%~) = 10
		END
	END
	SET stat_opcode = 108
	SPRINT stat_mode_3 ~invalid~
	LPM ad_stat_modifier_support
END

DEFINE_PATCH_MACRO ad_op_108_lines BEGIN
	SET stat_opcode = 108
	SPRINT stat_line_macro ~ad_op_108_line~
	LPM ad_stat_modifier_lines
END

DEFINE_PATCH_MACRO ad_op_108_line BEGIN
	PATCH_IF $fx_reputation_party(~%line_fx%~) BEGIN
		SET stat_name_tra = 21080003 // ~Réputation du groupe~
	END
END
