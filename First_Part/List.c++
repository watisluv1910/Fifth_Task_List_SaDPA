#include "List.h"

template<typename T>
inline List<T>::List(string name) {

	this->size = 0;
	this->head = nullptr;
	this->name = name;
}

template<typename T>
inline List<T>::~List() {

	clear();
}

template<typename T>
void List<T>::pushFront(T data) {

	head = new Node<T>(data, head);
	size++;
}

template<typename T>
void List<T>::remove(size_t index, size_t range) {

	while (range) {

		if (!index) {

			popFront();
			range--;
		}
		else {

			Node<T>* previous = this->head;

			// searching for the element previous to needed:
			for (size_t i = 0; i < index - 1; i++) {

				previous = previous->pNext;
			}

			Node<T>* toDelete = previous->pNext;
			previous->pNext = toDelete->pNext;
			delete toDelete;

			size--;
			range--;
		}
	}
}

template<typename T>
void List<T>::popFront() {

	Node<T>* temp = head;

	head = head->pNext;
	delete temp;

	this->size--;
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