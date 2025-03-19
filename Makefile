CC=g++
SRCPATH=./src/
LIB=-lsfml-graphics -lsfml-window -lsfml-system -lpthread -lpng -lstdc++fs -std=c++17
SRC=$(wildcard $(SRCPATH)*.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=main

all: $(EXEC)

main: $(OBJ)
	$(CC) main.cpp -o $(EXEC) $(notdir $^) $(LIB)
	rm *.o

%.o: %.cpp
	$(CC) -c $<
