// Opcode 205 (Spell: Protection from Spell (Secondary Type)) : immunise contre les sorts du type
// secondaire parameter2 (msectype.ids, ad_spell_secondary_type_name, new-lib/resources.tpp) :
// « Immunité aux sorts de type Dégâts offensifs ». Avec AD_ENABLE_SHRINKAGE, les immunités à un sort
// (opcode 206) du même type secondaire sont absorbées (ad_group_secondary_type_spells,
// new-lib/groups.tpp).

// Refus : type sans nom (l'ancien moteur n'écrit rien) ou ajouté par un mod (au-delà de 13).
DEFINE_PATCH_MACRO ad_op_205_support BEGIN
	FOR (sectype_id = 0; sectype_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++sectype_id) BEGIN
		PATCH_IF $fx_opcode(~%sectype_id%~) == 205 BEGIN
			LPF ad_spell_secondary_type_name INT_VAR secondary_type = $fx_parameter2(~%sectype_id%~) RET sectype_name = name END
			SPRINT $fx_sectype_name(~%sectype_id%~) ~%sectype_name%~
			PATCH_IF ~%sectype_name%~ STRING_EQUAL ~~ BEGIN
				SPRINT render_missing ~not_implemented:opcode205:no_name~
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_205_lines BEGIN
	SET state_opcode = 205
	SPRINT state_variant_macro ~ad_op_205_name~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_205_name BEGIN
	SPRINT spellSecondaryTypeName $fx_sectype_name(~%line_fx%~)
END
