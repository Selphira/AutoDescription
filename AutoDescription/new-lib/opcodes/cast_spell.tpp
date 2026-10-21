// Code commun des sorts lancés (opcodes 146 et 148), cités par leur nom (ancien opcode_target_146) :
// sur une capacité de charge (en-tête à charges ou utilisé depuis l'objet), le nom seul
// (« Boule de feu (instantané) ») ; ailleurs, « Lance « Boule de feu » sur la cible ».
// parameter2 non nul : lancé instantanément ; parameter2 2, ou parameter1 non nul avec parameter2
// 0 : « (comme un lanceur de sorts de niveau N) ». Les macros ad_op_<N>_* fixent cast_opcode (et
// cast_phrase pour les lignes) puis appellent les macros ci-dessous. Le regroupement avec l'opcode
// 321 (ancien opcode_146_group, non cumulatif) viendra avec cet opcode.

// Refus : ressource vide (écartée par l'ancien opcode_resref_is_valid) ; sort d'Item Revision
// (AD_ITEM_REVISION_SPELLS : l'ancien moteur en écrit un texte propre) ; sort lancé par une potion
// ou sans nom (AD_SPELL_NAMES vide compris) : l'ancien moteur en décrit les effets ; en-tête à
// charges d'une fléchette (ses lignes vont aux capacités de combat, où l'ancien moteur les écrit
// autrement).
DEFINE_PATCH_MACRO ad_cast_spell_support BEGIN
	FOR (cast_id = 0; cast_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++cast_id) BEGIN
		PATCH_IF $fx_opcode(~%cast_id%~) == cast_opcode BEGIN
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
			ELSE PATCH_IF item_type == ITM_TYPE_potion BEGIN
				SPRINT render_missing ~not_implemented:opcode%cast_opcode%:potion~
			END
			ELSE PATCH_IF ~%cast_name%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode%cast_opcode%:unnamed~
			END
			ELSE PATCH_IF item_type == ITM_TYPE_dart AND $fx_cast_charge(~%cast_id%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode%cast_opcode%:dart~
			END
		END
	END
END

// Phrase : cast_phrase + 10 × variante + forme ; variante 0 nom seul (capacité de charge), 1 nom
// seul instantané, 2 « Lance », 3 « Lance instantanément » ; les formes probables ne distinguent
// pas les capacités de charge, comme dans l'ancien moteur.
DEFINE_PATCH_MACRO ad_cast_spell_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~%cast_opcode%~)
	FOR (cast_id = 0; cast_id < fx_count; ++cast_id) BEGIN
		PATCH_IF $fx_opcode(~%cast_id%~) == cast_opcode AND NOT $fx_consumed(~%cast_id%~) BEGIN
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
