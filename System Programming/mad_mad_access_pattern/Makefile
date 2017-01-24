EXECS=lookup1 lookup2
CC=clang-3.6 -g -std=c99 -Wall


all: $(EXECS)

lookup1: lookup1.c
	$(CC) $^ $(LIBS) -o $@

lookup2: lookup2.c
	$(CC) $^ $(LIBS) -o $@

# This where the data in large.data came from:
# http://norvig.com/ngrams/count_1w.txt
large.data:
	svn export https://subversion.ews.illinois.edu/svn/fa15-cs241/_shared/random_files/mmap_seek/large.data

clean:
	rm -f $(EXECS) *.o *~
