#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool fillSchedule(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, size_t day, vector<size_t>& shiftsWorked);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    for(size_t i = 0; i < avail.size(); ++i){
        sched.push_back(vector<Worker_T>());
    }

    vector<size_t> shiftsWorked(avail[0].size(), 0);
    return fillSchedule(avail, dailyNeed, maxShifts, sched, 0, shiftsWorked);
}

// recursive helper function to fill the schedule
bool fillSchedule(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    vector<size_t>& shiftsWorked
)
{
    if(day == avail.size()){
        return true;
    }

    if(sched[day].size() == dailyNeed){
        return fillSchedule(avail, dailyNeed, maxShifts, sched, day + 1, shiftsWorked);
    }

    for(size_t worker = 0; worker < avail[0].size(); ++worker){
        if(avail[day][worker] && shiftsWorked[worker] < maxShifts && find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()){
            sched[day].push_back(worker);
            ++shiftsWorked[worker];

            if(fillSchedule(avail, dailyNeed, maxShifts, sched, day, shiftsWorked)){
                return true;
            }

            // backtrack
            sched[day].pop_back();
            --shiftsWorked[worker];
        }
    }

    return false;
}




