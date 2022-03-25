#!/bin/bash
if [ $# -ne 1 ]; then
  echo "run.sh: invalid argument"
  exit 1
fi

if [ "$1" == "1" ]; then
  cd ./partie_1/ex1/
  valgrind ./ex1.bin
  cd ../..
fi

if [ "$1" == "2" ]; then
  cd ./partie_1/ex2/
  valgrind ./ex2.bin
  cd ../..
fi

if [ "$1" == "3" ]; then
  cd ./partie_2/ex3/
  valgrind ./ex3.bin
  cd ../..
fi

if [ "$1" == "4" ]; then
  cd ./partie_2/ex4/
  valgrind ./ex4.bin
  cd ../..
fi

if [ "$1" == "5" ]; then
  cd ./partie_3/ex5/
  valgrind ./ex5.bin
  cd ../..
fi


if [ "$1" == "6" ]; then
  cd ./partie_3/ex6/
  valgrind ./ex6.bin
  cd ../..
fi