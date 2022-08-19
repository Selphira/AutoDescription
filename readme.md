[![Github Releases](https://img.shields.io/github/v/release/Selphira/AutoDescription?include_prereleases&color=blue)](https://github.com/Selphira/AutoDescription/releases/latest)
![Langues](https://img.shields.io/static/v1?label=Langues&message=Français&color=limegreen)
![Jeux supportés](https://img.shields.io/static/v1?label=Jeux%20supportés&message=BG2%20%7C%20BGT%20%7C%20BGEE%20%7C%20BG2EE%20%7C%20EET&color=dodgerblue)

# AutoDescription

AutoDescription est un mod, pour BG2, BGT, BGEE, BG2EE et EET, développé sur <a href="https://www.baldursgateworld.fr/lacouronne/la-correct-zone/33168-uniformisation-des-descriptions.html">La Couronne de Cuivre</a>, qui génère et remplace automatiquement la description "technique" des objets.  

Cela comporte plusieurs avantages:
- Les descriptions sont normalisées, ce qui les rend plus facile à lire
- La description s'adapte aux éventuelles modifications réalisées par les mods et les harmonise avec le reste du jeu
- En comparant les descriptions avant/après, on peut détecter d'éventuels bugs, erreurs ou incompatibilités entre mods 
  et sur le jeu de base.
- Si des mods non-traduits sont installés, les statistiques des objets de ces mods seront automatiquement traduites et 
  harmonisées.

À l'origine, ce mod a été pensé pour être utilisé par les joueurs, en étant installé après tous les mods ajoutant ou 
altérant des objets.  
En effet, AutoDescription s'adapte à tous les mods installés par l'utilisateur, si les capacités de certains objets sont
altérées, celles-ci seront mises à jour afin que leur description corresponde à la réalité et dans votre langue 
d'origine.

En pratique, il s'avère que AutoDescription peut aussi être utilisé dans le développement de mods, à divers niveaux...

Côté traducteurs, il permet de traduire automatiquement les statistiques contenues dans les descriptions de la plupart 
des objets, évitant ainsi une tâche souvent pénible et redondante.

Côté développeurs, il peut mettre en évidence certains problèmes, incohérences ou bugs dans les objets en traduisant les 
effets avec fiabilité.
A cet effet, quelques erreurs sont remontées dans un fichier de log.
Le mod n'étant pas destiné à cela à la base, la liste des erreurs remontées par ce biais est encore faible, mais elle 
s'étoffera au fil du temps.

## Comment ça fonctionne ?

AutoDescription va lire toutes les caractéristiques des objets et des effets qui leurs sont associés afin de
les traduire sous la forme d'un texte. Créant de ce fait, une ligne de description pour chaque effet présent sur l'objet.  
Si certains de ces effets sont d'une même categorie, ils seront regroupés en une seule ligne dans le but de réduire la 
longueur des descriptions.  
Cette description "technique" va alors remplacer celle présente dans la description originale, tout en conservant la 
partie texte "RP" de l'objet.

Pendant la phase de développement, aucun fichier du jeu n'est altéré, mais le mod va générer un fichier présentant les 
différences avant / après ; afin de comparer les descriptions originales des nouvelles descriptions générées par 
Autodescription.
Il produira aussi deux fichiers de log permettant de remonter certaines erreurs ou alertes, pour les opcodes pas encore 
integrés ou érronés.
	
Il est dors et déjà possible de remplacer les descriptions du jeu, en activant une option dans le fichier 
"settings-default.ini".
Ce fichier "settings-default.ini" contient d'autres options pour essayer de s'adapter à certaines préférences des joueurs.

Un composant supplémentaire (20), plutot destiné aux développeurs et traducteurs, permet de générer uniquement les 
descriptions des objets d'un mod en particulier, facilitant ainsi la verification d'objets spécifiques.

## Personnalisation

Plusieurs options sont disponibles dans le fichier "settings-default.ini" pour s'adapter à certaines préférérences des joueurs.    
Pour modifier une option, il est conseillé de ne pas modifier le fichier "settings-default.ini", mais de le copier dans un fichier "settings.ini" sau même endroit.
Libre à vous ensuite de modifier les options sans crainte de perdre votre configuration suite à une mise à jour du mod.

## Et la suite ?

Le mod est encore en développement et n'est pour l'instant disponible qu'en Français, si des traducteurs désirent 
entreprendre sa traduction, ce sera avec plaisir que je l'ajouterais au mod.
Il est aussi prévu de prendre en compte les munitions, les potions, et peut-être les sortilèges !

## Remerciements

Un grand merci à toutes ces personnes pour leur aide dans l'amélioration du mod !

- [JohnBob](https://www.baldursgateworld.fr/lacouronne/members/johnbob.html)
- [Deratiseur](https://www.baldursgateworld.fr/lacouronne/members/deratiseur.html)