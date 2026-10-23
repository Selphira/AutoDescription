// Opcode 177 (Use EFF File) : applique l'effet du fichier EFF resource. Comme l'ancien
// opcode_177_replace, l'effet 177 est remplacé dès la lecture (ad_fx_substitute_177, appelée par
// ad_fx_load_block, new-lib/effects.tpp) par celui de l'EFF, qui est ensuite décrit comme les autres
// effets de son opcode : opcode, puissance, paramètres (parameter3 compris, fx_parameter3 ; parameter4,
// resource2 et resource3 pour les journaux), ressource,
// résistance et special de l'EFF ;
// cible, timing et durée du 177 ; dés du 177 s'ils donnent des niveaux (colonne DICE de l'opcode de
// l'EFF), de l'EFF sinon ; jet de sauvegarde de l'EFF, ou du 177 si l'EFF n'en a pas, ou les deux
// types réunis à bonus égal ; probabilité de l'EFF, ou du 177 si celle de l'EFF est certaine.
// L'effet remplacé est marqué fx_external : les regroupements ne le réunissent pas à un effet du
// fichier, comme l'ancien moteur qui compare isExternal. Il compte pour son opcode et pour le 177
// (fx_opcode_count), pour que les macros ci-dessous soient appelées. Le type de créature
// visé (parameter2 : fichier IDS, 9 kit.ids sur EE ; parameter1 : valeur, 0 sans filtre) devient fx_versus_file et
// fx_versus_value (et fx_versus_inner_file, fx_versus_inner_value pour celui d'un 177 imbriqué, qui le
// restreint), écrits « contre les X » ou « (uniquement pour les X) » par
// ad_application_versus (new-lib/application.tpp).

// Remplace l'effet fx_id (opcode 177) par celui de son EFF, ou y laisse la raison de son refus
// (fx_substitution_error, expliquée en anglais pour les journaux dans fx_substitution_message) : drop pour un effet que l'ancien moteur écarte sans rien écrire
// (opcode_177_is_valid : fichier IDS hors de 2-9, 2-8 sur un jeu classique, valeur 100 de ea.ids,
// EFF absent) ; EFF d'un autre format ; refus de ad_fx_substitute_nested ; opcode de l'EFF que l'ancien moteur décrit autrement pour un
// effet externe (AD_OPCODES_EFF_FIELDS) ; niveaux minimum et maximum de l'EFF (l'ancien moteur lit
// ceux du dernier EFF lu) ; probabilités incertaines des deux côtés (l'ancien moteur multiplie l'une
// et garde les bornes de l'autre).
DEFINE_PATCH_MACRO ad_fx_substitute_177 BEGIN
	SPRINT $fx_substitution_error(~%fx_id%~) ~~
	SPRINT $fx_substitution_message(~%fx_id%~) ~~
	SPRINT substitute_resref $fx_resource(~%fx_id%~)
	SET substitute_ok = 0
	SET substitute_file = $fx_parameter2(~%fx_id%~)
	SET substitute_versus = $fx_parameter1(~%fx_id%~)
	SET substitute_inner_file = 0
	SET substitute_inner_versus = 0
	PATCH_IF substitute_file < 2 OR substitute_file > (IS_EE ? 9 : 8) OR (substitute_file == 2 AND $fx_parameter1(~%fx_id%~) == 100)
			OR ~%substitute_resref%~ STRING_EQUAL ~~ OR NOT FILE_EXISTS_IN_GAME ~%substitute_resref%.eff~ BEGIN
		SPRINT $fx_substitution_error(~%fx_id%~) ~drop~
		LPF ad_fx_substitute_drop_message INT_VAR ids_file = substitute_file ids_value = substitute_versus STR_VAR resref = ~%substitute_resref%~
			RET substitute_drop_message = message substitute_drop_kind = kind END
		SPRINT $fx_substitution_message(~%fx_id%~) ~%substitute_drop_message%~
		SPRINT $fx_substitution_drop_kind(~%fx_id%~) ~%substitute_drop_kind%~
	END
	ELSE BEGIN
		INNER_PATCH_FILE ~%substitute_resref%.eff~ BEGIN
			LPM ad_fx_read_substitute
		END
		PATCH_IF NOT substitute_ok BEGIN
			SPRINT $fx_substitution_error(~%fx_id%~) ~format~
			SPRINT $fx_substitution_message(~%fx_id%~) ~%substitute_resref%.EFF is not an EFF V2.0 file~
		END
		ELSE BEGIN
			LPM ad_fx_substitute_nested
		END
	END
	PATCH_IF substitute_ok BEGIN
		// Probabilités comme new-lib/normalize.tpp : tirage dans 0-99.
		SET substitute_high = substitute_probability1 > 99 ? 99 : substitute_probability1
		SET substitute_chance = substitute_probability2 <= substitute_high ? substitute_high - substitute_probability2 + 1 : 0
		SET parent_high = $fx_probability1(~%fx_id%~) > 99 ? 99 : $fx_probability1(~%fx_id%~)
		SET parent_chance = $fx_probability2(~%fx_id%~) <= parent_high ? parent_high - $fx_probability2(~%fx_id%~) + 1 : 0
		SET eff_fields_opcode = substitute_opcode
		SET eff_fields_parameter2 = substitute_parameter2
		LPM ad_eff_fields_differ
		PATCH_IF eff_fields_differ BEGIN
			SPRINT $fx_substitution_error(~%fx_id%~) ~eff_fields~
			SPRINT $fx_substitution_message(~%fx_id%~) ~opcode %substitute_opcode% of %substitute_resref%.EFF, which the old engine describes differently~
		END
		ELSE PATCH_IF substitute_level_min != 0 OR substitute_level_max != 0 BEGIN
			SPRINT $fx_substitution_error(~%fx_id%~) ~eff_level~
			SPRINT $fx_substitution_message(~%fx_id%~) ~level restriction in %substitute_resref%.EFF~
		END
		ELSE PATCH_IF substitute_chance < 100 AND parent_chance < 100 BEGIN
			SPRINT $fx_substitution_error(~%fx_id%~) ~probability~
			SPRINT $fx_substitution_message(~%fx_id%~) ~probabilities both in the effect and in %substitute_resref%.EFF~
		END
		ELSE BEGIN
			SPRINT substitute_dice ~LEVEL~
			PATCH_IF VARIABLE_IS_SET $AD_OPCODE_DICE(~%substitute_opcode%~) BEGIN
				SPRINT substitute_dice $AD_OPCODE_DICE(~%substitute_opcode%~)
			END
			PATCH_IF (~%substitute_dice%~ STRING_EQUAL ~DICE~)
					OR ((~%substitute_dice%~ STRING_EQUAL ~DICE_IF_P2_1_EE~) AND IS_EE AND substitute_parameter2 != 0) BEGIN
				SET $fx_dice_count(~%fx_id%~) = substitute_dice_count
				SET $fx_dice_sides(~%fx_id%~) = substitute_dice_sides
			END
			PATCH_IF substitute_save_type == 0 AND $fx_save_type(~%fx_id%~) != 0 BEGIN
				SET substitute_save_type = $fx_save_type(~%fx_id%~)
				SET substitute_save_bonus = $fx_save_bonus(~%fx_id%~)
			END
			ELSE PATCH_IF substitute_save_bonus == $fx_save_bonus(~%fx_id%~) BEGIN
				SET substitute_save_type = substitute_save_type BOR $fx_save_type(~%fx_id%~)
			END
			PATCH_IF substitute_chance < 100 BEGIN
				SET $fx_probability1(~%fx_id%~) = substitute_probability1
				SET $fx_probability2(~%fx_id%~) = substitute_probability2
			END
			SET $fx_opcode(~%fx_id%~)         = substitute_opcode
			SET $fx_power(~%fx_id%~)          = substitute_power
			SET $fx_parameter1(~%fx_id%~)     = substitute_parameter1
			SET $fx_parameter2(~%fx_id%~)     = substitute_parameter2
			SET $fx_parameter2_raw(~%fx_id%~) = substitute_parameter2
			SPRINT $fx_resource(~%fx_id%~)    ~%substitute_resource%~
			SET $fx_save_type(~%fx_id%~)      = substitute_save_type
			SET $fx_save_bonus(~%fx_id%~)     = substitute_save_bonus
			SET $fx_special(~%fx_id%~)        = substitute_special
			SET $fx_resistance(~%fx_id%~)     = substitute_resistance
			SET $fx_external(~%fx_id%~)       = 1
			SET $fx_parameter3(~%fx_id%~)     = substitute_parameter3
			SET $fx_parameter4(~%fx_id%~)     = substitute_parameter4
			SPRINT $fx_resource2(~%fx_id%~)   ~%substitute_resource2%~
			SPRINT $fx_resource3(~%fx_id%~)   ~%substitute_resource3%~
			PATCH_IF substitute_versus != 0 BEGIN
				SET $fx_versus_file(~%fx_id%~)  = substitute_file
				SET $fx_versus_value(~%fx_id%~) = substitute_versus
				SET $fx_versus_inner_file(~%fx_id%~)  = substitute_inner_file
				SET $fx_versus_inner_value(~%fx_id%~) = substitute_inner_versus
			END
			ELSE PATCH_IF substitute_inner_file > 0 BEGIN
				SET $fx_versus_file(~%fx_id%~)  = substitute_inner_file
				SET $fx_versus_value(~%fx_id%~) = substitute_inner_versus
			END
			SPRINT $fx_parent_resource(~%fx_id%~) ~%substitute_resref%~
		END
	END
END

// Raison, en anglais, pour laquelle l'ancien moteur écarte un 177 (opcode_177_is_valid) : fichier
// IDS ids_file hors de 2-9 (2-8 sur un jeu classique), valeur 100 de ea.ids, EFF resref absent ;
// kind : file_error, sauf pour la valeur 100 de ea.ids, que le jeu applique.
DEFINE_PATCH_FUNCTION ad_fx_substitute_drop_message
	INT_VAR
		ids_file = 0
		ids_value = 0
	STR_VAR
		resref = ~~
	RET
		message
		kind
BEGIN
	SPRINT kind ~file_error~
	PATCH_IF ids_file < 2 OR ids_file > (IS_EE ? 9 : 8) BEGIN
		SPRINT message ~IDS file %ids_file% is not a creature type (expected 2-8, 2-9 on enhanced editions)~
	END
	ELSE PATCH_IF ids_file == 2 AND ids_value == 100 BEGIN
		SPRINT message ~value 100 of EA.IDS not supported~
		SPRINT kind ~not_implemented~
	END
	ELSE PATCH_IF ~%resref%~ STRING_EQUAL ~~ BEGIN
		SPRINT message ~empty resource field~
	END
	ELSE BEGIN
		SPRINT message ~%resref%.EFF does not exist~
	END
END

// Champs de l'effet du fichier EFF ouvert : substitute_ok à 0 pour un autre format.
DEFINE_PATCH_MACRO ad_fx_read_substitute BEGIN
	SET substitute_ok = 0
	SPRINT substitute_signature ~~
	PATCH_IF BUFFER_LENGTH >= 0x110 BEGIN
		READ_ASCII EFF2_signature substitute_signature (8)
	END
	PATCH_IF ~%substitute_signature%~ STRING_EQUAL ~EFF V2.0~ BEGIN
		SET substitute_ok = 1
		READ_SHORT EFF2_opcode            substitute_opcode
		READ_BYTE  EFF2_power             substitute_power
		READ_LONG  EFF2_parameter1        substitute_parameter1
		READ_LONG  EFF2_parameter2        substitute_parameter2
		READ_BYTE  EFF2_probability1      substitute_probability1
		READ_BYTE  EFF2_probability2      substitute_probability2
		READ_ASCII EFF2_resource          substitute_resource (8) NULL
		READ_LONG  EFF2_dice_thrown       substitute_dice_count
		READ_LONG  EFF2_dice_sides        substitute_dice_sides
		READ_LONG  EFF2_save_type         substitute_save_type
		READ_LONG  EFF2_save_bonus        substitute_save_bonus
		READ_LONG  EFF2_stacking_id_tobex substitute_special
		READ_LONG  EFF2_resistance        substitute_resistance
		READ_LONG  EFF2_parameter3        substitute_parameter3
		READ_LONG  EFF2_parameter4        substitute_parameter4
		READ_ASCII EFF2_resource2         substitute_resource2 (8) NULL
		READ_ASCII EFF2_resource3         substitute_resource3 (8) NULL
		READ_LONG  0x54                   substitute_level_min
		READ_LONG  0x58                   substitute_level_max
	END
END

// EFF dont l'effet est lui-même un 177 (ancien opcode_177_replace, BUG-039 corrigé) : l'EFF de ce 177
// est lu à la suite et remplace le sien ; son type de créature restreint celui du premier
// (substitute_inner_file, substitute_inner_versus : « les démons qui sont aussi des diablotins »).
// Comme l'ancien moteur, un 177 intérieur invalide (fichier IDS, EFF absent, plus de 5 niveaux)
// écarte l'effet (drop). Refus : second type de créature intérieur ; 177 intérieur probable, avec un
// jet de sauvegarde, des dés ou des niveaux (l'ancien moteur ne garde que ceux du premier) ; kit
// avec un autre type de créature.
DEFINE_PATCH_MACRO ad_fx_substitute_nested BEGIN
	SET substitute_depth = 0
	SPRINT substitute_nested_error ~~
	SPRINT substitute_nested_message ~~
	SPRINT substitute_nested_kind ~not_implemented~
	WHILE substitute_ok AND substitute_opcode == 177 AND ~%substitute_nested_error%~ STRING_EQUAL ~~ BEGIN
		SET substitute_depth += 1
		SPRINT substitute_nested_resref ~%substitute_resource%~
		PATCH_IF substitute_depth > 5 OR substitute_parameter2 < 2 OR substitute_parameter2 > (IS_EE ? 9 : 8)
				OR ~%substitute_nested_resref%~ STRING_EQUAL ~~ OR NOT FILE_EXISTS_IN_GAME ~%substitute_nested_resref%.eff~ BEGIN
			SPRINT substitute_nested_error ~drop~
			PATCH_IF substitute_depth > 5 BEGIN
				SPRINT substitute_nested_message ~more than 5 nested opcode 177~
			END
			ELSE BEGIN
				LPF ad_fx_substitute_drop_message INT_VAR ids_file = substitute_parameter2 ids_value = substitute_parameter1 STR_VAR resref = ~%substitute_nested_resref%~
					RET substitute_nested_message = message substitute_nested_kind = kind END
				SPRINT substitute_nested_message ~nested opcode 177: %substitute_nested_message%~
			END
		END
		ELSE PATCH_IF substitute_parameter1 != 0 AND substitute_inner_file > 0 BEGIN
			SPRINT substitute_nested_error ~nested_depth~
			SPRINT substitute_nested_message ~second creature type in nested opcode 177 (%substitute_nested_resref%.EFF)~
		END
		ELSE PATCH_IF substitute_probability2 != 0 OR substitute_probability1 < 99 OR substitute_save_type != 0
				OR substitute_dice_count != 0 OR substitute_dice_sides != 0 OR substitute_level_min != 0 OR substitute_level_max != 0 BEGIN
			SPRINT substitute_nested_error ~nested_fields~
			SPRINT substitute_nested_message ~nested opcode 177 with a probability, saving throw, dice or levels (%substitute_nested_resref%.EFF)~
		END
		ELSE PATCH_IF substitute_parameter1 != 0 AND substitute_versus != 0 AND (substitute_parameter2 == 9 OR substitute_file == 9) BEGIN
			SPRINT substitute_nested_error ~nested_kit~
			SPRINT substitute_nested_message ~kit and another creature type in nested opcode 177 (%substitute_nested_resref%.EFF)~
		END
		ELSE BEGIN
			PATCH_IF substitute_parameter1 != 0 BEGIN
				SET substitute_inner_file = substitute_parameter2
				SET substitute_inner_versus = substitute_parameter1
			END
			INNER_PATCH_FILE ~%substitute_nested_resref%.eff~ BEGIN
				LPM ad_fx_read_substitute
			END
			PATCH_IF NOT substitute_ok BEGIN
				SPRINT substitute_nested_error ~format~
				SPRINT substitute_nested_message ~%substitute_nested_resref%.EFF is not an EFF V2.0 file~
			END
		END
	END
	PATCH_IF NOT (~%substitute_nested_error%~ STRING_EQUAL ~~) BEGIN
		SPRINT $fx_substitution_error(~%fx_id%~) ~%substitute_nested_error%~
		SPRINT $fx_substitution_message(~%fx_id%~) ~%substitute_nested_message%~
		SPRINT $fx_substitution_drop_kind(~%fx_id%~) ~%substitute_nested_kind%~
		SET substitute_ok = 0
	END
END

// Un 177 que l'ancien moteur écarte est consommé (ad_application_drop). Refus : 177 non remplacé
// (raison de ad_fx_substitute_177). Les 177 sont lus en fin de bloc (ad_fx_load_block,
// new-lib/effects.tpp) : l'effet remplacé est écrit après les effets du fichier de même opcode.
DEFINE_PATCH_MACRO ad_op_177_support BEGIN
	FOR (substitute_id = 0; substitute_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++substitute_id) BEGIN
		PATCH_IF $fx_opcode(~%substitute_id%~) == 177 BEGIN
			SPRINT substitute_error $fx_substitution_error(~%substitute_id%~)
			PATCH_IF ~%substitute_error%~ STRING_EQUAL ~drop~ BEGIN
				SET drop_id = substitute_id
				SPRINT substitute_drop_kind $fx_substitution_drop_kind(~%substitute_id%~)
				SPRINT ignored_reason ~%substitute_drop_kind%:opcode177:drop~
				SPRINT ignored_message $fx_substitution_message(~%substitute_id%~)
				LPM ad_application_drop
			END
			ELSE BEGIN
				SPRINT substitute_message $fx_substitution_message(~%substitute_id%~)
				SPRINT substitute_kind ~not_implemented~
				PATCH_IF ~%substitute_error%~ STRING_EQUAL ~format~ BEGIN
					SPRINT substitute_kind ~file_error~
				END
				LPF ad_refusal INT_VAR fx_id = substitute_id STR_VAR reason = ~%substitute_kind%:opcode177:%substitute_error%~ message = ~%substitute_message%~ RET render_missing = refusal END
			END
		END
	END
END

// Un effet qui vise un type de créature et qu'un regroupement autre que celui des effets identiques
// a consommé perdrait ce type : refusé. Un effet écarté sans rien écrire (fx_dropped) n'en perd aucun.
DEFINE_PATCH_MACRO ad_op_177_lines BEGIN
	FOR (substitute_id = 0; substitute_id < fx_count; ++substitute_id) BEGIN
		PATCH_IF $fx_versus_file(~%substitute_id%~) > 0 AND $fx_consumed(~%substitute_id%~) AND NOT $fx_dropped(~%substitute_id%~)
				AND $fx_identical_anchor(~%substitute_id%~) == substitute_id BEGIN
			LPF ad_refusal INT_VAR fx_id = substitute_id STR_VAR reason = ~not_implemented:opcode177:versus_group~ message = ~effect with a creature type grouped with other effects~ RET render_late_missing = refusal END
		END
	END
END
