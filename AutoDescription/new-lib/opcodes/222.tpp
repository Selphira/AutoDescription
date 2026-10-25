// Opcode 222 (Spell Effect: Teleport Field) : « Téléporte aléatoirement la cible dans un rayon de
// 5 mètres » ; parameter1 = portée en unités de rayon de projectile, 16 par pied (IESDP) ; code commun dans new-lib/opcodes/states.tpp.

// Refus : portée d'un mètre ou moins (ad_distance_text).
DEFINE_PATCH_MACRO ad_op_222_support BEGIN
	PHP_EACH fx_ids_222 AS _ => field_id BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			SET field_range = $fx_parameter1(~%field_id%~)
			LPF ad_distance_text INT_VAR feet = field_range / 16 RET field_text = text END
			SPRINT $fx_field_range(~%field_id%~) ~%field_text%~
			PATCH_IF ~%field_text%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = field_id STR_VAR reason = ~not_implemented:opcode222:range~ message = ~range %field_range% (16 per foot) of one meter or less~ RET render_missing = refusal END
			END
		END
	END
END

DEFINE_PATCH_MACRO ad_op_222_lines BEGIN
	SET state_opcode = 222
	SPRINT state_variant_macro ~ad_op_222_variant~
	LPM ad_state_lines
END

// Portée (range).
DEFINE_PATCH_MACRO ad_op_222_variant BEGIN
	SPRINT range $fx_field_range(~%line_fx%~)
END
