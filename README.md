# Projet: Blockchain appliquée à un processus éléctoral

## Arborescence du projet

```c
projet
│
└───assets        // schemas/courbes
│
└───bin           // executables
│
└───blockchain    // fichiers de l'ex9 (bloc et pending_vote/block)
│
└───data          // fichiers de donnees generes ex1-8
│
└───obj           // .o
│
└───src
│   ├── partie_1  // ex1-2
│   └── partie_2  // ex3-4
│   ├── partie_3  // ex5-6
│   └── partie_4  // ex7-8
│   ├── partie_5  // ex9
│   └── params.h  // fichier de configuration general (nb de candidats/d'electeurs, borne des premiers generes, nb de tests...)
```

## Commande de base

```bash
sudo chmod +x run.sh
sudo chmod +x simulation.sh
# COMPILATION
make ex[num_exercice]
# EXECUTION
./run.sh [num_exercice]
# EXECUTION W/ VALGRIND
./run.sh -t [num_exercice]
# EXECUTION EX9 (clean des données et exec)
./simulation.sh
```

## Génération de courbe w/ gnuplot

```bash
plot "./data/comparaison_exponentiation.txt" using 1:2 title "modpow_naive" with lines
replot "./data/comparaison_exponentiation.txt" using 1:3 title "modpow" with lines
set term postscript portrait
set output "./data/comparaison_exponentiation.ps"
set size 0.7, 0.7
```

## Code d'erreur

- 12: Erreur d'allocation
- 13: Erreur argument
- 14: Appel de fonction avec paramètre invalide
- 15: Autres

## Description globale

[Diagramme Projet](./assets/Diagramme%20Projet.pdf)

## Fonctionnement du RSA

1. Le candidat met a disposition sa cle publique.
2. L'electeur chiffre la cle publique du candidat avec sa cle secrete (structure signature)
3. L'electeur fait sa declaration de vote contentant sa signature, sa cle publique et la cle publique du candidat (structure protected)
4. Pour verifier la declaration de vote on dechiffre la signature avec la cle publique de l'electeur et on compare la resultat avec la cle publique du candidat

<img src="./assets/RSA_schema.jpeg"/>

## Fonctionnement du système de vote centralisée

1. L'electeur est enregistre sur les liste electoral puis il vote (emmet une declaration)
2. On recupere tous les votes depuis un fichier (ici declarations.txt) et on extrait toutes les declarations que l'on stocke sous forme d'une liste chainee
3. On verifie la validite du vote, s'il n'est pas valide on supprime la declaration de la liste chainee
4. On cree une table de hachage associee aux candidats et une autre associee aux electeurs, pour chaque declaration on verifie que le candidat existe bien dans notre liste de candidats et on verifie egalement que l'electeur n'a pas deja vote, et enfin si tout est valide on comptabilise le vote
5. On fait le decompte general et on declare le vainqueur de l'election

<img src="./assets/Systeme_Centralise_Schema.jpg"/>

## Fonctionnement du système de vote décentralisée (blockchain)

1. L'electeur vote, sa declaration de vote est envoye sur le reseau (ici le reseau est represente pas l'ensemble des blocs, et les pending_blocks et pending_votes)
2. La declaration est mise en attente dans le fichier pending_votes. Lorsqu'un nombre suffisant de vote est atteint alors un assesseur va generer un bloc a partir de tous les votes en attentes
3. Le bloc va etre constitue d'une trace du dernier bloc auquel on fait confiance dans la blockchain, des declarations de votes ainsi que d'une preuve de travail. La preuve de travail est generee avec de la puissance de calcul en utilisant des outils cryptographique (ici c'est le hachage successif du bloc avec SHA-256 pour obtenir d 0 au debut).
4. Ensuite on verifie que la preuve de travail est conforme (verify_block dans le add_block) puis on ajoute le bloc a la blockchain
5. Une fois que la periode de vote est finis on recupere tous les blocs. On formera alors une arborescence a l'aide de ces derniers. On souhaite maintenant recupere les blocs valide c'est-a-dire les blocs faisant partie du plus long chemin de l'arborescence (le plus long chemin est celui qui a necessite le plus de calcul a cause des preuves de travail, on lui fait donc confiance, c'est la notion de consensus)
6. A partir de tous ces blocs on extrait toutes les declarations de vote et les mets dans une liste chaine puis comme pour le systeme centralisee on cree des tables de hachages, on verifie les votes et on declare le vainqueur
