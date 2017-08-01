// Matthew Kerr

#include <string>
#include "linkedlist.h"
#include "linkedlistexception.h"
#include "biginteger.h"

using namespace std;

int getInt(int min, int max, string menu_type, string data_type);
void displayMenu(string data_type);
template<class T>
void performMenuChoice(LinkedList<T>& list, int menu_choice, string data_type);

int main()
{
	string data_type = "";
	int menu_choice = -1;
	menu_choice = getInt(1, 2, "data_type", "");
	
	LinkedList<int> int_list;
	LinkedList<BigInteger> bigint_list;
	cout << endl;
	if (menu_choice == 1)
	{
		int_list.add(0);
		int_list.add(7);
		int_list.add(4);
		int_list.add(1);
		int_list.add(6);
		data_type = "int";
	}
	else
	{
		bigint_list.add(BigInteger("0"));
		bigint_list.add(BigInteger("7"));
		bigint_list.add(BigInteger("4"));
		bigint_list.add(BigInteger("1"));
		bigint_list.add(BigInteger("6"));
		data_type = "bigint";
	}
	cout << "List populated with some default values" << endl << endl;
	while (menu_choice != 17)
	{
		menu_choice = getInt(1, 17, "full", data_type);
		if (menu_choice != 17)
		{
			if (data_type == "int")
			{
				performMenuChoice(int_list, menu_choice, data_type);
			}
			else
			{
				performMenuChoice(bigint_list, menu_choice, data_type);
			}
		}
		else
		{
			cout << endl << "Exiting..." << endl;
		}
	}
	return 0;
}

int getInt(int min, int max, string menu_type, string data_type)
{
	int user_input = -1;
	while (user_input == -1)
	{
		if (menu_type == "full")
		{
			displayMenu(data_type);
		}
		else if (menu_type == "data_type")
		{
			cout << "Choose a data type to test" << endl;
			cout << "1. int" << endl;
			cout << "2. BigInteger" << endl;
		}
		else if (menu_type == "index")
		{
			cout << "Choose an index [" << min << " - " << max << "]: ";
		}
		else if (menu_type == "data_value")
		{
			cout << "Enter a data value: [" << min << " - " << max << "]: ";
		}
		if (menu_type == "full" || menu_type == "data_type")
		{
			cout << "Enter choice: ";
		}
		cin >> user_input;
		if (cin.fail())
		{
			cout << endl << "Invalid choice (not int)" << endl << endl;
			cin.clear();
			cin.sync();
			user_input = -1;
		}
		else
		{
			if (user_input < min || user_input > max)
			{
				cout << endl << "Invalid choice (out of range)" << endl << endl;
				user_input = -1;
			}
			else
			{	
				return user_input;
			}
		}
	}
	return user_input;
}

void displayMenu(string data_type)
{
	cout << "Choose a function to test (data type = " << (data_type == "int" ? "int" : "BigInteger") << "):" << endl 
		 << "1.  copy constructor (deep copy)" << endl
		 << "2.  move constructor (&&) (C++11)" << endl
		 << "3.  = operator overload" << endl
		 << "4.  move = operator overload (&&)" << endl
		 << "5.  == operator overload" << endl
		 << "6.  [ ] operator overload (reading)" << endl
		 << "7.  [ ] operator overload (assignment)" << endl
		 << "8.  + operator overload" << endl
		 << "9.  << operator overload" << endl
		 << "10. add(data)" << endl
		 << "11. add(index, data)" << endl
		 << "12. remove(data)" << endl
		 << "13. remove(index)" << endl
		 << "14. removeAll(data)" << endl
		 << "15. sort" << endl
		 << "16. iterator" << endl
		 << "17. quit" << endl;
}

template<class T>
void performMenuChoice(LinkedList<T>& list, int menu_choice, string data_type)
{
	cout << endl;
	if (menu_choice == 1)
	{
		cout << "Testing copy constructor" << endl;
		LinkedList<T> list2(list);
		cout << "LinkedList 1:" << endl << list;
		cout << "LinkedList 2:" << endl << list2;
	}
	else if (menu_choice == 2)
	{
		cout << "Testing move constructor" << endl << endl;
		LinkedList<T> list2 = move(list);
		cout << "Moved data from LinkedList 1 to LinkedList 2" << endl;
		cout << endl << "LinkedList 1:" << endl << list;
		cout << endl << "LinkedList 2:" << endl << list2;
		for (int i = 0; i < *(list2.size); i++)
		{
			list.add(list2[i]);
		}
		cout << endl << "Original data put back into LinkedList 1 for further testing" << endl << endl;	
	}
	else if (menu_choice == 3)
	{
		cout << "Testing = operator overload" << endl << endl;
		LinkedList<T> list2 = list;
		cout << "LinkedList 1 assigned to LinkedList 2" << endl;
		cout << endl << "LinkedList 1:" << endl << list;
		cout << endl << "LinkedList 2:" << endl << list2;
		cout << endl;
	}
	else if (menu_choice == 4)
	{
		cout << "Testing move = operator overload (&&)" << endl << endl;
		LinkedList<T> list2;
		list2 = move(list);
		cout << "Moved data from LinkedList 1 to LinkedList 2" << endl;
		cout << endl << "LinkedList 1:" << endl << list;
		cout << endl << "LinkedList 2:" << endl << list2;
		for (int i = 0; i < *(list2.size); i++)
		{
			list.add(list2[i]);
		}
		cout << endl << "Original data put back into LinkedList 1 for further testing" << endl << endl;
	}
	else if (menu_choice == 5)
	{
		cout << "Testing == operator overload" << endl << endl;
		LinkedList<T> list2 = list;
		LinkedList<T> list3;
		cout << "Testing on identical lists (using = operator overload) returned: " << (list == list2 ? "true" : "false") << endl;
		cout << "Testing on non-identical lists returned: " << (list == list3 ? "true" : "false") << endl << endl;
	}
	else if (menu_choice == 6)
	{
		cout << "Testing [ ] operator overload (reading)" << endl << endl;
		int user_index = getInt(0, (*(list.size) - 1), "index", data_type);
		cout << "Data at list[" << user_index << "] = " << list[user_index] << endl << endl;
	}
	else if (menu_choice == 7)
	{
		cout << "Testing [ ] operator overload (assignment)" << endl << endl;
		int user_index = getInt(0, (*(list.size) - 1), "index", data_type);
		int user_data = getInt(-1000, 1000, "data_value", data_type);
		list[user_index] = user_data;
		cout << "Data at list[" << user_index << "] changed to " << user_data << endl << endl;
	}
	else if (menu_choice == 8)
	{
		cout << "Testing + operator overload" << endl << endl;
		cout << "Populating LinkedList 2 with values 0, 1, and 2" << endl;
		cout << "and using + operator overload on the 2 lists" << endl << endl;
		LinkedList<T> list2;
		list2.add(T(0));
		list2.add(T(1));
		list2.add(T(2));
		LinkedList<T> result = list + list2;
		cout << "Result:" << endl << result << endl;
		cout << "Adding both lists into new result LinkedList" << endl;
	}
	else if (menu_choice == 9)
	{
		cout << "Testing << operator overload" << endl << endl;
		cout << list << endl;
	}
	else if (menu_choice == 10)
	{
		cout << "Testing add(data)" << endl << endl;
		int user_data = getInt(-1000, 1000, "data_value", data_type);
		list.add(T(user_data));
		cout << endl << "Data " << user_data << " added to list" << endl << endl;
	}
	else if (menu_choice == 11)
	{
		cout << "Testing add(index, data)" << endl << endl;
		int user_index = getInt(0, (*(list.size) - 1), "index", data_type);
		int user_data = getInt(-1000, 1000, "data_value", data_type);
		list.add(user_index, T(user_data));
		cout << endl << "Data " << user_data << " added to list at index " << user_index << endl << endl;
	}
	else if (menu_choice == 12)
	{
		cout << "Testing remove(data)" << endl << endl;
		int user_data = getInt(-1000, 1000, "data_value", data_type);
		if (list.remove(T(user_data)))
		{
			cout << endl << "First instance of data " << user_data << " was found and removed" << endl << endl;
		}
		else
		{
			cout << endl << "First instance of data " << user_data << " was not found" << endl << endl;
		}
	}
	else if (menu_choice == 13)
	{
		cout << "Testing remove(index)" << endl << endl;
		int user_index = getInt(0, (*(list.size) - 1), "index", data_type);
		T * data = list.removeIndex(user_index);
		cout << endl << "Data value of " << *data << " was removed from index " << user_index << endl << endl;
	}
	else if (menu_choice == 14)
	{
		cout << "Testing removeAll(data)" << endl;
		int user_data = getInt(-1000, 1000, "data_value", data_type);
		if (list.removeAll(T(user_data)))
		{
			cout << endl << "All instances of data " << user_data << " were found and removed" << endl << endl;
		}
		else
		{
			cout << endl << "No instance of data " << user_data << " were found" << endl << endl;
		}
	}
	else if (menu_choice == 15)
	{
		cout << "Testing sort" << endl << endl;
		list.sort();
		cout << "List sorted" << endl << endl;
		cout << "Result:" << endl << list << endl;
	}
	else if (menu_choice == 16)
	{
		cout << "Testing iterator" << endl << endl;
		cout << "Old-style for loop:" << endl;
		for (typename LinkedList<T>::template Iterator<T> iter = list.begin(); iter != list.end(); ++iter)
		{
			cout << *iter << endl;
		}
		cout << endl << "Enhanced for loop:" << endl;
		for (T temp : list)
		{
			cout << temp << endl;
		}
		cout << endl;
	}
}