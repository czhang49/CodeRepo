#
# Mini Valgrind
# CS 241 Fall 2015
#

CC = clang-3.6
INC = -I.
FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11

all: memtest

memtest: test.o mini_valgrind.o
	$(CC) -o memtest test.o mini_valgrind.o

test.o: test.c
	$(CC) $(FLAGS) -c test.c

mini_valgrind.o: mini_valgrind.c mini_valgrind.h
	$(CC) $(FLAGS) -c mini_valgrind.c

clean:
	-rm -r -f *.o memtest
