// Opcode 233 (Stat: Proficiency Modifier) : parameter1 = points de compétence, mot de poids faible de
// parameter2 = compétence (stats.ids 89 à 134) ; sur EE, mot de poids fort 1 = ajout (Increment),
// 0 = valeur fixée ; « Compétence martiale Épée longue : Passe à 5 ». Modificateur simple, code
// commun dans new-lib/opcodes/stat_modifiers.tpp ; nom de la compétence lu dans weapprof.2da
// (AD_PROFICIENCY_NAMES).

// Validation de l'ancien opcode_233_is_valid. Une statistique de compétence sans nom dans
// weapprof.2da (EXTRAPROFICIENCY…, que le jeu détourne en marqueur de sort) n'est pas une
// compétence du personnage : l'ancien moteur l'écarte sans rien écrire.
DEFINE_PATCH_MACRO ad_op_233_support BEGIN
	FOR (stat_id = 0; stat_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == 233 BEGIN
			SET proficiency_stat = $fx_parameter2(~%stat_id%~) BAND 65535
			SET proficiency_mode = IS_EE ? $fx_parameter2(~%stat_id%~) BLSR 16 : 0
			PATCH_IF proficiency_stat < 89 OR proficiency_stat > 134 OR proficiency_mode > 1 BEGIN
				SPRINT render_missing ~not_implemented:opcode233:invalid~
			END
			// Ajout (EE) : l'ancien moteur perd le mode dès la validation et écrit une valeur fixée
			// (BUG-028).
			ELSE PATCH_IF proficiency_mode == 1 BEGIN
				SPRINT render_missing ~not_implemented:opcode233:increment~
			END
			ELSE BEGIN
				SET $fx_stat_subject(~%stat_id%~) = proficiency_stat
				SET $fx_parameter2(~%stat_id%~) = MOD_TYPE_flat
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		SET stat_opcode = 233
		SPRINT stat_mode_3 ~invalid~
		LPM ad_stat_modifier_support
	END
	FOR (stat_id = 0; stat_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == 233 BEGIN
			SET proficiency_stat = $fx_stat_subject(~%stat_id%~)
			PATCH_IF NOT VARIABLE_IS_SET $AD_PROFICIENCY_NAMES(~%proficiency_stat%~) BEGIN
				SET drop_id = stat_id
				LPM ad_application_drop
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_233_lines BEGIN
	SET stat_opcode = 233
	SPRINT stat_line_macro ~ad_op_233_line~
	LPM ad_stat_modifier_lines
END

DEFINE_PATCH_MACRO ad_op_233_line BEGIN
	SET proficiency_stat = $fx_stat_subject(~%line_fx%~)
	SPRINT proficiency $AD_PROFICIENCY_NAMES(~%proficiency_stat%~)
END
