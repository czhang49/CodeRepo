# Parmake
# CS 241 Fall 2015
# University of Illinois at Urbana-Champaign
CC=gcc
CFLAGS=-O0 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-sign-compare -g -std=c99 -pthread
THREAD_SANITIZER=-fsanitize=thread -DSANITIZE_THREADS -fPIC -pie -ltsan

all: parmake parmake-tsan

parmake: parmake.o queue.o parser.o rule.o
	$(CC) $(CFLAGS) parmake.o queue.o parser.o rule.o -o parmake

parmake-tsan: parmake.c queue.c parser.c rule.c
	@if ldconfig -p | grep libtsan.so.0 > /dev/null ; then echo "tsan installed"; else echo "install tsan"; sudo yum install -y libtsan; fi
	$(CC) $(CFLAGS) $(THREAD_SANITIZER) $^ -o $@

parmake.o: parmake.c
	$(CC) $(CFLAGS) -c parmake.c -o parmake.o

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c -o queue.o

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c -o parser.o

rule.o: rule.c rule.h
	$(CC) $(CFLAGS) -c rule.c -o rule.o

trial: trial.o
	$(CC) $(CFLAGS) trial.o -o trial

trial.o: trial.c
	$(CC) $(CFLAGS) -c trial.c -o trial.o
clean:
	rm -rf *.o parmake parmake-tsan
