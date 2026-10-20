// Opcode 135 (Graphics: Polymorph into Specific) : métamorphose en la créature resource
// (parameter2 0) ou déguisement (sinon) : « Métamorphose en Ogre » ; une créature sans nom est
// « créature sans nom ». Code commun dans new-lib/opcodes/states.tpp.

// Refus : ressource vide (retour à la forme naturelle : l'ancien moteur n'en écrit pas la durée) ;
// objet qui a aussi des effets 146 ou 171 (l'ancien opcode_135_post_group en retire certains).
DEFINE_PATCH_MACRO ad_op_135_support BEGIN
	SET polymorph_group = 0
	FOR (polymorph_id = 0; polymorph_id < fx_count; ++polymorph_id) BEGIN
		SET polymorph_opcode = $fx_opcode(~%polymorph_id%~)
		SET polymorph_group = polymorph_group OR polymorph_opcode == 146 OR polymorph_opcode == 171
	END
	FOR (polymorph_id = 0; polymorph_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++polymorph_id) BEGIN
		PATCH_IF $fx_opcode(~%polymorph_id%~) == 135 BEGIN
			SPRINT polymorph_resref $fx_resource(~%polymorph_id%~)
			LPF ad_creature_info STR_VAR resref = ~%polymorph_resref%~ RET polymorph_name = name END
			PATCH_IF ~%polymorph_name%~ STRING_EQUAL ~~ BEGIN
				SPRINT polymorph_name @21350000 // ~créature sans nom~
			END
			SPRINT $fx_creature_name(~%polymorph_id%~) ~%polymorph_name%~
			PATCH_IF ~%polymorph_resref%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode135:natural_form~
			END
			ELSE PATCH_IF polymorph_group BEGIN
				SPRINT render_missing ~not_implemented:opcode135:polymorph_group~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_135_lines BEGIN
	SET state_opcode = 135
	SPRINT state_variant_macro ~ad_op_135_variant~
	LPM ad_state_lines
END

// Variante 0 : métamorphose, 1 : déguisement.
DEFINE_PATCH_MACRO ad_op_135_variant BEGIN
	SET state_variant = $fx_parameter2(~%line_fx%~) == 0 ? 0 : 1
	SPRINT creatureName $fx_creature_name(~%line_fx%~)
END
