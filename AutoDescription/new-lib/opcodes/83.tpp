// Opcode 83 (Protection: From Projectile) : immunise contre les effets portés par le projectile
// parameter2 (projectl.ids) : « Immunité contre les éclairs ». Nom du projectile dans
// AD_PROJECTILE_NAMES (ad_projectile_name, new-lib/resources.tpp) ; un projectile sans nom connu
// n'écrit rien, comme dans l'ancien moteur. Avec AD_ENABLE_SHRINKAGE, les immunités d'un même bloc, si elles sont plusieurs,
// n'en font qu'une (ancien opcode_83_group) : noms réunis sans doublon et triés, ligne de l'effet lu
// en dernier ; les immunités aux sorts de même projectile sont absorbées
// (ad_group_projectile_spells, new-lib/groups.tpp). Une immunité consommée par un regroupement (effets
// identiques, immunité à l'état qu'apporte le projectile) n'est pas écrite.

DEFINE_PATCH_MACRO ad_op_83_support BEGIN END

DEFINE_PATCH_MACRO ad_op_83_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~83~)
	SPRINT the @1000008 // ~les~
	FOR (missile_id = 0; missile_id < fx_count; ++missile_id) BEGIN
		SET $missile_done(~%missile_id%~) = 0
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		FOR (missile_id = 0; missile_id < fx_count; ++missile_id) BEGIN
			PATCH_IF $fx_opcode(~%missile_id%~) == 83 AND NOT $fx_consumed(~%missile_id%~) AND NOT $missile_done(~%missile_id%~) BEGIN
				LPM ad_op_83_merged_line
			END
		END
	END
	FOR (missile_id = 0; missile_id < fx_count; ++missile_id) BEGIN
		PATCH_IF $fx_opcode(~%missile_id%~) == 83 AND NOT $fx_consumed(~%missile_id%~) AND NOT $missile_done(~%missile_id%~) BEGIN
			LPF ad_projectile_name INT_VAR projectile = $fx_parameter2(~%missile_id%~) RET missile_name = name END
			PATCH_IF NOT (~%missile_name%~ STRING_EQUAL ~~) BEGIN
				SPRINT projectiles ~%missile_name%~
				SET line_phrase = 20830100 // ~Immunité contre les %projectiles%~
				SET line_fx = missile_id
				LPM ad_effect_line
			END
		END
	END
END

// Immunités du bloc de l'effet missile_id, si elles sont plusieurs, en une ligne.
DEFINE_PATCH_MACRO ad_op_83_merged_line BEGIN
	SPRINT missile_scope $fx_scope(~%missile_id%~)
	SET missile_count = 0
	FOR (missile_other = 0; missile_other < fx_count; ++missile_other) BEGIN
		SPRINT missile_other_scope $fx_scope(~%missile_other%~)
		PATCH_IF $fx_opcode(~%missile_other%~) == 83 AND NOT $fx_consumed(~%missile_other%~) AND (~%missile_other_scope%~ STRING_EQUAL ~%missile_scope%~) BEGIN
			SET missile_count += 1
		END
	END
	PATCH_IF missile_count > 1 BEGIN
		CLEAR_ARRAY missile_names
		SET missile_last = 0 - 1
		FOR (missile_other = 0; missile_other < fx_count; ++missile_other) BEGIN
			SPRINT missile_other_scope $fx_scope(~%missile_other%~)
			PATCH_IF $fx_opcode(~%missile_other%~) == 83 AND NOT $fx_consumed(~%missile_other%~) AND (~%missile_other_scope%~ STRING_EQUAL ~%missile_scope%~) BEGIN
				SET $missile_done(~%missile_other%~) = 1
				SET missile_last = missile_other
				LPF ad_projectile_name INT_VAR projectile = $fx_parameter2(~%missile_other%~) RET missile_name = name END
				PATCH_IF NOT (~%missile_name%~ STRING_EQUAL ~~) BEGIN
					SPRINT $missile_names(~%missile_name%~) ~%missile_name%~
				END
			END
		END
		SORT_ARRAY_INDICES missile_names LEXICOGRAPHICALLY
		LPF ad_join STR_VAR array_name = ~missile_names~ glue = EVAL ~, %the% ~ final_glue = EVAL ~ %AD_AND% %the% ~ RET projectiles = text END
		PATCH_IF NOT (~%projectiles%~ STRING_EQUAL ~~) BEGIN
			SET line_phrase = 20830100 // ~Immunité contre les %projectiles%~
			SET line_fx = missile_last
			LPM ad_effect_line
		END
	END
END
