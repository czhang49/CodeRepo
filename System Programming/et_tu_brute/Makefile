#
# Pipes
# CS 241 Fall 2015
#

CC = clang-3.6
INC = -I.
FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c99

brutus: brutus.o cipher.o
	$(CC) $^ -o $@

brutus.o: brutus.c cipher.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@

.PHONY : clean
clean:
	-rm -r -f brutus brutus.o
