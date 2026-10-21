// Opcode 344 (Enchantment vs. creature type, EE) : « Niveau d'enchantement : +3 contre les
// morts-vivants » ; code commun dans new-lib/opcodes/versus_modifiers.tpp. Un 344 d'un EFF (emplacement
// et type d'arme dans parameter3 et parameter4) n'est pas remplacé (AD_OPCODES_EFF_FIELDS).

DEFINE_PATCH_MACRO ad_op_344_support BEGIN
	SET versus_opcode = 344
	LPM ad_versus_modifier_support
END

DEFINE_PATCH_MACRO ad_op_344_lines BEGIN
	SET versus_opcode = 344
	SET versus_name_tra = 23440000 // ~Niveau d'enchantement~
	LPM ad_versus_modifier_lines
END
