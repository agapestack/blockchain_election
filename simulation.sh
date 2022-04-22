#!/bin/bash
make mrproper
make
# valgrind --leak-check=full ./bin/ex9.bin 
./run.sh -t 9