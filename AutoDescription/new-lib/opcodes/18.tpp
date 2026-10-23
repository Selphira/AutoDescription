// Opcode 18 (HP: Maximum HP Modifier) : parameter1 = valeur, parameter2 = mode (0 ajout, 1 valeur
// fixée, 2 pourcentage ; 3 à 5 : mêmes modes sans changer les points de vie actuels ; 6, EE : ajout
// non cumulatif, décrit comme un ajout par l'ancien moteur). Le nom est « Points de vie maximums »
// si les points de vie actuels ne changent pas (modes 3 à 5, ou bit 0 de special sur EE), « Points
// de vie » sinon.
//
// Pris en charge : effets d'équipement certains, actifs tant que l'objet est équipé.

// ---------------------------------------------------------------------------------------------
// Prise en charge (ancien opcode_18_is_valid, plus les cas que ce moteur ne décrit pas encore)

DEFINE_PATCH_MACRO ad_op_18_support BEGIN
	PHP_EACH fx_ids_18 AS _ => hp_id BEGIN
		LPM ad_op_18_value
		SPRINT hp_scope $fx_scope(~%hp_id%~)
		SET $hp_seen(~%hp_scope%~ ~%hp_value%~ ~%hp_type%~) = 0
	END
	PHP_EACH fx_ids_18 AS _ => hp_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			LPM ad_op_18_value
			SPRINT hp_scope $fx_scope(~%hp_id%~)
			// L'ancien moteur écarte un mode inconnu (erreur journalisée).
			PATCH_IF hp_type < 0 OR hp_type > 6 OR (hp_type == 6 AND NOT IS_EE) BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~file_error:opcode18:invalid~ message = ~modifier type %hp_type% (expected 0-5, 0-6 on enhanced editions)~ RET render_missing = refusal END
			END
			// L'ancien moteur ignore les dés d'un effet d'équipement mais les compte ailleurs, et
			// l'IESDP ne les mentionne pas pour cet opcode (EDGE-008) ; sans dé lancé, les faces sont
			// ignorées partout.
			ELSE PATCH_IF $fx_dice_count(~%hp_id%~) > 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~not_implemented:opcode18:dice~ message = ~maximum hit points given by dice~ RET render_missing = refusal END
			END
			// Ajout nul : l'ancien moteur n'écrit pas de ligne ; pourcentage 100 : il écrit « 100 ».
			ELSE PATCH_IF (hp_mode == MOD_TYPE_cumulative AND hp_value == 0) OR (hp_mode == MOD_TYPE_percentage AND hp_value == 100) BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~file_error:opcode18:no_change~ message = ~no change (mode %hp_mode%, value %hp_value%)~ RET render_missing = refusal END
			END
			// L'ancien moteur fusionne deux effets identiques au lieu de les cumuler.
			ELSE PATCH_IF $hp_seen(~%hp_scope%~ ~%hp_value%~ ~%hp_type%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = hp_id STR_VAR reason = ~not_implemented:opcode18:same_effect_twice~ message = ~same effect twice (the old engine merges them)~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET $hp_seen(~%hp_scope%~ ~%hp_value%~ ~%hp_type%~) = 1
			END
		END
	END
END

// ---------------------------------------------------------------------------------------------
// Lignes (ancien opcode_self_18) : une par effet non consommé par un regroupement.

DEFINE_PATCH_MACRO ad_op_18_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~18~)
	PHP_EACH fx_ids_18 AS _ => hp_id BEGIN
		PATCH_IF NOT $fx_consumed(~%hp_id%~) BEGIN
			LPM ad_op_18_value
			PATCH_IF (hp_type >= 3 AND hp_type <= 5) OR (IS_EE AND ($fx_special(~%hp_id%~) BAND BIT0) != 0) BEGIN
				SPRINT name @20180000 // ~Points de vie maximums~
			END
			ELSE BEGIN
				SPRINT name @20180001 // ~Points de vie~
			END
			LPF ad_stat_modifier_value INT_VAR value = hp_value mode = hp_mode RET value = text END
			SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
			SET line_fx = hp_id
			LPM ad_effect_line
		END
	END
END

// Écrit hp_type (parameter2), hp_mode (son mode 0, 1 ou 2) et hp_value (parameter1) de l'effet
// hp_id.
DEFINE_PATCH_MACRO ad_op_18_value BEGIN
	SET hp_type = $fx_parameter2(~%hp_id%~)
	SET hp_mode = hp_type MODULO 3
	SET hp_value = $fx_parameter1(~%hp_id%~)
END
