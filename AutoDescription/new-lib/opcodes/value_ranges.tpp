// Valeurs tirées au sort (opcodes 12, 159, 244 et 261) : le jeu tire un seul nombre de 0 à 99 pour les
// effets d'une capacité ; des effets d'un même opcode semblables à leur valeur (parameter1) et à leur
// probabilité près, dont les plages sont contiguës et disjointes, donnent donc une seule de ces valeurs.
// Avec AD_ENABLE_SHRINKAGE, ils n'en font qu'un, sur l'union de leurs plages : « Draine entre 1 et 10
// sorts profanes ». Les valeurs sont écrites comme équiprobables : les écarts d'arrondi des plages
// (11 %, 10 %… 9 %) sont acceptés, AD_ENABLE_SHRINKAGE à 0 les détaille.
//
// Tableaux écrits : fx_range_min et fx_range_max (0 à la lecture, new-lib/effects.tpp), bornes des
// valeurs réunies, lues par la ligne de l'effet qui les représente.

// Effets semblables à range_id (fx_ids_<range_opcode>), de valeur positive, à la valeur et à la
// probabilité près. Sortie : range_broken, 1 si de tels effets existent mais que leurs plages se
// chevauchent ou laissent un trou (rien n'est réuni).
DEFINE_PATCH_MACRO ad_value_range_group BEGIN
	SET range_broken = 0
	SET same_id = range_id
	SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PROBABILITY
	SET range_min = $fx_parameter1(~%range_id%~)
	SET range_max = range_min
	SET range_low = $fx_probability_low(~%range_id%~)
	SET range_high = $fx_probability_high(~%range_id%~)
	SET range_total = $fx_probability(~%range_id%~)
	SET range_count = 0
	CLEAR_ARRAY range_members
	PHP_EACH ~fx_ids_%range_opcode%~ AS _ => range_other BEGIN
		SET range_other_value = $fx_parameter1(~%range_other%~)
		PATCH_IF range_other != range_id AND range_other_value > 0 AND NOT $fx_consumed(~%range_other%~) BEGIN
			SET same_other = range_other
			LPM ad_fx_same_fields
			PATCH_IF fx_same BEGIN
				SET $range_members(~%range_other%~) = 1
				SET range_count += 1
				SET range_min = range_other_value < range_min ? range_other_value : range_min
				SET range_max = range_other_value > range_max ? range_other_value : range_max
				SET range_low = $fx_probability_low(~%range_other%~) < range_low ? $fx_probability_low(~%range_other%~) : range_low
				SET range_high = $fx_probability_high(~%range_other%~) > range_high ? $fx_probability_high(~%range_other%~) : range_high
				SET range_total += $fx_probability(~%range_other%~)
			END
		END
	END
	// Plages disjointes et sans trou : leur somme est la largeur de leur union.
	PATCH_IF range_count > 0 AND range_total != range_high - range_low + 1 BEGIN
		SET range_broken = 1
	END
	ELSE PATCH_IF range_count > 0 BEGIN
		PHP_EACH range_members AS range_other => _ BEGIN
			SET $fx_consumed(~%range_other%~) = 1
		END
		SET $fx_range_min(~%range_id%~) = range_min
		SET $fx_range_max(~%range_id%~) = range_max
		SET $fx_probability_low(~%range_id%~) = range_low
		SET $fx_probability_high(~%range_id%~) = range_high
		SET $fx_probability(~%range_id%~) = range_total
		// Champs lus aussi à l'union, comme l'effet que l'ancien moteur ajoute : deux niveaux de sort aux
		// mêmes valeurs réunies se comparent égaux (ad_spell_level_same).
		SET $fx_probability1(~%range_id%~) = range_high
		SET $fx_probability2(~%range_id%~) = range_low
		SET $fx_late(~%range_id%~) = 2
		// Union de tout le tirage sous un effet probable qui lance le sort : l'effet devient certain et
		// prend la probabilité du parent, comme un sous-effet certain (ad_recursion_base_probability).
		PATCH_IF range_total >= 100 AND ctx_base_probability < 100 BEGIN
			SET $fx_probability(~%range_id%~) = ctx_base_probability
			SET $fx_probability_low(~%range_id%~) = ctx_base_low
			SET $fx_probability_high(~%range_id%~) = ctx_base_high
			SET $fx_parent_probability(~%range_id%~) = 1
		END
	END
END

// Réunit les effets de range_opcode, sauf avec support_header_only ; refus pour le 159
// (range_broken), que l'ancien moteur réunit aussi quand ses plages se chevauchent.
DEFINE_PATCH_MACRO ad_value_range_support BEGIN
	PATCH_IF AD_ENABLE_SHRINKAGE AND NOT support_header_only BEGIN
		PHP_EACH ~fx_ids_%range_opcode%~ AS _ => range_id BEGIN
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%range_id%~) AND $fx_parameter1(~%range_id%~) > 0 BEGIN
				SET range_eligible = 1
				PATCH_IF NOT (~%range_eligible_macro%~ STRING_EQUAL ~~) BEGIN
					LPM ~%range_eligible_macro%~
				END
				PATCH_IF range_eligible BEGIN
					LPM ad_value_range_group
					PATCH_IF range_broken AND range_opcode == 159 BEGIN
						LPF ad_refusal INT_VAR fx_id = range_id STR_VAR reason = ~not_implemented:opcode159:group~ message = ~several mirror image effects differing only by the amount, with overlapping or separate probability ranges~ RET render_missing = refusal END
					END
				END
			END
		END
	END
END

// Texte « entre X et Y » (range_text) des valeurs réunies sur l'effet line_fx, vide sans regroupement.
DEFINE_PATCH_MACRO ad_value_range_text BEGIN
	SPRINT range_text ~~
	PATCH_IF $fx_range_max(~%line_fx%~) > 0 BEGIN
		SET amountMin = $fx_range_min(~%line_fx%~)
		SET amountMax = $fx_range_max(~%line_fx%~)
		LPF ad_tra INT_VAR tra_id = 21270000 RET range_text = text END // ~entre %amountMin% et %amountMax%~
	END
END
