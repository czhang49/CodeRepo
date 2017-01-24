CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

LC_TEST = charcount
LC_OBJS = hashes.o primes.o textfile.o charcount.o

ANAGRAM_TEST = anagramtest
ANAGRAM_OBJS = hashes.o primes.o textfile.o anagramtest.o

WC_TEST = wordcount
WC_OBJS = hashes.o primes.o textfile.o wordcount.o

LP_HASH = include/hashes.h include/lp_hash_table.tcc include/lp_iterator.tcc\
		  include/lp_hash_table.h include/lp_iterator.h

SC_HASH = include/hashes.h include/sc_hash_table.tcc include/sc_iterator.tcc\
		  include/sc_hash_table.h include/sc_iterator.h

GENLOG = genlog

PARSER = lfparse
PARSE_OBJS = logfile_parser.o lfparse.o hashes.o primes.o

all: $(LC_TEST) $(ANAGRAM_TEST) $(WC_TEST) $(GENLOG) $(PARSER)

$(LC_TEST) : $(LC_OBJS)
	$(CXX) $(LDFLAGS) -o $(LC_TEST) $(LC_OBJS)

$(WC_TEST) : $(WC_OBJS)
	$(CXX) $(LDFLAGS) -o $(WC_TEST) $(WC_OBJS)

$(ANAGRAM_TEST) : $(ANAGRAM_OBJS)
	$(CXX) $(LDFLAGS) -o $(ANAGRAM_TEST) $(ANAGRAM_OBJS)

$(GENLOG) : src/logfile_generator.cpp
	$(CXX) $(CXXFLAGS) -o $(GENLOG) src/logfile_generator.cpp

$(PARSER) : $(PARSE_OBJS)
	$(CXX) $(LDFLAGS) -o $(PARSER) $(PARSE_OBJS)

anagramtest.o : src/anagramtest.cpp include/anagram_finder.h \
				include/anagram_finder.tcc $(LP_HASH) $(SC_HASH)
	$(CXX) $(CXXFLAGS) src/anagramtest.cpp

charcount.o : src/charcount.cpp include/char_counter.h include/textfile.h \
			  include/char_counter.h include/char_counter.tcc $(LP_HASH)\
			  $(SC_HASH)
	$(CXX) $(CXXFLAGS) src/charcount.cpp

wordcount.o : src/wordcount.cpp include/word_counter.h src/word_counter.cpp \
			  include/textfile.h $(LP_HASH) $(SC_HASH)
	$(CXX) $(CXXFLAGS) src/wordcount.cpp

textfile.o : include/textfile.h src/textfile.cpp
	$(CXX) $(CXXFLAGS) src/textfile.cpp

lfparse.o : src/lfparse.cpp include/logfile_parser.h
	$(CXX) $(CXXFLAGS) src/lfparse.cpp

logfile_parser.o : $(LP_HASH) $(SC_HASH) include/logfile_parser.h \
				   src/logfile_parser.cpp
	$(CXX) $(CXXFLAGS) src/logfile_parser.cpp

hashes.o : include/hashes.h src/hashes.cpp
	$(CXX) $(CXXFLAGS) src/hashes.cpp

primes.o : include/primes.h src/primes.cpp
	$(CXX) $(CXXFLAGS) src/primes.cpp

doc: $(wildcard include/*) $(wildcard src/*)
	-doxygen lab_hash.doxygen

clean:
	-rm -rf doc *.o $(LC_TEST) $(LC_TEST).exe $(ANAGRAM_TEST) $(ANAGRAM_TEST).exe $(WC_TEST) $(WC_TEST).exe $(GENLOG) $(GENLOG).exe $(PARSER) $(PARSER).exe

tidy:
	-rm -f anagrams.txt
