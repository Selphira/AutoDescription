// Opcode 259 (Protection: Spell Trap (by Power Level, decrementing)) : jusqu'à parameter1 niveaux de
// sorts du niveau parameter2 absorbés, chacun rendant un sort profane de son niveau (IESDP). Avec
// AD_ENABLE_SHRINKAGE, les effets semblables au niveau près n'en font qu'un (ancien opcode_259_group) :
// « Absorbe jusqu'à 30 niveaux de sorts de niveau 9 ou inférieur » ; pas de forme « cible », comme
// dans l'ancien moteur. fx_trap_anchor : effet qui écrit la ligne de son groupe, fx_trap_level :
// niveau le plus haut du groupe.

// Refus : niveau hors de 0-9 et total inférieur à 1 (ancien opcode_259_is_valid) ; niveau 0, sans
// nom ; sur EE, sort lancé à la fin de l'effet qui a un nom (la ressource, sinon le sort
// <ressource>B : l'ancien side_spell ajoute « puis lance « … » ») ; effet probable, que l'ancien
// regroupement traite à part ; niveau au-delà de 1 hors d'un groupe des niveaux 1 à N : l'ancien
// moteur l'écrit « de niveau N ou inférieur », alors qu'un effet ne piège que son niveau.
DEFINE_PATCH_MACRO ad_op_259_support BEGIN
	SPRINT trap_own_spell ~~
	PATCH_IF IS_EE AND STRING_LENGTH ~%ctx_resource%~ <= 7 BEGIN
		LPF ad_spell_name STR_VAR resref = EVAL ~%ctx_resource%B~ RET trap_own_spell = name END
	END
	PHP_EACH fx_ids_259 AS _ => trap_id BEGIN
		SET $fx_trap_anchor(~%trap_id%~) = trap_id
		SET $fx_trap_level(~%trap_id%~) = $fx_parameter2(~%trap_id%~)
	END
	PHP_EACH fx_ids_259 AS _ => trap_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET trap_level = $fx_parameter2(~%trap_id%~)
			SPRINT trap_resref $fx_resource(~%trap_id%~)
			SPRINT trap_spell ~%trap_own_spell%~
			PATCH_IF NOT (~%trap_resref%~ STRING_EQUAL ~~) BEGIN
				LPF ad_spell_name STR_VAR resref = ~%trap_resref%~ RET trap_spell = name END
			END
			PATCH_IF trap_level < 0 OR trap_level > 9 BEGIN
				LPF ad_refusal INT_VAR fx_id = trap_id STR_VAR reason = ~file_error:opcode259:level~ message = ~spell level %trap_level% (expected 0-9)~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_parameter1(~%trap_id%~) < 1 BEGIN
				LPF ad_refusal INT_VAR fx_id = trap_id STR_VAR reason = ~file_error:opcode259:amount~ message = ~amount of 0 or less~ RET render_missing = refusal END
			END
			ELSE PATCH_IF trap_level == 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = trap_id STR_VAR reason = ~not_implemented:opcode259:level0~ message = ~spell level 0~ RET render_missing = refusal END
			END
			ELSE PATCH_IF IS_EE AND NOT (~%trap_spell%~ STRING_EQUAL ~~) BEGIN
				LPF ad_refusal INT_VAR fx_id = trap_id STR_VAR reason = ~not_implemented:opcode259:spell~ message = ~spell cast when the effect ends~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_probability(~%trap_id%~) < 100 AND NOT support_header_only BEGIN
				LPF ad_refusal INT_VAR fx_id = trap_id STR_VAR reason = ~not_implemented:opcode259:probability~ message = ~probable spell trap~ RET render_missing = refusal END
			END
			ELSE PATCH_IF $fx_trap_anchor(~%trap_id%~) == trap_id AND NOT support_header_only BEGIN
				LPM ad_op_259_group
			END
		END
	END
END

// Effets semblables au niveau près réunis sous trap_id, s'ils couvrent les niveaux 1 à N.
DEFINE_PATCH_MACRO ad_op_259_group BEGIN
	SET trap_levels = 1 BLSL (trap_level - 1)
	SET trap_max = trap_level
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		SET same_id = trap_id
		SET same_ignored = AD_SAME_PARAMETER2
		PHP_EACH fx_ids_259 AS _ => trap_other BEGIN
			SET trap_other_level = $fx_parameter2(~%trap_other%~)
			PATCH_IF trap_other != trap_id AND $fx_trap_anchor(~%trap_other%~) == trap_other AND trap_other_level >= 1 AND trap_other_level <= 9 BEGIN
				SET same_other = trap_other
				LPM ad_fx_same_fields
				PATCH_IF fx_same BEGIN
					SET $fx_trap_anchor(~%trap_other%~) = trap_id
					SET trap_levels = trap_levels BOR (1 BLSL (trap_other_level - 1))
					SET trap_max = trap_other_level > trap_max ? trap_other_level : trap_max
				END
			END
		END
	END
	SET $fx_trap_level(~%trap_id%~) = trap_max
	PATCH_IF trap_levels != (1 BLSL trap_max) - 1 BEGIN
		LPF ad_refusal INT_VAR fx_id = trap_id STR_VAR reason = ~not_implemented:opcode259:levels~ message = ~spell levels other than 1 to %trap_max% (mask %trap_levels%)~ RET render_missing = refusal END
	END
END

DEFINE_PATCH_MACRO ad_op_259_lines BEGIN
	SPRINT line_section ~equipped~
	SET line_sort = $AD_OPCODE_SORT(~259~)
	PHP_EACH fx_ids_259 AS _ => trap_id BEGIN
		PATCH_IF NOT $fx_consumed(~%trap_id%~) AND $fx_trap_anchor(~%trap_id%~) == trap_id BEGIN
			SET amount = $fx_parameter1(~%trap_id%~)
			SET spellLevel = $fx_trap_level(~%trap_id%~)
			SET line_fx = trap_id
			SET line_phrase = 22590100 // ~Absorbe jusqu'à %amount% niveaux de sorts de niveau %spellLevel% ou inférieur~
			LPM ad_effect_line
		END
	END
END
