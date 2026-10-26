// Opcode 214 (Spell Effect: Select Spell) : « Permet de lancer un sort du livre de sorts » ; parameter2
// 0 : sorts listés par le 2DA resource (colonne ResRef), « Permet de lancer un sort de cette liste : »
// suivi de leurs noms ; 1 et 2 : sorts profanes connus (IESDP). Code commun dans
// new-lib/opcodes/states.tpp ; pas de forme « cible » probable, comme dans l'ancien moteur.
// fx_select_spells : liste écrite des sorts.

// 2DA absent : effet écarté sans rien écrire, erreur journalisée.
// Refus : sort de la liste absent (l'ancien moteur le saute et l'écrit dans son journal
// d'erreurs) ; liste sans aucun sort nommé (l'ancien moteur n'écrit rien).
DEFINE_PATCH_MACRO ad_op_214_support BEGIN
	PHP_EACH fx_ids_214 AS _ => select_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND $fx_parameter2(~%select_id%~) == 0 BEGIN
			SPRINT select_table $fx_resource(~%select_id%~)
			SPRINT select_spells ~~
			SPRINT select_missing ~~
			PATCH_IF NOT FILE_EXISTS_IN_GAME ~%select_table%.2da~ BEGIN
				SET drop_id = select_id
				SPRINT ignored_reason ~file_error:opcode214:table~
				SPRINT ignored_message ~missing table %select_table%.2da~
				LPM ad_application_drop
			END
			ELSE BEGIN
				INNER_PATCH_FILE ~%select_table%.2da~ BEGIN
					COUNT_2DA_ROWS 3 select_rows
					FOR (select_row = 0; select_row < select_rows; ++select_row) BEGIN
						READ_2DA_ENTRY select_row 1 3 select_resref
						PATCH_IF FILE_EXISTS_IN_GAME ~%select_resref%.spl~ BEGIN
							LPF ad_spell_name STR_VAR resref = ~%select_resref%~ RET select_name = name END
							PATCH_IF NOT (~%select_name%~ STRING_EQUAL ~~) BEGIN
								SPRINT select_spells ~%select_spells%%CRLF%  * %select_name%~
							END
						END
						ELSE BEGIN
							SPRINT select_missing ~%select_resref%~
						END
					END
				END
				PATCH_IF NOT (~%select_missing%~ STRING_EQUAL ~~) BEGIN
					LPF ad_refusal INT_VAR fx_id = select_id STR_VAR reason = ~file_error:opcode214:spell~ message = ~spell %select_missing%.spl of table %select_table%.2da not found~ RET render_missing = refusal END
				END
				ELSE PATCH_IF ~%select_spells%~ STRING_EQUAL ~~ BEGIN
					LPF ad_refusal INT_VAR fx_id = select_id STR_VAR reason = ~not_implemented:opcode214:no_spells~ message = ~no named spell in table %select_table%.2da~ RET render_missing = refusal END
				END
			END
			SPRINT $fx_select_spells(~%select_id%~) ~%select_spells%~
		END
	END
END

DEFINE_PATCH_MACRO ad_op_214_lines BEGIN
	SET state_opcode = 214
	SPRINT state_variant_macro ~ad_op_214_variant~
	LPM ad_state_lines
END

// Variante 1 : sorts de la liste (spells).
DEFINE_PATCH_MACRO ad_op_214_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0
	PATCH_IF state_variant BEGIN
		SPRINT spells $fx_select_spells(~%line_fx%~)
	END
END
