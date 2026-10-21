// Exceptions de cible (opcodes 318 et 324 qui visent la ressource elle-même, ancien load_opcode et
// opcode_324_target_exceptions) : l'ancien moteur les écarte, sans ligne propre, et écrit
// « (Inefficace contre les morts-vivants et les golems) » à la fin de la ligne de chaque effet lu
// après elles dans le même bloc (équipement ou en-tête) ; ses regroupements ne les comparent pas.
// Les noms viennent de 2da/target_exceptions.2da (AD_TARGET_EXCEPTION_*, new-lib/catalog.tpa). Les
// macros ad_op_<N>_* fixent exception_opcode puis appellent les macros ci-dessous.

// Au chargement (ad_fx_load_block, new-lib/effects.tpp) : fx_exception (1 pour une exception) et
// fx_exception_count (nombre d'exceptions lues avant l'effet dans son bloc ; les exceptions d'un
// effet sont celles de son bloc qui le précèdent). Un 318 ou un 324 d'un EFF n'en est pas une :
// l'ancien moteur ne teste que l'opcode lu dans la ressource, avant de remplacer le 177. Sur la
// ressource elle-même, parameter1 et parameter2 nuls : l'ancien moteur n'écrit rien (ligne 0 de ses
// phrases, vide), quels que soient ses autres champs ; écarté dès ici (fx_consumed, fx_dropped),
// sauf le 318 d'un jeu classique, refusé ensuite.
DEFINE_PATCH_MACRO ad_fx_mark_target_exception BEGIN
	SET $fx_exception_count(~%fx_id%~) = fx_block_exceptions
	SET $fx_exception(~%fx_id%~) = 0
	SET exception_opcode = $fx_opcode(~%fx_id%~)
	PATCH_IF (exception_opcode == 318 OR exception_opcode == 324) AND NOT $fx_external(~%fx_id%~) BEGIN
		SPRINT exception_resource $fx_resource(~%fx_id%~)
		PATCH_IF ~%exception_resource%~ STRING_EQUAL_CASE ~%SOURCE_RES%~ BEGIN
			PATCH_IF $fx_parameter1(~%fx_id%~) != 0 OR $fx_parameter2_raw(~%fx_id%~) != 0 BEGIN
				SET $fx_exception(~%fx_id%~) = 1
				SET fx_block_exceptions += 1
			END
			ELSE PATCH_IF IS_EE OR exception_opcode == 324 BEGIN
				SET $fx_consumed(~%fx_id%~) = 1
				SET $fx_dropped(~%fx_id%~) = 1
			END
		END
	END
END

// Effets exception_opcode qui ne sont pas déjà écartés : écartés, avec les noms de leur exception.
// Refus : effet d'un EFF ; 318 d'un jeu classique (Set Stat de ToBEx, pas une protection) ; autre
// ressource (l'ancien moteur en fait une immunité au sort ou à l'objet, ou des exceptions des
// effets de cette ressource).
DEFINE_PATCH_MACRO ad_target_exception_support BEGIN
	FOR (exception_id = 0; exception_id < fx_count AND ~%render_missing%~ STRING_EQUAL ~~; ++exception_id) BEGIN
		PATCH_IF $fx_opcode(~%exception_id%~) == exception_opcode AND NOT $fx_consumed(~%exception_id%~) BEGIN
			SPRINT exception_resource $fx_resource(~%exception_id%~)
			PATCH_IF $fx_external(~%exception_id%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode%exception_opcode%:external~
			END
			ELSE PATCH_IF exception_opcode == 318 AND NOT IS_EE BEGIN
				SPRINT render_missing ~not_implemented:opcode318:classic~
			END
			ELSE PATCH_IF NOT (~%exception_resource%~ STRING_EQUAL_CASE ~%SOURCE_RES%~) BEGIN
				SPRINT render_missing ~not_implemented:opcode%exception_opcode%:resource~
			END
			ELSE BEGIN
				LPM ad_target_exception_names
				SET drop_id = exception_id
				LPM ad_application_drop
			END
		END
	END
END

// Noms de l'exception exception_id : fx_exception_kind (EFFECTIVE, NOT_EFFECTIVE, BETWEEN, IF,
// EFFECTIVE_IF), fx_exception_name(id n) et fx_exception_name_count. Ligne parameter2 de
// splprot.2da, dans l'ordre de l'ancien moteur : valeur parameter1 d'un fichier IDS (102-109
// inefficace, 112-118 effectif) ; état de sort (76 et 110 inefficace, 111 effectif ; 121, Manteau,
// ignoré comme dans l'ancien moteur) ; état (138 inefficace, 139 effectif) ; sinon la table, où
// « chapitre 6 » (136) est la pénurie de fer. Refus : type de créature, état ou état de sort sans
// nom ; ligne des EE au-delà de 145 (l'ancien moteur reprend la condition de l'opcode 326) ou
// absente de la table (l'ancien moteur n'écrit rien).
DEFINE_PATCH_MACRO ad_target_exception_names BEGIN
	SET exception_stat = $fx_parameter2_raw(~%exception_id%~)
	SET exception_value = $fx_parameter1(~%exception_id%~)
	SET exception_name_count = 0
	SPRINT exception_kind ~~
	PATCH_IF (exception_stat >= 102 AND exception_stat <= 109) OR (exception_stat >= 112 AND exception_stat <= 118) BEGIN
		SPRINT exception_kind ~EFFECTIVE~
		SET exception_ids_file = exception_stat - 110
		PATCH_IF exception_stat <= 109 BEGIN
			SPRINT exception_kind ~NOT_EFFECTIVE~
			SET exception_ids_file = exception_stat - 100
		END
		LPF ad_ids_name INT_VAR ids_file = exception_ids_file entry = exception_value RET exception_name = name END
		LPM ad_target_exception_add_name
	END
	ELSE PATCH_IF exception_stat == 76 OR exception_stat == 110 OR exception_stat == 111 BEGIN
		SPRINT exception_kind ~NOT_EFFECTIVE~
		PATCH_IF exception_stat == 111 BEGIN
			SPRINT exception_kind ~EFFECTIVE~
		END
		PATCH_IF exception_value != 121 BEGIN
			SET exception_tra = 8120000 + exception_value
			SPRINT exception_name ~~
			PATCH_IF exception_value >= 0 AND exception_value <= 255 AND TRA_ENTRY_EXISTS (~%exception_tra%~) BEGIN
				LPF ad_tra INT_VAR tra_id = exception_tra tra_block_start = 8120000 tra_block_size = 256 RET splstateName = text END // ~« Bouclier »~ (@8120126)
				SPRINT exception_name @23240005 // ~créatures affectées par %splstateName%~
			END
			LPM ad_target_exception_add_name
		END
	END
	ELSE PATCH_IF exception_stat == 138 OR exception_stat == 139 BEGIN
		SPRINT exception_kind ~NOT_EFFECTIVE~
		PATCH_IF exception_stat == 139 BEGIN
			SPRINT exception_kind ~EFFECTIVE~
		END
		LPM ad_target_exception_state
		SPRINT exception_name ~~
		PATCH_IF NOT (~%descriptionState%~ STRING_EQUAL ~~) BEGIN
			SPRINT exception_name @23240006 // ~créatures %descriptionState%~
		END
		LPM ad_target_exception_add_name
	END
	ELSE PATCH_IF IS_EE AND exception_stat > 145 BEGIN
		SPRINT render_missing ~not_implemented:opcode%exception_opcode%:condition~
	END
	ELSE PATCH_IF VARIABLE_IS_SET $AD_TARGET_EXCEPTION_KIND(~%exception_stat%~) BEGIN
		SPRINT exception_kind $AD_TARGET_EXCEPTION_KIND(~%exception_stat%~)
		SET exception_tra = $AD_TARGET_EXCEPTION_TEXT(~%exception_stat%~)
		SET value = exception_value
		PATCH_IF exception_stat == 136 AND exception_value == 6 BEGIN
			SPRINT exception_kind ~EFFECTIVE_IF~
			SPRINT exception_name @23240007 // ~durant la pénurie de fer~
			LPM ad_target_exception_add_name
		END
		ELSE PATCH_IF exception_tra > 0 BEGIN
			LPF ad_tra INT_VAR tra_id = exception_tra tra_block_start = 23241000 tra_block_size = 1000 RET exception_name = text END // ~créatures immunisées aux poisons~ (@23241077)
			LPM ad_target_exception_add_name
		END
		ELSE BEGIN
			FOR (exception_n = 0; exception_n < $AD_TARGET_EXCEPTION_IDS_COUNT(~%exception_stat%~); ++exception_n) BEGIN
				SET exception_ids = $AD_TARGET_EXCEPTION_IDS(~%exception_stat%~ ~%exception_n%~)
				LPF ad_ids_name INT_VAR ids_file = exception_ids / 1000 entry = exception_ids MODULO 1000 RET exception_name = name END
				LPM ad_target_exception_add_name
			END
		END
	END
	ELSE BEGIN
		SPRINT render_missing ~not_implemented:opcode%exception_opcode%:stat~
	END
	SPRINT $fx_exception_kind(~%exception_id%~) ~%exception_kind%~
	SET $fx_exception_name_count(~%exception_id%~) = exception_name_count
END

DEFINE_PATCH_MACRO ad_target_exception_add_name BEGIN
	PATCH_IF ~%exception_name%~ STRING_EQUAL ~~ BEGIN
		SPRINT render_missing ~not_implemented:opcode%exception_opcode%:name~
	END
	ELSE BEGIN
		SPRINT $fx_exception_name(~%exception_id%~ ~%exception_name_count%~) ~%exception_name%~
		SET exception_name_count += 1
	END
END

// États de exception_value (ancien get_states_str) : un nom par bit, rang 1 à 32, réunis par
// « ou » ; sans bit, « sous aucun effet ». Un bit sans nom : descriptionState vide.
DEFINE_PATCH_MACRO ad_target_exception_state BEGIN
	SPRINT descriptionState ~~
	SPRINT exception_or @1000007 // ~ou~
	SET exception_state_ok = 1
	SET exception_mask = 1
	FOR (exception_rank = 1; exception_rank <= 32; ++exception_rank) BEGIN
		PATCH_IF (exception_value BAND exception_mask) != 0 BEGIN
			SET exception_tra = 8110000 + exception_rank
			PATCH_IF TRA_ENTRY_EXISTS (~%exception_tra%~) BEGIN
				LPF ad_tra INT_VAR tra_id = exception_tra tra_block_start = 8110000 tra_block_size = 33 RET exception_state_name = text END // ~sous l'effet de « Non-détection »~ (@8110022)
				PATCH_IF ~%descriptionState%~ STRING_EQUAL ~~ BEGIN
					SPRINT descriptionState ~%exception_state_name%~
				END
				ELSE BEGIN
					SPRINT descriptionState ~%descriptionState% %exception_or% %exception_state_name%~
				END
			END
			ELSE BEGIN
				SET exception_state_ok = 0
			END
		END
		SET exception_mask = exception_mask * 2
	END
	PATCH_IF NOT exception_state_ok BEGIN
		SPRINT descriptionState ~~
	END
	ELSE PATCH_IF ~%descriptionState%~ STRING_EQUAL ~~ BEGIN
		SPRINT descriptionState @8110000 // ~sous aucun effet~
	END
END

// Texte des exceptions de l'effet line_fx (ancien opcode_324_target_exceptions), vide sans
// exception nommée. Probabilité de chaque exception : la sienne, ou, pour un effet probable dont la
// plage recouvre la sienne, 100 % si une borne est commune, sinon la part de la plage commune dans
// celle de l'effet. Exceptions groupées par probabilité décroissante, « à 91 % » devant une
// probabilité partielle ; « Effectif… » (conditions, puis types de créatures), puis
// « Inefficace… » (types de créatures, plages horaires, conditions), séparés par un point.
DEFINE_PATCH_MACRO ad_application_target_exceptions BEGIN
	SPRINT app_exceptions_text ~~
	SPRINT exc_the @2002000 // ~les~
	SPRINT exc_and_the @2002001 // ~et les~
	SPRINT exc_effective_and ~%exc_and_the%~
	SPRINT exc_not_effective_and ~%exc_and_the%~
	SET exc_base = $fx_probability(~%line_fx%~)
	SET exc_base_high = $fx_probability1(~%line_fx%~)
	SET exc_base_low = $fx_probability2(~%line_fx%~)
	SPRINT exc_scope $fx_scope(~%line_fx%~)
	FOR (exc_id = 0; exc_id < line_fx; ++exc_id) BEGIN
		SPRINT exc_id_scope $fx_scope(~%exc_id%~)
		PATCH_IF $fx_exception(~%exc_id%~) AND (~%exc_id_scope%~ STRING_EQUAL ~%exc_scope%~) BEGIN
			SET exc_high = $fx_probability1(~%exc_id%~)
			SET exc_low = $fx_probability2(~%exc_id%~)
			SET exc_probability = $fx_probability(~%exc_id%~)
			PATCH_IF exc_base < 100 AND exc_base_high >= exc_low AND exc_base_low <= exc_high BEGIN
				PATCH_IF exc_base_high == exc_high OR exc_base_low == exc_low BEGIN
					SET exc_probability = 100
				END
				ELSE BEGIN
					SET exc_common_high = exc_base_high > exc_high ? exc_high : exc_base_high
					SET exc_common_high = exc_common_high > 99 ? 99 : exc_common_high
					SET exc_common_low = exc_base_low < exc_low ? exc_low : exc_base_low
					SET exc_probability = (exc_common_low <= exc_common_high ? exc_common_high - exc_common_low + 1 : 0) * 100 / exc_base
				END
			END
			SET $exc_key(~%exc_id%~) = 100 - exc_probability
		END
	END
	CLEAR_ARRAY exc_effective_all
	CLEAR_ARRAY exc_not_effective_all
	CLEAR_ARRAY exc_between_all
	CLEAR_ARRAY exc_if_all
	CLEAR_ARRAY exc_effective_if_all
	FOR (exc_key = 0; exc_key <= 100; ++exc_key) BEGIN
		CLEAR_ARRAY exc_EFFECTIVE
		CLEAR_ARRAY exc_NOT_EFFECTIVE
		CLEAR_ARRAY exc_BETWEEN
		CLEAR_ARRAY exc_IF
		CLEAR_ARRAY exc_EFFECTIVE_IF
		SET exc_found = 0
		FOR (exc_id = 0; exc_id < line_fx; ++exc_id) BEGIN
			SPRINT exc_id_scope $fx_scope(~%exc_id%~)
			PATCH_IF $fx_exception(~%exc_id%~) AND (~%exc_id_scope%~ STRING_EQUAL ~%exc_scope%~) BEGIN
				PATCH_IF $exc_key(~%exc_id%~) == exc_key BEGIN
					SET exc_found = 1
					SPRINT exc_kind $fx_exception_kind(~%exc_id%~)
					FOR (exc_n = 0; exc_n < $fx_exception_name_count(~%exc_id%~); ++exc_n) BEGIN
						SPRINT exc_name $fx_exception_name(~%exc_id%~ ~%exc_n%~)
						SPRINT $EVAL ~exc_%exc_kind%~(~%exc_name%~) ~%exc_name%~
					END
				END
			END
		END
		PATCH_IF exc_found BEGIN
			SET probability = 100 - exc_key
			SPRINT exc_prefix ~~
			PATCH_IF probability < 100 BEGIN
				SPRINT exc_prefix @23240004 // ~à %probability% % ~
			END
			LPF ad_join STR_VAR array_name = ~exc_EFFECTIVE~ glue = EVAL ~, %exc_the% ~ final_glue = EVAL ~ %exc_and_the% ~ RET creaturesList = text END
			PATCH_IF NOT (~%creaturesList%~ STRING_EQUAL ~~) BEGIN
				PATCH_IF probability < 100 BEGIN
					SPRINT exc_effective_and ~%AD_AND%~
				END
				SPRINT exc_text @23240003 // ~contre les %creaturesList%~
				SPRINT exc_text ~%exc_prefix%%exc_text%~
				SPRINT $exc_effective_all(~%exc_text%~) ~%exc_text%~
			END
			LPF ad_join STR_VAR array_name = ~exc_NOT_EFFECTIVE~ glue = EVAL ~, %exc_the% ~ final_glue = EVAL ~ %exc_and_the% ~ RET creaturesList = text END
			PATCH_IF NOT (~%creaturesList%~ STRING_EQUAL ~~) BEGIN
				PATCH_IF probability < 100 BEGIN
					SPRINT exc_not_effective_and ~%AD_AND%~
				END
				SPRINT exc_text @23240003 // ~contre les %creaturesList%~
				SPRINT exc_text ~%exc_prefix%%exc_text%~
				SPRINT $exc_not_effective_all(~%exc_text%~) ~%exc_text%~
			END
			LPF ad_join STR_VAR array_name = ~exc_BETWEEN~ RET exc_text = text END
			PATCH_IF NOT (~%exc_text%~ STRING_EQUAL ~~) BEGIN
				SPRINT exc_text ~%exc_prefix%%exc_text%~
				SPRINT $exc_between_all(~%exc_text%~) ~%exc_text%~
			END
			LPF ad_join STR_VAR array_name = ~exc_IF~ RET exc_text = text END
			PATCH_IF NOT (~%exc_text%~ STRING_EQUAL ~~) BEGIN
				SPRINT exc_text ~%exc_prefix%%exc_text%~
				SPRINT $exc_if_all(~%exc_text%~) ~%exc_text%~
			END
			LPF ad_join STR_VAR array_name = ~exc_EFFECTIVE_IF~ RET exc_text = text END
			PATCH_IF NOT (~%exc_text%~ STRING_EQUAL ~~) BEGIN
				SPRINT exc_text ~%exc_prefix%%exc_text%~
				SPRINT $exc_effective_if_all(~%exc_text%~) ~%exc_text%~
			END
		END
	END
	CLEAR_ARRAY exc_conditions
	LPF ad_join STR_VAR array_name = ~exc_effective_if_all~ RET exc_text = text END
	PATCH_IF NOT (~%exc_text%~ STRING_EQUAL ~~) BEGIN
		SPRINT $exc_conditions(~%exc_text%~) ~%exc_text%~
	END
	LPF ad_join STR_VAR array_name = ~exc_effective_all~ glue = EVAL ~, %exc_the% ~ final_glue = EVAL ~ %exc_effective_and% ~ RET exc_text = text END
	PATCH_IF NOT (~%exc_text%~ STRING_EQUAL ~~) BEGIN
		SPRINT $exc_conditions(~%exc_text%~) ~%exc_text%~
	END
	LPF ad_join STR_VAR array_name = ~exc_conditions~ glue = ~, ~ final_glue = ~, ~ RET creaturesList = text END
	SPRINT exc_effective ~~
	PATCH_IF NOT (~%creaturesList%~ STRING_EQUAL ~~) BEGIN
		SPRINT exc_effective @23240001 // ~Effectif %creaturesList%~
	END
	CLEAR_ARRAY exc_conditions
	LPF ad_join STR_VAR array_name = ~exc_not_effective_all~ glue = EVAL ~, %exc_the% ~ final_glue = EVAL ~ %exc_not_effective_and% ~ RET exc_text = text END
	PATCH_IF NOT (~%exc_text%~ STRING_EQUAL ~~) BEGIN
		SPRINT $exc_conditions(~%exc_text%~) ~%exc_text%~
	END
	LPF ad_join STR_VAR array_name = ~exc_between_all~ glue = EVAL ~ %AD_AND% ~ RET exc_text = text END
	PATCH_IF NOT (~%exc_text%~ STRING_EQUAL ~~) BEGIN
		SPRINT $exc_conditions(~%exc_text%~) ~%exc_text%~
	END
	LPF ad_join STR_VAR array_name = ~exc_if_all~ RET exc_text = text END
	PATCH_IF NOT (~%exc_text%~ STRING_EQUAL ~~) BEGIN
		SPRINT $exc_conditions(~%exc_text%~) ~%exc_text%~
	END
	LPF ad_join STR_VAR array_name = ~exc_conditions~ glue = ~, ~ final_glue = ~, ~ RET targetCondition = text END
	SPRINT exc_not_effective ~~
	PATCH_IF NOT (~%targetCondition%~ STRING_EQUAL ~~) BEGIN
		SPRINT exc_not_effective @23240002 // ~Inefficace %targetCondition%~
	END
	PATCH_IF NOT (~%exc_effective%~ STRING_EQUAL ~~) AND NOT (~%exc_not_effective%~ STRING_EQUAL ~~) BEGIN
		SPRINT app_exceptions_text ~%exc_effective%. %exc_not_effective%~
	END
	ELSE BEGIN
		SPRINT app_exceptions_text ~%exc_effective%%exc_not_effective%~
	END
END

// Lignes : aucune pour l'opcode. Les regroupements de l'ancien moteur ne comparent pas les
// exceptions. Refus : effets identiques réunis avec des exceptions différentes ; effet réuni par
// un autre regroupement dans une portée qui a des exceptions (la ligne réunie n'aurait pas
// forcément celles de l'ancien moteur).
DEFINE_PATCH_MACRO ad_target_exception_lines BEGIN
	CLEAR_ARRAY exception_scopes
	FOR (exception_id = 0; exception_id < fx_count; ++exception_id) BEGIN
		PATCH_IF $fx_exception_count(~%exception_id%~) > 0 AND NOT $fx_exception(~%exception_id%~) BEGIN
			SPRINT exception_scope $fx_scope(~%exception_id%~)
			SET $exception_scopes(~%exception_scope%~) = 1
		END
	END
	FOR (exception_id = 0; exception_id < fx_count; ++exception_id) BEGIN
		SET exception_anchor = $fx_identical_anchor(~%exception_id%~)
		SET exception_count = $fx_exception_count(~%exception_id%~)
		SPRINT exception_scope $fx_scope(~%exception_id%~)
		PATCH_IF exception_anchor != exception_id BEGIN
			SPRINT exception_anchor_scope $fx_scope(~%exception_anchor%~)
			PATCH_IF exception_count != $fx_exception_count(~%exception_anchor%~)
					OR (exception_count > 0 AND NOT (~%exception_scope%~ STRING_EQUAL ~%exception_anchor_scope%~)) BEGIN
				SPRINT render_late_missing ~not_implemented:opcode%exception_opcode%:exceptions_identical~
			END
		END
		ELSE PATCH_IF $fx_consumed(~%exception_id%~) AND NOT $fx_dropped(~%exception_id%~) AND VARIABLE_IS_SET $exception_scopes(~%exception_scope%~) BEGIN
			SPRINT render_late_missing ~not_implemented:opcode%exception_opcode%:exceptions_group~
		END
	END
END
