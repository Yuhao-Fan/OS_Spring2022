OBJS	= main.o Simulator.o
SOURCE	= main.cpp Simulator.cpp
HEADER	= Simulator.h Process.h VMA.h Pagers/Pager.h Pagers/FIFO.h Frame.h Pagers/Random.h Pagers/Aging.h Pagers/Clock.h Pagers/NRU.h Pagers/WorkingSet.h
OUT	= mmu
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

Simulator.o: Simulator.cpp
	$(CC) $(FLAGS) Simulator.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)