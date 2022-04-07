CC=gcc
CFLAG=-Wall

BIN=./bin
OBJ=./obj

EX1=./src/partie_1/ex1
EX2=./src/partie_1/ex2
EX3=./src/partie_2/ex3
EX4=./src/partie_2/ex4
EX4=./src/partie_2/ex4
EX5=./src/partie_3/ex5
EX6=./src/partie_3/ex6

all: ex1 ex2 ex3 ex4 ex5 ex6

ex1: $(EX1)/ex1.c $(OBJ)/miller_rabin.o
	gcc $^ -o $(BIN)/ex1.bin

ex2: $(EX2)/ex2.c $(OBJ)/keys.o $(OBJ)/miller_rabin.o
	gcc $^ -o $(BIN)/ex2.bin

ex3: $(EX3)/ex3.c $(OBJ)/keys_struct.o $(OBJ)/keys.o $(OBJ)/miller_rabin.o $(OBJ)/keys.o
	gcc $^ -o $(BIN)/ex3.bin

ex4: $(EX4)/ex4.c $(OBJ)/keys_struct.o $(OBJ)/keys.o $(OBJ)/miller_rabin.o $(OBJ)/keys.o
	gcc $^ -o $(BIN)/ex4.bin

ex5: $(EX5)/ex5.c $(OBJ)/linked_list.o $(OBJ)/keys_struct.o $(OBJ)/keys.o $(OBJ)/miller_rabin.o $(OBJ)/keys.o
	gcc $^ -o $(BIN)/ex5.bin

ex6: $(EX6)/ex6.c	$(OBJ)/hash.o $(OBJ)/linked_list.o $(OBJ)/keys_struct.o $(OBJ)/keys.o $(OBJ)/miller_rabin.o $(OBJ)/keys.o
	gcc $^ -o $(BIN)/ex6.bin

$(OBJ)/miller_rabin.o: $(EX1)/miller_rabin.c
	gcc -c $^ -o $@

$(OBJ)/keys.o: $(EX2)/keys.c
	gcc -c $^ -o $@

$(OBJ)/keys_struct.o: $(EX3)/keys_struct.c
	gcc -c $^ -o $@

$(OBJ)/linked_list.o: $(EX5)/linked_list.c
	gcc -c $^ -o $@

$(OBJ)/hash.o: $(EX6)/hash.c
	gcc -c $^ -o $@

clean:
	rm ./obj/*.o

mrproper: clean
	rm ./data/*
	rm ./bin/*

