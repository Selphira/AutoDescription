DEFINE_PATCH_FUNCTION ~add_casting_features~
	STR_VAR
		description = ~~
	RET
		description
		countLines
BEGIN
	LPF ~load_casting_features~ RET countLines RET_ARRAY lines END
	PATCH_IF countLines > 0 BEGIN
		SPRINT sectionDescription ~%description%~
		SPRINT description ~~
		LPF ~add_items_section_to_description~ STR_VAR arrayName = ~lines~ RET castingText = description END
		SPRINT description ~%sectionDescription%~
		LPF ~count_description_lines~ STR_VAR text = ~%castingText%~ RET castingTextLines = countLines END
		PATCH_IF castingTextLines > 1 BEGIN
			LPF ~appendSection~ INT_VAR strref = 100022 RET description END // ~Capacités d'incantation~
		END
		ELSE BEGIN
			LPF ~appendSection~ INT_VAR strref = 100016 RET description END // ~Capacité d'incantation~
		END
		SPRINT description ~%description%%castingText%~
	END
END

DEFINE_PATCH_FUNCTION ~load_casting_features~
	RET
		countLines
	RET_ARRAY
		lines
BEGIN
	SET countLines = 0

	CLEAR_ARRAY lines
	LPM ~clear_opcodes~

	PATCH_DEFINE_ASSOCIATIVE_ARRAY lines BEGIN END
	PATCH_DEFINE_ASSOCIATIVE_ARRAY opcodes BEGIN END

	SET cumulable = 1
	SET position = 0
	SPRINT target_exceptions ~~
	READ_LONG  SPL_feature_blocks_offset         castingEffectsOffset
	READ_SHORT SPL_casting_feature_blocks_offset castingIndex
	READ_SHORT SPL_casting_feature_blocks_count  castingCount
	FOR (castingEffect = 0; castingEffect < castingCount; ++castingEffect) BEGIN
		SET offset = castingEffectsOffset + 0x30 * (castingIndex + castingEffect)
		LPM ~load_effect~
	END
	LPM ~replace_effects~
	LPM ~filter_effects~
	LPM ~group_effects~

	PATCH_PHP_EACH opcodes AS opcode => count BEGIN
		PATCH_IF count > 0 BEGIN
			PATCH_PHP_EACH ~opcodes_%opcode%~ AS data => _ BEGIN
				LPM ~data_to_vars~
				// Le bloc de lancement touche toujours le lanceur.
				SET target = TARGET_FX_self
				LPF ~get_effect_description~ RET effectDescription = description sort END
				PATCH_IF NOT ~%effectDescription%~ STRING_EQUAL ~~ BEGIN
					SET $lines(~%sort%~ ~%countLines%~ ~%probability%~ ~%probability2%~ ~%probability1%~ ~%effectDescription%~) = 1
					SET countLines += 1
				END
			END
		END
	END

	LPF ~get_unique_effects~ RET countLines = count RET_ARRAY lines = effects END
	LPF ~group_probability_effects~ RET countLines = count RET_ARRAY lines = effects END
END
