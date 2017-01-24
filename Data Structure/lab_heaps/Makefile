CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

OBJS = testheap.o coloredout.o
EXENAME = testheap

.PHONY: clean tidy

$(EXENAME) : $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

testheap.o: src/testheap.cpp include/heap.h include/heap.tcc \
	include/printheap.tcc include/printtree.h include/random.h
	$(CXX) $(CXXFLAGS) $<

coloredout.o: src/coloredout.cpp include/coloredout.h
	$(CXX) $(CXXFLAGS) $<

doc: lab_heaps.doxygen $(wildcard include/*) $(wildcard src/*)
	doxygen $<

clean: tidy
	-rm -rf *.o $(EXENAME)

tidy:
	-rm -rf doc
