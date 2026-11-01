// Opcode 361 (Cast spell on critical miss, EE) : sort lancé à chaque échec critique (IESDP : sur
// l'attaquant) : « À chaque échec critique provoqué avec cette arme ; Inflige 1d4 points de dégâts
// d'électricité au porteur » ; code commun dans new-lib/opcodes/event_spells.tpp.

DEFINE_PATCH_MACRO ad_op_361_support BEGIN
	SET event_opcode = 361
	SET event_weapon = 1
	LPM ad_event_spell_support
END

DEFINE_PATCH_MACRO ad_op_361_lines BEGIN
	SET event_opcode = 361
	SET event_weapon = 1
	SET event_condition_tra = 23610001 // ~À chaque échec critique~
	LPM ad_event_spell_lines
END
