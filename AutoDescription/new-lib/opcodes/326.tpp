// Opcode 326 (Apply Effects List, EE) : sort resource appliqué à la cible si elle remplit la condition
// de la ligne parameter2 de splprot.2da (ancien opcode_self_326) : « Si l'état de la cible est « mort » ;
// Ressuscite la cible ». Le sort est décrit par ses effets (new-lib/recursion.tpp), qui reprennent les
// chaînes de cible de l'effet ; la durée de l'effet n'est pas écrite (ancien ignoreDuration). L'ancien
// moteur décrit ce sort sans limite de profondeur (recursivity remise à 0) : un 326 d'un sous-sort est
// décrit, un 146 du sort appliqué ne l'est pas (recursion_depth_reset).

// Avec AD_ENABLE_SHRINKAGE, les 326 de même portée vers le même sort dont la condition est un type
// de créature n'en font qu'un (ancien opcode_326_group, ad_op_326_versus_group) : le premier les
// réunit sans condition et ses sous-effets les visent (ctx_versus) : « Inflige 1d4 points de dégâts
// magiques contre les fées, les ombres et les esprits » ; les autres sont écartés. Sans condition à
// écrire (« EA >= 0 »), les lignes du sort suivent celles de l'objet, comme celles d'un sort lancé
// (D2WKBS3S).

// Refus : effet d'un EFF ; condition refusée (ad_op_326_condition) ; refus de ad_recursion_support.
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
			PATCH_IF apply_delayed AND ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_dropped(~%apply_id%~) BEGIN
				SPRINT apply_pending $fx_condition_refusal(~%apply_id%~)
				PATCH_IF ~%apply_pending%~ STRING_EQUAL ~~ BEGIN
					SPRINT $fx_condition_refusal(~%apply_id%~) ~not_implemented:opcode326:delayed~
					SPRINT $fx_condition_refusal_message(~%apply_id%~) ~delayed effect~
				END
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_dropped(~%apply_id%~) BEGIN
				SET recursion_fx = apply_id
				SPRINT recursion_resref ~%apply_resref%~
				SET recursion_casting_level = 0
				SPRINT recursion_targets ~effect~
				SET recursion_ignore_duration = 0
				SET recursion_series = 0
				SET recursion_depth_reset = 1
				SET recursion_delayed = apply_delayed
				// Effet probable : sa probabilité passe aux sous-effets, regroupés par probabilité, dans un objet comme dans
				// un sort (ancien opcode_self_probability_326, baseProbability).
				SET recursion_probability = 1
				SPRINT recursion_kind ~spl~
				SET recursion_parent_dice = 0
				SET recursion_versus_set = apply_versus_set
				SPRINT recursion_versus ~%apply_versus%~
				SPRINT recursion_single_reason ~~
				LPM ad_recursion_support
			END
		END
	END
END

// 326 de la portée de apply_id vers son sort, dont la condition est un type de créature nommé et
// dont les champs que la ligne écrit sont les siens (la puissance et la résistance ne s'écrivent
// pas, C2STAF01) : réunis à lui s'ils sont plusieurs (apply_versus_set, apply_versus) ; les autres
// gardent leur propre ligne, comme dans l'ancien moteur, qui ne réunit que les conditions de sa table.
DEFINE_PATCH_MACRO ad_op_326_versus_group BEGIN
	SPRINT apply_scope $fx_scope(~%apply_id%~)
	SET apply_members = 0
	CLEAR_ARRAY apply_versus_names
	CLEAR_ARRAY apply_versus_members
	SET apply_type_id = apply_id
	LPM ad_op_326_creature_type
	PATCH_IF NOT ~%apply_type_name%~ STRING_EQUAL ~~ BEGIN
		SET same_id = apply_id
		SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2 BOR AD_SAME_POWER BOR AD_SAME_RESISTANCE
		PHP_EACH fx_ids_326 AS _ => apply_other BEGIN
			SPRINT apply_other_scope $fx_scope(~%apply_other%~)
			SPRINT apply_other_resref $fx_resource_lower(~%apply_other%~)
			PATCH_IF NOT $fx_consumed(~%apply_other%~) AND NOT $fx_external(~%apply_other%~) AND (~%apply_other_scope%~ STRING_EQUAL ~%apply_scope%~)
					AND (~%apply_other_resref%~ STRING_EQUAL ~%apply_resref%~) BEGIN
				SET same_other = apply_other
				LPM ad_fx_same_fields
				SET apply_type_id = apply_other
				LPM ad_op_326_creature_type
				PATCH_IF fx_same AND NOT ~%apply_type_name%~ STRING_EQUAL ~~ BEGIN
					SPRINT $apply_versus_names(~%apply_type_name%~) ~%apply_type_name%~
					SET $apply_versus_members(~%apply_other%~) = 1
					SET apply_members += 1
				END
			END
		END
	END
	PATCH_IF apply_members > 1 BEGIN
		PHP_EACH apply_versus_members AS apply_other => _ BEGIN
			PATCH_IF apply_other != apply_id BEGIN
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

// Type de créature de la condition de l'effet apply_type_id (apply_type_name, vide s'il n'en a pas) :
// ligne de splprot.2da qui teste l'égalité d'une statistique de fichier IDS, valeur fixée par la
// table (64 : RACE=ORC) ou parameter1 (102 à 107), ou les bits d'alignement de parameter1 (108).
DEFINE_PATCH_MACRO ad_op_326_creature_type BEGIN
	SPRINT apply_type_name ~~
	SET apply_type_row = $fx_parameter2_raw(~%apply_type_id%~)
	PATCH_IF VARIABLE_IS_SET $AD_SPLPROT_STAT(~%apply_type_row%~) BEGIN
		SPRINT apply_type_stat $AD_SPLPROT_STAT(~%apply_type_row%~)
		SPRINT apply_type_value $AD_SPLPROT_VALUE(~%apply_type_row%~)
		SPRINT apply_type_relation $AD_SPLPROT_RELATION(~%apply_type_row%~)
		PATCH_IF IS_AN_INT apply_type_stat AND IS_AN_INT apply_type_value AND IS_AN_INT apply_type_relation BEGIN
			PATCH_IF (apply_type_stat >= 266 AND apply_type_stat <= 271 AND apply_type_relation == 1)
					OR (apply_type_stat == 272 AND apply_type_relation == 8 AND apply_type_value == 0 - 1) BEGIN
				PATCH_IF apply_type_value == 0 - 1 BEGIN
					SET apply_type_value = $fx_parameter1(~%apply_type_id%~)
				END
				LPF ad_ids_name INT_VAR ids_file = apply_type_stat - 264 entry = apply_type_value RET apply_type_name = name END
			END
		END
	END
END

// Condition de l'effet apply_id (ancien opcode_326_condition) : $fx_condition_text, vide pour une
// ligne de splprot.2da sans condition à écrire (« EA >= 0 »). Statistique, valeur (celle de la
// table, ou parameter1 pour - 1) et relation de la ligne donnent la chaîne de stats.2da, de la clé la
// plus précise à la plus générale ; une chaîne reprise de l'ancien fichier (@13260000-@13269999 ->
// @23260000-@23269999) n'utilise que les chaînes de cible et, pour les statistiques d'un fichier IDS
// (266 à 268, 271, 273), le nom de la valeur (idName), pour la taille, la classe, l'alignement et
// l'état de sort, le leur (ad_op_326_condition_name) et, pour les phrases génériques, le nom de la
// statistique (theStatistic) et la valeur (value). Refus : ligne absente ou inutilisée ; aucune
// clé dans stats.2da (l'ancien moteur garde la condition précédente) ; statistique que l'ancien moteur
// écrit autrement (263 heure, 270 type précis) ou d'un fichier IDS mal calculé (262) ; valeur sans
// nom ; statistique sans nom ; chaîne non
// reprise, qui utilise une autre variable (compétence, élément…). Hors erreur de fichier, le refus attend les
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
		SET drop_id = apply_id
		SPRINT ignored_reason ~file_error:opcode326:splprot~
		SPRINT ignored_message ~row %apply_row% of SPLPROT.2DA is missing or unused~
		LPM ad_application_drop
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
		// État de sort sans nom, propre à un mod (2da/stats_mods.2da, comme l'ancien moteur qui ne lit cette table
		// que pour un état sans nom) : sa phrase, avec le nom de la valeur s'il en a un (« un golem
		// d'argile », liste @8190000 : 8 190 000 + chaîne de l'ancien fichier - 800 000).
		SET apply_mod_tra = 0
		SET apply_mod_value_name = 0
		SET apply_splstate_tra = 8120000 + apply_value
		PATCH_IF apply_stat == 274 AND NOT TRA_ENTRY_EXISTS (~%apply_splstate_tra%~) BEGIN
			LOOKUP_IDS_SYMBOL_OF_INT apply_symbol ~SPLSTATE~ apply_value
			TO_UPPER apply_symbol
			PATCH_IF VARIABLE_IS_SET $AD_STAT_MOD_CONDITION(~274-%apply_symbol%~) BEGIN
				SET apply_mod_tra = $AD_STAT_MOD_CONDITION(~274-%apply_symbol%~) + 10000000
				PATCH_IF $AD_STAT_MOD_ADD_RELATION(~274-%apply_symbol%~) BEGIN
					SET apply_mod_tra += apply_relation
				END
				SET apply_mod_value_name = $AD_STAT_MOD_VALUE_NAME(~274-%apply_symbol%~)
			END
		END
		PATCH_IF apply_mod_tra > 0 BEGIN
			SET apply_tra = apply_mod_tra
			SET apply_mod_value_tra = 8190000 + apply_mod_value_name - 800000
			PATCH_IF NOT TRA_ENTRY_EXISTS (~%apply_tra%~) BEGIN
				SPRINT apply_pending ~not_implemented:opcode326:condition_text~
				SPRINT apply_pending_message ~no condition sentence %apply_tra%~
			END
			ELSE PATCH_IF apply_mod_value_name > 0 AND (apply_mod_value_name < 800000 OR apply_mod_value_name > 800999 OR NOT TRA_ENTRY_EXISTS (~%apply_mod_value_tra%~)) BEGIN
				SPRINT apply_pending ~not_implemented:opcode326:value_name~
				SPRINT apply_pending_message ~no name for value %apply_symbol% of stat %apply_stat% (string %apply_mod_value_name% of STATS_MODS.2DA)~
			END
			ELSE PATCH_IF apply_mod_value_name > 0 BEGIN
				LPF ad_tra INT_VAR tra_id = apply_mod_value_tra tra_block_start = 8190000 tra_block_size = 1000 RET stateValue = text END // ~un golem d'argile~ (@8190004)
			END
		END
		ELSE PATCH_IF NOT VARIABLE_IS_SET $AD_STAT_CONDITION(~%apply_key%~) BEGIN
			SPRINT apply_pending ~not_implemented:opcode326:condition~
			SPRINT apply_pending_message ~no condition text for SPLPROT.2DA row %apply_row% (stat %apply_stat%, value %apply_value%, relation %apply_relation%)~
		END
		ELSE PATCH_IF apply_stat == 262 OR apply_stat == 263 OR apply_stat == 270 BEGIN
			SPRINT apply_pending ~not_implemented:opcode326:condition_stat~
			SPRINT apply_pending_message ~stat %apply_stat% of SPLPROT.2DA row %apply_row% written differently by the old engine~
		END
		ELSE PATCH_IF apply_stat >= 266 AND apply_stat <= 273 AND apply_stat != 269 AND apply_stat != 272 BEGIN
			LPF ad_ids_name INT_VAR ids_file = apply_stat - 264 entry = apply_value RET idName = name END
			PATCH_IF ~%idName%~ STRING_EQUAL ~~ BEGIN
				SPRINT apply_pending ~not_implemented:opcode326:ids~
				SPRINT apply_pending_message ~value %apply_value% of stat %apply_stat% has no name~
			END
		END
		PATCH_IF ~%apply_pending%~ STRING_EQUAL ~~ AND apply_mod_tra == 0 BEGIN
			SET apply_tra = $AD_STAT_CONDITION(~%apply_key%~) + 10000000
			SET apply_stat_tra = apply_stat + 8060000
			PATCH_IF $AD_STAT_CONDITION_ADD_RELATION(~%apply_key%~) BEGIN
				SET apply_tra += apply_relation
			END
			PATCH_IF NOT TRA_ENTRY_EXISTS (~%apply_tra%~) BEGIN
				SPRINT apply_pending ~not_implemented:opcode326:condition_text~
				SPRINT apply_pending_message ~no condition sentence %apply_tra%~
			END
			// Phrases génériques d'une statistique (@23269000-@23269005, au masculin @23269020-@23269025) : son nom à la forme « cible »,
			// dans la liste des statistiques (8 060 000 + valeur de stats.ids).
			ELSE PATCH_IF ((apply_tra >= 23269000 AND apply_tra <= 23269005) OR (apply_tra >= 23269020 AND apply_tra <= 23269025)) AND NOT TRA_ENTRY_EXISTS (~%apply_stat_tra%~) BEGIN
				SPRINT apply_pending ~not_implemented:opcode326:statistic_name~
				SPRINT apply_pending_message ~stat %apply_stat% has no name~
			END
			ELSE PATCH_IF apply_stat == 258 OR apply_stat == 269 OR apply_stat == 272 OR apply_stat == 274 BEGIN
				LPM ad_op_326_condition_name
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
			PATCH_IF ((apply_tra >= 23269000 AND apply_tra <= 23269005) OR (apply_tra >= 23269020 AND apply_tra <= 23269025)) BEGIN
				LPF ad_tra INT_VAR tra_id = apply_stat_tra tra_block_start = 8060000 tra_block_size = 10000 RET theStatistic = text END // ~la force~ (@8060036)
				SPRINT value ~%apply_value%~
			END
			LPF ad_tra INT_VAR tra_id = apply_tra tra_block_start = 23260000 tra_block_size = 10000 RET apply_condition = text END // ~Si l'état %ofTheTarget% est « mort »~ (@23260181)
		END
	END
	SPRINT $fx_condition_text(~%apply_id%~) ~%apply_condition%~
END

// Nom de la valeur des statistiques dont l'ancien moteur écrit la condition avec sa propre variable :
// taille (258, sizeName), classe et alignement au singulier (269 className, 272 alignName : « clerc »,
// « mauvais » ; listes @8095500 et @8098500), état de sort (274, splstateName). La taille va de 1
// (minuscule) à 4 (gigantesque) : comme dans l'ancien moteur, une borne large devient stricte
// (« inférieure ou égale à grande » : « inférieure à gigantesque »), « supérieure à grande » devient
// « gigantesque ». Valeur sans nom : refus.
DEFINE_PATCH_MACRO ad_op_326_condition_name BEGIN
	SET apply_name_min = 0
	SET apply_name_max = 255
	PATCH_IF apply_stat == 258 BEGIN
		PATCH_IF apply_relation == 0 AND apply_value < 4 BEGIN
			SET apply_tra = 23269382 // ~Si %theTarget% est de taille inférieure à %sizeName%~
			SET apply_value += 1
		END
		ELSE PATCH_IF apply_relation == 3 AND apply_value == 3 BEGIN
			SET apply_tra = 23269381 // ~Si %theTarget% est de taille %sizeName%~
			SET apply_value += 1
		END
		ELSE PATCH_IF apply_relation == 4 AND apply_value > 1 BEGIN
			SET apply_tra = 23269383 // ~Si %theTarget% est de taille supérieure à %sizeName%~
			SET apply_value -= 1
		END
		SET apply_name_min = 1
		SET apply_name_max = 4
		SET apply_name_base = 23268010
		SET apply_name_block = 23260000
		SET apply_name_block_size = 10000
	END
	ELSE PATCH_IF apply_stat == 274 BEGIN
		SET apply_name_base = 8120000
		SET apply_name_block = 8120000
		SET apply_name_block_size = 256
	END
	ELSE BEGIN
		SET apply_name_base = (apply_stat == 269) ? 8095500 : 8098500
		SET apply_name_block = 8090000
		SET apply_name_block_size = 10000
	END
	SET apply_name_tra = apply_name_base + apply_value
	PATCH_IF apply_value < apply_name_min OR apply_value > apply_name_max OR NOT TRA_ENTRY_EXISTS (~%apply_name_tra%~) BEGIN
		SPRINT apply_pending ~not_implemented:opcode326:value_name~
		SPRINT apply_pending_message ~value %apply_value% of stat %apply_stat% has no name~
	END
	ELSE BEGIN
		LPF ad_tra INT_VAR tra_id = apply_name_tra tra_block_start = apply_name_block tra_block_size = apply_name_block_size RET apply_name = text END // ~clerc~ (@8095503)
		PATCH_IF apply_stat == 258 BEGIN
			SPRINT sizeName ~%apply_name%~
		END
		ELSE PATCH_IF apply_stat == 269 BEGIN
			SPRINT className ~%apply_name%~
		END
		ELSE PATCH_IF apply_stat == 272 BEGIN
			SPRINT alignName ~%apply_name%~
		END
		ELSE BEGIN
			SPRINT splstateName ~%apply_name%~
		END
	END
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
			SPRINT line_condition $fx_condition_text(~%apply_id%~)
			PATCH_IF ~%line_condition%~ STRING_EQUAL ~~ BEGIN
				SPRINT line_text $fx_sub_text(~%apply_id%~)
			END
			ELSE BEGIN
				LPM ad_recursion_condition_text
			END
			SET line_any_form = 1
			SET line_no_duration = 1
			SET line_fx = apply_id
			LPM ad_effect_line
		END
	END
END
