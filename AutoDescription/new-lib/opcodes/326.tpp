// Opcode 326 (Apply Effects List, EE) : sort resource appliqué à la cible si elle remplit la condition
// de la ligne parameter2 de splprot.2da (ancien opcode_self_326) : « Si l'état de la cible est « mort » ;
// Ressuscite la cible ». Le sort est décrit par ses effets (new-lib/recursion.tpp), qui reprennent les
// chaînes de cible de l'effet ; la durée de l'effet n'est pas écrite (ancien ignoreDuration). L'ancien
// moteur décrit ce sort sans limite de profondeur (recursivity remise à 0) : un 326 d'un sous-sort est
// décrit, un 146 du sort appliqué ne l'est pas (recursion_depth_reset).

// Refus : effet d'un EFF ; avec AD_ENABLE_SHRINKAGE, un autre 326 de même portée vers le même sort
// (ancien opcode_326_group, qui réunit leurs conditions) ; condition refusée (ad_op_326_condition) ;
// plusieurs lignes sous une condition vide ; refus de ad_recursion_support.
DEFINE_PATCH_MACRO ad_op_326_support BEGIN
	PHP_EACH fx_ids_326 AS _ => apply_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%apply_id%~) BEGIN
			SPRINT apply_resref $fx_resource_lower(~%apply_id%~)
			PATCH_IF $fx_external(~%apply_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~not_implemented:opcode326:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
				SPRINT apply_scope $fx_scope(~%apply_id%~)
				PHP_EACH fx_ids_326 AS _ => apply_other BEGIN
					SPRINT apply_other_scope $fx_scope(~%apply_other%~)
					SPRINT apply_other_resref $fx_resource_lower(~%apply_other%~)
					PATCH_IF apply_other != apply_id AND NOT $fx_consumed(~%apply_other%~) AND (~%apply_other_scope%~ STRING_EQUAL ~%apply_scope%~) AND (~%apply_other_resref%~ STRING_EQUAL ~%apply_resref%~) BEGIN
						LPF ad_refusal INT_VAR fx_id = apply_other STR_VAR reason = ~not_implemented:opcode326:group~ message = ~several opcode 326 casting the same spell~ RET render_missing = refusal END
					END
				END
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
				LPM ad_op_326_condition
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
				SET recursion_fx = apply_id
				SPRINT recursion_resref ~%apply_resref%~
				SET recursion_casting_level = 0
				SPRINT recursion_targets ~effect~
				SET recursion_ignore_duration = 0
				SET recursion_series = 0
				SET recursion_tracked = 1
				SET recursion_depth_reset = 1
				SPRINT recursion_kind ~spl~
				SET recursion_parent_dice = 0
				SET recursion_versus_set = 0
				SPRINT recursion_versus ~~
				SPRINT recursion_single_reason ~~
				PATCH_IF ~%apply_condition%~ STRING_EQUAL ~~ BEGIN
					SPRINT recursion_single_reason ~not_implemented:opcode326:no_condition~
					SPRINT recursion_single_message ~several lines without a condition text~
				END
				LPM ad_recursion_support
			END
		END
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
// autre variable (statistique, compétence, élément…).
DEFINE_PATCH_MACRO ad_op_326_condition BEGIN
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
			LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~not_implemented:opcode326:condition~ message = ~no condition text for SPLPROT.2DA row %apply_row% (stat %apply_stat%, value %apply_value%, relation %apply_relation%)~ RET render_missing = refusal END
		END
		ELSE PATCH_IF apply_stat == 258 OR apply_stat == 262 OR apply_stat == 263 OR apply_stat == 269 OR apply_stat == 270
				OR apply_stat == 272 OR apply_stat == 274 BEGIN
			LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~not_implemented:opcode326:condition_stat~ message = ~stat %apply_stat% of SPLPROT.2DA row %apply_row% written differently by the old engine~ RET render_missing = refusal END
		END
		ELSE PATCH_IF apply_stat >= 266 AND apply_stat <= 273 BEGIN
			LPF ad_ids_name INT_VAR ids_file = apply_stat - 264 entry = apply_value RET idName = name END
			PATCH_IF ~%idName%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~not_implemented:opcode326:ids~ message = ~value %apply_value% of stat %apply_stat% has no name~ RET render_missing = refusal END
			END
		END
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET apply_tra = $AD_STAT_CONDITION(~%apply_key%~) + 10000000
			PATCH_IF $AD_STAT_CONDITION_ADD_RELATION(~%apply_key%~) BEGIN
				SET apply_tra += apply_relation
			END
			PATCH_IF NOT TRA_ENTRY_EXISTS (~%apply_tra%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = apply_id STR_VAR reason = ~not_implemented:opcode326:condition_text~ message = ~no condition sentence %apply_tra%~ RET render_missing = refusal END
			END
		END
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
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
		PATCH_IF NOT $fx_consumed(~%apply_id%~) AND $fx_sub_count(~%apply_id%~) > 0 BEGIN
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
