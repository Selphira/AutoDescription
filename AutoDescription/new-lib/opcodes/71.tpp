// Opcode 71 (IDS: Sex Change) : parameter2 0 inverse le sexe de la cible (« Inverse le sexe du
// porteur ») ; 1 le fixe à la valeur parameter1 de gender.ids ; code commun dans
// new-lib/opcodes/states.tpp.

// Un autre mode : l'ancien moteur écarte l'effet (opcode_71_is_valid). Refus : sexe fixé (le nom au
// singulier n'est pas encore repris), à l'écriture de sa ligne : un emprisonnement retire celui qui
// l'accompagne (ad_group_imprisonment, new-lib/groups.tpp).
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
		PATCH_IF NOT $fx_consumed(~%gender_id%~) AND $fx_parameter2(~%gender_id%~) == MOD_TYPE_flat BEGIN
			LPF ad_refusal INT_VAR fx_id = gender_id STR_VAR reason = ~not_implemented:opcode71:gender_set~ message = ~gender set to a given value~ RET render_late_missing = refusal END
		END
	END
	SET state_opcode = 71
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
