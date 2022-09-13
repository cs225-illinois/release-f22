/**
 * @file fileio.h
 * Declaration of the fileio utility functions.
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include "room.h"

/**
 * Utility functions for reading students/rooms from files.
 * @note There are NO bugs in fileio
 */
namespace fileio
{
    /** Stores config name options if necessary */
    typedef std::map<std::string, std::vector<std::string>> FileMap;

    /**
     * Sets up the students and rooms variables as empty vectors.
     */
    void init();

    /**
     * Acts as a destructor for the fileio reader.
     */
    void halt();

    /**
     * Reads the student file into the students vector.
     * @param file The student file
     */
    void loadStudents(const std::string& file);

    /**
     * Reads the rooms file into the rooms vector.
     * @param file The room file
     */
    void loadRooms(const std::string& file);

    /**
     * @return The amount of students read from the students file.
     */
    int getNumStudents();

    /**
     * @return The number of rooms read from the rooms file.
     */
    int getNumRooms();

    /**
     * @return Whether there are more students to read from the
     *  students vector.
     */
    bool areMoreStudents();

    /**
     * @return Whether there are more rooms left to read from the
     *  rooms vector.
     */
    bool areMoreRooms();

    /**
     * @return The next student in the list of students.
     */
    std::string nextStudent();

    /**
     * @return The next room in the list of rooms.
     */
    Room nextRoom();

    /**
     * Reads a line parsed from the rooms file into a list of rooms.
     * @param line A line containing Room text
     * @return The Room read from the file
     */
    Room readRoom(const std::string& line);

    /**
     * Tokenizes a string of delimiter-separated elements.
     * @param str The string to tokenize
     * @param delim Delimiters to tokenize the string by
     * @return A vector of the tokenized items
     */
    std::vector<std::string> tokenize(const std::string& str, char delim);

    /**
     * Reads a file into a vector of lines.
     * @param file The file to read
     * @param lines The vector to fill with lines
     */
    void readFile(const std::string& file, std::vector<std::string>& lines);

    /**
     * @param filename The file to read. It may be stdin or similar.
     * @param map The options map (if needed)
     * @param lines Where to store the lines read from the file
     */
    void readFileGeneric(const std::string& filename, FileMap* map,
                         std::vector<std::string>* lines);
}
