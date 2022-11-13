/**
 * @file letter.h
 * Declaration of the Letter class.
 */

#pragma once

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
     */
    void addStudent();

    /**
     * Comparator for letters (to allow for sorting).
     * @param other A Letter to compare against
     * @return Whether the parameter is less than this Letter.
     */
    bool operator<(const Letter& other) const;
};
