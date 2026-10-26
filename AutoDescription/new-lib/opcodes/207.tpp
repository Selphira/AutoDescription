// Opcode 207 (Spell: Bounce Specified Spell) : renvoie le sort resource : « Renvoie le sort
// « Projectile magique » » ; l'ancien moteur n'a de phrase qu'aux formes « soi ». Avec
// AD_ENABLE_SHRINKAGE, le renvoi d'un projectile (opcode 197) absorbe les renvois des sorts qui
// l'utilisent (ad_group_bounce_spells, new-lib/groups.tpp). Code commun dans new-lib/opcodes/states.tpp.

// Sort absent : effet écarté sans rien écrire, erreur journalisée.
// Refus : sort sans nom (l'ancien moteur écrit « « » »).
DEFINE_PATCH_MACRO ad_op_207_support BEGIN
	PHP_EACH fx_ids_207 AS _ => bounce_spell_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SPRINT bounce_spell_resref $fx_resource(~%bounce_spell_id%~)
			LPF ad_spell_name STR_VAR resref = ~%bounce_spell_resref%~ RET bounce_spell_name = name END
			SPRINT $fx_spell_name(~%bounce_spell_id%~) ~%bounce_spell_name%~
			PATCH_IF ~%bounce_spell_name%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF FILE_EXISTS_IN_GAME ~%bounce_spell_resref%.spl~ BEGIN
					LPF ad_refusal INT_VAR fx_id = bounce_spell_id STR_VAR reason = ~not_implemented:opcode207:no_name~ message = ~spell %bounce_spell_resref%.SPL has no name~ RET render_missing = refusal END
				END
				ELSE BEGIN
					SET drop_id = bounce_spell_id
					SPRINT ignored_reason ~file_error:opcode207:missing_spell~
					SPRINT ignored_message ~spell %bounce_spell_resref%.SPL does not exist~
					LPM ad_application_drop
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
