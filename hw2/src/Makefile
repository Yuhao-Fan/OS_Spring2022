OBJS	= main.o Process.o Scheduler.o Event.o DES_Layer.o Simulator.o Schedulers/FIFO_Scheduler.o Schedulers/LCFS_Scheduler.o Schedulers/RR_Scheduler.o Schedulers/SRTF_Scheduler.o Schedulers/PRIO_Scheduler.o Schedulers/PREPRIO_Scheduler.o
SOURCE	= main.cpp Process.cpp Scheduler.cpp Event.cpp DES_Layer.cpp Simulator.cpp Schedulers/FIFO_Scheduler.cpp Schedulers/LCFS_Scheduler.cpp Schedulers/RR_Scheduler.cpp Schedulers/SRTF_Scheduler.cpp Schedulers/PRIO_Scheduler.cpp Schedulers/PREPRIO_Scheduler.cpp
HEADER	= Process.h Scheduler.h Event.h DES_Layer.h Simulator.h Schedulers/FIFO_Scheduler.h Schedulers/LCFS_Scheduler.h Schedulers/RR_Scheduler.h Schedulers/SRTF_Scheduler.h Schedulers/PRIO_Scheduler.h Schedulers/PREPRIO_Scheduler.h
SRC_DIR = $/Schedulers
OUT	= sched
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

Process.o: Process.cpp
	$(CC) $(FLAGS) Process.cpp -std=c++11

Scheduler.o: Scheduler.cpp
	$(CC) $(FLAGS) Scheduler.cpp -std=c++11

Event.o: Event.cpp
	$(CC) $(FLAGS) Event.cpp -std=c++11

DES_Layer.o: DES_Layer.cpp
	$(CC) $(FLAGS) DES_Layer.cpp -std=c++11

Simulator.o: Simulator.cpp
	$(CC) $(FLAGS) Simulator.cpp -std=c++11

Schedulers/FIFO_Scheduler.o: Schedulers/FIFO_Scheduler.cpp
	$(CC) $(FLAGS) -o $@ Schedulers/FIFO_Scheduler.cpp -std=c++11

Schedulers/LCFS_Scheduler.o: Schedulers/LCFS_Scheduler.cpp
	$(CC) $(FLAGS) -o $@ Schedulers/LCFS_Scheduler.cpp -std=c++11

Schedulers/RR_Scheduler.o: Schedulers/RR_Scheduler.cpp
	$(CC) $(FLAGS) -o $@ Schedulers/RR_Scheduler.cpp -std=c++11

Schedulers/SRTF_Scheduler.o: Schedulers/SRTF_Scheduler.cpp
	$(CC) $(FLAGS) -o $@ Schedulers/SRTF_Scheduler.cpp -std=c++11

Schedulers/PRIO_Scheduler.o: Schedulers/PRIO_Scheduler.cpp
	$(CC) $(FLAGS) -o $@ Schedulers/PRIO_Scheduler.cpp -std=c++11

Schedulers/PREPRIO_Scheduler.o: Schedulers/PREPRIO_Scheduler.cpp
	$(CC) $(FLAGS) -o $@ Schedulers/PREPRIO_Scheduler.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)