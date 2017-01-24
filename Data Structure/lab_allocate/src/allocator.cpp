/**
 * @file allocator.cpp
 * @author Jack Toole, updated by Sean Massung to add doxygen comments
 * @date Fall 2011
 */

#include <iostream>

#include "allocator.h"
#include "fileio.h"
#include "room_list.h"
#include "student_list.h"

Allocator::Allocator(const std::string& studentFile, const std::string& roomFile)
{
    createLetterGroups();
    loadStudents(studentFile);
    loadRooms(roomFile);
}

Allocator::Allocator(const Allocator& other)
    : roomCount{other.roomCount},
      studentCount{other.studentCount},
      totalCapacity{other.totalCapacity}
{
    createLetterGroups();
    rooms = new Room[roomCount];
    for (int i = 0; i < roomCount; ++i)
        rooms[i] = other.rooms[i];
}

Allocator::~Allocator()
{
	clear();

}

void Allocator::clear()
{
	delete[] alpha;
	delete[] rooms;

}

Allocator& Allocator::operator=(Allocator rhs)
{
    swap(rhs);
    return *this;
}


void Allocator::createLetterGroups()
{
    // Make letters (A - Z lettergroups)
    alpha = new Letter[26];
    for (int i = 0; i < 26; i++)
        alpha[i].letter = 'A' + i;
}

void Allocator::loadStudents(const std::string& file)
{
    // Read in students
    fileio::student_list list{file};
    studentCount = list.size(); // UNTESTED local var

    for (int i = 0; i < studentCount; i++)
    {
        auto name = list.next();
        char letter = name[0];
        int index = (int)letter - 'A';
        alpha[index].addStudent(name);
    }
}

void Allocator::loadRooms(const std::string& file)
{
    // Read in rooms
    fileio::room_list list{file};
    roomCount=list.size();
    rooms = new Room[roomCount];

    totalCapacity = 0;
    int i = 0;
    while (list.has_next())
    {
        rooms[i] = list.next();
        totalCapacity += rooms[i].capacity;
        i++;
     }
}

void Allocator::printStudents()
{
    // Output number of each last letter name
    std::cout << "Student counts (" << studentCount << " total)" << std::endl;
    for (int i = 0; i < 26; i++)
        std::cout << alpha[i].letter << ": " << alpha[i].count << std::endl;
}

void Allocator::allocate()
{
    // Perform the allocation
    int border = solve();

    // Check for an error
    if (border < 0)
    {
        std::cerr << std::endl << "Cannot allocate all students." << std::endl << std::endl;
        exit(-1);
    }
}

void Allocator::printRooms()
{
    // Output the allocation
    std::cout << "Room Allocation (" << studentCount << "/" << totalCapacity << ")"
         << std::endl;
    for (int i = 0; i < roomCount; i++)
        rooms[i].print();
}

void Allocator::swap(Allocator& other)
{
    std::swap(alpha, other.alpha);
    std::swap(rooms, other.rooms);
    std::swap(roomCount, other.roomCount);
    std::swap(studentCount, other.studentCount);
    std::swap(totalCapacity, other.totalCapacity);
}

int Allocator::solve()
{
    std::stable_sort(alpha, alpha + 26);

    for (int L = 0; L < 26; L++)
    {
        Room* r = largestOpening();
        r->addLetter(alpha[L]);
    }

    return minSpaceRemaining();
}

int Allocator::minSpaceRemaining()
{
    int border = 1000000;
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].spaceRemaining() < border)
            border = rooms[i].spaceRemaining();
    return border;
}

Room* Allocator::largestOpening()
{
    int index = 0;
    int max_remaining = 0;
    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].spaceRemaining() > max_remaining)
        {
            index = i;
            max_remaining = rooms[i].spaceRemaining();
        }
    }
    return &rooms[index];
}
