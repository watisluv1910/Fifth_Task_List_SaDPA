#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>
#include "List.h"
#include "VariadicTable.h"
#include "List.c++"

using namespace std;

void outputMenu();
template<typename T>
void fillList(List<T>& list);
template<typename T>
void formList(List<T>& list_1, List<T>& list_2, List<T>& list);
template<typename T>
void sort(List<T>& list);
template<typename T>
void outputLists(List<T>& list_1, List<T>& list_2, List<T>& list_3);

int main() {

	List<char> list_1("List_1");
	List<char> list_2("List_2");
	List<char> list("List");

	outputMenu();

	cout << "\nYour choise is:\n";
	int chosenTask;

	cin >> chosenTask;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// while will lasts until '0' will be entered
	while (chosenTask) {

		switch (chosenTask) {

		case 1: {

			// '0' is used as a signal of the end of input
			cout << "\nEnter the elements of the " 
				<< list_1.get_name() << " list:\n";
			fillList(list_1);

			cout << "\nEnter the elements of the " 
				<< list_2.get_name() << " list:\n";
			fillList(list_2);
			break;
		}
		case 2: {

			// checking the existance of both base lists
			if (!list_1.get_size() || !list_2.get_size()) {

				cerr << "\nUnable to form new list due to the lack of "
					"it's parents. Try again.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}

			formList(list_1, list_2, list);
			break;
		}
		case 3: {

			size_t index = 0;
			cout << "\nEnter the number of the beginning element:\n";
			cin >> index;

			// checking right position enter
			// index as a position can't be lower than 1
			if (!cin.good() || index < 1 || index > list_1.get_size()) {

				cerr << "\nIncorrect number. Try again.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}

			index--; // position turns into index

			size_t range = 0;
			cout << "\nEnter the range:\n";
			cin >> range;

			// checking the ability to delete chosen number of elements
			if (!cin.good() || range < 1 || range > list_1.get_size() - index) {

				cerr << "\nIncorrect range. Try again.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}

			list_1.remove(index, range);
			break;
		}
		case 4: {

			if (list_2.get_size() < 2) {

				// sorting is useless if there is less than 2 elem in the list
				cerr << "\nUnable to sort " << list_2.get_name() 
					<< ". Try again.\n";
				break;
			}

			sort(list_2);
			break;
		}
		case 5: {

			string name = "";
			cout << "\nEnter the name of the list you want to delete:\n";
			getline(cin, name);

			if (name == list_1.get_name()) {

				list_1.clear();
			}
			else if (name == list_2.get_name()) {

				list_2.clear();
			}
			else if (name == list.get_name()) {

				list.clear();
			}
			else {

				cerr << "\nIncorrect name. Try again.\n";
				break;
			}
			break;
		}
		default:

			cerr << "\nIncorrect task number. Try again.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}

		cout << endl;
		system("pause");
		system("cls");

		outputMenu();

		if (list_1.get_size() || list_2.get_size() || list.get_size()) {

			// if all lists are empty table isn't displayed
			cout << "\nCurrent lists are:\n";
			outputLists(list_1, list_2, list);
		}

		cout << "\nYour next choise is:\n";
		cin >> chosenTask;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return 0;
}

void outputMenu() {

	cout << "Practical task num. 5 IKBO-03-21 Nasevich V.V.\n"
		"Variant num. 3.\n\nMenu:\n"
		"1)Enter '1' to fill the lists.\n"
		"2)Enter '2' to form the new list accroding to the task.\n"
		"3)Enter '3' to delete some elements of the first list.\n"
		"4)Enter '4' to sort the second list by ascend.\n"
		"5)Enter '5' to delete one of the lists.\n"
		"6)Enter '0' to close the programm.\n";
}

template<typename T>
void fillList(List<T>& list) {

	T temp;

	cin >> temp;

	while (temp != '0') {

		list.pushFront(temp);
		cin >> temp;
	}
}

template<typename T>
void formList(List<T>& list_1, List<T>& list_2, List<T>& list) {
	
	set<T> unique; // using set for sorting and filtering out duplicates
	for (size_t i = 0; i < list_1.get_size(); i++) {

		for (size_t j = 0; j < list_2.get_size(); j++) {

			// searching for the identical elements
			if (list_1[i] == list_2[j]) {

				unique.insert(list_1[i]);
			}
		}
	}
	
	for (auto& element : unique) { // writing elements of a set to a list

		list.pushFront(element);
	}
}

template<typename T>
void sort(List<T>& list) {

	// using vector of ASCII codes for sorting
	// also could be done with multiset
	vector<int> temp;

	for (size_t i = 0; i < list.get_size(); i++) {
		
		temp.push_back((int)list[i]);
	}

	
	sort(temp.begin(), temp.end()); // built-in ascending sort function

	// writing char equivalents of ASCII codes to a list
	for (size_t i = 0; i < list.get_size(); i++) {

		list[i] = (char)temp.at(i);
	}
}

template<typename T>
void outputLists(List<T>& list_1, List<T>& list_2, List<T>& list_3) {

	// creating an object of VariabicTable class 
	// with table header parameters:
	VariadicTable<size_t, T, T, T> table ({ "Num.",
		list_1.get_name(),
		list_2.get_name(),
		list_3.get_name(),
	});

	size_t maxSize = max(list_1.get_size(), max(list_2.get_size(), list_3.get_size()));

	// condition set, which allows to avoid out of range problem during 
	// filling of the table
	for (size_t i = 0; i < maxSize; i++) {

		if (list_1.get_size() <= i) {

			if (list_2.get_size() <= i) {

				table.addRow(i + 1, ' ', ' ', list_3[i]);
			}
			else if (list_3.get_size() <= i) {

				table.addRow(i + 1, ' ', list_2[i], ' ');
			}
			else {

				table.addRow(i + 1, ' ', list_2[i], list_3[i]);
			}
		}
		else if (list_2.get_size() <= i) {

			if (list_3.get_size() <= i) {

				table.addRow(i + 1, list_1[i], ' ', ' ');
			}
			else {

				table.addRow(i + 1, list_1[i], ' ', list_3[i]);
			}
		}
		else if (list_3.get_size() <= i) {
			
			table.addRow(i + 1, list_1[i], list_2[i], ' ');
		}
		else {

			table.addRow(i + 1, list_1[i], list_2[i], list_3[i]);
		}
	}

	// printing the formed table
	table.print(cout);
}
