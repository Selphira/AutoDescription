// Opcode 332 (Stat: Specific Damage Modifier, EE) : modifie de parameter1 % les dégâts du type
// parameter2 (0 tous, 1 feu, 2 froid, 3 électricité, 4 acide, 5 magie, 6 poison, 7 tranchants,
// 8 perforants, 9 contondants, 10 projectiles) : « Dégâts de feu : +10 % ».

// Refus : valeur nulle ou type inconnu (écartés par l'ancien opcode_332_is_valid) ; avec
// AD_ENABLE_SHRINKAGE, les quatre types élémentaires (1 à 4) ou physiques (7 à 10) modifiés de la même
// façon (l'ancien opcode_332_group en fait « Dégâts élémentaires », « Dégâts physiques ») ; forme
// « cible » (l'ancien .tra anglais n'a pas ses noms « les dégâts de feu »).
DEFINE_PATCH_MACRO ad_op_332_support BEGIN
	FOR (damage_mod_id = 0; damage_mod_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++damage_mod_id) BEGIN
		PATCH_IF $fx_opcode(~%damage_mod_id%~) == 332 BEGIN
			SET damage_mod_type = $fx_parameter2(~%damage_mod_id%~)
			PATCH_IF $fx_parameter1(~%damage_mod_id%~) == 0 OR damage_mod_type < 0 OR damage_mod_type > 10 BEGIN
				LPF ad_refusal INT_VAR fx_id = damage_mod_id STR_VAR reason = ~file_error:opcode332:invalid~ message = ~modifier of 0 or damage type %damage_mod_type% (expected 0-10)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF AD_ENABLE_SHRINKAGE AND (damage_mod_type == 1 OR damage_mod_type == 7) BEGIN
				LPM ad_op_332_group_support
			END
		END
	END
END

// Les trois types qui suivent damage_mod_type, modifiés comme l'effet damage_mod_id.
DEFINE_PATCH_MACRO ad_op_332_group_support BEGIN
	LPF ad_fx_signature INT_VAR fx_id = damage_mod_id with_parameter2 = 0 RET damage_mod_signature = signature END
	SET damage_mod_found = 0
	FOR (damage_mod_other = 0; damage_mod_other < fx_count; ++damage_mod_other) BEGIN
		SET damage_mod_offset = $fx_parameter2(~%damage_mod_other%~) - damage_mod_type
		PATCH_IF $fx_opcode(~%damage_mod_other%~) == 332 AND damage_mod_offset >= 1 AND damage_mod_offset <= 3 BEGIN
			LPF ad_fx_signature INT_VAR fx_id = damage_mod_other with_parameter2 = 0 RET damage_mod_other_signature = signature END
			PATCH_IF ~%damage_mod_other_signature%~ STRING_EQUAL ~%damage_mod_signature%~ BEGIN
				SET damage_mod_found = damage_mod_found BOR (damage_mod_offset == 1 ? 1 : (damage_mod_offset == 2 ? 2 : 4))
			END
		END
	END
	PATCH_IF damage_mod_found == 7 BEGIN
		LPF ad_refusal INT_VAR fx_id = damage_mod_other STR_VAR reason = ~not_implemented:opcode332:group~ message = ~group of damage modifiers~ RET render_missing = refusal END
	END
END

// Ligne « nom : valeur » à la forme « soi » (ancien opcode_self_332).
DEFINE_PATCH_MACRO ad_op_332_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~332~)
	FOR (damage_mod_id = 0; damage_mod_id < fx_count; ++damage_mod_id) BEGIN
		PATCH_IF $fx_opcode(~%damage_mod_id%~) == 332 AND NOT $fx_consumed(~%damage_mod_id%~) BEGIN
			SET damage_mod_type = $fx_parameter2(~%damage_mod_id%~)
			SET damage_mod_value = $fx_parameter1(~%damage_mod_id%~)
			SET line_fx = damage_mod_id
			LPM ad_application_form
			PATCH_IF line_form == 0 BEGIN
				LPF ad_tra INT_VAR tra_id = 23320000 + damage_mod_type tra_block_start = 23320000 tra_block_size = 11 RET name = text END // ~Dégâts de feu~ (@23320001)
				LPF ad_signed_value INT_VAR value = damage_mod_value RET value = text END
				SPRINT value @1200003 // ~%value%%PERCENT%~
				SPRINT line_text @1200000 // ~%name%%AD_COLON%%value%~
				LPM ad_effect_line
			END
			ELSE BEGIN
				LPF ad_refusal INT_VAR fx_id = damage_mod_id STR_VAR reason = ~not_implemented:opcode332:form%line_form%~ message = ~no text for form %line_form%~ RET render_late_missing = refusal END
			END
		END
	END
END
