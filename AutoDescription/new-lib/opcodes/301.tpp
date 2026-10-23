// Opcode 301 (Stat: Critical Hit Modifier, EE) : chance de coup critique augmentée de 5 % par point de
// parameter1 (IESDP : coup critique sur un jet de 20 - parameter1 ou plus) ; parameter2 1 : « avec
// cette arme » ; special 1-3 : « en mêlée », « à distance », « magique » (ancien opcode_301_common) :
// « Chance de coup critique avec cette arme à distance : +5 % ». Libellés 2301 0001-0004 (« soi »
// puis « la chance… » des phrases « Augmente de… », 1 210 1x0), 0011-0013 type d'attaque.

// Refus : effet d'un EFF (l'ancien moteur y lit parameter3, la catégorie d'arme) ; type d'attaque
// hors de 0-3 ou valeur nulle (l'ancien opcode_301_is_valid les écarte).
DEFINE_PATCH_MACRO ad_op_301_support BEGIN
	PHP_EACH fx_ids_301 AS _ => critical_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT $fx_consumed(~%critical_id%~) BEGIN
			PATCH_IF $fx_external(~%critical_id%~) BEGIN
				LPF ad_refusal INT_VAR fx_id = critical_id STR_VAR reason = ~not_implemented:opcode301:external~ message = ~effect from an EFF file~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_special(~%critical_id%~) < 0 OR $fx_special(~%critical_id%~) > 3 OR $fx_parameter1(~%critical_id%~) == 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = critical_id STR_VAR reason = ~file_error:opcode301:invalid~ message = ~invalid weapon type (special, expected 0-3) or modifier of 0~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_301_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~301~)
	PHP_EACH fx_ids_301 AS _ => critical_id BEGIN
		PATCH_IF NOT $fx_consumed(~%critical_id%~) BEGIN
			SET line_fx = critical_id
			LPM ad_application_form
			SET critical_value = 5 * $fx_parameter1(~%critical_id%~)
			SET critical_name_tra = 23010001 + (line_form == 0 ? 0 : 2) + ($fx_parameter2(~%critical_id%~) != 0 ? 1 : 0)
			LPF ad_tra INT_VAR tra_id = critical_name_tra RET name = text END // ~Chance de coup critique~
			SET critical_attack = $fx_special(~%critical_id%~)
			PATCH_IF critical_attack > 0 BEGIN
				LPF ad_tra INT_VAR tra_id = 23010010 + critical_attack tra_block_start = 23010011 tra_block_size = 3 RET critical_attack_text = text END // ~en mêlée~
				SPRINT name ~%name% %critical_attack_text%~
			END
			PATCH_IF line_form == 0 BEGIN
				LPF ad_signed_value INT_VAR value = critical_value RET value = text END
				SPRINT value @1200003 // ~%value%%PERCENT%~
				SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
			END
			ELSE BEGIN
				SPRINT theStatistic ~%name%~
				SET value = ABS critical_value
				SPRINT value @1200003 // ~%value%%PERCENT%~
				SET line_phrase = critical_value > 0 ? 1210110 : 1210120 // ~Augmente de %value% %theStatistic% %ofTheTarget%~
			END
			LPM ad_effect_line
		END
	END
END
