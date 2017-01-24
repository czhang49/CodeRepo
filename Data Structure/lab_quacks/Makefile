CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

OBJS = main.o exercises.o
EXE = quackfun

.PHONY: all clean tidy

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS)

main.o: src/main.cpp include/quackfun.h include/quackfun.tcc
	$(CXX) $(CXXFLAGS) $<

exercises.o: src/exercises.cpp include/exercises.h
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -f *.o $(EXE)

tidy: clean
	rm -rf ./doc
