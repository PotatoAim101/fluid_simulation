CC=g++
OUT=simulation
FLAGS=-g -c -WALL
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

OBJS=main.o Matrix.o utils.o Particle.o Fluid.o

all:$(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LDFLAGS)

main.o: main.cpp utils.o Fluid.o
	$(CC) -o main.o -c main.cpp $(LDFLAGS)

Matrix.o: Matrix.cpp Matrix.h utils.h
	$(CC) -o Matrix.o -c Matrix.cpp $(LDFLAGS)

utils.o: utils.cpp utils.h Matrix.h
	$(CC) -o utils.o -c utils.cpp $(LDFLAGS)

Fluid.o: Fluid.cpp Fluid.h utils.h
	$(CC) -o Fluid.o -c Fluid.cpp $(LDFLAGS)

Particle.o: Particle.cpp Particle.h utils.h
	$(CC) -o Particle.o -c Particle.cpp $(LDFLAGS)

clean:
	rm -rf *.o
