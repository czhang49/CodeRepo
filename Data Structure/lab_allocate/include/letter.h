/**
 * @file letter.h
 */

#ifndef LETTER_H
#define LETTER_H

#include <string>

/**
 * Represents a group of students with the same first letter of their last
 * name.
 */
class Letter
{
  public:
    /** The character this Letter represents */
    char letter;

    /** How many students have been allocated for this letter. */
    int count;

    /**
     * Letter constructor. Initializes the letter to '-' with 0 students
     * The letter should be set by the client.
     */
    Letter();

    /**
     * Adds one additional student to the letter group.
     * @param name
     */
    void addStudent(const std::string& name);
};

/**
 * Comparator for letters (to allow for sorting).
 * @param lhs The letter
 * @param rhs A Letter to compare against
 * @return Whether the parameter rhs is less than lhs
 */
bool operator<(const Letter& lhs, const Letter& rhs);

#endif
