CC=gcc
CFLAG=-Wall
LIBS=-lm

EX1=./partie_1/ex1
EX2=./partie_1/ex2
EX3=./partie_2/ex3
EX4=./partie_2/ex4

all: ex1 ex2 ex3 

ex1: $(EX1)/ex1.c $(EX1)/exponentiation.c $(EX1)/miller_rabin.c
	$(CC) $^ $(LIBS) -o $(EX1)/ex1.bin

ex2: $(EX2)/ex2.c $(EX2)/keys.c $(EX1)/exponentiation.c $(EX1)/miller_rabin.c
	$(CC) $^ $(LIBS) -o $(EX2)/ex2.bin

ex3: $(EX3)/ex3.c $(EX3)/keys_struct.c $(EX1)/exponentiation.c $(EX1)/miller_rabin.c $(EX2)/keys.c
	$(CC) $^ $(LIBS) -o $(EX3)/ex3.bin

ex4: $(EX4)/ex4.c $(EX3)/keys_struct.c $(EX1)/exponentiation.c $(EX1)/miller_rabin.c $(EX2)/keys.c
	$(CC) $^ $(LIBS) -o $(EX4)/ex4.bin

clean:
	find . -name "*.o" -type f -delete

mrproper: clean
	find . -name "*.bin" -type f -delete
	find . -name "a.out" -type f -delete
	rm ./data/*.txt

