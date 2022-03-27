#include "List.h"

template<typename T>
inline List<T>::List(string name) {

	// constructor
	// class List fields initialization
	this->size = 0;
	this->head = nullptr;
	this->name = name;
}

template<typename T>
inline List<T>::~List() {

	// destructor
	clear(); // deleting the list
}

template<typename T>
void List<T>::pushFront(T data) {

	// creating new head Node object and head pointer update 
	head = new Node<T>(data, head);
	size++;
}

template<typename T>
void List<T>::remove(size_t index, size_t range) {

	// deleting Nodes obj in selected range starting from the selected index
	while (range) {

		if (!index) {

			// deleting from the beginning of the list
			popFront();
			range--;
		}
		else {

			Node<T>* previous = this->head;

			// searching for the element previous to needed:
			for (size_t i = 0; i < index - 1; i++) {

				previous = previous->pNext;
			}

			// creating temp object pointer
			Node<T>* toDelete = previous->pNext;
			// removing an object from the list
			previous->pNext = toDelete->pNext; 
			// deleting removed object
			delete toDelete;

			size--;
			range--;
		}
	}
}

template<typename T>
void List<T>::popFront() {

	Node<T>* temp = head; // creating temp object pointer

	head = head->pNext; // removing an object from the list

	delete temp; // deleting removed object

	size--;
}

template<typename T>
void List<T>::clear() {

	while (size) {

		popFront();
	}
}

template<typename T>
T& List<T>::operator[](const size_t index) {

	size_t counter = 0;
	Node<T>* current = this->head;

	while (current) {

		if (counter == index) {

			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}