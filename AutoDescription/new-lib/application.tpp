// Application des effets : ce qui ne dépend pas de l'opcode (cible, probabilité, durée, jet de
// sauvegarde…). Un opcode ne fournit que le cœur de sa phrase ; la prise en charge commune refuse
// ce que le flux commun ne sait pas encore écrire, et ad_effect_line complète la ligne.
//
// Formes d'une phrase (identifiant de base de la série + forme) : 0 soi,
// 1 cible, 2 soi probable, 3 cible probable. Pris en charge pour l'instant : effets d'équipement
// certains, actifs tant que l'objet est équipé (forme 0, sans durée ni jet de sauvegarde).

// Prise en charge commune (passe 2, avant celle des opcodes), pour chaque effet d'un opcode décrit.
DEFINE_PATCH_MACRO ad_application_support BEGIN
	FOR (app_id = 0; app_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++app_id) BEGIN
		SET render_opcode = $fx_opcode(~%app_id%~)
		LPM ad_opcode_is_described
		PATCH_IF opcode_described BEGIN
			SPRINT app_block $fx_block(~%app_id%~)
			SPRINT app_timing_kind $fx_timing_kind(~%app_id%~)
			PATCH_IF NOT (~%app_block%~ STRING_EQUAL ~equipped~) OR NOT (~%app_timing_kind%~ STRING_EQUAL ~while_equipped~)
					OR $fx_probability(~%app_id%~) != 100 BEGIN
				SPRINT render_missing ~not_implemented:opcode%render_opcode%:effect_kind~
			END
		END
	END
END

// Forme de la phrase de l'effet line_fx : 0 soi, 1 cible, 2 soi probable, 3 cible probable.
DEFINE_PATCH_MACRO ad_application_form BEGIN
	SET app_target = $fx_effective_target(~%line_fx%~)
	SET line_form = (app_target == TARGET_FX_self OR app_target == TARGET_FX_original_caster) ? 0 : 1
	PATCH_IF $fx_probability(~%line_fx%~) < 100 BEGIN
		SET line_form += 2
	END
END

// Ligne de l'effet line_fx (pour une ligne qui en réunit plusieurs, l'un d'eux, de même application
// que les autres) : phrase line_phrase (identifiant de base de la série, la forme y est ajoutée),
// ou line_text déjà rédigé à la forme « soi » ; line_section et line_sort comme pour ad_line_add.
DEFINE_PATCH_MACRO ad_effect_line BEGIN
	LPM ad_application_form
	PATCH_IF line_phrase > 0 BEGIN
		SET line_phrase_tra = line_phrase + line_form
		LPF ad_tra INT_VAR tra_id = line_phrase_tra RET line_text = text END
	END
	ELSE PATCH_IF line_form != 0 BEGIN
		PATCH_FAIL ~New engine: effect %line_fx% needs phrase form %line_form% but its line has none~
	END
	LPM ad_line_add
	SET line_phrase = 0
END
