#!/bin/bash
if [ $# -ne 1 ]; then
  echo "run.sh: invalid argument"
  exit 1
fi

if [ "$1" == "1" ]; then
  cd ./partie_1/ex1/
  ./ex1.bin
  cd ../..
fi

if [ "$1" == "2" ]; then
  cd ./partie_1/ex2/
  ./ex2.bin
  cd ../..
fi

if [ "$1" == "3" ]; then
  cd ./partie_2/ex3/
  ./ex3.bin
  cd ../..
fi

if [ "$1" == "4" ]; then
  cd ./partie_2/ex4/
  ./ex4.bin
  cd ../..
fi
