// Flux de rendu commun aux trois contextes : objet décrit (lib/item_render.tpp), sous-ressource
// (lib/recursion.tpp), en-tête et section « PARAMÈTRES » d'un sort (lib/spell_header.tpp,
// lib/spell_levels.tpp). Chaque opcode décrit dans le jeu courant (AD_OPCODE_DESCRIBED,
// lib/catalog.tpa) est appelé par son nom, ad_op_<N>_support puis ad_op_<N>_lines ; un opcode
// inconnu (absent du catalogue ou du jeu courant) n'est jamais décrit. render_opcode est l'opcode
// en cours : seules ces boucles l'écrivent.

// Prise en charge commune, puis celle de chaque opcode décrit, dans l'ordre de fx_opcode_count
// (trié par l'appelant) ; un refus (render_missing) arrête les suivantes. Les regroupements
// (ad_cross_groups) restent à l'appelant : l'en-tête d'un sort passe d'abord à « soi » la cible
// préréglée d'un sort personnel, que les macros des opcodes lisent encore préréglée.
DEFINE_PATCH_MACRO ad_render_support BEGIN
	PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ BEGIN
		LPM ad_application_support
	END
	PHP_EACH fx_opcode_count AS render_opcode => _ BEGIN
		PATCH_IF ~%render_missing%~ STRING_EQUAL ~~ AND VARIABLE_IS_SET $AD_OPCODE_DESCRIBED(~%render_opcode%~) BEGIN
			LPM ~ad_op_%render_opcode%_support~
		END
	END
END

// Lignes des sous-ressources et des effets dérivés, puis de chaque opcode décrit dans l'ordre des
// clés du tableau nommé par render_order (fx_opcode_count, ou l'ordre des effets restants d'un
// sort) ; les lignes sont remises à zéro par l'appelant (ad_lines_reset). Chaque appelant pose
// render_order, qu'une sous-description hérite de la ressource qui la cite.
DEFINE_PATCH_MACRO ad_render_lines BEGIN
	LPM ad_recursion_describe_pending
	LPM ad_derived_lines
	LPM ad_fx_ids_late_order
	PHP_EACH ~%render_order%~ AS render_opcode => _ BEGIN
		PATCH_IF VARIABLE_IS_SET $AD_OPCODE_DESCRIBED(~%render_opcode%~) BEGIN
			PATCH_TIME ~step:lines~ BEGIN
				LPM ~ad_op_%render_opcode%_lines~
			END
		END
	END
END
