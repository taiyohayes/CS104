#include <iostream>
#include <map>
#include "Schedule.h"

using namespace std;

// the add/drop functions are rly simple but the print all assignments might give them some trouble

Schedule::Schedule(string name)
{
    mName = name;
}

bool Schedule::dropCourse(std::string name)
{
    // ANNOTATION 3: `map.erase(key_to_erase)` would erase all
    // elements with key equals to `key_to_erase` inside the
    // map, and it will return the number of elements erased.
    //
    // Since a map cannot contain duplicate keys, the return value
    // is either 0 or 1: 0 for the case where the key is not found,
    // and no element is erased; 1 for the key is found, and the
    // corresponding element is erased.
    //
    // Since the question asks to return true only if the course
    // is successfully removed, we return true only if the call
    // to erase actually erased 1 element.

    return courseMap.erase(name) == 1;

/*
    // ANNOTATION 4: An alternative would be to try finding
    // the element first in the map. If it does not exist,
    // do nothing and return false; otherwise, erase it
    // and return true.

    if (courseMap.find(name) == courseMap.end())
        return false; // can't drop it if it's not there!

    // otherwise, erase from map and return true
    courseMap.erase(name);
    return true;
*/
}

bool Schedule::addCourse(Course* c)
{

    // ANNOTATION 5: map.insert(std::make_pair(key_to_insert, value_to_insert))
    // would try to insert the pair [key_to_insert, value_to_insert] into the
    // map. It will return a pair that has those two elements:
    //
    // - second: a `bool`. It is true if the insertion is successful (i.e 
    //           `key_to_insert` does not originally exist in the map), and
    //           false if the insertion failed (i.e. the key `key_to_insert`
    //           already exist in the map)
    // - first: an iterator of `map`. If the insertion is successful (i.e. `second` is true),
    //          it will be an iterator to the element just inserted;
    //          otherwise, the insertion has failed (i.e. `second` is false),
    //          it will be an iterator to the element that originally existed
    //          in the map.
    //
    // This is exactly what we need for this member function: we need
    // to return true only if the course does not already exist in the
    // schedule, so we just call `insert` and check if the insertion was
    // successful.

    return courseMap
        .insert(std::make_pair(c->getCourseName(), c))
        .second;

/*
    // ANNOTATION 6: An alternative would, again, be to look
    // for the course in the map first. If it is found, return false;
    // otherwise, insert it with `map[key] = value` and return true.

    if (courseMap.find(c->getCourseName()) != courseMap.end())
        return false; // already in map, can't add

    // otherwise, add and return true
    courseMap[c->getCourseName()] = c;
    return true;

    // ANNOTATION 7: The syntax `map[key] = value` has a nuance.
    // It allows you to both insert a new element into the map
    // (i.e. key does not exist yet), or to modify the value of
    // an existent element in the map (i.e. `key` already exist).
    // 
    // It is also possible to just do `map[key]` which reads
    // the value of the element with key. However, this will create
    // a new element if `key` doesn't exist, and its value would be
    // the default value for the given value type (pointer -> nullptr, 
    // int -> 0, bool -> false, string -> "", etc.)
*/
}

void Schedule::printAllAssignments()
{
	cout << mName << "'s classes: " << endl << endl;

    // ANNOTATION 8: Note the type of iterators here. The iterator type is always
    // `map<key, value>::iterator`.

    for (map<string, Course*>::iterator it = courseMap.begin(); it != courseMap.end(); ++it) {
        Course* c = it->second;
        cout << "COURSE: ";
        cout << c->getCourseName() << endl
             << endl;

        set<Assignment*> assignmentSet = c->getAssignmentSet();

        // ANNOTATIONS 9: Note that we called `c->getAssignmentSet()` and stored
        // the value inside a variable `assignmentSet` in the above line.
        //
        // This is very important. Later we called `begin()` and `end()` on it,
        // and since this variable lives outside the loop, those iterators
        // returned would be pointing to this variable.
        //
        // If instead we did something like this:
        //
        //  for (it = c->getAssignmentSet().begin(); c != c->getAssignmentSet().end(); ++it)
        //
        // bad things can happen. Each time we call `getAssignmentSet`, it returns a copy
        // (this wouldn't happen if it returns a reference) of the assignment set. Thus, the
        // `begin()` and `end()` are actually called on two DIFFERENT sets! Two iterators to
        // two different sets are never comparable, and therefore this would result in a
        // segfault.

        int i = 0;
        for (set<Assignment*>::iterator it2 = assignmentSet.begin(); it2 != assignmentSet.end(); ++it2) {
            Assignment* a = *it2;

            i++;
            cout << "Assignment " + to_string(i) + ": " + a->getName() << endl;
            cout << a->getType() << endl;
            if (a->isComplete()) {
                cout << "Completed!" << endl
                     << endl;
            }
            else {
                cout << "Incomplete" << endl
                     << endl;
            }
        }
        cout << "--------------" << endl;

        // ANNOTATION 10: Note that many of you tried to do something like
        // `it2->getName()` or `it2->getType()` etc., as if `it2` is a pointer to
        // `Assignment`. It is not. It is "an iterator to a pointer to an assignment".
        // Hence, you need to derefernece the iterator first (`*it`) to get the pointer
        // (on line 131), and then call functions with `->` on the pointer (line 134-146).
        //
        // Conceptually, an iterator to a pointer is a double pointer (i.e. `Assignment**`,
        // notice the two stars)
    }
}

// used for testing size
std::map<std::string, Course*> Schedule::getCourses()
{
    return courseMap;
}