SRC = src
INCLUDE = include
FLAGS = -ggdb

OBJ = main.o PointTransformations.o

a: $(OBJ)
	gcc $(OBJ) -o a $(FLAGS) -lSDL2

main.o: $(SRC)/main.c
	gcc -c $(SRC)/main.c $(FLAGS) -lSDL2

PointTransformations.o: $(SRC)/PointTransformations.c
	gcc -c $(SRC)/PointTransformations.c $(FLAGS) -lSDL2
