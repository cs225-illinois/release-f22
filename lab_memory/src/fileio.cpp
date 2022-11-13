/**
 * @file fileio.cpp
 * Implementation of the fileio utility functions.
 */

#include "fileio.h"

/**
 * Utility functions for reading students/rooms from files.
 * @note There are NO bugs in fileio
 */
namespace fileio
{
    /**
     * Holds variables that only need to be accessed by the namespace
     *  itself. This is similar to private variables in a class.
     */
    namespace fileio_internal
    {
        /** A vector of students that were read from the file */
        std::vector<std::string>* students = NULL;

        /** A vector of Rooms that were read from the file */
        std::vector<std::string>* rooms = NULL;

        /** Represents the index of the student to read next */
        size_t students_i;

        /** Represents the index of the Room to read next */
        size_t rooms_i;
    }

    void init()
    {
        using namespace fileio_internal;
        students = new std::vector<std::string>;
        rooms = new std::vector<std::string>;
    }

    void halt()
    {
        using namespace fileio_internal;
        if (students != NULL)
            delete students;
        if (rooms != NULL)
            delete rooms;
    }

    void loadStudents(const std::string& file)
    {
        using namespace fileio_internal;
        students->clear();
        students_i = 0;
        readFile(file, *students);
        std::stable_sort(students->begin(), students->end());
    }

    void loadRooms(const std::string& file)
    {
        using namespace fileio_internal;
        rooms->clear();
        rooms_i = 0;
        readFile(file, *rooms);
    }

    int getNumStudents()
    {
        using namespace fileio_internal;
        return students->size();
    }

    int getNumRooms()
    {
        using namespace fileio_internal;
        return rooms->size();
    }

    bool areMoreStudents()
    {
        using namespace fileio_internal;
        return students_i < students->size();
    }

    bool areMoreRooms()
    {
        using namespace fileio_internal;
        return rooms_i < rooms->size();
    }

    std::string nextStudent()
    {
        using namespace fileio_internal;
        return (*students)[students_i++];
    }

    Room nextRoom()
    {
        using namespace fileio_internal;
        return readRoom((*rooms)[rooms_i++]);
    }

    Room readRoom(const std::string& line)
    {
        std::vector<std::string> split = tokenize(line, ',');
        std::string name = split[0];
        int capacity = atol(split[1].c_str()) / 2;
        Room r(name, capacity);
        return r;
    }

    std::vector<std::string> tokenize(const std::string& str, char delim)
    {
        std::vector<std::string> args;

        size_t start = 0;
        size_t end;
        for (end = str.find(delim); end != std::string::npos;
             end = str.find(delim, start)) {
            args.push_back(str.substr(start, end - start));
            start = end + 1;
        }
        args.push_back(str.substr(start, str.size() - start));

        return args;
    }

    void readFile(const std::string& file, std::vector<std::string>& lines)
    {
        readFileGeneric(file, NULL, &lines);
    }

    void readFileGeneric(const std::string& filename, FileMap* map,
                         std::vector<std::string>* lines)
    {
        std::ifstream infile;
        std::istream* fileptr;
        if (filename == "/dev/stdin")
            fileptr = &std::cin;
        else {
            fileptr = &infile;
            infile.open(filename.c_str(), std::fstream::in);
        }
        std::istream& file = *fileptr;

        std::vector<std::string>* section = NULL;
        if (map != NULL)
            section = &(*map)[""];
        else
            section = lines;

        while ((file.good() && file.peek() == '\n') || file.peek() == '\r')
            file.get(); // get '\n'

        while (file.good()) {
            // Read a line - A lot of code, I know, right?
            std::stringbuf linebuf;
            file.get(linebuf);
            while ((file.good() && file.peek() == '\n') || file.peek() == '\r')
                file.get(); // get '\n'
            std::string line = linebuf.str();
            size_t len = line.size();
            if (len == 0)
                continue;
            if (line[len - 1] == '\r')
                line.replace(--len, 1, "");

            if (len == 0 || line[0] == ';')
                continue; // skip comments

            if (map != NULL) {
                // Update the section
                if (line[0] == '[' && line[len - 1] == ']') {
                    section = &(*map)[line.substr(1, len - 2)];
                    continue;
                } else if (line[0] == '[' || line[len - 1] == ']') {
                    std::cout << "config.ini: Format error: " << line << std::endl;
                    exit(-1);
                }
            }

            // Or add the line/file to the section
            size_t delim_pos = line.find_first_of("?:");
            if (delim_pos == std::string::npos || map == NULL)
                section->push_back(line);
            else if ((line[delim_pos] == ':' && (delim_pos == 0))
                     || line.compare(0, delim_pos, "") == 0)
                section->push_back(
                    line.substr(delim_pos + 1, line.size() - delim_pos - 1));
        }

        if (filename != "/dev/stdin")
            infile.close();
    }
}
