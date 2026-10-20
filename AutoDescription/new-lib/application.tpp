// Application des effets : ce qui ne dépend pas de l'opcode (cible, probabilité, durée, jet de
// sauvegarde…). Un opcode ne fournit que le cœur de sa phrase ; la prise en charge commune refuse
// ce que le flux commun ne sait pas encore écrire, et ad_effect_line complète la ligne.
//
// Formes d'une phrase (identifiant de base de la série + forme) : 0 soi,
// 1 cible, 2 soi probable, 3 cible probable. Pris en charge pour l'instant : effets d'équipement
// certains, actifs tant que l'objet est équipé ; effets certains des en-têtes d'objet, sans
// restriction de niveau, d'une durée limitée ou permanents (forme 0 ou 1, suivie de la durée). La
// ligne finit par le jet de sauvegarde de l'effet (ancien add_save). Une forme absente du .tra rend l'objet non couvert après son rendu
// (render_late_missing), comme une cible sans chaînes (bloc 2 000 000 de description_new.tra).

// Prise en charge commune (passe 2, avant celle des opcodes), pour chaque effet d'un opcode décrit.
DEFINE_PATCH_MACRO ad_application_support BEGIN
	FOR (app_id = 0; app_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++app_id) BEGIN
		SET render_opcode = $fx_opcode(~%app_id%~)
		LPM ad_opcode_is_described
		PATCH_IF opcode_described BEGIN
			SPRINT app_block $fx_block(~%app_id%~)
			SPRINT app_timing_kind $fx_timing_kind(~%app_id%~)
			PATCH_IF ~%app_block%~ STRING_EQUAL ~equipped~ BEGIN
				PATCH_IF NOT (~%app_timing_kind%~ STRING_EQUAL ~while_equipped~) OR $fx_probability(~%app_id%~) != 100 BEGIN
					SPRINT render_missing ~not_implemented:opcode%render_opcode%:effect_kind~
				END
			END
			ELSE PATCH_IF ~%app_block%~ STRING_EQUAL ~ability~ BEGIN
				LPM ad_application_ability_support
			END
			ELSE BEGIN
				SPRINT render_missing ~not_implemented:opcode%render_opcode%:effect_kind~
			END
		END
	END
END

// Effet app_id d'un en-tête d'objet. L'ancien moteur écarte sans le dire un effet sans cible ou
// d'une durée limitée nulle (opcode_is_valid) : refusés ici. Durée limitée en ticks : moins de 15
// ticks, l'ancien moteur écrit « N ticks » sans traduction.
DEFINE_PATCH_MACRO ad_application_ability_support BEGIN
	SET app_target = $fx_target(~%app_id%~)
	SET app_effective_target = $fx_effective_target(~%app_id%~)
	SET app_timing = $fx_timing(~%app_id%~)
	SET app_duration = $fx_duration(~%app_id%~)
	SPRINT app_duration_kind $AD_OPCODE_DURATION(~%render_opcode%~)
	PATCH_IF VARIABLE_IS_SET $AD_OPCODES_EQUIPPED_ONLY(~%render_opcode%~) BEGIN
		SPRINT render_missing ~not_implemented:opcode%render_opcode%:ability~
	END
	ELSE PATCH_IF $fx_probability(~%app_id%~) != 100 BEGIN
		SPRINT render_missing ~not_implemented:application:probability~
	END
	ELSE PATCH_IF $fx_level_max(~%app_id%~) > 0 OR $fx_level_min(~%app_id%~) > 1 BEGIN
		SPRINT render_missing ~not_implemented:application:level~
	END
	ELSE PATCH_IF app_target == TARGET_FX_none OR app_target > TARGET_FX_original_caster BEGIN
		SPRINT render_missing ~not_implemented:application:target~
	END
	ELSE PATCH_IF $fx_potion_drinker(~%app_id%~) AND $fx_header_target_count(~%app_id%~) != 0
			AND app_target != TARGET_FX_self AND app_target != TARGET_FX_original_caster BEGIN
		SPRINT render_missing ~not_implemented:application:potion_target~
	END
	// Cible d'un en-tête de zone à projectile : l'ancien moteur la nomme d'après le projectile
	// (get_target_by_projectile).
	ELSE PATCH_IF app_effective_target != TARGET_FX_self AND app_effective_target != TARGET_FX_original_caster
			AND $fx_header_target(~%app_id%~) == TARGET_HEAD_area AND $fx_header_projectile(~%app_id%~) > 1 BEGIN
		SPRINT render_missing ~not_implemented:application:projectile_target~
	END
	ELSE PATCH_IF app_timing == TIMING_duration AND app_duration <= 0 AND NOT (~%app_duration_kind%~ STRING_EQUAL ~IGNORED~) BEGIN
		SPRINT render_missing ~not_implemented:application:no_duration~
	END
	ELSE PATCH_IF app_timing == TIMING_duration_ticks AND app_duration > 0 AND app_duration < 15 BEGIN
		SPRINT render_missing ~not_implemented:application:ticks~
	END
	ELSE PATCH_IF app_timing != TIMING_duration AND app_timing != TIMING_duration_ticks AND app_timing != TIMING_permanent
			AND app_timing != TIMING_permanent_after_death BEGIN
		SPRINT render_missing ~not_implemented:application:timing~
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
// (charged_global_duration, new-lib/item_charged.tpp), qui remplace toutes celles de l'en-tête.
DEFINE_PATCH_MACRO ad_application_duration BEGIN
	SPRINT app_duration_text ~~
	SET app_opcode = $fx_opcode(~%line_fx%~)
	SPRINT app_duration_kind $AD_OPCODE_DURATION(~%app_opcode%~)
	SET app_header = $fx_header(~%line_fx%~)
	SET app_timing = $fx_timing(~%line_fx%~)
	SET app_duration = $fx_duration(~%line_fx%~)
	PATCH_IF (~%app_duration_kind%~ STRING_EQUAL ~IGNORED~) OR (~%app_duration_kind%~ STRING_EQUAL ~HIDDEN~)
			OR $charged_global_duration(~%app_header%~) > 0 BEGIN
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
		// Les ticks valent 1/15 de seconde ; la division entière est celle de l'ancien moteur.
		PATCH_IF app_timing == TIMING_duration_ticks BEGIN
			SET app_duration = app_duration / 15
		END
		PATCH_IF app_duration > 0 BEGIN
			LPF ad_duration_text INT_VAR seconds = app_duration RET strDuration = text END
			SPRINT app_duration_text @3000000 // ~pendant %strDuration%~
		END
	END
END

// « 2 heures » : la plus grande unité (jour, heure, tour, round, seconde) qui divise la durée.
DEFINE_PATCH_FUNCTION ad_duration_text
	INT_VAR
		seconds = 0
	RET
		text
BEGIN
	SPRINT text ~~
	FOR (duration_unit = 4; duration_unit >= 0 AND ~%text%~ STRING_EQUAL ~~; --duration_unit) BEGIN
		SET duration_divisor = $AD_DURATION_UNITS(~%duration_unit%~)
		PATCH_IF seconds MODULO duration_divisor == 0 BEGIN
			SET amount = seconds / duration_divisor
			SET duration_tra = 3010000 + duration_unit * 2 + (amount > 1 ? 1 : 0)
			LPF ad_tra INT_VAR tra_id = duration_tra tra_block_start = 3010000 tra_block_size = 10 RET text END
		END
	END
END

// Jet de sauvegarde de l'effet line_fx (ancien add_save), vide sans type de jet : « (jet de
// sauvegarde contre les sorts ou contre les souffles pour annuler) », avec son bonus, et sur EE
// les cibles qu'un projectile de ligne ignore. Les moitiés de dégâts ne concernent que l'opcode 12.
DEFINE_PATCH_MACRO ad_application_save BEGIN
	SPRINT app_save_text ~~
	SET app_save_types = $fx_save_types(~%line_fx%~)
	PATCH_IF app_save_types != 0 BEGIN
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
		PATCH_IF app_save_bonus != 0 BEGIN
			LPF ad_signed_value INT_VAR value = app_save_bonus RET saveBonus = text END
			SPRINT app_save_text @5000012 // ~jet de sauvegarde à %saveBonus% %saveTypeStr% pour annuler~
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
		SPRINT app_save_text ~(%app_save_text%)~
	END
END

// Chaînes de la cible effective de line_fx (theTarget, ofTheTarget, toTheTarget), pour une phrase
// à la forme « cible » ; app_target_missing si le .tra ne les a pas.
DEFINE_PATCH_MACRO ad_application_target_strings BEGIN
	SET app_target = $fx_effective_target(~%line_fx%~)
	SET app_target_tra = 2000000 + app_target * 10
	SET app_target_missing = NOT TRA_ENTRY_EXISTS (~%app_target_tra%~)
	PATCH_IF NOT app_target_missing BEGIN
		LPF ad_tra INT_VAR tra_id = app_target_tra     tra_block_start = 2000000 tra_block_size = 100 RET theTarget = text END
		LPF ad_tra INT_VAR tra_id = app_target_tra + 1 tra_block_start = 2000000 tra_block_size = 100 RET ofTheTarget = text END
		LPF ad_tra INT_VAR tra_id = app_target_tra + 2 tra_block_start = 2000000 tra_block_size = 100 RET toTheTarget = text END
	END
END

// Ligne de l'effet line_fx (pour une ligne qui en réunit plusieurs, l'un d'eux, de même application
// que les autres) : phrase line_phrase (identifiant de base de la série, la forme y est ajoutée),
// ou line_text déjà rédigé à la forme « soi » ; line_section et line_sort comme pour ad_line_add.
// Un opcode qui a une phrase à la forme « cible » lit line_form (ad_application_form) pour choisir
// entre les deux. Un effet d'en-tête va dans la section de son en-tête (fx_scope), suivi de sa
// durée. Forme ou cible sans texte : render_late_missing, et pas de ligne.
DEFINE_PATCH_MACRO ad_effect_line BEGIN
	LPM ad_application_form
	SET app_line_ok = 1
	PATCH_IF line_form MODULO 2 == 1 BEGIN
		LPM ad_application_target_strings
		PATCH_IF app_target_missing BEGIN
			SPRINT render_late_missing ~not_implemented:application:target%app_target%~
			SET app_line_ok = 0
		END
	END
	PATCH_IF line_phrase > 0 AND app_line_ok BEGIN
		SET line_phrase_tra = line_phrase + line_form
		PATCH_IF TRA_ENTRY_EXISTS (~%line_phrase_tra%~) BEGIN
			LPF ad_tra INT_VAR tra_id = line_phrase_tra RET line_text = text END
		END
		ELSE BEGIN
			SPRINT render_late_missing ~not_implemented:phrase%line_phrase%:form%line_form%~
			SET app_line_ok = 0
		END
	END
	ELSE PATCH_IF line_form != 0 AND app_line_ok BEGIN
		SET app_opcode = $fx_opcode(~%line_fx%~)
		SPRINT render_late_missing ~not_implemented:opcode%app_opcode%:form%line_form%~
		SET app_line_ok = 0
	END
	SPRINT app_saved_section ~%line_section%~
	SPRINT app_block $fx_block(~%line_fx%~)
	PATCH_IF ~%app_block%~ STRING_EQUAL ~ability~ BEGIN
		SPRINT line_section $fx_scope(~%line_fx%~)
		LPM ad_application_duration
		PATCH_IF NOT (~%app_duration_text%~ STRING_EQUAL ~~) BEGIN
			SPRINT line_text ~%line_text% %app_duration_text%~
		END
	END
	LPM ad_application_save
	PATCH_IF NOT (~%app_save_text%~ STRING_EQUAL ~~) BEGIN
		SPRINT line_text ~%line_text% %app_save_text%~
	END
	PATCH_IF app_line_ok BEGIN
		LPM ad_line_add
	END
	SPRINT line_section ~%app_saved_section%~
	SET line_phrase = 0
END
