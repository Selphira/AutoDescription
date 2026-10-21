// Code commun des sorts lancés (opcodes 146 et 148), cités par leur nom (ancien opcode_target_146) :
// sur une capacité de charge (en-tête à charges ou utilisé depuis l'objet), le nom seul
// (« Boule de feu (instantané) ») ; ailleurs, « Lance « Boule de feu » sur la cible ».
// parameter2 non nul : lancé instantanément ; parameter2 2, ou parameter1 non nul avec parameter2
// 0 : « (comme un lanceur de sorts de niveau N) ». Un sort sans nom, ou lancé par une potion, est
// décrit par ses effets (new-lib/recursion.tpp) : ses lignes prennent la place de celle du sort.
// Les macros ad_op_<N>_* fixent cast_opcode (et cast_phrase pour les lignes) puis appellent les
// macros ci-dessous. Le regroupement avec l'opcode 321 (ancien opcode_146_group, non cumulatif)
// viendra avec cet opcode.

// Refus : ressource vide (écartée par l'ancien opcode_resref_is_valid) ; sort d'Item Revision
// (AD_ITEM_REVISION_SPELLS : l'ancien moteur en écrit un texte propre) ; en-tête à charges d'une
// fléchette (ses lignes vont aux capacités de combat, où l'ancien moteur les écrit autrement) ; sort
// nommé lancé par un sous-sort (l'ancien moteur y lit le type de capacité de l'objet) ; refus de
// ad_cast_spell_recursion_support.
DEFINE_PATCH_MACRO ad_cast_spell_support BEGIN
	FOR (cast_id = 0; cast_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++cast_id) BEGIN
		PATCH_IF $fx_opcode(~%cast_id%~) == cast_opcode BEGIN
			SET $fx_recursion(~%cast_id%~) = 0
			SET $fx_sub_count(~%cast_id%~) = 0
		END
		// Une répétition est réunie à l'effet de tête de sa série (new-lib/groups.tpp).
		PATCH_IF $fx_opcode(~%cast_id%~) == cast_opcode AND $fx_series_of(~%cast_id%~) < 0 BEGIN
			SPRINT cast_resref $fx_resource_lower(~%cast_id%~)
			LPF ad_spell_name STR_VAR resref = ~%cast_resref%~ RET cast_name = name END
			SPRINT $fx_spell_name(~%cast_id%~) ~%cast_name%~
			SET cast_h = $fx_header(~%cast_id%~)
			SET $fx_cast_charge(~%cast_id%~) = 0
			PATCH_IF cast_h >= 0 BEGIN
				SET $fx_cast_charge(~%cast_id%~) = NOT $charged_other(~%cast_h%~)
			END
			PATCH_IF ~%cast_resref%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode%cast_opcode%:invalid~
			END
			ELSE PATCH_IF VARIABLE_IS_SET $AD_ITEM_REVISION_SPELLS(~%cast_resref%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode%cast_opcode%:item_revision~
			END
			ELSE PATCH_IF item_type == ITM_TYPE_dart AND $fx_cast_charge(~%cast_id%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode%cast_opcode%:dart~
			END
			ELSE PATCH_IF item_type == ITM_TYPE_potion OR ~%cast_name%~ STRING_EQUAL ~~ BEGIN
				SET $fx_recursion(~%cast_id%~) = 1
				LPM ad_cast_spell_recursion_support
			END
			ELSE PATCH_IF ctx_depth > 0 BEGIN
				SPRINT render_missing ~not_implemented:recursion:nested_cast~
			END
		END
	END
END

// Sort cast_id décrit par ses effets (ancien opcode_146_get_spell_effects_description) : niveau de
// lancement parameter1, aucun pour un sort lancé instantanément (parameter2 1) ; cible héritée
// pour l'opcode 146 ; durées des sous-effets non écrites sous la durée commune d'une potion. Au-delà
// de la profondeur permise, l'ancien moteur n'écrit rien, même pour un effet probable ou différé.
// Refus : effet probable (l'ancien moteur multiplie les probabilités et retire « N % de chances »
// des sous-lignes ; une potion y cite le sort par son nom) ; effet différé (l'ancien moteur en fait
// une condition) ; répétitions d'un sort sans nom (l'ancien moteur réécrit la durée des sous-lignes) ;
// effet d'un 177 contre un type de créature ; sort déjà décrit par la ressource
// (recursion_repeated) ; cible sans chaînes ; refus de la sous-description.
DEFINE_PATCH_MACRO ad_cast_spell_recursion_support BEGIN
	SPRINT recursion_resref ~%cast_resref%~
	LPM ad_recursion_allowed
	PATCH_IF recursion_allowed BEGIN
		PATCH_IF $fx_probability(~%cast_id%~) < 100 BEGIN
			SPRINT render_missing ~not_implemented:recursion:probability~
		END
		ELSE PATCH_IF $fx_timing(~%cast_id%~) == TIMING_delayed AND NOT $fx_series_anchor(~%cast_id%~) BEGIN
			SPRINT render_missing ~not_implemented:recursion:delayed~
		END
		ELSE PATCH_IF $fx_series_anchor(~%cast_id%~) AND item_type != ITM_TYPE_potion BEGIN
			SPRINT render_missing ~not_implemented:recursion:series~
		END
		ELSE PATCH_IF $fx_versus_file(~%cast_id%~) > 0 BEGIN
			SPRINT render_missing ~not_implemented:recursion:versus~
		END
		ELSE PATCH_IF recursion_repeated BEGIN
			SPRINT render_missing ~not_implemented:recursion:repeated~
		END
		ELSE BEGIN
			SET line_fx = cast_id
			SPRINT line_the_target ~~
			LPM ad_application_form
			LPM ad_application_target_strings
			SPRINT line_only_for ~~
			PATCH_IF app_target_missing BEGIN
				SPRINT render_missing ~not_implemented:recursion:target~
			END
			ELSE BEGIN
				SET cast_casting_level = $fx_parameter2(~%cast_id%~) == 1 ? 0 : $fx_parameter1(~%cast_id%~)
				SET cast_ignore_duration = ctx_ignore_duration
				PATCH_IF item_type == ITM_TYPE_potion AND cast_h >= 0 BEGIN
					SET cast_ignore_duration = cast_ignore_duration OR $charged_global_duration(~%cast_h%~) > 0
				END
				LPF ad_describe_subresource
					INT_VAR
						ctx_depth = ctx_depth + 1
						ctx_casting_level = cast_casting_level
						ctx_force_target = (cast_opcode == 146)
						ctx_ignore_duration = cast_ignore_duration
					STR_VAR
						resref = ~%cast_resref%~
						ctx_chain = ~%ctx_chain%~
						ctx_the_target = ~%theTarget%~
						ctx_of_the_target = ~%ofTheTarget%~
						ctx_to_the_target = ~%toTheTarget%~
					RET
						cast_sub_missing = sub_missing
						cast_sub_count = sub_count
						cast_sub_text = sub_text
				END
				SPRINT render_missing ~%cast_sub_missing%~
				SET $fx_sub_count(~%cast_id%~) = cast_sub_count
				SPRINT $fx_sub_text(~%cast_id%~) ~%cast_sub_text%~
			END
		END
	END
END

// Phrase : cast_phrase + 10 × variante + forme ; variante 0 nom seul (capacité de charge), 1 nom
// seul instantané, 2 « Lance », 3 « Lance instantanément » ; les formes probables ne distinguent
// pas les capacités de charge, comme dans l'ancien moteur. Un sort décrit par ses effets a pour ligne
// celles de ses effets (aucune s'il n'en a pas), suivie de la durée, du jet de sauvegarde et des
// exceptions de cible de l'effet qui le lance : avec plusieurs sous-lignes, ils ne suivent que la
// dernière (BUG-036).
DEFINE_PATCH_MACRO ad_cast_spell_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%cast_opcode%~)
	FOR (cast_id = 0; cast_id < fx_count; ++cast_id) BEGIN
		PATCH_IF $fx_opcode(~%cast_id%~) == cast_opcode AND NOT $fx_consumed(~%cast_id%~) AND $fx_recursion(~%cast_id%~) BEGIN
			PATCH_IF $fx_sub_count(~%cast_id%~) > 0 BEGIN
				SPRINT line_text $fx_sub_text(~%cast_id%~)
				SET line_any_form = 1
				SET line_fx = cast_id
				LPM ad_effect_line
			END
		END
		ELSE PATCH_IF $fx_opcode(~%cast_id%~) == cast_opcode AND NOT $fx_consumed(~%cast_id%~) BEGIN
			SPRINT spellName $fx_spell_name(~%cast_id%~)
			SET cast_type = $fx_parameter2(~%cast_id%~)
			SET castingLevel = $fx_parameter1(~%cast_id%~)
			SET cast_variant = ($fx_cast_charge(~%cast_id%~) ? 0 : 2) + (cast_type > 0 ? 1 : 0)
			PATCH_IF cast_type == 2 OR (castingLevel > 0 AND cast_type == 0) BEGIN
				LPF ad_tra INT_VAR tra_id = cast_phrase - 100 RET cast_level_text = text END // ~comme un lanceur de sorts de niveau %castingLevel%~
				SPRINT line_suffix ~(%cast_level_text%)~
			END
			SET line_phrase = cast_phrase + 10 * cast_variant // ~%spellName%~
			SET line_fx = cast_id
			LPM ad_effect_line
		END
	END
END
