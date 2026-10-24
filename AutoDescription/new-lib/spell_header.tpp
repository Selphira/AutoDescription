// En-tête d'un sort (ancien get_spell_description, lib/spl.tpp et lib/spl/misc.tpp, sans la section
// « PARAMÈTRES ») : nom, type et école, niveau, portée, durée, temps d'incantation, zone d'effet, jet
// de sauvegarde, dissipation et résistance à la magie, puis le texte d'origine sans son ancien bloc
// technique et la mention de Zone d'air pur. La durée, le jet de sauvegarde et la résistance se
// lisent, comme dans l'ancien moteur, sur les effets d'en-tête qui restent après sa chaîne
// (validation, remplacements, regroupements : ad_spell_header_pipeline), en-tête par en-tête, dans
// l'ordre de son tableau leveled_opcodes (ad_spell_header_effects).
//
// Tableaux écrits (portée de l'appelant) : spell_level, spell_target, spell_target_count,
// spell_range, spell_casting_time, spell_projectile (champs de l'en-tête h) ; spell_fx_count(h) et
// spell_fx_<h>(rang), effets restants de l'en-tête h.

// Champs des en-têtes du sort chargé dans le magasin.
DEFINE_PATCH_MACRO ad_spell_header_fields BEGIN
	FOR (header_h = 0; header_h < fx_header_count; ++header_h) BEGIN
		SET header_offset = fx_headers_offset + header_h * 0x28
		READ_SHORT (header_offset + SPL_HEAD_level_required) $spell_level(~%header_h%~)
		READ_BYTE  (header_offset + SPL_HEAD_target)         $spell_target(~%header_h%~)
		READ_BYTE  (header_offset + SPL_HEAD_target_number)  $spell_target_count(~%header_h%~)
		READ_SHORT (header_offset + SPL_HEAD_range)          $spell_range(~%header_h%~)
		READ_SHORT (header_offset + SPL_HEAD_casting_time)   $spell_casting_time(~%header_h%~)
		READ_SHORT (header_offset + SPL_HEAD_projectile)     $spell_projectile(~%header_h%~)
	END
END

// Chaîne des effets des en-têtes du sort chargé (son bloc de lancement n'est pas lu,
// fx_with_casting = 0), comme pour un objet, sans phrases pour l'en-tête seul (support_header_only) :
// effets que l'ancien moteur écarte dès leur lecture (ad_spell_header_keeps), prise en charge
// commune et de chaque opcode décrit, regroupements. Un effet écarté ou réuni à d'autres est
// consommé (fx_consumed) ; celui que seul l'en-tête ne compte plus est caché (fx_header_hidden).
// Avec les phrases, les effets d'un sort qui vise le lanceur sans zone visent le lanceur
// (spell_self_target, ancien globalSpellTarget). Rien n'est écrit : les lignes viennent après
// l'en-tête (ad_spell_statistics).
// header_missing : refus d'un cas dont on ne sait pas quels effets l'ancien moteur garde.
DEFINE_PATCH_MACRO ad_spell_header_pipeline BEGIN
	// Opcodes dans l'ordre numérique, comme pour la ressource décrite (ad_set_coverage) : un sous-sort
	// est chargé sans elle.
	SORT_ARRAY_INDICES fx_opcode_count NUMERICALLY
	SPRINT render_missing ~~
	SPRINT render_late_missing ~~
	// Un en-tête de sort n'est pas une capacité de charge (ancien abilityType négatif) : un sort nommé
	// qu'il lance est « Lance « X » sur la cible » (new-lib/opcodes/cast_spell.tpp).
	FOR (header_h = 0; header_h < fx_header_count; ++header_h) BEGIN
		SET $charged_other(~%header_h%~) = 1
		SET $charged_global_duration(~%header_h%~) = 0
	END
	FOR (header_id = 0; header_id < fx_count; ++header_id) BEGIN
		LPM ad_spell_header_keeps
		// Une exception de cible est écartée après la lecture de ses noms, que les lignes écrivent
		// (ad_target_exception_support) : seul l'en-tête l'ignore.
		SET $fx_header_hidden(~%header_id%~) = NOT keep_effect
		PATCH_IF NOT keep_effect AND (support_header_only OR NOT $fx_exception(~%header_id%~)) BEGIN
			SET $fx_consumed(~%header_id%~) = 1
			SET $fx_dropped(~%header_id%~) = 1
		END
	END
	PHP_EACH fx_opcode_count AS header_opcode => _ BEGIN
		PATCH_IF VARIABLE_IS_SET $AD_OPCODES_OLD_FILTERED(~%header_opcode%~) AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			PHP_EACH ~fx_ids_%header_opcode%~ AS _ => header_id BEGIN
				PATCH_IF NOT $fx_consumed(~%header_id%~) AND ~%render_missing%~ STRING_EQUAL ~~ BEGIN
					LPF ad_refusal INT_VAR fx_id = header_id STR_VAR reason = ~not_implemented:spell_header:opcode%header_opcode%~ message = ~opcode %header_opcode% not supported yet, whose effects the old engine may drop or merge before reading the header~ RET render_missing = refusal END
				END
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_application_support
	END
	PHP_EACH fx_opcode_count AS render_opcode => _ BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			LPM ad_opcode_is_described
			PATCH_IF opcode_described BEGIN
				LPM ~ad_op_%render_opcode%_support~
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT support_header_only AND spell_self_target BEGIN
		FOR (header_id = 0; header_id < fx_count; ++header_id) BEGIN
			PATCH_IF $fx_effective_target(~%header_id%~) == TARGET_FX_preset BEGIN
				SET $fx_effective_target(~%header_id%~) = TARGET_FX_self
			END
		END
	END
	SET derived_count = 0
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_cross_groups
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~321~) AND VARIABLE_IS_SET $fx_opcode_count(~206~) BEGIN
			LPM ad_op_321_after_groups
		END
		PATCH_IF AD_ENABLE_SHRINKAGE AND VARIABLE_IS_SET $fx_opcode_count(~206~) BEGIN
			LPM ad_op_206_header_groups
		END
	END
	PATCH_IF NOT (~%render_missing%~ STRING_EQUAL ~~) AND ~%header_missing%~ STRING_EQUAL ~~ BEGIN
		SPRINT header_missing ~%render_missing%~
	END
END

// Effets restants de chaque en-tête, dans l'ordre de l'ancien moteur : opcodes dans l'ordre de leur
// premier effet, puis effets de chaque opcode dans l'ordre de lecture ; les effets remplacés par
// ceux d'un EFF (177) ou d'une arme (111) viennent après les autres, l'ancien moteur les ajoutant une
// fois l'en-tête lu (opcode_177_replace, opcode_111_replace), de même que l'effet qui en représente
// plusieurs identiques (fx_late, ancien opcode_group_by_target) ou une série (fx_series_anchor,
// ancien opcode_group_by_duration) ; les effets dérivés des regroupements (ad_derived_add,
// new-lib/groups.tpp), avec l'opcode virtuel de l'ancien moteur, viennent en dernier. Les effets d'un
// en-tête se suivent dans le magasin : chacun n'est parcouru que dans ses bornes (header_first,
// header_end).
DEFINE_PATCH_MACRO ad_spell_header_effects BEGIN
	FOR (header_h = 0; header_h < fx_header_count; ++header_h) BEGIN
		SET $header_first(~%header_h%~) = 0
		SET $header_end(~%header_h%~) = 0
	END
	FOR (header_id = fx_count - 1; header_id >= 0; --header_id) BEGIN
		SET header_h = $fx_header(~%header_id%~)
		PATCH_IF header_h >= 0 BEGIN
			SET $header_first(~%header_h%~) = header_id
			PATCH_IF $header_end(~%header_h%~) == 0 BEGIN
				SET $header_end(~%header_h%~) = header_id + 1
			END
		END
	END
	FOR (header_h = 0; header_h < fx_header_count; ++header_h) BEGIN
		SET header_opcodes = 0
		FOR (header_pass = 0; header_pass < 2; ++header_pass) BEGIN
			FOR (header_id = $header_first(~%header_h%~); header_id < $header_end(~%header_h%~); ++header_id) BEGIN
				PATCH_IF NOT $fx_consumed(~%header_id%~) AND NOT $fx_header_hidden(~%header_id%~)
						AND ($fx_external(~%header_id%~) OR $fx_from_111(~%header_id%~)) == header_pass BEGIN
					SET header_opcode = $fx_opcode(~%header_id%~)
					SET header_k = 0
					WHILE header_k < header_opcodes AND $header_opcode_order(~%header_k%~) != header_opcode BEGIN
						SET header_k += 1
					END
					PATCH_IF header_k == header_opcodes BEGIN
						SET $header_opcode_order(~%header_k%~) = header_opcode
						SET $header_opcode_size(~%header_k%~) = 0
						SET $header_opcode_late(~%header_k%~) = 0
						SET header_opcodes += 1
					END
					PATCH_IF $fx_late(~%header_id%~) OR $fx_series_anchor(~%header_id%~) BEGIN
						SET header_size = $header_opcode_late(~%header_k%~)
						SET $EVAL ~header_late_%header_k%~(~%header_size%~) = header_id
						SET $header_opcode_late(~%header_k%~) = header_size + 1
					END
					ELSE BEGIN
						SET header_size = $header_opcode_size(~%header_k%~)
						SET $EVAL ~header_opcode_%header_k%~(~%header_size%~) = header_id
						SET $header_opcode_size(~%header_k%~) = header_size + 1
					END
				END
			END
		END
		SET header_kept = 0
		FOR (header_k = 0; header_k < header_opcodes; ++header_k) BEGIN
			SET header_opcode = $header_opcode_order(~%header_k%~)
			FOR (header_n = 0; header_n < $header_opcode_size(~%header_k%~); ++header_n) BEGIN
				SET $EVAL ~spell_fx_%header_h%~(~%header_kept%~) = $EVAL ~header_opcode_%header_k%~(~%header_n%~)
				SET $EVAL ~spell_fx_opcode_%header_h%~(~%header_kept%~) = header_opcode
				SET $EVAL ~spell_fx_derived_%header_h%~(~%header_kept%~) = 0 - 1
				SET header_kept += 1
			END
			FOR (header_n = 0; header_n < $header_opcode_late(~%header_k%~); ++header_n) BEGIN
				SET $EVAL ~spell_fx_%header_h%~(~%header_kept%~) = $EVAL ~header_late_%header_k%~(~%header_n%~)
				SET $EVAL ~spell_fx_opcode_%header_h%~(~%header_kept%~) = header_opcode
				SET $EVAL ~spell_fx_derived_%header_h%~(~%header_kept%~) = 0 - 1
				SET header_kept += 1
			END
		END
		FOR (header_k = 0; header_k < derived_count; ++header_k) BEGIN
			SET header_id = $derived_id(~%header_k%~)
			PATCH_IF $fx_header(~%header_id%~) == header_h BEGIN
				SPRINT header_derived_kind $derived_kind(~%header_k%~)
				SET $EVAL ~spell_fx_%header_h%~(~%header_kept%~) = header_id
				SET $EVAL ~spell_fx_opcode_%header_h%~(~%header_kept%~) = $AD_DERIVED_OLD_OPCODE(~%header_derived_kind%~)
				SET $EVAL ~spell_fx_derived_%header_h%~(~%header_kept%~) = header_k
				SET header_kept += 1
			END
		END
		SET $spell_fx_count(~%header_h%~) = header_kept
	END
END

// L'ancien moteur garde-t-il l'effet header_id à sa lecture (load_opcode, partie commune de
// opcode_is_valid, opcode_177_replace) ? keep_effect : 1 si oui. Il écarte les opcodes ignorés, les
// effets sans probabilité, de cible absente ou invalide, d'une durée limitée nulle (sauf pour un
// opcode dont la durée ne compte pas), les opcodes propres à l'EE sur un jeu classique, ceux qui
// exigent des paramètres nuls, et les opcodes 318, 321 et 324 qui visent le sort lui-même.
// spell_self : sort décrit, en minuscules (celui du sommet pour un sous-sort).
DEFINE_PATCH_MACRO ad_spell_header_keeps BEGIN
	SET keep_opcode = $fx_opcode(~%header_id%~)
	SPRINT keep_status ~~
	SPRINT keep_duration ~~
	PATCH_IF VARIABLE_IS_SET $AD_OPCODE_STATUS(~%keep_opcode%~) BEGIN
		SPRINT keep_status $AD_OPCODE_STATUS(~%keep_opcode%~)
		SPRINT keep_duration $AD_OPCODE_DURATION(~%keep_opcode%~)
	END
	SPRINT keep_error ~~
	PATCH_IF $fx_external(~%header_id%~) OR keep_opcode == 177 BEGIN
		SPRINT keep_error $fx_substitution_error(~%header_id%~)
	END
	SPRINT keep_resource $fx_resource_lower(~%header_id%~)
	SET keep_self = ~%keep_resource%~ STRING_EQUAL ~%spell_self%~
	SET keep_target = $fx_target(~%header_id%~)
	SET keep_effect = NOT (~%keep_status%~ STRING_EQUAL ~IGNORED~)
		AND (~%keep_error%~ STRING_EQUAL ~~)
		AND $fx_probability(~%header_id%~) > 0
		AND keep_target > 0 AND keep_target <= 9
		AND NOT ($fx_timing(~%header_id%~) == TIMING_duration AND $fx_duration(~%header_id%~) <= 0 AND NOT (~%keep_duration%~ STRING_EQUAL ~IGNORED~))
		AND NOT (NOT IS_EE AND keep_opcode >= 319 AND keep_opcode <= 367)
		AND NOT (NOT IS_EE AND (keep_opcode == 4 OR keep_opcode == 43 OR keep_opcode == 47 OR keep_opcode == 56)
			AND ($fx_parameter1(~%header_id%~) != 0 OR $fx_parameter2(~%header_id%~) != 0))
		AND NOT (keep_opcode == 321 AND keep_self AND ($fx_timing(~%header_id%~) != TIMING_duration OR $fx_duration(~%header_id%~) != 0))
		AND NOT ((keep_opcode == 318 OR keep_opcode == 324) AND keep_self AND ($fx_parameter1(~%header_id%~) != 0 OR $fx_parameter2(~%header_id%~) != 0))
	// Un 177 dont l'EFF est écarté (drop) disparaît ; une autre erreur de remplacement laisse un
	// effet que l'ancien moteur décrit autrement.
	PATCH_IF NOT (~%keep_error%~ STRING_EQUAL ~~) AND NOT (~%keep_error%~ STRING_EQUAL ~drop~) AND ~%header_missing%~ STRING_EQUAL ~~ BEGIN
		LPF ad_refusal INT_VAR fx_id = header_id STR_VAR reason = ~not_implemented:spell_header:opcode177_%keep_error%~ message = ~effect of an EFF file that the old engine keeps in another form: header block not supported~ RET header_missing = refusal END
	END
END

// Refus des cas que ce rendu ne sait pas reproduire (header_missing, vide sinon), avant le rendu :
// sort sans en-tête, plusieurs en-têtes dont les niveaux ne croissent pas à partir de 1 (absents du
// jeu de base), types, écoles et types
// secondaires sans nom, refus de la chaîne des effets.
DEFINE_PATCH_MACRO ad_spell_header_support BEGIN
	SPRINT header_missing ~~
	SPRINT spell_self ~%SOURCE_RES%~
	TO_LOWER spell_self
	LPM ad_spell_header_fields
	PATCH_IF fx_header_count == 0 BEGIN
		LPF ad_refusal STR_VAR reason = ~not_implemented:spell_header:no_ability~ message = ~spell without ability: header block not supported~ RET header_missing = refusal END
	END
	FOR (header_h = 1; header_h < fx_header_count AND ~%header_missing%~ STRING_EQUAL ~~; ++header_h) BEGIN
		SET header_previous = header_h - 1
		PATCH_IF $spell_level(~%header_h%~) <= $spell_level(~%header_previous%~) OR $spell_level(~0~) > 1 BEGIN
			LPF ad_refusal STR_VAR reason = ~not_implemented:spell_header:ability_levels~ message = ~abilities whose required levels do not grow from level 1: not supported~ RET header_missing = refusal END
		END
	END
	READ_SHORT SPL_type    spell_type
	READ_LONG  SPL_sectype spell_sectype
	READ_BYTE  SPL_school  spell_school
	PATCH_IF ~%header_missing%~ STRING_EQUAL ~~ BEGIN
		SET spell_type_name = spell_type
		PATCH_IF spell_type == 2 BEGIN
			READ_LONG SPL_exclusion_flags spell_exclusions
			SET spell_no_cleric = (spell_exclusions BAND BIT30) != 0
			SET spell_no_druid = (spell_exclusions BAND BIT31) != 0
			PATCH_IF spell_no_cleric AND spell_no_druid BEGIN
				LPF ad_refusal STR_VAR reason = ~file_error:spell_header:priest_exclusions~ message = ~priest spell excluded for both clerics and druids (exclusion flags %spell_exclusions%)~ RET header_missing = refusal END
			END
			ELSE PATCH_IF spell_no_druid BEGIN
				SET spell_type_name = 6
			END
			ELSE PATCH_IF spell_no_cleric BEGIN
				SET spell_type_name = 7
			END
		END
		PATCH_IF spell_type_name < 0 OR spell_type_name > 7 BEGIN
			LPF ad_refusal STR_VAR reason = ~file_error:spell_header:type~ message = ~spell type %spell_type% (expected 0-5)~ RET header_missing = refusal END
		END
		ELSE PATCH_IF spell_school > 10 BEGIN
			LPF ad_refusal STR_VAR reason = ~file_error:spell_header:school~ message = ~spell school %spell_school% (expected 0-10)~ RET header_missing = refusal END
		END
		ELSE PATCH_IF spell_sectype < 0 OR spell_sectype > 13 BEGIN
			LPF ad_refusal STR_VAR reason = ~not_implemented:spell_header:secondary_type~ message = ~secondary type %spell_sectype% (msectype.ids values 0-13 supported)~ RET header_missing = refusal END
		END
	END
	PATCH_IF ~%header_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_spell_self_target
		LPM ad_spell_header_pipeline
		LPM ad_spell_header_effects
	END
END

// Le sort vise-t-il le lanceur sans zone (ancien spell_target : globalSpellTarget « self ») ?
// spell_self_target : 1 si le dernier en-tête sans zone de projectile qui vise le lanceur ou une
// créature vise le lanceur.
DEFINE_PATCH_MACRO ad_spell_self_target BEGIN
	SET spell_self_target = 0
	FOR (self_h = 0; self_h < fx_header_count; ++self_h) BEGIN
		LPF ad_projectile_area INT_VAR projectile = $spell_projectile(~%self_h%~) RET self_shape = area_shape END
		SET self_target = $spell_target(~%self_h%~)
		PATCH_IF self_shape <= 0 BEGIN
			PATCH_IF self_target == TARGET_HEAD_self OR self_target == TARGET_HEAD_self_ignore_pause BEGIN
				SET spell_self_target = 1
			END
			ELSE PATCH_IF self_target == TARGET_HEAD_creature OR self_target == TARGET_HEAD_character_portrait BEGIN
				SET spell_self_target = 0
			END
		END
	END
END

// Texte de l'en-tête, après ad_spell_header_support sans refus ; une valeur que ce rendu ne sait pas
// reproduire laisse sa raison dans header_missing.
DEFINE_PATCH_MACRO ad_spell_header_render BEGIN
	// L'ancien moteur n'a jamais %theTarget% dans la portée de l'en-tête, que la chaîne anglaise de la
	// zone d'effet garde telle quelle (@102455) ; les lignes le définissent, et une réécriture de la
	// description le remplacerait (V41) : un repère en tient la place jusqu'à la fin
	// (ad_describe_spell).
	SPRINT header_saved_target ~%theTarget%~
	SPRINT theTarget ~AD_THE_TARGET_MARK~
	READ_STRREF SPL_unidentified_name spell_name
	SPRINT description ~%spell_name%~
	LPM ad_spell_header_type_line
	SPRINT description ~%description%%CRLF%~
	PATCH_IF spell_type == 1 OR spell_type == 2 BEGIN
		READ_LONG SPL_level value
		SPRINT name @7000000 // ~Niveau~
		LPM ad_spell_header_value
	END
	LPM ad_spell_header_range
	LPM ad_spell_header_duration
	LPM ad_spell_header_casting_time
	LPM ad_spell_header_area
	SPRINT save_missing ~~
	LPF ad_spell_header_save RET save_text save_missing END
	PATCH_IF NOT (~%save_missing%~ STRING_EQUAL ~~) AND ~%header_missing%~ STRING_EQUAL ~~ BEGIN
		SPRINT header_missing ~%save_missing%~
	END
	SPRINT name @7000005 // ~Jet de sauvegarde~
	SPRINT value ~%save_text%~
	LPM ad_spell_header_value
	// Un jet « Spécial » est écrit par les lignes (ancien ignoreSavingThrow).
	SPRINT save_special_text @7000010 // ~Spécial~
	SET header_hide_save = NOT (~%save_text%~ STRING_EQUAL ~%save_special_text%~)
	LPM ad_spell_header_resistance
	LPF ad_spell_roleplay_text STR_VAR text = ~%original_description%~ name = ~%spell_name%~ RET roleplay = text END
	SPRINT description ~%description%%CRLF%%CRLF%%roleplay%~
	LPF ad_spell_dispellable_by_clearair RET header_clearair = dispellable END
	PATCH_IF header_clearair BEGIN
		// Retire la phrase que CorrectFR ajoute au texte d'origine, pour éviter une redite.
		SPRINT clearair_text @7000031 // ~Le nuage peut être dissipé avec le sort Zone d'air pur.~
		INNER_PATCH_SAVE description ~%description%~ BEGIN
			REPLACE_TEXTUALLY ~%clearair_text%~ ~~
		END
		SPRINT clearair_text @7000030 // ~La zone d'effet peut être dissipée à l'aide d'un sort de Zone d'air pur.~
		SPRINT description ~%description%%CRLF%%clearair_text%~
	END
	PATCH_IF ~%SOURCE_RES%~ STRING_EQUAL_CASE ~sppr318~ BEGIN
		LPM ad_spell_header_clearair_list
	END
	SPRINT theTarget ~%header_saved_target%~
END

// Ligne « nom : valeur » ajoutée à la description (ancien appendValue).
DEFINE_PATCH_MACRO ad_spell_header_value BEGIN
	SPRINT line @1200000 // ~%name%%AD_COLON%%value%~
	SPRINT description ~%description%%CRLF%%line%~
END

// « (Profane - Évocation, Dégâts offensifs) » : type (un sort divin réservé aux prêtres ou aux
// druides est dit « Divin » ou « Druidique »), école si elle n'est pas nulle, type secondaire s'il a
// un nom (en anglais, le type 0 en a un).
DEFINE_PATCH_MACRO ad_spell_header_type_line BEGIN
	LPF ad_tra INT_VAR tra_id = 8130000 + spell_type_name tra_block_start = 8130000 tra_block_size = 8 RET header_type = text END // ~Profane~ (@8130001)
	LPF ad_tra INT_VAR tra_id = 8100000 + spell_sectype tra_block_start = 8100000 tra_block_size = 14 RET header_sectype = text END // ~Dégâts offensifs~ (@8100010)
	SPRINT header_line ~%header_type%~
	PATCH_IF spell_school > 0 BEGIN
		LPF ad_tra INT_VAR tra_id = 8140000 + spell_school tra_block_start = 8140000 tra_block_size = 11 RET header_school = text END // ~Évocation~ (@8140006)
		SPRINT header_line ~%header_line% - %header_school%~
	END
	PATCH_IF NOT (~%header_sectype%~ STRING_EQUAL ~~) BEGIN
		SPRINT header_line ~%header_line%, %header_sectype%~
	END
	SPRINT description ~%description%%CRLF%(%header_line%)~
END

// Distance d'un en-tête de sort, donnée en pieds, comme l'ancien feets_to_meters : au-delà d'un
// mètre, comme ad_distance_text ; en deçà, l'ancien moteur écrit en français le nombre de décimètres
// comme des mètres (« 3 mètres » pour 1 pied), en anglais le nombre de pieds. distance_number : ce
// nombre, que la portée compare à 2 (« Contact » en deçà) ; 2 au-delà d'un mètre.
DEFINE_PATCH_FUNCTION ad_spell_distance_text
	INT_VAR
		feet = 0
	RET
		text
		distance_number
BEGIN
	LPF ad_distance_text INT_VAR feet RET text END
	SET distance_number = 2
	PATCH_IF ~%text%~ STRING_EQUAL ~~ BEGIN
		SET distance_feet = feet
		SET distance_decimeters = feet * 10000 / 3281
		LPF ad_tra INT_VAR tra_id = 1100010 + (distance_decimeters > 1 ? 1 : 0)
			tra_block_start = 1100010 tra_block_size = 2 RET text END // ~%distance_decimeters% mètre~
		SPRINT distance_number ~%text%~
		INNER_PATCH_SAVE distance_number ~%distance_number%~ BEGIN
			REPLACE_TEXTUALLY ~^\(-?[0-9]+\).*$~ ~\1~
		END
		PATCH_IF NOT IS_AN_INT distance_number BEGIN
			SET distance_number = 2
		END
	END
END

// Portée (ancien spell_range) : celle des en-têtes si elle est la même partout (0 pour un en-tête
// qui vise le lanceur), « Contact » en deçà de 2 unités écrites ; sinon une progression par niveau
// (ad_spell_header_range_progression).
DEFINE_PATCH_MACRO ad_spell_header_range BEGIN
	SET range_same = 1
	FOR (range_h = 0; range_h < fx_header_count; ++range_h) BEGIN
		SET range_target = $spell_target(~%range_h%~)
		SET $range_feet(~%range_h%~) = (range_target == TARGET_HEAD_self OR range_target == TARGET_HEAD_self_ignore_pause) ? 0 : $spell_range(~%range_h%~)
		SET range_same = range_same AND $range_feet(~%range_h%~) == $range_feet(~0~)
	END
	PATCH_IF range_same BEGIN
		LPF ad_spell_distance_text INT_VAR feet = $range_feet(~0~) RET value = text range_number = distance_number END
		PATCH_IF range_number < 2 BEGIN
			SPRINT value @7000012 // ~Contact~
		END
	END
	ELSE BEGIN
		LPM ad_spell_header_range_progression
	END
	SPRINT name @7000001 // ~Portée~
	LPM ad_spell_header_value
END

// Portée qui varie avec le niveau (ancien get_complex_range) : le premier en-tête sert de base, au
// niveau du premier lanceur s'il est requis au niveau 1 ; les suivants doivent croître d'un même pas
// (« 1,5 mètre par niveau », « 3 mètres par tranche de 2 niveaux », précédé du reste s'il est
// positif), sinon « Spéciale ». Ces formules sont écrites en français dans les deux langues, comme
// dans l'ancien moteur.
DEFINE_PATCH_MACRO ad_spell_header_range_progression BEGIN
	SET range_base_level = $spell_level(~0~)
	PATCH_IF range_base_level == 1 BEGIN
		LPF ad_spell_first_level RET range_base_level = first_level END
	END
	SET range_delta = 0
	SET range_delta_level = 0
	SET range_valid = 1
	SET range_previous = $range_feet(~0~)
	SET range_previous_level = range_base_level
	FOR (range_h = 1; range_h < fx_header_count; ++range_h) BEGIN
		SET range_level = $spell_level(~%range_h%~)
		SET range_feet_h = $range_feet(~%range_h%~)
		PATCH_IF range_delta == 0 BEGIN
			SET range_delta = range_feet_h - range_previous
			SET range_delta_level = range_level - range_previous_level
		END
		ELSE PATCH_IF range_delta != range_feet_h - range_previous OR range_delta_level != range_level - range_previous_level BEGIN
			SET range_valid = 0
		END
		SET range_previous_level = range_level
		SET range_previous = range_feet_h
	END
	PATCH_IF NOT range_valid BEGIN
		SPRINT value @7000011 // ~Spéciale~
	END
	ELSE PATCH_IF range_delta_level == 0 BEGIN
		LPF ad_refusal STR_VAR reason = ~not_implemented:spell_header:range_progression~ message = ~range that changes between abilities of the same level~ RET header_missing = refusal END
	END
	ELSE BEGIN
		LPF ad_spell_distance_text INT_VAR feet = range_delta RET deltaRange = text END
		SET level = range_delta_level
		PATCH_IF range_delta_level == 1 BEGIN
			SPRINT value @7000040 // ~%deltaRange% par niveau~
		END
		ELSE BEGIN
			SPRINT value @7000041 // ~%deltaRange% par tranche de %level% niveaux~
		END
		SET range_remains = range_feet_h - (range_delta * range_level / range_delta_level)
		PATCH_IF range_remains > 0 BEGIN
			LPF ad_spell_distance_text INT_VAR feet = range_remains RET range_remains_text = text END
			SPRINT value ~%range_remains_text% + %value%~
		END
	END
END

// Premier niveau de lanceur du sort (ancien get_first_level_for_spell) : pour un sort profane ou
// divin, le premier niveau qui donne un emplacement de son niveau ; pour un autre, le niveau qui
// précède le deuxième en-tête du pas commun aux en-têtes au-delà du niveau 1, celui de l'en-tête
// unique, sinon 1.
DEFINE_PATCH_FUNCTION ad_spell_first_level
	RET
		first_level
BEGIN
	READ_SHORT SPL_type first_type
	READ_LONG  SPL_level first_spell_level
	PATCH_IF first_spell_level < 1 BEGIN
		SET first_spell_level = 1
	END
	PATCH_IF first_type == 1 OR first_type == 2 BEGIN
		READ_LONG SPL_exclusion_flags first_exclusions
		PATCH_IF first_type == 1 BEGIN
			SPRINT first_table ~AD_FIRST_CASTER_LEVEL_WIZARD~
		END
		ELSE PATCH_IF (first_exclusions BAND BIT31) == 0 BEGIN
			SPRINT first_table ~AD_FIRST_CASTER_LEVEL_DRUID~
		END
		ELSE BEGIN
			SPRINT first_table ~AD_FIRST_CASTER_LEVEL_PRIEST~
		END
		PATCH_IF NOT VARIABLE_IS_SET $EVAL ~%first_table%~(~%first_spell_level%~) BEGIN
			PATCH_FAIL ~New engine: no first caster level for a spell of level %first_spell_level% in %first_table%~
		END
		SET first_level = $EVAL ~%first_table%~(~%first_spell_level%~)
	END
	ELSE BEGIN
		SET first_level = 1
		SET first_step = 0
		SET first_valid = 1
		FOR (first_h = 1; first_h < fx_header_count; ++first_h) BEGIN
			SET first_previous_h = first_h - 1
			SET first_previous = $spell_level(~%first_previous_h%~)
			PATCH_IF first_previous > 1 BEGIN
				SET first_delta = $spell_level(~%first_h%~) - first_previous
				PATCH_IF first_step == 0 BEGIN
					SET first_step = first_delta
				END
				SET first_valid = first_valid AND first_step == first_delta
			END
		END
		PATCH_IF first_valid AND fx_header_count > 1 BEGIN
			SET first_level = $spell_level(~1~) - first_step
		END
		ELSE PATCH_IF fx_header_count == 1 BEGIN
			SET first_level = $spell_level(~0~)
		END
	END
END

// Durée (ancien spell_duration) : durée commune des effets de chaque en-tête (en secondes ; un effet
// différé ou permanent compte pour 0, un effet en ticks est converti, l'opcode 217 dure 30
// secondes), puis leur progression (ad_spell_header_complex_duration) ; si elle varie entre les
// effets d'un en-tête, la lecture s'arrête après lui et la durée est « Spéciale », sauf si seul le
// premier en-tête a été lu : celle des projectiles qui explosent plusieurs fois s'applique alors,
// comme pour un sort à un seul en-tête qui en a un. Sans durée : « Permanente », ou « Instantanée »
// si le premier effet différé ou permanent lu est d'un opcode dont la durée ne compte pas et
// qu'aucun autre ne l'a contredit ensuite. L'opcode 213 rend la durée « Spéciale ». Les opcodes 318,
// 321 et 324 qui visent le sort lui-même ne comptent pas. header_has_duration : 0 si la durée est
// permanente ou instantanée (ligne « Dissipation ») ; header_hide_duration : 0 si elle est
// « Spéciale », les lignes écrivant alors leurs durées (ancien ignoreDuration).
DEFINE_PATCH_MACRO ad_spell_header_duration BEGIN
	SET header_hide_duration = 1
	SET duration_valid = 1
	SET duration_special = 0
	SET duration_instant = 0 - 1
	SET duration_count = 0
	SET duration_read = 0
	FOR (duration_h = 0; duration_h < fx_header_count AND duration_valid; ++duration_h) BEGIN
		SET duration_read += 1
		SET duration_found = 0
		FOR (duration_n = 0; duration_n < $spell_fx_count(~%duration_h%~); ++duration_n) BEGIN
			SET duration_id = $EVAL ~spell_fx_%duration_h%~(~%duration_n%~)
			SET duration_opcode = $EVAL ~spell_fx_opcode_%duration_h%~(~%duration_n%~)
			SPRINT duration_resource $fx_resource_lower(~%duration_id%~)
			PATCH_IF NOT ((duration_opcode == 318 OR duration_opcode == 321 OR duration_opcode == 324) AND ~%duration_resource%~ STRING_EQUAL ~%spell_self%~) BEGIN
				SET duration_timing = $fx_timing(~%duration_id%~)
				SET duration_seconds = $fx_duration(~%duration_id%~)
				// Une série prend le dernier délai pour durée (ancien timing 5000 ou 5001).
				PATCH_IF $fx_series_anchor(~%duration_id%~) BEGIN
					SET duration_seconds = $fx_series_last(~%duration_id%~)
				END
				ELSE PATCH_IF duration_timing == TIMING_duration_ticks BEGIN
					SET duration_seconds = duration_seconds / 15
				END
				ELSE PATCH_IF duration_timing != TIMING_duration AND duration_timing != TIMING_delayed_duration BEGIN
					SET duration_seconds = 0
					SPRINT duration_kind ~~
					PATCH_IF VARIABLE_IS_SET $AD_OPCODE_DURATION(~%duration_opcode%~) BEGIN
						SPRINT duration_kind $AD_OPCODE_DURATION(~%duration_opcode%~)
					END
					// Anciennes listes opcodes_ignore_duration et opcodes_cant_be_permanent (177, et 525 :
					// objet remplacé, ad_derived_add).
					PATCH_IF ~%duration_kind%~ STRING_EQUAL ~IGNORED~ OR ~%duration_kind%~ STRING_EQUAL ~NOT_PERMANENT~ OR duration_opcode == 177 OR duration_opcode == 525 BEGIN
						PATCH_IF duration_instant < 0 BEGIN
							SET duration_instant = 1
						END
					END
					ELSE PATCH_IF duration_instant == 1 BEGIN
						SET duration_instant = 0
					END
				END
				PATCH_IF duration_opcode == 217 BEGIN
					SET duration_seconds = 30
				END
				PATCH_IF duration_opcode == 213 BEGIN
					SET duration_special = 1
				END
				PATCH_IF duration_seconds > 0 BEGIN
					PATCH_IF NOT duration_found BEGIN
						SET duration_found = 1
						SET $duration_level(~%duration_count%~) = $spell_level(~%duration_h%~)
						SET $duration_value(~%duration_count%~) = duration_seconds
						SET duration_count += 1
					END
					ELSE BEGIN
						SET duration_last = duration_count - 1
						PATCH_IF $duration_value(~%duration_last%~) != duration_seconds BEGIN
							SET duration_valid = 0
						END
					END
				END
			END
		END
	END
	SET header_has_duration = 1
	PATCH_IF duration_special BEGIN
		SPRINT value @7000011 // ~Spéciale~
		SET header_hide_duration = 0
	END
	ELSE BEGIN
		SET projectile_used = 0
		PATCH_IF duration_read == 1 BEGIN
			LPM ad_spell_header_projectile_duration
		END
		PATCH_IF duration_valid BEGIN
			PATCH_IF NOT projectile_used BEGIN
				SPRINT complex_array ~duration~
				SET complex_count = duration_count
				LPM ad_spell_header_complex_duration
			END
			PATCH_IF complex_special BEGIN
				SPRINT value @7000011 // ~Spéciale~
				SET header_hide_duration = 0
			END
			ELSE PATCH_IF complex_permanent BEGIN
				SET header_has_duration = 0
				PATCH_IF duration_instant == 1 BEGIN
					SPRINT value @7000014 // ~Instantanée~
				END
				ELSE BEGIN
					SPRINT value @7000013 // ~Permanente~
				END
			END
			ELSE BEGIN
				SPRINT value ~%complex_text%~
			END
		END
		// Durée variable : celle des projectiles est écrite telle quelle, même vide si elle est nulle.
		ELSE PATCH_IF projectile_used BEGIN
			SPRINT value ~%complex_text%~
		END
		ELSE BEGIN
			SPRINT value @7000011 // ~Spéciale~
			SET header_hide_duration = 0
		END
	END
	SPRINT name @7000002 // ~Durée~
	LPM ad_spell_header_value
END

// Durée des projectiles qui explosent plusieurs fois (ancien get_spell_duration_by_projectile) :
// délai entre deux explosions multiplié par leur nombre, pour chaque en-tête dont le projectile en
// a, puis leur progression. projectile_used : 1 si elle s'applique (complex_text, complex_permanent).
DEFINE_PATCH_MACRO ad_spell_header_projectile_duration BEGIN
	SET projectile_count = 0
	FOR (projectile_h = 0; projectile_h < fx_header_count; ++projectile_h) BEGIN
		LPF ad_projectile_area INT_VAR projectile = $spell_projectile(~%projectile_h%~) RET projectile_shape = area_shape
			projectile_delay = area_delay projectile_triggers = area_triggers projectile_missing = area_file_missing END
		PATCH_IF projectile_missing OR projectile_shape < 0 BEGIN
			LPF ad_refusal STR_VAR reason = ~file_error:spell_header:projectile~ message = ~projectile of ability %projectile_h% missing or too short to be read~ RET header_missing = refusal END
		END
		ELSE PATCH_IF projectile_shape != 0 AND projectile_triggers > 1 BEGIN
			SET $projectile_level(~%projectile_count%~) = $spell_level(~%projectile_h%~)
			SET $projectile_value(~%projectile_count%~) = 6 * projectile_delay * projectile_triggers / 100
			SET projectile_count += 1
		END
	END
	PATCH_IF projectile_count > 0 BEGIN
		SPRINT complex_array ~projectile~
		SET complex_count = projectile_count
		LPM ad_spell_header_complex_duration
		SET projectile_used = NOT complex_special
	END
END

// Durée commune des en-têtes <complex_array>_level(rang) => <complex_array>_value(rang),
// complex_count rangs (ancien get_complex_duration) : la même partout (complex_text), une
// progression régulière (« 1 round par niveau », « 2 rounds + 1 round par tranche de 2 niveaux »),
// deux valeurs (« 1 round + 2 rounds au niveau 7 »), aucune (complex_permanent), sinon
// complex_special. Le premier en-tête, souvent décalé, n'entre pas dans le pas ; un en-tête requis
// au niveau 1 compte au niveau du premier lanceur.
DEFINE_PATCH_MACRO ad_spell_header_complex_duration BEGIN
	SPRINT complex_text ~~
	SET complex_permanent = 0
	SET complex_special = 0
	SET complex_first = 0 - 1
	FOR (complex_pass = 1; complex_pass <= 2; ++complex_pass) BEGIN
		PATCH_IF complex_pass == 1 OR NOT complex_valid BEGIN
			SET complex_base = 0
			SET complex_delta = 0
			SET complex_delta_level = 0
			SET complex_valid = 1
			SET complex_previous = 0
			SET complex_previous_level = 0
			SET complex_rank = 0
			FOR (complex_n = 0; complex_n < complex_count; ++complex_n) BEGIN
				LPM ad_spell_header_complex_level
				PATCH_IF complex_rank > 1 AND complex_previous != complex_value BEGIN
					PATCH_IF complex_delta == 0 BEGIN
						SET complex_delta = complex_value - complex_previous
						SET complex_delta_level = complex_level - complex_previous_level
					END
					ELSE PATCH_IF complex_delta != complex_value - complex_previous OR complex_delta_level != complex_level - complex_previous_level BEGIN
						SET complex_valid = 0
					END
				END
				ELSE BEGIN
					SET complex_base = complex_value
					// La seconde passe prend aussi le niveau des valeurs qu'elle ne compare pas.
					PATCH_IF complex_pass == 2 BEGIN
						SET complex_previous_level = complex_level
					END
				END
				PATCH_IF complex_previous != complex_value BEGIN
					SET complex_previous = complex_value
					SET complex_previous_level = complex_level
				END
				SET complex_rank += 1
			END
		END
	END
	PATCH_IF complex_rank == 2 BEGIN
		FOR (complex_n = 0; complex_n < 2; ++complex_n) BEGIN
			LPM ad_spell_header_complex_level
			PATCH_IF complex_n == 0 BEGIN
				SET complex_base = complex_value
			END
			ELSE BEGIN
				SET complex_delta = complex_value - complex_previous
			END
			SET complex_previous = complex_value
		END
		LPF ad_spell_duration_text INT_VAR seconds = complex_base RET baseValue = text END
		LPF ad_spell_duration_text INT_VAR seconds = complex_delta RET value = text END
		SET level = complex_level
		SPRINT complex_text @3000010 // ~%baseValue% + %value% au niveau %level%~
	END
	ELSE PATCH_IF complex_valid BEGIN
		PATCH_IF complex_base == 0 AND complex_delta == 0 BEGIN
			SET complex_permanent = 1
		END
		ELSE PATCH_IF complex_base > 0 AND complex_delta == 0 BEGIN
			LPF ad_spell_duration_text INT_VAR seconds = complex_base RET complex_text = text END
		END
		ELSE BEGIN
			LPF ad_spell_duration_text INT_VAR seconds = complex_delta RET value = text END
			PATCH_IF complex_delta_level == 1 BEGIN
				SPRINT complex_text @3000011 // ~%value% par niveau~
			END
			ELSE BEGIN
				SET level = complex_delta_level
				SPRINT complex_text @3000012 // ~%value% par tranche de %level% niveaux~
			END
			SET complex_remains = complex_value - (complex_delta * complex_previous_level / complex_delta_level)
			PATCH_IF complex_remains > 0 BEGIN
				LPF ad_spell_duration_text INT_VAR seconds = complex_remains RET complex_remains_text = text END
				SPRINT complex_text ~%complex_remains_text% + %complex_text%~
			END
		END
	END
	ELSE BEGIN
		SET complex_special = 1
	END
END

// Niveau complex_level et valeur complex_value du rang complex_n ; un en-tête requis au niveau 1 ou
// moins compte au niveau du premier lanceur (calculé une fois).
DEFINE_PATCH_MACRO ad_spell_header_complex_level BEGIN
	SET complex_level = $EVAL ~%complex_array%_level~(~%complex_n%~)
	SET complex_value = $EVAL ~%complex_array%_value~(~%complex_n%~)
	PATCH_IF complex_level <= 1 BEGIN
		PATCH_IF complex_first < 0 BEGIN
			LPF ad_spell_first_level RET complex_first = first_level END
		END
		SET complex_level = complex_first
	END
END

// Durée en secondes (ancien get_str_duration) : vide si elle n'est pas positive.
DEFINE_PATCH_FUNCTION ad_spell_duration_text
	INT_VAR
		seconds = 0
	RET
		text
BEGIN
	SPRINT text ~~
	PATCH_IF seconds > 0 BEGIN
		LPF ad_duration_text INT_VAR seconds RET text END
	END
END

// Temps d'incantation (ancien spell_casting_time) : le même pour tous les en-têtes, sinon « Spécial ».
DEFINE_PATCH_MACRO ad_spell_header_casting_time BEGIN
	SET value = $spell_casting_time(~0~)
	FOR (casting_h = 1; casting_h < fx_header_count; ++casting_h) BEGIN
		PATCH_IF $spell_casting_time(~%casting_h%~) != $spell_casting_time(~0~) BEGIN
			SPRINT value @7000010 // ~Spécial~
		END
	END
	SPRINT name @7000003 // ~Temps d'incantation~
	LPM ad_spell_header_value
END

// Zone d'effet (ancien spell_target) : celle de chaque en-tête (ad_spell_header_ability_area) si elle
// est la même pour tous, sinon « Spécial ».
DEFINE_PATCH_MACRO ad_spell_header_area BEGIN
	FOR (area_h = 0; area_h < fx_header_count; ++area_h) BEGIN
		// Un en-tête de mêmes projectile et cible que le précédent a la même zone.
		SET area_previous = area_h - 1
		PATCH_IF area_h > 0 AND $spell_projectile(~%area_h%~) == $spell_projectile(~%area_previous%~)
				AND $spell_target(~%area_h%~) == $spell_target(~%area_previous%~)
				AND $spell_target_count(~%area_h%~) == $spell_target_count(~%area_previous%~) BEGIN
			SPRINT $area_text(~%area_h%~) $area_text(~%area_previous%~)
		END
		ELSE BEGIN
			LPM ad_spell_header_ability_area
			SPRINT $area_text(~%area_h%~) ~%area_ability%~
		END
	END
	SPRINT value $area_text(~0~)
	FOR (area_h = 1; area_h < fx_header_count; ++area_h) BEGIN
		PATCH_IF NOT (~%value%~ STRING_EQUAL $area_text(~%area_h%~)) BEGIN
			SPRINT value @7000010 // ~Spécial~
		END
	END
	SPRINT name @7000004 // ~Zone d'effet~
	LPM ad_spell_header_value
END

// Zone d'effet de l'en-tête area_h (ancien spell_target_by_projectile, puis la cible de l'en-tête) :
// zone d'un projectile de zone, dont le rayon est sa taille divisée par 17, même pour un cône (au
// contraire des lignes d'effets) ; sinon le lanceur, une ou plusieurs créatures, un point. Une cible
// sans texte laisse la zone vide, comme dans l'ancien moteur.
DEFINE_PATCH_MACRO ad_spell_header_ability_area BEGIN
	SPRINT area_ability ~~
	SET area_target = $spell_target(~%area_h%~)
	SET countTarget = $spell_target_count(~%area_h%~)
	LPF ad_projectile_area INT_VAR projectile = $spell_projectile(~%area_h%~) RET area_shape area_creatures
		area_angle area_cone area_ignore_target area_size area_file_missing END
	PATCH_IF area_file_missing OR area_shape < 0 BEGIN
		LPF ad_refusal STR_VAR reason = ~file_error:spell_header:projectile~ message = ~projectile of the ability missing or too short to be read~ RET header_missing = refusal END
	END
	ELSE PATCH_IF area_shape > 0 BEGIN
		LPF ad_spell_distance_text INT_VAR feet = area_size / 17 RET range = text END
		SET angle = area_angle
		SET area_form = 0 - 1
		PATCH_IF area_cone BEGIN
			SET area_form = 4
		END
		ELSE PATCH_IF area_target == TARGET_HEAD_self OR area_target == TARGET_HEAD_self_ignore_pause BEGIN
			PATCH_IF area_ignore_target OR area_creatures > 0 BEGIN
				SPRINT ofTheTarget @7001110 // ~du lanceur~
				SET area_form = 3
			END
			ELSE BEGIN
				SET area_form = 2
			END
		END
		ELSE PATCH_IF area_target == TARGET_HEAD_creature BEGIN
			PATCH_IF countTarget > 1 BEGIN
				SPRINT area_ability @7001102 // ~%countTarget% créatures~
			END
			ELSE PATCH_IF area_ignore_target BEGIN
				SPRINT ofTheTarget @7001111 // ~de la cible~
				SET area_form = 3
			END
			ELSE BEGIN
				SET area_form = 1
			END
		END
		ELSE PATCH_IF area_target == TARGET_HEAD_area BEGIN
			SET area_form = 0
		END
		PATCH_IF area_form >= 0 BEGIN
			LPF ad_tra INT_VAR tra_id = 7001000 + 10 * area_form + area_creatures
				tra_block_start = 7001000 tra_block_size = 50 RET area_ability = text END // ~Rayon de %range%~
		END
	END
	PATCH_IF ~%area_ability%~ STRING_EQUAL ~~ BEGIN
		PATCH_IF area_target == TARGET_HEAD_self OR area_target == TARGET_HEAD_self_ignore_pause BEGIN
			SPRINT area_ability @7001100 // ~Le lanceur~
		END
		ELSE PATCH_IF area_target == TARGET_HEAD_creature AND countTarget > 1 BEGIN
			SPRINT area_ability @7001102 // ~%countTarget% créatures~
		END
		ELSE PATCH_IF area_target == TARGET_HEAD_creature OR area_target == TARGET_HEAD_character_portrait BEGIN
			SPRINT area_ability @7001101 // ~1 créature~
		END
		ELSE PATCH_IF area_target == TARGET_HEAD_area BEGIN
			SPRINT area_ability @7001103 // ~Point dans le champ visuel du lanceur~
		END
	END
END

// Jet de sauvegarde du sort chargé dans le magasin (ancien spell_saving_throw), d'après les effets de
// ses en-têtes (hors opcodes 318, 321, 324 et effets qui visent le sort lui-même) : leur type de jet
// (bits 0 à 5) doit être le même partout, sinon « Spécial » ; « Aucun » sans type. Un 146, 148 ou
// 232 sans jet prend celui du premier sous-sort qu'il lance (une fois par sous-sort), dont la moitié
// des dégâts remplace alors celle des effets déjà lus. « Sorts à -2 (Annule) », « (1/2) » pour des
// dégâts réduits de moitié sur EE (ad_spell_header_save_bonus).
//
// save_* (rendus) : save_type (0 - 1 sans effet), save_bonus, save_half ; save_text : texte de la
// ligne ; save_missing : raison d'un cas que ce rendu ne sait pas reproduire ; save_bonus_text et
// save_bonus_valid : bonus de ce sort (ad_spell_header_save_bonus), que l'appelant lit après la
// lecture d'un sous-sort, l'ancien moteur rechargeant les effets de ce dernier à la place des siens.
// save_visited (hérité) : sous-sorts déjà lus.
DEFINE_PATCH_FUNCTION ad_spell_header_save
	RET
		save_type
		save_bonus
		save_half
		save_text
		save_missing
		save_bonus_text
		save_bonus_valid
BEGIN
	SPRINT save_missing ~~
	SET save_special = 0
	SET save_half = 0
	SET save_type = 0 - 1
	SET save_bonus = 0 - 1
	SET save_from_sub = 0
	SET $save_visited(~%spell_self%~) = 1
	FOR (save_h = 0; save_h < fx_header_count AND NOT save_special; ++save_h) BEGIN
		FOR (save_n = 0; save_n < $spell_fx_count(~%save_h%~); ++save_n) BEGIN
			SET save_id = $EVAL ~spell_fx_%save_h%~(~%save_n%~)
			SET save_opcode = $EVAL ~spell_fx_opcode_%save_h%~(~%save_n%~)
			SPRINT save_resource $fx_resource_lower(~%save_id%~)
			PATCH_IF save_opcode != 318 AND save_opcode != 321 AND save_opcode != 324 AND NOT (~%save_resource%~ STRING_EQUAL ~%spell_self%~) BEGIN
				SET save_effect_type = $fx_save_type(~%save_id%~) BAND 0b111111
				SET save_effect_bonus = $fx_save_bonus(~%save_id%~)
				PATCH_IF save_effect_type == 0 AND (save_opcode == 146 OR save_opcode == 148 OR save_opcode == 232) BEGIN
					PATCH_IF NOT VARIABLE_IS_SET $save_visited(~%save_resource%~) BEGIN
						SET $save_visited(~%save_resource%~) = 1
						PATCH_IF FILE_EXISTS_IN_GAME ~%save_resource%.spl~ BEGIN
							// L'ancien moteur recharge ici les effets du sous-sort à la place de ceux du sort :
							// les en-têtes suivants liraient les siens.
							PATCH_IF save_h < fx_header_count - 1 AND ~%save_missing%~ STRING_EQUAL ~~ BEGIN
								LPF ad_refusal INT_VAR fx_id = save_id STR_VAR reason = ~not_implemented:spell_header:save_subspell~ message = ~saving throw read from a sub-spell before the last ability: not supported~ RET save_missing = refusal END
							END
							LPF ad_spell_header_save_sub STR_VAR resref = ~%save_resource%~ RET save_effect_type = save_type
								save_effect_bonus = save_bonus save_half sub_missing = save_missing save_bonus_text save_bonus_valid END
							SET save_from_sub = 1
							PATCH_IF NOT (~%sub_missing%~ STRING_EQUAL ~~) AND ~%save_missing%~ STRING_EQUAL ~~ BEGIN
								SPRINT save_missing ~%sub_missing%~
							END
						END
					END
				END
				PATCH_IF IS_EE AND save_opcode == 12 AND ($fx_parameter2(~%save_id%~) BAND 65535) == 0 AND ($fx_special(~%save_id%~) BAND BIT8) != 0 BEGIN
					SET save_half = 1
				END
				PATCH_IF save_effect_type >= 0 BEGIN
					PATCH_IF save_type < 0 BEGIN
						SET save_type = save_effect_type
						SET save_bonus = save_effect_bonus
					END
					PATCH_IF save_type != save_effect_type BEGIN
						SET save_special = 1
					END
				END
			END
		END
	END
	PATCH_IF NOT save_from_sub BEGIN
		LPM ad_spell_header_save_bonus
	END
	PATCH_IF save_special BEGIN
		SPRINT save_text @7000010 // ~Spécial~
	END
	ELSE PATCH_IF save_type > 0 BEGIN
		PATCH_IF save_half BEGIN
			SPRINT savingThrow @7000019 // ~1/2~
		END
		ELSE BEGIN
			SPRINT savingThrow @7000018 // ~Annule~
		END
		PATCH_IF NOT save_bonus_valid BEGIN
			SPRINT save_text @7000010 // ~Spécial~
		END
		ELSE PATCH_IF save_type != 1 AND save_type != 2 AND save_type != 4 AND save_type != 8 AND save_type != 16 BEGIN
			LPF ad_refusal STR_VAR reason = ~not_implemented:spell_header:save_types~ message = ~saving throw type %save_type% (one of 1, 2, 4, 8, 16 supported)~ RET save_missing = refusal END
		END
		ELSE BEGIN
			LPF ad_tra INT_VAR tra_id = 5000060 + save_type tra_block_start = 5000060 tra_block_size = 17 RET saveType = text END // ~Sorts~ (@5000061)
			SPRINT value ~%save_bonus_text%~
			PATCH_IF ~%value%~ STRING_EQUAL ~~ OR ~%value%~ STRING_EQUAL ~0~ BEGIN
				SPRINT save_text @7000020 // ~%saveType% (%savingThrow%)~
			END
			ELSE BEGIN
				SPRINT save_text @7000021 // ~%saveType% à %value% (%savingThrow%)~
			END
		END
	END
	ELSE BEGIN
		SPRINT save_text @7000017 // ~Aucun~
	END
END

// Jet de sauvegarde du sous-sort resref (ad_spell_header_save), lu dans sa propre portée pour que
// ses effets ne remplacent pas ceux du sort en cours.
DEFINE_PATCH_FUNCTION ad_spell_header_save_sub
	STR_VAR
		resref = ~~
	RET
		save_type
		save_bonus
		save_half
		save_missing
		save_bonus_text
		save_bonus_valid
BEGIN
	SET save_type = 0 - 1
	SET save_bonus = 0 - 1
	SET save_half = 0
	SPRINT save_missing ~~
	SPRINT save_bonus_text ~~
	SET save_bonus_valid = 1
	// Seuls ses effets comptent, pas leurs phrases.
	SET support_header_only = 1
	INNER_PATCH_FILE ~%resref%.spl~ BEGIN
		LPM ad_fx_load_spell
		PATCH_IF NOT (~%fx_load_error%~ STRING_EQUAL ~~) BEGIN
			LPF ad_refusal STR_VAR reason = ~file_error:spell_header:subspell_%fx_load_error%~ message = ~%resref%.SPL: %fx_load_message%~ RET save_missing = refusal END
		END
		ELSE BEGIN
			SPRINT header_missing ~~
			LPM ad_spell_header_fields
			LPM ad_spell_header_pipeline
			LPM ad_spell_header_effects
			PATCH_IF NOT (~%header_missing%~ STRING_EQUAL ~~) BEGIN
				SPRINT save_missing ~%header_missing%~
			END
			LPF ad_spell_header_save RET save_type save_bonus save_half sub_missing = save_missing save_bonus_text save_bonus_valid END
			PATCH_IF NOT (~%sub_missing%~ STRING_EQUAL ~~) AND ~%save_missing%~ STRING_EQUAL ~~ BEGIN
				SPRINT save_missing ~%sub_missing%~
			END
			// Bonus du sous-sort lui-même, celui que l'ancien moteur lit au retour.
			LPM ad_spell_header_save_bonus
		END
	END
END

// Bonus du jet de sauvegarde (ancien get_spell_effects_by_saving_throw), d'après les effets du
// premier en-tête du sort chargé : le même pour chacun (« -2 », « +1 », « 0 »), sinon
// save_bonus_valid vaut 0 (« Spécial »). Avec plusieurs en-têtes, chaque effet du premier qui se
// retrouve dans tous les autres à la durée et au bonus près (ad_spell_level_search) donne son bonus
// (un seul effet trouvé) ou sa progression (ad_spell_level_formula : « -1 par tranche de 2 niveaux
// du lanceur/12 ») ; tous doivent donner le même, sinon, ou sans formule, save_bonus_valid vaut 0.
// Refus : formule à deux valeurs, que l'ancien moteur écrit en français dans les deux langues ;
// bonus suivi de l'unité de l'opcode de l'effet (ancien opcode_<N>_typed_value). Rien n'est cherché
// pour un sort déjà refusé (header_missing), dont les regroupements n'ont pas été faits.
DEFINE_PATCH_MACRO ad_spell_header_save_bonus BEGIN
	SPRINT save_bonus_text ~~
	SET save_bonus_valid = 1
	PATCH_IF fx_header_count == 1 BEGIN
		FOR (bonus_n = 0; bonus_n < $spell_fx_count(~0~) AND save_bonus_valid; ++bonus_n) BEGIN
			SET bonus_id = $spell_fx_0(~%bonus_n%~)
			LPF ad_signed_value INT_VAR value = $fx_save_bonus(~%bonus_id%~) RET bonus_effect_text = text END
			PATCH_IF bonus_n == 0 BEGIN
				SPRINT save_bonus_text ~%bonus_effect_text%~
			END
			SET save_bonus_valid = ~%bonus_effect_text%~ STRING_EQUAL ~%save_bonus_text%~
		END
		PATCH_IF NOT save_bonus_valid BEGIN
			SPRINT save_bonus_text ~~
		END
	END
	ELSE PATCH_IF ~%header_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_spell_levels_entries
		SET level_special_duration = NOT header_hide_duration
		SET level_skip = AD_SAME_TIMING BOR AD_SAME_SAVE
		SPRINT bonus_first_text ~~
		FOR (bonus_n = 0; bonus_n < $spell_fx_count(~0~) AND save_bonus_valid; ++bonus_n) BEGIN
			SPRINT level_a ~0 %bonus_n%~
			LPM ad_spell_level_search
			PATCH_IF search_in_all BEGIN
				PATCH_IF search_total > 1 BEGIN
					SPRINT formula_array ~search_save~
					SET formula_percent = 0
					SET formula_flat = 0
					SET formula_dice_sides = 0
					SET formula_opcode = $level_opcode(~%level_a%~)
					SET level_id = $level_id(~%level_a%~)
					LPM ad_spell_level_formula
					PATCH_IF formula_rank == 2 BEGIN
						LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell_header:save_bonus_two_values~ message = ~saving throw bonus taking only two values between the abilities~ RET save_missing = refusal END
					END
					ELSE PATCH_IF formula_unit_used BEGIN
						LPF ad_refusal INT_VAR fx_id = level_id STR_VAR reason = ~not_implemented:spell_header:save_bonus_effects~ message = ~saving throw bonus followed by the unit of opcode %formula_opcode%~ RET save_missing = refusal END
					END
					SET save_bonus_valid = formula_valid
					SPRINT save_bonus_text ~%formula_text%~
					PATCH_IF formula_base > 0 BEGIN
						SPRINT value ~%formula_text%~
						SPRINT save_bonus_text @1200001 // ~+%value%~
					END
				END
				ELSE PATCH_IF search_total == 1 BEGIN
					LPF ad_signed_value INT_VAR value = $search_save(~0~) RET save_bonus_text = text END
				END
				PATCH_IF ~%bonus_first_text%~ STRING_EQUAL ~~ BEGIN
					SPRINT bonus_first_text ~%save_bonus_text%~
				END
				PATCH_IF NOT (~%bonus_first_text%~ STRING_EQUAL ~%save_bonus_text%~) BEGIN
					SET save_bonus_valid = 0
				END
				PATCH_IF NOT save_bonus_valid BEGIN
					SPRINT save_bonus_text ~~
				END
			END
		END
	END
END

// Dissipation et résistance à la magie (ancien spell_resistance), d'après les effets des en-têtes
// (hors opcodes 318, 321, 324 et effets qui visent le sort lui-même) : la résistance (champ 2 ou 3 :
// ignorée) doit être la même partout, la dissipation (champ 1 ou 3) aussi pour les effets d'une durée
// non nulle ; sinon aucune des deux lignes. « Dissipation : Affecté » seulement si la durée du sort
// n'est ni permanente ni instantanée.
DEFINE_PATCH_MACRO ad_spell_header_resistance BEGIN
	SET resistance_special = 0
	SET resistance_dispel = 0 - 1
	SET resistance_ignored = 0 - 1
	FOR (resistance_h = 0; resistance_h < fx_header_count AND NOT resistance_special; ++resistance_h) BEGIN
		FOR (resistance_n = 0; resistance_n < $spell_fx_count(~%resistance_h%~); ++resistance_n) BEGIN
			SET resistance_id = $EVAL ~spell_fx_%resistance_h%~(~%resistance_n%~)
			SET resistance_opcode = $EVAL ~spell_fx_opcode_%resistance_h%~(~%resistance_n%~)
			SPRINT resistance_resource $fx_resource_lower(~%resistance_id%~)
			PATCH_IF resistance_opcode != 318 AND resistance_opcode != 321 AND resistance_opcode != 324 AND NOT (~%resistance_resource%~ STRING_EQUAL ~%spell_self%~) BEGIN
				SET resistance_value = $fx_resistance(~%resistance_id%~)
				SET resistance_effect_ignored = resistance_value == 2 OR resistance_value == 3
				PATCH_IF resistance_ignored < 0 BEGIN
					SET resistance_ignored = resistance_effect_ignored
				END
				SET resistance_special = resistance_special OR resistance_ignored != resistance_effect_ignored
				PATCH_IF NOT resistance_special AND ($fx_duration(~%resistance_id%~) > 0 OR $fx_series_anchor(~%resistance_id%~)) BEGIN
					SET resistance_effect_dispel = resistance_value == 1 OR resistance_value == 3
					PATCH_IF resistance_dispel < 0 BEGIN
						SET resistance_dispel = resistance_effect_dispel
					END
					SET resistance_special = resistance_dispel != resistance_effect_dispel
				END
			END
		END
	END
	PATCH_IF NOT resistance_special BEGIN
		PATCH_IF resistance_dispel >= 0 BEGIN
			PATCH_IF resistance_dispel AND header_has_duration BEGIN
				SPRINT value @7000015 // ~Affecté~
			END
			ELSE BEGIN
				SPRINT value @7000016 // ~Non-affecté~
			END
			SPRINT name @7000006 // ~Dissipation~
			LPM ad_spell_header_value
		END
		PATCH_IF resistance_ignored >= 0 BEGIN
			PATCH_IF NOT resistance_ignored BEGIN
				SPRINT value @7000015 // ~Affecté~
			END
			ELSE BEGIN
				SPRINT value @7000016 // ~Non-affecté~
			END
			SPRINT name @7000007 // ~Résistance à la magie~
			LPM ad_spell_header_value
		END
	END
END

// Texte d'origine sans le nom du sort qui le commence ni son ancien bloc technique (ancien
// get_spell_roleplay_description, expressions reprises telles quelles) : le texte qui précède la
// première ligne « Jet de sauvegarde », puis les lignes « Jet de sauvegarde… » qui le commencent.
DEFINE_PATCH_FUNCTION ad_spell_roleplay_text
	STR_VAR
		text = ~~
		name = ~~
	RET
		text
BEGIN
	SPRINT roleplay_save @1900001 // ~\(Jet de sauvegarde\|Jets de sauvegarde\)+~
	INNER_PATCH_SAVE text ~%text%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~^%name%\([\.%MNL%%LNL%%WNL%]\)+~ ~~
	END
	INNER_PATCH ~%text%~ BEGIN
		REPLACE_EVALUATE CASE_INSENSITIVE ~\(.*\)^%roleplay_save%\(.*[%MNL%%LNL%%WNL%]*\)*~ BEGIN
			SPRINT text ~%MATCH0%~
		END ~~
	END
	SPRINT roleplay_find ~~
	INNER_PATCH ~%text%~ BEGIN
		REPLACE_EVALUATE CASE_INSENSITIVE ~^\(%roleplay_save%[^%CRLF%]+\)+\(.*[%MNL%%LNL%%WNL%]*\)*~ BEGIN
			SPRINT roleplay_find ~%MATCH1%~
		END ~~
	END
	PATCH_IF NOT (~%roleplay_find%~ STRING_EQUAL ~~) BEGIN
		INNER_PATCH_SAVE text ~%text%~ BEGIN
			REPLACE_TEXTUALLY ~%roleplay_find%%CRLF%%CRLF%~ ~~
			REPLACE_TEXTUALLY ~%roleplay_find%%CRLF%~ ~~
		END
	END
END

// Le sort chargé a-t-il un en-tête dont le projectile est dissipé par Zone d'air pur (ancien
// is_dispellable_by_clearair) ? dispellable : 1 si oui.
DEFINE_PATCH_FUNCTION ad_spell_dispellable_by_clearair
	RET
		dispellable
BEGIN
	SET dispellable = 0
	READ_LONG  SPL_extended_headers_offset clearair_offset
	READ_SHORT SPL_extended_headers_count  clearair_count
	FOR (clearair_h = 0; clearair_h < clearair_count AND NOT dispellable; ++clearair_h) BEGIN
		SET clearair_header = clearair_offset + clearair_h * 0x28
		PATCH_IF clearair_header >= 0 AND clearair_header + 0x28 <= BUFFER_LENGTH BEGIN
			READ_SHORT (clearair_header + SPL_HEAD_projectile) clearair_projectile
			SET clearair_projectile -= 1
			SET dispellable = VARIABLE_IS_SET $AD_CLEARAIR_PROJECTILES(~%clearair_projectile%~)
		END
	END
END

// Sorts et capacités que Zone d'air pur dissipe, pour la description de ce sort (ancien
// spell_list_spells_dispellable_by_clearair) : noms des sorts du jeu qui ont un nom, sans doublon,
// triés.
DEFINE_PATCH_MACRO ad_spell_header_clearair_list BEGIN
	CLEAR_ARRAY clearair_spells
	INNER_ACTION BEGIN
		COPY_EXISTING_REGEXP GLOB ~^.+\.spl$~ ~override~
			READ_LONG SPL_unidentified_name clearair_name_ref
			PATCH_IF clearair_name_ref > 0 BEGIN
				READ_STRREF SPL_unidentified_name clearair_name
				PATCH_IF STRING_LENGTH ~%clearair_name%~ > 0 BEGIN
					LPF ad_spell_dispellable_by_clearair RET clearair_dispellable = dispellable END
					PATCH_IF clearair_dispellable BEGIN
						SET $clearair_spells(~%clearair_name%~) = 1
					END
				END
			END
		BUT_ONLY_IF_IT_CHANGES
	END
	SORT_ARRAY_INDICES clearair_spells LEXICOGRAPHICALLY
	CLEAR_ARRAY clearair_names
	PHP_EACH clearair_spells AS clearair_name => _ BEGIN
		SPRINT $clearair_names(~%clearair_name%~) ~%clearair_name%~
	END
	LPF ad_join STR_VAR array_name = ~clearair_names~ RET spellList = text END
	SPRINT clearair_text @7000032 // ~Les sorts et capacités affectés sont%AD_COLON%%spellList%~
	SPRINT description ~%description%%CRLF%%CRLF%%clearair_text%~
END
