CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpng

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

EPNG_HEADERS = include/epng.h include/rgba_pixel.h
DRAWABLE_HEADERS = include/color.h include/vector2.h include/drawable.h $(EPNG_HEADERS)
SHAPE_HEADERS = include/shape.h $(DRAWABLE_HEADERS)
CONCRETE_SHAPE_HEADERS = include/circle.h include/rectangle.h include/triangle.h

SHAPE_OBJS = epng.o line.o rgba_pixel.o shape.o vector2.o

EXECUTABLES = lab_inheritance test_virtual test_destructor test_constructor test_slicing test_pure_virtual


.PHONY: all clean tidy

all: $(EXECUTABLES)

circle.o : src/circle.cpp include/circle.h $(SHAPE_HEADERS)
	$(CXX) $(CXXFLAGS) src/circle.cpp

epng.o : src/epng.cpp include/epng.h include/rgba_pixel.h
	$(CXX) $(CXXFLAGS) src/epng.cpp

flower.o : src/flower.cpp include/flower.h $(SHAPE_HEADERS) $(CONCRETE_SHAPE_HEADERS)
	$(CXX) $(CXXFLAGS) src/flower.cpp

line.o : src/line.cpp include/line.h $(DRAWABLE_HEADERS)
	$(CXX) $(CXXFLAGS) src/line.cpp

main.o : src/main.cpp $(SHAPE_HEADERS) include/rectangle.h
	$(CXX) $(CXXFLAGS) src/main.cpp

rectangle.o : src/rectangle.cpp include/rectangle.h $(SHAPE_HEADERS)
	$(CXX) $(CXXFLAGS) src/rectangle.cpp

rgba_pixel.o : src/rgba_pixel.cpp include/rgba_pixel.h
	$(CXX) $(CXXFLAGS) src/rgba_pixel.cpp

shape.o : src/shape.cpp $(SHAPE_HEADERS)
	$(CXX) $(CXXFLAGS) src/shape.cpp

test_constructor.o : src/test_constructor.cpp  $(SHAPE_HEADERS) include/circle.h
	$(CXX) $(CXXFLAGS) src/test_constructor.cpp

test_destructor.o : src/test_destructor.cpp $(SHAPE_HEADERS) include/triangle.h
	$(CXX) $(CXXFLAGS) src/test_destructor.cpp

test_pure_virtual.o : src/test_pure_virtual.cpp $(SHAPE_HEADERS) include/circle.h include/rectangle.h include/truck.h
	$(CXX) $(CXXFLAGS) src/test_pure_virtual.cpp

test_slicing.o : src/test_slicing.cpp $(SHAPE_HEADERS) include/flower.h
	$(CXX) $(CXXFLAGS) src/test_slicing.cpp

test_virtual.o : src/test_virtual.cpp $(SHAPE_HEADERS) include/rectangle.h
	$(CXX) $(CXXFLAGS) $<

triangle.o : src/triangle.cpp include/triangle.h $(SHAPE_HEADERS)
	$(CXX) $(CXXFLAGS) src/triangle.cpp

truck.o : src/truck.cpp include/truck.h $(SHAPE_HEADERS) include/circle.h include/rectangle.h
	$(CXX) $(CXXFLAGS) src/truck.cpp

vector2.o : src/vector2.cpp include/vector2.h
	$(CXX) $(CXXFLAGS) src/vector2.cpp

lab_inheritance : main.o $(SHAPE_OBJS) rectangle.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_virtual : test_virtual.o $(SHAPE_OBJS) rectangle.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_destructor : test_destructor.o $(SHAPE_OBJS) triangle.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_constructor : test_constructor.o $(SHAPE_OBJS) circle.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_pure_virtual : test_pure_virtual.o $(SHAPE_OBJS) circle.o rectangle.o truck.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_slicing : test_slicing.o $(SHAPE_OBJS) circle.o flower.o rectangle.o triangle.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	-rm -f *.o $(EXECUTABLES)

tidy: clean
	-rm -rf ./doc

doc: $(wildcard include/* src/*)
	-rm -rf ./doc
	doxygen lab_allocate.doxygen
