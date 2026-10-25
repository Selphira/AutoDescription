// Opcode 71 (IDS: Sex Change) : parameter2 0 inverse le sexe de la cible (« Inverse le sexe du
// porteur ») ; 1 le fixe à la valeur parameter1 de gender.ids, nommée au singulier (liste
// @8099000) : « Change la cible en créature invoquée » ; code commun dans new-lib/opcodes/states.tpp.

// Un autre mode : l'ancien moteur écarte l'effet (opcode_71_is_valid). Refus : sexe fixé sans nom,
// à l'écriture de sa ligne : un emprisonnement retire celui qui l'accompagne (ad_group_imprisonment,
// new-lib/groups.tpp).
DEFINE_PATCH_MACRO ad_op_71_support BEGIN
	PHP_EACH fx_ids_71 AS _ => gender_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET gender_mode = $fx_parameter2(~%gender_id%~)
			PATCH_IF gender_mode != MOD_TYPE_flat AND gender_mode != MOD_TYPE_cumulative BEGIN
				SET drop_id = gender_id
				LPM ad_application_drop
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_71_lines BEGIN
	PHP_EACH fx_ids_71 AS _ => gender_id BEGIN
		SPRINT $fx_gender_name(~%gender_id%~) ~~
		SET gender_value = $fx_parameter1(~%gender_id%~)
		SET gender_tra = 8099000 + gender_value
		PATCH_IF NOT $fx_consumed(~%gender_id%~) AND $fx_parameter2(~%gender_id%~) == MOD_TYPE_flat BEGIN
			PATCH_IF gender_value >= 0 AND gender_value <= 255 AND TRA_ENTRY_EXISTS (~%gender_tra%~) BEGIN
				LPF ad_tra INT_VAR tra_id = gender_tra tra_block_start = 8099000 tra_block_size = 256 RET gender_name = text END // ~créature invoquée~ (@8099006)
				SPRINT $fx_gender_name(~%gender_id%~) ~%gender_name%~
			END
			ELSE BEGIN
				LPF ad_refusal INT_VAR fx_id = gender_id STR_VAR reason = ~not_implemented:opcode71:gender_name~ message = ~value %gender_value% of gender.ids has no name~ RET render_late_missing = refusal END
			END
		END
	END
	SET state_opcode = 71
	SPRINT state_variant_macro ~ad_op_71_variant~
	LPM ad_state_lines
END

// Variante 0 : sexe inversé, 1 : sexe fixé (genderType).
DEFINE_PATCH_MACRO ad_op_71_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == MOD_TYPE_flat ? 1 : 0
	SPRINT genderType $fx_gender_name(~%line_fx%~)
END
