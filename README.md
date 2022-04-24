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
