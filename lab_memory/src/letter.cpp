/**
 * @file letter.cpp
 * Implementation of the Letter class.
 */

#include "letter.h"

Letter::Letter() : letter('-'), count(0)
{
}

void Letter::addStudent()
{
    count++;
}

bool Letter::operator<(const Letter& other) const
{
    return count > other.count;
}
