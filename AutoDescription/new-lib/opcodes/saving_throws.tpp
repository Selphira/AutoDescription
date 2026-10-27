// Code commun des modificateurs de jets de sauvegarde (33 à 37) : modificateurs simples (prise en
// charge par ad_stat_modifier_support, new-lib/opcodes/stat_modifiers.tpp ; le mode 3 des jeux EE
// est un ajout) dont la ligne nomme le jet concerné. Le nom du jet (« contre les sorts ») est le
// libellé 2OOO0000 du bloc de l'opcode.

// Lignes (ancien opcode_self_<N> et opcode_save_vs) : une par effet non consommé par un regroupement ;
// sur une autre cible que soi, phrase des modificateurs (« Augmente de 1 les jets de sauvegarde contre
// les sorts de la cible »), où le mode 3 des jeux EE est un ajout. Une progression selon le niveau du
// sort (fx_level_value) y remplace la valeur, sans son signe pour une réduction, comme
// ad_stat_modifier_target_phrase ; refusée à la forme « soi », que le jeu de base n'exerce pas
// (render_late_missing).
DEFINE_PATCH_MACRO ad_saving_throw_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%stat_opcode%~)
	LPF ad_tra INT_VAR tra_id = 20000000 + stat_opcode * 10000 RET versus = text END
	SPRINT saves_name @5000000 // ~Jets de sauvegarde~
	PHP_EACH ~fx_ids_%stat_opcode%~ AS _ => stat_id BEGIN
		PATCH_IF NOT $fx_consumed(~%stat_id%~) BEGIN
			SET stat_value = $fx_parameter1(~%stat_id%~)
			SET stat_mode = $fx_parameter2(~%stat_id%~)
			SET line_fx = stat_id
			LPM ad_application_form
			SPRINT stat_level_value $fx_level_value(~%stat_id%~)
			PATCH_IF line_form == 0 AND NOT (~%stat_level_value%~ STRING_EQUAL ~~) BEGIN
				LPF ad_refusal INT_VAR fx_id = stat_id STR_VAR reason = ~not_implemented:spell:progression_self_save~ message = ~saving throw bonus of the caster varying with the level~ RET render_late_missing = refusal END
			END
			PATCH_IF line_form == 0 BEGIN
				LPF ad_stat_modifier_value INT_VAR value = stat_value mode = stat_mode RET value = text END
				// Un ajout nomme le jet après la valeur, les autres modes avant elle.
				PATCH_IF stat_mode == MOD_TYPE_flat OR stat_mode == MOD_TYPE_percentage BEGIN
					SPRINT name ~%saves_name% %versus%~
				END
				ELSE BEGIN
					SPRINT name ~%saves_name%~
					SPRINT value ~%value% %versus%~
				END
				SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
			END
			ELSE BEGIN
				SPRINT theStatistic @5000003 // ~les jets de sauvegarde %versus%~
				SET stat_percent = 0
				LPM ad_stat_modifier_phrase
				PATCH_IF NOT (~%stat_level_value%~ STRING_EQUAL ~~) BEGIN
					SPRINT value ~%stat_level_value%~
					PATCH_IF stat_value < 0 BEGIN
						LPF ad_level_unsigned STR_VAR text = ~%stat_level_value%~ RET value = text END
					END
				END
			END
			LPM ad_effect_line
		END
	END
END
