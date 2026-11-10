// Effets d'un même opcode qui ne diffèrent que par la ressource qu'ils nomment et par leur probabilité
// (AD_GROUP_UNEQUAL_PROBABILITIES, avec AD_ENABLE_SHRINKAGE) : le jeu tire un seul nombre de 0 à 99 par
// créature visée pour les effets d'une capacité (IESDP, eff_v1 : Probability) ; sur des plages
// contiguës et disjointes, un seul d'entre eux s'applique. Ils n'en font qu'un, sur l'union de leurs
// plages, qui liste les noms par chance décroissante, égalités dans l'ordre de lecture (« Lance
// instantanément l'un des sorts suivants sur la cible : « Orbe blanche » ou « Orbe verte » ») ; la
// chance de chacun n'est plus écrite. Un même nom sur plusieurs plages n'est écrit qu'une fois ; un
// seul nom garde la phrase de l'opcode, au total des chances. Des plages qui se chevauchent ou laissent
// un trou ne sont pas réunies (WAND12 : seules les deux plages qui se touchent le sont).
//
// AD_PROBABILITY_LIST_NAMES (new-lib/catalog.tpa) : opcode => tableau des noms de ses effets (vide pour
// un effet décrit autrement), rempli par la prise en charge de l'opcode avant l'appel.
// Tableaux écrits : fx_name_list (vide à la lecture), noms réunis, déjà joints, lus par la ligne de
// l'effet qui les représente ; fx_list_size et fx_list_member(~id k~), effets réunis à lui, lus pour la
// durée de l'en-tête d'un sort.

// Réunit les effets de list_opcode ; l'appelant écarte ceux que l'ancien moteur décrit autrement.
DEFINE_PATCH_MACRO ad_probability_list_support BEGIN
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_GROUP_UNEQUAL_PROBABILITIES AND NOT support_header_only
			AND VARIABLE_IS_SET $AD_PROBABILITY_LIST_NAMES(~%list_opcode%~) BEGIN
		SPRINT list_names $AD_PROBABILITY_LIST_NAMES(~%list_opcode%~)
		PHP_EACH ~fx_ids_%list_opcode%~ AS _ => list_id BEGIN
			SET list_candidate = list_id
			LPM ad_probability_list_eligible
			PATCH_IF list_eligible AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
				LPM ad_probability_list_group
			END
		END
	END
END

// L'effet list_candidate peut-il être réuni (list_eligible) : probable, nommé, ni écarté ni déjà réuni,
// ni répétition d'une série (son nom n'est pas lu, new-lib/opcodes/cast_spell.tpp).
DEFINE_PATCH_MACRO ad_probability_list_eligible BEGIN
	SET list_eligible = NOT $fx_consumed(~%list_candidate%~) AND NOT $fx_dropped(~%list_candidate%~)
		AND $fx_series_of(~%list_candidate%~) < 0
		AND $fx_probability(~%list_candidate%~) > 0 AND $fx_probability(~%list_candidate%~) < 100
		AND VARIABLE_IS_SET $EVAL ~%list_names%~(~%list_candidate%~)
	PATCH_IF list_eligible BEGIN
		SPRINT list_candidate_name $EVAL ~%list_names%~(~%list_candidate%~)
		SPRINT list_candidate_joined $fx_name_list(~%list_candidate%~)
		SET list_eligible = NOT (~%list_candidate_name%~ STRING_EQUAL ~~) AND ~%list_candidate_joined%~ STRING_EQUAL ~~
	END
END

// Effets semblables à list_id, à la ressource et à la probabilité près (et de même type de créature
// visé par un 177, que ad_fx_same_fields ne compare pas) : la suite de plages contiguës
// qui contient la sienne (rangées par borne basse) est réunie à lui si elle compte plusieurs effets.
DEFINE_PATCH_MACRO ad_probability_list_group BEGIN
	CLEAR_ARRAY list_by_low
	// Marque propre à cet appel : CLEAR_ARRAY ne défait pas les éléments que VARIABLE_IS_SET teste (V36).
	SET list_low_pass = VARIABLE_IS_SET list_low_pass ? list_low_pass + 1 : 1
	SET list_overlap = 0
	SET list_low = $fx_probability_low(~%list_id%~)
	SET $list_by_low(~%list_low%~) = list_id
	SET $list_low_seen(~%list_low%~) = list_low_pass
	SET same_id = list_id
	SET same_ignored = AD_SAME_PROBABILITY
	PHP_EACH ~fx_ids_%list_opcode%~ AS _ => list_other BEGIN
		SET list_candidate = list_other
		LPM ad_probability_list_eligible
		PATCH_IF list_other != list_id AND list_eligible
				AND $fx_exception_count(~%list_other%~) == $fx_exception_count(~%list_id%~)
				AND $fx_not_cumulative(~%list_other%~) == $fx_not_cumulative(~%list_id%~)
				AND $fx_versus_file(~%list_other%~) == $fx_versus_file(~%list_id%~)
				AND $fx_versus_value(~%list_other%~) == $fx_versus_value(~%list_id%~)
				AND $fx_versus_inner_file(~%list_other%~) == $fx_versus_inner_file(~%list_id%~)
				AND $fx_versus_inner_value(~%list_other%~) == $fx_versus_inner_value(~%list_id%~) BEGIN
			SET same_other = list_other
			LPM ad_fx_same_fields
			PATCH_IF fx_same BEGIN
				SET list_low = $fx_probability_low(~%list_other%~)
				PATCH_IF VARIABLE_IS_SET $list_low_seen(~%list_low%~) AND $list_low_seen(~%list_low%~) == list_low_pass BEGIN
					SET list_overlap = 1
				END
				SET $list_by_low(~%list_low%~) = list_other
				SET $list_low_seen(~%list_low%~) = list_low_pass
			END
		END
	END
	// Deux plages de même borne basse se chevauchent : rien n'est réuni.
	CLEAR_ARRAY list_run
	SET list_run_count = 0
	PATCH_IF NOT list_overlap BEGIN
		SORT_ARRAY_INDICES list_by_low NUMERICALLY
		SET list_run_has_id = 0
		SET list_previous_high = 0 - 2
		PHP_EACH list_by_low AS list_member_low => list_member BEGIN
			PATCH_IF NOT list_run_has_id OR list_member_low == list_previous_high + 1 BEGIN
				PATCH_IF list_member_low != list_previous_high + 1 BEGIN
					CLEAR_ARRAY list_run
					SET list_run_count = 0
				END
				SET $list_run(~%list_run_count%~) = list_member
				SET list_run_count += 1
				SET list_run_has_id = list_run_has_id OR list_member == list_id
				SET list_previous_high = $fx_probability_high(~%list_member%~)
			END
			ELSE BEGIN
				SET list_previous_high = 0 - 2
			END
		END
	END
	PATCH_IF list_run_count > 1 BEGIN
		LPM ad_probability_list_merge
	END
END

// Réunit les effets de list_run (list_run_count) à list_id : union des plages, total des chances, noms
// joints (fx_name_list) s'ils sont plusieurs.
DEFINE_PATCH_MACRO ad_probability_list_merge BEGIN
	CLEAR_ARRAY list_order
	SET list_low = 100
	SET list_high = 0
	SET list_total = 0
	FOR (list_k = 0; list_k < list_run_count; ++list_k) BEGIN
		SET list_member = $list_run(~%list_k%~)
		SET list_low = $fx_probability_low(~%list_member%~) < list_low ? $fx_probability_low(~%list_member%~) : list_low
		SET list_high = $fx_probability_high(~%list_member%~) > list_high ? $fx_probability_high(~%list_member%~) : list_high
		SET list_total += $fx_probability(~%list_member%~)
		SET list_order_key = (100 - $fx_probability(~%list_member%~)) * 100000 + list_member
		SET $list_order(~%list_order_key%~) = list_member
		// Membres gardés pour la durée de l'en-tête du sort (ad_spell_header_sub_duration).
		PATCH_IF list_member != list_id BEGIN
			SET $fx_consumed(~%list_member%~) = 1
			SET list_size = $fx_list_size(~%list_id%~) + 1
			SET $fx_list_member(~%list_id% %list_size%~) = list_member
			SET $fx_list_size(~%list_id%~) = list_size
		END
	END
	SORT_ARRAY_INDICES list_order NUMERICALLY
	// Marque propre à cet appel : CLEAR_ARRAY ne défait pas les éléments que VARIABLE_IS_SET teste (V36).
	SET list_pass = VARIABLE_IS_SET list_pass ? list_pass + 1 : 1
	CLEAR_ARRAY list_joined_names
	SET list_name_count = 0
	PHP_EACH list_order AS _ => list_member BEGIN
		SPRINT list_name $EVAL ~%list_names%~(~%list_member%~)
		SPRINT list_name_key ~%list_name%~
		TO_LOWER list_name_key
		PATCH_IF NOT VARIABLE_IS_SET $list_name_seen(~%list_name_key%~) OR $list_name_seen(~%list_name_key%~) != list_pass BEGIN
			SET $list_name_seen(~%list_name_key%~) = list_pass
			SPRINT $list_joined_names(~%list_name_count%~) ~%list_name%~
			SET list_name_count += 1
		END
	END
	PATCH_IF list_name_count > 1 BEGIN
		SPRINT and @1000007 // ~ou~
		SPRINT list_glue @1000005 // ~ », « ~
		SPRINT list_final_glue @1000006 // ~ » %and% « ~
		LPF ad_join STR_VAR array_name = ~list_joined_names~ glue = EVAL ~%list_glue%~ final_glue = EVAL ~%list_final_glue%~ RET list_joined = text END
		SPRINT $fx_name_list(~%list_id%~) ~%list_joined%~
	END
	SET $fx_probability_low(~%list_id%~) = list_low
	SET $fx_probability_high(~%list_id%~) = list_high
	SET $fx_probability(~%list_id%~) = list_total
	// Champs lus aussi à l'union, comme l'effet que l'ancien moteur ajoute : deux niveaux de sort aux
	// mêmes effets réunis se comparent égaux (ad_spell_level_same).
	SET $fx_probability1(~%list_id%~) = list_high
	SET $fx_probability2(~%list_id%~) = list_low
	SET $fx_late(~%list_id%~) = 2
	// Union de tout le tirage sous un effet probable qui lance le sort : l'effet devient certain et prend
	// la probabilité du parent, comme un sous-effet certain (ad_recursion_base_probability).
	PATCH_IF list_total >= 100 AND ctx_base_probability < 100 BEGIN
		SET $fx_probability(~%list_id%~) = ctx_base_probability
		SET $fx_probability_low(~%list_id%~) = ctx_base_low
		SET $fx_probability_high(~%list_id%~) = ctx_base_high
		SET $fx_parent_probability(~%list_id%~) = 1
	END
END
