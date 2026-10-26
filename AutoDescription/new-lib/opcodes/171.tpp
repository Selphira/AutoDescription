// Opcode 171 (Spell: Give Innate Ability) : ajoute le sort resource (ancien opcode_171_common) :
// « Ajoute la capacité « Métamorphose forme naturelle » », ou « Ajoute le sort « … » dans le livre de
// sorts » pour un sort profane ou divin (type 1 ou 2). Code commun dans new-lib/opcodes/states.tpp.
// Avec AD_ENABLE_SHRINKAGE, une métamorphose peut le retirer (ad_group_polymorph, new-lib/groups.tpp).

// Sort absent : effet écarté sans rien écrire, erreur journalisée (l'ancien moteur n'écrit rien).
// Refus : sort sans nom.
DEFINE_PATCH_MACRO ad_op_171_support BEGIN
	PHP_EACH fx_ids_171 AS _ => ability_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%ability_id%~) BEGIN
			SPRINT ability_resref $fx_resource(~%ability_id%~)
			PATCH_IF ~%ability_resref%~ STRING_EQUAL ~~ OR NOT FILE_EXISTS_IN_GAME ~%ability_resref%.spl~ BEGIN
				SET drop_id = ability_id
				SPRINT ignored_reason ~file_error:opcode171:invalid~
				SPRINT ignored_message ~spell %ability_resref%.SPL does not exist~
				LPM ad_application_drop
			END
			ELSE BEGIN
				LPF ad_spell_name STR_VAR resref = ~%ability_resref%~ RET ability_name = name END
				SET ability_type = 0
				INNER_PATCH_FILE ~%ability_resref%.spl~ BEGIN
					PATCH_IF BUFFER_LENGTH >= SPL_type + 2 BEGIN
						READ_SHORT SPL_type ability_type
					END
				END
				PATCH_IF ~%ability_name%~ STRING_EQUAL ~~ BEGIN
					LPF ad_refusal INT_VAR fx_id = ability_id STR_VAR reason = ~not_implemented:opcode171:no_name~ message = ~spell %ability_resref%.SPL has no name~ RET render_missing = refusal END
				END
				SPRINT $fx_spell_name(~%ability_id%~) ~%ability_name%~
				SET $fx_spell_book(~%ability_id%~) = ability_type == 1 OR ability_type == 2
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_171_lines BEGIN
	SET state_opcode = 171
	SPRINT state_variant_macro ~ad_op_171_variant~
	LPM ad_state_lines
END

// Variante 0 : capacité, 1 : sort du livre de sorts.
DEFINE_PATCH_MACRO ad_op_171_variant BEGIN
	SET state_variant = $fx_spell_book(~%line_fx%~)
	SPRINT spellName $fx_spell_name(~%line_fx%~)
END
