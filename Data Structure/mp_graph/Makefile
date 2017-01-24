CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpng

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

TEST_DSETS = testdsets
TEST_DSETS_OBJS = dsets.o testdsets.o

DEMO = graphdemo
DEMO_OBJS = vertex.o edge.o demo.o

GRAPH_TESTS = testgraph
GRAPH_TESTS_OBJS = vertex.o edge.o dsets.o tests.o

TEST_MAZE = testmaze
TEST_MAZE_OBJS = vertex.o edge.o dsets.o maze.o testmaze.o epng.o rgba_pixel.o

IDENT_HEADERS = include/util/identifiers.h include/util/comparable.h
GRAPH_HEADERS = include/vertex.h include/edge.h include/graph.h \
				include/graph.tcc include/tools.h include/tools.tcc \
				include/tools_provided.h include/tools_provided.tcc \
				$(wildcard include/features/*) $(IDENT_HEADERS)
EPNG_HEADERS = include/epng.h include/rgba_pixel.h

.PHONY: clean tidy all

all: $(DEMO) $(GRAPH_TESTS) $(TEST_DSETS) $(TEST_MAZE)

$(TEST_DSETS): $(TEST_DSETS_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(DEMO): $(DEMO_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(GRAPH_TESTS): $(GRAPH_TESTS_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(TEST_MAZE): $(TEST_MAZE_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

vertex.o: src/vertex.cpp include/vertex.h $(IDENT_HEADERS)
	$(CXX) $(CXXFLAGS) $<

edge.o: src/edge.cpp include/edge.h include/vertex.h $(IDENT_HEADERS)
	$(CXX) $(CXXFLAGS) $<

demo.o: src/demo.cpp
	$(CXX) $(CXXFLAGS) $<

tests.o: src/tests.cpp $(GRAPH_HEADERS)
	$(CXX) $(CXXFLAGS) $<

dsets.o: src/dsets.cpp include/dsets.h
	$(CXX) $(CXXFLAGS) $<

maze.o: src/maze.cpp include/maze.h include/dsets.h $(GRAPH_HEADERS) \
		$(EPNG_HEADERS)
	$(CXX) $(CXXFLAGS) $<

epng.o : src/epng.cpp $(EPNG_HEADERS)
	$(CXX) $(CXXFLAGS) src/epng.cpp

rgba_pixel.o : src/rgba_pixel.cpp include/rgba_pixel.h
	$(CXX) $(CXXFLAGS) src/rgba_pixel.cpp

testdsets.o: src/testdsets.cpp include/dsets.h
	$(CXX) $(CXXFLAGS) $<

testmaze.o: src/testmaze.cpp include/maze.h $(GRAPH_HEADERS) $(EPNG_HEADERS)
	$(CXX) $(CXXFLAGS) $<

doc: mp_graphs.doxygen $(GRAPH_HEADERS) $(wildcard include/*) $(wildcard src/*)
	doxygen $<

clean: tidy
	-rm -rf *.o $(DEMO) $(GRAPH_TESTS) $(TEST_DSETS) $(TEST_MAZE)

tidy:
	-rm -rf doc
	-rm -rf images/*.png
