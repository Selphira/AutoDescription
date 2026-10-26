// Application des effets : ce qui ne dépend pas de l'opcode (cible, probabilité, durée, jet de
// sauvegarde…). Un opcode ne fournit que le cœur de sa phrase ; la prise en charge commune refuse
// ce que le flux commun ne sait pas encore écrire, et ad_effect_line complète la ligne.
//
// Formes d'une phrase (identifiant de base de la série + forme) : 0 soi,
// 1 cible, 2 soi probable, 3 cible probable. Pris en charge pour l'instant : effets d'équipement
// certains, actifs tant que l'objet est équipé ; effets des en-têtes d'objet, sans restriction de
// niveau, d'une durée limitée ou permanents (suivis de la durée), certains ou probables (« 26 % de
// chances d'infliger… », regroupés par plage dans les capacités de combat, ad_lines_probability_groups,
// new-lib/lines.tpp). La
// ligne finit par le jet de sauvegarde de l'effet (ancien add_save). Une forme absente du .tra rend l'objet non couvert après son rendu
// (render_late_missing), comme une cible sans chaînes (bloc 2 000 000 de description_new.tra).

// Prise en charge commune (passe 2, avant celle des opcodes), pour chaque effet d'un opcode décrit
// qui n'est pas déjà écarté.
DEFINE_PATCH_MACRO ad_application_support BEGIN
	PATCH_IF AD_ENABLE_SHRINKAGE BEGIN
		LPM ad_application_series_support
	END
	FOR (app_id = 0; app_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++app_id) BEGIN
		SET render_opcode = $fx_opcode(~%app_id%~)
		LPM ad_opcode_is_described
		PATCH_IF opcode_described AND NOT $fx_consumed(~%app_id%~) BEGIN
			SPRINT app_block $fx_block(~%app_id%~)
			SPRINT app_timing_kind $fx_timing_kind(~%app_id%~)
			PATCH_IF ~%app_block%~ STRING_EQUAL ~equipped~ BEGIN
				SPRINT app_duration_kind $AD_OPCODE_DURATION(~%render_opcode%~)
				// Effet d'équipement permanent : l'ancien moteur l'écrit comme un effet tant que l'objet est
				// équipé quand la durée de l'opcode n'est jamais affichée.
				SET app_equipped_timing = (~%app_timing_kind%~ STRING_EQUAL ~while_equipped~)
					OR ((~%app_timing_kind%~ STRING_EQUAL ~permanent~)
						AND ((~%app_duration_kind%~ STRING_EQUAL ~IGNORED~) OR (~%app_duration_kind%~ STRING_EQUAL ~HIDDEN~)))
				// Durée limitée nulle : l'ancien opcode_is_valid écarte l'effet (avertissement journalisé).
				PATCH_IF $fx_timing(~%app_id%~) == TIMING_duration AND $fx_duration(~%app_id%~) <= 0
						AND NOT (~%app_duration_kind%~ STRING_EQUAL ~IGNORED~) BEGIN
					SET drop_id = app_id
					SPRINT ignored_reason ~file_error:application:no_duration~
					SPRINT ignored_message ~limited duration (timing 0) of 0 seconds: the effect ends at once~
					LPM ad_application_drop
				END
				ELSE PATCH_IF NOT app_equipped_timing
						OR ($fx_probability(~%app_id%~) != 100 AND NOT VARIABLE_IS_SET $AD_OPCODES_SUB_PROBABILITY(~%render_opcode%~)) BEGIN
					LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~not_implemented:opcode%render_opcode%:effect_kind~ message = ~equipped effect of this opcode with this timing or probability not supported~ RET render_missing = refusal END
				END
			END
			// Les effets de lancement d'un sort s'écrivent comme ceux d'un en-tête.
			ELSE PATCH_IF (~%app_block%~ STRING_EQUAL ~ability~) OR (~%app_block%~ STRING_EQUAL ~casting~) BEGIN
				LPM ad_application_ability_support
			END
			ELSE BEGIN
				LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~not_implemented:opcode%render_opcode%:effect_kind~ message = ~effect of this opcode outside an equipped block or an ability not supported~ RET render_missing = refusal END
			END
		END
	END
END

// Répétitions d'un effet à intervalle régulier (ancien opcode_group_by_duration, avec
// AD_ENABLE_SHRINKAGE) : les effets différés (timing 4) qui ont les mêmes champs qu'un effet
// series_id, hors timing et durée, forment avec lui une série si leurs délais, dans l'ordre du
// fichier et précédés de celui de series_id s'il est différé, croissent d'un même pas. Une seule
// ligne, celle de series_id : « chaque round pendant 4 rounds » si series_id est immédiat (non
// différé, ou sans délai). Calculé ici pour que la prise en charge accepte les effets différés de
// la série ; ad_group_delayed_series (new-lib/groups.tpp) les réunit ensuite. Comme dans l'ancien
// moteur, un effet déjà comparé dans une série, valide ou non, n'en commence pas d'autre.
//
// Tableaux écrits : fx_series_of (effet de tête de la série d'un effet différé, 0 - 1 sinon),
// fx_series_anchor (1 pour l'effet de tête), fx_series_delta (pas, en secondes), fx_series_last
// (dernier délai), fx_series_instant (l'effet de tête est immédiat).
DEFINE_PATCH_MACRO ad_application_series_support BEGIN
	// Une série compte au moins un effet différé, d'un opcode lu plusieurs fois.
	SET series_possible = 0
	FOR (series_id = 0; series_id < fx_count; ++series_id) BEGIN
		SET $fx_series_compared(~%series_id%~) = 0
		SET series_opcode = $fx_opcode(~%series_id%~)
		SET series_possible = series_possible OR ($fx_timing(~%series_id%~) == TIMING_delayed AND $fx_opcode_count(~%series_opcode%~) > 1)
	END
	SET same_ignored = AD_SAME_TIMING
	FOR (series_id = 0; series_possible AND series_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++series_id) BEGIN
		PATCH_IF NOT $fx_series_compared(~%series_id%~) BEGIN
			SET series_opcode = $fx_opcode(~%series_id%~)
			SET series_delayed = $fx_timing(~%series_id%~) == TIMING_delayed
			CLEAR_ARRAY series_members
			SET series_count = 0
			PATCH_IF series_delayed BEGIN
				SET $series_members(~%series_count%~) = series_id
				SET series_count += 1
			END
			SET same_id = series_id
			SPRINT series_resource $fx_resource_lower(~%series_id%~)
			SET series_matched = 0
			PHP_EACH ~fx_ids_%series_opcode%~ AS _ => series_other BEGIN
				// Un autre en-tête est une autre portée (ad_fx_same_fields), testé d'abord parce que moins coûteux.
				PATCH_IF series_other != series_id AND $fx_timing(~%series_other%~) == TIMING_delayed AND $fx_header(~%series_other%~) == $fx_header(~%series_id%~) BEGIN
					SET same_other = series_other
					LPM ad_fx_same_fields
					SPRINT series_other_resource $fx_resource_lower(~%series_other%~)
					PATCH_IF fx_same AND (~%series_other_resource%~ STRING_EQUAL ~%series_resource%~) BEGIN
						// L'ancien moteur reprendrait cet effet dans une seconde série.
						PATCH_IF $fx_series_compared(~%series_other%~) BEGIN
							LPF ad_refusal INT_VAR fx_id = series_other STR_VAR reason = ~not_implemented:application:series_overlap~ message = ~delayed effect that would belong to two series of repetitions~ RET render_missing = refusal END
						END
						SET $series_members(~%series_count%~) = series_other
						SET series_count += 1
						SET series_matched = 1
					END
				END
			END
			PATCH_IF series_matched BEGIN
				SET series_delta = 0
				SET series_previous = 0
				SET series_valid = 1
				FOR (series_k = 0; series_k < series_count; ++series_k) BEGIN
					SET series_member = $series_members(~%series_k%~)
					SET $fx_series_compared(~%series_member%~) = 1
					SET series_delay = $fx_duration(~%series_member%~)
					PATCH_IF series_delta == 0 BEGIN
						SET series_delta = series_delay
					END
					ELSE PATCH_IF series_delta != series_delay - series_previous BEGIN
						SET series_valid = 0
					END
					SET series_previous = series_delay
				END
				SET $fx_series_compared(~%series_id%~) = 1
				PATCH_IF series_valid AND (series_delta <= 0 OR series_previous <= 0) AND NOT support_header_only BEGIN
					LPF ad_refusal INT_VAR fx_id = series_id STR_VAR reason = ~not_implemented:application:series_delay~ message = ~repetitions with a delay of 0~ RET render_missing = refusal END
				END
				ELSE PATCH_IF series_valid BEGIN
					SET $fx_series_anchor(~%series_id%~) = 1
					SET $fx_series_delta(~%series_id%~) = series_delta
					SET $fx_series_last(~%series_id%~) = series_previous
					SET $fx_series_instant(~%series_id%~) = NOT series_delayed OR $fx_duration(~%series_id%~) == 0
					FOR (series_k = 0; series_k < series_count; ++series_k) BEGIN
						SET series_member = $series_members(~%series_k%~)
						PATCH_IF series_member != series_id BEGIN
							SET $fx_series_of(~%series_member%~) = series_id
						END
					END
				END
			END
		END
	END
END

// Effet app_id d'un en-tête d'objet. L'ancien moteur écarte sans le dire un effet sans cible ou
// d'une durée limitée nulle (opcode_is_valid) : refusés ici.
DEFINE_PATCH_MACRO ad_application_ability_support BEGIN
	SET app_target = $fx_target(~%app_id%~)
	SET app_effective_target = $fx_effective_target(~%app_id%~)
	SET app_timing = $fx_timing(~%app_id%~)
	SET app_duration = $fx_duration(~%app_id%~)
	SPRINT app_duration_kind $AD_OPCODE_DURATION(~%render_opcode%~)
	// En-tête d'un sort seul (new-lib/spell_header.tpp) : seuls comptent les effets gardés et leurs
	// champs, pas leur phrase ; l'ancien moteur garde un effet de timing invalide.
	PATCH_IF support_header_only BEGIN
		PATCH_IF NOT (app_timing >= 0 AND (app_timing <= 10 OR app_timing == 4096)) BEGIN
			LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~file_error:application:timing~ message = ~timing %app_timing% (expected 0-10 or 4096)~ RET render_missing = refusal END
		END
	END
	ELSE PATCH_IF VARIABLE_IS_SET $AD_OPCODES_EQUIPPED_ONLY(~%render_opcode%~) BEGIN
		LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~not_implemented:opcode%render_opcode%:ability~ message = ~opcode %render_opcode% is only described as an equipped effect~ RET render_missing = refusal END
	END
	// Plage vide : l'effet n'a jamais lieu.
	ELSE PATCH_IF $fx_probability(~%app_id%~) <= 0 BEGIN
		LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~file_error:application:probability_empty~ message = ~empty probability range (probability2 above probability1): the effect never occurs~ RET render_missing = refusal END
	END
	// Restriction de niveau d'un effet remplacé par celui d'un EFF (177 : l'ancien add_target_level
	// prend celle du dernier EFF lu dans sa portée, minLevel, sinon les dés du 177 ; dans un sort, il
	// ne lit les EFF que dans des fonctions, qui la perdent au retour : les dés du 177) ou sans effet
	// (minimum au-dessus du maximum, erreur journalisée par l'ancien moteur).
	ELSE PATCH_IF ($fx_level_max(~%app_id%~) > 0 OR $fx_level_min(~%app_id%~) > 1) AND (($fx_external(~%app_id%~) AND NOT $fx_eff_levels(~%app_id%~) AND NOT resource_is_spell)
			OR ($fx_level_max(~%app_id%~) > 0 AND $fx_level_min(~%app_id%~) > $fx_level_max(~%app_id%~))) BEGIN
		PATCH_IF $fx_external(~%app_id%~) AND NOT $fx_eff_levels(~%app_id%~) AND NOT resource_is_spell BEGIN
			LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~not_implemented:application:level~ message = ~level restriction of an effect from an EFF file not supported~ RET render_missing = refusal END
		END
		ELSE BEGIN
			SET app_level_min = $fx_level_min(~%app_id%~)
			SET app_level_max = $fx_level_max(~%app_id%~)
			LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~file_error:application:level~ message = ~minimum level %app_level_min% above maximum level %app_level_max%: the effect never applies~ RET render_missing = refusal END
		END
	END
	ELSE PATCH_IF app_target == TARGET_FX_none OR app_target > TARGET_FX_original_caster BEGIN
		LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~file_error:application:target~ message = ~target %app_target% (expected 1-9)~ RET render_missing = refusal END
	END
	ELSE PATCH_IF $fx_potion_drinker(~%app_id%~) AND $fx_header_target_count(~%app_id%~) != 0
			AND app_target != TARGET_FX_self AND app_target != TARGET_FX_original_caster BEGIN
		LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~not_implemented:application:potion_target~ message = ~potion effect with target %app_target% while the ability has a number of targets (BUG-020)~ RET render_missing = refusal END
	END
	ELSE PATCH_IF app_timing == TIMING_duration AND app_duration <= 0 AND NOT (~%app_duration_kind%~ STRING_EQUAL ~IGNORED~) BEGIN
		SET drop_id = app_id
		SPRINT ignored_reason ~file_error:application:no_duration~
		SPRINT ignored_message ~limited duration (timing 0) of 0 seconds: the effect ends at once~
		LPM ad_application_drop
	END
	// Timing 2 d'un en-tête : l'ancien moteur n'écrit pas de durée, comme pour un effet d'équipement.
	// Effet différé sans délai : l'ancien moteur le décrit comme permanent, sans le dire.
	ELSE PATCH_IF app_timing == TIMING_delayed AND app_duration <= 0 AND $fx_series_of(~%app_id%~) < 0 AND NOT $fx_series_anchor(~%app_id%~) BEGIN
		LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~not_implemented:application:no_delay~ message = ~delayed effect (timing 4) with a delay of 0~ RET render_missing = refusal END
	END
	ELSE PATCH_IF app_timing != TIMING_duration AND app_timing != TIMING_duration_ticks AND app_timing != TIMING_permanent
			AND app_timing != TIMING_permanent_after_death AND app_timing != TIMING_while_equipped AND app_timing != TIMING_delayed
			AND app_timing != TIMING_delayed_duration BEGIN
		PATCH_IF app_timing >= 0 AND (app_timing <= 10 OR app_timing == 4096) BEGIN
			LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~not_implemented:application:timing~ message = ~timing %app_timing% not supported in an ability~ RET render_missing = refusal END
		END
		ELSE BEGIN
			LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~file_error:application:timing~ message = ~timing %app_timing% (expected 0-10 or 4096)~ RET render_missing = refusal END
		END
	END
	// Les lignes d'un sort ne nomment pas la zone de son projectile (ancien projectile 0 hors d'un
	// sous-sort).
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND NOT support_spell BEGIN
		LPM ad_application_area_target
	END
END

// Cibles d'un effet d'une capacité de charge dont l'en-tête vise une zone avec un projectile :
// l'ancien moteur les nomme d'après la zone du projectile (get_target_by_projectile), même pour un
// effet sur soi : « aux créatures dans un rayon de 4,5 mètres ». Il lit la cible de l'en-tête avec
// son nombre de cibles (BUG-020) : un nombre non nul l'en empêche. Les lignes d'une fléchette
// viennent de ses capacités de combat, où il ne le fait pas.
DEFINE_PATCH_MACRO ad_application_area_target BEGIN
	SET app_header = $fx_header(~%app_id%~)
	PATCH_IF $fx_header_target(~%app_id%~) == TARGET_HEAD_area AND $fx_header_target_count(~%app_id%~) == 0
			AND $fx_header_projectile(~%app_id%~) > 1 AND item_type != ITM_TYPE_dart AND NOT $charged_other(~%app_header%~) BEGIN
		LPF ad_projectile_area INT_VAR projectile = $fx_header_projectile(~%app_id%~) RET app_area_shape = area_shape
			app_area_creatures = area_creatures app_area_feet = area_feet angle = area_angle END
		PATCH_IF app_area_shape < 0 BEGIN
			SET app_projectile = $fx_header_projectile(~%app_id%~) - 1
			LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~file_error:application:projectile_target~ message = ~area projectile %app_projectile% of the ability (PROJECTL.IDS) has a .PRO file too short to be read~ RET render_missing = refusal END
		END
		ELSE PATCH_IF app_area_shape > 0 BEGIN
			LPF ad_distance_text INT_VAR feet = app_area_feet RET range = text END
			PATCH_IF ~%range%~ STRING_EQUAL ~~ BEGIN
				LPF ad_refusal INT_VAR fx_id = app_id STR_VAR reason = ~not_implemented:application:area_range~ message = ~no text for an area radius of %app_area_feet% feet~ RET render_missing = refusal END
			END
			ELSE BEGIN
				SET app_area_phrase = app_area_shape == 2 ? 2001102 : 2001100 // ~%target% dans un rayon de %range%~
				FOR (app_area_form = 0; app_area_form < 3; ++app_area_form) BEGIN
					LPF ad_tra INT_VAR tra_id = 2001000 + app_area_creatures * 10 + app_area_form
						tra_block_start = 2001000 tra_block_size = 100 RET target = text END // ~les créatures~
					LPF ad_tra INT_VAR tra_id = app_area_phrase RET app_area_text = text END
					SPRINT $fx_area_text(~%app_id% %app_area_form%~) ~%app_area_text%~
				END
				SET $fx_area_target(~%app_id%~) = 1
			END
		END
	END
END

// Effet drop_id que l'ancien moteur écarte dès sa lecture, sans rien écrire (validation d'un opcode) :
// consommé ; journalisé si l'appelant en a fixé la raison (ignored_reason, ignored_message :
// ad_log_ignored, new-lib/log.tpp). La durée commune des effets d'une potion est déjà calculée (ad_item_potion_durations,
// new-lib/item_charged.tpp) : l'effet n'est accepté dans un en-tête que s'il est sans durée (dont une
// durée limitée de 0 seconde), si la durée de son opcode n'y est jamais comptée (colonne DURATION à
// IGNORED) ou si un autre effet décrit du même en-tête a la même durée.
DEFINE_PATCH_MACRO ad_application_drop BEGIN
	SPRINT drop_scope $fx_scope(~%drop_id%~)
	SET drop_timing = $fx_timing(~%drop_id%~)
	SET drop_opcode = $fx_opcode(~%drop_id%~)
	SPRINT drop_duration_kind $AD_OPCODE_DURATION(~%drop_opcode%~)
	// L'en-tête d'un sort se lit après l'écart (new-lib/spell_header.tpp).
	PATCH_IF NOT support_spell AND NOT (~%drop_scope%~ STRING_EQUAL ~equipped~) AND NOT (~%drop_duration_kind%~ STRING_EQUAL ~IGNORED~)
			AND (drop_timing == TIMING_duration OR drop_timing == TIMING_duration_ticks) AND $fx_duration(~%drop_id%~) > 0 BEGIN
		SET drop_twin = 0
		FOR (drop_other = 0; drop_other < fx_count; ++drop_other) BEGIN
			SET render_opcode = $fx_opcode(~%drop_other%~)
			SPRINT drop_other_scope $fx_scope(~%drop_other%~)
			LPM ad_opcode_is_described
			PATCH_IF drop_other != drop_id AND opcode_described AND NOT $fx_consumed(~%drop_other%~)
					AND (~%drop_other_scope%~ STRING_EQUAL ~%drop_scope%~)
					AND $fx_timing(~%drop_other%~) == drop_timing
					AND $fx_duration(~%drop_other%~) == $fx_duration(~%drop_id%~) BEGIN
				SPRINT drop_duration_kind $AD_OPCODE_DURATION(~%render_opcode%~)
				PATCH_IF NOT (~%drop_duration_kind%~ STRING_EQUAL ~IGNORED~) BEGIN
					SET drop_twin = 1
				END
			END
		END
		PATCH_IF NOT drop_twin BEGIN
			LPF ad_refusal INT_VAR fx_id = drop_id STR_VAR reason = ~not_implemented:opcode%drop_opcode%:dropped_duration~ message = ~ignored effect whose duration the old engine would give to the whole ability~ RET render_missing = refusal END
		END
	END
	SET $fx_consumed(~%drop_id%~) = 1
	SET $fx_dropped(~%drop_id%~) = 1
	PATCH_IF NOT (~%ignored_reason%~ STRING_EQUAL ~~) BEGIN
		SET ignored_fx = drop_id
		LPM ad_log_ignored
	END
END

// Forme de la phrase de l'effet line_fx : 0 soi, 1 cible, 2 soi probable, 3 cible probable.
DEFINE_PATCH_MACRO ad_application_form BEGIN
	SET app_target = $fx_effective_target(~%line_fx%~)
	SET line_form = (app_target == TARGET_FX_self OR app_target == TARGET_FX_original_caster) ? 0 : 1
	PATCH_IF $fx_probability(~%line_fx%~) < 100 BEGIN
		SET line_form += 2
	END
END

// Durée de l'effet line_fx d'un en-tête (ancien add_duration et get_duration_value), vide si elle
// n'est pas affichée : colonne DURATION du catalogue, ou durée commune de la potion
// (charged_global_duration, new-lib/item_charged.tpp), qui remplace toutes celles de l'en-tête, et
// dans un sous-sort qu'elle couvre (ctx_ignore_duration, new-lib/recursion.tpp) ; unité de l'opcode
// dans AD_OPCODE_DURATION_SCALE, fraction dans AD_OPCODE_DURATION_DIVISOR, durée fixe dans
// AD_OPCODE_FIXED_DURATION.
DEFINE_PATCH_MACRO ad_application_duration BEGIN
	SPRINT app_duration_text ~~
	SET app_opcode = $fx_opcode(~%line_fx%~)
	SPRINT app_duration_kind $AD_OPCODE_DURATION(~%app_opcode%~)
	SET app_header = $fx_header(~%line_fx%~)
	SET app_timing = $fx_timing(~%line_fx%~)
	SET app_duration = $fx_duration(~%line_fx%~)
	// L'en-tête du sort ne compte pas les effets de lancement : leur durée est toujours écrite.
	SPRINT app_duration_block $fx_block(~%line_fx%~)
	SET app_hide_duration = ctx_ignore_duration AND NOT (~%app_duration_block%~ STRING_EQUAL ~casting~)
	PATCH_IF app_header >= 0 BEGIN
		SET app_hide_duration = app_hide_duration OR $charged_global_duration(~%app_header%~) > 0
	END
	PATCH_IF VARIABLE_IS_SET $AD_OPCODE_FIXED_DURATION(~%app_opcode%~) BEGIN
		SET app_timing = TIMING_duration
		SET app_duration = $AD_OPCODE_FIXED_DURATION(~%app_opcode%~)
	END
	PATCH_IF VARIABLE_IS_SET $AD_OPCODE_DURATION_SCALE(~%app_opcode%~) BEGIN
		SET app_duration *= $AD_OPCODE_DURATION_SCALE(~%app_opcode%~)
	END
	PATCH_IF VARIABLE_IS_SET $AD_OPCODE_DURATION_DIVISOR(~%app_opcode%~) BEGIN
		SET app_duration /= $AD_OPCODE_DURATION_DIVISOR(~%app_opcode%~)
	END
	SPRINT app_level_duration $fx_level_duration(~%line_fx%~)
	// Progression selon le niveau du sort (new-lib/spell_levels.tpp), calculée seulement quand les
	// lignes écrivent les durées.
	PATCH_IF NOT (~%app_level_duration%~ STRING_EQUAL ~~) AND NOT (~%app_duration_kind%~ STRING_EQUAL ~HIDDEN~)
			AND (app_timing == TIMING_delayed OR NOT (~%app_duration_kind%~ STRING_EQUAL ~IGNORED~)) BEGIN
		SPRINT app_duration_text ~%app_level_duration%~
	END
	// Une répétition est toujours écrite, même quand la durée de l'opcode ne l'est pas (ancien
	// add_duration, timings 5000 et 5001 de opcode_group_by_duration).
	ELSE PATCH_IF $fx_series_anchor(~%line_fx%~) AND NOT (~%app_duration_kind%~ STRING_EQUAL ~HIDDEN~) BEGIN
		SET app_series_delta = $fx_series_delta(~%line_fx%~)
		LPF ad_duration_text INT_VAR seconds = app_series_delta tra_base = 3020000 RET frequency = text END
		PATCH_IF $fx_series_instant(~%line_fx%~) BEGIN
			// L'effet immédiat compte pour une période : quatre coups en trois rounds durent quatre rounds.
			LPF ad_duration_text INT_VAR seconds = $fx_series_last(~%line_fx%~) + app_series_delta RET strDuration = text END
			SPRINT app_duration_text @3000003 // ~%frequency% pendant %strDuration%~
		END
		ELSE BEGIN
			LPF ad_duration_text INT_VAR seconds = $fx_series_last(~%line_fx%~) RET strDuration = text END
			LPF ad_duration_text INT_VAR seconds = app_series_delta RET afterStrDuration = text END
			SPRINT app_duration_text @3000004 // ~%frequency% pendant %strDuration% après %afterStrDuration%~
		END
	END
	// Un délai est toujours écrit, comme une répétition.
	ELSE PATCH_IF app_timing == TIMING_delayed AND NOT (~%app_duration_kind%~ STRING_EQUAL ~HIDDEN~) BEGIN
		LPF ad_duration_text INT_VAR seconds = app_duration RET strDuration = text END
		SPRINT app_duration_text @3000005 // ~après %strDuration%~
	END
	ELSE PATCH_IF (~%app_duration_kind%~ STRING_EQUAL ~IGNORED~) OR (~%app_duration_kind%~ STRING_EQUAL ~HIDDEN~)
			OR app_hide_duration OR app_timing == TIMING_while_equipped OR app_timing == TIMING_delayed BEGIN
		SPRINT app_duration_text ~~
	END
	ELSE PATCH_IF app_timing == TIMING_permanent OR app_timing == TIMING_permanent_after_death BEGIN
		PATCH_IF NOT (~%app_duration_kind%~ STRING_EQUAL ~NOT_PERMANENT~) BEGIN
			PATCH_IF app_timing == TIMING_permanent OR (~%app_duration_kind%~ STRING_EQUAL ~NOT_AFTER_DEATH~) BEGIN
				SPRINT app_duration_text @3000001 // ~de manière permanente~
			END
			ELSE BEGIN
				SPRINT app_duration_text @3000002 // ~de manière permanente, persiste après la mort~
			END
		END
	END
	ELSE BEGIN
		// Les ticks valent 1/15 de seconde ; la division entière est celle de l'ancien moteur. Moins de
		// 15 ticks : l'ancien moteur écrit « N ticks » sans traduction, refusé quand la durée est écrite.
		PATCH_IF app_timing == TIMING_duration_ticks AND app_duration > 0 AND app_duration < 15 BEGIN
			LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:application:ticks~ message = ~duration of %app_duration% ticks, under one second~ RET render_late_missing = refusal END
		END
		PATCH_IF app_timing == TIMING_duration_ticks BEGIN
			SET app_duration = app_duration / 15
		END
		PATCH_IF app_duration > 0 BEGIN
			LPF ad_duration_text INT_VAR seconds = app_duration RET strDuration = text END
			SPRINT app_duration_text @3000000 // ~pendant %strDuration%~
			// Timing 3 (IESDP) : l'effet commence après la durée et dure autant.
			PATCH_IF app_timing == TIMING_delayed_duration BEGIN
				SPRINT app_duration_text @3000006 // ~après %strDuration% et pendant %strDuration%~
			END
		END
	END
END

// « 2 heures » : la plus grande unité (jour, heure, tour, round, seconde) qui divise la durée ;
// avec tra_base = 3020000, la fréquence : « chaque round », « tous les 2 tours ».
DEFINE_PATCH_FUNCTION ad_duration_text
	INT_VAR
		seconds = 0
		tra_base = 3010000
	RET
		text
BEGIN
	SPRINT text ~~
	FOR (duration_unit = 4; duration_unit >= 0 AND ~%text%~ STRING_EQUAL ~~; --duration_unit) BEGIN
		SET duration_divisor = $AD_DURATION_UNITS(~%duration_unit%~)
		PATCH_IF seconds MODULO duration_divisor == 0 BEGIN
			SET amount = seconds / duration_divisor
			SET duration_tra = tra_base + duration_unit * 2 + (amount > 1 ? 1 : 0)
			LPF ad_tra INT_VAR tra_id = duration_tra tra_block_start = tra_base tra_block_size = 10 RET text END
		END
	END
END

// Jet de sauvegarde de l'effet line_fx (ancien add_save), vide sans type de jet : « (jet de
// sauvegarde contre les sorts ou contre les souffles pour annuler) », avec son bonus, et sur EE
// les cibles qu'un projectile de ligne ignore, les images miroir et la difficulté
// (AD_SAVE_MIRROR_OPCODES, AD_SAVE_DIFFICULTY_OPCODES). Moitié des dégâts, fixée par l'opcode
// (line_save_for_half : jet réussi ; line_fail_for_half : jet raté) : « pour réduire de moitié »,
// « pour annuler et pour moitié en cas d'échec », ou « (réduits de moitié) » sans jet possible.
// Rien quand l'en-tête du sort l'écrit (ctx_ignore_save, new-lib/spell.tpp).
DEFINE_PATCH_MACRO ad_application_save BEGIN
	SPRINT app_save_text ~~
	SET app_save_types = $fx_save_types(~%line_fx%~)
	SPRINT app_save_block $fx_block(~%line_fx%~)
	PATCH_IF ctx_ignore_save AND NOT (~%app_save_block%~ STRING_EQUAL ~casting~) BEGIN
	END
	ELSE PATCH_IF line_fail_for_half AND (app_save_types == 0 OR line_save_for_half) BEGIN
		SPRINT app_save_text @5000050 // ~réduits de moitié~
		SPRINT app_save_text ~(%app_save_text%)~
	END
	ELSE PATCH_IF app_save_types != 0 BEGIN
		SPRINT saveTypeStr ~~
		SPRINT app_or @1000007 // ~ou~
		PHP_EACH AD_SAVE_TYPES AS app_save_bit => app_save_opcode BEGIN
			PATCH_IF (app_save_types BAND app_save_bit) != 0 BEGIN
				LPF ad_tra INT_VAR tra_id = 20000000 + app_save_opcode * 10000 RET app_save_name = text END
				PATCH_IF ~%saveTypeStr%~ STRING_EQUAL ~~ BEGIN
					SPRINT saveTypeStr ~%app_save_name%~
				END
				ELSE BEGIN
					SPRINT saveTypeStr ~%saveTypeStr% %app_or% %app_save_name%~
				END
			END
		END
		SET app_save_bonus = $fx_save_bonus(~%line_fx%~)
		LPF ad_signed_value INT_VAR value = app_save_bonus RET saveBonus = text END
		PATCH_IF app_save_bonus != 0 AND line_save_for_half BEGIN
			SPRINT app_save_text @5000032 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour réduire de moitié~
		END
		ELSE PATCH_IF app_save_bonus != 0 AND line_fail_for_half BEGIN
			SPRINT app_save_text @5000042 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour annuler et pour moitié en cas d'échec~
		END
		ELSE PATCH_IF app_save_bonus != 0 BEGIN
			SPRINT app_save_text @5000012 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour annuler~
		END
		ELSE PATCH_IF line_save_for_half BEGIN
			SPRINT app_save_text @5000030 // ~jet de sauvegarde %saveTypeStr% pour réduire de moitié~
		END
		ELSE PATCH_IF line_fail_for_half BEGIN
			SPRINT app_save_text @5000040 // ~jet de sauvegarde %saveTypeStr% pour annuler et pour moitié en cas d'échec~
		END
		ELSE BEGIN
			SPRINT app_save_text @5000010 // ~jet de sauvegarde %saveTypeStr% pour annuler~
		END
		SET app_save_flags = $fx_save_type(~%line_fx%~)
		PATCH_IF IS_EE AND (app_save_flags BAND FLAG_SAVINGTHROW_ignore_primary_target_EE) != 0 BEGIN
			SPRINT app_save_extra @5000020 // ~ignore la cible principale~
			SPRINT app_save_text ~%app_save_text%, %app_save_extra%~
		END
		PATCH_IF IS_EE AND (app_save_flags BAND FLAG_SAVINGTHROW_ignore_secondary_target_EE) != 0 BEGIN
			SPRINT app_save_extra @5000021 // ~ignore la cible secondaire~
			SPRINT app_save_text ~%app_save_text%, %app_save_extra%~
		END
		SET app_opcode = $fx_opcode(~%line_fx%~)
		PATCH_IF IS_EE AND VARIABLE_IS_SET $AD_SAVE_MIRROR_OPCODES(~%app_opcode%~)
				AND (app_save_flags BAND FLAG_SAVINGTHROW_bypass_mirror_image_EE) != 0 BEGIN
			SPRINT app_save_extra @5000022 // ~ignore les images miroir~
			SPRINT app_save_text ~%app_save_text%, %app_save_extra%~
		END
		PATCH_IF IS_EE AND VARIABLE_IS_SET $AD_SAVE_DIFFICULTY_OPCODES(~%app_opcode%~)
				AND (app_save_flags BAND FLAG_SAVINGTHROW_ignore_difficulty_EE) != 0 BEGIN
			SPRINT app_save_extra @5000023 // ~ignore la difficulté~
			SPRINT app_save_text ~%app_save_text%, %app_save_extra%~
		END
		SPRINT app_save_text ~(%app_save_text%)~
	END
END

// Chaînes de la cible effective de line_fx (theTarget, ofTheTarget, toTheTarget) ; app_target_missing
// si le .tra ne les a pas. Sur soi ou le lanceur d'origine, c'est la source de l'effet (ancien
// get_effect_description) : le lanceur d'un sort et de ses sous-sorts, le buveur d'une potion, le
// porteur d'un autre objet. Un sous-effet qui
// hérite de la cible du parent prend ses chaînes (ctx_force_target, new-lib/recursion.tpp). La zone
// d'un projectile (ad_application_area_target, ou celle d'un sous-sort, ad_recursion_area_strings)
// remplace l'une et l'autre ; line_the_target, la cible que nomme l'opcode (« les rakshasas »),
// remplace le tout à la forme sujet ; puis le type de créature d'un effet d'un 177
// (ad_application_versus).
DEFINE_PATCH_MACRO ad_application_target_strings BEGIN
	SET app_target = $fx_effective_target(~%line_fx%~)
	SET app_target_tra = 2000000 + app_target * 10
	PATCH_IF app_target == TARGET_FX_self OR app_target == TARGET_FX_original_caster BEGIN
		LPM ad_application_source
		SET app_target_tra = source_tra
	END
	SET app_target_missing = NOT TRA_ENTRY_EXISTS (~%app_target_tra%~)
	PATCH_IF NOT app_target_missing BEGIN
		LPF ad_tra INT_VAR tra_id = app_target_tra     tra_block_start = 2000000 tra_block_size = 1000 RET theTarget = text END
		LPF ad_tra INT_VAR tra_id = app_target_tra + 1 tra_block_start = 2000000 tra_block_size = 1000 RET ofTheTarget = text END
		LPF ad_tra INT_VAR tra_id = app_target_tra + 2 tra_block_start = 2000000 tra_block_size = 1000 RET toTheTarget = text END
	END
	PATCH_IF ctx_force_target BEGIN
		SET app_target_missing = 0
		SPRINT theTarget   ~%ctx_the_target%~
		SPRINT ofTheTarget ~%ctx_of_the_target%~
		SPRINT toTheTarget ~%ctx_to_the_target%~
	END
	PATCH_IF ctx_area_phrase > 0 AND NOT app_target_missing BEGIN
		// Cible principale qui est la source, que l'effet excepte (ligne 43 de splprot.2da) : seules
		// les créatures de la zone (ancien get_target_by_projectile, sourceExcluded).
		SET area_phrase = ctx_area_phrase
		PATCH_IF area_phrase == 2001103 BEGIN
			LPM ad_fx_source_excluded
			LPM ad_application_source
			LPF ad_tra INT_VAR tra_id = source_tra tra_block_start = 2000000 tra_block_size = 1000 RET app_source_name = text END // ~le lanceur~ (@2000120)
			PATCH_IF source_excluded AND (~%theTarget%~ STRING_EQUAL ~%app_source_name%~) BEGIN
				SET area_phrase = 2001100 // ~%target% dans un rayon de %range%~
			END
		END
		LPM ad_recursion_area_strings
	END
	PATCH_IF $fx_area_target(~%line_fx%~) BEGIN
		SET app_target_missing = 0
		SPRINT theTarget   $fx_area_text(~%line_fx% 0~)
		SPRINT ofTheTarget $fx_area_text(~%line_fx% 1~)
		SPRINT toTheTarget $fx_area_text(~%line_fx% 2~)
	END
	PATCH_IF NOT (~%line_the_target%~ STRING_EQUAL ~~) BEGIN
		SET app_target_missing = 0
		SPRINT theTarget ~%line_the_target%~
	END
	LPM ad_application_versus
	PATCH_IF NOT app_target_missing BEGIN
		LPM ad_application_target_level
	END
END

// Premier identifiant (source_tra, puis « de… » et « à… ») des chaînes de la source des effets :
// le lanceur d'un sort et de ses sous-sorts, le buveur d'une potion, le porteur d'un autre objet.
DEFINE_PATCH_MACRO ad_application_source BEGIN
	SET source_tra = resource_is_spell ? 2000120 : item_type == ITM_TYPE_potion ? 2000110 : 2000100
END

// Restriction de niveau de l'effet line_fx (ancien add_target_level), après la zone du projectile
// qui remplace les chaînes de la cible (l'ancien moteur la perdait, BUG-045) : « les créatures dans
// un rayon de 4,5 mètres (de niveau 4 ou inférieur) ». Sur EE, l'ancien moteur n'en écrit pas pour
// le 127 ni pour le 218 de parameter2 non nul. Refus (render_late_missing) : cible propre à l'opcode
// (line_the_target).
DEFINE_PATCH_MACRO ad_application_target_level BEGIN
	SET levelMin = $fx_level_min(~%line_fx%~)
	SET levelMax = $fx_level_max(~%line_fx%~)
	SET app_opcode = $fx_opcode(~%line_fx%~)
	PATCH_IF (levelMax > 0 OR levelMin > 1) AND NOT (IS_EE AND (app_opcode == 127 OR (app_opcode == 218 AND $fx_parameter2(~%line_fx%~) != 0))) BEGIN
		PATCH_IF NOT (~%line_the_target%~ STRING_EQUAL ~~) BEGIN
			LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:application:level_target~ message = ~level restriction on an opcode-specific target~ RET render_late_missing = refusal END
		END
		SET app_level_tra = levelMin == levelMax ? 2003000 : (levelMin <= 1 ? 2003001 : (levelMax == 0 ? 2003002 : 2003003)) // ~%target% (de niveau %levelMin%)~
		SPRINT target ~%theTarget%~
		LPF ad_tra INT_VAR tra_id = app_level_tra tra_block_start = 2003000 tra_block_size = 10 RET theTarget = text END
		SPRINT target ~%ofTheTarget%~
		LPF ad_tra INT_VAR tra_id = app_level_tra tra_block_start = 2003000 tra_block_size = 10 RET ofTheTarget = text END
		SPRINT target ~%toTheTarget%~
		LPF ad_tra INT_VAR tra_id = app_level_tra tra_block_start = 2003000 tra_block_size = 10 RET toTheTarget = text END
	END
END

// Type de créature visé par l'effet line_fx d'un 177 (fx_versus_file, new-lib/opcodes/177.tpp) et par
// les effets identiques qu'il réunit (fx_identical_anchor), comme l'ancien opcode_set_target_strings :
// noms sans doublon dans l'ordre des effets ; la cible devient « les X, les Y et les Z » (« des… »,
// « aux… »), y compris dans une phrase à la forme « soi », versus « contre les X… » ; à la forme
// « soi », line_only_for « uniquement pour les X… » finit la ligne (ancien add_only_for) ; versus
// n'est écrit que pour un tel effet (la ligne de classe d'armure de l'opcode 0 a le sien). Refus
// (render_late_missing) : effet réuni à un effet sans type de créature (l'ancien moteur l'écrirait
// pour les deux) ; valeur sans nom ; classes que l'ancien moteur réunit sous un seul nom (mages,
// voleurs, monoclassés et multiclassés) ; cible d'une zone (l'ancien moteur y écrit la zone, comme
// BUG-032) ; restriction de niveau. Un kit (kit.ids, AD_KIT_NAMES) est celui du porteur : la cible
// garde ses chaînes et la ligne finit par « uniquement pour le kit Archer » (« … les kits Bretteur et
// Maître-lames ») ; refusé à une autre forme que « soi » ou avec un autre type de créature.
DEFINE_PATCH_MACRO ad_application_versus BEGIN
	SET app_versus_count = 0
	SET app_versus_kits = 0
	SET app_versus_plain = 0
	SET app_versus_mages = 0
	SET app_versus_thieves = 0
	CLEAR_ARRAY app_versus_names
	FOR (app_member = line_fx; app_member < fx_count; ++app_member) BEGIN
		PATCH_IF $fx_identical_anchor(~%app_member%~) == line_fx BEGIN
			SET app_versus_file = $fx_versus_file(~%app_member%~)
			SET app_versus_value = $fx_versus_value(~%app_member%~)
			PATCH_IF app_versus_file == 0 BEGIN
				SET app_versus_plain = 1
			END
			ELSE BEGIN
				LPF ad_ids_name INT_VAR ids_file = app_versus_file entry = app_versus_value RET app_versus_name = name END
				PATCH_IF app_versus_file == 9 AND VARIABLE_IS_SET $AD_KIT_NAMES(~%app_versus_value%~) BEGIN
					SPRINT app_versus_name $AD_KIT_NAMES(~%app_versus_value%~)
					SET app_versus_kits += 1
				END
				// Type d'un 177 imbriqué : il restreint le premier (« démons qui sont aussi des diablotins »).
				SET app_versus_inner_file = $fx_versus_inner_file(~%app_member%~)
				PATCH_IF app_versus_inner_file > 0 AND NOT (~%app_versus_name%~ STRING_EQUAL ~~) BEGIN
					LPF ad_ids_name INT_VAR ids_file = app_versus_inner_file entry = $fx_versus_inner_value(~%app_member%~) RET innerType = name END
					SPRINT outerType ~%app_versus_name%~
					SPRINT app_versus_name ~~
					PATCH_IF NOT (~%innerType%~ STRING_EQUAL ~~) BEGIN
						SPRINT app_versus_name @2002040 // ~%outerType% qui sont aussi des %innerType%~
					END
				END
				PATCH_IF ~%app_versus_name%~ STRING_EQUAL ~~ BEGIN
					LPF ad_refusal INT_VAR fx_id = app_member STR_VAR reason = ~not_implemented:versus:ids_name~ message = ~value %app_versus_value% of IDS file %app_versus_file% has no name~ RET render_late_missing = refusal END
				END
				ELSE BEGIN
					SPRINT $app_versus_names(~%app_versus_name%~) ~%app_versus_name%~
					SET app_versus_count += 1
				END
				PATCH_IF app_versus_file == 5 BEGIN
					SET app_versus_mages = app_versus_mages BOR ((app_versus_value == 1) + 2 * (app_versus_value == 7) + 4 * (app_versus_value == 10)
						+ 8 * (app_versus_value == 13) + 16 * (app_versus_value == 14) + 32 * (app_versus_value == 17))
					SET app_versus_thieves = app_versus_thieves BOR ((app_versus_value == 4) + 2 * (app_versus_value == 9) + 4 * (app_versus_value == 10)
						+ 8 * (app_versus_value == 13) + 16 * (app_versus_value == 15))
				END
			END
		END
	END
	// Sous-effet d'un sort lancé par l'opcode 232 : l'ancien moteur y fixe versus à la cible de l'opcode,
	// ou à vide pour une condition de distance (BUG-038).
	PATCH_IF ctx_versus_set BEGIN
		SPRINT versus ~%ctx_versus%~
		PATCH_IF app_versus_count > 0 BEGIN
			LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:recursion:versus_mixed~ message = ~creature type in a spell cast by opcode 232, whose target the old engine sets~ RET render_late_missing = refusal END
		END
	END
	PATCH_IF app_versus_count > 0 BEGIN
		PATCH_IF app_versus_plain BEGIN
			LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:versus:mixed~ message = ~identical effects with and without a creature type~ RET render_late_missing = refusal END
		END
		ELSE PATCH_IF app_versus_mages == 63 OR app_versus_thieves == 31 BEGIN
			LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:versus:class_group~ message = ~creature types covering all mage or thief classes~ RET render_late_missing = refusal END
		END
		ELSE PATCH_IF $fx_area_target(~%line_fx%~) BEGIN
			LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:versus:area~ message = ~creature type with targets named after the area of the projectile~ RET render_late_missing = refusal END
		END
		// À la forme « cible », la restriction de niveau suit les types de créature (ad_application_target_level).
		ELSE PATCH_IF ($fx_level_max(~%line_fx%~) > 0 OR $fx_level_min(~%line_fx%~) > 1) AND (line_form == 0 OR line_form == 2) BEGIN
			LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:versus:level~ message = ~creature type with a level restriction on an effect on oneself~ RET render_late_missing = refusal END
		END
		ELSE PATCH_IF app_versus_kits > 0 BEGIN
			PATCH_IF app_versus_kits < app_versus_count BEGIN
				LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:versus:kit_mixed~ message = ~kits mixed with other creature types~ RET render_late_missing = refusal END
			END
			ELSE PATCH_IF line_form != 0 BEGIN
				LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:versus:kit_form~ message = ~kit restriction on an effect on the target or probable~ RET render_late_missing = refusal END
			END
			ELSE BEGIN
				SPRINT app_versus_and @2002006 // ~et~
				LPF ad_join STR_VAR array_name = ~app_versus_names~ glue = ~, ~ final_glue = EVAL ~ %app_versus_and% ~ RET targetType = text END
				SET app_versus_distinct = 0
				PHP_EACH app_versus_names AS app_versus_key => app_versus_text BEGIN
					SET app_versus_distinct += 1
				END
				SET app_versus_kit_tra = app_versus_distinct == 1 ? 2002031 : 2002032
				LPF ad_tra INT_VAR tra_id = app_versus_kit_tra RET line_only_for = text END // ~uniquement pour le kit %targetType%~
			END
		END
		ELSE BEGIN
			SPRINT app_versus_the    @2002000 // ~les~
			SPRINT app_versus_and_the @2002001 // ~et les~
			SPRINT app_versus_of     @2002002 // ~des~
			SPRINT app_versus_and_of @2002003 // ~et des~
			SPRINT app_versus_to     @2002004 // ~aux~
			SPRINT app_versus_and_to @2002005 // ~et aux~
			LPF ad_join STR_VAR array_name = ~app_versus_names~ glue = EVAL ~, %app_versus_the% ~ final_glue = EVAL ~ %app_versus_and_the% ~ RET targetType = text END
			SPRINT versus @2002020 // ~contre les %targetType%~
			SPRINT app_versus_only_for @2002030 // ~uniquement pour les %targetType%~
			SPRINT theTarget @2002010 // ~les %targetType%~
			LPF ad_join STR_VAR array_name = ~app_versus_names~ glue = EVAL ~, %app_versus_of% ~ final_glue = EVAL ~ %app_versus_and_of% ~ RET targetType = text END
			SPRINT ofTheTarget @2002011 // ~des %targetType%~
			LPF ad_join STR_VAR array_name = ~app_versus_names~ glue = EVAL ~, %app_versus_to% ~ final_glue = EVAL ~ %app_versus_and_to% ~ RET targetType = text END
			SPRINT toTheTarget @2002012 // ~aux %targetType%~
			// Sous-effet d'un sort à zone : la zone restreint les types (SPPR515 : « les morts-vivants
			// dans un rayon de 2,5 mètres »), comme l'ancien get_target_by_projectile corrigé.
			PATCH_IF ctx_area_phrase > 0 BEGIN
				SPRINT app_versus_saved_range ~%range%~
				SET app_versus_saved_angle = angle
				SPRINT range ~%ctx_area_range%~
				SET angle = ctx_area_angle
				SET app_versus_area_phrase = ctx_area_phrase == 2001102 ? 2001102 : 2001100
				SPRINT target ~%theTarget%~
				LPF ad_tra INT_VAR tra_id = app_versus_area_phrase RET theTarget = text END // ~%target% dans un rayon de %range%~
				SPRINT target ~%ofTheTarget%~
				LPF ad_tra INT_VAR tra_id = app_versus_area_phrase RET ofTheTarget = text END
				SPRINT target ~%toTheTarget%~
				LPF ad_tra INT_VAR tra_id = app_versus_area_phrase RET toTheTarget = text END
				SPRINT range ~%app_versus_saved_range%~
				SET angle = app_versus_saved_angle
			END
			SET app_target_missing = 0
			PATCH_IF line_form == 0 OR line_form == 2 BEGIN
				SPRINT line_only_for ~%app_versus_only_for%~
			END
		END
	END
END

// Ligne de l'effet line_fx (pour une ligne qui en réunit plusieurs, l'un d'eux, de même application
// que les autres) : phrase line_phrase (identifiant de base de la série, la forme y est ajoutée),
// ou line_text déjà rédigé à la forme « soi » (à toute forme avec line_any_form : lignes d'un
// sous-sort, qui nomment déjà leurs cibles) ; line_section et line_sort comme pour ad_line_add ;
// line_no_duration : durée de l'effet non écrite (déjà dans la condition).
// Un opcode qui a une phrase à la forme « cible » lit line_form (ad_application_form) pour choisir
// entre les deux. Un effet d'en-tête va dans la section de son en-tête (fx_line_section : sa portée,
// ou sa plage de niveaux dans un sort à plusieurs en-têtes, new-lib/spell_levels.tpp), suivi de sa
// durée. line_sentence (phrase ajoutée par l'opcode) suit le texte après un point ; line_suffix
// (précisions de l'opcode, « (ne réveille pas la cible) ») les suit, avant la durée ; line_save_for_half et line_fail_for_half règlent le jet de sauvegarde
// (ad_application_save), suivi de « (non cumulatif) » pour un effet lu après un 321 sur la ressource
// elle-même (fx_not_cumulative) ; line_condition (« En combat ») précède toute la ligne, séparée par
// AD_SEMICOLON (ancien add_condition) ; line_the_target, voir ad_application_target_strings ;
// line_only_for (ad_application_versus), puis les exceptions de cible de l'effet
// (ad_application_target_exceptions, new-lib/opcodes/target_exceptions.tpp) finissent la ligne, entre
// parenthèses ; tous sont remis à zéro
// après la ligne. Forme ou cible sans
// texte : render_late_missing, et pas de ligne.
DEFINE_PATCH_MACRO ad_effect_line BEGIN
	LPM ad_application_form
	SET app_line_ok = 1
	LPM ad_application_target_strings
	PATCH_IF app_target_missing BEGIN
		LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:application:target%app_target%~ message = ~no text for target %app_target%~ RET render_late_missing = refusal END
		SET app_line_ok = 0
	END
	PATCH_IF line_phrase > 0 AND app_line_ok BEGIN
		SET line_phrase_tra = line_phrase + line_form
		PATCH_IF TRA_ENTRY_EXISTS (~%line_phrase_tra%~) BEGIN
			LPF ad_tra INT_VAR tra_id = line_phrase_tra RET line_text = text END
		END
		ELSE BEGIN
			LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:phrase%line_phrase%:form%line_form%~ message = ~no sentence %line_phrase_tra% for this form (target or probable effect)~ RET render_late_missing = refusal END
			SET app_line_ok = 0
		END
	END
	ELSE PATCH_IF line_form != 0 AND app_line_ok AND NOT line_any_form BEGIN
		SET app_opcode = $fx_opcode(~%line_fx%~)
		LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:opcode%app_opcode%:form%line_form%~ message = ~no text for form %line_form% (1 target, 2 probable, 3 probable on the target)~ RET render_late_missing = refusal END
		SET app_line_ok = 0
	END
	PATCH_IF NOT (~%line_sentence%~ STRING_EQUAL ~~) BEGIN
		SPRINT line_text ~%line_text%. %line_sentence%~
	END
	PATCH_IF NOT (~%line_suffix%~ STRING_EQUAL ~~) BEGIN
		SPRINT line_text ~%line_text% %line_suffix%~
	END
	SPRINT app_saved_section ~%line_section%~
	SPRINT app_block $fx_block(~%line_fx%~)
	PATCH_IF (~%app_block%~ STRING_EQUAL ~ability~) OR (~%app_block%~ STRING_EQUAL ~casting~) BEGIN
		SPRINT line_section $fx_line_section(~%line_fx%~)
		LPM ad_application_duration
		PATCH_IF NOT (~%app_duration_text%~ STRING_EQUAL ~~) AND NOT line_no_duration BEGIN
			SPRINT line_text ~%line_text% %app_duration_text%~
		END
	END
	LPM ad_application_save
	PATCH_IF NOT (~%app_save_text%~ STRING_EQUAL ~~) BEGIN
		SPRINT line_text ~%line_text% %app_save_text%~
	END
	SET app_opcode = $fx_opcode(~%line_fx%~)
	PATCH_IF $fx_not_cumulative(~%line_fx%~) AND NOT VARIABLE_IS_SET $AD_OPCODES_ALWAYS_CUMULATIVE(~%app_opcode%~) BEGIN
		SPRINT app_not_cumulative @4000010 // ~non cumulatif~
		SPRINT app_not_cumulative ~ (%app_not_cumulative%)~
		// Pas de seconde mention après la dernière sous-ligne d'un sort lancé qui l'a déjà.
		SET app_not_cumulative_start = STRING_LENGTH ~%line_text%~ - STRING_LENGTH ~%app_not_cumulative%~
		PATCH_IF app_not_cumulative_start < 0 OR INDEX (CASE_SENSITIVE EXACT_MATCH ~%app_not_cumulative%~ ~%line_text%~ app_not_cumulative_start) != app_not_cumulative_start BEGIN
			SPRINT line_text ~%line_text%%app_not_cumulative%~
		END
	END
	PATCH_IF NOT (~%line_only_for%~ STRING_EQUAL ~~) BEGIN
		SPRINT line_text ~%line_text% (%line_only_for%)~
	END
	PATCH_IF $fx_exception_count(~%line_fx%~) > 0 BEGIN
		LPM ad_application_target_exceptions
		PATCH_IF NOT (~%app_exceptions_text%~ STRING_EQUAL ~~) BEGIN
			SPRINT line_text ~%line_text% (%app_exceptions_text%)~
		END
	END
	// Effet probable : « 26 % de chances » devant la ligne entière (ancien get_effect_description),
	// rang abaissé d'autant que la probabilité est faible (ancien set_opcode_sort).
	SET app_saved_sort = line_sort
	SET app_probability = $fx_probability(~%line_fx%~)
	// Probabilité déjà écrite dans les lignes du sort lancé (AD_OPCODES_SUB_PROBABILITY) : seul le
	// rang de la ligne en dépend.
	PATCH_IF $fx_probability_in_sub(~%line_fx%~) BEGIN
		SET line_sort += (100 - app_probability) * 10000
		SET app_probability = 100
	END
	PATCH_IF app_probability < 100 BEGIN
		SPRINT line_core ~%line_text%~
		SET value = app_probability
		SPRINT probability @1200003 // ~%value%%PERCENT%~
		SPRINT app_saved_description ~%description%~
		SPRINT description ~%line_text%~
		SPRINT line_text @4000000 // ~%probability% de chances %description%~
		SPRINT description ~%app_saved_description%~
		SET line_sort += (100 - app_probability) * 10000
		SET line_probability = app_probability
		SET line_probability_low = $fx_probability_low(~%line_fx%~)
		SET line_probability_high = $fx_probability_high(~%line_fx%~)
	END
	// Effet d'un EFF maudit (opcode 283) : « Malédiction : » devant toute la ligne, probabilité comprise
	// (« Malédiction : 20 % de chances d'aveugler la cible ») ; elle n'entre pas dans les regroupements
	// par probabilité, qui réécrivent « 20 % de chances » (ancien forceSort).
	PATCH_IF $fx_cursed(~%line_fx%~) BEGIN
		SPRINT app_curse @22830000 // ~Malédiction~
		SPRINT line_text ~%app_curse%%AD_COLON%%line_text%~
		SET line_probability = 0
	END
	PATCH_IF NOT (~%line_condition%~ STRING_EQUAL ~~) BEGIN
		// Le regroupement par probabilité de l'ancien moteur ne retire plus le préfixe « N % de chances »
		// placé après la condition.
		PATCH_IF app_probability < 100 BEGIN
			LPF ad_refusal INT_VAR fx_id = line_fx STR_VAR reason = ~not_implemented:application:condition_probability~ message = ~probable effect under a condition~ RET render_late_missing = refusal END
			SET app_line_ok = 0
		END
		// Sections de niveaux d'un sous-sort sans ligne commune : en retrait sous la condition (ancien
		// add_condition, qui décale les sauts de ligne d'une description commencée par un saut de ligne).
		PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~%CRLF%%CRLF%~ ~%line_text%~) == 0 BEGIN
			INNER_PATCH_SAVE line_text ~%line_text%~ BEGIN
				REPLACE_TEXTUALLY ~%CRLF%~ ~%CRLF%  ~
			END
		END
		SPRINT line_text ~%line_condition%%AD_SEMICOLON%%line_text%~
	END
	PATCH_IF app_line_ok BEGIN
		SET app_line_count = line_count
		LPM ad_line_add
		// Progression selon le niveau du sort : l'ancien moteur ajoute l'effet qui la porte en fin de
		// liste ; à rang égal, il vient donc avant les autres lignes (égalités inversées, SPWI603).
		PATCH_IF line_count > app_line_count AND $fx_level_progression(~%line_fx%~) BEGIN
			SET $line_order(~%app_line_count%~) = app_line_count + 500
		END
	END
	SET line_sort = app_saved_sort
	SET line_probability = 0
	SPRINT line_section ~%app_saved_section%~
	SET line_phrase = 0
	SET line_any_form = 0
	SET line_no_duration = 0
	SPRINT line_suffix ~~
	SPRINT line_sentence ~~
	SPRINT line_condition ~~
	SPRINT line_the_target ~~
	SPRINT line_only_for ~~
	SET line_save_for_half = 0
	SET line_fail_for_half = 0
END
