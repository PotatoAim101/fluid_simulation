CC=g++
OUT=simulation
FLAGS=-g -c -WALL
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

OBJS=main.o matrix.o utils.o Fluid.o

all:$(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LDFLAGS)

main.o: main.cpp utils.o Fluid.o
	$(CC) -o main.o -c main.cpp $(LDFLAGS)

matrix.o: matrix.cpp matrix.h utils.h
	$(CC) -o matrix.o -c matrix.cpp $(LDFLAGS)

utils.o: utils.cpp utils.h matrix.h
	$(CC) -o utils.o -c utils.cpp $(LDFLAGS)

Fluid.o: Fluid.cpp Fluid.h utils.h
	$(CC) -o Fluid.o -c Fluid.cpp $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm $(OUT)
