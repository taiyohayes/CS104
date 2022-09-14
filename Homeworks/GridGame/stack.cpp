#include "stack.h"
#include <iostream>

using namespace std;

int main()
{
    Stack<int> myStack;
    cout << myStack.empty() << endl;
    myStack.push(88);
    cout << myStack.top() << endl;
    cout << myStack.empty() << endl;
    myStack.push(3);
    myStack.push(1234);
    cout << myStack.top() << endl;
    myStack.pop();
    cout << myStack.top() << endl;
    myStack.pop();
    cout << myStack.top() << endl;

    return 0;
}