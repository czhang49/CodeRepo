# Malloc
# CS 241 Fall 2015
# originally gcc
CC = gcc-5
INC = -I.
# originally -Werror at second last position and no -w flag
FLAGS += -O3 -Wextra -Wall -w -Wno-unused-parameter
TESTERS = $(patsubst %.c, %, $(wildcard testers/*))

all: alloc.so contest-alloc.so mreplace mcontest tester-agents

alloc.so: alloc.c
	$(CC) $^ $(FLAGS) -o $@ -shared -fPIC

contest-alloc.so: contest-alloc.c
	$(CC) $^ $(FLAGS) -o $@ -shared -fPIC -ldl

mreplace: mreplace.c
	$(CC) $^ $(FLAGS) -o $@

mcontest: mcontest.c contest.h
	$(CC) $^ $(FLAGS) -o $@ -ldl -lpthread

tester-agents: part1 part2

part1: part1/tester-1 part1/tester-2 part1/tester-3 part1/tester-4

#part2: $(subst testers, part2, $(TESTERS))
part2: part2/tester-1 part2/tester-2 part2/tester-3 part2/tester-4 part2/tester-5 part2/tester-6 part2/tester-7 part2/tester-8 part2/tester-9 part2/tester-10 part2/tester-11 

part1/%: testers/%.c
	@mkdir -p part1/
	$(CC) $^ $(FLAGS) -o $@

part2/%: testers/%.c
	@mkdir -p part2/
	$(CC) $^ $(FLAGS) -DPART2 -o $@

.PHONY : clean
clean:
	-rm -rf *.o *.so mreplace mcontest part1 part2
