# use gcc with -fsanitize=thread bc clang on student vms (3.4) has buggy thread
# sanitizer
# this means we also need -ltsan in the link step. libtsan must be installed
# (sudo yum install libtsan on student vms)
EXECS=cracker0 cracker1 cracker2 create_examples timing
EXECS+=cracker1-tsan cracker2-tsan
THREAD_SANITIZER=-fsanitize=thread -DSANITIZE_THREADS -fPIC -pie -ltsan
CFLAGS=-g -Wall -Wextra -Wno-unused-parameter -pthread -std=c99
# CC=clang $(CFLAGS)
CC=gcc $(CFLAGS)
LIBS=-lcrypt -lrt

all: $(EXECS)

cracker0: cracker0.o common.o thread_status.o
	$(CC) $^ $(LIBS) -o $@

cracker1: cracker1_main.c cracker1.o common.o thread_status.o
	$(CC) $^ $(LIBS) -o $@

cracker2: cracker2_main.c cracker2.o common.o thread_status.o
	$(CC) $^ $(LIBS) -o $@

cracker1-tsan: cracker1_main.c cracker1.c common.c thread_status.c
	$(CC) $(THREAD_SANITIZER) $^ $(LIBS) -o $@

cracker2-tsan: cracker2_main.c cracker2.c common.c thread_status.c
	$(CC) $(THREAD_SANITIZER) $^ $(LIBS) -o $@

timing: timing.o common.o
	$(CC) $^ $(LIBS) -o $@

create_examples: create_examples.o
	$(CC) $^ $(LIBS) -o $@

common.o: common.c common.h

%.o: %.c
	$(CC) -c $<

clean:
	rm -f *.o $(EXECS) *~
