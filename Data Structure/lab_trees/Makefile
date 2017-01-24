CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

OBJS = main.o coloredout.o
EXENAME = treefun

all : $(EXENAME)

$(EXENAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXENAME) $(OBJS)

main.o: src/main.cpp include/binary_tree.h include/binary_tree.tcc \
	include/binary_tree_given.tcc include/coloredout.h include/random.h
	$(CXX) $(CXXFLAGS) $<

coloredout.o: src/coloredout.cpp include/coloredout.h
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -f *.o $(EXENAME)

doc: $(wildcard include/*) $(wildcard src/*) lab_trees.doxygen
	doxygen lab_trees.doxygen

tidy: clean
	rm -rf ./doc
