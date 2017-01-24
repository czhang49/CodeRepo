CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

OBJECTS = main.o letter.o room.o allocator.o fileio.o room_list.o student_list.o

allocate: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o allocate

main.o: src/main.cpp include/allocator.h include/letter.h include/room.h include/fileio.h
	$(CXX) $(CXXFLAGS) src/main.cpp

letter.o: include/letter.h src/letter.cpp
	$(CXX) $(CXXFLAGS) src/letter.cpp

room.o: include/room.h src/room.cpp include/letter.h
	$(CXX) $(CXXFLAGS) src/room.cpp

allocator.o: include/allocator.h src/allocator.cpp include/room.h include/letter.h include/fileio.h
	$(CXX) $(CXXFLAGS) src/allocator.cpp

fileio.o: include/fileio.h src/fileio.cpp include/room.h
	$(CXX) $(CXXFLAGS) src/fileio.cpp

room_list.o: include/fileio.h include/room_list.h include/room.h src/room_list.cpp
	$(CXX) $(CXXFLAGS) src/room_list.cpp

student_list.o: include/fileio.h include/student_list.h src/student_list.cpp
	$(CXX) $(CXXFLAGS) src/student_list.cpp

clean:
	-rm -f *.o allocate

tidy: clean
	-rm -rf ./doc

doc: $(wildcard include/* src/*)
	-rm -rf ./doc
	doxygen lab_allocate.doxygen
