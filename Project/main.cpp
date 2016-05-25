#include <limits>
#include <string>
#include <cassert>
#include <iostream>
#include "LinkedList.h"

using namespace std;

// Prototypes (allow implementation to follow main)
template <typename T, typename F>
void traverse(LinkedList<T> const& q, F& dataFunction);

void printString(string& testString);
void printCString(char const* testString);

int main()
{
    // Get ready.
    LinkedList<string&> referenceList;
    LinkedList<char const*> valueList;

    unsigned int numOfStrings = 8;
    string testStrings[] = {
            "alpha"
            , "bravo"
            , "charlie"
            , "charlie"
            , "dog"
            , "echo"
            , "foxtrot"
            , "golf"
    };
    string tempStr;

    // Test isEmpty function.
    assert(valueList.isEmpty() && referenceList.isEmpty());

    // Test enqueue.
    cout << "Testing enqueue..." << endl;
    for (unsigned int index = 0; index < numOfStrings; ++index)
    {
        referenceList.enqueue(testStrings[index]);
        valueList.enqueue(testStrings[index].c_str());
        assert(valueList.getFront() == referenceList.getFront().c_str());
        cout << "\tvalueList:";
        traverse(valueList, printCString);
        cout << endl;
    }

    // Test dequeue.
    cout << endl << "Testing dequeue..." << endl;
    for (;;)
    {
        cout << "Removing the front element:";
        printCString(valueList.getFront());
        valueList.dequeue();
        cout << endl << "\tvalueList:";
        traverse(valueList, printCString);
        cout << endl;

        if (valueList.isEmpty())
            break;
        else
            referenceList.dequeue();
    }

    // Test removal of only element.
    cout << endl << "Removing the only element from referenceList:";
    printCString(referenceList.getFront().c_str());
    referenceList.remove(testStrings[numOfStrings - 1]);
    cout << endl << "\treferenceList:";
    traverse(referenceList, printString);
    cout << endl;

    // Test containment check when empty
    cout << endl << "Testing search for: alpha";
    tempStr = "alpha";
    if (!referenceList.contains(tempStr))
    {
        cout << endl << "\treferenceList:";
        traverse(referenceList, printString);
        cout << endl;
    }

    // Test pop.
    cout << endl << "Testing pop..." << endl;
    cout << "Rebuilding list." << endl;
    for (unsigned int index = 0; index < numOfStrings; ++index)
        valueList.enqueue(testStrings[index].c_str());

    cout << "\tvalueList:";
    traverse(valueList, printCString);
    cout << endl;

    while (!valueList.isEmpty())
    {
        cout << "Removing the back element:";
        printCString(valueList.getBack());
        valueList.pop();
        cout << endl << "\tvalueList:";
        traverse(valueList, printCString);
        cout << endl;
    }

    // Test enqueue after removal.
    cout << endl << "Testing enqueue after removal..." << endl;
    for (unsigned int index = 1; index < numOfStrings; ++index)
    {
        referenceList.enqueue(testStrings[index]);
        valueList.enqueue(testStrings[index].c_str());
    }
    cout << "\tvalueList:";
    traverse(valueList, printCString);
    cout << endl;

    // Test unsuccessful search.
    cout << endl << "Testing unsuccessful search and remove:";

    if (valueList.contains(testStrings[0].c_str()))
    {
        assert(referenceList.contains(testStrings[0]) && "alpha not found in referenceList");
        cout << " " << testStrings[0];
        valueList.remove(testStrings[0].c_str());
        referenceList.remove(testStrings[0]);
        referenceList.remove(testStrings[0]);
        cout << endl << "\tvalueList:";
        traverse(valueList, printCString);
        cout << endl;
    }
    else
    {
        assert(!referenceList.contains(tempStr) && "alpha found in referenceList");
        cout << " ELEMENT NOT FOUND." << endl;
    }

    // Test removal of first element.
    cout << endl << "Testing search and remove:";

    if (valueList.contains(testStrings[1].c_str()))
    {
        assert(referenceList.contains(testStrings[1]) && "bravo not found in referenceList");
        cout << " " << testStrings[1];
        valueList.remove(testStrings[1].c_str());
        referenceList.remove(testStrings[1]);
        referenceList.remove(testStrings[1]);
        cout << endl << "\tvalueList:";
        traverse(valueList, printCString);
        cout << endl;
    }
    else
    {
        assert(!referenceList.contains(tempStr) && "bravo found in referenceList");
        cout << " ELEMENT NOT FOUND." << endl;
    }

    // Test removal of middle element.
    cout << "Testing search and remove:";

    if (valueList.contains(testStrings[4].c_str()))
    {
        assert(referenceList.contains(testStrings[4]) && "dog not found in referenceList");
        cout << " " << testStrings[4];
        valueList.remove(testStrings[4].c_str());
        referenceList.remove(testStrings[4]);
        referenceList.remove(testStrings[4]);
        cout << endl << "\tvalueList:";
        traverse(valueList, printCString);
        cout << endl;
    }
    else
    {
        assert(!referenceList.contains(tempStr) && "dog found in referenceList");
        cout << " ELEMENT NOT FOUND." << endl;
    }

    // Test removal of last element.
    cout << "Testing search and remove:";

    if (valueList.contains(testStrings[7].c_str()))
    {
        assert(referenceList.contains(testStrings[7]) && "golf not found in referenceList");
        cout << " " << testStrings[7];
        valueList.remove(testStrings[7].c_str());
        referenceList.remove(testStrings[7]);
        referenceList.remove(testStrings[7]);
        cout << endl << "\tvalueList:";
        traverse(valueList, printCString);
        cout << endl;
    }
    else
    {
        assert(!referenceList.contains(tempStr) && "golf found in referenceList");
        cout << " ELEMENT NOT FOUND." << endl;
    }

    // Test removal of all elements by method.
    cout << endl << "Removing all elements from valueList...";
    valueList.clear();
    cout << endl << "\tvalueList:";
    traverse(valueList, printCString);
    cout << endl;

    // Test destructor.
    cout << endl << "Adding elements to test descructor...";
    valueList.enqueue("hotel");
    valueList.enqueue("india");
    valueList.enqueue("juliet");

    cout << endl << "\tvalueList:";
    traverse(valueList, printCString);
    cout << endl << "\treferenceList:";
    traverse(referenceList, printString);
    cout << endl << endl;

    cout << "Press ENTER to continue..." << endl;
    while(cin.get() != '\n') {;}
    return 0;
}

template <typename T, typename F>
void traverse(LinkedList<T> const& q, F& dataFunction)
{
    printCString("[");

    for (auto itr = q.begin(); itr != q.end(); ++itr)
    {
        dataFunction(*itr);
    }
    printCString("]");
}

void printString(string& testString)
{
    cout << ' ' << testString;
}

void printCString(char const* testString)
{
    cout << ' ' << testString;
}
