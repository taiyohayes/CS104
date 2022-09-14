#include <string>

class Assignment {

public:
	Assignment();
	virtual ~Assignment();
	void setName(std::string name);
	std::string getName();
	double getPoints();
	int getTotalPoints();
	void setPoints(double points);
	void setTotalPoints(int totalPoints);
	bool isComplete();
	void complete();

	// ANNOTATION 1: This function must be virtual,
	// since we want classes deriving from assignment
	// to override its behavior (different assignment types
	// should, by definition, have different names for their
	// type)
	//
	// If it is not virtual, then whenever calling `ptr->getType()`
	// where `ptr` is a pointer of type `Assignment*`, we would always
	// be calling `getType()` implemented for the `Assignment` class,
	// even if the pointer is actually pointing to an `Essay`, e.g. 
	// `Assignment* ptr = new Essay;`
	// 
	virtual std::string getType();

private:
	std::string mName;
	double mPoints;
	int mTotalPoints;
	bool mComplete;
	int mPriority;
};

class Essay : public Assignment {

public:
	// ANNOTATION 2: The `virtual` keyword is not needed
	// for `getType()` if it is already present in `Assignment`.
	// If a member function has the same return type, same parameters, and
	// same qualifiers (such as `const`) as a virtual function in its base
	// class, it automatically becomes virtual and overrides the one in
	// the base.
	std::string getType();
	std::string getPrompt();
private:
	std::string mPrompt;
};

class Exam : public Assignment {

public:
	std::string getType();
};	

class Homework : public Assignment {

public:
	std::string getType();
};	