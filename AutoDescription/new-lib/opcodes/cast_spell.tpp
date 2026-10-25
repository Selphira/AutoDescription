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
// nommé lancé par un sous-sort d'un objet (l'ancien moteur y lit le type de capacité de l'objet ; un
// sort n'en a pas, ancien abilityType négatif) ; refus de ad_cast_spell_recursion_support.
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
			PATCH_IF cast_h >= 0 AND NOT resource_is_spell BEGIN
				SET $fx_cast_charge(~%cast_id%~) = NOT $charged_other(~%cast_h%~)
			END
			PATCH_IF ~%cast_resref%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = cast_id STR_VAR reason = ~file_error:opcode%cast_opcode%:invalid~ message = ~empty resource field~ RET render_missing = refusal END
			END
			ELSE PATCH_IF VARIABLE_IS_SET $AD_ITEM_REVISION_SPELLS(~%cast_resref%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = cast_id STR_VAR reason = ~not_implemented:opcode%cast_opcode%:item_revision~ message = ~spell %cast_resref% from Item Revisions~ RET render_missing = refusal END
			END
			ELSE PATCH_IF item_type == ITM_TYPE_dart AND $fx_cast_charge(~%cast_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = cast_id STR_VAR reason = ~not_implemented:opcode%cast_opcode%:dart~ message = ~dart casting a spell on each charge~ RET render_missing = refusal END
			END
			ELSE PATCH_IF item_type == ITM_TYPE_potion OR ~%cast_name%~ STRING_EQUAL ~~ BEGIN
				SET $fx_recursion(~%cast_id%~) = 1
				LPM ad_cast_spell_recursion_support
			END
			ELSE PATCH_IF ctx_depth > 0 AND NOT resource_is_spell BEGIN
				LPF ad_refusal INT_VAR fx_id = cast_id STR_VAR reason = ~not_implemented:recursion:nested_cast~ message = ~spell cast by a spell already cast by another effect~ RET render_missing = refusal END
			END
		END
	END
END

// Sort cast_id décrit par ses effets (ancien opcode_146_get_spell_effects_description,
// ad_recursion_support) : niveau de lancement parameter1, aucun pour un sort lancé instantanément
// (parameter2 1) par un objet (ancien isItem) ; cible héritée pour l'opcode 146 ; lancé après un délai, sous une condition
// (ad_cast_spell_delayed_condition) ; répété (série), la durée des sous-lignes réécrite
// (ad_cast_spell_series_text). Effet probable d'un sort : sa probabilité passe aux sous-effets, dont
// les lignes sont regroupées par probabilité (ancien baseProbability) ; l'ancien moteur décrit
// autrement celui d'un objet, refusé.
DEFINE_PATCH_MACRO ad_cast_spell_recursion_support BEGIN
	SET recursion_fx = cast_id
	SPRINT recursion_resref ~%cast_resref%~
	SET recursion_casting_level = ($fx_parameter2(~%cast_id%~) == 1 AND NOT resource_is_spell) ? 0 : $fx_parameter1(~%cast_id%~)
	PATCH_IF cast_opcode == 146 BEGIN
		SPRINT recursion_targets ~effect~
	END
	ELSE BEGIN
		SPRINT recursion_targets ~own~
	END
	SET recursion_ignore_duration = 0
	SET recursion_series = 1
	SET recursion_depth_reset = 0
	SPRINT recursion_kind ~spl~
	SET recursion_parent_dice = 0
	SET recursion_versus_set = 0
	SPRINT recursion_versus ~~
	SPRINT recursion_single_reason ~~
	SET recursion_delayed = 1
	SET recursion_probability = resource_is_spell
	LPM ad_recursion_support
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
				PATCH_IF $fx_sub_delayed(~%cast_id%~) AND $fx_sub_count(~%cast_id%~) > 1 BEGIN
					LPM ad_cast_spell_delayed_condition
				END
				PATCH_IF $fx_series_anchor(~%cast_id%~) AND item_type != ITM_TYPE_potion BEGIN
					LPM ad_cast_spell_series_text
				END
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

// Sort cast_id répété chaque round (série, ancien timing 5000 ou 5001 de opcode_target_146) : « pendant
// 1 round » des sous-lignes devient la durée de la série (« chaque round pendant 3 rounds »), qui ne
// suit plus la ligne ; sinon, ou à un autre intervalle, elle la suit (ad_application_duration). Une
// potion garde les sous-lignes telles quelles.
DEFINE_PATCH_MACRO ad_cast_spell_series_text BEGIN
	PATCH_IF $fx_series_delta(~%cast_id%~) == 6 BEGIN
		SET line_fx = cast_id
		LPM ad_application_duration
		LPF ad_duration_text INT_VAR seconds = 6 RET strDuration = text END
		SPRINT cast_round @3000000 // ~pendant %strDuration%~
		SPRINT cast_series_text ~%line_text%~
		INNER_PATCH_SAVE cast_series_text ~%cast_series_text%~ BEGIN
			REPLACE_TEXTUALLY EXACT_MATCH ~%cast_round%~ ~%app_duration_text%~
		END
		PATCH_IF NOT (~%cast_series_text%~ STRING_EQUAL ~%line_text%~) BEGIN
			SPRINT line_text ~%cast_series_text%~
			SET line_no_duration = 1
		END
	END
END

// Sort cast_id lancé après un délai, à plusieurs sous-lignes (ancien opcode_146_condition) : la
// condition « Après 1 tour, pendant 5 rounds » (durée commune de ses effets, fx_sub_duration_text,
// new-lib/recursion.tpp) précède la première, les suivantes en retrait ; ni délai ni durée après la
// ligne. Une seule sous-ligne garde le délai à sa suite (« … après 2 heures »).
DEFINE_PATCH_MACRO ad_cast_spell_delayed_condition BEGIN
	LPF ad_duration_text INT_VAR seconds = $fx_duration(~%cast_id%~) RET strDuration = text END
	SPRINT line_condition @3000005 // ~après %strDuration%~
	SPRINT cast_common_duration $fx_sub_duration_text(~%cast_id%~)
	PATCH_IF NOT (~%cast_common_duration%~ STRING_EQUAL ~~) BEGIN
		SPRINT strDuration ~%cast_common_duration%~
		SPRINT cast_during @3000000 // ~pendant %strDuration%~
		SPRINT line_condition ~%line_condition%, %cast_during%~
	END
	LPF ad_ucfirst STR_VAR text = ~%line_condition%~ RET line_condition = text END
	INNER_PATCH_SAVE line_text ~%line_text%~ BEGIN
		REPLACE_TEXTUALLY ~%CRLF%~ ~%CRLF%  ~
	END
	SET line_no_duration = 1
END
