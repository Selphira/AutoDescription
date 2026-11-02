// Opcode 300 (Spell Effect: NPCBump) : fixe la statistique NPC_BUMP à parameter2 (IESDP) ; l'ancien
// moteur nomme les valeurs 1 à 3 : « Permet au porteur de bousculer les créatures sur son passage »
// (1), « d'être inébranlable » (2), les deux (3) ; code commun dans new-lib/opcodes/states.tpp. Il n'a
// pas de phrase pour un effet probable : refusé (phrase absente).

// Autre valeur, dont 0 qui suspend l'effet : pas de ligne, comme l'ancien moteur, journalisé.
DEFINE_PATCH_MACRO ad_op_300_support BEGIN
	PHP_EACH fx_ids_300 AS _ => bump_id BEGIN
		SET bump_value = $fx_parameter2(~%bump_id%~)
		PATCH_IF (bump_value < 1 OR bump_value > 3) AND NOT $fx_dropped(~%bump_id%~) AND NOT support_header_only BEGIN
			SET ignored_fx = bump_id
			SPRINT ignored_reason ~not_implemented:opcode300:value~
			SPRINT ignored_message ~value %bump_value% (parameter2) has no sentence (expected 1-3)~
			LPM ad_log_ignored
		END
	END
END

DEFINE_PATCH_MACRO ad_op_300_lines BEGIN
	PHP_EACH fx_ids_300 AS _ => bump_id BEGIN
		SET bump_value = $fx_parameter2(~%bump_id%~)
		PATCH_IF bump_value < 1 OR bump_value > 3 BEGIN
			SET $fx_consumed(~%bump_id%~) = 1
		END
	END
	SET state_opcode = 300
	SPRINT state_variant_macro ~ad_op_300_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_300_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) - 1
END
