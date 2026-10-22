// Opcode 171 (Spell: Give Innate Ability) : ajoute le sort resource (ancien opcode_171_common) :
// « Ajoute la capacité « Métamorphose forme naturelle » », ou « Ajoute le sort « … » dans le livre de
// sorts » pour un sort profane ou divin (type 1 ou 2). Code commun dans new-lib/opcodes/states.tpp.
// Avec AD_ENABLE_SHRINKAGE, une métamorphose peut le retirer (ad_group_polymorph, new-lib/groups.tpp).

// Refus : sort absent (l'ancien moteur n'écrit rien) ; sort sans nom.
DEFINE_PATCH_MACRO ad_op_171_support BEGIN
	FOR (ability_id = 0; ability_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++ability_id) BEGIN
		PATCH_IF $fx_opcode(~%ability_id%~) == 171 AND NOT $fx_consumed(~%ability_id%~) BEGIN
			SPRINT ability_resref $fx_resource(~%ability_id%~)
			PATCH_IF ~%ability_resref%~ STRING_EQUAL ~~ OR NOT FILE_EXISTS_IN_GAME ~%ability_resref%.spl~ BEGIN
				SPRINT render_missing ~not_implemented:opcode171:invalid~
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
					SPRINT render_missing ~not_implemented:opcode171:no_name~
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
