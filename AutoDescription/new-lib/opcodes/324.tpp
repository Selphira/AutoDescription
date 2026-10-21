// Opcode 324 (Protection: Immunity to Resource and Message) : sur la ressource elle-même, exception
// de cible des effets lus après lui (« Inefficace contre les morts-vivants ») ; code commun dans
// new-lib/opcodes/target_exceptions.tpp.

DEFINE_PATCH_MACRO ad_op_324_support BEGIN
	SET exception_opcode = 324
	LPM ad_target_exception_support
END

DEFINE_PATCH_MACRO ad_op_324_lines BEGIN
	SET exception_opcode = 324
	LPM ad_target_exception_lines
END
