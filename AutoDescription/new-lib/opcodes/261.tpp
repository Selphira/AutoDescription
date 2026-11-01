// Opcode 261 (Spell: Restore Lost Spells) : « Se remémore 1 sort divin de niveau 5 ou inférieur »,
// type selon parameter2 (0 profane, 1 divin), niveau parameter1 ramené à 9 ou 7 ; « de niveau 1 »
// pour le premier niveau (ancien opcode_261_common) ; plusieurs niveaux réunis par
// ad_group_restored_spells (new-lib/groups.tpp) ; niveau tiré au sort réuni : « de niveau 1 à 8 ou
// inférieur » (new-lib/opcodes/value_ranges.tpp). Code commun dans new-lib/opcodes/states.tpp.

// Refus : type autre que 0 ou 1 et niveau négatif (écartés par l'ancien opcode_261_is_valid).
DEFINE_PATCH_MACRO ad_op_261_support BEGIN
	PHP_EACH fx_ids_261 AS _ => restore_id BEGIN
		SET $fx_restore_both(~%restore_id%~) = 0
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET restore_type = $fx_parameter2(~%restore_id%~)
			PATCH_IF (restore_type != 0 AND restore_type != 1) OR $fx_parameter1(~%restore_id%~) < 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = restore_id STR_VAR reason = ~file_error:opcode261:invalid~ message = ~spell type %restore_type% (expected 0 or 1) or negative spell level~ RET render_missing = refusal END
			END
		END
	END
	SET range_opcode = 261
	SPRINT range_eligible_macro ~ad_op_261_range_eligible~
	LPM ad_value_range_support
END

// Un niveau au-delà du maximum du type de sort (ramené à 9 ou 7) n'est pas réuni (ancien
// opcode_261_range_eligible).
DEFINE_PATCH_MACRO ad_op_261_range_eligible BEGIN
	SET range_type = $fx_parameter2(~%range_id%~)
	SET range_eligible = (range_type == 0 AND $fx_parameter1(~%range_id%~) <= 9) OR (range_type == 1 AND $fx_parameter1(~%range_id%~) <= 7)
END

DEFINE_PATCH_MACRO ad_op_261_lines BEGIN
	SET state_opcode = 261
	SPRINT state_variant_macro ~ad_op_261_variant~
	LPM ad_state_lines
END

// Variante 0 : jusqu'à un niveau, 1 : premier niveau.
DEFINE_PATCH_MACRO ad_op_261_variant BEGIN
	SET spellLevel = $fx_parameter1(~%line_fx%~)
	LPM ad_op_261_type
	PATCH_IF $fx_parameter2(~%line_fx%~) == 0 BEGIN
		SET spellLevel = spellLevel > 9 ? 9 : spellLevel
	END
	ELSE BEGIN
		SET spellLevel = spellLevel > 7 ? 7 : spellLevel
	END
	SET state_variant = spellLevel == 1
	PATCH_IF $fx_range_max(~%line_fx%~) > 0 BEGIN
		SET amountMin = $fx_range_min(~%line_fx%~)
		SET amountMax = $fx_range_max(~%line_fx%~)
		SPRINT spellLevel @22610013 // ~%amountMin% à %amountMax%~
		SET state_variant = 0
	END
END

// Type « profane ou divin » : restaurations des deux types réunies (fx_restore_both,
// ad_group_restored_spells).
DEFINE_PATCH_MACRO ad_op_261_type BEGIN
	PATCH_IF $fx_restore_both(~%line_fx%~) BEGIN
		SPRINT spellType @22610012 // ~profane ou divin~
	END
	ELSE PATCH_IF $fx_parameter2(~%line_fx%~) == 0 BEGIN
		SPRINT spellType @22610010 // ~profane~
	END
	ELSE BEGIN
		SPRINT spellType @22610011 // ~divin~
	END
END
