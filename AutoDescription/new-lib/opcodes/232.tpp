// Opcode 232 (Spell Effect: Cast Spell on Condition) : sort resource lancé sur la cible parameter1
// (0 porteur, 1 attaquant, 2 adversaire le plus proche, 3 créature la plus proche) quand la condition
// parameter2 est remplie (ancien opcode_232_common) : « Lorsque le porteur est touché ; Inflige 1d4
// points de dégâts de feu à l'attaquant ». Le sort est décrit par ses effets (new-lib/recursion.tpp),
// qui reprennent les chaînes de la cible parameter1, sauf pour une condition de distance (8, 9, 14) ;
// l'ancien moteur y fixe aussi versus à cette cible (vide pour une distance, BUG-038), que les dégâts
// écrivent même sous une zone de projectile (ctx_versus) ;
// un sort nommé dont les effets donnent plusieurs lignes est cité par son nom.

// Refus : effet d'un EFF (l'ancien moteur y lit aussi resource2 et resource3) ; valeurs que l'ancien
// opcode_232_is_valid écarte (cible hors de 0-3, condition hors de 0-21, ou de 0-11 sur un jeu
// classique, moment de la journée sur une autre cible que le porteur, condition 10 sans special,
// ressource vide) ; effet d'un sous-sort (l'ancien moteur n'y limite pas la profondeur) ; condition
// d'un état (5, 6, 15) ; condition de distance trop courte, moment de la journée ou état de sort sans
// nom ; plusieurs lignes d'un sort sans nom sous une condition vide ; refus de ad_recursion_support.
DEFINE_PATCH_MACRO ad_op_232_support BEGIN
	FOR (condition_id = 0; condition_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++condition_id) BEGIN
		PATCH_IF $fx_opcode(~%condition_id%~) == 232 AND NOT $fx_consumed(~%condition_id%~) BEGIN
			SET condition_target = $fx_parameter1(~%condition_id%~)
			SET condition_type = $fx_parameter2(~%condition_id%~)
			SET condition_special = $fx_special(~%condition_id%~)
			SPRINT condition_resref $fx_resource_lower(~%condition_id%~)
			PATCH_IF $fx_external(~%condition_id%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode232:external~
			END
			ELSE PATCH_IF condition_target < 0 OR condition_target > 3 OR condition_type < 0 OR condition_type > (IS_EE ? 21 : 11)
					OR (condition_type == 13 AND condition_target != 0) OR (condition_type == 10 AND condition_special == 0)
					OR ~%condition_resref%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode232:invalid~
			END
			ELSE PATCH_IF ctx_depth > 0 BEGIN
				SPRINT render_missing ~not_implemented:recursion:nested_condition~
			END
			ELSE BEGIN
				LPM ad_op_232_targets
				LPM ad_op_232_condition
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
				LPF ad_spell_name STR_VAR resref = ~%condition_resref%~ RET condition_name = name END
				SPRINT $fx_spell_name(~%condition_id%~) ~%condition_name%~
				SET recursion_fx = condition_id
				SPRINT recursion_resref ~%condition_resref%~
				SET recursion_casting_level = 0
				SPRINT recursion_targets ~given~
				SET recursion_versus_set = 1
				SPRINT recursion_versus ~%toTheTarget%~
				PATCH_IF condition_type == 8 OR condition_type == 9 OR condition_type == 14 BEGIN
					SPRINT recursion_targets ~own~
					SPRINT recursion_versus ~~
				END
				SPRINT recursion_the_target ~%theTarget%~
				SPRINT recursion_of_the_target ~%ofTheTarget%~
				SPRINT recursion_to_the_target ~%toTheTarget%~
				SET recursion_series = 0
				SET recursion_tracked = 0
				SPRINT recursion_kind ~spl~
				SET recursion_parent_dice = 0
				LPM ad_recursion_support
				PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND $fx_sub_count(~%condition_id%~) > 1
						AND ~%condition_name%~ STRING_EQUAL ~~ AND ~%condition_text%~ STRING_EQUAL ~~ BEGIN
					SPRINT render_missing ~not_implemented:opcode232:no_condition~
				END
			END
		END
	END
END

// Chaînes de la cible parameter1 de l'effet condition_id (theTarget, ofTheTarget, toTheTarget).
DEFINE_PATCH_MACRO ad_op_232_targets BEGIN
	SET condition_target = $fx_parameter1(~%condition_id%~)
	LPF ad_tra INT_VAR tra_id = 22321000 + condition_target RET theTarget = text END // ~le porteur~
	LPF ad_tra INT_VAR tra_id = 22321010 + condition_target RET ofTheTarget = text END // ~du porteur~
	LPF ad_tra INT_VAR tra_id = 22321020 + condition_target RET toTheTarget = text END // ~au porteur~
END

// Condition de l'effet condition_id (ancien opcode_232_condition) : $fx_condition_text, vide pour un
// sort lancé à chaque round par un effet d'équipement, que l'ancien moteur décrit comme permanent ;
// sous cette condition ou celle d'un moment de la journée sur un effet d'équipement, les durées du
// sous-sort ne sont pas écrites (recursion_ignore_duration). Points de vie : seuil de 50, 25 ou 10 %
// (conditions 2 à 4), special % (20) ou special points (19) ; distance : 4, 10 ou special pieds (8,
// 9, 14).
DEFINE_PATCH_MACRO ad_op_232_condition BEGIN
	SPRINT condition_text ~~
	SET recursion_ignore_duration = 0
	SPRINT condition_block $fx_block(~%condition_id%~)
	SET condition_equipped = ~%condition_block%~ STRING_EQUAL ~equipped~
	PATCH_IF condition_type == 0 OR condition_type == 1 OR condition_type == 7 OR condition_type == 10 OR condition_type == 11
			OR condition_type == 12 OR condition_type == 16 OR condition_type == 17 OR condition_type == 18 BEGIN
		LPF ad_tra INT_VAR tra_id = 22320010 + condition_type RET condition_text = text END // ~Lorsque le porteur est touché~
	END
	ELSE PATCH_IF (condition_type >= 2 AND condition_type <= 4) OR condition_type == 20 BEGIN
		SET value = condition_type == 2 ? 50 : condition_type == 3 ? 25 : condition_type == 4 ? 10 : condition_special
		PATCH_IF value >= 100 AND condition_equipped BEGIN
			SET recursion_ignore_duration = 1
		END
		ELSE PATCH_IF value >= 100 BEGIN
			SPRINT condition_text @22320020 // ~À chaque round~
		END
		ELSE BEGIN
			SPRINT percent @1200003 // ~%value%%PERCENT%~
			SPRINT condition_text @22320030 // ~Lorsque les points de vie du porteur tombent sous les %percent%~
		END
	END
	ELSE PATCH_IF condition_type == 19 BEGIN
		SET value = condition_special
		SPRINT condition_text @22320029 // ~Lorsque les points de vie du porteur tombent en dessous de %value%~
	END
	ELSE PATCH_IF condition_type == 8 OR condition_type == 9 OR condition_type == 14 BEGIN
		LPF ad_distance_text INT_VAR feet = condition_type == 8 ? 4 : condition_type == 9 ? 10 : condition_special RET range = text END
		PATCH_IF ~%range%~ STRING_EQUAL ~~ BEGIN
			SPRINT render_missing ~not_implemented:opcode232:range~
		END
		ELSE BEGIN
			SPRINT condition_text @22320024 // ~Lorsque la cible se trouve à moins de %range%~
		END
	END
	ELSE PATCH_IF condition_type == 13 BEGIN
		PATCH_IF condition_special < 0 OR condition_special > 3 BEGIN
			SPRINT render_missing ~not_implemented:opcode232:time_of_day~
		END
		ELSE BEGIN
			SET recursion_ignore_duration = condition_equipped
			LPF ad_tra INT_VAR tra_id = 22321100 + (condition_equipped ? 0 : 4) + condition_special RET condition_text = text END // ~À la nuit tombée~
		END
	END
	ELSE PATCH_IF condition_type == 21 BEGIN
		SET condition_splstate_tra = 8120000 + condition_special
		PATCH_IF condition_special < 0 OR condition_special > 255 OR NOT TRA_ENTRY_EXISTS (~%condition_splstate_tra%~) BEGIN
			SPRINT render_missing ~not_implemented:opcode232:splstate~
		END
		ELSE BEGIN
			LPF ad_tra INT_VAR tra_id = condition_splstate_tra tra_block_start = 8120000 tra_block_size = 256 RET splstate = text END // ~la folie du berserker~ (@8120104)
			SPRINT condition_text @22320031 // ~À chaque round où %theTarget% est affecté par %splstate%~
		END
	END
	ELSE BEGIN
		SPRINT render_missing ~not_implemented:opcode232:state~
	END
	SPRINT $fx_condition_text(~%condition_id%~) ~%condition_text%~
END

// Une ligne par effet dont le sous-sort en a ; « Lance le sort « … » sur le porteur » pour un sort
// nommé à plusieurs lignes.
DEFINE_PATCH_MACRO ad_op_232_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~232~)
	FOR (condition_id = 0; condition_id < fx_count; ++condition_id) BEGIN
		PATCH_IF $fx_opcode(~%condition_id%~) == 232 AND NOT $fx_consumed(~%condition_id%~) AND $fx_sub_count(~%condition_id%~) > 0 BEGIN
			SET recursion_fx = condition_id
			SPRINT spellName $fx_spell_name(~%condition_id%~)
			PATCH_IF $fx_sub_count(~%condition_id%~) > 1 AND NOT (~%spellName%~ STRING_EQUAL ~~) BEGIN
				LPM ad_op_232_targets
				SPRINT line_text @22320001 // ~Lance le sort « %spellName% » sur %theTarget%~
			END
			ELSE BEGIN
				LPM ad_recursion_condition_text
			END
			SPRINT line_condition $fx_condition_text(~%condition_id%~)
			SET line_any_form = 1
			SET line_fx = condition_id
			LPM ad_effect_line
		END
	END
END
