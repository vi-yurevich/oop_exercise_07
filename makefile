CC=g++
CFLAGS=-std=c++14 -pedantic
OUTPUT=oop_exercise_07

all:
	$(CC) $(CFLAGS) Figure.h Figure.cpp main.cpp -o $(OUTPUT)
run:
	./$(OUTPUT)