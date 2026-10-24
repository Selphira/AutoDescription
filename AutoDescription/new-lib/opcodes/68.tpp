// Opcode 68 (Summon: Unsummon Creature) : « Renvoie la cible s'il s'agit d'une créature invoquée » ;
// pas de forme « soi » probable, comme dans l'ancien moteur ; code commun dans new-lib/opcodes/states.tpp.

DEFINE_PATCH_MACRO ad_op_68_support BEGIN END

DEFINE_PATCH_MACRO ad_op_68_lines BEGIN
	SET state_opcode = 68
	SPRINT state_variant_macro ~~
	LPM ad_state_lines
END
