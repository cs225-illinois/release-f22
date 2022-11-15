#include "schedule.h"
#include "tests_util.h"
#include <map>
#include <string>
#include <catch2/catch_test_macros.hpp>

using std::string;


void validColoring(const V2D &rosterList, const V2D &color, unsigned maxColor){
    
    std::map<std::string, std::string> nodeInfo;

    for(auto & time : color){
        for(unsigned long i = 1; i < time.size(); i++){
            nodeInfo[time[i]]= time[0]; 
           // std::cout << time[0] << " " << time[i] << std::endl;
        }
    }
    
    std::set<std::string> mc;
    std::map<std::string, std::set<std::string> > sMap; 
    for(auto & row : rosterList){
        std::string course = row[0];
        std::set<std::string> ts;
        for(unsigned long i = 1; i < row.size(); i++){
            std::string student = row[i];
            std::string tcolor = nodeInfo[course];
            
            if(sMap[student].count(tcolor)!=0){
                UNSCOPED_INFO("Course " + course + " has an edge with student " \
                + student + " that are both labeled " + tcolor);
            }

            REQUIRE(sMap[student].count(tcolor)==0);
            sMap[student].insert(tcolor);
            mc.insert(tcolor);
            //std::cout << tcolor << " " << mc.size() << std::endl;
        }
    }
    
    INFO("Number of unique colors in coloring exceeds allowable.");
    REQUIRE(mc.size() <= maxColor);
}


void verifySchedule(const V2D &rosters, const V2D &sched, unsigned slots) {

    REQUIRE(sched.size() == slots);

    // map of students to vector of courses
    std::map<string,std::vector<string> > student_schedule;
    // map of courses to exam slot id
    std::map<string, unsigned> exam_schedule;

    // map student schedule
    for(auto roster:rosters) {
        std::string course = roster[0];
        for(unsigned i = 1; i < roster.size(); ++i) {
            student_schedule[roster[i]].push_back(course);
        }
    }

    // map courses to time slots
    for(unsigned time_index = 0; time_index < sched.size(); ++time_index ){
        for(unsigned course_index = 1; course_index < sched[time_index].size(); ++course_index) {
            exam_schedule[sched[time_index][course_index]] = time_index;
        }
    }

    // verify each student 
    for(auto student:student_schedule) {
        std::vector<bool> busy(slots);
        for(auto course:student.second){
            auto exam_time = exam_schedule.find(course);
            REQUIRE(exam_time != exam_schedule.end() );
            unsigned time_index = exam_time->second;
            REQUIRE(busy[time_index] == false );
            busy[time_index] = true;
        }
    }

}