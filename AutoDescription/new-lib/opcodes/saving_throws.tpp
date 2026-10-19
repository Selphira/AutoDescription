// Code commun des modificateurs de jets de sauvegarde (33 à 37) : modificateurs simples (prise en
// charge par ad_stat_modifier_support, new-lib/opcodes/stat_modifiers.tpp ; le mode 3 des jeux EE
// est un ajout) dont la ligne nomme le jet concerné. Le nom du jet (« contre les sorts ») est le
// libellé 2OOO0000 du bloc de l'opcode.

// Lignes (ancien opcode_self_<N> et opcode_save_vs) : une par effet non consommé par un regroupement.
DEFINE_PATCH_MACRO ad_saving_throw_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%stat_opcode%~)
	LPF ad_tra INT_VAR tra_id = 20000000 + stat_opcode * 10000 RET versus = text END
	SPRINT saves_name @5000000 // ~Jets de sauvegarde~
	FOR (stat_id = 0; stat_id < fx_count; ++stat_id) BEGIN
		PATCH_IF $fx_opcode(~%stat_id%~) == stat_opcode AND NOT $fx_consumed(~%stat_id%~) BEGIN
			SET stat_value = $fx_parameter1(~%stat_id%~)
			SET stat_mode = $fx_parameter2(~%stat_id%~)
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
			SET line_fx = stat_id
			LPM ad_effect_line
		END
	END
END
