#
# Overworked Interns
# CS 241 Fall 2015
#

CC = clang-3.6
INC = -I.
FLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c99

all: good_companies bad_companies

good_companies: good_companies.o main.o
	$(CC) -pthread $^ -o $@

good_companies.o: good_company.c
	$(CC) -c $(FLAGS) $(INC) $< -o $@

bad_companies: bad_companies.o main.o
	$(CC) -pthread $^ -o $@

bad_companies.o: bad_company.c
	$(CC) -c $(FLAGS) $(INC) $< -o $@

main.o: main.c
	$(CC) -c $(FLAGS) $(INC) $< -o $@

.PHONY : clean
clean:
	-rm -r -f *.o good_companies bad_companies
