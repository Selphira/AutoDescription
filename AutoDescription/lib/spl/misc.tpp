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

DEFINE_PATCH_FUNCTION ~spell_duration~ RET description BEGIN
	// Récupérer la durée des opcodes supportés dans l'extended header
	// s'ils ne sont pas tous le même => Spécial
	// @100031 // ~Durée~
	LPF ~appendValue~ INT_VAR strref = 100031 STR_VAR value = ~TODO~ RET description END // ~Durée~
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

			PATCH_IF target == TARGET_HEAD_self OR target == TARGET_HEAD_self_ignore_pause BEGIN
				SPRINT target @102467 // ~Le lanceur~
				READ_SHORT (offset + SPL_HEAD_projectile) projectile
				PATCH_IF projectile > 1 BEGIN
					SET projectile -= 1
					LOOKUP_IDS_SYMBOL_OF_INT projectileFile ~projectl~ projectile

	                PATCH_IF !IS_AN_INT projectileFile BEGIN
	                    INNER_PATCH_FILE ~%projectileFile%.pro~ BEGIN
	                        READ_SHORT 0x8 type
	                        PATCH_IF type == 3 BEGIN
		                        READ_SHORT 0x206 area
		                        // On divise par 8.5 pour avoir le diamètre en pied, et encore par 2 pour avoir le rayon
		                        SET area /= 17
		                        LPF ~feets_to_meters~ INT_VAR range = area RET range = rangeToMeter END
								SPRINT target @102463 // ~Rayon de %range% autour du lanceur~
	                        END
	                    END
	                END
				END
			END
			ELSE PATCH_IF target == TARGET_HEAD_creature BEGIN
				READ_BYTE (offset + SPL_HEAD_target_number) countTarget

				PATCH_IF countTarget <= 1 BEGIN
					SPRINT target @102466 // ~1 créature~
				END
				ELSE BEGIN
					SPRINT target @102465 // ~%countTarget% créatures~
				END
			END
			ELSE PATCH_IF target == TARGET_HEAD_area BEGIN
				READ_SHORT (offset + SPL_HEAD_projectile) projectile
				PATCH_IF projectile > 1 BEGIN
					SET projectile -= 1
					LOOKUP_IDS_SYMBOL_OF_INT projectileFile ~projectl~ projectile

	                PATCH_IF !IS_AN_INT projectileFile BEGIN
	                    INNER_PATCH_FILE ~%projectileFile%.pro~ BEGIN
	                        READ_SHORT 0x8 type
	                        PATCH_IF type == 3 BEGIN
		                        READ_SHORT 0x206 area
		                        // On divise par 8.5 pour avoir le diamètre en pied, et encore par 2 pour avoir le rayon
		                        SET area /= 17
		                        LPF ~feets_to_meters~ INT_VAR range = area RET range = rangeToMeter END
								SPRINT target @102464 // ~Rayon de %range%~
	                        END
							ELSE BEGIN
								SPRINT target @102462 // ~Point dans le champ visuel du lanceur~
							END
	                    END
	                END
				END
				ELSE BEGIN
					SPRINT target @102462 // ~Point dans le champ visuel du lanceur~
				END
			END
			ELSE BEGIN
				// TODO: TARGET_HEAD_character_portrait // dead actor 1 objet ou une créature morte
				LPF ~add_log_warning~ STR_VAR message = EVAL ~Cible à gerer : %target% ~ END
			END
			SPRINT $targets(~%count%~) ~%target%~
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

DEFINE_PATCH_FUNCTION ~spell_saving_throw~ RET description BEGIN
	LPF ~appendValue~ INT_VAR strref = 100036 STR_VAR value = ~TODO~ RET description END // ~Jet de sauvegarde~
END