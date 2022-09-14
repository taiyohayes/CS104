#include "Assignment.h"
#include <iostream>

using namespace std;

Assignment::Assignment() {
	mName = "";
	mPoints = 0;
	mTotalPoints = 1;
	mComplete = false;
	mPriority = 0;
}

Assignment::~Assignment() {

}

void Assignment::setName(std::string name) {
	mName = name;
}

std::string Assignment::getName() {
	return mName;
}

std::string Assignment::getType() {
	return "Assignment";
}

bool Assignment::isComplete() {
	return mComplete;
}

void Assignment::complete() {
	mComplete = true;
}

// ended up not using these, but could have been a fun calculate GPA function!

// void Assignment::setPoints(double points) {
// 	mPoints = points;
// }

// void Assignment::setTotalPoints(int totalPoints) {
// 	mTotalPoints = totalPoints;
// }

// double Assignment::getPoints() {
// 	return mPoints;
// }

// int Assignment::getTotalPoints() {
// 	return mTotalPoints;
// }

std::string Essay::getType() {
	return "Essay";
}

std::string Essay::getPrompt() {
	return mPrompt;
}

std::string Exam::getType() {
	return "Exam";
}

std::string Homework::getType() {
	return "Homework";
}
