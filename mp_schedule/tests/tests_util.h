#pragma once

#include "schedule.h"

/**
 * This will test schedule using a coloring point of view
 * 
 * @param rosterList The cleaned rosters of the courses with one line per course
 * @param color The schedule of exams
 * @param maxColor The number of slots in in the schedule
 */
void validColoring(const V2D &rosterList, const V2D &color, unsigned maxColor);


/**
 * This will test if the students all have non-conflicting schedules
 * 
 * @param roster The cleaned rosters of the courses with one line per course
 * @param schedu The schedule of exams
 * @param slots The number of slots in in the schedule
 */
void verifySchedule(const V2D &rosters, const V2D &sched, unsigned slots);