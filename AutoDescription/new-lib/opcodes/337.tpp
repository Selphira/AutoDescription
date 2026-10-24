// Opcode 337 (Remove: Opcode) : « Dissipe les effets de charme sur la cible » ; nom des effets de
// l'opcode parameter2, ou parameter1 pour les immunités à un opcode (101) ; code commun dans
// new-lib/opcodes/states.tpp.

// Refus : opcode sans nom (l'ancien moteur n'écrit alors rien).
DEFINE_PATCH_MACRO ad_op_337_support BEGIN
	PHP_EACH fx_ids_337 AS _ => remove_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET remove_opcode = $fx_parameter2(~%remove_id%~)
			PATCH_IF remove_opcode == 101 AND $fx_parameter1(~%remove_id%~) >= 0 BEGIN
				SET remove_opcode = $fx_parameter1(~%remove_id%~)
			END
			SET remove_tra = 8160000 + remove_opcode
			SPRINT remove_name ~~
			PATCH_IF remove_opcode >= 0 AND remove_opcode <= 999 AND TRA_ENTRY_EXISTS (~%remove_tra%~) BEGIN
				LPF ad_tra INT_VAR tra_id = remove_tra tra_block_start = 8160000 tra_block_size = 1000 RET remove_name = text END // ~les effets de charme~ (@8160005)
			END
			SPRINT $fx_remove_name(~%remove_id%~) ~%remove_name%~
			PATCH_IF ~%remove_name%~ STRING_EQUAL ~~ AND NOT support_header_only BEGIN
				LPF ad_refusal INT_VAR fx_id = remove_id STR_VAR reason = ~not_implemented:opcode337:name~ message = ~effects of opcode %remove_opcode% have no name~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_337_lines BEGIN
	SET state_opcode = 337
	SPRINT state_variant_macro ~ad_op_337_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_337_variant BEGIN
	SPRINT opcodeStr $fx_remove_name(~%line_fx%~)
END
