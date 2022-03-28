# Projet: Blockchain appliquée à un processus éléctoral

## Note aux correcteurs

```bash
sudo chmod +x test.sh
sudo chmod +x run.sh
# make ex[numero de l'exercice] pour compiler 
make ex1
# ./run.sh [numero de l'exercice]
./run.sh 1
```

## Rappel utilisation gnuplot

```bash
plot "comparaison_exponentiation.txt" using 1:2 title "modpow_naive" with lines
replot "comparaison_exponentiation.txt" using 1:3 title "modpow" with lines
set term postscript portrait
set output "comparaison_exponentiation.ps"
set size 0.7, 0.7
```

## Error code

- 12: Erreur d'allocation
- 13: Erreur argument
- 14: Appel de fonction avec paramètre invalide

## TODOS

### Memory Leak

- [x] memory leak ex1
- [x] memory leak ex2
- [x] memory leak ex3
- [x] memory leak ex4
- [x] memory leak ex5
- [ ] memory leak ex6

### Presentations
