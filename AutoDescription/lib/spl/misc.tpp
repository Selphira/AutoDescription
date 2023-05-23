DEFINE_PATCH_FUNCTION ~spell_level~ RET description BEGIN
	READ_SHORT SPL_type  spellType
	READ_LONG  SPL_level spellLevel

	// There is no good reason for a Special/Psionic/Innate/Bard song to be any Spell level except 1.
	PATCH_IF spellType == 1 OR spellType == 2 BEGIN
		LPF ~appendValue~ INT_VAR strref = 10960001 STR_VAR value = ~%spellLevel%~ RET description END // ~Niveau~
	END
END

DEFINE_PATCH_FUNCTION ~spell_school~ RET description BEGIN
	READ_BYTE SPL_school spellSchool

	PATCH_IF spellSchool > 0 BEGIN
		LPF ~get_spell_school_name~ INT_VAR school = spellSchool RET spellSchoolName END
		LPF ~appendValue~ INT_VAR strref = 100030 STR_VAR value = ~%spellSchoolName%~ RET description END // ~École~
	END
END

/*
 * Récupère la portée.
 * TODO: Si le range est différent entre les différents niveaux, afficher une valeur plus précise que "Spéciale"
 *   Ex: 10 mètres + 1 mètre par niveau ?
 */
DEFINE_PATCH_FUNCTION ~spell_range~ RET description BEGIN
	SET count = 0

	PATCH_DEFINE_ARRAY ~ranges~ BEGIN END

	PATCH_IF headerCount > 0 BEGIN
	    FOR (headerIndex = 0; headerIndex < headerCount; headerIndex += 1) BEGIN
            SET offset = headerOffset + 0x28 * headerIndex

			READ_SHORT (offset + SPL_HEAD_target) target
			READ_SHORT (offset + SPL_HEAD_range) range

			PATCH_IF target == 5 OR target == 7 BEGIN
				SET range = 0
			END
			SET $ranges(~%count%~) = range
			SET count += 1
	    END
	END

	SET currentRange = $ranges(~0~)

	FOR (i = 1 ; i < count ; ++i ) BEGIN
		PATCH_IF currentRange != $ranges(~%i%~) BEGIN
			SPRINT currentRange @100033 // ~Spéciale~
			SET i = count
		END
	END

	PATCH_IF IS_AN_INT ~%currentRange%~ BEGIN
		LPF ~feets_to_meters~ INT_VAR range = currentRange RET range currentRange = rangeToMeter END
		PATCH_IF range < 2 BEGIN
			SPRINT currentRange @100034 // ~Contact~
		END
	END

	// TODO: @102461 = ~Champ visuel du lanceur~

	LPF ~appendValue~ INT_VAR strref = 102006 STR_VAR value = ~%currentRange%~ RET description END // ~Portée~
END

DEFINE_PATCH_FUNCTION ~spell_duration~ RET description ignoreDuration BEGIN
	SET base_level = ~-1~
	SET base_duration = ~-1~
	SET isValid = 1
	SET count_levels = 0

    PATCH_DEFINE_ARRAY levels BEGIN END
    PATCH_DEFINE_ARRAY all_durations BEGIN END

	GET_OFFSET_ARRAY headerOffsets SPL_V10_HEADERS
	PHP_EACH headerOffsets AS _ => headerOffset BEGIN
		PATCH_IF isValid == 1 BEGIN
			READ_SHORT (headerOffset + SPL_HEAD_level_required) requiredLevel
			SET $levels(~%count_levels%~) = requiredLevel
			SET count_levels += 1
			GET_OFFSET_ARRAY2 offsets headerOffset ITM_V10_HEAD_EFFECTS
			PHP_EACH offsets AS _ => offset BEGIN
				READ_SHORT (offset) opcode
				READ_ASCII (offset + EFF_resref_key) resref
				PATCH_IF NOT VARIABLE_IS_SET $ignored_opcodes(~%opcode%~) BEGIN
					PATCH_IF NOT (opcode == 321 AND ~%resref%~ STRING_EQUAL_CASE ~%CURRENT_SOURCE_RES%~) BEGIN
						READ_LONG  (offset + EFF_duration) duration

						PATCH_IF opcode == 217 BEGIN
							SET duration = 30
						END

						PATCH_IF base_level == ~-1~ BEGIN
							SET base_level = requiredLevel
						END

						PATCH_IF duration > 0 BEGIN
							PATCH_IF base_duration == ~-1~ BEGIN
								SET base_duration = duration
							END

							PATCH_IF count_levels > 1 BEGIN
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
	END

	PATCH_IF isValid == 1 BEGIN
		PATCH_IF base_duration == ~-1~ BEGIN
			SET base_duration = 0
		END
		PATCH_IF base_level == 1 BEGIN
			LPF get_first_level_for_spell RET base_level = minLevel END
		END
		LPF ~get_complex_duration~
			INT_VAR
				base_level
				base_duration
			STR_VAR
				array_name = ~all_durations~
			RET
				is_special
				is_permanent
				duration = complex_duration
		END
		PATCH_IF NOT is_special BEGIN
			SET ignoreDuration = 1
		END
		ELSE BEGIN
			SPRINT duration @100033 // ~Spéciale~
		END
		PATCH_IF is_permanent BEGIN
			//TODO: Gestion du permanent ! Dépend des opcodes utilisés par le sort...
			//SPRINT duration @100037 // ~Permanente~
			SPRINT duration @100038 // ~Instantanée~
		END
	END
	ELSE BEGIN
		SPRINT duration @100033 // ~Spéciale~
	END

	LPF ~appendValue~ INT_VAR strref = 100031 STR_VAR value = ~%duration%~ RET description END // ~Durée~
END

DEFINE_PATCH_FUNCTION ~get_complex_duration~
	INT_VAR
		base_level = 0
		base_duration = 0
	STR_VAR
		array_name = ~~
	RET
		is_special
		is_permanent
		complex_duration
BEGIN
	SPRINT complex_duration ~~

	SET delta_duration = 0
	SET delta_level = 0
	SET is_valid = 1
	SET is_special = 0
	SET is_permanent = 0
	SET by_x_level = 1
	SET duration_by_level = base_duration / base_level
	SET prev_duration = base_duration
	SET prev_level = base_level
	SET cpt = 0

	PATCH_PHP_EACH ~%array_name%~ AS level => duration BEGIN
		// On ignore la première entrée qui n'est pas toujours en harmonie avec le reste
		PATCH_IF cpt > 0 BEGIN
			PATCH_IF delta_duration = 0 BEGIN
				SET delta_duration = duration - prev_duration
				SET delta_level = level - prev_level
			END
			ELSE PATCH_IF delta_duration != duration - prev_duration OR delta_level != level - prev_level BEGIN
				SET is_valid = 0
			END
		END
		SET prev_duration = duration
		SET prev_level = level
		SET cpt += 1
	END

	PATCH_IF is_valid == 1 BEGIN
		PATCH_IF base_duration == 0 AND delta_duration == 0 BEGIN
			SET is_permanent = 1
		END
		ELSE PATCH_IF base_duration > 0 AND delta_duration == 0 BEGIN
			LPF ~get_str_duration~ INT_VAR duration = base_duration RET complex_duration = strDuration END
		END
		ELSE BEGIN
			LPF ~get_str_duration~ INT_VAR duration = delta_duration RET deltaDuration = strDuration END

			PATCH_IF delta_level == 1 BEGIN
				SPRINT complex_duration ~%deltaDuration% par niveau~
			END
			ELSE BEGIN
				LPF ~get_str_duration~ INT_VAR duration = base_duration RET baseDuration = strDuration END
				SPRINT complex_duration ~%deltaDuration% par tranche de %delta_level% niveaux~
			END
			SET remains_duration = duration - (delta_duration * level / delta_level)
			PATCH_IF remains_duration > 0 BEGIN
				LPF ~get_str_duration~ INT_VAR duration = remains_duration RET remainsDuration = strDuration END
				SPRINT complex_duration ~%remainsDuration% + %complex_duration%~
			END
			// TODO: Ajouter le "à partir du xxème" "1 round + 2 rounds par tranche de 3 niveaux à partir du 12ème"
		END
	END
	ELSE BEGIN
		SET is_special = 1
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

DEFINE_PATCH_FUNCTION ~spell_saving_throw~ RET description BEGIN
	LPF ~appendValue~ INT_VAR strref = 100036 STR_VAR value = ~TODO~ RET description END // ~Jet de sauvegarde~
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
