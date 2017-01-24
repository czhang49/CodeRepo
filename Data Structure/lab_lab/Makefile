# Lines that start with a # are comments
#
# Here we define variables that we can use later.
# When variables are used we must wrap them with $()
OBJS = main.o epng.o rgba_pixel.o
EXENAME = remove

CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

.PHONY: all clean

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : src/main.cpp epng.o rgba_pixel.o
	$(CXX) $(CXXFLAGS) src/main.cpp

rgba_pixel.o: include/rgba_pixel.h src/rgba_pixel.cpp
	$(CXX) $(CXXFLAGS) src/rgba_pixel.cpp

epng.o : src/epng.cpp include/epng.h include/rgba_pixel.h
	$(CXX) $(CXXFLAGS) src/epng.cpp

clean :
	rm -f *.o $(EXENAME) 2>/dev/null
