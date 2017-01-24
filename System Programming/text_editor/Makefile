#
# Text Editor Lab
# CS 241 Fall 2015
#

CC = clang-3.6
INC = -I.
FLAGS = -Wall -Wextra -Werror -Wno-unused -Wno-sign-compare -g -std=c11 

all: editor

editor: editor.o
	$(CC) $^ -o $@ -lm

editor.o: editor.c editor.h
	$(CC) -c $(FLAGS) $(INC) $< -o $@ 

.PHONY : clean
clean:
	-rm -r -f *.o editor
