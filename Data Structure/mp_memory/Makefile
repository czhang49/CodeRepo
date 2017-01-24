CXX := clang++
CXXFLAGS := -Iinclude -std=c++1y -stdlib=libc++ -g -O0 -c -Wall -Wextra
LDFLAGS := -stdlib=libc++ -lc++abi -lpng

.PHONY: all tidy clean

EXES = scoped_ptr_test scoped_array_test collage_test

EPNG_HEADERS = include/epng.h include/rgba_pixel.h
SPTR_HEADERS = include/scoped_ptr.h include/scoped_ptr.tcc
SARR_HEADERS = include/scoped_array.h include/scoped_array.tcc
SCOPED_HEADERS = $(SPTR_HEADERS) $(SARR_HEADERS)

all: $(EXES)

scoped_ptr_test.o : $(SPTR_HEADERS) src/scoped_ptr_test.cpp
	$(CXX) $(CXXFLAGS) src/scoped_ptr_test.cpp

scoped_ptr_test : scoped_ptr_test.o
	$(CXX) $(LDFLAGS) scoped_ptr_test.o -o scoped_ptr_test

scoped_array_test.o : $(SARR_HEADERS) src/scoped_array_test.cpp
	$(CXX) $(CXXFLAGS) src/scoped_array_test.cpp

scoped_array_test : scoped_array_test.o
	$(CXX) $(LDFLAGS) scoped_array_test.o -o scoped_array_test

rgba_pixel.o : include/rgba_pixel.h src/rgba_pixel.cpp
	$(CXX) $(CXXFLAGS) src/rgba_pixel.cpp

epng.o : include/epng.h src/epng.cpp
	$(CXX) $(CXXFLAGS) src/epng.cpp

collage.o : $(EPNG_HEADERS) $(SCOPED_HEADERS) include/collage.h src/collage.cpp
	$(CXX) $(CXXFLAGS) src/collage.cpp

collage_test.o : $(EPNG_HEADERS) $(SCOPED_HEADERS) include/collage.h src/collage_test.cpp
	$(CXX) $(CXXFLAGS) src/collage_test.cpp

collage_test : collage_test.o collage.o epng.o rgba_pixel.o
	$(CXX) $(LDFLAGS) collage_test.o collage.o epng.o rgba_pixel.o -o collage_test

tidy:
	rm -rf scene*.png

clean: tidy
	rm -rf *.o $(EXES)
