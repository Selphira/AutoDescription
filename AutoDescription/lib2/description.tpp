DEFINE_ACTION_MACRO ~update_descriptions~ BEGIN
	LAM ~update_item_descriptions~
	//LAM ~update_spell_descriptions~
END

DEFINE_ACTION_MACRO ~update_item_descriptions~ BEGIN
	COPY_EXISTING_REGEXP GLOB ~SW2H19.itm$~ ~override~
		LPF ~update_item_description~ END
	BUT_ONLY_IF_IT_CHANGES
END

DEFINE_ACTION_MACRO ~update_spell_descriptions~ BEGIN
	COPY_EXISTING_REGEXP GLOB ~^.+\.spl$~ ~override~
		LPF ~update_spell_description~ END
	BUT_ONLY_IF_IT_CHANGES
END


DEFINE_PATCH_FUNCTION ~add_section_to_description~
	INT_VAR
		count = 0
	STR_VAR
		title = ~~
		arrayName = ~~
	RET
		description
BEGIN
	PATCH_IF count > 0 BEGIN
        SORT_ARRAY_INDICES ~%arrayName%~ NUMERICALLY
		LPF ~appendSection~ STR_VAR string = ~%title%~ RET description END

        //TODO: Regrouper les éléments ayant la même probabilité: Nécessite une seconde boucle

	    PATCH_PHP_EACH ~%arrayName%~ AS data => value BEGIN
			LPF ~appendProperty~ STR_VAR name = EVAL ~%data_5%~ RET description END
	    END
	END
END