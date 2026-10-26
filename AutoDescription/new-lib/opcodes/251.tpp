// Opcode 251 (Spell Effect: Change Bard Song Effect) : le chant de barde de la cible devient le sort
// resource (IESDP) : « Remplace le chant de barde : » suivi des effets du sort, décrits par leurs
// propres cibles (ancien opcode_self_251, get_item_spell_effects_description appelée sans profondeur :
// ni limite de profondeur, ni liste des sorts déjà décrits) ; code commun dans new-lib/recursion.tpp.

// Ressource vide : effet écarté sans rien écrire, erreur journalisée (comme l'ancien
// opcode_resref_is_valid).
// Refus : refus de la sous-description (ad_recursion_support).
DEFINE_PATCH_MACRO ad_op_251_support BEGIN
	PHP_EACH fx_ids_251 AS _ => heading_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%heading_id%~) BEGIN
			SPRINT heading_resref $fx_resource_lower(~%heading_id%~)
			PATCH_IF ~%heading_resref%~ STRING_EQUAL ~~ BEGIN
				SET drop_id = heading_id
				SPRINT ignored_reason ~file_error:opcode251:invalid~
				SPRINT ignored_message ~empty resource field~
				LPM ad_application_drop
			END
			ELSE BEGIN
				SET recursion_fx = heading_id
				SPRINT recursion_resref ~%heading_resref%~
				SET recursion_casting_level = 0
				SPRINT recursion_targets ~own~
				SET recursion_ignore_duration = 0
				SET recursion_series = 0
				SET recursion_depth_reset = 1
				SPRINT recursion_kind ~spl~
				SET recursion_parent_dice = 0
				SET recursion_versus_set = 0
				SPRINT recursion_versus ~~
				SPRINT recursion_single_reason ~~
				LPM ad_recursion_support
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_251_lines BEGIN
	SET heading_opcode = 251
	SET heading_tra = 22510000 // ~Remplace le chant de barde~
	LPM ad_recursion_heading_lines
END
