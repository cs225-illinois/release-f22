/**
 * @file main.cpp
 * A simple program that allocates students to rooms.
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "fileio.h"
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

    fileio::init();
    Allocator theAllocator("../students.txt", "../rooms.txt");
    theAllocator.allocate();
    theAllocator.printRooms();
    fileio::halt();

    std::cout << std::endl;
    return 0;
}
