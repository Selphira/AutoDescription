// Opcode 326 (Apply Effects List, EE) : sort resource appliqué à la cible si elle remplit la condition
// de la ligne parameter2 de splprot.2da (ancien opcode_self_326) : « Si l'état de la cible est « mort » ;
// Ressuscite la cible ». Le sort est décrit par ses effets (new-lib/recursion.tpp), qui reprennent les
// chaînes de cible de l'effet ; la durée de l'effet n'est pas écrite (ancien ignoreDuration). L'ancien
// moteur décrit ce sort sans limite de profondeur (recursivity remise à 0) : un 326 d'un sous-sort est
// décrit, un 146 du sort appliqué ne l'est pas (recursion_depth_reset).

// Avec AD_ENABLE_SHRINKAGE, les 326 de même portée vers le même sort n'en font qu'un (ancien
// opcode_326_group) : quand toutes leurs conditions sont des types de créature (lignes 102 à 108 de
// splprot.2da : fichier IDS parameter2 - 100, valeur parameter1), le premier les réunit sans
// condition et ses sous-effets les visent (ctx_versus) : « Inflige 1d4 points de dégâts magiques
// contre les fées, les ombres et les esprits » ; les autres sont écartés.

// Refus : effet d'un EFF ; avec AD_ENABLE_SHRINKAGE, d'autres 326 de même portée vers le même sort
// dont une condition n'est pas un type de créature, ou aux autres champs différents (l'ancien moteur
// les réunit quand même), ou type sans nom ; condition refusée (ad_op_326_condition) ; plusieurs
// lignes sous une condition vide ; refus de ad_recursion_support.
DEFINE_PATCH_MACRO ad_op_326_support BEGIN
	PHP_EACH fx_ids_326 AS _ => apply_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%apply_id%~) BEGIN
			SPRINT apply_resref $fx_resource_lower(~%apply_id%~)
			SET apply_versus_set = 0
			SPRINT apply_versus ~~
			PATCH_IF $fx_external(~%apply_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~not_implemented:opcode326:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
				LPM ad_op_326_versus_group
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT apply_versus_set BEGIN
				LPM ad_op_326_condition
			END
			ELSE PATCH_IF apply_versus_set BEGIN
				SPRINT apply_condition ~~
				SPRINT $fx_condition_text(~%apply_id%~) ~~
				SPRINT $fx_condition_refusal(~%apply_id%~) ~~
			END
			// Effet différé : l'ancien moteur n'écrit rien quand le sort appliqué n'a pas de ligne
			// (SPWI910) ; sinon refus, avec les lignes.
			SET apply_delayed = $fx_timing(~%apply_id%~) == TIMING_delayed
			PATCH_IF apply_delayed AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
				SPRINT apply_pending $fx_condition_refusal(~%apply_id%~)
				PATCH_IF ~%apply_pending%~ STRING_EQUAL ~~ BEGIN
					SPRINT $fx_condition_refusal(~%apply_id%~) ~not_implemented:opcode326:delayed~
					SPRINT $fx_condition_refusal_message(~%apply_id%~) ~delayed effect~
				END
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
				SET recursion_fx = apply_id
				SPRINT recursion_resref ~%apply_resref%~
				SET recursion_casting_level = 0
				SPRINT recursion_targets ~effect~
				SET recursion_ignore_duration = 0
				SET recursion_series = 0
				SET recursion_depth_reset = 1
				SET recursion_delayed = apply_delayed
				SPRINT recursion_kind ~spl~
				SET recursion_parent_dice = 0
				SET recursion_versus_set = apply_versus_set
				SPRINT recursion_versus ~%apply_versus%~
				SPRINT recursion_single_reason ~~
				PATCH_IF ~%apply_condition%~ STRING_EQUAL ~~ AND NOT apply_versus_set BEGIN
					SPRINT recursion_single_reason ~not_implemented:opcode326:no_condition~
					SPRINT recursion_single_message ~several lines without a condition text~
				END
				LPM ad_recursion_support
			END
		END
	END
END

// Autres 326 de la portée de apply_id vers son sort : réunis à lui (apply_versus_set, apply_versus)
// quand tous ont un type de créature pour condition et les mêmes autres champs, sinon refus.
DEFINE_PATCH_MACRO ad_op_326_versus_group BEGIN
	SPRINT apply_scope $fx_scope(~%apply_id%~)
	SET apply_members = 0
	SET apply_others = 0
	PHP_EACH fx_ids_326 AS _ => apply_other BEGIN
		SPRINT apply_other_scope $fx_scope(~%apply_other%~)
		SPRINT apply_other_resref $fx_resource_lower(~%apply_other%~)
		SET apply_others += apply_other != apply_id AND NOT $fx_consumed(~%apply_other%~) AND (~%apply_other_scope%~ STRING_EQUAL ~%apply_scope%~)
			AND (~%apply_other_resref%~ STRING_EQUAL ~%apply_resref%~)
	END
	CLEAR_ARRAY apply_versus_names
	SET same_id = apply_id
	SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2
	PHP_EACH fx_ids_326 AS _ => apply_other BEGIN
		SPRINT apply_other_scope $fx_scope(~%apply_other%~)
		SPRINT apply_other_resref $fx_resource_lower(~%apply_other%~)
		PATCH_IF apply_others > 0 AND NOT $fx_consumed(~%apply_other%~) AND (~%apply_other_scope%~ STRING_EQUAL ~%apply_scope%~)
				AND (~%apply_other_resref%~ STRING_EQUAL ~%apply_resref%~) BEGIN
			SET apply_other_row = $fx_parameter2_raw(~%apply_other%~)
			SET same_other = apply_other
			LPM ad_fx_same_fields
			PATCH_IF apply_other_row < 102 OR apply_other_row > 108 OR NOT fx_same BEGIN
				SET apply_members = 0 - 1000
			END
			ELSE BEGIN
				LPF ad_ids_name INT_VAR ids_file = apply_other_row - 100 entry = $fx_parameter1(~%apply_other%~) RET apply_versus_name = name END
				PATCH_IF ~%apply_versus_name%~ STRING_EQUAL ~~ BEGIN
					SET apply_members = 0 - 1000
				END
				SPRINT $apply_versus_names(~%apply_versus_name%~) ~%apply_versus_name%~
				SET apply_members += 1
			END
		END
	END
	PATCH_IF apply_members < 0 BEGIN
		LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~not_implemented:opcode326:group~ message = ~several opcode 326 casting the same spell, not all under a named creature type with the same fields~ RET render_missing = refusal END
	END
	ELSE PATCH_IF apply_members > 1 BEGIN
		PHP_EACH fx_ids_326 AS _ => apply_other BEGIN
			SPRINT apply_other_scope $fx_scope(~%apply_other%~)
			SPRINT apply_other_resref $fx_resource_lower(~%apply_other%~)
			PATCH_IF apply_other != apply_id AND (~%apply_other_scope%~ STRING_EQUAL ~%apply_scope%~) AND (~%apply_other_resref%~ STRING_EQUAL ~%apply_resref%~) BEGIN
				SET $fx_consumed(~%apply_other%~) = 1
			END
		END
		SPRINT apply_the @2002000 // ~les~
		SPRINT apply_and_the @2002001 // ~et les~
		LPF ad_join STR_VAR array_name = ~apply_versus_names~ glue = EVAL ~, %apply_the% ~ final_glue = EVAL ~ %apply_and_the% ~ RET targetType = text END
		SPRINT apply_versus @2002020 // ~contre les %targetType%~
		SET apply_versus_set = 1
	END
END

// Condition de l'effet apply_id (ancien opcode_326_condition) : $fx_condition_text, vide pour une
// ligne de splprot.2da sans condition à écrire (« EA >= 0 »). Statistique, valeur (celle de la
// table, ou parameter1 pour - 1) et relation de la ligne donnent la chaîne de stats.2da, de la clé la
// plus précise à la plus générale ; une chaîne reprise de l'ancien fichier (@13260000-@13269999 ->
// @23260000-@23269999) n'utilise que les chaînes de cible et, pour les statistiques d'un fichier IDS
// (266 à 268, 271, 273), le nom de la valeur (idName). Refus : ligne absente ou inutilisée ; aucune
// clé dans stats.2da (l'ancien moteur garde la condition précédente) ; statistique que l'ancien moteur
// écrit autrement (258 taille, 263 heure, 269 classe, 270 type précis, 272 alignement, 274 état de
// sort) ou d'un fichier IDS mal calculé (262) ; valeur sans nom ; chaîne non reprise, qui utilise une
// autre variable (statistique, compétence, élément…). Hors erreur de fichier, le refus attend les
// lignes (fx_condition_refusal) : l'ancien moteur n'écrit pas de condition sans ligne du sort
// appliqué (SPWI910).
DEFINE_PATCH_MACRO ad_op_326_condition BEGIN
	SPRINT $fx_condition_refusal(~%apply_id%~) ~~
	SPRINT apply_pending ~~
	SET apply_row = $fx_parameter2_raw(~%apply_id%~)
	SPRINT apply_stat ~*~
	SPRINT apply_value ~*~
	SPRINT apply_relation ~*~
	PATCH_IF VARIABLE_IS_SET $AD_SPLPROT_STAT(~%apply_row%~) BEGIN
		SPRINT apply_stat $AD_SPLPROT_STAT(~%apply_row%~)
		SPRINT apply_value $AD_SPLPROT_VALUE(~%apply_row%~)
		SPRINT apply_relation $AD_SPLPROT_RELATION(~%apply_row%~)
	END
	SPRINT apply_condition ~~
	PATCH_IF NOT IS_AN_INT apply_stat OR NOT IS_AN_INT apply_value OR NOT IS_AN_INT apply_relation BEGIN
		LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~file_error:opcode326:splprot~ message = ~row %apply_row% of SPLPROT.2DA is missing or unused~ RET render_missing = refusal END
	END
	ELSE BEGIN
		PATCH_IF apply_value == 0 - 1 BEGIN
			SPRINT apply_value $fx_parameter1(~%apply_id%~)
		END
		SPRINT apply_key ~%apply_stat%-%apply_value%-%apply_relation%~
		PATCH_IF NOT VARIABLE_IS_SET $AD_STAT_CONDITION(~%apply_key%~) BEGIN
			SPRINT apply_key ~%apply_stat%-%apply_value%-*~
		END
		PATCH_IF NOT VARIABLE_IS_SET $AD_STAT_CONDITION(~%apply_key%~) BEGIN
			SPRINT apply_key ~%apply_stat%-*-%apply_relation%~
		END
		PATCH_IF NOT VARIABLE_IS_SET $AD_STAT_CONDITION(~%apply_key%~) BEGIN
			SPRINT apply_key ~%apply_stat%-*-*~
		END
		SPRINT idName ~~
		PATCH_IF NOT VARIABLE_IS_SET $AD_STAT_CONDITION(~%apply_key%~) BEGIN
			SPRINT apply_pending ~not_implemented:opcode326:condition~
			SPRINT apply_pending_message ~no condition text for SPLPROT.2DA row %apply_row% (stat %apply_stat%, value %apply_value%, relation %apply_relation%)~
		END
		ELSE PATCH_IF apply_stat == 258 OR apply_stat == 262 OR apply_stat == 263 OR apply_stat == 269 OR apply_stat == 270
				OR apply_stat == 272 OR apply_stat == 274 BEGIN
			SPRINT apply_pending ~not_implemented:opcode326:condition_stat~
			SPRINT apply_pending_message ~stat %apply_stat% of SPLPROT.2DA row %apply_row% written differently by the old engine~
		END
		ELSE PATCH_IF apply_stat >= 266 AND apply_stat <= 273 BEGIN
			LPF ad_ids_name INT_VAR ids_file = apply_stat - 264 entry = apply_value RET idName = name END
			PATCH_IF ~%idName%~ STRING_EQUAL ~~ BEGIN
				SPRINT apply_pending ~not_implemented:opcode326:ids~
				SPRINT apply_pending_message ~value %apply_value% of stat %apply_stat% has no name~
			END
		END
		PATCH_IF ~%apply_pending%~ STRING_EQUAL ~~ BEGIN
			SET apply_tra = $AD_STAT_CONDITION(~%apply_key%~) + 10000000
			PATCH_IF $AD_STAT_CONDITION_ADD_RELATION(~%apply_key%~) BEGIN
				SET apply_tra += apply_relation
			END
			PATCH_IF NOT TRA_ENTRY_EXISTS (~%apply_tra%~) BEGIN
				SPRINT apply_pending ~not_implemented:opcode326:condition_text~
				SPRINT apply_pending_message ~no condition sentence %apply_tra%~
			END
		END
		PATCH_IF NOT ~%apply_pending%~ STRING_EQUAL ~~ BEGIN
			SPRINT $fx_condition_refusal(~%apply_id%~) ~%apply_pending%~
			SPRINT $fx_condition_refusal_message(~%apply_id%~) ~%apply_pending_message%~
		END
		ELSE PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET line_fx = apply_id
			SPRINT line_the_target ~~
			LPM ad_application_form
			LPM ad_application_target_strings
			SPRINT line_only_for ~~
			LPF ad_tra INT_VAR tra_id = apply_tra tra_block_start = 23260000 tra_block_size = 10000 RET apply_condition = text END // ~Si l'état %ofTheTarget% est « mort »~ (@23260181)
		END
	END
	SPRINT $fx_condition_text(~%apply_id%~) ~%apply_condition%~
END

// Une ligne par effet dont le sort appliqué en a.
DEFINE_PATCH_MACRO ad_op_326_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~326~)
	PHP_EACH fx_ids_326 AS _ => apply_id BEGIN
		SPRINT apply_pending $fx_condition_refusal(~%apply_id%~)
		PATCH_IF NOT $fx_consumed(~%apply_id%~) AND $fx_sub_count(~%apply_id%~) > 0 AND NOT ~%apply_pending%~ STRING_EQUAL ~~ BEGIN
			SPRINT apply_pending_message $fx_condition_refusal_message(~%apply_id%~)
			LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~%apply_pending%~ message = ~%apply_pending_message%~ RET render_late_missing = refusal END
		END
		ELSE PATCH_IF NOT $fx_consumed(~%apply_id%~) AND $fx_sub_count(~%apply_id%~) > 0 BEGIN
			SET recursion_fx = apply_id
			LPM ad_recursion_condition_text
			SPRINT line_condition $fx_condition_text(~%apply_id%~)
			SET line_any_form = 1
			SET line_no_duration = 1
			SET line_fx = apply_id
			LPM ad_effect_line
		END
	END
END
