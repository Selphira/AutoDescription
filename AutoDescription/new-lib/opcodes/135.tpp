// Opcode 135 (Graphics: Polymorph into Specific) : métamorphose en la créature resource
// (parameter2 0) ou déguisement (sinon) : « Métamorphose en Ogre » ; une créature sans nom est
// « créature sans nom ». Code commun dans new-lib/opcodes/states.tpp. Une arme créée (111) qui
// métamorphose est remplacée par sa métamorphose (new-lib/opcodes/111.tpp, fx_from_111) ; avec
// AD_ENABLE_SHRINKAGE, la métamorphose retire le retour à la forme naturelle (ad_group_polymorph,
// new-lib/groups.tpp).

// Comme l'ancien opcode_111_replace, une métamorphose venue d'un 111 est écartée si sa portée en a
// déjà une, du fichier ou d'un 111 précédent, de même timing et de même durée. Refus : ressource vide
// (retour à la forme naturelle : l'ancien moteur n'en écrit pas la durée).
DEFINE_PATCH_MACRO ad_op_135_support BEGIN
	FOR (polymorph_id = 0; polymorph_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++polymorph_id) BEGIN
		PATCH_IF $fx_opcode(~%polymorph_id%~) == 135 AND $fx_from_111(~%polymorph_id%~) AND NOT $fx_consumed(~%polymorph_id%~) BEGIN
			SPRINT polymorph_scope $fx_scope(~%polymorph_id%~)
			SET drop_id = 0 - 1
			FOR (polymorph_other = 0; polymorph_other < fx_count; ++polymorph_other) BEGIN
				SPRINT polymorph_other_scope $fx_scope(~%polymorph_other%~)
				PATCH_IF $fx_opcode(~%polymorph_other%~) == 135 AND NOT $fx_consumed(~%polymorph_other%~)
						AND (NOT $fx_from_111(~%polymorph_other%~) OR polymorph_other < polymorph_id)
						AND (~%polymorph_other_scope%~ STRING_EQUAL ~%polymorph_scope%~)
						AND $fx_timing(~%polymorph_other%~) == $fx_timing(~%polymorph_id%~)
						AND $fx_duration(~%polymorph_other%~) == $fx_duration(~%polymorph_id%~) BEGIN
					SET drop_id = polymorph_id
				END
			END
			PATCH_IF drop_id == polymorph_id BEGIN
				LPM ad_application_drop
			END
		END
	END
	FOR (polymorph_id = 0; polymorph_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++polymorph_id) BEGIN
		PATCH_IF $fx_opcode(~%polymorph_id%~) == 135 AND NOT $fx_consumed(~%polymorph_id%~) BEGIN
			SPRINT polymorph_resref $fx_resource(~%polymorph_id%~)
			LPF ad_creature_info STR_VAR resref = ~%polymorph_resref%~ RET polymorph_name = name END
			PATCH_IF ~%polymorph_name%~ STRING_EQUAL ~~ BEGIN
				SPRINT polymorph_name @21350000 // ~créature sans nom~
			END
			SPRINT $fx_creature_name(~%polymorph_id%~) ~%polymorph_name%~
			PATCH_IF ~%polymorph_resref%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode135:natural_form~
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
