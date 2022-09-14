#include <iostream>
#include <map>
#include "Schedule.h"

using namespace std;

Schedule::Schedule(string name)
{
    mName = name;
}

bool Schedule::dropCourse(std::string name)
{
    // TO DO: if the course was not already in the map, return false
    // otherwise, remove it from the map and return true!
    if (courseMap.find(name) != courseMap.end())
    {
        courseMap.erase(name);
        return true;
    }
    return false;
}

bool Schedule::addCourse(Course* c)
{
    // TO DO: if the course was already in the map, return false
    // otherwise, add it to the map and return true!
    string name = c->getCourseName();
    if (courseMap.find(name) == courseMap.end())
    {
        courseMap.insert(std::make_pair(name, c));
        return true;
    }

    return false;
}

void Schedule::printAllAssignments()
{
    // TO DO: print out the name of each course, followed by the set of assignments.
    // for each assignment, display its name, its type (essay vs hw vs exam), and whether or not it was completed.
    // formatting is up to you, but make sure it's easy to read!
    std::map<std::string, Course*>::iterator courseIt;
    for (courseIt = courseMap.begin(); courseIt != courseMap.end(); ++courseIt)
    {
        std::cout << courseIt -> first << ": " << endl;
        std::set<Assignment*>::iterator assignIt;
        for (assignIt = courseIt->second->mAssignmentSet.begin(); assignIt != courseIt->second->mAssignmentSet.end(); ++assignIt)
        {
            Assignment* a = *assignIt;
            cout << "Assignment Name: " << a -> getName() << endl << "Assignment Type: " << a -> getType() << endl 
            << "Completed: " << a -> isComplete();
        }
    }
}

std::map<std::string, Course*> Schedule::getCourses()
{
    return courseMap;
}