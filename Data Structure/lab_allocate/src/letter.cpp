/**
 * @file letter.cpp
 */

#include "letter.h"

Letter::Letter() : letter('-'), count(0)
{
}

void Letter::addStudent(const std::string&)
{
    count++;
}

bool operator<(const Letter& lhs, const Letter& rhs)
{
    return lhs.count > rhs.count;
}
