CC = gcc
INC = -I.
FLAGS = -g -O2 -W -Wall
LINKOPTS = -lpthread

all: wearable_sim wearable_server

wearable_sim: wearable.o queue.o wearable_sim.c
	$(CC) $^ $(FLAGS) $(LINKOPTS) -o $@

wearable.o: wearable.c wearable.h
	$(CC) -o $@ $< -c $(FLAGS) $(LINKOPTS)

queue.o: queue.c queue.h
	$(CC) -o $@ $< -c $(FLAGS)

wearable_server: wearable_server.c queue.o
	$(CC) $^ $(FLAGS) $(LINKOPTS) -o $@

.PHONY : clean
clean:
	-rm -f *.o *.so *.rp wearable_sim wearable_server