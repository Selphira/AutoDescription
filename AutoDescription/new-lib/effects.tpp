// Magasin d'effets d'une ressource : chaque effet reçoit un identifiant (fx_id, ordre de lecture)
// et ses champs bruts sont rangés dans des tableaux parallèles fx_<champ>(fx_id). Les macros de
// ce fichier s'exécutent dans la portée de ad_describe_item / ad_describe_spell : les tableaux
// disparaissent avec la fonction (V7), rien ne passe d'une ressource à la suivante.
//
// Tableaux écrits : fx_block, fx_header, fx_position, fx_opcode, fx_target, fx_power,
// fx_parameter1, fx_parameter2 (fx_parameter2_raw : valeur lue, qu'une prise en charge ne réécrit
// pas), fx_parameter3, fx_parameter4, fx_resource2, fx_resource3 (0 ou vides : seul un EFF en a,
// new-lib/opcodes/177.tpp), fx_timing, fx_resistance, fx_duration, fx_probability1,
// fx_probability2, fx_resource, fx_dice_count, fx_dice_sides, fx_save_type, fx_save_bonus,
// fx_special, et les valeurs normalisées de new-lib/normalize.tpp ; fx_header_target,
// fx_header_projectile et fx_potion_drinker (ad_fx_header_fields, 0 hors
// d'un en-tête d'objet) ; fx_area_target (0 à la lecture, 1 pour un effet dont les cibles sont
// nommées d'après la zone du projectile, new-lib/application.tpp, qui fixe alors fx_area_cone et
// fx_area_range, texte du rayon) ; fx_late (0 à la lecture, 1 pour
// un effet réuni que l'ancien moteur ajoute en fin de liste par son premier regroupement, les effets
// identiques, 2 par un regroupement suivant, qui l'y ajoute après : chaque opcode écrit ses lignes
// niveau par niveau, new-lib/groups.tpp) ; fx_series_of,
// fx_series_anchor (0 - 1 et 0 à la lecture, répétitions d'un effet, new-lib/application.tpp) ;
// fx_level_value, fx_level_duration et fx_level_save (vides à la lecture, progressions de la valeur,
// de la durée et du bonus du jet de sauvegarde d'un effet présent à tous les niveaux d'un sort, new-lib/spell_levels.tpp) ; fx_level_progression
// (0 à la lecture, 1 pour un effet qui porte une telle progression) ; fx_duration_dice (0 à la lecture,
// N pour une durée tirée au sort de 1dN unités, ad_group_duration_ranges, new-lib/groups.tpp) ;
// fx_consumed (0 à la lecture,
// mis à 1 par new-lib/groups.tpp pour un effet réuni à d'autres) ; fx_dropped (0 à la lecture, 1
// pour un effet écarté, ad_application_drop) ; fx_level_merged (1 pour l'effet d'un en-tête que l'effet
// égal d'un autre niveau représente, new-lib/spell_levels.tpp) ; fx_group_anchor (l'effet lui-même à
// la lecture, celui qui le représente une fois réuni par le regroupement d'un opcode : maladies,
// invocations, ad_group_same_fields) ; fx_derived_source (1 pour l'effet d'ancrage d'un effet dérivé,
// dont la ligne lit les champs, new-lib/groups.tpp) ; fx_exception et fx_exception_count (exceptions de
// cible des opcodes 318 et 324, ad_fx_mark_target_exception, new-lib/opcodes/target_exceptions.tpp) ; fx_not_cumulative (effet lu après un
// 321 sur la ressource elle-même dans son bloc, ad_fx_mark_not_cumulative, new-lib/opcodes/321.tpp) ; fx_external (1 pour un effet 177
// remplacé par celui de son EFF, ad_fx_substitute_177, new-lib/opcodes/177.tpp), fx_probability_in_sub
// (1 pour un effet dont la probabilité est écrite dans les lignes de son sort, new-lib/recursion.tpp),
// fx_parent_probability (0 à la lecture, 1 pour un effet certain d'un sous-sort qui a reçu la
// probabilité de l'effet qui le lance, ad_recursion_base_probability), fx_range_min et fx_range_max
// (0 à la lecture, valeurs tirées au sort réunies, new-lib/opcodes/value_ranges.tpp), fx_versus_file et
// fx_versus_value (fichier IDS et valeur du type de créature visé par ce 177, 0 sans filtre),
// fx_versus_inner_file et fx_versus_inner_value (type d'un 177 imbriqué qui le restreint) ; fx_cursed (1 pour
// un effet 283 remplacé de même par celui de son EFF, new-lib/opcodes/283.tpp) ; fx_opcode_count(opcode).
// Index par opcode : fx_ids_<opcode>, les effets de l'opcode dans l'ordre de lecture (clé et valeur :
// fx_id), parcouru par PHP_EACH ~fx_ids_%opcode%~ AS _ => id ; un opcode absent n'a pas de tableau
// et la boucle ne fait rien. Une passe qui change l'opcode d'un effet reconstruit les deux tableaux
// (ad_fx_index_opcode).
// Variable lue par ad_fx_load_spell : fx_with_casting (0 : le bloc de lancement n'est pas lu ; 1 :
// il l'est, avant les en-têtes, en bloc « casting » sans en-tête, décrit à part).
// Variables écrites : fx_count, fx_header_count, fx_load_error (vide si la lecture a réussi) et
// fx_load_message (son explication, en anglais, pour les journaux).

// Tailles fixes des formats ITM V1 et SPL V1 (IESDP) : en-tête étendu 0x38 (objet) ou 0x28
// (sort), bloc d'effet 0x30.
DEFINE_PATCH_MACRO ad_fx_reset BEGIN
	SET fx_count = 0
	SET fx_header_count = 0
	SET fx_casting_start = 0
	SET fx_casting_count = 0
	SET recursion_pending_count = 0
	SPRINT fx_load_error ~~
	SPRINT fx_load_message ~~
	SPRINT ignored_reason ~~
	SPRINT ignored_message ~~
	SPRINT ignored_consequence ~ignored~
	// Une sous-ressource hérite des tableaux de l'appelant (V7) ; CLEAR_ARRAY laisse les entrées
	// lisibles (V36) : les comptes sont remis à 0, sinon ceux du parent s'ajoutent.
	PHP_EACH fx_opcode_count AS fx_reset_opcode => _ BEGIN
		CLEAR_ARRAY ~fx_ids_%fx_reset_opcode%~
		SET $fx_opcode_count(~%fx_reset_opcode%~) = 0
	END
	CLEAR_ARRAY fx_opcode_count
END

// Reconstruit l'index de l'opcode index_opcode, dans l'ordre des effets : parcourt tout le magasin,
// pas l'index qu'il remplace.
DEFINE_PATCH_MACRO ad_fx_index_opcode BEGIN
	CLEAR_ARRAY ~fx_ids_%index_opcode%~
	FOR (index_id = 0; index_id < fx_count; ++index_id) BEGIN
		PATCH_IF $fx_opcode(~%index_id%~) == index_opcode BEGIN
			SET $EVAL ~fx_ids_%index_opcode%~(~%index_id%~) = index_id
		END
	END
END

DEFINE_PATCH_MACRO ad_fx_load_item BEGIN
	LPM ad_fx_reset
	READ_ASCII ITM_signature fx_signature (8)
	PATCH_IF NOT (~%fx_signature%~ STRING_EQUAL ~ITM V1  ~) BEGIN
		SPRINT fx_load_error ~unsupported_format~
		SPRINT fx_load_message ~signature "%fx_signature%" (expected "ITM V1  ")~
	END
	ELSE PATCH_IF BUFFER_LENGTH < 0x72 BEGIN
		SPRINT fx_load_error ~invalid_file~
		SPRINT fx_load_message ~file of %BUFFER_LENGTH% bytes, shorter than the ITM V1 header (114 bytes)~
	END
	ELSE BEGIN
		READ_LONG  ITM_feature_blocks_offset   fx_table_offset
		READ_LONG  ITM_extended_headers_offset fx_headers_offset
		READ_SHORT ITM_extended_headers_count  fx_header_count
		READ_SHORT ITM_feature_blocks_index    fx_block_index
		READ_SHORT ITM_feature_blocks_count    fx_block_count
		SPRINT fx_block_kind ~equipped~
		SET fx_block_header = 0 - 1
		LPM ad_fx_load_block
		FOR (fx_h = 0; fx_h < fx_header_count AND ~%fx_load_error%~ STRING_EQUAL ~~; ++fx_h) BEGIN
			SET fx_header_offset = fx_headers_offset + fx_h * 0x38
			PATCH_IF fx_header_offset < 0 OR fx_header_offset + 0x38 > BUFFER_LENGTH BEGIN
				SPRINT fx_load_error ~invalid_header~
				SPRINT fx_load_message ~ability %fx_h% at offset %fx_header_offset% lies outside the file (%BUFFER_LENGTH% bytes)~
			END
			ELSE BEGIN
				READ_SHORT (fx_header_offset + ITM_HEAD_feature_block_count) fx_block_count
				READ_SHORT (fx_header_offset + ITM_HEAD_feature_block_index) fx_block_index
				SPRINT fx_block_kind ~ability~
				SET fx_block_header = fx_h
				SET fx_first_id = fx_count
				LPM ad_fx_load_block
				LPM ad_fx_header_fields
			END
		END
	END
END

// Champs de l'en-tête d'objet des effets qui viennent d'être lus. Une potion dont l'en-tête vise
// son utilisateur (cible 5) est bue par lui : ses effets le touchent, quelle que soit leur cible
// (ancien load_charged_abilities).
DEFINE_PATCH_MACRO ad_fx_header_fields BEGIN
	READ_SHORT ITM_type fx_item_type
	READ_BYTE  (fx_header_offset + ITM_HEAD_target)               fx_header_target
	READ_SHORT (fx_header_offset + ITM_HEAD_projectile_animation) fx_header_projectile
	FOR (fx_id = fx_first_id; fx_id < fx_count; ++fx_id) BEGIN
		SET $fx_header_target(~%fx_id%~) = fx_header_target
		SET $fx_header_projectile(~%fx_id%~) = fx_header_projectile
		SET $fx_potion_drinker(~%fx_id%~) = fx_item_type == ITM_TYPE_potion AND fx_header_target == TARGET_HEAD_self
		PATCH_IF $fx_potion_drinker(~%fx_id%~) BEGIN
			SET $fx_effective_target(~%fx_id%~) = TARGET_FX_self
		END
	END
END

DEFINE_PATCH_MACRO ad_fx_load_spell BEGIN
	LPM ad_fx_reset
	READ_ASCII SPL_signature fx_signature (8)
	PATCH_IF NOT (~%fx_signature%~ STRING_EQUAL ~SPL V1  ~) BEGIN
		SPRINT fx_load_error ~unsupported_format~
		SPRINT fx_load_message ~signature "%fx_signature%" (expected "SPL V1  ")~
	END
	ELSE PATCH_IF BUFFER_LENGTH < 0x72 BEGIN
		SPRINT fx_load_error ~invalid_file~
		SPRINT fx_load_message ~file of %BUFFER_LENGTH% bytes, shorter than the SPL V1 header (114 bytes)~
	END
	ELSE BEGIN
		READ_LONG  SPL_feature_blocks_offset         fx_table_offset
		READ_LONG  SPL_extended_headers_offset       fx_headers_offset
		READ_SHORT SPL_extended_headers_count        fx_header_count
		// Malgré leur nom BGforge, 0x6e et 0x20 sont des index dans la table d'effets (IESDP).
		LPM ad_fx_casting_range
		SET fx_block_index = fx_casting_start
		SET fx_block_count = fx_casting_count
		SPRINT fx_block_kind ~casting~
		SET fx_block_header = 0 - 1
		PATCH_IF fx_with_casting BEGIN
			LPM ad_fx_load_block
		END
		FOR (fx_h = 0; fx_h < fx_header_count AND ~%fx_load_error%~ STRING_EQUAL ~~; ++fx_h) BEGIN
			SET fx_header_offset = fx_headers_offset + fx_h * 0x28
			PATCH_IF fx_header_offset < 0 OR fx_header_offset + 0x28 > BUFFER_LENGTH BEGIN
				SPRINT fx_load_error ~invalid_header~
				SPRINT fx_load_message ~ability %fx_h% at offset %fx_header_offset% lies outside the file (%BUFFER_LENGTH% bytes)~
			END
			ELSE BEGIN
				READ_SHORT (fx_header_offset + SPL_HEAD_feature_blocks_count)  fx_block_count
				READ_SHORT (fx_header_offset + SPL_HEAD_feature_blocks_offset) fx_block_index
				SPRINT fx_block_kind ~ability~
				SET fx_block_header = fx_h
				LPM ad_fx_load_block
			END
		END
	END
END

// Lit fx_block_count effets à partir de l'index fx_block_index de la table d'effets. Une lecture
// hors du fichier ferait échouer toute la ressource (V31) : les bornes sont vérifiées avant. Les 177
// sont lus après les autres effets du bloc : l'ancien moteur (opcode_177_replace) ajoute l'effet de
// leur EFF en fin de liste, il est donc écrit après les effets du fichier de même opcode. La
// première passe note leurs positions (fx_deferred) : la seconde ne relit qu'eux, avec les exceptions
// de cible et la marque « non cumulatif » de leur place dans le bloc, que l'ancien moteur leur
// attache à la lecture.
DEFINE_PATCH_MACRO ad_fx_load_block BEGIN
	SET fx_block_exceptions = 0
	SET fx_block_not_cumulative = 0
	SET fx_deferred_count = 0
	SET fx_pass = 0
	FOR (fx_p = 0; fx_p < fx_block_count AND ~%fx_load_error%~ STRING_EQUAL ~~; ++fx_p) BEGIN
		LPM ad_fx_load_block_effect
	END
	SET fx_pass = 1
	FOR (fx_k = 0; fx_k < fx_deferred_count AND ~%fx_load_error%~ STRING_EQUAL ~~; ++fx_k) BEGIN
		SET fx_p = $fx_deferred(~%fx_k%~)
		SET fx_block_exceptions = $fx_deferred_exceptions(~%fx_k%~)
		SET fx_block_not_cumulative = $fx_deferred_not_cumulative(~%fx_k%~)
		LPM ad_fx_load_block_effect
	END
END

// Bloc de lancement du sort chargé (fx_casting_start, fx_casting_count) : un effet d'en-tête qui y
// tombe n'est pas relu avec l'en-tête (ad_fx_load_block_effect).
DEFINE_PATCH_MACRO ad_fx_casting_range BEGIN
	READ_SHORT SPL_casting_feature_blocks_offset fx_casting_start
	READ_SHORT SPL_casting_feature_blocks_count  fx_casting_count
END

// Un effet d'en-tête pris dans le bloc de lancement (index de l'en-tête qui le chevauche : OHBWI302,
// OHBWI304) n'est pas lu : le jeu l'applique déjà à chaque lancement.
DEFINE_PATCH_MACRO ad_fx_load_block_effect BEGIN
	SET fx_offset = fx_table_offset + (fx_block_index + fx_p) * 0x30
	SET fx_table_index = fx_block_index + fx_p
	PATCH_IF fx_block_header >= 0
			AND fx_table_index >= fx_casting_start AND fx_table_index < fx_casting_start + fx_casting_count BEGIN
		PATCH_IF fx_pass == 0 BEGIN
			SET fx_casting_end = fx_casting_start + fx_casting_count - 1
			LPF ad_refusal STR_VAR reason = ~file_error:spell:casting_overlap~ message = ~ability %fx_block_header% effect %fx_p% (index %fx_table_index%) is also casting effect %fx_table_index% (casting effects %fx_casting_start%-%fx_casting_end%): ability effect index %fx_block_index% overlaps the casting effects; read once, as a casting effect~ RET fx_overlap_event = refusal END
			LPF ad_log_event STR_VAR event = ~%fx_overlap_event%~ consequence = ~ignored~ RET fx_overlap_logged = reason END
		END
	END
	ELSE PATCH_IF fx_offset < 0 OR fx_offset + 0x30 > BUFFER_LENGTH BEGIN
		SPRINT fx_load_error ~invalid_effect~
		SPRINT fx_load_message ~%fx_block_kind% effect %fx_p%~
		PATCH_IF fx_block_header >= 0 BEGIN
			SPRINT fx_load_message ~ability %fx_block_header%, effect %fx_p%~
		END
		SPRINT fx_load_message ~%fx_load_message% at offset %fx_offset% lies outside the file (%BUFFER_LENGTH% bytes)~
	END
	ELSE BEGIN
		READ_SHORT (fx_offset + FX_opcode) fx_pass_opcode
		PATCH_IF fx_pass_opcode == 177 AND fx_pass == 0 BEGIN
			SET $fx_deferred(~%fx_deferred_count%~) = fx_p
			SET $fx_deferred_exceptions(~%fx_deferred_count%~) = fx_block_exceptions
			SET $fx_deferred_not_cumulative(~%fx_deferred_count%~) = fx_block_not_cumulative
			SET fx_deferred_count += 1
		END
		ELSE BEGIN
			SET fx_id = fx_count
			SPRINT $fx_block(~%fx_id%~) ~%fx_block_kind%~
			SET $fx_header(~%fx_id%~)   = fx_block_header
			SET $fx_position(~%fx_id%~) = fx_p
			SET $fx_opcode(~%fx_id%~)   = fx_pass_opcode
			READ_BYTE  (fx_offset + FX_target)       $fx_target(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_power)        $fx_power(~%fx_id%~)
			READ_LONG  (fx_offset + FX_parameter1)   $fx_parameter1(~%fx_id%~)
			READ_LONG  (fx_offset + FX_parameter2)   $fx_parameter2(~%fx_id%~)
			SET $fx_parameter2_raw(~%fx_id%~) = $fx_parameter2(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_timing)       $fx_timing(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_resistance)   $fx_resistance(~%fx_id%~)
			READ_LONG  (fx_offset + FX_duration)     $fx_duration(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_probability1) $fx_probability1(~%fx_id%~)
			READ_BYTE  (fx_offset + FX_probability2) $fx_probability2(~%fx_id%~)
			READ_ASCII (fx_offset + FX_resource)     $fx_resource(~%fx_id%~) (8) NULL
			READ_LONG  (fx_offset + FX_dice_thrown)  $fx_dice_count(~%fx_id%~)
			READ_LONG  (fx_offset + FX_dice_sides)   $fx_dice_sides(~%fx_id%~)
			READ_LONG  (fx_offset + FX_save_type)    $fx_save_type(~%fx_id%~)
			READ_LONG  (fx_offset + FX_save_bonus)   $fx_save_bonus(~%fx_id%~)
			READ_LONG  (fx_offset + FX_stacking_id_Ex) $fx_special(~%fx_id%~)
			SET $fx_external(~%fx_id%~) = 0
			SET $fx_parameter3(~%fx_id%~) = 0
			SET $fx_parameter4(~%fx_id%~) = 0
			SPRINT $fx_resource2(~%fx_id%~) ~~
			SPRINT $fx_resource3(~%fx_id%~) ~~
			LPM ad_fx_add_effect
		END
	END
END

// Un effet d'un fichier EFF de l'opcode eff_fields_opcode, aux champs eff_fields_parameter2,
// eff_fields_parameter3, eff_fields_parameter4, eff_fields_resource2 et eff_fields_resource3, est-il
// décrit autrement par l'ancien moteur (AD_OPCODES_EFF_FIELDS) ? eff_fields_differ : 1 si oui.
DEFINE_PATCH_MACRO ad_eff_fields_differ BEGIN
	SET eff_fields_differ = 0
	PATCH_IF VARIABLE_IS_SET $AD_OPCODES_EFF_FIELDS(~%eff_fields_opcode%~) BEGIN
		SPRINT eff_fields_mode $AD_OPCODES_EFF_FIELDS(~%eff_fields_opcode%~)
		PATCH_IF ~%eff_fields_mode%~ STRING_EQUAL ~ALL~ BEGIN
			SET eff_fields_differ = 1
		END
		ELSE PATCH_IF ~%eff_fields_mode%~ STRING_EQUAL ~RESOURCES_EE~ BEGIN
			SET eff_fields_differ = IS_EE AND (NOT (~%eff_fields_resource2%~ STRING_EQUAL ~~) OR NOT (~%eff_fields_resource3%~ STRING_EQUAL ~~))
		END
		ELSE PATCH_IF ~%eff_fields_mode%~ STRING_EQUAL ~PARAMETER3_EE~ BEGIN
			SET eff_fields_differ = IS_EE AND eff_fields_parameter3 != 0
		END
		ELSE PATCH_IF ~%eff_fields_mode%~ STRING_EQUAL ~TYPE4_PARAMETER4_EE~ BEGIN
			SET eff_fields_differ = eff_fields_parameter2 == 4 OR (IS_EE AND eff_fields_parameter4 != 0)
		END
		ELSE BEGIN
			SET eff_fields_differ = eff_fields_mode == eff_fields_parameter2
		END
	END
END

// Fin de la lecture de l'effet fx_id, dont les champs bruts sont lus (fx_external et fx_parameter3
// compris) : remplacement d'un 177 ou d'un 111, valeurs normalisées, marques des passes, compte de
// l'opcode.
DEFINE_PATCH_MACRO ad_fx_add_effect BEGIN
	SET $fx_versus_file(~%fx_id%~) = 0
	SET $fx_versus_value(~%fx_id%~) = 0
	SET $fx_versus_inner_file(~%fx_id%~) = 0
	SET $fx_versus_inner_value(~%fx_id%~) = 0
	SET $fx_identical_anchor(~%fx_id%~) = fx_id
	SET $fx_group_anchor(~%fx_id%~) = fx_id
	SET $fx_derived_source(~%fx_id%~) = 0
	SET $fx_from_111(~%fx_id%~) = 0
	SET $fx_probability_in_sub(~%fx_id%~) = 0
	SET $fx_cursed(~%fx_id%~) = $fx_opcode(~%fx_id%~) == 283
	PATCH_IF $fx_opcode(~%fx_id%~) == 177 OR $fx_opcode(~%fx_id%~) == 283 BEGIN
		LPM ad_fx_substitute_177
	END
	ELSE PATCH_IF $fx_opcode(~%fx_id%~) == 111 BEGIN
		LPM ad_fx_substitute_111
	END
	// Valeurs lues des champs que des passes réécrivent ensuite (regroupements, opcodes 23, 143, 189),
	// pour les journaux (ad_fx_data, new-lib/log.tpp), comme fx_parameter2_raw.
	SET $fx_parameter1_raw(~%fx_id%~) = $fx_parameter1(~%fx_id%~)
	SET $fx_timing_raw(~%fx_id%~) = $fx_timing(~%fx_id%~)
	SET $fx_duration_raw(~%fx_id%~) = $fx_duration(~%fx_id%~)
	SET $fx_dice_count_raw(~%fx_id%~) = $fx_dice_count(~%fx_id%~)
	SET $fx_special_raw(~%fx_id%~) = $fx_special(~%fx_id%~)
	SET $fx_save_type_raw(~%fx_id%~) = $fx_save_type(~%fx_id%~)
	LPM ad_fx_normalize
	SET $fx_consumed(~%fx_id%~) = 0
	SET $fx_dropped(~%fx_id%~) = 0
	SET $fx_parent_probability(~%fx_id%~) = 0
	SET $fx_range_min(~%fx_id%~) = 0
	SET $fx_range_max(~%fx_id%~) = 0
	SET $fx_level_merged(~%fx_id%~) = 0
	SET $fx_header_target(~%fx_id%~) = 0
	SET $fx_header_projectile(~%fx_id%~) = 0
	SET $fx_potion_drinker(~%fx_id%~) = 0
	SET $fx_area_target(~%fx_id%~) = 0
	SET $fx_area_cone(~%fx_id%~) = 0
	SPRINT $fx_area_range(~%fx_id%~) ~~
	SET $fx_late(~%fx_id%~) = 0
	SET $fx_series_of(~%fx_id%~) = 0 - 1
	SET $fx_series_anchor(~%fx_id%~) = 0
	SPRINT $fx_level_value(~%fx_id%~) ~~
	SPRINT $fx_dice_text(~%fx_id%~) ~~
	SET $fx_charge_rewritten(~%fx_id%~) = 0
	SPRINT $fx_level_duration(~%fx_id%~) ~~
	SET $fx_duration_dice(~%fx_id%~) = 0
	SPRINT $fx_level_save(~%fx_id%~) ~~
	SET $fx_level_progression(~%fx_id%~) = 0
	LPM ad_fx_mod_ignored
	// Écarté comme un effet que l'ancien moteur ne charge pas : sans effet sur son bloc (exceptions de
	// cible, 321 qui rend la suite non cumulative).
	PATCH_IF fx_mod_ignored BEGIN
		SET $fx_exception_count(~%fx_id%~) = fx_block_exceptions
		SET $fx_exception(~%fx_id%~) = 0
		SET $fx_exception_name_count(~%fx_id%~) = 0
		SET $fx_not_cumulative(~%fx_id%~) = fx_block_not_cumulative
		SET $fx_consumed(~%fx_id%~) = 1
		SET $fx_dropped(~%fx_id%~) = 1
	END
	ELSE BEGIN
		LPM ad_fx_mark_target_exception
		LPM ad_fx_mark_not_cumulative
	END
	SET fx_opcode = $fx_opcode(~%fx_id%~)
	SET $fx_opcode_count(~%fx_opcode%~) = VARIABLE_IS_SET $fx_opcode_count(~%fx_opcode%~) ? $fx_opcode_count(~%fx_opcode%~) + 1 : 1
	SET $EVAL ~fx_ids_%fx_opcode%~(~%fx_id%~) = fx_id
	PATCH_IF $fx_external(~%fx_id%~) BEGIN
		SET $fx_opcode_count(~177~) = VARIABLE_IS_SET $fx_opcode_count(~177~) ? $fx_opcode_count(~177~) + 1 : 1
	END
	PATCH_IF $fx_cursed(~%fx_id%~) AND fx_opcode != 283 BEGIN
		SET $fx_opcode_count(~283~) = VARIABLE_IS_SET $fx_opcode_count(~283~) ? $fx_opcode_count(~283~) + 1 : 1
	END
	SET fx_count += 1
END

// fx_mod_ignored : 1 si l'effet fx_id est l'un de ceux que l'ancien moteur écarte pour un mod
// (2da/mod_ignored.2da, ad_read_mod_ignored, new-lib/catalog.tpa).
DEFINE_PATCH_MACRO ad_fx_mod_ignored BEGIN
	SET mod_opcode = $fx_opcode(~%fx_id%~)
	SPRINT mod_resource $fx_resource_lower(~%fx_id%~)
	SET fx_mod_ignored = VARIABLE_IS_SET $AD_MOD_IGNORED_EXACT(~%mod_opcode%~ ~%mod_resource%~)
	PATCH_IF NOT fx_mod_ignored AND VARIABLE_IS_SET $AD_MOD_IGNORED_PARTIAL_COUNT(~%mod_opcode%~) BEGIN
		FOR (mod_rank = 0; mod_rank < $AD_MOD_IGNORED_PARTIAL_COUNT(~%mod_opcode%~); ++mod_rank) BEGIN
			SPRINT mod_rule $AD_MOD_IGNORED_PARTIAL(~%mod_opcode%~ ~%mod_rank%~)
			PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~PREFIX ~ ~%mod_rule%~) == 0 BEGIN
				SPRINT mod_value ~%mod_rule%~
				INNER_PATCH_SAVE mod_value ~%mod_value%~ BEGIN DELETE_BYTES 0 7 END
				SET fx_mod_ignored = fx_mod_ignored OR INDEX (CASE_SENSITIVE EXACT_MATCH ~%mod_value%~ ~%mod_resource%~) == 0
			END
			ELSE BEGIN
				SPRINT mod_value ~%mod_rule%~
				INNER_PATCH_SAVE mod_value ~%mod_value%~ BEGIN DELETE_BYTES 0 9 END
				SET fx_mod_ignored = fx_mod_ignored OR INDEX (CASE_SENSITIVE EXACT_MATCH ~%mod_value%~ ~%mod_resource%~) >= 0
			END
		END
	END
	PATCH_IF NOT fx_mod_ignored AND mod_opcode == 326 BEGIN
		SET mod_splprot = $fx_parameter2_raw(~%fx_id%~)
		SET fx_mod_ignored = VARIABLE_IS_SET $AD_MOD_IGNORED_SPLPROT(~%mod_splprot%~)
		PATCH_IF NOT fx_mod_ignored AND VARIABLE_IS_SET $AD_SPLPROT_STAT(~%mod_splprot%~) BEGIN
			SPRINT mod_stat $AD_SPLPROT_STAT(~%mod_splprot%~)
			PATCH_IF ~%mod_stat%~ STRING_EQUAL ~274~ BEGIN
				SET mod_state = $fx_parameter1_raw(~%fx_id%~)
				SET fx_mod_ignored = VARIABLE_IS_SET $AD_MOD_IGNORED_SPLSTATE(~%mod_state%~)
			END
		END
	END
END
