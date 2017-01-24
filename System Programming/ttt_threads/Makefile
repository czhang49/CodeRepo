CC = gcc
INC = -I.
FLAGS = -W -Wall -g -std=c99 -Wno-unused-variable -Wno-unused-parameter
LINKOPTS = -pthread
SOURCE = queue.c

all: rende testqueue

testqueue: queue.c   testqueue.c 
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) queue.c testqueue.c -o runtestqueue
	./runtestqueue 1
	./runtestqueue 2
	./runtestqueue 3
	./runtestqueue 4
	./runtestqueue 5

testqueue1: queue.c   testqueue.c 
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) queue.c testqueue.c -o runtestqueue
	./runtestqueue 1

testqueue2: queue.c   testqueue.c 
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) queue.c testqueue.c -o runtestqueue
	./runtestqueue 2

testqueue3: queue.c   testqueue.c 
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) queue.c testqueue.c -o runtestqueue
	./runtestqueue 3

testqueue4: queue.c   testqueue.c 
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) queue.c testqueue.c -o runtestqueue
	./runtestqueue 4

testqueue5: queue.c   testqueue.c 
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) queue.c testqueue.c -o runtestqueue
	./runtestqueue 5

rende: rendezvous.c
	gcc -Wall -pthread rendezvous.c -o testrendezvous

semamore: semamore.c rendezvous.c
	gcc -Wall -pthread semamore.c rendezvous.c -o testsemamore
clean:
	rm -rf runtestqueue testrendezvous testsemamore 
