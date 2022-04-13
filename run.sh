#!/bin/bash

if [ $# -lt 1 ]
then
  echo "run.sh: Préciser le numéro associé à l'exercice!"
  exit 2;
fi

path="./bin/ex$1.bin"

while getopts "t:" option;
do
  echo $option
  case $option in
    t)
      path="valgrind --track-origins=yes ./bin/ex$2.bin"
      ;;
    *)
      echo "Argument invalide: utiliser -t pour lancer le binaire avec valgrind"
      path="./bin/ex$1.bin"
      ;;
  esac

done

exec $path