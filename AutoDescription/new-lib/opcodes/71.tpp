// Opcode 71 (IDS: Sex Change) : parameter2 0 inverse le sexe de la cible (« Inverse le sexe du
// porteur ») ; 1 le fixe à la valeur parameter1 de gender.ids ; code commun dans
// new-lib/opcodes/states.tpp.

// Un autre mode : l'ancien moteur écarte l'effet (opcode_71_is_valid). Refus : sexe fixé (le nom au
// singulier n'est pas encore repris).
DEFINE_PATCH_MACRO ad_op_71_support BEGIN
	FOR (gender_id = 0; gender_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++gender_id) BEGIN
		PATCH_IF $fx_opcode(~%gender_id%~) == 71 BEGIN
			SET gender_mode = $fx_parameter2(~%gender_id%~)
			PATCH_IF gender_mode == MOD_TYPE_flat BEGIN
				LPF ad_refusal INT_VAR fx_id = gender_id STR_VAR reason = ~not_implemented:opcode71:gender_set~ message = ~gender set to a given value~ RET render_missing = refusal END
			END
			ELSE PATCH_IF gender_mode != MOD_TYPE_cumulative BEGIN
				SET drop_id = gender_id
				LPM ad_application_drop
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_71_lines BEGIN
	SET state_opcode = 71
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
