// Opcode 120 (Protection: from Weapons) : immunise contre les armes du type parameter2 (0 armes
// enchantées jusqu'au bonus parameter1, 1 magiques, 2 non magiques…, liste @21200010) :
// « Immunité contre les armes non-magiques » ; code commun dans new-lib/opcodes/states.tpp.
// Sur EE avec AD_ENABLE_SHRINKAGE, seules les immunités aux armes enchantées du bonus le plus élevé
// de leur bloc restent (ancien opcode_120_group).

// Type inconnu : écarté par l'ancien opcode_120_is_valid.
DEFINE_PATCH_MACRO ad_op_120_support BEGIN
	FOR (weapon_id = 0; weapon_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++weapon_id) BEGIN
		PATCH_IF $fx_opcode(~%weapon_id%~) == 120 AND ($fx_parameter2(~%weapon_id%~) < 0 OR $fx_parameter2(~%weapon_id%~) > 11) BEGIN
			SPRINT render_missing ~not_implemented:opcode120:invalid~
		END
	END
END

DEFINE_PATCH_MACRO ad_op_120_lines BEGIN
	PATCH_IF IS_EE AND AD_ENABLE_SHRINKAGE BEGIN
		FOR (weapon_id = 0; weapon_id < fx_count; ++weapon_id) BEGIN
			PATCH_IF $fx_opcode(~%weapon_id%~) == 120 AND $fx_parameter2(~%weapon_id%~) == 0 AND NOT $fx_consumed(~%weapon_id%~) BEGIN
				SPRINT weapon_scope $fx_scope(~%weapon_id%~)
				FOR (weapon_other = 0; weapon_other < fx_count; ++weapon_other) BEGIN
					SPRINT weapon_other_scope $fx_scope(~%weapon_other%~)
					PATCH_IF $fx_opcode(~%weapon_other%~) == 120 AND $fx_parameter2(~%weapon_other%~) == 0
							AND (~%weapon_other_scope%~ STRING_EQUAL ~%weapon_scope%~)
							AND $fx_parameter1(~%weapon_other%~) > $fx_parameter1(~%weapon_id%~) BEGIN
						SET $fx_consumed(~%weapon_id%~) = 1
					END
				END
			END
		END
	END
	SET state_opcode = 120
	SPRINT state_variant_macro ~ad_op_120_variant~
	LPM ad_state_lines
END

// Variante 0 armes enchantées (« +2 et inférieures »), 1 autres types.
DEFINE_PATCH_MACRO ad_op_120_variant BEGIN
	SET weapon_type = $fx_parameter2(~%line_fx%~)
	LPF ad_tra INT_VAR tra_id = 21200010 + weapon_type tra_block_start = 21200010 tra_block_size = 12 RET weaponType = text END // ~armes non-magiques~
	SET state_variant = weapon_type == 0 ? 0 : 1
	PATCH_IF weapon_type == 0 BEGIN
		LPF ad_signed_value INT_VAR value = $fx_parameter1(~%line_fx%~) RET enchantment = text END
	END
END
