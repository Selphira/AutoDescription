// Cache des descriptions de sous-sorts (AD_SUBSPELL_CACHE), dans la portée de
// ad_describe_subresource (new-lib/recursion.tpp) : un même sort, lancé dans le même contexte par de
// nombreux objets (potions), n'est décrit qu'une fois par exécution. Un fichier d'index par sort
// (<AD_SUBSPELL_CACHE_FOLDER>/<SORT>.txt), une ligne par contexte : clé, fichier du texte, sub_count,
// sub_checked ; le texte dans son propre fichier, lu tel quel.
// La clé réunit les paramètres de ad_describe_subresource et les variables de l'appelant que ses
// passes lisent. La chaîne des ressources n'y est pas, pour que des objets différents partagent un
// texte : elle ne change le texte que par une boucle (ad_recursion_allowed), d'où sub_checked, les
// sous-ressources vérifiées pendant la description, dont aucune ne doit être dans la chaîne de
// l'appelant pour reprendre le texte.
// Pas de cache pour un EFF (un seul effet, décrit selon la ressource décrite, ctx_resource), pour un
// refus (son emplacement suit le chemin de l'appelant) ni pour une description qui a écrit dans les
// journaux (…-events.txt, …-recursion.txt) : ses messages sont au nom de la ressource décrite, et un
// texte repris ne les répéterait pas.
// AD_SUBSPELL_CACHE = 2 : chaque texte trouvé est recalculé et comparé, écarts dans
// AutoDescription/log/<journal>-subspell-cache.txt, signe d'une variable que la clé ignore.

DEFINE_ACTION_FUNCTION ad_subspell_cache_init
	STR_VAR
		log_name = ~~
BEGIN
	DELETE + ~%AD_SUBSPELL_CACHE_FOLDER%~
	ACTION_IF AD_SUBSPELL_CACHE BEGIN
		MKDIR ~%AD_SUBSPELL_CACHE_FOLDER%~
	END
	ACTION_IF AD_SUBSPELL_CACHE == 2 BEGIN
		COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%MOD_FOLDER%/log/%log_name%-subspell-cache.txt~
	END
END

// Avant la description : cache_hit (texte trouvé : cache_text, cache_count, cache_checked) ;
// cache_events_size et cache_recursion_size, tailles des journaux, pour savoir ensuite si la
// description y a écrit.
DEFINE_PATCH_MACRO ad_subspell_cache_read BEGIN
	SET cache_hit = 0
	SPRINT cache_key ~%ctx_depth%|%ctx_casting_level%|%ctx_force_target%|%ctx_force_keep_self%|%ctx_ignore_duration%|%ctx_ignore_save%|%ctx_versus_set%|%ctx_base_probability%|%ctx_base_low%|%ctx_base_high%|%ctx_base_lines%|%ctx_lift_sections%|%item_type%|%resource_is_spell%|%support_header_only%|%fx_with_casting%|%ctx_the_target%|%ctx_of_the_target%|%ctx_to_the_target%|%ctx_force_only_for%|%ctx_versus%|%ctx_named_lines%~
	SPRINT cache_caller_chain ~%ctx_chain%%ctx_resource%|~
	SPRINT cache_index ~%AD_SUBSPELL_CACHE_FOLDER%/%sub_resref%.txt~
	SET cache_at = 0 - 1
	PATCH_IF FILE_EXISTS ~%cache_index%~ BEGIN
		INNER_PATCH_FILE ~%cache_index%~ BEGIN
			SET cache_at = INDEX_BUFFER (CASE_SENSITIVE EXACT_MATCH ~%LNL%%cache_key%%TAB%~)
			PATCH_IF cache_at >= 0 BEGIN
				SET cache_at += STRING_LENGTH ~%LNL%%cache_key%%TAB%~
				READ_ASCII cache_at cache_values (BUFFER_LENGTH - cache_at)
			END
		END
	END
	PATCH_IF cache_at >= 0 BEGIN
		INNER_PATCH ~%cache_values%~ BEGIN
			REPLACE_EVALUATE CASE_SENSITIVE ~^\([^%TAB%]+\)%TAB%\([0-9]+\)%TAB%\([^%TAB%%MNL%%LNL%]*\)~ BEGIN
				PATCH_IF NOT cache_hit BEGIN
					SET cache_hit = 1
					SPRINT cache_entry ~%MATCH1%~
					SET cache_count = MATCH2
					SPRINT cache_checked ~%MATCH3%~
				END
			END ~%MATCH0%~
		END
	END
	// Une sous-ressource vérifiée qui est dans la chaîne de l'appelant y aurait été une boucle.
	PATCH_IF cache_hit BEGIN
		INNER_PATCH ~%cache_checked%~ BEGIN
			REPLACE_EVALUATE CASE_SENSITIVE ~|\([^|]+\)|~ BEGIN
				PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~|%MATCH1%|~ ~%cache_caller_chain%~) >= 0 BEGIN
					SET cache_hit = 0
				END
			END ~%MATCH0%~
		END
	END
	PATCH_IF cache_hit BEGIN
		SPRINT cache_text ~~
		INNER_PATCH_FILE ~%AD_SUBSPELL_CACHE_FOLDER%/%cache_entry%~ BEGIN
			PATCH_IF BUFFER_LENGTH > 0 BEGIN
				READ_ASCII 0 cache_text (BUFFER_LENGTH)
			END
		END
	END
	SET cache_events_size = SIZE_OF_FILE ~%MOD_FOLDER%/log/%log_name%-events.txt~
	SET cache_recursion_size = SIZE_OF_FILE ~%MOD_FOLDER%/log/%log_name%-recursion.txt~
END

// Après la description : écart avec le texte trouvé (AD_SUBSPELL_CACHE = 2), sinon texte enregistré.
DEFINE_PATCH_MACRO ad_subspell_cache_store BEGIN
	SET cache_logged = (SIZE_OF_FILE ~%MOD_FOLDER%/log/%log_name%-events.txt~ != cache_events_size)
		OR (SIZE_OF_FILE ~%MOD_FOLDER%/log/%log_name%-recursion.txt~ != cache_recursion_size)
	PATCH_IF cache_hit BEGIN
		PATCH_IF NOT (~%sub_missing%~ STRING_EQUAL ~~) OR cache_logged OR sub_count != cache_count
				OR NOT (~%sub_text%~ STRING_EQUAL ~%cache_text%~) OR NOT (~%sub_checked%~ STRING_EQUAL ~%cache_checked%~) BEGIN
			INNER_ACTION BEGIN
				SILENT
				APPEND_OUTER ~%MOD_FOLDER%/log/%log_name%-subspell-cache.txt~ ~%SOURCE_FILE%%TAB%%sub_resref%%TAB%%cache_key%%WNL%  cached (%cache_count%, %cache_checked%): %cache_text%%WNL%  computed (%sub_count%, %sub_checked%, logged %cache_logged%): %sub_missing%%sub_text%~ KEEP_CRLF
				VERBOSE
			END
		END
	END
	ELSE PATCH_IF ~%sub_missing%~ STRING_EQUAL ~~ AND NOT cache_logged BEGIN
		LPM ad_subspell_cache_write
	END
END

// COPY change SOURCE_FILE, SOURCE_RES et SOURCE_SIZE, que les journaux de la ressource décrite lisent
// ensuite.
DEFINE_PATCH_MACRO ad_subspell_cache_write BEGIN
	SPRINT cache_source_file ~%SOURCE_FILE%~
	SPRINT cache_source_res ~%SOURCE_RES%~
	SET cache_source_size = SOURCE_SIZE
	SET cache_index_size = SIZE_OF_FILE ~%cache_index%~
	PATCH_IF cache_index_size < 0 BEGIN
		SET cache_index_size = 0
	END
	// La taille de l'index, qui croît à chaque ligne, nomme le fichier du texte.
	SPRINT cache_entry ~%sub_resref%.%cache_index_size%.txt~
	SET cache_length = STRING_LENGTH ~%sub_text%~
	INNER_ACTION BEGIN
		COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%AD_SUBSPELL_CACHE_FOLDER%/%cache_entry%~
			PATCH_IF cache_length > 0 BEGIN
				INSERT_BYTES 0 cache_length
				WRITE_ASCIIE 0 ~%sub_text%~
			END
		ACTION_IF NOT FILE_EXISTS ~%cache_index%~ BEGIN
			COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%cache_index%~
		END
		SILENT
		APPEND_OUTER ~%cache_index%~ ~%LNL%%cache_key%%TAB%%cache_entry%%TAB%%sub_count%%TAB%%sub_checked%~ KEEP_CRLF
		VERBOSE
	END
	SPRINT SOURCE_FILE ~%cache_source_file%~
	SPRINT SOURCE_RES ~%cache_source_res%~
	SET SOURCE_SIZE = cache_source_size
END
