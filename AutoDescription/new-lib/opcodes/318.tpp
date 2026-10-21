// Opcode 318 (Protection from Resource, EE) : sur la ressource elle-même, exception de cible des
// effets lus après lui (« Inefficace contre les morts-vivants ») ; code commun dans
// new-lib/opcodes/target_exceptions.tpp.

DEFINE_PATCH_MACRO ad_op_318_support BEGIN
	SET exception_opcode = 318
	LPM ad_target_exception_support
END

DEFINE_PATCH_MACRO ad_op_318_lines BEGIN
	SET exception_opcode = 318
	LPM ad_target_exception_lines
END
