// Opcode 17 (HP: Current HP Modifier) : parameter2, mot de poids faible : 0 ajout, 1 valeur fixée,
// 2 pourcentage ; mot de poids fort : bit 0 rend la vie, bit 1 retire les effets (ancien
// opcode_17_common, qui le signale sans le décrire). Valeur : dés et parameter1 (ad_dice_text) ;
// positive, « Restaure 5 points de vie au porteur » ; négative, « Inflige 3 points de dégâts à la
// cible » ; valeur fixée, « Points de vie actuels : Passe à +5 », à toutes les formes « soi » et
// « cible ».

DEFINE_PATCH_MACRO ad_op_17_support BEGIN
	PHP_EACH fx_ids_17 AS _ => hp_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET hp_type = $fx_parameter2(~%hp_id%~) BAND 65535
			// L'ancien moteur divise par 65 535, et non 65 536.
			SET hp_subtype = $fx_parameter2(~%hp_id%~) / 65535
			LPF ad_dice_text INT_VAR dice_count = $fx_dice_count(~%hp_id%~) dice_sides = $fx_dice_sides(~%hp_id%~)
				bonus = $fx_parameter1(~%hp_id%~) RET hp_value = text END
			PATCH_IF hp_type < 0 OR hp_type > 2 BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~file_error:opcode17:invalid~ message = ~healing type %hp_type% (expected 0-2)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF ~%hp_value%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~not_implemented:opcode17:no_value~ message = ~no text for this amount~ RET render_missing = refusal END
			END
			// Avec AD_ENABLE_SHRINKAGE, l'ancien moteur ajoute un effet de résurrection (opcode 32), pas
			// encore décrit (opcode_17_group).
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND (hp_subtype BAND BIT0) != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~not_implemented:opcode17:raise_dead~ message = ~healing that also raises the dead~ RET render_missing = refusal END
			END
			// Valeur fixée probable : l'ancien moteur écrit « les points de vie actuels : … ».
			ELSE PATCH_IF hp_type == 1 AND $fx_probability(~%hp_id%~) < 100 BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~not_implemented:opcode17:probable_set~ message = ~probable healing to a set value~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_17_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~17~)
	PHP_EACH fx_ids_17 AS _ => hp_id BEGIN
		PATCH_IF NOT $fx_consumed(~%hp_id%~) BEGIN
			SET hp_type = $fx_parameter2(~%hp_id%~) BAND 65535
			LPF ad_dice_text INT_VAR dice_count = $fx_dice_count(~%hp_id%~) dice_sides = $fx_dice_sides(~%hp_id%~)
				bonus = $fx_parameter1(~%hp_id%~) RET value = text END
			SET line_fx = hp_id
			PATCH_IF hp_type == 1 BEGIN
				SPRINT name @20170000 // ~Points de vie actuels~
				SPRINT value @1200002 // ~Passe à %value%~
				SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
			END
			ELSE BEGIN
				LPM ad_op_17_phrase
			END
			LPM ad_effect_line
		END
	END
END

// Phrase d'un ajout ou d'un pourcentage : sans « - » en tête, un soin ; sinon des dégâts.
DEFINE_PATCH_MACRO ad_op_17_phrase BEGIN
	SET hp_damage = INDEX (EXACT_MATCH ~-~ ~%value%~) == 0
	INNER_PATCH_SAVE value ~%value%~ BEGIN
		REPLACE_TEXTUALLY EVALUATE_REGEXP ~^[-+]~ ~~
	END
	PATCH_IF hp_type == 2 BEGIN
		SPRINT value @1200003 // ~%value%%PERCENT%~
	END
	SET hp_single = (~%value%~ STRING_EQUAL ~1~) OR (~%value%~ STRING_EQUAL ~1%PERCENT%~)
	PATCH_IF NOT hp_damage BEGIN
		PATCH_IF hp_type == 2 BEGIN
			SPRINT valueType @20170005 // ~des points de vie~
			SET line_phrase = 20170120 // ~Restaure %value% %ofTheTarget%~
		END
		ELSE BEGIN
			LPF ad_tra INT_VAR tra_id = hp_single ? 20170001 : 20170002 RET valueType = text END // ~point de vie~
			SET line_phrase = 20170100 // ~Restaure %value% %toTheTarget%~
		END
	END
	ELSE BEGIN
		LPF ad_tra INT_VAR tra_id = hp_single ? 20170003 : 20170004 RET valueType = text END // ~point de dégât~
		SET line_phrase = 20170110 // ~Inflige %value% %toTheTarget%~
	END
	SPRINT value @20170006 // ~%value% %valueType%~
END
