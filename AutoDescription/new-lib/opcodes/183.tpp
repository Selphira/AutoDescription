// Opcode 183 (Item: Apply Effect Itemtype, EE) : applique l'EFF resource à la cible quand elle équipe un
// objet du type parameter2 (IESDP). Vers un EFF qui protège seulement contre la ressource elle-même
// (318) : exception de cible des effets lus après lui dans son bloc (ad_fx_mark_target_exception,
// new-lib/opcodes/target_exceptions.tpp), « (Inefficace si l'équipement du porteur contient des robes
// ou des armures de cuir) » ; les types d'un même rang de probabilité réunis.

// Type d'objet sans nom : non écrit, journalisé, les autres restent. Refus : un autre EFF.
DEFINE_PATCH_MACRO ad_op_183_support BEGIN
	PHP_EACH fx_ids_183 AS _ => exception_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND (NOT $fx_consumed(~%exception_id%~) OR $fx_exception(~%exception_id%~)) BEGIN
			PATCH_IF NOT $fx_exception(~%exception_id%~) BEGIN
				SPRINT exception_resource $fx_resource(~%exception_id%~)
				LPF ad_refusal INT_VAR fx_id = exception_id STR_VAR reason = ~not_implemented:opcode183:effect~ message = ~EFF %exception_resource% applied when an item type is equipped~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET exception_value = $fx_parameter2(~%exception_id%~)
				SET exception_tra = 8180000 + exception_value
				SET exception_name_count = 0
				PATCH_IF exception_value >= 0 AND exception_value < 74 AND TRA_ENTRY_EXISTS (~%exception_tra%~) BEGIN
					LPF ad_tra INT_VAR tra_id = exception_tra tra_block_start = 8180000 tra_block_size = 74 RET exception_name = text END // ~robes~ (@8180067)
					PATCH_IF NOT (~%exception_name%~ STRING_EQUAL ~~) BEGIN
						SPRINT $fx_exception_name(~%exception_id%~ ~0~) ~%exception_name%~
						SET exception_name_count = 1
					END
				END
				PATCH_IF exception_name_count == 0 AND NOT support_header_only BEGIN
					SET ignored_fx = exception_id
					SPRINT ignored_reason ~not_implemented:opcode183:item_type_name~
					SPRINT ignored_message ~item type %exception_value% (parameter2) has no name~
					LPM ad_log_ignored
				END
				SPRINT $fx_exception_kind(~%exception_id%~) ~EQUIPPED~
				SET $fx_exception_name_count(~%exception_id%~) = exception_name_count
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_183_lines BEGIN
	SET exception_opcode = 183
	LPM ad_target_exception_lines
END
