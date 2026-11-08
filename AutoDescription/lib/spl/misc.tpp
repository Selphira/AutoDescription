DEFINE_PATCH_FUNCTION ~spell_level~ RET description BEGIN
	READ_SHORT SPL_type  spellType
	READ_LONG  SPL_level spellLevel

	// There is no good reason for a Special/Psionic/Innate/Bard song to be any Spell level except 1.
	PATCH_IF spellType == 1 OR spellType == 2 BEGIN
		LPF ~appendValue~ INT_VAR strref = 10960001 STR_VAR value = ~%spellLevel%~ RET description END // ~Niveau~
	END
END

DEFINE_PATCH_FUNCTION ~spell_school~ RET description BEGIN
	READ_SHORT SPL_type spellType
	READ_LONG SPL_sectype secondaryType
	READ_BYTE SPL_school spellSchool

	LPF ~get_spell_type_name~ INT_VAR type = spellType RET spellTypeName END
	LPF ~get_spell_secondary_type~ INT_VAR secondaryType opcode = ~-1~ RET spellSecondaryTypeName END

	PATCH_IF spellSchool > 0 BEGIN
		LPF ~get_spell_school_name~ INT_VAR school = spellSchool RET spellSchoolName END
		PATCH_IF STRING_LENGTH ~%spellSecondaryTypeName%~ > 0 BEGIN
		    LPF ~appendLine~ STR_VAR string = ~(%spellTypeName% - %spellSchoolName%, %spellSecondaryTypeName%)~ RET description END
		END
		ELSE BEGIN
		    LPF ~appendLine~ STR_VAR string = ~(%spellTypeName% - %spellSchoolName%)~ RET description END
		END
	END
	ELSE BEGIN
		PATCH_IF STRING_LENGTH ~%spellSecondaryTypeName%~ > 0 BEGIN
		    LPF ~appendLine~ STR_VAR string = ~(%spellTypeName%, %spellSecondaryTypeName%)~ RET description END
        END
        ELSE BEGIN
		    LPF ~appendLine~ STR_VAR string = ~(%spellTypeName%)~ RET description END
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_type_name~ INT_VAR type = 0 RET spellTypeName BEGIN
	PATCH_IF type == 2 BEGIN
		READ_LONG SPL_exclusion_flags exclusionFlags
		SET excludeCleric = (exclusionFlags BAND BIT30) == BIT30
		SET excludeDruid = (exclusionFlags BAND BIT31) == BIT31
		PATCH_IF excludeCleric AND excludeDruid BEGIN
			LPF ~add_log_error~ STR_VAR message = ~Priest spell exclude cleric and druid.~ END
		END
		ELSE PATCH_IF excludeDruid BEGIN
			SET type = 6 // ~Divin~
		END
		ELSE PATCH_IF excludeCleric BEGIN
			SET type = 7 // ~Druidique~
		END
	END
	SET strref = 101320 + type
	LPF ~getTranslation~ INT_VAR strref opcode = 0 RET spellTypeName = string END
END

/*
 * Récupère la portée.
 * TODO: Si le range est différent entre les différents niveaux, afficher une valeur plus précise que "Spéciale"
 *   Ex: 10 mètres + 1 mètre par niveau ?
 */
DEFINE_PATCH_FUNCTION ~spell_range~ RET description BEGIN
	SET base_level = ~-1~
	SET base_range = ~-1~
	SET count = 0
	SET first = 0 - 1

	PATCH_DEFINE_ARRAY ~ranges~ BEGIN END

	PATCH_IF headerCount > 0 BEGIN
	    FOR (headerIndex = 0; headerIndex < headerCount; headerIndex += 1) BEGIN
            SET offset = headerOffset + 0x28 * headerIndex

			READ_BYTE  (offset + SPL_HEAD_target) target
			READ_SHORT (offset + SPL_HEAD_range) range
			READ_SHORT (offset + SPL_HEAD_level_required) requiredLevel

			PATCH_IF target == 5 OR target == 7 BEGIN
				SET range = 0
			END

			PATCH_IF base_level == ~-1~ BEGIN
				SET base_level = requiredLevel
			END
			PATCH_IF base_range == ~-1~ BEGIN
				SET base_range = range
			END

			PATCH_IF first == 0 - 1 BEGIN
				SET first = requiredLevel
			END
			SET $ranges(~%requiredLevel%~) = range
			SET count += 1
	    END
	END

	SET currentRange = $ranges(~%first%~)

	PATCH_PHP_EACH ~ranges~ AS level => levelRange BEGIN
		PATCH_IF IS_AN_INT ~%currentRange%~ AND currentRange != levelRange BEGIN
			SPRINT currentRange @100033 // ~Spéciale~
		END
	END

	PATCH_IF IS_AN_INT ~%currentRange%~ BEGIN
		// Contact jusqu'à un mètre, en décimètres dans toutes les langues : en anglais, feets_to_meters
		// rend la portée en pieds.
		SET rangeDecimeters = currentRange * 10000 / 3281
		LPF ~feets_to_meters~ INT_VAR range = currentRange RET currentRange = rangeToMeter END
		PATCH_IF rangeDecimeters < 11 BEGIN
			SPRINT currentRange @100034 // ~Contact~
		END
	END
	ELSE BEGIN
		PATCH_IF base_range == ~-1~ BEGIN
			SET base_range = 0
		END
		PATCH_IF base_level == 1 BEGIN
			LPF get_first_level_for_spell RET base_level = minLevel END
		END
		LPF ~get_complex_range~
			INT_VAR
				base_level
				base_range
			STR_VAR
				array_name = ~ranges~
			RET
				currentRange = complex_range
		END
	END

	// TODO: @102461 = ~Champ visuel du lanceur~

	LPF ~appendValue~ INT_VAR strref = 102006 STR_VAR value = ~%currentRange%~ RET description END // ~Portée~
END

DEFINE_PATCH_FUNCTION ~get_complex_range~
	INT_VAR
		base_level = 0
		base_range = 0
	STR_VAR
		array_name = ~~
	RET
		complex_range
BEGIN
	SPRINT complex_range ~~

	SET delta_range = 0
	SET delta_level = 0
	SET is_valid = 1
	SET prev_range = base_range
	SET prev_level = base_level
	SET cpt = 0

	PATCH_PHP_EACH ~%array_name%~ AS level => range BEGIN
		// On ignore la première entrée qui n'est pas toujours en harmonie avec le reste
		PATCH_IF cpt > 0 BEGIN
			PATCH_IF delta_range = 0 BEGIN
				SET delta_range = range - prev_range
				SET delta_level = level - prev_level
			END
			ELSE PATCH_IF delta_range != range - prev_range OR delta_level != level - prev_level BEGIN
				SET is_valid = 0
			END
			SET prev_level = level
		END
		SET prev_range = range
		SET cpt += 1
	END

	PATCH_IF is_valid == 1 BEGIN
		PATCH_IF base_range > 0 AND delta_range == 0 BEGIN
			LPF ~feets_to_meters~ INT_VAR range = base_range RET complex_range = rangeToMeter END
		END
		ELSE BEGIN
			LPF ~feets_to_meters~ INT_VAR range = delta_range RET deltaRange = rangeToMeter END

			PATCH_IF delta_level == 1 BEGIN
				SPRINT complex_range ~%deltaRange% par niveau~
			END
			ELSE BEGIN
				SPRINT complex_range ~%deltaRange% par tranche de %delta_level% niveaux~
			END
			SET remains_range = range - (delta_range * level / delta_level)
			PATCH_IF remains_range > 0 BEGIN
				LPF ~feets_to_meters~ INT_VAR range = remains_range RET remainsRange = rangeToMeter END
				SPRINT complex_range ~%remainsRange% + %complex_range%~
			END
			// TODO: Ajouter le "à partir du xxème" "1 round + 2 rounds par tranche de 3 niveaux à partir du 12ème"
			// TODO: Ajouter le "jusqu'au niveau xx"
		END
	END
	ELSE BEGIN
		SPRINT complex_range @100033 // ~Spéciale~
	END
END

DEFINE_PATCH_FUNCTION ~spell_duration~ STR_VAR subspellsDuration = ~~ RET description ignoreDuration strDuration is_special has_duration is_instant BEGIN
	SET base_duration = ~-1~
	SET has_duration = 1
	SET isValid = 1
	SET is_special = 0
	SET is_instant = ~-1~
	SET count_levels = 0
	SPRINT strDuration ~~

    PATCH_DEFINE_ARRAY levels BEGIN END
    PATCH_DEFINE_ARRAY all_durations BEGIN END

	PATCH_PHP_EACH level_effects AS index => requiredLevel BEGIN
		PATCH_IF isValid == 1 BEGIN
			SET $levels(~%count_levels%~) = requiredLevel
			SET count_levels += 1
			PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
				// Si plus petit, c'est qu'on a désactivé l'entrée lors d'une précédente opération
				PATCH_IF opcode >= 0 BEGIN
				    LPM ~data_to_vars~
				    SET subScan = VARIABLE_IS_SET subspellsScan AND subspellsScan
				    SET isProtection = opcode == 318 OR opcode == 321 OR opcode == 324 OR (subScan AND opcode == 206)
				    SET protectsCaster = 0
				    PATCH_IF isProtection AND subScan AND NOT ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ BEGIN
				        LPF ~spell_refers_to_resource~ STR_VAR spell = ~%resref%~ resource = ~%CURRENT_SOURCE_RES%~ RET protectsCaster = found END
				    END
				    PATCH_IF NOT (isProtection AND (~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~ OR protectsCaster)) BEGIN
	                    PATCH_IF VARIABLE_IS_SET itemDuration AND (opcode == 146 OR opcode == 232) BEGIN
							PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
								INNER_PATCH_FILE ~%resref%.spl~ BEGIN
									//lire les opcodes de l'item et les ajouter dans les opcodes actuels
								    GET_OFFSET_ARRAY offsets SPL_V10_GEN_EFFECTS
								    PHP_EACH offsets AS _ => offset BEGIN
									    LPM ~read_effect_vars~
									    // Ne dure que le temps que l'arme est équipée
									    SET duration = itemDuration
									    SET timingMode = itemTimingMode
								    END
								END
							END
	                    END

	                    PATCH_IF timingMode == TIMING_duration_ticks BEGIN
	                        SET duration = duration / 15
	                    END
	                    ELSE PATCH_IF timingMode == TIMING_delayed BEGIN
	                        SET duration = 0
	                        PATCH_IF VARIABLE_IS_SET $opcodes_ignore_duration(~%opcode%~) OR VARIABLE_IS_SET $opcodes_cant_be_permanent(~%opcode%~) BEGIN
	                            PATCH_IF is_instant == 0 - 1 BEGIN
	                                SET is_instant = 1
	                            END
	                        END
	                        ELSE PATCH_IF is_instant == 1 BEGIN
	                            SET is_instant = 0
	                        END
	                    END
						ELSE PATCH_IF timingMode == 5000 OR timingMode == 5001 BEGIN
							SET duration = duration MODULO 10000
						END
	                    ELSE PATCH_IF timingMode != TIMING_duration AND timingMode != TIMING_duration_ticks AND timingMode != TIMING_delayed_duration BEGIN
	                        SET duration = 0
	                        PATCH_IF VARIABLE_IS_SET $opcodes_ignore_duration(~%opcode%~) OR VARIABLE_IS_SET $opcodes_cant_be_permanent(~%opcode%~) BEGIN
	                            PATCH_IF is_instant == 0 - 1 BEGIN
	                                SET is_instant = 1
	                            END
	                        END
	                        ELSE PATCH_IF is_instant == 1 BEGIN
	                            SET is_instant = 0
	                        END
	                    END

	                    PATCH_IF opcode == 217 BEGIN
	                        SET duration = 30
	                    END

	                    PATCH_IF opcode == 213 BEGIN
	                        SET is_special = 1
	                    END

	                    PATCH_IF duration > 0 AND NOT (~%complex_duration%~ STRING_CONTAINS_REGEXP ~ 1d[0-9]~) BEGIN
	                        SET isValid = 0
	                    END

	                    PATCH_IF duration > 0 BEGIN
	                        PATCH_IF base_duration == ~-1~ BEGIN
	                            SET base_duration = duration
	                        END

	                        PATCH_IF NOT VARIABLE_IS_SET $all_durations(~%requiredLevel%~) BEGIN
	                            SET $all_durations(~%requiredLevel%~) = duration
	                        END

	                        PATCH_IF $all_durations(~%requiredLevel%~) != duration BEGIN
	                            SET isValid = 0
	                        END
	                    END
	                END
				END
			END
		END
	END

    PATCH_IF is_special == 1 BEGIN
        SPRINT duration @100033 // ~Spéciale~
    END
	ELSE PATCH_IF isValid == 1 BEGIN
	    SET durationByProjectile = 0
		PATCH_IF count_levels == 1 BEGIN // Ex: SPPR250
			LPF ~get_spell_duration_by_projectile~ RET is_special_by_projectile = is_special is_permanent_by_projectile = is_permanent duration END
			PATCH_IF NOT is_special_by_projectile BEGIN
			    SET durationByProjectile = 1
				SET ignoreDuration = 1
				SET is_permanent = is_permanent_by_projectile
				SET is_special = is_special_by_projectile
				SPRINT strDuration ~%duration%~
			END
		END
		PATCH_IF durationByProjectile == 0 BEGIN
            LPF ~get_complex_duration~
                STR_VAR
                    array_name = ~all_durations~
                RET
                    is_special
                    is_permanent
                    duration = complex_duration
            END
		END
		PATCH_IF NOT is_special BEGIN
			SET ignoreDuration = 1
			SPRINT strDuration ~%duration%~
		END
		ELSE BEGIN
			SPRINT duration @100033 // ~Spéciale~
		END
		PATCH_IF is_permanent BEGIN
		    SET has_duration = 0

		    PATCH_IF is_instant == 1 BEGIN
			    SPRINT duration @100038 // ~Instantanée~
			    PATCH_IF NOT ~%subspellsDuration%~ STRING_EQUAL ~~ BEGIN
				    SPRINT duration ~%subspellsDuration%~
				    SPRINT strDuration ~%subspellsDuration%~
				    SET has_duration = 1
			    END
		    END
		    ELSE BEGIN
			    SPRINT duration @100037 // ~Permanente~
		    END
		END
	END
	ELSE BEGIN
		PATCH_IF count_levels == 1 BEGIN // Ex: SPPR250
			LPF ~get_spell_duration_by_projectile~ RET is_special is_permanent duration END
			PATCH_IF NOT is_special BEGIN
				SET ignoreDuration = 1
				SPRINT strDuration ~%duration%~
			END
		END
		ELSE BEGIN
			SET is_special = 1
		END
		PATCH_IF is_special BEGIN
			SPRINT duration @100033 // ~Spéciale~
		END
	END

	LPF ~appendValue~ INT_VAR strref = 100031 STR_VAR value = ~%duration%~ RET description END // ~Durée~
END

DEFINE_PATCH_FUNCTION ~spell_refers_to_resource~
	STR_VAR
		spell = ~~
		resource = ~~
	RET
		found
BEGIN
	SET found = 0
	PATCH_IF NOT ~%spell%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~%spell%.spl~ BEGIN
		INNER_PATCH_FILE ~%spell%.spl~ BEGIN
			GET_OFFSET_ARRAY refersHeaders SPL_V10_HEADERS
			PHP_EACH refersHeaders AS _ => refersHeader BEGIN
				GET_OFFSET_ARRAY2 refersEffects refersHeader SPL_V10_HEAD_EFFECTS
				PHP_EACH refersEffects AS _ => offset BEGIN
					LPM ~read_effect_vars~
					PATCH_IF ~%resref%~ STRING_EQUAL_CASE ~%resource%~ BEGIN
						SET found = 1
					END
				END
			END
		END
	END
END

DEFINE_PATCH_FUNCTION ~subspells_common_duration~
	RET
		subspells_duration
BEGIN
	SPRINT subspells_duration ~~
	SPRINT spellSelf ~%CURRENT_SOURCE_RES%~
	SET subValid = 1
	GET_OFFSET_ARRAY subHeaders SPL_V10_HEADERS
	PHP_EACH subHeaders AS _ => subHeader BEGIN
		GET_OFFSET_ARRAY2 subEffects subHeader SPL_V10_HEAD_EFFECTS
		PHP_EACH subEffects AS _ => offset BEGIN
			PATCH_IF subValid BEGIN
				LPM ~read_effect_vars~
				PATCH_IF opcode == 146 OR opcode == 148 BEGIN
					// Type 1 : lancé au niveau du lanceur quel que soit parameter1 (IESDP).
					PATCH_IF (timingMode == TIMING_delayed AND duration > 0) OR (parameter1 > 0 AND parameter2 != 1)
							OR ~%resref%~ STRING_EQUAL_CASE ~%spellSelf%~ OR NOT FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
						SET subValid = 0
					END
					ELSE BEGIN
						INNER_PATCH_FILE ~%resref%.spl~ BEGIN
							SPRINT CURRENT_SOURCE_RES ~%resref%~
							SET isSubSpell = 1
							SET ignoreDuration = 0
							SET subspellsScan = 1
							LPM ~load_level_effects~
							LPF ~spell_duration~ RET subIgnoreDuration = ignoreDuration subDuration = strDuration subSpecial = is_special subHasDuration = has_duration subInstant = is_instant END
							LPM ~clear_levels~
						END
						PATCH_IF subSpecial OR NOT subIgnoreDuration BEGIN
							SET subValid = 0
						END
						// Un sous-sort permanent écrit « de manière permanente » dans ses lignes.
						ELSE PATCH_IF NOT subHasDuration BEGIN
							SET subValid = subInstant == 1
						END
						ELSE PATCH_IF ~%subspells_duration%~ STRING_EQUAL ~~ BEGIN
							SPRINT subspells_duration ~%subDuration%~
						END
						ELSE PATCH_IF NOT ~%subspells_duration%~ STRING_EQUAL ~%subDuration%~ BEGIN
							SET subValid = 0
						END
					END
				END
				ELSE PATCH_IF opcode == 177 OR opcode == 251 OR opcode == 252 BEGIN
					SET subValid = 0
				END
			END
		END
	END
	PATCH_IF NOT subValid BEGIN
		SPRINT subspells_duration ~~
	END
END

DEFINE_PATCH_FUNCTION ~get_spell_duration_by_projectile~
	RET
		is_special
		is_permanent
		duration
BEGIN
	SET is_special = 1
	SET is_permanent = 0
	SPRINT duration ~~

    PATCH_DEFINE_ARRAY all_projectile_durations BEGIN END

	PATCH_PHP_EACH level_effects AS index => requiredLevel BEGIN
		SET projectile = $level_projectiles(~%index%~)
		PATCH_IF projectile > 1 BEGIN
			SET projectile -= 1
			LOOKUP_IDS_SYMBOL_OF_INT projectileFile ~projectl~ projectile
			PATCH_IF !IS_AN_INT projectileFile BEGIN
				INNER_PATCH_FILE ~%projectileFile%.pro~ BEGIN
	                READ_SHORT 0x8 type
	                PATCH_IF type == 3 BEGIN
						READ_SHORT 0x210 explosionDelay // 100 = 1 round
						READ_BYTE 0x216 triggerCount
						PATCH_IF triggerCount > 1 BEGIN
							SET duration = 6 * explosionDelay * triggerCount / 100
							PATCH_IF NOT VARIABLE_IS_SET $all_projectile_durations(~%requiredLevel%~) BEGIN
								SET $all_projectile_durations(~%requiredLevel%~) = duration
								SET is_special = 0
							END
						END
					END
				END
			END
		END
	END
	PATCH_IF is_special == 0 BEGIN
		LPF ~get_complex_duration~
			STR_VAR
				array_name = ~all_projectile_durations~
			RET
				is_special
				is_permanent
				duration = complex_duration
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_complex_duration~
	STR_VAR
		array_name = ~~
	RET
		is_special
		is_permanent
		complex_duration
BEGIN
	SPRINT complex_duration ~~

	SET base_duration = 0
	SET delta_duration = 0
	SET delta_level = 0
	SET is_valid = 1
	SET is_special = 0
	SET is_permanent = 0
	SET prev_duration = 0
	SET cpt = 0

	PATCH_PHP_EACH ~%array_name%~ AS level => duration BEGIN
		PATCH_IF level <= 1 BEGIN
			LPF get_first_level_for_spell RET level = minLevel END
		END
		// On ignore la première entrée qui n'est pas toujours en harmonie avec le reste
		PATCH_IF cpt > 1 AND prev_duration != duration BEGIN
			PATCH_IF delta_duration = 0 BEGIN
				SET delta_duration = duration - prev_duration
				SET delta_level = level - prev_level
			END
			ELSE PATCH_IF delta_duration != duration - prev_duration OR delta_level != level - prev_level BEGIN
				SET is_valid = 0
			END
		END
		ELSE BEGIN
			SET base_duration = duration
		END
		PATCH_IF prev_duration != duration BEGIN
			SET prev_duration = duration
			SET prev_level = level
		END
		SET cpt += 1
	END

	PATCH_IF is_valid == 0 BEGIN
		SET is_valid = 1
		SET cpt = 0
		SET prev_duration = 0
		SET base_duration = 0
		SET delta_duration = 0
		SET delta_level = 0
		PATCH_PHP_EACH ~%array_name%~ AS level => duration BEGIN
			PATCH_IF level <= 1 BEGIN
				LPF get_first_level_for_spell RET level = minLevel END
			END
			// On ignore la première entrée qui n'est pas toujours en harmonie avec le reste
			PATCH_IF cpt > 1 AND prev_duration != duration BEGIN
				PATCH_IF delta_duration = 0 BEGIN
					SET delta_duration = duration - prev_duration
					SET delta_level = level - prev_level
				END
				ELSE PATCH_IF delta_duration != duration - prev_duration OR delta_level != level - prev_level BEGIN
					SET is_valid = 0
				END
			END
			ELSE BEGIN
				SET base_duration = duration
				SET prev_level = level
			END
			PATCH_IF prev_duration != duration BEGIN
				SET prev_duration = duration
				SET prev_level = level
			END
			SET cpt += 1
		END
	END

	PATCH_IF cpt == 2 BEGIN
		SET cpt = 0
		SET delta_duration = 0
		SET delta_level = 0
		PATCH_PHP_EACH ~%array_name%~ AS level => duration BEGIN
			PATCH_IF level <= 1 BEGIN
				LPF get_first_level_for_spell RET level = minLevel END
			END
			PATCH_IF cpt > 0 BEGIN
				PATCH_IF delta_duration = 0 BEGIN
					SET delta_duration = duration - prev_duration
					SET delta_level = level - prev_level
				END
			END
			ELSE BEGIN
				SET base_duration = duration
			END
			SET prev_duration = duration
			SET prev_level = level
			SET cpt += 1
		END
		LPF ~get_str_duration~ INT_VAR duration = base_duration RET baseValue = strDuration END
		LPF ~get_str_duration~ INT_VAR duration = delta_duration RET value = strDuration END
		SPRINT complex_duration @102160 // ~%baseValue% + %value% au niveau %level%~
	END
	ELSE PATCH_IF is_valid == 1 BEGIN
		PATCH_IF base_duration == 0 AND delta_duration == 0 BEGIN
			SET is_permanent = 1
		END
		ELSE PATCH_IF base_duration > 0 AND delta_duration == 0 BEGIN
			LPF ~get_str_duration~ INT_VAR duration = base_duration RET complex_duration = strDuration END
		END
		ELSE BEGIN
			LPF ~get_str_duration~ INT_VAR duration = delta_duration RET value = strDuration END
			PATCH_IF delta_level == 1 BEGIN
				SPRINT complex_duration @102161 // ~%value% par niveau~
			END
			ELSE BEGIN
				SET level = delta_level
				SPRINT complex_duration @102162 // ~%value% par tranche de %level% niveaux~
			END
			SET remains_duration = duration - (delta_duration * prev_level / delta_level)
			PATCH_IF remains_duration > 0 BEGIN
				LPF ~get_str_duration~ INT_VAR duration = remains_duration RET remainsDuration = strDuration END
				SPRINT complex_duration ~%remainsDuration% + %complex_duration%~
			END
			// TODO: Ajouter le "à partir du xxème" "1 round + 2 rounds par tranche de 3 niveaux à partir du 12ème"
			// TODO: Ajouter le "jusqu'au niveau xx"
		END
	END
	ELSE BEGIN
		SET is_special = 1
	END
END

// untyped : valeur sans l'unité de l'opcode (opcode_<N>_typed_value), pour un bonus de jet de sauvegarde.
DEFINE_PATCH_FUNCTION ~get_complex_value~
	INT_VAR
		is_percent = 0
		is_flat_value = 0
		dice_sides = 0
		no_two_values = 0
		untyped = 0
	STR_VAR
		array_name = ~~
	RET
		is_valid
		complex_value
		complex_value_int
BEGIN
	SPRINT complex_value ~~
	SET complex_value_int = 0

	SET is_valid = 1

	SET base_value = 0
	SET last_value = 0
	SET delta_value = 0
	SET delta_level = 0
	SET prev_value = 0
	SET prev_level = 0
	SET cpt = 0

	// Nombre de valeurs distinctes : no_two_values refuse une série de deux valeurs, que les passes
	// suivantes peuvent ajuster à une formule fausse (« -1 + 2 par tranche de 9 niveaux » pour -2 et -4).
	SET distinct_values = 0
	CLEAR_ARRAY distinct_seen
	PATCH_PHP_EACH ~%array_name%~ AS _ => value BEGIN
		PATCH_IF NOT VARIABLE_IS_SET $distinct_seen(~%value%~) OR $distinct_seen(~%value%~) == 0 BEGIN
			SET $distinct_seen(~%value%~) = 1
			SET distinct_values += 1
		END
	END
	PATCH_PHP_EACH distinct_seen AS distinct_key => _ BEGIN
		SET $distinct_seen(~%distinct_key%~) = 0
	END

	PATCH_PHP_EACH ~%array_name%~ AS level => value BEGIN
		PATCH_IF level <= 1 BEGIN
			LPF get_first_level_for_spell RET level = minLevel END
		END
		// On ignore la première entrée qui n'est pas toujours en harmonie avec le reste
		PATCH_IF cpt > 0 BEGIN
			PATCH_IF value != prev_value BEGIN
				PATCH_IF delta_value = 0 BEGIN
					SET delta_value = value - prev_value
					SET delta_level = level - prev_level
				END
				ELSE PATCH_IF delta_value != value - prev_value OR delta_level != level - prev_level BEGIN
					SET is_valid = 0
				END
			END
		END
		ELSE BEGIN
			SET base_value = value
		END
		PATCH_IF prev_level == 0 OR value != prev_value BEGIN
			SET prev_level = level
			SET cpt += 1
		END
		SET prev_value = value
	END

	// delta_level est calculé qu'au moment où la valeur est modifiée (cas de la même valeur consécutive à travers les niveaux)
	PATCH_IF is_valid == 0 BEGIN
		SET is_valid = 1
		SET cpt = 0
		SET prev_value = 0
		SET prev_level = 0
		SET base_value = 0
		SET delta_value = 0
		SET delta_level = 0
		PATCH_PHP_EACH ~%array_name%~ AS level => value BEGIN
			PATCH_IF level <= 1 BEGIN
				LPF get_first_level_for_spell RET level = minLevel END
			END
			PATCH_IF cpt > 1 AND prev_value != value BEGIN
				PATCH_IF delta_value = 0 BEGIN
					SET delta_value = value - prev_value
					SET delta_level = level - prev_level
				END
				ELSE PATCH_IF delta_value != value - prev_value OR delta_level != level - prev_level BEGIN
					SET is_valid = 0
				END
			END
			ELSE BEGIN
				SET base_value = value
			END
			PATCH_IF prev_value != value BEGIN
				SET prev_value = value
				SET prev_level = level
			END
			SET cpt += 1
		END
	END
	// On tente avec le delta_level qui ne tient pas compte du premier niveau.
	PATCH_IF is_valid == 0 BEGIN
		SET is_valid = 1
		SET cpt = 0
		SET prev_value = 0
		SET prev_level = 0
		SET base_value = 0
		SET delta_value = 0
		SET delta_level = 0
		PATCH_PHP_EACH ~%array_name%~ AS level => value BEGIN
			PATCH_IF level <= 1 BEGIN
				LPF get_first_level_for_spell RET level = minLevel END
			END
			PATCH_IF cpt > 1 AND prev_value != value BEGIN
				PATCH_IF delta_value = 0 BEGIN
					SET delta_value = value - prev_value
					SET delta_level = level - prev_level + 1
				END
				ELSE PATCH_IF delta_value != value - prev_value OR delta_level != level - prev_level BEGIN
					SET is_valid = 0
				END
			END
			ELSE BEGIN
				SET base_value = value
			END
			PATCH_IF prev_value != value BEGIN
				SET prev_value = value
				SET prev_level = level
			END
			SET cpt += 1
		END
	END
	// On tente en ignorant totalement la 1ère en-tête, et en vérifiant 2 delta_level différent.
	PATCH_IF is_valid == 0 BEGIN
		SET is_valid = 1
		SET cpt = 0
		SET prev_value = 0
		SET prev_level = 0
		SET base_value = 0
		SET delta_value = 0
		SET delta_level = 0
		PATCH_PHP_EACH ~%array_name%~ AS level => value BEGIN
			PATCH_IF level <= 1 BEGIN
				LPF get_first_level_for_spell RET level = minLevel END
			END
			PATCH_IF cpt > 1 AND prev_value != value BEGIN
				PATCH_IF delta_value = 0 BEGIN
					SET delta_value = value - prev_value
					SET delta_level = level - prev_level
				END
				ELSE PATCH_IF delta_value != value - prev_value OR (delta_level != level - prev_level AND delta_level + 1 != level - prev_level) BEGIN
					SET is_valid = 0
				END
			END
			ELSE BEGIN
				SET base_value = value
			END
			PATCH_IF prev_value != value OR cpt < 2 BEGIN
				SET prev_value = value
				SET prev_level = level
			END
			SET cpt += 1
		END
	END

	PATCH_IF (cpt == 2 OR distinct_values == 2) AND no_two_values BEGIN
		SET is_valid = 0
	END
	ELSE PATCH_IF cpt == 2 BEGIN
		SET cpt = 0
		SET delta_value = 0
		SET delta_level = 0
		PATCH_PHP_EACH ~%array_name%~ AS level => value BEGIN
			PATCH_IF level <= 1 BEGIN
				LPF get_first_level_for_spell RET level = minLevel END
			END
			PATCH_IF cpt > 0 BEGIN
				PATCH_IF delta_value = 0 BEGIN
					SET delta_value = value - prev_value
					SET delta_level = level - prev_level
				END
			END
			ELSE BEGIN
				SET base_value = value
			END
			PATCH_IF prev_value != value BEGIN
				SET prev_level = level
			END
			SET prev_value = value
			SET cpt += 1
		END
		PATCH_IF base_value > 0 AND prev_value == 0 BEGIN
			PATCH_IF is_percent BEGIN
				SPRINT value ~%base_value%~
				SPRINT base_value @10002 // ~%value% %~
			END
			SET level = prev_level - 1
			SPRINT baseValue ~%base_value%~
			SPRINT complex_value @102167 // ~%baseValue% jusqu'au niveau %level%~
		END
		ELSE BEGIN
			PATCH_IF is_percent BEGIN
				SPRINT value ~%base_value%~
				SPRINT base_value @10002 // ~%value% %~
				SPRINT value ~%delta_value%~
				SPRINT delta_value @10002 // ~%value% %~
			END
			SPRINT baseValue ~%base_value%~
			SPRINT value ~%delta_value%~
			// Niveau du changement, et non le dernier parcouru.
			SET level = prev_level
			SPRINT complex_value @102160 // ~%baseValue% + %value% au niveau %level%~
		END
	END
	ELSE PATCH_IF is_valid == 1 BEGIN
		SET strref = 0
		PATCH_IF NOT untyped BEGIN
			SPRINT dispatch_typed_value ~opcode_%opcode%_typed_value~
			PATCH_TRY LPF ~%dispatch_typed_value%~ INT_VAR value = delta_value RET strref END WITH DEFAULT
				strref = 0
				PATCH_IF show_swallowed_errors BEGIN LPF ~log_swallowed_error~ STR_VAR name = ~%dispatch_typed_value%~ type = ~function~ error = ~%ERROR_MESSAGE%~ END END
			END
		END
		SET last_value = value
		SET value = ABS delta_value
		SET complex_value_int = base_value
		PATCH_IF dice_sides > 0 BEGIN
			SET diceCount = value
			SET diceSides = dice_sides
			SPRINT value @10014 // ~%diceCount%d%diceSides%~
		END
		ELSE BEGIN
			SET value = delta_value
		END
		PATCH_IF base_value > 0 AND delta_value == 0 BEGIN
			LPF ~get_complex_typed_value~ INT_VAR is_percent strref STR_VAR value = ~%base_value%~ RET complex_value = value END
			PATCH_IF is_flat_value == 1 BEGIN
				SET base_value = prev_level + last_value
				SPRINT complex_value ~%base_value% %complex_value%~
			END
		END
		ELSE BEGIN
			PATCH_IF delta_level != 0 BEGIN
				SET levelMax = prev_level
				// Reste au niveau du dernier changement : un dernier en-tête à la même valeur ne le change pas.
				SET remains_value = ABS prev_value - (ABS delta_value * prev_level / delta_level)
				LPF ~get_complex_typed_value~ INT_VAR is_percent strref STR_VAR value RET value END
				// Valeur fixée qui décroît : la valeur au niveau 0, d'après la dernière et le pas (« Passe à 21 -1
				// par niveau », « Passe à 6 -1 par tranche de 4 niveaux »).
				PATCH_IF is_flat_value == 1 AND delta_value < 0 BEGIN
					SET base_value = last_value + (ABS delta_value) * prev_level / delta_level
					SPRINT value ~%base_value% %value%~
				END
				PATCH_IF ABS delta_level == 1 BEGIN
					SPRINT complex_value @102163 // ~%value% par niveau/%levelMax%~
				END
				ELSE PATCH_IF delta_level != 0 BEGIN
					SET level = delta_level
					SPRINT complex_value @102164 // ~%value% par tranche de %level% niveaux/%levelMax%~
				END
				PATCH_IF remains_value > 0 BEGIN
					PATCH_IF dice_sides > 0 BEGIN
						SET diceCount = remains_value
						SET diceSides = dice_sides
						SPRINT remains_value @10014 // ~%diceCount%d%diceSides%~
					END
					PATCH_IF is_percent BEGIN
						SPRINT value ~%remains_value%~
						SPRINT remains_value @10002 // ~%value% %~
					END
					PATCH_IF delta_level < 0 BEGIN
						SPRINT complex_value ~%remains_value% %complex_value%~
					END
					ELSE BEGIN
						INNER_PATCH_SAVE complex_value ~%complex_value%~ BEGIN
	                        REPLACE_TEXTUALLY EVALUATE_REGEXP ~^- ~ ~~
	                        REPLACE_TEXTUALLY EVALUATE_REGEXP ~^-~ ~~
	                    END
						PATCH_IF untyped AND delta_value < 0 AND prev_value < 0 BEGIN
							SPRINT complex_value ~-%remains_value% - %complex_value%~
						END
						ELSE BEGIN
							SPRINT complex_value ~%remains_value% + %complex_value%~
						END
					END
				END
			END
			ELSE BEGIN
				SPRINT complex_value ~%base_value%~
			END
			// TODO: Ajouter le "à partir du xxème" "1 round + 2 rounds par tranche de 3 niveaux à partir du 12ème"
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_complex_typed_value~ INT_VAR strref = 0 STR_VAR value = 0 RET value BEGIN
	PATCH_IF strref > 0 BEGIN
		PATCH_IF is_percent BEGIN
			SPRINT value ~%value%~
			SPRINT value @10002 // ~%value% %~
		END
		SPRINT valueType (AT strref)
		SPRINT value @102165 // ~%value% %valueType%~
	END
	ELSE BEGIN
		PATCH_IF is_percent BEGIN
			SPRINT value ~%value%~
			SPRINT value @10002 // ~%value% %~
		END
	END
END

DEFINE_PATCH_FUNCTION ~spell_casting_time~ RET description BEGIN
	SET count = 0

	PATCH_DEFINE_ARRAY ~castingTimes~ BEGIN END

	PATCH_IF headerCount > 0 BEGIN
	    FOR (headerIndex = 0; headerIndex < headerCount; headerIndex += 1) BEGIN
            SET offset = headerOffset + 0x28 * headerIndex

			READ_SHORT (offset + SPL_HEAD_casting_time) castingTime

			SET $castingTimes(~%count%~) = castingTime
			SET count += 1
	    END
	END

	SET currentCastingTime = $castingTimes(~0~)

	FOR (i = 1 ; i < count ; ++i ) BEGIN
		PATCH_IF currentCastingTime != $castingTimes(~%i%~) BEGIN
			SPRINT currentCastingTime @100032 // ~Spécial~
			SET i = count
		END
	END

	LPF ~appendValue~ INT_VAR strref = 11890001 STR_VAR value = ~%currentCastingTime%~ RET description END // ~Temps d'incantation~
END

DEFINE_PATCH_FUNCTION ~spell_target~ RET description spellTarget BEGIN
	SET count = 0
	SPRINT spellTarget ~area~

	PATCH_DEFINE_ARRAY ~targets~ BEGIN END

	PATCH_IF headerCount > 0 BEGIN
	    FOR (headerIndex = 0; headerIndex < headerCount; headerIndex += 1) BEGIN
            SET offset = headerOffset + 0x28 * headerIndex

			READ_BYTE (offset + SPL_HEAD_target) target

			LPF ~spell_target_by_projectile~ INT_VAR target RET areaTarget END

			PATCH_IF ~%areaTarget%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF target == TARGET_HEAD_self OR target == TARGET_HEAD_self_ignore_pause BEGIN
					SPRINT areaTarget @102467 // ~Le lanceur~
	                SPRINT spellTarget ~self~
				END
				ELSE PATCH_IF target == TARGET_HEAD_creature BEGIN
                    READ_BYTE (offset + SPL_HEAD_target_number) countTarget
                    PATCH_IF countTarget <= 1 BEGIN
                        SPRINT areaTarget @102466 // ~1 créature~
	                    SPRINT spellTarget ~creature~
                    END
                    ELSE BEGIN
                        SPRINT areaTarget @102465 // ~%countTarget% créatures~
	                    SPRINT spellTarget ~creatures~
                    END
                END
				ELSE PATCH_IF target == TARGET_HEAD_area BEGIN
					SPRINT areaTarget @102462 // ~Point dans le champ visuel du lanceur~
				END
				ELSE PATCH_IF target == TARGET_HEAD_character_portrait BEGIN
					SPRINT areaTarget @102466 // ~1 créature~
	                SPRINT spellTarget ~creature~
				END
			END

			SPRINT $targets(~%count%~) ~%areaTarget%~
			SET count += 1
	    END
	END

	SPRINT currentTarget $targets(~0~)

	FOR (i = 1 ; i < count ; ++i ) BEGIN
		PATCH_IF NOT ~%currentTarget%~ STRING_EQUAL $targets(~%i%~) BEGIN
			SPRINT currentTarget @100032 // ~Spécial~
			SET i = count
		END
	END

	LPF ~appendValue~ INT_VAR strref = 100035 STR_VAR value = ~%currentTarget%~ RET description END // ~Zone d'effet~
END


DEFINE_PATCH_FUNCTION ~get_target_by_projectile~
	INT_VAR
		projectile = 0
		target = 0
		targetNumber = 0
		sourceExcluded = 0
	STR_VAR
		theTarget = ~~
		ofTheTarget = ~~
		toTheTarget = ~~
	RET
		theTarget ofTheTarget toTheTarget
BEGIN
	SET strref = 0
	SET targetOffset = 0

	PATCH_IF projectile > 1 BEGIN
		SET projectile -= 1
		LOOKUP_IDS_SYMBOL_OF_INT projectileFile ~projectl~ projectile

        PATCH_IF !IS_AN_INT projectileFile BEGIN
            INNER_PATCH_FILE ~%projectileFile%.pro~ BEGIN
                READ_SHORT 0x8 type
                PATCH_IF type == 3 BEGIN
					READ_LONG  0xc   sparkingFlags
					READ_LONG  0x2c  extendedFlags
					READ_LONG  0x200 areaProjectileFlags
                    READ_SHORT 0x206 areaOfEffect
                    READ_SHORT 0x224 coneWidth

					//LinedUpAreaOfEffect 0x2c BIT14
					//RectangularAreaOfEffect 0x2c BIT15 (longeur = 0x204, largeur = 0x206) (Prioritaire sur LinedUpAreaOfEffect)
					//CasterAffected 0x2c BIT31

					SET ignoreTarget = (sparkingFlags BAND BIT4) == BIT4
					SET enemiesOnly = (areaProjectileFlags BAND BIT6) == BIT6
					SET alliesOnly = (areaProjectileFlags BAND BIT7) == BIT7
					SET isConeShape = (areaProjectileFlags BAND BIT11) == BIT11

                    // On divise par 8.5 pour avoir le diamètre en pied, et encore par 2 pour avoir le rayon
                    PATCH_IF isConeShape BEGIN
                        SET areaOfEffect = areaOfEffect * 10 / 85
                    END
                    ELSE BEGIN
                        SET areaOfEffect /= 17
                    END
                    LPF ~feets_to_meters~ INT_VAR range = areaOfEffect RET range = rangeToMeter END

					PATCH_IF VARIABLE_IS_SET rangeProgression AND NOT ~%rangeProgression%~ STRING_EQUAL ~~ BEGIN
						SPRINT range ~%rangeProgression%~
					END

					PATCH_IF alliesOnly AND enemiesOnly BEGIN
						SET targetOffset = 2
					END
					ELSE PATCH_IF enemiesOnly BEGIN
						SET targetOffset = 1
					END

					PATCH_IF isConeShape BEGIN
						SET angle = coneWidth
						PATCH_IF angle == 0 BEGIN
							SET strref = 102800 // ~%target% dans un rayon de %range%~
						END
						ELSE BEGIN
							SET strref = 102802 // ~%target% dans un cône de %range% sur un arc de %angle%°~
						END
					END
					ELSE BEGIN
						PATCH_IF target == TARGET_HEAD_self OR target == TARGET_HEAD_self_ignore_pause BEGIN
							PATCH_IF ignoreTarget OR enemiesOnly BEGIN
								SET strref = 102801 // ~%target% dans un rayon de %range% autour %ofTheTarget%~
							END
							ELSE BEGIN
								SET strref = 102803 // ~%main_target% et %target% dans un rayon de %range%~
							END
						END
						ELSE PATCH_IF target == TARGET_HEAD_creature BEGIN
							PATCH_IF targetNumber <= 1 BEGIN
								PATCH_IF ignoreTarget BEGIN
									SET strref = 102801 // ~%target% dans un rayon de %range% autour %ofTheTarget%~
								END
								ELSE BEGIN
									SET strref = 102803 // ~%main_target% et %target% dans un rayon de %range%~
								END
							END
							ELSE BEGIN
								SET targetOffset += 3
							END
						END
						ELSE PATCH_IF target == TARGET_HEAD_area BEGIN
							SET strref = 102800 // ~%target% dans un rayon de %range%~
						END
						ELSE BEGIN
							// TODO: TARGET_HEAD_character_portrait // dead actor 1 objet ou une créature morte
							LPF ~add_log_warning~ STR_VAR message = EVAL ~Cible à gerer : %target% ~ END
						END
					END
					// Cible principale qui est la source, dont l'effet l'excepte (sourceExcluded, ligne 43 de
					// splprot.2da) : seules les créatures de la zone (SPWM101 : « Repousse les créatures dans un
					// rayon de 2,5 mètres… », et non « le lanceur et les créatures »).
					PATCH_IF strref == 102803 AND sourceExcluded AND VARIABLE_IS_SET theSource BEGIN
						PATCH_IF ~%theTarget%~ STRING_EQUAL ~%theSource%~ BEGIN
							SET strref = 102800 // ~%target% dans un rayon de %range%~
						END
					END
					// Cible nommée par un type de créature (opcode_set_target_strings) : la zone la restreint
					// (SPPR515 : « les morts-vivants dans un rayon de 2,5 mètres »).
					SET versusNamed = VARIABLE_IS_SET onlyForTheTarget
					PATCH_IF versusNamed BEGIN
						SET versusNamed = NOT ~%onlyForTheTarget%~ STRING_EQUAL ~~ AND ~%onlyForTheTarget%~ STRING_EQUAL ~%theTarget%~
					END
					PATCH_IF strref > 0 AND versusNamed AND NOT isConeShape BEGIN
						SET strref = 102800 // ~%target% dans un rayon de %range%~
						SPRINT target ~%theTarget%~
						SPRINT theTarget (AT strref)
						SPRINT target ~%toTheTarget%~
						SPRINT toTheTarget (AT strref)
						SPRINT target ~%ofTheTarget%~
						SPRINT ofTheTarget (AT strref)
					END
					ELSE PATCH_IF strref > 0 BEGIN
						SET strrefTarget = 102700 + targetOffset
						SPRINT target (AT strrefTarget)
						SPRINT main_target ~%theTarget%~
                        SPRINT theTarget (AT strref)

						SET strrefTarget = 102720 + targetOffset
						SPRINT target (AT strrefTarget)
						SPRINT main_target ~%toTheTarget%~
                        SPRINT toTheTarget (AT strref)

						SET strrefTarget = 102710 + targetOffset
						SPRINT target (AT strrefTarget)
						SPRINT main_target ~%ofTheTarget%~
                        SPRINT ofTheTarget (AT strref)

					END
                END
            END
        END
	END
END

DEFINE_PATCH_FUNCTION ~get_projectile_area~
	INT_VAR
		projectile = 0
	RET
		area_feet
		area_signature
BEGIN
	SET area_feet = 0 - 1
	SPRINT area_signature ~~
	PATCH_IF projectile > 1 BEGIN
		SET projectileIndex = projectile - 1
		LOOKUP_IDS_SYMBOL_OF_INT projectileFile ~projectl~ projectileIndex
		PATCH_IF !IS_AN_INT projectileFile AND FILE_EXISTS_IN_GAME ~%projectileFile%.pro~ BEGIN
			INNER_PATCH_FILE ~%projectileFile%.pro~ BEGIN
				READ_SHORT 0x8 type
				PATCH_IF type == 3 BEGIN
					READ_LONG  0xc   sparkingFlags
					READ_LONG  0x200 areaProjectileFlags
					READ_SHORT 0x206 areaOfEffect
					PATCH_IF (areaProjectileFlags BAND BIT11) != BIT11 BEGIN
						SET area_feet = areaOfEffect / 17
						SET ignoreTarget = (sparkingFlags BAND BIT4) == BIT4
						SET enemiesOnly = (areaProjectileFlags BAND BIT6) == BIT6
						SET alliesOnly = (areaProjectileFlags BAND BIT7) == BIT7
						SPRINT area_signature ~%ignoreTarget%-%enemiesOnly%-%alliesOnly%~
					END
				END
			END
		END
	END
END

DEFINE_PATCH_FUNCTION ~get_projectile_range_progression~
	RET
		range_progression
BEGIN
	SPRINT range_progression ~~
	SET isValid = 1
	SET hasStep = 0
	SET prevFeet = 0 - 1
	SPRINT firstSignature ~~
	PATCH_PHP_EACH level_effects AS index => level BEGIN
		PATCH_IF isValid BEGIN
			LPF ~get_projectile_area~ INT_VAR projectile = $level_projectiles(~%index%~) RET feet = area_feet signature = area_signature END
			PATCH_IF feet < 0 OR (prevFeet >= 0 AND NOT ~%signature%~ STRING_EQUAL ~%firstSignature%~) OR feet < prevFeet BEGIN
				SET isValid = 0
			END
			ELSE PATCH_IF prevFeet < 0 BEGIN
				SPRINT firstSignature ~%signature%~
				LPF ~feets_to_meters~ INT_VAR range = feet RET range_progression = rangeToMeter END
			END
			ELSE PATCH_IF feet > prevFeet BEGIN
				SET hasStep = 1
				LPF ~feets_to_meters~ INT_VAR range = feet - prevFeet RET deltaRange = rangeToMeter END
				SPRINT range ~%range_progression%~
				SPRINT range_progression @102168 // ~%range% + %deltaRange% à partir du niveau %level%~
			END
			SET prevFeet = feet
		END
	END
	PATCH_IF NOT isValid OR NOT hasStep BEGIN
		SPRINT range_progression ~~
	END
END

DEFINE_PATCH_FUNCTION ~spell_area_within_distance~
	INT_VAR
		distance = 0
	STR_VAR
		file = ~~
	RET
		withinDistance
BEGIN
	SET withinDistance = 0
	PATCH_IF FILE_EXISTS_IN_GAME ~%file%.spl~ BEGIN
		INNER_PATCH_FILE ~%file%.spl~ BEGIN
			READ_LONG  SPL_extended_headers_offset areaHeaderOffset
			READ_SHORT SPL_extended_headers_count  areaHeaderCount
			READ_LONG  SPL_feature_blocks_offset   areaEffectsOffset
			SET withinDistance = areaHeaderCount > 0
			FOR (areaHeader = 0; areaHeader < areaHeaderCount AND withinDistance; ++areaHeader) BEGIN
				SET offset = areaHeaderOffset + 0x28 * areaHeader
				READ_SHORT (offset + SPL_HEAD_projectile)            areaProjectile
				READ_SHORT (offset + SPL_HEAD_feature_blocks_count)  areaEffectCount
				READ_SHORT (offset + SPL_HEAD_feature_blocks_offset) areaEffectIndex
				// Un effet sur la cible de l'en-tête (le porteur du 232) ne dépend pas de la zone.
				SET withinDistance = areaEffectCount > 0
				FOR (areaEffect = 0; areaEffect < areaEffectCount; ++areaEffect) BEGIN
					READ_BYTE (areaEffectsOffset + 0x30 * (areaEffectIndex + areaEffect) + FX_target) areaEffectTarget
					PATCH_IF areaEffectTarget != 2 BEGIN
						SET withinDistance = 0
					END
				END
				SET areaRadius = 0
				PATCH_IF withinDistance AND areaProjectile > 1 BEGIN
					LOOKUP_IDS_SYMBOL_OF_INT areaProjectileFile ~projectl~ (areaProjectile - 1)
					PATCH_IF NOT IS_AN_INT areaProjectileFile AND FILE_EXISTS_IN_GAME ~%areaProjectileFile%.pro~ BEGIN
						INNER_PATCH_FILE ~%areaProjectileFile%.pro~ BEGIN
							READ_SHORT 0x8 areaType
							PATCH_IF areaType == 3 AND BUFFER_LENGTH >= 0x226 BEGIN
								READ_LONG  0x200 areaFlags
								READ_SHORT 0x206 areaRadius
								// Même conversion que get_target_by_projectile.
								SET areaRadius = (areaFlags BAND BIT11) == BIT11 ? 0 : areaRadius / 17
							END
						END
					END
				END
				SET withinDistance = withinDistance AND areaRadius > 0 AND areaRadius <= distance
			END
		END
	END
END

DEFINE_PATCH_FUNCTION ~spell_target_by_projectile~
	INT_VAR
		target = 0
	RET
		areaTarget
BEGIN
	SET strref = 0
	SET areaTargetOffset = 0
	SPRINT areaTarget ~~
	READ_BYTE (offset + SPL_HEAD_target_number) countTarget
	READ_SHORT (offset + SPL_HEAD_projectile) projectile
	PATCH_IF projectile > 1 BEGIN
		SET projectile -= 1
		LOOKUP_IDS_SYMBOL_OF_INT projectileFile ~projectl~ projectile

        PATCH_IF !IS_AN_INT projectileFile BEGIN
            INNER_PATCH_FILE ~%projectileFile%.pro~ BEGIN
                READ_SHORT 0x8 type
                PATCH_IF type == 3 BEGIN
					READ_LONG  0xc   sparkingFlags
					READ_LONG  0x2c  extendedFlags
					READ_LONG  0x200 areaProjectileFlags
                    READ_SHORT 0x206 areaOfEffect
                    READ_SHORT 0x224 coneWidth

                    // On divise par 8.5 pour avoir le diamètre en pied, et encore par 2 pour avoir le rayon
                    SET areaOfEffect /= 17
                    LPF ~feets_to_meters~ INT_VAR range = areaOfEffect RET range = rangeToMeter END

					//LinedUpAreaOfEffect 0x2c BIT14
					//RectangularAreaOfEffect 0x2c BIT15 (longeur = 0x204, largeur = 0x206) (Prioritaire sur LinedUpAreaOfEffect)
					//CasterAffected 0x2c BIT31

					SET ignoreTarget = (sparkingFlags BAND BIT4) == BIT4
					SET enemiesOnly = (areaProjectileFlags BAND BIT6) == BIT6
					SET alliesOnly = (areaProjectileFlags BAND BIT7) == BIT7
					SET isConeShape = (areaProjectileFlags BAND BIT11) == BIT11

					PATCH_IF alliesOnly AND enemiesOnly BEGIN
						SET areaTargetOffset = 2
					END
					ELSE PATCH_IF enemiesOnly BEGIN
						SET areaTargetOffset = 1
					END

					PATCH_IF isConeShape BEGIN
						SET angle = coneWidth
						SET strref = 102458 // ~Cône de %range% sur un arc de %angle%°~
					END
					ELSE BEGIN
						PATCH_IF target == TARGET_HEAD_self OR target == TARGET_HEAD_self_ignore_pause BEGIN
							PATCH_IF ignoreTarget OR enemiesOnly BEGIN
								SPRINT ofTheTarget @102476 // ~du lanceur~
								SET strref = 102455 // ~Rayon de %range% autour %ofTheTarget%~
							END
							ELSE BEGIN
								SET strref = 102448 // ~Le lanceur et toute créature dans un rayon de %range%~
							END
						END
						ELSE PATCH_IF target == TARGET_HEAD_creature BEGIN
							PATCH_IF countTarget <= 1 BEGIN
								PATCH_IF ignoreTarget BEGIN
									SPRINT ofTheTarget @101085 // ~de la cible~
									SET strref = 102455 // ~Rayon de %range% autour %ofTheTarget%~
								END
								ELSE BEGIN
									SET strref = 102445 // ~1 créature et toute créature dans un rayon de %range%~
								END
							END
							ELSE BEGIN
								SPRINT areaTarget @102465 // ~%countTarget% créatures~
							END
						END
						ELSE PATCH_IF target == TARGET_HEAD_area BEGIN
							SET strref = 102442 // ~Rayon de %range%~
						END
						ELSE BEGIN
							// TODO: TARGET_HEAD_character_portrait // dead actor 1 objet ou une créature morte
							LPF ~add_log_warning~ STR_VAR message = EVAL ~Cible à gerer : %target% ~ END
						END
					END
					PATCH_IF strref > 0 BEGIN
						SET strref += areaTargetOffset
						SPRINT areaTarget (AT strref)
					END
                END
            END
        END
	END
END

// Jet de sauvegarde du sous-sort resref, lu dans la portée de cette fonction : load_level_effects y réécrit
// level_effects et leveled_opcodes_<niveau>, que le sort en cours garde ainsi pour ses en-têtes suivants et
// pour le bonus de son jet.
DEFINE_PATCH_FUNCTION ~spell_saving_throw_sub~ STR_VAR resref = ~~ RET ignoreSavingThrow232 saveType saveBonus isHalfDamage subBonusValue subBonusValid BEGIN
	SET ignoreSavingThrow232 = 1
	SET saveType = 0 - 1
	SET saveBonus = 0 - 1
	SET isHalfDamage = 0
	SPRINT subBonusValue ~~
	SET subBonusValid = 1
	INNER_PATCH_FILE ~%resref%.spl~ BEGIN
		LPM ~load_level_effects~
		LPF ~spell_saving_throw~ RET ignoreSavingThrow232 = ignoreSavingThrow saveType = baseSavingType saveBonus = baseSavingBonus isHalfDamage subBonusValue = savingBonusValue subBonusValid = savingBonusValid END
	END
END

// Le bonus du jet ne se lit que dans les effets qui le portent : quand aucun effet du sort n'a de type
// de jet, celui-ci vient de ses sous-sorts, et leur bonus avec lui (SPPR725 : « Sorts à -2 »).
DEFINE_PATCH_FUNCTION ~spell_saving_throw~ RET description ignoreSavingThrow baseSavingType baseSavingBonus isHalfDamage savingBonusValue savingBonusValid BEGIN
	SET ignoreSavingThrow = 1
	SET count = 0
	SET isSpecial = 0
	SET isHalfDamage = 0
	SET baseSavingType = 0 - 1
	SET baseSavingBonus = 0 - 1
	SPRINT savingBonusValue ~~
	SET savingBonusValid = 1
	SET ownSavingType = 0
	SET subBonusCount = 0
	SPRINT subBonusFirst ~~
	SET subBonusAllValid = 1

	PATCH_PHP_EACH level_effects AS index => requiredLevel BEGIN
		PATCH_IF isSpecial == 0 BEGIN
			PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
				PATCH_IF opcode >= 0 BEGIN
				    LPM ~data_to_vars~
				    PATCH_IF( NOT (opcode == 318 OR opcode == 321 OR opcode == 324) AND NOT ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~) BEGIN
						SET saveType = (saveType BAND 0b111111)
						SET ownSavingType = ownSavingType OR saveType > 0
		                PATCH_IF saveType == 0 AND (opcode == 232 OR opcode == 146 OR opcode == 148) BEGIN
							SET $recursive_resref(~%CURRENT_SOURCE_RES%~) = 1
							PATCH_IF NOT VARIABLE_IS_SET $recursive_resref(~%resref%~) BEGIN
								SET $recursive_resref(~%resref%~) = 1
								PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
									LPF ~spell_saving_throw_sub~ STR_VAR resref RET ignoreSavingThrow232 saveType saveBonus isHalfDamage subBonusValue subBonusValid END
									PATCH_IF saveType > 0 BEGIN
										PATCH_IF subBonusCount == 0 BEGIN
											SPRINT subBonusFirst ~%subBonusValue%~
										END
										SET subBonusAllValid = subBonusAllValid AND subBonusValid AND ~%subBonusValue%~ STRING_EQUAL ~%subBonusFirst%~
										SET subBonusCount += 1
									END
									// Sous-sort « Spécial » (jets différents) : le sort l'est aussi, et ses lignes écrivent
									// leur jet, que l'en-tête ne donne pas.
									PATCH_IF ignoreSavingThrow232 == 0 BEGIN
										SET isSpecial = 1
									END
								END
							END
		                END
						PATCH_IF is_ee AND opcode == 12 AND (parameter2 BAND 65535) == 0 AND (special BAND BIT8) > 0 BEGIN
							SET isHalfDamage = 1
						END
						PATCH_IF saveType != 0 - 1 BEGIN
							PATCH_IF baseSavingType == 0 - 1 BEGIN
								SET baseSavingType = saveType
								SET baseSavingBonus = saveBonus
							END
							PATCH_IF baseSavingType != saveType BEGIN
								SET isSpecial = 1
							END
						END
					END
				END
			END
		END
	END

	PATCH_IF isSpecial BEGIN
		SPRINT savingThrow @100032 // ~Spécial~
		SET ignoreSavingThrow = 0
	END
	ELSE PATCH_IF baseSavingType > 0 BEGIN
		PATCH_IF isHalfDamage == 1 BEGIN
			SPRINT savingThrow @10017 // ~1/2~
		END
		ELSE BEGIN
			SPRINT savingThrow @10016 // ~Annule~
		END
		PATCH_IF NOT ownSavingType AND subBonusCount > 0 BEGIN
			SPRINT value ~%subBonusFirst%~
			SET is_valid = subBonusAllValid
		END
		ELSE BEGIN
			LPF ~get_spell_effects_by_saving_throw~ RET value = complex_value is_valid END
		END
		SPRINT savingBonusValue ~%value%~
		SET savingBonusValid = is_valid
		PATCH_IF is_valid BEGIN
			SPRINT saveTypeStrref $short_saveType_to_strref(~%baseSavingType%~)
			SPRINT saveType (AT saveTypeStrref)
			PATCH_IF ~%value%~ STRING_EQUAL ~~ OR ~%value%~ STRING_EQUAL ~0~ BEGIN
				SPRINT savingThrow @103100 // ~%saveType% (%savingThrow%)~
			END
			ELSE BEGIN
				SPRINT savingThrow @103101 // ~%saveType% à %value% (%savingThrow%)~
			END
		END
		ELSE BEGIN
            SPRINT savingThrow @100032 // ~Spécial~
			SET ignoreSavingThrow = 0
        END
	END
	ELSE BEGIN
		SPRINT savingThrow @10015 // ~Aucun~
	END

	LPF ~appendValue~ INT_VAR strref = 100036 STR_VAR value = ~%savingThrow%~ RET description END // ~Jet de sauvegarde~
END


/*
	0 ⟶ Natural/Nonmagical
    1 ⟶ Can be dispelled/Affected by resistance
    2 ⟶ Cannot be dispelled/Ignores resistance
    3 ⟶ Can be dispelled/Ignores resistance
*/
DEFINE_PATCH_FUNCTION ~spell_resistance~ RET description BEGIN
	SET count = 0
	SET isSpecial = 0
	SET baseIsDispellable = 0 - 1
	SET baseIgnoreResistance = 0 - 1

	PATCH_PHP_EACH level_effects AS index => requiredLevel BEGIN
		PATCH_IF isSpecial == 0 BEGIN
			PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
				PATCH_IF opcode >= 0 BEGIN
				    LPM ~data_to_vars~
				    PATCH_IF( NOT (opcode == 318 OR opcode == 321 OR opcode == 324) AND NOT ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~) BEGIN
                        SET ignoreResistance = (resistance == 2 OR resistance == 3) ? 1 : 0
                        PATCH_IF baseIgnoreResistance == 0 - 1 BEGIN
                            SET baseIgnoreResistance = ignoreResistance
                        END
                        PATCH_IF baseIgnoreResistance != ignoreResistance BEGIN
                            SET isSpecial = 1
                        END

                        PATCH_IF isSpecial == 0 AND duration > 0 BEGIN
                            SET isDispellable = (resistance == 1 OR resistance == 3) ? 1 : 0
                            PATCH_IF baseIsDispellable == 0 - 1 BEGIN
                                SET baseIsDispellable = isDispellable
                            END
                            PATCH_IF baseIsDispellable != isDispellable BEGIN
                                SET isSpecial = 1
                            END
                        END
				    END
				END
		    END
		END
    END

	PATCH_IF isSpecial == 0 BEGIN
        PATCH_IF baseIsDispellable != 0 - 1 BEGIN
            PATCH_IF baseIsDispellable == 1 AND hasDuration == 1 BEGIN
                SPRINT isDispellable @100041 // ~Affecté~
            END
            ELSE BEGIN
                SPRINT isDispellable @100042 // ~Non-affecté~
            END
	        LPF ~appendValue~ INT_VAR strref = 100039 STR_VAR value = ~%isDispellable%~ RET description END // ~Dissipation~
	    END

	    PATCH_IF baseIgnoreResistance != 0 - 1 BEGIN
            PATCH_IF baseIgnoreResistance == 0 BEGIN
                SPRINT ignoreResistance @100041 // ~Affecté~
            END
            ELSE BEGIN
                SPRINT ignoreResistance @100042 // ~Non-affecté~
            END
	        LPF ~appendValue~ INT_VAR strref = 100040 STR_VAR value = ~%ignoreResistance%~ RET description END // ~Résistance à la magie~
	    END
	END
END


DEFINE_PATCH_FUNCTION ~get_spell_effects_by_saving_throw~ RET complex_value is_valid BEGIN
	SPRINT complex_value ~~
	SPRINT base_complex_value ~~
	SET level = $level_effects(~0~)
	SET is_valid = 1
	PATCH_PHP_EACH ~leveled_opcodes_%level%~ AS data => opcode BEGIN
		CLEAR_ARRAY effects_to_disabled
		PATCH_IF opcode >= 0 AND is_valid == 1 BEGIN
		    LPM ~data_to_vars~
		    LPM ~data_to_match_vars~

		    LPF spell_has_same_effects_on_all_levels_except_duration
				INT_VAR
					match_opcode match_isExternal match_target match_power match_parameter1 match_parameter2
					match_timingMode match_resistance match_duration match_probability match_probability1
					match_probability2 match_diceCount match_diceSides match_saveType match_saveBonus match_special
					match_parameter3 match_parameter4 match_custom_int
				STR_VAR
					match_resref match_resref2 match_resref3 match_custom_str
					match_macro = ~opcode_match_except_duration_saveBonus~
					return_parameter = ~saveBonus~
		        RET
		            inAllLevels total
		        RET_ARRAY
		            all_effects
		    END
		    PATCH_IF inAllLevels BEGIN
		        PATCH_IF total > 1 BEGIN
					LPF ~get_complex_value~
						INT_VAR
							untyped = 1
						STR_VAR
							array_name = ~all_effects~
						RET
							is_valid
							complex_value
							complex_value_int
					END
					PATCH_IF complex_value_int > 0 BEGIN
						SPRINT value ~%complex_value%~
						SPRINT complex_value @10003
					END
			    END
			    ELSE PATCH_IF total == 1 BEGIN
					PATCH_PHP_EACH ~all_effects~ AS level => value BEGIN
						LPF ~signed_value~ INT_VAR value RET complex_value = value END
					END
			    END
				PATCH_IF ~%base_complex_value%~ STRING_EQUAL ~~ BEGIN
					SPRINT base_complex_value ~%complex_value%~
				END
				PATCH_IF NOT ~%base_complex_value%~ STRING_EQUAL ~%complex_value%~ BEGIN
					SET is_valid = 0
				END
		        PATCH_IF is_valid == 0 BEGIN
					SPRINT complex_value ~~
		        END
		    END
		END
	END
	// data_to_vars de l'effet suivant remet complex_value à la valeur gardée dans l'effet (vide) :
	// seul base_complex_value garde le bonus commun.
	SPRINT complex_value ~~
	PATCH_IF is_valid BEGIN
		SPRINT complex_value ~%base_complex_value%~
	END
END

DEFINE_PATCH_FUNCTION ~get_first_level_for_spell~
	RET
		minLevel
BEGIN
	READ_SHORT SPL_type spellType
	READ_LONG SPL_level spellLevel
	PATCH_IF spellLevel < 1 BEGIN
		SET spellLevel = 1
	END
	// Niveau absent de la table (Ex: un sort divin de niveau 9)
	PATCH_IF spellType == 1 OR spellType == 2 BEGIN
		SPRINT firstLevelTable ~wizard~
		PATCH_IF spellType == 2 BEGIN
			READ_LONG SPL_exclusion_flags exclusionFlags
			PATCH_IF (exclusionFlags BAND BIT31) == BIT31 BEGIN
				SPRINT firstLevelTable ~priest~
			END
			ELSE BEGIN
				SPRINT firstLevelTable ~druid~
			END
		END
		PATCH_IF NOT VARIABLE_IS_SET $EVAL ~first_caster_level_%firstLevelTable%~(~%spellLevel%~) BEGIN
			LPF ~add_log_warning~ STR_VAR message = ~No first caster level for spell %SOURCE_RES% (type %spellType%, level %spellLevel%) in the table of %firstLevelTable% spells (MXSPL*.2DA): first level taken from the headers.~ END
			SET spellType = 0
		END
	END
	PATCH_IF spellType == 2 BEGIN
		READ_LONG SPL_exclusion_flags exclusionFlags
		SET excludeDruid = (exclusionFlags BAND BIT31) == BIT31
		PATCH_IF NOT excludeDruid BEGIN
			SET minLevel = $first_caster_level_druid(~%spellLevel%~)
		END
		ELSE BEGIN
			SET minLevel = $first_caster_level_priest(~%spellLevel%~)
		END
	END
	ELSE PATCH_IF spellType == 1 BEGIN
		SET minLevel = $first_caster_level_wizard(~%spellLevel%~)
	END
	ELSE BEGIN
		SET count_levels = 0
	    PATCH_DEFINE_ARRAY levels BEGIN END
		GET_OFFSET_ARRAY headerOffsets SPL_V10_HEADERS
		PHP_EACH headerOffsets AS _ => headerOffset BEGIN
			READ_SHORT (headerOffset + SPL_HEAD_level_required) requiredLevel
			SET $levels(~%count_levels%~) = requiredLevel
			SET count_levels += 1
		END

		SET diff = 0
		SET delta = 0
		SET level1 = 0
		SET level2 = 0
		SET minLevel = 1
		SET isValid = 1
		PATCH_PHP_EACH levels AS _ => level BEGIN
			SET level1 = level2
			SET level2 = level
			PATCH_IF level1 > 1 BEGIN
				SET delta = level2 - level1
				PATCH_IF diff == 0 BEGIN
					SET diff = delta
				END
				PATCH_IF diff != delta BEGIN
					SET isValid = 0
				END
			END
		END
		PATCH_IF isValid == 1 AND VARIABLE_IS_SET $levels(1) BEGIN
			SET minLevel = $levels(1) - diff
		END
		ELSE PATCH_IF count_levels == 1 BEGIN
			SET minLevel = $levels(0)
		END
		ELSE BEGIN
			// LPF ~add_log_warning~ STR_VAR message = ~Niveau minimum non calculable~ END
		END
	END
END

DEFINE_ACTION_FUNCTION ~get_first_caster_level_list~
	STR_VAR
		2dafile = ~~
	RET_ARRAY
		first_caster_level
BEGIN
	ACTION_DEFINE_ARRAY first_caster_level BEGIN END
	COPY_EXISTING ~%2dafile%.2da~ ~override~
		COUNT_2DA_COLS colCount
		COUNT_2DA_ROWS colCount rowCount
		READ_2DA_ENTRIES_NOW mxspl colCount
		FOR (row = 0; row < rowCount; ++row) BEGIN
			FOR (level = 1; level < colCount; ++level) BEGIN
				SET $first_caster_level(~%level%~) = 0
			END
		END
		FOR (row = 0; row < rowCount; ++row) BEGIN
			FOR (level = 1; level < colCount; ++level) BEGIN
				PATCH_IF $first_caster_level(~%level%~) == 0 BEGIN
					READ_2DA_ENTRY_FORMER mxspl row level maxSpells
					PATCH_IF maxSpells > 0 BEGIN
						SET $first_caster_level(~%level%~) = row + 1
					END
				END
			END
		END
	BUT_ONLY_IF_IT_CHANGES
END

DEFINE_PATCH_FUNCTION ~spell_dispellable_by_clearair~ RET description BEGIN
	LPF ~is_dispellable_by_clearair~ RET is_dispellable_by_clearair = is_dispellable END

	PATCH_IF is_dispellable_by_clearair BEGIN
        // Supprime l'éventuel texte ajouté par CorrectFR pour éviter une redite
        INNER_PATCH_SAVE description ~%description%~ BEGIN
            SPRINT dispellableText (AT 102129)
            REPLACE_TEXTUALLY ~%dispellableText%~ ~~
        END
        SPRINT dispellableText (AT 102128)
	    SPRINT description ~%description%%crlf%%dispellableText%~
	END
END

DEFINE_PATCH_FUNCTION ~spell_list_spells_dispellable_by_clearair~ RET description
BEGIN
    PATCH_DEFINE_ARRAY dispellableSpells BEGIN END
    INNER_ACTION BEGIN
        COPY_EXISTING_REGEXP GLOB ~^.+\.spl$~ ~override~
            READ_STRREF SPL_unidentified_name spellName
	        READ_LONG   SPL_unidentified_name spellNameRef
            PATCH_IF spellNameRef > 0 AND STRING_LENGTH ~%spellName%~ > 0 BEGIN
	            LPF ~is_dispellable_by_clearair~ RET is_dispellable_by_clearair = is_dispellable END
                PATCH_IF is_dispellable_by_clearair BEGIN
                    SET $dispellableSpells(~%spellName%~) = 1
                END
            END
        BUT_ONLY_IF_IT_CHANGES
    END
    SORT_ARRAY_INDICES ~dispellableSpells~ LEXICOGRAPHICALLY

	SPRINT and @100021 // ~et~
    LPF ~implode~ STR_VAR array_name = ~dispellableSpells~ glue = ~, ~ final_glue = ~ %and% ~ RET spellList = text END
    SPRINT affectedSpellList @102130 // ~Les sorts et capacités affectés sont%colon%%spellList%~
	SPRINT description ~%description%%crlf%%crlf%%affectedSpellList%~
END

DEFINE_PATCH_FUNCTION ~is_dispellable_by_clearair~
    RET
        is_dispellable
BEGIN
    SET is_dispellable = 0

    GET_OFFSET_ARRAY headerOffsets SPL_V10_HEADERS
    PHP_EACH headerOffsets AS _ => headerOffset BEGIN
        READ_SHORT (headerOffset + SPL_HEAD_projectile) spellProjectile
        SET spellProjectile -= 1

        PATCH_IF VARIABLE_IS_SET $clearair_projectiles(~%spellProjectile%~) AND is_dispellable == 0 BEGIN
            is_dispellable = 1
        END
    END
END