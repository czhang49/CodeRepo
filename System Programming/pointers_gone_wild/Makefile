#
# Machine Problem #0
# CS 241 Fall 2015
#

CC = clang-3.5
INC = -I.
FLAGS = -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -g -std=c99

all: part1 part2

part1: part1-main.o part1-functions.o
	$(CC) $^ -o $@

part2: part2-main.o part2-functions.o
	$(CC) $^ -o $@

part1-functions.o: part1-functions.c part1-functions.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@

part1-main.o: part1-main.c
	$(CC) -c $(FLAGS) $(INC) $< -o $@

part2-functions.o: part2-functions.c part2-functions.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@

part2-main.o: part2-main.c
	$(CC) -c $(FLAGS) $(INC) $< -o $@

.PHONY : clean
clean:
	-rm -r -f *.o part1 part2
