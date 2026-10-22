// Récursion : effets d'un sort lancé par un effet (opcodes 146 et 148 sans nom ou d'une potion),
// décrits par les passes du moteur (chargement, prise en charge commune et par opcode,
// regroupements, lignes) dans la portée de ad_describe_subresource : le magasin d'effets et les
// lignes de la ressource parente sont rétablis au retour (V32). Ce qui distingue une sous-ressource
// passe par les variables ctx_*, lues par les passes communes :
// - ctx_depth : profondeur (0 pour la ressource décrite), limitée à AD_RECURSION_MAX_DEPTH ;
// - ctx_chain : ressources de la chaîne au-dessus de la sous-ressource, « |RES1|RES2| » (vide pour
//   la ressource décrite : l'ancien moteur n'y ajoute la ressource parente qu'à sa première
//   sous-description, recursive_resref) ;
// - ctx_force_target : les sous-effets reprennent les chaînes de cible du parent (ctx_the_target,
//   ctx_of_the_target, ctx_to_the_target), chacun gardant sa forme, soi ou cible (ancien forceTarget,
//   opcode 146) ;
// - ctx_area_phrase (0 sans zone), ctx_area_creatures, ctx_area_range, ctx_area_angle : cibles
//   nommées d'après la zone du projectile de l'en-tête du sous-sort (ad_recursion_area_strings) ;
// - ctx_ignore_duration : durées des sous-effets non écrites, hors délais et répétitions (ancien
//   ignoreDuration hérité de la durée commune d'une potion) ;
// - ctx_casting_level : niveau de lancement, qui choisit l'en-tête du sous-sort ;
// - ctx_versus_set, ctx_versus : l'ancien moteur fixe versus (opcode 232), que les dégâts écrivent à la
//   place de leur cible (« à l'attaquant »), même vide (BUG-038) ;
// - ctx_resource : ressource décrite, dont les opcodes comparent les effets à elle-même (exceptions
//   de cible, opcodes 180, 200, 201, 321), comme l'ancien CURRENT_SOURCE_RES.
// Les règles propres aux objets (équipement, capacités de combat, en-têtes à charges) ne
// s'appliquent pas aux sous-effets.

// Contexte d'une ressource décrite seule ; recursion_done et recursion_seen suivent les
// sous-descriptions de la ressource (ad_recursion_allowed).
DEFINE_PATCH_MACRO ad_recursion_reset BEGIN
	SET ctx_depth = 0
	SET ctx_force_target = 0
	SET ctx_area_phrase = 0
	SET ctx_ignore_duration = 0
	SET ctx_casting_level = 0
	SET ctx_versus_set = 0
	SPRINT ctx_versus ~~
	SPRINT ctx_resource ~%SOURCE_RES%~
	TO_UPPER ctx_resource
	SPRINT ctx_chain ~|~
	SET recursion_done = 0
END

// La sous-ressource recursion_resref peut-elle être décrite ? recursion_allowed : 1 si oui ; 0 au-delà
// de AD_RECURSION_MAX_DEPTH ou pour une ressource déjà dans la chaîne, où l'ancien moteur n'écrit
// rien (recursivity, recursive_resref) : aucune ligne, journalisé (…-recursion.txt). L'ancien moteur
// ne retire pas non plus les ressources déjà décrites de sa liste (V36) : un second sort décrit
// par la même ressource, ou le sort qui porte le nom de la ressource après un autre, n'écrit rien
// selon un ordre de traitement qui n'est pas reproduit (recursion_repeated, refusé par l'appelant) ;
// seuls les opcodes 146 et 148 tiennent cette liste (recursion_tracked).
DEFINE_PATCH_MACRO ad_recursion_allowed BEGIN
	SPRINT recursion_upper ~%recursion_resref%~
	TO_UPPER recursion_upper
	SET recursion_allowed = 1
	SET recursion_repeated = 0
	PATCH_IF ctx_depth + 1 > AD_RECURSION_MAX_DEPTH BEGIN
		SET recursion_allowed = 0
		SPRINT recursion_reason ~depth~
	END
	ELSE PATCH_IF INDEX (CASE_SENSITIVE EXACT_MATCH ~|%recursion_upper%|~ ~%ctx_chain%~) >= 0 BEGIN
		SET recursion_allowed = 0
		SPRINT recursion_reason ~loop~
	END
	PATCH_IF NOT recursion_allowed BEGIN
		LPM ad_log_recursion
	END
	ELSE PATCH_IF recursion_tracked BEGIN
		SPRINT recursion_source ~%ctx_resource%~
		TO_UPPER recursion_source
		SET recursion_repeated = VARIABLE_IS_SET $recursion_seen(~%recursion_upper%~)
			OR (recursion_done AND ~%recursion_upper%~ STRING_EQUAL ~%recursion_source%~)
		SET $recursion_seen(~%recursion_upper%~) = 1
		SET recursion_done = 1
	END
END

// Sous-description du sort recursion_resref lancé par l'effet recursion_fx, pour la prise en charge
// de son opcode : résultat dans fx_sub_count et fx_sub_text (ad_describe_subresource), refus dans
// render_missing. L'appelant fixe recursion_casting_level ; recursion_targets : effect (les
// sous-effets reprennent les chaînes de cible de l'effet), given (celles de recursion_the_target,
// recursion_of_the_target, recursion_to_the_target), own (chacun les siennes) ;
// recursion_ignore_duration (durées masquées par l'opcode lui-même ; elles le sont aussi sous la
// durée commune d'une potion) ; recursion_series (répétitions de l'effet acceptées) ;
// recursion_tracked (ad_recursion_allowed) ; recursion_versus_set et recursion_versus (ctx_versus_set,
// ctx_versus). Au-delà de la
// profondeur permise, l'ancien moteur n'écrit rien, même pour un effet probable ou différé. Refus :
// effet probable (l'ancien moteur multiplie les probabilités et retire « N % de chances » des
// sous-lignes) ; effet différé (l'ancien moteur en fait une condition) ; répétitions non acceptées ;
// effet d'un 177 contre un type de créature ; sort déjà décrit par la ressource (recursion_repeated) ;
// cible sans chaînes ; refus de la sous-description.
DEFINE_PATCH_MACRO ad_recursion_support BEGIN
	SET $fx_sub_count(~%recursion_fx%~) = 0
	SPRINT $fx_sub_text(~%recursion_fx%~) ~~
	LPM ad_recursion_allowed
	PATCH_IF recursion_allowed BEGIN
		PATCH_IF $fx_probability(~%recursion_fx%~) < 100 BEGIN
			SPRINT render_missing ~not_implemented:recursion:probability~
		END
		ELSE PATCH_IF $fx_timing(~%recursion_fx%~) == TIMING_delayed AND NOT $fx_series_anchor(~%recursion_fx%~) BEGIN
			SPRINT render_missing ~not_implemented:recursion:delayed~
		END
		ELSE PATCH_IF $fx_series_anchor(~%recursion_fx%~) AND NOT recursion_series BEGIN
			SPRINT render_missing ~not_implemented:recursion:series~
		END
		ELSE PATCH_IF $fx_versus_file(~%recursion_fx%~) > 0 BEGIN
			SPRINT render_missing ~not_implemented:recursion:versus~
		END
		ELSE PATCH_IF recursion_repeated BEGIN
			SPRINT render_missing ~not_implemented:recursion:repeated~
		END
		ELSE BEGIN
			PATCH_IF ~%recursion_targets%~ STRING_EQUAL ~effect~ BEGIN
				SET line_fx = recursion_fx
				SPRINT line_the_target ~~
				LPM ad_application_form
				LPM ad_application_target_strings
				SPRINT line_only_for ~~
				PATCH_IF app_target_missing BEGIN
					SPRINT render_missing ~not_implemented:recursion:target~
				END
				SPRINT recursion_the_target ~%theTarget%~
				SPRINT recursion_of_the_target ~%ofTheTarget%~
				SPRINT recursion_to_the_target ~%toTheTarget%~
			END
			PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
				SET recursion_h = $fx_header(~%recursion_fx%~)
				SET recursion_hide = ctx_ignore_duration OR recursion_ignore_duration
				PATCH_IF item_type == ITM_TYPE_potion AND recursion_h >= 0 BEGIN
					SET recursion_hide = recursion_hide OR $charged_global_duration(~%recursion_h%~) > 0
				END
				LPF ad_describe_subresource
					INT_VAR
						ctx_depth = ctx_depth + 1
						ctx_casting_level = recursion_casting_level
						ctx_force_target = NOT (~%recursion_targets%~ STRING_EQUAL ~own~)
						ctx_ignore_duration = recursion_hide
						ctx_versus_set = recursion_versus_set
					STR_VAR
						resref = ~%recursion_resref%~
						ctx_chain = ~%ctx_chain%~
						ctx_the_target = ~%recursion_the_target%~
						ctx_of_the_target = ~%recursion_of_the_target%~
						ctx_to_the_target = ~%recursion_to_the_target%~
						ctx_versus = ~%recursion_versus%~
					RET
						recursion_sub_missing = sub_missing
						recursion_sub_count = sub_count
						recursion_sub_text = sub_text
				END
				SPRINT render_missing ~%recursion_sub_missing%~
				SET $fx_sub_count(~%recursion_fx%~) = recursion_sub_count
				SPRINT $fx_sub_text(~%recursion_fx%~) ~%recursion_sub_text%~
			END
		END
	END
END

// Texte de la ligne de l'effet recursion_fx, dont le sous-sort est décrit sous une condition (opcodes
// 232, 341) : la sous-ligne seule ; plusieurs, chacune sur sa ligne, en retrait, après la condition
// (ancien add_condition, qui décale les sauts de ligne d'une description commencée par un saut de
// ligne).
DEFINE_PATCH_MACRO ad_recursion_condition_text BEGIN
	SPRINT line_text $fx_sub_text(~%recursion_fx%~)
	PATCH_IF $fx_sub_count(~%recursion_fx%~) > 1 BEGIN
		SPRINT line_text ~%CRLF%- %line_text%~
		INNER_PATCH_SAVE line_text ~%line_text%~ BEGIN
			REPLACE_TEXTUALLY ~%CRLF%~ ~%CRLF%  ~
		END
	END
END

// Lignes du sort resref lancé par un effet du parent (ctx_* : contexte de la sous-ressource, voir
// en tête du fichier) : sub_count lignes, rendues comme l'ancien moteur les insère dans la ligne
// parente (sub_text : la première sans puce, les suivantes après un saut de ligne et une puce) ;
// sub_missing, raison de non-couverture (not_implemented:recursion:<raison>), vide si le sort est
// décrit. En-tête : avec un niveau de lancement, celui du plus haut niveau requis compris entre 1 et
// ce niveau (le premier à égalité, ancien get_spell_headeroffset_for_level) ; sans, l'unique
// en-tête. Refus : sort absent ou illisible ; aucun en-tête de ce niveau (l'ancien moteur lit alors
// le début du fichier comme un en-tête, BUG-037) ; plusieurs en-têtes sans niveau de lancement
// (rendu par niveaux du sort) ; effets de lancement ; opcode à prendre en charge ; tout refus des
// passes ; ligne probable (l'ancien moteur regroupe les lignes probables du sous-sort) ; ligne hors
// de la section de l'en-tête.
DEFINE_PATCH_FUNCTION ad_describe_subresource
	INT_VAR
		ctx_depth = 1
		ctx_casting_level = 0
		ctx_force_target = 0
		ctx_ignore_duration = 0
		ctx_versus_set = 0
	STR_VAR
		resref = ~~
		ctx_chain = ~~
		ctx_the_target = ~~
		ctx_of_the_target = ~~
		ctx_to_the_target = ~~
		ctx_versus = ~~
	RET
		sub_missing
		sub_count
		sub_text
BEGIN
	SPRINT sub_missing ~~
	SET sub_count = 0
	SPRINT sub_text ~~
	SET sub_header = 0 - 1
	SET ctx_area_phrase = 0
	SPRINT sub_resref ~%resref%~
	TO_UPPER sub_resref
	SPRINT ctx_chain ~%ctx_chain%%ctx_resource%|%sub_resref%|~
	PATCH_IF NOT FILE_EXISTS_IN_GAME ~%sub_resref%.spl~ BEGIN
		SPRINT sub_missing ~not_implemented:recursion:missing_file~
	END
	ELSE BEGIN
		SPRINT ctx_resource ~%sub_resref%~
		INNER_PATCH_FILE ~%sub_resref%.spl~ BEGIN
			LPM ad_recursion_load_spell
		END
	END
	PATCH_IF ~%sub_missing%~ STRING_EQUAL ~~ AND sub_header >= 0 BEGIN
		LPM ad_recursion_area
	END
	PATCH_IF ~%sub_missing%~ STRING_EQUAL ~~ AND sub_header >= 0 BEGIN
		LPM ad_recursion_render
	END
END

// Effets de l'en-tête retenu du sort ouvert (sub_header, 0 - 1 si le sort n'a aucun en-tête).
DEFINE_PATCH_MACRO ad_recursion_load_spell BEGIN
	SPRINT sub_signature ~~
	PATCH_IF BUFFER_LENGTH >= 0x72 BEGIN
		READ_ASCII SPL_signature sub_signature (8)
	END
	PATCH_IF NOT (~%sub_signature%~ STRING_EQUAL ~SPL V1  ~) BEGIN
		SPRINT sub_missing ~not_implemented:recursion:unsupported_format~
	END
	ELSE BEGIN
		READ_LONG  SPL_extended_headers_offset     sub_headers_offset
		READ_SHORT SPL_extended_headers_count      sub_header_count
		READ_SHORT SPL_casting_feature_blocks_count sub_casting_count
		PATCH_IF sub_headers_offset < 0 OR sub_headers_offset + sub_header_count * 0x28 > BUFFER_LENGTH BEGIN
			SPRINT sub_missing ~not_implemented:recursion:invalid_header~
		END
		ELSE PATCH_IF sub_casting_count > 0 BEGIN
			SPRINT sub_missing ~not_implemented:recursion:casting_effects~
		END
		ELSE PATCH_IF ctx_casting_level > 0 BEGIN
			SET sub_header_level = 0
			FOR (sub_h = 0; sub_h < sub_header_count; ++sub_h) BEGIN
				READ_SHORT (sub_headers_offset + sub_h * 0x28 + SPL_HEAD_level_required) sub_level
				PATCH_IF sub_level <= ctx_casting_level AND sub_level > sub_header_level BEGIN
					SET sub_header_level = sub_level
					SET sub_header = sub_h
				END
			END
			PATCH_IF sub_header < 0 AND sub_header_count > 0 BEGIN
				SPRINT sub_missing ~not_implemented:recursion:header_level~
			END
		END
		ELSE PATCH_IF sub_header_count > 1 BEGIN
			SPRINT sub_missing ~not_implemented:recursion:headers~
		END
		ELSE PATCH_IF sub_header_count == 1 BEGIN
			SET sub_header = 0
		END
	END
	PATCH_IF ~%sub_missing%~ STRING_EQUAL ~~ AND sub_header >= 0 BEGIN
		LPM ad_fx_reset
		SET fx_header_count = sub_header_count
		SET fx_header_offset = sub_headers_offset + sub_header * 0x28
		READ_LONG  SPL_feature_blocks_offset fx_table_offset
		READ_SHORT (fx_header_offset + SPL_HEAD_feature_blocks_count)  fx_block_count
		READ_SHORT (fx_header_offset + SPL_HEAD_feature_blocks_offset) fx_block_index
		READ_BYTE  (fx_header_offset + SPL_HEAD_target)        sub_head_target
		READ_BYTE  (fx_header_offset + SPL_HEAD_target_number) sub_head_target_count
		READ_SHORT (fx_header_offset + SPL_HEAD_projectile)    sub_projectile
		SPRINT fx_block_kind ~ability~
		SET fx_block_header = sub_header
		LPM ad_fx_load_block
		PATCH_IF NOT (~%fx_load_error%~ STRING_EQUAL ~~) BEGIN
			SPRINT sub_missing ~not_implemented:recursion:%fx_load_error%~
		END
	END
END

// Zone du projectile de l'en-tête du sous-sort (ancien get_target_by_projectile, appelé pour chaque
// sous-effet) : selon la forme de la zone et la cible de l'en-tête, « les créatures dans un rayon de
// 4,5 mètres », « … autour du buveur » (sur soi ou une créature, projectile qui ignore sa cible ou,
// sur soi, ne vise que les hostiles), « la cible et les créatures dans un rayon de… ». Refus : fichier
// illisible, distance trop courte, plusieurs cibles, autre cible d'en-tête (l'ancien moteur garde
// alors les chaînes de cible).
DEFINE_PATCH_MACRO ad_recursion_area BEGIN
	LPF ad_projectile_area INT_VAR projectile = sub_projectile RET sub_area_shape = area_shape
		ctx_area_creatures = area_creatures sub_area_feet = area_feet ctx_area_angle = area_angle
		sub_area_cone = area_cone sub_area_ignore = area_ignore_target END
	PATCH_IF sub_area_shape < 0 BEGIN
		SPRINT sub_missing ~not_implemented:recursion:projectile_target~
	END
	ELSE PATCH_IF sub_area_shape > 0 BEGIN
		LPF ad_distance_text INT_VAR feet = sub_area_feet RET ctx_area_range = text END
		PATCH_IF ~%ctx_area_range%~ STRING_EQUAL ~~ BEGIN
			SPRINT sub_missing ~not_implemented:recursion:area_range~
		END
		ELSE PATCH_IF sub_area_cone BEGIN
			SET ctx_area_phrase = sub_area_shape == 2 ? 2001102 : 2001100 // ~%target% dans un rayon de %range%~
		END
		ELSE PATCH_IF sub_head_target == TARGET_HEAD_self OR sub_head_target == TARGET_HEAD_self_ignore_pause BEGIN
			SET ctx_area_phrase = (sub_area_ignore OR ctx_area_creatures > 0) ? 2001101 : 2001103 // ~%target% dans un rayon de %range% autour %ofTheTarget%~
		END
		ELSE PATCH_IF sub_head_target == TARGET_HEAD_creature AND sub_head_target_count <= 1 BEGIN
			SET ctx_area_phrase = sub_area_ignore ? 2001101 : 2001103 // ~%main_target% et %target% dans un rayon de %range%~
		END
		ELSE PATCH_IF sub_head_target == TARGET_HEAD_area BEGIN
			SET ctx_area_phrase = 2001100 // ~%target% dans un rayon de %range%~
		END
		ELSE BEGIN
			SPRINT sub_missing ~not_implemented:recursion:area_target~
		END
	END
END

// Chaînes de cible theTarget, ofTheTarget et toTheTarget remplacées par la zone du sous-sort
// (ad_recursion_area) ; chacune est construite à partir des trois chaînes d'origine.
DEFINE_PATCH_MACRO ad_recursion_area_strings BEGIN
	SPRINT range ~%ctx_area_range%~
	SET angle = ctx_area_angle
	SPRINT $area_main(~0~) ~%theTarget%~
	SPRINT $area_main(~1~) ~%ofTheTarget%~
	SPRINT $area_main(~2~) ~%toTheTarget%~
	FOR (area_form = 0; area_form < 3; ++area_form) BEGIN
		LPF ad_tra INT_VAR tra_id = 2001000 + ctx_area_creatures * 10 + area_form
			tra_block_start = 2001000 tra_block_size = 100 RET target = text END // ~les créatures~
		SPRINT main_target $area_main(~%area_form%~)
		LPF ad_tra INT_VAR tra_id = ctx_area_phrase RET area_text = text END
		SPRINT $area_text(~%area_form%~) ~%area_text%~
	END
	SPRINT theTarget   $area_text(~0~)
	SPRINT ofTheTarget $area_text(~1~)
	SPRINT toTheTarget $area_text(~2~)
END

// Passes du moteur sur les effets du sous-sort, puis texte de ses lignes. L'en-tête du sous-sort
// n'est ni une capacité de charge d'objet ni l'en-tête d'une potion.
DEFINE_PATCH_MACRO ad_recursion_render BEGIN
	SET $charged_other(~%sub_header%~) = 0
	SET $charged_global_duration(~%sub_header%~) = 0
	SORT_ARRAY_INDICES fx_opcode_count NUMERICALLY
	SPRINT sub_todo ~~
	SPRINT sub_versus_opcode ~~
	PHP_EACH fx_opcode_count AS render_opcode => _ BEGIN
		PATCH_IF ctx_versus_set AND VARIABLE_IS_SET $AD_OPCODES_READ_VERSUS(~%render_opcode%~) BEGIN
			SPRINT sub_versus_opcode ~%render_opcode%~
		END
		PATCH_IF VARIABLE_IS_SET $AD_OPCODE_STATUS(~%render_opcode%~) BEGIN
			SPRINT sub_status $AD_OPCODE_STATUS(~%render_opcode%~)
			PATCH_IF $AD_OPCODE_AVAILABLE(~%render_opcode%~) AND (~%sub_status%~ STRING_EQUAL ~TODO~) BEGIN
				SPRINT sub_todo ~%sub_todo% %render_opcode%~
			END
		END
	END
	SPRINT render_missing ~~
	SPRINT render_late_missing ~~
	PATCH_IF NOT (~%sub_versus_opcode%~ STRING_EQUAL ~~) BEGIN
		SPRINT render_missing ~not_implemented:versus_opcode%sub_versus_opcode%~
	END
	ELSE PATCH_IF NOT (~%sub_todo%~ STRING_EQUAL ~~) BEGIN
		INNER_PATCH_SAVE sub_todo ~%sub_todo%~ BEGIN
			DELETE_BYTES 0 1
		END
		SPRINT render_missing ~not_implemented:missing_opcodes:%sub_todo%~
	END
	ELSE BEGIN
		LPM ad_application_support
	END
	PHP_EACH fx_opcode_count AS render_opcode => _ BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
			LPM ad_opcode_is_described
			PATCH_IF opcode_described BEGIN
				LPM ~ad_op_%render_opcode%_support~
			END
		END
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_lines_reset
		LPM ad_cross_groups
		PHP_EACH fx_opcode_count AS render_opcode => _ BEGIN
			LPM ad_opcode_is_described
			PATCH_IF opcode_described BEGIN
				LPM ~ad_op_%render_opcode%_lines~
			END
		END
		SPRINT render_missing ~%render_late_missing%~
	END
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPF ad_lines_section_text STR_VAR section = EVAL ~ability%sub_header%~ RET sub_text = text sub_count = count END
		PATCH_IF sub_count != line_count BEGIN
			SPRINT render_missing ~not_implemented:section~
		END
		FOR (sub_line = 0; sub_line < line_count; ++sub_line) BEGIN
			PATCH_IF $line_probability(~%sub_line%~) > 0 BEGIN
				SPRINT render_missing ~not_implemented:probability~
			END
		END
		// L'ancien moteur retire la puce de la première ligne, qui prend la place de la ligne parente.
		SPRINT sub_bullet ~%CRLF%- ~
		PATCH_IF sub_count > 0 BEGIN
			INNER_PATCH_SAVE sub_text ~%sub_text%~ BEGIN
				DELETE_BYTES 0 STRING_LENGTH ~%sub_bullet%~
			END
		END
	END
	PATCH_IF NOT (~%render_missing%~ STRING_EQUAL ~~) BEGIN
		SPRINT sub_missing ~%render_missing%~
		INNER_PATCH_SAVE sub_missing ~%sub_missing%~ BEGIN
			REPLACE_TEXTUALLY ~^not_implemented:~ ~not_implemented:recursion:~
		END
		SET sub_count = 0
		SPRINT sub_text ~~
	END
END
