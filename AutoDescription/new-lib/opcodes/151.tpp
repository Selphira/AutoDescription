// Opcode 151 (Summon: Replace Creature) : remplace la cible par la créature resource. parameter2
// règle le sort de la cible (IESDP) : 0 retirée sans bruit, 1 et 2 tuée, 3 laissée en place (la
// créature est alors invoquée à côté) : « Tue et remplace la cible par Tanar'ri ». Code commun dans
// new-lib/opcodes/states.tpp.

// Refus : créature absente (aucun remplacement en jeu ; l'ancien opcode_151_is_valid écarte l'effet,
// erreur journalisée) ; créature sans nom.
DEFINE_PATCH_MACRO ad_op_151_support BEGIN
	FOR (replace_id = 0; replace_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++replace_id) BEGIN
		PATCH_IF $fx_opcode(~%replace_id%~) == 151 AND NOT $fx_consumed(~%replace_id%~) BEGIN
			SPRINT replace_resref $fx_resource(~%replace_id%~)
			PATCH_IF ~%replace_resref%~ STRING_EQUAL ~~ OR NOT FILE_EXISTS_IN_GAME ~%replace_resref%.cre~ BEGIN
				LPF ad_refusal INT_VAR fx_id = replace_id STR_VAR reason = ~file_error:opcode151:missing_creature~ message = ~creature %replace_resref%.CRE does not exist~ RET render_missing = refusal END
			END
			ELSE BEGIN
				LPF ad_creature_info STR_VAR resref = ~%replace_resref%~ RET replace_name = name END
				PATCH_IF ~%replace_name%~ STRING_EQUAL ~~ BEGIN
					LPF ad_refusal INT_VAR fx_id = replace_id STR_VAR reason = ~not_implemented:opcode151:no_name~ message = ~creature %replace_resref%.CRE has no name~ RET render_missing = refusal END
				END
				SPRINT $fx_creature_name(~%replace_id%~) ~%replace_name%~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_151_lines BEGIN
	SET state_opcode = 151
	SPRINT state_variant_macro ~ad_op_151_variant~
	LPM ad_state_lines
END

// Variante 0 : remplacement, 1 : la cible est tuée, 2 : invocation sur la cible.
DEFINE_PATCH_MACRO ad_op_151_variant BEGIN
	SET replace_mode = $fx_parameter2(~%line_fx%~)
	SET state_variant = replace_mode == 0 ? 0 : ((replace_mode == 1 OR replace_mode == 2) ? 1 : 2)
	SPRINT creatureName $fx_creature_name(~%line_fx%~)
END
