# AutoDescription

AutoDescription génère et remplace automatiquement la description "technique" des objets.  
Cela apporte plusieurs avantages:
- Les descriptions sont normalisées, ce qui les rend plus facile à lire
- La description s'adapte aux éventuelles modifications réalisées par les mods
- En comparant les descriptions avant/après, on peut détecter d'éventuels bugs.

## Todolist

### Général

- Grouper les effets ayant la même probabilité de se délencher (Ex: blun14) ?  
  Attention, 2 effets à 10% ne s'activeront pas forcément en mêem temps, il faut pour le cas qui nous intéresse, que probabilit1 et probability2 soient égaux dans les 2 effets !  
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
- Mieux grouper les entrées dans la section "(Non) Utilisable par"  
  - Si la classe de Mage n'est pas autoriseé ET que tous les kits de mage ne le sont pas non plus, juste laisser Mage ou préciser "Mage monoclassé et kittés" ?
  - Est-ce que le groupe d'une classe doit comporter les multi-classe où la classe en question n'est pas la base ?
  Ex: Le groupe "mage" doit-il comporter les multi-classs du genre "guerrier/mage" (mage/voleur oui, car mage est la base)
- Certains objets ont une description "non identifiée" mais aucune description "identifiée" (Ex: A!BCHAN1.ITM). Copier la version non identifiée dans la version identifiée et passer à la moulinette.
  Ceci n'est pas à faire pour les objets sans aucune description qui sont (normalement) des objets non accessibles au joueur.
- Gestion du timing "delayed" dans tous les types de capacités (Ex: CLCKK2.ITM, STAF17.itm, C2BLUN03) 
- Gérer les potions et les munitions
- Ignorer certains objets ou les traiter d'une manière spécifique ? (Ex: RING42.ITM S#SHLD01)
- Bug: loyal transformé en neutre (Ex: WANDORC.ITM)
- Bug: si la classe mage pure est (non) utilisable par, "monoclassé" n'est pas ajouté à la fin
- Bug: usability (Ex: BHCLUB01)
  > Utilisable par : 
  > - Voleur monoclassé et multiclassé
  > - Voleur
- opcode_target_probability_166: gérer le timing "permanent"
- Piège à sorts, pouvoir récupérer le nombre de niveaux maximum qu peuvent être piégés pour l'ajouter dans le nom de la capacité, plutot que d'avoir la liste de chaque niveau de sort. (Ex: PXL7087.ITM)
- Gérer le timing "permanent", il affichera "de manière permanente" ou "définitivement" à la fin de la phrase, mais pas systématiquement. (les conditions restent à définir) (ex: L#NI6CQ)
  Exemple à éviter: 21 % de chance d'infliger 2 points de dégâts de froid supplémentaires de manière permanente
- Meilleure gestion des targetType "target". Si targetType du extended header est "self" et que l'effet qu'il actionne est target "target", ça doit rester un self ? (CLCKK2.ITM : 116)
- Gérer les opcodes suivants : 101, 144, 177, 180, 188, 232, 248, 249, 251, 268, 272, 300, 318
- Opcode 177  
  Grouper si l'effet est le même ! (Ex: U#BLUN01). L'objet possède 4 opcode 177 ayant le même effet, selon une condition sur la cible.
  Gérer les dés de vie ! Certains effets ne s'applique que si la cible a un certain niveau de dé de vie (Ex: SW1H64)
- Améliorer le tri des effets en faisant en sorte que, pour un même opcode, ceux ayant 100% soient avant ceux < 100 (Ex: RR#TROL)

  > - Si la cible est un humain, un gnome, un nain ou une petite-personne :
  >  -  Endort la cible (jet de sauvegarde contre les sorts à +4 pour annuler)
- Opcode 1  
  Améliorer les textes, mieux adapté aux situations et moins génériques.
- Opcode 67
  Gérer l'hostilité de la créature invoquée
- Opcode 101 (Ex: BLUN25, immunité au drain de niveau)
- Les opcodes de type "State: Sanctuary [153]" doivent avoir un texte différent en fonction de s'ils sont une capacité de charge, de combat ou d'équipement... (Ex: GTT#BO.ITM)  
  Charge : Sanctuaire x fois par jour  
  Combat : Sanctuaire sur le porteur  
  Equipement : "Sanctuaire permanent", "Sous l'effet de Sanctuaire", "Sanctuaire", autres ?
- Opcode 206 (resref tb#preti) + opcode 146 (resref tb#depet)
  // Fusionner en une seule ligne ! // Immunité au sort Pétrification
- "Revient dans les mains du lanceur immédiatement après avoir été lancée" (Ex: AX1H10)
- Grouper les charmes (Ex: A7RING02)
  

### Capacités de combat

- Préciser la cible de l'effet, uniquement si la cible est le porteur.
  La cible par défaut de l'effet d'une capacité de combat est la cible du personnage, il n'est pas nécessaire de toujours le mentionner, et cela diminuera un peu les lignes.
- Si une résistance de la cible passe à 0 avec une capacité de combat, écrire "Ignore la résistance à xxx de la cible" à la place de "Résistance à xxx de la cible: Passe à 0"

### Capacités de charge

- Trouver un nom qui ne soit pas générique pour les capacités de charge qui ont plusieurs effets affichés et qui n'ont aucun tooltip
  - D'abord regarder en jeu ce qui est inscrit lorsqu'on passe la souris sur ce genre d'effet, et voir comment il serait possible de récupérer cette chaîne.
  - Si rien n'est inscrit, ou juste le nom de l'objet : créer un tooltip pour l'objet (travail au cas par cas) ?
- Afficher la portée des capacités de charge ?