// Valeurs normalisées d'un effet fx_id du magasin, calculées à la lecture d'après l'IESDP (format
// des effets) ; les champs bruts restent disponibles. Aucune règle d'affichage ici : le rendu
// décidera de ce qu'il montre.
//
// Tableaux écrits :
// - fx_timing_kind : limited, permanent, while_equipped, until_reload, delayed_limited,
//   delayed_permanent, delayed_while_equipped, game_time_limited, game_time_permanent,
//   game_time_while_equipped, permanent_after_death, absolute, unknown ;
// - fx_delay_ticks, fx_duration_ticks : en ticks (1/15 s), 0 s'ils ne s'appliquent pas ;
// - fx_probability_low, fx_probability_high, fx_probability : bornes du tirage et pourcentage ;
// - fx_save_types (bits 0-4 : un jet contre le meilleur des types cochés), fx_save_flags (le reste) ;
// - fx_level_min, fx_level_max : restriction de niveau de la cible (0 = aucune) ;
// - fx_resource_lower ;
// - fx_effective_target : cible réelle (le porteur pour un effet d'équipement d'objet ; une potion
//   bue par son porteur est corrigée par ad_fx_load_item) ;
// - fx_scope : portée de l'effet, equipped, casting ou ability<h> (en-tête h) ; les lignes, les
//   regroupements et les contrôles de doublons ne réunissent que des effets de même portée, comme
//   l'ancien moteur qui traite chaque bloc séparément ;
// - fx_group_target : cible comparée par les regroupements, celle que l'ancien moteur compare : « soi »
//   pour un effet d'équipement (remplacée à la lecture), la cible du fichier sinon (une potion n'est
//   corrigée qu'après ses regroupements).
DEFINE_PATCH_MACRO ad_fx_normalize BEGIN
	SET fx_timing   = $fx_timing(~%fx_id%~)
	SET fx_duration = $fx_duration(~%fx_id%~)
	SET fx_delay_ticks    = 0
	SET fx_duration_ticks = 0
	// Timings 0, 3, 4, 5 : durée en secondes ; 6, 7, 8 et 10 : en ticks. 3 attend la durée puis
	// dure autant ; 6, 7, 8 attendent une heure de jeu absolue (Gametime), indépendante du moment
	// de l'application : ni délai ni durée ne s'en déduisent.
	PATCH_MATCH fx_timing WITH
		0 BEGIN
			SPRINT fx_timing_kind ~limited~
			SET fx_duration_ticks = fx_duration * 15
		END
		1 BEGIN SPRINT fx_timing_kind ~permanent~ END
		// Sur un en-tête d'objet ou dans un sort, le timing 2 dure jusqu'au rechargement de la partie.
		2 BEGIN
			PATCH_IF ~%fx_block_kind%~ STRING_EQUAL ~equipped~ BEGIN
				SPRINT fx_timing_kind ~while_equipped~
			END
			ELSE BEGIN
				SPRINT fx_timing_kind ~until_reload~
			END
		END
		3 BEGIN
			SPRINT fx_timing_kind ~delayed_limited~
			SET fx_delay_ticks    = fx_duration * 15
			SET fx_duration_ticks = fx_duration * 15
		END
		4 BEGIN
			SPRINT fx_timing_kind ~delayed_permanent~
			SET fx_delay_ticks = fx_duration * 15
		END
		5 BEGIN
			SPRINT fx_timing_kind ~delayed_while_equipped~
			SET fx_delay_ticks = fx_duration * 15
		END
		6 BEGIN SPRINT fx_timing_kind ~game_time_limited~ END
		7 BEGIN SPRINT fx_timing_kind ~game_time_permanent~ END
		8 BEGIN SPRINT fx_timing_kind ~game_time_while_equipped~ END
		9 BEGIN SPRINT fx_timing_kind ~permanent_after_death~ END
		10 BEGIN
			SPRINT fx_timing_kind ~limited~
			SET fx_duration_ticks = fx_duration
		END
		4096 BEGIN SPRINT fx_timing_kind ~absolute~ END
		DEFAULT
			SPRINT fx_timing_kind ~unknown~
	END
	SPRINT $fx_timing_kind(~%fx_id%~) ~%fx_timing_kind%~
	SET $fx_delay_ticks(~%fx_id%~)    = fx_delay_ticks
	SET $fx_duration_ticks(~%fx_id%~) = fx_duration_ticks

	// Le moteur tire x dans 0-99 : l'effet a lieu si probabilité 2 <= x <= probabilité 1.
	SET fx_probability_low  = $fx_probability2(~%fx_id%~)
	SET fx_probability_high = $fx_probability1(~%fx_id%~) > 99 ? 99 : $fx_probability1(~%fx_id%~)
	SET $fx_probability_low(~%fx_id%~)  = fx_probability_low
	SET $fx_probability_high(~%fx_id%~) = fx_probability_high
	SET $fx_probability(~%fx_id%~) = fx_probability_low <= fx_probability_high ? fx_probability_high - fx_probability_low + 1 : 0

	SET $fx_save_types(~%fx_id%~) = $fx_save_type(~%fx_id%~) BAND 0b11111
	SET $fx_save_flags(~%fx_id%~) = $fx_save_type(~%fx_id%~) BAND (BNOT 0b11111)

	// Les champs « dés » donnent un niveau maximum (dés lancés) et minimum (faces) de la cible,
	// sauf pour les opcodes qui s'en servent comme de vrais dés.
	SET fx_opcode = $fx_opcode(~%fx_id%~)
	SPRINT fx_dice_usage ~LEVEL~
	PATCH_IF VARIABLE_IS_SET $AD_OPCODE_DICE(~%fx_opcode%~) BEGIN
		SPRINT fx_dice_usage $AD_OPCODE_DICE(~%fx_opcode%~)
	END
	SET fx_level_restriction = 0
	PATCH_IF ~%fx_dice_usage%~ STRING_EQUAL ~LEVEL~ BEGIN
		SET fx_level_restriction = 1
	END
	ELSE PATCH_IF ~%fx_dice_usage%~ STRING_EQUAL ~DICE_IF_P2_1_EE~ BEGIN
		SET fx_level_restriction = NOT (IS_EE AND $fx_parameter2(~%fx_id%~) == 1)
	END
	SET $fx_level_max(~%fx_id%~) = fx_level_restriction ? $fx_dice_count(~%fx_id%~) : 0
	SET $fx_level_min(~%fx_id%~) = fx_level_restriction ? $fx_dice_sides(~%fx_id%~) : 0

	// L'effet d'équipement d'un objet touche toujours le porteur : sa cible est sans objet.
	SET $fx_effective_target(~%fx_id%~) = $fx_target(~%fx_id%~)
	PATCH_IF ~%fx_block_kind%~ STRING_EQUAL ~equipped~ BEGIN
		SET $fx_effective_target(~%fx_id%~) = TARGET_FX_self
	END
	SET $fx_group_target(~%fx_id%~) = $fx_effective_target(~%fx_id%~)

	SPRINT $fx_scope(~%fx_id%~) ~%fx_block_kind%~
	PATCH_IF ~%fx_block_kind%~ STRING_EQUAL ~ability~ BEGIN
		SPRINT $fx_scope(~%fx_id%~) ~ability%fx_block_header%~
	END

	SPRINT fx_resource_lower $fx_resource(~%fx_id%~)
	TO_LOWER fx_resource_lower
	SPRINT $fx_resource_lower(~%fx_id%~) ~%fx_resource_lower%~
END
