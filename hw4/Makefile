OBJS	= main.o Simulator.o
SOURCE	= main.cpp Simulator.cpp
HEADER	= DiskScheduling/Scheduler.h DiskScheduling/FIFO.h DiskScheduling/SSTF.h Simulator.h DiskScheduling/LOOK.h DiskScheduling/CLOOK.h DiskScheduling/FLOOK.h Request.h
OUT	= iosched
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