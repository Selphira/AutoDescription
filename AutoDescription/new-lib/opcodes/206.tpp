// Opcode 206 (Spell: Protection from Spell) : immunité au sort resource, « Immunité au sort
// « Lent » » ; nom du sort par ad_spell_name (new-lib/resources.tpp), sans ligne si le nom est
// vide. Une immunité à l'opcode que le sort inflige peut l'absorber (ad_group_immunities,
// new-lib/groups.tpp).
//
// Pris en charge : effets que la prise en charge commune accepte (ad_application_support,
// new-lib/application.tpp). Avec AD_ENABLE_SHRINKAGE, cinq protections psioniques d'un bloc
// deviennent « Immunité aux capacités psioniques » (ad_group_psionic_immunity, new-lib/groups.tpp).

// Effet sans ressource : écarté sans rien écrire, erreur journalisée. L'immunité aux capacités
// psioniques prend les champs de la cinquième protection, qui la placent dans un groupe de la ligne
// unique des immunités (new-lib/opcodes/101.tpp).
DEFINE_PATCH_MACRO ad_op_206_support BEGIN
	PHP_EACH fx_ids_206 AS _ => spell_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SPRINT spell_resref $fx_resource(~%spell_id%~)
			TO_UPPER spell_resref
			// L'ancien moteur écarte un effet sans ressource (erreur journalisée).
			PATCH_IF ~%spell_resref%~ STRING_EQUAL ~~ BEGIN
				SET drop_id = spell_id
				SPRINT ignored_reason ~file_error:opcode206:invalid~
				SPRINT ignored_message ~empty resource field~
				LPM ad_application_drop
			END
			// Sort absent ou sans nom : pas de ligne (ad_op_206_lines), comme dans l'ancien moteur ; sans
			// objet pour l'en-tête d'un sort seul.
			ELSE PATCH_IF NOT support_header_only BEGIN
				LPF ad_spell_name STR_VAR resref = ~%spell_resref%~ RET spell_support_name = name END
				PATCH_IF ~%spell_support_name%~ STRING_EQUAL ~~ BEGIN
					SET ignored_fx = spell_id
					SPRINT ignored_reason ~not_implemented:opcode206:no_name~
					SPRINT ignored_message ~spell %spell_resref%.SPL has no name~
					PATCH_IF NOT FILE_EXISTS_IN_GAME ~%spell_resref%.spl~ BEGIN
						SPRINT ignored_reason ~file_error:opcode206:missing_spell~
						SPRINT ignored_message ~spell %spell_resref%.SPL does not exist~
					END
					LPM ad_log_ignored
				END
			END
		END
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_IMMUNITIES_SINGLE_LINE BEGIN
		LPM ad_op_206_psionic_support
	END
END

// Cinquième protection psionique de chaque en-tête qui en a au moins cinq : mêmes champs que les
// immunités (101) de l'en-tête.
DEFINE_PATCH_MACRO ad_op_206_psionic_support BEGIN
	CLEAR_ARRAY spell_psionic_count
	FOR (spell_id = 0; spell_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++spell_id) BEGIN
		SPRINT spell_scope $fx_scope(~%spell_id%~)
		SPRINT spell_resref $fx_resource(~%spell_id%~)
		TO_UPPER spell_resref
		PATCH_IF $fx_opcode(~%spell_id%~) == 206 AND VARIABLE_IS_SET $AD_IMMUNITY_SPELLS(~505 %spell_resref%~)
				AND NOT (~%spell_scope%~ STRING_EQUAL ~equipped~) BEGIN
			SET spell_psionic_total = VARIABLE_IS_SET $spell_psionic_count(~%spell_scope%~) ? $spell_psionic_count(~%spell_scope%~) + 1 : 1
			SET $spell_psionic_count(~%spell_scope%~) = spell_psionic_total
			PATCH_IF spell_psionic_total == 5 BEGIN
				SET same_id = spell_id
				SET same_ignored = AD_SAME_PARAMETER2
				PHP_EACH fx_ids_101 AS _ => spell_other BEGIN
					SPRINT spell_other_scope $fx_scope(~%spell_other%~)
					PATCH_IF (~%spell_other_scope%~ STRING_EQUAL ~%spell_scope%~) BEGIN
						SET same_other = spell_other
						LPM ad_fx_same_fields
						PATCH_IF NOT fx_same BEGIN
							LPF ad_refusal INT_VAR fx_id = spell_other STR_VAR reason = ~not_implemented:opcode206:psionic_fields~ message = ~psionic protections and immunities of the ability with different fields~ RET render_missing = refusal END
						END
					END
				END
			END
		END
	END
END

// Lignes (ancien opcode_self_206 et opcode_206_post_group) : avec AD_ENABLE_SHRINKAGE, les
// immunités d'une même cible et d'une même section (portée, ou plage de niveaux d'un sort à plusieurs
// en-têtes ; l'ancien moteur décrit chaque bloc à part) à au moins deux sorts de noms différents sont
// réunies en une ligne
// (effet dérivé SPELL_IMMUNITIES), noms triés ; les lignes réunies viennent après les autres. Comme
// l'ancien opcode_206_post_group, le groupe s'ouvre sur un effet, même sans nom ; les autres le
// rejoignent s'il dure tant que l'objet est porté, et la ligne prend alors sa durée (SOLAK1B), ou s'ils
// ont même timing et même durée. Dans un sort à plusieurs en-têtes, ils doivent aussi avoir la même
// progression de durée entre niveaux (fx_level_duration, new-lib/spell_levels.tpp) : la durée du
// premier niveau ne suffit pas (SPWI613 du jeu de base).
DEFINE_PATCH_MACRO ad_op_206_lines BEGIN
	SPRINT line_section ~equipped~
	FOR (spell_id = 0; spell_id < fx_count; ++spell_id) BEGIN
		SET $spell_group(~%spell_id%~) = 0 - 1
		PATCH_IF $fx_opcode(~%spell_id%~) == 206 AND NOT $fx_consumed(~%spell_id%~) BEGIN
			SPRINT spell_resref $fx_resource(~%spell_id%~)
			LPF ad_spell_name STR_VAR resref = ~%spell_resref%~ RET spell_name = name END
			SPRINT $spell_name(~%spell_id%~) ~%spell_name%~
		END
	END
	SET spell_group_count = 0
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		PHP_EACH fx_ids_206 AS _ => spell_id BEGIN
			PATCH_IF NOT $fx_consumed(~%spell_id%~) AND $spell_group(~%spell_id%~) < 0 BEGIN
				SET spell_target = $fx_effective_target(~%spell_id%~)
				SPRINT spell_scope $fx_line_section(~%spell_id%~)
				SET spell_timing = $fx_timing(~%spell_id%~)
				SET spell_duration = $fx_duration(~%spell_id%~)
				SPRINT spell_level_duration $fx_level_duration(~%spell_id%~)
				SET $spell_group_head(~%spell_group_count%~) = spell_id
				SET spell_name_count = 0
				PHP_EACH fx_ids_206 AS _ => spell_other BEGIN
					SPRINT spell_other_scope $fx_line_section(~%spell_other%~)
					SPRINT spell_other_level_duration $fx_level_duration(~%spell_other%~)
					// Un effet déjà rangé a son groupe : seul l'ordre de fx_ids_206 compte, les effets placés après
					// les autres (fx_late, 318 devenus des 206) y compris.
					PATCH_IF NOT $fx_consumed(~%spell_other%~) AND $spell_group(~%spell_other%~) < 0 AND $fx_effective_target(~%spell_other%~) == spell_target AND (~%spell_other_scope%~ STRING_EQUAL ~%spell_scope%~)
							AND (spell_timing == TIMING_while_equipped OR ($fx_timing(~%spell_other%~) == spell_timing AND $fx_duration(~%spell_other%~) == spell_duration))
							AND (~%spell_other_level_duration%~ STRING_EQUAL ~%spell_level_duration%~) BEGIN
						SPRINT spell_name $spell_name(~%spell_other%~)
						PATCH_IF NOT ~%spell_name%~ STRING_EQUAL ~~ BEGIN
							SET spell_name_new = 1
							PHP_EACH fx_ids_206 AS _ => spell_member BEGIN
								PATCH_IF $spell_group(~%spell_member%~) == spell_group_count BEGIN
									SPRINT spell_member_name $spell_name(~%spell_member%~)
									PATCH_IF ~%spell_member_name%~ STRING_EQUAL ~%spell_name%~ BEGIN
										SET spell_name_new = 0
									END
								END
							END
							SET $spell_group(~%spell_other%~) = spell_group_count
							SET spell_name_count += spell_name_new
						END
					END
				END
				SET $spell_group_size(~%spell_group_count%~) = spell_name_count
				SET spell_group_count += 1
			END
		END
	END
	SET line_sort = $AD_OPCODE_SORT(~206~)
	PHP_EACH fx_ids_206 AS _ => spell_id BEGIN
		PATCH_IF NOT $fx_consumed(~%spell_id%~) BEGIN
			SET spell_group_id = $spell_group(~%spell_id%~)
			SPRINT spellName $spell_name(~%spell_id%~)
			PATCH_IF NOT ~%spellName%~ STRING_EQUAL ~~ AND (spell_group_id < 0 OR $spell_group_size(~%spell_group_id%~) < 2) BEGIN
				SET line_phrase = 22060100 // ~Immunité contre le sort « %spellName% »~
				SET line_fx = spell_id
				LPM ad_effect_line
			END
		END
	END
	SET line_sort = $AD_DERIVED_SORT(~SPELL_IMMUNITIES~)
	FOR (spell_group_id = 0; spell_group_id < spell_group_count; ++spell_group_id) BEGIN
		PATCH_IF $spell_group_size(~%spell_group_id%~) >= 2 BEGIN
			CLEAR_ARRAY spell_group_names
			SET spell_first = 0 - 1
			PHP_EACH fx_ids_206 AS _ => spell_id BEGIN
				PATCH_IF NOT $fx_consumed(~%spell_id%~) AND $spell_group(~%spell_id%~) == spell_group_id BEGIN
					SPRINT spell_name $spell_name(~%spell_id%~)
					SPRINT $spell_group_names(~%spell_name%~) ~%spell_name%~
					PATCH_IF spell_first < 0 BEGIN
						SET spell_first = spell_id
					END
				END
			END
			SORT_ARRAY_INDICES spell_group_names
			SPRINT and ~%AD_AND%~
			SPRINT spell_glue @1000005 // ~ », « ~
			SPRINT spell_final_glue @1000006 // ~ » %and% « ~
			LPF ad_join STR_VAR array_name = ~spell_group_names~ glue = ~%spell_glue%~ final_glue = ~%spell_final_glue%~ RET spellNames = text END
			SET line_phrase = 30100100 // ~Immunité contre les sorts « %spellNames% »~
			// Les membres ont le timing et la durée de la tête, sauf si elle dure tant que l'objet est porté :
			// la ligne est alors celle de la tête ; sinon celle du premier sort nommé, qui garde sa plage de
			// niveaux (TR#DC03 : tête sans nom sur le seul premier en-tête).
			SET spell_head = $spell_group_head(~%spell_group_id%~)
			SET line_fx = $fx_timing(~%spell_head%~) == TIMING_while_equipped ? spell_head : spell_first
			LPM ad_effect_line
		END
	END
END

// En-tête d'un sort seul (new-lib/spell_header.tpp), après les regroupements (ancien
// opcode_206_post_group, seconde partie) : dans chaque en-tête, les immunités de même cible et, sauf
// si la première dure tant que l'objet est porté, de même timing et même durée, à au moins deux sorts
// de noms différents disparaissent (avec la première, même sans nom) au profit d'un effet 518. Comme
// dans l'ancien moteur, celui-ci prend les champs de la dernière immunité qui reste dans l'en-tête,
// réunie ou non (ad_derived_add, sans ligne). Les immunités réunies sont cachées à l'en-tête
// (fx_header_hidden) : leurs lignes sont écrites par ad_op_206_lines. Pour la comparaison entre
// niveaux (new-lib/spell_levels.tpp), chacune garde son effet dérivé (fx_immunity_derived, -1 sans
// regroupement) et celui-ci la liste triée des noms (derived_signature), que l'ancien moteur compare
// dans custom_str. Dans un sort à plusieurs en-têtes, une immunité ne rejoint le groupe que si elle
// garde le timing et la durée de la première dans tous les en-têtes lus (ad_op_206_same_on_all_levels).
DEFINE_PATCH_MACRO ad_op_206_header_groups BEGIN
	SET immunity_serial = 0
	PHP_EACH fx_ids_206 AS _ => immunity_id BEGIN
		SET $fx_immunity_derived(~%immunity_id%~) = 0 - 1
	END
	FOR (immunity_h = 0; immunity_h < fx_header_count; ++immunity_h) BEGIN
		SET $immunity_header_loaded(~%immunity_h%~) = 0
	END
	FOR (immunity_id = 0; immunity_id < fx_count; ++immunity_id) BEGIN
		SET immunity_block = $fx_header(~%immunity_id%~)
		PATCH_IF immunity_block >= 0 BEGIN
			SET $immunity_header_loaded(~%immunity_block%~) = 1
		END
	END
	// Timing et durée de la première immunité de chaque ressource dans chaque en-tête, hors EFF, lus
	// une fois pour ad_op_206_same_on_all_levels ; clé préfixée par le numéro du sort (V36).
	PATCH_IF NOT VARIABLE_IS_SET immunity_levels_serial BEGIN
		SET immunity_levels_serial = 0
	END
	SET immunity_levels_serial += 1
	PATCH_IF fx_header_count > 1 BEGIN
		PHP_EACH fx_ids_206 AS _ => level_id BEGIN
			SET level_h = $fx_header(~%level_id%~)
			PATCH_IF level_h >= 0 AND NOT $fx_external(~%level_id%~) BEGIN
				SPRINT level_resref $fx_resource_lower(~%level_id%~)
				PATCH_IF NOT VARIABLE_IS_SET $immunity_level_timing(~%immunity_levels_serial% %level_h% %level_resref%~) BEGIN
					SET $immunity_level_timing(~%immunity_levels_serial% %level_h% %level_resref%~) = $fx_timing_raw(~%level_id%~)
					SET $immunity_level_duration(~%immunity_levels_serial% %level_h% %level_resref%~) = $fx_duration_raw(~%level_id%~)
				END
			END
		END
	END
	FOR (immunity_h = 0; immunity_h < fx_header_count; ++immunity_h) BEGIN
		SET immunity_size = 0
		FOR (immunity_late = 0; immunity_late < 3; ++immunity_late) BEGIN
			PHP_EACH fx_ids_206 AS _ => immunity_id BEGIN
				PATCH_IF $fx_header(~%immunity_id%~) == immunity_h AND NOT $fx_consumed(~%immunity_id%~) AND NOT $fx_header_hidden(~%immunity_id%~)
						AND $fx_late(~%immunity_id%~) == immunity_late BEGIN
					SET $immunity_order(~%immunity_size%~) = immunity_id
					SET $immunity_checked(~%immunity_size%~) = 0
					SPRINT immunity_resref $fx_resource(~%immunity_id%~)
					LPF ad_spell_name STR_VAR resref = ~%immunity_resref%~ RET immunity_name = name END
					SPRINT $immunity_names(~%immunity_size%~) ~%immunity_name%~
					SET immunity_size += 1
				END
			END
		END
		FOR (immunity_k = 0; immunity_k < immunity_size; ++immunity_k) BEGIN
			SET immunity_id = $immunity_order(~%immunity_k%~)
			PATCH_IF NOT $immunity_checked(~%immunity_k%~) AND NOT $fx_header_hidden(~%immunity_id%~) BEGIN
				SET immunity_target = $fx_target(~%immunity_id%~)
				SET immunity_timing = $fx_timing(~%immunity_id%~)
				SET immunity_duration = $fx_duration(~%immunity_id%~)
				// Noms déjà vus du groupe : clé préfixée par son numéro, CLEAR_ARRAY ne les oubliant pas (V36).
				SET immunity_serial += 1
				SET immunity_name_count = 0
				SET immunity_member_count = 0
				SET $immunity_members(~0~) = immunity_k
				SET immunity_member_count = 1
				SET immunity_last = 0 - 1
				SET immunity_last_member = immunity_id
				SET immunity_last_unstable = 0
				FOR (immunity_j = 0; immunity_j < immunity_size; ++immunity_j) BEGIN
					SET immunity_other = $immunity_order(~%immunity_j%~)
					PATCH_IF NOT $fx_header_hidden(~%immunity_other%~) BEGIN
						SET immunity_last = immunity_other
						SET immunity_last_unstable = 0
						PATCH_IF NOT $immunity_checked(~%immunity_j%~) AND $fx_target(~%immunity_other%~) == immunity_target
								AND (immunity_timing == TIMING_while_equipped OR ($fx_timing(~%immunity_other%~) == immunity_timing AND $fx_duration(~%immunity_other%~) == immunity_duration)) BEGIN
							SPRINT immunity_name $immunity_names(~%immunity_j%~)
							SET immunity_stable = 1
							PATCH_IF immunity_j != immunity_k AND NOT (~%immunity_name%~ STRING_EQUAL ~~) BEGIN
								LPM ad_op_206_same_on_all_levels
								SET immunity_last_unstable = NOT immunity_stable
							END
							PATCH_IF NOT (~%immunity_name%~ STRING_EQUAL ~~) AND immunity_stable BEGIN
								SET immunity_last_member = immunity_other
								PATCH_IF NOT VARIABLE_IS_SET $immunity_group_names(~%immunity_serial% %immunity_name%~) BEGIN
									SET immunity_name_count += 1
								END
								SET $immunity_group_names(~%immunity_serial% %immunity_name%~) = 1
								SET $immunity_checked(~%immunity_j%~) = 1
								PATCH_IF immunity_j != immunity_k BEGIN
									SET $immunity_members(~%immunity_member_count%~) = immunity_j
									SET immunity_member_count += 1
								END
							END
						END
					END
				END
				PATCH_IF immunity_name_count > 1 BEGIN
					CLEAR_ARRAY immunity_signature_names
					FOR (immunity_m = 0; immunity_m < immunity_member_count; ++immunity_m) BEGIN
						SET immunity_member = $immunity_members(~%immunity_m%~)
						SET immunity_member_id = $immunity_order(~%immunity_member%~)
						SET $fx_header_hidden(~%immunity_member_id%~) = 1
						SET $fx_immunity_derived(~%immunity_member_id%~) = derived_count
						SPRINT immunity_name $immunity_names(~%immunity_member%~)
						SPRINT $immunity_signature_names(~%immunity_name%~) ~%immunity_name%~
					END
					SORT_ARRAY_INDICES immunity_signature_names
					LPF ad_join STR_VAR array_name = ~immunity_signature_names~ glue = ~|~ final_glue = ~|~ RET immunity_signature = text END
					SPRINT $derived_signature(~%derived_count%~) ~%immunity_signature%~
					SPRINT derived_kind ~SPELL_IMMUNITIES~
					// Dernière immunité écartée par ad_op_206_same_on_all_levels : elle peut être de tous les
					// niveaux et écarter l'effet dérivé avec elle ; il prend le dernier membre (PXW7BARR).
					SET derived_id = immunity_last
					PATCH_IF immunity_last_unstable BEGIN
						SET derived_id = immunity_last_member
					END
					SET derived_other = 0 - 1
					SPRINT derived_line ~~
					LPM ad_derived_add
				END
			END
		END
	END
END

// Immunités immunity_id (première du groupe) et immunity_other : immunity_stable vaut 0 si un en-tête
// lu (immunity_header_loaded) n'a que l'une des deux, ou les a de timing ou de durée différents, sauf
// si la première dure tant que l'objet est porté. Sans cela, la réunion d'un seul niveau rendrait ce
// niveau différent des autres et empêcherait la progression de la durée (SPWI613 du jeu de base,
// SPCL521 de 90 secondes à tous les niveaux). Comme l'ancien opcode_206_same_duration_on_all_levels,
// ce sont les valeurs lues dans le fichier, hors effets d'un EFF (fx_external), qui sont comparées,
// celles de la première immunité de chaque ressource dans l'en-tête (immunity_level_timing et
// immunity_level_duration, ad_op_206_header_groups).
DEFINE_PATCH_MACRO ad_op_206_same_on_all_levels BEGIN
	SET immunity_stable = 1
	SPRINT immunity_head_resref $fx_resource_lower(~%immunity_id%~)
	SPRINT immunity_member_resref $fx_resource_lower(~%immunity_other%~)
	PATCH_IF fx_header_count > 1 AND NOT (~%immunity_head_resref%~ STRING_EQUAL ~%immunity_member_resref%~) BEGIN
		FOR (level_h = 0; level_h < fx_header_count AND immunity_stable; ++level_h) BEGIN
			PATCH_IF $immunity_header_loaded(~%level_h%~) BEGIN
				SPRINT level_head_key ~%immunity_levels_serial% %level_h% %immunity_head_resref%~
				SPRINT level_member_key ~%immunity_levels_serial% %level_h% %immunity_member_resref%~
				SET level_head_found = VARIABLE_IS_SET $immunity_level_timing(~%level_head_key%~)
				SET level_member_found = VARIABLE_IS_SET $immunity_level_timing(~%level_member_key%~)
				PATCH_IF level_head_found AND level_member_found BEGIN
					SET level_head_timing = $immunity_level_timing(~%level_head_key%~)
					SET level_head_duration = $immunity_level_duration(~%level_head_key%~)
					SET level_member_timing = $immunity_level_timing(~%level_member_key%~)
					SET level_member_duration = $immunity_level_duration(~%level_member_key%~)
				END
				// Un en-tête sans aucune des deux n'a pas ce groupe : il ne l'empêche pas (PXW7BARR).
				PATCH_IF level_head_found != level_member_found
						OR (level_head_found AND level_head_timing != TIMING_while_equipped AND (level_head_timing != level_member_timing OR level_head_duration != level_member_duration)) BEGIN
					SET immunity_stable = 0
				END
			END
		END
	END
END
