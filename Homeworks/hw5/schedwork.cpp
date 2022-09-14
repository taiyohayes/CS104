

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedule_helper(const AvailabilityMatrix& avail, const int& k, const int& m, const int& d, const int& n, DailySchedule& sched, int row, int col);
bool isValid(const AvailabilityMatrix& avail, const int& m, const int& d, const int& n, const DailySchedule& sched, const Worker_T& id);

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

    int k = int(avail[0].size());  // workers
    int n = int(avail.size());     // days
    int d = dailyNeed;
    int m = maxShifts;

    for (int i = 0; i < n; i++)
    {
        vector<Worker_T> vec;
        sched.push_back(vec);
        for (int j = 0; j < d; j++)
        {
            sched[i].push_back(INVALID_ID);        
        }
    }
    bool valid = schedule_helper(avail, k, m, d, n, sched, 0, 0);
    return valid;
}

bool schedule_helper(const AvailabilityMatrix& avail, const int& k, const int& m, const int& d,  const int& n, 
                    DailySchedule& sched, int row, int col)
{
    if (row == n-1 && col == d)
    {
        return true;
    }
    if (col == d)
    {
        col = 0;
        row++;
    }
    for (Worker_T id = 0; id < Worker_T(k); id++)
    {
        sched[row][col] = id;
        if (isValid(avail, m, d, n, sched, id))
        {
            if (schedule_helper(avail, k, m, d, n, sched, row, col+1))
            {
                return true;
            }
        }
        sched[row][col] = INVALID_ID;
    }
    return false;
}

bool isValid(const AvailabilityMatrix& avail, const int& m, const int& d, const int& n, const DailySchedule& sched, const Worker_T& id)
{
    int id_count = 0;
    for (int i = 0; i < n; i++)
    {
        int id_daily_count = 0;
        for (int j = 0; j < d; j++)
        {
            if (sched[i][j] == id)
            {
                id_daily_count++;
                if (avail[i][id] == false)
                {
                    return false;
                }
            }
        }
        if (id_daily_count > 1)
        {
            return false;
        }
        id_count += id_daily_count;
    }
    if (id_count > m)
    {
        return false;
    }
    return true;
}

