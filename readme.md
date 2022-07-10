# AutoDescription

AutoDescription génère et remplace automatiquement la description "technique" des objets.  
Cela apporte plusieurs avantages:
- Les descriptions sont normalisées, ce qui les rend plus facile à lire
- La description s'adapte aux éventuelles modifications réalisées par les mods
- En comparant les descriptions avant/après, on peut détecter d'éventuels bugs.

## Todolist

### Général

- les points de vie maximum -> le maximum de points de vie
- Grouper les effets ayant la même probabilité de se délencher (Ex: blun14) ?  
  Attention, 2 effets à 10% ne s'activeront pas forcément en même temps, il faut pour le cas qui nous intéresse, que probabilit1 et probability2 soient égaux dans les 2 effets !  
  Il y a risque d'y avoir des chaînes trop longues...  Mais il faut trouver une façon d'indiquer au joueur que plusieurs effets vont se déclencher en même temps !
- Grouper les effets de dégâts (opcode 12) dans une section "Dagâts" qui contiendrait aussi les dégâts de l'arme ?
  Ex:
  > Capacités de combat :
  > - Dégâts: +6 points de dégâts de feu supplémentaires
  > - 21 % de chance d'infliger 2 points de dégâts de froid supplémentaires de manière permanente
  > 
  > Dégâts: 1d6 +3
  
  Deviendrait
  
  > Dégâts: 
  > - 1d6 +3
  > - +6 points de dégâts de feu supplémentaires
  > - 21 % de chance d'infliger 2 points de dégâts de froid supplémentaires de manière permanente
- Modifier la gestion des modifications par pourcentage d'une valeur ?  
  Actuellement, on affiche "Multiplié par xx%"
  Changer en "+/- xx%" ?
- Gérer les potions et les munitions
- Ignorer certains objets ou les traiter d'une manière spécifique ? (Ex: RING42.ITM S#SHLD01 SHLD24 U#AMUL02)
- Bug: usability (Ex: NPSW05)
  "Utilisable" par et "Non utilisable par" affichés en même temps
- Piège à sorts, pouvoir récupérer le nombre de niveaux maximum qu peuvent être piégés pour l'ajouter dans le nom de la capacité, plutot que d'avoir la liste de chaque niveau de sort. (Ex: PXL7087.ITM)
- Meilleure gestion des targetType "target". Si targetType du extended header est "self" et que l'effet qu'il actionne est target "target", ça doit rester un self ? (CLCKK2.ITM : 116)
- Gérer les opcodes suivants : 180, 248, 251, 268, 272, 300
- Opcode 177  
  Grouper si l'effet est le même ! (Ex: U#BLUN01). L'objet possède 4 opcode 177 ayant le même effet, selon une condition sur la cible.
  Gérer les dés de vie ! Certains effets ne s'applique que si la cible a un certain niveau de dé de vie (Ex: SW1H64)
- Opcode 1  
  Améliorer les textes, mieux adapté aux situations et moins génériques.
- Les opcodes de type "State: Sanctuary [153]" doivent avoir un texte différent en fonction de s'ils sont une capacité de charge, de combat ou d'équipement... (Ex: GTT#BO.ITM)  
  Charge : Sanctuaire x fois par jour  
  Combat : Sanctuaire sur le porteur  
  Equipement : "Sanctuaire permanent", "Sous l'effet de Sanctuaire", "Sanctuaire", autres ?
- Opcode 206 (resref tb#preti) + opcode 146 (resref tb#depet)
  // Fusionner en une seule ligne ! // Immunité au sort Pétrification
- Grouper les charmes (Ex: A7RING02)
- Les effets de zone ?
  

### Capacités de combat

- Préciser la cible de l'effet, uniquement si la cible est le porteur.
  La cible par défaut de l'effet d'une capacité de combat est la cible du personnage, il n'est pas nécessaire de toujours le mentionner, et cela diminuera un peu les lignes.
- Si une résistance de la cible passe à 0 avec une capacité de combat, écrire "Ignore la résistance à xxx de la cible" à la place de "Résistance à xxx de la cible: Passe à 0"

### Capacités de charge

- Trouver un nom qui ne soit pas générique pour les capacités de charge qui ont plusieurs effets affichés et qui n'ont aucun tooltip
  - D'abord regarder en jeu ce qui est inscrit lorsqu'on passe la souris sur ce genre d'effet, et voir comment il serait possible de récupérer cette chaîne.
  - Si rien n'est inscrit, ou juste le nom de l'objet : créer un tooltip pour l'objet (travail au cas par cas) ?
- Afficher la portée des capacités de charge ?

### Objets à corriger

Une liste d'objets sur lesquels je suis tombée et qui ont un bug évident.
Ces objets seront corrigés dans un composant optionnel qui devra s'exécuter avant le composant principal.

#### Capacités d'équipement : 
- **AMASWD.ITM** (??) : Possède un opcode 189 avec 1% de chance, non présent dans la description
- **BHCLUB01.ITM** (Secret of Bonehill) : Multiplicateur d'attaque sournoise +50 (vive les dégâts x 57 pour l'assassin :D)! Devrait être x 150% selon la description.
- **C-CS.ITM** (??) : Le opcode 30 a 1% de chance de multiplier la résistance en feu de 60%, au lieu d'augmenter la résistance au feu de 60 %.
- **C2STAF02.ITM** (Item Upgrade) : Possède des bonus aux jets de sauvegarde non décrits
- **JKVAHL.ITM** (Tsujatha) : Probabilité de l'effet de modification d'alignement pas à 100% 
- **LOTHARMO.ITM** (??) : Le bonus de chance est de +2 dans la description, mais +3 et avec une mauvaise probabilité dans le code
- **NAMUL.ITM** (??) : Un des 2 opcode 173 à 1% de chance, et il devrait être supprimé
- **RING42.ITM** (??) : 3 opcodes (292, et 2 206) ont une probabilité de 1% au lieu de 100%

#### Capacités de charge : 
- **J#JANSHU.ITM** (??) : Le second opcode 135 pointe vers une ressource vide ! (à supprimer)