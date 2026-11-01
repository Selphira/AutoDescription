// Opcode 144 (Button: Disable Button) : bouton parameter2 désactivé, « Empêche l'utilisation des
// compétences de roublard » ; code commun dans new-lib/opcodes/buttons.tpp.

DEFINE_PATCH_MACRO ad_op_144_support BEGIN
	SET button_opcode = 144
	LPM ad_button_support
END

DEFINE_PATCH_MACRO ad_op_144_lines BEGIN
	SET button_opcode = 144
	SET button_action_tra = 21440100 // ~Empêche~
	LPM ad_button_lines
END
