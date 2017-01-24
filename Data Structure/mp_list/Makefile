CXX = clang++-3.5
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O1 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpng

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

EXENAME = mp_list_test

OBJECTS = epng.o rgba_pixel.o blockpng.o main.o

.PHONY: all clean tidy doc

all: $(EXENAME)

$(EXENAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

epng.o : src/epng.cpp include/epng.h include/rgba_pixel.h
	$(CXX) $(CXXFLAGS) $<

rgba_pixel.o : src/rgba_pixel.cpp include/rgba_pixel.h
	$(CXX) $(CXXFLAGS) $<

blockpng.o : src/blockpng.cpp include/blockpng.h include/epng.h include/rgba_pixel.h
	$(CXX) $(CXXFLAGS) $<

main.o : src/main.cpp include/epng.h include/rgba_pixel.h include/blockpng.h include/dl_list.h include/dl_list.tcc
	$(CXX) $(CXXFLAGS) $<

clean: tidy
	-rm -f *.o $(EXENAME)

tidy:
	-rm -rf ./doc merge.png reverseNth_01.png reverseNth_02.png reverse.png split_01.png split_02.png split_03.png unshuffled_1.png unshuffled_60.png waterfall_01.png waterfall_02.png

doc: $(wildcard include/* src/*)
	-rm -rf ./doc
	doxygen mp_list.doxygen
