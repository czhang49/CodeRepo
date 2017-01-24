#
# Shell
# CS 241 Fall 2015
#

CC = clang-3.6
INC = -I.
FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11

all: vector_test log_test wtsh

vector_test: vector.o vector_test.o
	$(CC) $^ -o $@ -lm

vector.o: vector.c vector.h
	$(CC) -c $(FLAGS) $(INC) $< -o  $@ 

vector_test.o: vector_test.c vector.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ 

log_test: vector.o log.o log_test.o -lm
	$(CC) $^ -o $@

log.o: log.c log.h vector.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@

log_test.o: log_test.c vector.h log.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@

wtsh: shell.o log.o vector.o
	$(CC) $^ -o $@ -lm

shell.o: shell.c vector.h log.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@

.PHONY : clean
clean:
	-rm -r -f *.o vector_test log_test wtsh
