// Matthew Kerr
//
// Used the fix from the following link in many parts of this code:
// http://stackoverflow.com/questions/8454539/trouble-with-templates-in-c-expected-primary-expression-before-token

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include "linkedlistexception.h"
#include "biginteger.h"

using namespace std;

template<class T> class LinkedList;
template<class T> ostream& operator<<(ostream& out, const LinkedList<T>& list);

template<class T>
class LinkedList
{
	public:
		template<class N>
		class Node
		{
			public:
				Node<N> * prev;
				Node<N> * next;
				N * data;
				
				Node(); // Nodes should always be initialized with some data
				Node(const N& data, Node<N> * next, Node<N> * prev); // Node explicit constructor
				Node(Node& orig); // Node copy constructor
				virtual ~Node(); // Node destructor		
		};
		
		template<class I>
		class Iterator
		{
			friend class LinkedList;
			
			public:
				typename LinkedList<I>::template Node<I> * curr;
				Iterator(typename LinkedList<I>::template Node<I> * pos) { curr = pos; }
				Iterator& operator++() { curr = curr->next; return *this; }
				Iterator operator++(int) { Iterator result = *this; ++*this; return result; }
				I& operator*() const { return *(curr->data); }
				bool operator==(const Iterator& rhs) const { return curr == rhs.curr; }
				bool operator!=(const Iterator& rhs) const { return !(curr == rhs.curr); }
		};
		
		int * size;
		Node<T> * head;
		
		LinkedList(); // default constructor
		LinkedList(LinkedList& orig); // copy constructor
		LinkedList(LinkedList&& orig); // move constructor
		virtual ~LinkedList(); // destructor
		LinkedList<T>& operator=(const LinkedList& orig); // = operator overload
		LinkedList<T>& operator=(LinkedList&& orig); // move = operator overload (move assignment overload)
		bool operator==(const LinkedList& rhs) const; // == operator overload
		T& operator[](int index); // [] writing overload
		const T& operator[](int index) const; // [] reading overload
		LinkedList<T> operator+(const LinkedList& rhs) const; // + operator overload, makes deep copy of data
		void add(T data); // add(data): adds at end of list
		void add(int index, T data); // adds at index, throw an exception if index is out of range
		bool remove(T data); // deletes the first instance of specified data, returns a bool
		T * removeIndex(int index); // deletes data at index and returns that data, throws and exception if index is bad
		bool removeAll(T data); // deletes all instances of the specified data, returns a bool
		void sort(); // sort linked list using < and ==
		LinkedList<T>::Iterator<T> begin() const { return LinkedList<T>::Iterator<T>(head->next); }
		LinkedList<T>::Iterator<T> end() const { return LinkedList<T>::Iterator<T>(head); }
		
	private:
		LinkedList(T data); // explicit constructor not allowed, always use the default
		
};


// << operator overload
template<class U>
ostream& operator<<(ostream& out, const LinkedList<U>& list)
{
	if (*(list.size) == 0)
	{
		cout << "Empty list" << endl;
	}
	else
	{
		typename LinkedList<U>::template Node<U> * temp = list.head;
		temp = temp->next;
		for (int i = 0; i < *(list.size); i++)
		{	
			cout << *(temp->data) << endl;
			temp = temp->next;
		}
	}
	return out;
}

////////////////////////////////////////////////////
// NODE FUNCTIONS
////////////////////////////////////////////////////

template<class T>
template<class N>
LinkedList<T>::Node<N>::Node()
{
	
}

template<class T>
template<class N>
LinkedList<T>::Node<N>::Node(const N& data, Node<N> * next, Node<N> * prev)
{
	T * temp = new T(data);
	this->data = temp;
	this->next = next;
	this->prev = prev;
}

template<class T>
template<class N>
LinkedList<T>::Node<N>::Node(Node& orig)
{
	this->data = orig->data;
	this->next = orig->next;
	this->prev = orig->prev;
}

template<class T>
template<class N>
LinkedList<T>::Node<N>::~Node()
{
	delete this->data;
	delete this->prev;
}

////////////////////////////////////////////////////
// LINKEDLIST FUNCTIONS
////////////////////////////////////////////////////

// default constructor
template<class T>
LinkedList<T>::LinkedList()// : head(NULL, NULL, NULL), tail(NULL, NULL, NULL), size(0)
{
	this->head = new LinkedList<T>::Node<T>();
	this->head->data = nullptr;
	this->head->next = this->head;
	this->head->prev = this->head;
	size = new int;
	*size = 0;
}

// copy constructor
template<class T>
LinkedList<T>::LinkedList(LinkedList& orig) : LinkedList()
{
	typename LinkedList<T>::template Node<T> * curr_orig = orig.head;
	curr_orig = curr_orig->next;
	for (int i = 0; i < *(orig.size); i++)
	{
		T temp = *(curr_orig->data); // temp to make sure the 2 Nodes don't point to the same place
		add(temp);
		curr_orig = curr_orig->next;
	}
}

// move constructor
template<class T>
LinkedList<T>::LinkedList(LinkedList&& orig) : LinkedList()
{
	typename LinkedList<T>::template Node<T> * curr_orig = orig.head;
	curr_orig = curr_orig->next;
	int temp = *(orig.size); // orig size is changing during the loop, so store this is something else
	for (int i = 0; i < temp; i++)
	{
		T temp = *(curr_orig->data);
		add(temp);
		curr_orig = curr_orig->next;
		orig.removeIndex(0);
	}
}

// move = operator overload (move assignment overload)
template<class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& orig)
{
	if (this != &orig) // don't copy if assigning to self
	{
		typename LinkedList<T>::template Node<T> * curr_orig = orig.head;
		curr_orig = curr_orig->next;
		int temp = *(orig.size); // orig size is changing during the loop, so store this is something else
		for (int i = 0; i < temp; i++)
		{
			T temp = *(curr_orig->data);
			add(temp);
			curr_orig = curr_orig->next;
			orig.removeIndex(0);
		}
	}
	return *this;
}

// destructor
template<class T>
LinkedList<T>::~LinkedList()
{
	int temp = *(this->size);
	for (int i = 0; i < temp; i++)
	{
		removeIndex(0);
	}
	delete size;
}

// = operator overload
template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& orig)
{
	LinkedList<T> list2 = orig;
	return list2;
}

// == operator overload
template<class T>
bool LinkedList<T>::operator==(const LinkedList& rhs) const
{
	if (*(this->size) != *(rhs.size))
	{
		return false;
	}
	typename LinkedList<T>::template Node<T> * curr_this = this->head;
	typename LinkedList<T>::template Node<T> * curr_rhs = rhs.head;
	curr_this = curr_this->next;
	curr_rhs = curr_rhs->next;
	for (int i = 0; i < *(this->size); i++)
	{
		if (*(curr_this->data) != *(curr_rhs->data))
		{
			return false;
		}
		curr_this = curr_this->next;
		curr_rhs = curr_rhs->next;
	}
	return true;
}

// [] writing overload
template<class T>
T& LinkedList<T>::operator[](int index)
{
	if (index < 0 || index >= *(this->size))
	{
		throw LinkedListException("Index out of range");
	}
	typename LinkedList<T>::template Node<T> * curr = this->head;
	curr = curr->next;
	for (int i = 0; i < index; i++)
	{
		curr = curr->next;
	}
	return *(curr->data);
}

// [] reading overload
template<class T>
const T& LinkedList<T>::operator[](int index) const
{
	if (index < 0 || index >= *(this->size))
	{
		throw LinkedListException("Index out of range");
	}
	typename LinkedList<T>::template Node<T> * curr = this->head;
	curr = curr->next;
	for (int i = 0; i < index; i++)
	{
		curr = curr->next;
	}
	return *(curr->data);
}

// + operator overload, makes deep copy of data
template<class T>
LinkedList<T> LinkedList<T>::operator+(const LinkedList& rhs) const
{
	LinkedList<T> result;
	
	typename LinkedList<T>::template Node<T> * curr_this = this->head;
	curr_this = curr_this->next;
	for (int i = 0; i < *(this->size); i++)
	{
		T * temp = new T(*(curr_this->data));
		result.add(*temp);
		curr_this = curr_this->next;
	}
	
	typename LinkedList<T>::template Node<T> * curr_rhs = rhs.head;
	curr_rhs = curr_rhs->next;
	for (int i = 0; i < *(rhs.size); i++)
	{
		T * temp = new T(*(curr_rhs->data));
		result.add(*temp);
		curr_rhs = curr_rhs->next;
	}
	return result;
}



// add(data): adds at end of list
template<class T>
void LinkedList<T>::add(T data)
{
	typename LinkedList<T>::template Node<T> * newNode = new LinkedList<T>::Node<T>(data, this->head, this->head->prev);
	this->head->prev->next = newNode;
	this->head->prev = newNode;
	*(this->size) = *(this->size) + 1;
}

// adds at index, throw an exception if index is out of range
template<class T>
void LinkedList<T>::add(int index, T data)
{
	if (index < 0 || index > *(this->size))
	{
		throw LinkedListException("Index out of range");
	}
	typename LinkedList<T>::template Node<T> * curr = this->head;
	curr = curr->next;
	for (int i = 0; i < index; i++)
	{
		curr = curr->next;
	}
	typename LinkedList<T>::template Node<T> * new_node = new LinkedList<T>::Node<T>(data, curr, curr->prev);
	curr->prev->next = new_node;
	curr->prev = new_node;
	*(this->size) = *(this->size) + 1;
}

// deletes the first instance of specified data, returns a bool
template<class T>
bool LinkedList<T>::remove(T data)
{
	if (*(this->size) == 0)
	{
		return false;
	}
	bool found = false;
	typename LinkedList<T>::template Node<T> * curr = this->head;
	curr = curr->next;
	for (int i = 0; i < *(this->size); i++)
	{
		if (*(curr->data) == data)
		{
			removeIndex(i);
			found = true;
			break;
		}
		curr = curr->next;
	}
	return found;
}

// deletes data at index and returns that data, throws and exception if index is bad
template<class T>
T * LinkedList<T>::removeIndex(int index)
{
	if (index < 0 || index >= *(this->size))
	{
		throw LinkedListException("Index out of range");
	}
	if (*(this->size) == 0)
	{
		throw LinkedListException("LinkedList is empty");
	}
	typename LinkedList<T>::template Node<T> * curr = this->head;
	curr = curr->next;
	for (int i = 0; i < index; i++)
	{
		curr = curr->next;
	}
	T * temp = curr->data;
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	*(this->size) = *(this->size) - 1;
	return temp;
}

// deletes all instances of the specified data, returns a bool
template<class T>
bool LinkedList<T>::removeAll(T data)
{
	if (*(this->size) == 0)
	{
		return false;
	}
	bool found = false;
	typename LinkedList<T>::template Node<T> * curr = this->head;
	curr = curr->next;
	for (int i = 0; i < *(this->size); i++)
	{
		if (*(curr->data) == data)
		{
			curr = curr->next;
			removeIndex(i);
			i--;
			found = true;
		}
		else
		{
			curr = curr->next;
		}
	}
	return found;
}

// sort linked list using < and ==
template<class T>
void LinkedList<T>::sort()
{
	if (*(this->size) == 0)
	{
		return;
	}
	typename LinkedList<T>::template Node<T> * last_sorted;
	typename LinkedList<T>::template Node<T> * sorted_walker;
	T first_unsorted_data;
	for (last_sorted = this->head->next; last_sorted != this->head->prev; last_sorted = last_sorted->next)
	{
		first_unsorted_data = *(last_sorted->next->data);
         
         for (sorted_walker = last_sorted; sorted_walker != this->head && *(sorted_walker->data) > first_unsorted_data; sorted_walker = sorted_walker->prev)
         {
            *(sorted_walker->next->data) = *(sorted_walker->data); 
         }
         *(sorted_walker->next->data) = first_unsorted_data;
	}
}

#endif