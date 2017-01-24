CC=clang-3.6
INC=-Icore/
CFLAGS=-g -Wall -Wextra -Werror -std=c99 -D_GNU_SOURCE $(INC)
LDFLAGS=

VERSIONS=wordcount lettercount asciicount wordlengths
OBJECTS=libds.o common.o
EXES=mr0 mr1 mr2 shuffler splitter

MAPPERS_DIR=mappers
REDUCERS_DIR=reducers
CORE_DIR=core

all: $(OBJECTS) $(VERSIONS) $(EXES)

# data
.PHONY: data
data: data/alice.txt data/dracula.txt

data/alice.txt:
	curl "http://www.gutenberg.org/files/11/11.txt" > data/alice.txt

data/dracula.txt:
	curl "http://www.gutenberg.org/cache/epub/345/pg345.txt" > data/dracula.txt

# libs
libds.o: core/libds.c core/libds.h
	$(CC) -c $(CFLAGS) $< -o $@

common.o: $(CORE_DIR)/common.c $(CORE_DIR)/common.h
	$(CC) -c $(CFLAGS) $< -o $@

mapper.o: $(CORE_DIR)/mapper.c
	$(CC) -c $(CFLAGS) $^ -o $@

# core
reducer.o: $(CORE_DIR)/reducer.c
	$(CC) -c $(CFLAGS) $^ -o $@

shuffler: shuffler.c common.o
	$(CC) $(CFLAGS) $^ -o $@

splitter: $(CORE_DIR)/splitter.c
	$(CC) $(CFLAGS) $^ -o $@

mr0: mr0.c common.o
	$(CC) $(CFLAGS) $^ -o $@

mr1: mr1.c common.o
	$(CC) $(CFLAGS) $^ -o $@

mr2: mr2.c common.o
	$(CC) $(CFLAGS) $^ -o $@

# versions
.PHONY: wordcount
wordcount: mapper_wordcount reducer_sum

mapper_wordcount: mapper.o $(MAPPERS_DIR)/wordcount.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: lettercount
lettercount: mapper_lettercount reducer_sum

mapper_lettercount: mapper.o $(MAPPERS_DIR)/lettercount.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: asciicount
asciicount: mapper_asciicount reducer_sum

mapper_asciicount: mapper.o $(MAPPERS_DIR)/asciicount.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: wordlengths
wordlengths: mapper_wordlengths reducer_sum

mapper_wordlengths: mapper.o $(MAPPERS_DIR)/wordlengths.c
	$(CC) $(CFLAGS) $^ -o $@

# we don't need to keep defining this reducer over and over again
# we can just use the same one for lots of different problems
reducer_sum: libds.o reducer.o $(REDUCERS_DIR)/sum.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f reducer_* mapper_* *.o $(EXES)
