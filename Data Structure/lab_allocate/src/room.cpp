/**
 * @file room.cpp
 */

#include <utility>
#include <iostream>
#include "room.h"

Room::Room()
    : capacity(0), count(0), max_letters(26), letters(nullptr), letterCount(0)
{
}

Room::Room(const std::string& init_name, int init_capacity)
    : name(init_name),
      capacity(init_capacity),
      count(0),
      max_letters(26),
      letterCount(0)
{
    letters = new Letter[max_letters];
}

Room::Room(const Room& other)
{
    copy(other);
}

Room& Room::operator=(Room other)
{
    swap(other);
    return *this;
}

Room::~Room()
{
    clear();
}

void Room::addLetter(const Letter& L)
{
    letters[letterCount++] = L;
    count += L.count;
}

int Room::spaceRemaining()
{
    return capacity - count;
}

void Room::print()
{
    std::cout << name << " (" << count << "/" << capacity << "):";
    for (int L = 0; L < letterCount; L++)
        std::cout << " " << letters[L].letter;
    std::cout << std::endl;
}

void Room::clear()
{
    delete letters;
}

void Room::copy(const Room& other)
{
    name = other.name;
    capacity = other.capacity;
    count = other.count;
    letterCount = other.letterCount;
    letters = other.letters;
}

void Room::swap(Room& other)
{
    std::swap(name, other.name);
    std::swap(capacity, other.capacity);
    std::swap(count, other.count);
    std::swap(max_letters, other.max_letters);
    std::swap(letters, other.letters);
    std::swap(letterCount, other.letterCount);
}
