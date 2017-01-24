#
# Barrier Lab
# CS 241 Fall 2015
#

CC = clang-3.6
INC = -I.
FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c99
LINKOPTS = -pthread

all: barrier_test dance_eat_sleep

dance_eat_sleep: dance_eat_sleep.c barrier.o
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) -D _BSD_SOURCE $^ -o $@

barrier_test: barrier_test.c barrier.o
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) -D _BSD_SOURCE $^ -o $@

barrier.o: barrier.c barrier.h
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) -c $<

clean:
	-rm -r -f *.o dance_eat_sleep barrier_test
