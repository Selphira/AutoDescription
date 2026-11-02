// Opcode 264 (Spell Effect: Drop Weapons in Panic) : fait lâcher un objet, une arme des emplacements
// rapides si parameter2 vaut 1, sinon le premier objet de l'inventaire (IESDP) : « Fait abandonner à la
// cible une arme équipée » ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_264_support BEGIN END

DEFINE_PATCH_MACRO ad_op_264_lines BEGIN
	SET state_opcode = 264
	SPRINT state_variant_macro ~ad_op_264_object~
	LPM ad_state_lines
END

DEFINE_PATCH_MACRO ad_op_264_object BEGIN
	PATCH_IF $fx_parameter2(~%line_fx%~) == 1 BEGIN
		SPRINT objectType @22640011 // ~une arme équipée~
	END
	ELSE BEGIN
		SPRINT objectType @22640010 // ~un objet de son inventaire~
	END
END
