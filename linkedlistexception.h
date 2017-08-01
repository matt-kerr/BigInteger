#ifndef LINKEDLISTEXCEPTION_H
#define LINKEDLISTEXCEPTION_H
#include <iostream>
#include <string>

using namespace std;

class LinkedListException
{
	public:
		LinkedListException(string msg);
		virtual ~LinkedListException();
		
};

#endif