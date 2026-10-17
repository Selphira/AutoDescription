[![Github Releases](https://img.shields.io/github/v/release/Selphira/AutoDescription?include_prereleases&color=blue)](https://github.com/Selphira/AutoDescription/releases/latest)
![Langues](https://img.shields.io/static/v1?label=Langues&message=Français%20%7C%20English&color=limegreen)
![Jeux supportés](https://img.shields.io/static/v1?label=Jeux%20supportés&message=BG2%20%7C%20BGT%20%7C%20BGEE%20%7C%20BG2EE%20%7C%20EET&color=dodgerblue)
![GitHub Downloads (all assets, latest release)](https://img.shields.io/github/downloads/Selphira/AutoDescription/total)
![GitHub Downloads (all assets, latest release)](https://img.shields.io/github/downloads/Selphira/AutoDescription/latest/total)

# AutoDescription

AutoDescription est un mod pour **BG2, BGT, BGEE, BG2EE et EET**, développé sur 
[La Couronne de Cuivre](https://www.baldursgateworld.fr/lacouronne/la-correct-zone/33168-uniformisation-des-descriptions.html), 
qui génère et remplace automatiquement la description "technique" des objets et des sortilèges.  

## Avantages

- Les descriptions sont **normalisées**, ce qui les rend plus faciles à lire.
- La description s'adapte aux éventuelles **modifications réalisées par d'autres mods** et les harmonise avec le reste du jeu.
- En comparant les descriptions avant/après, on peut détecter d'éventuels **bugs, erreurs ou incompatibilités** entre mods et avec le jeu de base.
- Si des mods **non traduits** sont installés, les statistiques de leurs objets seront automatiquement **traduites et harmonisées**.

À l'origine, ce mod était pensé pour être installé **par les joueurs**, après tous les mods ajoutant ou altérant des objets.  
En effet, AutoDescription s'adapte à tous les contenus déjà présents : si les capacités de certains objets sont modifiées, elles seront mises à jour dans la description technique, et ce dans la langue d'origine du joueur.  

En pratique, AutoDescription s'avère aussi utile pour le **développement de mods**, à plusieurs niveaux :

- **Traducteurs** : il permet d'automatiser la traduction des statistiques contenues dans la majorité des descriptions d'objets, évitant une tâche fastidieuse et répétitive.  
- **Développeurs** : il peut mettre en évidence certains problèmes, incohérences ou bugs dans les objets, en traduisant et harmonisant les effets.  
  Des erreurs et avertissements sont également consignés dans un fichier de log.

## Comment ça fonctionne ?

AutoDescription analyse toutes les **caractéristiques des objets** et les effets associés, pour les **traduire sous forme textuelle**.  
Chaque effet génère une ligne de description ; les effets similaires sont regroupés afin de réduire la longueur de la description.  

La description "technique" générée remplace celle de l'objet, tout en conservant sa partie **roleplay** (texte narratif).  

Le mod génère aussi :
- Un fichier comparant les descriptions **originales** et celles **générées par AutoDescription** ([voir la version interactive en ligne](https://selphira.github.io/AutoDescription/)).
- Deux fichiers de **log** pour signaler certaines erreurs ou opcodes encore non intégrés.

Un fichier `settings-default.ini` contient une série d'options pour personnaliser le comportement.  

Des composants supplémentaires `(20 et 25)`, plutôt destinés aux **développeurs et traducteurs**, permettent de générer uniquement les descriptions des objets et sortilèges d'un mod particulier, afin de vérifier rapidement un contenu spécifique.

## Personnalisation

Les options sont définies dans `settings-default.ini`.  

⚠️ Pour conserver vos préférences lors des mises à jour, **ne modifiez pas directement ce fichier** :  
- Copiez-le sous le nom `settings.ini` au même emplacement.  
- Modifiez vos options dans `settings.ini`.  

## Et la suite ?

Le mod est encore en développement.  
Il est disponible en **français** et en **anglais (bêta)**. mais si des traducteurs souhaitent entreprendre d'autres traductions, elles seront intégrées avec plaisir.  

## Remerciements

Un grand merci à toutes les personnes qui ont contribué, de près ou de loin, à l'amélioration d'AutoDescription !

- [JohnBob](https://www.baldursgateworld.fr/memberlist.php?mode=viewprofile&u=16284)
- [rivvers](https://www.baldursgateworld.fr/memberlist.php?mode=viewprofile&u=12905)
- [Deratiseur](https://www.baldursgateworld.fr/memberlist.php?mode=viewprofile&u=8352)