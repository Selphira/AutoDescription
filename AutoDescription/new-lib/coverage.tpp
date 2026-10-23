// Couverture d'une ressource d'après le catalogue (new-lib/catalog.tpa), après la lecture des
// effets. Un opcode TODO rend la ressource « non couverte » ; un opcode inconnu (absent du
// catalogue ou du jeu courant) n'est pas décrit, sans empêcher la couverture. Les opcodes TODO et
// inconnus sont journalisés dans …-opcodes.txt, synthétisé en fin de composant (ad_close_log).
// Une ressource sans opcode TODO reçoit la raison not_implemented ; le point d'entrée la couvre
// si son rendu sait la décrire entièrement. Les autres raisons sont des refus (ad_refusal,
// new-lib/log.tpp).
DEFINE_PATCH_MACRO ad_set_coverage BEGIN
	PATCH_IF NOT (~%fx_load_error%~ STRING_EQUAL ~~) BEGIN
		LPF ad_refusal STR_VAR reason = ~file_error:load:%fx_load_error%~ message = ~%fx_load_message%~ RET uncovered_reason = refusal END
	END
	ELSE BEGIN
		SORT_ARRAY_INDICES fx_opcode_count NUMERICALLY
		SPRINT cov_todo ~~
		SPRINT cov_lines ~~
		PHP_EACH fx_opcode_count AS cov_opcode => cov_occurrences BEGIN
			SPRINT cov_kind ~~
			PATCH_IF NOT VARIABLE_IS_SET $AD_OPCODE_STATUS(~%cov_opcode%~) BEGIN
				SPRINT cov_kind ~absent~
			END
			ELSE PATCH_IF NOT $AD_OPCODE_AVAILABLE(~%cov_opcode%~) BEGIN
				SPRINT cov_kind ~unavailable~
			END
			ELSE BEGIN
				SPRINT cov_status $AD_OPCODE_STATUS(~%cov_opcode%~)
				PATCH_IF ~%cov_status%~ STRING_EQUAL ~TODO~ BEGIN
					SPRINT cov_kind ~todo~
					SPRINT cov_todo ~%cov_todo% %cov_opcode%~
				END
			END
			PATCH_IF NOT (~%cov_kind%~ STRING_EQUAL ~~) BEGIN
				// APPEND_OUTER termine lui-même la dernière ligne.
				PATCH_IF NOT (~%cov_lines%~ STRING_EQUAL ~~) BEGIN
					SPRINT cov_lines ~%cov_lines%%WNL%~
				END
				SPRINT cov_lines ~%cov_lines%%SOURCE_RES%%TAB%%cov_opcode%%TAB%%cov_occurrences%%TAB%%cov_kind%~
			END
		END
		PATCH_IF ~%cov_todo%~ STRING_EQUAL ~~ BEGIN
			SPRINT uncovered_reason ~not_implemented~
		END
		ELSE BEGIN
			INNER_PATCH_SAVE cov_todo ~%cov_todo%~ BEGIN
				DELETE_BYTES 0 1
			END
			LPF ad_refusal STR_VAR reason = ~not_implemented:missing_opcodes:%cov_todo%~ message = ~opcodes not supported yet: %cov_todo%~ RET uncovered_reason = refusal END
		END
		PATCH_IF NOT (~%cov_lines%~ STRING_EQUAL ~~) BEGIN
			INNER_ACTION BEGIN
				SILENT
				APPEND_OUTER ~AutoDescription/log/%log_name%-opcodes.txt~ ~%cov_lines%~ KEEP_CRLF
				VERBOSE
			END
		END
	END
END
