// Noms des ressources citées par les effets.

// Nom d'un sort : nom imposé par AD_SPELL_NAMES (new-lib/catalog.tpa ; vide : sort à ne pas citer),
// sinon nom non identifié du fichier ; vide si le sort n'existe pas ou n'a pas de nom.
DEFINE_PATCH_FUNCTION ad_spell_name
	STR_VAR
		resref = ~~
	RET
		name
BEGIN
	SPRINT name ~~
	SPRINT spell_key ~%resref%~
	TO_LOWER spell_key
	PATCH_IF VARIABLE_IS_SET $AD_SPELL_NAMES(~%spell_key%~) BEGIN
		SET spell_name_tra = $AD_SPELL_NAMES(~%spell_key%~)
		LPF ad_tra INT_VAR tra_id = spell_name_tra RET name = text END
	END
	ELSE PATCH_IF NOT ~%resref%~ STRING_EQUAL ~~ AND FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
		INNER_PATCH_FILE ~%resref%.spl~ BEGIN
			READ_LONG SPL_unidentified_name spell_name_ref
			PATCH_IF spell_name_ref > 0 BEGIN
				READ_STRREF SPL_unidentified_name name
			END
		END
	END
END
