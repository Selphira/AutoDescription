// Cache des descriptions de sous-sorts (AD_SUBSPELL_CACHE), dans la portée de
// ad_describe_subresource (lib/recursion.tpp) : un même sort, lancé dans le même contexte par de
// nombreux objets (potions), n'est décrit qu'une fois par exécution. Un fichier d'index par sort
// (<AD_SUBSPELL_CACHE_FOLDER>/<SORT>.txt), une ligne par contexte : clé, fichier du texte, sub_count,
// sub_checked, fichier des journaux (vide si la description n'y a rien écrit) ; le texte dans son
// propre fichier, lu tel quel.
// La clé réunit les paramètres de ad_describe_subresource et les variables de l'appelant que ses
// passes lisent. La chaîne des ressources n'y est pas, pour que des objets différents partagent un
// texte : elle ne change le texte que par une boucle (ad_recursion_allowed), d'où sub_checked, les
// sous-ressources vérifiées pendant la description, dont aucune ne doit être dans la chaîne de
// l'appelant pour reprendre le texte, ni pour l'enregistrer quand une boucle y a été journalisée.
// Les lignes écrites dans …-events.txt et …-recursion.txt pendant la description sont gardées sans
// ce qui dépend de l'appelant (ressource décrite SOURCE_FILE, chemin ctx_origin au début de
// l'emplacement, chaîne de l'appelant au début de celle d'une récursion), puis réécrites avec ceux de
// l'appelant suivant par les macros qui les ont écrites (ad_event_write écrit aussi la ligne du
// tableau markdown). Une ligne qui ne suit pas ce format fait renoncer au cache.
// Pas de cache pour un EFF (un seul effet, décrit selon la ressource décrite, ctx_resource) ni pour un
// refus (son emplacement suit le chemin de l'appelant).
// AD_SUBSPELL_CACHE = 2 : chaque texte trouvé est recalculé et comparé, journaux compris, écarts dans
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

// Le cache ne sert que pendant un composant : rien n'en reste dans le jeu. Tout CACHE_FOLDER est
// effacé, avec le cache/subspell des versions précédentes.
DEFINE_ACTION_FUNCTION ad_subspell_cache_close BEGIN
	DELETE + ~%CACHE_FOLDER%~
END

// Avant la description : cache_hit (texte trouvé : cache_text, cache_count, cache_checked,
// cache_log_cached) ; cache_events_size et cache_recursion_size, tailles des journaux, pour savoir
// ensuite ce que la description y a écrit.
DEFINE_PATCH_MACRO ad_subspell_cache_read BEGIN
	SET cache_hit = 0
	// L'erreur d'un projectile déjà journalisée par l'appelant n'est pas répétée par le sous-sort
	// (ad_log_projectile_error, lib/resources.tpp).
	SPRINT cache_projectiles ~~
	PHP_EACH projectile_error_logged AS cache_projectile => cache_projectile_logged BEGIN
		SPRINT cache_projectiles ~%cache_projectiles%%cache_projectile%,~
	END
	SPRINT cache_key ~%ctx_depth%|%ctx_casting_level%|%ctx_force_target%|%ctx_force_keep_self%|%ctx_ignore_duration%|%ctx_ignore_save%|%ctx_versus_set%|%ctx_base_probability%|%ctx_base_low%|%ctx_base_high%|%ctx_base_lines%|%ctx_lift_sections%|%item_type%|%resource_is_spell%|%support_header_only%|%fx_with_casting%|%ctx_the_target%|%ctx_of_the_target%|%ctx_to_the_target%|%ctx_force_only_for%|%ctx_versus%|%ctx_named_lines%|%cache_projectiles%~
	SPRINT chain_in ~%ctx_chain%~ LPM ad_recursion_caller_chain
	SPRINT cache_caller_chain ~%chain_out%~
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
			REPLACE_EVALUATE CASE_SENSITIVE ~^\([^%TAB%]+\)%TAB%\([0-9]+\)%TAB%\([^%TAB%%MNL%%LNL%]*\)%TAB%\([^%TAB%%MNL%%LNL%]*\)~ BEGIN
				PATCH_IF NOT cache_hit BEGIN
					SET cache_hit = 1
					SPRINT cache_entry ~%MATCH1%~
					SET cache_count = MATCH2
					SPRINT cache_checked ~%MATCH3%~
					SPRINT cache_log_entry ~%MATCH4%~
				END
			END ~%MATCH0%~
		END
	END
	PATCH_IF cache_hit BEGIN
		SPRINT cache_checked_list ~%cache_checked%~
		LPM ad_subspell_cache_chain_free
		SET cache_hit = cache_chain_free
	END
	PATCH_IF cache_hit BEGIN
		SPRINT cache_text ~~
		INNER_PATCH_FILE ~%AD_SUBSPELL_CACHE_FOLDER%/%cache_entry%~ BEGIN
			PATCH_IF BUFFER_LENGTH > 0 BEGIN
				READ_ASCII 0 cache_text (BUFFER_LENGTH)
			END
		END
		SPRINT cache_log_cached ~~
		PATCH_IF NOT (~%cache_log_entry%~ STRING_EQUAL ~~) BEGIN
			INNER_PATCH_FILE ~%AD_SUBSPELL_CACHE_FOLDER%/%cache_log_entry%~ BEGIN
				PATCH_IF BUFFER_LENGTH > 0 BEGIN
					READ_ASCII 0 cache_log_cached (BUFFER_LENGTH)
				END
			END
		END
	END
	// Tronçons en cours des journaux (ad_log_part, lib/install.tpp) ; -1 s'ils n'existent pas encore.
	SET cache_log_part = ad_processed / AD_LOG_PART_SIZE
	SPRINT cache_events_part ~%MOD_FOLDER%/log/%log_name%-events.txt.%cache_log_part%.part~
	SPRINT cache_recursion_part ~%MOD_FOLDER%/log/%log_name%-recursion.txt.%cache_log_part%.part~
	SET cache_events_size = SIZE_OF_FILE ~%cache_events_part%~
	SET cache_recursion_size = SIZE_OF_FILE ~%cache_recursion_part%~
END

// cache_chain_free : aucune des sous-ressources de cache_checked_list (« |RES1||RES2| ») n'est dans la
// chaîne de l'appelant, où elle serait une boucle.
DEFINE_PATCH_MACRO ad_subspell_cache_chain_free BEGIN
	SET cache_chain_free = 1
	INNER_PATCH ~%cache_checked_list%~ BEGIN
		REPLACE_EVALUATE CASE_SENSITIVE ~|\([^|]+\)|~ BEGIN
			PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~|%MATCH1%|~ ~%cache_caller_chain%~) >= 0 BEGIN
				SET cache_chain_free = 0
			END
		END ~%MATCH0%~
	END
END

// Texte rendu par la sous-description (AD_SUBSPELL_CACHE = 1) : celui du cache, et ses journaux
// réécrits pour l'appelant.
DEFINE_PATCH_MACRO ad_subspell_cache_use BEGIN
	SET sub_count = cache_count
	SPRINT sub_text ~%cache_text%~
	SPRINT sub_checked ~%cache_checked%~
	PATCH_IF NOT (~%cache_log_cached%~ STRING_EQUAL ~~) BEGIN
		LPM ad_subspell_cache_replay
	END
END

// Après la description : écart avec le texte trouvé (AD_SUBSPELL_CACHE = 2), sinon texte enregistré.
DEFINE_PATCH_MACRO ad_subspell_cache_store BEGIN
	SPRINT cache_log ~~
	SET cache_log_ok = 1
	SET cache_logged = (SIZE_OF_FILE ~%cache_events_part%~ != cache_events_size)
		OR (SIZE_OF_FILE ~%cache_recursion_part%~ != cache_recursion_size)
	PATCH_IF cache_logged BEGIN
		LPM ad_subspell_cache_record
	END
	PATCH_IF cache_hit BEGIN
		PATCH_IF NOT (~%sub_missing%~ STRING_EQUAL ~~) OR NOT cache_log_ok OR sub_count != cache_count
				OR NOT (~%sub_text%~ STRING_EQUAL ~%cache_text%~) OR NOT (~%sub_checked%~ STRING_EQUAL ~%cache_checked%~)
				OR NOT (~%cache_log%~ STRING_EQUAL ~%cache_log_cached%~) BEGIN
			INNER_ACTION BEGIN
				SILENT
				APPEND_OUTER ~%MOD_FOLDER%/log/%log_name%-subspell-cache.txt~ ~%SOURCE_FILE%%TAB%%sub_resref%%TAB%%cache_key%%WNL%  cached (%cache_count%, %cache_checked%): %cache_text%%WNL%  cached logs: %cache_log_cached%%WNL%  computed (%sub_count%, %sub_checked%, logs readable %cache_log_ok%): %sub_missing%%sub_text%%WNL%  computed logs: %cache_log%~ KEEP_CRLF
				VERBOSE
			END
		END
	END
	ELSE PATCH_IF ~%sub_missing%~ STRING_EQUAL ~~ AND cache_log_ok BEGIN
		// Une boucle journalisée sur une ressource de la chaîne de l'appelant dépend de cet appelant.
		SET cache_chain_free = 1
		PATCH_IF cache_logged BEGIN
			SPRINT cache_checked_list ~%sub_checked%~
			LPM ad_subspell_cache_chain_free
		END
		PATCH_IF cache_chain_free BEGIN
			LPM ad_subspell_cache_write
		END
	END
END

// cache_new_lines : ce que la description a écrit dans le tronçon cache_part, de taille cache_part_size
// avant elle (-1 : absent), sans le « \r\n » qu'APPEND_OUTER écrit d'abord dans un fichier vide (V46).
DEFINE_PATCH_MACRO ad_subspell_cache_new_lines BEGIN
	SPRINT cache_new_lines ~~
	SET cache_from = cache_part_size > 0 ? cache_part_size : 2
	PATCH_IF SIZE_OF_FILE ~%cache_part%~ > cache_from BEGIN
		INNER_PATCH_FILE ~%cache_part%~ BEGIN
			READ_ASCII cache_from cache_new_lines (BUFFER_LENGTH - cache_from)
		END
	END
END

// cache_log : lignes écrites pendant la description sans ce qui dépend de l'appelant, une par ligne :
// « E<TAB>nature<TAB>raison<TAB>conséquence<TAB>suite de l'emplacement<TAB>données<TAB>message »
// (…-events.txt, ad_event_write, lib/log.tpp) puis « R<TAB>suite de la chaîne<TAB>sous-ressource<TAB>
// raison » (…-recursion.txt, ad_log_recursion). cache_log_ok : 0 si une ligne ne suit pas ce format.
DEFINE_PATCH_MACRO ad_subspell_cache_record BEGIN
	SET cache_origin_length = STRING_LENGTH ~%ctx_origin%~
	SET cache_chain_length = STRING_LENGTH ~%cache_caller_chain%~
	SPRINT cache_part ~%cache_events_part%~
	SET cache_part_size = cache_events_size
	LPM ad_subspell_cache_new_lines
	INNER_PATCH ~%cache_new_lines%~ BEGIN
		REPLACE_EVALUATE CASE_SENSITIVE ~\([^%MNL%%LNL%]*\)%MNL%%LNL%~ BEGIN
			SPRINT cache_line ~%MATCH1%~
			SET cache_line_ok = 0
			INNER_PATCH ~%cache_line%~ BEGIN
				REPLACE_EVALUATE CASE_SENSITIVE ~^\([^%TAB%]*\)%TAB%\([^%TAB%]*%TAB%[^%TAB%]*%TAB%[^%TAB%]*\)%TAB%\([^%TAB%]*\)%TAB%\([^%TAB%]*%TAB%[^%TAB%]*\)$~ BEGIN
					PATCH_IF ~%MATCH1%~ STRING_EQUAL ~%SOURCE_FILE%~
							AND INDEX (CASE_SENSITIVE EXACT_MATCH ~%ctx_origin%~ ~%MATCH3%~) == 0 BEGIN
						SET cache_line_ok = 1
						SPRINT cache_fields ~%MATCH2%~
						SPRINT cache_tail ~%MATCH4%~
						INNER_PATCH_SAVE cache_location ~%MATCH3%~ BEGIN
							DELETE_BYTES 0 cache_origin_length
						END
						SPRINT cache_log ~%cache_log%E%TAB%%cache_fields%%TAB%%cache_location%%TAB%%cache_tail%%LNL%~
					END
				END ~%MATCH0%~
			END
			PATCH_IF NOT cache_line_ok BEGIN
				SET cache_log_ok = 0
			END
		END ~%MATCH0%~
	END
	SPRINT cache_part ~%cache_recursion_part%~
	SET cache_part_size = cache_recursion_size
	LPM ad_subspell_cache_new_lines
	INNER_PATCH ~%cache_new_lines%~ BEGIN
		REPLACE_EVALUATE CASE_SENSITIVE ~\([^%MNL%%LNL%]*\)%MNL%%LNL%~ BEGIN
			SPRINT cache_line ~%MATCH1%~
			PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~%cache_caller_chain%~ ~%cache_line%~) == 0 BEGIN
				INNER_PATCH_SAVE cache_line ~%cache_line%~ BEGIN
					DELETE_BYTES 0 cache_chain_length
				END
				SPRINT cache_log ~%cache_log%R%TAB%%cache_line%%LNL%~
			END
			ELSE BEGIN
				SET cache_log_ok = 0
			END
		END ~%MATCH0%~
	END
END

// Réécrit les lignes de cache_log_cached (ad_subspell_cache_record) pour la ressource décrite et le
// chemin de l'appelant.
DEFINE_PATCH_MACRO ad_subspell_cache_replay BEGIN
	INNER_PATCH ~%cache_log_cached%~ BEGIN
		REPLACE_EVALUATE CASE_SENSITIVE ~^E%TAB%\([^%TAB%%LNL%]*\)%TAB%\([^%TAB%%LNL%]*\)%TAB%\([^%TAB%%LNL%]*\)%TAB%\([^%TAB%%LNL%]*\)%TAB%\([^%TAB%%LNL%]*\)%TAB%\([^%TAB%%LNL%]*\)$~ BEGIN
			SPRINT event_kind ~%MATCH1%~
			SPRINT event_code ~%MATCH2%~
			SPRINT event_outcome ~%MATCH3%~
			SPRINT event_location ~%ctx_origin%%MATCH4%~
			SPRINT event_data ~%MATCH5%~
			SPRINT event_message ~%MATCH6%~
			LPM ad_event_write
		END ~%MATCH0%~
		REPLACE_EVALUATE CASE_SENSITIVE ~^R%TAB%\([^%TAB%%LNL%]*\)%TAB%\([^%TAB%%LNL%]*\)%TAB%\([^%TAB%%LNL%]*\)$~ BEGIN
			SPRINT recursion_chain ~%cache_caller_chain%%MATCH1%~
			SPRINT recursion_upper ~%MATCH2%~
			SPRINT recursion_reason ~%MATCH3%~
			LPM ad_log_recursion
		END ~%MATCH0%~
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
	// La taille de l'index, qui croît à chaque ligne, nomme les fichiers du texte et des journaux.
	SPRINT cache_entry ~%sub_resref%.%cache_index_size%.txt~
	SPRINT cache_log_entry ~~
	PATCH_IF NOT (~%cache_log%~ STRING_EQUAL ~~) BEGIN
		SPRINT cache_log_entry ~%sub_resref%.%cache_index_size%.log~
	END
	SET cache_length = STRING_LENGTH ~%sub_text%~
	SET cache_log_length = STRING_LENGTH ~%cache_log%~
	INNER_ACTION BEGIN
		COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%AD_SUBSPELL_CACHE_FOLDER%/%cache_entry%~
			PATCH_IF cache_length > 0 BEGIN
				INSERT_BYTES 0 cache_length
				WRITE_ASCIIE 0 ~%sub_text%~
			END
		ACTION_IF cache_log_length > 0 BEGIN
			COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%AD_SUBSPELL_CACHE_FOLDER%/%cache_log_entry%~
				INSERT_BYTES 0 cache_log_length
				WRITE_ASCIIE 0 ~%cache_log%~
		END
		ACTION_IF NOT FILE_EXISTS ~%cache_index%~ BEGIN
			COPY ~.../AutoDescription/inlined/ad_empty.txt~ ~%cache_index%~
		END
		SILENT
		APPEND_OUTER ~%cache_index%~ ~%LNL%%cache_key%%TAB%%cache_entry%%TAB%%sub_count%%TAB%%sub_checked%%TAB%%cache_log_entry%~ KEEP_CRLF
		VERBOSE
	END
	SPRINT SOURCE_FILE ~%cache_source_file%~
	SPRINT SOURCE_RES ~%cache_source_res%~
	SET SOURCE_SIZE = cache_source_size
END
