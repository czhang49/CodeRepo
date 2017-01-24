CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -g -O0 -c -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpng

.PHONY: all clean tidy

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

EXE = mp_qtree
OBJS = epng.o rgba_pixel.o quadtree.o quadtree_given.o main.o

EPNG_HEADERS = include/epng.h include/rgba_pixel.h

all: $(EXE)

epng.o: src/epng.cpp include/epng.h include/rgba_pixel.h
	$(CXX) $(CXXFLAGS) $<

rgba_pixel.o: src/rgba_pixel.cpp include/rgba_pixel.h
	$(CXX) $(CXXFLAGS) $<

quadtree_given.o: src/quadtree_given.cpp include/quadtree.h $(EPNG_HEADERS)
	$(CXX) $(CXXFLAGS) $<

quadtree.o: src/quadtree.cpp include/quadtree.h $(EPNG_HEADERS)
	$(CXX) $(CXXFLAGS) $<

main.o: src/main.cpp include/quadtree.h $(EPNG_HEADERS)
	$(CXX) $(CXXFLAGS) $<

mp_qtree: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	-rm -f *.o $(EXE) mp_qtree.out out*.png

doc: $(wildcard include/*) $(wildcard src/*) mp_qtree.doxygen
	doxygen mp_qtree.doxygen

tidy:
	-rm -rf ./doc
