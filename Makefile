CC=gcc
CFLAGS=-lssl -lcrypto

BIN=./bin
OBJ=./obj

EX1=./src/partie_1/ex1
EX2=./src/partie_1/ex2
EX3=./src/partie_2/ex3
EX4=./src/partie_2/ex4
EX4=./src/partie_2/ex4
EX5=./src/partie_3/ex5
EX6=./src/partie_3/ex6
EX7=./src/partie_4/ex7
EX8=./src/partie_4/ex8
EX9=./src/partie_5/ex9

all: ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9

# Pas très propre pour les .o --> à améliorer si possible

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

ex7: $(EX7)/ex7.c $(OBJ)/block.o $(OBJ)/hash.o $(OBJ)/linked_list.o $(OBJ)/keys_struct.o $(OBJ)/keys.o $(OBJ)/miller_rabin.o $(OBJ)/keys.o
	gcc $^ -o $(BIN)/ex7.bin $(CFLAGS)

ex8: $(EX8)/ex8.c $(OBJ)/tree.o $(OBJ)/block.o $(OBJ)/hash.o $(OBJ)/linked_list.o $(OBJ)/keys_struct.o $(OBJ)/keys.o $(OBJ)/miller_rabin.o $(OBJ)/keys.o
	gcc $^ -o $(BIN)/ex8.bin $(CFLAGS)

ex9: $(EX9)/ex9.c $(OBJ)/vote.o $(OBJ)/tree.o $(OBJ)/block.o $(OBJ)/hash.o $(OBJ)/linked_list.o $(OBJ)/keys_struct.o $(OBJ)/keys.o $(OBJ)/miller_rabin.o $(OBJ)/keys.o
	gcc $^ -o $(BIN)/ex8.bin $(CFLAGS)

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

$(OBJ)/block.o: $(EX7)/block.c
	gcc -c $^ -o $@

$(OBJ)/tree.o: $(EX8)/tree.c
	gcc -c $^ -o $@

$(OBJ)/vote.o: $(EX9)/vote.c
	gcc -c $^ -o $@

clean:
	rm ./obj/*.o

mrproper: clean
	rm ./data/*
	rm ./bin/*

