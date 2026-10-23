// Opcode 207 (Spell: Bounce Specified Spell) : renvoie le sort resource : « Renvoie le sort
// « Projectile magique » » ; l'ancien moteur n'a de phrase qu'aux formes « soi ». Avec
// AD_ENABLE_SHRINKAGE, le renvoi d'un projectile (opcode 197) absorbe les renvois des sorts qui
// l'utilisent (ad_group_bounce_spells, new-lib/groups.tpp). Code commun dans new-lib/opcodes/states.tpp.

// Refus : sort sans nom (l'ancien moteur écrit « « » »).
DEFINE_PATCH_MACRO ad_op_207_support BEGIN
	FOR (bounce_spell_id = 0; bounce_spell_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++bounce_spell_id) BEGIN
		PATCH_IF $fx_opcode(~%bounce_spell_id%~) == 207 BEGIN
			SPRINT bounce_spell_resref $fx_resource(~%bounce_spell_id%~)
			LPF ad_spell_name STR_VAR resref = ~%bounce_spell_resref%~ RET bounce_spell_name = name END
			SPRINT $fx_spell_name(~%bounce_spell_id%~) ~%bounce_spell_name%~
			PATCH_IF ~%bounce_spell_name%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF FILE_EXISTS_IN_GAME ~%bounce_spell_resref%.spl~ BEGIN
					LPF ad_refusal INT_VAR fx_id = bounce_spell_id STR_VAR reason = ~not_implemented:opcode207:no_name~ message = ~spell %bounce_spell_resref%.SPL has no name~ RET render_missing = refusal END
				END
				ELSE BEGIN
					LPF ad_refusal INT_VAR fx_id = bounce_spell_id STR_VAR reason = ~file_error:opcode207:missing_spell~ message = ~spell %bounce_spell_resref%.SPL does not exist~ RET render_missing = refusal END
				END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_207_lines BEGIN
	SET state_opcode = 207
	SPRINT state_variant_macro ~ad_op_207_name~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_207_name BEGIN
	SPRINT spellName $fx_spell_name(~%line_fx%~)
END
