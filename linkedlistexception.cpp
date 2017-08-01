#include "linkedlist.h"
#include "linkedlistexception.h"
#include <iostream>
#include <string>

using namespace std;

LinkedListException::LinkedListException(string msg)
{
	cout << "LinkedList error occurred: " << msg << endl;
}

LinkedListException::~LinkedListException()
{
	
}