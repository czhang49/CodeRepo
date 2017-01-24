#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "letter.h"
#include "room.h"
#include "allocator.h"

/**
 * Main routine.
 * Creates an Allocator object and allocates the students.
 */
int main()
{
    std::cout << std::endl;

    Allocator theAllocator("students.txt", "rooms.txt");
    theAllocator.allocate();
    theAllocator.printRooms();

    std::cout << std::endl;
    return 0;
}
