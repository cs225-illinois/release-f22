#include <iostream>
#include "schedule.h"

int main() {
    //std::cout << "Hello, mp_schedule!" << std::endl;

    //Graph myGraph("rosterList.txt", "studentList.txt");

    //V2D roster = file_to_V2D("../rosterList.txt");
    V2D roster = file_to_V2D("../tests/data/c5_s10_3_roster_errors.csv");

    /*
    for (int i = 0; i < (int) roster.size(); ++i){
        std::cout << "{ ";
        for(int j = 0; j < (int) roster[i].size()-1; ++j){
        std::cout << roster[i][j] << ", ";
        }
        std::cout << roster[i][roster[i].size()-1] << "}, \\" << std::endl;
    }
    */

    //V2D student = file_to_V2D("../studentList.txt");
    V2D student = file_to_V2D("../tests/data/c5_s10_3_students_errors.csv");

    /*
    for (int i = 0; i < (int) student.size(); ++i){
        std::cout << "{ ";
        for(int j = 0; j < (int) student[i].size()-1; ++j){
        std::cout << student[i][j] << ", ";
        }
        std::cout << student[i][student[i].size()-1] << "}, \\" << std::endl;
    }
    */

    
    V2D out = clean(roster, student);

    for (int i = 0; i < (int) out.size(); ++i){
        std::cout << "{ ";
        for(int j = 0; j < (int) out[i].size()-1; ++j){
        std::cout << "\"" << out[i][j] << "\", ";
        }
        std::cout << "\"" << out[i][out[i].size()-1] << "\"}, \\" << std::endl;
    }


  
    std::vector<std::string> timeSlots;
    timeSlots.push_back("0");
    timeSlots.push_back("1");
    timeSlots.push_back("2");
    //timeSlots.push_back("3");
    //Graph(out, timeSlots);

    V2D outSched = schedule(out, timeSlots);

    std::cout << "Coloring:" << std::endl;
    std::cout << "{ ";
    for (int i = 0; i < (int) outSched.size(); ++i){
        std::cout << "{ ";
        for(int j = 0; j < (int) outSched[i].size()-1; ++j){
        std::cout << outSched[i][j] << ", ";
        }
        std::cout << outSched[i][outSched[i].size()-1] << "}, \\" << std::endl;
    }
    std::cout << "}" << std::endl;
}