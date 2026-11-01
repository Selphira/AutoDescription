// Opcode 279 (Button: Enable Button) : bouton parameter2 réactivé, « Permet l'utilisation des sorts » ;
// le jeu ne retire que les effets 144 qui le désactivent (IESDP). Code commun dans
// new-lib/opcodes/buttons.tpp.

DEFINE_PATCH_MACRO ad_op_279_support BEGIN
	SET button_opcode = 279
	LPM ad_button_support
END

DEFINE_PATCH_MACRO ad_op_279_lines BEGIN
	SET button_opcode = 279
	SET button_action_tra = 22790100 // ~Permet~
	LPM ad_button_lines
END
