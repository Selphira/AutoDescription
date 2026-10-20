// Opcode 216 (Spell Effect: Level Drain) : « Draine 2 niveaux à la cible » ; parameter1 0 inhibe le
// passage de niveau, -1 injecte un niveau ; code commun dans new-lib/opcodes/states.tpp.

// Plusieurs niveaux injectés : l'ancien moteur lit une chaîne absente (BUG-025).
DEFINE_PATCH_MACRO ad_op_216_support BEGIN
	FOR (state_id = 0; state_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++state_id) BEGIN
		PATCH_IF $fx_opcode(~%state_id%~) == 216 AND $fx_parameter1(~%state_id%~) < 0 - 1 BEGIN
			SPRINT render_missing ~not_implemented:opcode216:levels_added~
		END
	END
END

DEFINE_PATCH_MACRO ad_op_216_lines BEGIN
	SET state_opcode = 216
	SPRINT state_variant_macro ~ad_op_216_variant~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_216_variant BEGIN
	SET amount = $fx_parameter1(~%line_fx%~)
	SET state_variant = amount > 1 ? 1 : (amount == 0 ? 2 : (amount < 0 ? 3 : 0))
END
