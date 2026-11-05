// Code commun des sorts lancés (opcodes 146 et 148), cités par leur nom (ancien opcode_target_146) :
// sur une capacité de charge (en-tête à charges ou utilisé depuis l'objet), le nom seul
// (« Boule de feu (instantané) ») ; ailleurs, « Lance « Boule de feu » sur la cible ».
// parameter2 non nul : lancé instantanément ; parameter2 2, ou parameter1 non nul avec parameter2
// 0 : « (comme un lanceur de sorts de niveau N) ». Un sort sans nom, ou lancé à coup sûr par une
// potion, est décrit par ses effets (new-lib/recursion.tpp) : ses lignes prennent la place de celle du
// sort. Effet probable : comme l'ancien opcode_target_probability_146, une potion cite aussi le sort
// par son nom.
// Les macros ad_op_<N>_* fixent cast_opcode (et cast_phrase pour les lignes) puis appellent les
// macros ci-dessous. Le regroupement avec l'opcode 321 (ancien opcode_146_group, non cumulatif)
// viendra avec cet opcode.

// Ressource vide : effet écarté sans rien écrire, erreur journalisée (comme l'ancien
// opcode_resref_is_valid).
// Refus : sort d'Item Revision
// (AD_ITEM_REVISION_SPELLS : l'ancien moteur en écrit un texte propre) ; sort nommé lancé par un
// en-tête à charges d'une fléchette (ses lignes vont aux capacités de combat, où l'ancien moteur les
// écrit autrement) ; sort nommé lancé par un sous-sort d'un objet (l'ancien moteur y lit le type de
// capacité de l'objet ; un sort n'en a pas, ancien abilityType négatif) ; refus de
// ad_cast_spell_recursion_support. Un sort sans nom d'une fléchette est décrit par ses effets, et ne
// refuse la fléchette que s'il écrit des lignes (recursion_lines_reason) : sans ligne, l'ancien moteur
// n'écrit rien.
DEFINE_PATCH_MACRO ad_cast_spell_support BEGIN
	FOR (cast_id = 0; cast_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++cast_id) BEGIN
		PATCH_IF $fx_opcode(~%cast_id%~) == cast_opcode BEGIN
			SET $fx_recursion(~%cast_id%~) = 0
			SET $fx_sub_count(~%cast_id%~) = 0
		END
		// Niveau imposé qui choisit dans le sort le même en-tête que le niveau du lanceur : lancé au niveau
		// du lanceur (parameter1 0, IESDP), l'effet est alors semblable d'un en-tête à l'autre.
		PATCH_IF cast_opcode == 146 AND $fx_opcode(~%cast_id%~) == 146 AND resource_is_spell AND $fx_header(~%cast_id%~) >= 0
				AND $fx_parameter2(~%cast_id%~) == 0 AND $fx_parameter1(~%cast_id%~) > 0 BEGIN
			LPF ad_cast_level_is_caster_level INT_VAR header = $fx_header(~%cast_id%~) casting_level = $fx_parameter1(~%cast_id%~)
				STR_VAR resref = $fx_resource_lower(~%cast_id%~) RET cast_caster_level = is_caster_level END
			PATCH_IF cast_caster_level BEGIN
				SET $fx_parameter1(~%cast_id%~) = 0
			END
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
				SET drop_id = cast_id
				SPRINT ignored_reason ~file_error:opcode%cast_opcode%:invalid~
				SPRINT ignored_message ~empty resource field~
				LPM ad_application_drop
			END
			ELSE PATCH_IF VARIABLE_IS_SET $AD_ITEM_REVISION_SPELLS(~%cast_resref%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = cast_id STR_VAR reason = ~not_implemented:opcode%cast_opcode%:item_revision~ message = ~spell %cast_resref% from Item Revisions~ RET render_missing = refusal END
			END
			ELSE PATCH_IF item_type == ITM_TYPE_dart AND $fx_cast_charge(~%cast_id%~) AND NOT (~%cast_name%~ STRING_EQUAL ~~) BEGIN
				LPF ad_refusal INT_VAR fx_id = cast_id STR_VAR reason = ~not_implemented:opcode%cast_opcode%:dart~ message = ~dart casting a spell on each charge~ RET render_missing = refusal END
			END
			ELSE PATCH_IF (item_type == ITM_TYPE_potion AND $fx_probability(~%cast_id%~) >= 100) OR ~%cast_name%~ STRING_EQUAL ~~ BEGIN
				SET $fx_recursion(~%cast_id%~) = 1
				LPM ad_cast_spell_recursion_support
			END
			ELSE PATCH_IF ctx_depth > 0 AND NOT resource_is_spell BEGIN
				LPF ad_refusal INT_VAR fx_id = cast_id STR_VAR reason = ~not_implemented:recursion:nested_cast~ message = ~spell cast by a spell already cast by another effect~ RET render_missing = refusal END
			END
		END
	END
END

// Le sort resref, lancé au niveau imposé casting_level par un effet de l'en-tête header du sort ouvert,
// l'est-il au niveau du lanceur (ancien cast_level_is_caster_level, lib/spl/extended_effects.tpp) ?
// is_caster_level : 1 si ce niveau choisit dans resref le même en-tête que tout niveau de lanceur
// couvert par cet en-tête (PXM4PROJ : lancé au niveau 14 jusqu'au niveau 14, puis au niveau du lanceur
// jusqu'au 30, dernier en-tête de PXM4PROA). En-tête choisi pour un niveau : celui du plus haut niveau
// requis qui ne le dépasse pas, sinon le premier. Le niveau imposé d'un sous-sort à un seul en-tête ne
// choisit rien mais reste écrit (SPWISH09) : il est aussi celui de ses effets.
DEFINE_PATCH_FUNCTION ad_cast_level_is_caster_level
	INT_VAR
		header = 0
		casting_level = 0
	STR_VAR
		resref = ~~
	RET
		is_caster_level
BEGIN
	SET is_caster_level = 0
	READ_LONG  SPL_extended_headers_offset caster_headers_offset
	READ_SHORT SPL_extended_headers_count  caster_header_count
	READ_SHORT (caster_headers_offset + header * 0x28 + SPL_HEAD_level_required) caster_first_level
	// Niveau de l'en-tête suivant du sort ouvert, 0 sans en-tête suivant.
	SET caster_next_level = 0
	FOR (caster_h = 0; caster_h < caster_header_count; ++caster_h) BEGIN
		READ_SHORT (caster_headers_offset + caster_h * 0x28 + SPL_HEAD_level_required) caster_level
		PATCH_IF caster_level > caster_first_level AND (caster_next_level == 0 OR caster_level < caster_next_level) BEGIN
			SET caster_next_level = caster_level
		END
	END
	PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
		INNER_PATCH_FILE ~%resref%.spl~ BEGIN
			PATCH_IF BUFFER_LENGTH >= 0x72 BEGIN
				READ_LONG  SPL_extended_headers_offset caster_sub_offset
				READ_SHORT SPL_extended_headers_count  caster_sub_count
				SET caster_cast_selected = 0 - 1
				SET caster_first_selected = 0 - 1
				SET caster_lowest = 0 - 1
				SET caster_splits = 0
				FOR (caster_h = 0; caster_h < caster_sub_count AND caster_sub_offset + caster_h * 0x28 + 0x28 <= BUFFER_LENGTH; ++caster_h) BEGIN
					READ_SHORT (caster_sub_offset + caster_h * 0x28 + SPL_HEAD_level_required) caster_level
					PATCH_IF caster_lowest < 0 OR caster_level < caster_lowest BEGIN
						SET caster_lowest = caster_level
					END
					PATCH_IF caster_level <= casting_level AND caster_level > caster_cast_selected BEGIN
						SET caster_cast_selected = caster_level
					END
					PATCH_IF caster_level <= caster_first_level AND caster_level > caster_first_selected BEGIN
						SET caster_first_selected = caster_level
					END
					PATCH_IF caster_level > caster_first_level AND (caster_next_level == 0 OR caster_level < caster_next_level) BEGIN
						SET caster_splits = 1
					END
				END
				PATCH_IF caster_cast_selected < 0 BEGIN
					SET caster_cast_selected = caster_lowest
				END
				PATCH_IF caster_first_selected < 0 BEGIN
					SET caster_first_selected = caster_lowest
				END
				SET is_caster_level = caster_sub_count > 1 AND caster_lowest >= 0 AND NOT caster_splits AND caster_cast_selected == caster_first_selected
			END
		END
	END
END

// Sort cast_id décrit par ses effets (ancien opcode_146_get_spell_effects_description,
// ad_recursion_support) : niveau de lancement parameter1, aucun pour un sort lancé instantanément
// (parameter2 1) par un objet (ancien isItem) ; cible héritée pour l'opcode 146 ; lancé après un délai, sous une condition
// (ad_cast_spell_delayed_condition) ; répété (série), la durée des sous-lignes réécrite
// (ad_cast_spell_series_text). Effet probable : sa probabilité passe aux sous-effets, dont les lignes
// sont regroupées par probabilité (ancien baseProbability), puis avec les effets de même plage de la
// ressource (ad_lines_split_sub_probability, new-lib/lines.tpp).
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
	SPRINT recursion_lines_reason ~~
	SPRINT recursion_lines_message ~~
	PATCH_IF item_type == ITM_TYPE_dart AND $fx_cast_charge(~%cast_id%~) BEGIN
		SPRINT recursion_lines_reason ~not_implemented:opcode%cast_opcode%:dart~
		SPRINT recursion_lines_message ~dart casting a spell on each charge~
	END
	SET recursion_delayed = 1
	SET recursion_probability = 1
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
				PATCH_IF $fx_sub_delayed(~%cast_id%~) AND INDEX (CASE_SENSITIVE EXACT_MATCH ~%CRLF%~ ~%line_text%~) >= 0 BEGIN
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
// new-lib/recursion.tpp) précède la première, les suivantes en retrait (ad_effect_line) ; ni délai ni durée après la
// ligne. Une seule sous-ligne, sans sous-lignes, garde le délai à sa suite (« … après 2 heures »).
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
	SET line_no_duration = 1
END
