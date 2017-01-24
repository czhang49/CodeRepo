CC = gcc
INC = -I.
FLAGS = -Wall -Wextra -Wno-unused -Wno-sign-compare -g -std=c99

all: basketcases camelCaser

basketcases: basketcases_tests.o basketcases.o basketcases_main.o
	$(CC) $^ -o $@

basketcases_tests.o: basketcases_tests.c basketcases.h basketcases_tests.h
	$(CC) -c $(INC) $(FLAGS) $< -o $@

basketcases.o: basketcases.c
	$(CC) -c $(INC) $(FLAGS) $< -o $@

basketcases_main.o: basketcases_main.c basketcases_tests.h basketcases.h
	$(CC) -c $(INC) $(FLAGS) $< -o $@

camelCaser: camelCaser_tests.o camelCaser.o camelCaser_main.o
	$(CC) $^ -o $@

camelCaser_tests.o: camelCaser_tests.c camelCaser.h camelCaser_tests.h
	$(CC) -c $(INC) $(FLAGS) $< -o $@

camelCaser.o: camelCaser.c
	$(CC) -c $(INC) $(FLAGS) $< -o $@

camelCaser_main.o: camelCaser_main.c camelCaser_tests.h camelCaser.h
	$(CC) -c $(INC) $(FLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f basketcases
	rm -f camelCaser
