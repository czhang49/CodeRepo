#
# Utilities Unleashed
# CS 241 Fall 2015
#

CC = clang-3.6
INC = -I.
FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11

all: time env

time: time.o
	$(CC) $^ -o $@

time.o: time.c
	$(CC) -c $(FLAGS) $(INC) $< -o $@

env: env.o
	$(CC) $^ -o $@

env.o: env.c
	$(CC) -c $(FLAGS) $(INC) $< -o $@

.PHONY : clean
clean:
	-rm -r -f *.o time env
