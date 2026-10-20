// Opcode 58 (Cure: Dispellable Effects) : « Dissipation de la magie sur la cible » ; parameter2, octet
// de poids faible : 0 dissipation inéluctable, 1 selon le niveau du lanceur, 2 et plus selon le
// niveau parameter1 ; sur EE, mot de poids fort : 0 dissipe toujours les armes invoquées, 2 selon le
// niveau, une autre valeur ne les affecte pas. Avec AD_ENABLE_SHRINKAGE, la dissipation absorbe les
// guérisons de la débilité mentale et de la surdité qu'elle implique (ad_group_dispel_cures,
// new-lib/groups.tpp). Code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_58_support BEGIN END

DEFINE_PATCH_MACRO ad_op_58_lines BEGIN
	SET state_opcode = 58
	SPRINT state_variant_macro ~ad_op_58_variant~
	LPM ad_state_lines
END

// Précisions de l'ancien opcode_58_common, entre parenthèses après la phrase.
DEFINE_PATCH_MACRO ad_op_58_variant BEGIN
	SET dispel_type = $fx_parameter2(~%line_fx%~) BAND 255
	SET dispel_weapons = $fx_parameter2(~%line_fx%~) BLSR 16
	SET state_variant = dispel_type == 0
	PATCH_IF dispel_type >= 2 BEGIN
		SET castingLevel = $fx_parameter1(~%line_fx%~)
		SPRINT dispel_note @20580001 // ~comme un lanceur de sorts de niveau %castingLevel%~
		SPRINT line_suffix ~(%dispel_note%)~
	END
	PATCH_IF IS_EE AND ((dispel_weapons == 0 AND dispel_type != 0) OR (dispel_weapons != 0 AND dispel_weapons != 2)) BEGIN
		PATCH_IF dispel_weapons == 0 BEGIN
			SPRINT dispel_note @20580003 // ~les armes invoquées sont toujours dissipées~
		END
		ELSE BEGIN
			SPRINT dispel_note @20580002 // ~les armes invoquées ne sont pas affectées~
		END
		PATCH_IF ~%line_suffix%~ STRING_EQUAL ~~ BEGIN
			SPRINT line_suffix ~(%dispel_note%)~
		END
		ELSE BEGIN
			SPRINT line_suffix ~%line_suffix% (%dispel_note%)~
		END
	END
END
