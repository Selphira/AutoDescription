// Passe 3 : regroupements entre opcodes, après la prise en charge de tous les opcodes et avant
// leurs lignes. Un effet réuni à d'autres est marqué consommé (fx_consumed) : la macro
// ad_op_<N>_lines de son opcode le saute, et la ligne est celle d'un effet dérivé. Les règles
// s'appliquent dans l'ordre ci-dessous, indépendamment de l'ordre des opcodes. Une règle fixe
// l'opcode d'ancrage, les opcodes membres, l'effet dérivé, le nom de la ligne et la macro qui
// écrit la ligne (group_line), puis appelle ad_group_same_fields.
//
// Tableau écrit : fx_consumed (initialisé à 0 à la lecture, new-lib/effects.tpp).
//
// Une règle n'est appliquée que si l'objet a les opcodes sans lesquels elle ne réunit rien
// (fx_opcode_count) : chacune parcourt tous les effets, souvent plusieurs fois.

DEFINE_PATCH_MACRO ad_cross_groups BEGIN
	SET group_statistic_tra = 0
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		LPM ad_group_identical_effects
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_ABILITIES BEGIN
		LPM ad_group_abilities
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_SAVES_THROWS BEGIN
		LPM ad_group_saving_throws
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND VARIABLE_IS_SET $fx_opcode_count(~97~) AND VARIABLE_IS_SET $fx_opcode_count(~44~) BEGIN
		LPM ad_group_exceptional_strength
	END
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_THIEF_SKILLS BEGIN
		LPM ad_group_thief_skills
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~83~) AND VARIABLE_IS_SET $fx_opcode_count(~206~) BEGIN
			LPM ad_group_projectile_spells
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~102~) BEGIN
			LPM ad_group_spell_levels
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~205~) AND VARIABLE_IS_SET $fx_opcode_count(~206~) BEGIN
			LPM ad_group_secondary_type_spells
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~197~) AND VARIABLE_IS_SET $fx_opcode_count(~207~) BEGIN
			LPM ad_group_bounce_spells
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~23~) AND VARIABLE_IS_SET $fx_opcode_count(~101~) BEGIN
			LPM ad_group_morale
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~101~) BEGIN
			LPM ad_group_immunities
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~206~) BEGIN
			LPM ad_group_psionic_immunity
		END
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~20~) BEGIN
			LPM ad_group_improved_invisibility
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~58~) AND (VARIABLE_IS_SET $fx_opcode_count(~77~) OR VARIABLE_IS_SET $fx_opcode_count(~81~)) BEGIN
			LPM ad_group_dispel_cures
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~126~) AND VARIABLE_IS_SET $fx_opcode_count(~163~) BEGIN
			LPM ad_group_movement_restored
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~154~) BEGIN
			LPM ad_group_entangle
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~101~) BEGIN
			LPM ad_group_free_action
		END
		PATCH_FOR_EACH group_spell_opcode IN 60 145 BEGIN
			PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~%group_spell_opcode%~) BEGIN
				LPM ad_group_spell_types
			END
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~112~) AND VARIABLE_IS_SET $fx_opcode_count(~122~) BEGIN
			LPM ad_group_item_return
			LPM ad_group_replace_item
		END
	END
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		LPM ad_group_delayed_series
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~12~) BEGIN
			LPM ad_group_damage_halves
		END
		PATCH_IF VARIABLE_IS_SET $fx_opcode_count(~135~) BEGIN
			LPM ad_group_polymorph
		END
	END
	// L'ancien moteur tente toujours le regroupement de toutes les résistances avant ceux des
	// éléments et des dégâts physiques, qui n'ont aucun opcode commun.
	PATCH_IF AD_ENABLE_SHRINKAGE AND AD_SHRINK_RESISTANCES BEGIN
		LPM ad_group_all_resistances
		LPM ad_group_elemental_resistances
		LPM ad_group_physical_resistances
	END
END

// Effets identiques (ancien opcode_group_by_target, le premier regroupement de chaque opcode) : les
// effets d'un même opcode dont tous les champs sont égaux n'en font qu'un, écrit après les autres
// effets de son opcode (fx_late), comme celui que l'ancien moteur remet en fin de liste ;
// fx_identical_count en garde le nombre, fx_identical_anchor(id) l'effet qui les représente (initialisé
// à id à la lecture, new-lib/effects.tpp) ; l'ancien moteur ne compare pas le type de créature
// d'un effet d'un 177, qui réunit leurs noms (ad_application_versus, new-lib/application.tpp).
// identical_left(opcode) : effets de l'opcode qui suivent group_id (au plus : fx_opcode_count compte
// aussi les 177 remplacés) ; la recherche s'arrête quand il n'en reste plus, ou à la fin du bloc de
// group_id (les effets d'un bloc se suivent dans le magasin, et deux portées ne sont jamais réunies).
DEFINE_PATCH_MACRO ad_group_identical_effects BEGIN
	PHP_EACH fx_opcode_count AS identical_opcode => identical_total BEGIN
		SET $identical_left(~%identical_opcode%~) = identical_total
	END
	SET same_ignored = 0
	FOR (group_id = 0; group_id < fx_count; ++group_id) BEGIN
		SET $fx_identical_count(~%group_id%~) = 1
		SET group_opcode = $fx_opcode(~%group_id%~)
		SET group_left = $identical_left(~%group_opcode%~) - 1
		SET $identical_left(~%group_opcode%~) = group_left
		PATCH_IF NOT $fx_consumed(~%group_id%~) AND group_left > 0 BEGIN
			SET same_id = group_id
			SPRINT group_resource $fx_resource_lower(~%group_id%~)
			SET group_header = $fx_header(~%group_id%~)
			FOR (group_candidate = group_id + 1; group_left > 0 AND group_candidate < fx_count AND $fx_header(~%group_candidate%~) == group_header; ++group_candidate) BEGIN
				PATCH_IF $fx_opcode(~%group_candidate%~) == group_opcode BEGIN
					SET group_left -= 1
					PATCH_IF NOT $fx_consumed(~%group_candidate%~) BEGIN
						SET same_other = group_candidate
						LPM ad_fx_same_fields
						SPRINT group_other_resource $fx_resource_lower(~%group_candidate%~)
						PATCH_IF fx_same AND (~%group_other_resource%~ STRING_EQUAL ~%group_resource%~) BEGIN
							SET $fx_consumed(~%group_candidate%~) = 1
							SET $fx_identical_anchor(~%group_candidate%~) = group_id
							SET $fx_identical_count(~%group_id%~) = $fx_identical_count(~%group_id%~) + 1
							SET $fx_late(~%group_id%~) = 1
						END
					END
				END
			END
		END
	END
END

// Six caractéristiques modifiées de la même façon (ancien opcode_6_group, opcode virtuel 501).
DEFINE_PATCH_MACRO ad_group_abilities BEGIN
	SET group_anchor = 6
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 10 15 19 44 49 END
	SPRINT group_derived ~ABILITIES~
	SPRINT group_name @30030000 // ~Caractéristiques~
	SPRINT group_line ~ad_group_modifier_line~
	LPM ad_group_same_fields
END

// Cinq jets de sauvegarde modifiés de la même façon (ancien opcode_33_group, qui produit un effet
// de l'opcode 325 « tous les jets de sauvegarde »).
DEFINE_PATCH_MACRO ad_group_saving_throws BEGIN
	SET group_anchor = 33
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 34 35 36 37 END
	SPRINT group_derived ~ALL_SAVES~
	SPRINT group_name @5000000 // ~Jets de sauvegarde~
	SET group_statistic_tra = 5000002 // ~les jets de sauvegarde~
	SPRINT group_line ~ad_group_modifier_line~
	LPM ad_group_same_fields
	SET group_statistic_tra = 0
END

// Sept compétences de voleur modifiées de la même façon (ancien opcode_59_group, opcode virtuel
// 500).
DEFINE_PATCH_MACRO ad_group_thief_skills BEGIN
	SET group_anchor = 59
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 90 91 92 275 276 277 END
	SPRINT group_derived ~THIEF_SKILLS~
	SPRINT group_name @30090000 // ~Compétences de roublard~
	SPRINT group_line ~ad_group_modifier_line~
	LPM ad_group_same_fields
END

// Onze résistances modifiées de la même façon (ancien opcode_group_all_resistances, opcode
// virtuel 502).
DEFINE_PATCH_MACRO ad_group_all_resistances BEGIN
	SET group_anchor = 84
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 27 28 29 30 31 85 86 87 88 89 END
	SPRINT group_derived ~ALL_RESISTANCES~
	SET group_name_tra = 30050000 // ~Résistance aux dégâts~
	SPRINT group_line ~ad_group_resistance_line~
	LPM ad_group_same_fields
END

// Acide, froid, électricité, feu (ancien opcode_27_group, opcode virtuel 503).
DEFINE_PATCH_MACRO ad_group_elemental_resistances BEGIN
	SET group_anchor = 27
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 28 29 30 END
	SPRINT group_derived ~ELEMENTAL_RESISTANCES~
	SET group_name_tra = 30060000 // ~Résistance aux dégâts élémentaires~
	SPRINT group_line ~ad_group_resistance_line~
	LPM ad_group_same_fields
END

// Dégâts tranchants, contondants, perforants, de projectiles (ancien opcode_86_group, opcode
// virtuel 504).
DEFINE_PATCH_MACRO ad_group_physical_resistances BEGIN
	SET group_anchor = 86
	CLEAR_ARRAY group_members
	PATCH_DEFINE_ARRAY group_members BEGIN 87 88 89 END
	SPRINT group_derived ~PHYSICAL_RESISTANCES~
	SET group_name_tra = 30070000 // ~Résistance aux dégâts physiques~
	SPRINT group_line ~ad_group_resistance_line~
	LPM ad_group_same_fields
END

// Force exceptionnelle fixée et Force fixée (ancien opcode_97_group, opcode virtuel 522) :
// « Force : Passe à 18/50 » (effet dérivé EXCEPTIONAL_STRENGTH). Chaque effet 97 de valeur fixée,
// dans l'ordre du fichier, est réuni au premier effet 44 de valeur fixée non consommé qui a les
// mêmes champs sauf parameter1.
DEFINE_PATCH_MACRO ad_group_exceptional_strength BEGIN
	PHP_EACH fx_ids_97 AS _ => group_id BEGIN
		PATCH_IF $fx_parameter2(~%group_id%~) == MOD_TYPE_flat AND NOT $fx_consumed(~%group_id%~) BEGIN
			SET same_id = group_id
			SET same_ignored = AD_SAME_PARAMETER1
			SET group_other = 0 - 1
			FOR (group_candidate = 0; group_other < 0 AND group_candidate < fx_count; ++group_candidate) BEGIN
				PATCH_IF $fx_opcode(~%group_candidate%~) == 44 AND NOT $fx_consumed(~%group_candidate%~) BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					PATCH_IF fx_same BEGIN
						SET group_other = group_candidate
					END
				END
			END
			PATCH_IF group_other >= 0 BEGIN
				SET $fx_consumed(~%group_id%~) = 1
				SET $fx_consumed(~%group_other%~) = 1
				SET strength = $fx_parameter1(~%group_other%~)
				SET strength_bonus = $fx_parameter1(~%group_id%~)
				SPRINT bonus ~%strength_bonus%~
				// Seul 100 est écrit sur deux chiffres (« 18/00 ») : l'ancien moteur écrit « 18/5 ».
				PATCH_IF strength_bonus == 100 BEGIN
					SPRINT bonus ~00~
				END
				SPRINT value ~%strength%/%bonus%~
				SPRINT value @1200002 // ~Passe à %value%~
				SPRINT name @8000036 // ~Force~
				SPRINT line_section ~equipped~
				PATCH_IF support_header_only BEGIN
					SET derived_id = group_id
					SET derived_opcode = $AD_DERIVED_OLD_OPCODE(~EXCEPTIONAL_STRENGTH~)
					LPM ad_spell_header_derive
				END
				SET line_sort = $AD_DERIVED_SORT(~EXCEPTIONAL_STRENGTH~)
				SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
				SET line_fx = group_id
				LPM ad_effect_line
			END
		END
	END
END

// Immunités aux projectiles (ancien opcode_83_group) : une immunité au projectile P (83) absorbe
// les immunités à un sort (206) de son bloc dont le premier en-tête utilise P ; l'ancien moteur lit
// cet en-tête juste après celui du fichier (0x72), et la valeur du .spl vaut celle de projectl.ids
// plus 1.
DEFINE_PATCH_MACRO ad_group_projectile_spells BEGIN
	PHP_EACH fx_ids_83 AS _ => group_id BEGIN
		SPRINT group_scope $fx_scope(~%group_id%~)
		SET group_projectile = $fx_parameter2(~%group_id%~) + 1
		PHP_EACH fx_ids_206 AS _ => group_candidate BEGIN
			SPRINT group_other_scope $fx_scope(~%group_candidate%~)
			SPRINT group_spell $fx_resource(~%group_candidate%~)
			PATCH_IF NOT $fx_consumed(~%group_candidate%~) AND (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~) AND NOT (~%group_spell%~ STRING_EQUAL ~~) AND FILE_EXISTS_IN_GAME ~%group_spell%.spl~ BEGIN
				SET group_spell_projectile = 0 - 1
				INNER_PATCH_FILE ~%group_spell%.spl~ BEGIN
					PATCH_IF BUFFER_LENGTH >= 0x72 + SPL_HEAD_projectile + 2 BEGIN
						READ_SHORT (0x72 + SPL_HEAD_projectile) group_spell_projectile
					END
				END
				PATCH_IF group_spell_projectile == group_projectile BEGIN
					SET $fx_consumed(~%group_candidate%~) = 1
				END
			END
		END
	END
END

// Immunités par niveau de sort (ancien opcode_102_group, opcode virtuel 509) : les 102 d'une même
// portée, aux mêmes champs (ad_op_102_support), sont réunis dans le premier, qui reçoit le masque
// des niveaux (fx_spell_levels) ; il absorbe les immunités à un sort (206) de sa portée dont le
// niveau ne dépasse pas le plus haut réuni ; pour les neuf niveaux (ancien opcode_509_post_group),
// aussi les immunités à une école ou un type secondaire de sort (204, 205) de même cible, puissance,
// résistance, probabilités, dés et jet de sauvegarde.
DEFINE_PATCH_MACRO ad_group_spell_levels BEGIN
	PHP_EACH fx_ids_102 AS _ => group_id BEGIN
		PATCH_IF NOT $fx_consumed(~%group_id%~) BEGIN
			SPRINT group_scope $fx_scope(~%group_id%~)
			SET group_mask = 0
			SET group_top = 0
			PHP_EACH fx_ids_102 AS _ => group_candidate BEGIN
				SPRINT group_other_scope $fx_scope(~%group_candidate%~)
				PATCH_IF group_candidate >= group_id AND NOT $fx_consumed(~%group_candidate%~) AND (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~) BEGIN
					SET group_level = $fx_parameter1(~%group_candidate%~)
					SET group_mask = group_mask BOR (1 << (group_level - 1))
					SET group_top = group_level > group_top ? group_level : group_top
					SET $fx_consumed(~%group_candidate%~) = group_candidate != group_id
				END
			END
			SET $fx_spell_levels(~%group_id%~) = group_mask
			SET same_id = group_id
			SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2 BOR AD_SAME_TIMING BOR AD_SAME_SPECIAL
			FOR (group_candidate = 0; group_candidate < fx_count; ++group_candidate) BEGIN
				SET group_other_opcode = $fx_opcode(~%group_candidate%~)
				SPRINT group_other_scope $fx_scope(~%group_candidate%~)
				PATCH_IF NOT $fx_consumed(~%group_candidate%~) AND (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~) BEGIN
					PATCH_IF group_other_opcode == 206 BEGIN
						SPRINT group_spell $fx_resource(~%group_candidate%~)
						LPF ad_spell_level STR_VAR resref = ~%group_spell%~ RET group_spell_level = level END
						PATCH_IF group_spell_level >= 0 AND group_spell_level <= group_top BEGIN
							SET $fx_consumed(~%group_candidate%~) = 1
						END
					END
					ELSE PATCH_IF group_mask == 0x1FF AND (group_other_opcode == 204 OR group_other_opcode == 205) BEGIN
						SET same_other = group_candidate
						LPM ad_fx_same_fields
						PATCH_IF fx_same BEGIN
							SET $fx_consumed(~%group_candidate%~) = 1
						END
					END
				END
			END
		END
	END
END

// Immunités à un type secondaire de sort (ancien opcode_205_group) : une immunité au type T (205)
// absorbe les immunités à un sort (206) de son bloc dont le sort est de type T ; l'ancien moteur lit
// le type sur quatre octets.
DEFINE_PATCH_MACRO ad_group_secondary_type_spells BEGIN
	PHP_EACH fx_ids_205 AS _ => group_id BEGIN
		SET group_sectype = $fx_parameter2(~%group_id%~)
		PATCH_IF group_sectype > 0 BEGIN
			SPRINT group_scope $fx_scope(~%group_id%~)
			PHP_EACH fx_ids_206 AS _ => group_candidate BEGIN
				SPRINT group_other_scope $fx_scope(~%group_candidate%~)
				SPRINT group_spell $fx_resource(~%group_candidate%~)
				PATCH_IF NOT $fx_consumed(~%group_candidate%~) AND (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~) AND NOT (~%group_spell%~ STRING_EQUAL ~~) AND FILE_EXISTS_IN_GAME ~%group_spell%.spl~ BEGIN
					SET group_spell_sectype = 0 - 1
					INNER_PATCH_FILE ~%group_spell%.spl~ BEGIN
						PATCH_IF BUFFER_LENGTH >= SPL_sectype + 4 BEGIN
							READ_LONG SPL_sectype group_spell_sectype
						END
					END
					PATCH_IF group_spell_sectype == group_sectype BEGIN
						SET $fx_consumed(~%group_candidate%~) = 1
					END
				END
			END
		END
	END
END

// Renvois d'un projectile (ancien opcode_197_group) : un renvoi du projectile P (197) absorbe les
// renvois d'un sort (207) de son bloc dont l'un des en-têtes utilise P ; la valeur du .spl vaut
// celle de projectl.ids plus 1.
DEFINE_PATCH_MACRO ad_group_bounce_spells BEGIN
	PHP_EACH fx_ids_197 AS _ => group_id BEGIN
		SPRINT group_scope $fx_scope(~%group_id%~)
		SET group_projectile = $fx_parameter2(~%group_id%~) + 1
		PHP_EACH fx_ids_207 AS _ => group_candidate BEGIN
			SPRINT group_other_scope $fx_scope(~%group_candidate%~)
			SPRINT group_spell $fx_resource(~%group_candidate%~)
			PATCH_IF NOT $fx_consumed(~%group_candidate%~) AND (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~) AND NOT (~%group_spell%~ STRING_EQUAL ~~) AND FILE_EXISTS_IN_GAME ~%group_spell%.spl~ BEGIN
				SET group_spell_match = 0
				INNER_PATCH_FILE ~%group_spell%.spl~ BEGIN
					READ_LONG  SPL_extended_headers_offset group_headers_offset
					READ_SHORT SPL_extended_headers_count  group_headers_count
					FOR (group_header = 0; group_header < group_headers_count; ++group_header) BEGIN
						SET group_header_offset = group_headers_offset + 0x28 * group_header + SPL_HEAD_projectile
						PATCH_IF BUFFER_LENGTH >= group_header_offset + 2 BEGIN
							READ_SHORT group_header_offset group_spell_projectile
							SET group_spell_match = group_spell_match OR group_spell_projectile == group_projectile
						END
					END
				END
				PATCH_IF group_spell_match BEGIN
					SET $fx_consumed(~%group_candidate%~) = 1
				END
			END
		END
	END
END

// Moral (ancien opcode_23_group) : dans chaque bloc, le premier rétablissement du moral (23, moral
// fixé à 10) disparaît si le bloc immunise aussi contre la modification du moral et contre la
// panique (101 sur 23 et sur 106 ; la première de ces immunités fixe la durée des suivantes, une
// durée nulle les acceptant toutes). Sont aussi consommés l'immunité à la modification du moral,
// la dernière lue avant que les deux immunités ne soient trouvées, et les points de rupture de moral
// fixés à 1 (106) du bloc ; l'immunité à la panique reste. Les rétablissements suivants du bloc
// restent : l'ancien moteur n'en réunit qu'un.
DEFINE_PATCH_MACRO ad_group_morale BEGIN
	CLEAR_ARRAY morale_done
	PHP_EACH fx_ids_23 AS _ => group_id BEGIN
		SPRINT group_scope $fx_scope(~%group_id%~)
		PATCH_IF NOT $fx_consumed(~%group_id%~) AND $fx_parameter1(~%group_id%~) == 10 AND $fx_parameter2(~%group_id%~) == MOD_TYPE_flat AND NOT VARIABLE_IS_SET $morale_done(~%group_scope%~) BEGIN
			SET $morale_done(~%group_scope%~) = 1
			SET morale_found = 0
			SET morale_duration = 0
			SET morale_immunity = 0 - 1
			PHP_EACH fx_ids_101 AS _ => group_candidate BEGIN
				SPRINT group_other_scope $fx_scope(~%group_candidate%~)
				SET morale_protected = $fx_parameter2(~%group_candidate%~)
				PATCH_IF morale_found != 3 AND NOT $fx_consumed(~%group_candidate%~) AND (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~) AND (morale_protected == 23 OR morale_protected == 106) AND (morale_duration == 0 OR morale_duration == $fx_duration(~%group_candidate%~)) BEGIN
					SET morale_duration = $fx_duration(~%group_candidate%~)
					PATCH_IF morale_protected == 23 BEGIN
						SET morale_found = morale_found BOR 1
						SET morale_immunity = group_candidate
					END
					ELSE BEGIN
						SET morale_found = morale_found BOR 2
					END
				END
			END
			PATCH_IF morale_found == 3 BEGIN
				SET $fx_consumed(~%group_id%~) = 1
				SET $fx_consumed(~%morale_immunity%~) = 1
				PHP_EACH fx_ids_106 AS _ => group_candidate BEGIN
					SPRINT group_other_scope $fx_scope(~%group_candidate%~)
					PATCH_IF (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~) AND $fx_parameter1(~%group_candidate%~) == 1 AND $fx_parameter2(~%group_candidate%~) == MOD_TYPE_flat BEGIN
						SET $fx_consumed(~%group_candidate%~) = 1
					END
				END
			END
		END
	END
END

// Immunités (ancien opcode_101_group) : chaque immunité à l'opcode P (101), dans l'ordre du fichier,
// absorbe les effets qu'elle rend sans objet, s'ils ont la même cible, les mêmes probabilités et le
// même jet de sauvegarde :
// - ceux des lignes de 2da/immunity_absorbs.2da pour P (soins de l'état, autres immunités ; une
//   ligne CURE seulement avec AD_SHRINK_CURE_WITH_IMMUNITIES, une ligne EQUIPPED seulement dans un
//   bloc d'équipement, comme l'ancien delete_cure_linked_to_specific_immunity) ; une ligne RELABEL donne à
//   l'immunité ce libellé et la place après les autres, comme l'effet que l'ancien moteur ajoute ;
//   la colonne P2 est comparée à la valeur lue (fx_parameter2_raw), que l'ancien moteur teste avant
//   toute correction du mode ;
// - les protections contre un sort (206, 321) qui inflige P selon 2da/immunity_spells.2da, si elles
//   ont aussi les mêmes dés et la même puissance (321 : la même résistance).
DEFINE_PATCH_MACRO ad_group_immunities BEGIN
	PHP_EACH fx_ids_101 AS _ => immunity_id BEGIN
		SPRINT immunity_scope $fx_scope(~%immunity_id%~)
		// Dans un sort, l'ancien moteur applique aussi les règles des effets d'équipement (abilityType
		// négatif, ancien delete_cure_linked_to_specific_immunity).
		SET immunity_equipped = (~%immunity_scope%~ STRING_EQUAL ~equipped~) OR group_spell_as_equipped
		PATCH_IF NOT $fx_consumed(~%immunity_id%~) BEGIN
			SET immunity_opcode = $fx_parameter2(~%immunity_id%~)
			FOR (absorb_row = 0; absorb_row < AD_IMMUNITY_ABSORB_COUNT; ++absorb_row) BEGIN
				PATCH_IF $AD_IMMUNITY_ABSORB_IMMUNITY(~%absorb_row%~) == immunity_opcode
						AND (NOT $AD_IMMUNITY_ABSORB_CURE(~%absorb_row%~) OR AD_SHRINK_CURE_WITH_IMMUNITIES)
						AND (NOT $AD_IMMUNITY_ABSORB_EQUIPPED(~%absorb_row%~) OR immunity_equipped) BEGIN
					SET absorb_opcode = $AD_IMMUNITY_ABSORB_OPCODE(~%absorb_row%~)
					SET absorb_found = 0
					PHP_EACH ~fx_ids_%absorb_opcode%~ AS _ => absorb_id BEGIN
						PATCH_IF NOT $fx_consumed(~%absorb_id%~) AND absorb_id != immunity_id AND $fx_header(~%absorb_id%~) == $fx_header(~%immunity_id%~) BEGIN
							SET absorb_parameter1 = $fx_parameter1(~%absorb_id%~)
							LPM ad_immunity_same_fields
							PATCH_IF absorb_same AND absorb_parameter1 >= $AD_IMMUNITY_ABSORB_P1_MIN(~%absorb_row%~)
									AND absorb_parameter1 <= $AD_IMMUNITY_ABSORB_P1_MAX(~%absorb_row%~)
									AND ($AD_IMMUNITY_ABSORB_ANY_P2(~%absorb_row%~) OR $fx_parameter2_raw(~%absorb_id%~) == $AD_IMMUNITY_ABSORB_P2(~%absorb_row%~)) BEGIN
								SET $fx_consumed(~%absorb_id%~) = 1
								SET absorb_found = 1
							END
						END
					END
					PATCH_IF absorb_found AND $AD_IMMUNITY_ABSORB_RELABEL(~%absorb_row%~) >= 0 BEGIN
						SET $fx_immunity_label(~%immunity_id%~) = $AD_IMMUNITY_ABSORB_RELABEL(~%absorb_row%~)
						SET $fx_immunity_late(~%immunity_id%~) = 1
					END
				END
			END
			// Un autre en-tête est une autre portée (ad_immunity_same_fields), testé d'abord.
			PATCH_FOR_EACH absorb_opcode IN 206 321 BEGIN PHP_EACH ~fx_ids_%absorb_opcode%~ AS _ => absorb_id BEGIN
				PATCH_IF NOT $fx_consumed(~%absorb_id%~) AND $fx_header(~%absorb_id%~) == $fx_header(~%immunity_id%~) BEGIN
					SPRINT absorb_resref $fx_resource(~%absorb_id%~)
					TO_UPPER absorb_resref
					LPM ad_immunity_same_fields
					PATCH_IF absorb_same AND VARIABLE_IS_SET $AD_IMMUNITY_SPELLS(~%immunity_opcode% %absorb_resref%~)
							AND $fx_dice_count(~%absorb_id%~) == $fx_dice_count(~%immunity_id%~)
							AND $fx_dice_sides(~%absorb_id%~) == $fx_dice_sides(~%immunity_id%~)
							AND $fx_power(~%absorb_id%~) == $fx_power(~%immunity_id%~)
							AND (absorb_opcode == 206 OR $fx_resistance(~%absorb_id%~) == $fx_resistance(~%immunity_id%~)) BEGIN
						SET $fx_consumed(~%absorb_id%~) = 1
					END
				END
			END END
		END
	END
END

// Capacités psioniques (ancien opcode_206_group, après les absorptions des immunités) : à partir de
// cinq protections contre une capacité psionique (206 d'un sort de type 505 de
// 2da/immunity_spells.2da) non consommées dans un bloc, la cinquième, dans l'ordre du fichier, devient
// l'immunité « aux capacités psioniques » (101 de parameter2 505, placée après les autres comme
// l'effet que l'ancien moteur ajoute) et toutes les protections psioniques du bloc sont consommées,
// quels que soient leurs champs.
DEFINE_PATCH_MACRO ad_group_psionic_immunity BEGIN
	CLEAR_ARRAY psionic_scope_done
	FOR (psionic_id = 0; psionic_id < fx_count; ++psionic_id) BEGIN
		SPRINT psionic_scope $fx_scope(~%psionic_id%~)
		LPM ad_psionic_protection
		PATCH_IF psionic_protection AND NOT VARIABLE_IS_SET $psionic_scope_done(~%psionic_scope%~) BEGIN
			SET $psionic_scope_done(~%psionic_scope%~) = 1
			SET psionic_found = 0
			SET psionic_fifth = 0 - 1
			SET psionic_self = psionic_id
			FOR (psionic_id = psionic_self; psionic_id < fx_count; ++psionic_id) BEGIN
				SPRINT psionic_other_scope $fx_scope(~%psionic_id%~)
				LPM ad_psionic_protection
				PATCH_IF psionic_protection AND (~%psionic_other_scope%~ STRING_EQUAL ~%psionic_scope%~) BEGIN
					SET psionic_found += 1
					PATCH_IF psionic_found == 5 BEGIN
						SET psionic_fifth = psionic_id
					END
				END
			END
			PATCH_IF psionic_fifth >= 0 BEGIN
				FOR (psionic_id = psionic_self; psionic_id < fx_count; ++psionic_id) BEGIN
					SPRINT psionic_other_scope $fx_scope(~%psionic_id%~)
					LPM ad_psionic_protection
					PATCH_IF psionic_protection AND (~%psionic_other_scope%~ STRING_EQUAL ~%psionic_scope%~) BEGIN
						SET $fx_consumed(~%psionic_id%~) = 1
					END
				END
				SET $fx_opcode(~%psionic_fifth%~) = 101
				SET $fx_parameter2(~%psionic_fifth%~) = 505
				SET $fx_parameter2_raw(~%psionic_fifth%~) = 505
				SET $fx_immunity_label(~%psionic_fifth%~) = 505
				SET $fx_immunity_late(~%psionic_fifth%~) = 1
				SET $fx_consumed(~%psionic_fifth%~) = 0
				SET $fx_opcode_count(~101~) = VARIABLE_IS_SET $fx_opcode_count(~101~) ? $fx_opcode_count(~101~) + 1 : 1
				PATCH_FOR_EACH index_opcode IN 101 206 BEGIN
					LPM ad_fx_index_opcode
				END
			END
			SET psionic_id = psionic_self
		END
	END
END

// L'effet psionic_id est-il une protection non consommée contre une capacité psionique ?
DEFINE_PATCH_MACRO ad_psionic_protection BEGIN
	SET psionic_protection = 0
	PATCH_IF $fx_opcode(~%psionic_id%~) == 206 AND NOT $fx_consumed(~%psionic_id%~) BEGIN
		SPRINT psionic_resref $fx_resource(~%psionic_id%~)
		TO_UPPER psionic_resref
		SET psionic_protection = VARIABLE_IS_SET $AD_IMMUNITY_SPELLS(~505 %psionic_resref%~)
	END
END

// Invisibilité améliorée (ancien opcode_20_group) : un effet 20 de parameter2 1 remplace les autres
// effets 20 qui ont les mêmes champs, parameter2 mis à part.
DEFINE_PATCH_MACRO ad_group_improved_invisibility BEGIN
	PHP_EACH fx_ids_20 AS _ => group_id BEGIN
		PATCH_IF $fx_parameter2(~%group_id%~) == 1 AND NOT $fx_consumed(~%group_id%~) BEGIN
			SET same_id = group_id
			SET same_ignored = AD_SAME_PARAMETER2
			SPRINT group_resource $fx_resource_lower(~%group_id%~)
			PHP_EACH fx_ids_20 AS _ => group_candidate BEGIN
				PATCH_IF group_candidate != group_id AND NOT $fx_consumed(~%group_candidate%~) BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					SPRINT group_other_resource $fx_resource_lower(~%group_candidate%~)
					PATCH_IF fx_same AND (~%group_other_resource%~ STRING_EQUAL ~%group_resource%~) BEGIN
						SET $fx_consumed(~%group_candidate%~) = 1
					END
				END
			END
		END
	END
END

// Dissipation de la magie (ancien opcode_58_group) : elle dissipe aussi la surdité et la débilité
// mentale ; les guérisons de ces états (opcodes 77, 81) de même portée, avec les mêmes dés, puissance,
// probabilités, résistance, cible et jet de sauvegarde (paramètres, timing, durée et special mis à
// part), sont consommées.
DEFINE_PATCH_MACRO ad_group_dispel_cures BEGIN
	PHP_EACH fx_ids_58 AS _ => group_id BEGIN
		PATCH_IF NOT $fx_consumed(~%group_id%~) BEGIN
			SET same_id = group_id
			SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2 BOR AD_SAME_TIMING BOR AD_SAME_SPECIAL
			FOR (group_candidate = 0; group_candidate < fx_count; ++group_candidate) BEGIN
				SET group_candidate_opcode = $fx_opcode(~%group_candidate%~)
				PATCH_IF (group_candidate_opcode == 77 OR group_candidate_opcode == 81) AND NOT $fx_consumed(~%group_candidate%~) BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					PATCH_IF fx_same BEGIN
						SET $fx_consumed(~%group_candidate%~) = 1
					END
				END
			END
		END
	END
END

// Vitesse de déplacement rétablie (ancien opcode_126_group : opcode 126 à 100 %) : elle absorbe
// l'action libre (opcode 163) de même portée et de mêmes probabilités.
DEFINE_PATCH_MACRO ad_group_movement_restored BEGIN
	PHP_EACH fx_ids_126 AS _ => group_id BEGIN
		PATCH_IF $fx_parameter2(~%group_id%~) == MOD_TYPE_percentage AND $fx_parameter1(~%group_id%~) == 100 AND NOT $fx_consumed(~%group_id%~) BEGIN
			SPRINT group_scope $fx_scope(~%group_id%~)
			PHP_EACH fx_ids_163 AS _ => group_candidate BEGIN
				SPRINT group_other_scope $fx_scope(~%group_candidate%~)
				PATCH_IF NOT $fx_consumed(~%group_candidate%~) AND (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~) AND $fx_probability1(~%group_candidate%~) == $fx_probability1(~%group_id%~) AND $fx_probability2(~%group_candidate%~) == $fx_probability2(~%group_id%~) BEGIN
					SET $fx_consumed(~%group_candidate%~) = 1
				END
			END
		END
	END
END

// Enchevêtrement (ancien opcode_154_group) : un enchevêtrement (154) absorbe les immobilisations de
// son bloc (126 de parameter1 0, parameter2 lu 1, 2 ou 5) qui ont les mêmes cible, timing, durée,
// probabilités, dés, puissance, jet de sauvegarde et résistance à la dissipation ; sans elles, il
// n'est pas écrit.
DEFINE_PATCH_MACRO ad_group_entangle BEGIN
	PHP_EACH fx_ids_154 AS _ => group_id BEGIN
		PATCH_IF NOT $fx_consumed(~%group_id%~) BEGIN
			SET same_id = group_id
			SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2 BOR AD_SAME_SPECIAL
			SET group_absorbed = 0
			PHP_EACH fx_ids_126 AS _ => group_candidate BEGIN
				SET group_movement_mode = $fx_parameter2_raw(~%group_candidate%~)
				PATCH_IF NOT $fx_consumed(~%group_candidate%~) AND $fx_parameter1(~%group_candidate%~) == 0 AND (group_movement_mode == 1 OR group_movement_mode == 2 OR group_movement_mode == 5) BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					PATCH_IF fx_same BEGIN
						SET $fx_consumed(~%group_candidate%~) = 1
						SET group_absorbed = 1
					END
				END
			END
			PATCH_IF NOT group_absorbed BEGIN
				SET $fx_consumed(~%group_id%~) = 1
			END
		END
	END
END

// Action libre (ancien opcode_101_group, opcode virtuel 520 ; capacités d'équipement) : une immunité
// à la modification de la vitesse de déplacement (101 sur 126), avec l'action libre (163) ou la
// vitesse rétablie (126 à 100 %) et les immunités à la hâte, à la lenteur, à la paralysie, à
// l'enchevêtrement, à la toile d'araignée et à l'immobilisation (101 sur 16, 40, 109, 154, 157, 175)
// de mêmes probabilités, cible et jet de sauvegarde, s'écrivent « Action libre » (effet dérivé
// FREE_ACTION). Ces effets, l'action libre, la vitesse et les soins de l'étourdissement et de la
// paralysie (46, 162) sont consommés. L'ancien moteur vérifie la présence de ces effets même si un
// autre regroupement les a déjà absorbés.
DEFINE_PATCH_MACRO ad_group_free_action BEGIN
	PHP_EACH fx_ids_101 AS _ => group_id BEGIN
		PATCH_IF $fx_parameter2(~%group_id%~) == 126 AND NOT $fx_consumed(~%group_id%~) BEGIN
			SPRINT group_scope $fx_scope(~%group_id%~)
			PATCH_IF ~%group_scope%~ STRING_EQUAL ~equipped~ BEGIN
				SET same_id = group_id
				SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2 BOR AD_SAME_TIMING BOR AD_SAME_SPECIAL
					BOR AD_SAME_POWER BOR AD_SAME_DICE BOR AD_SAME_RESISTANCE
				CLEAR_ARRAY group_needed
				SET group_restore = 0
				FOR (group_candidate = 0; group_candidate < fx_count; ++group_candidate) BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					PATCH_IF fx_same BEGIN
						SET group_candidate_opcode = $fx_opcode(~%group_candidate%~)
						PATCH_IF group_candidate_opcode == 163 OR (group_candidate_opcode == 126 AND $fx_parameter1(~%group_candidate%~) == 100
								AND $fx_parameter2(~%group_candidate%~) == MOD_TYPE_percentage) BEGIN
							SET group_restore = 1
						END
						ELSE PATCH_IF group_candidate_opcode == 101 BEGIN
							SET group_needed_immunity = $fx_parameter2(~%group_candidate%~)
							SET $group_needed(~%group_needed_immunity%~) = 1
						END
					END
				END
				SET group_complete = group_restore
				PATCH_FOR_EACH group_immunity IN 16 40 109 154 157 175 BEGIN
					PATCH_IF NOT VARIABLE_IS_SET $group_needed(~%group_immunity%~) BEGIN
						SET group_complete = 0
					END
				END
				PATCH_IF group_complete BEGIN
					FOR (group_candidate = 0; group_candidate < fx_count; ++group_candidate) BEGIN
						SET same_other = group_candidate
						LPM ad_fx_same_fields
						SET group_candidate_opcode = $fx_opcode(~%group_candidate%~)
						SET group_candidate_parameter2 = $fx_parameter2(~%group_candidate%~)
						PATCH_IF fx_same AND (group_candidate_opcode == 46
								OR group_candidate_opcode == 126 OR group_candidate_opcode == 162 OR group_candidate_opcode == 163
								OR (group_candidate_opcode == 101 AND (group_candidate_parameter2 == 16 OR group_candidate_parameter2 == 40
									OR group_candidate_parameter2 == 109 OR group_candidate_parameter2 == 126 OR group_candidate_parameter2 == 154
									OR group_candidate_parameter2 == 157 OR group_candidate_parameter2 == 175))) BEGIN
							SET $fx_consumed(~%group_candidate%~) = 1
						END
					END
					SPRINT line_section ~equipped~
					PATCH_IF support_header_only BEGIN
						SET derived_id = group_id
						SET derived_opcode = $AD_DERIVED_OLD_OPCODE(~FREE_ACTION~)
						LPM ad_spell_header_derive
					END
					SET line_sort = $AD_DERIVED_SORT(~FREE_ACTION~)
					SET line_phrase = 30110100 // ~Action libre~
					SET line_fx = group_id
					LPM ad_effect_line
				END
			END
		END
	END
END

// Objet rendu (ancien opcode_112_group, second cas) : un retrait d'objet (112) sans délai ni durée
// limitée suivi de la création du même objet après un délai (122, timing 4) dans le même bloc
// devient un retrait pour la durée de ce délai ; la création est consommée. L'ancien moteur ne
// prévoit qu'une création par retrait : plusieurs sont refusées.
DEFINE_PATCH_MACRO ad_group_item_return BEGIN
	PHP_EACH fx_ids_112 AS _ => group_id BEGIN
		SET group_timing = $fx_timing(~%group_id%~)
		PATCH_IF NOT $fx_consumed(~%group_id%~) AND (group_timing <= TIMING_while_equipped OR group_timing >= TIMING_permanent_after_death) BEGIN
			SPRINT group_scope $fx_scope(~%group_id%~)
			SPRINT group_resource $fx_resource_lower(~%group_id%~)
			SET group_returns = 0
			FOR (group_candidate = 0; group_candidate < fx_count; ++group_candidate) BEGIN
				SPRINT group_other_scope $fx_scope(~%group_candidate%~)
				SPRINT group_other_resource $fx_resource_lower(~%group_candidate%~)
				PATCH_IF $fx_opcode(~%group_candidate%~) == 122 AND NOT $fx_consumed(~%group_candidate%~)
						AND $fx_timing(~%group_candidate%~) == TIMING_delayed AND (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~)
						AND (~%group_other_resource%~ STRING_EQUAL ~%group_resource%~) BEGIN
					SET group_returns += 1
					SET $fx_consumed(~%group_candidate%~) = 1
					SET $fx_item_return(~%group_id%~) = $fx_duration(~%group_candidate%~)
				END
			END
			PATCH_IF group_returns > 1 BEGIN
				LPF ad_refusal INT_VAR fx_id = group_candidate STR_VAR reason = ~not_implemented:opcode112:several_returns~ message = ~several items returned by opcode 112 in one block~ RET render_late_missing = refusal END
			END
		END
	END
END

// Objet remplacé (ancien opcode_122_group, opcode virtuel 525) : chaque création d'objet (122) est
// réunie au premier retrait d'objet (112) du même bloc qui a les mêmes cible, timing, durée,
// probabilités, jet de sauvegarde, résistance à la dissipation et special : « Remplace « Lance +3 »
// par « Sceptre de puissance altière » » (effet dérivé REPLACE_ITEM).
DEFINE_PATCH_MACRO ad_group_replace_item BEGIN
	PHP_EACH fx_ids_122 AS _ => group_id BEGIN
		PATCH_IF NOT $fx_consumed(~%group_id%~) BEGIN
			SET same_id = group_id
			SET same_ignored = AD_SAME_PARAMETER1 BOR AD_SAME_PARAMETER2 BOR AD_SAME_POWER BOR AD_SAME_DICE
			SET group_removal = 0 - 1
			PHP_EACH fx_ids_112 AS _ => group_candidate BEGIN
				PATCH_IF group_removal < 0 AND NOT $fx_consumed(~%group_candidate%~) BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					PATCH_IF fx_same BEGIN
						SET group_removal = group_candidate
					END
				END
			END
			PATCH_IF group_removal >= 0 BEGIN
				SET $fx_consumed(~%group_id%~) = 1
				SET $fx_consumed(~%group_removal%~) = 1
				SPRINT itemName $fx_item_name(~%group_removal%~)
				SPRINT itemName2 $fx_item_name(~%group_id%~)
				SPRINT line_section ~equipped~
				PATCH_IF support_header_only BEGIN
					SET derived_id = group_id
					SET derived_opcode = $AD_DERIVED_OLD_OPCODE(~REPLACE_ITEM~)
					LPM ad_spell_header_derive
				END
				SET line_sort = $AD_DERIVED_SORT(~REPLACE_ITEM~)
				SET line_phrase = 30120100 // ~Remplace « %itemName% » par « %itemName2% » dans l'inventaire %ofTheTarget%~
				SET line_fx = group_id
				LPM ad_effect_line
			END
		END
	END
END

// Types de sort (anciens opcode_60_group et opcode_145_group, échec des sorts et lancement de sorts
// empêché) : chaque effet de l'opcode group_spell_opcode réunit les autres effets de cet opcode de
// types de sort 0 à 2 qui ont les mêmes champs, parameter2 mis à part ; l'effet réuni
// (fx_spell_types : masque des types) est écrit après les autres, comme celui que l'ancien moteur
// ajoute en fin de liste.
DEFINE_PATCH_MACRO ad_group_spell_types BEGIN
	PHP_EACH ~fx_ids_%group_spell_opcode%~ AS _ => group_id BEGIN
		PATCH_IF NOT $fx_consumed(~%group_id%~) BEGIN
			SET group_type = $fx_parameter2(~%group_id%~)
			SET group_types = 1 << (group_type > 2 ? group_type - 3 : group_type)
			SET group_merged = 0
			SET same_id = group_id
			SET same_ignored = AD_SAME_PARAMETER2
			SPRINT group_resource $fx_resource_lower(~%group_id%~)
			PHP_EACH ~fx_ids_%group_spell_opcode%~ AS _ => group_candidate BEGIN
				SET group_other_type = $fx_parameter2(~%group_candidate%~)
				PATCH_IF group_candidate != group_id AND NOT $fx_consumed(~%group_candidate%~) AND group_other_type >= 0 AND group_other_type <= 2 BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					PATCH_IF fx_same BEGIN
						SET $fx_consumed(~%group_candidate%~) = 1
						SET group_types = group_types BOR (1 << group_other_type)
						SET group_merged = 1
					END
				END
			END
			PATCH_IF group_merged BEGIN
				SET $fx_spell_types(~%group_id%~) = group_types
				SET $fx_late(~%group_id%~) = 1
			END
		END
	END
END

// Répétitions d'un effet (ancien opcode_group_by_duration), trouvées par la prise en charge
// (ad_application_series_support, new-lib/application.tpp) : les effets différés de la série sont
// consommés, la ligne est celle de l'effet de tête, écrite après les autres effets de son opcode
// (fx_late) comme celui que l'ancien moteur ajoute en fin de liste.
DEFINE_PATCH_MACRO ad_group_delayed_series BEGIN
	FOR (group_id = 0; group_id < fx_count; ++group_id) BEGIN
		PATCH_IF $fx_series_of(~%group_id%~) >= 0 BEGIN
			SET $fx_consumed(~%group_id%~) = 1
		END
		PATCH_IF $fx_series_anchor(~%group_id%~) BEGIN
			SET $fx_late(~%group_id%~) = 1
		END
	END
END

// Métamorphose (ancien opcode_135_post_group) : dans la portée d'une métamorphose (135), le retour à
// la forme naturelle est retiré : capacité ajoutée (171) dont le sort joue l'animation POLYBACK
// (215) ; sort lancé avec un délai (146) dont le sort retire SPWI491, « Métamorphose forme
// naturelle », si la métamorphose dure autant ; une métamorphose permanente prend alors la durée de
// ce délai et est écrite après les autres, comme celle que l'ancien moteur ajoute. L'ancien moteur
// reconnaît ces sorts à ces ressources.
DEFINE_PATCH_MACRO ad_group_polymorph BEGIN
	PHP_EACH fx_ids_135 AS _ => group_id BEGIN
		PATCH_IF NOT $fx_consumed(~%group_id%~) BEGIN
			SPRINT group_scope $fx_scope(~%group_id%~)
			FOR (group_candidate = 0; group_candidate < fx_count; ++group_candidate) BEGIN
				SET group_other_opcode = $fx_opcode(~%group_candidate%~)
				SPRINT group_other_scope $fx_scope(~%group_candidate%~)
				SPRINT group_spell $fx_resource(~%group_candidate%~)
				PATCH_IF NOT $fx_consumed(~%group_candidate%~) AND (~%group_other_scope%~ STRING_EQUAL ~%group_scope%~) BEGIN
					PATCH_IF group_other_opcode == 171 BEGIN
						LPF ad_spell_has_effect INT_VAR opcode = 215 STR_VAR resref = ~%group_spell%~ resource = ~POLYBACK~ RET group_found = found END
						SET $fx_consumed(~%group_candidate%~) = group_found
					END
					ELSE PATCH_IF group_other_opcode == 146 AND $fx_timing(~%group_candidate%~) == TIMING_delayed BEGIN
						LPF ad_spell_has_effect STR_VAR resref = ~%group_spell%~ resource = ~SPWI491~ RET group_found = found END
						PATCH_IF group_found AND $fx_timing(~%group_id%~) == TIMING_duration
								AND $fx_duration(~%group_id%~) == $fx_duration(~%group_candidate%~) BEGIN
							SET $fx_consumed(~%group_candidate%~) = 1
						END
						ELSE PATCH_IF group_found AND $fx_timing(~%group_id%~) == TIMING_permanent BEGIN
							SET $fx_consumed(~%group_candidate%~) = 1
							SET $fx_timing(~%group_id%~) = TIMING_duration
							SET $fx_duration(~%group_id%~) = $fx_duration(~%group_candidate%~)
							SET $fx_late(~%group_id%~) = 1
						END
					END
				END
			END
		END
	END
END

// Moitié des dégâts au jet de sauvegarde (ancien opcode_12_group) : chaque effet 12 sans jet de
// sauvegarde, dans l'ordre du fichier, est réuni au premier autre effet 12 non consommé qui a les mêmes
// champs, hors jet de sauvegarde et résistance à la dissipation : la ligne additionne leurs dés et
// prend le jet de l'autre, réussi pour moitié des dégâts (bit 8 de special, lu sur EE). L'effet
// réuni est écrit après les autres effets 12 (fx_late), comme celui que l'ancien moteur ajoute.
DEFINE_PATCH_MACRO ad_group_damage_halves BEGIN
	PHP_EACH fx_ids_12 AS _ => group_id BEGIN
		PATCH_IF NOT $fx_consumed(~%group_id%~) AND $fx_save_type(~%group_id%~) == 0 BEGIN
			SET same_id = group_id
			SET same_ignored = AD_SAME_SAVE
			SET group_other = 0 - 1
			FOR (group_candidate = 0; group_other < 0 AND group_candidate < fx_count; ++group_candidate) BEGIN
				PATCH_IF group_candidate != group_id AND $fx_opcode(~%group_candidate%~) == 12 AND NOT $fx_consumed(~%group_candidate%~) BEGIN
					SET same_other = group_candidate
					LPM ad_fx_same_fields
					SPRINT group_resource $fx_resource_lower(~%group_id%~)
					SPRINT group_other_resource $fx_resource_lower(~%group_candidate%~)
					PATCH_IF fx_same AND (~%group_other_resource%~ STRING_EQUAL ~%group_resource%~) BEGIN
						SET group_other = group_candidate
					END
				END
			END
			PATCH_IF group_other >= 0 BEGIN
				SET $fx_consumed(~%group_other%~) = 1
				SET $fx_dice_count(~%group_id%~) = $fx_dice_count(~%group_id%~) + $fx_dice_count(~%group_other%~)
				SET $fx_special(~%group_id%~) = $fx_special(~%group_id%~) BOR BIT8
				SET $fx_save_type(~%group_id%~) = $fx_save_type(~%group_other%~)
				SET $fx_save_types(~%group_id%~) = $fx_save_types(~%group_other%~)
				SET $fx_save_flags(~%group_id%~) = $fx_save_flags(~%group_other%~)
				SET $fx_late(~%group_id%~) = 1
			END
		END
	END
END

// absorb_same : l'effet absorb_id a la même portée, la même cible, les mêmes probabilités et le même
// jet de sauvegarde que l'immunité immunity_id.
DEFINE_PATCH_MACRO ad_immunity_same_fields BEGIN
	SPRINT absorb_scope $fx_scope(~%absorb_id%~)
	SPRINT immunity_scope $fx_scope(~%immunity_id%~)
	SET absorb_same = (~%absorb_scope%~ STRING_EQUAL ~%immunity_scope%~)
		AND $fx_group_target(~%absorb_id%~) == $fx_group_target(~%immunity_id%~)
		AND $fx_probability1(~%absorb_id%~) == $fx_probability1(~%immunity_id%~)
		AND $fx_probability2(~%absorb_id%~) == $fx_probability2(~%immunity_id%~)
		AND $fx_save_type(~%absorb_id%~) == $fx_save_type(~%immunity_id%~)
		AND $fx_save_bonus(~%absorb_id%~) == $fx_save_bonus(~%immunity_id%~)
END

// Règle générique (ancien group_opcode_with_same_parameters) : chaque effet de l'opcode
// group_anchor, dans l'ordre du fichier, est réuni au premier effet non consommé de chacun des
// opcodes group_members qui a les mêmes champs (ad_fx_same_fields) ; s'ils sont tous trouvés, ils
// sont consommés et la macro group_line écrit la ligne de l'effet dérivé group_derived, d'après
// l'effet d'ancrage group_id.
DEFINE_PATCH_MACRO ad_group_same_fields BEGIN
	SET group_possible = VARIABLE_IS_SET $fx_opcode_count(~%group_anchor%~)
	PHP_EACH group_members AS _ => group_opcode BEGIN
		SET group_possible = group_possible AND VARIABLE_IS_SET $fx_opcode_count(~%group_opcode%~)
	END
	FOR (group_id = 0; group_possible AND group_id < fx_count; ++group_id) BEGIN
		PATCH_IF $fx_opcode(~%group_id%~) == group_anchor AND NOT $fx_consumed(~%group_id%~) BEGIN
			SET same_id = group_id
			SET same_ignored = 0
			SET group_found = 1
			PHP_EACH group_members AS _ => group_opcode BEGIN
				SET $group_member(~%group_opcode%~) = 0 - 1
				FOR (group_other = 0; group_found AND group_other < fx_count AND $group_member(~%group_opcode%~) < 0; ++group_other) BEGIN
					PATCH_IF $fx_opcode(~%group_other%~) == group_opcode AND NOT $fx_consumed(~%group_other%~) BEGIN
						SET same_other = group_other
						LPM ad_fx_same_fields
						PATCH_IF fx_same BEGIN
							SET $group_member(~%group_opcode%~) = group_other
						END
					END
				END
				SET group_found = group_found AND $group_member(~%group_opcode%~) >= 0
			END
			PATCH_IF group_found BEGIN
				SET $fx_consumed(~%group_id%~) = 1
				PHP_EACH group_members AS _ => group_opcode BEGIN
					SET group_other = $group_member(~%group_opcode%~)
					SET $fx_consumed(~%group_other%~) = 1
				END
				SPRINT line_section ~equipped~
				SET line_sort = $AD_DERIVED_SORT(~%group_derived%~)
				SET group_value = $fx_parameter1(~%group_id%~)
				SET group_mode = $fx_parameter2(~%group_id%~)
				PATCH_IF support_header_only BEGIN
					SET derived_id = group_id
					SET derived_opcode = $AD_DERIVED_OLD_OPCODE(~%group_derived%~)
					LPM ad_spell_header_derive
				END
				LPM ~%group_line%~
				SET line_fx = group_id
				LPM ad_effect_line
			END
		END
	END
END

// « group_name : +1 » (modificateurs simples, new-lib/opcodes/stat_modifiers.tpp), en pourcentage
// si l'opcode d'ancrage l'est. Sur une autre cible que soi, avec un libellé de la statistique
// (group_statistic_tra), la phrase à la forme « cible » des modificateurs (ancien opcode_target) :
// « Augmente de 2 les jets de sauvegarde du porteur » ; le mode 3 des jeux EE y est un ajout.
DEFINE_PATCH_MACRO ad_group_modifier_line BEGIN
	SET group_percent = VARIABLE_IS_SET $AD_STAT_MODIFIER_PERCENT(~%group_anchor%~)
	LPF ad_stat_modifier_value INT_VAR value = group_value mode = group_mode percent = group_percent RET value = text END
	SPRINT name ~%group_name%~
	SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
	SET group_target = $fx_effective_target(~%group_id%~)
	PATCH_IF group_statistic_tra > 0 AND group_target != TARGET_FX_self AND group_target != TARGET_FX_original_caster BEGIN
		LPF ad_tra INT_VAR tra_id = group_statistic_tra RET theStatistic = text END
		SET value = ABS group_value
		SET line_phrase = group_mode == MOD_TYPE_flat ? 1210130 : (group_mode == MOD_TYPE_percentage ? 1210140
			: (group_value >= 0 ? 1210110 : 1210120)) // ~Augmente de %value% %theStatistic% %ofTheTarget%~ (+1)
	END
END

// Ligne de résistance (new-lib/opcodes/resistances.tpp), nom au libellé group_name_tra.
DEFINE_PATCH_MACRO ad_group_resistance_line BEGIN
	LPF ad_resistance_text INT_VAR value = group_value mode = group_mode name_tra = group_name_tra RET line_text = text END
END

// fx_same : les effets same_id et same_other ont les champs qui doivent être égaux pour être réunis,
// comme dans l'ancien moteur : la portée (il regroupe chaque bloc séparément), la cible de
// regroupement (fx_group_target, new-lib/normalize.tpp), l'origine de l'effet (fx_external : effet
// d'un EFF, opcode 177), et ceux que same_ignored (bits AD_SAME_*, new-lib/startup.tpa) ne laisse
// pas de côté : AD_SAME_PARAMETER1, AD_SAME_PARAMETER2, AD_SAME_SAVE (jet de sauvegarde et
// résistance à la dissipation), AD_SAME_TIMING (timing et durée), AD_SAME_SPECIAL, AD_SAME_POWER,
// AD_SAME_DICE, AD_SAME_RESISTANCE, AD_SAME_PROBABILITY. L'ancien moteur compare parameter2 tel que
// lu, avant que la prise en charge d'un opcode n'y range un mode (191, 233 : la statistique visée
// y disparaît). Macro, appelée pour des paires d'effets : un LPF y coûterait la copie de toutes les
// variables, magasin d'effets compris ; AND n'évalue pas son second terme si le premier est faux.
DEFINE_PATCH_MACRO ad_fx_same_fields BEGIN
	SET fx_same = $fx_group_target(~%same_id%~) == $fx_group_target(~%same_other%~)
		AND $fx_external(~%same_id%~) == $fx_external(~%same_other%~)
		AND ((same_ignored BAND AD_SAME_PARAMETER1) != 0 OR $fx_parameter1(~%same_id%~) == $fx_parameter1(~%same_other%~))
		AND ((same_ignored BAND AD_SAME_PARAMETER2) != 0 OR $fx_parameter2_raw(~%same_id%~) == $fx_parameter2_raw(~%same_other%~))
		AND ((same_ignored BAND AD_SAME_TIMING) != 0 OR ($fx_timing(~%same_id%~) == $fx_timing(~%same_other%~)
			AND $fx_duration(~%same_id%~) == $fx_duration(~%same_other%~)))
		AND ((same_ignored BAND AD_SAME_POWER) != 0 OR $fx_power(~%same_id%~) == $fx_power(~%same_other%~))
		AND ((same_ignored BAND (AD_SAME_SAVE BOR AD_SAME_RESISTANCE)) != 0 OR $fx_resistance(~%same_id%~) == $fx_resistance(~%same_other%~))
		AND ((same_ignored BAND AD_SAME_PROBABILITY) != 0 OR ($fx_probability1(~%same_id%~) == $fx_probability1(~%same_other%~)
			AND $fx_probability2(~%same_id%~) == $fx_probability2(~%same_other%~)))
		AND ((same_ignored BAND AD_SAME_DICE) != 0 OR ($fx_dice_count(~%same_id%~) == $fx_dice_count(~%same_other%~)
			AND $fx_dice_sides(~%same_id%~) == $fx_dice_sides(~%same_other%~)))
		AND ((same_ignored BAND AD_SAME_SAVE) != 0 OR ($fx_save_type(~%same_id%~) == $fx_save_type(~%same_other%~)
			AND $fx_save_bonus(~%same_id%~) == $fx_save_bonus(~%same_other%~)))
		AND ((same_ignored BAND AD_SAME_SPECIAL) != 0 OR $fx_special(~%same_id%~) == $fx_special(~%same_other%~))
	PATCH_IF fx_same BEGIN
		SPRINT same_scope $fx_scope(~%same_id%~)
		SPRINT same_other_scope $fx_scope(~%same_other%~)
		SET fx_same = ~%same_scope%~ STRING_EQUAL ~%same_other_scope%~
	END
END
