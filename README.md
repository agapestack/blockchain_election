# Projet: Blockchain appliquée à un processus éléctoral

## Note aux correcteurs

> De nombreuses options peuvent être facilement changer depuis le fichier params.h

```bash
sudo chmod +x run.sh
# make ex[numero de l'exercice] pour compiler 
make ex1
# ./run.sh [numero de l'exercice]     LANCEMENT
./run.sh 1
# ./run.sh -t [numero de l'exercice]  LANCEMENT AVEC VALGRIND
./run.sh -t 1
```

## Rappel utilisation gnuplot

```bash
plot "./data/comparaison_exponentiation.txt" using 1:2 title "modpow_naive" with lines
replot "./data/comparaison_exponentiation.txt" using 1:3 title "modpow" with lines
set term postscript portrait
set output "./data/comparaison_exponentiation.ps"
set size 0.7, 0.7
```

## Error code

- 12: Erreur d'allocation
- 13: Erreur argument
- 14: Appel de fonction avec paramètre invalide
- 15: Autres

## TODOS

- [x] fuite ex6
- [ ] verfier fonction ex7 (surtout serialisation, et representation binaire)
- [ ] Test compute winner de l'ex 6
- [ ] generer des jeux de tests
- [ ] rapport

### Memory Leak

- [x] memory leak ex1
- [x] memory leak ex2
- [x] memory leak ex3
- [x] memory leak ex4
- [x] memory leak ex5
- [x] memory leak ex6
- [ ] memory leak ex7

### Presentations
