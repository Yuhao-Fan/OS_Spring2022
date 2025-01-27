OBJS	= main.o Linker.o Token.o
SOURCE	= main.cpp Linker.cpp Token.cpp
HEADER	= Linker.h Memory.h Symbol.h Token.h
OUT	= linker
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

Linker.o: Linker.cpp
	$(CC) $(FLAGS) Linker.cpp -std=c++11

Token.o: Token.cpp
	$(CC) $(FLAGS) Token.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)