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
	READ_BYTE SPL_school spellSchool

	LPF ~get_spell_type_name~ INT_VAR type = spellType RET spellTypeName END

	PATCH_IF spellSchool > 0 BEGIN
		LPF ~get_spell_school_name~ INT_VAR school = spellSchool RET spellSchoolName END
		LPF ~appendLine~ STR_VAR string = ~(%spellTypeName% - %spellSchoolName%)~ RET description END
	END
	ELSE BEGIN
		LPF ~appendLine~ STR_VAR string = ~(%spellTypeName%)~ RET description END
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

			READ_SHORT (offset + SPL_HEAD_target) target
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
		LPF ~feets_to_meters~ INT_VAR range = currentRange RET range currentRange = rangeToMeter END
		PATCH_IF range < 2 BEGIN
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

DEFINE_PATCH_FUNCTION ~spell_duration~ RET description ignoreDuration strDuration is_special BEGIN
	SET base_duration = ~-1~
	SET isValid = 1
	SET is_special = 0
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
				    PATCH_IF NOT ((opcode == 318 OR opcode == 321 OR opcode == 324) AND ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~) BEGIN
				        /*
	                    PATCH_IF opcode == 146 BEGIN
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
	                    */

	                    PATCH_IF timingMode == TIMING_duration_ticks BEGIN
	                        SET duration = duration / 15
	                    END
	                    ELSE PATCH_IF timingMode == TIMING_delayed BEGIN
	                        SET duration = 0
	                    END
						ELSE PATCH_IF timingMode == 5000 OR timingMode == 5001 BEGIN
							SET duration = duration MODULO 10000
						END
	                    ELSE PATCH_IF timingMode != TIMING_duration AND timingMode != TIMING_duration_ticks AND timingMode != TIMING_delayed_duration BEGIN
	                        SET duration = 0
	                    END

	                    PATCH_IF opcode == 217 BEGIN
	                        SET duration = 30
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

	PATCH_IF isValid == 1 BEGIN
		LPF ~get_complex_duration~
			STR_VAR
				array_name = ~all_durations~
			RET
				is_special
				is_permanent
				duration = complex_duration
		END
		PATCH_IF NOT is_special BEGIN
			SET ignoreDuration = 1
			SPRINT strDuration ~%duration%~
		END
		ELSE BEGIN
			SPRINT duration @100033 // ~Spéciale~
		END
		PATCH_IF is_permanent BEGIN
			//FIXME: Gestion du permanent ! Dépend des opcodes utilisés par le sort...
			//SPRINT duration @100037 // ~Permanente~
			SPRINT duration @100038 // ~Instantanée~
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

DEFINE_PATCH_FUNCTION ~get_complex_value~
	INT_VAR
		is_percent = 0
		dice_sides = 0
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
	SET delta_value = 0
	SET delta_level = 0
	SET prev_value = 0
	SET prev_level = 0
	SET cpt = 0

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

	PATCH_IF cpt == 2 BEGIN
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
			SPRINT complex_value ~%base_value% jusqu'au niveau %level%~
		END
		ELSE BEGIN
			PATCH_IF is_percent BEGIN
				SPRINT value ~%base_value%~
				SPRINT base_value @10002 // ~%value% %~
				SPRINT value ~%delta_value%~
				SPRINT delta_value @10002 // ~%value% %~
			END
			SPRINT complex_value ~%base_value% + %delta_value% au niveau %level%~
		END
	END
	ELSE PATCH_IF is_valid == 1 BEGIN
		PATCH_TRY LPF ~opcode_%opcode%_typed_value~ INT_VAR value = delta_value RET strref END WITH DEFAULT strref = 0 END
		SET value = ABS delta_value
		SET complex_value_int = delta_value
		PATCH_IF dice_sides > 0 BEGIN
			SET diceCount = value
			SET diceSides = dice_sides
			SPRINT value @10014 // ~%diceCount%d%diceSides%~
		END
		PATCH_IF base_value > 0 AND delta_value == 0 BEGIN
			LPF ~get_complex_typed_value~ INT_VAR is_percent strref STR_VAR value RET complex_value = value END
		END
		ELSE BEGIN
			SET levelMax = level
			SET remains_value = ABS prev_value - (ABS delta_value * level / delta_level)
			LPF ~get_complex_typed_value~ INT_VAR is_percent strref STR_VAR value RET value END
			PATCH_IF ABS delta_level == 1 BEGIN
				SPRINT complex_value @102163 // ~%value% par niveau/%levelMax%~
			END
			ELSE BEGIN
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
					SPRINT complex_value ~%remains_value% + %complex_value%~
				END
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

DEFINE_PATCH_FUNCTION ~spell_target~ RET description BEGIN
	SET count = 0

	PATCH_DEFINE_ARRAY ~targets~ BEGIN END

	PATCH_IF headerCount > 0 BEGIN
	    FOR (headerIndex = 0; headerIndex < headerCount; headerIndex += 1) BEGIN
            SET offset = headerOffset + 0x28 * headerIndex

			READ_SHORT (offset + SPL_HEAD_target) target

			LPF ~spell_target_by_projectile~ INT_VAR target RET areaTarget END

			PATCH_IF ~%areaTarget%~ STRING_EQUAL ~~ BEGIN
				PATCH_IF target == TARGET_HEAD_self OR target == TARGET_HEAD_self_ignore_pause BEGIN
					SPRINT areaTarget @102467 // ~Le lanceur~
				END
				ELSE PATCH_IF target == TARGET_HEAD_creature BEGIN
                    READ_BYTE (offset + SPL_HEAD_target_number) countTarget
                    PATCH_IF countTarget <= 1 BEGIN
                        SPRINT areaTarget @102466 // ~1 créature~
                    END
                    ELSE BEGIN
                        SPRINT areaTarget @102465 // ~%countTarget% créatures~
                    END
                END
				ELSE PATCH_IF target == TARGET_HEAD_area BEGIN
					SPRINT areaTarget @102462 // ~Point dans le champ visuel du lanceur~
				END
				ELSE PATCH_IF target == TARGET_HEAD_character_portrait BEGIN
					SPRINT areaTarget @102466 // ~1 créature~
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
					PATCH_IF strref > 0 BEGIN
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

DEFINE_PATCH_FUNCTION ~spell_saving_throw~ RET description ignoreSavingThrow baseSavingType baseSavingBonus BEGIN
	SET ignoreSavingThrow = 1
	SET count = 0
	SET isSpecial = 0
	SET baseSavingType = 0 - 1
	SET baseSavingBonus = 0 - 1

	PATCH_PHP_EACH level_effects AS index => requiredLevel BEGIN
		PATCH_IF isSpecial == 0 BEGIN
			PATCH_PHP_EACH ~leveled_opcodes_%requiredLevel%~ AS data => opcode BEGIN
				PATCH_IF opcode >= 0 BEGIN
				    LPM ~data_to_vars~
					SET saveType = (saveType BAND 0b111111)
	                PATCH_IF saveType == 0 AND (opcode == 232 OR opcode == 146) BEGIN
						PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
							INNER_PATCH_FILE ~%resref%.spl~ BEGIN
								LPM ~load_level_effects~
								LPF ~spell_saving_throw~ RET ignoreSavingThrow232 = ignoreSavingThrow saveType = baseSavingType saveBonus = baseSavingBonus END
							END
						END
	                END
					PATCH_IF is_ee AND opcode == 12 AND (parameter2 BAND 65535) == 0 AND (special BAND BIT8) > 0 BEGIN
						SET saveType = 32 // demi-dégâts
					END
					PATCH_IF baseSavingType == 0 - 1 BEGIN
						SET baseSavingType = saveType
						SET baseSavingBonus = saveBonus
					END
					PATCH_IF /*NOT (saveType == 0 AND saveType == 32) AND*/ baseSavingType != saveType BEGIN
						SET isSpecial = 1
						SET ignoreSavingThrow = 0
					END
					PATCH_IF saveBonus != 0 BEGIN
						SET ignoreSavingThrow = 0
					END
				END
			END
		END
	END

	PATCH_IF isSpecial BEGIN
		SPRINT savingThrow @100032 // ~Spécial~
	END
	ELSE PATCH_IF baseSavingType > 0 BEGIN
		PATCH_IF baseSavingType == 32 BEGIN
			SPRINT savingThrow @10017 // ~1/2~
		END
		ELSE BEGIN
			SPRINT savingThrow @10016 // ~Annule~
		END
	END
	ELSE BEGIN
		SPRINT savingThrow @10015 // ~Aucun~
	END

	LPF ~appendValue~ INT_VAR strref = 100036 STR_VAR value = ~%savingThrow%~ RET description END // ~Jet de sauvegarde~
END

DEFINE_PATCH_FUNCTION ~get_first_level_for_spell~
	RET
		minLevel
BEGIN
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
		// TODO: Déterminer le niveau selon les fichier mxsplxx.2da ? Afin de prendre le niveau auquel le personnage peut apprendre le sort
		SET minLevel = $levels(0)
	END
	ELSE BEGIN
		LPF ~add_log_warning~ STR_VAR message = ~Niveau minimum non calculable~ END
	END
END
