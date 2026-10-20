// Opcode 197 (Spell: Bounce (by Impact Projectile)) : renvoie au lanceur les effets portés par le
// projectile parameter2 (projectl.ids) : « Renvoie les éclairs ». Nom du projectile dans
// AD_PROJECTILE_NAMES (ad_projectile_name, new-lib/resources.tpp) ; un projectile sans nom connu
// n'écrit rien, comme dans l'ancien moteur. Avec AD_ENABLE_SHRINKAGE, les renvois d'un même bloc, s'ils sont plusieurs, n'en
// font qu'un (ancien opcode_197_group) : noms réunis sans doublon dans l'ordre du fichier, ligne de
// l'effet lu en dernier. L'ancien moteur réunit aussi les renvois aux protections contre un sort
// (opcode 207) de même projectile, qui n'est pas encore décrit.

DEFINE_PATCH_MACRO ad_op_197_support BEGIN END

DEFINE_PATCH_MACRO ad_op_197_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~197~)
	SPRINT the @1000008 // ~les~
	FOR (bounce_id = 0; bounce_id < fx_count; ++bounce_id) BEGIN
		SET $bounce_done(~%bounce_id%~) = 0
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		FOR (bounce_id = 0; bounce_id < fx_count; ++bounce_id) BEGIN
			PATCH_IF $fx_opcode(~%bounce_id%~) == 197 AND NOT $bounce_done(~%bounce_id%~) BEGIN
				LPM ad_op_197_merged_line
			END
		END
	END
	FOR (bounce_id = 0; bounce_id < fx_count; ++bounce_id) BEGIN
		PATCH_IF $fx_opcode(~%bounce_id%~) == 197 AND NOT $bounce_done(~%bounce_id%~) BEGIN
			LPF ad_projectile_name INT_VAR projectile = $fx_parameter2(~%bounce_id%~) RET bounce_name = name END
			PATCH_IF NOT (~%bounce_name%~ STRING_EQUAL ~~) BEGIN
				SPRINT projectiles ~%bounce_name%~
				SET line_phrase = 21970100 // ~Renvoie %the% %projectiles%~
				SET line_fx = bounce_id
				LPM ad_effect_line
			END
		END
	END
END

// Renvois du bloc de l'effet bounce_id, s'ils sont plusieurs, en une ligne.
DEFINE_PATCH_MACRO ad_op_197_merged_line BEGIN
	SPRINT bounce_scope $fx_scope(~%bounce_id%~)
	SET bounce_count = 0
	FOR (bounce_other = 0; bounce_other < fx_count; ++bounce_other) BEGIN
		SPRINT bounce_other_scope $fx_scope(~%bounce_other%~)
		PATCH_IF $fx_opcode(~%bounce_other%~) == 197 AND (~%bounce_other_scope%~ STRING_EQUAL ~%bounce_scope%~) BEGIN
			SET bounce_count += 1
		END
	END
	PATCH_IF bounce_count > 1 BEGIN
		CLEAR_ARRAY bounce_names
		SET bounce_name_count = 0
		SET bounce_last = 0 - 1
		FOR (bounce_other = 0; bounce_other < fx_count; ++bounce_other) BEGIN
			SPRINT bounce_other_scope $fx_scope(~%bounce_other%~)
			PATCH_IF $fx_opcode(~%bounce_other%~) == 197 AND (~%bounce_other_scope%~ STRING_EQUAL ~%bounce_scope%~) BEGIN
				SET $bounce_done(~%bounce_other%~) = 1
				SET bounce_last = bounce_other
				LPF ad_projectile_name INT_VAR projectile = $fx_parameter2(~%bounce_other%~) RET bounce_name = name END
				PATCH_IF NOT (~%bounce_name%~ STRING_EQUAL ~~) AND NOT VARIABLE_IS_SET $bounce_seen(~%bounce_scope% %bounce_name%~) BEGIN
					// Clé propre au bloc : CLEAR_ARRAY ne défait pas les éléments que VARIABLE_IS_SET teste (V36).
					SET $bounce_seen(~%bounce_scope% %bounce_name%~) = 1
					// « fléchettes, les dagues de jet et les billes » : l'article du premier nom est dans la phrase.
					PATCH_IF bounce_name_count == 0 BEGIN
						SPRINT $bounce_names(~%bounce_name_count%~) ~%bounce_name%~
					END
					ELSE BEGIN
						SPRINT $bounce_names(~%bounce_name_count%~) ~%the% %bounce_name%~
					END
					SET bounce_name_count += 1
				END
			END
		END
		PATCH_IF bounce_name_count > 0 BEGIN
			LPF ad_join STR_VAR array_name = ~bounce_names~ RET projectiles = text END
			SET line_phrase = 21970100 // ~Renvoie %the% %projectiles%~
			SET line_fx = bounce_last
			LPM ad_effect_line
		END
	END
END
